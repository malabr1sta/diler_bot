#include <stdio.h>
#include <stdlib.h>

#include "roulette.h"


enum zero_result {
  amount_ind=0,
  change_ind=1,
};

enum ind {
  play_buy_ind=0,
  rest_ind=1,
  stright_ind = 0,
  spleet_ind = 1,
  street_ind = 2,
  corner_ind = 3,

  stight_cof = 1,
  spleet_cof = 2,
  street_cof = 3,
  corner_cof = 4,
};


static void sort_arr(int *arr_size, int *arr_cof, int *arr_twin, int len)
{
  for(int i=0; i < len - 1; i++) {
    for(int j=i+1; j < len; j++) {
      if(arr_size[i] > arr_size[j]) {
        int var;
        var = arr_size[j];
        arr_size[j] = arr_size[i];
        arr_size[i] = var;
        
        var = arr_cof[j];
        arr_cof[j] = arr_cof[i];
        arr_cof[i] = var;

        var = arr_twin[j];
        arr_twin[j] = arr_twin[i];
        arr_twin[i] = var;
      }
    }
  }
}


static int *copy_arr(const int *arr, int len)
{
  int *m = malloc(sizeof(int) * len);
  int *p = m;
  for(; len; len--, arr++, p++){
    *p = *arr;
  }
  return m;
}


int *roulette(int summ, const int *input, const int *twin)
{
  int *result=malloc(sizeof(int) * 2);
  int *arr_max_size=malloc(sizeof(int) * 4);
  int count;
  int *copy_twin, *copy_input;
  result[play_buy_ind] = 0;
  result[rest_ind] = 0;

  count = 0;
  for(int i=0; i < 4; i++) {
    count += input[i] * twin[i];
  }
  for(int i=0; i < 4; i++) {
    if(!input[i]) {
      arr_max_size[i] = 1000000;
      continue;
    }
    arr_max_size[i] = max_size * (i+1) / twin[i]; 
  }
  copy_twin = copy_arr(twin, 4);
  copy_input = copy_arr(input, 4);
  sort_arr(arr_max_size, copy_input, copy_twin, 4);

  for(int i=0; i < 4; i++) {
    if(arr_max_size[i] == 1000000) {
      break;
    }
    if(summ > arr_max_size[i] * count) {
      summ -= arr_max_size[i] * count;
      count -= copy_input[i] * copy_twin[i];
      result[play_buy_ind] = arr_max_size[i];
    } else {
      result[rest_ind] = summ % (count * chip_size);
      result[play_buy_ind] += (summ - result[rest_ind]) / count;
      return result;
    }
  } 
  free(arr_max_size);
  free(copy_twin);
  free(copy_input);
  return result;
}
