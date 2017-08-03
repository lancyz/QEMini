#pragma once

#include "IMConst.h"


class IMLocalDb
{
public:
	IMLocalDb(void);
	~IMLocalDb(void);

public:
	void InitTables();

//	//从本地数据库中导出好友分组列表
//	bool	GetGroupListFromDB(CFriendsPage * pPage);
//
	//从本地数据库中导出好友列表
	bool	GetFriendListFromDB(std::vector<BaseInfo*>* pUserList);
//
//	//从本地数据库中导出群列表
	bool	GetTeamListFromDB(std::vector<BaseInfo*>* pGroupList);
//
//	//从本地数据库中导出群详细信息列表
	bool	GetTeamInfoFromDB(GroupInfo* pTeam);
//	void	GetTeamMsgCountFromDB(CString & szTableName, UINT nTeamId, int& nCount);
//
//	bool SaveTeamSetToDB(int nID, int nSet);
//	bool GetTeamSetFromDB(IMTeamDraw * pTeam);
//	bool UpdateTeamSetFromDB(IMTeamDraw * pTeam);
//	bool ClearTeamSetFromDB();
//
//public:
//	//
//	bool   GetLastContact(vector<RecentInfo*> *recentList);
//
//	bool SaveFriendGroupToDB(CString strName);
//	bool SaveFriendGroupToDB(IMGroupDraw* pGroup);
//	bool DelFriendGroupToDB(CString strName);
//	bool DelFriendGroupToDB(IMGroupDraw* pGroup);
//	bool UpdateFriendGroupToDB(IMGroupDraw* pGroup);
//	bool ClearFriendGroup();
//
	//好友列表
	bool	SaveFriendToDB(UserInfo* pUser);
	bool	DelFriendToDB(UserInfo* pUser);
	bool	ClearFriend();
//	bool	UpdateFriendToDB(IMFriendDraw * pFriend);
//
//	bool	UpdateTeamFriendNameToDB(IMFriend* pFrinend);
//	bool    UpdateFriendNameToDB(IMFriend* pFriend);
//
	//群成员单个保存
	bool	SaveTeamMemberToDB(UINT nTeamId, UserInfo* pTeamFriend);
	//bool    SaveTeamMemberToDB(UINT nTeamId, UINT nFriendId, CString strFriendName, CString strImgPath);
	//bool	UpdateTeamMemberToDB(UINT nTeamId, UserInfo* pTeamFriend);
	bool   DelTeamMemberFormDB(UINT nTeamId, UINT nTeamFriendId);
	////群成员列表保存
	//bool	UpdateTeamMembersToDB(IMTeamDraw * pTeam);
	//bool	SaveTeamMembersToDB(IMTeamDraw * pTeam);
	//bool   ClearTeamMembersFormDB(IMTeamDraw * pTeam);
//
//	bool   GetTeamMemberName(int nFriendId, CString& strName);
//
//	//群基本信息保存
	bool	SaveTeamToDB(GroupInfo* pGroup);
	bool	DelTeamToDB(GroupInfo* pGroup);
	bool	ClearTeam();
//	bool	UpdateTeamToDB(IMTeamDraw * pTeam);
//
//	//消息验证 更新消息状态
//	bool	UpdateFriendMsgStatus(UINT nSendId, UINT nRecvId, UINT nMsgID, int nStatus);
//	bool	UpdateTeamMsgStatus(UINT nSendId, UINT nTeamId, UINT nMsgID, int nStatus);
//
//	bool	MsgExist(UINT nSendId, const char * szTableName, UINT nCheckID);
//
//	//好友聊天消息
	bool	SaveFriendMsgToDB(UINT nSendId, SStringT &szSendName, UINT nRecvId, SStringT & szRecvName, UINT nTime, 
		bool bDirection,const char * szMsg, int nLen, SStringT szTableName, UINT nCheckID = 0);
	bool	SaveTeamMsgToDB(UINT nSendId, SStringT & szSendName, UINT nTeamId, UINT nTime,const char * szMsg,
		int nLen, SStringT szTableName, UINT nCheckID = 0, bool bDirection = true);
//
//	bool	GetFriendMsgFromDB(CString & szTableName, UINT nMyId, UINT nFriendId, std::vector<FriendMsgRecord>  *pMsgList); 
//	bool	GetFriendMsgFromDB(CString &szTableName, UINT nMyId, UINT nFriendId, int nRecords, std::vector<FriendMsgRecord> * pMsgList,
//		UINT nPos = 0,UINT nStartTime = 0, UINT nEndTime = 0);
//	bool	GetFriendMsgFromDB(CString & szTableName, UINT nMyId, UINT nFriendId, CString strText, std::vector<FriendMsgRecord>  *pMsgList);
//
//	bool   GetTeamMsgFromDB(CString &szTableName, UINT nTeamId, std::vector<TeamMsgRecord> * pMsgList);
//	bool	GetTeamMsgFromDB(CString &szTableName, UINT nTeamId, int nRecords, std::vector<TeamMsgRecord> * pMsgList,
//		UINT nPos = 0,UINT nStartTime = 0, UINT nEndTime = 0);
//	bool    GetTeamMsgFromDB(CString &szTableName, UINT nTeamId, CString szText, std::vector<TeamMsgRecord> * pMsgList);
//
//	void	GetFriendMsgCountFromDB(CString & szTableName, UINT nMyId, UINT nFriendId, int& nCount);
//	void	GetNameFromDB(CString  strTableName,CString &strNAME, CString strFilePath);
//	void	GetTimeStampFromDB(CString  strTableName,CString &strTimeStamp, CString strFilePath);
//
//	bool	UpdateMsg(UINT nMsgID, CString strText, bool isTeam);
//	bool	DeleteRevokeMsg(UINT nMsgID, bool isTeam);
//	bool   GetMsgContextByMsgId(UINT nMsgID, CString& strText, bool isTeam);
//	bool   GetSendTimeByMsgId(UINT nMsgId,CString& sendTime,bool isTeam);
//
//	bool    DelFriendRecord(UINT nFriendId);
//	bool    DelTeamRecord(UINT nTeamId);
//
//	bool    InsertMyExpression(CString strGroup, CString strExpName, CString strFileName, CString strFilePath, CString strPos);
//	bool    InsertMyExpression(CString strGroup, CString strExpName, CString strFileName, CString strFilePath,int n);
//	bool    AheadInsertMyExpression(CString strGroup, CString strExpName, CString strFileName, CString strFilePath, CString timeStamp,int n);
//	bool    UpdateMyExpression(MyExpInfo* pExp);
//	bool    GetMyExpression(std::vector<MyExpInfo>** pMyExpList);
//	bool    DelMyExpression(MyExpInfo* pExp);
//	bool    DelMyExpression(CString strFileName);
//	//删除离职人员信息
//	bool    DeleteStructureInfoLeavePer(int imId);
//	//删除过期部门信息
//	bool    DeleteStructureInfoDept(int deptId);
//	//将组织结构数据写入数据库
//	bool    InsertStructureInfoDep(int deptId, int parentId,CString deptCode,CString deptName,CString deptFullId,CString deptFullName,int deptLayer);
//	bool    InsertStructureInfoPer(int imId,CString empNum,CString empName,CString empEngName,CString empDept,CString empHead,CString empPhone,CString empMail,int deptLayer);
//	bool   GetDeptFullNameFromDbByDeptId(int deptId,CString& deptFullName);
//	//从本地数据库获取组织结构信息
//	bool  GetInfoFromDbByParentId(int mParentId,std::vector<StructureInfo>& StructInfoShowList);
//	bool GetDeptInfoFromDbByDeptId(int mDeptId,StructureInfo* structDeptInfo);
//	bool GetPerInfoFromDbByImId(int mDeptId,StructureInfo& structDeptInfo);
//	//从本地数据库获取模糊查找结果
//	bool GetFuzzySearchResultByDept(CString szText,std::vector<IMFriend>& retList,int resultNumMax);
//	bool GetFuzzySearchResultByName(CString szText,std::vector<IMFriend>& retList,int resultNumMax);
//	bool GetFuzzySearchResultByNum(CString szText,std::vector<IMFriend>& retList,int resultNumMax);
//	bool GetFuzzySearchResultByEngName(CString szText,std::vector<IMFriend>& retList,int resultNumMax);
//	bool GetFuzzySearchResultByEmail(CString szText,std::vector<IMFriend>& retList,int resultNumMax);
//
//	 //群共享文件信息
//	 bool GetGroupFileDownloadInfo(int nId, CString& strPath, int& nStatus);
//	 bool SaveGroupFileDownloadInfo(int nId, int nImId, int nTeamId, CString strPath, int nStatus);
//	 bool UpdateGroupFileDownloadStatus(int nId, int nStatus);
//	 bool DeleteGroupFileDownloadInfo(int nId);
//
//	 bool GetGroupFileUploadInfo(int nId, CString& strPath, int& nStatus);
//	 bool SaveGroupFileUploadInfo(int nId, int nImId, int nTeamId, ULONGLONG nPos, CString strPath, int nStatus);
//	 bool UpdateGroupFileUploadStatus(int nId, int nStatus);
//	 bool DeleteGroupFileUploadInfo(int nId);
//
//	 //多人语音会议
//	 bool SaveMeetingInfo(CString strId, CString strTitle, CString strCode, int nType, CString strTime, UINT nOrganizerImId, int nMembers, CString strSummary);
//	 bool GetMeetingInfo(MeetInfo& meetInfo, CString strId);
//	 bool GetMeetingInfo(vector<MeetInfo>& meetInfo);
//	 bool UpdateMeetDescribe(CString strId, CString strText);
//	 bool UpdateMeetCount(CString strId, int nCount);
//	 bool DeleteMeetingInfo(CString strId);
//
//	 bool SaveMeetingMember(CString strId, UINT nImId, CString strName, CString strImgName, CString strImgPath);
//	 bool GetMeetingMember(vector<MemberInfo>& memberInfo, CString strId);
//	 bool GetMeetingMember(MemberInfo& memberInfo, UINT nImid, CString strId);
//	 bool DeleteMeetMember(UINT nImid, CString strId);
//	 //bool GetMeetingMember(vector<MemberInfo>& memberInfo, CString strId);
//	 //bool DeleteMeetMember();
//
//
//public:
//	friend int GetSingleMeetMemberCallBack(void* arg, int argc, char** pvalue, char** pname);
//	friend int GetMeetMemberCallBack(void* arg, int argc, char** pvalue, char** pname);
//	friend int GetMeetInfoCallBack(void* arg,int argc,char** pvalue,char** pname);
//	friend int GetMeetInfoListCallBack(void* arg,int argc,char** pvalue,char** pname);
//	friend int GetGroupFilePathCallback(void* arg,int argc,char** pvalue,char** pname);
//	friend int GetTeamMemberNameCallback(void* arg,int argc,char** pvalue,char** pname);
//	friend	bool   IsTableExist(string strName);
//	friend int GetServiceNameFromDBCallback(void* arg,int argc,char** pvalue,char** pname) ;

//	friend int GetServiceTimeFromDBCallback(void* arg,int argc,char** pvalue,char** pname) ;
//	friend int GetFriendLastContactCallBack(void* arg,int argc,char** pvalue,char** pname);
//	friend int GetTeamLastContactCallBack(void* arg,int argc,char** pvalue,char** pname);
	friend int GetFriendListCallback(void* arg,int argc,char** pvalue,char** pname);
	friend int GetTeamListCallback(void* arg,int argc,char** pvalue,char** pname);
	friend int GetTeamInfoCallback(void* arg,int argc,char** pvalue,char** pname);
//	friend int GetMsgCountFromDBCallback(void* arg,int argc,char** pvalue,char** pname);
//	friend int GetMyExpFromDBCallback(void* arg,int argc,char** pvalue,char** pname);
//	friend int GetMsgContextByMsgIdCallBack(void* arg,int argc,char** pvalue,char** pname) ;
//	friend int GetSendTimeByMsgIdCallBack(void* arg,int argc,char** pvalue,char** pname) ;
//	friend int GetTeamSetCallback(void* arg,int argc,char** pvalue,char** pname);
//
//	friend int GetDeptFullNameFromDbByDeptIdCallBack(void* arg,int argc,char** pvalue,char** pname);//根据部门部门Id获取名称
//	friend int GetDeptInfoFromDbByParentIdCallBack(void* arg,int argc,char** pvalue,char** pname);//根据上级部们获取所有下一级部门
//	friend int GetDeptInfoFromDbByDeptIdCallBack(void* arg,int argc,char** pvalue,char** pname);//根据部门ID获取部门信息
//	friend int GetImIdFromDbByEmpDeptCallBack(void* arg,int argc,char** pvalue,char** pname);//根据部门名称获取个人ImId
//	friend int GetPerInfoFromDbByImIdCallBack(void* arg,int argc,char** pvalue,char** pname);//根据ImId获取个人信息
//
//	friend int GetFuzzySearchResultByEachCallBack(void* arg,int argc,char** pvalue,char** pname);//通过部门名称模糊搜索匹配人员
};

