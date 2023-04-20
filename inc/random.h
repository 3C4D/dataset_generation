// Enzo CADONI - LIS - 2022/2023
// Random number generation function prototypes

#ifndef RANDOM_H_
#define RANDOM

// Give a random int number knowning normal distribution and bounds
//   - mean : mean
//   - std : standard deviation
//   - min, max : min < result < max
int rand_norm_int(int mean, int std, int min, int max);

#endif