#pragma once

#include "IMCmdPacket.h"
#include "Recver.h"
#include "os_singleton.h"
#include <string>

#include "Winsock2.h"
#pragma comment(lib, "Ws2_32.lib")

class IMSocket : public onesec::Singleton<IMSocket>
{
public:
	IMSocket(void);
	~IMSocket(void);

	bool	m_bInit;
	SOCKET	m_socket;
	SOCKADDR_IN	m_addr;
	UINT						m_sendid;

	Recver m_recver;

	void SetImID(UINT imid);
	bool InitializeSocket();
	int Send(char * buf, ULONG ulMsgId,UCHAR ucCmdID,UINT uiRecvID, UCHAR ucType, char *data, UINT uiDataLen);

	void SendMsgCheck(PIM_CMD_HEADER pheader);

private:
	CIMCmdPacket				m_pkt;

	HANDLE m_hSendThread;

	bool Init();

	//ÓòÃû×ª»»ipµØÖ·
	std::string DomainName2IPAddress(std::string strDomain);
};

