#include "Stdafx.h"
#include "SystemOption.h"
#include "ServerItemView.h"

#include "mmsystem.h"
#pragma comment(lib,"winmm")


//////////////////////////////////////////////////////////////////////////
//�궨��


//////////////////////////////////////////////////////////////////////////

CGlobalOption						g_GlobalOption;						//ȫ������

//////////////////////////////////////////////////////////////////////////

//���캯��
CServerOption::CServerOption(WORD wServerID, CListServer * pListServer)
	: m_wServerID(wServerID),m_pListServer(pListServer)
{
	//Я������
	m_bPassword=false;
	m_szPassword[0]=0;
	return;
}

//��������
CServerOption::~CServerOption()
{
}

//��������
void CServerOption::LoadOptionParameter()
{
	return;
}

//��������
void CServerOption::SaveOptionParameter()
{
	return;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameOption::CGameOption(WORD wKindID, CListKind * pListKind) 
	: m_wKindID(wKindID),m_pListKind(pListKind)
{
	//��Ϸ������
	m_bLimitScore=false;
	m_lMaxScore=2147483647;
	m_lLessScore=-2147483646;

	//��ʱ����
	m_wNetDelay=500;
	m_bLimitDelay=false;

	//��������
	m_wFleeRate=5000;
	m_bLimitFlee=false;

	//ʤ������
	m_wWinRate=0;
	m_bLimitWin=false;

	return;
}

//��������
CGameOption::~CGameOption()
{
}

//��������
void CGameOption::LoadOptionParameter()
{
	//��������
	CWinApp * pApp=AfxGetApp();
	tagGameKind * pGameKind=m_pListKind->GetItemInfo();
	LPCTSTR pszRegKeyName=pGameKind->szKindName;

	//��Ϸ������
	m_lMaxScore=pApp->GetProfileInt(pszRegKeyName,TEXT("MaxScore"),m_lMaxScore);
	m_lLessScore=pApp->GetProfileInt(pszRegKeyName,TEXT("LessScore"),m_lLessScore);
	m_bLimitScore=pApp->GetProfileInt(pszRegKeyName,TEXT("LimitScore"),m_bLimitScore)?true:false;

	//��ʱ����
	m_wNetDelay=pApp->GetProfileInt(pszRegKeyName,TEXT("NetDelay"),m_wNetDelay);
	m_bLimitDelay=pApp->GetProfileInt(pszRegKeyName,TEXT("LimitDelay"),m_bLimitDelay)?true:false;

	//��������
	m_wFleeRate=pApp->GetProfileInt(pszRegKeyName,TEXT("FleeRate"),m_wFleeRate);
	m_bLimitFlee=pApp->GetProfileInt(pszRegKeyName,TEXT("LimitFlee"),m_bLimitFlee)?true:false;

	//ʤ������
	m_wWinRate=pApp->GetProfileInt(pszRegKeyName,TEXT("WinRate"),m_wWinRate);
	m_bLimitWin=pApp->GetProfileInt(pszRegKeyName,TEXT("LimitWin"),m_bLimitWin)?true:false;

	return;
}

//��������
void CGameOption::SaveOptionParameter()
{
	//��������
	CWinApp * pApp=AfxGetApp();
	tagGameKind * pGameKind=m_pListKind->GetItemInfo();
	LPCTSTR pszRegKeyName=pGameKind->szKindName;

	//��Ϸ������
	pApp->WriteProfileInt(pszRegKeyName,TEXT("LimitScore"),m_bLimitScore);
	pApp->WriteProfileInt(pszRegKeyName,TEXT("MaxScore"),m_lMaxScore);
	pApp->WriteProfileInt(pszRegKeyName,TEXT("LessScore"),m_lLessScore);

	//��ʱ����
	pApp->WriteProfileInt(pszRegKeyName,TEXT("LimitDelay"),m_bLimitDelay);
	pApp->WriteProfileInt(pszRegKeyName,TEXT("NetDelay"),m_wNetDelay);

	//��������
	pApp->WriteProfileInt(pszRegKeyName,TEXT("FleeRate"),m_wFleeRate);
	pApp->WriteProfileInt(pszRegKeyName,TEXT("LimitFlee"),m_bLimitFlee);

	//ʤ������
	pApp->WriteProfileInt(pszRegKeyName,TEXT("WinRate"),m_wWinRate);
	pApp->WriteProfileInt(pszRegKeyName,TEXT("LimitWin"),m_bLimitWin);

	return;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CGlobalOption::CGlobalOption()
{
	//ȫ������
	m_bExpandedList=true;
	m_enAcountsRule=enAcountsRule_Accounts;

	//��������
	m_bLimitDetest=true;
	m_bCheckSameIP=false;

	//��Ϣ����
	m_bSaveWisper=true;
	m_bShowInOutMessage=true;
	m_bOnlyFriendMessage=false;
	m_bHideDetestMessage=true;

	//��������
	m_bAutoSit=true;
	m_InviteMode=enInviteMode_All;

	//��ɫ����
	m_crChatTX=RGB(0,0,0);
	m_crMsgName=RGB(0,0,200);
	m_crMsgNormal=RGB(0,0,0);
	m_crMsgSysHead=RGB(200,0,0);
	m_crMsgSysString=RGB(0,0,200);
	m_crServerListTX=RGB(0,0,0);
	m_crServerListBK=RGB(200,200,200);

	m_ScreenW=0;
	GetDisplay(m_ScreenW,m_ScreenH,m_ScreenBits,m_ScreenFrequency);
	return;
}

//��������
CGlobalOption::~CGlobalOption()
{
	//ɾ������
	CGameOption * pGameOption=NULL;
	for (INT_PTR i=0;i<m_GameOptionArray.GetCount();i++)
	{
		pGameOption=m_GameOptionArray[i];
		ASSERT(pGameOption!=NULL);
		SafeDelete(pGameOption);
	}
	m_GameOptionArray.RemoveAll();

	//ɾ������
	CServerOption * pServerOption=NULL;
	for (INT_PTR i=0;i<m_ServerOptionArray.GetCount();i++)
	{
		pServerOption=m_ServerOptionArray[i];
		ASSERT(pServerOption!=NULL);
		SafeDelete(pServerOption);
	}
	m_ServerOptionArray.RemoveAll();

	SetDisplayDefault();
	return;
}

//��������
void CGlobalOption::LoadOptionParameter()
{
	//��������
	CWinApp * pApp=AfxGetApp();

	//ȫ������
	m_bExpandedList=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("ExpandedList"),m_bExpandedList)?true:false;
	m_enAcountsRule=(enAcountsRule)pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("AcountsRule"),m_enAcountsRule);

	//��������
	m_bLimitDetest=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("LimitDetest"),m_bLimitDetest)?true:false;
	m_bCheckSameIP=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("AutoHideServerList"),m_bCheckSameIP)?true:false;

	//��Ϣ����
	m_bSaveWisper=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("SaveWisper"),m_bSaveWisper)?true:false;
	m_bShowInOutMessage=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("ShowInOutMessage"),m_bShowInOutMessage)?true:false;
	m_bOnlyFriendMessage=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("OnlyFriendMessage"),m_bOnlyFriendMessage)?true:false;
	m_bHideDetestMessage=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("HideDetestMessage"),m_bHideDetestMessage)?true:false;

	//��������
	m_bAutoSit=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("AutoSit"),m_bAutoSit)?true:false;
	m_InviteMode=(enInviteMode)pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("InviteMode"),m_InviteMode);

	//��ɫ����
	m_crChatTX=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("ChatTX"),m_crChatTX);
	m_crMsgName=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("MsgName"),m_crMsgName);
	m_crMsgNormal=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("MsgNormal"),m_crMsgNormal);
	m_crMsgSysHead=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("MsgSysHead"),m_crMsgSysHead);
	m_crMsgSysString=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("MsgSysString"),m_crMsgSysString);
	m_crServerListTX=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("ServerListTX"),m_crServerListTX);
	m_crServerListBK=pApp->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("ServerListBK"),m_crServerListBK);

	//��Ϸ����
	CGameOption * pGameOption=NULL;
	for (INT_PTR i=0;i<m_GameOptionArray.GetCount();i++)
	{
		pGameOption=m_GameOptionArray[i];
		ASSERT(pGameOption!=NULL);
		pGameOption->LoadOptionParameter();
	}

	//��������
	CServerOption * pServerOption=NULL;
	for (INT_PTR i=0;i<m_ServerOptionArray.GetCount();i++)
	{
		pServerOption=m_ServerOptionArray[i];
		ASSERT(pServerOption!=NULL);
		pServerOption->LoadOptionParameter();
	}

	return;
}

//��������
void CGlobalOption::SaveOptionParameter()
{
	//��������
	CWinApp * pApp=AfxGetApp();

	//ȫ������
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("ExpandedList"),m_bExpandedList);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("AcountsRule"),m_enAcountsRule);



	//��������
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("LimitDetest"),m_bLimitDetest);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("AutoHideServerList"),m_bCheckSameIP);

	//��Ϣ����
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("SaveWisper"),m_bSaveWisper);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("ShowInOutMessage"),m_bShowInOutMessage);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("OnlyFriendMessage"),m_bOnlyFriendMessage);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("HideDetestMessage"),m_bHideDetestMessage);

	//��������
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("AutoSit"),m_bAutoSit);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("InviteMode"),m_InviteMode);

	//��ɫ����
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("ChatTX"),m_crChatTX);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("MsgName"),m_crMsgName);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("MsgNormal"),m_crMsgNormal);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("MsgSysHead"),m_crMsgSysHead);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("MsgSysString"),m_crMsgSysString);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("ServerListTX"),m_crServerListTX);
	pApp->WriteProfileInt(REG_GLOBAL_OPTIONS,TEXT("ServerListBK"),m_crServerListBK);

	//��Ϸ����
	CGameOption * pGameOption=NULL;
	for (INT_PTR i=0;i<m_GameOptionArray.GetCount();i++)
	{
		pGameOption=m_GameOptionArray[i];
		ASSERT(pGameOption!=NULL);
		pGameOption->SaveOptionParameter();
	}

	//��������
	CServerOption * pServerOption=NULL;
	for (INT_PTR i=0;i<m_ServerOptionArray.GetCount();i++)
	{
		pServerOption=m_ServerOptionArray[i];
		ASSERT(pServerOption!=NULL);
		pServerOption->SaveOptionParameter();
	}

	return;
}

//��Ϸ����
CGameOption * CGlobalOption::GetGameOption(CListKind * pListKind)
{
	//��ȡ����
	ASSERT(pListKind!=NULL);
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	
	//Ѱ���ִ�
	CGameOption * pGameOption=NULL;
	for (INT_PTR i=0;i<m_GameOptionArray.GetCount();i++)
	{
		pGameOption=m_GameOptionArray[i];
		ASSERT(pGameOption!=NULL);
		if (pGameOption->m_wKindID==pGameKind->wKindID) return pGameOption;
	}

	//��������
	try
	{
		pGameOption=new CGameOption(pGameKind->wKindID,pListKind);
		if (pGameOption==NULL) return NULL;
		pGameOption->LoadOptionParameter();
		m_GameOptionArray.Add(pGameOption);
		return pGameOption;
	}
	catch (...) {}

	return NULL;
}

//��������
CServerOption * CGlobalOption::GetServerOption(CListServer * pListServer)
{
	//��ȡ����
	ASSERT(pListServer!=NULL);
	tagGameServer * pGameServer=pListServer->GetItemInfo();
	
	//Ѱ���ִ�
	CServerOption * pServerOption=NULL;
	for (INT_PTR i=0;i<m_ServerOptionArray.GetCount();i++)
	{
		pServerOption=m_ServerOptionArray[i];
		ASSERT(pServerOption!=NULL);
		if (pServerOption->m_wServerID==pGameServer->wServerID) return pServerOption;
	}

	//��������
	try
	{
		pServerOption=new CServerOption(pGameServer->wServerID,pListServer);
		if (pServerOption==NULL) return NULL;
		pServerOption->LoadOptionParameter();
		m_ServerOptionArray.Add(pServerOption);
		return pServerOption;
	}
	catch (...) {}

	return NULL;
}


#define PlayMediaName TEXT("XiaoHongRenMedia")

bool CGlobalOption::PlayMedia(LPCTSTR pFile)
{
TCHAR szCommand[256];
	if(m_bDisableBgSound)return false;
	CloseMedia();
	sprintf(szCommand,"open \"%s\" ALIAS "PlayMediaName" type MPEGVideo",pFile);//align XiaoHongRenMedia 
	mciSendString(szCommand,szCommand,sizeof(szCommand),0);
	return (mciSendString("play "PlayMediaName" repeat",0,0,0)==ERROR_SUCCESS);
}
bool CGlobalOption::CloseMedia()
{
	return (mciSendString("close "PlayMediaName,NULL,0,0)==0);
}

bool CGlobalOption::GetDisplay(int &nWidth,int &nHeight,int &nBits,int &nFrequency)
{
	DEVMODE	devmode;
	if (::EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devmode))
	{
		nWidth = devmode.dmPelsWidth;
		nHeight = devmode.dmPelsHeight;
		nBits = devmode.dmBitsPerPel;
		nFrequency = devmode.dmDisplayFrequency;
		return true;
	}
	return false;
}

void CGlobalOption::SetDisplayDefault()
{
	SetDisplay(m_ScreenW,m_ScreenH,m_ScreenBits,m_ScreenFrequency);
}

bool CGlobalOption::SetDisplay(int nWidth,int nHeight,int nBits,int nFrequency)
{
	DEVMODE	devmode;
	BOOL  bRetVal=true;
	DWORD iMode = 0;

	while (1)
	{
		BOOL bRetVal = ::EnumDisplaySettings(NULL, iMode, &devmode);
		if (!bRetVal)break;
		if(devmode.dmPelsWidth == nWidth && devmode.dmPelsHeight==nHeight && devmode.dmBitsPerPel==nBits && devmode.dmDisplayFrequency == nFrequency)
		{
			devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
			::ChangeDisplaySettings(&devmode, 0);
			return true;
		}
		iMode++;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
