#pragma once

#include "IMConst.h"
#include <vector>

class HttpInterface
{
public:
	HttpInterface(void);
	~HttpInterface(void);

	void    GetGroupInfo(GroupInfo* pGroup, UINT nGroupId);
	void    GetGroupList(std::vector<BaseInfo*>* pGroupList, UINT nId);
	void	GetFriendList(std::vector<BaseInfo*>* pUserList, UINT nId);

private:
	char* GetHttpData(SStringT szUrl);
	void    ParseGroupInfo(GroupInfo* pGroup, char* pData);
	void    ParseFriendList(std::vector<BaseInfo*>* pUserList, char * pData);
	void    ParseGroupList(std::vector<BaseInfo*>* pGroupList, char * pData);

};

