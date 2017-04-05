#pragma once

#include "Stdafx.h"
#include "ScoreView.h"
#include "CardControl.h"

//////////////////////////////////////////////////////////////////////////
//��Ϣ����

#define IDM_START					(WM_USER+100)						//��ʼ��Ϣ
#define IDM_OUT_CARD				(WM_USER+101)						//������Ϣ
#define IDM_PASS_CARD				(WM_USER+102)						//��������
#define IDM_CAVERN_SCORE			(WM_USER+103)						//�з���Ϣ

//////////////////////////////////////////////////////////////////////////

//��Ϸ��ͼ
class CGameClientView : public CGameFrameView
{
	//��Ϸ����
protected:
	LONG							m_lBaseScore;						//��������
	WORD							m_wCavernUser;						//�ڿ��û�
	BYTE							m_bCavernScore;						//�ڿӷ���

	//���ñ���
protected:
	bool							m_bDeasilOrder;						//����˳��

	//״̬����
public:
	bool							m_bCavernTitle;						//�ڿӱ�־
	bool							m_bPass[GAME_PLAYER];				//��������
	BYTE							m_bScore[GAME_PLAYER];				//�û��з�
	BYTE							m_bCardCount[GAME_PLAYER];			//�˿���Ŀ

	//λ����Ϣ
public:
	CSize							m_CavernSize;						//�ڿӱ�־
	CPoint							m_ptScore[GAME_PLAYER];				//�з�λ��
	CPoint							m_ptCavern[GAME_PLAYER];			//����λ��

	//λͼ����
protected:
	CSkinImage						m_ImageBack;						//������Դ
	CSkinImage						m_ImageBackGround;					//������Դ
	CSkinImage						m_ImageScore;						//����ͼƬ
	CSkinImage						m_ImageCavern;						//ׯ��ͼƬ

	//��ť�ؼ�
public:
	CSkinButton						m_btStart;							//��ʼ��ť
	CSkinButton					    m_btOutCard;						//���ư�ť
	CSkinButton						m_btPassCard;						//������ť
	CSkinButton						m_btOneScore;						//1 �ְ�ť
	CSkinButton						m_btTwoScore;						//2 �ְ�ť
	CSkinButton						m_btThreeScore;						//3 �ְ�ť
	CSkinButton					    m_btGiveUpScore;					//������ť

	//�˿˿ؼ�
public:
	CCardControl					m_HandCardControl;					//�����˿�
	CCardControl					m_BackCardControl;					//�����˿�
	CCardControl					m_UserCardControl[3];				//�˿���ͼ
	CCardControl					m_LeaveCardControl[2];				//�����˿�

	//�ؼ����
public:
	CScoreView						m_ScoreView;						//������ͼ

	//��������
public:
	//���캯��
	CGameClientView();
	//��������
	virtual ~CGameClientView();

	//�̳к���
private:
	//���ý���
	virtual void ResetGameView();
	//�����ؼ�
	virtual void RectifyGameView(int nWidth, int nHeight);
	//�滭����
	virtual void DrawGameView(CDC * pDC, int nWidth, int nHeight);
	
	//���ú���
public:
	//�û�˳��
	void SetUserOrder(bool bDeasilOrder);
	//��ȡ˳��
	bool IsDeasilOrder() { return m_bDeasilOrder; }

	//���ܺ���
public:
	//��������
	void SetBaseScore(LONG lBaseScore);
	//��ʾ��ʾ
	void ShowCavernTitle(bool bCavernTitle);
	//���÷���
	void SetPassFlag(WORD wChairID, bool bPass);
	//�˿���Ŀ
	void SetCardCount(WORD wChairID, BYTE bCardCount);
	//�ڿӷ���
	void SetCavernUser(WORD wChairID, BYTE bCavernScore);
	//�ڿӷ���
	void SetCavernScore(WORD wChairID, BYTE bCavernScore);

	//��Ϣӳ��
protected:
	//��ʼ��ť
	afx_msg void OnStart();
	//���ư�ť
	afx_msg void OnOutCard();
	//������ť
	afx_msg void OnPassCard();
	//�зְ�ť
	afx_msg void OnOneScore();
	//�зְ�ť
	afx_msg void OnTwoScore();
	//�зְ�ť
	afx_msg void OnThreeScore();
	//������ť
	afx_msg void OnGiveUpScore();
	//��������
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	afx_msg void OnRButtonUp(UINT nFlags, CPoint Point);
	//���˫��
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
