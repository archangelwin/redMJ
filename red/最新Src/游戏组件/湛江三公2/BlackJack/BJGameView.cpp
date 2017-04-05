#include "StdAfx.h"
#include "Resource.h"
#include "BJGameView.h"
#include "BJGameDlg.h"

//////////////////////////////////////////////////////////////////////////

//��ť��ʶ 
#define IDC_BEGIN					    101				//��ʼ��ť
#define IDC_ADD_GOLD					102				//��ע��ť
#define IDC_GIVE_UP						103				//������ť
#define IDC_GET_CARD					104		    	//Ҫ�ư�ť
#define IDC_STOP_CARD				    105				//ͣ�ư�ť
#define IDC_DOUBLE_CARD				    106				//˫����ť
#define IDC_CUT_CARD				    107				//���ư�ť

//���Ʊ�ʶ
#define NO_CUT				            0				//û�з���
#define TOP_CARD				        1				//���ַ���
#define BOTTOM_CARD				        2				//���ַ���

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CBJGameView, CGameFrameView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BEGIN, OnStart)
	ON_BN_CLICKED(IDC_ADD_GOLD, OnAddGold)
	ON_BN_CLICKED(IDC_GIVE_UP, OnGiveUp)
	ON_BN_CLICKED(IDC_GET_CARD, OnGetCard)
	ON_BN_CLICKED(IDC_STOP_CARD, OnStopCard)
	ON_BN_CLICKED(IDC_DOUBLE_CARD, OnDoubleCard)
	ON_BN_CLICKED(IDC_CUT_CARD, OnCutCard)
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////////

//���캯��
CBJGameView::CBJGameView(void) : CGameFrameView(true,24)
{
	//��ұ���
	m_lMaxGold   = 0L;
	m_lBasicGold = 0L;

	//�������
	m_wBankerStation = 255;
	m_cbCutCardMark  = NO_CUT;
	memset(m_cbTopCardSum, 0, sizeof(m_cbTopCardSum));
	memset(m_cbBottomCardSum, 0, sizeof(m_cbBottomCardSum));
	memset(m_cbPlayStatus, 0, sizeof(m_cbPlayStatus));

	//������Դ
	HINSTANCE hInstance = AfxGetInstanceHandle();
	if (GetSystemMetrics(SM_CXSCREEN) >= 1024) 
	{
		m_ImageCenter.SetLoadInfo(IDB_CENTER,hInstance);
	}	
	else
	{
		m_ImageCenter.SetLoadInfo(IDB_CENTER_800,hInstance);
	}	
	m_ImageBack.SetLoadInfo(IDB_BACKGROUD,hInstance);
	m_ImageTitle.SetLoadInfo(IDB_TITLE,hInstance);
	m_ImageBanker.SetLoadInfo(IDB_BANKER,hInstance);
	m_ImageArrowHead.SetLoadInfo(IDB_ARROW_HEAD,hInstance);
	m_ImageLc.SetLoadInfo(IDB_LC,hInstance);
	m_ImageRc.SetLoadInfo(IDB_RC,hInstance);
	m_ImageHeadBg.SetLoadInfo(IDB_HEAD_BG,hInstance);
	m_ImageAddGoldMark.SetLoadInfo(IDB_ADDGOLD_MARK,hInstance);
	m_ImageGetCardMark.SetLoadInfo(IDB_GETCARD_MARK,hInstance);
	m_ImageStopMark.SetLoadInfo(IDB_STOP_MARK,hInstance);
	m_ImageBrustMark.SetLoadInfo(IDB_BRUST_MARK,hInstance);

	//��ȡ��С
	//CImageHandle HandleBack(&m_ImageBack);
	//m_ImageSize.SetSize(m_ImageBack.GetWidth(),m_ImageBack.GetHeight());
	return;
}

//��������
CBJGameView::~CBJGameView(void)
{
}

//������Ϣ
int CBJGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1) return -1;

	//�����ؼ�
	CRect CreateRect(0,0,0,0);
	m_GoldControl.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS,CreateRect,this,8,NULL);
	m_ScoreView.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,CreateRect,this,9);
	for (int i = 0; i < GAME_PLAYER * 2; i++)
	{
		m_CardControl[i].Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CreateRect,this,10+i);
	}

	//������ť
	m_btGiveUp.Create(NULL,WS_CHILD|WS_CHILD,CreateRect,this,IDC_GIVE_UP);
	m_btAddGold.Create(NULL,WS_CHILD|WS_CHILD,CreateRect,this,IDC_ADD_GOLD);
	m_btBegin.Create(NULL,WS_CHILD|WS_CHILD,CreateRect,this,IDC_BEGIN);	
	m_btGetCard.Create(NULL,WS_CHILD|WS_CHILD,CreateRect,this,IDC_GET_CARD);
	m_btStop.Create(NULL,WS_CHILD|WS_CHILD,CreateRect,this,IDC_STOP_CARD);
	m_btDouble.Create(NULL,WS_CHILD|WS_CHILD,CreateRect,this,IDC_DOUBLE_CARD);
	m_btCutCard.Create(NULL,WS_CHILD|WS_CHILD,CreateRect,this,IDC_CUT_CARD);

	//����λͼ
	HINSTANCE hInstance = AfxGetInstanceHandle();
	m_btAddGold.SetButtonImage(IDB_BT_ADD_GOLD,hInstance,false);
	m_btBegin.SetButtonImage(IDB_BT_BEGIN,hInstance,false);
	m_btGiveUp.SetButtonImage(IDB_BT_GIVE_UP,hInstance,false);
	m_btGetCard.SetButtonImage(IDB_BT_GET_CARD,hInstance,false);
	m_btStop.SetButtonImage(IDB_BT_STOP_CARD,hInstance,false);
	m_btDouble.SetButtonImage(IDB_BT_DOUBLE,hInstance,false);
	m_btCutCard.SetButtonImage(IDB_BT_CUT_CARD,hInstance,false);

	m_HeapCard.ResetMinusMiddleCount();

	return 0;
}


//���ý���
void CBJGameView::ResetGameView()
{	
	//��ұ���
	m_lMaxGold   = 0L;
	m_lBasicGold = 0L;

	//�������
	m_wBankerStation = 255;
	m_cbCutCardMark  = NO_CUT;
	memset(m_cbTopCardSum, 0, sizeof(m_cbTopCardSum));
	memset(m_cbBottomCardSum, 0, sizeof(m_cbBottomCardSum));
	memset(m_cbPlayStatus, 0, sizeof(m_cbPlayStatus));	


	//���ÿؼ�
	m_ScoreView.ShowWindow(SW_HIDE);
	m_GoldControl.ShowWindow(SW_HIDE);

	m_btBegin.ShowWindow(SW_HIDE);
	m_btGiveUp.ShowWindow(SW_HIDE);
	m_btGetCard.ShowWindow(SW_HIDE);
	m_btStop.ShowWindow(SW_HIDE);
	m_btDouble.ShowWindow(SW_HIDE);
	m_ScoreView.ShowWindow(SW_HIDE);
	m_GoldControl.ShowWindow(SW_HIDE);

	//�����˿� 
	m_HeapCard.SetCardData(0,0,0,0);

	for (int i=0;i<CountArray(m_GoldView);i++) m_GoldView[i].SetGold(m_lBasicGold);
	for (int i=0;i<CountArray(m_CardControl);i++) m_CardControl[i].SetCardData(NULL,0);

	return;
}

//�����ؼ�
void CBJGameView::RectifyGameView(int nWidth, int nHeight)
{
	m_Rct_Play.left		= m_nXBorder;
	m_Rct_Play.top		= m_nYBorder;
	m_Rct_Play.right	= nWidth  - m_nXBorder;
	m_Rct_Play.bottom	= nHeight - m_nYBorder;

	int nXCenter = nWidth / 2;
	int nYCenter = nHeight / 2;	
	int temp     = 100;

	//��������
	m_ptFace[0].x    = nXCenter - m_nXFace;
	m_ptFace[0].y    = m_Rct_Play.top + 5;
	m_ptName[0].x    = m_ptFace[0].x + m_nXFace + 5;
	m_ptName[0].y    = m_ptFace[0].y;	
	m_ptReady[0].x   = m_ptFace[0].x - 5;
	m_ptReady[0].y   = m_ptFace[0].y + 10;
	m_ptMark[0].x    = m_ptFace[0].x - 40;
	m_ptMark[0].y    = m_ptFace[0].y;
	m_ptCardSum[0].x = m_ptFace[0].x - 50;
	m_ptCardSum[0].y = m_ptFace[0].y + 40;

	m_ptFace[1].x    = m_Rct_Play.right - m_nXFace - 5;
	m_ptFace[1].y    = nYCenter;	
	m_ptName[1].x    = m_Rct_Play.right - 5;
	m_ptName[1].y    = m_ptFace[1].y + m_nXFace + 5 ;
	m_ptReady[1].x   = m_ptFace[1].x + m_nXFace / 2;
	m_ptReady[1].y   = m_ptFace[1].y - 10;
	m_ptMark[1].x    = m_ptFace[1].x;
	m_ptMark[1].y    = m_ptFace[1].y - 40;
	m_ptCardSum[1].x = m_Rct_Play.right - 120;
	m_ptCardSum[1].y = m_ptFace[1].y - 70;

	m_ptFace[2].x    = nXCenter - 200;
	m_ptFace[2].y    = m_Rct_Play.bottom - 50;
	m_ptName[2].x    = m_ptFace[2].x + m_nXFace + 5;
	m_ptName[2].y    = m_ptFace[2].y;
	m_ptReady[2].x   = m_ptFace[2].x + m_nXFace / 2;
	m_ptReady[2].y   = m_ptFace[2].y - 10;
	m_ptMark[2].x    = m_ptFace[2].x;
	m_ptMark[2].y    = m_ptFace[2].y - 40;
	m_ptCardSum[2].x = nWidth/2 - 15;
	m_ptCardSum[2].y = nHeight/2 + 220;
	
	m_ptFace[3].x    = m_Rct_Play.left + 5;
	m_ptFace[3].y    = nYCenter;
	m_ptName[3].x    = m_ptFace[3].x;
	m_ptName[3].y    = m_ptFace[3].y  + m_nXFace + 5;
	m_ptReady[3].x   = m_ptFace[3].x + m_nXFace / 2;
	m_ptReady[3].y   = m_ptFace[3].y - 10;
	m_ptMark[3].x    = m_ptFace[3].x;
	m_ptMark[3].y    = m_ptFace[3].y - 40;
	m_ptCardSum[3].x = m_Rct_Play.left + 100;
	m_ptCardSum[3].y = m_ptFace[3].y - 70;
	
	//����ؼ�
	int nXCenterPos = nWidth/2;
	int nYCenterPos = nHeight/2;

	if (GetSystemMetrics(SM_CXSCREEN) >= 1024)
	{
		m_GoldStation[0].SetPoint(nXCenterPos-50,nYCenterPos-145);
		m_GoldStation[1].SetPoint(nXCenterPos+50,nYCenterPos-145);
		m_GoldStation[2].SetPoint(nXCenterPos+145,nYCenterPos-50);
		m_GoldStation[3].SetPoint(nXCenterPos+145,nYCenterPos+50);

		m_GoldStation[4].SetPoint(nXCenterPos+50,nYCenterPos+145);
		m_GoldStation[5].SetPoint(nXCenterPos-50,nYCenterPos+145);
		m_GoldStation[6].SetPoint(nXCenterPos-145,nYCenterPos+50);
		m_GoldStation[7].SetPoint(nXCenterPos-145,nYCenterPos-50);
	}
	else
	{
		m_GoldStation[0].SetPoint(nXCenterPos-32,nYCenterPos-92);
		m_GoldStation[1].SetPoint(nXCenterPos+28,nYCenterPos-92);
		m_GoldStation[2].SetPoint(nXCenterPos+96,nYCenterPos-27);
		m_GoldStation[3].SetPoint(nXCenterPos+96,nYCenterPos+33);
		m_GoldStation[4].SetPoint(nXCenterPos+28,nYCenterPos+93);
		m_GoldStation[5].SetPoint(nXCenterPos-32,nYCenterPos+93);
		m_GoldStation[6].SetPoint(nXCenterPos-94,nYCenterPos+33);
		m_GoldStation[7].SetPoint(nXCenterPos-94,nYCenterPos-27);
	}

	//��ť�ؼ�
	HDWP hDwp = BeginDeferWindowPos(5);
	const UINT uFlags = SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;

/*	DeferWindowPos(hDwp,m_btBegin,NULL,nWidth-m_nXBorder-110,nHeight-m_nYBorder-65,0,0,uFlags);
	DeferWindowPos(hDwp,m_btGiveUp,NULL,nWidth-m_nXBorder-190,nHeight-m_nYBorder-50,0,0,uFlags);     
	DeferWindowPos(hDwp,m_btAddGold,NULL,nWidth-m_nXBorder-130,nHeight-m_nYBorder-90,0,0,uFlags);    

	DeferWindowPos(hDwp,m_btCutCard,NULL,nWidth-m_nXBorder-45,nHeight-m_nYBorder-170,0,0,uFlags);  
	DeferWindowPos(hDwp,m_btStop,NULL,nWidth-m_nXBorder-165,nHeight-m_nYBorder-60,0,0,uFlags);
	DeferWindowPos(hDwp,m_btDouble,NULL,nWidth-m_nXBorder-95,nHeight-m_nYBorder-110,0,0,uFlags);  
	DeferWindowPos(hDwp,m_btGetCard,NULL,nWidth-m_nXBorder-65,nHeight-m_nYBorder-60,0,0,uFlags); */ 

	DeferWindowPos(hDwp,m_btBegin,NULL,nWidth-m_nXBorder-150,nHeight-m_nYBorder-150,0,0,uFlags);
	DeferWindowPos(hDwp,m_btGiveUp,NULL,nWidth-m_nXBorder-190,nHeight-m_nYBorder-50,0,0,uFlags);     
	DeferWindowPos(hDwp,m_btAddGold,NULL,nWidth-m_nXBorder-130,nHeight-m_nYBorder-90,0,0,uFlags);    

	DeferWindowPos(hDwp,m_btCutCard,NULL,nWidth-m_nXBorder-75,nHeight-m_nYBorder-170,0,0,uFlags);  
	DeferWindowPos(hDwp,m_btStop,NULL,nWidth-m_nXBorder-195,nHeight-m_nYBorder-60,0,0,uFlags);
	DeferWindowPos(hDwp,m_btDouble,NULL,nWidth-m_nXBorder-125,nHeight-m_nYBorder-110,0,0,uFlags);  
	DeferWindowPos(hDwp,m_btGetCard,NULL,nWidth-m_nXBorder-95,nHeight-m_nYBorder-60,0,0,uFlags); 

	EndDeferWindowPos(hDwp);
	
	//�ɼ�����
	CRect rcScoreView;
	m_ScoreView.GetWindowRect(&rcScoreView);
	m_ScoreView.MoveWindow((nWidth-rcScoreView.Width())/2,(nHeight-rcScoreView.Height())/2-10,rcScoreView.Width(),rcScoreView.Height());

	//��ע����
	m_GoldControl.SetBasicPoint(nWidth-25-m_nXBorder,nHeight-100-m_nYBorder);

	//�˿˿ؼ�
	m_CardControl[0].SetBasicStation(CPoint(nWidth/2,42+m_nYBorder),enXCenter,enYTop);
	m_CardControl[1].SetBasicStation(CPoint(nWidth-m_nXBorder-70,nHeight/2),enXRight,enYCenter);
	m_CardControl[2].SetBasicStation(CPoint(nWidth/2,nHeight-30-m_nYBorder),enXLeft,enYBottom);
	m_CardControl[3].SetBasicStation(CPoint(m_nXBorder+60,nHeight/2),enXLeft,enYCenter);
	m_CardControl[4].SetBasicStation(CPoint(nWidth/2,67+m_nYBorder),enXCenter,enYTop);
	m_CardControl[5].SetBasicStation(CPoint(nWidth-m_nXBorder-70,nHeight/2+25),enXRight,enYCenter);
	m_CardControl[6].SetBasicStation(CPoint(nWidth/2,nHeight-5-m_nYBorder),enXLeft,enYBottom);
	m_CardControl[7].SetBasicStation(CPoint(m_nXBorder+60,nHeight/2+25),enXLeft,enYCenter);

	m_HeapCard.SetControlPoint(nWidth/2-100,nHeight/2-20);

    return;
}

//�滭����
void CBJGameView::DrawGameView(CDC * pDC, int nWidth, int nHeight)
{
	//��������
	CImageHandle HandleTitle(&m_ImageTitle);
	CImageHandle HandleBanker(&m_ImageBanker);
	CImageHandle HandleArrowHead(&m_ImageArrowHead);
	CImageHandle HandleAddGoldMark(&m_ImageAddGoldMark);
	CImageHandle HandleGetCardMark(&m_ImageGetCardMark);
	CImageHandle HandleStopMark(&m_ImageStopMark);
	CImageHandle HandleBrustMark(&m_ImageBrustMark);
	CImageHandle HandleLc(&m_ImageLc);
	CImageHandle HandleRc(&m_ImageRc);
	CImageHandle HandleHeadBg(&m_ImageHeadBg);



	//�滭����
	pDC->FillSolidRect(0, 0, nWidth, nHeight, RGB(0,0,0));
	DrawViewImage(pDC, m_ImageBack, enMode_Spread);
	DrawViewImage(pDC,m_ImageCenter,enMode_Centent);
	//m_ImageTitle.BitBlt(pDC->m_hDC,m_nXBorder,m_nYBorder);
	m_ImageTitle.AlphaDrawImage(pDC,m_nXBorder,m_nYBorder,RGB(255,0,255));
	m_ImageLc.AlphaDrawImage(pDC,m_nXBorder,nHeight-m_ImageRc.GetHeight()-m_nYBorder,RGB(255,0,255));
	m_ImageRc.AlphaDrawImage(pDC,nWidth-m_ImageLc.GetWidth()-m_nXBorder,m_nYBorder,RGB(255,0,255));

	//�滭�û�
	TCHAR szBuffer[64];
	WORD  wUserTimer = 0;
	
	pDC->SetTextColor(RGB(255,255,0));
	
	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		//��������
		const tagUserData * pUserData = GetUserInfo(i);
		
		if (pUserData != NULL)
		{
			//�û�����
			pDC->SetTextAlign((i == 1) ? (TA_RIGHT|TA_TOP) : (TA_LEFT|TA_TOP));
			pDC->TextOut(m_ptName[i].x, m_ptName[i].y, pUserData->szName, lstrlen(pUserData->szName));

			//�û����
			_snprintf(szBuffer, sizeof(szBuffer), TEXT("��%ld"), pUserData->lScore);
			pDC->TextOut(m_ptName[i].x, m_ptName[i].y + 16, szBuffer, lstrlen(szBuffer));

			//������Ϣ
			wUserTimer = GetUserTimer(i);
			if (wUserTimer != 0)
			{
				//DrawUserTimer(pDC, nWidth - 80, 50, wUserTimer);
				DrawUserTimer(pDC, nWidth-m_nXBorder-85, m_nYBorder+50, wUserTimer);
			}
			
			if (pUserData->cbUserStatus == US_READY)
			{
				DrawUserReady(pDC, m_ptReady[i].x, m_ptReady[i].y);
			}
			m_ImageHeadBg.BitBlt(pDC->m_hDC,m_ptFace[i].x-2, m_ptFace[i].y-2);
			DrawUserFace(pDC,pUserData->wFaceID, m_ptFace[i].x, m_ptFace[i].y, pUserData->cbUserStatus == US_OFFLINE);
		}
	}

	//�ѻ��˿�
	m_HeapCard.DrawCardControl(pDC);

	//��Ϸ��Ϣ
	const UINT uDrawFormat = DT_END_ELLIPSIS|DT_CENTER|DT_SINGLELINE|DT_VCENTER;

	pDC->SetTextAlign(TA_LEFT|TA_TOP);
	pDC->SetTextColor(RGB(255,255,255));

	if (m_lMaxGold != 0) 
	{
		_snprintf(szBuffer, sizeof(szBuffer), TEXT("��%ld"), m_lMaxGold);
		DrawText(pDC->GetSafeHdc(), szBuffer, lstrlen(szBuffer), CRect(86,38,162,53), uDrawFormat);
	}
	if (m_lBasicGold != 0) 
	{
		_snprintf(szBuffer, sizeof(szBuffer), TEXT("��%ld"), m_lBasicGold);
		DrawText(pDC->GetSafeHdc(), szBuffer, lstrlen(szBuffer), CRect(86,55,162,70), uDrawFormat);
	}
	
	//�滭����
	LONG lTotalGold=0L;
	for (DWORD i = 0; i < CountArray(m_GoldView); i++)
	{
		lTotalGold += m_GoldView[i].GetGold();
		m_GoldView[i].DrawGoldView(pDC,m_GoldStation[i].x,m_GoldStation[i].y);
	}

	//��ע��Ϣ
	if (lTotalGold != 0L)
	{
		CFont ViewFont;
		ViewFont.CreateFont(-24,0,0,0,700,0,0,0,134,3,2,1,1,TEXT("����_GB2312"));
		CFont * pOldFont=pDC->SelectObject(&ViewFont);
		pDC->SetTextColor(RGB(255,255,0));
		pDC->SetTextAlign(TA_CENTER|TA_TOP);
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%ld"),lTotalGold);
		pDC->TextOut(nWidth/2,nHeight/2-8,szBuffer,lstrlen(szBuffer));
		pDC->SelectObject(pOldFont);
		ViewFont.DeleteObject();
	}

	//�˿���ֵ
	pDC->SetTextColor(RGB(255,255,0));
	CFont ViewFont;
	ViewFont.CreateFont(-20,0,0,0,700,0,0,0,134,3,2,1,1,TEXT("����_GB2312"));
	CFont * pOldFont=pDC->SelectObject(&ViewFont);
	pDC->SetTextColor(RGB(255,255,0));
	pDC->SetTextAlign(TA_CENTER|TA_TOP);

	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		//��������
		const tagUserData * pUserData = GetUserInfo(i);

		if (pUserData != NULL)
		{
			if(m_cbTopCardSum[i] !=0)
			{
				_snprintf(szBuffer, sizeof(szBuffer), TEXT("%d"), m_cbTopCardSum[i]);
				
				pDC->TextOut(m_ptCardSum[i].x, m_ptCardSum[i].y, szBuffer, lstrlen(szBuffer));
			}
			if(m_cbBottomCardSum[i] !=0)
			{
				_snprintf(szBuffer, sizeof(szBuffer), TEXT("%d"), m_cbBottomCardSum[i]);
				pDC->TextOut(nWidth/2-15, nHeight/2+250, szBuffer, lstrlen(szBuffer));
			}
		}
	}

	pDC->SelectObject(pOldFont);
	ViewFont.DeleteObject();	

	//���Ʊ�ʶ
	if(m_cbCutCardMark == TOP_CARD)
	{
		m_ImageArrowHead.AlphaDrawImage(pDC,nWidth/2-80,nHeight-140,RGB(5,136,30));
	}
	if(m_cbCutCardMark == BOTTOM_CARD)
	{
		m_ImageArrowHead.AlphaDrawImage(pDC,nWidth/2-80,nHeight-80,RGB(5,136,30));
	}
	
	//���״̬
	
	HINSTANCE hInstance = AfxGetInstanceHandle();

	for(int i=0;i<GAME_PLAYER;i++)
	{
		if(i == 2) continue;
		switch(m_cbPlayStatus[i])
		{
		case 0:
			{
				break;
			}
			//�û���ע
		case 1:
			{				
				m_ImageAddGoldMark.AlphaDrawImage(pDC,m_ptMark[i].x,m_ptMark[i].y,RGB(255,0,255));
				break;
			}
			//�û�Ҫ��
		case 2:
			{				
				m_ImageGetCardMark.AlphaDrawImage(pDC,m_ptMark[i].x,m_ptMark[i].y,RGB(255,0,255));
				break;
			}
			//�û�ͣ��
		case 3:
			{				
				m_ImageStopMark.AlphaDrawImage(pDC,m_ptMark[i].x,m_ptMark[i].y,RGB(255,0,255));
				break;
			}
			//�û�����
		case 4:
			{				
				m_ImageBrustMark.AlphaDrawImage(pDC,m_ptMark[i].x,m_ptMark[i].y,RGB(255,0,255));
				break;
			}
		}		
	}

	//ׯ�ұ�ʶ	
	if ((m_wBankerStation != 255))
	{
		m_ImageBanker.AlphaDrawImage(pDC,m_ptMark[m_wBankerStation].x,m_ptMark[m_wBankerStation].y,RGB(255,0,255));
	}
	else m_wBankerStation = 255;

	return;
}

//��ʼ��ť
void CBJGameView::OnStart()
{		
	memset(m_cbTopCardSum, 0, sizeof(m_cbTopCardSum));
	memset(m_cbBottomCardSum, 0, sizeof(m_cbBottomCardSum));

	CWnd * pWnd = ::AfxGetMainWnd();
	if(!pWnd)
	{
		return;	
	}
	pWnd->SendMessage(IDM_GAME_START,0,0);
}
//��ע��ť
void CBJGameView::OnAddGold()
{
	CWnd * pWnd = ::AfxGetMainWnd();
	if(!pWnd)
	{
		return;	
	}
	pWnd->SendMessage(IDM_ADD_GOLD,0,0);
}
//ȡ����ť
void CBJGameView::OnGiveUp()
{
	CWnd * pWnd = ::AfxGetMainWnd();
	if(!pWnd)
	{
		return;	
	}
	pWnd->SendMessage(IDM_GIVE_UP,0,0);
}

//Ҫ�ư�ť
void CBJGameView::OnGetCard()
{
	CWnd * pWnd = ::AfxGetMainWnd();
	if(!pWnd)
	{
		return;	
	}
	pWnd->SendMessage(IDM_GET_CARD,0,0);
}

//ͣ�ư�ť
void CBJGameView::OnStopCard()
{
	CWnd * pWnd = ::AfxGetMainWnd();
	if(!pWnd)
	{
		return;	
	}
	pWnd->SendMessage(IDM_STOP_CARD,0,0);
}

//˫����ť
void CBJGameView::OnDoubleCard()
{
	CWnd * pWnd = ::AfxGetMainWnd();
	if(!pWnd)
	{
		return;	
	}
	pWnd->SendMessage(IDM_DOUBLE_CARD,0,0);
}

//���ư�ť
void CBJGameView::OnCutCard()
{
	CWnd * pWnd = ::AfxGetMainWnd();
	if(!pWnd)
	{
		return;	
	}
	pWnd->SendMessage(IDM_CUT_CARD,0,0);
}

//��ұ���
void CBJGameView::SetGoldTitleInfo(DWORD lMaxGold, DWORD lBasicGold)
{
	//���ñ���
	m_lMaxGold   = lMaxGold;
	m_lBasicGold = lBasicGold;

	//������ͼ
	UpdateGameView(NULL);

	return;
}

//�û�����
void CBJGameView::SetUserGoldInfo(WORD wViewChairID, bool bTableGold, DWORD dwGold)
{
	//�����ж�
	WORD wGoldPos = wViewChairID * 2 + ((bTableGold == true) ? 1 : 0);
	
	if (wGoldPos >= CountArray(m_GoldStation)) return;

	//���ñ���
	DWORD m_dwAllGold = 0L;

	m_GoldView[wGoldPos].SetGold(dwGold);

	for (int i = 0; i < CountArray(m_GoldStation); i++) 
	{
		m_dwAllGold += m_GoldView[i].GetGold();
	}
	//������ͼ
	UpdateGameView(NULL);

	return;
}
//////////////////////////////////////////////////////////////////////////





