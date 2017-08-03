#pragma once
#include "imre/ImgProvider.h"
#include "SAntialiasSkin.h"
#include "IMConst.h"
#include "utils.h"

#include <vector>
#include <helper/SAdapterBase.h>

using namespace SOUI;



class AdapterUserListView :
	public SAdapterBase
{
public:
	HWND m_hWnd;
	//链表里的指针使用的是 AdapterContactView 链表里的指针
	//所以这个类不对指针做释放操作
	std::vector<BaseInfo*> m_recentList;

	AdapterUserListView(void)
	{
		m_nCurSel = -1;
	}
	~AdapterUserListView(void)
	{

	}

	void Add(BaseInfo* pInfo)
	{
		m_recentList.push_back(pInfo);
	}

	void InsertToFirst(BaseInfo* pInfo)
	{
		m_recentList.insert(m_recentList.begin(), pInfo);
	}

	void MoveToFirst(UINT nId)
	{
		BaseInfo* pInfo = NULL;
		if(FindFormId(nId, &pInfo))
		{
			Delete(nId);
			InsertToFirst(pInfo);
		}
	}

	void Delete(UINT nId)
	{
		for (int i = 0; i < getCount(); i++)
		{
			if(nId == m_recentList[i]->Id)
			{
				//delete m_recentList[i];
				m_recentList.erase(m_recentList.begin() + i);

				break;
			}
		}
	}

	bool FindFormId(UINT nId, BaseInfo** pInfo)
	{
		for (int i = 0; i < getCount(); i++)
		{
			if(nId == m_recentList[i]->Id)
			{
				*pInfo = m_recentList[i];
				return true;
			}
		}

		return false;
	}

	void SetSel(int nIndex)
	{
		m_nCurSel = nIndex;
	}

	int GetSelNo()
	{
		return m_nCurSel;
	}

	BaseInfo* GetCurSel()
	{
		SASSERT(m_nCurSel >= 0 && m_nCurSel <= getCount());
		return m_recentList[m_nCurSel];
	}

	UserInfo& GetCurSelUser()
	{
		SASSERT(m_nCurSel >= 0 && m_nCurSel <= getCount());
		return *((UserInfo*)m_recentList[m_nCurSel]);
	}

	virtual int getCount()
	{
		return (int)m_recentList.size();
	}   

	virtual int getViewTypeCount()
	{
		return 3;
	}

	virtual int getItemViewType(int position,DWORD dwState)
	{
		if(dwState & WndState_Hover)
			return 1;
		else
			return 0;
	}

	//void SetHeadImgSkin(BaseInfo* pInfo, SImageWnd* pImgWnd)
	//{
	//	if (!ImageProvider::IsExist(pInfo->AvatarId))
	//	{
	//		SAntialiasSkin* pSkin = new SAntialiasSkin();
	//		pSkin->SetMaxSize(CSize(60,60));
	//		pSkin->SetRoundCorner(5, 5, 5, 5); // 添加圆角处理
	//		if (pSkin->LoadFromFile(pInfo->AvatarPath))
	//		{
	//			ImageProvider::Insert(pInfo->AvatarId, pSkin);
	//			pImgWnd->SetSkin(pSkin);
	//		}
	//		else
	//		{
	//			delete pSkin;
	//		}
	//	}
	//	else
	//	{
	//		ISkinObj* pSkin = ImageProvider::GetImage(pInfo->AvatarId);
	//		pImgWnd->SetSkin(pSkin);
	//	}
	//}

	virtual void getView(int position, SWindow * pItem,pugi::xml_node xmlTemplate)
	{
		if(pItem->GetChildrenCount()==0)
		{
			//pItem->InitFromXml(xmlTemplate);

			//if(pItem->GetState() == WndState_Hover)
			//	pItem->InitFromXml(xmlTemplate.child(L"itemEvenHover"));
			//else
				pItem->InitFromXml(xmlTemplate.child(L"itemEvenNormal"));
		}

		BaseInfo* pInfo = m_recentList[position];

		SWindow* pWnd = pItem->FindChildByName2<SWindow>("textName");
		if(pWnd)
		{
			pWnd->SetWindowText(pInfo->Name);
		}

		SImageWnd* pImgWnd = pItem->FindChildByName2<SImageWnd>("imgHead");
		if(pImgWnd)
		{
			SetImgWndSkin(pImgWnd, pInfo->AvatarId, pInfo->AvatarPath, CSize(60,60));
			//SetHeadImgSkin(pInfo, pImgWnd);
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

private:
	int m_nCurSel;
};

