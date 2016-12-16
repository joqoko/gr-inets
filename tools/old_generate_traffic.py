import numpy as np
import socket
import math
import time

IP = "127.0.0.1"
PORT = 52001

np.random.seed(0)
payload = np.random.randint(0, 256,1000) #500 byte payload
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print len(payload)

num = s.sendto(payload.tostring()[0::8], (IP,PORT))
print 'send '+str(num)+' bytes'
wait_time = 0.05 # second
while True:
    time.sleep(wait_time)
    num = s.sendto(payload.tostring()[0::8], (IP,PORT))
    print 'send '+str(num)+' bytes'


