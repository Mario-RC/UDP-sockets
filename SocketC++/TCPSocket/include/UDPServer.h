
// UDPServer.h: interface for the UDP Socket Server class.

#if !defined(AFX_UDPSERVER_H__9510340A_3D75_485F_93DC_302A43B8039A__INCLUDED_)
#define AFX_UDPSERVER_H__9510340A_3D75_485F_93DC_302A43B8039A__INCLUDED_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <Socket.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BUFFER_SIZE 1024

class UDPServer {
public:
	UDPServer();
	virtual ~UDPServer();	

	void Init();
	void ComunicationClient();

	Socket serverSock;
	Socket clientSock;
	char buff[1024];
};

#endif // !defined(AFX_UDPSERVER_H__9510340A_3D75_485F_93DC_302A43B8039A__INCLUDED_)
