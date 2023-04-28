// Enzo CADONI - LIS - 2022/2023
// Auxiliary functions for the yacc file

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/fct_aux_yacc.h"
#include "../inc/colors.h"

extern FILE *file;
extern int act_line;
extern int line_num;
extern int semantic_err;

// Print a semantic error using the program and an error message
void semantic_error(char *error){
  int i;
  char c = '\0';
  // More than one error, we ignore the rest
  if(act_line >= line_num){
    return;
  }

  // We parse till the line
  for(i = act_line; i < line_num-1; i++){
    c = '\0';
    while(c != '\n'){
      c = fgetc(file);
    }
  };
  act_line = line_num;

  color(MAGENTA_BF);
  fprintf(stderr, "\nSemantic error : %s\n", error);
  color(WHITE_BF);;
  fprintf(stderr, " %d |  ", line_num);
  color(RESET);
  c = '\0';
  c = fgetc(file);
  while(c != '\n' && c != EOF){
    fprintf(stderr, "%c", c);
    c = fgetc(file);
  }
  fprintf(stderr, "\n\n");
  semantic_err++;
}