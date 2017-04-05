#ifndef DLG_TOOLBARDLG_HEAD_FILE
#define DLG_TOOLBARDLG_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"

#include "GameFrame.h"
#include "GlobalOption.h"
#include "..\..\�������\����ؼ�\SkinControls.h"


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

class CDialogIX : public CDialog
{
protected:
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};


//������
class CDlgToolBar : public CDialogIX
{
public:
	//���캯��
	CDlgToolBar();
	//��������
	virtual ~CDlgToolBar();

private:
	CSkinImage					m_MainBg;//����ͼƬ
	
	CRgnButton					*m_btChatSend; //���Ͱ�ť
	CRgnButton					*m_btChatDict; //������䰴ť
	CRgnButton					*m_btShowChat; //��/�� ��Ϣ��
	CRgnButton					*m_btShowUserList; //��/���û���
	CEdit						*m_ChatEdit;	//���������

	DWORD						m_dwLastChat;
public:
	IClientKernel						*m_pICK;//�ں˽ӿ�


public:
	afx_msg void OnBnClickedShowChat();//��/�� ��Ϣ��
	afx_msg void OnBnClickedShowUserList();//��/���û���

	//���غ���
protected:
	//��ʼ������
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////
//�û��б��
class CDlgUserList : public CDialogIX
{
public:
	//���캯��
	CDlgUserList();
	//��������
	virtual ~CDlgUserList();

	CImageListCtrl					m_ListUsers;				//�û��б�

	CRgnButton						m_btQuit; //����


	//����Timer
private:
	DWORD m_dwTimes;

	//���غ���
protected:
	//��ʼ������
	virtual BOOL OnInitDialog();
	virtual void OnOK(){return;}
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedHide();//����
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
//////////////////////////////////////////////////////////////////////////

//��Ϣ����
class CDlgChatMsg : public CDialogIX
{
public:
	//���캯��
	CDlgChatMsg();
	//��������
	virtual ~CDlgChatMsg();
	void Show();


	CSkinImage							m_Msg_T;
	CSkinImage							m_Msg_B;
	CSkinImage							m_Msg_L;
	CSkinImage							m_Msg_R;

	CSkinRichEdit						m_ChatMsg;;				//�������

	CRgnButton							m_btQuit; //����

	//����Timer
private:
	DWORD m_dwTimes;

	//���غ���
protected:
	//��ʼ������
	virtual BOOL OnInitDialog();
	virtual void OnOK(){return;}
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedHide();//����

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
//////////////////////////////////////////////////////////////////////////

/*
	CRect rc;
	GetWindowRect(rc);

	m_ToolBar->SetWindowPos(NULL,0,0,397,25,SWP_NOMOVE);
	m_ToolBar->SetWindowPos(NULL,rc.left + 7,rc.bottom - 34,0,0,SWP_NOSIZE);

	m_ChatMsgDlg->SetWindowPos(NULL,0,0,299,159,SWP_NOMOVE);
	m_ChatMsgDlg->SetWindowPos(NULL,rc.left+7,rc.bottom - 195,0,0,SWP_NOSIZE);

	m_DlgUserList->SetWindowPos(NULL,0,0,m_DlgUserList->m_ListUsers.GetWidth(),159,SWP_NOMOVE);
	m_DlgUserList->SetWindowPos(NULL,rc.left+307,rc.bottom - 195,0,0,SWP_NOSIZE);

*/

#endif