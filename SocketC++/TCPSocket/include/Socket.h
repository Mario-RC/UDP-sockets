// Socket.h: interface for the Socket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKET_H__F0ACF86D_2491_474D_8E1E_09D4B604D51A__INCLUDED_)
#define AFX_SOCKET_H__F0ACF86D_2491_474D_8E1E_09D4B604D51A__INCLUDED_

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
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <errno.h>	
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define SD_BOTH SHUT_RDWR
	#define closesocket(x) close(x)
	#define Sleep(x) usleep(x*1000)
#endif

class Socket  
{
public:
	Socket();
	virtual ~Socket();
	
	int Connect(const char *ip,int port);
	int InitServer(const char *ip,int port);
	Socket Accept();
	void Close();

	int Send(char cad[],int length);
	int Receive(char cad[],int length);

private:
	int sock;
};

#endif // !defined(AFX_SOCKET_H__F0ACF86D_2491_474D_8E1E_09D4B604D51A__INCLUDED_)
