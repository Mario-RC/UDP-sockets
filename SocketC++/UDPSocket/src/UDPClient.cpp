
// UDPClient.cpp: implementation of the UDP Socket Client class.
//
//////////////////////////////////////////////////////////////////////

#include "UDPClient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UDPCLient::UDPCLient() {
	Init();
}

UDPCLient::~UDPCLient() {
	clientSock.Close();
}

void UDPCLient::Init() {
	clientSock.InitSocket("127.0.0.1", 5000);
	clientSock.Connect();
	ComunicationServer();
}

void UDPCLient::ComunicationServer() {
	while(1) {
		bzero(buff, BUFFER_SIZE);
		printf("\nSent Message: ");
		fgets(buff, BUFFER_SIZE, stdin);
		clientSock.Send(buff, "server");

		bzero(buff, BUFFER_SIZE);
		clientSock.Receive(buff, BUFFER_SIZE);
	}
	clientSock.Close();
}