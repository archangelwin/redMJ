#pragma once

#include "StdAfx.h"
#include "Resource.h"
#include "Afxcmn.h"

//���Ͷ���Ϣ��
class CShow : public CSkinDialogEx
{
	//��������
public:
	CWnd								* s_pParentWnd;						//������
	
	//��Ϣ����
	long int							m_dwTargetUserID;					//�Ի��û�
	__int64								m_dwTargerAccID;					//ACC ����
	CString								m_strTargerName;					//�û�����
	CString								m_strRoomName;						//��������
	IUserItem							* m_pTargetUserItem;				//Ŀ���û�
	

	//�ؼ�����
public:
	
	CSkinButton							m_BtClose;							//�˳���ť
	CMessageProxyHelper					m_MessageProxyHelper;				//��Ϣ����

	DECLARE_MESSAGE_MAP()
	//��������
public:
	//���캯��
	CShow(CWnd * pParentWnd);
	//��������
	virtual ~CShow();
	//��ʼ������
	virtual BOOL OnInitDialog();
	//���غ���
protected:
	//�ؼ��󶨺���
	virtual void DoDataExchange(CDataExchange * pDX); 
	
	//��Ϣ���ͺ���
	//virtual BOOL PreTranslateMessage(MSG * pMsg);
	//���ܺ��� 

public:
	
	//�˳���ť
	afx_msg void OnBnClickedClose();
	//��ȡλ��
	afx_msg void OnGetMinMaxInfo(MINMAXINFO * lpMMI);
	
};
