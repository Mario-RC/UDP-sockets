// Socket.cpp: implementation of the Socket class.
//
//////////////////////////////////////////////////////////////////////

#include "Socket.h"
#include <iostream>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Socket::Socket()
{
	sock=INVALID_SOCKET;
}

Socket::~Socket()
{

}

int Socket::Connect(const char *ip,int port)
{
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(ip);
	server_address.sin_port = htons(port);

	sock=socket(AF_INET, SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
	{
		std::cout<<"Client: Error create socket"<<std::endl;
		return -1;
	}

	int len= sizeof(server_address);
	if(connect(sock,(const struct sockaddr *) &server_address,len)!=0) 
	{	
		std::cout<<"Client could not connect"<<std::endl;
		return -1;
	}
	return 0;
}

int Socket::InitServer(const char *ip,int port)
{
	struct sockaddr_in server_address;
	
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(ip);
	server_address.sin_port = htons(port);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock==INVALID_SOCKET)
	{
		std::cout<<"Server: Error Create Socket"<<std::endl;
		return -1;
	}
//configuracion del socket para reusar direcciones
	int on=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

	int len = sizeof(server_address);
	if (bind(sock,(struct sockaddr *) &server_address,len) < 0)
	{
		std::cerr<<"Server: bind"<<std::endl;
		return -1;
	}
	// Damos como m�ximo 5 puertos de conexi�n.
	if (listen(sock,5) < 0)
	{
		std::cerr<<"Server: listen"<<std::endl;
		return -1;
	}	
	return 0;
}

Socket Socket::Accept()
{
	struct sockaddr_in client_address;
	#ifdef _WIN32
	int leng = sizeof(client_address);
	#else
	unsigned int leng = sizeof(client_address);
	#endif

	printf("Server accepting connections\n");

	Socket s;
	s.sock = accept(sock,(struct sockaddr *)&client_address, &leng);
	if(s.sock==INVALID_SOCKET)
	{
		std::cout<<"Server Accept returned invalid socket"<<std::endl;
	}
	return s;
}

int Socket::Send(char cad[],int length)
{
	if(sock==INVALID_SOCKET)
		return -1;
	int err=send(sock, cad, length,0);

	if(err!=length)
	{
		std::cout<<"Send error"<<std::endl;
		sock=INVALID_SOCKET;
		return -1;
	}
	return length;
}

int Socket::Receive(char cad[],int length)
{
	if(sock==INVALID_SOCKET)
		return -1;
	int r=recv(sock,cad,length,0);
	if(r==SOCKET_ERROR || r==0)
	{	
		std::cout<<"Receive bytes Error"<<std::endl;
		sock=INVALID_SOCKET;
		return -1;		
	}
	return r;
}

void Socket::Close()
{
	shutdown(sock,SD_BOTH);
	closesocket(sock);
	sock=INVALID_SOCKET;	
}
