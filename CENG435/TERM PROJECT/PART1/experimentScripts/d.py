from threading import Thread
import os
import time
from socket import *

# Set server ip's
localr3ServerAddr = '10.10.7.1'
localr3ServerPort = 14543

r3ServerAddr = '10.10.7.2'
r3ServerPort = 14534

#Open socket connection
localr3Socket = socket(AF_INET, SOCK_DGRAM)
localr3Socket.bind((localr3ServerAddr, localr3ServerPort))

r3Socket = socket(AF_INET, SOCK_DGRAM)
r3Socket.connect((r3ServerAddr, r3ServerPort))

#Delete old files that created before
os.system("rm -f recv.txt")

# Keep the information of time that the packets come
def r3():
	while True:
		(data, addr) = localr3Socket.recvfrom(4)
		with open("recv.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")

#Start simulteneous processing
Thread(target=r3).start()

#Continue until the KeyboardInterrupt comes
try:
	while True:
		continue
except KeyboardInterrupt:
	localr3Socket.close()
	r3Socket.close()
