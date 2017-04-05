#ifndef GLOBAL_SERVICE_HEAD_FILE
#define GLOBAL_SERVICE_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////
//
////数据库名字
//const TCHAR szGameUserDB[]=TEXT("LobbyGameUserDB");						//用户数据库
//const TCHAR	szTreasureDB[]=TEXT("LobbyTreasureDB");						//财富数据库
//const TCHAR szServerInfoDB[]=TEXT("LobbyServerInfoDB");					//房间数据库

//数据库名字
const TCHAR szGameUserDB[]=TEXT("WHGameUserDB");						//用户数据库
const TCHAR	szTreasureDB[]=TEXT("WHTreasureDB");						//财富数据库
const TCHAR szServerInfoDB[]=TEXT("WHServerInfoDB");					//房间数据库

//数据库表名
const TCHAR szTableScore[]=TEXT("GameScore");							//游戏积分表
const TCHAR szTableAccounts[]=TEXT("UserAccounts");						//用户帐户表

//////////////////////////////////////////////////////////////////////////

//数据库信息
struct tagDataBaseInfo
{
	WORD							wDataBasePort;						//数据库端口
	DWORD							dwDataBaseAddr;						//数据库地址
	TCHAR							szDataBaseUser[32];					//数据库用户
	TCHAR							szDataBasePass[32];					//数据库密码
	TCHAR							szDataBaseName[32];					//数据库名字
};

//////////////////////////////////////////////////////////////////////////

//游戏服务属性
struct tagGameServiceAttrib
{
	WORD							wKindID;							//名称号码
	WORD							wChairCount;						//椅子数目
	WORD							wSupporType;						//支持类型
	DWORD							dwServerVersion;					//版本信息
	DWORD							dwMaxClientVersion;					//版本信息
	DWORD							dwLessClientVersion;				//版本信息
	TCHAR							szDataBaseName[32];					//游戏库名
	TCHAR							szDescription[128];					//模块描述
	TCHAR							szKindName[KIND_LEN];				//类型名字
	TCHAR							szServerModuleName[MODULE_LEN];		//模块名字
	TCHAR							szClientModuleName[MODULE_LEN];		//模块名字
};

//游戏服务配置
struct tagGameServiceOption
{
	//房间属性
	WORD							wKindID;							//类型标识
	WORD							wServerID;							//房间号码
	WORD							wStationID;							//站点号码
	WORD							wTableCount;						//桌子数目
	WORD							wServerType;						//房间类型
	WORD							wServerPort;						//房间端口
	WORD							wSitByServer;						//bluker:只能由服务器指定座位
	DWORD							dwServerAddr;						//房间地址
	LONG							lMaxGold;							//bluker:总下注上限
	TCHAR							szGameRoomName[SERVER_LEN];			//房间名称


	//游戏币限制
	LONG							lCellScore;							//单位游戏币
	LONG							lHighScore;							//最高游戏币
	LONG							lLessScore;							//最低游戏币


	//扩展配置
	WORD							wMaxConnect;						//最大连接
	DWORD							dwUserRight;						//附加权限
	tagOptionBuffer					OptionBuffer;						//配置缓冲

	//比赛配置
	LONG							lMatchDraw;							//比赛局数
	BYTE							cbLimitDraw;						//限制局数
	BYTE							cbControlStart;						//控制开始
};

//////////////////////////////////////////////////////////////////////////

#endif