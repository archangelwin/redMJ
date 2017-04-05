#ifndef SYSTEM_OPTION_HEAD_FILE
#define SYSTEM_OPTION_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////


//ȫ��������
class CGlobalOption
{
	//��Ϣ����
public:
	bool							m_bShowInOutMessage;				//������Ϣ

	//��ɫ����
public:
	COLORREF						m_crChatTX;							//��������
	COLORREF						m_crMsgName;						//������Ϣ
	COLORREF						m_crMsgNormal;						//��ͨ��Ϣ
	COLORREF						m_crMsgSysHead;						//ϵͳ��Ϣ
	COLORREF						m_crMsgSysString;					//ϵͳ��Ϣ

	CFont							m_Font;

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