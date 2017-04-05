#include "StdAfx.h"
#include "Resource.h"
#include "GameFrameView.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
const int			CGameFrameView::m_nXFace=32;						//ͷ��߶�
const int			CGameFrameView::m_nYFace=32;						//ͷ����
const int			CGameFrameView::m_nXTimer=15;						//��ʱ����
const int			CGameFrameView::m_nYTimer=21;						//��ʱ����
const int			CGameFrameView::m_nXBorder=6;						//��ʱ����
const int			CGameFrameView::m_nYBorder=23;						//��ʱ����


CImage CGameFrameView::m_ImageBuffer;						//����λͼ
CImage CGameFrameView::m_ImageBuffer2;						//����λͼ2
//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameView, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameView::CGameFrameView(bool bDoubleBuf ,UINT uColorCount, CThreadDraw * pThreadDraw) 
	: m_bDoubleBuf(bDoubleBuf), m_uColorCount(uColorCount), m_pThreadDraw(pThreadDraw)
{
	//���ñ���
	m_bReDraw=true;
	m_pReserve=NULL;
	m_pIUserFaceRes=NULL;
	memset(&m_wTimer,0,sizeof(m_wTimer));
	memset(&m_ptName,0,sizeof(m_ptName));
	memset(&m_ptFace,0,sizeof(m_ptFace));
	memset(&m_ptTimer,0,sizeof(m_ptTimer));
	memset(&m_ptReady,0,sizeof(m_ptReady));
	memset(&m_pUserItem,0,sizeof(m_pUserItem));

	//������Դ
	HINSTANCE hInstance=GetModuleHandle(GAME_FRAME_DLL_NAME);
	m_ImageReady.SetLoadInfo(IDB_USER_READY,hInstance,true);
	m_ImageTimer.SetLoadInfo(IDB_USER_TIMER,hInstance,true);

	return;
}

//��������
CGameFrameView::~CGameFrameView()
{
}

//�ӿڲ�ѯ
void * __cdecl CGameFrameView::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameFrameView,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameFrameView,Guid,dwQueryVer);
	return NULL;
}

//���½���
void CGameFrameView::UpdateGameView(const CRect * pRect)
{
	if (m_bDoubleBuf==true) m_bReDraw=true;
	if (pRect!=NULL) InvalidateRect(pRect,FALSE);
	else Invalidate(FALSE);
	return;
}

//��ȡ����
bool CGameFrameView::GetGameViewImage(CImage & ImageBuffer, int nXPos, int nYPos, int nWidth, int nHeight)
{
	ASSERT(ImageBuffer.IsNull()==false);
	ASSERT(m_ImageBuffer.IsNull()==false);
	if (m_ImageBuffer.IsNull()==false)
	{
		m_ImageBuffer.BitBlt(ImageBuffer.GetDC(),nXPos,nYPos,nWidth,nHeight,nXPos,nYPos);
		ImageBuffer.ReleaseDC();
		return true;
	}
	return false;
}

//��ȡʱ��
WORD CGameFrameView::GetUserTimer(WORD wChairID)
{
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID>=MAX_CHAIR) return 0;
	return m_wTimer[wChairID];
}

//��ȡ���
const tagUserData * CGameFrameView::GetUserInfo(WORD wChairID)
{
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID>=MAX_CHAIR) return NULL;
	return m_pUserItem[wChairID];
}

//�滭����
void CGameFrameView::DrawViewImage(CDC * pDC, CSkinImage & SkinImage, enImageMode ImageMode)
{
	//��ȡλ��
	RECT rcClient;
	GetClientRect(&rcClient);

	//�滭λͼ
	switch (ImageMode)
	{
	case enMode_ElongGate:	//����ģʽ
		{
			CImageHandle ImageHandle(&SkinImage);
			int nImageWidth=ImageHandle->GetWidth();
			int nImageHeight=ImageHandle->GetHeight();
			ImageHandle->StretchBlt(pDC->m_hDC,0,0,rcClient.right,rcClient.bottom,0,0,nImageWidth,nImageHeight);
			return;
		}
	case enMode_Centent:	//����ģʽ
		{
			CImageHandle ImageHandle(&SkinImage);
			int nXPos=(rcClient.right-ImageHandle->GetWidth())/2;
			int nYPos=(rcClient.bottom-ImageHandle->GetHeight())/2;
			ImageHandle->BitBlt(pDC->m_hDC,nXPos,nYPos);
			return;
		}
	case enMode_Spread:		//ƽ��ģʽ
		{
			CImageHandle ImageHandle(&SkinImage);
			int nImageWidth=ImageHandle->GetWidth();
			int nImageHeight=ImageHandle->GetHeight();
			for (int nXPos=0;nXPos<rcClient.right;nXPos+=nImageWidth)
			{
				for (int nYPos=0;nYPos<rcClient.bottom;nYPos+=nImageHeight)
				{
					ImageHandle->BitBlt(pDC->m_hDC,nXPos,nYPos);
				}
			}
			return;
		}
	}
	return;
}

//�滭ͷ��
void CGameFrameView::DrawUserFace(CDC * pDC, WORD wFaceID, int nXPos, int nYPos, bool bOffLine)
{
	ASSERT(m_pIUserFaceRes!=NULL);
	m_pIUserFaceRes->DrawNormalFace(pDC,nXPos,nYPos,wFaceID);
	return;
}

//�滭ͷ��
void CGameFrameView::DrawUserSmallFace(CDC * pDC, WORD wFaceID, int nXPos, int nYPos, bool bOffLine)
{
	ASSERT(m_pIUserFaceRes!=NULL);
	m_pIUserFaceRes->DrawSmallFace(pDC,nXPos,nYPos,wFaceID);
	return;
}

//�滭ͷ��
void CGameFrameView::DrawUserBigFace(CDC * pDC, WORD wFaceID, int nXPos, int nYPos, bool bOffLine)
{
	ASSERT(m_pIUserFaceRes!=NULL);
	m_pIUserFaceRes->DrawBigFace(pDC,nXPos,nYPos,wFaceID);
	return;
}

//�滭׼��
void CGameFrameView::DrawUserReady(CDC * pDC, int nXPos, int nYPos)
{
	CImageHandle ImageHandle(&m_ImageReady);
	int nImageWidth=m_ImageReady.GetWidth();
	int nImageHeight=m_ImageReady.GetHeight();
	AlphaDrawImage(pDC,nXPos-nImageWidth/2,nYPos-nImageHeight/2,nImageWidth,nImageHeight,ImageHandle.GetBitmapHandle(),0,0,RGB(255,0,255));
	return;
}

//�滭ʱ��
void CGameFrameView::DrawUserTimer(CDC * pDC, int nXPos, int nYPos, WORD wTime, WORD wTimerArea)
{
	if ((wTime>0)&&(wTimerArea>=wTime))
	{
		//���� DC
		CDC DCBuffer;
		DCBuffer.CreateCompatibleDC(pDC);
		CImageHandle ImageHandle(&m_ImageTimer);
		HGDIOBJ hOldGdiObj=DCBuffer.SelectObject(ImageHandle.GetBitmapHandle());

		//�滭��ʱ��
		int nDrawPos=nXPos;
		for (WORD nArea=10000;nArea>0;nArea/=10)
		{
			if (wTimerArea<nArea) continue;
			int nTimerPos=wTime/nArea;
			AlphaDrawImage(pDC,nDrawPos,nYPos,m_nXTimer,m_nYTimer,&DCBuffer,nTimerPos*m_nXTimer,0,RGB(255,0,255));
			wTime-=nTimerPos*nArea;
			nDrawPos+=m_nXTimer;
		}

		//������Դ
		DCBuffer.SelectObject(hOldGdiObj);
		DCBuffer.DeleteDC();
	}
	return;
}

//͸���滭
void CGameFrameView::AlphaDrawImage(CDC * pDesDC, int nXDes, int nYDes, int nDesWidth, int nDesHeight, CDC * pScrDC, int nXScr, int nYScr, COLORREF crTransColor)
{
	::AlphaDrawImage(pDesDC,nXDes,nYDes,nDesWidth,nDesHeight,pScrDC,nXScr,nYScr,nDesWidth,nDesHeight,crTransColor);
	return;
}

//�滭͸��ͼ
void CGameFrameView::AlphaDrawImage(CDC * pDesDC, int nXDes, int nYDes, int nDesWidth, int nDesHeight, HBITMAP hBitBmp, int nXScr, int nYScr, COLORREF crTransColor)
{
	//���� DC
	CDC DCBuffer;
	DCBuffer.CreateCompatibleDC(NULL);
	HGDIOBJ hOldGdiObj=DCBuffer.SelectObject(hBitBmp);

	//�滭λͼ
	::AlphaDrawImage(pDesDC,nXDes,nYDes,nDesWidth,nDesHeight,&DCBuffer,nXScr,nYScr,nDesWidth,nDesHeight,crTransColor);

	//������Դ
	DCBuffer.SelectObject(hOldGdiObj);
	DCBuffer.DeleteDC();

	return;
}

//���ý���
void CGameFrameView::ResetData()
{
	//���ñ���
	memset(m_wTimer,0,sizeof(m_wTimer));
	memset(m_pUserItem,0,sizeof(m_pUserItem));

	//���ý���
	ResetGameView();
	UpdateGameView(NULL);
	
	return;
}

//���ýӿ�
bool CGameFrameView::SetUserFaceRes(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pIUserFaceRes=(IUserFaceRes *)pIUnknownEx->QueryInterface(IID_IUserFaceRes,VER_IUserFaceRes);
	return (m_pIUserFaceRes!=NULL);
}

//����ʱ��
bool CGameFrameView::SetUserTimer(WORD wChairID, WORD wTimer)
{
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID>=MAX_CHAIR) return false;
	m_wTimer[wChairID]=wTimer;
	UpdateGameView(NULL);
	return true;
}

//�����û�
bool CGameFrameView::SetUserInfo(WORD wChairID, tagUserData * pUserItem)
{
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID>=MAX_CHAIR) return false;
	m_pUserItem[wChairID]=pUserItem;
	UpdateGameView(NULL);
	return true;
}

//�滭�߿�
bool CGameFrameView::DrawGameViewFrame(CDC * pDC, int nWidth, int nHeight)
{
	ShowChat.OnDraw(pDC);
	char szTitle[128];
	::GetWindowText(AfxGetMainWnd()->GetSafeHwnd(),szTitle,sizeof(szTitle));

	//д����
	UINT nAlign = pDC->GetTextAlign();
	pDC->SetTextAlign(0);
	pDC->SetTextColor(0);
	//pDC->TextOut(10,6,szTitle);
	pDC->SetTextAlign(nAlign);

	return true;
}

//������Ϣ
int CGameFrameView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//��ʼ��
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);
	if (m_pThreadDraw!=NULL) m_pThreadDraw->BeginThread();

	RegisterHotKey(m_hWnd, (int)m_hWnd, MOD_ALT, VK_F12);

	return 0;
}

//�滭����
void CGameFrameView::OnPaint()
{
	CPaintDC dc(this);

	//�ж�ģʽ
	if (m_pThreadDraw!=NULL) return;

	//��ȡλ��
	CRect ClientRect;
	GetClientRect(&ClientRect);

	//�ػ�������

	if ((m_bDoubleBuf==true)&&(m_ImageBuffer.IsNull()==false))
	{
		if (m_bReDraw==true)
		{
			//��������
			CFont DrawFont;
			DrawFont.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("����"));
			CDC * pDC=CDC::FromHandle(m_ImageBuffer.GetDC());
			CFont * pOldFont=pDC->SelectObject(&DrawFont);

			//���»���
			m_bReDraw=false;
			pDC->SetBkMode(TRANSPARENT);
			pDC->FillSolidRect(0,0,ClientRect.Width(),ClientRect.Height(),RGB(0,0,150));
			DrawGameView(pDC,ClientRect.Width(),ClientRect.Height());
			DrawGameViewFrame(pDC,ClientRect.Width(),ClientRect.Height());

			//������Դ
			m_ImageBuffer.ReleaseDC();
			pDC->SelectObject(pOldFont);
			DrawFont.DeleteObject();
		}

		//�滭����
		CRect rcClip;
		dc.GetClipBox(&rcClip);

		GetGameViewImage(m_ImageBuffer2,0,0,m_ImageBuffer.GetWidth(),m_ImageBuffer.GetHeight());
		CDC * pDC=CDC::FromHandle(m_ImageBuffer2.GetDC());
		DrawGameView2(pDC,ClientRect.Width(),ClientRect.Height());
		m_ImageBuffer2.ReleaseDC();
		m_ImageBuffer2.BitBlt(dc,rcClip.left,rcClip.top,rcClip.Width(),rcClip.Height(),rcClip.left,rcClip.top);
	}
	else 
	{
		//��������
		CFont DrawFont;
		DrawFont.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("����"));
		CFont * pOldFont=dc.SelectObject(&DrawFont);

		//�滭����
		dc.SetBkMode(TRANSPARENT);
		DrawGameView(&dc,ClientRect.Width(),ClientRect.Height());
		DrawGameViewFrame(&dc,ClientRect.Width(),ClientRect.Height());
		//������Դ
		dc.SelectObject(pOldFont);
		DrawFont.DeleteObject();
	}

	return;
}

//λ�ñ仯
void CGameFrameView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	
	//Ч��״̬
	bool bOk = false;
	if((cx>=640 && cx<=4000) && (cy>=480 && cy<=4000))bOk=true;

	if (!bOk) return;


	//���Ļ���ͼ
	if ((m_bDoubleBuf==true)&&(nType!=SIZE_MINIMIZED))
	{
		if ((cx!=m_ImageSize.cx)||(cy!=m_ImageSize.cy))
		{
			m_bReDraw=true;
			m_ImageBuffer.Destroy();
			m_ImageBuffer2.Destroy();
			m_ImageSize.cx=cx;
			m_ImageSize.cy=cy;
			if(!m_ImageBuffer.Create(m_ImageSize.cx,m_ImageSize.cy,m_uColorCount))
				throw "�����������";
			if(!m_ImageBuffer2.Create(m_ImageSize.cx,m_ImageSize.cy,m_uColorCount))
				throw "�����������";
		}
	}


	//������ͼ
	RectifyGameView(cx,cy);
	
	//���û滭����
	if (m_pThreadDraw!=NULL)
	{
		m_pThreadDraw->SetClientRange(cx,cy);
		if (nType==SIZE_MINIMIZED) m_pThreadDraw->SuspendDrawThread();
		else m_pThreadDraw->ResumeDrawThread();
	}
	else UpdateGameView(NULL);

	return;
}

//�����Ϣ
void CGameFrameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	__super::OnLButtonDown(nFlags, point);
}

//������Ϣ
void CGameFrameView::OnDestroy()
{
	__super::OnDestroy();

	//�����߳�
	if (m_pThreadDraw!=NULL) m_pThreadDraw->EndThread();

	return;
}


//////////////////////////////////////////////////////////////////////////
