
// UDPServer.cpp: implementation of the UDP Socket Server class.
//
//////////////////////////////////////////////////////////////////////

#include "UDPServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UDPServer::UDPServer() {
	Init();
}

UDPServer::~UDPServer() {
	serverSock.Close();
}

void UDPServer::Init() {
	serverSock.InitSocket("127.0.0.1", 5000);
	serverSock.Bind();
	ComunicationClient();
}

void UDPServer::ComunicationClient() {
	while(1) {
		bzero(buff, BUFFER_SIZE);
		serverSock.Receive(buff, BUFFER_SIZE);

		bzero(buff, BUFFER_SIZE);
		strncpy(buff, "Received", sizeof(buff));
		serverSock.Send(buff, BUFFER_SIZE, "client");
	}
	serverSock.Close();
}
