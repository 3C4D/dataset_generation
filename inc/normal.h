// Enzo CADONI - LIS - 2022/2023
// Normal distribution functions prototypes

#ifndef NORMAL_H_
#define NORMAL_H_

// Initialisation of the normal distribution
//   - mean : mean of the distribution
//   - std : standard deviation of the distribution
void init_normal(double _mean, double _std);

// Normal distribution function
double normal(double x);

// Retreive the X from a binary search of z in the inverse table
double invnorm(double z);

#endif