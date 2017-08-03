#pragma once
#include <vector>
#include <helper/SAdapterBase.h>

#include "imre/ImgProvider.h"
#include "SAntialiasSkin.h"
#include "IMConst.h"
#include "utils.h"

class CAdapterMemberView : public SAdapterBase
{
public:
	std::vector<UserInfo> m_memberList;

	CAdapterMemberView()
	{

	}

	~CAdapterMemberView()
	{
		m_memberList.clear();
	}

	virtual int getCount()
	{
		return m_memberList.size();
	}   

	void FillMember(std::vector<UserInfo>& memberList)
	{
		for (int i = 0; i < (int)memberList.size(); i++)
		{
			m_memberList.push_back(memberList[i]);
		}
		//notifyDataSetInvalidated();
		notifyDataSetChanged();
	}

	void Add(UserInfo& memberInfo)
	{
		m_memberList.push_back(memberInfo);
		notifyDataSetChanged();
	}

	void Clear()
	{
		if(getCount())
		{
			m_memberList.clear();
			notifyDataSetChanged();
		}
	}

	//virtual SIZE getViewDesiredSize(int position,SWindow *pItem, LPCRECT prcContainer)
	//{
	//	DWORD dwState = pItem->GetState();
	//	int viewType = getItemViewType(position,dwState);
	//	return CSize(0,m_nItemHeight[viewType]);//cx在listview，mclistview中没有使用，不需要计算
	//}

	virtual void getView(int position, SWindow * pItem,pugi::xml_node xmlTemplate)
	{
		if(pItem->GetChildrenCount()==0)
		{
			pItem->InitFromXml(xmlTemplate);
		}

		pItem->GetEventSet()->subscribeEvent(EventSwndStateChanged::EventID,Subscriber(&CAdapterMemberView::OnItemStateChanged,this));

		UserInfo userInfo = m_memberList[position];

		SImageWnd *pImgWnd = (SImageWnd*)pItem->FindChildByName(L"img_head_member");
		if(pImgWnd)
			SetImgWndSkin(pImgWnd, userInfo.AvatarId, userInfo.AvatarPath, CSize(60,60));
			//SetHeadImgSkin(&userInfo, pImgWnd);

		pItem->FindChildByName(L"text_member_name")->SetWindowText(userInfo.Name);
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

	bool OnItemStateChanged(EventArgs *e)
	{
		EventSwndStateChanged *e2 = sobj_cast<EventSwndStateChanged>(e);
		if(!e2->CheckState(WndState_Hover)) return false;
		//通知界面重绘
		notifyDataSetInvalidated();
		return true;
	}
};