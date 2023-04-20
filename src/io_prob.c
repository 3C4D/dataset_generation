// Enzo CADONI - LIS - 2022/2023
// IO functions processing probability distributions files

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "dataset.h"
#include "alloc.h"

FILE *open_file_rd(char *filename){
  FILE *file = fopen(filename, "r");          // Open the file
  if(file == NULL){                           // Problem at opening the file
    perror("Probability distribution IO ");
    exit(-1);
  }
  return file;
}

int quantity_or_type_rd(FILE *file, int type, int max_len, int line){
  char *buffer = NULL, *end;
  ssize_t nb_read = 0;
  size_t str_len;
  int tmpl;

  buffer = NULL;                                // Buffer empty
  nb_read = getline(&buffer, &str_len, file);   // Read the line
  tmpl = (int)strtol(buffer, &end, 10);         // Read the long, cast it

  // Line too long or not an int, we use the \n to check if the line is ok
  if(nb_read-1 > max_len || nb_read-1 < 1 || *end != '\n'){
    fprintf(
      stdout,
      "Probability IO : Bad quantity line %d (not an integer ?)\n",
      line
    );
    exit(-1);
  }

  // Wrong type
  if(type && tmpl != 1 && tmpl != 2){
    fprintf(
      stderr,
      "Probability IO : Wrong table type line %d\n",
      line
    );
    exit(-1);
  }

  free(buffer);

  return tmpl;
}

void read_complex_table_info(FILE *file, table_t *t, int line){
  int i = 2, j = 2, tmpl;
  char *token, *end, *buffer = NULL;
  size_t str_len;

  while(i--){
    j = 2;
    getline(&buffer, &str_len, file);   // Read the line
    token = strtok(buffer, ";");                  // Read the first token
    while(j--){
      if(token == NULL){                          // Less than 2 tokens
        fprintf(stderr, "Not enough bounds\n");
        exit(-1);
      }

      tmpl = (int)strtol(token, &end, 10);
      if(token == end){                           // Can't read a long
        fprintf(stderr, "Invalid value for bound\n");
        exit(-1);
      }

      switch(i){
        case 1: t->mins[2-i] = tmpl; break;
        case 0: t->maxs[2-i] = tmpl; break;
      }

      token = strtok(NULL, ";");                  // Read the next token
    }

    if(token != NULL){                            // More than 2 tokens
      fprintf(stderr, "Too many bounds\n");
      exit(-1);
    }
  }

  i = 4;
  getline(&buffer, &str_len, file);               // Read the line
  token = strtok(buffer, ";");                    // Read the first token
  while(i--){
    if(token == NULL){                            // Less than 4 tokens
      fprintf(stderr, "Not enough infos\n");
      exit(-1);
    }

    tmpl = (int)strtol(token, &end, 10);
    if(token == end){                             // Can't read a long
      fprintf(stderr, "Invalid value for info\n");
      exit(-1);
    }

    switch(i){
      case 3: t->means[0] = tmpl; break;
      case 2: t->stds[0] = tmpl; break;
      case 1: t->mins[0] = tmpl; break;
      case 0: t->maxs[0] = tmpl; break;
    }

    token = strtok(NULL, ";");                    // Read the next token
  }

  if(token != NULL){                              // More than 4 tokens
    fprintf(stderr, "Too many infos\n");
    exit(-1);
  } 
}

void read_tables(FILE *file, dataset_t *ds, int ds_num, int quant, int line){
  table_t *t;
  size_t str_len;
  int table_num = 0, nb_read;

  // Iterate over tables of the ds
  while(table_num < quant){
    // Catch the table
    t = &ds[ds_num].tables[table_num];

    // Read table name
    nb_read = getline(&ds[ds_num].names[table_num], &str_len, file);
    if(nb_read > 100){
      fprintf(
        stderr,
        "Probability IO : Table name line %d too long (100 char max)\n",
        line
      );
    }
    line++;

    // Read table type, line quantity and column quantity
    t->type = quantity_or_type_rd(file, 1, 1, line++);
    t->colq = quantity_or_type_rd(file, 0, 3, line++);
    t->lineq = quantity_or_type_rd(file, 0, 3, line++);

    // Double factor table
    if(t->type == 2){
      // Read infos of the table
      t->mins = safe_alloc(3 * sizeof(char *));
      t->maxs = safe_alloc(3 * sizeof(char *));
      t->means = safe_alloc(sizeof(char *));
      t->stds = safe_alloc(sizeof(char *));
      read_complex_table_info(file, t, line++);
    }
    // Simple table
    else{
      t->names = safe_alloc(t->colq * sizeof(char *));
      t->means = safe_alloc(t->colq * sizeof(char *));
      t->stds = safe_alloc(t->colq * sizeof(char *));
      t->mins = safe_alloc(t->colq * sizeof(char *));
      t->maxs = safe_alloc(t->colq * sizeof(char *));

      // read_table_info(file, t, 0, line++);
    }

    table_num++;
    break;
  }
}

void read_datasets(FILE *file, dataset_t *ds, int quant, int line){
  int ds_num = 0;

  // Loop over datasets
  while(ds_num < quant){

    // Read the table quantity of the ds
    ds[ds_num].tableq = quantity_or_type_rd(file, 0, 3, line++);

    // Allocate the tables
    ds[ds_num].tables = safe_alloc(ds[ds_num].tableq * sizeof(table_t));
    ds[ds_num].names = safe_alloc(ds[ds_num].tableq * sizeof(table_t));

    // Read the tables
    read_tables(file, ds, ds_num, ds[ds_num].tableq, line);

    ds_num++;
    break;
  }
}

// Read a file containing datasets/tables specs
//   - filename : filename
void read_prob_file(char *filename){
  int line = 1, ds_q;
  FILE *file;
  dataset_t *ds;

  // Open file
  file = open_file_rd(filename);

  // Read datasets quantity
  ds_q = quantity_or_type_rd(file, 0, 2, line);

  // Allocate datasets array
  ds = safe_alloc(ds_q * sizeof(dataset_t));

  // Read the datasets
  read_datasets(file, ds, ds_q, line+1);
}