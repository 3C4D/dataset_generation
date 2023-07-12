# This program is made to compress vectors representing no relations
# in the relations table

import sys, csv, tempfile

# Arguments number control
if(len(sys.argv) < 2):
  print('Usage :', sys.argv[0], 'relations_csv_file')
  sys.exit(-1)

# We open a temporary directory for post treatment
with tempfile.TemporaryDirectory() as tmpdirname:
    path = tmpdirname + '/file.csv'
    print(path)

    # We make the a new file
    # We write the rows, replacing
    with open(path, 'w') as fout, open(sys.argv[1]) as relfile:
      cfout = csv.writer(fout, delimiter=';', quotechar='"', quoting=csv.QUOTE_MINIMAL)
      cfin = csv.reader(relfile, delimiter=';', quotechar='"')

      for i in cfin:
        for j in range(len(i)):
          if '0' in i[j] and j > 0:
            i[j] = '0'

        cfout.writerow(i)

    # We then open the Relations file and re-write it with the
    # cleaned lines
    with open(path) as fin, open(sys.argv[1], 'w') as relfile:
      cfout = csv.writer(relfile, delimiter=';', quotechar='"', quoting=csv.QUOTE_MINIMAL)
      cfin = csv.reader(fin, delimiter=';', quotechar='"')
    
      for i in cfin:
        print(i)
        cfout.writerow(i)

