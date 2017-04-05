#include "StdAfx.h"
#include "GlobalUnits.h"
#include "DlgControlBar.h"

//////////////////////////////////////////////////////////////////////////

//��������
#define DTP_GAME_CLIENT			1									//��������

//ȫ�ֱ���
CGlobalUnits					g_GlobalUnits;						//��Ϣ���			
CGlobalAttemper					g_GlobalAttemper;					//ȫ�ֵ���

//////////////////////////////////////////////////////////////////////////

//���캯��
CGlobalUnits::CGlobalUnits(void)
{
	m_szDirSkin[0]=0;
	m_szDirWork[0]=0;

	//��ȡ�汾
	char MFName[MAX_PATH];
	::GetModuleFileName(NULL,MFName,MAX_PATH);
	CWinFileInfo WinFileInfo;
	if (WinFileInfo.OpenWinFile(MFName)==false)::MessageBox(0,"ȡ�ļ��汾����",0,0);
	DWORD dwFileVerMS=0L,dwFileVerLS=0L;
	WinFileInfo.GetFileVersion(dwFileVerMS,dwFileVerLS);
	//m_dwPlazaVersion = (dwFileVerMS>>16) |
	//					((dwFileVerMS&0xffff)<<8)|
	//					((dwFileVerLS>>16)<<16)|
	//					((dwFileVerLS&0xffff)<<24);
	m_dwPlazaVersion = 65542 ;
	//CString a;
	//a.Format("%x",a);
	//MessageBox(0,a,0,0);
	//char as[61];
	//sprintf(as,"%x",m_dwPlazaVersion);
	//MessageBox(0,as,0,0);
	//m_dwPlazaVersion = MAKELONG(MAKEWORD(1,0),MAKEWORD(1,0));
	
	memset(&m_GloblaUserData,0,sizeof(m_GloblaUserData));
	lstrcpyn(m_szStationPage,szStationPage,sizeof(m_szStationPage));
	
	return;
}

//��������
CGlobalUnits::~CGlobalUnits(void)
{
}

//��ʼ������
bool CGlobalUnits::InitGlobalUnits()
{
	//�����������
	srand((UINT)time(NULL));

	//���ù���Ŀ¼
	GetModuleFileName(AfxGetInstanceHandle(),m_szDirWork,sizeof(m_szDirWork));
	int nModuleLen=lstrlen(m_szDirWork);
	int nProcessLen=lstrlen(AfxGetApp()->m_pszExeName)+lstrlen(TEXT(".EXE"));
	m_szDirWork[nModuleLen-nProcessLen]=0;
	SetCurrentDirectory(m_szDirWork);

	//���ý���Ŀ¼
	_snprintf(m_szDirSkin,sizeof(m_szDirSkin),TEXT("%s\\Skin"),m_szDirWork);

	//�������
	if (m_UserFaceRes.CreateInstance()==false) return false;
	if (m_DownLoadService.CreateInstance()==false) return false;
	if (m_CompanionManager.CreateInstance()==false) return false;
	if (m_GameRankManager.CreateInstance()==false) return false;

	//��ʼ�����
	m_CompanionManager->LoadCompanion();

	return true;
}

//�����ַ�
bool CGlobalUnits::CopyToClipboard(LPCTSTR pszString)
{
	//��������
	HWND hWnd=AfxGetMainWnd()->GetSafeHwnd();

	//�򿪼��а�
	if (OpenClipboard(hWnd)==FALSE) return false;
	if (EmptyClipboard()==FALSE) { CloseClipboard(); return false; }

	//��������
	HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,CountString(pszString));
	if (hData==NULL) 
	{
		CloseClipboard();
		return false;
	}

	//��������
	LPSTR pszMemString=(LPSTR)GlobalLock(hData);
	lstrcpy(pszMemString,pszString);
	SetClipboardData(CF_TEXT,hData);

	//��������
	GlobalUnlock(hData);
	CloseClipboard();

	return true;
}

//��ȡ����
void CGlobalUnits::GetClientSerial(tagClientSerial & ClientSerial)
{
	return;
}

//������վ��ַ
LPCTSTR CGlobalUnits::SetStationPage(LPCTSTR pszStationPage)
{
	ASSERT(pszStationPage!=NULL);
	lstrcpyn(m_szStationPage,pszStationPage,sizeof(m_szStationPage));
	return m_szStationPage;
}

void CGlobalUnits::AddSessionUrl(LPCTSTR pszPage,CString &szOutUrl)
{
CString s=pszPage;
	char cSign='?';
	if(strchr(s,'?'))
		cSign='&';
	szOutUrl.Format("%s%cSessionId=%s",s,cSign,m_GloblaUserData.szSessionId);
}

void CGlobalUnits::GoWeb(LPCTSTR pszPage,bool bAddSession)
{
	CString s;
	s.Format("http://"ServerDomain"%s",pszPage);
	if(bAddSession)
		AddSessionUrl(s,s);
	ShellExecute(NULL,TEXT("open"),s,NULL,NULL,SW_NORMAL);
}


//////////////////////////////////////////////////////////////////////////

//���캯��
CGlobalAttemper::CGlobalAttemper(void)
{
}

//��������
CGlobalAttemper::~CGlobalAttemper(void)
{
}

//��ʾ��ʾ
bool CGlobalAttemper::ShowStatusMessage(LPCTSTR pszMessage, CWnd * pNotifyWnd)
{
	return m_DlgStatus.ShowStatusMessage(pszMessage,pNotifyWnd);
}

//�ر�״̬
bool CGlobalAttemper::DestroyStatusWnd(CWnd * pNotifyWnd)
{
	return m_DlgStatus.DestroyStatusWnd(pNotifyWnd);
}

//������Ϸ
bool CGlobalAttemper::DownLoadClient(LPCTSTR pszKindName, WORD wKindID, bool bDisplay)
{
	//��������
	tagDownLoadRequest DownLoadRequest;
	memset(&DownLoadRequest,0,sizeof(DownLoadRequest));
	DownLoadRequest.bDisplay=bDisplay;
	lstrcpyn(DownLoadRequest.szDescribe,pszKindName,CountArray(DownLoadRequest.szDescribe));
	_snprintf(DownLoadRequest.szFileName,sizeof(DownLoadRequest.szFileName),TEXT("%s.EXE"),pszKindName);
	_snprintf(DownLoadRequest.szLocalPath,sizeof(DownLoadRequest.szLocalPath),TEXT("%s\\DownLoad"),g_GlobalUnits.GetWorkDirectory());
	_snprintf(DownLoadRequest.szDownLoadUrl,sizeof(DownLoadRequest.szDownLoadUrl),TEXT("http://"ServerDomain"/Download.asp?KindID=%ld&LocalVersion=0&PlazaVersion=%ld"),wKindID,g_GlobalUnits.GetPlazaVersion());

	//Ͷ������
	DWORD dwDownLoadID=g_GlobalUnits.m_DownLoadService->AddDownLoadRequest(DTP_GAME_CLIENT,&DownLoadRequest);

	return true;
}

//////////////////////////////////////////////////////////////////////////
