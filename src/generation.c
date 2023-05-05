// Enzo CADONI - LIS - 2022/2023
// Dataset generation functions

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../inc/dataset.h"
#include "../inc/random.h"

// Generate a table file
//   - t : table to generate
void generate_table(table_t t, char *table_name){
  int i, j, m, ltv, ctv, dis = 0, c1, c2, ind;
  FILE *fic = fopen(table_name, "r");

  // Check is the file exists
  if(fic != NULL){
    fprintf(stderr, "File %s already exists\n", table_name);
    exit(-1);
  }

  // Try to create the file
  if((fic = fopen(table_name, "w")) == NULL){
    perror("GENERATION ");
    exit(-1);
  }

  // Condition variable to factorize code
  c1 = t->type == TYPE1;
  c2 = t->type == TYPE2;

  // Prepare TYPE1 table
  if(c1){
    // Write columns names
    for(i = 0; i < t->colq-1; i++){
      fprintf(fic, "%s,", t->names[i]);
    }
    fprintf(fic, "%s\n", t->names[i]);
  }

  // Prepare TYPE2 table
  if(c2){
    dis = -1; ltv = -1; ctv = -1;
    for(i = 0; i < 3; i++){
      switch(t->dist_type[i]){
        case _LINES_TOP_VAL: ltv = i; break;
        case _COLUMNS_TOP_VAL: ctv = i; break;
        default: dis = i; break;
      }
    }

    // Write columns top values based on range type
    fprintf(fic, " ,");
    if(t->range_type[ctv] == AUTO_RANGE){
      for(i = t->range[ctv][0]; i < t->range[ctv][1]; i++){
        fprintf(fic, "%d,", t->range[ctv][i]);
      }
      fprintf(fic, "%d\n", t->range[ctv][i]);
    }
    else{
      for(i = 0; i < t->colq-1; i++){
        fprintf(fic, "%d,", t->range[ctv][i]);
      }
      fprintf(fic, "%d\n", t->range[ctv][i]);
    }
  }

  // Table filling
  for(i = 0; i < t->lineq; i++){
    // Lines top values for TYPE2 tables
    if(c2){
      if(t->range_type[ltv] == AUTO_RANGE){
          fprintf(fic, "%d,", t->range[ltv][0] + i);
      }
      else{
        fprintf(fic, "%d,", t->range[ltv][i]);
      }
    }

    // Table filling based on distribution types
    for(j = 0; j < t->colq; j++){
      ind = c1 * j + c2 * dis;
      m = -1;
      switch(t->dist_type[ind]){
        case FIXED_DIS:
          m = t->range[ind][i];
          break;
        case NORMAL_DIS:
          m = rand_norm_int(
            t->means[ind],
            t->stds[ind],
            t->range[ind][0],
            t->range[ind][1]
          );
          break;
        case UNIFORM_DIS:
          m = t->range[ind][0] + rand()%(t->range[ind][1]);
          break;
      }
      fprintf(fic, "%d", m);
      if(j == t->colq-1){
        fprintf(fic, "\n");
      }
      else{
        fprintf(fic, ",");
      }
    }
  }

  // Close the file
  fclose(fic);
}

void generate_sym_table(table_t t, char *table_name){
  int i, j, m, ltv, ctv, dis = 0, **donnees;
  FILE *fic = fopen(table_name, "r");

  // Check is the file exists
  if(fic != NULL){
    fprintf(stderr, "File %s already exists\n", table_name);
    exit(-1);
  }

  // Try to create the file
  if((fic = fopen(table_name, "w")) == NULL){
    perror("GENERATION ");
    exit(-1);
  }

  donnees = malloc(sizeof(int *) * t->lineq+1);
  for(i = 0; i < t->lineq+1; i++){
    donnees[i] = malloc(sizeof(int) * t->colq+1);
  }

  dis = -1; ltv = -1; ctv = -1;
  for(i = 0; i < 3; i++){
    switch(t->dist_type[i]){
      case _LINES_TOP_VAL: ltv = i; break;
      case _COLUMNS_TOP_VAL: ctv = i; break;
      default: dis = i; break;
    }
  }

  // Write columns top values based on range type
  donnees[0][0] = 0;
  if(t->range_type[ctv] == AUTO_RANGE){
    j = 1;
    for(i = t->range[ctv][0]; i < t->range[ctv][1]; i++){
      donnees[0][j] = i;
      j++;
    }
  }
  else{
    for(i = 0; i < t->colq; i++){
      donnees[0][i+1] = t->range[ctv][i];
    }
  }

  // Table filling
  for(i = 0; i < t->lineq; i++){
    // Lines top values for TYPE2 tables
    if(t->range_type[ltv] == AUTO_RANGE){
      donnees[i+1][0] = t->range[ltv][0] + i;
    }
    else{
      donnees[i+1][0] = t->range[ltv][i];
    }

    // Table filling based on distribution types
    for(j = 0; j < t->colq; j++){
      m = -1;
      switch(t->dist_type[dis]){
        case FIXED_DIS:
          m = t->range[dis][i];
          break;
        case NORMAL_DIS:
          m = rand_norm_int(
            t->means[dis],
            t->stds[dis],
            t->range[dis][0],
            t->range[dis][1]
          );
          break;
        case UNIFORM_DIS:
          m = t->range[dis][0] + rand()%(t->range[dis][1]);
          break;
      }
      donnees[i+1][j+1] = m;
    }
  }

  // Make the symmetry
  for(i = 1; i < t->lineq+1; i++){
    for(j = i; j < t->colq+1; j++){
      donnees[j][i] = donnees[i][j];
    }
  }

  // Write the data table now symmetric
  fprintf(fic, " ,");
  for(i = 1; i < t->lineq; i++){
    fprintf(fic, "%d,", donnees[0][i]);
  }
  fprintf(fic, "%d\n", donnees[0][i]);
  for(i = 1; i < t->lineq+1; i++){
    for(j = 0; j < t->colq; j++){
      fprintf(fic, "%d,", donnees[i][j]);
    }
    fprintf(fic, "%d\n", donnees[i][j]);
  }

  for(i = 0; i < t->lineq+1; i++){
    free(donnees[i]);
  }
  free(donnees);
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

  // Change directory (cd)
  chdir(ds.name);

  // Initialize uniform random seed
  srand(time(NULL));

  // Generate each table
  for(i = 0; i < ds.tableq; i++){
    if(tables[i]->type == TYPE2 && tables[i]->symmetry){
      generate_sym_table(tables[i], ds.names[i]);
    }
    else{
      generate_table(tables[i], ds.names[i]);
    }
  }
}