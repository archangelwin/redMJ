#ifndef CALL_SCORE_HEAD_FILE
#define CALL_SCORE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"

#define IDM_LAND_SCORE				(WM_USER+104)						//�з���Ϣ

//////////////////////////////////////////////////////////////////////////

//������ͼ��
class CCallScore : public CWnd
{
	/*
	TransButton                    m_Score120;            //120��
	TransButton                    m_Score115;            //115��
	TransButton                    m_Score110;            //110��
	TransButton                    m_Score105;            //105��
	TransButton                    m_Score100;            //100��
	TransButton                    m_Score95;             //95��
	TransButton                    m_Score90;             //90��
	TransButton                    m_Score85;             //85��
	*/
	TransButton                    m_Score80;             //80��
	TransButton                    m_Score75;             //75��
	TransButton                    m_Score70;             //70��
	TransButton                    m_Score65;             //65��
	TransButton                    m_Score60;             //60��
	TransButton                    m_Score55;             //55��
	TransButton                    m_Score50;             //50��
	TransButton                    m_Score45;             //45��
	TransButton                    m_Score40;             //40��
	TransButton                    m_Score35;             //35��
	TransButton                    m_Score30;             //30��
	TransButton                    m_Score25;             //25��
	TransButton                    m_Score20;             //20��
	TransButton                    m_Score15;             //15��
	TransButton                    m_Score10;             //10��
	TransButton                    m_Score5;              //5��
	TransButton					   m_btGiveUpScore;		  //����

	CSkinImage					   m_ImageScoreBack;			  //����ͼ��

	//�з���Ϣ
public:
	BYTE						   m_cbCount;					//�зִ���
	BYTE						   m_cbPriScore;				//�ϴνз�
	bool						   m_bMustCall;					//������=7�� �����
	
	//��������
public:
	//���캯��
	CCallScore();

	//�ػ�����
	void ReloadView();

	//��������
	virtual ~CCallScore();

	
	//��Ϣ����
protected:
	//�ػ�����
	afx_msg void OnPaint();
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//�з�OK��ť
	afx_msg void OnCallScore80();
	//�з�OK��ť
	afx_msg void OnCallScore75();
	//�з�OK��ť
	afx_msg void OnCallScore70();
	//�з�OK��ť
	afx_msg void OnCallScore65();
	//�з�OK��ť
	afx_msg void OnCallScore60();
	//�з�OK��ť
	afx_msg void OnCallScore55();
	//�з�OK��ť
	afx_msg void OnCallScore50();
	//�з�OK��ť
	afx_msg void OnCallScore45();
	//�з�OK��ť
	afx_msg void OnCallScore40();
	//�з�OK��ť
	afx_msg void OnCallScore35();
	//�з�OK��ť
	afx_msg void OnCallScore30();
	//�з�OK��ť
	afx_msg void OnCallScore25();
	//�з�OK��ť
	afx_msg void OnCallScore20();
	//�з�OK��ť
	afx_msg void OnCallScore15();
	//�з�OK��ť
	afx_msg void OnCallScore10();
	//�з�OK��ť
	afx_msg void OnCallScore5();
	//������ť
	afx_msg void OnGiveUpScore();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif