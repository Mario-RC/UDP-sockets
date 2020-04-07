
from UDPSocket.Socket import Socket

sent_template = "Sent Message: "

IP_ADDRESS = "127.0.0.1" # server's hostname
PORT = 5000 # server's port

clientSock = Socket(IP_ADDRESS, PORT)
clientSock.connect()

def CommunicationToServer(quit="exit"):
    user_input = ""
    try:
        while user_input != quit:
            user_input = quit
            try:
                user_input = str(input(sent_template))
                clientSock.send(user_input, sideway='server')
            except EOFError:
                print(user_input)
            if user_input:
                while user_input[-1] in "!.":
                    user_input = user_input[:-1]
                response = clientSock.receive()
                
    finally:
        clientSock.close()

if __name__ == "__main__":
    CommunicationToServer()
    