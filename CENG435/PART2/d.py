#!/usr/bin/env python

import hashlib # used for generating md5 Checksums
from socket import *# for python Socket API
import struct  # used in decoding and encoding messages
import threading # used for multithreaded structure
import time  # used to generate timestamps

####################modified imports##########################
import gen
import sys
import random
import packet
import os

####################modified imports##########################



# Destination node

## Notice that, RDT protocol implemented here is reusable for any topology
## or any network configuration based bandwidth, delay, and packet size.
## In case of changing of above values, one can just alter the addresses
## of the destination interfaces with configuring routers correctly.
## In addition, Note that since RDT protocol implemented here sends feedbacks packets as
## 47 bytes (actually with Ethernet, IP and UDP headers it is 89 bytes)
## It will never send more data than 1000 bytes (max packet size of a packet in RDT protocol here)
expectedSeqnum = 0

def handler(listenSock, outSock, data):

	global expectedSeqnum
	while True:
		try:
			print "abi ben dinliyom valla"
			# Listen from interfaces
			msg = listenSock.recv(1000) # Expect maximum 1000 bytes
			if msg == "" or msg is None: # terminate connection
				print "kanka burda break yedim"
				outSock.send("")
				break

			# extract md5 checksum

			checksum = struct.unpack("32s", msg[:32])[0]
			pkt = msg[32:]
			# calculate packet checksum
			packetChecksum = hashlib.md5(pkt).hexdigest()

			# extract time information
			timeOld = struct.unpack("d", pkt[:8])[0]
			# extract sequence number
			seq = struct.unpack("i", pkt[8:12])[0]
			pkt = pkt[12:]

			print "paket hazir ",seq

			# if packet hasseqnum == expectedSeqnum and packet is notCorrupt; then send ACK pkt for the data packet
			if packetChecksum == checksum:
				if seq == expectedSeqnum:
					# append data to the data list
					data.append([seq, pkt])
					print "Received a data correctly, sending an ACK back to source with expectedSeqnum:", expectedSeqnum

					# pack old time, sequence number and data
					sendPkt = struct.pack("d", timeOld) + struct.pack("i", expectedSeqnum) + b"ACK"
					# calculate checksum
					ackChecksum = hashlib.md5(sendPkt).hexdigest()
					# embed to packet; now packet has; 32 + 4 + 900 = 936 bytes
					sendPkt = struct.pack("32s", ackChecksum) + sendPkt
					# send ACK packet to source
					outSock.send(sendPkt)

					#time.sleep(0.01)
					# increment expectedSeqnum
					expectedSeqnum += 1

				else:
					outSock.send(msg)
					print "Wrong Seq"
			else:
				print "OOPS, corrupt data packet.."


		except KeyboardInterrupt:
			outSock.send("")
			print "Exitting..."
			break





if __name__ == "__main__":
	local_s_server_addr = '10.10.3.2'
	local_s_server_port = 1800+30

	s_server_addr = '10.10.3.1'
	s_server_port = 1800+03

	local_s_socket = socket(AF_INET, SOCK_DGRAM)
	local_s_socket.bind((local_s_server_addr, local_s_server_port))

	s_socket = socket(AF_INET, SOCK_DGRAM)
	s_socket.connect((s_server_addr, s_server_port))
	# Two lists used for storing incoming data temporarily
	data1 = [] # for packets that came from interface-1 (host1)
	data2 = [] # for packets that came from interface-2 (host2)

	# Initially expectedSeqnum = 0




	# Since destination needs to listen from 2 interfaces at the same time
	# A thread for handling incoming messages from interface-1 (r1) gets created and sent to 'handler'
	# function with proper parameters
	#r1_handler = threading.Thread(target=handler,args=(sock1, outSock1, b1Addr, data1))
	#r1_handler.start()

	# Main execution will listen incoming messages from interface-2 (r2)
	handler(local_s_socket, s_socket,data2)

	# Wait implicitly for r1_handler to finish
	#r1_handler.join()

	# Combine arrived data from 2 lists
	data = data1 + data2

	# Receive file checksum at the end
	"""print "Waiting for Checksum of file to arrive.."
	msg = sock1.recv(1000)
	fileChecksum = struct.unpack("32s", msg[:32])[0]
	startTime = struct.unpack("d", msg[32:40])[0]

	print "File sending process took:", time.time() - startTime

	# and order them according to their sequence numbers; Be sure that data is in Correct Order
	data.sort()

	# Save them to a file named "output.txt"
	with open("output.txt", "wb") as outputFile:
		for i in data:
			outputFile.write(i[1])

	# Open "output.txt" file and read chunk by chunk to calculate its md5sum
	with open("output.txt", "rb") as outputFile:
		calculatedChecksum = hashlib.md5()
		# Iteratively calculate md5checksum of file
		for chunk in iter(lambda: outputFile.read(500000), b""):
			calculatedChecksum.update(chunk)

	# Check if file is transferred correctly
	if fileChecksum == calculatedChecksum.hexdigest():
		print "File is transferred correctly (md5Cheksums match).."
	else:
		print "OOPS, checksums does not match; file is not received correctly!"""

	print "Terminating process..."

	#s_socket.close()
	#local_s_socket.close()
