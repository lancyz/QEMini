/*SQL语句
	
SERVER_CONF：	
						CREATE TABLE "SERVER_CONF"(
						"LOGIN_DNS_LIST" varchar(200) NOT NULL, 
						"CONF_DNS_LIST" 	varchar(200) NOT NULL,
						"UDP_PORT_LIST" varchar(200) NOT NULL
						);

			
SYSCONF：		
						CREATE TABLE "SYSCONF"(
						"LOGIN_SINCE_SETUP" Tinyint default 0, 
						"MAINBOARD_AUTO_HIDDEN" 	tinyint default 0,
						"MAINBOARD_SHOW_ICON" tinyint default 0,
						"MAINBOARD_CLOSE_SET" tinyint  	default 0,
						"STATUS_LOGIN_DEFAULT"  tinyint default 0,
						"STATUS_AUTO_ANS" varchar(200) default NULL,
						"MSG_STORAGE_PATH" varchar(200) NOT NULL,
						"FILE_REMIND_CLEAN" tinyint default 0
						);

NEAREST_CHAT：	
						CREATE TABLE "NEAREST_CHAT1"(
						"IM_ID" int unsigned, 
						"IM_TYPE" 	tinyint
						);

FRIENDS：		
						CREATE TABLE "FRIENDS"(
						"IM_ID" int unsigned primary key,
						"IM_NAME" varchar(20) default NULL,
						"IM_HEAD_PATH" varchar(20) default NULL,
						"IM_GROUP_NAME" varchar(20) default NULL,
						"IM_EMPNO" varchar(10) default NULL,
						"IM_NOTE" varchar(200) default NULL,
						"IM_ENAME" varchar(25) default NULL,
						"IM_DEPT" varchar(100) default NULL,
						"IM_EMAIL" varchar(100) default NULL
						);

TEAMS：
						CREATE TABLE "TEAMS"(
						"IM_TEAM_ID" int unsigned primary key,
						"IM_TEAM_NAME" varchar(30) NOT NULL,
						"TEAM_OWNER_ID" unsigned int,
						"TEAM_MEMBERS" unsigned int,
						"TEAM_LIMIT" unsigned int,
						"TEAM_GROUP_NAME" varchar(20) default NULL,
						"TEAM_HEAD_PATH" varchar(20) default NULL,
						"TEAM_DESC" varchar(200) default NULL
						);

TEAMS_MEMBERS：
						CREATE TABLE "TEAM_MEMBERS"(
						"IM_TEAM_ID" int unsigned,
						"IM_ID" int unsigned,
						"IM_NAME"  varchar(20) default NULL,
						"IM_HEAD_PATH" varchar(20) default NULL
						);

FRIENDS_TALK_******：（如：FRIENDS_TALK_201508）
						CREATE TABLE "FRIENDS_TALK_201511" (
						"MSG_ID"  INTEGER PRIMARY KEY AUTOINCREMENT,
						"SEND_ID"  int unsigned,
						"RECV_ID"  int unsigned,
						"SEND_TIME"  int unsigned,
						"RECV_TIME"  int unsigned,
						"SEND_NAME"  varchar(20) NOT NULL,
						"RECV_NAME"	  varchar(20) NOT NULL,
						"DIRECTION"  tinyint,
						"MSG_DETAIL"  text
						);


TEAM_TALK_******：（如：TEAM_TALK_201508）
						CREATE TABLE "TEAM_TALK_201510" (
						"MSG_ID"  INTEGER PRIMARY KEY AUTOINCREMENT,
						"IM_TEAM_ID"  int unsigned,
						"SEND_ID"  int unsigned,
						"SEND_NAME"	varchar(20) NOT NULL,
						"SEND_TIME"  int unsigned,
						"RECV_TIME"  int unsigned,
						"MSG_DETAIL"  text
						);

*/

#ifndef __HI_SQLITE__
#define __HI_SQLITE__

#include <iostream>
#include <Windows.h>
#include "sqlite3.h"
#include "os_singleton.h"

//IM本地数据库名字
#define  IM_DB_NAME "IMSQLITE.db"

#define  CREATE_STATIC_TABLE_SQL {			\
		"CREATE TABLE 'SERVER_CONF'(		\
					'LOGIN_DNS_LIST' varchar(200) NOT NULL, \
					'CONF_DNS_LIST' 	varchar(200) NOT NULL,\
					'UDP_PORT_LIST' varchar(200) NOT NULL)",			\
		"CREATE TABLE 'SYSCONF'(		\
					'LOGIN_SINCE_SETUP' tinyint default 0, \
					'MAINBOARD_AUTO_HIDDEN'	tinyint default 0,\
					'MAINBOARD_SHOW_ICON' tinyint default 0,\
					'MAINBOARD_CLOSE_SET' tinyint  	default 0,\
					'STATUS_LOGIN_DEFAULT'  tinyint default 0,\
					'STATUS_AUTO_ANS' varchar(1000) default NULL,\
					'STATUS_ANS_CHOICE' tinyint default 0,\
					'HOTKEY_HELP' tinyint default 0,\
					'HOTKEY_SET' tinyint default 0,\
					'FILE_STORAGE_PATH' varchar(200) default NULL,\
					'FILE_REMIND_CLEAN' tinyint default 0,\
					'HOTKEY_STR' varchar(200) default NULL)",				\
		"CREATE TABLE 'NEAREST_CHAT'( \
					'IM_ID' int unsigned, \
					'IM_TYPE' 	tinyint)",			\
		"CREATE TABLE IF NOT EXISTS 'FRIENDS'( \
					'IM_ID' int unsigned primary key,\
					'IM_NAME' varchar(20) default NULL,\
					'IM_HEAD_PATH' varchar(40) default NULL,\
					'IM_GROUP_NAME' varchar(20) default NULL,\
					'IM_EMPNO' varchar(20) default NULL,\
					'IM_NOTE' varchar(200) default NULL,\
					'IM_ENAME' varchar(25) default NULL,\
					'IM_DEPT' varchar(100) default NULL,\
					'IM_EMAIL' varchar(100) default NULL)",			\
		"CREATE TABLE 'TEAMS'(		\
					'IM_TEAM_ID' int unsigned primary key,\
					'IM_TEAM_NAME' varchar(100) NOT NULL,\
					'TEAM_OWNER_ID' unsigned int,\
					'TEAM_MEMBERS' unsigned int,\
					'TEAM_LIMIT' unsigned int,\
					'TEAM_GROUP_NAME' varchar(20) default NULL,\
					'TEAM_HEAD_PATH' varchar(20) default NULL,\
					'TEAM_DESC' varchar(200) default NULL)",		\
		"CREATE TABLE IF NOT EXISTS 'TEAM_MEMBERS'(		\
					'IM_TEAM_ID' int unsigned,\
					'IM_ID' int unsigned,\
					'IM_NAME'  varchar(20) NOT NULL,\
					'IM_HEAD_PATH' varchar(20) NOT NULL,\
                     primary key(IM_TEAM_ID, IM_ID))",     \
		"CREATE TABLE IF NOT EXISTS 'MY_EXPRESSION'( \
					'ID' int unsigned primary key,\
					'GROUP_NAME' varchar(40) default NULL,\
					'NAME' varchar(40) default NULL,\
					'FILE_NAME' varchar(20) default NULL,\
					'FILE_PATH' varchar(256) default NULL,\
					'TIME' int unsigned default NULL,\
					'POS' varchar(20) default NULL,\
					'ISNEW' int unsigned default NULL)",    \
		"CREATE TABLE IF NOT EXISTS 'FRIEND_GROUP'( \
					'IM_NAME' varchar(50) primary key)"  ,\
			"CREATE TABLE IF NOT EXISTS 'TEAMS_SET'( \
					'ID_TEAM' int unsigned primary key,\
					'SET_TEAM' int unsigned default NULL)" ,   \
			"CREATE TABLE IF NOT EXISTS 'STRUCTURE_INFO_DEP'(		\
					'DEPT_ID' int unsigned,\
					'PARENT_ID' int unsigned,\
					'DEPT_CODE'  varchar(20) NOT NULL,\
					'DEPT_NAME' varchar(20) NOT NULL,\
					'DEPT_FULL_ID' varchar(20) NOT NULL,\
					'DEPT_FULL_NAME' varchar(20) NOT NULL,\
					'DEPT_LAYER' int unsigned,\
					primary key(DEPT_ID))"   ,   \
			"CREATE TABLE IF NOT EXISTS 'STRUCTURE_INFO_PER'(		\
					'IM_ID' int unsigned,\
					'EMP_NUM' varchar(20) NOT NULL,\
					'EMP_NAME' varchar(20) NOT NULL,\
					'EMP_ENGNAME' varchar(20) NOT NULL,\
					'EMP_DEPT'  varchar(100) NOT NULL,\
					'EMP_HEAD' varchar(50) NOT NULL,\
					'EMP_MPHONE' varchar(50) NOT NULL,\
					'EMP_MAIL' varchar(50) NOT NULL,\
					'DEPT_LAYER' int unsigned,\
					primary key(IM_ID))"  }

#define  CREATE_DYNAMIC_TABLE_SQL {		\
	"CREATE TABLE IF NOT EXISTS 'FRIENDS_TALK_%d' (		\
			'MSG_ID'  INTEGER PRIMARY KEY AUTOINCREMENT,\
			'SEND_ID'  int unsigned,\
			'RECV_ID'  int unsigned,\
			'SEND_TIME'  int unsigned,\
			'RECV_TIME'  int unsigned,\
			'SEND_NAME'  varchar(20) NOT NULL,\
			'RECV_NAME'	  varchar(20) NOT NULL,\
			'DIRECTION'  tinyint,\
			'MSG_DETAIL'  text, \
			'STATUS' int, \
			'CHECK_ID'  int unsigned )",		\
	"CREATE TABLE IF NOT EXISTS 'TEAM_TALK_%d' (	\
			'MSG_ID'  INTEGER PRIMARY KEY AUTOINCREMENT,\
			'IM_TEAM_ID'  int unsigned,\
			'SEND_ID'  int unsigned,\
			'SEND_NAME'	varchar(20) NOT NULL,\
			'SEND_TIME'  int unsigned,\
			'RECV_TIME'  int unsigned,\
			'MSG_DETAIL'  text, \
			'STATUS' int, \
			'CHECK_ID'  int unsigned )"				}

#define  ARR_SIZE(arr)	(sizeof(arr)/sizeof(arr[0]))


typedef int (*HisqliteCallback)(void*,int,char**,char**);
#pragma comment(lib,"SQLITE3.lib")

using namespace onesec;

class Hisqlite : public Singleton<Hisqlite>
{
public:
	////判断数据库中是否存在表回调函数
	friend int Hisqlite_isTableExist_callback(void* arg,int argc,char** pvalue,char** pname);
public:

	Hisqlite();
	~Hisqlite();

	void SetDbFile(SStringT & szDb);
	
	//打印出错信息
	SStringT Hisqlite_errmsg();
	//创建静态数据库表：SERVER_CONF、SYSCONF、NEAREST_CHAT、FRIENDS、TEAMS、TEAMS_MEMBERS
	bool Hisqlite_createStaticTables();
	//创建动态数据库表如：FRIENDS_TALK_201507、TEAM_TALK_201507
	bool Hisqlite_createDynamicTables();
	//判断数据库中是否存在特定表
	bool Hisqlite_isTableExist(char *);
	//建立数据库连接
	bool Hisqlite_conn();
	//执行sql语句
	bool Hisqlite_exec(char *,HisqliteCallback,void *);
	//初始化本地端配置表SERVER_CONF
	bool Hisqlite_initConf();

	//修改表TEAMS中IM_TEAM_NAME的大小为varchar(100)
	bool changTeamsField();
	//增加表SYSCONF中字段HOTKEY_STR大小为varchar(200)
	bool changSysconfField();

private:
	bool isOpen;
	sqlite3 *IMdb;
	char *IMsqls;

	SStringT m_szDbFile;
};

#endif