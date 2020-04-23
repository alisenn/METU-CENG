from threading import Thread
import time
from socket import *
import os
# Set server ip's
localdServerAddr = '10.10.7.2'
localdServerPort = 14534

localsServerAddr = '10.10.3.2'
localsServerPort = 14530

sServerAddr = '10.10.3.1'
sServerPort = 14503

dServerAddr = '10.10.7.1'
dServerPort = 14543

#Open socket connection
localdSocket = socket(AF_INET, SOCK_DGRAM)
localdSocket.bind((localdServerAddr, localdServerPort))

localsSocket = socket(AF_INET, SOCK_DGRAM)
localsSocket.bind((localsServerAddr, localsServerPort))

dSocket = socket(AF_INET, SOCK_DGRAM)
dSocket.connect((dServerAddr, dServerPort))

sSocket = socket(AF_INET, SOCK_DGRAM)
sSocket.connect((sServerAddr, sServerPort))

# Keep the information of time that the packets send
def d():
	while True:
		(data, addr) = localdSocket.recvfrom(4)
		sSocket.send(data)

# Keep the information of time that the packets send
def s():
	while True:
		(data, addr) = localsSocket.recvfrom(4)
		dSocket.send(data)

#Start simulteneous processing
Thread(target=d).start()
Thread(target=s).start()

#Continue until the KeyboardInterrupt comes
try:
	while True:
		continue
except KeyboardInterrupt:
	localdSocket.close()
	localsSocket.close()
	dSocket.close()
	sSocket.close()
