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

1. Specify the generated data format (datasets, tables, etc).
2. Make our program full parametric and flexible.
3. Specify the synthax of the input file and make it exhaustive.
4. Read documentation and litterature to have consistent statistics to use.
5. Build various and different datasets.

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

### 1.2 - Generate random numbers based on the normal distribution

We can use normal distribution to generate random number, we
just have to choose a couple (mean, std) to have our distribution
and pick a random y and find it's invert in the distribution.

### 1.3 - Make the distribution flexible

We want the distribution to have parameters such as mean and
standard deviation.

### 1.4 - Specifying input file synthax

The program will take a file in input, this file has a grammar.

The grammar is specified in the file `docs/grammar_specs.md`
