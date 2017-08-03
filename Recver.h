#pragma once

#include "IMSocket.h"
#include "IMCmdHeader.h"
#include "IMConst.h"
#include "IMGlobal.h"
#include "IMMsg.h"
#include "IMLocalDb.h"
#include "MainDlg.h"
#include "utils.h"

class CMainDlg;

class Recver
{
public:
	Recver(){};
	~Recver(){};

	void ParseMessage(IM_CMD_HEADER * pHeader)
	{
		switch(pHeader->ucCmdID)
		{
		case IM_LOG_IN:
			Login(pHeader);
			break;
		case IM_NORMAL_CHAT:
			NormalChat(pHeader);
			break;
		case IM_TEAM_CHAT:
			TeamChat(pHeader);
			break;
		case IM_KEEPALIVE_CMD:
			HeartBeat(pHeader);
			break;
		}
	}

	void Login(IM_CMD_HEADER * pHeader)
	{
		//登录成功 返回登录结果
		PIM_RESPONSE_DATA pRsp = (PIM_RESPONSE_DATA)( (CHAR*)pHeader+sizeof(IM_CMD_HEADER));

		if(pRsp->uiRsp == IM_RESPONSE_SUCCESS)
		{
			LOGIN_RESPONSE4 * plr = (LOGIN_RESPONSE4*)( (char*)pRsp + sizeof(IM_RESPONSE_DATA) );

			UserInfo* pUserInfo = IMGlobal::Instance()->m_pMyself;

			pUserInfo->Id = plr->uiUserID;
			pUserInfo->Name = S_CA2W(plr->szName);
			pUserInfo->EnName = S_CA2W(plr->szEnglishName);
			pUserInfo->Dept = S_CA2W(plr->szDept);
			pUserInfo->EmpNo = S_CA2W(plr->szNo);
			pUserInfo->EMail = S_CA2W(plr->szMail);
			pUserInfo->Note = S_CA2W(plr->szNote);
			//pUserInfo->AvatarPath = S_CA2W(plr->szPic);
			pUserInfo->AvatarId = pUserInfo->EmpNo;
			pUserInfo->AvatarPath = SetCurDir(L"Head\\").c_str();
			pUserInfo->AvatarPath.Append(S_CA2W(plr->szPic));

			if(!PathFileExists( (LPCWSTR)pUserInfo->AvatarPath) )
				DownLoadHead(S_CA2W(plr->szPic), (LPCWSTR)pUserInfo->AvatarPath);

			IMGlobal::Instance()->m_bIsLoginSuccess = true;
		}
		else
		{
			//登录失败
			IMGlobal::Instance()->m_bIsLoginSuccess = false;
		}

		HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_LOGIN);
		if(hEvent)
		{
			SetEvent(hEvent);
			CloseHandle(hEvent);
		}
	}

	void HeartBeat(IM_CMD_HEADER * pHeader)
	{
		int n = 0;
	}

	void NormalChat(IM_CMD_HEADER * pHeader)
	{
		UserInfo userInfo;
		UserInfo* pMySelf = IMGlobal::Instance()->m_pMyself;
		CMainDlg* pMainWnd = (CMainDlg*)IMGlobal::Instance()->m_pMainWnd;

		bool isFind = false;

		//同步消息send id是自己
		if(pHeader->uiSenderID == pMySelf->Id)
			isFind = pMainWnd->m_pAdapterLvContact->FindUserFormId(pHeader->uiRecverID, userInfo);
		else
			isFind = pMainWnd->m_pAdapterLvContact->FindUserFormId(pHeader->uiSenderID, userInfo);

		if(!isFind)
		{
			//稍后处理
		}

		IMLocalDb db;
		CHAT_DATA * pData = (CHAT_DATA*)( (char*)pHeader + sizeof(IM_CMD_HEADER) );

		if(pHeader->uiSenderID == pMySelf->Id)
		{
			db.SaveFriendMsgToDB( 
				pMySelf->Id, 
				pMySelf->Name, 
				userInfo.Id, 
				userInfo.Name, 
				(ULONG)time(NULL),
				0, 
				pData->chData, pData->uiDataLen,
				GetCurFriendTableName(),
				pHeader->uiMsgID);
		}
		else
		{
			db.SaveFriendMsgToDB(
				userInfo.Id, 
				userInfo.Name, 
				pMySelf->Id, 
				pMySelf->Name, 
				(ULONG)time(NULL),
				0, 
				pData->chData,pData->uiDataLen, 
				GetCurFriendTableName(), 
				pHeader->uiMsgID);
		}

		if(IMGlobal::Instance()->m_hMainWnd)
			::SendMessage(IMGlobal::Instance()->m_hMainWnd, WM_NORMAL_CHAT, (WPARAM)pHeader, 0);
	}

	void TeamChat(IM_CMD_HEADER * pHeader)
	{
		CHAT_DATA * pData = (CHAT_DATA*)( (char*)pHeader + sizeof(IM_CMD_HEADER) );
		pData->chData[pData->uiDataLen] = '\0';

		GroupInfo groupInfo;
		UserInfo* pMySelf = IMGlobal::Instance()->m_pMyself;
		CMainDlg* pMainWnd = (CMainDlg*)IMGlobal::Instance()->m_pMainWnd;

		IMLocalDb db;
		bool isFind = false;

		isFind = pMainWnd->m_pAdapterLvContact->FindGroupFormId(pHeader->uiRecverID, groupInfo);

		if(!isFind)
		{
			//
		}

		UserInfo userInfo;
		groupInfo.FindMember(pHeader->uiSenderID, userInfo);

		if(IMGlobal::Instance()->m_hMainWnd)
			::SendMessage(IMGlobal::Instance()->m_hMainWnd, WM_TEAM_CHAT, (WPARAM)pHeader, 0);

		db.SaveTeamMsgToDB( pHeader->uiSenderID, userInfo.Name, pHeader->uiRecverID, (ULONG)time(NULL),
			pData->chData,pData->uiDataLen, GetCurTeamTableName(), pHeader->uiMsgID, false);
	}
};