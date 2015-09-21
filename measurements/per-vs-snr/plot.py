import matplotlib
import os
#matplotlib.use('PS')
import numpy as np
from numpy import genfromtxt
import matplotlib.pyplot as plt

dirs = os.listdir('.')
snr = []
ber = []
meas_points = []
for dir in dirs:    
    if(os.path.isdir(dir)):
        curr_dir = os.listdir(dir) 
        if(curr_dir[0].endswith('csv')):
            curr_file = curr_dir[0]
            data = genfromtxt(dir+'/'+curr_file, delimiter=',', skip_header=1)
            mean_snr = np.mean(data[:,1])
            mean_ber = np.mean(data[:,2])
            mean_per = np.mean(data[:,3])
            snr.append(mean_snr)
            ber.append(mean_ber) 
            
            meas_points.append([mean_snr,mean_ber,mean_per])

meas_points.sort(key=lambda point: point[1])
data = np.array(meas_points)

#plt.figure(figsize=(128, 128))

plt.plot(data[:,0], data[:,1])
plt.savefig('test.svg', dpi=3600, bbox_inches='tight')
