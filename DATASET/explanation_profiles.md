# Profiles program

The program "profiles.py" consists in adding some profiles, considered "extrem"
in the dataset. 

The program will take some tables of the generated dataset (the one generated
by the "ds_mark1.ds" config file).

The program will take some tables of the dataset and modify it. In order not
to erase the previous generated tables during the execution, a modified
version of the tables will be named "TABLE_MOD.csv" if the tables were
previously named "TABLE.csv". Indeed, if a table isn't modified (for example
the table Access_Request will not be modified), no modified version will be
created.

For the moment, the program is modifying the tables Object_Sensitivity and
the table Intra_Prop_Cont. The program will create a modified version of them
in the folder ds_mark1 and leave the other tables unmodified.

## Profiles added

The profiles added to the tables are :

- Persons that always estimate very high (or very low) the objects sensitivity
- Persons that are extremely influenced (or not at all) by their peers
- Persons that have many advantages (or not at all) to share
  (sharing benefits parameter)

## Execution

The program is coded in python language.

To apply the program on the the generated dataset, you'll have to execute it
in the same directory than the dataset's directory.

To use the profiles.py program, you have to give it one parameter, the
percentage of enounced profiles you want to put in the dataset files.

```
Usage : python3 profiles.py percentage
```

For example, if you choose 7 for the percentage parameter, each profile will
be 7% of the global generated data.