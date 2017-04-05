#include "Stdafx.h"
#include "Resource.h"
#include "DlgStatus.h"
#include "GlobalUnits.h"
#include ".\dlgstatus.h"

//��ʱ�� ID

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgStatus, CDialog)
	ON_BN_CLICKED(IDC_CLOSE, OnBnClickedClose)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgStatus::CDlgStatus() : CDialog(IDD_STATUS)
{
	m_wImagePos=0;
	m_pNotifyWnd=NULL;
	m_bTimer = false;
	return;
}

//��������
CDlgStatus::~CDlgStatus()
{
	if(m_bTimer)
	{
		KillTimer(499);
		m_bTimer=false;
	}
}

//�ؼ���
void CDlgStatus::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLOSE, m_btCancel);
}

//�ػ���Ϣ
void CDlgStatus::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClientRect;
	GetClientRect(&rcClientRect);

	m_BgImage.SetLoadInfo(IDB_CONNECT_BG,AfxGetInstanceHandle());
	m_ImgStatus.SetLoadInfo(IDB_CONNECT_STATUS,AfxGetInstanceHandle());
	CImageHandle m_BgImageHandle(&m_BgImage);
	CImageHandle m_ImgStatusHandle(&m_ImgStatus);

	SetWindowPos(NULL,0,0,m_BgImage.GetWidth(),m_BgImage.GetHeight(),SWP_NOMOVE);

	m_BgImage.BitBlt(dc,0,0);


	//�滭״̬
	for(int i=0;i<m_wImagePos;i++)
	{
		m_ImgStatus.AlphaDrawImage((CDC*)&dc,10 + i*10,28,RGB(255,0,255));
	}

	//�滭��Ϣ
	CFont DrawFont;
	DrawFont.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("����"));
	CFont * pOldFont=dc.SelectObject(&DrawFont);
	dc.SetTextColor(RGB(0,0,0));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(60,15,m_strMessage);
	dc.SelectObject(pOldFont);
	DrawFont.DeleteObject();


	return;
}

//��ʱ����Ϣ
void CDlgStatus::OnTimer(UINT nIDEvent)
{
	m_wImagePos ++;
	if(m_wImagePos>23)m_wImagePos=0;
	CRect rc;
	GetClientRect(&rc);
	rc.top += 28;
	rc.right -= 70;
	InvalidateRect(rc,false);
	__super::OnTimer(nIDEvent);
}

//������Ϣ
bool CDlgStatus::ShowStatusMessage(LPCTSTR pszMessage, CWnd * pNotifyWnd)
{
	//��������
	if (m_hWnd==NULL)
	{
		Create(IDD_STATUS);
		m_wImagePos=0;
	}


	//������Ϣ
	if(!m_bTimer)
	{
		m_bTimer=true;
		SetTimer(499,200,NULL);
	}
	m_pNotifyWnd=pNotifyWnd;
	m_strMessage=pszMessage;
	Invalidate(FALSE);

	//��ʾ����
	ShowWindow(SW_SHOW);
	SetForegroundWindow();

	return true;
}

//���ٴ���
bool CDlgStatus::DestroyStatusWnd(CWnd * pNotifyWnd)
{
	if(m_bTimer)
	{
		m_bTimer=false;
		KillTimer(499);
	}

	if ((m_pNotifyWnd==pNotifyWnd)||(pNotifyWnd==NULL))
	{
		DestroyWindow();
		return true;
	}
	return false;
}

//ȡ����ť
void CDlgStatus::OnBnClickedClose()
{
	if (m_pNotifyWnd==NULL) return;
	if (IsWindow(m_pNotifyWnd->m_hWnd)==FALSE) return;
	m_pNotifyWnd->PostMessage(WM_COMMAND,IDM_CANCEL_CONNECT,0);
	return;
}

//////////////////////////////////////////////////////////////////////////

BOOL CDlgStatus::OnEraseBkgnd(CDC* pDC)
{
	return true;
}
