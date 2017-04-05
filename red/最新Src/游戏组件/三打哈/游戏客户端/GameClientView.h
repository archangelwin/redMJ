#include "../../../�������/����ؼ�/TransButton.h"

#pragma once

#include "Stdafx.h"
#include "ScoreView.h"
#include "CallCardWnd.h"
#include "CardControl.h"
#include "ConcealCardView.h"
#include "CallScore.h"
#include "ScoreCard.h"




//////////////////////////////////////////////////////////////////////////
//��Ϣ����

//��ť��Ϣ
#define IDM_START					(WM_USER+100)						//��ʼ��Ϣ
#define IDM_OUT_CARD				(WM_USER+101)						//������Ϣ
#define IDM_OUT_PROMPT				(WM_USER+102)						//��ʾ��Ϣ
#define IDM_SEND_CONCEAL			(WM_USER+103)						//������Ϣ
#define IDM_SURRENDER				(WM_USER+105)						//Ͷ����Ϣ

//���ܰ�ť
#define IDM_CONCEAL_CARD			(WM_USER+110)						//�鿴����
#define IDM_REQUEST_LEAVE			(WM_USER+111)						//�����뿪
#define IDM_LAST_TURN_CARD			(WM_USER+112)						//�����˿�
#define IDM_TRUSTEE_CONTROL			(WM_USER+113)						//�йܿ���

//////////////////////////////////////////////////////////////////////////

//��Ϸ��ͼ
class CGameClientView : public CGameFrameView
{
	//��ʾ����
protected:
	bool							m_bDeasilOrder;						//����˳��
	bool							m_bWaitConceal;						//�ȴ���־
	bool							m_bLastTurnCard;					//�����˿�

	//��Ϸ����
protected:
	WORD							m_wCardScore;						//��ҵ÷�
	WORD							m_wBankerUser;						//ׯ���û�
	WORD							m_wBankerScore;						//ׯ�ҷ���
	bool							m_Help;								//����

	//������Ϣ
protected:
	BYTE							m_cbCallColor;						//���ƻ�ɫ
	BYTE							m_cbCallCount;						//������Ŀ
	BYTE							m_cbMainValue;						//������ֵ
	WORD							m_wCallCardUser;					//�����û�
	BYTE							m_cbValueOrder[2];					//������ֵ

	//״̬����
public:
	bool							m_bLandTitle;						//������־
	bool							m_bPass[GAME_PLAYER];				//��������
	BYTE							m_bScore[GAME_PLAYER];				//�û��з�
	BYTE							m_bCardCount[GAME_PLAYER];			//�˿���Ŀ
	WORD							m_wLandUser;						//�����û�
	BYTE							m_cbLandScore;						//��������

	//λ����Ϣ
protected:
	CSize							m_SizeBanker;						//ׯ�Ҵ�С
	CSize							m_SizeStation;						//״̬��С
	CPoint							m_PointBanker[GAME_PLAYER];			//ׯ��λ��

	//λͼ����
protected:
	CSkinImage						m_ImageBack;						//������Դ
	//CSkinImage						m_ImageBackGround;					//������Դ
	CSkinImage						m_ImageBanker;						//ׯ����Դ
	CSkinImage						m_ImageLastTurn;					//���ֱ�־
	CSkinImage						m_ImageColorFlag;					//��ɫ��־
	CSkinImage						m_ImageWaitConceal;					//�ȴ���Դ
	//CSkinImage						m_ImageStationBack;					//״̬��Դ
	CSkinImage						m_ImageStationTitle;				//״̬��Դ
	CSkinImage						m_ImageHeadBg;						//ͷ�񱳾�
	CSkinImage						m_ImageLeve1;					    //�ȼ�1
	CSkinImage						m_ImageLeve2;					    //�ȼ�2
	CSkinImage						m_ImageLeve3;						//�ȼ�3
	CSkinImage						m_ImageLeve4;						//�ȼ�4
	CSkinImage						m_ImageLeve5;						//�ȼ�5
	CSkinImage						m_ImageLeve6;						//�ȼ�6
	CSkinImage						m_ImageHelp;						//����

	//��ť�ؼ�
public:
	TransButton						m_btStart;							//��ʼ��ť
	TransButton						m_btOutCard;						//���ư�ť
	TransButton						m_btOutPrompt;						//��ʾ��ť
	TransButton						m_btSendConceal;					//���װ�ť
	TransButton						m_btSurrender;						//Ͷ����ť
	
	//���ܰ�ť
public:
	TransButton						m_btConcealCard;					//�鿴����
	//TransButton						m_btRuquestLeave;					//�����뿪
	TransButton						m_btLastTurnCard;					//�����˿�
	TransButton						m_btStusteeControl;					//�Ϲܿ���

	//�˿˿ؼ�
public:
	CScoreCard						m_CardScore;						//�÷��˿�
	CCardControl					m_HandCardControl;					//�����˿�
	CCardControl					m_UserCardControl[4];				//�˿���ͼ

	//�ؼ����
public:
	CScoreView						m_ScoreView;						//������ͼ
	CToolTipCtrl					m_ToolTipCtrl;						//��ʾ�ؼ�
	CCallCardWnd					m_CallCardWnd;						//���ƴ���
	CConcealCardView				m_ConcealCardView;					//���ƴ���
	CCallScore						m_CallScore;						//�зִ���


	//��������
public:
	//���캯��
	CGameClientView();
	//��������
	virtual ~CGameClientView();

	//���غ���
public:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//�̳к���
private:
	//���ý���
	virtual void ResetGameView();
	//�����ؼ�
	virtual void RectifyGameView(int nWidth, int nHeight);
	//�滭����
	virtual void DrawGameView(CDC * pDC, int nWidth, int nHeight);

	virtual void DrawGameView2(CDC * pDC, int nWidth, int nHeight){};

	//���ú���
public:
	//�û�˳��
	void SetUserOrder(bool bDeasilOrder);
	//��ȡ˳��
	bool IsDeasilOrder() { return m_bDeasilOrder; }

	//��Ϸ��Ϣ
public:
	//���õ÷�
	void SetCardScore(WORD wCardScore);
	//ׯ���û�
	void SetBankerUser(WORD wBankerUser);
	//���õȴ�
	void SetWaitConceal(bool bWaitConceal);
	//��������
	void SetLastTurnCard(bool bLastTurnCard);
	//��������
	void SetValueOrder(BYTE cbMainValue, BYTE cbValueMySelf, BYTE cbValueOther);
	//��������
	void SetCallCardInfo(WORD wCallCardUser, BYTE cbCallColor, BYTE cbCallCount);
	//�ڿӷ���
	void SetLandScore(WORD wChairID, BYTE bLandScore);
	//���÷���
	void SetPassFlag(WORD wChairID, bool bPass);
	//�ڿӵ���
	void SetLandUser(WORD wChairID, BYTE bLandScore);
	//�ڿӷ���
	void SetBankerScore(WORD cbBankerScore);
	//����
	void SetHelp(bool bHelp);

	//��������
protected:
	//��������
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos);

	//��Ϣӳ��
protected:
	//��ʼ��ť
	afx_msg void OnStart();
	//���ư�ť
	afx_msg void OnOutCard();
	//��ʾ��ť
	afx_msg void OnOutPrompt();
	//���װ�ť
	afx_msg void OnSendConceal();
	//Ͷ����ť
	afx_msg void OnSurrender();
	//�鿴����
	afx_msg void OnConcealCard();
	//�����뿪
	afx_msg void OnRuquestLeave();
	//�����˿�
	afx_msg void OnLastTurnCard();
	//�Ϲܿ���
	afx_msg void OnStusteeControl();
	//��������
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	afx_msg void OnRButtonUp(UINT nFlags, CPoint Point);
	//���˫��
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

//////////////////////////////////////////////////////////////////////////
