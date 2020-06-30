import subprocess
import ipTable
from socket import *
from threading import Thread

listenSockets = {}
talkSockets = {}

def setUp(whoami):
    global listenSockets, talkSockets
    # Set Listen and Talk Sockets According to Host Name with Using ipTable Dictionary
    if(whoami == "s" or whoami == "d"):
        listenSockets["r1"] = socket(AF_INET, SOCK_DGRAM)
        listenSockets["r2"] = socket(AF_INET, SOCK_DGRAM)
        listenSockets["r3"] = socket(AF_INET, SOCK_DGRAM)
        talkSockets["r1"] = socket(AF_INET, SOCK_DGRAM)
        talkSockets["r2"] = socket(AF_INET, SOCK_DGRAM)
        talkSockets["r3"] = socket(AF_INET, SOCK_DGRAM)
    if(whoami == "r1" or whoami == "r2" or whoami == "r3"):
        listenSockets["s"] = socket(AF_INET, SOCK_DGRAM)
        listenSockets["d"] = socket(AF_INET, SOCK_DGRAM)
        talkSockets["s"] = socket(AF_INET, SOCK_DGRAM)
        talkSockets["d"] = socket(AF_INET, SOCK_DGRAM)

    #whoami listens the ith value in listenSockets
    for i in listenSockets:
        listenSockets[i].bind(ipTable.ip_table[whoami+"_"+i])
    #whoami talks with jth value in talkSockets
    for j in talkSockets:
        talkSockets[j].connect(ipTable.ip_table[j+"_"+whoami])

def closeAll():
    global listenSockets
    global talkSockets
    for i in listenSockets:
        listenSockets[i].close()
    for j in talkSockets:
        talkSockets[j].close()
