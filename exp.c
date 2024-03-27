#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int main()
{
  int ran;
  while(1){

    ran = create_random(35, 700, 5);
    printf("%d\n", ran);
    sleep(1);
  }
}

