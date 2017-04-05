#ifndef COM_SERVICE_HEAD_FILE
#define COM_SERVICE_HEAD_FILE


//////////////////////////////////////////////////////////////////////////
#pragma once

//ϵͳͷ�ļ�
#include <AfxHtml.h>

//ƽ̨ͷ�ļ�
#include "..\..\ģ���\Template.h"

//////////////////////////////////////////////////////////////////////////
//�����궨��

//��������
#ifndef COM_SERVICE_CLASS
	#ifdef  COM_SERVICE_DLL
		#define COM_SERVICE_CLASS _declspec(dllexport)
	#else
		#define COM_SERVICE_CLASS _declspec(dllimport)
	#endif
#endif

//ģ�鶨��
#ifdef _DEBUG
	#define COM_SERVICE_DLL_NAME	TEXT("ComServiceD.dll")			//��� DLL ����
#else
	#define COM_SERVICE_DLL_NAME	TEXT("ComService.dll")			//��� DLL ����
#endif

//////////////////////////////////////////////////////////////////////////

//������ͷ�ļ�
#include "Encrypt.h"
#include "WebBrowser.h"
#include "HtmlBrowser.h"
#include "WinFileInfo.h"
#include "DataStorage.h"
#include "ServiceThread.h"
#include "FilterString.h"

#define VER_PLAZA_HIGH (GetPlazaRoomVersion()>>16)
DWORD COM_SERVICE_CLASS GetPlazaRoomVersion();

bool COM_SERVICE_CLASS GetCommandParam(LPCSTR szParamName,CString &pOut);//GetCommandParam(TEXT(" /RoomToken:"),s);

//////////////////////////////////////////////////////////////////////////

#endif