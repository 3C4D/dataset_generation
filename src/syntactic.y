%{
// Enzo CADONI - LIS - 2022/2023
// Syntactic analyser producer (Yacc part)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/colors.h"
#include "../inc/dataset.h"
#include "../inc/fct_aux_yacc.h"
#include "../inc/alloc.h"

int yylex();
int yyerror();

FILE *file;
int act_line;
int line_num;

int semantic_err = 0;

int table_number;

extern char *yytext;
extern FILE *yyin;
extern int column;

// Final Structures
dataset_t ds;

// Diverse accumulators
int nb_table = 0;
int col_count;
int nb_range;
int range_size;
int nb_int_list;
int size_sent;

// Flags for tables attributes
int flags[] = {0, 0, 0, 0, 0, 0};
%}

%token DATASET TABLE INFOS CONTENT TP BEG END IDF SEM
%token OP CP COM NORMAL UNIFORM FIXED DISTRIBUTION COLUMNS LINES
%token RANGE LINES_TOP_VAL COLUMNS_TOP_VAL TYP1 TYP2
%token SYMMETRY _TRUE _FALSE VECTORS DIAGONAL EMPTY FULL

%union{
  int typ1;
  double typ2;
}

%token<typ1> INT
%token<typ2> REAL

%%
  // Beginning of the dataset description
  dataset : DATASET IDF {
    ds.name = strdup(yytext); 
  } TP INT BEG {
    ds.names = safe_alloc($5 * sizeof(char *));
    ds.tables = safe_alloc($5 * sizeof(table_t *));
    for(int i = 0; i < $5; i++){
      ds.tables[i] = safe_alloc(sizeof(struct table_t));
      ds.names[i] = NULL;
    }
    ds.tableq = $5;
  } tables END;

  // Tables (verification of the tables quantity)
  tables :
    table {
      nb_table++;
      if(nb_table == ds.tableq){
        char error[100];
        sprintf(
          error,
          "Too many tables, expected %d, found %d",
          ds.tableq, nb_table+1
        );
        semantic_error(error);
      }
    } tables
  | table {
      nb_table++;
      if(nb_table < ds.tableq){
        char error[100];
        sprintf(
          error,
          "Too few tables, expected %d, found %d",
          ds.tableq, nb_table
        );
        semantic_error(error);
      }
  };

  table : table_typ1 | table_typ2;

  // Type 1 table
  table_typ1 : TABLE {
    ds.tables[nb_table]->type = TYPE1;
    for(int i = 0; i < 6; i++)
      flags[i] = 0;
    nb_range = 0;
    ds.tables[nb_table]->range = safe_alloc(
      sizeof(int *) * ds.tables[nb_table]->colq
    );
    range_size = ds.tables[nb_table]->lineq;
  } TYP1 IDF {
    int i;
    ds.names[nb_table] = strdup(yytext);

    for(i = 0; i < ds.tableq; i++){
      if(ds.names[i] != NULL
      && !strcmp(ds.names[i], ds.names[nb_table])
      && i != nb_table){
        char error[100];
        sprintf(error, "A table is already named %s", ds.names[i]);
        semantic_error(error);
      }
    }
  } BEG content_typ1 END;
  
  // Type 2 table
  table_typ2 : TABLE {
    ds.tables[nb_table]->type = TYPE2;
    for(int i = 0; i < 6; i++)
      flags[i] = 0;
    ds.tables[nb_table]->range = safe_alloc(sizeof(int *) * 3);
    nb_range = 0;

    ds.tables[nb_table]->colq = -1;
    ds.tables[nb_table]->lineq = -1;

    ds.tables[nb_table]->means = safe_alloc(sizeof(int) * 4);
    ds.tables[nb_table]->stds = safe_alloc(sizeof(int) * 4);
    ds.tables[nb_table]->dist_type = safe_alloc(sizeof(int) * 4);
    ds.tables[nb_table]->range_type = safe_alloc(sizeof(int) * 4);
    ds.tables[nb_table]->range_len = safe_alloc(sizeof(int) * 4);
  } TYP2 IDF {
    int i;
    ds.names[nb_table] = strdup(yytext);

    for(i = 0; i < ds.tableq; i++){
      if(ds.names[i] != NULL
      && !strcmp(ds.names[i], ds.names[nb_table])
      && i != nb_table){
        char error[100];
        sprintf(error, "A table is already named %s", ds.names[i]);
        semantic_error(error);
      }
    }
  } BEG content_typ2 END;

  // Type 1 table description
  content_typ1 :
    content_typ1_attr content_typ1
  | content_typ1_attr
  ;
  
  content_typ1_attr :
    columns_typ1
  | lines_num
  ;

  // Type 2 table description
  content_typ2 :
    content_typ2_attr content_typ2
  | content_typ2_attr
  ;

  content_typ2_attr :
    symmetry
  | columns_num
  | lines_num
  | distr_attr
  | {size_sent = 1;} lines_top_val {size_sent = 0;}
  | {size_sent = 1;} columns_top_val {size_sent = 0;}
  | vectors
  | diagonal
  ; 

  // Symmetry parameter for double entry tables
  symmetry :
      SYMMETRY TP _TRUE SEM {
        if(ds.tables[nb_table]->colq == -1
        || ds.tables[nb_table]->lineq == -1){
          line_num++;
          semantic_error(
            "You must precise column quantity and line quantity before symmetry parameter"
          );
          line_num--;
          ds.tables[nb_table]->symmetry = 0;
        }
        else if(ds.tables[nb_table]->colq != ds.tables[nb_table]->lineq){
          line_num++;
          semantic_error(
            "Line and column quantity must be the same to activate symmetry parameter"
          );
          line_num--;
          ds.tables[nb_table]->symmetry = 0;
        }
        else{
          ds.tables[nb_table]->symmetry = 1;
        }
      }
    | SYMMETRY TP _FALSE SEM {
      ds.tables[nb_table]->symmetry = 0;
    }
    ;

  // Lines quantity
  lines_num : LINES TP INT SEM {
    flags[0]++;
    if(flags[0] > 1){
      line_num++;
      semantic_error("You already precised line quantity for this table");
      line_num--;
    }

    ds.tables[nb_table]->lineq = $3;
  };

  // Column quantity
  columns_num : COLUMNS TP INT SEM {
    flags[2]++;
    if(flags[2] > 1){
      line_num++;
      semantic_error("You already precised column quantity for this table");
      line_num--;
    }

    ds.tables[nb_table]->colq = $3;
  };

  // Columns description in type 1 tables
  columns_typ1: COLUMNS INT TP BEG {
    flags[1]++;
    if(flags[1] > 1){
      line_num++;
      semantic_error("You already precised columns for this table");
      line_num--;
    }
    else if(flags[0] != 1){
      line_num++;
      semantic_error("You must precise line quantity before the columns");
      line_num--;
      range_size = 0;
    }
    else{
      range_size = ds.tables[nb_table]->lineq;
    }

    col_count = 0;
    ds.tables[nb_table]->colq = $2;
    ds.tables[nb_table]->dist_type = safe_alloc(sizeof(int) * $2);
    ds.tables[nb_table]->range_type = safe_alloc(sizeof(int) * $2);
    ds.tables[nb_table]->range_len = safe_alloc(sizeof(int) * $2);
    ds.tables[nb_table]->means = safe_alloc(sizeof(int) * $2);
    ds.tables[nb_table]->stds = safe_alloc(sizeof(int) * $2);
    ds.tables[nb_table]->names = safe_alloc(sizeof(char *) * $2);
  } column_list END SEM;
  
  column_list : column_desc {
    col_count++;
    if(col_count == ds.tables[nb_table]->colq){
      char error[100];
      sprintf(
        error,
        "Too many columns, expected %d, found %d",
        ds.tables[nb_table]->colq, col_count+1
      );
      semantic_error(error);
    }
  } column_list | column_desc {
    col_count++;
    if(col_count < ds.tables[nb_table]->colq){
      char error[100];
      sprintf(
        error,
        "Too few columns, expected %d, found %d",
        ds.tables[nb_table]->colq, col_count
      );
      semantic_error(error);
    }
  };

  // Description of a Type 1 table's column
  column_desc : fixed_col | distr_col;

  // Beginning of a column
  beg_col : BEG IDF {
    ds.tables[nb_table]->names[col_count] = strdup(yytext);
  };

  // Fixed column in the table
  fixed_col : beg_col COM FIXED COM {size_sent = 1;} range_desc {
    ds.tables[nb_table]->dist_type[col_count] = FIXED_DIS;
    size_sent = 0;
  } END SEM;

  range_desc :
    manual_range {
    nb_range++;
  }
  | auto_range {
    nb_range++;
  };

  // Hand made range
  manual_range : BEG {
    ds.tables[nb_table]->range[nb_range] = safe_alloc(sizeof(int) * range_size);
    ds.tables[nb_table]->range_type[nb_range] = MAN_RANGE;
    ds.tables[nb_table]->range_len[nb_range] = range_size;
    nb_int_list = 0;
  } int_list END;

  int_list: INT {
    nb_int_list++;

    if(nb_int_list == range_size){
      char error[100];
      sprintf(
        error,
        "Too many ints into range list, expected %d, found %d",
        range_size, nb_int_list+1
      );
      line_num++;
      semantic_error(error);
      line_num--;
    }

    ds.tables[nb_table]->range[nb_range][nb_int_list-1] = $1;
  } COM int_list
  | INT {
    nb_int_list++;

    if(nb_int_list < range_size){
      char error[100];
      sprintf(
        error,
        "Too few ints into range list, expected %d, found %d",
        range_size, nb_int_list
      );
      line_num++;
      semantic_error(error);
      line_num--;
    }
    
    ds.tables[nb_table]->range[nb_range][nb_int_list-1] = $1;
  };

  // Automatic range
  auto_range : RANGE OP INT COM INT CP {
    if(size_sent){
      if($5 - $3 + 1 != range_size){
        char error[100];
        sprintf(
          error,
          "Range size incorrect, expected %d, found %d",
          range_size, $5 - $3 + 1
        );
        line_num++;
        semantic_error(error);
        line_num--;
      }
    }

    ds.tables[nb_table]->range[nb_range] = safe_alloc(sizeof(int) * 2);
    ds.tables[nb_table]->range_type[nb_range] = AUTO_RANGE;
    ds.tables[nb_table]->range_len[nb_range] = 2;
    ds.tables[nb_table]->range[nb_range][0] = $3;
    ds.tables[nb_table]->range[nb_range][1] = $5;
  };

  // Not fixed columns
  distr_col : beg_col COM distrib COM auto_range {nb_range++;} END SEM;

  // Distribution choice for type 2 tables
  distr_attr : DISTRIBUTION TP {
    flags[3]++;
    if(flags[3] > 1){
      line_num++;
      semantic_error("You already precised distribution for this table");
      line_num--;
    }
  } BEG distrib COM auto_range END SEM {
    nb_range++;
  };
  
  // Top values (names) for lines
  lines_top_val : LINES_TOP_VAL TP {
    flags[4]++;
    if(flags[4] > 1){
      line_num++;
      semantic_error(
        "You already precised lines top values for this table"
      );
      line_num--;
    }
    else if(flags[0] != 1){
      line_num++;
      semantic_error(
        "You must precise line quantity before lines top values"
      );
      line_num--;
    }

    ds.tables[nb_table]->dist_type[nb_range] = _LINES_TOP_VAL;
    range_size = ds.tables[nb_table]->lineq;
  } range_desc SEM;

  // Top values (names) for columns
  columns_top_val : COLUMNS_TOP_VAL {
    flags[5]++;
    if(flags[5] > 1){
      line_num++;
      semantic_error(
        "You already precised columns top values for this table"
      );
      line_num--;
    }
    else if(flags[2] != 1){
      line_num++;
      semantic_error(
        "You must precise column quantity before columns top values"
      );
      line_num--;
    }

    ds.tables[nb_table]->dist_type[nb_range] = _COLUMNS_TOP_VAL;
    range_size = ds.tables[nb_table]->colq;
  } TP range_desc SEM {
  };

  // Distribution description
  distrib :
    NORMAL OP INT COM INT CP {
      if($5 <= 0){
        line_num++;
        semantic_error("The std of a normal distribution must be > 0");
        line_num--;
      }
      ds.tables[nb_table]->dist_type[nb_range] = NORMAL_DIS;
      ds.tables[nb_table]->means[nb_range] = $3;
      ds.tables[nb_table]->stds[nb_range] = $5;
    }
  | UNIFORM {
    ds.tables[nb_table]->dist_type[nb_range] = UNIFORM_DIS;
  };

  // Vectors parameter
  vectors :
    VECTORS TP _TRUE SEM {ds.tables[nb_table]->vectors = 1;}
  | VECTORS TP _FALSE SEM {ds.tables[nb_table]->vectors = 0;}
  ;

  // Diagonal emptyness parameter
  diagonal :
    DIAGONAL TP FULL SEM {ds.tables[nb_table]->diagonal = 1;}
  | DIAGONAL TP EMPTY SEM {ds.tables[nb_table]->diagonal = 0;}
  ;
%%

int yyerror(){
  int i;
  char c = '\0';

  // More than one error on the line, we ignore the rest
  if(act_line > line_num){
    return -1;
  }

  // We parse till the line
  for(i = act_line; i < line_num; i++){
    c = '\0';
    while(c != '\n' && c != EOF){
      c = fgetc(file);
    }
  }

  // We print the line and the line number
  color(RED_BF);
  fprintf(stderr, "\nSyntactic error\n");
  color(WHITE_BF);
  fprintf(stderr, " %d |  ", line_num);
  color(RESET);
  
  c = '\0';
  c = fgetc(file);
  while(c != '\n' && c != EOF){
    fprintf(stderr, "%c", c);
    c = fgetc(file);
  }

  color(WHITE_BF);
  fprintf(stderr, "\n   | ");
  for(i = 0; i < column+1; i++){
    fprintf(stderr, " ");
  }
  
  color(RED_BF);
  fprintf(stderr, "^\n\n");
  color(RESET);
  semantic_err++;
  return -1;
}
