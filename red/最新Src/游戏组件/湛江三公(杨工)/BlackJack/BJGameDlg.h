#pragma once

#include "Stdafx.h"
#include "BJGameView.h"
#include "..\��Ϣ����\CMD_BlackJack.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//��Ϣ����
#define IDM_GAME_START				WM_USER+120							//��ʼ��ť��Ϣ
#define IDM_ADD_GOLD				WM_USER+121							//��ע��ť��Ϣ
#define IDM_GIVE_UP				    WM_USER+122							//ȡ����ť��Ϣ

//��Ϸ�Ի���
class CBJGameDlg : public CGameFrameDlg
{
	
	//��Ϸ����
protected:
	LONG							m_lTurnMaxGold;						//�����ע
	LONG							m_lTurnBasicGold;					//��ע��Ŀ
	WORD							m_wCardSum;			                //�˿���ֵ
	BOOL							m_bCutCard;			                //���Ʊ�ʶ

	//��������
protected:
	bool							m_bMeAddGold;						//�Ƿ���ע
	LONG							m_lGoldShow;						//��ע����
	TCHAR							m_szName[GAME_PLAYER][NAME_LEN];	//�������

	//�ؼ�����
protected:
	CBJGameView					    m_GameView;							//��Ϸ��ͼ
	
	//��������
public:
	//���캯��
	CBJGameDlg();
	//��������
	virtual ~CBJGameDlg();

	//����̳�
private:
	//��ʼ����
	virtual bool InitGameFrame();
	//���ÿ��
	virtual void ResetGameFrame();
	//��Ϸ����
	virtual void OnGameOptionSet();
	//ʱ����Ϣ
	virtual bool OnTimerMessage(WORD wChairID, UINT nElapse, UINT nTimerID);
	//�Թ�״̬
	virtual void OnLookonChanged(bool bLookonUser, const void * pBuffer, WORD wDataSize);
	//������Ϣ
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);
	//��Ϸ����
	virtual bool OnGameSceneMessage(BYTE cbGameStatus, bool bLookonOther, const void * pBuffer, WORD wDataSize);

	//��Ϣ����
protected:	
	//��Ϸ��ʼ
	bool OnSubGameStart(const void * pBuffer, WORD wDataSize);
	//�û���ע
	bool OnSubAddGold(const void * pBuffer, WORD wDataSize);
	//��ʼ����
	bool OnSubInitCard(const void * pBuffer, WORD wDataSize);
	//������Ϣ
	bool OnSubSendCard(const void * pBuffer, WORD wDataSize);
	//���ǿ��
	bool OnSubUserLeft(const void * pBuffer, WORD wDataSize);
	//��Ϸ����
	bool OnSubGameEnd(const void * pBuffer, WORD wDataSize);

	//��Ϣӳ��
protected:
	//��ʼ��ť	
	LRESULT	OnStart(WPARAM wParam, LPARAM lParam);
	//��ע��ť 
	LRESULT	OnAddGold(WPARAM wParam, LPARAM lParam);
	//������ť
	LRESULT OnGiveUp(WPARAM wParam, LPARAM lParam);	
	
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
