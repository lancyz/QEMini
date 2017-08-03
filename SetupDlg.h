#pragma once

class CSetupDlg : public SHostWnd
{
public:
	CSetupDlg();
	~CSetupDlg();

	void OnClose()
	{
		AnimateHostWindow(200, AW_CENTER | AW_HIDE);
		//ShowWindow(SW_HIDE);
		DestroyWindow();
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

	void OnBtnCh();
	void OnBtnEn();

	void OnLanguage(int nID);

protected:

	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_ch", OnBtnCh)
		EVENT_NAME_COMMAND(L"btn_en", OnBtnEn)
		EVENT_MAP_END()

		BEGIN_MSG_MAP_EX(CSetupDlg)
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

