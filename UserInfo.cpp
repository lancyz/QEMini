// MainDlg.cpp : implementation of the CUserInfoDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserInfo.h"
#include "SAntialiasSkin.h"
#include "imre/ImgProvider.h"
#include "utils.h"

#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")

CUserInfoDlg::CUserInfoDlg() : SHostWnd(_T("LAYOUT:XML_USERINFOWND"))
{
	m_nRetCode = -1;
	m_bLayoutInited = FALSE;
}

CUserInfoDlg::~CUserInfoDlg()
{
}

int CUserInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// 		MARGINS mar = {5,5,30,5};
	// 		DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CUserInfoDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;

	return 0;
}

void CUserInfoDlg::ShowUserInfo(UserInfo& userInfo, CPoint pt)
{
	SImageWnd* pImgWnd = FindChildByName2<SImageWnd>("img_head");
	SetImgWndSkin(pImgWnd, userInfo.AvatarId, userInfo.AvatarPath, CSize(60,60));

	SWindow* pWnd = FindChildByName2<SWindow>("text_name");
	if(pWnd)
		pWnd->SetWindowText(userInfo.Name);

	pWnd = FindChildByName2<SWindow>("text_empNo");
	if(pWnd)
		pWnd->SetWindowText(userInfo.EmpNo);

	pWnd = FindChildByName2<SWindow>("text_dept");
	if(pWnd)
		pWnd->SetWindowText(userInfo.Dept);

	SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
}

void CUserInfoDlg::OnBtnChat()
{

}