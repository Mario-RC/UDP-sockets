
import socket
import sys

IP_ADDRESS = "127.0.0.1" # 'localhost'
PORT = 5000
BUFFER_SIZE = 1024

def main():
    saddr = (IP_ADDRESS, PORT)
    
    try:
        serverSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except serverSock.error as err: 
        print("ERROR: Socket creation failed with error %s" %(err))
    
    try:
        serverSock.bind(saddr)
        print("Bind to %s\n" % repr(saddr))
    except:
        print("ERROR: Bind to %s refused" % repr(saddr))
        sys.exit(1)

    try:
        while True:
            buff, caddr = serverSock.recvfrom(BUFFER_SIZE)
            msg = buff.decode()
            print ("Received message: " + msg)
            print('received %s bytes from %s\n' % (len(buff), caddr))
            
            msg = "Received"
            print("Sent message: " + msg)
            buff = msg.encode()
            csent = serverSock.sendto(buff, caddr)
            print('sent %s bytes back to %s\n' % (csent, caddr))
        
    finally:
        print("Closing socket")
        serverSock.close()

if __name__ == "__main__":
    main()
