# Profiles program

The program "profiles.py" consists in adding a quantity of fixed profile into
our dataset's tables.

The program will take two arguments :
  - the name of the directory containg the generated tables.
  - the name of the file describing the desired profiles

## Profile config file

The config file describing the profiles is a CSV file.

It can contain 3 types of lines, one for creating a profile for the tables
1 and 4, an other type for the table 2 and an other the table 3.

Also comments can be added in the file by putting "//" in the beginning of the line

### Tables 1 and 4 lines

```
table id; quantity of lines we want to add; actual top value; quantity 1; entity1; quantity2; entity2; ...
```

Example (for the table 1, Object Sensitivity) :

```
1;5;12;2;1;4;2
```

Here the line means that we want to add, in the table 1, 5 lines.
The last line of the table begin with the top value 12.
In these lines we will have 2 entity :
  - 2 cells with the number 1
  - 4 celles with the number 2

Of course the composition is random, it could be "1,2,2,1,2,2" or "2,1,2,2,2,1"
for example.

Example (for the table 4, Object Sensitivity, which is vectorised) :

```
4;5;18;1;0,1,2;4;0,1;3;2,3
```

Here the line means that we want to add, in the table 4, 5 lines.
The last line of the table begin with the top value 18.
In these lines we will have 2 entity :
  - 1 cell with the vector 0,1,2
  - 4 celles with the vector 0,1
  - 3 celles with the vector 2,3

As a reminder, delimiter for cells in the file are ';' and the delimiter for vectors in the
cells are ','.

### Tables 2 lines

```
table id; quantity of lines we want to add; actual request id; column 2 value; column 3 value
```

Example :

```
2;5;50;1;8
```

Here the line means that we want to add, in table 2, 5 lines.
These lines will all have 1 and 8 as values for the 2 last columns.
The first column will begin at 50 (it's the request id) and increment with the lines.


### Tables 3 lines

```
table id; quantity of lines we want to add; actual controller id; column 2 value; column 3 value
```

Example :

```
3;5;40;2;3
```

Here the line means that we want to add, in table 3, 5 lines.
These lines will all have 2 and 3 as values for the 2 last columns.
The first column will begin at 40 (it's the controller id) and increment with the lines

## Execution

The program is coded in python language.

```
Usage : python3 dataset_path config_file_path
```

- dataset_path : path to the dataset's directory
- config_file_path : path to the profiles config path

An example of profiles config file is given in the file 'profiles_file.csv'.

Example of execution command : `python profiles.py ds_mark1 profiles_file.csv`