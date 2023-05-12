# dataset_generation

The goal of this project is to build a set of very various datasets according to
the notions of a game in a Multi-Party access control strategy context.

## Compilation

`make` or `make all`.

## Execution

The compiled program can be found in the `bin` directory.

Example : `./bin/generation test.ds`

## Example

A detailed example is in the directory `EXAMPLE`, this example contains the
tables described in the document that I have (with the 4 tables based on
different factors like sensitivity, relationships etc)

You will find a file named `ds_mark1.ds` that is the dataset file we passed
to the program.

The file `explanation.md` contains explanation on lines of the parameter file.

Finally, the directory `ds_mark1` contains the dataset, ie one CSV file per
table described in the file `ds_mark1.ds`.

## Further information

Steps followed can be found in the document `docs/steps.md`
References used can be found in the document `docs/references.md`

## Credit

Thanks to François Jacquenet for his fantastic compiler course that gave me
idea for the syntactic analyser.
