#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "CenterService.h"

#include "ServerSystray.h"


//////////////////////////////////////////////////////////////////////////

//���öԻ���
class CSystemOptionDlg : public CDialog
{
public:
	CSystemOptionDlg();
	virtual ~CSystemOptionDlg();

	//���غ���
protected:
	//��ʼ������
	virtual BOOL OnInitDialog();
	//�ؼ����໯
	virtual void DoDataExchange(CDataExchange * pDX);
	//ȷ������
	virtual void OnOK();

	//���ܺ���
public:
	//���ò���
	void SetInitParamter(const CInitParamter & InitParamter);

	//��Ϣӳ��
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//���Ի���
class CCenterServerDlg : public CDialog
{
	//��������
protected:
	bool							m_bAskQuit;							//�˳�ѯ��
	CServerSystray					m_Systray;

	//�������
public:
	CCenterService					m_CenterService;					//��¼����
	CEventServiceHelper				m_EventService;						//�¼�����

	//�ؼ�����
public:
	CRichEditCtrl					m_RichEditCtrl;						//�¼���¼

	//���캯��
public:
	//�������
	CCenterServerDlg();
	//��������
	virtual ~CCenterServerDlg();

	//���غ���
protected:
	//�ؼ����໯
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ����Ϣ
	virtual void OnOK();
	//ȡ������
	virtual void OnCancel();
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//��Ϣ����
protected:
	//��������
	afx_msg void OnBnClickedStartService();
	//ֹͣ����
	afx_msg void OnBnClickedStopService();
	//���÷���
	afx_msg void OnBnClickedInitService();

	//Systray��Ϣ
	afx_msg LRESULT OnSystrayIcon(WPARAM wParam, LPARAM lParam);

	//����װ������������Ϣ
	afx_msg LRESULT OnGameServerRunning(WPARAM wParam, LPARAM lParam);

	//������ӦSystray��Ϣ
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

//////////////////////////////////////////////////////////////////////////
