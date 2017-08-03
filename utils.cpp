#include "stdafx.h"
#include "utils.h"
#include <shlobj.h>
#include "AES.h"
#include "IMConst.h"
#include "imre/HTTPDownloader.h"

#include "SAntialiasSkin.h"
#include "imre/ImgProvider.h"

namespace SOUI
{
    //
    // xml helpers
    //

    SStringW XMLEscape(SStringW& strXML)
    {
        strXML.Replace(L"&", L"&amp;");
        strXML.Replace(L"<", L"&lt;");
        strXML.Replace(L">", L"&gt;");
        strXML.Replace(L"'", L"&apos;");
        strXML.Replace(L"\"", L"&quot;");
        return strXML;
    }


    SStringW GenGuid()
    {
        SStringW sGUID;
        GUID guid;

        if (S_OK == ::CoCreateGuid(&guid))
        {
            sGUID.Format(_T("%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x"),
                guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2],
                guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
        }

        return sGUID;
    }

    int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
    {
        UINT  num = 0;          // number of image encoders  
        UINT  size = 0;         // size of the image encoder array in bytes  

        Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

        Gdiplus::GetImageEncodersSize(&num, &size);
        if (size == 0)
            return -1;  // Failure  

        pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
        if (pImageCodecInfo == NULL)
            return -1;  // Failure  

        Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

        for (UINT j = 0; j < num; ++j)
        {
            if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
            {
                *pClsid = pImageCodecInfo[j].Clsid;
                free(pImageCodecInfo);
                return j;  // Success  
            }
        }

        free(pImageCodecInfo);
        return -1;  // Failure  
    }

    int GetCodecInfo(const WCHAR* format, Gdiplus::ImageCodecInfo* p)
    {
        UINT  num = 0;          // number of image encoders  
        UINT  size = 0;         // size of the image encoder array in bytes  

        Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

        Gdiplus::GetImageEncodersSize(&num, &size);
        if (size == 0)
            return -1;  // Failure  

        pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
        if (pImageCodecInfo == NULL)
            return -1;  // Failure  

        GetImageEncoders(num, size, pImageCodecInfo);

        for (UINT n = 0; n < num; ++n)
        {
            if (wcscmp(pImageCodecInfo[n].MimeType, format) == 0)
            {
                *p = pImageCodecInfo[n];
                free(pImageCodecInfo);
                return n;  // Success  
            }
        }

        free(pImageCodecInfo);
        return -1;
    }

    double GetZoomRatio(SIZE normalSize, SIZE maxSize)
    {
        double fXRatio = 1.0f;
        double fYRatio = 1.0f;

        if (normalSize.cx > maxSize.cx)
        {
            fXRatio = (double)maxSize.cx / (double)normalSize.cx;
        }

        if (normalSize.cy > maxSize.cy)
        {
            fYRatio = (double)maxSize.cy / (double)normalSize.cy;
        }

        return fXRatio > fYRatio ? fYRatio : fXRatio;
    }

    SStringW GetTempPath()
    {
        WCHAR szTempPath[MAX_PATH + 1];
        ::GetTempPathW(MAX_PATH + 1, szTempPath);

        SStringW path;
        path.Format(L"%sImClient\\", szTempPath);

        SHCreateDirectoryEx(NULL, path, NULL);

        return path;
    }

	void SetImgWndSkin(SImageWnd* pImgWnd, SStringT strId, SStringT strPath, CSize szImg)
	{
		if(pImgWnd == NULL)
			return;

		if (!ImageProvider::IsExist(strId))
		{
			SAntialiasSkin* pSkin = new SAntialiasSkin();
			pSkin->SetMaxSize(szImg);
			pSkin->SetRoundCorner(5, 5, 5, 5); // 添加圆角处理
			if (pSkin->LoadFromFile(strPath))
			{
				ImageProvider::Insert(strId, pSkin);
				pImgWnd->SetSkin(pSkin);
			}
			else
			{
				delete pSkin;
			}
		}
		else
		{
			ISkinObj* pSkin = ImageProvider::GetImage(strId);
			pImgWnd->SetSkin(pSkin);
		}
	}

	std::wstring SetCurDir(LPCWSTR szFolderName)
	{
		TCHAR szMbsFile[MAX_PATH] = { 0 };
		::GetModuleFileName(NULL, szMbsFile, MAX_PATH);
		TCHAR* pFind = _tcsrchr(szMbsFile, '\\');
		if(pFind)
		{
			*(pFind+1) = 0;
			_tcscat(szMbsFile, szFolderName);
		}

		return szMbsFile;
	}

	void DownLoadHead(SStringT strImgName, SStringT strImgPath)
	{
		SStringT szUrl;
		szUrl.Format(_T("http://%s/EPA_IM/heads/%s"), 
			_T(WEB_SRV_ADDR), strImgName);

		DWORD dwStatus = 0;
		HTTPDownloader downloader;
		if (downloader.OpenURL((LPCWSTR)szUrl) != 0)
			return;

		downloader.QueryStatusCode(dwStatus);
		if (dwStatus != HTTP_STATUS_OK)
			return;

		downloader.DownLoadFile((LPCWSTR)strImgPath);
	}

	SStringA HttpAesParam(int nId)
	{
		char ciphertext[1024] = {0};
		SStringA strPlaintex;  //密文
		SStringA strKey;

		ULONG uTime = (ULONG)time(NULL);

		if(nId == 0)
			strPlaintex = "epaim_servernumber";
		else
			strPlaintex.Format("%u", nId);

		strKey.Format("%u_epaim", uTime); 

		AES aes((unsigned char*)strKey.GetBuffer(0));
		aes.Bm53Cipher((char*)strPlaintex.GetBuffer(0), ciphertext);

		SStringA strVal;
		strVal.Format("aestime=%u&aes=%s", uTime, ciphertext);

		strKey.ReleaseBuffer();
		strPlaintex.ReleaseBuffer();

		return strVal;
	}

	int Unicode2Utf8(const wchar_t* unicode, char* utf8, int nBuffSize)   
	{      
		if (!unicode || !wcslen(unicode))  
		{  
			return 0;  
		}  
		int len;      
		len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);   
		if (len > nBuffSize)  
		{  
			return 0;  
		}    
		WideCharToMultiByte(CP_UTF8, 0, unicode, -1, utf8, len, NULL,NULL);      
		return len;      
	}  

	int Utf82Unicode(const char* utf, wchar_t* unicode, int nBuffSize)    
	{    
		if(!utf || !strlen(utf))    
		{    
			return 0;    
		}    

		int dwUnicodeLen = MultiByteToWideChar(CP_UTF8,0,utf,-1,NULL,0);    
		size_t num = dwUnicodeLen*sizeof(wchar_t);    
		if (num > nBuffSize)  
		{  
			return 0;  
		}  
		MultiByteToWideChar(CP_UTF8, 0, utf, -1, unicode, dwUnicodeLen);     
		return dwUnicodeLen;   
	}  

	SStringT GetCurTeamTableName()
	{
		SStringT tableName;
		time_t now = time(NULL);
		struct tm * t = localtime(&now);
		tableName.Format(_T("TEAM_TALK_%d%02d"), t->tm_year + 1900, t->tm_mon + 1);

		return tableName;
	}

	SStringT GetCurFriendTableName()
	{
		SStringT tableName;
		time_t now = time(NULL);
		struct tm * t = localtime(&now);
		tableName.Format(_T("FRIENDS_TALK_%d%02d"), t->tm_year + 1900, t->tm_mon + 1);

		return tableName;
	}
}
