import numpy as np
import socket
import math
import time

IP = "127.0.0.1"
PORT = 52001

np.random.seed(0)
payload = np.random.randint(0, 256, 200) #500 byte payload
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print len(payload)

num = s.sendto(payload.tostring()[0::8], (IP,PORT))
print 'send '+str(num)+' bytes'
abc = 0
wait_time = 1.1 # second
while True:
    time.sleep(0.001)
    abc = abc + 1
    if int(abc/wait_time/1000) >int((abc-1)/wait_time/1000):
        num = s.sendto(payload.tostring()[0::8], (IP,PORT))
        print 'send '+str(num)+' bytes'


