
from UDPSocket.Socket import Socket

IP_ADDRESS = "127.0.0.1" # server's hostname
PORT = 5000 # server's port

serverSock = Socket(IP_ADDRESS, PORT)
serverSock.bind()

def CommunicationToClient():
    try:
        while True:
            msg = serverSock.receive()
            if msg:
                msg = "Received"
                serverSock.send(msg, sideway='client')
                
    finally:
        serverSock.close()

if __name__ == "__main__":
    CommunicationToClient()
