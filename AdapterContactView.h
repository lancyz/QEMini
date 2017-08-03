#pragma once
#include "imre/ImgProvider.h"
#include "SAntialiasSkin.h"
#include "IMConst.h"
#include "utils.h"

#include <vector>
#include <helper/SAdapterBase.h>

using namespace SOUI;

//#define WM_SWITCH_USER WM_USER + 1
//
//#define MY_USERID 101

class AdapterContactView :
	public SAdapterBase
{
public:
	HWND m_hWnd;
	std::vector<BaseInfo*> m_contactList;

	AdapterContactView(void)
	{
		m_nCurSel = -1;
	}
	~AdapterContactView(void)
	{

	}

	void Add(BaseInfo* pInfo)
	{
		m_contactList.push_back(pInfo);
	}

	void DelUser(UINT nId)
	{
		for (int i = 0; i < getCount(); i++)
		{
			if(m_contactList[i]->nType == BaseInfo::USER_INFO && nId == ((UserInfo*)m_contactList[i])->Id)
			{
				delete m_contactList[i];
				m_contactList.erase(m_contactList.begin() + i);

				break;
			}
		}
	}

	bool FindFormId(UINT nId, BaseInfo** pInfo)
	{
		for (int i = 0; i < getCount(); i++)
		{
			if(nId == m_contactList[i]->Id)
			{
				*pInfo = m_contactList[i];
				return true;
			}
		}
		return false;
	}

	bool FindUserFormId(UINT nId, UserInfo& userInfo)
	{
		for (int i = 0; i < getCount(); i++)
		{
			if(m_contactList[i]->nType == BaseInfo::USER_INFO && nId == ((UserInfo*)m_contactList[i])->Id)
			{
				userInfo = *((UserInfo*)m_contactList[i]);
				return true;
			}
		}
		return false;
	}

	bool FindGroupFormId(UINT nId, GroupInfo& userInfo)
	{
		for (int i = 0; i < getCount(); i++)
		{
			if(m_contactList[i]->nType == BaseInfo::GROUP_INFO && nId == ((UserInfo*)m_contactList[i])->Id)
			{
				userInfo = *((GroupInfo*)m_contactList[i]);
				return true;
			}
		}
		return false;
	}

	//一定要先调用这个函数给m_nCurSel赋值才能调用带有 Cur 的函数。。
	void SetSel(int nIndex)
	{
		m_nCurSel = nIndex;
	}

	BaseInfo* GetCurSel()
	{
		SASSERT(m_nCurSel >= 0 && m_nCurSel <= getCount());
		return m_contactList[m_nCurSel];
	}

	UserInfo& GetCurSelUser()
	{
		SASSERT(m_nCurSel >= 0 && m_nCurSel <= getCount());
		return *((UserInfo*)m_contactList[m_nCurSel]);
	}

	GroupInfo& GetCurSelGroup()
	{
		SASSERT(m_nCurSel >= 0 && m_nCurSel <= getCount());
		return *((GroupInfo*)m_contactList[m_nCurSel]);
	}

	int GetCurSelType()
	{
		SASSERT(m_nCurSel >= 0 && m_nCurSel <= getCount());
		return m_contactList[m_nCurSel]->nType;
	}

	virtual int getCount()
	{
		return (int)m_contactList.size();
	}   

	virtual int getViewTypeCount()
	{
		return 3;
	}

	virtual int getItemViewType(int position,DWORD dwState)
	{
		return m_contactList[position]->nType;
	}

	//void SetHeadImgSkin(BaseInfo* pUserInfo, SImageWnd* pImgWnd)
	//{
	//	if (!ImageProvider::IsExist(pUserInfo->AvatarId))
	//	{
	//		SAntialiasSkin* pSkin = new SAntialiasSkin();
	//		pSkin->SetMaxSize(CSize(60,60));
	//		pSkin->SetRoundCorner(5, 5, 5, 5); // 添加圆角处理
	//		if (pSkin->LoadFromFile(pUserInfo->AvatarPath))
	//		{
	//			ImageProvider::Insert(pUserInfo->AvatarId, pSkin);
	//			pImgWnd->SetSkin(pSkin);
	//		}
	//		else
	//		{
	//			delete pSkin;
	//		}
	//	}
	//	else
	//	{
	//		ISkinObj* pSkin = ImageProvider::GetImage(pUserInfo->AvatarId);
	//		pImgWnd->SetSkin(pSkin);
	//	}
	//}

	int getItemHeight(int position)
	{
		if(m_contactList[position]->nType == BaseInfo::SEPARATOR)
			return 30;
		else
			return 50;
	}

	virtual SIZE getViewDesiredSize(int position,SWindow *pItem, LPCRECT prcContainer)
	{
		int nHeight = getItemHeight(position);
		return CSize(0,nHeight);//cx在listview，mclistview中没有使用，不需要计算
	}

	virtual void getView(int position, SWindow * pItem,pugi::xml_node xmlTemplate)
	{
		if(pItem->GetChildrenCount() == 0)
		{
			//pItem->InitFromXml(xmlTemplate);

			if(m_contactList[position]->nType == BaseInfo::SEPARATOR)
				pItem->InitFromXml(xmlTemplate.child(L"itemSepar"));
			else if(m_contactList[position]->nType == BaseInfo::USER_INFO)
				pItem->InitFromXml(xmlTemplate.child(L"itemUser"));
			else if(m_contactList[position]->nType == BaseInfo::GROUP_INFO)
				pItem->InitFromXml(xmlTemplate.child(L"itemGroup"));
		}
		pItem->GetEventSet()->subscribeEvent(EventSwndStateChanged::EventID,Subscriber(&AdapterContactView::OnItemStateChanged,this));

		if(m_contactList[position]->nType == BaseInfo::USER_INFO)
		{
			UserInfo* pUserInfo = (UserInfo*)m_contactList[position];

			SWindow* pWnd = pItem->FindChildByName2<SWindow>("text_user_name");
			if(pWnd)
				pWnd->SetWindowText(pUserInfo->Name);

			SImageWnd* pImgWnd = pItem->FindChildByName2<SImageWnd>("img_head_user");
			if(pImgWnd)
				SetImgWndSkin(pImgWnd, pUserInfo->AvatarId, pUserInfo->AvatarPath, CSize(60,60));
				//SetHeadImgSkin(pUserInfo, pImgWnd);
		}
		else if(m_contactList[position]->nType == BaseInfo::GROUP_INFO)
		{
			GroupInfo* pGroupInfo = (GroupInfo*)m_contactList[position];

			SWindow* pWnd = pItem->FindChildByName2<SWindow>("text_group_name");
			if(pWnd)
				pWnd->SetWindowText(pGroupInfo->Name);

			SImageWnd* pImgWnd = pItem->FindChildByName2<SImageWnd>("img_head_group");
			if(pImgWnd)
				SetImgWndSkin(pImgWnd, pGroupInfo->AvatarId, pGroupInfo->AvatarPath, CSize(60,60));
				//SetHeadImgSkin(pGroupInfo, pImgWnd);
		}
		else if(m_contactList[position]->nType == BaseInfo::SEPARATOR)
		{
			SeparInfo* pSeparInfo = (SeparInfo*)m_contactList[position];

			SWindow* pWnd = pItem->FindChildByName2<SWindow>("text_title");
			if(pWnd)
				pWnd->SetWindowText(pSeparInfo->szName);
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

