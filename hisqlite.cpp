#include "stdafx.h"
#include "hisqlite.h"

#include "IMConst.h"

Hisqlite::Hisqlite()
{
	IMdb= NULL;
	isOpen= false;
	//Hisqlite_conn();
}

//�ر�����
Hisqlite::~Hisqlite()
{
	if(IMdb)
	{
		sqlite3_close(IMdb);
		isOpen= false;
	}
}

//��ӡ������Ϣ
SStringT Hisqlite::Hisqlite_errmsg()
{
	std::cout<< sqlite3_errmsg(IMdb)<< std::endl;

	SStringT szInfo;
	szInfo.Format(_T("****** SQLLite error msg: %s\n\n"), S_CA2W(sqlite3_errmsg(IMdb)));
	//OutputDebugStringA(szInfo);

	return szInfo;
}

void Hisqlite::SetDbFile(SStringT & szDb)
{
	m_szDbFile = szDb;
}
//�������ݿ����Ӻ���
bool Hisqlite::Hisqlite_conn()
{
	if (!isOpen)
	{
		SStringA strDgFile = S_CW2A(m_szDbFile);
		if(SQLITE_OK!=  sqlite3_open(strDgFile.GetBuffer(0),&IMdb)) 
			isOpen= false;
		else
			isOpen= true;
	}
	return isOpen;
}

//������̬���ݿ��SERVER_CONF��SYSCONF��NEAREST_CHAT��FRIENDS��TEAMS��TEAMS_MEMBERS
bool Hisqlite::Hisqlite_createStaticTables()
{
	bool bRet= true;
	char* pSql[]= CREATE_STATIC_TABLE_SQL;

	if(!Hisqlite_conn())
		return false;
	
	for (int i= 0;i< ARR_SIZE(pSql);i++)
	{
		//�����̶����ݱ�
		if (SQLITE_OK!= sqlite3_exec(IMdb,pSql[i],NULL,NULL,NULL))
			return false;
	}
	//��ʼ��SERVER_CONF��
	return Hisqlite_initConf();
}

//������̬���ݿ���磺FRIENDS_TALK_201507��TEAM_TALK_201507
bool Hisqlite::Hisqlite_createDynamicTables()
{
	bool bRet= true;
	char* pSql[]= CREATE_DYNAMIC_TABLE_SQL;
	char tabName[1024]={0};
	SYSTEMTIME sysTime;

	if(!Hisqlite_conn())
		return false;

	//������sysTimeStrֵ����Ϊ����ʱ��  �磺201504  201512
	GetLocalTime(&sysTime);
	for (int i= 0;i< ARR_SIZE(pSql);i++)
	{
		int nYear = sysTime.wYear;
		int nMon = sysTime.wMonth;

		sprintf_s(tabName, pSql[i], nYear*100 + nMon);

		//���������Ⱥ�����ݱ�FRIENDS_TALK_******��TEAM_TALK_******
		if (SQLITE_OK!= sqlite3_exec(IMdb,tabName,NULL,NULL,NULL))
			bRet= false;
	}
	return bRet;
}

/*
����1��sql	��ִ�е�sql���
����2��funs	ִ��selectʱ�Ļص��������������select��������ΪNULL  
			Ĭ�ϻص�������ʽΪ int (*HisqliteCallback)(void* arg,int argc,char** pvalue,char** pname)
			exec_callback�����в����� 
					arg: �Ǵ��������������Ĳ��� 
					argc:  �������
					pvalue: �ǲ�ѯ�����ֵ 
					pname: ��ѯ����е����� 

����3��arg	���������ݸ��ص������Ĳ������������select�������޲������ݿ���ΪNULL
*/
bool Hisqlite::Hisqlite_exec(char *sql,HisqliteCallback funs,void *arg)
{
	bool bRet= true;
	if(NULL== sql)
		return false;

	if(!Hisqlite_conn())
		return false;

	int nRet = 0;
	//�������ݿ�sql���
	nRet = sqlite3_exec(IMdb,sql,funs,arg,NULL);

	if (SQLITE_OK!= nRet)
	{
		//if(nRet != 19)
		//	TRACE("sqlite error. err code: %d\r\n", nRet);

		bRet= false;
	}

	return bRet;
}

//Hisqlite_isTableExist�����Ļص�������Hisqlite�����Ԫ����
int Hisqlite_isTableExist_callback(void* arg,int argc,char** pvalue,char** pname) 
{  
	//select��ѯ�������Ϊ�գ���ʱpvalue[i]ΪNULL
	int *bRet= (int *) arg;
	*bRet= ((pvalue[0] == NULL)? 0: 1);
	return 0;  //callback������������0   
} 

//�ж����ݿ����Ƿ���ڱ�
bool Hisqlite::Hisqlite_isTableExist(char *tableName)
{
	char sql[1024]= {0};
	int bRet= 0;
	//exec_callback funs= Hisqlite_isTableExist_callback;
	sprintf_s(sql,"SELECT * FROM sqlite_master WHERE type='table' AND name='%s'",tableName);
	Hisqlite_exec(sql,Hisqlite_isTableExist_callback,(void *)&bRet);
	return (0!= bRet);
}

//��ʼ�����ض����ñ�SERVER_CONF
bool Hisqlite::Hisqlite_initConf()
{
	char sql[1024]= {0};

	//sprintf_s(sql,"INSERT INTO SERVER_CONF(LOGIN_DNS_LIST,CONF_DNS_LIST,UDP_PORT_LIST) VALUES('%s','%s','%s')", \
	//	"172.16.4.67","172.16.4.67", \
	//			  "8840,8841,8842,8843,8844,8845,8846,8847,8848,8849");

#if PRODUCT_VERSION
	sprintf_s(sql,"INSERT INTO SERVER_CONF(LOGIN_DNS_LIST,CONF_DNS_LIST,UDP_PORT_LIST) VALUES('%s','%s','%s')", \
		/*"10.1.3.90","10.1.3.93", \*/
		MSG_SRV_ADDR,WEB_SRV_ADDR, \
		/*"10.202.1.16", "10.202.1.9", \*/
		/*"qechat.yulong.com","qeweb.yulong.com", \*/
		 /*"139.219.234.43","139.219.192.232", \*/
		"8840,8841,8842,8843,8844,8845,8846,8847,8848,8849");
#else
	sprintf_s(sql,"INSERT INTO SERVER_CONF(LOGIN_DNS_LIST,CONF_DNS_LIST,UDP_PORT_LIST) VALUES('%s','%s','%s')", \
		  /*"10.202.1.4","10.202.1.15", \*/
		  "139.219.234.43","139.219.192.232", \
		 /* "172.16.4.67","172.16.4.67", \*/
		 /*"10.3.64.67", "10.3.64.67",*/
		  "8840,8841,8842,8843,8844,8845,8846,8847,8848,8849");
#endif

	return Hisqlite_exec(sql,NULL,NULL);
}

//�޸ı�TEAMS��IM_TEAM_NAME�Ĵ�СΪvarchar(100)
bool Hisqlite::changTeamsField()
{
	bool bRet= false;
	bRet= Hisqlite_exec("ALTER TABLE TEAMS RENAME TO TEAMS1",NULL,NULL);

	if ( ! bRet )
		return bRet;

	bRet= Hisqlite_exec("create table TEAMS(IM_TEAM_ID int unsigned primary key, IM_TEAM_NAME varchar(100) NOT NULL, \
						TEAM_OWNER_ID unsigned int, TEAM_MEMBERS unsigned int, TEAM_LIMIT unsigned int, \
						TEAM_GROUP_NAME varchar(20) default NULL,  TEAM_HEAD_PATH varchar(20) default NULL, \
						TEAM_DESC varchar(200) default NULL)",NULL,NULL);
	if ( ! bRet )
		return bRet;
	bRet= Hisqlite_exec("INSERT INTO TEAMS SELECT * from TEAMS1",NULL,NULL);
	if ( ! bRet )
		return bRet;
	bRet= Hisqlite_exec("DROP TABLE TEAMS1",NULL,NULL);

	return bRet;
}

//���ӱ�SYSCONF���ֶ�HOTKEY_STR��СΪvarchar(200)
bool Hisqlite::changSysconfField()
{
	return Hisqlite_exec("ALTER table SYSCONF add COLUMN 'HOTKEY_STR' varchar(200) default NULL",NULL,NULL);
}
