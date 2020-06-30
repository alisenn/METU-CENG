import gen
import packet
import sys
from threading import Thread

# Command Line Arguments
me = sys.argv[1]

# Listen s and send data to d
def s():
    while True:
        (data, addr) = gen.listenSockets["s"].recvfrom(packet.packetLength)
        if data:
            gen.talkSockets["d"].send(data)
        else:
            continue

# Listen d and send data to s
def d():
    while True:
        (data, addr) = gen.listenSockets["d"].recvfrom(packet.packetLength)
        if data:
            gen.talkSockets["s"].send(data)
        else:
            continue

gen.setUp(me)

sThread = Thread(target=s)
dThread = Thread(target=d)
sThread.start()
dThread.start()
sThread.join()
dThread.join()
