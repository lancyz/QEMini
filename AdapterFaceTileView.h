#pragma once
#include "imre/ImgProvider.h"
#include "SAntialiasSkin.h"
#include "utils.h"
#include <vector>
#include <helper/SAdapterBase.h>

class CAdapterFaceTileView :
    public SAdapterBase
{
public:
    CAdapterFaceTileView(void)
    {
        //TCHAR szMbsFile[MAX_PATH] = { 0 };
        //::GetModuleFileName(NULL, szMbsFile, MAX_PATH);
        //TCHAR* pFind = _tcsrchr(szMbsFile, '\\');
        //if(pFind)
        //{
        //    *(pFind+1) = 0;
        //    _tcscat(szMbsFile, _T("Face"));

            DirectoryList(SetCurDir(L"Face").c_str());
        //}
    };
    ~CAdapterFaceTileView(void){};

    std::vector<SStringT> m_faceList;

#define FACE_PATH "uires\\image\\emotion\\"

    void PushFace(SStringT strPath)
    {
        m_faceList.push_back(strPath);
    }

    SStringT GetFace(int nIndex)
    {
        if(nIndex >= 0 && nIndex < getCount())
            return m_faceList[nIndex];
        else
            return L"";
    }

    virtual int getCount()
    {
        return m_faceList.size();
    }   

    virtual void getView(int position, SWindow * pItem,pugi::xml_node xmlTemplate)
    {
        if(pItem->GetChildrenCount()==0)
        {
            pItem->InitFromXml(xmlTemplate);
        }

		//pItem->GetEventSet()->subscribeEvent(EventSwndStateChanged::EventID,Subscriber(&CAdapterFaceTileView::OnItemStateChanged,this));

		SStringT facePath = m_faceList[position];

		SImageWnd* pImgWnd = pItem->FindChildByName2<SImageWnd>("img_face");
		if(pImgWnd)
		{
			SetFaceImgSkin(SStringT().Format(L"%d", position), facePath, pImgWnd);
		}
    }

	void SetFaceImgSkin(SStringT strId, SStringT strPath, SImageWnd* pImgWnd)
	{
		if (!ImageProvider::IsExist(strId))
		{
			SAntialiasSkin* pSkin = new SAntialiasSkin();
			pSkin->SetMaxSize(CSize(28,28));
			//pSkin->SetRoundCorner(5, 5, 5, 5); // 添加圆角处理
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

	bool OnItemStateChanged(EventArgs *e)
	{
		EventSwndStateChanged *e2 = sobj_cast<EventSwndStateChanged>(e);
		if(!e2->CheckState(WndState_Hover)) return false;
		//通知界面重绘
		notifyDataSetInvalidated();
		return true;
	}

    BOOL  DirectoryList(LPCWSTR Path)
    {
        WIN32_FIND_DATA FindData;
        HANDLE hError;
        int FileCount = 0;
        wchar_t FilePathName[MAX_PATH];
        // 构造路径
        wchar_t FullPathName[MAX_PATH];
        StrCpyW(FilePathName, Path);
        StrCatW(FilePathName, L"\\*.*");
        hError = FindFirstFile(FilePathName, &FindData);
        if(hError == INVALID_HANDLE_VALUE)
        {
            printf("搜索失败!");
            return 0;
        }
        while(::FindNextFile(hError, &FindData))
        {
            // 过虑.和..
            if(StrCmpW(FindData.cFileName,L".") == 0 
                || StrCmpW(FindData.cFileName, L"..") == 0 )
            {
                continue;
            }
                            
            // 构造完整路径
            wsprintf(FullPathName,L"%s\\%s", Path,FindData.cFileName);
            FileCount++;
            // 输出本级的文件
            printf("\n%d  %s  ", FileCount, FullPathName);

			PushFace(FullPathName);
                          
            if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("<Dir>");
                DirectoryList(FullPathName);
            }			  
        }
        return 0;
    }
};

