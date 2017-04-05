#ifndef CMD_UPGRADE_HEAD_FILE
#define CMD_UPGRADE_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//公共宏定义

#define KIND_ID						2004							//游戏 I D
#define GAME_PLAYER					4									//游戏人数
#define GAME_NAME					TEXT("三打哈游戏")					//游戏名字
#define GAME_GENRE					(GAME_GENRE_GOLD|GAME_GENRE_MATCH)	//游戏类型

//游戏状态
#define GS_UG_FREE					GS_FREE								//空闲状态
#define GS_UG_CALL					(GS_PLAYING+1)						//叫牌状态
#define GS_UG_BACK					(GS_PLAYING+2)						//留底状态
#define GS_UG_PLAY					(GS_PLAYING+3)						//游戏状态
#define GS_UG_WAIT					(GS_PLAYING+4)						//等待状态
#define GS_UG_SCORE					(GS_PLAYING+5)						//叫分状态

//////////////////////////////////////////////////////////////////////////
//服务器命令结构

#define SUB_S_GAME_START			100									//游戏开始
#define SUB_S_SEND_CARD				101									//发送扑克
#define SUB_S_CALL_CARD				102									//用户叫牌
#define SUB_S_SEND_CONCEAL			103									//底牌扑克
#define SUB_S_GAME_PLAY				104									//游戏开始
#define SUB_S_OUT_CARD				105									//用户出牌
#define SUB_S_THROW_RESULT			106									//甩牌结果
#define SUB_S_TURN_BALANCE			107									//一轮统计
#define SUB_S_GAME_END				108									//游戏结束
#define SUB_S_CALL_SCORE			109									//叫分命令

//游戏状态
struct CMD_S_StatusFree
{
	LONG							lBaseScore;							//基础积分
};

//叫牌状态
struct CMD_S_StatusCall
{
	//游戏变量
	WORD							wBankerUser;						//庄家用户
	BYTE							cbPackCount;						//副数数目
	BYTE							cbMainValue;						//主牌数值
	BYTE							cbValueOrder[2];					//主牌数值

	//发牌变量
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[52];						//扑克列表

	//叫牌信息
	BYTE							cbComplete;							//完成标志
	BYTE							cbCallCard;							//叫牌扑克
	BYTE							cbCallCount;						//叫牌数目
	WORD							wCallCardUser;						//叫牌用户
};


//叫分状态
struct CMD_S_StatusScore
{
	//游戏变量
	WORD							wBankerUser;						//庄家用户
	BYTE							bBossScore;							//庄家分数
	BYTE							cbPackCount;						//副数数目
	BYTE							cbMainValue;						//主牌数值
	BYTE							cbValueOrder[2];					//主牌数值

	//发牌变量
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[52];						//扑克列表

	
	//叫分信息
	BYTE							bScoreInfo[4];						//叫分信息
	WORD							wCallScoreUser;						//叫分用户
	WORD				 			wCurrentUser;						//当前玩家

	//叫牌信息
	BYTE							cbCallCard;							//叫牌扑克
	BYTE							cbCallCount;						//叫牌数目
	WORD							wCallCardUser;						//叫牌用户

	
};

//留底状态
struct CMD_S_StatusBack
{
	//游戏变量
	BYTE							cbPackCount;						//副数数目
	BYTE							cbMainValue;						//主牌数值
	BYTE							cbMainColor;						//主牌数值
	BYTE							cbValueOrder[2];					//主牌数值

	//叫牌信息
	BYTE							cbCallCard;							//叫牌扑克
	BYTE							cbCallCount;						//叫牌数目
	WORD							wCallCardUser;						//叫牌用户

	//用户变量
	WORD							wBankerUser;						//庄家用户
	WORD							wCurrentUser;						//当前用户

	//扑克变量
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[60];						//扑克列表

	//底牌信息
	BYTE							cbConcealCount;						//暗藏数目
	BYTE							cbConcealCard[8];					//暗藏扑克
};

//游戏状态
struct CMD_S_StatusPlay
{
	//游戏变量
	BYTE							cbPackCount;						//副数数目
	BYTE							cbMainValue;						//主牌数值
	BYTE							cbMainColor;						//主牌数值
	BYTE							cbValueOrder[2];					//主牌数值

	//用户变量
	WORD							wBankerUser;						//庄家用户
	WORD							wCurrentUser;						//当前用户
	WORD							wFirstOutUser;						//出牌用户

	//叫牌信息
	BYTE							cbCallCard;							//叫牌扑克
	BYTE							cbCallCount;						//叫牌数目
	WORD							wCallCardUser;						//叫牌用户

	//扑克变量
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[52];						//扑克列表

	//底牌信息
	BYTE							cbConcealCount;						//暗藏数目
	BYTE							cbConcealCard[8];					//暗藏扑克

	//出牌变量
	BYTE							cbOutCardCount[4];					//出牌数目
	BYTE							cbOutCardData[4][52];				//出牌列表

	//得分变量
	BYTE							cbScoreCardCount;					//扑克数目
	BYTE							cbScoreCardData[48];				//得分扑克
};

//等待状态
struct CMD_S_StatusWait
{
	//游戏变量
	BYTE							cbPackCount;						//副数数目
	BYTE							cbMainValue;						//主牌数值
	BYTE							cbValueOrder[2];					//主牌数值

	//用户变量
	WORD							wBankerUser;						//庄家用户
};


//游戏开始
struct CMD_S_GameStart
{
	WORD							wBankerUser;						//庄家用户
	BYTE							cbPackCount;						//副数数目
	BYTE							cbMainValue;						//主牌数值
	BYTE							cbValueOrder[2];					//主牌数值
};

//发送扑克
struct CMD_S_SendCard
{
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[52];						//扑克列表
};

//用户叫分
struct CMD_S_CallScore
{
	WORD							bCallScoreUser;						//叫分玩家
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bPrevScore;							//上次叫分
	BYTE							bCurrentScore;						//当前叫分
	BYTE							bLandCount;							//叫分次数
};

//用户叫牌
struct CMD_S_CallCard
{
	//BYTE							cbCallCard;							//叫牌扑克
	BYTE							cbCallCount;						//叫牌数目
	BYTE							cbCallColor;						//叫牌花色
	WORD							wCallCardUser;						//叫牌用户
	BYTE							cbBankScore;						//庄家分数
};

//底牌扑克
struct CMD_S_SendConceal
{
	BYTE							cbMainColor;						//主牌数值
	WORD							wBankerUser;						//庄家用户
	WORD							wCurrentUser;						//当前用户
	BYTE							cbConcealCount;						//暗藏数目
	BYTE							cbConcealCard[8];					//暗藏扑克
	BYTE							cbBankScore;						//庄家叫分
};

//游戏开始
struct CMD_S_GamePlay
{
	WORD							wCurrentUser;						//当前用户
	BYTE							cbConcealCount;						//暗藏数目
	BYTE							cbConcealCard[8];					//暗藏扑克
	BYTE							cbMainColor;						//主牌数值
	BYTE							cbBankScore;						//庄家叫分
};

//用户出牌
struct CMD_S_OutCard
{
	BYTE							cbCardCount;						//扑克数目
	WORD							wOutCardUser;						//出牌玩家
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							cbCardData[52];						//扑克列表
	

};

//甩牌结果
struct CMD_S_ThrowResult
{
	WORD							wOutCardUser;						//出牌玩家
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							cbThrowCardCount;					//扑克数目
	BYTE							cbResultCardCount;					//扑克数目
	BYTE							cbCardDataArray[104];				//扑克数组
};

//一轮统计
struct CMD_TurnBalance
{
	WORD							wTurnWinner;						//一轮胜者
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							cbMainColor;						//主牌数值
	BYTE							cbBankScore;						//庄家叫分
	WORD							cbBankUser;							//庄家用户

};

//游戏结束
struct CMD_S_GameEnd
{
	LONG							lScore[4];							//用户得分
	WORD							wGameScore;							//游戏得分
	WORD							wConcealTime;						//扣底倍数
	WORD							wConcealScore;						//底牌积分
	BYTE							cbConcealCount;						//暗藏数目
	BYTE							cbConcealCard[8];					//暗藏扑克
	char							strEnd[20];                         //结束信息
	LONG							lGameTax;                          //游戏税率
};

//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define SUB_C_CALL_CARD				1									//用户叫牌
#define SUB_C_CALL_FINISH			2									//叫牌完成
#define SUB_C_CONCEAL_CARD			3									//底牌扑克
#define SUB_C_OUT_CARD				4									//用户出牌
#define SUB_C_CALL_SCORE			5									//用户叫分
#define SUB_C_SURRENDER				6									//用户头像

//用户叫牌
struct CMD_C_CallCard
{
	BYTE							cbCallColor;						//叫牌花色
	BYTE							cbBankScore;						//庄家分数
};

//底牌扑克
struct CMD_C_ConcealCard
{
	BYTE							cbConcealCount;						//暗藏数目
	BYTE							cbConcealCard[8];					//暗藏扑克
	BYTE							cbBankScore;						//庄家分
};

//用户叫分
struct CMD_C_CallScore
{
	BYTE							bBossScore;							//地主分数
};

 
//用户出牌
struct CMD_C_OutCard
{
	BYTE							cbCardCount;						//出牌数目
	BYTE							cbCardData[52];						//扑克列表

};


//用户逃跑
struct CMD_C_SURRENDER
{
	WORD							cbBankerUser;						//投降庄家
};

//////////////////////////////////////////////////////////////////////////

#endif