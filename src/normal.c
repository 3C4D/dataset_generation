// Enzo CADONI - LIS - 2022/2023
// Normal distribution functions

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../inc/constants.h"
#include "inverse_norm.h"

// Constant 1/(std * sqrt(2*PI))
static double const_a;
// Constant -1/(2*(std^2))
static double const_b;
static double mean;
static double std;

// Initialisation of the normal distribution
//   - mean : mean of the distribution
//   - std : standard deviation of the distribution
void init_normal(double _mean, double _std){
  const_a = 1/(_std * sqrt(2*PI));
  const_b = -1/(2 * _std * _std);
  std = _std;
  mean = _mean;
}

// Normal distribution function
double normal(double x){
  return const_a * pow(NUM_E, pow(x-mean, 2) * const_b);
}

// Retreive the X from a binary search of z in the inverse table
double invnorm(double z){
  int ecart = 125, act = 250, other = 0;
  double res;
  
  if(z <= 0 || 1 <= z){
    return 0;
  }

  if(z < 0.5){
    z = 1-z;
    other = 1;
  }

  while(ecart > 0){
    act += (1 - 2 * (inverse_norm[act] > z)) * ecart;
    ecart /= 2;
  }

  res = (act*1.)/100.;

  if(other){
    return 1-res;
  }

  return res;
}