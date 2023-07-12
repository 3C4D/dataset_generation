// Enzo CADONI - LIS - 2022/2023
// Random number generation functions

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../inc/normal.h"

// Give a random int number knowning normal distribution and bounds
//   - mean : mean
//   - std : standard deviation
//   - min, max : min < result < max
int rand_norm_int(int mean, int std, int min, int max){
  int res;

  // We iterate while the number is not in the given range
  do{
    res = (int)(invnorm(((rand()%10000)*1.)/10000) * std + mean);
  }while(res < min || max < res);

  return res;
}