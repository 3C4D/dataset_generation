# Grammar without semantics

This is the full grammar of the file :

```
  dataset : DATASET IDF TP INT BEG tables END;

  tables : table tables | table

  table : table_typ1 | table_typ2;

  table_typ1 : TABLE  TYP1 IDF BEG content_typ1 END;
  
  table_typ2 : TABLE  TYP2 IDF BEG content_typ2 END;

  content_typ1 :
    content_typ1_attr content_typ1
  | content_typ1_attr
  
  content_typ1_attr : columns_typ1 | lines_num

  content_typ2 :
    content_typ2_attr content_typ2
  | content_typ2_attr
  ;

  content_typ2_attr :
    symmetry
  | columns_num
  | lines_num
  | distr_attr
  | lines_top_val 
  | columns_top_val 
  ; 

  symmetry :
      SYMMETRY TP _TRUE SEM
    | SYMMETRY TP _FALSE SEM
    ;

  lines_num : LINES TP INT SEM;

  columns_num : COLUMNS TP INT SEM;

  columns_typ1: COLUMNS INT TP BEG column_list END SEM;
  
  column_list : column_desc column_list | column_desc;

  column_desc : fixed_col | distr_col;

  beg_col : BEG IDF;

  fixed_col : beg_col COM FIXED COM range_desc END SEM;

  range_desc :
    manual_range | auto_range;

  manual_range : BEG int_list END;

  int_list: INT COM int_list | INT

  auto_range : RANGE OP INT COM INT CP

  distr_col : beg_col COM distrib COM auto_range END SEM;

  distr_attr : DISTRIBUTION TP BEG distrib COM auto_range END SEM
  
  lines_top_val : LINES_TOP_VAL TP range_desc SEM;

  columns_top_val : COLUMNS_TOP_VAL TP range_desc SEM

  distrib :
    NORMAL OP INT COM INT CP
  | UNIFORM
```