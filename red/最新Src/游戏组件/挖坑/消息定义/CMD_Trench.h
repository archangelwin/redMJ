#ifndef CMD_TRENCH_HEAD_FILE
#define CMD_TRENCH_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//�����궨��

//��Ϸ����
#define KIND_ID						2810							//��Ϸ I D
#define GAME_PLAYER					3									//��Ϸ����
#define GAME_NAME					TEXT("�ڿ���Ϸ")					//��Ϸ����

//��Ϸ����
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_GOLD|GAME_GENRE_MATCH)

//��Ϸ״̬
#define GS_WK_FREE					GS_FREE								//�ȴ���ʼ
#define GS_WK_SCORE					GS_PLAYING							//�з�״̬
#define GS_WK_PLAYING				GS_PLAYING+1						//��Ϸ����

//////////////////////////////////////////////////////////////////////////
//����������ṹ

#define SUB_S_SEND_CARD				100									//��������
#define SUB_S_CAVERN_SCORE			101									//�з�����
#define SUB_S_GAME_START			102									//��Ϸ��ʼ
#define SUB_S_OUT_CARD				103									//�û�����
#define SUB_S_PASS_CARD				104									//��������
#define SUB_S_GAME_END				105									//��Ϸ����

//��Ϸ״̬
struct CMD_S_StatusFree
{
	LONG							lBaseScore;							//��������
};

//��Ϸ״̬
struct CMD_S_StatusScore
{
	LONG							lBaseScore;							//��������
	WORD				 			wCurrentUser;						//��ǰ���
	BYTE							bCavernScore;						//�ڿӷ���
	BYTE							bScoreInfo[3];						//�з���Ϣ
	BYTE							bCardData[16];						//�����˿�
};

//��Ϸ״̬
struct CMD_S_StatusPlay
{
	LONG							lBaseScore;							//��������
	WORD							wCavernUser;						//�������
	WORD				 			wCurrentUser;						//��ǰ���
	BYTE							bCavernScore;						//�ڿӷ���
	WORD							wLastOutUser;						//���Ƶ���
	BYTE							bBackCard[4];						//�����˿�
	BYTE							bCardData[20];						//�����˿�
	BYTE							bCardCount[3];						//�˿���Ŀ
	BYTE							bTurnCardCount;						//��������
	BYTE							bTurnCardData[20];					//�����б�
};

//�����˿�
struct CMD_S_SendCard
{
	WORD				 			wCurrentUser;						//��ǰ���
	BYTE							bCardData[16];						//�˿��б�
};

//�û��з�
struct CMD_S_CavernScore
{
	WORD							bCavernUser;						//�з����
	WORD				 			wCurrentUser;						//��ǰ���
	BYTE							bCavernScore;						//�ϴνз�
	BYTE							bCurrentScore;						//��ǰ�з�
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	WORD				 			wCavernUser;						//�ڿ����
	BYTE							bCavernScore;						//�ڿӷ���
	WORD				 			wCurrentUser;						//��ǰ���
	BYTE							bBackCard[4];						//�����˿�
};

//�û�����
struct CMD_S_OutCard
{
	BYTE							bCardCount;							//������Ŀ
	WORD				 			wCurrentUser;						//��ǰ���
	WORD							wOutCardUser;						//�������
	BYTE							bCardData[20];						//�˿��б�
};

//��������
struct CMD_S_PassCard
{
	BYTE							bNewTurn;							//һ�ֿ�ʼ
	WORD				 			wPassUser;							//�������
	WORD				 			wCurrentUser;						//��ǰ���
};

//��Ϸ����
struct CMD_S_GameEnd
{
	LONG							lGameTax;							//��Ϸ˰��
	LONG							lGameScore[3];						//��Ϸ����
	BYTE							bCardCount[3];						//�˿���Ŀ
	BYTE							bCardData[52];						//�˿��б� 
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_CAVERN_SCORE			1									//�û��з�
#define SUB_C_OUT_CART				2									//�û�����
#define SUB_C_PASS_CARD				3									//��������

//�û��з�
struct CMD_C_CavernScore
{
	BYTE							bCavernScore;						//�ڿӷ���
};

//�������ݰ�
struct CMD_C_OutCard
{
	BYTE							bCardCount;							//������Ŀ
	BYTE							bCardData[20];						//�˿��б�
};

//////////////////////////////////////////////////////////////////////////

#endif