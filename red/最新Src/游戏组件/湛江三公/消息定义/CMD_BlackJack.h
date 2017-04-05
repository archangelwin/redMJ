#ifndef CMD_BLACKJACK_FILE
#define CMD_BLACKJACK_FILE

//////////////////////////////////////////////////////////////////////////
//�����궨��

//#define KIND_ID							ID_BACK_JACK						//��Ϸ I D
#define KIND_ID							29									//��Ϸ I D
#define GAME_PLAYER						6									//��Ϸ����
#define GAME_NAME						TEXT("տ������")						//��Ϸ����
#define GAME_GENRE						(GAME_GENRE_GOLD|GAME_GENRE_MATCH)	//��Ϸ����

//�汾����
#define		MAXCLIENTVER			    MAKELONG(0,4)
#define		LESSCLIENTVER			    0
 
//��Ϸ״̬����
#define GS_FREE  						0									//����״̬
#define	GS_PLAYING				        100									//��Ϸ״̬
#define GS_ADDGOLDING   				101									//��ע״̬

//����ԭ��
#define GO_NORMAL_FINISH			    0x10								//��������

//���״̬
#define NO_CARD					        0									//����״̬
#define INIT_CARD						1									//��ʼ״̬

//�˿�����
#define CARD_COUNT						3									//�˿�����
//////////////////////////////////////////////////////////////////////////
//����������ṹ

//�����붨��

#define SUB_S_GAME_START				100									//��Ϸ��ʼ
#define SUB_S_ADD_GOLD					101									//��ע���
#define SUB_S_INIT_CARD					102									//��ʼ����
#define SUB_S_USER_LEFT     	    	110									//�м�ǿ��
#define SUB_S_GAME_END					111									//��Ϸ����

//��Ϣ�ṹ��

//����״̬
struct CMD_S_StatusFree
{
	LONG								dwBasicGold;						//�������
};

//��ע״̬
struct CMD_S_StatusAddGold
{
	WORD				 				wCurrentUser;						//��ǰ���
	WORD						        wBankerStation;				    	//ׯ��λ��
	BOOL						        bAddGoldEnd[GAME_PLAYER];	    	//��ע����
	LONG								dwBasicGold;						//�������
	LONG								lMaxGold;							//�����ע
	LONG								lBasicGold;							//�������
	LONG								lTableGold[2*GAME_PLAYER];			//������
};

//��Ϸ״̬
struct CMD_S_StatusPlay
{
	WORD				 				wCurrentUser;						//��ǰ���
	WORD						        wBankerStation;				    	//ׯ��λ��
	BYTE								cbPlayStatus[GAME_PLAYER];			//��Ϸ״̬
	BYTE								cbTableCardCount[GAME_PLAYER];		//�˿���Ŀ
	BYTE								cbTableCardArray[GAME_PLAYER][13];	//�˿�����
	LONG								lMaxGold;							//�����ע
	LONG								lBasicGold;							//�������
	LONG								lTableGold[2*GAME_PLAYER];			//������
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{	
	WORD						        wBankerStation;				    	//ׯ��λ��
	WORD				 				wCurrentUser;						//��ǰ���
	LONG								lMaxGold;							//�����ע
	LONG								lTurnBasicGold;						//������ע
	BYTE								cbCardData[GAME_PLAYER];			//�û��˿�
};

//��ע���
struct CMD_S_AddGold
{
	WORD								wCurrentUser;						//��ǰ�û�
	WORD								wPrevUser;							//��һ�û�
	LONG								lLastAddGold;						//��ע��Ŀ
	LONG								lMaxGold;							//�����ע
};

//��ʼ����
struct CMD_S_InitCard
{	
	BYTE								cbCardData[GAME_PLAYER][CARD_COUNT];//�û��˿�
	BYTE								cbCardSum;	            			//�˿���ֵ
	WORD								wDiceCount;							//���ӵ���
};

//�û�ǿ��
struct CMD_S_UserLeft
{
	WORD								wUserChairID;						//ǿ���û�
	BOOL								bAddGoldEnd;						//��ע����
};

//��Ϸ����
struct CMD_S_GameEnd
{
	LONG								lTax;								//��Ϸ˰��
	LONG								lGameGold[GAME_PLAYER];				//��Ϸ�÷�
	BYTE								cbUserCard[GAME_PLAYER];			//�û��˿�
	BYTE								cbCardSum[GAME_PLAYER];	   	    	//�˿���ֵ
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

//�����붨��
#define SUB_C_ADD_GOLD					1									//�û���ע
#define SUB_C_CANCEL_GOLD				2   								//ȡ����ע

//��Ϣ�ṹ��

//�û���ע
struct CMD_C_AddGold
{
	LONG								lGold;								//��ע��Ŀ
	WORD								wChairID;							//��ע���
};

//////////////////////////////////////////////////////////////////////////

#endif