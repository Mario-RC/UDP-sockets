
// UDPClient.h: interface for the UDP Socket Client class.

#if !defined(AFX_UDPCLIENT_H__9510340A_3D75_485F_93DC_302A43B8039A__INCLUDED_)
#define AFX_UDPCLIENT_H__9510340A_3D75_485F_93DC_302A43B8039A__INCLUDED_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <UDPSocket.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

#define BUFFER_SIZE 1024

class UDPCLient {
public:
	UDPCLient();
	virtual ~UDPCLient();	
	
	void Init();
	void ComunicationServer();
	
	UDPSocket clientSock;
	char buff[BUFFER_SIZE];
};

#endif // !defined(AFX_UDPCLIENT_H__9510340A_3D75_485F_93DC_302A43B8039A__INCLUDED_)
