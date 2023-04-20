# 1 - Build a normal distribution

In order to calculate numbers based on a normal distribution,
we can make an approximation of the integral calculus on the
normal distribution function.

The method used to calculate is the trapezoidal rule.

# 2 - Generate random numbers based on the normal distribution

We can use normal distribution to generate random number, we
just have to choose a couple (mean, std) to have our distribution
and pick a random y and find it's invert in the distribution.

# 3 - Make the distribution flexible

We want the distribution to have parameters such as mean and
standard deviation.

# 4 - Creating a standard file for generation

The program will take in input a file containing the probability
distributions which will be processed to generate the datasets

the file format will be as the following example :

```
dataset_quantity
table_quantity_1
table_name_1
table_type (let's say 1)
column_quantity
line_quantity
name1;mean1;stddev1;min;max
name2;mean2;stddev2;min;max
table_name_2
table_type (let's say 2)
column_quantity
line_quantity
lower_bound_col;upper_bound_col
lower_bound_line;upper_bound_line
mean;stddev;min;max
table_quantity_2
table_type (let's say 2)
column_quantity
line_quantity
mean;stddev;min;max
...
```

table_type :
- 1 = Simple columns with random cells
- 2 = 2x2 table with random columns and cells

