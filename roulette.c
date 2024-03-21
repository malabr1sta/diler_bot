#include <stdio.h>
#include <stdlib.h>

#include "roulette.h"


enum zero_result {
  amount_ind=0,
  change_ind=1,
  count_position_z = 4,
};

int *zero_shpil(int summ)
{
  int *result=malloc(sizeof(int) * 2);
  int amount, change;
  change = summ % (count_position_z * chip_size);
  amount = summ - change;
  amount /= count_position_z;
  result[change_ind] = change;
  if(amount > max_size) {
    int count_position = chip_size*(count_position_z-1);
    change = (amount - max_size) % count_position;
    result[change_ind] += change;
    result[change_ind] %= count_position;
    result[amount_ind] = (summ - result[change_ind] - max_size) / (count_position_z - 1);
  } else {
    result[amount_ind] = amount;
  }
  return result;
}


int main()
{
  int x;
  int *m;
  while(1) {
    scanf("%d", &x);
    m = zero_shpil(x);
    printf("result = %d, change = %d\n", m[0], m[1]);
    free(m);
  }
}
