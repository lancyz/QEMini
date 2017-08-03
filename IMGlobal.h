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

	UserInfo* m_pMyself;  //�Լ�����Ϣ

	SHostWnd* m_pMainWnd; //������ָ��
	HWND m_hMainWnd; //�����ھ��
	bool m_bIsLoginSuccess; //��¼�ɹ���־
};

#endif