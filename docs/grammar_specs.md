# Grammar specification

The input file of the generation program is ruled by a grammar, here it is.

The syntax :

```
DATASET dataset_name : table_quantity {
  TABLE typ1 table_name_1{
    lines : line_quantity;
    columns column_quantity : {
      {first_column_name, distribution_type, distribution_range};
      {second_column_name, distribution_type, distribution_range};
      ...
      {last_column_name, distribution_type, distribution_range};
    }
  }

  // Comment
  // Another Comment

  TABLE typ2 table_name_2{
    lines : line_quantity;
    columns : column_quantity;
    symmetry : symmetry_parameter;
    columns_top_values : columns_top_val_range;
    lines_top_values : lines_top_val_range;
    distribution : {distribution_type, distribution_range};
  }

  TABLE typ2 table_name_3{
    ...
  }

  TABLE typ1 table_name_4{
    ...
  }
}
```

An exhaustive example of what can be written is here :

```
DATASET DS1 : 2{
  TABLE typ1 T1 {
    lines : 2;
    columns 4 : {
      {a, fixed, {1, 5}};
      {a, fixed, {2, 2}};
      {b, normal(2, 10), range(1, 50)};
      {c, uniform, range(1, 50)};
    };
  }

  TABLE typ2 T2 {
    lines : 10;
    columns : 10;
    symmetry : true;
    columns_top_values : {1, 2, 4, 2, 4, 1, 2, 1, 8, 2};
    lines_top_values : range(2, 11);
    distribution : {normal(5, 1), range(5, 10)};
  }
}
```

Explanation :
  - A file is representing a single dataset, here the dataset named `DS1`.
  - There is two table types for the moment :
    - typ1 : single entry table
      - We precise the name of each columns
      - Each columns have it's own distribution and range of value
    - typ2 : double entry table
      - We precise the name of columns as values (columns top values)
      - We precise the name of lines as values (lines top values)
      - The whole table has a single distribution
      - If the table has the same number of columns and line, we can tell the
        program that we want it to be symmetric (with the  `symmetry` parameter)
