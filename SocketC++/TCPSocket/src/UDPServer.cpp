
// UDPServer.cpp: implementation of the UDP Socket Server class.
//
//////////////////////////////////////////////////////////////////////

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "UDPServer.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UDPServer::UDPServer() {
	Init();
}

UDPServer::~UDPServer() {
	serverSock.Close();
	clientSock.Close();
}

void UDPServer::Init() {
	serverSock.InitServer("127.0.0.1",5000);
	clientSock = serverSock.Accept();
	ComunicationClient();
}

void UDPServer::ComunicationClient() {
	while(1) {
		char buff[1024];

		clientSock.Receive(buff,sizeof(buff));
		printf("\nReceived message: %s",buff);

		strncpy(buff, "Received", BUFFER_SIZE);
		clientSock.Send(buff,sizeof(buff));
		printf("Sent message: %s\n",buff);
	}
	serverSock.Close();
	clientSock.Close();
}
