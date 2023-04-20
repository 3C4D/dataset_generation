// Enzo CADONI - LIS - 2022/2023
// Integral calculus functions prorotypes

#ifndef INTEGRALS_H_
#define INTEGRALS_H_

// Find the value of the integral of the function f using the trapezoidal rule
//   - inter : number of sub-intervals
//   - inf : inferior bound
//   - sup : superior bound
//   - f : pointer to a function of type 'double f(double x)'
double integral(int inter, double min, double max, double f(double));

#endif
