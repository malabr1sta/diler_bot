#include <stdio.h>
#include <stdlib.h>

#include "telegramm.h"


#define TEXT_HELP  "Hi %.50s\n1: Begin game\n2: End game\n"
#define TEXT_START  "Start game"
#define TEXT_END  "End game"

enum {size_buf_text=100};

char buf_text[size_buf_text] = {};


void response_bot(struct message_data *chat)
{
  static int result;
  int result_player;
  static int flag_game=0;
  static int flag_result=0;
  if(*chat->text == '2') {
    flag_game = 0;
    flag_result=0;
    send_message(chat->id, TEXT_END);
    return;
  }
  if(flag_result) {
    result_player = atoi(chat->text);
    if(result == result_player) {
      send_message(chat->id, "yes");
    } else {
      sprintf(buf_text, "Not correct, response = %d", result);
      send_message(chat->id, buf_text);
    }
    flag_result = 0;
    return;
  }
  if(flag_game) {
    result = 1111111111;
    flag_result=1;
    return;
  }
  if(*chat->text == 'h') {
    sprintf(buf_text, TEXT_HELP, chat->username);
    printf("%s\n", buf_text);
    send_message(chat->id, buf_text);
    return;
  }
  if(*chat->text == '1') {
    flag_game=1;
    send_message(chat->id, TEXT_START);
    return;
  }
  
}

int main()
{
  init_bot();
  polling_tgmm(&response_bot);
  return 0;
}
