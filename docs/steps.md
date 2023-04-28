# Steps and specification

## Introduction

In this project, we want to generate datasets using diverse techniques of
random generation.

The datasets aims to be used as test subjects in the context of a multiparty
access control problem resolution algorithm.

In a way to generate datasets, we are gonna make a program that take a file
in input that contains datasets distributions or specifications infos.

The program will then generate datasets based on the specifications.

We will then use user studies and know statistics to build meaningful input
files for the program to generate consistent datasets.

## Needs

- Specify the generated data format (datasets, tables, etc).
- Make our program full parametric and flexible.
- Specify the syntax of the input file and make it exhaustive.
- Read documentation and litterature to have consistent statistics to use.
- Build various and different datasets.
- Make the tables format to be choosable (symetric, fixed, full random).

## Goals

1. Make a program that can generate parametric datasets 
2. Read litterature about user studies to catch real datas or statistics
3. Generate datasets

## 1 - Make a program that can generate random datasets

### 1.1 - Build a normal distribution

In order to calculate numbers based on a normal distribution,
we can make an approximation of the integral calculus on the
normal distribution function.

The method used to calculate is the trapezoidal rule.

We may also, in the future, want to have more distributions like chi-squared,
beta distribution or exponential eistribution.

### 1.2 - Generate random numbers based on the normal distribution

We can use normal distribution to generate random number, we
just have to choose a couple (mean, std) to have our distribution
and pick a random y and find it's invert in the distribution.

### 1.3 - Make the distribution flexible

We want the distribution to have parameters such as mean and
standard deviation.

In the case of a normal distribution, we may want to tell the program
the mean and the standard deviation of the distribution.

### 1.4 - Specifying generated data

The datasets we will generate will contain tables. These tables are containing
columns, lines, and numerical values (discret or continuous).

A dataset will be a folder containing a file per table.

We will need to consider enough table format such as single or double entry
tables.

### 1.5 - Specifying input file syntax and making an analyser

The program will take a file in input, this file has a grammar.

The grammar is specified in the file `docs/grammar_specs.md`

We use lex/yacc to build a syntactic analyser in order to parse
the file properly and to tell the user if he's making a lexical,
syntactic or semantic error.

### 1.6 - Build the whole program mixing the analyser and the generator

We link the analyser and the diverse generator in order to make the datasets
and the tables.