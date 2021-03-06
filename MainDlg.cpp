// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "utils.h"
#include "imre/RichEditObjEvents.h"
#include "extend.events/ExtendEvents.h"
#include "extend.ctrls/FileHelper.h"

#include "Sender.h"
#include "IMLocalDb.h"
#include "SetupDlg.h"
#include "HttpInterface.h"
#include "IMGlobal.h"
#include "IMCmdHeader.h"


#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;

	_pMemberSelWnd = NULL;

	m_pMyInfo = IMGlobal::Instance()->m_pMyself;
	//myInfo = UserInfo(600424, L"莫小白", L"563992016", L"iv501", L"uires\\image\\head\\1.jpg", L"设计部");
}

CMainDlg::~CMainDlg()
{
	shellNotifyIcon.Hide();
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	#ifdef DWMBLUR	//win7毛玻璃开关
	MARGINS mar = {5,5,30,5};
	DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	#endif

	SetMsgHandled(FALSE);
	return 0;
}

DWORD WINAPI HeartBeatThread(PVOID pPara)
{
	while(true)
	{
		Sender::HeartBeatReq();
		Sleep(1000 * 29);
	}

	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	IMGlobal::Instance()->m_pMainWnd = this;
	IMGlobal::Instance()->m_hMainWnd = m_hWnd;

	IMSocket::Instance()->SetImID(IMGlobal::Instance()->m_pMyself->Id);

	CreateThread(NULL, 0, HeartBeatThread, this, NULL, NULL);

	IMLocalDb db;
	db.InitTables();

	//创建托盘图标
	m_bLayoutInited = TRUE;
	shellNotifyIcon.Create(m_hWnd,GETRESPROVIDER->LoadIcon(_T("ICON_LOGO"),16));
	shellNotifyIcon.Show();

	//创建用户信息窗口
	m_userInfoDlg.Create(m_hWnd);
	m_userInfoDlg.SendMessage(WM_INITDIALOG);
	m_userInfoDlg.ShowWindow(SW_HIDE);

	//注册拖拽消息
	::DragAcceptFiles(m_hWnd, TRUE);
	::RegisterDragDrop(m_hWnd, GetDropTarget());

	//初始化richedit
	_pMsgRichEdit = FindChildByName2<SImRichEdit>("re-message");
	_pInputRichEdit = FindChildByName2<SImRichEdit>("re-input");

	if (_pInputRichEdit)
	{
		_pInputRichEdit->SetFocus();
		DWORD dwEvtMask = _pInputRichEdit->SSendMessage(EM_GETEVENTMASK);
		_pInputRichEdit->SSendMessage(EM_SETEVENTMASK, 0, dwEvtMask | ENM_CHANGE);

		SUBSCRIBE(_pInputRichEdit, EVT_CTXMENU, CMainDlg::OnShowInputRichEditMenu);
		SUBSCRIBE(_pInputRichEdit, EVT_RE_NOTIFY, CMainDlg::OnInputEditorChange);
		SUBSCRIBE(_pInputRichEdit, EVT_RE_QUERY_ACCEPT, CMainDlg::OnEditorAcceptData);
		SUBSCRIBE(_pInputRichEdit, EVT_RE_OBJ, CMainDlg::OnInputRichObjEvent);
	}

	if (_pMsgRichEdit)
	{
		SUBSCRIBE(_pMsgRichEdit, EVT_RE_QUERY_ACCEPT, CMainDlg::OnEditorAcceptData);
		SUBSCRIBE(_pMsgRichEdit, EVT_CTXMENU, CMainDlg::OnShowMessageRichEditMenu);
		SUBSCRIBE(_pMsgRichEdit, EVT_RE_OBJ, CMainDlg::OnMsgRichObjEvent);
		SUBSCRIBE(_pMsgRichEdit, EVT_RE_SCROLLBAR, CMainDlg::OnMsgRichScrollEvent);
	}

	m_pMainTab = FindChildByName2<GSTabCtrl>("tab_main");

	//设置自己的头像
	SImageWnd* pImgWnd = FindChildByName2<SImageWnd>("imgMainHead");
	SetImgWndSkin(pImgWnd, m_pMyInfo->AvatarId, m_pMyInfo->AvatarPath, CSize(60,60));

	m_pUserWnd = FindChildByName2<SWindow>("wnd_user_info");
	m_pGroupWnd = FindChildByName2<SWindow>("wnd_group_info");

	//初始化最近联系人列表
	m_pLstViewFixUser = FindChildByName2<SListView>("lv_user");
	if(m_pLstViewFixUser)
	{
		ILvAdapter *pAdapter = new AdapterUserListView();
		m_pLstViewFixUser->SetAdapter(pAdapter);
		pAdapter->Release();

		m_pAdapterLvUser = (AdapterUserListView*)m_pLstViewFixUser->GetAdapter();

		//HttpInterface httpInterface;
		//httpInterface.GetFriendList(&m_pAdapterLvUser->m_userInfoList, IMGlobal::Instance()->m_pMyself->Id);
		//m_pAdapterLvUser->notifyDataSetChanged();
	}

	//初始化联系人列表
	m_pLstViewFixContact = FindChildByName2<SListView>("lv_contact");
	if(m_pLstViewFixContact)
	{
		IMLocalDb db;

		ILvAdapter *pAdapter = new AdapterContactView();
		m_pLstViewFixContact->SetAdapter(pAdapter);
		pAdapter->Release();

		m_pAdapterLvContact = (AdapterContactView*)m_pLstViewFixContact->GetAdapter();

		HttpInterface httpInterface;

		SeparInfo* pInfo = new SeparInfo;
		pInfo->szName = L"我的群组";
		m_pAdapterLvContact->m_contactList.push_back(pInfo);
		//获取群列表
		//httpInterface.GetGroupList(&m_pAdapterLvContact->m_contactList, IMGlobal::Instance()->m_pMyself->Id);

		db.GetTeamListFromDB(&m_pAdapterLvContact->m_contactList);
		for (int i = 0; i < m_pAdapterLvContact->m_contactList.size(); i++)
		{
			if(m_pAdapterLvContact->m_contactList[i]->nType == BaseInfo::GROUP_INFO)
				db.GetTeamInfoFromDB((GroupInfo*)m_pAdapterLvContact->m_contactList[i]);
		}

		SeparInfo* pInfo2 = new SeparInfo;
		pInfo2->szName = L"我的好友";
		m_pAdapterLvContact->m_contactList.push_back(pInfo2);
		//获取好友列表
		//httpInterface.GetFriendList(&m_pAdapterLvContact->m_contactList, IMGlobal::Instance()->m_pMyself->Id);

		db.GetFriendListFromDB(&m_pAdapterLvContact->m_contactList);

		m_pAdapterLvContact->notifyDataSetChanged();
	}

	//初始化群组成员列表
	m_pGroupMemberView = FindChildByName2<STileView>("lv_member_tile");
	if(m_pGroupMemberView)
	{
		ILvAdapter *pAdapter = new CAdapterMemberView();
		m_pGroupMemberView->SetAdapter(pAdapter);
		pAdapter->Release();

		m_pAdapterTvGroupMember = (CAdapterMemberView*)m_pGroupMemberView->GetAdapter();
	}

	//初始化表情列表
	m_pFaceTileView = FindChildByName2<STileView>("lv_face_tile");
	if(m_pFaceTileView)
	{
		ILvAdapter *pAdapter = new CAdapterFaceTileView();
		m_pFaceTileView->SetAdapter(pAdapter);
		pAdapter->Release();

		m_pAdapterTvFace = (CAdapterFaceTileView*)m_pFaceTileView->GetAdapter();
	}

	return 0;
}

BOOL IsKeyDown(DWORD key) {
	return (GetKeyState(key) & 0x8000) != 0;
}

void CMainDlg::OnKeyDown(TCHAR nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN)
	{
		BOOL ctrlDown = IsKeyDown(VK_CONTROL);

		if (_sendType == PRESS_ENTER_TO_SEND && !ctrlDown)
		{
			OnSend();
			return;
		}
		else if (_sendType == PRESS_ENTER_AND_CTRL_TO_SEND && ctrlDown)
		{
			OnSend();
			return;
		}
	}

	SetMsgHandled(FALSE);
}

void CMainDlg::OnLButtonUp(UINT nFlags,CPoint pt)
{
	//是否显示用户信息窗口
	SImageWnd* pImgWnd = FindChildByName2<SImageWnd>("imgMainHead");
	if(pImgWnd->GetWindowRect().PtInRect(pt))
	{
		GetCursorPos(&m_LBtnDownPt);
		m_userInfoDlg.ShowUserInfo( *IMGlobal::Instance()->m_pMyself, m_LBtnDownPt);
	}
	else
	{
		if(m_userInfoDlg.IsVisible())
			m_userInfoDlg.ShowWindow(SW_HIDE);
	}

	//隐藏表情窗口
	SWindow* pWnd = FindChildByName2<SWindow>("wnd_face");
	if(pWnd && !pWnd->GetWindowRect().PtInRect(pt))
	{
		if(pWnd->IsVisible())
			pWnd->SetAttribute(L"show", L"0");
	}

	SetMsgHandled(FALSE);
}

void CMainDlg::OnDropFiles(HDROP hDropInfo)
{
	RichFormatConv conv;
	if (conv.InitFromHDrop(hDropInfo))
	{
		::SetForegroundWindow(m_hWnd);
		DragDropFiles(conv.GetDropFiles());
	}

	DragFinish(hDropInfo);
}

void CMainDlg::DragDropFiles(RichFormatConv::DropFiles& files)
{
	RichFormatConv::DropFiles::iterator it = files.begin();

	for (; it != files.end(); ++it)
	{
		SStringW content;
		content.Format(L"<RichEditContent><metafile file=\"%s\" /></RichEditContent>", *it);
		_pInputRichEdit->InsertContent(content, RECONTENT_CARET);
	}

	::SetFocus(m_hWnd);
	_pInputRichEdit->SetFocus();
	_pInputRichEdit->GetContainer()->OnShowCaret(TRUE);
}

SWindow* CMainDlg::GetDropDownOwner()
{
	return this;
}

void CMainDlg::OnCreateDropDown(SDropDownWnd *pDropDown)
{
}

void CMainDlg::OnDestroyDropDown(SDropDownWnd *pDropDown)
{
	_pMemberSelWnd = NULL;
}

void CMainDlg::ShowMemberSelectionWnd(const CRect& rcCursor, const SStringW& strKeyWord)
{
	//暂不处理

	//if (!_pMemberSelWnd)
	//{
	//	_pMemberSelWnd = new DropDownListWnd(this);
	//	_pMemberSelWnd->Create(CRect(), 0);
	//	_pMemberSelWnd->GetEventSet()->subscribeEvent(
	//		EventItemSelected::EventID,
	//		Subscriber(&CMainDlg::OnMemberSelected, this));

	//	SListBoxEx * plb = _pMemberSelWnd->FindChildByName2<SListBoxEx>(L"selectionlist");

	//	UserInfoVec::iterator it = m_pAdapterLvUser->m_userInfoList.begin();
	//	for (int i = 0; it != m_pAdapterLvUser->m_userInfoList.end(); ++it, ++i)
	//	{
	//		SStringW strItem;

	//		strItem.Format(
	//			L"<item><text pos=\"5,0,-0,-0\" font=\"size:12\" valign=\"middle\" dotted=\"1\">%s(%s)</text></item>",
	//			it->Name,
	//			it->EmpNo);

	//		int npos = plb->InsertItem(-1, strItem);
	//		SWindow * pPanel = plb->GetItemPanel(npos);

	//		pPanel->SetAttribute(L"colorNormal", i % 2 == 0 ? L"#f0f7fc" : L"#e4eff8");
	//		pPanel->SetAttribute(L"colorSelected", L"#f2ebcd");
	//		pPanel->SetAttribute(L"colorHover", L"#f2ebcd");
	//	}
	//	plb->SetCurSel(0);

	//	_pMemberSelWnd->AdjustWindowSize();
	//}

	//_pMemberSelWnd->SetWindowPos(HWND_TOP,
	//	rcCursor.left, rcCursor.bottom, // left,top
	//	0, 0,                           // width,height
	//	SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
}

bool CMainDlg::OnMemberSelected(SOUI::EventArgs *pEvt)
{
	EventItemSelected * pev = (EventItemSelected*)pEvt;

	//暂不处理

	//SStringW strKeyWord;
	//CHARRANGE cr = { 0, 0 };
	//_pInputRichEdit->SSendMessage(EM_EXGETSEL, NULL, (LPARAM)&cr);

	//strKeyWord = _pInputRichEdit->GetWindowText();
	//strKeyWord = strKeyWord.Left(cr.cpMin);
	//int nIndex = strKeyWord.ReverseFind(TCHAR('@'));
	//if (nIndex >= 0)
	//{
	//	_pInputRichEdit->SetSel(nIndex, cr.cpMin);
	//}

	//SStringW name = L"@";
	//name += m_pAdapterLvUser->m_userInfoList[pev->nCurrSelect].Name;

	//SStringW str = RichEditReminderOle::MakeFormattedText(name, 13, RGB(0x00, 0x6e, 0xfe));

	//SStringW content;
	//content.Format(L"<RichEditContent>%s</RichEditContent>", str);

	//_pInputRichEdit->InsertContent(content, RECONTENT_CARET);

	return false;
}

void CMainDlg::OnTimer(UINT_PTR idEvent)
{
	if (idEvent == TIMERID_LOAD_MSG)
	{
		::KillTimer(m_hWnd, idEvent);

		// 增加一条消息
		_msgAdded += 1;

		if (_msgAdded % 2 == 0)
		{
			//AddLeftMessage(GetRandomUser(), L"<text>这也是一条动态添加的文本</text>", 1);
		}
		else
		{
			//AddRightMessage(GetRandomUser(), L"<text>这是一条动态添加的文本</text>", 1);
		}

		RichEditContent* pFirstContent = _pMsgRichEdit->GetContent((UINT)0);
		RichEditFetchMoreOle* pFetchMore =
			sobj_cast<RichEditFetchMoreOle>(pFirstContent->GetByName(OLENAME_FETCHMORE));

		if (pFetchMore)
		{
			if (_msgAdded >= 2)
				pFetchMore->ShowOpenLinkState();
			else
				pFetchMore->ResetState();
		}
	}

	SetMsgHandled(FALSE);
}

bool CMainDlg::OnInputRichObjEvent(SOUI::EventArgs *pEvt)
{
	EventRichEditObj * pev = (EventRichEditObj*)pEvt;

	if (pev->SubEventId == DBLCLICK_RICH_METAFILE)
	{
		RichEditMetaFileOle * pmf = sobj_cast<RichEditMetaFileOle>(pev->RichObj);
		ShellExecute(NULL, _T("open"), pmf->GetFilePath(), NULL, NULL, SW_SHOW);
	}
	else if (pev->SubEventId == DBLCLICK_IMAGEOLE)
	{
		RichEditImageOle * pImageOle = sobj_cast<RichEditImageOle>(pev->RichObj);

		if (pImageOle->GetImageType() == IMGTYPE_NORMAL)
		{
			ShellExecute(NULL, _T("open"), pImageOle->GetImagePath(), NULL, NULL, SW_SHOW);
		}
	}

	return true;
}

bool CMainDlg::OnMsgRichObjEvent(SOUI::EventArgs *pEvt)
{
	EventRichEditObj * pev = (EventRichEditObj*)pEvt;

	switch (pev->SubEventId)
	{
	case DBLCLICK_IMAGEOLE:
		{
			RichEditImageOle * pImageOle = sobj_cast<RichEditImageOle>(pev->RichObj);
			ShellExecute(NULL, _T("open"), pImageOle->GetImagePath(), NULL, NULL, SW_SHOW);
		}
		break;

	case CLICK_FILEOLE:
		{
			RichEditFileOle* pFileOle = sobj_cast<RichEditFileOle>(pev->RichObj);
			SStringW text;
			text.Format(_T("点击了文件按钮:%04x，文件路径:%s"), pev->wParam, pFileOle->GetFileName());
			::MessageBox(m_hWnd, text, _T("提示"), MB_OK);
		}
		break;

	case CLICK_FETCHMOREOLE_MORE_MSG:
		::SetTimer(m_hWnd, TIMERID_LOAD_MSG, 1000, NULL);
		break;

	case CLICK_FETCHMOREOLE_OPEN_LINK:
		::MessageBox(m_hWnd, _T("点击了打开历史记录"), _T("提示"), MB_OK);
		break;

	case CLICK_LINK:
		{
			RichEditText * pText = sobj_cast<RichEditText>(pev->RichObj);
			SStringW text;
			text.Format(_T("点击了模仿的链接：%s"), pText->GetText());
			::MessageBox(m_hWnd, text, _T("提示"), MB_OK);
		}
		break;

	case CLICK_BK_ELE:
		{
			RichEditBkElement* pBkEle = sobj_cast<RichEditBkElement>(pev->RichObj);
			if (pBkEle->GetData() == L"avatar")
			{
				SStringT strId = pBkEle->GetUserData();
				//UINT nId = atoi(S_CW2A(strId).GetBuffer(0));
				UINT nId = m_pAdapterLvUser->GetCurSel()->Id;
				strId.ReleaseBuffer();

				BaseInfo* pInfo = NULL;

				if(m_pAdapterLvUser->FindFormId(nId, &pInfo))
				{
					GetCursorPos(&m_LBtnDownPt);
					if(pInfo->nType == BaseInfo::USER_INFO)
					{
						m_userInfoDlg.ShowUserInfo(*((UserInfo*)pInfo), m_LBtnDownPt);
					}
					else if(pInfo->nType == BaseInfo::GROUP_INFO)
					{
						UINT nUserID = atoi(S_CW2A(strId).GetBuffer(0));

						UserInfo userInfo;
						if( ((GroupInfo*)pInfo)->FindMember(nUserID, userInfo) )
						{
							m_userInfoDlg.ShowUserInfo(userInfo, m_LBtnDownPt);
						}
					}
				}

				//::MessageBox(m_hWnd, _T("点击了头像"), _T("提示"), MB_OK);
			}
			else if (pBkEle->GetData() == L"resend")
			{
				::MessageBox(m_hWnd, _T("点击了重新发送"), _T("提示"), MB_OK);
			}
		}
		break;
	}

	return true;
}

bool CMainDlg::OnMsgRichScrollEvent(SOUI::EventArgs *pEvt)
{
	EventRichEditScroll* pev = (EventRichEditScroll*)pEvt;

	time_t now = GetTickCount();

	if (pev->ScrollAtTop && (now - _lastWhellTime) < 200)
	{
		_totalWhellDelta += pev->WheelDelta;
	}
	else
	{
		_totalWhellDelta = 0;
	}
	_lastWhellTime = now;

	if (_totalWhellDelta > 3)
	{
		RichEditContent * pContent = _pMsgRichEdit->GetContent(UINT(0));
		RichEditFetchMoreOle * pOle = NULL;
		pOle = sobj_cast<RichEditFetchMoreOle>(pContent->GetByName(OLENAME_FETCHMORE));

		if (!pOle || pOle->GetCurrentState() != RichEditFetchMoreOle::REFM_STATE_NORMAL)
		{
			return true;
		}

		pOle->ShowLoadingState();
		::SetTimer(m_hWnd, TIMERID_LOAD_MSG, 1000, NULL);
	}

	return true;
}

bool CMainDlg::OnEditorAcceptData(SOUI::EventArgs *pEvt)
{
	EventQueryAccept * pev = (EventQueryAccept*)pEvt;

	if (pev->Conv->GetAvtiveFormat() == CF_HDROP)
	{
		::SetForegroundWindow(m_hWnd);
		RichFormatConv::DropFiles files = pev->Conv->GetDropFiles();
		DragDropFiles(files);
		return true;
	}

	return false;
}

void CMainDlg::OnFace()
{
	SWindow* pWnd = FindChildByName2<SWindow>("wnd_face");
	if(pWnd)
	{
		if(!pWnd->IsVisible())
		{
			pWnd->BringWindowToTop();
			pWnd->SetAttribute(L"show", L"1");
		}
	}
}

void CMainDlg::OnSendPicture()
{
	SStringW strFile;
	CFileDialogEx dlg(TRUE, NULL, 0, 0,
		_T("图片文件\0*.gif;*.bmp;*.jpg;*.png\0\0"));

	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	strFile = dlg.m_szFileName;
	InsertPicture(strFile);
}

void CMainDlg::InsertPicture(SStringT strFile)
{
	strFile = XMLEscape(strFile);

	SStringW str;
	str.Format(L"<RichEditContent>"
		L"<para break=\"0\" disable-layout=\"1\">"
		L"<img type=\"normal_img\" path=\"%s\" id=\"zzz\" size=\"100,50\" max-size=\"\" minsize=\"\" scaring=\"1\" cursor=\"hand\" />"
		L"</para>"
		L"</RichEditContent>", strFile);

	if (_pInputRichEdit)
	{
		_pInputRichEdit->InsertContent(str, RECONTENT_CARET);
	}
}

bool CMainDlg::OnInputEditorChange(SOUI::EventArgs *pEvt)
{
	EventRENotify *pReNotify = (EventRENotify*)pEvt;
	if (pReNotify->iNotify == EN_CHANGE)
	{
		CRect rcCursor;
		CHARRANGE cr = { 0, 0 };
		_pInputRichEdit->SSendMessage(EM_EXGETSEL, NULL, (LPARAM)&cr);

		if (cr.cpMin == cr.cpMax)
		{
			SStringW strKeyWord = _pInputRichEdit->GetWindowText();
			strKeyWord = strKeyWord.Left(cr.cpMin);

			int nIndex = strKeyWord.ReverseFind(TCHAR('@'));
			if (nIndex >= 0)
			{
				_pInputRichEdit->GetCaretRect(rcCursor);
				ShowMemberSelectionWnd(rcCursor, strKeyWord);
			}
		}
	}

	return false;
}

void CMainDlg::OnTvFaceSelchanging(EventArgs *pEvt)
{
	EventLVSelChanging *pEvt2 = sobj_cast<EventLVSelChanging>(pEvt);
	if(!pEvt2)
		return;

	int nNewSel = pEvt2->iNewSel;

	if(nNewSel < 0 || nNewSel >= m_pAdapterTvFace->getCount())
		return;

	SStringT strFile = m_pAdapterTvFace->GetFace(nNewSel);
	InsertPicture(strFile);

	SWindow* pWnd = FindChildByName2<SWindow>("wnd_face");
	if(pWnd)
	{
		pWnd->SetAttribute(L"show", L"0");
	}
}

void CMainDlg::OnLvContactSelchanging(EventArgs *pEvt)
{
	EventLVSelChanging *pEvt2 = sobj_cast<EventLVSelChanging>(pEvt);
	if(!pEvt2)
		return;

	int nNewSel = pEvt2->iNewSel;
	int nOldSel = pEvt2->iOldSel;

	if(nNewSel < 0 || nNewSel >= m_pAdapterLvContact->getCount())
		return;

	m_pAdapterLvContact->SetSel(nNewSel);
	int nSelType = m_pAdapterLvContact->GetCurSelType();

	m_pUserWnd->SetVisible(FALSE, TRUE);
	m_pGroupWnd->SetVisible(FALSE, TRUE);

	if(nSelType == BaseInfo::USER_INFO)
	{
		UserInfo userInfo = m_pAdapterLvContact->GetCurSelUser();

		SImageWnd* pImgWnd = FindChildByName2<SImageWnd>("img_head");
		SetImgWndSkin(pImgWnd, userInfo.AvatarId, userInfo.AvatarPath, CSize(60,60));

		SWindow* pWnd = FindChildByName2<SWindow>("text_name");
		if(pWnd)
			pWnd->SetWindowText(userInfo.Name);

		pWnd = FindChildByName2<SWindow>("text_empNo");
		if(pWnd)
			pWnd->SetWindowText(userInfo.EmpNo);

		pWnd = FindChildByName2<SWindow>("text_dept");
		if(pWnd)
			pWnd->SetWindowText(userInfo.Dept);

		pWnd = FindChildByName2<SWindow>("text_note");
		if(pWnd)
			pWnd->SetWindowText(userInfo.Note);

		m_pUserWnd->BringWindowToTop();
		m_pUserWnd->SetVisible(TRUE, TRUE);
	}
	else if(nSelType == BaseInfo::GROUP_INFO)
	{
		GroupInfo groupInfo = m_pAdapterLvContact->GetCurSelGroup();

		m_pAdapterTvGroupMember->Clear();
		m_pAdapterTvGroupMember->FillMember(groupInfo.MemberList);

		SWindow* pWnd = FindChildByName2<SWindow>("text_group_title");
		if(pWnd)
			pWnd->SetWindowText(SStringT().Format(_T("%s (%d)"), groupInfo.Name, groupInfo.Members));

		m_pGroupWnd->BringWindowToTop();
		m_pGroupWnd->SetVisible(TRUE, TRUE);
	}

	//SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
}

void CMainDlg::OnLvUserSelchanging(EventArgs *pEvt)
{
	EventLVSelChanging *pEvt2 = sobj_cast<EventLVSelChanging>(pEvt);
	if(!pEvt2)
		return;

	int nNewSel = pEvt2->iNewSel;
	int nOldSel = pEvt2->iOldSel;

	if(nNewSel < 0 || nNewSel >= m_pAdapterLvUser->getCount())
		return;

	ShowChat(nNewSel);
}

void CMainDlg::ShowChat(int nNewSel)
{
	SWindow* pWnd = FindChildByName2<SWindow>("wnd_chat");
	if(pWnd)
		if(!pWnd->IsVisible())
			pWnd->SetVisible(TRUE, TRUE);

	m_pAdapterLvUser->SetSel(nNewSel);
	BaseInfo* pInfo = m_pAdapterLvUser->GetCurSel();

	pWnd = FindChildByName2<SWindow>("textUserName");
	if(pWnd)
		pWnd->SetWindowText(pInfo->Name);

	_pMsgRichEdit->Clear();
	for (int i = 0; i < pInfo->m_historyChat.getCount(); i ++)
	{
		_pMsgRichEdit->InsertContent(pInfo->m_historyChat.GetMsg(i).strText);
		//if(pInfo->m_historyChat.GetMsg(i).nSendId == atoi(S_CW2A(m_pMyInfo->Id)))
		//{
		//	_pMsgRichEdit->InsertContent(pInfo->m_historyChat.GetMsg(i).strText);
		//	//AddRightMessage(*m_pMyInfo, pInfo->m_historyChat.GetMsg(i).strText);
		//}
		//else
		//{
		//	if(pInfo->nType == BaseInfo::USER_INFO)
		//	{
		//		_pMsgRichEdit->InsertContent(pInfo->m_historyChat.GetMsg(i).strText);
		//		//AddLeftMessage(*((UserInfo*)pInfo), pInfo->m_historyChat.GetMsg(i).strText);
		//	}
		//	else if(pInfo->nType == BaseInfo::GROUP_INFO)
		//	{
		//		UserInfo userInfo;
		//		if( ((GroupInfo*)pInfo)->FindMember(pInfo->Id, userInfo) )
		//		{
		//			_pMsgRichEdit->InsertContent(pInfo->m_historyChat.GetMsg(i).strText);
		//			//AddLeftMessage(userInfo, pInfo->m_historyChat.GetMsg(i).strText);
		//		}
		//	}
		//}
	}
	_pMsgRichEdit->ScrollToBottom();
}

void CMainDlg::OnChat()
{
	BaseInfo* pTempInfo = NULL;
	BaseInfo* pInfo = m_pAdapterLvContact->GetCurSel();

	//如果最近联系人列表中没有此人，就从联系人列表中查找，然后添加到最近联系人中
	if(!m_pAdapterLvUser->FindFormId(pInfo->Id, &pTempInfo))
	{
		m_pAdapterLvUser->InsertToFirst(pInfo);
		////移动到首位
		//m_pAdapterLvUser->MoveToFirst(pInfo->Id);
		//切换到最近联系人列
		m_pMainTab->SetCurSel(0);

		m_pLstViewFixUser->SetSel(0);
		ShowChat(0);

		m_pAdapterLvUser->notifyDataSetChanged();
	}
	else
	{
		//移动到首位
		m_pAdapterLvUser->MoveToFirst(pInfo->Id);
		//切换到最近联系人列
		m_pMainTab->SetCurSel(0);

		m_pLstViewFixUser->SetSel(0);
		ShowChat(0);

		m_pAdapterLvUser->notifyDataSetChanged();
	}
}

void CMainDlg::OnGroupChat()
{
	BaseInfo* pTempInfo = NULL;
	BaseInfo* pInfo = m_pAdapterLvContact->GetCurSel();

	//如果最近联系人列表中没有此人，就从联系人列表中查找，然后添加到最近联系人中
	if(!m_pAdapterLvUser->FindFormId(pInfo->Id, &pTempInfo))
	{
		m_pAdapterLvUser->InsertToFirst(pInfo);
		////移动到首位
		//m_pAdapterLvUser->MoveToFirst(pInfo->Id);
		//切换到最近联系人列
		m_pMainTab->SetCurSel(0);

		m_pLstViewFixUser->SetSel(0);
		ShowChat(0);

		m_pAdapterLvUser->notifyDataSetChanged();
	}
	else
	{
		//移动到首位
		m_pAdapterLvUser->MoveToFirst(pInfo->Id);
		//切换到最近联系人列
		m_pMainTab->SetCurSel(0);

		m_pLstViewFixUser->SetSel(0);
		ShowChat(0);

		m_pAdapterLvUser->notifyDataSetChanged();
	}
}

void CMainDlg::SendMsg(SStringT strMsg)
{
	BaseInfo* pInfo = m_pAdapterLvUser->GetCurSel();

	if(pInfo->nType == BaseInfo::USER_INFO)
		Sender::SendNormalChat(pInfo, strMsg);
	else if(pInfo->nType == BaseInfo::GROUP_INFO)
		Sender::SendTeamChat(pInfo->Id, strMsg);
}

void CMainDlg::OnSend()
{
	CHARRANGE chr = { 0, -1 };
	SStringW content = _pInputRichEdit->GetSelectedContent(&chr);
	pugi::xml_document  doc;

	if (!doc.load_buffer(content, content.GetLength() * sizeof(WCHAR)))
	{
		return;
	}

	//写入历史消息列表
	//SStringW bkContent = content;

	content.Empty();

	SStringT strText;

	pugi::xml_node node = doc.child(L"RichEditContent").first_child();
	for (; node; node = node.next_sibling())
	{
		const wchar_t* pNodeName = node.name();

		if (wcscmp(RichEditText::GetClassName(), pNodeName) == 0)
		{
			strText = node.text().get();
			content += RichEditText::MakeFormatedText(node.text().get(), node.attribute(L"file-size").as_int(10));
		}
		else if (wcscmp(RichEditReminderOle::GetClassName(), pNodeName) == 0)
		{
			content += RichEditReminderOle::MakeFormattedText(node.text().get(), 13, RGB(00, 0x6e, 0xfe));
		}
		else if (wcscmp(RichEditImageOle::GetClassName(), pNodeName) == 0)
		{
			content += RichEditImageOle::MakeFormattedText(
				L"",
				L"",
				IMGTYPE_NORMAL,
				L"",
				node.attribute(L"path").as_string(),
				L"",
				TRUE);
		}
		else if (wcscmp(RichEditMetaFileOle::GetClassName(), pNodeName) == 0)
		{
			content += RichEditFileOle::MakeFormattedText(node.attribute(L"file").as_string(),
				L"等待发送", 440227874, 0x04);
		}
	}

	//if (_pMsgRichEdit->GetContentCount() % 2 == 0)
	//{
	//	AddLeftMessage(m_pAdapterLvUser->GetCurSelUser(), content);
	//}
	//else
	//{
		AddRightMessage(m_pMyInfo, content);
	//}

	_pInputRichEdit->Clear();
	_pMsgRichEdit->ScrollToBottom();

	SendMsg(strText);
}

//UserInfo& CMainDlg::GetRandomUser()
//{
//	return m_pAdapterLvUser->m_recentList[rand() % m_pAdapterLvUser->m_recentList.size()];
//}

void CMainDlg::OnLanguageBtnCN()
{
	OnLanguage(1);
}
void CMainDlg::OnLanguageBtnJP()
{
	OnLanguage(0);
}
void CMainDlg::OnLanguage(int nID)
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

//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}

	if (nType == SIZE_MINIMIZED)
		return;
}

#include <helper/smenu.h>
LRESULT CMainDlg::OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/)
{
	switch (lParam)
	{
	case  WM_RBUTTONDOWN:
	{
            //显示右键菜单
            SMenu menu;
            menu.LoadMenu(_T("menu_tray"),_T("smenu"));
            POINT pt;
            GetCursorPos(&pt);
            menu.TrackPopupMenu(0,pt.x,pt.y,m_hWnd);
	}break;
	case WM_LBUTTONDOWN:
	{
		//显示/隐藏主界面
		if (IsIconic())
		   ShowWindow(SW_SHOWNORMAL);
		else
		   ShowWindow(SW_MINIMIZE);
	}break;
	default:
		break;
	}
	return S_OK;
}

//演示如何响应菜单事件
void CMainDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if (uNotifyCode == 0)
	{
		switch (nID)
		{
		case 6:
			PostMessage(WM_CLOSE);
			break;
		default:
			break;
		}
	}
}


void CMainDlg::AddFetchMoreBlock()
{
    //
    // 获取更多消息OLE
    // 

    SStringW content;
    content.Format(
        L"<RichEditContent type=\"ContentFetchMore\" align=\"center\">"
        L"<para name=\"para\" margin=\"0,5,0,0\" break=\"1\">"
        L"<fetchmore name=\"%s\" selectable=\"0\" />"
        L"</para>"
        L"</RichEditContent>",
        OLENAME_FETCHMORE);

    _pMsgRichEdit->InsertContent(content);
}

void CMainDlg::AddSeparatorBar()
{
    SStringW content;
    content.Format(
        L"<RichEditContent  type=\"ContentSeperator\" align=\"center\">"
        L"<para margin=\"0,10,0,0\" break=\"1\">"
        L"<split selectable=\"0\" />"
        L"</para>"
        L"</RichEditContent>");

    _pMsgRichEdit->InsertContent(content);
}

UINT  CMainDlg::AddCenterMessage(UserInfo& info, const SStringW& body, UINT insertTo/*=RECONTENT_LAST*/)
{
    SStringW content;
    content.Format(
        L"<RichEditContent type=\"ContentCenter\" >"
        L"<para break=\"1\" align=\"left\" />"
        L"<para margin=\"100,0,100,0\" align=\"center\" break=\"1\" >"
        L"%s"
        L"</para>"
        L"<bkele skin=\"skin.rich_sysmsg_bk\" hittestable=\"0\" pos=\"{-10,{0,[10,[0\" />"
        L"</RichEditContent>", body);

    return _pMsgRichEdit->InsertContent(content, insertTo);
}

UINT  CMainDlg::AddCenterMessageWhitoutBuggle(UserInfo& info, const SStringW& body, UINT insertTo/*=RECONTENT_LAST*/)
{
    SStringW content;
    content.Format(
        L"<RichEditContent type=\"ContentCenter\" >"
        L"<para margin=\"100,5,100,5\" align=\"center\" break=\"1\" >"
        L"%s"
        L"</para>"
        L"</RichEditContent>", body);

    return _pMsgRichEdit->InsertContent(content, insertTo);
}

LRESULT CMainDlg::OnTeamChat(UINT uMsg,WPARAM wp,LPARAM lp,BOOL & bHandled)
{
	IM_CMD_HEADER * pHeader = (IM_CMD_HEADER *)wp;
	CHAT_DATA * pData = (CHAT_DATA*)( (char*)pHeader + sizeof(IM_CMD_HEADER) );

	SStringW strBody;
	strBody.Format(_T("<text font-size=\"10\"><![CDATA[%s]]></text>"), S_CA2W(pData->chData));

	//如果最近联系人列表中没有此人，就从联系人列表中查找，然后添加到最近联系人中
	BaseInfo* pInfo = NULL;
	if(!m_pAdapterLvUser->FindFormId(pHeader->uiRecverID, &pInfo))
	{
		if(m_pAdapterLvContact->FindFormId(pHeader->uiRecverID, &pInfo))
		{
			m_pAdapterLvUser->InsertToFirst(pInfo);
			m_pAdapterLvUser->notifyDataSetChanged();
			//m_pMainTab->SetCurSel(0);		
			
			AddTeamLeftMessage(pInfo, pHeader->uiSenderID, strBody );
		}
	}
	else
	{
		AddTeamLeftMessage(pInfo, pHeader->uiSenderID, strBody );
	}

	return 0;
}

LRESULT CMainDlg::OnNormalChat(UINT uMsg,WPARAM wp,LPARAM lp,BOOL & bHandled)
{
	IM_CMD_HEADER * pHeader = (IM_CMD_HEADER *)wp;
	CHAT_DATA * pData = (CHAT_DATA*)( (char*)pHeader + sizeof(IM_CMD_HEADER) );

	SStringW strBody;
	strBody.Format(_T("<text font-size=\"10\"><![CDATA[%s]]></text>"), S_CA2W(pData->chData));

	//如果最近联系人列表中没有此人，就从联系人列表中查找，然后添加到最近联系人中
	BaseInfo* pInfo = NULL;
	if(!m_pAdapterLvUser->FindFormId(pHeader->uiSenderID, &pInfo))
	{
		if(m_pAdapterLvContact->FindFormId(pHeader->uiSenderID, &pInfo))
		{
			m_pAdapterLvUser->InsertToFirst(pInfo);
			m_pAdapterLvUser->notifyDataSetChanged();
			//m_pMainTab->SetCurSel(0);
			AddLeftMessage(pInfo, strBody );
		}
	}
	else
	{
		AddLeftMessage(pInfo, strBody );
	}

	return 0;
}

UINT  CMainDlg::AddTeamLeftMessage(BaseInfo* pInfo, UINT uSendID, const SStringW& body, UINT insertTo/*=RECONTENT_LAST*/)
{
	static int i = 0;

	UserInfo userInfo;
	if(!((GroupInfo*)pInfo)->FindMember(uSendID, userInfo))
	{
		return 0;
	}

		/* 靠左显示的消息 */
		SStringW content;
	content.Format(
		L"<RichEditContent  type=\"ContentLeft\" align=\"left\">"
		L"<para margin=\"36,10,100,4\">"
		L"<text font-size=\"10\" color=\"#808080\">%s</text>"
		L"</para>"
		L"<bkele data=\"avatar\" userData = \"%d\" skin=\"%s\" pos=\"0,]-18,@30,@30\" cursor=\"hand\" interactive=\"1\"/>"
		L"<para id=\"msgbody\" margin=\"45,0,30,0\" break=\"1\" simulate-align=\"1\">"
		L"%s"
		L"</para>"
		L"<bkele data=\"bubble\" left-skin=\"skin.rich_left_bubble\"  left-pos=\"35,{-9,[10,[10\" />"
		L"</RichEditContent>",
		userInfo.Name,
		userInfo.Id,
		userInfo.AvatarId,
		body);

	//写入历史消息列表
	BaseInfo* pUser;
	MsgInfo msgInfo(content,pInfo->Id, 1);
	m_pAdapterLvContact->FindFormId(pInfo->Id, &pUser);
	pUser->m_historyChat.PushMsg(msgInfo);

	if(m_pAdapterLvUser->GetSelNo() < 0 || m_pAdapterLvUser->GetCurSelUser().Id != pInfo->Id)
		return 0;

	return _pMsgRichEdit->InsertContent(content, insertTo);
}

UINT  CMainDlg::AddLeftMessage(BaseInfo* pInfo, const SStringW& body, UINT insertTo/*=RECONTENT_LAST*/)
{
    static int i = 0;

    /* 靠左显示的消息 */
    SStringW content;
    content.Format(
        L"<RichEditContent  type=\"ContentLeft\" align=\"left\">"
        L"<para margin=\"36,10,100,4\">"
        L"<text font-size=\"10\" color=\"#808080\">%s</text>"
        L"</para>"
        L"<bkele data=\"avatar\" userData = \"%d\" skin=\"%s\" pos=\"0,]-18,@30,@30\" cursor=\"hand\" interactive=\"1\"/>"
        L"<para id=\"msgbody\" margin=\"45,0,30,0\" break=\"1\" simulate-align=\"1\">"
        L"%s"
        L"</para>"
        L"<bkele data=\"bubble\" left-skin=\"skin.rich_left_bubble\"  left-pos=\"35,{-9,[10,[10\" />"
        L"</RichEditContent>",
        pInfo->Name,
		pInfo->Id,
        pInfo->AvatarId,
        body);

	//写入历史消息列表
	BaseInfo* pUser;
	MsgInfo msgInfo(content,pInfo->Id, 1);
	m_pAdapterLvContact->FindFormId(pInfo->Id, &pUser);
	pUser->m_historyChat.PushMsg(msgInfo);
	//m_pAdapterLvUser->GetCurSelUser().m_historyChat.PushMsg(msgInfo);

	if(m_pAdapterLvUser->GetSelNo() < 0 || m_pAdapterLvUser->GetCurSelUser().Id != pInfo->Id)
		return 0;

    return _pMsgRichEdit->InsertContent(content, insertTo);
}

UINT  CMainDlg::AddRightMessage(BaseInfo* pInfo, const SStringW& body, UINT insertTo/*=RECONTENT_LAST*/)
{
    LPCWSTR pResendBtn = L"<bkele name=\"BkEleSendFail\" data=\"resend\" right-skin=\"skin.rich_warning\" left-skin=\"skin.rich_warning\" left-pos=\"[0,[-25,@16,@16\" right-pos=\"{-20,[-25,@16,@16\" cursor=\"hand\" interactive=\"1\"/>";
    /* 靠右显示的消息 */
    SStringW content;
    content.Format(
        L"<RichEditContent  type=\"ContentRight\" align=\"right\" auto-layout=\"1\">"
        L"<para break=\"1\" align=\"left\" />"
        L"<bkele data=\"avatar\" userData = \"%d\"  skin=\"%s\" left-pos=\"0,]-4,@30,@30\" right-pos=\"-30,]-4,@30,@30\" cursor=\"hand\" interactive=\"1\"/>"
        L"<para id=\"msgbody\" margin=\"45,0,30,0\" break=\"1\" simulate-align=\"1\">"
        L"%s"
        L"</para>"
        L"<bkele data=\"bubble\" left-skin=\"skin.rich_left_bubble\" right-skin=\"skin.rich_right_bubble\" left-pos=\"35,{-9,[10,[10\" right-pos=\"{-10,{-9,-35,[10\" />"
        L"%s"
        L"</RichEditContent>",
		pInfo->Id,
        pInfo->AvatarId,
        body,
        pResendBtn);

	//写入历史消息列表
	BaseInfo* pUser;
	MsgInfo msgInfo(content,pInfo->Id, 1);
	m_pAdapterLvContact->FindFormId(pInfo->Id, &pUser);
	pUser->m_historyChat.PushMsg(msgInfo);
	//m_pAdapterLvUser->GetCurSelUser().m_historyChat.PushMsg(msgInfo);

	if(m_pAdapterLvUser->GetSelNo() < 0 /*|| m_pAdapterLvUser->GetCurSelUser().Id != info.Id*/)
		return 0;

    return _pMsgRichEdit->InsertContent(content, insertTo);
}

void CMainDlg::AddCustomCenterMessage()
{
    const TCHAR * pFormatedCenterText =
        L"<RichEditContent id=\"201601015337090001\" type=\"msg\" >"
        L"<para break=\"1\" />"
        L"<para id=\"righttext\" margin=\"100,0,100,0\" break=\"1\" align=\"center\" simulate-align=\"1\">"
        L"<text font-size=\"10\" >您取消了“Adobe_Photoshop_CS5_green_7xdown.com.rar”(118.91MB)的发送，文件传输失败。</text>"
        L"</para>"
        L"<bkele skin=\"skin.rich_sysmsg_bk\" pos=\"{-30,{0,[10,[0\" hittestable=\"0\" />"
        L"<bkele skin=\"skin.rich_warning\" pos=\"{10,{3,@16,@16\" hittestable=\"0\"/>"
        L"</RichEditContent>";

    _pMsgRichEdit->InsertContent(pFormatedCenterText);
}

void CMainDlg::OnShowSendTypeMenu()
{
    CPoint pt;
    GetCursorPos(&pt);

    MenuWrapper menu(L"menu_template", L"SMENU");
    menu.AddMenu(_T("按Enter键发送消息"), MENUID_PRESS_ENTER_TO_SEND, TRUE, _sendType == PRESS_ENTER_TO_SEND);
    menu.AddMenu(_T("按Ctrl+Enter键发送消息"), MENUID_PRESS_ENTER_AND_CTRL_TO_SEND, TRUE, _sendType == PRESS_ENTER_AND_CTRL_TO_SEND);
    int ret = menu.ShowMenu(TPM_RETURNCMD, pt.x, pt.y, m_hWnd);

    if (ret == MENUID_PRESS_ENTER_TO_SEND)
    {
        _sendType = PRESS_ENTER_TO_SEND;
    }
    else if (ret == MENUID_PRESS_ENTER_AND_CTRL_TO_SEND)
    {
        _sendType = PRESS_ENTER_AND_CTRL_TO_SEND;
    }
}

bool CMainDlg::OnShowInputRichEditMenu(SOUI::EventArgs *pEvt)
{
    CHARRANGE chrSel;
    _pInputRichEdit->GetSel(&chrSel.cpMin, &chrSel.cpMax);
    RichEditOleBase* pOle = _pInputRichEdit->GetSelectedOle();

    /*
     * 构造菜单项
     */

    MenuWrapper menu(L"menu_template", L"SMENU");

    BOOL enableCopy = (chrSel.cpMax - chrSel.cpMin) >= 1;
    menu.AddMenu(_T("Copy(&C)"), MENUID_COPY, enableCopy, FALSE);
    menu.AddMenu(_T("Cut(&X)"), MENUID_CUT, enableCopy, FALSE);
    menu.AddMenu(_T("Paste(&V)"), MENUID_PASTE, TRUE, FALSE);
    menu.AddMenu(_T("Select all(&A)"), MENUID_SEL_ALL, TRUE, FALSE);

    if (pOle && pOle->IsClass(RichEditImageOle::GetClassName()))
    {
        menu.AddMenu(_T("另存为"), MENUID_SAVE_AS, TRUE, FALSE);
    }
    else if (pOle && pOle->IsClass(RichEditMetaFileOle::GetClassName()))
    {
        menu.AddMenu(_T("打开"), MENUID_OPEN_FILE, TRUE, FALSE);
        menu.AddMenu(_T("打开文件夹"), MENUID_OPEN_FILE_DIR, TRUE, FALSE);
    }

    /*
     * 弹出菜单
     */
    int ret = 0;
    POINT pt;
    ::GetCursorPos(&pt);

    ret = menu.ShowMenu(TPM_RETURNCMD, pt.x, pt.y, m_hWnd);

    /*
     * 处理菜单消息
     */
    switch (ret)
    {
    case MENUID_COPY:
        _pInputRichEdit->Copy();
        break;

    case MENUID_SEL_ALL:
        _pInputRichEdit->SelectAll();
        break;

    case MENUID_CUT:
        _pInputRichEdit->Cut();
        break;

    case MENUID_PASTE:
        _pInputRichEdit->Paste();
        break;

    case MENUID_SAVE_AS:
        if (pOle)
        {
            RichEditImageOle* pImageOle = static_cast<RichEditImageOle*>(pOle);
            //SaveImage(pImageOle->GetImagePath());
        }
        break;

    case MENUID_OPEN_FILE:
        if (pOle)
        {
            RichEditMetaFileOle* pMetaFileOle = static_cast<RichEditMetaFileOle*>(pOle);
            ShellExecute(NULL, _T("open"), pMetaFileOle->GetFilePath(), NULL, NULL, SW_SHOW);
        }
        break;

    case MENUID_OPEN_FILE_DIR:
        if (pOle)
        {
            RichEditMetaFileOle* pMetaFileOle = static_cast<RichEditMetaFileOle*>(pOle);
            SStringW param;
            param.Format(_T("/select,\"%s\""), pMetaFileOle->GetFilePath());
            ShellExecute(NULL, _T("open"), _T("explorer.exe"), param, NULL, SW_SHOW);
        }
        break;
    }

    return true;
}

void CMainDlg::FillRClickAvatarMenu(MenuWrapper& menu, RichEditContent* pContent)
{
    menu.AddMenu(_T("Send message"), MENUID_SEND_MSG, TRUE, FALSE);
    menu.AddMenu(_T("Network call"), MENUID_MAKE_CALL, TRUE, FALSE);
    menu.AddMenu(_T("View more"), MENUID_SHOW_INFO, TRUE, FALSE);
    if (pContent && pContent->GetAlign() == RichEditObj::ALIGN_LEFT)
    {
        menu.AddMenu(_T("@TA"), MENUID_AT, TRUE, FALSE);
    }
}

void CMainDlg::FillRClickImageMenu(MenuWrapper& menu, RichEditContent* pContent)
{
    if (pContent && pContent->GetAlign() == RichEditObj::ALIGN_RIGHT)
    {
        menu.AddMenu(_T("Revoke"), MENUID_RECALL_MSG, TRUE, FALSE);
    }

    menu.AddMenu(_T("Copy"), MENUID_COPY, TRUE, FALSE);
    menu.AddMenu(_T("Save as"), MENUID_SAVE_AS, TRUE, FALSE);
    menu.AddMenu(_T("Select all"), MENUID_SEL_ALL, TRUE, FALSE);
    menu.AddMenu(_T("Clear"), MENUID_CLEAR, TRUE, FALSE);
}

void CMainDlg::FillRClickFileMenu(MenuWrapper& menu, RichEditContent* pContent)
{
    if (pContent && pContent->GetAlign() == RichEditObj::ALIGN_RIGHT)
    {
        menu.AddMenu(_T("Revoke"), MENUID_RECALL_MSG, TRUE, FALSE);
    }

    menu.AddMenu(_T("Open"), MENUID_OPEN_FILE, TRUE, FALSE);
    menu.AddMenu(_T("Open folder"), MENUID_OPEN_FILE_DIR, TRUE, FALSE);
    menu.AddMenu(_T("Select all"), MENUID_SEL_ALL, TRUE, FALSE);
    menu.AddMenu(_T("Clear"), MENUID_CLEAR, TRUE, FALSE);
}

void CMainDlg::FillRClickSelRegionMenu(MenuWrapper& menu, RichEditContent* pContent)
{
    if (pContent && pContent->GetAlign() == RichEditObj::ALIGN_RIGHT)
    {
        menu.AddMenu(_T("Revoke"), MENUID_RECALL_MSG, TRUE, FALSE);
    }

    menu.AddMenu(_T("Copy"), MENUID_COPY, TRUE, FALSE);
    menu.AddMenu(_T("Select all"), MENUID_SEL_ALL, TRUE, FALSE);
    menu.AddMenu(_T("Clear"), MENUID_CLEAR, TRUE, FALSE);
}

void CMainDlg::FillRClickBubbleMenu(MenuWrapper& menu, RichEditContent* pContent)
{
    if (pContent && pContent->GetAlign() == RichEditObj::ALIGN_RIGHT)
    {
        menu.AddMenu(_T("Revoke"), MENUID_RECALL_MSG, TRUE, FALSE);
    }
    menu.AddMenu(_T("Copy"), MENUID_COPY_BUBBLE, TRUE, FALSE);
    menu.AddMenu(_T("Select all"), MENUID_SEL_ALL, TRUE, FALSE);
    menu.AddMenu(_T("Clear"), MENUID_CLEAR, TRUE, FALSE);
}

void CMainDlg::FillRClickNothingMenu(MenuWrapper& menu)
{
    menu.AddMenu(_T("Select all"), MENUID_SEL_ALL, TRUE, FALSE);
    menu.AddMenu(_T("Clear"), MENUID_CLEAR, TRUE, FALSE);
}

bool CMainDlg::OnShowMessageRichEditMenu(SOUI::EventArgs *pEvt)
{
    EventCtxMenu * pev = static_cast<EventCtxMenu*>(pEvt);

    CHARRANGE selRange;
    _pMsgRichEdit->GetSel(&selRange.cpMin, &selRange.cpMax);
    int selectedCount = selRange.cpMax - selRange.cpMin;

    //
    // 如果鼠标没有落在选中区域上，需要取消选中
    //
    if (selectedCount > 0)
    {
        int cp = _pMsgRichEdit->CharFromPos(pev->pt);
        if (cp < selRange.cpMin || cp > selRange.cpMax)
        {
            _pMsgRichEdit->SetSel(cp, cp);
            selectedCount = 0;
        }
    }

    //
    // 对于右键在选择区域上的各种判断
    //

    RichEditObj * pHitTestObj = _pMsgRichEdit->HitTest(pev->pt);
    RichEditObj * pObj = pHitTestObj;

    for (; pObj != NULL && pObj->GetParent(); pObj = pObj->GetParent());

    RichEditContent * pContent = sobj_cast<RichEditContent>(pObj);
    RichEditImageOle* pImageOle = NULL;
    RichEditFileOle* pFileOle = NULL;

    MenuWrapper menu(L"menu_template", L"SMENU");

    if (pContent == NULL || pHitTestObj == NULL)
    {
        if (selectedCount > 0)
            FillRClickSelRegionMenu(menu, pContent);
        else
            FillRClickNothingMenu(menu);
    }
    else if (pHitTestObj->IsClass(RichEditBkElement::GetClassName()) && pHitTestObj->GetData() == _T("avatar"))
    {
        FillRClickAvatarMenu(menu, pContent);
    }
    else if (pHitTestObj->IsClass(RichEditImageOle::GetClassName()))
    {
        pImageOle = static_cast<RichEditImageOle*>(pHitTestObj);
        if (pImageOle->GetImageType() == IMGTYPE_NORMAL)
            FillRClickImageMenu(menu, pContent);
        else
            FillRClickSelRegionMenu(menu, pContent);
    }
    else if (pHitTestObj->IsClass(RichEditFileOle::GetClassName()))
    {
        pFileOle = static_cast<RichEditFileOle*>(pHitTestObj);
        FillRClickFileMenu(menu, pContent);
    }
    else if (pHitTestObj->IsClass(RichEditReminderOle::GetClassName()))
    {
        FillRClickSelRegionMenu(menu, pContent);
    }
    else if (pHitTestObj->IsClass(RichEditBkElement::GetClassName()) && pHitTestObj->GetData() == _T("bubble"))
    {
        if (selectedCount > 0)
            FillRClickSelRegionMenu(menu, pContent);
        else
            FillRClickBubbleMenu(menu, pContent);
    }
    else
    {
        FillRClickNothingMenu(menu);
    }

    /*
     * 弹出菜单
     */
    int ret = 0;
    POINT pt;
    ::GetCursorPos(&pt);

    ret = menu.ShowMenu(TPM_RETURNCMD, pt.x, pt.y, m_hWnd);

    /*
     * 处理菜单消息
     */

    CHARRANGE          chr = { 0, -1 };
    IDataObject      * pobj;
    RichFormatConv     conv;
    SStringW           str;

    switch (ret)
    {
    case MENUID_COPY:
        _pMsgRichEdit->Copy();
        break;

    case MENUID_SEL_ALL:
        _pMsgRichEdit->SelectAll();
        break;

    case MENUID_SAVE_AS:
        if (pImageOle)
        {
            //SaveImage(pImageOle->GetImagePath());
        }
        break;

    case MENUID_OPEN_FILE:
        if (pFileOle)
        {
            //ShellExecute(NULL, _T("open"), pFileOle->GetFilePath(), NULL, NULL, SW_SHOW);
        }
        break;

    case MENUID_OPEN_FILE_DIR:
        if (pFileOle)
        {
            //SStringW param;
            //param.Format(_T("/select,\"%s\""), pMetaFileOle->GetFilePath());
            //ShellExecute(NULL, _T("open"), _T("explorer.exe"), param, NULL, SW_SHOW);
        }
        break;

    case MENUID_COPY_BUBBLE:
        if (pContent)
        {
            pObj = pContent->GetById(_T("msgbody"));
            chr = pObj->GetCharRange();
            str = _pMsgRichEdit->GetSelectedContent(&chr);
            conv.InitFromRichContent(str);
            conv.ToDataObject(&pobj);
            OleSetClipboard(pobj);
            OleFlushClipboard();
            pobj->Release();
        }
        break;

    case MENUID_CLEAR:
        _pMsgRichEdit->Clear();
        break;

    case MENUID_SEND_MSG:
        ::MessageBox(m_hWnd, _T("点击了发送消息菜单"), _T("提示"), MB_OK);
        break;

    case MENUID_MAKE_CALL:
        ::MessageBox(m_hWnd, _T("点击了网络通话菜单"), _T("提示"), MB_OK);
        break;

    case MENUID_SHOW_INFO:
        ::MessageBox(m_hWnd, _T("点击了查看资料菜单"), _T("提示"), MB_OK);
        break;

    case MENUID_AT:
        {
            str = RichEditReminderOle::MakeFormattedText(
                _T("点击菜单@人"),
                13,
                RGB(00, 0x6e, 0xfe));

            SStringW content;
            content.Format(L"<RichEditContent>%s</RichEditContent>", str);
            _pInputRichEdit->InsertContent(content, RECONTENT_CARET);
        }
        break;

    case MENUID_RECALL_MSG:
        if (pContent)
        {
            UINT index = _pMsgRichEdit->DeleteContent(pContent);
            //AddCenterMessage(GetRandomUser(), L"<text font-size=\"10\">你已撤回一条消息</text>", index);
        }
        break;
    }

    return true;
}

void CMainDlg::OnSetup()
{
	CSetupDlg* dlg = new CSetupDlg;
	dlg->Create(m_hWnd);
	dlg->SSendMessage(WM_INITDIALOG);
	dlg->ShowWindow(SW_SHOW);
}
