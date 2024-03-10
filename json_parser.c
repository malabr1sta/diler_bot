#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "json_parser.h"


static bool is_letter(char c)
{
  if (isalnum(c) || c == '_' || c == '-') {
    return true;
  } 
  return false;
}

static bool check_key(const char **str_json, const char *key, char *prev_c)
{
  if(is_letter(**str_json) && !is_letter(*prev_c)) {
    for(; is_letter(**str_json) && *key; (*str_json)++, key++) {
      if(*key != **str_json) {
        break;
      }
      *prev_c=**str_json;
    }
  }
  return !*key? true: false;
}


static char *value_parser(const char **str_json, char *prev_c)
{
  char *value;
  value = malloc(sizeof(char));
  int count;
  count=0;
  for(; **str_json; *prev_c=**str_json, (*str_json)++) {
    if(is_letter(**str_json) && !is_letter(*prev_c)) {
      for(; **str_json != '"' && **str_json != ',' && **str_json != '}'; (*str_json)++, count++) {
        value[count] = **str_json;
        value = realloc(value, sizeof(char)*(count+1)); 
        *prev_c=**str_json;
      }
      value[count] = '\0';
      return value;
    }
  }
  return value;
}


char *get_value_json(const char *str_json, const char *key)
{
  char *value=NULL;
  char prev_c;
  enum key_flag flag = is_not_key;
  for(prev_c='\0'; *str_json; str_json++) {
    char c;
    c = *str_json;
    if(c == '{' || c == ',') {
      flag = is_key;
    }
    if(flag == is_key) {
      if(check_key(&str_json, key, &prev_c))
        return value_parser(&str_json, &prev_c);
      if(c == ':')
        flag = is_not_key;
    }
    prev_c=*str_json;
  }
  return value;
}
