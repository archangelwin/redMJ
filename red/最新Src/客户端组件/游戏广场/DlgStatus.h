#ifndef DLG_STATUS_HEAD_FILE
#define DLG_STATUS_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//��Ϸ״̬��
class CDlgStatus : public CDialog
{
	//��������
protected:
	WORD								m_wImagePos;					//λͼλ��
	bool								m_bTimer;						//�Ƿ�ʱ���ڹ���
	CWnd								* m_pNotifyWnd;					//֪ͨ����
	CString								m_strMessage;					//��Ϣ�ַ�

	//�ؼ�����
protected:
	CSkinButton							m_btCancel;						//ȡ����ť
	CSkinImage							m_BgImage;
	CSkinImage							m_ImgStatus;

	//��������
public:
	//���캯��
	CDlgStatus();
	//��������
	virtual ~CDlgStatus();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//ȷ������
	virtual void OnOK() { return; };
	//ȡ������
	virtual void OnCancel() { return; };

	//���ܺ���
public:
	//������Ϣ
	bool ShowStatusMessage(LPCTSTR pszMessage, CWnd * pNotifyWnd);
	//���ٴ���
	bool DestroyStatusWnd(CWnd * pNotifyWnd);

	//��Ϣӳ��
protected:
	//�ػ���Ϣ
	afx_msg void OnPaint();
	//ȡ����ť
	afx_msg void OnBnClickedClose();
	//��ʱ����Ϣ
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

//////////////////////////////////////////////////////////////////////////

#endif