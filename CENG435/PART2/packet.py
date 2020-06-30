import struct
import hashlib

# Common Packet Length
packetLength = 1000
partitionLength = 500
totalLength = 50000
size = totalLength / partitionLength - 1

def unpack(msg):
    checksum = struct.unpack("32s", msg[:32])[0]
    pkt = msg[32:]
    packetChecksum = hashlib.md5(pkt).hexdigest()
    if packetChecksum == checksum:
        seq = struct.unpack("i", pkt[:4])[0]
        return (seq,pkt[4:])
    else:
        return false
def pack(seq,pkt):
    part = struct.pack("i", seq) + pkt
    checksum = hashlib.md5(part).hexdigest()
    part = struct.pack("32s", checksum) + part
    return part
