#include "Stdafx.h"
#include "GamePlaza.h"
#include "GameFrame.h"
#include "GlobalUnits.h"




//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGamePlazaApp, CWinApp)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//Ӧ�ó������˵��
CGamePlazaApp theApp;

//���캯��
CGamePlazaApp::CGamePlazaApp()
{
	m_intTheme = 1;
}

//��ʼ������
BOOL CGamePlazaApp::InitInstance()
{
	__super::InitInstance();

	//�ж��Ƿ�����
#ifndef ADMIN_PLAZA
#ifndef _DEBUG
	bool bExistIGame=false;
	CMutex Mutex(FALSE,MAIN_DLG_CLASSNAME,NULL);
	if (Mutex.Lock(0)==FALSE) bExistIGame=true;
	CWnd * pIGameWnd=CWnd::FindWindow(MAIN_DLG_CLASSNAME,szProductName);
	if (pIGameWnd!=NULL) 
	{
		bExistIGame=true;
		//pIGameWnd->ShowWindow(SW_RESTORE);
		//pIGameWnd->SetActiveWindow();
		//pIGameWnd->BringWindowToTop();
		//pIGameWnd->SetForegroundWindow();
	}
	if (bExistIGame==true) return FALSE;
#endif
#endif


	//�����ʼ��
	AfxOleInit();
	AfxInitRichEdit();
	AfxInitRichEdit2();
	InitCommonControls();
	AfxEnableControlContainer();

	//����ע���
	SetRegistryKey(szSystemRegKey);

	//���ؽ����
	CSkinAttribute::LoadSkinAttribute(GET_OBJECT_INTERFACE(m_SkinRecordFile,IUnknownEx));

	//��������
	g_GlobalOption.LoadOptionParameter();
	g_GlobalOption.m_bDisableBgSound=AfxGetApp()->GetProfileInt(REG_GLOBAL_OPTIONS,TEXT("DisableBgSound"),g_GlobalOption.m_bDisableBgSound)?true:false;


	//ȫ����Ϣ
	if (g_GlobalUnits.InitGlobalUnits()==false)
	{
		AfxMessageBox(TEXT("��Ϸ�㳡����ʧ�ܣ������˳���"),MB_ICONSTOP);
		return FALSE;
	}

	//ע�ᴰ����
	WNDCLASS WndClasss;
	memset(&WndClasss,0,sizeof(WndClasss));
	WndClasss.lpfnWndProc=::DefWindowProc;
	WndClasss.hInstance=AfxGetInstanceHandle();
	WndClasss.lpszClassName=MAIN_DLG_CLASSNAME;
	if (!AfxRegisterClass(&WndClasss)) AfxThrowResourceException();

	//��������
	//WS_SYSMENU|WS_MINIMIZEBOX|WS_OVERLAPPED|WS_CLIPCHILDREN
	//DS_SETFONT | DS_CENTER | WS_POPUP | WS_CLIPCHILDREN | WS_SYSMENU
	const DWORD dwStyte=DS_SETFONT | DS_CENTER | WS_POPUP | WS_CLIPCHILDREN | WS_SYSMENU;
	CGameFrame * pMainFrame=new CGameFrame();
	pMainFrame->Create(MAIN_DLG_CLASSNAME,TEXT(""),dwStyte,CRect(0,0,0,0));
	m_pMainWnd=pMainFrame;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

