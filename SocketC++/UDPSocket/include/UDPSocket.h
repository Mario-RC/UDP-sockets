
// UDPSocket.h: interface for the UDPSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDPSOCKET_H__F0ACF86D_2491_474D_8E1E_09D4B604D51A__INCLUDED_)
#define AFX_UDPSOCKET_H__F0ACF86D_2491_474D_8E1E_09D4B604D51A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _WIN32
	#include <winsock2.h>
	#pragma comment (lib, "ws2_32.lib")
#else
	#include <sys/time.h> 
	#include <sys/types.h>    
	#include <sys/socket.h>
	#include <sys/select.h>	
	#include <unistd.h>
	#include <string.h>
	#include <string>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <errno.h>
	#include <iostream>
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define SD_BOTH SHUT_RDWR
	#define closesocket(x) close(x)
	#define Sleep(x) usleep(x*1000)
#endif

using namespace std;

class UDPSocket {
public:
	UDPSocket();
	virtual ~UDPSocket();

	int InitSocket(const char *ip, int port);
	int Bind();
	int Connect();
	int Send(char buff[], int buff_len, std::string sideway);
	int Receive(char buff[], int buff_len);
	void Close();

private:
	struct sockaddr_in server_addr;
	struct sockaddr_in receive_addr;
	socklen_t server_addr_len;
	socklen_t receive_addr_len;
	int sock, nread, nsent;
};

#endif // !defined(AFX_UDPSOCKET_H__F0ACF86D_2491_474D_8E1E_09D4B604D51A__INCLUDED_)
