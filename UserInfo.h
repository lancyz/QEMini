#pragma once
#include "AdapterUserListView.h"

class CUserInfoDlg : public SHostWnd
{
public:
	CUserInfoDlg();
	~CUserInfoDlg();

	void ShowUserInfo(UserInfo& userInfo, CPoint pt);

	void OnClose()
	{
		AnimateHostWindow(200, AW_CENTER | AW_HIDE);
		ShowWindow(SW_HIDE);
		//DestroyWindow();
	}
	void OnMaximize()
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	}
	void OnRestore()
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE);
	}
	void OnMinimize()
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
	}

	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	void OnBtnChat();

	int  GetReturnCode() { return m_nRetCode; }

protected:

	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_chat", OnBtnChat)
		//EVENT_NAME_HANDLER(L"turn3d", EventTurn3d::EventID, OnTurn3D);
		EVENT_MAP_END()

		BEGIN_MSG_MAP_EX(CUserInfoDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;
	int             m_nRetCode;
};

