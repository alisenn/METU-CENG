from threading import Thread
import os
import time
from socket import *

# Set server ip's
localr3ServerAddr = '10.10.3.1'
localr3ServerPort = 14503

r3ServerAddr = '10.10.3.2'
r3ServerPort = 14530

#Open socket connection
localr3Socket = socket(AF_INET, SOCK_DGRAM)
localr3Socket.bind((localr3ServerAddr, localr3ServerPort))

r3Socket = socket(AF_INET, SOCK_DGRAM)
r3Socket.connect((r3ServerAddr, r3ServerPort))

os.system("rm -f send.txt")

# Keep the information of time that the packets recived
def r3():
	while True:
		(data, addr) = localr3Socket.recvfrom(4)

# Creates and sends packets to the destination
def virus():
	for x in range(3000):
		data = str(x).zfill(4)
		r3Socket.send(data)
		with open("send.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")

#Start simulteneous processing
Thread(target=r3).start()
Thread(target=virus).start()

#Continue until the KeyboardInterrupt comes
try:
	while True:
		continue
except KeyboardInterrupt:
	localr3Socket.close()
	r3Socket.close()
