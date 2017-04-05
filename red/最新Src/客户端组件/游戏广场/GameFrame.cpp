#include "Stdafx.h"
#include "GameFrame.h"
#include "GlobalUnits.h"
#include ".\gameframe.h"

//////////////////////////////////////////////////////////////////////////


//CTextRenderWnd GameFrame_TR;											//�ı����Ӷ���

//�궨��
#define TITLE_HEIGHT						48							//����߶�
#define MIN_CLIENT_WIDTH					800							//��С���
#define MIN_CLIENT_HEIGHT					500							//��С�߶�



//��ť��ʾ
#define IDC_BT_MIN							1000						//��С��ť
#define IDC_BT_CLOSE						1001						//�رհ�ť
#define IDC_BT_MAX							1002						//��󻯰�ť
#define IDC_BT_BUTTON_1						1003						//���ܰ�ť
#define IDC_BT_BUTTON_2						1004						//���ܰ�ť
#define IDC_BT_BUTTON_3						1005						//���ܰ�ť
#define IDC_BT_BUTTON_4						1006						//���ܰ�ť
#define IDC_BT_BUTTON_5						1007						//���ܰ�ť
//#define IDC_BT_BUTTON_6						1008						//���ܰ�ť
//#define IDC_BT_BUTTON_7						1009						//���ܰ�ť

//��Ϣ����
#define WM_SETUP_FINISH						WM_USER+100					//��װ���

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrame, CFrameWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SETTINGCHANGE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BT_MIN, OnBnClickedMin)
	ON_BN_CLICKED(IDC_BT_CLOSE, OnBnClickedClose)
	ON_BN_CLICKED(IDC_BT_MAX, OnBnClickedMax)
	ON_MESSAGE(WM_SETUP_FINISH,OnMessageSetupFinish)
	ON_BN_CLICKED(IDC_BT_BUTTON_1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BT_BUTTON_2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BT_BUTTON_3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BT_BUTTON_4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BT_BUTTON_5, OnBnClickedButton5)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_MESSAGE(WM_GAMECLIENT, OnGameClient)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrame::CGameFrame()
{
	//���ñ���
	m_bMaxed =  false;
	m_bMaxedC = false;

	m_pHtmlBrower1	= NULL;;

	//������Դ
	HINSTANCE hInstance=AfxGetInstanceHandle();

	m_ImageTL.SetLoadInfo(IDB_FRAME_TL,hInstance);
	m_ImageTM.SetLoadInfo(IDB_FRAME_TM,hInstance);
	m_ImageTR.SetLoadInfo(IDB_FRAME_TR,hInstance);
	//m_StatusL.SetLoadInfo(IDB_STATUS_L,hInstance);
	//m_StatusM.SetLoadInfo(IDB_STATUS_M,hInstance);

	return;
}

//��������
CGameFrame::~CGameFrame()
{
}

//��Ϣ����
BOOL CGameFrame::PreTranslateMessage(MSG * pMsg)
{
	m_ToolTipCtrl.RelayEvent(pMsg);
	return __super::PreTranslateMessage(pMsg);
}

//������Ϣ
int CGameFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (__super::OnCreate(lpCreateStruct)==-1) return -1;
	//��������
	//ModifyStyle(WS_CAPTION|WS_BORDER,0,0);

	//����ͼ��
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	//���ñ���
	CString strTitle;
	strTitle.LoadString(AfxGetInstanceHandle(),IDS_MAIN_TITLE);
	SetWindowText(strTitle);

	//������ť
	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_MIN);
	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_MAX);
	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_CLOSE);

	m_btButton1.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_1);
	m_btButton2.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_2);
	m_btButton3.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_3);
	m_btButton4.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_4);
	m_btButton5.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_5);

	//����ͼƬ
	m_btMin.SetButtonImage(IDB_FRAME_MIN,AfxGetInstanceHandle(),false);
	m_btMax.SetButtonImage(IDB_FRAME_MAX,AfxGetInstanceHandle(),false);
	m_btClose.SetButtonImage(IDB_FRAME_CLOSE,AfxGetInstanceHandle(),false);

	m_btButton1.SetButtonImage(IDB_FRAME_BT_BUTTON_1,AfxGetInstanceHandle(),false);
	m_btButton2.SetButtonImage(IDB_FRAME_BT_BUTTON_2,AfxGetInstanceHandle(),false);
	m_btButton3.SetButtonImage(IDB_FRAME_BT_BUTTON_3,AfxGetInstanceHandle(),false);
	m_btButton4.SetButtonImage(IDB_FRAME_BT_BUTTON_4,AfxGetInstanceHandle(),false);
	m_btButton5.SetButtonImage(IDB_FRAME_BT_BUTTON_5,AfxGetInstanceHandle(),false);

	//������ʾ�ؼ�
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_BT_MIN),TEXT("��С����Ϸ�㳡"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_BT_CLOSE),TEXT("�˳���Ϸ�㳡"));

	//�����ؼ�
	m_DlgControlBar.Create(IDD_CONTROL_BAR,this);
	m_DlgGamePlaza.Create(IDD_GAME_PLAZA,this);
	m_DlgControlBar.ActivePlazaViewItem();
	m_DlgControlBar.ShowWindow(SW_HIDE);

	//��ʾ����
	CRect rcRect;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcRect,SPIF_SENDCHANGE);
	
	//״̬������
	//m_pHtmlStatus = new CHtmlBrower();
	//m_pHtmlStatus->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,20,NULL);
	//m_pHtmlStatus->EnableBrowser(true);
	//m_pHtmlStatus->Navigate("http://"ServerDomain"/StatusAd.asp");

	//�����ؼ�
	//m_pHtmlBrower1->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(320,521,751,580),this,20,NULL);
	m_pHtmlBrower1 = new CHtmlBrower;
	m_pHtmlBrower1->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(109,7,300,45),this,20,NULL);
	m_pHtmlBrower1->EnableBrowser(true);
	m_pHtmlBrower1->Navigate("http://"ServerDomain"/Client/PlazaAD.asp");

	//bluker: SWP_HIDEWINDOW,SWP_SHOWWINDOW
	SetWindowPos(&wndTop,rcRect.Width()/2 - 400,rcRect.Height()/2 - 300,800,600,SWP_DRAWFRAME|SWP_SHOWWINDOW);
	//SetWindowPos(&wndTop,rcRect.Width()/2 - 512,rcRect.Height()/2 - 374,1024,748,SWP_DRAWFRAME|SWP_SHOWWINDOW);
	//del:SetWindowPos(&wndTop,rcRect.left,rcRect.top,rcRect.Width(),rcRect.Height(),SWP_DRAWFRAME|SWP_SHOWWINDOW);

	RegisterHotKey(m_hWnd, (int)m_hWnd, HOTKEY_MOD, HOTKEY_VK);

	return 0;
}


//�滭����
BOOL CGameFrame::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//���øı�
void CGameFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	__super::OnSettingChange(uFlags, lpszSection);

	//������ܴ�С
	//CRect rcClient;
	//SystemParametersInfo(SPI_GETWORKAREA,0,&rcClient,SPIF_SENDCHANGE);
	//MoveWindow(&rcClient,TRUE);

	return;
}

//�ر���Ϣ
void CGameFrame::OnClose()
{
	//�ر���ʾ
	if (g_GlobalUnits.GetGolbalUserData().dwUserID!=0L)
	{
		int nCode=AfxMessageBox(TEXT("��ȷʵҪ�ر���Ϸ�㳡��"),MB_YESNO|MB_DEFBUTTON2|MB_ICONQUESTION);
		if (nCode!=IDYES) return;
	}

	//���ؽ���
	ShowWindow(SW_HIDE);

	//�رշ���
	g_pControlBar->CloseAllRoomViewItem();

	//��������
	g_GlobalOption.SaveOptionParameter();
	g_GlobalUnits.m_CompanionManager->SaveCompanion();

	UnregisterHotKey(m_hWnd,(int)m_hWnd);

	__super::OnClose();
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton1()
{//�ٷ���վ
	//g_GlobalUnits.GoWeb("/",true);
	return;
}


//���ܰ�ť
void CGameFrame::OnBnClickedButton2()
{//��ҳ�ֵ
	//g_GlobalUnits.GoWeb("/Client/Pay",true);
	return;
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton3()
{//��������
	//g_GlobalUnits.GoWeb("/Client/Bank",true);
	return;
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton4()
{//��Ҷһ�
	//g_GlobalUnits.GoWeb("/",true);
	return;
}

//���ܰ�ť
void CGameFrame::OnBnClickedButton5()
{//��Ҷһ�
	//g_GlobalUnits.GoWeb("/",true);
	return;
}


//��ȡ���λ��
void CGameFrame::OnGetMinMaxInfo(MINMAXINFO FAR * lpMMI) 
{
	lpMMI->ptMinTrackSize.x=MIN_CLIENT_WIDTH;
	lpMMI->ptMinTrackSize.y=MIN_CLIENT_HEIGHT;
	__super::OnGetMinMaxInfo(lpMMI);
}

//�滭��Ϣ
void CGameFrame::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//������Դ
	int nXPos=0,nYPos=0;

	CImageHandle ImageTLHandle(&m_ImageTL);
	CImageHandle ImageTMHandle(&m_ImageTM);
	CImageHandle ImageTRHandle(&m_ImageTR);

	//CImageHandle StatusLHandle(&m_StatusL);
	//CImageHandle StatusMHandle(&m_StatusM);
	

	//�滭���Ͻ�
	m_ImageTL.BitBlt(dc,0,0);
	//�滭����
	m_ImageTM.StretchBlt(dc,
		CRect(m_ImageTL.GetWidth(),0,rcClient.right-m_ImageTR.GetWidth(),m_ImageTM.GetHeight()),
			CRect(0,0,m_ImageTM.GetWidth(),m_ImageTM.GetHeight())
			);
	//�滭���Ͻ�
	m_ImageTR.BitBlt(dc,rcClient.right-m_ImageTR.GetWidth(),0);

	//m_StatusL.BitBlt(dc,275,rcClient.bottom-83);
	//m_StatusM.StretchBlt(dc,
	//		CRect(573,rcClient.bottom-83,rcClient.right,rcClient.bottom),
	//		CRect(0,0,m_StatusM.GetWidth(),m_StatusM.GetHeight())
	//		);
/*
	char text[] =	"\\b0���������Ϸ�ң�������ͨ���������̵깺�����⿨���г�ֵ��[\\a1��������\\a0](9.5��)"
		"��3.�̶��绰������1601234567���г�ֵ��\\par";
	DWORD textAlignment = THA_LEFT | TVA_TOP;
	RECT margins = {2,2,2,2};
	dc.SetBkMode(TRANSPARENT);
	GameFrame_TR.m_color=0x942525;//0x111197
	GameFrame_TR.SetFontFace("����",12);
	GameFrame_TR.EnhDrawText( dc, text, strlen(text), &CRect(100,rcClient.bottom-24,rcClient.right-5,rcClient.bottom-5), &margins, textAlignment );
*/

	return;
}

//λ����Ϣ
void CGameFrame::OnSize(UINT nType, int cx, int cy) 
{
	__super::OnSize(nType, cx, cy);
	
	switch(nType)   
	{
	case   SIZE_RESTORED:         //��ԭ   
		if(m_bMaxedC)
		{
			if(g_GlobalOption.SetDisplay(800,600,32,g_GlobalOption.m_ScreenFrequency) || g_GlobalOption.SetDisplay(800,600,32,60))
			{
				SetWindowPos(&wndTop,0,0,800,600,SWP_DRAWFRAME|SWP_SHOWWINDOW);
			}
	}
	break;
	}
	//���ÿؼ�
	//48Ϊ�������߶�,83Ϊstatus�߶�
	m_DlgControlBar.SetViewItemRect(0,48,cx,cy-48-0);

	//������Ļ
	LockWindowUpdate();

	//�ƶ��ؼ�
	HDWP hDwp=BeginDeferWindowPos(20);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//�����ؼ�
	DeferWindowPos(hDwp,m_btMin,NULL,cx-123,10,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,cx-96,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btClose,NULL,cx-65,10,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_DlgControlBar,NULL,0,/*m_ImageTL.GetHeight()*/44,cx,CONTROL_BAR_HEIGHT,uFlags);

	////״̬������
	//DeferWindowPos(hDwp,m_pHtmlStatus->GetSafeHwnd(),NULL,88,cy-27,cx-93,22,uFlags);
	

	//������ť
	CRect rcButton;
	m_btButton1.GetWindowRect(&rcButton);
	int nSpace=rcButton.right-rcButton.left+2;
	DeferWindowPos(hDwp,m_btButton1,NULL,311,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton2,NULL,311+nSpace,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton3,NULL,311+nSpace*2,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton4,NULL,311+nSpace*3,6,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btButton5,NULL,311+nSpace*4,6,0,0,uFlags|SWP_NOSIZE);

	//�ƶ��ؼ�
	EndDeferWindowPos(hDwp);

	//�������
	UnlockWindowUpdate();

	return;
}

//��С��ť
void CGameFrame::OnBnClickedMin()
{
	ShowWindow(SW_MINIMIZE);	
	g_GlobalOption.SetDisplayDefault();
	return;
}

//��󻯰�ť
void CGameFrame::OnBnClickedMax()
{
	if(m_bMaxed)
	{
		g_GlobalOption.SetDisplayDefault();
		SetWindowPos(&wndTop,g_GlobalOption.m_ScreenW/2 - 400,g_GlobalOption.m_ScreenH/2 - 300,800,600,SWP_DRAWFRAME|SWP_SHOWWINDOW);
		m_bMaxed=false;
		m_bMaxedC = false;
	}
	else
	{
		if(g_GlobalOption.SetDisplay(800,600,32,g_GlobalOption.m_ScreenFrequency) || g_GlobalOption.SetDisplay(800,600,32,60))
		{
			SetWindowPos(&wndTop,0,0,800,600,SWP_DRAWFRAME|SWP_SHOWWINDOW);
		}
		m_bMaxed=true;
		m_bMaxedC = true;
	}
}

//�رհ�ť
void CGameFrame::OnBnClickedClose()
{
	g_pControlBar->CloseCurrentViewItem();
	return;
}

//��װ���
LRESULT CGameFrame::OnMessageSetupFinish(WPARAM wParam, LPARAM lParam)
{
	g_GlobalUnits.m_ServerListManager.UpdateGameKind((WORD)wParam);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
void CGameFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(point.y<TITLE_HEIGHT && !m_bMaxed)
	{
		SendMessage(WM_NCLBUTTONDOWN, HTCAPTION,0);
	}
	//GameFrame_TR.OnLButtonDown(nFlags,point);
	CFrameWnd::OnLButtonDown(nFlags, point);
}


BOOL CGameFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if(GameFrame_TR.OnSetCursor(pWnd))return true;
	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CGameFrame::OnHotKey(WPARAM wParam, LPARAM lParam)
{
CWnd *pGameWnd = AfxGetMainWnd();
	
	if ((g_GameProcessInfo.hProcess!=NULL)&&(WaitForSingleObject(g_GameProcessInfo.hProcess,0)==WAIT_TIMEOUT))
	{
		ShowWindow(SW_HIDE);
		if(!IsWindow(g_GameProcessWnd))return 0;
		pGameWnd = CWnd::FromHandle(g_GameProcessWnd);
	}
	if (wParam==(WPARAM)m_hWnd)
	{
		if(pGameWnd->IsWindowVisible())
		{
			pGameWnd->ShowWindow(SW_MINIMIZE);
			pGameWnd->ShowWindow(SW_HIDE);
		}
		else
		{
			pGameWnd->ShowWindow(SW_NORMAL);
			pGameWnd->SetActiveWindow();
			pGameWnd->BringWindowToTop();
			pGameWnd->SetForegroundWindow();
		}
	}return 0;
}

//��Ϸ���̷����ھ��������
LRESULT CGameFrame::OnGameClient(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case MSG_SENDWND:
		g_GameProcessWnd = (HWND)lParam;
		break;
	}
	return 0;
}
