// Enzo CADONI - LIS - 2022/2023
// Structures representing tables and datasets

#ifndef DATASET_H_
#define DATASET_H_

typedef struct table_t{
  int type;               // Type of the table (1 or 2)
  int colq;               // Quantity of columns
  int lineq;              // Quantity of lines
  char **names;           // Names of the columns
  int *means;             // Means
  int *stds;              // Standard deviations
  int *mins;              // Lower bounds
  int *maxs;              // Upper bounds
} table_t;

typedef struct dataset_t{
  table_t *tables;        // Tables in the dataset
  char **names;           // Names of the tables
  int tableq;             // Quantity of table
} dataset_t;

#endif