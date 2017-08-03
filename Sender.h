#pragma once

#include "IMSocket.h"
#include "IMConst.h"
#include "utils.h"

class Sender
{
public:
	Sender(){};
	~Sender(){};

	static ULONG getMsgId()
	{
		return GetTickCount();
	}

	static void LoginReq(std::string szName, std::string szPwd, bool bIsService = false)
	{
		LOGIN_REQUEST4 loginReq;
		strcpy_s(loginReq.szEmpNo, szName.c_str());
		strcpy_s(loginReq.szPasswd, szPwd.c_str());
		loginReq.chStatus = 0;
		loginReq.chFlag = bIsService;

		char buf[IM_BUF_SIZE] = {0};
		ULONG ulMsgId = getMsgId();

		IMSocket::Instance()->Send(buf, ulMsgId, IM_LOG_IN, 0, IM_TYPE_REQUEST, (char *)&loginReq, sizeof(loginReq));
	}

	static void HeartBeatReq()
	{
		//发送心跳包给服务器
		char buf[IM_BUF_SIZE] = {0};
		ULONG ulMsgId = getMsgId();
		//群聊的消息的接收者设置为群id
		IMSocket::Instance()->Send(buf, ulMsgId, IM_KEEPALIVE_CMD, 0, 
			IM_TYPE_REQUEST, NULL,0);
	}

	static void SendNormalChat(BaseInfo* userInfo, SStringT& strMsg)
	{
		SStringA strMb;
		strMb = S_CW2A(strMsg);

		//通过socket发送消息
		int nDataLen = strMb.GetLength() + sizeof(CHAT_DATA);
		char * pData  = new char[nDataLen];
		memset(pData, 0, nDataLen);

		CHAT_DATA * pChatReq = (CHAT_DATA*)pData;
		pChatReq->uiDataLen = strMb.GetLength();
		memcpy(pChatReq->chData, strMb, pChatReq->uiDataLen);

		UINT ulMsgId = getMsgId();
		char	 buf[IM_BUF_SIZE] = {0};
		IMSocket::Instance()->Send(buf, ulMsgId, IM_NORMAL_CHAT, userInfo->Id, IM_TYPE_REQUEST, (char *)pChatReq, nDataLen);

		IMLocalDb db;
		db.SaveFriendMsgToDB( IMGlobal::Instance()->m_pMyself->Id, IMGlobal::Instance()->m_pMyself->Name, userInfo->Id, userInfo->Name, (ULONG)time(NULL),
			1, strMb, strMb.GetLength(),GetCurFriendTableName(), ulMsgId);

		delete[] pData;
	}

	static void SendTeamChat(UINT uRecvId, SStringT& strMsg)
	{
		SStringA strMb;
		strMb = S_CW2A(strMsg);

		//通过socket发送消息
		int nDataLen = strMb.GetLength() + sizeof(CHAT_DATA);
		char * pData  = new char[nDataLen];
		memset(pData, 0, nDataLen);

		CHAT_DATA * pChatReq = (CHAT_DATA*)pData;
		pChatReq->uiDataLen = strMb.GetLength();
		memcpy(pChatReq->chData, strMb, pChatReq->uiDataLen);

		UINT ulMsgId = getMsgId();
		char	 buf[IM_BUF_SIZE] = {0};
		IMSocket::Instance()->Send(buf, ulMsgId, IM_TEAM_CHAT, uRecvId, IM_TYPE_REQUEST, (char *)pChatReq, nDataLen);

		IMLocalDb db;
		db.SaveTeamMsgToDB( IMGlobal::Instance()->m_pMyself->Id, IMGlobal::Instance()->m_pMyself->Name, uRecvId, (ULONG)time(NULL),
			strMb,strMb.GetLength(),GetCurTeamTableName(), ulMsgId, true);
	}
};