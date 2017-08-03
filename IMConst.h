#pragma once
#include <vector>

#ifndef _IMCONST_H
#define _IMCONST_H

//"10.202.1.4","10.202.1.15"   云测试
//"qechat.coolpad.com","qeweb.coolpad.com"   生产

//消息服务器
#define  MSG_SRV_ADDR "qechat.coolpad.com"

//web服务器
#define WEB_SRV_ADDR "qeweb.coolpad.com"

//图片服务器
#define DOWNLOAD_PIC_ADDR "http://qevideo.coolpad.com:80"
#define UPLOAD_PIC_ADDR "http://qevideo.coolpad.com:80"

//语音视频服务器
#define DOWNLOAD_VOICE_ADDR "http://qevideo.coolpad.com:80"
#define UPLOAD_VOICE_ADDR "http://qevideo.coolpad.com:80"

//新闻公告：
#define  NEWS_ADDR_IN "http://10.3.2.165:8080"  //内网
#define  NEWS_ADDR_OUT "m.yulong.com"   //外网

//论坛url：
#define BBS_URL "http://qebbs.yulong.com:1108/adminapi.php"

//导航url：
#define NAVIGATION_URL "http://ioa.yulong.com/menuNavigater/load.html"

//群文件传输Tracker服务器地址
#define TRANSFER_TEAM_FILE_TRACKER_IP "qegroupfile.coolpad.com"


#define IM_BUF_SIZE		(5*1024)

//项目中的命名事件
#define EVENT_LOGIN _T("LoginEvent")


//消息信息类
class MsgInfo
{
public:
	MsgInfo(){};
	MsgInfo(SStringT strText, int nSendId, int nRecvId, int nType = NORMAL, bool bIsTeamMsg = false, UINT nId = MakeMsgId(), UINT uTime = (UINT)time(0))
	{
		this->nId = nId;
		this->nType = nType;
		this->nSendId = nSendId;
		this->nRecvId = nRecvId;
		this->bIsGroupMsg = bIsTeamMsg;
		this->uTime = uTime;
		this->strText = strText;
	}
	~MsgInfo(){};

public:

	enum MsgType
	{
		NORMAL = 0,  //普通消息，可夹带本地表情
		PICTURE,  //仅有图片的消息，如自定义表情
		VOICE,  //语音消息
		VEDIO,  //小视频
	};

	UINT nId;  //消息id
	int nType; //消息类型
	int nSendId; //发送人ID
	int nRecvId;  //接收人ID
	bool bIsGroupMsg; //是否群消息
	UINT uTime; //时间戳
	SStringT strText;  //消息内容

private:
	//生成消息id
	static UINT MakeMsgId()
	{
		return GetTickCount();
	}
};

//历史聊天消息缓存管理类
class HistoryChat
{
public:
	HistoryChat()
	{ 
		m_nUnReadMsg = 0;
	}
	~HistoryChat(){};

#define MSG_MAX   30

	inline int getCount()
	{
		return m_msgList.size();
	}

	void PushMsg(MsgInfo msgInfo)
	{
		if(getCount() < MSG_MAX)
		{
			m_msgList.push_back(msgInfo);
		}
		else
		{
			for (int i = 0; i < getCount() - 1; i++)
			{
				m_msgList[i] = m_msgList[i + 1];
			}
			m_msgList[getCount() - 1] = msgInfo;
		}
	}

	MsgInfo& GetMsg(int nIndex)
	{
		return m_msgList[nIndex];
	}

	MsgInfo& FindMsg(int nId)
	{
		for (int i = 0 ; i < getCount(); i++)
		{
			if(m_msgList[i].nId = nId)
				return m_msgList[i];
		}
	}

	MsgInfo& GetLastMsg()
	{
		return m_msgList.back();
	}

private:
	std::vector<MsgInfo> m_msgList;
	int m_nUnReadMsg; //未读消息数
};


class BaseInfo
{
public:
	BaseInfo()
	{
		//nType = DEFAULT;
	}
	~BaseInfo(){};

	enum InfoType
	{
		USER_INFO = 0,
		GROUP_INFO,
		SEPARATOR
	};

	UINT Id;  //id号,系统生成唯一
	int nType; //类型
	SStringT Name; //名称
	SStringW AvatarId; //头像图片资源id
	SStringW AvatarPath; //头像路径

	HistoryChat m_historyChat; //历史消息缓存
};

class SeparInfo : public BaseInfo
{
public:
	SeparInfo()
	{
		nType = SEPARATOR;
	};
	~SeparInfo(){};

	SStringW szName; //标题
};

//用户信息类
class UserInfo : public BaseInfo
{
public:
	UserInfo()
	{
		nType = USER_INFO;
	}

	SStringT EnName; //英文名
	SStringT EmpNo; //工号
	SStringT Dept; //部门
	SStringT EMail; //邮箱
	SStringT Note; //签名
};

//群信息类
class GroupInfo : public BaseInfo
{
public:
	GroupInfo()
	{
		nType = GROUP_INFO;
	}

	GroupInfo(UINT nId, LPCWSTR pName, int nCount)
	{
		nType = GROUP_INFO;
	}

	~GroupInfo()
	{

	}

	bool FindMember(UINT nId, UserInfo& userInfo)
	{
		for (int i = 0; i < (int)MemberList.size(); i++)
		{
			if(nId == MemberList[i].Id)
			{
				userInfo = MemberList[i];
				return true;
			}
		}
		return false;
	}

	UINT MasterId;  //创建者id
	SStringT Note; //群公告
	int Members;  //成员数

	std::vector<UserInfo> MemberList;
};

#endif


