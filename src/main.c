// Enzo CADONI - LIS - 2022/2023
// Main function of the program

#include <stdlib.h>
#include <stdio.h>
#include "../obj/syntactic.tab.h"
#include "../inc/dataset.h"
#include "../inc/generation.h"
#include "../inc/colors.h"

extern FILE *yyin;
extern FILE *file;
extern dataset_t ds;
extern int semantic_err;

// Main function of the program
int main(int argc, char *argv[]){

  // Arguments number checking
  if(argc < 2){
    fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
    exit(-1);
  }

  // We redirect yacc standard input
  if((yyin = fopen(argv[argc-1], "r")) == NULL){
    perror("GENERATION ");
    exit(-1);
  }
  // We open the file again to print errors
  else{
    if((file = fopen(argv[argc-1], "r")) == NULL){
      perror("GENERATION ");
      exit(-1);
    }
  }

  // File parsing
  yyparse();

  // Semantic error case
  if(semantic_err){
    color(RED_BF);
    printf("Errors, generation failed\n");
    color(RESET);
    exit(-1);
  }

  // Dataset print
  print_dataset(ds);

  // Dataset generation
  generate_dataset(ds);

  exit(0);
}