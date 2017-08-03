#pragma once

#include <GdiPlus.h>
#include <string>
#include "string\tstring.h"

namespace SOUI
{
    SStringW GenGuid();
    SStringW XMLEscape(SStringW& strXml);
    int GetCodecInfo(const WCHAR* format, Gdiplus::ImageCodecInfo* p);
    SStringW GetTempPath();
    double GetZoomRatio(SIZE normalSize, SIZE maxSize);

	std::wstring SetCurDir(LPCWSTR szFolderName);
	void SetImgWndSkin(SImageWnd* pImgWnd, SStringT strId, SStringT strPath, CSize szImg);
	void DownLoadHead(SStringT strImgName, SStringT strImgPath);
	SStringA HttpAesParam(int nId);

	int Unicode2Utf8(const wchar_t* unicode, char* utf8, int nBuffSize);
	int Utf82Unicode(const char* utf, wchar_t* unicode, int nBuffSize);

	SStringT GetCurTeamTableName();
	SStringT GetCurFriendTableName();
}

#define SUBSCRIBE(x,y,z) (x)->GetEventSet()->subscribeEvent(y,Subscriber(&z,this))

#define UNSUBSCRIBE(x,y,z) (x)->GetEventSet()->unsubscribeEvent(y,Subscriber(&z,this))