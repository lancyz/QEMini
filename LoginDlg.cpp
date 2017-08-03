// MainDlg.cpp : implementation of the CLoginDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "utils.h"
#include "LoginDlg.h"
#include "Sender.h"

#include "imre/HTTPDownloader.h"

CLoginDlg::CLoginDlg() : SHostWnd(_T("LAYOUT:XML_LOGINWND"))
{
	m_nRetCode = -1;
	m_bLayoutInited = FALSE;
}

CLoginDlg::~CLoginDlg()
{
}

int CLoginDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// 		MARGINS mar = {5,5,30,5};
	// 		DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CLoginDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;

	SImageWnd* pImgWnd = FindChildByName2<SImageWnd>("img_avatar");
	SetImgWndSkin(pImgWnd, _T("123455"), _T("uires\\image\\head\\1.jpg"), CSize(80,80));

	FindChildByName(L"edit_empNo")->SetWindowText(_T("YLLB573"));
	FindChildByName(L"edit_pwd")->SetWindowText(_T("lancy.123"));



	return 0;
}

void CLoginDlg::OnBtnLogin()
{
	m_nRetCode = 0; // ��½ 

	SStringT strEmpNo = FindChildByName(L"edit_empNo")->GetWindowText();
	SStringT strPwd = FindChildByName(L"edit_pwd")->GetWindowText();

	std::string szEmpNo = S_CT2A(strEmpNo.GetBuffer(0));
	std::string szPwd = S_CT2A(strPwd.GetBuffer(0));

	HANDLE hEvent = CreateEvent(NULL,FALSE,FALSE, EVENT_LOGIN);
	if(hEvent)
	{
		//����������͵�¼����
		Sender::LoginReq(szEmpNo, szPwd, false);

		//�ȴ����������ؽ��
		if(WaitForSingleObject(hEvent, 1000 * 15) == WAIT_TIMEOUT)
			SMessageBox(NULL, SStringT(_T("��¼��ʱ")), _T("QE"), MB_OK);

		//�Ƿ��¼�ɹ�
		if(IMGlobal::Instance()->m_bIsLoginSuccess)
			OnClose();
		else
			SMessageBox(NULL, SStringT(_T("��¼ʧ��")), _T("QE"), MB_OK);

		CloseHandle(hEvent);
	}
}