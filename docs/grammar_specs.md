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
    lines : 20;
    columns : 8;
    columns_top_values : range(2, 21);
    lines_top_values : range(1, 8);
    distribution : {normal(5, 1), range(10, 5)};
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