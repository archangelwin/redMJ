//-------------------------------------------------------------------------------------------------------
//
//							Wave.h �����ļ��¼�����
//


//----------------------------------�����¼�-------------------------------------------------------------
//���������
#define WAV_SITDOWN			1

//���̫��
#define WAV_TOOSLOWLY		2

//��Ϸ��ʼ
#define WAV_START			3

//��Ϸ����
#define WAV_END				4

//Ӯ
#define WAV_WIN				5

//��
#define WAV_LOST			6

//----------------------------------թ��--------------------------------------------------------------
#define WAV_GOLDFLOWER_BEGIN 1000

//��ע
#define WAV_GOLDFLOWER_DO_GOLD			WAV_GOLDFLOWER_BEGIN+5

//��ע
#define WAV_GOLDFLOWER_FOLLOW			WAV_GOLDFLOWER_BEGIN+6

//��ע
#define WAV_GOLDFLOWER_ADD_GOLD			WAV_GOLDFLOWER_BEGIN+7

//����
#define WAV_GOLDFLOWER_GIVEUP			WAV_GOLDFLOWER_BEGIN+8

//����
#define WAV_GOLDFLOWER_BIPAI			WAV_GOLDFLOWER_BEGIN+9

//----------------------------------���----------------------------------------------------------------
#define WAV_SHOWHAND_BEGIN 2000

//��ע
#define WAV_SHOWHAND_DO_GOLD			WAV_GOLDFLOWER_DO_GOLD

//��ע
#define WAV_SHOWHAND_FOLLOW				WAV_GOLDFLOWER_FOLLOW

//��ע
#define WAV_SHOWHAND_ADD_GOLD			WAV_GOLDFLOWER_ADD_GOLD

//����
#define WAV_SHOWHAND_GIVEUP				WAV_GOLDFLOWER_GIVEUP

//����
#define WAV_SHOWHAND_BIPAI				WAV_GOLDFLOWER_BIPAI

//���
#define WAV_SHOWHAND_SHOWHAND			WAV_SHOWHAND_BEGIN+1
//------------------------------------------------------------------------------------------------------


//----------------------------------������----------------------------------------------------------------
#define WAV_LAND 3000

//����
#define WAV_LAND_OUTCARD				WAV_LAND+100        //����һ ������
#define WAV_LAND_OUTCARD_SINGE			WAV_LAND_OUTCARD+1  //��˳
#define WAV_LAND_OUTCARD_DOUBLE			WAV_LAND_OUTCARD+2  //˫˳
#define WAV_LAND_OUTCARD_GIVEUP			WAV_LAND_OUTCARD+3  //��Ҫ
#define WAV_LAND_OUTCARD_TEAM_BEHIND	WAV_LAND_OUTCARD+4  //ͬ����ƺ�
#define WAV_LAND_OUTCARD_TEAM_ON		WAV_LAND_OUTCARD+5  //ͬ�����ʱ
#define WAV_LAND_OUTCARD_DS_BEHIND		WAV_LAND_OUTCARD+6  //���ֳ��ƺ�
#define WAV_LAND_OUTCARD_DS_WIN			WAV_LAND_OUTCARD+7  //����Ӯ

//����
#define WAV_LAND_CALLSCORE				WAV_LAND+200		 //����
#define WAV_LAND_CALLSCORE_BANKER		WAV_LAND_CALLSCORE+1 //������

//����
#define WAV_LAND_END					WAV_LAND+300

//Ӯ��
#define WAV_LAND_WIN					WAV_LAND+400

//------------------------------------------------------------------------------------------------------














