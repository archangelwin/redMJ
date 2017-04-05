#ifndef COMMONALITY_HEAD_FILE
#define COMMONALITY_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////
//����ͷ�ļ�

//�������ļ�
#include "..\..\��Ϣ����\CMD_Plaza.h"
#include "..\..\��Ϣ����\CMD_Center.h"

//ȫ��ͷ�ļ�
#include "..\..\�����ļ�\GlobalField.h"
#include "..\..\�����ļ�\GlobalService.h"

//////////////////////////////////////////////////////////////////////////
//���ݿ������

//���ݿ������ʶ
#define	DBR_GP_LOGON_BY_ACCOUNTS	1									//�ʺŵ�½
#define	DBR_GP_LOGON_BY_USERID		2									//I D ��½
#define DBR_GP_REGISTER_ACCOUNTS	3									//ע���ʺ�

//���ݿ������ʶ
#define DBR_GP_LOGON_SUCCESS		100									//��½�ɹ�
#define DBR_GP_LOGON_ERROR			101									//��½ʧ��

//�ʺŵ�½
struct DBR_GP_LogonByAccounts
{
	DWORD							dwClientIP;							//���ӵ�ַ
	TCHAR							szAccounts[NAME_LEN];				//��¼�ʺ�
	TCHAR							szPassWord[PASS_LEN];				//��¼����
	TCHAR							szRealityPass[PASS_LEN];			//��ʵ����
};

//ID ��¼
struct DBR_GP_LogonByUserID
{
	DWORD							dwClientIP;							//���ӵ�ַ
	DWORD							dwUserID;							//�û� I D
	TCHAR							szPassWord[PASS_LEN];				//��¼����
};

//�ʺ�ע��
struct DBR_GP_RegisterAccounts
{
	DWORD							dwClientIP;							//���ӵ�ַ
	WORD							wFaceID;							//ע��ͷ��
	TCHAR							szAccounts[NAME_LEN];				//��¼�ʺ�
	TCHAR							szPassWord[PASS_LEN];				//��¼����
};

//��½�ɹ�
struct DBR_GP_LogonSuccess
{
	BYTE							cbGender;							//�û��Ա�
	BYTE							cbMember;							//��Ա�ȼ�
	WORD							wFaceID;							//ͷ������
	DWORD							dwUserID;							//�û� I D
	DWORD							dwGroupID;							//��������
	DWORD							dwExperience;						//�û�����
	DWORD							dwUserRight;						//�û��ȼ�
	DWORD							dwMasterRight;						//����Ȩ��
	TCHAR							szAccounts[NAME_LEN];				//��¼�ʺ�
	TCHAR							szPassWord[PASS_LEN];				//��¼����
	TCHAR							szGroupName[GROUP_LEN];				//��������
	TCHAR							szSessionId[128];				//��������
};

//��½ʧ��
struct DBR_GP_LogonError
{
	LONG							lErrorCode;							//�������
	TCHAR							szErrorDescribe[128];				//������Ϣ
};

//////////////////////////////////////////////////////////////////////////

#endif