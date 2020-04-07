
// UDPClient.cpp: implementation of the UDP Socket Client class.
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

#include "UDPClient.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UDPCLient::UDPCLient() {
	Init();
}

UDPCLient::~UDPCLient() {
	serverSock.Close();
}

void UDPCLient::Init() {
	serverSock.Connect("127.0.0.1",5000);
	while(1) {
		char buff[1024];
		
		printf("\nSent Message: ");
		fgets(buff, BUFFER_SIZE, stdin);
		serverSock.Send(buff,sizeof(buff));

		serverSock.Receive(buff,sizeof(buff));
		printf("Received message: %s\n",buff);
	}
	serverSock.Close();
}
