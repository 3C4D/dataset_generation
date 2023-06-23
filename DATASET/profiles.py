import csv, sys, os

nrow = 0
indir = "ds_mark1/"
with open(indir + 'Object_Sensitivity.csv', newline='') as csvfile:
  reader = csv.reader(csvfile, delimiter=';', quotechar="'")
  for row in reader:nrow += 1
nrow -= 1

if(len(sys.argv) < 2):
  print("Usage : profiles.py percentage_of_profiles")
  sys.exit(-1)

perc = int(sys.argv[1])

profnb = nrow*perc//100

section = 0
with open(indir + 'Object_Sensitivity.csv', newline='') as csvfile:
  reader = csv.reader(csvfile, delimiter=';', quotechar="'")
  with open(indir + 'Object_Sensitivity_MOD.csv', 'w') as output:
    writer = csv.writer(output, delimiter=';', quotechar=" ", quoting=csv.QUOTE_MINIMAL)

    i = -1
    for row in reader:
      if i < 0: i = 0
      elif section == 0:
        for j in range(1, len(row)): row[j] = "1"
        if i == profnb: section += 1; i = 0
      elif section == 1:
        for j in range(1, len(row)): row[j] = "3"
        if i == profnb: section += 1; i = 0
      writer.writerow(row)
      i += 1

with open(indir + 'Intra_Prop_Cont.csv', newline='') as csvfile:
  reader = csv.reader(csvfile, delimiter=';', quotechar="'")
  with open(indir + 'Intra_Prop_Cont_MOD.csv', 'w') as output:
    writer = csv.writer(output, delimiter=';', quotechar=" ", quoting=csv.QUOTE_MINIMAL)

    i = -(profnb*section)
    for row in reader:
      if i <= 0: pass
      elif section == 2:
        row[1] = "1"
        if i == profnb: section += 1; i = 0
      elif section == 3:
        row[1] = "3"
        if i == profnb: section += 1; i = 0
      elif section == 4:
        row[2] = "1"
        if i == profnb: section += 1; i = 0
      elif section == 5:
        row[2] = "3"
        if i == profnb: section += 1; i = 0
      writer.writerow(row)
      i += 1
