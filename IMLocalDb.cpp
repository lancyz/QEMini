#include "StdAfx.h"
#include "IMLocalDb.h"
#include "IMGlobal.h"
#include "hisqlite.h"
#include "utils.h"
#include <fstream>

IMLocalDb::IMLocalDb(void)
{
}


IMLocalDb::~IMLocalDb(void)
{
}

void IMLocalDb::InitTables()
{
	//进行初始化配置
	SStringT szTemp = SetCurDir(_T("temp\\")).c_str();
	BOOL bRet = PathFileExists(szTemp);
	if ( ! bRet )
	{
		bRet = CreateDirectory(szTemp, NULL);
		if ( ! bRet )
		{
			//AfxMessageBox("创建本地temp目录失败");
			return;
		}
	}

	SStringT szData = SetCurDir(_T("data\\")).c_str();
	bRet = PathFileExists(szData);

	if ( ! bRet )
	{
		bRet = CreateDirectory( szData, NULL );
		if ( ! bRet )
		{
			//AfxMessageBox("创建本地数据库文件夹失败");
			return;
		}
	}

	szData = szData + IMGlobal::Instance()->m_pMyself->EmpNo;
	bRet = PathFileExists(szData);

	if ( ! bRet )
	{
		bRet = CreateDirectory( szData, NULL );
		if ( ! bRet )
		{
			//AfxMessageBox("创建本地数据库文件夹失败");
			return;
		}
	}

	szData = szData + _T("\\imlocal.db");

	bRet = PathFileExists(szData);
	if ( ! bRet )
	{
		//创建文件
		std::ofstream outf(szData);
		outf.close();

		//初始化数据库文件
		Hisqlite::Instance()->SetDbFile(szData);
		if ( ! Hisqlite::Instance()->Hisqlite_createStaticTables() )
		{
			//AfxMessageBox("初始化本地数据库(静态表)失败");
		}

		if ( ! Hisqlite::Instance()->Hisqlite_createDynamicTables() )
		{
			//AfxMessageBox("初始化本地数据库(动态表)失败");
		}

		//Sysconf::Instance()->SaveToDb();
	}
	else
	{
		//初始化数据库文件
		Hisqlite::Instance()->SetDbFile(szData);
		Hisqlite::Instance()->Hisqlite_createDynamicTables();
	}
}

//bool   IsTableExist(string strName)
//{
//    char sql[200]= {0};
//    sprintf_s(sql,"SELECT * FROM %s", strName.c_str());
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//int GetGroupFilePathCallback(void* arg,int argc,char** pvalue,char** pname)
//{
//	char* pStr= (char *)arg;
//	if (pvalue[0]== NULL)
//	{
//		return -1;
//	}
//
//	strcpy(pStr, pvalue[0]);
//	strcat(pStr, "|");
//	strcat(pStr, pvalue[1]);
//
//	return 0;
//}
//
//bool  IMLocalDb::GetGroupFileDownloadInfo(int nId, CString& strPath, int& nStatus)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"SELECT FILE_PATH,DOWN_STATUS FROM GROUP_FILE_DOWNLOAD_INFO WHERE FILE_ID = %d",nId);
//
//	char str[512] = {0};
//	bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql, GetGroupFilePathCallback, str);
//	CString strTemp = str;
//	if(strTemp.GetLength() == 0)
//		return false;
//
//	CString strStatus;
//	
//	strPath = strTemp.Left( strTemp.Find('|') );
//	strStatus = strTemp.Right( strTemp.GetLength() - strTemp.Find('|') - 1);
//
//	nStatus = atoi(strStatus.GetString());
//
//	return bRet;
//}
//
//bool  IMLocalDb::SaveGroupFileDownloadInfo(int nId, int nImId, int nTeamId, CString strPath, int nStatus)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"INSERT INTO GROUP_FILE_DOWNLOAD_INFO VALUES(%d, %d, %d, '%s', %d)",nId, nImId, nTeamId, strPath, nStatus);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::UpdateGroupFileDownloadStatus(int nId, int nStatus)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"UPDATE GROUP_FILE_DOWNLOAD_INFO SET DOWN_STATUS = %d WHERE FILE_ID = %d", 
//		nStatus,
//		nId
//		);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool  IMLocalDb::DeleteGroupFileDownloadInfo(int nId)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"DELETE FROM GROUP_FILE_DOWNLOAD_INFO WHERE FILE_ID = %d",nId);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::GetGroupFileUploadInfo(int nId, CString& strPath, int& nStatus)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"SELECT FILE_PATH,DOWN_STATUS FROM GROUP_FILE_UPLOAD_INFO WHERE FILE_ID = %d",nId);
//
//	char str[512] = {0};
//	bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql, GetGroupFilePathCallback, str);
//	CString strTemp = str;
//	if(strTemp.GetLength() == 0)
//		return false;
//
//	CString strStatus;
//
//	strPath = strTemp.Left( strTemp.Find('|') );
//	strStatus = strTemp.Right( strTemp.GetLength() - strTemp.Find('|') - 1);
//
//	nStatus = atoi(strStatus.GetString());
//
//	return bRet;
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::SaveGroupFileUploadInfo(int nId, int nImId, int nTeamId, ULONGLONG nPos, CString strPath, int nStatus)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"INSERT INTO GROUP_FILE_UPLOAD_INFO VALUES(%d, %d, %d, %d, '%s', %d)",nId, nImId, nTeamId, nPos, strPath, nStatus);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::UpdateGroupFileUploadStatus(int nId, int nStatus)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"UPDATE GROUP_FILE_UPLOAD_INFO SET DOWN_STATUS = %d WHERE FILE_ID = %d", 
//		nStatus,
//		nId
//		);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::DeleteGroupFileUploadInfo(int nId)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"DELETE FROM GROUP_FILE_UPLOAD_INFO WHERE FILE_ID = %d",nId);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::SaveMeetingInfo(CString strId, CString strTitle, CString strCode, int nType, CString strTime, UINT nOrganizerImId, int nMembers, CString strSummary)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"INSERT INTO MEETING_HISTORY VALUES('%s', '%s', '%s', %d, '%s', %d, %d, '%s')",
//		strId, strCode, strTitle, nType, strTime, nOrganizerImId, nMembers, strSummary);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::GetMeetingInfo(MeetInfo& meetInfo, CString strId)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"SELECT * FROM MEETING_HISTORY WHERE ID = '%s'", strId);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,GetMeetInfoCallBack, &meetInfo);
//}
//
//bool IMLocalDb::GetMeetingInfo(vector<MeetInfo>& meetInfo)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"SELECT * FROM MEETING_HISTORY ORDER BY MEETING_TIME DESC");
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,GetMeetInfoListCallBack, &meetInfo);
//}
//
//bool IMLocalDb::UpdateMeetCount(CString strId, int nCount)
//{
//	char sql[1024]= {0};
//
//	sprintf_s(sql,"UPDATE MEETING_HISTORY SET MEMBER_COUNT = %d WHERE ID = '%s'",nCount, strId);
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
// bool IMLocalDb::UpdateMeetDescribe(CString strId, CString strText)
// {
//	 char sql[1024]= {0};
//
//	 sprintf_s(sql,"UPDATE MEETING_HISTORY SET MEETING_SUMMARY = '%s' WHERE ID = '%s'",strText, strId);
//	 return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
// }
//
//bool IMLocalDb::DeleteMeetingInfo(CString strId)
//{
//	char sql[1024]={0};
//	sprintf(sql, "DELETE FROM MEETING_HISTORY WHERE ID = '%s'", strId);
//
//	if(Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL))
//	{
//		sprintf(sql, "DELETE FROM MEETING_MEMBER WHERE ID = '%s'", strId);
//		if(Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL))
//			return true;
//	}
//
//	return false;
//}
//
//bool IMLocalDb::SaveMeetingMember(CString strId, UINT nImId, CString strName, CString strImgName, CString strImgPath)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"INSERT INTO MEETING_MEMBER VALUES('%s', %u, '%s', '%s', '%s')",
//		strId, nImId, strName, strImgName, strImgPath);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::GetMeetingMember(vector<MemberInfo>& memberInfo, CString strId)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"SELECT * FROM MEETING_MEMBER WHERE ID = '%s'", strId);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,GetMeetMemberCallBack, &memberInfo);
//}
//
//bool IMLocalDb::GetMeetingMember(MemberInfo& memberInfo, UINT nImid, CString strId)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"SELECT * FROM MEETING_MEMBER WHERE ID = '%s' AND IM_ID = %u", strId, nImid);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,GetSingleMeetMemberCallBack, &memberInfo);
//}
//
//bool IMLocalDb::DeleteMeetMember(UINT nImid, CString strId)
//{
//	char sql[1024]= {0};
//	sprintf(sql,"DELETE FROM MEETING_MEMBER WHERE ID = '%s' AND IM_ID = %u", strId, nImid);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
////bool IMLocalDb::DeleteMeetMember()
////{
////
////	return true;
////}
//
//bool   IMLocalDb::GetLastContact(vector<RecentInfo*> *recentList)
//{
//	char sql[1024]= {0};
//	string strTableName = IMUtil::GetCurFriendTableName();
//	int nMon = atoi(strTableName.substr(17, 2).c_str());
//	int nYear = atoi(strTableName.substr(13, 4).c_str());
//	if(nMon == 1)
//	{
//		nMon = 12;
//		nYear--;
//	}
//	else
//		nMon--;
//
//	sprintf((char*)strTableName.c_str(),"FRIENDS_TALK_%d%02d",nYear,nMon);
//
//	if(IsTableExist(strTableName))
//	{
//		sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME FROM  \
//					  (SELECT SEND_ID,RECV_ID,SEND_TIME FROM %s \
//					  UNION ALL \
//					  SELECT SEND_ID,RECV_ID,SEND_TIME FROM %s) \
//					  AS A \
//					  GROUP BY A.SEND_ID,A.RECV_ID \
//					  ORDER BY A.SEND_TIME DESC",
//					  IMUtil::GetCurFriendTableName(), strTableName.c_str());
//
//		Hisqlite::Instance()->Hisqlite_exec(sql,GetFriendLastContactCallBack,recentList);
//	}
//	else
//	{
//		sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME FROM %s ORDER BY SEND_TIME DESC", IMUtil::GetCurFriendTableName());
//		Hisqlite::Instance()->Hisqlite_exec(sql,GetFriendLastContactCallBack,recentList);
//	}
//
//	 ZeroMemory(sql, 1024);
//
//	 strTableName = IMUtil::GetCurTeamTableName();
//	 nMon = atoi(strTableName.substr(14, 2).c_str());
//	 nYear = atoi(strTableName.substr(10, 4).c_str());
//
//	 if(nMon == 1)
//	 {
//		 nMon = 12;
//		 nYear--;
//	 }
//	 else
//		 nMon--;
//
//	 sprintf((char*)strTableName.c_str(),"TEAMS_TALK_%d%02d",nYear,nMon);
//
//	 if(IsTableExist(strTableName))
//	 {
//		 sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_TIME FROM  \
//					   (SELECT IM_TEAM_ID,SEND_TIME FROM %s \
//					   UNION ALL \
//					   SELECT IM_TEAM_ID,SEND_TIME FROM %s) \
//					   AS A \
//					   GROUP BY A.IM_TEAM_ID ORDER BY A.SEND_TIME DESC",
//					   IMUtil::GetCurTeamTableName(), strTableName.c_str());
//
//		 Hisqlite::Instance()->Hisqlite_exec(sql,GetTeamLastContactCallBack,recentList);
//	 }
//	 else
//	 {
//		 sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_TIME FROM %s GROUP BY IM_TEAM_ID ORDER BY SEND_TIME DESC", IMUtil::GetCurTeamTableName());
//		 Hisqlite::Instance()->Hisqlite_exec(sql,GetTeamLastContactCallBack,recentList);
//	 }
//
//	 return true;
//}
//
//int GetMeetMemberCallBack(void* arg, int argc, char** pvalue, char** pname)
//{
//	if(argc< 5)
//		return -1;
//
//	vector<MemberInfo>* pInfo = (vector<MemberInfo>*)arg;
//
//	MemberInfo memberInfo;
//
//	//memberInfo.strId = pvalue[0];
//	memberInfo.nImId = atoi(pvalue[1]);
//	memberInfo.strName = SOUI::S_CA2W(pvalue[2]);
//	memberInfo.strHeadName = SOUI::S_CA2W(pvalue[3]);
//	memberInfo.strHeadPath = SOUI::S_CA2W(pvalue[4]);
//
//	pInfo->push_back(memberInfo);
//
//	return 0;
//}
//
//int GetSingleMeetMemberCallBack(void* arg, int argc, char** pvalue, char** pname)
//{
//	if(argc< 5)
//		return -1;
//
//	MemberInfo* pInfo = (MemberInfo*)arg;
//
//	//memberInfo.strId = pvalue[0];
//	pInfo->nImId = atoi(pvalue[1]);
//	pInfo->strName = SOUI::S_CA2W(pvalue[2]);
//	pInfo->strHeadName = SOUI::S_CA2W(pvalue[3]);
//	pInfo->strHeadPath = SOUI::S_CA2W(pvalue[4]);
//
//	return 0;
//}
//
//int GetMeetInfoListCallBack(void* arg, int argc, char** pvalue, char** pname)
//{
//	if(argc< 8)
//		return -1;
//
//	vector<MeetInfo>* pInfo = (vector<MeetInfo>*)arg;
//
//	MeetInfo meetInfo;
//
//	meetInfo.strId = pvalue[0];
//	meetInfo.strCode = pvalue[1];
//	meetInfo.strTitle = pvalue[2];
//	meetInfo.nType = atoi(pvalue[3]);
//	meetInfo.strTime = pvalue[4];
//	meetInfo.nimid = atoi(pvalue[5]);
//	meetInfo.nMember = atoi(pvalue[6]);
//	meetInfo.strText = pvalue[7];
//
//	pInfo->push_back(meetInfo);
//
//	return 0;
//}
//
//int GetMeetInfoCallBack(void* arg, int argc, char** pvalue, char** pname)
//{
//	if(argc< 8)
//		return -1;
//
//	MeetInfo* pInfo = (MeetInfo*)arg;
//
//	pInfo->strId = pvalue[0];
//	pInfo->strCode = pvalue[1];
//	pInfo->strTitle = pvalue[2];
//	pInfo->nType = atoi(pvalue[3]);
//	pInfo->strTime = pvalue[4];
//	pInfo->nimid = atoi(pvalue[5]);
//	pInfo->nMember = atoi(pvalue[6]);
//	pInfo->strText = pvalue[7];
//
//	return 0;
//}
//
//int GetFriendLastContactCallBack(void* arg,int argc,char** pvalue,char** pname)
//{
//    if(argc< 2)
//        return -1;
//
//    vector<RecentInfo*> *pList= (vector<RecentInfo*>  *)arg;
//
//	UINT nID = 0;
//	if(atoi(pvalue[0]) == IMGlobal::Instance()->m_pMyself->m_nId)
//		nID = atoi(pvalue[1]);
//	else
//		nID = atoi(pvalue[0]);
//
//    RecentInfo* pInfo = new RecentInfo;
//
//	pInfo->nID = nID;
//	pInfo->nLastTime = atoi(pvalue[2]);
//	pInfo->isTeam = false;	
//
//    pList->push_back(pInfo);
//
//    return 0;
//}
//
//int GetTeamLastContactCallBack(void* arg,int argc,char** pvalue,char** pname)
//{
//    if(argc< 2)
//        return -1;
//
//    vector<RecentInfo*> *pList= (vector<RecentInfo*>  *)arg;
//
//    RecentInfo* pInfo = new RecentInfo;
//    pInfo->nID = atoi(pvalue[0]);
//    pInfo->nLastTime = atoi(pvalue[1]);
//    pInfo->isTeam = true;	
//
//    pList->push_back(pInfo);
//
//    return 0;
//}
//
//int GetFriendGroupListCallback(void* arg,int argc,char** pvalue,char** pname)
//{
//    USES_CONVERSION;
//
//    CFriendsPage *pPage= (CFriendsPage  *)arg;
//
//    //如果查询结果小于9列，则直接返回-1,sqlite3_exec将返回 SQLITE_ABORT
//    if(argc< 1)
//        return -1;
//
//    IMGroupDraw * pGroup = new IMGroupDraw();
//    if(NULL== pGroup)	
//        return -1;
//    //组ID
//    //pGroup->m_nId= atoi(pvalue[0]);
//    //分组名
//    pGroup->m_szName = pvalue[0];
//
//    pPage->AddNode(pGroup);
//
//    return 0;
//}

int GetFriendListCallback(void* arg,int argc,char** pvalue,char** pname)
{
    std::vector<BaseInfo*> *pUserList= (std::vector<BaseInfo*>  *)arg;
    //std::string szPath(SkinMgr::Instance()->m_szWorkPath);
    //szPath += std::string("skin\\head\\");
    //std::string szTmp("");

    //如果查询结果小于9列，则直接返回-1,sqlite3_exec将返回 SQLITE_ABORT
    if(argc< 9)
        return -1;

	wchar_t szUnicode[1024] = {0};

    UserInfo* pUser = new UserInfo();
    if(NULL== pUser)	
        return -1;
    //好友ID
    pUser->Id= atoi(pvalue[0]);
    //好友名
	Utf82Unicode(pvalue[1], szUnicode, 1024);
    pUser->Name = szUnicode;

    ////头像文件名
   // szTmp = pvalue[2];
	szUnicode[0] = '\0';
	Utf82Unicode(pvalue[2], szUnicode, 1024);
    pUser->AvatarPath = szUnicode;

	pUser->AvatarId = SStringT().Format(_T("%u"), pUser->Id);

    //std::string szFile = szPath;
    //szFile.append(szTmp);

    //if(pFriend->m_nId == QE_ROBORT_ID)
    //    szFile = SkinMgr::Instance()->m_szWorkPath + "skin\\qe_robort.png";

    //pFriend->m_pImage = Bitmap::FromFile(A2OLE(szFile.c_str()));
    ////分组名
    //pFriend->m_szGroupName = pvalue[3];
    ////检查组是否存在
    //if ( ! pPage->FindGroup(pFriend->m_szGroupName) )
    //{
    //    IMGroupDraw * pGroup = new IMGroupDraw();
    //    pGroup->m_szName = pFriend->m_szGroupName;
    //    pPage->AddNode(pGroup);
    //}

    ////工号
	//Utf82Unicode(pvalue[4], szUnicode, 1024);
	pUser->EmpNo = S_CA2W(pvalue[4]);
    //pFriend->m_szEmpNo = pvalue[4];
    ////签名
	szUnicode[0] = '\0';
	Utf82Unicode(pvalue[5], szUnicode, 1024);
	pUser->Note = szUnicode;
    //pFriend->m_szNote = pvalue[5];
    ////英文名
	pUser->EnName = S_CA2W(pvalue[6]);
    //pFriend->m_szEnglish= pvalue[6];
    ////部门
	szUnicode[0] = '\0';
	Utf82Unicode(pvalue[7], szUnicode, 1024);
	pUser->Dept = szUnicode;
    //pFriend->m_szDept = pvalue[7];
    ////邮箱
	pUser->EMail = S_CA2W(pvalue[8]);
    //pFriend->m_szEmail = pvalue[8];
   
	pUserList->push_back(pUser);

    return 0;
}

//bool	IMLocalDb::GetGroupListFromDB(CFriendsPage * pPage)
//{
//    return Hisqlite::Instance()->Hisqlite_exec("SELECT * FROM FRIEND_GROUP",GetFriendGroupListCallback,pPage);
//}
//
////返回true代表导出好友列表成功，返回false代表导出好友列表失败
bool	IMLocalDb::GetFriendListFromDB(std::vector<BaseInfo*>* pUserList)
{
	//USES_CONVERSION;
	//IMFriendDraw * pRobort = new IMFriendDraw();
	//pRobort->m_bOnline = true;
	//pRobort->m_nId = QE_ROBORT_ID;
	//pRobort->m_szName = "讯耳机器人";
	//pRobort->m_szGroupName = "服务号";
	//pRobort->m_szImg = "skin\\qe_robort.png";
	//pRobort->LoadImage(A2OLE(SkinMgr::Instance()->m_szWorkPath + "skin\\qe_robort.png"));
	//pRobort->m_szEmpNo = "96786";
	//pRobort->m_szDept = "云安全技术部";
	//pRobort->m_szEmail = "";
	//pRobort->m_szNote = "欢迎光临我的解忧杂货铺";

	//if(pPage)
	//	pPage->AddNode(pRobort);

	return Hisqlite::Instance()->Hisqlite_exec("SELECT * FROM FRIENDS",GetFriendListCallback, pUserList);
}
//
//
int GetTeamListCallback(void* arg,int argc,char** pvalue,char** pname)
{
//    USES_CONVERSION;

    std::vector<BaseInfo*> *pGroupList= (std::vector<BaseInfo*>  *)arg;
    //std::string szTmp("");

    //如果查询结果小于8列，则直接返回-1,sqlite3_exec将返回 SQLITE_ABORT
    if (argc < 8)
        return -1;

    //std::string szPath(SkinMgr::Instance()->m_szWorkPath);
    //szPath += std::string("skin\\team_head.png");
    //Bitmap * pImage = Bitmap::FromFile(A2OLE(szPath.c_str()));

    GroupInfo* pTeam = new GroupInfo();
    if(NULL== pTeam)
        return -1;

	wchar_t szUnicode[1024] = {0};

    //群组ID
    pTeam->Id= atoi(pvalue[0]);
    //群组名
	Utf82Unicode(pvalue[1], szUnicode, 1024);
    pTeam->Name= szUnicode;
    //群主ID
    pTeam->MasterId= atoi(pvalue[2]);
    //当前群成员数
    pTeam->Members= atoi(pvalue[3]);
    ////当前群成员上限数
    //pTeam->m_nMax= atoi(pvalue[4]);
    //某些公共属性
    //群的分组名
    //m_szGroupName = pvalue[5];
    //pTeam->m_szGroupName = "我的群组";
   ////群的头像
	pTeam->AvatarId = _T("G0001");
	pTeam->AvatarPath = SetCurDir(_T("\\")).c_str();
	pTeam->AvatarPath.Append(L"Group.png");

    //pTeam->m_pImage = pImage;

    //pTeam->m_isTeam = true;

    ////检查组是否存在
    //if ( ! pPage->FindGroup( pTeam->m_szGroupName ) )
    //{
    //    IMGroupDraw * pGroup = new IMGroupDraw();
    //    pGroup->m_szName = pTeam->m_szGroupName;
    //    pPage->AddNode(pGroup);
    //}
    //群公告
	szUnicode[0] = '\0';
	Utf82Unicode(pvalue[7], szUnicode, 1024);
    pTeam->Note= szUnicode;
    //pPage->AddNode(pTeam);

	pGroupList->push_back(pTeam);

    return 0;
}
//
//int GetTeamMemberNameCallback(void* arg,int argc,char** pvalue,char** pname)
//{
//    char* pStr= (char *)arg;
//    if (pvalue[0]== NULL)
//    {
//        return -1;
//    }
//
//    strcpy(pStr, pvalue[0]);
//    return 0;
//}
//
//bool IMLocalDb::GetTeamMemberName(int nFriendId, CString& strName)
//{
//    char sql[100]= {0};
//    sprintf_s(sql,"SELECT IM_NAME FROM TEAM_MEMBERS_NEW WHERE IM_ID=%d GROUP BY IM_ID", nFriendId);
//
//    char strFriendName[100] = {0};
//    bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql, GetTeamMemberNameCallback, strFriendName);
//    strName = strFriendName;
//
//    return bRet;
//}
//
//返回true代表导出群组列表成功，返回false代表导出群组列表失败
bool	IMLocalDb::GetTeamListFromDB(std::vector<BaseInfo*>* pGroupList)
{
    return Hisqlite::Instance()->Hisqlite_exec("SELECT * FROM TEAMS",GetTeamListCallback,pGroupList);
}

//int GetTeamSetCallback(void* arg,int argc,char** pvalue,char** pname)
//{
//    IMTeamDraw* pTeam= (IMTeamDraw *)arg;
//    if (pvalue[0]== NULL)
//    {
//        pTeam->m_msgMode = 0;
//        return -1;
//    }
//
//    pTeam->m_msgMode = atoi(pvalue[0]);
//
//    return 0;
//}


//GetTeamInfoFromDB回调函数
int GetTeamInfoCallback(void* arg,int argc,char** pvalue,char** pname)
{
    GroupInfo * pTeam= (GroupInfo *)arg;
    //群公告
	wchar_t szUnicode[1024] = {0};
  
    //int	nId = 0;
    //CString szName("");
    //CString szImage("");
    //std::string szTmp("");

	UserInfo userInfo;

    //成员id
    userInfo.Id = atoi(pvalue[0]);
    //成员名
	Utf82Unicode(pvalue[1], szUnicode, 1024);
	userInfo.Name = szUnicode;
    //头像id
	szUnicode[0] = '\0';
	Utf82Unicode(pvalue[2], szUnicode, 1024);
	userInfo.AvatarPath = szUnicode;

	userInfo.AvatarId = SStringT().Format(_T("%d"), userInfo.Id);
    //szTmp= pvalue[2];
    //szImage = SkinMgr::Instance()->m_szWorkPath + CString("skin\\head\\") + szTmp.c_str();
    //szImage =  szTmp.c_str();

	pTeam->MemberList.push_back(userInfo);

    //if ( ! pTeam->AddMember(nId, szName, szImage) )
    //{
    //    //return -1;
    //}
    return 0;
}

//返回true代表导出群成员列表成功，返回false代表导出群成员列表失败
bool	IMLocalDb::GetTeamInfoFromDB(GroupInfo* pTeam)
{
    char sql[100]= {0};
    sprintf_s(sql,"SELECT IM_ID,IM_NAME,IM_HEAD_PATH FROM TEAM_MEMBERS WHERE IM_TEAM_ID= %d",pTeam->Id);

    return Hisqlite::Instance()->Hisqlite_exec(sql,GetTeamInfoCallback,pTeam);
}

//bool IMLocalDb::SaveTeamSetToDB(int nID, int nSet)
//{
//    char sql[100]= {0};
//    sprintf_s(sql, "INSERT OR REPLACE INTO TEAMS_SET  VALUES(%d, %d)", nID, nSet);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool IMLocalDb::GetTeamSetFromDB(IMTeamDraw * pTeam)
//{
//    char sql[100]= {0};
//    sprintf_s(sql,"SELECT SET_TEAM FROM TEAMS_SET WHERE ID_TEAM = %d", pTeam->m_nId);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,GetTeamSetCallback, pTeam);
//}
//
//bool IMLocalDb::UpdateTeamSetFromDB(IMTeamDraw * pTeam)
//{
//    char sql[100]= {0};
//    sprintf_s(sql,"UPDATE TEAMS_SET SET SET_TEAM = %d WHERE ID_TEAM = %d", pTeam->m_msgMode, pTeam->m_nId);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL, NULL);
//}
//
//bool IMLocalDb::ClearTeamSetFromDB()
//{
//    return Hisqlite::Instance()->Hisqlite_exec("DELETE FROM TEAMS_SET  WHERE 1 = 1",NULL,NULL);
//}
//

bool	IMLocalDb::DelFriendToDB(UserInfo* pUser)
{
	if ( ! pUser )
		return false;

	char sql[1024]= {0};

	sprintf_s(sql,"DELETE FROM FRIENDSNEW  WHERE IM_ID = %d", pUser->Id);
	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
}

bool	IMLocalDb::ClearFriend()
{
	return Hisqlite::Instance()->Hisqlite_exec("DELETE FROM FRIENDSNEW WHERE IM_GROUP_NAME != '服务号'",NULL,NULL);
}

//bool	IMLocalDb::SaveFriendGroupToDB(CString strName)
//{
//	if(strName.Compare("我的群组") == 0 || strName.Compare("最近联系人") == 0 || strName.Compare("待办事项") == 0|| strName.Compare("讯耳机器人") == 0|| strName.Compare("宇龙科技") == 0)
//		return false;
//
//	char sql[1024]= {0};
//
//	sprintf_s(sql,"INSERT INTO FRIEND_GROUP  VALUES('%s')",strName);
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}

//bool	IMLocalDb::SaveFriendGroupToDB(IMGroupDraw * pGroup)
//{
//    if ( ! pGroup )
//        return false;
//
//    if(pGroup->m_szName.Compare("我的群组") == 0 || pGroup->m_szName.Compare("最近联系人") == 0  || pGroup->m_szName.Compare("待办事项") == 0 || pGroup->m_szName.Compare("讯耳机器人") == 0|| pGroup->m_szName.Compare("宇龙科技") == 0)
//        return false;
//
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"INSERT INTO FRIEND_GROUP  VALUES('%s')",pGroup->m_szName);
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool	IMLocalDb::DelFriendGroupToDB(CString strName)
//{
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"DELETE FROM FRIEND_GROUP WHERE IM_NAME = '%s'",strName);
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//
//bool	IMLocalDb::DelFriendGroupToDB(IMGroupDraw * pGroup)
//{
//    if ( ! pGroup )
//        return false;
//
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"DELETE FROM FRIEND_GROUP WHERE IM_NAME = '%s'",pGroup->m_szName);
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool IMLocalDb::ClearFriendGroup()
//{
//    return Hisqlite::Instance()->Hisqlite_exec("DELETE FROM FRIEND_GROUP WHERE 1 = 1",NULL,NULL);
//}
//
//bool	IMLocalDb::UpdateFriendGroupToDB(IMGroupDraw * pGroup)
//{
//    if ( ! pGroup )
//        return false;
//
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"UPDATE FRIEND_GROUP IM_NAME = '%s')",pGroup->m_szName);
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}


bool	IMLocalDb::SaveFriendToDB(UserInfo* pUser)
{
    if ( ! pUser )
        return false;

    SStringT strPath = pUser->AvatarPath;
    //if(pUser->Id != QE_ROBORT_ID && strPath.Find("\\") != -1)
    //{
    //    int nIndex = strPath.ReverseFind('\\');
    //    strPath = strPath.Right(strPath.GetLength() - nIndex - 1);
    //}

    SStringT sql;
	sql.Format(_T("INSERT OR REPLACE INTO FRIENDS  VALUES(%d,'%s','%s','%s','%s','%s','%s','%s','%s')"), 
		pUser->Id, pUser->Name, strPath, _T("groupName"), pUser->EmpNo, pUser->Note, pUser->EnName, pUser->Dept, pUser->EMail);

	char utf8[1024] = {0};
	Unicode2Utf8(sql.GetBuffer(0), utf8, 1024);

    return Hisqlite::Instance()->Hisqlite_exec(utf8,NULL,NULL);
}

//bool	IMLocalDb::UpdateFriendToDB(IMFriendDraw * pFriend)
//{
//    if ( ! pFriend )
//        return false;
//
//    char sql[1024]= {0};
//
//    std::string szPath(SkinMgr::Instance()->m_szWorkPath);
//    szPath += std::string("skin\\head\\");
//
//    CString szFile = szPath.c_str();
//    szFile.Append(pFriend->m_szImg);
//
//	sprintf_s(sql,"UPDATE FRIENDSNEW SET IM_NAME = '%s',IM_HEAD_PATH='%s',IM_GROUP_NAME='%s',\
//				  IM_EMPNO = '%s',IM_NOTE ='%s',IM_ENAME='%s',IM_DEPT='%s',IM_EMAIL='%s' WHERE IM_ID = %d" ,
//				  pFriend->m_szName,pFriend->m_szImg,
//				  pFriend->m_szGroupName,pFriend->m_szEmpNo,pFriend->m_szNote,pFriend->m_szEnglish,pFriend->m_szDept,pFriend->m_szEmail,
//				  pFriend->m_nId);
//
//	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool	IMLocalDb::UpdateTeamFriendNameToDB(IMFriend* pFrinend)
//{
//    CString tableName;
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//    tableName.Format("TEAM_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    char sql[1024]= {0};
//
//    sprintf_s(sql, 
//        "UPDATE %s \
//        SET send_name = '%s' \
//        WHERE send_id = %d and send_name = 'Ahri'", 
//        tableName, pFrinend->m_szName, pFrinend->m_nId
//        );
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool	IMLocalDb::UpdateFriendNameToDB(IMFriend* pFrinend)
//{
//    CString tableName;
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//    tableName.Format("FRIENDS_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    char sql[1024]= {0};
//
//    sprintf_s(sql, 
//        "UPDATE %s \
//        SET send_name = '%s' \
//        WHERE send_id = %d and send_name = 'Ahri'", 
//        tableName, pFrinend->m_szName, pFrinend->m_nId
//        );
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//

bool	IMLocalDb::SaveTeamMemberToDB(UINT nTeamId, UserInfo* pTeamFriend)
{
	if ( ! pTeamFriend )
		return false;

	SStringT sql;
	sql.Format(_T("INSERT OR REPLACE INTO TEAM_MEMBERS  VALUES(%d,%d,'%s','%s')"),
		nTeamId, pTeamFriend->Id, pTeamFriend->Name, pTeamFriend->AvatarPath);

	char utf8[1024] = {0};
	Unicode2Utf8(sql.GetBuffer(0), utf8, 1024);

	return Hisqlite::Instance()->Hisqlite_exec(utf8,NULL,NULL);
}

//bool	IMLocalDb::SaveTeamMemberToDB(UINT nTeamId, UINT nFriendId, CString strFriendName, CString strImgPath)
//{
//    char sql[200]= {0};
//
//    sprintf_s(sql,"INSERT OR REPLACE INTO TEAM_MEMBERS_NEW  VALUES(%d,%d,'%s','%s')",
//        nTeamId, nFriendId, strFriendName, strImgPath);
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}

bool   IMLocalDb::DelTeamMemberFormDB(UINT nTeamId, UINT nTeamFriendId)
{
	char sql[200]= {0};

	sprintf_s(sql,"DELETE FROM TEAM_MEMBERS WHERE IM_TEAM_ID = %d AND IM_ID = %d",
		nTeamId, nTeamFriendId);
	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
}

//bool	IMLocalDb::UpdateTeamMemberToDB(UINT nTeamId, IMFriend * pTeamFriend)
//{
//    if ( ! pTeamFriend )
//        return false;
//
//    char sql[200]= {0};
//
//    sprintf_s(sql,"UPDATE TEAM_MEMBERS_NEW SET IM_TEAM_ID = %d,IM_ID = %d,IM_NAME = '%s',IM_HEAD_PATH = '%s')",
//        nTeamId, pTeamFriend->m_nId, pTeamFriend->m_szName,pTeamFriend->m_szImg);
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool	IMLocalDb::UpdateFriendMsgStatus(UINT nSendId, UINT nRecvId, UINT nMsgID, int nStatus)
//{
//    char * sql =NULL;
//    sql	= new char[100];
//
//    if(!sql)
//        return false;
//
//    CString tableName;
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//    tableName.Format("FRIENDS_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    //szMsg 要进行转义处理
//    sprintf_s(sql, 100, "UPDATE %s SET STATUS=%d WHERE CHECK_ID=%u",
//        tableName, nStatus, nMsgID);
//
//    bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//    delete[] sql;
//
//    return bRet;
//}
//
//bool	IMLocalDb::UpdateTeamMsgStatus(UINT nSendId, UINT nTeamId, UINT nMsgID, int nStatus)
//{
//    char * sql =NULL;
//    sql	= new char[100];
//
//    if(!sql)
//        return false;
//
//    CString tableName;
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//    tableName.Format("TEAM_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    //szMsg 要进行转义处理
//    sprintf_s(sql, 100, "UPDATE %s SET STATUS=%d WHERE CHECK_ID=%d",
//        tableName, nStatus, nMsgID);
//
//    bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//    delete[] sql;
//
//    return bRet;
//}

bool	IMLocalDb::SaveFriendMsgToDB(UINT nSendId, SStringT &szSendName, UINT nRecvId,SStringT & szRecvName,  UINT nTime, bool bDirection, const char * szMsg, int nLen, SStringT szTableName, UINT nCheckID)
{
    std::string strMsg(szMsg, nLen);
    //if(strMsg.find("%#{~d%#}~") != -1)
    //    return true;

    //消息状态 0：未收到，1：已收到
    //接收的信息都默认填已收到
    int nStatus = 1;
    if(bDirection)
        nStatus = 0;

    SStringT cStrMsg = S_CA2W(strMsg.c_str());
    cStrMsg.Replace(L"'",L"''");
    //szMsg 要进行转义处理

	SStringT strSql;
	strSql.Format(_T("INSERT INTO %s(SEND_ID,SEND_NAME,RECV_ID,RECV_NAME,SEND_TIME,RECV_TIME,DIRECTION,MSG_DETAIL,STATUS,CHECK_ID) VALUES(%d, '%s', %d, '%s',%d, %d, %d, '%s', %d, %u)"),
		szTableName,nSendId, szSendName, nRecvId,szRecvName, nTime, 0, bDirection,cStrMsg , nStatus, nCheckID);

	const int bufLen = nLen + 300;
	char* utf8 = new char[bufLen];
	Unicode2Utf8(strSql.GetBuffer(0), utf8, bufLen);

    bool bRet = Hisqlite::Instance()->Hisqlite_exec(utf8,NULL,NULL);
    if ( !  bRet )
    {
        Hisqlite::Instance()->Hisqlite_createDynamicTables();
        bRet = Hisqlite::Instance()->Hisqlite_exec(utf8,NULL,NULL);
    }

	delete[] utf8;

    return bRet;
}

//int MsgExistCallback(void* arg,int argc,char** pvalue,char** pname) 
//{  
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    if (pvalue[0]== NULL)
//        return -1;
//    memcpy(arg, pvalue[0], strlen(pvalue[0]) );
//    return 0;  //callback函数正常返回0   
//}
//
//bool	IMLocalDb::MsgExist(UINT nSendId, const char * szTableName, UINT nCheckID)
//{
//    char * sql =NULL;
//    sql	= new char[100];
//
//    sprintf(sql, "SELECT COUNT(CHECK_ID) FROM %s WHERE CHECK_ID = %u AND SEND_ID = %d", szTableName, nCheckID, nSendId);
//
//    bool ret = Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//
//    int nCount = 0;
//    char pValue[10] = {0};
//    bool result = Hisqlite::Instance()->Hisqlite_exec(sql,MsgExistCallback, pValue);
//
//    if(result)
//        nCount = atoi(pValue);
//    else
//        nCount = 0;
//
//    return nCount;
//}

bool	IMLocalDb::SaveTeamMsgToDB(UINT nSendId, SStringT & szSendName, UINT nTeamId, UINT nTime,const char * szMsg, int nLen, SStringT szTableName, UINT nCheckID, bool bDirection)
{
    std::string strMsg(szMsg, nLen);
    //if(strMsg.find("%#{~d%#}~") != -1)
    //    return true;

    char * sql = new char[nLen + 300];

    //消息状态 0：未收到，1：已收到
    //接收的信息都默认填已收到
    //int nStatus = 1;
    //if( IMGlobal::Instance()->m_pMyself->m_nId == nSendId)
    //	nStatus = 0;

    int nStatus = 1;
    if(bDirection)
        nStatus = 0;
    //if(nCheckID == 0)
    //	nStatus = 1;

	SStringT strSql;
	strSql.Format(_T("INSERT INTO %s(SEND_ID,SEND_NAME,IM_TEAM_ID,SEND_TIME,RECV_TIME,MSG_DETAIL, STATUS, CHECK_ID) VALUES (%d,'%s', %d, %d, %d, '%s', %d, %u)"),
		szTableName, nSendId, szSendName, nTeamId, nTime, 0, S_CA2W(strMsg.c_str()), nStatus, nCheckID);

	const int bufLen = nLen + 300;
	char* utf8 = new char[bufLen];
	Unicode2Utf8(strSql.GetBuffer(0), utf8, bufLen);

    bool bRet = Hisqlite::Instance()->Hisqlite_exec(utf8,NULL,NULL);
    if ( !  bRet )
    {
        Hisqlite::Instance()->Hisqlite_createDynamicTables();
        bRet = Hisqlite::Instance()->Hisqlite_exec(utf8,NULL,NULL);
    }

    delete [] utf8;

    return bRet;
}

//
//
////GetFriendMsgFromDB函数的回调函数
//int GetFriendMsgFromDBCallback(void* arg,int argc,char** pvalue,char** pname) 
//{  
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    std::vector<FriendMsgRecord> *msgList = (std::vector<FriendMsgRecord> *) arg;
//    if (/*argc!= 8 ||*/ pvalue[0]== NULL)
//        return -1;
//    //FriendMsgRecord(UINT   sendId,UINT   recvId,string sendName,string recvName,bool direction,UINT   ntime,string szmsg)
//    int nStatus = 1;
//    UINT nCheckID = 0;
//
//    if(argc == 9)
//    {
//        if(pvalue[8] == NULL)
//            nStatus = 1;
//        else
//            nStatus = atoi(pvalue[8]);
//
//        if(pvalue[7] != NULL)
//            nCheckID = atoi(pvalue[7]);
//    }
//
//    msgList->push_back(FriendMsgRecord(atoi(pvalue[0]),atoi(pvalue[1]),pvalue[3],pvalue[4],atoi(pvalue[5])== 1,atoi(pvalue[2]),pvalue[6],nCheckID,nStatus));
//    return 0;  //callback函数正常返回0   
//}
//
//bool	IMLocalDb::GetFriendMsgFromDB(CString & szTableName, UINT nMyId, UINT nFriendId, std::vector<FriendMsgRecord>  *pMsgList)
//{
//    char sql[1000]= {0};
//
//    sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL,CHECK_ID,STATUS FROM %s  \
//                  WHERE ((SEND_ID= %d and RECV_ID= %d) OR (SEND_ID= %d and RECV_ID= %d)) \
//                  ORDER BY MSG_ID DESC LIMIT 0,30",
//                  szTableName,nMyId,nFriendId,nFriendId,nMyId);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,GetFriendMsgFromDBCallback,pMsgList);
//}
//
//bool	IMLocalDb::GetFriendMsgFromDB(CString & szTableName, UINT nMyId, UINT nFriendId, CString strText, std::vector<FriendMsgRecord>  *pMsgList)
//{
//    char sql[1000]= {0};
//
//    string strTableName = szTableName;
//    int nMon = atoi(strTableName.substr(17, 2).c_str());
//    int nYear = atoi(strTableName.substr(13, 4).c_str());
//
//    if(nMon == 1)
//    {
//        nMon = 12;
//        nYear--;
//    }
//    else
//        nMon--;
//
//    sprintf((char*)strTableName.c_str(),"FRIENDS_TALK_%d%02d",nYear,nMon);
//
//    if(IsTableExist(strTableName))
//    {
//        sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM  \
//                      (SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM %s \
//                      UNION ALL \
//                      SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM %s) \
//                      AS A \
//                      WHERE ((A.SEND_ID= %d and A.RECV_ID= %d) OR (A.SEND_ID= %d and A.RECV_ID= %d)) AND (A.MSG_DETAIL LIKE '%%%s%%' OR A.SEND_NAME = '%s')",
//                      szTableName,strTableName.c_str(), nMyId,nFriendId,nFriendId,nMyId,strText,strText);
//    }
//    else
//    {
//        sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM %s  \
//                      WHERE ((SEND_ID= %d and RECV_ID= %d) OR (SEND_ID= %d and RECV_ID= %d)) AND (MSG_DETAIL LIKE '%%%s%%' OR SEND_NAME = '%s')",
//                      szTableName,nMyId,nFriendId,nFriendId,nMyId,strText,strText);
//    }
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,GetFriendMsgFromDBCallback,pMsgList);
//}
//
//bool	IMLocalDb::GetFriendMsgFromDB(CString & szTableName, UINT nMyId, UINT nFriendId, int nRecords, std::vector<FriendMsgRecord>  *pMsgList,
//    UINT nPos,UINT nStartTime, UINT nEndTime)
//{
//    char sql[1000]= {0};
//
//    if(nRecords != 0 && nStartTime== 0 && nEndTime== 0)
//    {
//        string strTableName = szTableName;
//        int nMon = atoi(strTableName.substr(17, 2).c_str());
//        int nYear = atoi(strTableName.substr(13, 4).c_str());
//
//        if(nMon == 1)
//        {
//            nMon = 12;
//            nYear--;
//        }
//        else
//            nMon--;
//
//        sprintf((char*)strTableName.c_str(),"FRIENDS_TALK_%d%02d",nYear,nMon);
//
//        if(IsTableExist(strTableName))
//        {
//            sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL,MSG_ID FROM \
//                          (SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL,MSG_ID FROM %s  \
//                          UNION ALL \
//                          SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL,MSG_ID FROM %s)  \
//                          AS A \
//                          WHERE ((A.SEND_ID= %d and A.RECV_ID= %d) or (A.SEND_ID= %d and A.RECV_ID= %d)) \
//                          ORDER BY A.SEND_TIME DESC,MSG_ID DESC LIMIT %d,%d",
//                          szTableName, strTableName.c_str(), nMyId,nFriendId,nFriendId,nMyId,nPos,nRecords);
//        }
//        else
//        {
//            sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM %s  \
//                          WHERE ((SEND_ID= %d and RECV_ID= %d) or (SEND_ID= %d and RECV_ID= %d)) ORDER BY MSG_ID DESC LIMIT %d,%d",
//                          szTableName,nMyId,nFriendId,nFriendId,nMyId,nPos,nRecords);
//        }
//    }
//    else if(nRecords == 0)
//    {
//        string strTableName = szTableName;
//        int nMon = atoi(strTableName.substr(17, 2).c_str());
//        int nYear = atoi(strTableName.substr(13, 4).c_str());
//
//        time_t now = time(NULL);
//        struct tm * t = localtime(&now);
//        int nCurMon = t->tm_mon + 1;
//        int nCurYear = t->tm_year + 1900;
//
//        if(nCurMon == nMon)
//        {
//            sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM %s  \
//                          WHERE ((SEND_ID= %d and RECV_ID= %d) or (SEND_ID= %d and RECV_ID= %d))  and SEND_TIME > %d \
//                          ORDER BY MSG_ID DESC",
//                          szTableName,nMyId,nFriendId,nFriendId,nMyId, nStartTime);
//        }
//        else if((nCurMon == 1 && nMon == 12) || (nCurMon == nMon + 1))
//        {
//            sprintf((char*)strTableName.c_str(),"FRIENDS_TALK_%d%02d",nCurYear,nCurMon);
//
//            if(IsTableExist(strTableName))
//            {
//                sprintf_s(sql,"SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM \
//                              (SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM %s  \
//                              UNION ALL \
//                              SELECT SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM %s)  \
//                              AS A \
//                              WHERE ((A.SEND_ID= %d and A.RECV_ID= %d) or (A.SEND_ID= %d and A.RECV_ID= %d)) and A.SEND_TIME > %d \
//                              ORDER BY A.SEND_TIME DESC",
//                              szTableName, strTableName.c_str(), nMyId,nFriendId,nFriendId,nMyId, nStartTime);
//            }
//        }
//        else
//            return false;
//    }
//    else
//    {
//        sprintf_s(sql,"SELECT  SEND_ID,RECV_ID,SEND_TIME,SEND_NAME,RECV_NAME,DIRECTION,MSG_DETAIL FROM  %s  \
//                      WHERE ((SEND_ID= %d and RECV_ID= %d) or (SEND_ID= %d and RECV_ID= %d)) and (SEND_TIME BETWEEN %d AND %d) \
//                      ORDER BY MSG_ID DESC LIMIT %d,%d", 
//                      szTableName,nMyId,nFriendId,nFriendId,nMyId,nStartTime,nEndTime,nPos,nRecords);
//    }
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,GetFriendMsgFromDBCallback,pMsgList);
//}
//
//void	IMLocalDb::GetNameFromDB(CString  strTableName,CString &strName, CString strFilePath)
//{
//    char sql[1000]= {0};
//    char chRet[100] = {0};
//
//    if(IsTableExist(strTableName.GetString()))
//    {
//        sprintf_s(sql,"SELECT NAME FROM %s WHERE FILE_NAME='%s'",
//                      strTableName, strFilePath);
//        bool result = Hisqlite::Instance()->Hisqlite_exec(sql,GetServiceNameFromDBCallback,chRet );
//        strName.Format(_T("%s"),chRet);
//    }
//
//    return;
//}
//
//void	IMLocalDb::GetTimeStampFromDB(CString  strTableName,CString &strTimeStamp, CString strFilePath)
//{
//    char sql[1000]= {0};
//    char chRet[100] = {0};
//
//    if(IsTableExist(strTableName.GetString()))
//    {
//        sprintf_s(sql,"SELECT TIME FROM %s WHERE FILE_NAME='%s'",
//            strTableName, strFilePath);
//        bool result = Hisqlite::Instance()->Hisqlite_exec(sql,GetServiceTimeFromDBCallback,chRet );
//        strTimeStamp.Format(_T("%s"),chRet);
//    }
//
//    return;
//}
//
//void	IMLocalDb::GetFriendMsgCountFromDB(CString & szTableName, UINT nMyId, UINT nFriendId, int& nCount)
//{
//    char sql[1000]= {0};
//
//    string strTableName = szTableName;
//    int nMon = atoi(strTableName.substr(17, 2).c_str());
//    int nYear = atoi(strTableName.substr(13, 4).c_str());
//
//    if(nMon == 1)
//    {
//        nMon = 12;
//        nYear--;
//    }
//    else
//        nMon--;
//
//    sprintf((char*)strTableName.c_str(),"FRIENDS_TALK_%d%d",nYear,nMon);
//
//    if(IsTableExist(strTableName))
//    {
//        sprintf_s(sql,"SELECT COUNT(MSG_DETAIL) FROM \
//                      ( \
//                      SELECT MSG_DETAIL,SEND_ID,RECV_ID  \
//                      FROM  %s UNION ALL \
//                      SELECT MSG_DETAIL,SEND_ID,RECV_ID \
//                      FROM  %s \
//                      ) \
//                      AS A \
//                      WHERE ((A.SEND_ID= %d and A.RECV_ID= %d) or (A.SEND_ID= %d and A.RECV_ID= %d))",
//                      szTableName, strTableName.c_str(), nMyId,nFriendId,nFriendId,nMyId);
//    }
//    else
//    {
//        sprintf_s(sql,"SELECT COUNT(MSG_DETAIL) \
//                      FROM %s  \
//                      WHERE ((SEND_ID= %d and RECV_ID= %d) or (SEND_ID= %d and RECV_ID= %d))",
//                      szTableName,nMyId,nFriendId,nFriendId,nMyId);
//    }
//
//
//    char pValue[10] = {0};
//    bool result = Hisqlite::Instance()->Hisqlite_exec(sql,GetMsgCountFromDBCallback, pValue);
//
//    if(result)
//        nCount = atoi(pValue);
//    else
//        nCount = 0;
//}
//
//void	IMLocalDb::GetTeamMsgCountFromDB(CString & szTableName, UINT nTeamId, int& nCount)
//{
//    char sql[1000]= {0};
//
//    string strTableName = szTableName;
//    int nMon = atoi(strTableName.substr(14, 2).c_str());
//    int nYear = atoi(strTableName.substr(10, 4).c_str());
//
//    if(nMon == 1)
//    {
//        nMon = 12;
//        nYear--;
//    }
//    else
//        nMon--;
//
//    sprintf((char*)strTableName.c_str(),"TEAM_TALK_%d%d",nYear,nMon);
//
//    if(IsTableExist(strTableName))
//    {
//        sprintf_s(sql,"SELECT COUNT(MSG_DETAIL) FROM \
//                      ( \
//                      SELECT MSG_DETAIL,IM_TEAM_ID  \
//                      FROM  %s UNION ALL \
//                      SELECT MSG_DETAIL,IM_TEAM_ID \
//                      FROM  %s \
//                      ) \
//                      AS A \
//                      WHERE A.IM_TEAM_ID = %d",
//                      szTableName, strTableName.c_str(), nTeamId);
//    }
//    else
//    {
//        sprintf_s(sql,"SELECT COUNT(MSG_DETAIL) \
//                      FROM %s \
//                      WHERE IM_TEAM_ID = %d",
//                      szTableName, nTeamId);
//    }
//
//    char pValue[10] = {0};
//    bool result = Hisqlite::Instance()->Hisqlite_exec(sql,GetMsgCountFromDBCallback, pValue);
//
//    if(result)
//        nCount = atoi(pValue);
//    else
//        nCount = 0;
//}
//
//int GetServiceTimeFromDBCallback(void* arg,int argc,char** pvalue,char** pname) 
//{
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    if (pvalue[0]== NULL)
//        return false;
//    memcpy(arg, pvalue[0], strlen(pvalue[0]) );
//    return true;
//}
//
//int GetServiceNameFromDBCallback(void* arg,int argc,char** pvalue,char** pname) 
//{
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    if (pvalue[0]== NULL)
//        return false;
//    memcpy(arg, pvalue[0], strlen(pvalue[0]) );
//    return true;
//}
//
//int GetMsgCountFromDBCallback(void* arg,int argc,char** pvalue,char** pname) 
//{  
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    if (pvalue[0]== NULL)
//        return -1;
//    memcpy(arg, pvalue[0], strlen(pvalue[0]) );
//    return 0;  //callback函数正常返回0   
//}
//
//
////GetTeamMsgFromDB函数的回调函数
//int GetTeamMsgFromDBCallback(void* arg,int argc,char** pvalue,char** pname) 
//{  
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    std::vector<TeamMsgRecord> *msgList = (std::vector<TeamMsgRecord> *) arg;
//    if (/*argc!= 5 ||*/ pvalue[0]== NULL)
//        return -1;
//
//    int nStatus = 1;
//    UINT nCheckID = 0;
//
//    if(argc == 7)
//    {
//        if(pvalue[6] == NULL)
//            nStatus = 1;
//        else
//            nStatus = atoi(pvalue[6]);
//
//        if(pvalue[5] != NULL)
//            nCheckID = atoi(pvalue[5]);
//    }
//
//
//    msgList->push_back(TeamMsgRecord(atoi(pvalue[0]),atoi(pvalue[1]),pvalue[2],atoi(pvalue[3]),pvalue[4], nCheckID, nStatus));
//    return 0;  //callback函数正常返回0   
//}
//
//bool   IMLocalDb::GetTeamMsgFromDB(CString &szTableName, UINT nTeamId, std::vector<TeamMsgRecord> * pMsgList)
//{
//    char sql[1000]= {0};
//
//    sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL,CHECK_ID,STATUS FROM %s \
//                  WHERE IM_TEAM_ID= %d \
//                  ORDER BY MSG_ID DESC LIMIT 0,20" , 
//                  szTableName, nTeamId);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,GetTeamMsgFromDBCallback,pMsgList);
//}
//
//bool   IMLocalDb::GetTeamMsgFromDB(CString &szTableName, UINT nTeamId, CString szText, std::vector<TeamMsgRecord> * pMsgList)
//{
//    char sql[1000]= {0};
//
//    string strTableName = szTableName;
//    int nMon = atoi(strTableName.substr(14, 2).c_str());
//    int nYear = atoi(strTableName.substr(10, 4).c_str());
//
//    if(nMon == 1)
//    {
//        nMon = 12;
//        nYear--;
//    }
//    else
//        nMon--;
//
//    sprintf((char*)strTableName.c_str(),"TEAM_TALK_%d%02d",nYear,nMon);
//
//    if(IsTableExist(strTableName))
//    {
//        sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL FROM \
//                      ( \
//                      SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL,MSG_ID  \
//                      FROM  %s UNION ALL \
//                      SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL,MSG_ID \
//                      FROM  %s \
//                      ) \
//                      AS A \
//                      WHERE A.IM_TEAM_ID= %d AND (A.MSG_DETAIL LIKE '%%%s%%' OR A.SEND_NAME = '%s')" , 
//                      szTableName, strTableName.c_str(), nTeamId, szText, szText);
//    }
//    else
//    {
//        sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL FROM %s \
//                      WHERE IM_TEAM_ID= %d AND (MSG_DETAIL LIKE '%%%s%%' OR SEND_NAME = '%s')" , 
//                      szTableName, nTeamId, szText, szText);
//    }
//
//
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,GetTeamMsgFromDBCallback,pMsgList);
//}
//
//bool	IMLocalDb::GetTeamMsgFromDB(CString &szTableName, UINT nTeamId, int nRecords, std::vector<TeamMsgRecord> * pMsgList,
//    UINT nPos,UINT nStartTime, UINT nEndTime)
//{
//    char sql[1000]= {0};
//
//    if(nRecords != 0 && nStartTime== 0 && nEndTime== 0)
//    {
//        string strTableName = szTableName;
//        int nMon = atoi(strTableName.substr(14, 2).c_str());
//        int nYear = atoi(strTableName.substr(10, 4).c_str());
//
//        if(nMon == 1)
//        {
//            nMon = 12;
//            nYear--;
//        }
//        else
//            nMon--;
//
//        sprintf((char*)strTableName.c_str(),"TEAM_TALK_%d%02d",nYear,nMon);
//
//        if(IsTableExist(strTableName))
//        {
//            sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL FROM \
//                          ( \
//                          SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL,MSG_ID  \
//                          FROM  %s UNION ALL \
//                          SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL,MSG_ID \
//                          FROM  %s \
//                          ) \
//                          AS A \
//                          WHERE A.IM_TEAM_ID = %d \
//                          ORDER BY A.SEND_TIME DESC LIMIT %d,%d",
//                          szTableName, strTableName.c_str(), nTeamId, nPos, nRecords);
//        }
//        else
//        {
//            sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL  FROM  %s WHERE IM_TEAM_ID= %d \
//                          ORDER BY MSG_ID DESC LIMIT %d,%d",
//                          szTableName,nTeamId,nPos,nRecords);
//        }
//    }
//    else if(nRecords == 0)
//    {
//        string strTableName = szTableName;
//        int nMon = atoi(strTableName.substr(14, 2).c_str());
//        int nYear = atoi(strTableName.substr(10, 4).c_str());
//
//        time_t now = time(NULL);
//        struct tm * t = localtime(&now);
//        int nCurMon = t->tm_mon + 1;
//        int nCurYear = t->tm_year + 1900;
//
//        if(nCurMon == nMon)
//        {
//            sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL  FROM  %s \
//                          WHERE IM_TEAM_ID= %d and SEND_TIME > %d \
//                          ORDER BY MSG_ID DESC",
//                          szTableName,nTeamId,nStartTime);
//        }
//        else if((nCurMon == nMon + 1) || (nCurMon == 1 && nMon == 12))
//        {
//            sprintf((char*)strTableName.c_str(),"TEAM_TALK_%d%02d",nCurYear,nCurMon);
//
//            if(IsTableExist(strTableName))
//            {
//                sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL FROM \
//                              ( \
//                              SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL,MSG_ID  \
//                              FROM  %s UNION ALL \
//                              SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL,MSG_ID \
//                              FROM  %s \
//                              ) \
//                              AS A \
//                              WHERE A.IM_TEAM_ID = %d and A.SEND_TIME > %d \
//                              ORDER BY A.SEND_TIME DESC",
//                              szTableName, strTableName.c_str(), nTeamId, nStartTime);
//            }
//        }
//        else
//            return false;
//    }
//    else
//    {
//        sprintf_s(sql,"SELECT IM_TEAM_ID,SEND_ID,SEND_NAME,SEND_TIME,MSG_DETAIL  FROM  %s WHERE IM_TEAM_ID= %d  \
//                      and SEND_TIME BETWEEN %d and %d ORDER BY MSG_ID DESC LIMIT %d,%d",
//                      szTableName,nTeamId,nStartTime,nEndTime,nPos,nRecords);
//    }
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,GetTeamMsgFromDBCallback,pMsgList);
//}
//
//bool   IMLocalDb::ClearTeamMembersFormDB(IMTeamDraw * pTeam)
//{
//    if(pTeam == NULL)
//        return false;
//
//    char sql[200]= {0};
//
//    sprintf_s(sql,"DELETE TEAM_MEMBERS_NEW WHERE IM_TEAM_ID = %d",
//        pTeam->m_nId);
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//
//bool	IMLocalDb::SaveTeamMembersToDB(IMTeamDraw * pTeam)
//{
//    IMTeamDraw::team_member_list_iter_type iter, end(pTeam->m_memberList.end());
//    for ( iter = pTeam->m_memberList.begin(); iter != end; ++ iter )
//    {
//        if ( ! SaveTeamMemberToDB(pTeam->m_nId, iter->second) )
//            UpdateTeamMemberToDB(pTeam->m_nId, iter->second);
//    }
//
//    return true;
//}
//
//bool	IMLocalDb::UpdateTeamMembersToDB(IMTeamDraw * pTeam)
//{
//    IMTeamDraw::team_member_list_iter_type iter, end(pTeam->m_memberList.end());
//    for ( iter = pTeam->m_memberList.begin(); iter != end; ++ iter )
//    {
//        UpdateTeamMemberToDB(iter->first, iter->second);
//    }
//
//    return true;
//}
//
//
bool	IMLocalDb::DelTeamToDB(GroupInfo* pGroup)
{
	if ( ! pGroup )
		return false;

	char sql[1024]= {0};
	sprintf_s(sql,"DELETE FROM TEAMS WHERE IM_TEAM_ID = %d",pGroup->Id);

	return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
}

bool	IMLocalDb::ClearTeam()
{
	return Hisqlite::Instance()->Hisqlite_exec("DELETE FROM TEAMS WHERE 1 = 1",NULL,NULL);
}


bool	IMLocalDb::SaveTeamToDB(GroupInfo* pTeam)
{
	if ( ! pTeam )
		return false;

	SStringT sql;
	sql.Format(_T("INSERT OR REPLACE INTO TEAMS  VALUES(%d,'%s',%d,%d,%d,'%s','%s','%s')"),
		pTeam->Id, pTeam->Name,pTeam->MasterId,pTeam->Members, 0, _T("GroupName"),pTeam->AvatarPath, pTeam->Note);

	char utf8[1024] = {0};
	Unicode2Utf8(sql.GetBuffer(0), utf8, 1024);

	return Hisqlite::Instance()->Hisqlite_exec(utf8,NULL,NULL);
}
//
//bool	IMLocalDb::UpdateTeamToDB(IMTeamDraw * pTeam)
//{
//    if ( ! pTeam )
//        return false;
//
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"UPDATE TEAMS SET IM_TEAM_NAME = '%s',TEAM_OWNER_ID=%d,TEAM_MEMBERS=%d,\
//                  TEAM_LIMIT = %d,TEAM_GROUP_NAME ='%s',TEAM_HEAD_PATH='%s',TEAM_DESC='%s' WHERE IM_TEAM_ID = %d",
//                  pTeam->m_szName,pTeam->m_nMasterId,
//                  pTeam->m_memberList.size(),pTeam->m_nMax,pTeam->m_szGroupName,pTeam->m_szImg,pTeam->m_szNotice,
//                  pTeam->m_nId);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool   IMLocalDb::DelFriendRecord(UINT nFriendId)
//{
//    char sql[1024]= {0};
//
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//    CString szTableName;
//    szTableName.Format("FRIENDS_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    std::string strTableName = szTableName;
//    int nMon = atoi(strTableName.substr(17, 2).c_str());
//    int nYear = atoi(strTableName.substr(13, 4).c_str());
//
//    if(nMon == 1)
//    {
//        nMon = 12;
//        nYear--;
//    }
//    else
//        nMon--;
//
//    sprintf((char*)strTableName.c_str(),"FRIENDS_TALK_%d%02d",nYear,nMon);
//
//    int nMyId = IMGlobal::Instance()->m_pMyself->m_nId;
//
//    sprintf_s(sql,"DELETE FROM %s WHERE (SEND_ID = %d  AND RECV_ID = %d) OR (SEND_ID = %d  AND RECV_ID = %d)",
//        szTableName,
//        nFriendId,
//        nMyId,
//        nMyId,
//        nFriendId);
//
//    Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//    ZeroMemory(sql, 1024);
//
//    sprintf_s(sql,"DELETE FROM %s WHERE (SEND_ID = %d  AND RECV_ID = %d) OR (SEND_ID = %d  AND RECV_ID = %d)",
//        strTableName.c_str(),
//        nFriendId,
//        nMyId,
//        nMyId,
//        nFriendId);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool   IMLocalDb::DelTeamRecord(UINT nTeamId)
//{
//    char sql[1024]= {0};
//
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//    CString szTableName;
//    szTableName.Format("TEAM_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    std::string strTableName = szTableName;
//    int nMon = atoi(strTableName.substr(14, 2).c_str());
//    int nYear = atoi(strTableName.substr(10, 4).c_str());
//
//    if(nMon == 1)
//    {
//        nMon = 12;
//        nYear--;
//    }
//    else
//        nMon--;
//
//    sprintf((char*)strTableName.c_str(),"TEAM_TALK_%d%02d",nYear,nMon);
//
//    sprintf_s(sql,"DELETE FROM %s WHERE IM_TEAM_ID = %d",
//        szTableName,
//        nTeamId);
//
//    Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//    ZeroMemory(sql, 1024);
//
//    sprintf_s(sql,"DELETE FROM %s WHERE IM_TEAM_ID = %d",
//        strTableName.c_str(),
//        nTeamId);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//int GetMyExpFromDBCallback(void* arg,int argc,char** pvalue,char** pname) 
//{  
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    std::vector<MyExpInfo> *myExpList = (std::vector<MyExpInfo> *) arg;
//    if (/*argc!= 5 ||*/ pvalue[0]== NULL)
//        return -1;
//
//    myExpList->push_back(MyExpInfo(atoi(pvalue[0]), pvalue[1],pvalue[2], pvalue[3],  pvalue[4], atoi(pvalue[5]), pvalue[6], atoi(pvalue[7])));
//    return 0;  //callback函数正常返回0   
//}
//
//
//bool    IMLocalDb::GetMyExpression(std::vector<MyExpInfo>** pMyExpList)
//{
//    char sql[1000]= {0};
//
//    sprintf_s(sql,"SELECT * FROM MY_EXPRESSION ORDER BY TIME DESC");
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql, GetMyExpFromDBCallback, *pMyExpList);
//}
//
//
//bool   IMLocalDb::UpdateMyExpression(MyExpInfo* pExp)
//{
//    char sql[1024]= {0};
//
//    sprintf_s(sql,	"update MY_EXPRESSION SET GROUP_NAME = %s, NAME = %s, FILE_NAME = %s, FILE_PATH = %s, TIME = %u, POS = %s, ISNEW = 0 \
//                    where ID = %u",
//        pExp->strGroup, pExp->strExpName, pExp->strFileName, pExp->strFilePath, pExp->nUploadTime, pExp->strPos, pExp->nID);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool    IMLocalDb::InsertMyExpression(CString strGroup, CString strExpName, CString strFileName, CString strFilePath, CString strPos)
//{
//    char sql[1024]= {0};
//
//    ULONG uTime = (ULONG)time(0);
//
//    sprintf_s(sql,"insert into MY_EXPRESSION( ID, GROUP_NAME, NAME, FILE_NAME, FILE_PATH, TIME, POS, ISNEW ) values(%u, '%s', '%s', '%s', '%s', %u, '%s', 1)",
//        uTime, strGroup, strExpName, strFileName, strFilePath, uTime, strPos);
//
//    TRACE("uTime:------------>%u\r\n",uTime);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool    IMLocalDb::AheadInsertMyExpression(CString strGroup, CString strExpName, CString strFileName, CString strFilePath, CString timeStamp,int n)
//{
//    char sql[1024]= {0};
//    USES_CONVERSION;
//
//    CString timeStampId;
//    if(strFileName.GetLength()<20)
//    {
//        timeStampId=strFileName.Left(12);
//    }
//    else
//    {
//        ULONG uTime = (ULONG)time(0);
//        timeStampId.Format(_T("%u%02d"),uTime,n);
//    }
//
//    //ULONG64 id = _ttoi64  (timeStamp);
//    //UINT uTime=(UINT) time(0);
//
//    sprintf_s(sql,"insert into MY_EXPRESSION( ID, GROUP_NAME, NAME, FILE_NAME, FILE_PATH, TIME, ISNEW ) values(%s, '%s', '%s', '%s', '%s', '%s', 1)",
//        timeStampId, strGroup, strExpName, strFileName, strFilePath, timeStamp );
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool    IMLocalDb::InsertMyExpression(CString strGroup, CString strExpName, CString strFileName, CString strFilePath,int n)
//{
//    char sql[1024]= {0};
//    USES_CONVERSION;
//
//    CString timeStampId;
//    if(strFileName.GetLength()<20)
//    {
//        timeStampId=strFileName.Left(12);
//    }
//    else
//    {
//        ULONG uTime = (ULONG)time(0);
//        timeStampId.Format(_T("%u%02d"),uTime,n);
//    }
//    
//    //ULONG64 id = _ttoi64  (timeStamp);
//    UINT uTime=(UINT) time(0);
//
//
//    sprintf_s(sql,"insert into MY_EXPRESSION( ID, GROUP_NAME, NAME, FILE_NAME, FILE_PATH, TIME, ISNEW ) values(%s, '%s', '%s', '%s', '%s', %u, 1)",
//        timeStampId, strGroup, strExpName, strFileName, strFilePath, uTime );
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool    IMLocalDb::DelMyExpression(MyExpInfo* pExp)
//{
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"DELETE FROM MY_EXPRESSION WHERE ID = %u", pExp->nID);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool    IMLocalDb::DelMyExpression(CString strFileName)
//{
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"DELETE FROM MY_EXPRESSION WHERE FILE_NAME = '%s'", strFileName);
//
//    return Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool	IMLocalDb::UpdateMsg(UINT nMsgID, CString strText, bool isTeam)
//{
//    char * sql =NULL;
//    sql	= new char[1024];
//
//    if(!sql)
//        return false;
//
//    CString tableName;
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//
//    if(!isTeam)
//        tableName.Format("FRIENDS_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//    else
//        tableName.Format("TEAM_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    //szMsg 要进行转义处理
//    sprintf_s(sql, 1024, "UPDATE %s SET MSG_DETAIL='%s' WHERE CHECK_ID=%u",
//        tableName, strText, nMsgID);
//
//    bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//    delete[] sql;
//
//    return bRet;
//}
//
//bool	IMLocalDb::DeleteRevokeMsg(UINT nMsgID, bool isTeam)
//{
//    char * sql =NULL;
//    sql	= new char[1024];
//
//    if(!sql)
//        return false;
//
//    CString tableName;
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//
//    if(!isTeam)
//        tableName.Format("FRIENDS_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//    else
//        tableName.Format("TEAM_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    //szMsg 要进行转义处理
//    sprintf_s(sql, 1024, "DELETE FROM %s WHERE CHECK_ID=%u",
//        tableName, nMsgID);
//
//    bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//    delete[] sql;
//
//    return bRet;
//}
//
//bool IMLocalDb::GetMsgContextByMsgId(UINT nMsgID, CString& strText, bool isTeam)
//{
//    char * sql =NULL;
//    sql	= new char[1024];
//
//    if(!sql)
//        return false;
//
//    CString tableName;
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//
//    if(!isTeam)
//        tableName.Format("FRIENDS_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//    else
//        tableName.Format("TEAM_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    //szMsg 要进行转义处理
//    sprintf_s(sql, 1024, "SELECT MSG_DETAIL FROM %s  WHERE CHECK_ID=%u",
//        tableName, nMsgID);
//
//    char chRet[2048] = {0};
//    bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql,GetMsgContextByMsgIdCallBack, chRet);
//    strText.Format(_T("%s"),chRet);
//
//    delete[] sql;
//
//    return bRet;
//}
//
//int GetMsgContextByMsgIdCallBack(void* arg,int argc,char** pvalue,char** pname) 
//{  
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    if (/*argc!= 5 ||*/ pvalue[0]== NULL)
//        return -1;
//
//    memcpy(arg, pvalue[0], strlen(pvalue[0]) );
//    return 0;  //callback函数正常返回0   
//}
//
//bool IMLocalDb::GetSendTimeByMsgId(UINT nMsgID, CString& sendTime, bool isTeam)
//{
//    char * sql =NULL;
//    sql	= new char[1024];
//
//    if(!sql)
//        return false;
//
//    CString tableName;
//    time_t now = time(NULL);
//    struct tm * t = localtime(&now);
//
//    if(!isTeam)
//        tableName.Format("FRIENDS_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//    else
//        tableName.Format("TEAM_TALK_%d%02d", t->tm_year + 1900, t->tm_mon + 1);
//
//    //szMsg 要进行转义处理
//    sprintf_s(sql, 1024, "SELECT SEND_TIME FROM %s  WHERE CHECK_ID=%u",
//        tableName, nMsgID);
//
//    char chRet[100] = {0};
//    bool bRet = Hisqlite::Instance()->Hisqlite_exec(sql,GetSendTimeByMsgIdCallBack, chRet);
//    sendTime.Format(_T("%s"),chRet);
//
//    delete[] sql;
//
//    return bRet;
//}
//
//int GetSendTimeByMsgIdCallBack(void* arg,int argc,char** pvalue,char** pname) 
//{  
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    if (/*argc!= 5 ||*/ pvalue[0]== NULL)
//        return -1;
//
//    memcpy(arg, pvalue[0], strlen(pvalue[0]) );
//    return 0;  //callback函数正常返回0   
//}
//
//bool    IMLocalDb::InsertStructureInfoDep(int deptId, int parentId,CString deptCode,CString deptName,CString deptFullId,CString deptFullName,int deptLayer)
//{
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"INSERT INTO STRUCTURE_INFO_DEP (DEPT_ID,PARENT_ID,DEPT_CODE,DEPT_NAME,DEPT_FULL_ID,DEPT_FULL_NAME,DEPT_LAYER)VALUES(%d,%d,'%s','%s','%s','%s',%d)",
//        deptId, parentId, deptCode,deptName,deptFullId,deptFullName,deptLayer);
//
//    return Structuresqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool    IMLocalDb::DeleteStructureInfoDept(int deptId)
//{
//	char sql[1024]= {0};
//
//	sprintf_s(sql,"DELETE FROM STRUCTURE_INFO_DEP WHERE DEPT_ID=%d",deptId);
//
//	return Structuresqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool    IMLocalDb::DeleteStructureInfoLeavePer(int imId)
//{
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"DELETE FROM STRUCTURE_INFO_PER WHERE IM_ID=%d",imId);
//
//    return Structuresqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool    IMLocalDb::InsertStructureInfoPer(int imId,CString empNum,CString empName,CString empEngName,CString empDept,CString empHead,CString empPhone,CString empMail,int deptLayer)
//{
//    char sql[1024]= {0};
//
//    sprintf_s(sql,"INSERT INTO STRUCTURE_INFO_PER (IM_ID,EMP_NUM,EMP_NAME,EMP_ENGNAME,EMP_DEPT,EMP_HEAD,EMP_MPHONE,EMP_MAIL,DEPT_LAYER)VALUES(%d,'%s','%s','%s','%s','%s','%s','%s',%d)",
//        imId,empNum,empName,empEngName,empDept,empHead,empPhone,empMail,deptLayer);
//
//    return Structuresqlite::Instance()->Hisqlite_exec(sql,NULL,NULL);
//}
//
//bool IMLocalDb::GetDeptFullNameFromDbByDeptId(int deptId,CString& deptFullName)
//{
//    char sql[1024]= {0};
//    char strDeptFullName[100]={0};
//    //获取子级部门信息
//    sprintf_s(sql,1024,"SELECT DEPT_FULL_NAME FROM STRUCTURE_INFO_DEP WHERE DEPT_ID=%d",deptId);
//    bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetDeptFullNameFromDbByDeptIdCallBack,strDeptFullName);
//
//    deptFullName.Format("%s",strDeptFullName);
//
//    return bRet;
//}
//
//int  GetDeptFullNameFromDbByDeptIdCallBack(void* arg,int argc,char** pvalue,char** pname)
//{
//    //select查询结果可能为空，此时pvalue[0]为NULL
//    if (/*argc!= 5 ||*/ pvalue[0]== NULL)
//        return -1;
//
//    memcpy(arg,pvalue[0],strlen(pvalue[0]));
//
//    return 0;  //callback函数正常返回0   
//}
//
//bool IMLocalDb::GetInfoFromDbByParentId(int mParentId,std::vector<StructureInfo>& mStructInfoShowList)
//{
//    //获取上级部门的部门全名称，用于查找该部门下的人员
//    CString deptFullName;
//    IMLocalDb db;
//    db.GetDeptFullNameFromDbByDeptId(mParentId,deptFullName);
//
//    CStructureInfo mStructInfo;
//    std::string strDeptFullName=mStructInfo.UTF8ToGBK((const std::string &)deptFullName.GetString());
//    std::string strDeptFullNameUft8=mStructInfo.GBKToUTF8((const std::string &)strDeptFullName);
//
//    char sql[1024]= {0};
//    ////获取部门下的人员信息
//    std::vector<StructureInfo> mPerInfoList;
//    sprintf_s(sql,1024,"SELECT IM_ID FROM STRUCTURE_INFO_PER WHERE EMP_DEPT='%s' ORDER BY IM_ID",strDeptFullNameUft8.c_str());
//    bool bRet1 = Structuresqlite::Instance()->Hisqlite_exec(sql,GetImIdFromDbByEmpDeptCallBack, &mPerInfoList);
//
//    if(mPerInfoList.size()&&(strDeptFullName.compare("宇龙科技"))!=0)
//        mStructInfo.AddPerInfoToShowList(mParentId,&mPerInfoList,&mStructInfoShowList);
//
//    //获取子级部门信息
//    std::vector<StructureInfo> mDeptInfoList;
//    sprintf_s(sql,1024,"SELECT DEPT_ID  FROM STRUCTURE_INFO_DEP WHERE PARENT_ID=%d ORDER BY DEPT_CODE",mParentId);
//    bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetDeptInfoFromDbByParentIdCallBack, &mDeptInfoList);
//
//    if(mDeptInfoList.size())
//        mStructInfo.AddDeptInfoToShowList(strDeptFullName.c_str(),&mDeptInfoList,&mStructInfoShowList);
//
//    return bRet*bRet1;
//}
//
// int  GetDeptInfoFromDbByParentIdCallBack(void* arg,int argc,char** pvalue,char** pname)
// {
//     //select查询结果可能为空，此时pvalue[0]为NULL
//     if (/*argc!= 5 ||*/ pvalue[0]== NULL)
//         return -1;
//
//     USES_CONVERSION;
//
//     int mDeptId=atoi(pvalue[0]);
//     StructureInfo structDeptInfo;
//     ZeroMemory(&structDeptInfo, sizeof(structDeptInfo));
////	 structDeptInfo=NULL;
//
//     IMLocalDb db;
//     db.GetDeptInfoFromDbByDeptId(mDeptId,&structDeptInfo);
//
//     std::vector<StructureInfo>* StructInfoShowList=(std::vector<StructureInfo>*) arg;
//
//	 //判断该部门及子部门是否有人员，对于空部门不显示
//	 CString deptFullName=structDeptInfo.deptFullName.c_str();
//	 std::vector<IMFriend> retList;
//	 int resultNumMax=1;
//	 bool mRet=db.GetFuzzySearchResultByDept(deptFullName,retList,resultNumMax);
//
//     //找到对应位置插入结构信息
//	 if(retList.size()==1)
//	   StructInfoShowList->push_back(structDeptInfo);
//
//     return 0;  //callback函数正常返回0   
// }
//
// int  GetImIdFromDbByEmpDeptCallBack(void* arg,int argc,char** pvalue,char** pname)
// {
//     //select查询结果可能为空，此时pvalue[0]为NULL
//     if (/*argc!= 5 ||*/ pvalue[0]== NULL)
//         return -1;
//
//     USES_CONVERSION;
//
//     int imId=atoi(pvalue[0]);
//     StructureInfo structDeptInfo;
//     //	 structDeptInfo=NULL;
//
//     IMLocalDb db;
//     db.GetPerInfoFromDbByImId(imId,structDeptInfo);
//
//     std::vector<StructureInfo>* StructInfoShowList=(std::vector<StructureInfo>*) arg;
//     StructInfoShowList->push_back(structDeptInfo);
//
//     return 0;  //callback函数正常返回0   
// }
//
// bool IMLocalDb::GetDeptInfoFromDbByDeptId(int mDeptId,StructureInfo* structDeptInfo)
// {
//     char sql[1024]= {0};
//    
//     sprintf_s(sql,1024,"SELECT * FROM STRUCTURE_INFO_DEP WHERE DEPT_ID=%d",mDeptId);
//     bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetDeptInfoFromDbByDeptIdCallBack, structDeptInfo);
//
//     return bRet;
// }
//
// int  GetDeptInfoFromDbByDeptIdCallBack(void* arg,int argc,char** pvalue,char** pname)
// {
//     //select查询结果可能为空，此时pvalue[0]为NULL
//     if (argc!= 7 || pvalue[0]== NULL)
//         return -1;
//
//     USES_CONVERSION;
//     StructureInfo* mStructDeptInfo=(StructureInfo*)arg;
//
//     mStructDeptInfo->isShow=true;
//      mStructDeptInfo->isOpen=false;
//     mStructDeptInfo->isDep=true;
//     mStructDeptInfo->deptLayer=atoi(pvalue[6]);
//
//     CStructureInfo convert;
//     mStructDeptInfo->deptId=atoi(pvalue[0]);
//     mStructDeptInfo->parentId=atoi(pvalue[1]);
//     mStructDeptInfo->deptName=convert.UTF8ToGBK((const std::string &)pvalue[3]);;
//     mStructDeptInfo->deptFullName=convert.UTF8ToGBK((const std::string &)pvalue[5]);
//
//     mStructDeptInfo->imId=0;
//     mStructDeptInfo->empName="\0";
//     mStructDeptInfo->empDept="\0";
//     mStructDeptInfo->empHead="\0";
//
//     mStructDeptInfo->empNum="\0";
//     mStructDeptInfo->empEngName="\0";
//     mStructDeptInfo->empPhone="\0";
//      mStructDeptInfo->empEmail="\0";
//
//     return 0;  //callback函数正常返回0   
// }
//
// bool IMLocalDb::GetPerInfoFromDbByImId(int imId,StructureInfo& structDeptInfo)
// {
//     char sql[1024]= {0};
//
//     sprintf_s(sql,1024,"SELECT * FROM STRUCTURE_INFO_PER WHERE IM_ID=%d",imId);
//     bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetPerInfoFromDbByImIdCallBack, &structDeptInfo);
//
//     return bRet;
// }
//
// int  GetPerInfoFromDbByImIdCallBack(void* arg,int argc,char** pvalue,char** pname)
// {
//     //select查询结果可能为空，此时pvalue[0]为NULL
//     if (argc!= 9 ||pvalue[0]== NULL)
//         return -1;
//
//     USES_CONVERSION;
//     StructureInfo* mStructDeptInfo=(StructureInfo*)arg;
//
//     mStructDeptInfo->isShow=true;
//     mStructDeptInfo->isOpen=false;
//     mStructDeptInfo->isDep=false;
//     mStructDeptInfo->deptLayer=atoi(pvalue[8]);
//
//     mStructDeptInfo->deptId=0;
//     mStructDeptInfo->parentId=0;
//     mStructDeptInfo->deptName ="\0";
//     mStructDeptInfo->deptFullName="\0";
//
//     CStructureInfo convert;
//     mStructDeptInfo->imId=atoi(pvalue[0]);
//     mStructDeptInfo->empName=convert.UTF8ToGBK((const std::string &)pvalue[2]);
//     mStructDeptInfo->empDept=convert.UTF8ToGBK((const std::string &)pvalue[4]);
//     mStructDeptInfo->empHead=pvalue[5];
//
//     mStructDeptInfo->empNum=pvalue[1];
//     mStructDeptInfo->empEngName=pvalue[3];
//	 if( mStructDeptInfo->imId!=41999)//屏蔽江峰总电话
//		mStructDeptInfo->empPhone=pvalue[6];
//     mStructDeptInfo->empEmail=pvalue[7];
//
//     return 0;  //callback函数正常返回0   
// }
//
// //从数据库获取模糊查找结果
// bool IMLocalDb::GetFuzzySearchResultByDept(CString szText,std::vector<IMFriend>& retList,int resultNumMax)
// {
//     char sql[1024]= {0};
//
//     CStructureInfo mStructInfo;
//     std::string szTextUft8=mStructInfo.GBKToUTF8((const std::string &)szText.GetString());
//
//     sprintf_s(sql,1024,"SELECT IM_ID FROM STRUCTURE_INFO_PER WHERE EMP_DEPT LIKE '%%%s%%' LIMIT %d  OFFSET 0",szTextUft8.c_str(),resultNumMax);
//     bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetFuzzySearchResultByEachCallBack, &retList);
//
//     return bRet;
// }
//
// bool IMLocalDb::GetFuzzySearchResultByName(CString szText,std::vector<IMFriend>& retList,int resultNumMax)
// {
//     char sql[1024]= {0};
//
//     CStructureInfo mStructInfo;
//     std::string szTextUft8=mStructInfo.GBKToUTF8((const std::string &)szText.GetString());
//
//     sprintf_s(sql,1024,"SELECT IM_ID FROM STRUCTURE_INFO_PER WHERE EMP_NAME LIKE '%%%s%%' LIMIT %d  OFFSET 0",szTextUft8.c_str(),resultNumMax);
//     bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetFuzzySearchResultByEachCallBack, &retList);
//
//     return bRet;
// }
//
// bool IMLocalDb::GetFuzzySearchResultByNum(CString szText,std::vector<IMFriend>& retList,int resultNumMax)
// {
//     char sql[1024]= {0};
//
//     //CStructureInfo mStructInfo;
//     //std::string szTextUft8=mStructInfo.GBKToUTF8((const std::string &)szText.GetString());
//
//     sprintf_s(sql,1024,"SELECT IM_ID FROM STRUCTURE_INFO_PER WHERE EMP_NUM LIKE '%%%s%%' LIMIT %d  OFFSET 0",szText,resultNumMax);
//     bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetFuzzySearchResultByEachCallBack, &retList);
//
//     return bRet;
// }
//
// bool IMLocalDb::GetFuzzySearchResultByEngName(CString szText,std::vector<IMFriend>& retList,int resultNumMax)
// {
//     char sql[1024]= {0};
//
//     //CStructureInfo mStructInfo;
//     //std::string szTextUft8=mStructInfo.GBKToUTF8((const std::string &)szText.GetString());
//
//     sprintf_s(sql,1024,"SELECT IM_ID FROM STRUCTURE_INFO_PER WHERE EMP_ENGNAME LIKE '%%%s%%' LIMIT %d  OFFSET 0",szText,resultNumMax);
//     bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetFuzzySearchResultByEachCallBack, &retList);
//
//     return bRet;
// }
//
// bool IMLocalDb::GetFuzzySearchResultByEmail(CString szText,std::vector<IMFriend>& retList,int resultNumMax)
// {
//     char sql[1024]= {0};
//
//     //CStructureInfo mStructInfo;
//     //std::string szTextUft8=mStructInfo.GBKToUTF8((const std::string &)szText.GetString());
//
//     sprintf_s(sql,1024,"SELECT IM_ID FROM STRUCTURE_INFO_PER WHERE EMP_MAIL LIKE '%%%s%%' LIMIT %d  OFFSET 0",szText,resultNumMax);
//     bool bRet = Structuresqlite::Instance()->Hisqlite_exec(sql,GetFuzzySearchResultByEachCallBack, &retList);
//
//     return bRet;
// }
//
//int GetFuzzySearchResultByEachCallBack(void* arg,int argc,char** pvalue,char** pname)
//{
//    if(pvalue[0]==0)
//        return -1;
//
//    int imId=atoi(pvalue[0]);
//
//    StructureInfo m_structureInfo;
//    IMLocalDb db;
//    db.GetPerInfoFromDbByImId(imId,m_structureInfo);
//
//    IMFriend mFriend;
//
//    mFriend.m_nId=imId;
//    mFriend.m_szName.Format("%s",(m_structureInfo.empName).c_str());
//    mFriend.m_szEmpNo.Format("%s",(m_structureInfo.empNum).c_str());
//    mFriend.m_szImg.Format("%s",(m_structureInfo.empHead).c_str());
//    mFriend.m_szEnglish.Format("%s",(m_structureInfo.empEngName).c_str());
//	mFriend.m_phoneNum.Format("%s",(m_structureInfo.empPhone).c_str());
//
//    std::vector<IMFriend>* searchInfoShowList=(std::vector<IMFriend>*) arg;
//    searchInfoShowList->push_back(mFriend);
//
//    return 0;
//}