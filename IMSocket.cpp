#include "StdAfx.h"
#include "IMSocket.h"
#include "IMConst.h"

DWORD WINAPI RecvThread(PVOID pPara);
DWORD WINAPI SendThread(PVOID pPara);

IMSocket::IMSocket(void)
{
	m_bInit = false;
	m_hSendThread = NULL;

	Init();
}


IMSocket::~IMSocket(void)
{
}

void IMSocket::SetImID(UINT imid)
{
	m_sendid = imid;

	m_pkt.SetSendID(m_sendid);
}

bool IMSocket::Init()
{
	WSADATA wsa;  
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0) 
		return false;  

	return true;
}

bool IMSocket::InitializeSocket()
{
	//ULONG ip = ipPort.first;
	USHORT port = 8851;

	if ( ! m_bInit )
	{
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

		if (INVALID_SOCKET == m_socket)
			return false;

		//设置非阻塞方式连接
		unsigned long ul = 1;
		int ret = ioctlsocket(m_socket, FIONBIO, (unsigned long*)&ul);
		if(ret==SOCKET_ERROR)
			return false;

		m_addr.sin_family = AF_INET;
		m_addr.sin_port = htons(port);
		m_addr.sin_addr.S_un.S_addr = inet_addr(DomainName2IPAddress(MSG_SRV_ADDR).c_str());

		srand((unsigned int)time(NULL));
		USHORT sPort = rand() % 65536;

		struct sockaddr_in local_addr;
		int len = sizeof(local_addr);
		//DWORD dwAddress= ntohl( inet_addr(m_ipList[i].c_str()));  
		//IMSysConfig::Instance()->m_uLocalIp = htonl( dwAddress);  

		//local_addr.sin_addr.S_un.S_addr = dwAddress;
		local_addr.sin_addr.S_un.S_addr = ADDR_ANY;
		local_addr.sin_family = AF_INET;
		local_addr.sin_port = htons(sPort);
		getsockname(m_socket, (sockaddr*) & local_addr, &len);

		int flag=1,ilen=sizeof(int);
		if(setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,(char*)&flag,ilen)!= 0 )
		{
			perror("setsockopt");
		}

		connect(m_socket, (struct sockaddr *) &m_addr, sizeof(struct sockaddr));

		//select 模型，即设置超时
		struct timeval timeout ;
		fd_set r;

		FD_ZERO(&r);
		FD_SET(m_socket, &r);
		timeout.tv_sec = 3; //连接超时时间（sec）
		timeout.tv_usec =0;
		ret = select(0, 0, &r, 0, &timeout);
		if ( ret <= 0 )
			return false;

		//设回阻塞模式
		unsigned long ul1= 0 ;
		ret = ioctlsocket(m_socket, FIONBIO, (unsigned long*)&ul1);
		if(ret==SOCKET_ERROR)
			return false;

		m_bInit = true;

		//if(m_hSendThread == NULL)
		//	m_hSendThread = CreateThread(NULL, 0, SendThread, this, NULL, NULL);

		//CreateThread(NULL, 0, HeartBeatThread, this, NULL, NULL);
		CreateThread(NULL, 0, RecvThread, this, NULL, NULL);
	}

	return true;
}

int IMSocket::Send(char * buf, ULONG ulMsgId,UCHAR ucCmdID,UINT uiRecvID, UCHAR ucType, char *data, UINT uiDataLen)
{
	int nPacketLen  = m_pkt.SetupDataPkt(buf, ulMsgId, ucCmdID, uiRecvID, ucType, data, uiDataLen);

	PIM_CMD_HEADER pHeader= (PIM_CMD_HEADER)buf; 
	if (nPacketLen)
	{
		pHeader->usLength = nPacketLen - sizeof(IM_CMD_HEADER);
		return send(m_socket, buf, nPacketLen, 0);  
	}

	return 0;
}

//DWORD WINAPI SendThread(PVOID pPara)
//{
//	IMSocket *pUser = (IMSocket *)pPara;
//
//	//while(true)
//	//{
//	//	pUser->SendDataProc();
//	//}
//
//	return 0;
//}

DWORD WINAPI RecvThread(PVOID pPara)
{
	IMSocket *pUser = (IMSocket *)pPara;

	bool bFirst = false;
	int len = sizeof(SOCKADDR_IN);

	struct timeval fd_timeout;
	fd_timeout.tv_sec = 1;
	fd_timeout.tv_usec = 0;

	while(pUser->m_bInit)
	{
		char *pRecvbuf = new char[IM_BUF_SIZE];
		ZeroMemory(pRecvbuf, IM_BUF_SIZE);

		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(pUser->m_socket, &readfds);

		int iRet = select(0, &readfds, NULL, NULL, &fd_timeout);

		int retLen = -2;
		if( iRet>0 && FD_ISSET(pUser->m_socket, &readfds))
		{
			retLen = recv(pUser->m_socket, pRecvbuf, IM_BUF_SIZE, 0);
		}

		if ( pUser->m_addr.sin_addr.S_un.S_addr == 0 ||retLen == -2)
		{
			delete [] pRecvbuf;
			pRecvbuf = NULL;

			continue;
		}

		if( retLen == -1 || retLen == 0)
		{
			if(retLen == -1)
			{
				char buf[IM_BUF_SIZE] = {0};
				pUser->Send(buf, 0, IM_LOG_OUT, 0, IM_TYPE_REQUEST,NULL,0);
			}

			break;
		}

		PIM_CMD_HEADER pheader = (PIM_CMD_HEADER)pRecvbuf;

		//返回消息验证包
		pUser->SendMsgCheck(pheader);

		//解析内容
		pUser->m_recver.ParseMessage(pheader);

		delete [] pRecvbuf;
		pRecvbuf = NULL;
	}

	return 0;
}

void IMSocket::SendMsgCheck(PIM_CMD_HEADER pheader)
{
	if(pheader->ucCmdID == IM_NORMAL_CHAT)
	{
		char buf[100] = {0};
		Send(buf, pheader->uiMsgID, IM_MSG_PERSONAL_CHECK, pheader->uiSenderID, IM_TYPE_RESPONSE, NULL, 0);
	}
	else if(pheader->ucCmdID == IM_TEAM_CHAT)
	{
		char buf[100] = {0};
		Send(buf, pheader->uiMsgID, IM_MSG_TEAM_CHECK, pheader->uiRecverID, IM_TYPE_RESPONSE, NULL, 0);
	}
	else if(pheader->ucCmdID == IM_SERVIE_NOTICE)
	{ 
		char buf[100]={0};
		Send(buf, pheader->uiMsgID, IM_SERVIE_NOTICE_CHECK, pheader->uiSenderID, pheader->ucCmdType , NULL , 0);
	}
}


std::string IMSocket::DomainName2IPAddress(std::string strDomain)
{
	struct hostent * host = gethostbyname(strDomain.c_str());

	std::string ip;
	for (int k=0; host != NULL && host->h_addr_list[k] != NULL; k++)
		ip = inet_ntoa(*(struct in_addr*)host->h_addr_list[k]);

	return ip;
}