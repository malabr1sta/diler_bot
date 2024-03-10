#ifndef CHECK_MODUL_IMPORT_TELEGRAMM
#define CHECK_MODUL_IMPORT_TELEGRAMM


#define ENV_FILE_NAME           ".env"

#define URL_TGMM                "https://api.telegram.org/bot%.100s/%.50s" 
#define TYPE_REQUEST_TGMM       "accept: application/json" 
#define USER_AGENT_TGMM         "User-Agent: Telegram Bot SDK - (https://github.com/irazasyed/telegram-bot-sdk)"
#define TYPE_CONTENT_TGMM       "content-type: application/json"

#define SEND_MESSAGE            "sendMessage"

#define GET_UPDATES             "getUpdates"
#define GET_UPDATES_OFFSET      "-1"
#define GET_UPDATES_LIMIT       "1"
#define GET_UPDATES_TIEMEOUT    "0"


#define FIELD_NAME_ID           "id\0"
#define FIELD_NAME_USERNAME     "username\0"
#define FIELD_NAME_MESSAGE_ID   "message_id\0"
#define FIELD_NAME_TEXT         "text\0"
#define FIELD_NAME_DATA         "data\0"



enum setting {
  size_buf_id=100,
  size_url_buffer=300,
  size_json_buffer_send=200,
  size_json_buffer_update=200,
  polling_rate=5,
};

enum run_bot {run=1};

struct message_data {
  char *id;
  char *username;
  char *message_id;
  char *text;
  char *date;
};

void init_bot(void);

char *send_message(char *chat_id, char *text);
char *get_update(char *offset, char *limit, char *timeout);

void polling_tgmm(void (*callback)(struct message_data *, int*));

#endif
