#include "stdafx.h"
#include "imCmdHeader.h"
#include "imCmdPacket.h"

CIMCmdPacket::CIMCmdPacket()
{
	m_uiSendID = 0;
}

CIMCmdPacket::CIMCmdPacket(UINT uiSendID)
{
	m_uiSendID = uiSendID;
}

CIMCmdPacket::~CIMCmdPacket()
{
	m_uiSendID = 0;
}

VOID CIMCmdPacket::SetSendID(UINT uiSendID)
{
	m_uiSendID = uiSendID;
}


int CIMCmdPacket::SetupDataPkt(char * szBuf,ULONG ulMsgId, UCHAR ucCmdID, UINT uiRecvID, UCHAR ucType, char *data, UINT uiDataLen)
{
	//分配内存，包头+数据包+具体数据
	int nPacketLen = 0;
	if (ucType == IM_TYPE_REQUEST)
	{
		nPacketLen = sizeof(IM_CMD_HEADER)  + uiDataLen;
	}
	else if (ucType == IM_TYPE_RESPONSE)
	{
		nPacketLen = sizeof(IM_CMD_HEADER) + sizeof(IM_RESPONSE_DATA) + uiDataLen;
	}

	SetupHeaderData(szBuf, ulMsgId, ucCmdID,uiRecvID, ucType);
	CopyData(szBuf, ucType, data, uiDataLen);

	return nPacketLen;
}

VOID CIMCmdPacket::SetupHeaderData(char * szBuf, ULONG ulMsgId,UCHAR ucCmdID, UINT uiRecvID, UCHAR ucType)
{
	PIM_CMD_HEADER pich = (PIM_CMD_HEADER)szBuf;

	pich->uiSenderID = m_uiSendID;
	pich->uiRecverID = uiRecvID;
	pich->usLength	= sizeof(IM_CMD_HEADER);
	//if (ucCmdID == IM_LOG_IN || ucCmdID == IM_ADD_FRIEND) //登录，添加好友
	//{
	//	pich->ucVer = 0x04;  //登录与添加好友使用协议4.0
	//}
	//else
	//{
	//	pich->ucVer = IM_CMD_VERSION;
	//}

	pich->ucVer = IM_CMD_VERSION;


	pich->ucCmdID = ucCmdID;
	pich->uiMsgID = ulMsgId;

	if(IM_LOG_IN == ucCmdID)
		pich->uiReserved = 0;
	else
		pich->uiReserved = (ULONG) time(NULL);

	//设置是否转发位
	if ((IM_LOG_IN == ucCmdID)
	 ||(IM_LOG_OUT == ucCmdID)
	 ||(IM_CHANGE_STATUS == ucCmdID)
	 ||(IM_GET_NETINFO == ucCmdID))    //不需要转发
	{
		pich->ucCmdType = 0;
	}
	else
	{
		pich->ucCmdType = 1;
	}

	if (ucType == IM_TYPE_REQUEST)
	{
		pich->ucFlag = IM_TYPE_REQUEST;
	}
	else if(ucType == IM_TYPE_RESPONSE)
	{
		pich->ucFlag = IM_TYPE_RESPONSE;
	}
}

VOID CIMCmdPacket::CopyData(char * szBuf, UCHAR ucType, char *data, DWORD length)
{
	char *pTmp = szBuf;
	pTmp = pTmp + sizeof(IM_CMD_HEADER);
	if (ucType == IM_TYPE_REQUEST)
	{
		if ( data && length != 0 )
			memcpy(pTmp, data, length);
	} 
	else
	{
		PIM_RESPONSE_DATA pird = (PIM_RESPONSE_DATA)pTmp;
		pird->uiRsp = IM_RESPONSE_SUCCESS;
		pird->uiLen = length;
		
		pTmp += sizeof(IM_RESPONSE_DATA);
		if ( data && length != 0 )
			memcpy(pTmp, data, length);
	}
}


