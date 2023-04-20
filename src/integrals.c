// Enzo CADONI - LIS - 2022/2023
// Integral calculus functions

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Find the value of the integral of the function f using the trapezoidal rule
//   - inter : number of sub-intervals
//   - inf : inferior bound
//   - sup : superior bound
//   - f : pointer to a function of type 'double f(double x)'
double integral(int inter, double min, double max, double f(double)){
  double sum = .0, h = fabs(max-min) / inter;

  if(inter < 1)
    return 0;

  while(inter--)
    sum += f(min + inter * h);

  return ((h/2) * (f(min) + f(max) + 2 * sum));
}
