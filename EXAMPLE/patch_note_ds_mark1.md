# Patch note

As we can see, the table Object_Sensitivity has been modified.

It's now a double entry table. The point is to have all objects/controllers
pairs.

## Profiles program

To use the profiles.py program, you have to give it one parameter, the
percentage of extreme profiles you want to put in the dataset files.

```
Usage : profiles.py percentage
```

The file will take the table Object_Sensitivity and the table Intra_Prop_Cont.

The files produced will be ds_mark1/Object_Sensitivity_MOD.csv and
ds_mark1/Intra_Prop_Cont_MOD.csv. These are containing the added profiles.
