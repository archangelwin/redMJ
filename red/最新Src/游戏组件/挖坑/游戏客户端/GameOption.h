#pragma once

#include "Stdafx.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////

//���ض���
#define MAX_PELS					25									//��С����
#define LESS_PELS					10									//��С����
#define DEFAULT_PELS				18									//Ĭ������

//����ģʽ
enum enSoundMode
{
	enNoSound,						//û������
	enNormalSound,					//��ͳ����
	enMandarinSound,				//��ͨ������
	enShanXiSound,					//����������
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ����
class CGameOption : public CSkinDialogEx
{
	//��������
public:
	bool							m_bDeasilOrder;						//����˳��
	DWORD							m_dwCardHSpace;						//�˿�����
	enSoundMode						m_GameSoundMode;					//����ģʽ

	//�ؼ�����
public:
	CSkinButton						m_btOK;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť
	CSkinButton						m_btDefault;						//Ĭ�ϰ�ť

	//��������
public:
	//���캯��
	CGameOption();
	//��������
	virtual ~CGameOption();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ����Ϣ
	virtual void OnOK();

	//��Ϣӳ��
protected:
	//Ĭ�ϲ���
	afx_msg void OnDefault();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
