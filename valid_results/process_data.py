import numpy

t1 = []
t2 = []
t3 = []
t4 = []
t5 = []
tRX1 = []
tRX2 = []
tao12 = []
tao23 = []
tao34 = []
tao45 = []
tao15 = []
tao3RX1 = []
taoRX1RX2 = []
tao5RX2 = []

with open("2017_5_2_16_29_46_block101_t1.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t1.append(this_time)
  
with open("2017_5_2_16_29_46_block102_t2.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t2.append(this_time)
 
with open("2017_5_2_16_29_46_block5_t3.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t3.append(this_time)
 
with open("2017_5_2_16_29_46_block103_t4.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t4.append(this_time)
 
with open("2017_5_2_16_29_46_block104_t5.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t5.append(this_time)
 
with open("2017_5_2_16_29_29_block100_tRX1.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    start_cs_time = float(words[0]) + float(words[1]) / 1000000
    end_cs_time = float(words[2]) + float(words[3]) / 1000000
    tRX1.append(this_time)
 
with open("2017_5_2_16_29_29_block100_tRX2.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    tRX2.append(this_time)

print len(t1)
print len(t2)
print len(t3)
print len(t4)
print len(t5)
print len(tRX1)
print len(tRX2) 

for i in range(len(t1)):
  tao12.append(t2[i] - t1[i])
  tao23.append(t3[i] - t2[i])
  tao34.append(t4[i] - t3[i])
  tao45.append(t5[i] - t4[i])
  tao15.append(t5[i] - t1[i])
  tao3RX1.append(t3[i] - tRX1[i])
  taoRX1RX2.append(tRX1[i] - tRX2[i])
  tao5RX2.append(tRX2[i] - t5[i])

tao12_arr = numpy.array([tao12])
tao23_arr = numpy.array([tao23])
tao34_arr = numpy.array([tao34])
tao45_arr = numpy.array([tao45])
tao15_arr = numpy.array([tao15])
tao3RX1_arr = numpy.array([tao3RX1])
taoRX1RX2_arr = numpy.array([taoRX1RX2])
tao5RX2_arr = numpy.array([tao5RX2])

tao_12_mean = numpy.mean(tao12_arr)
tao_23_mean = numpy.mean(tao23_arr)
tao_34_mean = numpy.mean(tao34_arr)
tao_45_mean = numpy.mean(tao45_arr)
tao_15_mean = numpy.mean(tao15_arr)
tao_3RX1_mean = numpy.mean(tao3RX1_arr)
tao_RX1RX2_mean = numpy.mean(taoRX1RX2_arr)
tao_5RX2_mean = numpy.mean(tao5RX2_arr)

print tao_12_mean
print tao_23_mean
print tao_34_mean
print tao_45_mean
print tao_15_mean
print tao_3RX1_mean
print tao_RX1RX2_mean
print tao_5RX2_mean
