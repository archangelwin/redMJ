#pragma once

#include "ximage/ximage.h"

#define MAX_PLAYER      6


#define SCP_T            1
#define SCP_TL           2
#define SCP_L            3
#define SCP_BL           4
#define SCP_B            5
#define SCP_BR           6
#define SCP_R            7
#define SCP_TR           8



#define GFDlg ((CGameFrameDlg*)AfxGetMainWnd())

class CShowChat;
extern CShowChat ShowChat;
LPPOINT GAME_FRAME_CLASS GetChatPt();

// CShowChat

class CShowChat
{
public:
	//CxImage			m_ChatImg_T;	//���챳��
	//CxImage			m_ChatImg_B;	//���챳��
	//CxImage			m_ChatImg_L;	//���챳��
	//CxImage			m_ChatImg_R;	//���챳��
	//CxImage			m_ChatImg_BL;	//���챳��
	//CxImage			m_ChatImg_BR;	//���챳��
	CSkinImage			m_ChatImg_T;	//���챳��
	CSkinImage			m_ChatImg_B;	//���챳��
	CSkinImage			m_ChatImg_L;	//���챳��
	CSkinImage			m_ChatImg_R;	//���챳��
	CSkinImage			m_ChatImg_BL;	//���챳��
	CSkinImage			m_ChatImg_BR;	//���챳��

	CString			m_szMsg[MAX_PLAYER];		//��������
	int				m_lStartTick[MAX_PLAYER];	//��ʼ����ʾʱ��
	int				m_lTime[MAX_PLAYER];		//��ʾʱ��

	POINT			PosPt[8];//8����λ������

public:
	CShowChat();
	~CShowChat();
	//ʹ�÷���
	//CxImage *GetChairPos(WORD wViewChair,int &x,int &y,int &Word_x,int &Word_y);
	CSkinImage *GetChairPos(WORD wViewChair,int &x,int &y,int &Word_x,int &Word_y);

	bool ShowChat(LPCTSTR szString,tagUserData *pUser,int lTime=3000);


	void OnDraw(CDC *pDC);//Ҫ������Ӧ��OnPaint�¼���
};


