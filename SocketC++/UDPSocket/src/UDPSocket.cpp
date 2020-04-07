
// UDPSocket.cpp: implementation of the UDPSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "UDPSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UDPSocket::UDPSocket() {
	sock = INVALID_SOCKET;
}

UDPSocket::~UDPSocket() {

}

int UDPSocket::InitSocket(const char *ip, int port) {

	server_addr_len = sizeof(server_addr);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cout<<"Error Create Socket"<<std::endl;
		exit(1);
	}

	bzero((char *) &server_addr, server_addr_len);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        exit(1);
    }
	// server_addr.sin_addr.s_addr = inet_addr(ip);
	
	// int one = 1;
	// setsockopt(serverSock,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one));
}

int UDPSocket::Bind() {

	if (bind(sock,(struct sockaddr *) &server_addr,server_addr_len) < 0) {
		std::cerr<<"Error Bind failed"<<std::endl;
		exit(1);
	}
	
	printf("Bind to (%s, %d)\n", inet_ntoa(server_addr.sin_addr), htons(server_addr.sin_port));
	return 0;
}

int UDPSocket::Connect() {

	if(connect(sock,(const struct sockaddr *) &server_addr,server_addr_len)!=0) {
		std::cout<<"Client could not connect"<<std::endl;
		exit(1);
	}
	
	printf("Connect to (%s, %d)\n", inet_ntoa(server_addr.sin_addr), htons(server_addr.sin_port));
	return 0;
}

int UDPSocket::Send(char buff[], int buff_len, std::string sideway) {

	if(sock == INVALID_SOCKET)
		exit(1);

	server_addr_len = sizeof(server_addr);
	receive_addr_len = sizeof(receive_addr);
	
	if (sideway == "server") {
		buff_len = strlen(buff)-1; // -1 to correct fgets \n
		if ((nsent=sendto(sock,(char*)buff,buff_len,0,(struct sockaddr*)&server_addr,server_addr_len)) < 0) {
			printf("Can't send message.\n");
			exit(1);
		}
		printf("sent %d bytes to (%s, %d)\n", nsent, inet_ntoa(server_addr.sin_addr), htons(server_addr.sin_port));
	}
	else if (sideway == "client") {
		buff_len = strlen(buff);
		if ((nsent=sendto(sock,(char*)buff,buff_len,0,(struct sockaddr*)&receive_addr,receive_addr_len)) < 0) {
			printf("Can't send message.\n");
			exit(1);
		}
		printf("\nSent message: %s", buff);
		printf("\nsent %d bytes to (%s, %d)\n", nsent, inet_ntoa(receive_addr.sin_addr), htons(receive_addr.sin_port));
	}

	if(nsent != buff_len) {
		std::cout<<"Send error"<<std::endl;
		sock = INVALID_SOCKET;
		exit(1);
	}
	return nsent;
}

int UDPSocket::Receive(char buff[], int buff_len) {

	if(sock == INVALID_SOCKET)
		exit(1);

	receive_addr_len = sizeof(receive_addr);

	if ((nread=recvfrom(sock,(char*)buff,buff_len,0,(struct sockaddr*)&receive_addr,&receive_addr_len)) < 0) {
		printf("Can't recieve message.\n");
		exit(1);
	}
	printf("\nReceive message: %s", buff);
    printf("\nreceive %d bytes from (%s, %d)\n", nread, inet_ntoa(receive_addr.sin_addr), htons(receive_addr.sin_port));

	if(nread == SOCKET_ERROR || nread < 0) {	
		std::cout<<"Receive bytes Error"<<std::endl;
		sock=INVALID_SOCKET;
		exit(1);
	}
	return nread;
}

void UDPSocket::Close() {
	shutdown(sock,SD_BOTH);
	closesocket(sock);
	sock=INVALID_SOCKET;	
}
