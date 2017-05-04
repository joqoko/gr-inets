import numpy

t1 = []
t2 = []
t3 = []
t4 = []
t5 = []
tRX1s = []
tRX1e = []
tRX2 = []
tao12 = []
tao23 = []
tao35 = []
tao15 = []
taocs = []
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
    tRX1s.append(start_cs_time)
    tRX1e.append(end_cs_time)
 
with open("2017_5_2_16_29_29_block100_tRX2.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    tRX2.append(this_time)

for i in range(len(t1)):
  tao12.append(t2[i] - t1[i])
  tao23.append(t3[i] - t2[i])
  tao35.append(t5[i] - t3[i])
  tao15.append(t5[i] - t1[i])
  tao3RX1.append(tRX1s[i] - t3[i])
  taocs.append(tRX1e[i] - tRX1s[i])
  taoRX1RX2.append(tRX2[i] - tRX1s[i])
  tao5RX2.append(tRX2[i] - t5[i])

tao12_arr = numpy.array([tao12])
tao23_arr = numpy.array([tao23])
tao35_arr = numpy.array([tao35])
tao15_arr = numpy.array([tao15])
tao3RX1_arr = numpy.array([tao3RX1])
taocs_arr = numpy.array([taocs])
taoRX1RX2_arr = numpy.array([taoRX1RX2])
tao5RX2_arr = numpy.array([tao5RX2])

tao_12_mean = numpy.mean(tao12_arr)
tao_23_mean = numpy.mean(tao23_arr)
tao_35_mean = numpy.mean(tao35_arr)
tao_15_mean = numpy.mean(tao15_arr)
tao_3RX1_mean = numpy.mean(tao3RX1_arr)
tao_cs_mean = numpy.mean(taocs_arr)
tao_RX1RX2_mean = numpy.mean(taoRX1RX2_arr)
tao_5RX2_mean = numpy.mean(tao5RX2_arr)

print tao_12_mean
print tao_23_mean
print tao_35_mean
print tao_15_mean
print tao_3RX1_mean
print tao_cs_mean
print tao_RX1RX2_mean
print tao_5RX2_mean

with open("300_result.txt", "w") as f:
  f.write("tao 12 mean: ")
  f.write(str(tao_12_mean))
  f.write("\ntao 23 mean: ")
  f.write(str(tao_23_mean))
  f.write("\ntao 35 mean: ")
  f.write(str(tao_35_mean))
  f.write("\ntao 15 mean: ")
  f.write(str(tao_15_mean))
  f.write("\ntao 3RX1 mean: ")
  f.write(str(tao_3RX1_mean))
  f.write("\ntao cs mean: ")
  f.write(str(tao_cs_mean))
  f.write("\ntao RX1RX2 mean: ")
  f.write(str(tao_RX1RX2_mean))
  f.write("\ntao 5RX2 mean: ")
  f.write(str(tao_5RX2_mean))
