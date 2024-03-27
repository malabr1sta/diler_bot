#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "telegramm.h"
#include "roulette.h"


#define TEXT_HELP  "Hi %.50s\ns: Begin game\ne: End game\n"
#define TEXT_START  "Start game"
#define TEXT_END  "End game"

#define TEXT_ZERO_SHPIL "Roulette %d\nBet: %d $, in zero shpil"
#define TEXT_TIER "Roulette %d\nBet: %d $, in tier"
#define TEXT_ORFA "Roulette %d\nBet: %d $, in orphelins"
#define TEXT_VUAZEN "Roulette %d\nBet: %d $, in voisins"


#define TEXT_INPUT "Input play by..."
#define TEXT_INPUT_REST "Input rest..."

#define TEXT_RESULT  "Play by: %d $\nRest: %d $"

enum {
  size_buf_text=100,
  zero_shpil_ind=1,
  tier_ind=2,
  orfa_ind=3,
  vuazon_ind=4,

  min_zero = 4*chip_size,
  min_tier = 6*chip_size,
  min_orfa = 5*chip_size,
  min_vuazon = 9*chip_size,

  max_zero = max_size*7,
  max_tier = max_size*12,
  max_orfa = max_size*9,
  max_vuazon = max_size*17,
};
enum step {
  step_1=0,
  step_2=1,
  step_3=2, 
  step_4=3,
  step_5=4,
};

char buf_text[size_buf_text] = {};

const int zero_shpil[4] = {1, 3, 0, 0};
const int zero_shpil_twin[4] = {1, 1, 0, 0};

const int tier[4] = {0, 6, 0, 0};
const int tier_twin[4] = {0, 1, 0, 0};

const int orfa[4] = {1, 4, 0, 0};
const int orfa_twin[4] = {1, 1, 0, 0};

const int vuazon[4] = {0, 5, 1, 1};
const int vuazon_twin[4] = {0, 1, 2, 2};


int create_random(int min_num, int max_num, int step)
{
  int num;
  num = (1+(int)((double)max_num * rand() / (RAND_MAX + 1.0)) / step) * step;
  if(num < min_num) {
    num += min_num;
  }
  if(num > max_num) {
    num = max_num;
  }
  return num;
}


void response_bot(struct message_data *chat)
{
  static int *result;
  static int flag_step;
  int var;
  if(*chat->text == 'e') {
    flag_step = step_1;
    result = NULL;
    send_message(chat->id, TEXT_END);
    return;
  }
  if(*chat->text == 'h') {
    sprintf(buf_text, TEXT_HELP, chat->username);
    send_message(chat->id, buf_text);
    return;
  }
  if(*chat->text == 's') {
    flag_step = step_2;
    send_message(chat->id, TEXT_START);
  }
  
  switch(flag_step) {

    case(step_2):
      flag_step = step_3;
      var = create_random(1, 4, 1);
      if(var == zero_shpil_ind) {
        var = create_random(min_zero, max_zero, chip_size);
        sprintf(buf_text, TEXT_ZERO_SHPIL, max_size, var);
        send_message(chat->id, buf_text);
        result = roulette(var, zero_shpil, zero_shpil_twin);
        send_message(chat->id, TEXT_INPUT);
        return;
      }
      if(var == tier_ind) {
        var = create_random(min_tier, max_tier, chip_size);
        sprintf(buf_text, TEXT_TIER, max_size, var);
        send_message(chat->id, buf_text);
        result = roulette(var, tier, tier_twin);
        send_message(chat->id, TEXT_INPUT);
        return;
      }
      if(var == orfa_ind) {
        var = create_random(min_orfa, max_orfa, chip_size);
        sprintf(buf_text, TEXT_ORFA, max_size, var);
        send_message(chat->id, buf_text);
        result = roulette(var, orfa, orfa_twin);
        send_message(chat->id, TEXT_INPUT);
        return;
      }
      if(var == vuazon_ind) {
        var = create_random(min_vuazon, max_vuazon, chip_size);
        sprintf(buf_text, TEXT_VUAZEN,  max_size, var);
        send_message(chat->id, buf_text);
        result = roulette(var, vuazon, vuazon_twin);
        send_message(chat->id, TEXT_INPUT);
        return;
      }

    case(step_3):
      flag_step = step_4;
      send_message(chat->id, TEXT_INPUT_REST);
      return;

    case(step_4):
      flag_step = step_2;
      sprintf(buf_text, TEXT_RESULT, result[0], result[1]);
      send_message(chat->id, buf_text);
      free(result);
      return;
      
  }
  
}


int main()
{
  srand(time(NULL));
  init_bot();
  polling_tgmm(&response_bot);
  return 0;
}
