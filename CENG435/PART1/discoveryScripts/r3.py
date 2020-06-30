from threading import Thread
import time
from socket import *
import os

# Ip Addresses and Ports of Links of r3 Node

localdServerAddr = '10.10.7.2'
localdServerPort = 14534

localr2ServerAddr = '10.10.6.2'
localr2ServerPort = 14532

localsServerAddr = '10.10.3.2'
localsServerPort = 14530

sServerAddr = '10.10.3.1'
sServerPort = 14503

r2ServerAddr = '10.10.6.1'
r2ServerPort = 14523

dServerAddr = '10.10.7.1'
dServerPort = 14543

# Socket Connections

localdSocket = socket(AF_INET, SOCK_DGRAM)
localdSocket.bind((localdServerAddr, localdServerPort))

localr2Socket = socket(AF_INET, SOCK_DGRAM)
localr2Socket.bind((localr2ServerAddr, localr2ServerPort))

localsSocket = socket(AF_INET, SOCK_DGRAM)
localsSocket.bind((localsServerAddr, localsServerPort))

dSocket = socket(AF_INET, SOCK_DGRAM)
dSocket.connect((dServerAddr, dServerPort))

r2Socket = socket(AF_INET, SOCK_DGRAM)
r2Socket.connect((r2ServerAddr, r2ServerPort))

sSocket = socket(AF_INET, SOCK_DGRAM)
sSocket.connect((sServerAddr, sServerPort))

# Delete Old Log Files
os.system("rm -f r3*.txt")

# Connection with Node d / Listen and Take Log That Data is received
def d():
	while True:
		(data, addr) = localdSocket.recvfrom(4)
		with open("r3d_recv.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")

# Connection with Node r2 / Listen, Response to r2, Send The Same Data to d and s, Take Log That Data is sent
def r2():
	while True:
		(data, addr) = localr2Socket.recvfrom(4)
		r2Socket.send(data)
		dSocket.send(data)
		with open("r3d_send.txt", "a") as myfile:
    			myfile.write(data+ "\t"+str( int(time.time() * 1000*1000))+ "\n")
		sSocket.send(data)
		with open("r3s_send.txt", "a") as myfile:
    			myfile.write(data+ "\t"+str( int(time.time() * 1000*1000))+ "\n")

# Connection with Node s / Listen and Take Log That Data is received
def s():
	while True:
		(data, addr) = localsSocket.recvfrom(4)
		with open("r3s_recv.txt", "a") as myfile:
    			myfile.write(data+ "\t"+str( int(time.time() * 1000*1000))+ "\n")

#Threads for Multirequesting
Thread(target=d).start()
Thread(target=r2).start()
Thread(target=s).start()

#Wait Keyboard Interrupt for Exit and Keep The Server Alive
try:
	while True:
		continue
except KeyboardInterrupt:
	localdSocket.close()
	localr2Socket.close()
	localsSocket.close()
	dSocket.close()
	r2Socket.close()
	sSocket.close()
