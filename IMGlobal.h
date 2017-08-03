#ifndef _IMGLOBAL_H
#define _IMGLOBAL_H

#include "os_singleton.h"
#include "IMConst.h"

class IMGlobal : public onesec::Singleton<IMGlobal>
{
public:
	IMGlobal()
	{
		m_pMyself = new UserInfo;

		m_hMainWnd = NULL;
		m_pMainWnd = NULL;
		m_bIsLoginSuccess = false;
	};

	~IMGlobal()
	{
		delete m_pMyself;
	};

	UserInfo* m_pMyself;  //自己的信息

	SHostWnd* m_pMainWnd; //主窗口指针
	HWND m_hMainWnd; //主窗口句柄
	bool m_bIsLoginSuccess; //登录成功标志
};

#endif