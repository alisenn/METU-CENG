from threading import Thread

from socket import *

# Ip Addresses and Ports of Links of d Node

localr1ServerAddr = '10.10.4.2'
localr1ServerPort = 14541

localr2ServerAddr = '10.10.5.2'
localr2ServerPort = 14542

localr3ServerAddr = '10.10.7.1'
localr3ServerPort = 14543

r1ServerAddr = '10.10.4.1'
r1ServerPort = 14514

r2ServerAddr = '10.10.5.1'
r2ServerPort = 14524

r3ServerAddr = '10.10.7.2'
r3ServerPort = 14534

# Socket Connections

localr1Socket = socket(AF_INET, SOCK_DGRAM)
localr1Socket.bind((localr1ServerAddr, localr1ServerPort))

localr2Socket = socket(AF_INET, SOCK_DGRAM)
localr2Socket.bind((localr2ServerAddr, localr2ServerPort))

localr3Socket = socket(AF_INET, SOCK_DGRAM)
localr3Socket.bind((localr3ServerAddr, localr3ServerPort))

r1Socket = socket(AF_INET, SOCK_DGRAM)
r1Socket.connect((r1ServerAddr, r1ServerPort))

r2Socket = socket(AF_INET, SOCK_DGRAM)
r2Socket.connect((r2ServerAddr, r2ServerPort))

r3Socket = socket(AF_INET, SOCK_DGRAM)
r3Socket.connect((r3ServerAddr, r3ServerPort))

# Connection with Node r1 / Listen and Send The Same Data
def r1():
	while True:
		(data, addr) = localr1Socket.recvfrom(4)
		r1Socket.send(data)
# Connection with Node r2 / Listen and Send The Same Data
def r2():
	while True:
		(data, addr) = localr2Socket.recvfrom(4)
		r2Socket.send(data)
# Connection with Node r3 / Listen and Send The Same Data
def r3():
	while True:
		(data, addr) = localr3Socket.recvfrom(4)
		r3Socket.send(data)

#Threads for Multirequesting

Thread(target=r1).start()
Thread(target=r2).start()
Thread(target=r3).start()

#Wait Keyboard Interrupt for Exit and Keep The Server Alive
try:
	while True:
		continue
except KeyboardInterrupt:
	localr1Socket.close()
	localr2Socket.close()
	localr3Socket.close()
	r1Socket.close()
	r2Socket.close()
	r3Socket.close()
