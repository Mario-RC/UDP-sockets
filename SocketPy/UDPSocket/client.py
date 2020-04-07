
import socket
import sys
import random
from ctypes import *

IP_ADDRESS = "127.0.0.1" # 'localhost', the server's hostname or IP address
PORT = 5000 # The port used by the server
BUFFER_SIZE = 1024

# msg = buffer.decode()
# zxc = b'zxc'.decode()

# Message = "Hello, Server".encode()
# Message = str.encode("Hello, Server")
# class Payload(Structure):
#     _fields_ = [("id", c_uint32),
#                 ("temp", c_float),
#                 ("msg", c_wchar)]

def main():
    saddr = (IP_ADDRESS, PORT)
    
    try:
        clientSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except clientSock.error as err: 
        print("ERROR: Socket creation failed with error %s" %(err))

    try:
        clientSock.connect(saddr)
        print("Connected to %s\n" % repr(saddr))
    except:
        print("ERROR: Connection to %s refused" % repr(saddr))
        sys.exit(1)

    try:
        while True:
            msg = str(input("Sent message: "))
            buff = msg.encode()
            ssent = clientSock.sendto(buff, saddr)
            # nsent = clientSock.send(payload_out)
            print('sent %s bytes to %s\n' % (ssent, saddr))

            buff, saddr = clientSock.recvfrom(BUFFER_SIZE) # buffer size is 1024 bytes
            msg = buff.decode('utf-8')
            print ("Received message: " + msg)
            print('received %s bytes from %s\n' % (len(buff), saddr))

            # payload_out = Payload(1, random.uniform(-10, 30))
            # print("Sending id=%d, temp=%f" % (payload_out.id, payload_out.temp))
            # buff = clientSock.recv(sizeof(Payload))
            # payload_in = Payload.from_buffer_copy(buff)
            # print("Received id=%d, temp=%f" % (payload_in.id, payload_in.temp))

    finally:
        print("Closing socket")
        clientSock.close()

if __name__ == "__main__":
    main()
