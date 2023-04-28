// Enzo CADONI - LIS - 2022/2023
// Datasets and tables related functions

#include <stdlib.h>
#include <stdio.h>
#include "../inc/dataset.h"

// Print a table
//   - t : table to print
void print_table(table_t t){
  int i, j, range;

  printf("  type : %d\n", t->type);
  printf("  col_num : %d\n", t->colq);
  printf("  line_num : %d\n", t->lineq);
  
  // Calculate the number of range
  range = (t->type == TYPE2) * 4 + (t->type == TYPE1) * t->colq;

  // Printing each distribution/range/columns
  for(i = 0; i < range; i++){
    if(t->dist_type[i] == NORMAL_DIS
    || t->dist_type[i] == UNIFORM_DIS
    || t->dist_type[i] == FIXED_DIS){
      if(t->type == TYPE1){
        printf("  %s : ", t->names[i]);
      }
      else{
        printf("  distribution : ");
      }
    }

    // Distribution type (normal, uniform, fixed)
    switch(t->dist_type[i]){
      case _LINES_TOP_VAL: printf("  Lines top values : "); break;
      case _COLUMNS_TOP_VAL: printf("  Columns top values : "); break;
      case NORMAL_DIS:
        printf("normal(%d, %d), ", t->means[i], t->stds[i]);
        break;
      case UNIFORM_DIS: printf("uniform, "); break;
      case FIXED_DIS: printf("fixed, "); break;
    }

    // Print depends on the range type (auto/manual)
    switch(t->range_type[i]){
      case AUTO_RANGE:
        printf("range(%d, %d)\n", t->range[i][0], t->range[i][1]);
        break;
      case MAN_RANGE:
        printf("{");
        for(j = 0; j < t->range_len[i]-1; j++){
          printf("%d, ", t->range[i][j]);
        }
        printf("%d}\n", t->range[i][j]);
        break;
    }
  }
}

// Print a dataset
//   - ds : dataset to print
void print_dataset(dataset_t ds){
  int i;
  table_t *tables = ds.tables;
  char **names = ds.names;

  printf("\nDATASET %s\n\n", ds.name);
  
  // Print each table of the dataset
  for(i = 0; i < ds.tableq; i++){
    printf("TABLE %s\n", names[i]);
    print_table(tables[i]);
    putchar('\n');
  }
}

