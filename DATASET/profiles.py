import sys, csv, random

# Arguments number control
if(len(sys.argv) < 2):
  print("Usage : profiles.py tables_dir profiles_file")
  sys.exit(-1)

# Open a csv file in write mode
def open_csv_w(dirname, filename):
  return csv.writer(open(dirname + filename, "a"), delimiter=';', quotechar='"', quoting=csv.QUOTE_MINIMAL)

# Open a csv file in read mode
def open_csv_r(dirname, filename):
  return csv.reader(open(dirname + filename), delimiter=';', quotechar='"')

# Generate a combination of elements in elems by quantity described in quant
def list_of_elem(elems, quant):
  l = []
  elems_all = []
  
  # Generate the whole list of available elements
  for i in range(len(elems)):elems_all += (quant[i] * [elems[i]])

  # Randomly choosing the elements and their position in the line
  while elems_all != []:
    l.append(random.choice(elems_all))
    elems_all.remove(l[-1])
  return l

# Open the config file
dirname = sys.argv[1]
pfile = open_csv_r("", sys.argv[2])

# Open every table csv file
tables = [
  open_csv_w(dirname, "/Object_Sensitivity.csv"),
  open_csv_w(dirname, "/Access_Requests.csv"),
  open_csv_w(dirname, "/Intra_Prop_Cont.csv"),
  open_csv_w(dirname, "/Relationship_Controllers.csv")
]

# Table Quantity of columns
table_coln = [None, 3, 3, None]

# Iterate on every line of the config file
for i in pfile:

  # Empty and comment lines
  if(len(i) == 0 or (len(i) < 2 and i[0].count("//") > 0)): continue
  
  # Take the table ID
  ind = int(i[0])-1

  # Table 2 or 3 treatment
  if(ind in [1, 2]):
    if(table_coln[ind] != len(i)-2):  # Not enough fields provided for the profile
      print("You have to provide", table_coln[ind] ,"field to make a profile for table", i[0])
      sys.exit(-1)

    cont = int(i[2])+1
    for j in range(int(i[1])):
      # Write the id and the the entities
      tables[ind].writerow([str(cont+j)] + i[2:])
  
  # Table 1 or 4
  if(ind in [0, 3]):
    if((len(i)-3) % 2 != 0):
      print("Bad profile for table", ind+1 ,": odd number of elements")
      sys.exit(-1)
    
    # Randomly create the line with parameters
    # (entities, number of each entity)
    el, qu = [], []
    for j in range(3, len(i)):
      if(j % 2 == 0): el.append(i[j])
      else: qu.append(int(i[j]))

    cont = int(i[2])+1
    for j in range(int(i[1])):
      # Write the id and then the randmly created line
      tables[ind].writerow([str(cont+j)] + list_of_elem(el, qu))
