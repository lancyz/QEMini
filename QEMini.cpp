// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "MainDlg.h"
#include "LoginDlg.h"

#include "simagemaskwnd.h"

#include "extend.ctrls/SButtonEx.h"
#include "extend.ctrls/ExtendCtrls.h"
#include "extend.ctrls/imre/SImRichedit.h"
#include "extend.ctrls/SSplitBar.h"
#include "extend.ctrls/SImageView.h"
#include "extend.ctrls/GSSkin.h"
#include "extend.ctrls/STabCtrl2.h"
#include "extend.ctrls/GSTabCtrl.h"

#include "extend.skins/ExtendSkins.h"
#include "extend.skins/SAntialiasSkin.h"
#include "extend.skins/SVscrollbar.h"

#include "IMSocket.h"

//从PE文件加载，注意从文件加载路径位置
#define RES_TYPE 1
// #define RES_TYPE 1  //从PE资源中加载UI资源

#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif
	
//定义唯一的一个R,UIRES对象,ROBJ_IN_CPP是resource.h中定义的宏。
ROBJ_IN_CPP
	
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int /*nCmdShow*/)
{
    HRESULT hRes = OleInitialize(NULL);
    SASSERT(SUCCEEDED(hRes));

    int nRet = 0;
    
    SComMgr *pComMgr = new SComMgr;

    //将程序的运行路径修改到项目所在目录所在的目录
    TCHAR szCurrentDir[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, szCurrentDir, sizeof(szCurrentDir));
    LPTSTR lpInsertPos = _tcsrchr(szCurrentDir, _T('\\'));
    _tcscpy(lpInsertPos + 1, _T("..\\QEMini"));
    SetCurrentDirectory(szCurrentDir);

	// 加载自带的riched20.DLL,其实是msftedit.dll.
	// 如果使用系统的riched20.dll，在计算缩进等方面有问题,原因未查
	SStringW re = szCurrentDir;
	re += L"\\riched20.dll";
	LoadLibrary(re);

    {
        BOOL bLoaded=FALSE;
        CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
        CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
        bLoaded = pComMgr->CreateRender_GDI((IObjRef**)&pRenderFactory);
        SASSERT_FMT(bLoaded,_T("load interface [render] failed!"));
        bLoaded=pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
        SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("imgdecoder"));

        pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
        SApplication *theApp = new SApplication(pRenderFactory, hInstance);
        //从DLL加载系统资源
        HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
        if (hModSysResource)
        {
            CAutoRefPtr<IResProvider> sysResProvider;
            CreateResProvider(RES_PE, (IObjRef**)&sysResProvider);
            sysResProvider->Init((WPARAM)hModSysResource, 0);
            theApp->LoadSystemNamedResource(sysResProvider);
            FreeLibrary(hModSysResource);
        }else
        {
            SASSERT(0);
        }

        CAutoRefPtr<IResProvider>   pResProvider;
#if (RES_TYPE == 0)
        CreateResProvider(RES_FILE, (IObjRef**)&pResProvider);
        if (!pResProvider->Init((LPARAM)_T("uires"), 0))
        {
            SASSERT(0);
            return 1;
        }
#else 
        CreateResProvider(RES_PE, (IObjRef**)&pResProvider);
        pResProvider->Init((WPARAM)hInstance, 0);
#endif

		theApp->InitXmlNamedID(namedXmlID,ARRAYSIZE(namedXmlID),TRUE);

		theApp->RegisterWindowClass<GSTabCtrl>();
		theApp->RegisterWindowClass<SImRichEdit>();
		theApp->RegisterWindowClass<SButtonEx>();
		theApp->RegisterWindowClass<SImageView>();
		theApp->RegisterWindowClass<SWindowEx>();
		theApp->RegisterWindowClass<SSplitBar>();
		theApp->RegisterWindowClass<SImageMaskWnd>();//注册SImageMaskWnd

		//extened skins
		theApp->RegisterWindowClass<STabPage2>();//注册STabPage2
		theApp->RegisterWindowClass<STabCtrl2>();//注册STabCtrl2
		theApp->RegisterSkinClass<GSSkinImgList>();
		theApp->RegisterSkinClass<SColorMask>();
		theApp->RegisterSkinClass<SAntialiasSkin>();
		theApp->RegisterSkinClass<SSkinVScrollbar>();
		theApp->RegisterWindowClass<SListBoxEx>();

        theApp->AddResProvider(pResProvider);
        //加载LUA脚本模块。
        CAutoRefPtr<IScriptModule> pScriptLua;
        bLoaded=pComMgr->CreateScrpit_Lua((IObjRef**)&pScriptLua);
        SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("script_lua"));

        //加载多语言翻译模块。
        CAutoRefPtr<ITranslatorMgr> trans;
        bLoaded=pComMgr->CreateTranslator((IObjRef**)&trans);
        SASSERT_FMT(bLoaded,_T("load interface [%s] failed!"),_T("translator"));
        if(trans)
        {//加载语言翻译包
            theApp->SetTranslator(trans);
            pugi::xml_document xmlLang;
            if(theApp->LoadXmlDocment(xmlLang,_T("lang_en"),_T("translator")))
            {
                CAutoRefPtr<ITranslator> langCN;
                trans->CreateTranslator(&langCN);
                langCN->Load(&xmlLang.child(L"language"),1);//1=LD_XML
                trans->InstallTranslator(langCN);
            }
        }

		IMSocket::Instance()->InitializeSocket();
        
        // BLOCK: Run application
        {
			CLoginDlg dlgLogin;
			dlgLogin.Create(GetActiveWindow());
			dlgLogin.SendMessage(WM_INITDIALOG);
			dlgLogin.CenterWindow(dlgLogin.m_hWnd);
			dlgLogin.ShowWindow(SW_SHOWNORMAL);
			nRet = theApp->Run(dlgLogin.m_hWnd);

			if (dlgLogin.GetReturnCode() == 0)
			{
				CMainDlg dlgMain;
				dlgMain.Create(GetActiveWindow());
				dlgMain.SendMessage(WM_INITDIALOG);
				dlgMain.CenterWindow(dlgMain.m_hWnd);
				dlgMain.ShowWindow(SW_SHOWNORMAL);
				nRet = theApp->Run(dlgMain.m_hWnd);
			}
        }

        delete theApp;
    }
    
    delete pComMgr;
    
    OleUninitialize();
    return nRet;
}
