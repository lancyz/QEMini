#include "StdAfx.h"
#include "SetupDlg.h"
#include "SAntialiasSkin.h"
#include "imre/ImgProvider.h"


CSetupDlg::CSetupDlg() : SHostWnd(_T("LAYOUT:XML_SETUPWND"))
{
	m_nRetCode = -1;
	m_bLayoutInited = FALSE;
}

CSetupDlg::~CSetupDlg()
{
}

int CSetupDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// 		MARGINS mar = {5,5,30,5};
	// 		DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CSetupDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;

	return 0;
}

void CSetupDlg::OnBtnCh()
{
	OnLanguage(1);
}

void CSetupDlg::OnBtnEn()
{
	OnLanguage(0);
}

void CSetupDlg::OnLanguage(int nID)
{
	ITranslatorMgr *pTransMgr = SApplication::getSingletonPtr()->GetTranslator();
	SASSERT(pTransMgr);
	bool bCnLang = nID == 1;

	pugi::xml_document xmlLang;
	if (SApplication::getSingletonPtr()->LoadXmlDocment(xmlLang, bCnLang ? _T("lang_cn") : _T("lang_en"), _T("translator")))
	{
		CAutoRefPtr<ITranslator> lang;
		pTransMgr->CreateTranslator(&lang);
		lang->Load(&xmlLang.child(L"language"), 1);//1=LD_XML
		pTransMgr->SetLanguage(lang->name());
		pTransMgr->InstallTranslator(lang);
		SDispatchMessage(UM_SETLANGUAGE,0,0);
	}
}