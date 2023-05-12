# Dataset file explanation

In this file, we are gonna explain how the file `ds_mark1.ds`
works in details.

## File usage

We can use the file using the program in the `bin` directory that
is accessible at the root of the repo.

For example : `../bin/generation ds_mark1.ds`

This will generate the directory `ds_mark1` and the tables CSV files
in it.

to regenerate the dataset (with other values), we will have to delete
the directory `ds_mark1` and re-use the previous command.

## Dependencies required to launch the program

You will need to have flex and bison installed on your distribution to launch
the program. It's accessible on most of the linux distributions (because it's
the GNU implementation of their equivalent lex and yacc).

## The creation of the dataset in the file

First, we begin the dataset with the keywork `DATASET`, we name it
and precise the number of tables.

```
DATASET ds_mark1 : 4  {
```

## Tables

Once we began the dataset, we havec to define each tables and it's parameters.

### Object Controllers and Sensitivity Levels

This is a simple entry table, so it's type is `typ1`.
We name it `Object_Sensitivity`.

We precise the number of lines : 4 according to the document but we can change
it later.

We fill the columns field (also with the column quantity) with the description
of each column :
  - `{ObjectID, uniform, range(1, 3)};` :
    - There are 3 objects in the system, so the range is between 1 and 3
    - We decide to generate them based on a uniform distribution
  - `{Controller, uniform, range(1, 4)};` :
    - There are 4 controller, that's why the range is between 1 and 4
    - We decide to generate them based on a uniform distribution
  - `{Sensitivity, normal(2, 1), range(1, 3)};` :
    - There are 3 possible values for sensitivity (low:1, mid:2, high:3)
    - We use a normal distribution to generate the values, considering the
      mean is the mid value

### Access Requests

This is a simple entry table, so it's type is `typ1`.
We name it `Access_Requests`.

We precise the number of lines : 4 according to the document.

We fill the columns field with the description of each column :
  - `{RequestID, fixed, {1, 2, 3, 4}};` :
    - The column seems to be fixed (from 1 to 4), we could also define the
      column values like a range : `range(1, 4)`.
  - `{Requester, uniform, range(1, 4)};` :
    - We guess the number of requester is equal to the number of controller
    - Distribution : uniform
  - `{Object, uniform, range(1, 4)};` :
    - We will fix the number of object to 4
    - Distribution : uniform

### Intrapersonal Properties of Controllers

This is a simple entry table, so it's type is `typ1`.
We name it `Intra_Prop_Cont`.

We precise the number of lines : 4 according to the document.

We fill the columns field with the description of each column :
  - `{Controller, fixed, {1, 2, 3, 4}};` :
    - The column seems to be fixed (from 1 to 4), we could also define the
      column values like a range : `range(1, 4)`.
  - `{Sharing_benefit, uniform, range(1, 4)};` :
    - We guess the number of requester is equal to the number of controller
    - Distribution : uniform
  - `{Peer_influence, normal(2, 1), range(1, 3)};` :
    - There are 3 possible values for sensitivity (low:1, mid:2, high:3)
    - Distribution : normal (mean:2, standard deviation : 1)

### Relationship between Controllers

This is a simple entry table, so it's type is `typ2`.
We name it `Relationship_Controllers`.

We precise the quantities of line and columns, 4 and 4.

thus, considering the relationships are symmetric, we can precise tha table
to be symmetric with the parameter `symmetry : true;`. We need to define
lines and columns quantity before the symmetry parameter because only square
table can be symmetric.

We fill lines top values, the lines entry, here c1, c2, c3, c4, but we will
represent them as the numerical values 1, 2, 3 and 4, so :

`lines_top_values : {1, 2, 3, 4}`

but the following line also work :

`lines_top_values : range(1, 4)`

The columns top values are the same.

Finally we fill the distribution parameter. We guess the relationship can be
'friend' or 'not friend', we associate numerical values to them, 1 and 2. We
choose a normal distribution, the range will be between 1 and 2. The mean will
be 'not friend' because there is more person that is not our friend than the
opposite.
