// Enzo CADONI - LIS - 2022/2023
// Dataset generation functions

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include "../inc/dataset.h"

// Generate a table file
//   - t : table to generate
void generate_table(table_t t){
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

// Generate a dataset directory
//   - ds : dataset to generate
void generate_dataset(dataset_t ds){
  int i;
  table_t *tables = ds.tables;

  // Try to create directory
  if(mkdir(ds.name, 0777)){
    perror("GENERATION ");
    exit(-1);
  }

  // Initialize uniform random seed
  srand(time(NULL));

  // Generate each table
  for(i = 0; i < ds.tableq; i++){
    generate_table(tables[i]);
  }
}