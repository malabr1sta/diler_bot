#ifndef CHECK_MODUL_IMPORT_JSON_PARSER
#define CHECK_MODUL_IMPORT_JSON_PARSER

enum key_flag {is_key, is_not_key};


char *get_value_json(const char *str_json, const char *key);

bool is_letter(char c);

#endif
