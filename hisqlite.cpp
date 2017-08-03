#include "stdafx.h"
#include "hisqlite.h"

#include "IMConst.h"

Hisqlite::Hisqlite()
{
	IMdb= NULL;
	isOpen= false;
	//Hisqlite_conn();
}

//关闭连接
Hisqlite::~Hisqlite()
{
	if(IMdb)
	{
		sqlite3_close(IMdb);
		isOpen= false;
	}
}

//打印出错信息
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
//建立数据库连接函数
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

//创建静态数据库表：SERVER_CONF、SYSCONF、NEAREST_CHAT、FRIENDS、TEAMS、TEAMS_MEMBERS
bool Hisqlite::Hisqlite_createStaticTables()
{
	bool bRet= true;
	char* pSql[]= CREATE_STATIC_TABLE_SQL;

	if(!Hisqlite_conn())
		return false;
	
	for (int i= 0;i< ARR_SIZE(pSql);i++)
	{
		//创建固定数据表
		if (SQLITE_OK!= sqlite3_exec(IMdb,pSql[i],NULL,NULL,NULL))
			return false;
	}
	//初始化SERVER_CONF表
	return Hisqlite_initConf();
}

//创建动态数据库表如：FRIENDS_TALK_201507、TEAM_TALK_201507
bool Hisqlite::Hisqlite_createDynamicTables()
{
	bool bRet= true;
	char* pSql[]= CREATE_DYNAMIC_TABLE_SQL;
	char tabName[1024]={0};
	SYSTEMTIME sysTime;

	if(!Hisqlite_conn())
		return false;

	//将变量sysTimeStr值设置为本地时间  如：201504  201512
	GetLocalTime(&sysTime);
	for (int i= 0;i< ARR_SIZE(pSql);i++)
	{
		int nYear = sysTime.wYear;
		int nMon = sysTime.wMonth;

		sprintf_s(tabName, pSql[i], nYear*100 + nMon);

		//创建聊天和群聊数据表FRIENDS_TALK_******和TEAM_TALK_******
		if (SQLITE_OK!= sqlite3_exec(IMdb,tabName,NULL,NULL,NULL))
			bRet= false;
	}
	return bRet;
}

/*
参数1：sql	被执行的sql语句
参数2：funs	执行select时的回调函数，如果不是select操作可置为NULL  
			默认回调函数格式为 int (*HisqliteCallback)(void* arg,int argc,char** pvalue,char** pname)
			exec_callback函数中参数： 
					arg: 是从主函数传进来的参数 
					argc:  表的列数
					pvalue: 是查询结果的值 
					pname: 查询结果列的名字 

参数3：arg	主函数传递给回调函数的参数，如果不是select操作或无参数传递可置为NULL
*/
bool Hisqlite::Hisqlite_exec(char *sql,HisqliteCallback funs,void *arg)
{
	bool bRet= true;
	if(NULL== sql)
		return false;

	if(!Hisqlite_conn())
		return false;

	int nRet = 0;
	//插入数据库sql语句
	nRet = sqlite3_exec(IMdb,sql,funs,arg,NULL);

	if (SQLITE_OK!= nRet)
	{
		//if(nRet != 19)
		//	TRACE("sqlite error. err code: %d\r\n", nRet);

		bRet= false;
	}

	return bRet;
}

//Hisqlite_isTableExist函数的回调函数，Hisqlite类的友元函数
int Hisqlite_isTableExist_callback(void* arg,int argc,char** pvalue,char** pname) 
{  
	//select查询结果可能为空，此时pvalue[i]为NULL
	int *bRet= (int *) arg;
	*bRet= ((pvalue[0] == NULL)? 0: 1);
	return 0;  //callback函数正常返回0   
} 

//判断数据库中是否存在表
bool Hisqlite::Hisqlite_isTableExist(char *tableName)
{
	char sql[1024]= {0};
	int bRet= 0;
	//exec_callback funs= Hisqlite_isTableExist_callback;
	sprintf_s(sql,"SELECT * FROM sqlite_master WHERE type='table' AND name='%s'",tableName);
	Hisqlite_exec(sql,Hisqlite_isTableExist_callback,(void *)&bRet);
	return (0!= bRet);
}

//初始化本地端配置表SERVER_CONF
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

//修改表TEAMS中IM_TEAM_NAME的大小为varchar(100)
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

//增加表SYSCONF中字段HOTKEY_STR大小为varchar(200)
bool Hisqlite::changSysconfField()
{
	return Hisqlite_exec("ALTER table SYSCONF add COLUMN 'HOTKEY_STR' varchar(200) default NULL",NULL,NULL);
}
