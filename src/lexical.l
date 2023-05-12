%{
// Enzo CADONI - LIS - 2022/2023
// Syntactic analyser producer (Lex part)

#include <string.h>
#include "../obj/syntactic.tab.h"
#include "../inc/colors.h"

extern int line_num;
int column = 0;

%}

C1 [^"]
C2 [^"*]
C3 [^"*/]

%%
(0|[1-9][0-9]*) {yylval.typ1 = atoi(yytext); return(INT);}
(0|[1-9][0-9]*)\.([0-9]+)  {yylval.typ2 = atof(yytext); return(REAL);}

\/\/.*$

"DATASET" {column += 7; return(DATASET);}
"TABLE" {column += 5; return(TABLE);}
"lines" {column += 5; return(LINES);}
"columns" {column += 7; return(COLUMNS);}
"fixed" {column += 5; return(FIXED);}
"range" {column += 5; return(RANGE);}
"normal" {column += 6; return(NORMAL);}
"uniform" {column += 7; return(UNIFORM);}
"typ1" {column += 4; return(TYP1);}
"typ2" {column += 4; return(TYP2);}
"distribution" {column += 12; return(DISTRIBUTION);}
"lines_top_values" {column += 16; return(LINES_TOP_VAL);}
"columns_top_values" {column += 18; return(COLUMNS_TOP_VAL);}  
"symmetry" {column += 8; return(SYMMETRY);}
"true" {column += 4; return(_TRUE);}
"false" {column += 5; return(_FALSE);}

[a-zA-Z_][a-zA-Z0-9_]*  {
  column += strlen(yytext);
  return(IDF);
}

":" {return(TP); column++;}
"{" {return(BEG); column++;}
"}" {return(END); column++;}
"(" {return(OP); column++;}
")" {return(CP); column++;}
";" {return(SEM); column++;}
"," {return(COM); column++;}

\n  {line_num++; column = 0;}
" " {column ++;}
\t  {column += 2;}

. {
  color(GREEN_BF);
  fprintf(stderr, "\nLexicographic Error\n");
  color(WHITE_BF);
  fprintf(stderr, " %d |  %s", line_num, yytext);
  color(RESET);
  fprintf(stderr, "\n\n");
}
%%

int yywrap(){
}
