#include "StdAfx.h"

#include "IMLocalDb.h"
#include "HttpInterface.h"
#include "imre/HTTPDownloader.h"
#include "utils.h"


HttpInterface::HttpInterface(void)
{
}


HttpInterface::~HttpInterface(void)
{
}

char* HttpInterface::GetHttpData(SStringT szUrl)
{
	DWORD dwStatus = 0;
	HTTPDownloader downloader;
	if (downloader.OpenURL((LPCWSTR)szUrl) != 0)
		return NULL;

	char* pData = new char[1024*1024];
	ZeroMemory(pData, 1024*1024);

	downloader.QueryStatusCode(dwStatus);
	if (dwStatus != HTTP_STATUS_OK || downloader.ReadFile(pData) != 0)
	{
		delete [] pData;
		pData = NULL;

		return pData;
	}

	return pData;
}

void    HttpInterface::GetGroupInfo(GroupInfo* pGroup, UINT nGroupId)
{
	//url
	SStringT szUrl;
	szUrl.Format(_T("http://%s/EPA_IM/teamList!getTeamInfo.action?teamId=%d&%s"), 
		_T(WEB_SRV_ADDR),
		nGroupId, 
		S_CA2W(HttpAesParam(nGroupId)));

	char* pData = GetHttpData(szUrl);

	if ( pData )
	{
		ParseGroupInfo(pGroup, pData);

		delete [] pData;
		pData = NULL;
	}
}

void	HttpInterface::ParseGroupInfo(GroupInfo* pGroup, char* pData)
{
	IMLocalDb db;
	//db.ClearTeamMembersFormDB(pTeam);

	int tmp = 0;
	std::string szTmp("");

	//Ⱥ����
	memcpy(&tmp, pData, 4);
	if ( tmp < 0 || tmp > 500 )
		return;
	pData += 4;
	szTmp = std::string(pData, tmp);
	pGroup->Note = S_CA2W(szTmp.c_str());
	pData += tmp;


	//������Ա�б�����
	int size = 0;
	memcpy(&size, pData, 4);

	if ( size < 0 || size > 10000 )
		return;

	pGroup->Members = size;

	if( size == pGroup->MemberList.size() )
	{
		return;
	}

	pData += 4;

	//int	nId = 0;
	//CString szName("");
	//CString szImage("");

	UserInfo userInfo;

	for ( int i = 0; i < size; ++ i )
	{
		//��Աid
		memcpy(&userInfo.Id, pData, 4);
		if ( userInfo.Id < 0 )
			break;
		pData += 4;

		//��Ա��
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 100 )
			break;
		pData += 4;
		szTmp = std::string(pData, tmp);
		userInfo.Name = S_CA2W(szTmp.c_str());
		pData += tmp;

		//ͷ��id
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 100 )
			break;
		pData += 4;
		szTmp = std::string(pData, tmp);
		
		userInfo.AvatarPath = SetCurDir(L"Head\\").c_str();
		userInfo.AvatarPath.Append(S_CA2W(szTmp.c_str()));
		if(!PathFileExists( (LPCWSTR)userInfo.AvatarPath) )
			DownLoadHead(S_CA2W(szTmp.c_str()), (LPCWSTR)userInfo.AvatarPath);

		pData += tmp;

		userInfo.AvatarId = SStringT().Format(_T("%u"), userInfo.Id);

		pGroup->MemberList.push_back(userInfo);

		//IMFriendDraw	* pFriend = new IMFriendDraw();
		//pFriend->m_nId = nId;
		//pFriend->m_szName = szName;
		//pFriend->m_szImg = szImage;

		db.SaveTeamMemberToDB(pGroup->Id, &userInfo);
		//delete pFriend;
	}
}

void HttpInterface::GetGroupList(std::vector<BaseInfo*>* pGroupList, UINT nId)
{
	//url
	SStringT szUrl;
	szUrl.Format(_T("http://%s/EPA_IM/teamList!getTeamList.action?imId=%d&%s"), 
		_T(WEB_SRV_ADDR),
		nId, 
		S_CA2W(HttpAesParam(nId)));

	char* pData = GetHttpData(szUrl);

	if ( pData )
	{
		ParseGroupList(pGroupList, pData);

		delete [] pData;
		pData = NULL;
	}
}

void    HttpInterface::ParseGroupList(std::vector<BaseInfo*>* pGroupList, char * pData)
{
	IMLocalDb db;

	//���Ƚ�������
	int size = 0;
	memcpy(&size, pData, 4);

	if ( size < 0 || size > 10000 )
		return;

	pData += 4;

	//std::string szTmp("");

	int tmp = 0;
	for ( int i = 0; i < size; ++ i )
	{
		GroupInfo * pTeam = new GroupInfo();

		//Ⱥ��ID
		memcpy(&pTeam->Id, pData, 4);
		pData += 4;

		//Ⱥ����
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 300 )
			break;
		pData += 4;
		std::string szName(pData, tmp);
		pData += tmp;
		pTeam->Name = S_CA2W(szName.c_str());

		//Ⱥ��ID
		memcpy(& pTeam->MasterId, pData, 4);
		pData += 4;

		//��ǰȺ��Ա��
		memcpy(& pTeam->Members, pData, 4);
		pData += 4;

		//��ǰȺ��Ա������
		//memcpy(&pTeam->m_nMax, pData, 4);
		pData += 4;

		//ĳЩ��������
		//Ⱥ�ķ�����
		//pTeam->m_szGroupName = "�ҵ�Ⱥ��";
		//Ⱥ��ͷ��
		//std::string szPath(SkinMgr::Instance()->m_szWorkPath);
		//szPath += std::string("skin\\team_head.png");
		//pTeam->LoadImage(A2OLE(szPath.c_str()));

		pTeam->AvatarId = _T("G0001");
		pTeam->AvatarPath = SetCurDir(_T("")).c_str();
		pTeam->AvatarPath.Append(L"Group.png");

		//pTeam->m_isTeam = true;
		//pTeam->m_bOnline = true;

		//������Ƿ����
		//if ( pPage && pTeam->m_nId != 0 && !pPage->FindGroup( pTeam->m_szGroupName ) )
		//{
		//	IMGroupDraw * pGroup = new IMGroupDraw();
		//	pGroup->m_szName = pTeam->m_szGroupName;
		//	pPage->AddNode(pGroup);
		//}

		GetGroupInfo(pTeam, pTeam->Id);

		pGroupList->push_back(pTeam);

		//if(pTeam->m_nId != 0)
		//{
		//	if(pPage)
		//		pPage->AddNodeNoSaveDB(pTeam);
		//	else
				db.SaveTeamToDB(pTeam);
		//}
	}
}

void	HttpInterface::GetFriendList(std::vector<BaseInfo*>* pUserList, UINT nId)
{
	//url
	SStringT szUrl;
	szUrl.Format(_T("http://%s/EPA_IM/friendList!getFriendList.action?imid=%d&%s"), 
		_T(WEB_SRV_ADDR),
		nId, 
		S_CA2W(HttpAesParam(nId)));

	char* pData = GetHttpData(szUrl);

	if ( pData )
	{
		ParseFriendList(pUserList, pData);

		delete [] pData;
		pData = NULL;
	}
}

//vector<������������id���������֣�ͷ���ļ��������ţ����ţ����䣬ǩ��>
void  HttpInterface::ParseFriendList(std::vector<BaseInfo*>* pUserList, char * pData)
{
	IMLocalDb db;

	//���Ƚ�������
	int size = 0;
	memcpy(&size, pData, 4);

	if ( size < 0 || size > 10000 )
		return;
	pData += 4;

	std::string szTmp("");

	int tmp = 0;
	for ( int i = 0; i < size; ++ i )
	{
		UserInfo* pUserInfo = new UserInfo;

		//����id
		memcpy(&pUserInfo->Id, pData, 4);
		pData += 4;

		//������
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 200 )
			break;
		pData += 4;
		std::string szName(pData, tmp);
		pData += tmp;
		pUserInfo->Name = S_CA2W(szName.c_str());

		//������
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 300 )
			break;
		pData += 4;
		std::string szGroup(pData, tmp);
		pData += tmp;
		//userInfo.Group = szGroup.c_str();

		////������Ƿ����
		//if (pPage && ! pPage->FindGroup(szGroup.c_str()) )
		//{
		//	IMGroupDraw * pGroup = new IMGroupDraw();
		//	pGroup->m_szName = szGroup.c_str();

		//	pPage->AddNode(pGroup);
		//}

		//ͷ���ļ���
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 100 )
			break;
		pData += 4;
		szTmp = std::string(pData, tmp);

		pUserInfo->AvatarPath = SetCurDir(L"Head\\").c_str();
		pUserInfo->AvatarPath.Append(S_CA2W(szTmp.c_str()));
		if(!PathFileExists( (LPCWSTR)pUserInfo->AvatarPath) )
			DownLoadHead(S_CA2W(szTmp.c_str()), (LPCWSTR)pUserInfo->AvatarPath);

		pData += tmp;

		//����
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 50 )
			break;
		pData += 4;
		szTmp = std::string(pData, tmp);
		pUserInfo->EmpNo = S_CA2W(szTmp.c_str());
		pData += tmp;

		//����
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 100 )
			break;
		pData += 4;
		szTmp = std::string(pData, tmp);
		pUserInfo->Dept = S_CA2W(szTmp.c_str());
		pData += tmp;

		//����
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 200 )
			break;
		pData += 4;
		szTmp = std::string(pData, tmp);
		pUserInfo->EMail = S_CA2W(szTmp.c_str());
		pData += tmp;

		//ǩ��
		memcpy(&tmp, pData, 4);
		if ( tmp < 0 || tmp > 400 )
			break;
		pData += 4;
		szTmp = std::string(pData, tmp);
		pUserInfo->Note = S_CA2W(szTmp.c_str());
		pData += tmp;

		pUserInfo->AvatarId = pUserInfo->EmpNo;
		pUserList->push_back(pUserInfo);

		//if(pPage)
		//	pPage->AddNodeNoSaveDB(pFriend);
		//else
		db.SaveFriendToDB(pUserInfo);
	}
}
