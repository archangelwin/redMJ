#ifndef GAME_FRAME_HEAD_FILE
#define GAME_FRAME_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "DlgControlBar.h"
#include "PlazaViewItem.h"

/////////////////////////////////////////////////////////////////////////////


//�������
class CGameFrame : public CFrameWnd
{
	//�ؼ�����
public:
	CSkinButton							m_btMin;						//��С��ť
	CSkinButton							m_btClose;						//�رհ�ť
	bool								m_bMaxed;						//��󻯱�־
	bool								m_bMaxedC;						//�Ƿ�����󻯱�־
	CSkinButton							m_btMax;						//��󻯰�ť
	CToolTipCtrl						m_ToolTipCtrl;					//��ʾ�ؼ�
	CPlazaViewItem						m_DlgGamePlaza;					//��Ϸ�㳡
	CDlgControlBar						m_DlgControlBar;				//��������

	//CHtmlBrower							*m_pHtmlStatus;					//״̬������

	//������ť
public:
	CSkinButton							m_btButton1;					//���ܰ�ť
	CSkinButton							m_btButton2;					//���ܰ�ť
	CSkinButton							m_btButton3;					//���ܰ�ť
	CSkinButton							m_btButton4;					//���ܰ�ť
	CSkinButton							m_btButton5;					//���ܰ�ť
	CHtmlBrower							*m_pHtmlBrower1;				//�������

	//��Դ����
protected:
	CSkinImage							m_ImageTL;						//���ϱ���
	CSkinImage							m_ImageTM;						//���ϱ���
	CSkinImage							m_ImageTR;						//���ϱ���

//	CSkinImage							m_StatusL;						//״̬��
//	CSkinImage							m_StatusM;						//״̬��
	//��������	
public:
	//���캯��
	CGameFrame();
	//��������
	virtual ~CGameFrame();

	//���غ���
public:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//��Ϣ����
protected:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//��С��Ϣ
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR * lpMMI);
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��С��ť
	afx_msg void OnBnClickedMin();
	//��󻯰�ť
	afx_msg void OnBnClickedMax();
	//�رհ�ť
	afx_msg void OnBnClickedClose();
	//�ı���Ϣ
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//�ر���Ϣ
	afx_msg void OnClose();

	//������ť
protected:
	//���ܰ�ť
	afx_msg void OnBnClickedButton1();
	//���ܰ�ť
	afx_msg void OnBnClickedButton2();
	//���ܰ�ť
	afx_msg void OnBnClickedButton3();
	//���ܰ�ť
	afx_msg void OnBnClickedButton4();
	//���ܰ�ť
	afx_msg void OnBnClickedButton5();

	//�ȼ�
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);

	//��Ϸ���̷����ھ��������
	afx_msg LRESULT OnGameClient(WPARAM wParam, LPARAM lParam);

	//�Զ�����Ϣ
protected:
	//��װ���
	LRESULT OnMessageSetupFinish(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

/////////////////////////////////////////////////////////////////////////////

#endif
