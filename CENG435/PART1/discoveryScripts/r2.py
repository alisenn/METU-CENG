from threading import Thread
import time
import os
from socket import *

# Ip Addresses and Ports of Links of r2 Node

localdServerAddr = '10.10.5.1'
localdServerPort = 14524

localr1ServerAddr = '10.10.8.2'
localr1ServerPort = 14521

localr3ServerAddr = '10.10.6.1'
localr3ServerPort = 14523

localsServerAddr = '10.10.2.1'
localsServerPort = 14520

dServerAddr = '10.10.5.2'
dServerPort = 14542

r1ServerAddr = '10.10.8.1'
r1ServerPort = 14512

r3ServerAddr = '10.10.6.2'
r3ServerPort = 14532

sServerAddr = '10.10.2.2'
sServerPort = 14502

# Socket Connections

localdSocket = socket(AF_INET, SOCK_DGRAM)
localdSocket.bind((localdServerAddr, localdServerPort))

localr1Socket = socket(AF_INET, SOCK_DGRAM)
localr1Socket.bind((localr1ServerAddr, localr1ServerPort))

localr3Socket = socket(AF_INET, SOCK_DGRAM)
localr3Socket.bind((localr3ServerAddr, localr3ServerPort))

localsSocket = socket(AF_INET, SOCK_DGRAM)
localsSocket.bind((localsServerAddr, localsServerPort))

dSocket = socket(AF_INET, SOCK_DGRAM)
dSocket.connect((dServerAddr, dServerPort))

r1Socket = socket(AF_INET, SOCK_DGRAM)
r1Socket.connect((r1ServerAddr, r1ServerPort))

r3Socket = socket(AF_INET, SOCK_DGRAM)
r3Socket.connect((r3ServerAddr, r3ServerPort))

sSocket = socket(AF_INET, SOCK_DGRAM)
sSocket.connect((sServerAddr, sServerPort))

# Delete Old Log Files
os.system("rm -f r2*.txt")

# Connection with Node d / Listen and Take Log That Data is received
def d():
	while True:
		(data, addr) = localdSocket.recvfrom(4)
		with open("r2d_recv.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")

# Connection with Node r1 / Listen and Take Log That Data is received
def r1():
	while True:
		(data, addr) = localr1Socket.recvfrom(4)
		with open("r2r1_recv.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")

# Connection with Node r3 / Listen and Take Log That Data is received
def r3():
	while True:
		(data, addr) = localr3Socket.recvfrom(4)
		with open("r2r3_recv.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")

# Connection with Node s / Listen and Take Log That Data is received
def s():
	while True:
		(data, addr) = localsSocket.recvfrom(4)
		with open("r2s_recv.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")

# Create Data Packets And Send Them To All Neighbors Then Take Log That Data is sent
def virus():
	for x in range(1000):
		data = str(x).zfill(4)
		dSocket.send(data)
		with open("r2d_send.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")
		r1Socket.send(data)
		with open("r2r1_send.txt", "a") as myfile:
    			myfile.write(data +"\t"+ str(int(time.time() * 1000*1000))+ "\n")
		r3Socket.send(data)
		with open("r2r3_send.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")
		sSocket.send(data)
		with open("r2s_send.txt", "a") as myfile:
    			myfile.write(data+ "\t"+ str(int(time.time() * 1000*1000))+ "\n")

#Threads for Multirequesting
Thread(target=d).start()
Thread(target=r1).start()
Thread(target=r3).start()
Thread(target=s).start()
Thread(target=virus).start()

#Wait Keyboard Interrupt for Exit and Keep The Server Alive
try:
	while True:
		continue
except KeyboardInterrupt:
	localdSocket.close()
	localr1Socket.close()
	localr3Socket.close()
	localsSocket.close()
	dSocket.close()
	r1Socket.close()
	r3Socket.close()
	sSocket.close()
