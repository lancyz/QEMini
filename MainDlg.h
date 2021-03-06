// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "imre\SImRichedit.h"
#include "imre\ClipboardConverter.h"
#include "imre/ImgProvider.h"
#include "SAntialiasSkin.h"
#include "control\SDropDown.h"
#include "MenuWrapper.h"
#include "extend.ctrls/SListboxex.h"
#include "WHRoundRectFrameHelper.h"

#include "extend.ctrls/GSTabCtrl.h"

#include "AdapterUserListView.h"
#include "AdapterContactView.h"
#include "AdapterFaceTileView.h"
#include "AdapterGroupMember.h"

#include "UserInfo.h"
#include "IMMsg.h"

enum RichEditMenuId
{
	MENUID_COPY = 1,
	MENUID_CUT,
	MENUID_PASTE,
	MENUID_SEL_ALL,
	MENUID_SAVE_AS,
	MENUID_OPEN_FILE,
	MENUID_OPEN_FILE_DIR,
	MENUID_COPY_BUBBLE,
	MENUID_CLEAR,
	MENUID_SEND_MSG,
	MENUID_MAKE_CALL,
	MENUID_AT,
	MENUID_SHOW_INFO,
	MENUID_RECALL_MSG,
};

enum SendTypeMenuId
{
	MENUID_PRESS_ENTER_TO_SEND = 1,
	MENUID_PRESS_ENTER_AND_CTRL_TO_SEND
};

#define IMGTYPE_NORMAL _T("normal_img")
#define IMGTYPE_SMILEY _T("smiley_img")

#define TIMERID_LOAD_MSG 1499

#define OLENAME_FETCHMORE _T("FetchMoreOle")

class EventItemSelected : public TplEventArgs<EventItemSelected>
{
	SOUI_CLASS_NAME(EventItemSelected, L"on_item_selected")
public:
	EventItemSelected(SObject *pSender) :TplEventArgs<EventItemSelected>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 1 };
	int nCurrSelect;
};

// 点击就要选中，是down还是up不要紧
// 回车就要选中
// 上下移动不要关闭
class DropDownListWnd : public SDropDownWnd
{
public:
	DropDownListWnd(ISDropDownOwner* pOwner) :SDropDownWnd(pOwner),
		m_pListBox(NULL)
	{
		m_evtSet.addEvent(EVENTID(EventItemSelected));
	}

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		SDropDownWnd::PreTranslateMessage(pMsg);

		if (pMsg->message == WM_MOUSEMOVE && m_pListBox)
		{
			POINT pt = { LOWORD(pMsg->lParam), HIWORD(pMsg->lParam) };
			CRect rc = m_pListBox->GetClientRect();
			if (rc.PtInRect(pt))
			{
				int nItem = (pt.y - rc.top) / m_pListBox->GetItemHeight();
				m_pListBox->SetCurSel(nItem);
			}
		}

		if (pMsg->message == WM_MOUSEWHEEL ||
			((pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP) &&
			(pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN || pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)))
		{
			if (pMsg->wParam == VK_RETURN && m_pListBox)
			{
				EventItemSelected evt(this);
				evt.nCurrSelect = m_pListBox->GetCurSel();
				FireEvent(evt);
			}
			//截获滚轮及上下键消息
			CSimpleWnd::SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
			return TRUE;
		}

		return FALSE;
	}

	virtual BOOL Create(LPCRECT lpRect, LPVOID lParam, DWORD dwStyle = WS_POPUP, DWORD dwExStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
	{
		if (!SDropDownWnd::Create(lpRect, lParam, dwStyle, dwExStyle))
			return FALSE;

		pugi::xml_document xmlDoc;
		LOADXML(xmlDoc, L"SelectionDropDownWnd", RT_LAYOUT);

		if (xmlDoc)
		{
			InitFromXml(xmlDoc.child(L"SOUI"));
			m_pListBox = FindChildByName2<SListBoxEx>(L"selectionlist");
			m_pListBox->SetOwner(this);
			m_pListBox->SetFocus();
			CSimpleWnd::SetCapture();
		}
		return TRUE;
	}

	void AdjustWindowSize()
	{
		if (!m_pListBox)
		{
			return;
		}

		int nWndWidth = GetClientRect().Width();
		int nWndHeight = m_pListBox->GetItemCount() * m_pListBox->GetItemHeight();
		if (nWndHeight > 160)
		{
			nWndHeight = 160;
		}

		int nYOffset = GetClientRect().Height() - m_pListBox->GetClientRect().Height();
		nWndHeight += nYOffset;         //加上阴影偏移

		SetWindowPos(HWND_TOP,
			0, 0, nWndWidth, nWndHeight,    // left,top,width,height
			SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE);
	}

	BOOL FireEvent(EventArgs &evt)
	{
		if (evt.GetID() == EventOfPanel::EventID)
		{
			EventOfPanel *pEvtOfPanel = (EventOfPanel*)&evt;
			if (pEvtOfPanel->pOrgEvt->GetID() == EventCmd::EventID)
			{
				EventItemSelected evt(this);
				evt.nCurrSelect = m_pListBox->GetCurSel();
				__super::FireEvent(evt);

				EndDropDown(IDCANCEL);
				return TRUE;
			}
		}
		return SWindow::FireEvent(evt);
	}

private:
	SListBoxEx * m_pListBox;
};

class CMainDlg : public SHostWnd , public ISDropDownOwner//, public CWHRoundRectFrameHelper<CMainDlg>
{
public:
	CMainDlg();
	~CMainDlg();

	virtual SWindow * GetDropDownOwner();
	virtual void OnCreateDropDown(SDropDownWnd *pDropDown);
	virtual void OnDestroyDropDown(SDropDownWnd *pDropDown);

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);
	void OnChat();
	void OnGroupChat();
	void OnSetup();
	void OnSend();
	void OnFace();
	void OnSendPicture();
	void OnShowSendTypeMenu();
	void OnTimer(UINT_PTR idEvent);
	void OnDropFiles(HDROP hDropInfo);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnKeyDown(TCHAR nChar, UINT nRepCnt, UINT nFlags);
	void OnLButtonUp(UINT nFlags,CPoint pt);
	bool OnEditorAcceptData(SOUI::EventArgs *pEvt);
	bool OnShowInputRichEditMenu(SOUI::EventArgs *pEvt);
	bool OnShowMessageRichEditMenu(SOUI::EventArgs *pEvt);
	bool OnInputEditorChange(SOUI::EventArgs *pEvt);
	bool OnMemberSelected(SOUI::EventArgs *pEvt);
	bool OnInputRichObjEvent(SOUI::EventArgs *pEvt);
	bool OnMsgRichObjEvent(SOUI::EventArgs *pEvt);
	bool OnMsgRichScrollEvent(SOUI::EventArgs *pEvt);
	
	void OnBtnMsgBox();
		//托盘通知消息处理函数
	LRESULT OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);
	//演示如何响应菜单事件
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);
		int OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	void AddFetchMoreBlock();
	void AddSeparatorBar();
	UINT AddCenterMessage(UserInfo& info, const SStringW& body, UINT insertTo = RECONTENT_LAST);
	UINT AddCenterMessageWhitoutBuggle(UserInfo& info, const SStringW& body, UINT insertTo = RECONTENT_LAST);
	UINT AddLeftMessage(BaseInfo* pInfo, const SStringW& body, UINT insertTo = RECONTENT_LAST);
	UINT AddTeamLeftMessage(BaseInfo* pInfo, UINT uSendID, const SStringW& body, UINT insertTo = RECONTENT_LAST);
	UINT AddRightMessage(BaseInfo* pInfo, const SStringW& body, UINT insertTo = RECONTENT_LAST);
	void AddCustomCenterMessage();
	void ShowMemberSelectionWnd(const CRect& rcCursor, const SStringW& strKeyWord);
	void FillRClickAvatarMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickImageMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickFileMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickSelRegionMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickBubbleMenu(MenuWrapper& menu, RichEditContent* pContent);
	void FillRClickNothingMenu(MenuWrapper& menu);
	void DragDropFiles(RichFormatConv::DropFiles& files);

	void OnLvUserSelchanging(EventArgs *pEvt);
	void OnLvContactSelchanging(EventArgs *pEvt);
	void OnTvFaceSelchanging(EventArgs *pEvt);

//	UserInfo& GetRandomUser();
	void InsertPicture(SStringT strFile);
	void ShowChat(int nNewSel);
	void SendMsg(SStringT strMsg);

protected:
	LRESULT OnNormalChat(UINT uMsg,WPARAM wp,LPARAM lp,BOOL & bHandled);
	LRESULT OnTeamChat(UINT uMsg,WPARAM wp,LPARAM lp,BOOL & bHandled);


protected:
	void OnLanguage(int nID);
	void OnLanguageBtnCN();
	void OnLanguageBtnJP();
		//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_chat", OnChat)
		EVENT_NAME_COMMAND(L"btn_group_chat", OnGroupChat)
		EVENT_NAME_COMMAND(L"btn_setup", OnSetup)
		EVENT_NAME_COMMAND(L"btn_face", OnFace)
		EVENT_NAME_COMMAND(L"btn_send", OnSend)
		EVENT_NAME_COMMAND(L"btn_sendpic", OnSendPicture)
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_NAME_COMMAND(L"zh_cn", OnLanguageBtnCN);
		EVENT_NAME_COMMAND(L"jp", OnLanguageBtnJP);
		EVENT_NAME_COMMAND(L"btn_showsendmenu", OnShowSendTypeMenu)
		EVENT_NAME_HANDLER(L"lv_user",SOUI::EVT_LV_SELCHANGING, OnLvUserSelchanging)
		EVENT_NAME_HANDLER(L"lv_contact",SOUI::EVT_LV_SELCHANGING, OnLvContactSelchanging)
		EVENT_NAME_HANDLER(L"lv_face_tile",SOUI::EVT_LV_SELCHANGING, OnTvFaceSelchanging)
			EVENT_MAP_END()
		//HostWnd真实窗口消息处理
		BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_LBUTTONUP(OnLButtonUp)
				//托盘消息处理
		MESSAGE_HANDLER(WM_ICONNOTIFY, OnIconNotify)
		MSG_WM_COMMAND(OnCommand)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DROPFILES(OnDropFiles)
		MSG_WM_TIMER(OnTimer)
		MSG_WM_KEYDOWN(OnKeyDown)
		//CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainDlg >)//重要

		//自定义消息
		MESSAGE_HANDLER(WM_NORMAL_CHAT, OnNormalChat)
		MESSAGE_HANDLER(WM_TEAM_CHAT, OnTeamChat)

		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
		END_MSG_MAP()

public:
	SListView* m_pLstViewFixUser;
	AdapterUserListView* m_pAdapterLvUser;

	SListView* m_pLstViewFixContact;
	AdapterContactView* m_pAdapterLvContact;

	STileView* m_pFaceTileView;
	CAdapterFaceTileView* m_pAdapterTvFace;

	STileView* m_pGroupMemberView;
	CAdapterMemberView* m_pAdapterTvGroupMember;

private:
	BOOL			m_bLayoutInited;
		SShellNotifyIcon shellNotifyIcon;

		enum SendType
		{
			PRESS_ENTER_TO_SEND = 1,
			PRESS_ENTER_AND_CTRL_TO_SEND,
		};

		UserInfo* m_pMyInfo;
		CUserInfoDlg m_userInfoDlg;

		CPoint m_LBtnDownPt;

		typedef std::vector<UserInfo> UserInfoVec;

		//UserInfoVec         _users;
		BOOL			    _initialized;
		SImRichEdit *       _pMsgRichEdit;
		SImRichEdit *       _pInputRichEdit;
		DropDownListWnd *   _pMemberSelWnd;     /**< 群聊时@的时候用来选人 */
		int                 _msgAdded;          // 用来判断获取更多ole的状态
		time_t              _lastWhellTime;
		int                 _totalWhellDelta;
		int                 _sendType;          // 输入enter发送或者enter+ctrl发送

		GSTabCtrl* m_pMainTab;

		SWindow* m_pUserWnd;
		SWindow* m_pGroupWnd;
	};
