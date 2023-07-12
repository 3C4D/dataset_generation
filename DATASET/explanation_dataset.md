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

This is a double entry table, so it's type is `typ2`.
We name it `Object_Sensitivity`.

We precise the quantities of line and columns, which are the number of
controllers and the number of objects, respectively 40 and 30.

No need here for symmetry : `symmetric : false;`

We fill lines/columns top values, the lines/columns entry, here the IDs of
the controllers/objects, so the ints between 1 and 40/30.

`lines_top_values : range(1, 40)`
`columns_top_values : range(1, 30)`

No need for vector generation here : `vectors : false;`

The diagonal have to contain values here : `diagonal : full;`

Finally we fill the distribution parameter.
We estimage the level of sensitivity on a scale of 7 values, we estimate
that a coherent distribution could be a normal distribution with a mean of
5 (mid/mid-high, based on the read litterature), and with a std of 2

### Access Requests

This is a simple entry table, so it's type is `typ1`.
We name it `Access_Requests`.

We precise the number of lines : 4 according to the document.

We fill the columns field with the description of each column :
  - `{RequestID, fixed, range(1, 50)};` :
    - The ID of the request represented by the line of the csv file.
  - `{Requester, uniform, range(1, 200)};` :
    - The number of requester depends on the total number of user in the
      system, we can choose here a number of 200
    - Distribution : uniform
  - `{Object, uniform, range(1, 30)};` :
    - We will fix the number of object to 30 like in the previous table
    - Distribution : uniform

### Intrapersonal Properties of Controllers

This is a simple entry table, so it's type is `typ1`.
We name it `Intra_Prop_Cont`.

We precise the number of lines : 4 according to the document.

We fill the columns field with the description of each column :
  - `{Controller, fixed, range(1, 40)};` :
    - The ID of the controller represented by the line of the csv file.
    - Number fixed to 40 like in the table 1
  - `{Sharing_benefit, normal(2, 2), range(1, 5)};` :
    - The distribution for the sharing benefits is purely guessed for now
    - Distribution : normal (mean : 2, standard deviation : 2)
  - `{Peer_influence, normal(2, 5), range(1, 5)};` :
    - The distribution for the peer influence is purely guessed for now
    - Distribution : normal (mean : 2, standard deviation : 2)

### Relationship between Controllers

This is a double entry table, so it's type is `typ2`.
We name it `Relationship_Controllers`.

We precise the quantities of line and columns, 4 and 4.

thus, considering the relationships are symmetric, we can precise tha table
to be symmetric with the parameter `symmetry : true;`. We need to define
lines and columns quantity before the symmetry parameter because only square
table can be symmetric.

If the symmetry parameter is set to `true`, the values above the diagonal will
be put to `X`, because they are redundants.

We fill lines/columns top values, the lines/columns entry, here the IDs of
the controllers, so the ints between 1 and 40.

`lines_top_values : range(1, 40)`

The columns top values are the same.

Also we want the cells to be vectors because a person can have different types
of relation with a single person, or no relations.

We toggle the parameter `vectors : true;` for that.

Knowing that a person don't have relation with itself, we can set the diagonal
parameter to empty : `diagonal : empty;` (instead of setting it to `full`)

Finally we fill the distribution parameter. We guess the relationship can be :
  - friend (value : -1)
  - no relation (value : 0)
  - colleague (value : 1)
  - family (value : 2)

We map numerical values to these situations, -1, 0, 1 and 2. We choose a normal
distribution, the range will be between -1 and 2. The mean will be
'no relation' ie the value 0. The standard deviation will be 2.

With these parameters, we could have a cell of relation where two persons are
friends AND family AND colleagues or just not related.