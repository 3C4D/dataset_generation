// Enzo CADONI - LIS - 2022/2023
// Structures and functions prorotypes for tables and datasets

#ifndef DATASET_H_
#define DATASET_H_

#define TYPE1 1
#define TYPE2 2

#define FIXED_DIS 1
#define UNIFORM_DIS 2
#define NORMAL_DIS 3
#define _LINES_TOP_VAL 4
#define _COLUMNS_TOP_VAL 5

#define MAN_RANGE 1
#define AUTO_RANGE 2

#define EMPTY_DIAG 0
#define FULL_DIAG 1

typedef struct table_t{
  int type;               // Type of the table (1 or 2)
  int colq;               // Quantity of columns
  int lineq;              // Quantity of lines
  char **names;           // Names of the columns
  int *means;             // Means
  int *stds;              // Standard deviations
  int *dist_type;         // Distribution type
  int *range_type;        // Range type
  int *range_len;         // Range length
  int **range;            // Ranges
  int symmetry;           // Symmetry parameter
  int vectors;            // Vectors parameter
  int diagonal;           // Diagonal emptyness parameter
} *table_t;

typedef struct dataset_t{
  char *name;             // Name of the dataset
  table_t *tables;        // Tables in the dataset
  char **names;           // Names of the tables
  int tableq;             // Quantity of table
} dataset_t;

// Print a dataset
//   - ds : dataset to print
void print_dataset(dataset_t ds);

#endif