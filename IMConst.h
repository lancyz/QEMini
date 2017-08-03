#pragma once
#include <vector>

#ifndef _IMCONST_H
#define _IMCONST_H

//"10.202.1.4","10.202.1.15"   �Ʋ���
//"qechat.coolpad.com","qeweb.coolpad.com"   ����

//��Ϣ������
#define  MSG_SRV_ADDR "qechat.coolpad.com"

//web������
#define WEB_SRV_ADDR "qeweb.coolpad.com"

//ͼƬ������
#define DOWNLOAD_PIC_ADDR "http://qevideo.coolpad.com:80"
#define UPLOAD_PIC_ADDR "http://qevideo.coolpad.com:80"

//������Ƶ������
#define DOWNLOAD_VOICE_ADDR "http://qevideo.coolpad.com:80"
#define UPLOAD_VOICE_ADDR "http://qevideo.coolpad.com:80"

//���Ź��棺
#define  NEWS_ADDR_IN "http://10.3.2.165:8080"  //����
#define  NEWS_ADDR_OUT "m.yulong.com"   //����

//��̳url��
#define BBS_URL "http://qebbs.yulong.com:1108/adminapi.php"

//����url��
#define NAVIGATION_URL "http://ioa.yulong.com/menuNavigater/load.html"

//Ⱥ�ļ�����Tracker��������ַ
#define TRANSFER_TEAM_FILE_TRACKER_IP "qegroupfile.coolpad.com"


#define IM_BUF_SIZE		(5*1024)

//��Ŀ�е������¼�
#define EVENT_LOGIN _T("LoginEvent")


//��Ϣ��Ϣ��
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
		NORMAL = 0,  //��ͨ��Ϣ���ɼд����ر���
		PICTURE,  //����ͼƬ����Ϣ�����Զ������
		VOICE,  //������Ϣ
		VEDIO,  //С��Ƶ
	};

	UINT nId;  //��Ϣid
	int nType; //��Ϣ����
	int nSendId; //������ID
	int nRecvId;  //������ID
	bool bIsGroupMsg; //�Ƿ�Ⱥ��Ϣ
	UINT uTime; //ʱ���
	SStringT strText;  //��Ϣ����

private:
	//������Ϣid
	static UINT MakeMsgId()
	{
		return GetTickCount();
	}
};

//��ʷ������Ϣ���������
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
	int m_nUnReadMsg; //δ����Ϣ��
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

	UINT Id;  //id��,ϵͳ����Ψһ
	int nType; //����
	SStringT Name; //����
	SStringW AvatarId; //ͷ��ͼƬ��Դid
	SStringW AvatarPath; //ͷ��·��

	HistoryChat m_historyChat; //��ʷ��Ϣ����
};

class SeparInfo : public BaseInfo
{
public:
	SeparInfo()
	{
		nType = SEPARATOR;
	};
	~SeparInfo(){};

	SStringW szName; //����
};

//�û���Ϣ��
class UserInfo : public BaseInfo
{
public:
	UserInfo()
	{
		nType = USER_INFO;
	}

	SStringT EnName; //Ӣ����
	SStringT EmpNo; //����
	SStringT Dept; //����
	SStringT EMail; //����
	SStringT Note; //ǩ��
};

//Ⱥ��Ϣ��
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

	UINT MasterId;  //������id
	SStringT Note; //Ⱥ����
	int Members;  //��Ա��

	std::vector<UserInfo> MemberList;
};

#endif


