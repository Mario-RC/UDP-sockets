
import socket
import sys

BUFFER_SIZE = 1024

class Socket():

    def __init__(self, ip, port):
        self.socketaddr = (ip, port)
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        except sock.error as err: 
            print("ERROR: Socket creation failed with error %s" %(err))

    def bind(self):
        try:
            self.sock.bind(self.socketaddr)
            print("Bind to %s\n" % repr(self.socketaddr))
        except:
            print("ERROR: Bind to %s refused" % repr(self.socketaddr))
            sys.exit(1)

    def connect(self):
        try:
            self.sock.connect(self.socketaddr)
            print("Connected to %s\n" % repr(self.socketaddr))
        except:
            print("ERROR: Connection to %s refused" % repr(socketaddr))
            sys.exit(1)

    def send(self, msg, sideway):
        buff = msg.encode()
        if sideway == 'server':
            nsent = self.sock.sendto(buff, self.socketaddr)
            print('sent %s bytes to %s\n' % (nsent, self.socketaddr))
        elif sideway == 'client':
            nsent = self.sock.sendto(buff, self.receiveaddr)
            print("Sent message: " + msg)
            print('sent %s bytes back to %s\n' % (nsent, self.receiveaddr))
    
    def receive(self):
        buff, self.receiveaddr = self.sock.recvfrom(BUFFER_SIZE)
        msg = buff.decode('utf-8') # msg = buffer.decode(), zxc = b'zxc'.decode()
        print ("Received message: " + msg)
        print('received %s bytes from %s\n' % (len(buff), self.receiveaddr))
        return msg

    def close(self):
        print("Closing socket")
        self.sock.close()
