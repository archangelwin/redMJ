#ifndef INIR_SERVERSYSTRAY_HEAD_FILE
#define INIR_SERVERSYSTRAY_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include <vector>


#define MY_WM_SYSTRAYICON	(WM_USER+4)		// ϵͳ������Ϣ
#define MY_WM_GAMESERVER_LOAD	(WM_USER+5)		// ϵͳ������Ϣ


#define IDM_SHOW_CENTER_SERVER  10000			// ��ʾ���ķ�����
#define IDM_SHOW_LOGON_SERVER   10001			// ��ʾ��½������
#define IDM_SHOW_ALL_SERVER	    10002			// ȫ����ʾ
#define IDM_HIDE_ALL_SERVER	    10003			// ȫ������
#define IDM_EXIT_SERVER	        10004			// ȫ������

#define IDM_SHOW_GAMESERVER_IDSTART	10100		// ��Ϸ����������¼���ʼ��ID

#define MAX_GAMESERVER_COUNT		100		// ÿ̨�������Ͷ�����е���Ϸ��������

//////////////////////////////////////////////////////////////////////////

//���ò���
class CServerSystray
{
	//��������
public:
	CServerSystray();
	~CServerSystray();
	
	CWnd *GetCenterServer();
	CWnd *GetLogonServer();

	void ShowCenterServer();
	void ShowLogonServer();
	void ShowGameServer(WPARAM nMenuId);

	void HideAll();
	void ShowAll();
	void StopAndCloseAllService();

	void AddIcon_To_Systray(HWND hwnd);
	void DeleteIcon_From_Systray(HWND hwnd);

	void AddGameServerWindow(HWND hwnd);

	void ShowMenu(CWnd *hwnd);

private:
	void ShowWindow(HWND hwnd);

	TCHAR m_ExePath[MAX_PATH];
	std::vector<HWND>					m_GameServerHwnds;
};

//////////////////////////////////////////////////////////////////////////

#endif//INIR_SERVERSYSTRAY_HEAD_FILE
