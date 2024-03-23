#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

#include "telegramm.h"
#include "json_parser.h"

static char bot_id[size_buf_id] = {};
static char json_buffer_update[size_json_buffer_update] = {};

struct memory {
  char *response;
  size_t size;
};
 

static size_t cb(void *data, size_t size, size_t nmemb, void *clientp)
{
  size_t realsize = size * nmemb;
  struct memory *mem = (struct memory *)clientp;
  char *ptr = realloc(mem->response, mem->size + realsize + 1);
  if(!ptr)
    return 0;  /* out of memory! */
  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;
  return realsize;
}


static char *request_tgmm(char *tgmm_method, char *http_method, char *data)
{
  CURL *hnd = curl_easy_init();
  struct memory chunk = {0};
  struct curl_slist *headers = NULL;
  CURLcode ret;
  char url_buffer[size_url_buffer] = {};

  sprintf(url_buffer, URL_TGMM, bot_id, tgmm_method);

  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, http_method);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, cb);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);
  curl_easy_setopt(hnd, CURLOPT_URL, url_buffer);

  headers = curl_slist_append(headers, TYPE_REQUEST_TGMM);
  headers = curl_slist_append(headers, USER_AGENT_TGMM);
  headers = curl_slist_append(headers, TYPE_CONTENT_TGMM);
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

  if(*http_method == 'P')
    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, data);
  ret = curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);
  return chunk.response;
}


static int read_ln(FILE *f, char *s, int size)
/* function read first line in .env and write bot_id in *s */
{
  int count;
  char c;
  size--;
  for(count=0; size; size--, count++, s++) {
    c = fgetc(f);
    if(c == '\n') {
      *s = '\0';
      return count;
    }
    *s = c;
  }
  s[count] = '\0';
  return count;
}


void init_bot()
/* function reads id and writes data to bot_id */
{
  FILE *env;
  env = fopen(ENV_FILE_NAME, "r");
  if(!env) {
    perror(ENV_FILE_NAME);
    exit(1);
  }
  read_ln(env, bot_id, size_buf_id);
  fclose(env);
}

char *send_message(char *chat_id, char *text)
{
  char json_buffer_send[size_json_buffer_send] = {};
  struct memory chunk = {0};
  sprintf(
    json_buffer_send,
    "{\"chat_id\":\"%.50s\",\"text\":\"%.100s\"}",
    chat_id, text
  );
  return request_tgmm(SEND_MESSAGE, "POST", json_buffer_send);
}

char *get_update(char *offset, char *limit, char *timeout)
{
  struct memory chunk_update = {0};
  sprintf(
    json_buffer_update,
    "{\"offset\":%.20s,\"limit\":%.20s,\"timeout\":%.20s}",
    offset, limit, timeout
  );
  return request_tgmm(GET_UPDATES, "POST", json_buffer_update);
}


static struct message_data *init_chat(const char *response)
{
  struct message_data *chat;
  chat = malloc(sizeof(struct message_data));
  chat->id = get_value_json(response, FIELD_NAME_ID);
  chat->username = get_value_json(response, FIELD_NAME_USERNAME);
  chat->message_id = get_value_json(response, FIELD_NAME_MESSAGE_ID);
  chat->text = get_value_json(response, FIELD_NAME_TEXT);
  chat->date = get_value_json(response, FIELD_NAME_DATA);
  return chat;
}

static void free_chat(struct message_data *chat)
{
  free(chat->id);
  free(chat->username);
  free(chat->message_id);
  free(chat->text);
  free(chat->date);
  free(chat);
}


void polling_tgmm(void (*callback)(struct message_data*))
{
  struct message_data *chat;
  int val_sleep=polling_rate;
  int last_message_id=-1;
  int now_message_id;
  char *response;
  char *check_res;
  char *value=NULL;
  while(run) {
    response = get_update(
      GET_UPDATES_OFFSET,
      GET_UPDATES_LIMIT,
      GET_UPDATES_TIEMEOUT
    );
    check_res = get_value_json(response, "result\0");
    if(!is_letter(*check_res)) {
      continue;
    }
    chat = init_chat(response);
    free(response);
    now_message_id = atoi(chat->message_id);
    if(last_message_id != now_message_id) {
      last_message_id = now_message_id;
      (*callback)(chat);
    }
    free_chat(chat);
    sleep(val_sleep);
  }
}
