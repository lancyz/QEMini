#ifndef _IMCMD_H
#define _IMCMD_H

/******************************/
/* EPA IM protocol V1.0                       */
/* 2015-07-09                                   */
/* Copyright @ Yulong Corporation    */
/******************************/
#include <windows.h>
#pragma warning(disable:4200)

/*the CMD code*/

#define		IM_CLIENT_CHECK							0xEE

#define     IM_LOG_IN                                    0x01                     //登录
#define     IM_LOG_OUT                                0x02                    //注销
#define     IM_CHANGE_STATUS                 0x03                    //修改用户状态
#define     IM_MODIFY_USERDATA             0x04                     //修改用户资料
#define     IM_GET_OFFLINEMSG                 0x05                   //获取离线信息
#define     IM_SEARCH_USER                       0x06                   //查找用户信息
#define     IM_GET_FRIENDS_LIST                0x08                  //获取好友列表
#define     IM_GET_TEAM_LIST                     0x09                 //获取群列表
#define     IM_GET_TEAM_DATA                  0x0A                 //获取某个群信息
#define     IM_JOIN_TEAM_MSG                  0x0B                //加入群信息
#define     IM_TEAM_ALTER_USER              0x0C                //群主操作用户
#define     IM_TEAM_CHANGE_OWNER	   0x0D                //群主转移
#define     IM_TEAM_MODIFY_DATA          0x0E               //修改群资料
#define     IM_TEAM_DISMISS                      0x0F                //解散群
#define     IM_SWITCH_TEAMTALK             0x10                //群聊界面开关
#define     IM_GET_NETINFO                        0x11              //获取指定ID的用户的IP与端口号
#define     IM_NORMAL_CHAT                    0x12               //普通两个用户聊天
#define     IM_TEAM_CHAT                          0x13              //群聊
#define	    IM_QUIT_TEAM						  0x14				//退群
#define	    IM_KEEPALIVE_CMD				  0x15				//心跳指令，用来接收用户好友在线状态列表
#define     IM_ADD_FRIEND                         0x16                   //添加好友
#define     IM_DEL_FRIEND                          0x17                   //删除好友
#define     IM_BEGIN_TEAMTALK			   	 0x18                //开始群聊
#define     IM_END_TEAMTALK					 0x19                //结束群聊
#define		IM_TEAMCHAT_HEARTBEAT	 0x20				//群聊的心跳
#define		IM_MODIFY_TEAMNOTICE		 0x21				//修改群公告
#define		IM_GET_FRIEND_IP					 0x22				//获取用户的IP地址
#define     IM_MSG_PERSONAL_CHECK  0x23          //个人消息验证包
#define     IM_ERROR_IP_OR_PORT           0x24          //IP或PORT和Server的不一致
#define     IM_TEST                                       0x25         //测试
#define     IM_GET_USER_INFO                   0x26         //获取用户信息
#define     IM_SET_ONESELF_STATUS        0x27        //设置自己的在线状态
#define     IM_MSG_TEAM_CHECK             0x28        //群组消息验证
#define     IM_BE_TAKE_OVER                  0x30      //账号在别处登录被T下线的消息
//#define     IM_TAKING_OVER                   0x31       //告诉服务器在别处登录了账号
#define     IM_SERVIE_NOTICE                     0x32         //服务号公告
#define		IM_SERVIE_NOTICE_CHECK			0x33 //服务号公告消息验证

#define               IM_MEET_CREATE          0x34         //主持人创建多人语音会议消息
#define              IM_MEET_LOGIC              0x35        //用户进行语音会议操作：包括拒绝、接听、接听之后挂断、新成员加入等操作消息
#define              IM_MEET_SEND               0x36        //服务器转发语音电话会议状态消息
#define              IM_MEET_INFO_GET        0x37        //获取所有会议成员的信息

//#define              IM_HAVE_SVR_NUM_NOTICE         0x37      //有服务号消息需要推送      
#define              IM_SF_CAR_CMD                   0x39          //顺风车车讯操作以及提示信息 是

#define              IM_GROUP_FILES                 0x3A                    //群文件操作消息
#define              IM_MSG_END                       0x3B                            //消息结束



#define     IM_RESPONSE_SUCCESS             0
#define     IM_RESPONSE_FAILED                 1

#define		IM_CMD_VERSION                      0x0B 			//版本  
#define		IM_CMD_VERSION_TEST           0x0B 			//该版本号提供测试用，绕过cas认证

////////////////////////////////////////////////////////////////

#define DEPT_TEAM_NAME_LEN		100


#define LOGIN_USER_LEN					50


//////////////////////////////////////////////////////////////////////////
#define		IM_FAKE_TRANSFER_FILE					0x23			//这个是点对点文件传输时，模拟的命令包


#pragma pack(push)
#pragma pack(1)




/***************************cmd request format***********************/

/* IM_CMD_HEADER + IM_REQUEST_DATA (pData == XXXX_XXXX_REQUEST struct) */

/***************************cmd response format**********************/

/* IM_CMD_HEADER + IM_RESPONSE_DATA (pData == XXXX_XXXX_RESPONSE struct) */

/******************************************************************/

#define IM_SEND_TRANSMIT			1   
#define IM_SEND_NO_TRANSMIT		0
#define IM_TYPE_REQUEST			0
#define IM_TYPE_RESPONSE			1

typedef struct _TEAMMEET {
	char szMeetId[20];                                                         //会议id                    20字节
	char    szMeetPswd[32];                                                         //会议密码                         20字节
	char szMeetName[30];                                                           //会议名称                         30字节
	int              iType;                                                                                  //消息类型                         4字节
	int              iHostImid;                                                                          //主持imid                         4字节
	int              iMemNums;                                                                      //成员人数(MEETMEMB)4字节    
	char szHostName[20];                                                            //主持人名字           20字节    
	char szHostHead[30];                                                              //主持人头像           30字节    
} TEAMMEET;

typedef struct _MEETMEMB
{
	int              iMemImid;                          //成员imid                                            4字节
	char szMemName[20];             //成员名字                                           20字节    
	char szMemHead[30];              //成员头像                                           30字节    
	int              iStaus;                             //逻辑状态                                       4字节
	int     iFlag;              //在线状态,0离线，1在线     4字节
}MEETMEMB;

typedef struct _MEETSTATCHANGE
{
	char szMeetId[20];           //会议id                        4字节
	int              iMemImid;                          //成员imid                                  4字节
	char szMemName[20];             //成员名字                                  20字节    
	char szMemHead[30];              //成员头像                                  30字节    
	int              iStaus;                             //逻辑状态                              4字节
}MEETSTATCHANGE;


typedef struct _GROUPFILE
{
	 CHAR    szFileName[MAX_PATH]; 
}GROUPFILE, *PROUPFILE;

//顺风车协议
typedef struct _PSFCAR 
{
	UINT         UiReqOrRes;                                //4字节， 0请求或是1应答
	UINT         uiOrderId;                                     //4字节 订单ID
	UINT         uiCmd;                                           //4字节 操作信息 0乘客预约车； 1乘客取消预约； 2司机取消预约； 4司机修改车讯信息
	UINT         uiMsgLen;                                    //4字节 消息长度
}SFCAR, *PSFCAR;


typedef struct _IM_CMD_HEADER
{
    UINT			uiSenderID;				/*发送者ID号---4字节*/
    UINT			uiRecverID;				/*接收者ID号---4字节*/
	UINT			uiMsgID;				//消息ID，标示一个消息
    USHORT			usLength;				/*长度        ---2字节*/
    UCHAR			ucVer;					/*版本        ---1字节*/
    UCHAR   		ucCmdID		: 6;		/*命令类型ID           */  
    UCHAR     		ucCmdType	: 1;		//是否转发：0---不转发  1--转发
    UCHAR     		ucFlag		: 1;		//标志位   ：0---请求    1---响应
    UINT			uiReserved;				//保留		---4字节
}IM_CMD_HEADER, *PIM_CMD_HEADER;

// typedef struct _IM_REQUEST_DATA
// {
//     UINT			uiLen;					//DATA部分总长度，不包括HEADER
//     CHAR			chReqData[1];			//这里为发送的具体命令存储区
// }IM_REQUEST_DATA, *PIM_REQUEST_DATA;

typedef struct _IM_RESPONSE_DATA
{
    UINT			uiRsp;					//命令响应结果 0-命令响应失败  1-命令响应成功
    UINT			uiLen;
   // CHAR			RspData[1];				//response data
}IM_RESPONSE_DATA, *PIM_RESPONSE_DATA;

/*聊天协议*/
/* IM_CMD_HEADER + CHAT_DATA  */
// typedef struct _PIC_TRANS_FROMAT
// {
//     UINT			uiOffset;
//     CHAR			szName[10];
// }PIC_TRANS_FROMAT, *PPIC_TRANS_FROMAT;

typedef struct _CHAT_DATA
{
    UINT			uiDataLen;				//指示后面数据的长度
    CHAR			chData[1];              //uiPicCount * sizeof (PIC_TRANS_FROMAT)  + text char(len = uiDataLen - uiPicCount * sizeof (PIC_TRANS_FROMAT) )
}CHAT_DATA, *PCHAT_DATA;

/*如果为群聊，则uiRecverID为Group ID*/

/*login request and response*/
typedef struct _LOGIN_REQUEST
{
    CHAR    szEmpNo[10];
    CHAR    szPasswd[30];
    CHAR    chStatus;						// 0 -- online   1 -- hide
	CHAR	chFlag;							// 0 普通用户 1 服务号
}LOGIN_REQUEST, *PLOGIN_REQUEST;


typedef struct _LOGIN_REQUEST4
{
	CHAR    szEmpNo[LOGIN_USER_LEN];
	CHAR    szPasswd[30];
	CHAR    chStatus;		 // 0 --离线   1--在线 2--离开
	CHAR    chFlag;			// 0 -- 普通用户   1 -- 服务号
	CHAR    szMd5_IMEI[33];   // 用®?户¡ì手º?机¨²IMEI的Ì?md5值¦Ì
}LOGIN_REQUEST4, *PLOGIN_REQUEST4;

//typedef struct _LOGIN_REQUEST9
//{
//	CHAR    szEmpNo[LOGIN_USER_LEN];
//	CHAR    szPasswd[30];
//	CHAR    chStatus;          // 0 --离¤?线?   1--在¨²线? 2--离¤?开a
//	CHAR    chFlag;            // 0 -- 普?通ª¡§用®?户¡ì   1 -- 服¤t务?号?
//	CHAR    szMd5_IMEI[33];   // 用®?户¡ì手º?机¨²IMEI的Ì?md5值¦Ì
//}LOGIN_REQUEST9, *PLOGIN_REQUEST9;


typedef struct _LOGIN_RESPONSE
{
		UINT	uiUserID;              //登录成功返回用户ID
		char	szName[20];
		char	szNo[10];
		char	szSex[20];
		char	szDept[DEPT_TEAM_NAME_LEN];
		char	szMail[100];
		char	szEnglishName[25];
		char	szPic[30];
		char	szGroupName[20];
		char	szNote[200];
		_LOGIN_RESPONSE()
		{
			memset(this, 0, sizeof(*this));
		}

}LOGIN_RESPONSE, *PLOGIN_RESPONSE;

typedef struct _LOGIN_RESPONSE4
{
	UINT	uiUserID;              //登录成功返回用户ID
	char	szName[20];
	char	szNo[LOGIN_USER_LEN];
	char	szSex[20];
	char	szDept[DEPT_TEAM_NAME_LEN];
	char	szMail[100];
	char	szEnglishName[25];
	char	szPic[30];
	char	szGroupName[20];
	char	szNote[200];

	_LOGIN_RESPONSE4()
	{
		memset(this, 0, sizeof(*this));
	}

}LOGIN_RESPONSE4, *PLOGIN_RESPONSE4;


/*user change status(online/hide/offline/busy/away)*/
//typedef struct _CHANGE_STATUS_REQUEST
//{
//    UCHAR ucNewStatus;
//}CHANGE_STATUS_REQUEST, *PCHANGE_STATUS_REQUEST;

typedef struct _SET_ONESELF_STATUS
{
	CHAR    u8OneselfStatus;// 0 --离线   1--在线  2--离开

}SET_ONESELF_STATUS,*PSET_ONESELF_STATUS;



//////////////////////////////////////////////////////////////////////////
//添加或者删除好友
struct ADD_FRIEND_REQUEST
{
		CHAR			szTeamName[DEPT_TEAM_NAME_LEN];
		CHAR			szMyName[20];			//自己的姓名，让对方知道是谁加了自己为好友
		CHAR			szPic[30];				//自己的头像ID
		CHAR			szNo[10];
		CHAR			szMail[100];
		CHAR			szEnglishName[25];

		ADD_FRIEND_REQUEST()
		{
				memset(this,0,sizeof(*this));
		}
};

struct ADD_FRIEND_REQUEST4
{
	CHAR			szTeamName[DEPT_TEAM_NAME_LEN];
	CHAR			szMyName[20];			//自己的姓名，让对方知道是谁加了自己为好友
	CHAR			szPic[30];				//自己的头像ID
	CHAR			szEmpNo[LOGIN_USER_LEN];
	CHAR			szMail[100];
	CHAR			szEnglishName[25];

	ADD_FRIEND_REQUEST4()
	{
		memset(this,0,sizeof(*this));
	}
};


struct ADD_FRIEND_RESPONSE
{
		CHAR			szTeamName[DEPT_TEAM_NAME_LEN];	
		CHAR			szOtherTeamName[DEPT_TEAM_NAME_LEN];	//两个都是组名，主要是给服务器存数据库需要
		CHAR			szMyName[20];			//自己的姓名，让对方知道是谁加了自己为好友
		CHAR			szPic[30];				//自己的头像ID
		CHAR			szNo[10];
		CHAR			szMail[100];
		CHAR			szEnglishName[25];

		ADD_FRIEND_RESPONSE()
		{
				memset(this,0,sizeof(*this));
		}
};

struct ADD_FRIEND_RESPONSE4
{
	CHAR			szTeamName[DEPT_TEAM_NAME_LEN];	
	CHAR			szOtherTeamName[DEPT_TEAM_NAME_LEN];	//两个都是组名，主要是给服务器存数据库需要
	CHAR			szMyName[20];			//自己的姓名，让对方知道是谁加了自己为好友
	CHAR			szPic[30];				//自己的头像ID
	CHAR			szNo[LOGIN_USER_LEN];
	CHAR			szMail[100];
	CHAR			szEnglishName[25];

	ADD_FRIEND_RESPONSE4()
	{
		memset(this,0,sizeof(*this));
	}
};


struct DEL_FRIEND_REQUEST
{
	CHAR			szMyName[20];			//自己的姓名

	DEL_FRIEND_REQUEST()
	{
		memset(this,0,sizeof(*this));
	}
};

struct DEL_FRIEND_RESPONSE
{
};

//////////////////////////////////////////////////////////////////////////

/*用户申请加入群*/
struct JOIN_GROUP_REQUEST
{
    UINT			uiGroupID;      //申请加入的群的ID
	CHAR			szName[20];		//申请者的名字
	CHAR			szReason[100];	//50个字的申请原因

	JOIN_GROUP_REQUEST()
	{
		memset(this,0,sizeof(*this));
	}
};

typedef JOIN_GROUP_REQUEST*  PJOIN_GROUP_REQUEST;


#define   IM_REQUEST_AGREE					0
#define	 IM_REQUEST_REJECT					1
struct JOIN_GROUP_RESPONSE
{
    CHAR		chRsp;					// 0 -- 同意 1 -- 拒绝
	CHAR		szMasterName[20];		//群主名
    UINT        uiGroupID;				//群ID
	UINT		uiMasterId;
	CHAR		szTeamName[DEPT_TEAM_NAME_LEN];
	USHORT		nMembers;
	USHORT		nMax;

	JOIN_GROUP_RESPONSE()
	{
		memset(this,0,sizeof(*this));
	}
};

typedef JOIN_GROUP_RESPONSE * PJOIN_GROUP_RESPONSE;

/*用户退出群*/
typedef struct _QUIT_GROUP_REQUEST
{
	UINT uiGroupID;      //退出群的ID
}QUIT_GROUP_REQUEST, *PQUIT_GROUP_REQUEST;

// typedef struct _QUIT_GROUP_RESPONSE
// {
// 	UINT uiGroupID;      //退出群的ID
// }QUIT_GROUP_RESPONSE, *PQUIT_GROUP_RESPONSE;


/*群主增加删除用户*/
struct GROUP_ALTERUSER_REQUEST
{
    UINT		uiType;							// 1 -- 增加用户 2 -- 删除用户
    UINT		uiUserID;
    UINT		usGroupID;
	CHAR		szName[20];						//加入或退出群的用户名
	CHAR		szPic[30];						//加入的用户的头像文件名

	UINT		uiMasterId;
	CHAR		szMasterName[20];				//群主名

	//这部分是加用户入群需要的数据
	CHAR		szTeamName[DEPT_TEAM_NAME_LEN];
	USHORT		nMembers;
	USHORT		nMax;
	
	GROUP_ALTERUSER_REQUEST()
	{
		memset(this,0,sizeof(*this));
	}
};

typedef GROUP_ALTERUSER_REQUEST *   PGROUP_ALTERUSER_REQUEST;

// typedef struct _GROUP_ALTERUSER_RESPONSE
// {
//     USHORT		usGroupID;
// }GROUP_ALTERUSER_RESPONSE, *PGROUP_ALTERUSER_RESPONSE;


/*群主变更*/
typedef struct _GROUP_CHANGEADMIN_REQUEST
{
	UINT		uiNewAdminID;		//新群主ID
    UINT		uiGroupID;
}GROUP_CHANGEADMIN_REQUEST, *PGROUP_CHANGEADMIN_REQUEST;

// typedef struct _GROUP_CHANGEADMIN_RESPONSE
// {
//     USHORT usGroupID;
// }GROUP_CHANGEADMIN_RESPONSE, *PGROUP_CHANGEADMIN_RESPONSE;


/*修改群公告*/
struct MODIFY_TEAMNOTICE_REQUEST
{
    UINT		usGroupID;
    CHAR		szDesc[200];

	MODIFY_TEAMNOTICE_REQUEST()
	{
		memset(this,0,sizeof(*this));
	}
};

typedef MODIFY_TEAMNOTICE_REQUEST*  PMODIFY_TEAMNOTICE_REQUEST;


// typedef struct _MODIFY_GROUPDATA_RESPONSE
// {
//     USHORT usUserID;            //修改者ID
// }MODIFY_GROUPDATA_RESPONSE, *PMODIFY_GROUPDATA_RESPONSE;


/*群主解散群组*/
typedef struct _GROUP_DISMISS_REQUEST
{
    UINT      uiGroupID;
}GROUP_DISMISS_REQUEST, *PGROUP_DISMISS_REQUEST;

// typedef struct _GROUP_DISMISS_RESPONSE
// {
//     USHORT      usAdminID;
//     USHORT      usGroupID;
//     CHAR          szTime[20];
//     CHAR          szName[30];         //群组名称
// }GROUP_DISMISS_RESPONSE, *PGROUP_DISMISS_RESPONSE;


//打开或关闭群聊天界面
typedef struct _SWITCH_GROUPTALK_REQUEST
{
    UCHAR			ucType;                      // 1 --ON   0 --OFF
    USHORT			usGroupID;
}SWITCH_GROUPTALK_REQUEST, *PSWITCH_GROUPTALK_REQUEST;


//这个是开始群聊的心跳返回数据，包括群公告和当前正在进行群聊的ID列表
struct TEAMCHAT_HEARTBEAT_RESPONSE
{
	struct TEAMCHAT_MEMBER_STATUS
	{
		UINT		id;
		CHAR		online;
	};
	
	//CHAR						note[200];
	UINT						count;
	TEAMCHAT_MEMBER_STATUS		onlineUsers[1];

	TEAMCHAT_HEARTBEAT_RESPONSE()
	{
		memset(this, 0, sizeof(*this));
	}
};

typedef struct _GET_NETINFO_REQUEST
{
	UINT			uiUserID;
}GET_NETINFO_REQUEST, *PGET_NETINFO_REQUEST;

typedef struct _GET_NETINFO_RESPONSE
{
	ULONG			ulIPAddr;
	ULONG			ulPort;
}GET_NETINFO_RESPONSE, *PGET_NETINFO_RESPONSE;

//心跳接口
typedef struct _KEEPALIVE_RESPONSE
{
	UINT uiNum;				//在线好友个数
	CHAR uiData[1];			//后面是好友的IMID组成的数组
}KEEPALIVE_RESPONSE, *PKEEPALIVE_RESPONSE;

typedef struct _FRIEND_STATE
{
	UINT    imId;
	CHAR   status;
	CHAR   szPicHead[25];  //头像图片路径
	CHAR   szDeviceType;
}FRIEND_STATE,*PFRIEND_STATE;


struct FAKE_TRANSFER_FILE_REQUEST
{
	int			nFriendId;
	int			nSize;
	DWORD		pParam;
	char		szName[MAX_PATH];
};

//要获取对方的IP，以便传输文件
struct FRIEND_IP_REQUEST
{
	char    isCancel;
	char		szName[MAX_PATH];	//文件名或者文件夹名
	ULONGLONG	    nSize;				//文件大小或文件夹大小

	FRIEND_IP_REQUEST()
	{
		memset(this,0 ,sizeof(*this));
	}
};

struct FRIEND_IP_RESPONSE
{
	unsigned int		ulIp;
	SHORT		sPort;
	int			nLastPos;		//上次传输的大小

	FRIEND_IP_RESPONSE()
	{
		memset(this,0 ,sizeof(*this));
	}
};

typedef struct _SVRNOTICETITLEMSG
{
	UINT    uiTitleLen;
	char    msgTilte[];
}SVRNOTICETITLEMSG;

typedef struct _SVRNOTCEABSTRACTMSG
{
	UINT    uiAbsLen;
	char    msgAbstract[];
}SVRNOTCEABSTRACTMSG;

typedef struct _SVRNOTICEURLMSG
{
	UINT    uiUrlLen;
	char    msgUrl[];
}SVRNOTICEURLMSG;


#pragma pack(pop)


#endif
