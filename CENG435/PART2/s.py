#!/usr/bin/env python
import sys
import os
import hashlib # used for generating md5 Checksums
from socket import *  # for python Socket API
import struct # used in encoding and decoding messages
from threading import *
import threading
import time # used for timeout calculations
####################modified imports##########################
import gen
import random
import packet
import math
import hashlib
####################modified imports##########################


#  node

## Notice that, RDT protocol implemented here is reusable for any topology
## or any network configuration based bandwidth, delay, and packet size.
## In case of changing of above values, one can just alter the addresses
## of the destination interfaces with configuring routers correctly.
## In addition, Note that since RDT protocol implemented here sends data packets as
## 944 bytes (actually with Ethernet, IP and UDP headers it is 986 bytes)
## It will never send more data than 1000 bytes (max packet size of a packet in RDT protocol here)

local_r1_server_addr = '10.10.1.1'			#the adresses in the geni platform
local_r1_server_port = 1800+01				# port number we created (+01 mean s to r1) s->0 r1->1 r2->2 r3->3 d->4

local_r3_server_addr = '10.10.3.1'
local_r3_server_port = 1800+03

local_r2_server_addr = '10.10.2.2'
local_r2_server_port = 1800+02


r1_server_addr = '10.10.1.2'				# port number we created (+10 mean r1 to s) s->0 r1->1 r2->2 r3->3 d->4
r1_server_port = 1800+10

r3_server_addr = '10.10.3.2'
r3_server_port = 1800+30

r2_server_addr = '10.10.2.1'
r2_server_port = 1800+20



local_r1_socket = socket(AF_INET, SOCK_DGRAM)							# open a socket to listen r1 from s
local_r1_socket.bind((local_r1_server_addr, local_r1_server_port))

local_r3_socket = socket(AF_INET, SOCK_DGRAM)
local_r3_socket.bind((local_r3_server_addr, local_r3_server_port))

local_r2_socket = socket(AF_INET, SOCK_DGRAM)
local_r2_socket.bind((local_r2_server_addr, local_r2_server_port))



r1_socket = socket(AF_INET, SOCK_DGRAM)									#open a socket r1 in s to send packets to r1 from rs
r1_socket.connect((r1_server_addr, r1_server_port))

r3_socket = socket(AF_INET, SOCK_DGRAM)
r3_socket.connect((r3_server_addr, r3_server_port))

r2_socket = socket(AF_INET, SOCK_DGRAM)
r2_socket.connect((r2_server_addr, r2_server_port))


buff=[]

# Sequence number and base, initially = 0
seqnum = 0
base = 0
# Window size is set to 20
windowSize = 30

# timeout value is initially set to 0.5, it will be recalculated per incoming ACK packet
timeoutInterval = 0.5
# estimatedRTT and devRTT initially set to timeoutInterval and 0, respectively.
estimatedRTT = timeoutInterval
devRTT = 0

# set of locks for shared common variables
baseLock = threading.Lock()
timerLock = threading.Lock()
buffLock = threading.Lock()
baseCond = threading.Condition()

terminate=False
retransmit=False
isR1connected=True
isR2connected=True
# flag for acquiring file checksum and initial transfer time
first = False

def recvHandler_1(local_r3_socket):
	'''Function for handling incoming ACK pkts from destination'''
	global terminate, r3_socket,base
	while not terminate:
		openRouter(local_r3_socket,1)
	print "Exitting..."
	for i in range(100):
		r3_socket.send("")



#determines the open router and takes the socket and manipulates the packets
def openRouter(socket_,experiment):
	global terminate, base, timer,isR1connected,isR2connected,timeoutInterval
	msg = socket_.recv(1000) # expect a maximum of 1000 bytes
	checksum = struct.unpack("32s", msg[:32])[0]
	pkt = msg[32:]

	# calculate packet checksum
	packetChecksum = hashlib.md5(pkt).hexdigest()

	# if ACK packet is not corrupt
	if packetChecksum == checksum:
		# extract time information
		timeOld = struct.unpack("d", pkt[:8])[0]
		# extract sequence number
		seq = struct.unpack("i", pkt[8:12])[0]
		if seq == len(buff)-1:
			terminate = True
		else:
			# slide base (acknumOfPkt + 1) indices
			with baseLock:
				if seq == base:
					base = seq + 1

					with baseCond:
					    # Notify waiting threads
						baseCond.notify()
			if seq == base-1:
				print "Received a correct ACK packet from destination with seqnum:", seq
				with timerLock:
					with baseLock:
					# If base equals to current sequence number; stop timer
						if base == seqnum:
							timer.cancel()
						# Else; start timer
						else:
							timer.cancel()
							# calculate new sampleRTT
							sampleRTT = time.time() - timeOld
							# calculate new timeout interval value
							timeoutInterval = calcTimeoutInterval(sampleRTT)
							# Start timer again (with newly calculated timeout value)
							if experiment == 1:
								timer = threading.Timer(timeoutInterval, retransmitHandler_1)
							elif experiment == 2:
								timer = threading.Timer(timeoutInterval, retransmitHandler_2)
							timer.start()
	else:
	# else; packet is corrupt; wait for timeout
		print "OOPS.., Received a corrupt ACK packet.."


######################################################ACK#####ex2##################################################################
def recvHandler_2(local_r1_socket,local_r2_socket):
	#Function for handling incoming ACK pkts from destination
	global base, terminate, timer,isR1connected,isR2connected
	while not terminate:
		if not(isR1connected or isR2connected):
			break
		elif(isR1connected and isR2connected):
			openRouter(local_r1_socket,2)
			openRouter(local_r2_socket,2)

		elif(isR1connected and isR2connected==False ):
			openRouter(local_r1_socket,2)

			#if r2 is connected take ack from r1
		elif(isR1connected==False and isR2connected ):
			openRouter(local_r1_socket,2)
	print "Exitting..."
	for i in range(100):
		r1_socket.send("")
		r2_socket.send("")
###########################################################ex2##################################################################

def sendHandler_1():
	#Function for handling sending of data pkts to destination
	global buff, terminate, base,timer,seqnum,retransmit
		# Opens input file again for reading and sending it to
	with open("input.txt", "rb") as inputFile:
		# Read 500KB data from file
		data = inputFile.read(100000)
		# Insert checksum of file and sending process's start time

		#hold the time of the first packet that send


	while data:
		buff.append(data[0:900])
		data = data[900:]

	while not terminate:
		if not retransmit:
			with buffLock:
				if seqnum == len(buff):
					seqnum-=1
					r3_socket.send("")
					break
			with baseLock:
				tempBase = base
					# if sequence number is within the bounds of window size; send data
			if seqnum < tempBase + windowSize:
				sendHandler_helper(r3_socket,seqnum)

				if tempBase == seqnum:
					# For initial case; start timer
					with timerLock:
						timer.cancel()
						timer = threading.Timer(timeoutInterval, retransmitHandler_1)
						timer.start()

				# increment seqnum
				seqnum += 1

				# else; wait for base to slide
			else:
				with baseCond:
					print "Waiting for base to slide.."
					baseCond.wait()

					# Wait for network to process sent data
			time.sleep(0.02)




def sendHandler_helper(socket_,i):
	global buff,base
	part=buff[i]
	# pack current time, sequence number and data
	part = struct.pack("d", time.time()) + struct.pack("i", i) + part
	# calculate checksum
	checksum = hashlib.md5(part).hexdigest()
	# embed to packet; now packet has; 32 + 4 + 900 = 936 bytes
	part = struct.pack("32s", checksum) + part
	socket_.send(part)

def sendHandler_2():
	'''Function for handling sending of data pkts to destination'''
	global buff, terminate,base,timer,seqnum,isR1connected,isR2connected


	# Opens input file again for reading and sending it to
	with open("input.txt", "rb") as inputFile:
		# Read 500KB data from file
		data = inputFile.read(100000)
		# Insert checksum of file and sending process's start time
		# to the beginning of very first data packet

	while not terminate:
		print "Sending DATA to destination"
		with buffLock:
			if seqnum == len(buff):
				r1_socket.send("")
				r2_socket.send("")
				break

		with baseLock:
			tempBase = base
				# if sequence number is within the bounds of window size; send data
		if seqnum < tempBase + windowSize:

			# if seqnum is even then send that packet to destination to d1 interface (via r1)
			# with embedding seqnum and checksum

			#if R1 is not connected
			if not(isR1connected):
				sendHandler_helper(r2_socket,seqnum)

			#if R2 is not connected
			elif not(isR2connected):
				sendHandler_helper(r1_socket,seqnum)

			elif seqnum % 2 == 0:
				sendHandler_helper(r1_socket,seqnum)

				# if seqnum is odd then send that packet to destination to d2 interface (via r2)
				# with embedding seqnum and checksum
			elif seqnum % 2 == 1:
				sendHandler_helper(r2_socket,seqnum)

			if tempBase == seqnum:
				# For initial case; start timer
				with timerLock:
					timer.cancel()
					timer = threading.Timer(timeoutInterval, retransmitHandler_2)
					timer.start()

			seqnum += 1

				# else; wait for base to slide
		else:
			with baseCond:
				print "Waiting for base to slide.."
				baseCond.wait()

		# Wait for network to process sent data
		time.sleep(0.02)

	isR1connected=False
	isR2connected=False

def retransmitHandler_2(): #go back n yapcaz buraya
	global terminate, buffLock, timerLock,timer, baseLock,buff,base
	'''Function for handling fast retransmission in case of timeout'''
	while not terminate:
		with buffLock:
			with timerLock:
				# Start timer again
				timer = threading.Timer(timeoutInterval, retransmitHandler_2)
				timer.start()
		with baseLock:
			print "Timeout for packet:", base
			# Retransmit all UnAcked packets back
			# starting from base to seqnum
		for i in range(base,seqnum):
			part = buff[i]
			print "Retransmitting packet with seqnum:", i
			# if seqnum is even then send that packet to destination to d1 interface (via r1)
			# with embedding seqnum and checksum
			if i % 2 == 0:
				sendHandler_helper(r1_socket,i)
			# if seqnum is odd then send that packet to destination to d2 interface (via r2)
			# with embedding seqnum and checksum
			else:
				sendHandler_helper(r2_socket,i)

			# Wait for threads to process sent data
			time.sleep(0.02)

def retransmitHandler_1(): #go back n yapcaz buraya
	'''Function for handling fast retransmission in case of timeout'''
	global terminate, timer,retransmit,base,timeoutInterval
	print "true false: ",sendPacketThread.isAlive(),listenACKThread.isAlive()
	retransmit=True
	if not terminate:
		with buffLock:
			with timerLock:
				# Start timer again
				timer.cancel()
				#time.sleep(0.05)
				timer = threading.Timer(timeoutInterval, retransmitHandler_1)
				timer.start()
		with baseLock:
			print "Timeout for packet:", base,	" ",timeoutInterval
			# Retransmit all UnAcked packets back
			# starting from base to seqnum
			for i in range(base,seqnum):
				#time.sleep(0.0001)
				print "Retransmitting packet with seqnum:", i
				# if seqnum is even then send that packet to destination to d1 interface (via r1)

				# if seqnum is odd then send that packet to destination to d2 interface (via r2)

				sendHandler_helper(r3_socket,i)

				# Wait for threads to process sent data
			retransmit=False




def calcTimeoutInterval(sampleRTT):
	"""Function for calculation of timeout value based on sample, estimated and devRTT values"""
	global estimatedRTT, devRTT
	estimatedRTT = (0.875 * estimatedRTT) + (0.125 * sampleRTT)
	devRTT = (0.75 * devRTT) + (0.75 * abs(sampleRTT - estimatedRTT))
	return estimatedRTT + (4 * devRTT)

# Set initial timer
if(sys.argv[1]=="1"):



	timer = threading.Timer(timeoutInterval, retransmitHandler_1)
	sendPacketThread = Thread(target=sendHandler_1)
	listenACKThread = Thread(target=recvHandler_1, args=(local_r3_socket,))


else:
	timer = threading.Timer(timeoutInterval, retransmitHandler_2)
	sendPacketThread = Thread(target=sendHandler_2)
	listenACKThread = Thread(target=recvHandler_2, args=(local_r1_socket,local_r2_socket))

average_time=0
for i in range(10):
	time_init=int(time.time()*1000*1000)
	listenACKThread.start()
	sendPacketThread.start()

	listenACKThread.join()
	sendPacketThread.join()

	while listenACKThread.isAlive() or sendPacketThread.isAlive():
		continue

	average_time+=(int(time.time()*1000*1000)-time_init)

with open("average_time_exp1.txt", "w") as ffile:
	ffile.write(str(average_time)+ "\n")

r1_socket.close()
r2_socket.close()
r3_socket.close()

local_r1_socket.close()
local_r2_socket.close()
local_r3_socket.close()

print "Terminating process..."
