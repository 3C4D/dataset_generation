// Enzo CADONI - LIS - 2022/2023
// Dataset generation functions

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../inc/dataset.h"
#include "../inc/random.h"

int generate_number(table_t t, int i, int ind){
  int m = -1;

  switch(t->dist_type[ind]){
    case FIXED_DIS:
      if(t->range_type[ind] == AUTO_RANGE){
        m = t->range[ind][0] + i;
      }
      else{
        m = t->range[ind][i];
      }
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

  return m;
}

// Generate a table file
//   - t : table to generate
void generate_table(table_t t, char *t_name){
  int i, j, k, m, ltv = -1, ctv = -1, dis = -1, c1, c2, ind, t_len;
  int *values = NULL, nb_val;
  FILE *fic = NULL;
  char *table_name;

  t_len = strlen(t_name);

  // We need the .csv extension to be more clear
  table_name = malloc(sizeof(char) * t_len + 5);

  strcpy(table_name, t_name);

  table_name[t_len] = '.';
  table_name[t_len+1] = 'c';
  table_name[t_len+2] = 's';
  table_name[t_len+3] = 'v';
  table_name[t_len+4] = '\0';

  // Check is the file exists
  if((fic = fopen(table_name, "r")) != NULL){
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
      fprintf(fic, "%s;", t->names[i]);
    }
    fprintf(fic, "%s\n", t->names[i]);
  }

  // Prepare TYPE2 table
  if(c2){
    for(i = 0; i < 3; i++){
      switch(t->dist_type[i]){
        case _LINES_TOP_VAL: ltv = i; break;
        case _COLUMNS_TOP_VAL: ctv = i; break;
        default: dis = i; break;
      }
    }

    // Write columns top values based on range type
    fprintf(fic, " ;");
    if(t->range_type[ctv] == AUTO_RANGE){

      values = malloc(sizeof(int) * (t->range[ctv][1] - t->range[ctv][0] + 2));

      for(i = t->range[ctv][0]; i < t->range[ctv][1]; i++){
        fprintf(fic, "%d;", i);
      }
      fprintf(fic, "%d\n", i);
    }
    else{

      values = malloc(sizeof(int) * t->colq + 1);

      for(i = 0; i < t->colq-1; i++){
        fprintf(fic, "%d;", t->range[ctv][i]);
      }
      fprintf(fic, "%d\n", t->range[ctv][i]);
    }
  }

  // Table filling
  for(i = 0; i < t->lineq; i++){
    // Lines top values for TYPE2 tables
    if(c2){
      if(t->range_type[ltv] == AUTO_RANGE){
          fprintf(fic, "%d;", t->range[ltv][0] + i);
      }
      else{
        fprintf(fic, "%d;", t->range[ltv][i]);
      }
    }

    // Table filling based on distribution types
    for(j = 0; j < t->colq; j++){
      if(c2 && ((t->symmetry && j < i) || (!t->diagonal && i == j))){
        fprintf(fic, "X");
        if(j < t->colq-1){
          fprintf(fic, ";");
        }
      }
      else{
        ind = c1 * j + c2 * dis;
        
        if(c1 || (c2 && !t->vectors)){
          fprintf(fic, "%d", generate_number(t, i, ind));
        }
        else{ // Generating the vectors (CONSIDERING AUTO RANGE)
          for(k = 0; k <= t->range[ind][1] - t->range[ind][0]; k++){
            values[k] = 0;
          }

          // Generating what value will appear in the vector
          nb_val = 0;
          for(k = t->range[ind][0]; k <= t->range[ind][1]; k++){
            m = generate_number(t, i, ind);
            if(values[m - t->range[ind][0]] == 0){
              nb_val++;
            }
            values[m - t->range[ind][0]] = 1;
          }

          // Writing in the file
          for(k = 0; k <= t->range[ind][1] - t->range[ind][0]; k++){
            if(values[k]){
              fprintf(fic, "%d", t->range[ind][0] + k);
              
              nb_val--;
              if(nb_val){
                fprintf(fic, ",");
              }
            }
          }
        }

        if(j == t->colq-1){
          fprintf(fic, "\n");
        }
        else{
          fprintf(fic, ";");
        }
      }
    }
  }

  // Close the file
  fclose(fic);
  free(table_name);
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
   generate_table(tables[i], ds.names[i]);
  }
}