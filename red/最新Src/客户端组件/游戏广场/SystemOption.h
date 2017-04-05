#ifndef SYSTEM_OPTION_HEAD_FILE
#define SYSTEM_OPTION_HEAD_FILE

#pragma once

#include "Stdafx.h"

//��˵��
class CListKind;
class CListServer;

//////////////////////////////////////////////////////////////////////////
//ö�ٶ���

#define REG_GLOBAL_OPTIONS			TEXT("GlobalOption")				//ȫ������

//����ģʽ
enum enInviteMode
{
	enInviteMode_All					=1,								//ȫ����ʾ
	enInviteMode_Friend					=2,								//������ʾ
	enInviteMode_None					=3,								//ȫ����ʾ
};

//�ʻ�����
enum enAcountsRule
{
	enAcountsRule_None					=1,								//����¼��Ϣ
	enAcountsRule_Accounts				=2,								//��ס�ʻ�
	enAcountsRule_AccountsAndPass		=3,								//�ʻ�������
};

//////////////////////////////////////////////////////////////////////////

//����������Ϣ
class CServerOption
{
	//���Ա���
public:
	const WORD						m_wServerID;						//�����ʾ
	const CListServer 				* m_pListServer;					//��Ϸ����
	

	//Я������
public:
	bool							m_bPassword;						//��������
	TCHAR							m_szPassword[PASS_LEN];				//��������

	//��������
public:
	//���캯��
	CServerOption(WORD wServerID, CListServer * pListServer);
	//��������
	virtual ~CServerOption();

	//���ܺ���
public:
	//��������
	void LoadOptionParameter();
	//��������
	void SaveOptionParameter();
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ������Ϣ
class CGameOption
{
	//���Ա���
public:
	const WORD						m_wKindID;							//��Ϸ��ʾ
	CListKind 						* m_pListKind;						//��Ϸ����

	//��Ϸ������
public:
	LONG							m_lMaxScore;						//��߷��� 
	LONG							m_lLessScore;						//��ͷ���
	bool							m_bLimitScore;						//���Ʒ���

	//��ʱ����
public:
	WORD							m_wNetDelay;						//������ʱ
	bool							m_bLimitDelay;						//������ʱ

	//��������
public:
	WORD							m_wFleeRate;						//������
	bool							m_bLimitFlee;						//���ƶ���

	//ʤ������
public:
	WORD							m_wWinRate;							//ʤ����
	bool							m_bLimitWin;						//����ʤ��

	//��������
public:
	//���캯��
	CGameOption(WORD wKindID, CListKind * pListKind);
	//��������
	virtual ~CGameOption();

	//���ܺ���
public:
	//��������
	void LoadOptionParameter();
	//��������
	void SaveOptionParameter();
};

//////////////////////////////////////////////////////////////////////////

//��˵��
typedef CArrayTemplate<CGameOption *> CGameOptionArray;
typedef CArrayTemplate<CServerOption *> CServerOptionArray;

//ȫ��������
class CGlobalOption
{
	//ȫ������
public:
	bool							m_bExpandedList;					//չ���б�
	enAcountsRule					m_enAcountsRule;					//�ʻ�����
	bool							m_bDisableBgSound;					//�Ƿ񱳾�����

	//��������
public:
	bool							m_bLimitDetest;						//�������
	bool							m_bCheckSameIP;						//Ч���ַ

	//��Ϣ����
public:
	bool							m_bSaveWisper;						//����˽��
	bool							m_bShowInOutMessage;				//������Ϣ
	bool							m_bOnlyFriendMessage;				//������Ϣ
	bool							m_bHideDetestMessage;				//�����Ϣ

	//��������
public:
	bool							m_bAutoSit;							//�Զ�����
	enInviteMode					m_InviteMode;						//����ģʽ

	//��ɫ����
public:
	COLORREF						m_crChatTX;							//��������
	COLORREF						m_crMsgName;						//������Ϣ
	COLORREF						m_crMsgNormal;						//��ͨ��Ϣ
	COLORREF						m_crMsgSysHead;						//ϵͳ��Ϣ
	COLORREF						m_crMsgSysString;					//ϵͳ��Ϣ
	COLORREF						m_crServerListTX;					//�б���ɫ
	COLORREF						m_crServerListBK;					//�б��ɫ

	//�ڲ�����
private:
	CGameOptionArray				m_GameOptionArray;					//��Ϸ����
	CServerOptionArray				m_ServerOptionArray;				//��������

	//��������
public:
	//���캯��
	CGlobalOption();
	//��������
	virtual ~CGlobalOption();

	//���ܺ���
public:
	//��������
	void LoadOptionParameter();
	//��������
	void SaveOptionParameter();
	//��Ϸ����
	CGameOption * GetGameOption(CListKind * pListKind);
	//��������
	CServerOption * GetServerOption(CListServer * pListServer);

	//���ֲ��ź���
	bool PlayMedia(LPCTSTR pFile);
	bool CloseMedia();

	int m_ScreenW,m_ScreenH,m_ScreenBits,m_ScreenFrequency;
	bool SetDisplay(int nWidth,int nHeight,int nBits,int nFrequency);
	bool GetDisplay(int &nWidth,int &nHeight,int &nBits,int &nFrequency);
	void SetDisplayDefault();
};

//////////////////////////////////////////////////////////////////////////

//ȫ����Ϣ 
extern	CGlobalOption					g_GlobalOption;					//ϵͳ����

//////////////////////////////////////////////////////////////////////////

#endif