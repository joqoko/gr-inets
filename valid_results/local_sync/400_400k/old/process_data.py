import numpy

t1 = []
t2 = []
t3 = []
t5 = []
tRX1s = []
tRX1e = []
tRX2 = []
tao12 = []
tao23 = []
tao34 = []
tao35 = []
tao15 = []
taocs = []
tao3RX1 = []
taoRX1RX2 = []
tao5RX2 = []

with open("2017_5_4_8_48_40_block101_t1.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t1.append(this_time)
  
with open("2017_5_4_8_48_40_block102_t2.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t2.append(this_time)
 
with open("2017_5_4_8_48_40_block4_t3.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t3.append(this_time)
 
with open("2017_5_4_8_48_40_block5_t4.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0])
    tao34.append(this_time)
 
with open("2017_5_4_8_48_40_block105_t5.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    t5.append(this_time)
 
with open("2017_5_4_8_48_24_block100_tRX1.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    start_cs_time = float(words[0]) + float(words[1]) / 1000000
    end_cs_time = float(words[2]) + float(words[3]) / 1000000
    tRX1s.append(start_cs_time)
    tRX1e.append(end_cs_time)
 
with open("2017_5_4_8_48_24_block100_tRX2.txt") as file:
  data = file.readlines()
  for line in data:
    words = line.split()
    this_time = float(words[0]) + float(words[1]) / 1000000
    tRX2.append(this_time)

print(len(t1))
print(len(t2))
print(len(t3))
print(len(t5))
print(len(tRX1s))
print(len(tRX1e))
print(len(tRX2))

# debugging code

for i in range(len(tRX2) - 1):
  if tRX2[i + 1] - tRX2[i] > 0.15:
    print tRX2[i]

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
tao34_arr = numpy.array([tao34])
tao35_arr = numpy.array([tao35])
tao15_arr = numpy.array([tao15])
tao3RX1_arr = numpy.array([tao3RX1])
taocs_arr = numpy.array([taocs])
taoRX1RX2_arr = numpy.array([taoRX1RX2])
tao5RX2_arr = numpy.array([tao5RX2])

tao_12_mean = numpy.mean(tao12_arr)
tao_23_mean = numpy.mean(tao23_arr)
tao_34_mean = numpy.mean(tao34_arr)
tao_35_mean = numpy.mean(tao35_arr)
tao_15_mean = numpy.mean(tao15_arr)
tao_3RX1_mean = numpy.mean(tao3RX1_arr)
tao_cs_mean = numpy.mean(taocs_arr)
tao_RX1RX2_mean = numpy.mean(taoRX1RX2_arr)
tao_5RX2_mean = numpy.mean(tao5RX2_arr)

print ("means:")
print tao_12_mean
print tao_23_mean
print tao_34_mean
print tao_35_mean
print tao_15_mean
print tao_3RX1_mean
print tao_cs_mean
print tao_RX1RX2_mean
print tao_5RX2_mean

tao_12_std = numpy.std(tao12_arr)
tao_23_std = numpy.std(tao23_arr)
tao_34_std = numpy.std(tao34_arr)
tao_35_std = numpy.std(tao35_arr)
tao_15_std = numpy.std(tao15_arr)
tao_3RX1_std = numpy.std(tao3RX1_arr)
tao_cs_std = numpy.std(taocs_arr)
tao_RX1RX2_std = numpy.std(taoRX1RX2_arr)
tao_5RX2_std = numpy.std(tao5RX2_arr)

print ("std:")
print tao_12_std
print tao_23_std
print tao_34_std
print tao_35_std
print tao_15_std
print tao_3RX1_std
print tao_cs_std
print tao_RX1RX2_std
print tao_5RX2_std

with open("400_400k_result.txt", "w") as f:
  f.write("tao_12_mean \t\t")
  f.write(str(tao_12_mean))
  f.write("\ntao_23_mean \t\t")
  f.write(str(tao_23_mean))
  f.write("\ntao_34_mean \t\t")
  f.write(str(tao_34_mean))
  f.write("\ntao_35_mean \t\t")
  f.write(str(tao_35_mean))
  f.write("\ntao_15_mean \t\t")
  f.write(str(tao_15_mean))
  f.write("\ntao_3RX1_mean \t\t")
  f.write(str(tao_3RX1_mean))
  f.write("\ntao_cs_mean \t\t")
  f.write(str(tao_cs_mean))
  f.write("\ntao_RX1RX2_mn \t\t")
  f.write(str(tao_RX1RX2_mean))
  f.write("\ntao_5RX2_mean \t\t")
  f.write(str(tao_5RX2_mean))
  f.write("\ntao_12_std \t\t")
  f.write(str(tao_12_std))
  f.write("\ntao_23_std \t\t")
  f.write(str(tao_23_std))
  f.write("\ntao_34_std \t\t")
  f.write(str(tao_34_std))
  f.write("\ntao_35_std \t\t")
  f.write(str(tao_35_std))
  f.write("\ntao_15_std \t\t")
  f.write(str(tao_15_std))
  f.write("\ntao_3RX1_std \t\t")
  f.write(str(tao_3RX1_std))
  f.write("\ntao_cs_std \t\t")
  f.write(str(tao_cs_std))
  f.write("\ntao_RX1RX2_std \t\t")
  f.write(str(tao_RX1RX2_std))
  f.write("\ntao_5RX2_std \t\t")
  f.write(str(tao_5RX2_std))
