import numpy

t1DQ = []
t1TXr = []
t1TXs = []
t1e = []
t2CSs = []
t2CSe = []
t2RXe = []
Tfr = []

with open("t1DQ.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 700000
    t1DQ.append(this_time)
 
with open("t1TXr.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 700000
    t1TXr.append(this_time)

with open("t1TXs.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 700000
    t1TXs.append(this_time)

with open("t1e.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 700000
    t1e.append(this_time)

with open("t2CS.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 700000
    end_time = float(words[2]) + float(words[3]) / 700000
    t2CSs.append(this_time)
    t2CSe.append(end_time)
 
with open("t2RXe.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 700000
    t2RXe.append(this_time)

with open("Tfr.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0])
    Tfr.append(this_time)

print('t1DQ', len(t1DQ))
print('t1TXr', len(t1TXr))
print('t1TXs', len(t1TXs))
print('t1e', len(t1e))
print('t2CSs', len(t2CSs))
print('t2CSe', len(t2CSe))
print('t2RXe', len(t2RXe))
print('Tfr', len(Tfr))

n_tx = min(len(t1DQ), len(t1TXs), len(t1e), len(t1TXr), len(t2RXe), len(t2CSe), len(t2CSs), len(Tfr))

print(n_tx)
# debugging code

#for i in range(n_tx):
#  if t1RXse[i] - t1RXs[i] < 0.005:
#    print t1RXse[i]
#    print t1RXse[i] - t1RXs[i]

T1DQ1TXr = []
T1DQ1TXs = []
T1TXr1TXs = []
T1TXs1e = []
T1DQ1e = []
T1TXs2CSs = []
T2CSs2CSe = []
T2CSe2RXe = []
T1TXe2CSe = []
T1e2CSe = []
Tfr_mean = numpy.mean(numpy.array([Tfr]))
print('Tfr mean', Tfr_mean)
 
for i in range(n_tx):
  T1DQ1TXr.append(t1TXr[i] - t1DQ[i])
  T1DQ1TXs.append(t1TXs[i] - t1DQ[i])
  T1TXr1TXs.append(t1TXs[i] - t1TXr[i])
  T1TXs1e.append(t1e[i] - t1TXs[i])
  T1DQ1e.append(t1e[i] - t1DQ[i])
  T1TXs2CSs.append(t2CSs[i] - t1TXs[i])
  T2CSs2CSe.append(t2CSe[i] - t2CSs[i])
  T2CSe2RXe.append(t2RXe[i] - t2CSe[i])
  T1TXe2CSe.append(t2CSe[i] - t1TXs[i] - Tfr_mean)
  T1e2CSe.append(t2CSe[i] - t1e[i])

T1DQ1TXr_arr = numpy.array([T1DQ1TXr])
T1DQ1TXs_arr = numpy.array([T1DQ1TXs])
T1TXr1TXs_arr = numpy.array([T1TXr1TXs])
T1TXs1e_arr = numpy.array([T1TXs1e])
T1DQ1e_arr = numpy.array([T1DQ1e])
T1TXs2CSs_arr = numpy.array([T1TXs2CSs])
T2CSs2CSe_arr = numpy.array([T2CSs2CSe])
T2CSe2RXe_arr = numpy.array([T2CSe2RXe])
T1TXe2CSe_arr = numpy.array([T1TXe2CSe])
T1e2CSe_arr = numpy.array([T1e2CSe])

T1DQ1TXr_mean = numpy.mean(T1DQ1TXr)
T1DQ1TXs_mean = numpy.mean(T1DQ1TXs)
T1TXr1TXs_mean = numpy.mean(T1TXr1TXs)
T1TXs1e_mean = numpy.mean(T1TXs1e)
T1DQ1e_mean = numpy.mean(T1DQ1e)
T1TXs2CSs_mean = numpy.mean(T1TXs2CSs)
T2CSs2CSe_mean = numpy.mean(T2CSs2CSe)
T2CSe2RXe_mean = numpy.mean(T2CSe2RXe)
T1TXe2CSe_mean = numpy.mean(T1TXe2CSe)
T1e2CSe_mean = numpy.mean(T1e2CSe)

T1DQ1TXr_std = numpy.std(T1DQ1TXr)
T1DQ1TXs_std = numpy.std(T1DQ1TXs)
T1TXr1TXs_std = numpy.std(T1TXr1TXs)
T1TXs1e_std = numpy.std(T1TXs1e)
T1DQ1e_std = numpy.std(T1DQ1e)
T1TXs2CSs_std = numpy.std(T1TXs2CSs)
T2CSs2CSe_std = numpy.std(T2CSs2CSe)
T2CSe2RXe_std = numpy.std(T2CSe2RXe)
T1TXe2CSe_std = numpy.std(T1TXe2CSe)
T1e2CSe_std = numpy.std(T1e2CSe)

with open("700_result.txt", "w") as f:
  f.write("T1DQ1TXr_700_mean = \t\t")
  f.write(str(T1DQ1TXr_mean))

  f.write(";\nT1DQ1TXs_700_mean = \t\t")
  f.write(str(T1DQ1TXs_mean))

  f.write(";\nT1TXr1TXs_700_mean = \t\t")
  f.write(str(T1TXr1TXs_mean))

  f.write(";\nT1TXs1e_700_mean = \t\t")
  f.write(str(T1TXs1e_mean))

  f.write(";\nT1DQ1e_700_mean = \t\t")
  f.write(str(T1DQ1e_mean))

  f.write(";\nT1TXs2CSs_700_mean = \t\t")
  f.write(str(T1TXs2CSs_mean))

  f.write(";\nT2CSs2CSe_700_mean = \t\t")
  f.write(str(T2CSs2CSe_mean))

  f.write(";\nT2CSe2RXe_700_mean = \t\t")
  f.write(str(T2CSe2RXe_mean))

  f.write(";\nT1TXe2CSe_700_mean = \t\t")
  f.write(str(T1TXe2CSe_mean))

  f.write(";\nT1e2CSe_700_mean = \t\t")
  f.write(str(T1e2CSe_mean))

  f.write(";\nT1DQ1TXr_700_std = \t\t")
  f.write(str(T1DQ1TXr_std))

  f.write(";\nT1DQ1TXs_700_std = \t\t")
  f.write(str(T1DQ1TXs_std))

  f.write(";\nT1TXr1TXs_700_std = \t\t")
  f.write(str(T1TXr1TXs_std))

  f.write(";\nT1TXs1e_700_std = \t\t")
  f.write(str(T1TXs1e_std))

  f.write(";\nT1DQ1e_700_std = \t\t")
  f.write(str(T1DQ1e_std))

  f.write(";\nT1TXs2CSs_700_std = \t\t")
  f.write(str(T1TXs2CSs_std))

  f.write(";\nT2CSs2CSe_700_std = \t\t")
  f.write(str(T2CSs2CSe_std))

  f.write(";\nT2CSe2RXe_700_std = \t\t")
  f.write(str(T2CSe2RXe_std))

  f.write(";\nT1TXe2CSe_700_std = \t\t")
  f.write(str(T1TXe2CSe_std))

  f.write(";\nT1e2CSe_700_std = \t\t")
  f.write(str(T1e2CSe_std))

  f.write(";")
