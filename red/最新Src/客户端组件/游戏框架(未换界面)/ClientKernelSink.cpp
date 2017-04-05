#include "StdAfx.h"
#include "GameFrameDlg.h"
#include "ClientKernelSink.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CClientKernelSink::CClientKernelSink(CGameFrameDlg & GameFrameDlg) : m_GameFrameDlg(GameFrameDlg)
{
}

//��������
CClientKernelSink::~CClientKernelSink()
{
}

//�ӿڲ�ѯ
void * __cdecl CClientKernelSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IClientKernelSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IClientKernelSink,Guid,dwQueryVer);
	return NULL;
}

//��ȡ����
HWND __cdecl CClientKernelSink::GetFrameWnd()
{
	return m_GameFrameDlg.m_hWnd;
}

//����״̬
void __cdecl CClientKernelSink::ResetGameFrame()
{
	//���ý���
	m_GameFrameDlg.m_pGameFrameView->ResetData();
	m_GameFrameDlg.m_pGameFrameView->ResetGameView();
	m_GameFrameDlg.ResetGameFrame();

	return;
}

//�رմ���
void __cdecl CClientKernelSink::CloseGameFrame(bool bForceClose)
{
	if (m_GameFrameDlg.m_hWnd!=NULL) m_GameFrameDlg.PostMessage(WM_CLOSE,0,0);
	return;
}

//ʱ����Ϣ
bool __cdecl CClientKernelSink::OnEventTimer(WORD wChairID, UINT nElapse, UINT nTimerID)
{
	//��������
	WORD wViewChairID=m_GameFrameDlg.SwitchViewChairID(wChairID);
	m_GameFrameDlg.m_pGameFrameView->SetUserTimer(wViewChairID,nElapse);

	//�¼�֪ͨ
	return m_GameFrameDlg.OnTimerMessage(wChairID,nElapse,nTimerID);
}

//������Ϣ
bool __cdecl CClientKernelSink::OnEventSocket(const CMD_Command & Command, const void * pBuffer, WORD wDataSize)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GF_FRAME:	//�����Ϣ
		{
			return m_GameFrameDlg.OnFrameMessage(Command.wSubCmdID,pBuffer,wDataSize);
		}
	case MDM_GF_GAME:	//��Ϸ��Ϣ
		{
			return m_GameFrameDlg.OnGameMessage(Command.wSubCmdID,pBuffer,wDataSize);
		}
	}

	return false;
}

//������Ϣ
bool __cdecl CClientKernelSink::OnEventProcess(const IPC_Head & Head, const void * pBuffer, WORD wDataSize, HWND hWndSend)
{
	return false;
}

//��Ϸ״̬
bool __cdecl CClientKernelSink::OnEventGameScene(BYTE cbGameStation, bool bLookonOther, void * pBuffer, WORD wDataSize)
{
	return m_GameFrameDlg.OnGameSceneMessage(cbGameStation,bLookonOther,pBuffer,wDataSize);
}

//������Ϣ
bool __cdecl CClientKernelSink::OnUserChatMessage(tagUserData * pSendUserData, tagUserData * pRecvUserData, LPCTSTR pszChatMessage, COLORREF crColor)
{
	if(strncmp(VOICE_SIGN,pszChatMessage,lstrlen(VOICE_SIGN))==0)
	{
		CGameFrameDlg *dlg = (CGameFrameDlg*)AfxGetMainWnd();
		char *p = (char*)pszChatMessage + lstrlen(VOICE_SIGN);
		char *pszWavFile = strchr(p,':');
		if(!pszWavFile)return true;
		*pszWavFile=0;
		pszWavFile++;
		WORD wToWho = (WORD)atol(p);

		//���ѷ��������˵�����
		if(pSendUserData->wChairID == dlg->GetMeChairID() && wToWho==0)
			return true;

		if(wToWho!=0)
		{
			//�Ǹ����˽������Ǻ��ҽ�
			if(wToWho!= dlg->GetMeChairID())
				return true;
			//���Ǻ��ҽ���
			dlg->PlayGameSoundFromFip(pszWavFile);
		}
		else
		{
			//���Ǻ����Ǵ�ҽ���
			dlg->PlayGameSoundFromFip(pszWavFile);
		}
		return true;
	}
	else
	{
		//��ʾ��Ϣ
		if (pRecvUserData==NULL)
			m_GameFrameDlg.m_MessageProxyHelper->InsertUserChat(pSendUserData->szName,pszChatMessage,crColor,MS_NORMAL);
		else
			m_GameFrameDlg.m_MessageProxyHelper->InsertUserChat(pSendUserData->szName,pRecvUserData->szName,pszChatMessage,crColor,MS_NORMAL);

		ShowChat.ShowChat(pszChatMessage,pSendUserData);
		m_GameFrameDlg.m_pGameFrameView->UpdateGameView(NULL);
	}

	return true;
}

//�û�����
void __cdecl CClientKernelSink::OnEventUserEnter(tagUserData * pUserData, WORD wChairID, bool bLookonUser)
{
	m_GameFrameDlg.m_wKindID=m_GameFrameDlg.m_ClientKernelHelper->GetServerAttribute()->wKindID;
	m_GameFrameDlg.m_wGameGenre=m_GameFrameDlg.m_ClientKernelHelper->GetServerAttribute()->wGameGenre;

	int nBtn=m_GameFrameDlg.m_DlgUserList->m_ListUsers.AddButton(GetModuleHandle(GAME_FRAME_DLL_NAME),
					USERLIST_BTN,IMG_LISTCTRL_CMD_ID,
					pUserData->szName,
					0,0,0x505050,0);
	m_GameFrameDlg.m_DlgUserList->m_ListUsers.UpdateButton();
	if (bLookonUser==false)
	{
		WORD wViewChairID=m_GameFrameDlg.SwitchViewChairID(wChairID);
		m_GameFrameDlg.m_pGameFrameView->SetUserInfo(wViewChairID,pUserData);
	}
	//m_GameFrameDlg.m_pGameFrameView->SetUserInfo(wViewChairID,pUserData);
	return;
}

//�û��뿪
void __cdecl CClientKernelSink::OnEventUserLeft(tagUserData * pUserData, WORD wChairID, bool bLookonUser)
{
	int nItem=m_GameFrameDlg.m_DlgUserList->m_ListUsers.GetButtonByTitle(pUserData->szName);
	if(nItem)m_GameFrameDlg.m_DlgUserList->m_ListUsers.DeleteButton(nItem);
	m_GameFrameDlg.m_DlgUserList->m_ListUsers.UpdateButton();
	if (bLookonUser==false)
	{
		WORD wViewChairID=m_GameFrameDlg.SwitchViewChairID(wChairID);
		m_GameFrameDlg.m_pGameFrameView->SetUserInfo(wViewChairID,NULL);
	}
	m_GameFrameDlg.m_MessageProxyHelper->InsertUserName(pUserData->szName);
	m_GameFrameDlg.m_MessageProxyHelper->InsertGeneralString(TEXT("�뿪��"),0,0,true);
	return;
}

//�û���Ϸ��
void __cdecl CClientKernelSink::OnEventUserScore(tagUserData * pUserData, WORD wChairID, bool bLookonUser)
{
	//���ý���
	//m_GameFrameDlg.m_pGameFrameControl->UpdateUserItem(pUserData);
	//if (bLookonUser==false) m_GameFrameDlg.m_pGameFrameView->UpdateGameView(NULL);

	return;
}

//�û�״̬
void __cdecl CClientKernelSink::OnEventUserStatus(tagUserData * pUserData, WORD wChairID, bool bLookonUser)
{
	//���ý���
	//m_GameFrameDlg.m_pGameFrameControl->UpdateUserItem(pUserData);
	//if (bLookonUser==false)
		m_GameFrameDlg.m_pGameFrameView->UpdateGameView(NULL);

	return;
}

//ʱ�����
void __cdecl CClientKernelSink::OnEventTimerKilled(WORD wChairID, UINT nTimerID)
{
	//���ý���
	WORD wViewChairID=m_GameFrameDlg.SwitchViewChairID(wChairID);
	m_GameFrameDlg.m_pGameFrameView->SetUserTimer(wViewChairID,0);

	return;
}

//�Թ�״̬
void __cdecl CClientKernelSink::OnEventLookonChanged(bool bLookonUser, void * pBuffer, WORD wDataSize)
{
	return;
}

//////////////////////////////////////////////////////////////////////////
