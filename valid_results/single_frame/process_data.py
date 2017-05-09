import numpy

last_time = 0;
pr = numpy.zeros((10000, 50))
pt = numpy.zeros((10000, 100))
rowt = 0
rowr = 0
index = 0

with open("2017_5_9_11_45_56_block100_cs.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[1]) + float(words[2]) / 1000000
    this_power = float(words[0])
    if this_time - last_time > 0.5:
      rowr = rowr + 1
      index = 0
    else:
      index = index + 1
    pr[rowr][index] = this_power;
    last_time = this_time

index = 0

with open("2017_5_9_11_45_45_block100_tx.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[1]) + float(words[2]) / 1000000
    this_power = float(words[0])
    if this_time - last_time > 0.5:
      rowt = rowt + 1
      index = 0
    else:
      index = index + 1
    pt[rowt][index] = this_power;
    last_time = this_time

pt_row = sum(pt) / rowt
pr_row = sum(pr) / rowr
print pt_row 
print pr_row 

with open("single_frame_tx.txt", "w") as f:
  f.write("tx = [")
  for i in range(100):
    f.write(str(pt_row[i]))
    f.write(" ")
  f.write("];")

with open("single_frame_rx.txt", "w") as f:
  f.write("rx = [")
  for i in range(50):
    f.write(str(pr_row[i]))
    f.write(" ")
  f.write("];")
