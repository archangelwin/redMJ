#include "StdAfx.h"
#include "Resource.h"
#include "GameClientView.h"
#include ".\gameclientview.h"

//////////////////////////////////////////////////////////////////////////
//��ť��ʶ 

#define IDC_START						100								//��ʼ��ť
#define IDC_ONE_SCORE					101								//1 �ְ�ť
#define IDC_TWO_SCORE					102								//2 �ְ�ť
#define IDC_THREE_SCORE					103								//3 �ְ�ť
#define IDC_GIVE_UP_SCORE				104								//������ť
#define IDC_OUT_CARD					105								//���ư�ť
#define IDC_PASS_CARD					106								//PASS��ť
#define IDC_AUTO_OUTCARD                107                             //��ʾ��Ŧ

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameClientView, CGameFrameView)
	ON_WM_CREATE()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_OUT_CARD, OnOutCard)
	ON_BN_CLICKED(IDC_PASS_CARD, OnPassCard)
	ON_BN_CLICKED(IDC_ONE_SCORE, OnOneScore)
	ON_BN_CLICKED(IDC_TWO_SCORE, OnTwoScore)
	ON_BN_CLICKED(IDC_THREE_SCORE, OnThreeScore)
	ON_BN_CLICKED(IDC_AUTO_OUTCARD, OnAutoOutCard)
	ON_BN_CLICKED(IDC_GIVE_UP_SCORE, OnGiveUpScore)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameClientView::CGameClientView(void) : CGameFrameView(true,24)
{
	//��Ϸ����
	m_lBaseScore=0;
	m_wBombTime=1;
	m_cbLandScore=0;
	m_wLandUser=INVALID_CHAIR;
	m_Help=false;

	//���ñ���
	m_bDeasilOrder=true;

	//״̬����
	m_bLandTitle=false;
	memset(m_bPass,0,sizeof(m_bPass));
	memset(m_bScore,0,sizeof(m_bScore));
	memset(m_bCardCount,0,sizeof(m_bCardCount));

	//λ����Ϣ
	memset(m_ptScore,0,sizeof(m_ptScore));
	memset(m_ptLand,0,sizeof(m_ptLand));

	//������Դ
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_ImageBomb.SetLoadInfo(IDB_BOMB,hInstance);
	m_ImageLandScore.SetLoadInfo(IDB_LAND_SCORE,hInstance);
	m_ImageLeve1.SetLoadInfo(IDB_LEVEL1,hInstance);
	m_ImageLeve2.SetLoadInfo(IDB_LEVEL2,hInstance);
	m_ImageLeve3.SetLoadInfo(IDB_LEVEL3,hInstance);
	m_ImageLeve4.SetLoadInfo(IDB_LEVEL4,hInstance);
	m_ImageLeve5.SetLoadInfo(IDB_LEVEL5,hInstance);
	m_ImageLeve6.SetLoadInfo(IDB_LEVEL6,hInstance);
	m_ImageScore.SetLoadInfo(IDB_SCORE,hInstance);
	m_ImageLand.SetLoadInfo(IDB_BANKER,hInstance);
	m_ImageBack.SetLoadInfo(IDB_VIEW_BACK,hInstance);
	m_ImageCenter.SetLoadInfo(IDB_VIEW_CENTER,hInstance);
	m_ImageLc.SetLoadInfo(IDB_VIEW_LC,hInstance);
	m_ImageHeadBg.SetLoadInfo(IDB_HEAD_BG,hInstance);
	m_ImageHelp.SetLoadInfo(IDB_HELP,hInstance);

	//����λ��
	CImageHandle ImageHandleLand(&m_ImageLand);
	m_LandSize.cx=m_ImageLand.GetWidth();
	m_LandSize.cy=m_ImageLand.GetHeight();


	return;
}

//��������
CGameClientView::~CGameClientView(void)
{
}

//������Ϣ
int CGameClientView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//�����ؼ�
	CRect CreateRect(0,0,0,0);
	m_ScoreView.Create(IDD_GAME_SCORE,this);

	//�����˿�
	for (WORD i=0;i<3;i++)
	{
		m_UserCardControl[i].SetDirection(true);
		m_UserCardControl[i].SetDisplayFlag(true);
		m_UserCardControl[i].Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CreateRect,this,20+i);
	}
	for (WORD i=0;i<2;i++) 
	{
		m_LeaveCardControl[i].SetDirection(false);
		m_LeaveCardControl[i].SetDisplayFlag(true);
		m_LeaveCardControl[i].SetCardSpace(0,18,0);
		m_LeaveCardControl[i].Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CreateRect,this,30+i);
	}

	m_BackCardControl.SetCardSpace(80,0,0);
	m_BackCardControl.SetDisplayFlag(true);
	m_HandCardControl.SetSinkWindow(AfxGetMainWnd());
	m_HandCardControl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CreateRect,this,40);
	m_BackCardControl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CreateRect,this,41);

	//������ť
	m_btStart.Create(TEXT(""),WS_CHILD,CreateRect,this,IDC_START);
	m_btOutCard.Create(TEXT(""),WS_CHILD,CreateRect,this,IDC_OUT_CARD);
	m_btPassCard.Create(TEXT(""),WS_CHILD,CreateRect,this,IDC_PASS_CARD);
	m_btOneScore.Create(TEXT(""),WS_CHILD,CreateRect,this,IDC_ONE_SCORE);
	m_btTwoScore.Create(TEXT(""),WS_CHILD,CreateRect,this,IDC_TWO_SCORE);
	m_btThreeScore.Create(TEXT(""),WS_CHILD,CreateRect,this,IDC_THREE_SCORE);
	m_btGiveUpScore.Create(TEXT(""),WS_CHILD,CreateRect,this,IDC_GIVE_UP_SCORE);
	m_btAutoOutCard.Create(TEXT(""),WS_CHILD,CreateRect,this,IDC_AUTO_OUTCARD);

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btStart.SetButtonImage(IDB_START,hInstance,false);
	m_btOutCard.SetButtonImage(IDB_OUT_CARD,hInstance,false);
	m_btPassCard.SetButtonImage(IDB_PASS,hInstance,false);
	m_btOneScore.SetButtonImage(IDB_ONE_SCORE,hInstance,false);
	m_btTwoScore.SetButtonImage(IDB_TWO_SCORE,hInstance,false);
	m_btThreeScore.SetButtonImage(IDB_THREE_SCORE,hInstance,false);
	m_btGiveUpScore.SetButtonImage(IDB_GIVE_UP,hInstance,false);
	m_btAutoOutCard.SetButtonImage(IDB_AUTO_OUT_CARD,hInstance,false);

	//��ȡ����
	m_bDeasilOrder=AfxGetApp()->GetProfileInt(TEXT("GameOption"),TEXT("DeasilOrder"),FALSE)?true:false;


	return 0;
}

//�����Ϣ
void CGameClientView::OnRButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnRButtonUp(nFlags, Point);

	//������Ϣ
	AfxGetMainWnd()->SendMessage(IDM_OUT_CARD,1,1);

	return;
}

//���˫��
void CGameClientView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	__super::OnLButtonDblClk(nFlags, point);

	//�����˿�
	m_btOutCard.EnableWindow(FALSE);
	m_HandCardControl.ShootAllCard(false);

	return;
}

//���ý���
void CGameClientView::ResetGameView()
{
	//��Ϸ����
	m_lBaseScore=0;
	m_wBombTime=1;
	m_cbLandScore=0;
	m_wLandUser=INVALID_CHAIR;
	m_Help=false;

	//״̬����
	m_bLandTitle=false;
	memset(m_bPass,0,sizeof(m_bPass));
	memset(m_bScore,0,sizeof(m_bScore));
	memset(m_bCardCount,0,sizeof(m_bCardCount));

	//���ؿؼ�
	m_ScoreView.ShowWindow(SW_HIDE);

	//���ذ�ť
	m_btStart.ShowWindow(SW_HIDE);
	m_btOutCard.ShowWindow(SW_HIDE);
	m_btPassCard.ShowWindow(SW_HIDE);
	m_btOneScore.ShowWindow(SW_HIDE);
	m_btTwoScore.ShowWindow(SW_HIDE);
	m_btThreeScore.ShowWindow(SW_HIDE);
	m_btGiveUpScore.ShowWindow(SW_HIDE);
	m_btAutoOutCard.ShowWindow(SW_HIDE);

	//���ÿؼ�
	m_btOutCard.EnableWindow(FALSE);
	m_btPassCard.EnableWindow(FALSE);
	m_btAutoOutCard.EnableWindow(FALSE);

	//�˿˿ؼ�
	m_BackCardControl.SetCardData(NULL,0);
	m_HandCardControl.SetCardData(NULL,0);
	m_HandCardControl.SetPositively(false);
	m_HandCardControl.SetDisplayFlag(false);
	m_LeaveCardControl[0].SetCardData(NULL,0);
	m_LeaveCardControl[1].SetCardData(NULL,0);

	for (WORD i=0;i<GAME_PLAYER;i++) m_UserCardControl[i].SetCardData(NULL,0);

	return;
}

//�����ؼ�
void CGameClientView::RectifyGameView(int nWidth, int nHeight)
{
	//��������
	if (m_bDeasilOrder==true)
	{
		m_ptFace[2].x=nWidth-m_nXBorder-m_nXFace-115;
		m_ptFace[2].y=nHeight/2-m_nYFace-65;
	
		m_ptName[2].x=nWidth-m_nXBorder-m_nXFace-95;
		m_ptName[2].y=nHeight/2-m_nYFace-77;

		m_ptTimer[2].x=nWidth-m_nXBorder-m_nXFace-65;
		m_ptTimer[2].y=nHeight/2-m_nYFace-m_nYTimer+60;

		m_ptReady[2].x=nWidth-m_nXBorder-m_nXTimer-160;
		m_ptReady[2].y=nHeight/2-m_nYFace-m_nYTimer/2-38;

		m_ptScore[2].x=nWidth-m_nXBorder-m_nXFace-80;
		m_ptScore[2].y=nHeight/2-m_nYFace-150;

		m_ptLand[2].x=nWidth-m_nXBorder-m_LandSize.cx;
		m_ptLand[2].y=nHeight/2-175;

		m_ptFace[0].x=m_nXBorder+10;   
		m_ptFace[0].y=nHeight/2-m_nYFace-65;
		
		m_ptName[0].x=m_nXBorder+m_nXFace-5;
		m_ptName[0].y=nHeight/2+m_nYFace-142;
		
		m_ptTimer[0].x=m_nXBorder+60;
		m_ptTimer[0].y=nHeight/2-m_nYFace+60-m_nYTimer;

		m_ptReady[0].x=m_nXBorder+5+155+m_nXTimer;
		m_ptReady[0].y=nHeight/2-m_nYFace-m_nYTimer/2-40;

		m_ptScore[0].x=m_nXBorder+m_nXFace+30;
		m_ptScore[0].y=nHeight/2-m_nYFace-150;

		m_ptLand[0].x=m_nXBorder;
		m_ptLand[0].y=nHeight/2-175;
	}
	else
	{
		m_ptFace[2].x=nWidth-m_nXBorder-m_nXFace-115;
		m_ptFace[2].y=nHeight/2-m_nYFace-65;
	
		m_ptName[2].x=nWidth-m_nXBorder-m_nXFace-95;
		m_ptName[2].y=nHeight/2-m_nYFace-77;

		m_ptTimer[2].x=nWidth-m_nXBorder-m_nXFace-65;
		m_ptTimer[2].y=nHeight/2-m_nYFace-m_nYTimer+60;

		m_ptReady[2].x=nWidth-m_nXBorder-m_nXTimer-160;
		m_ptReady[2].y=nHeight/2-m_nYFace-m_nYTimer/2-38;

		m_ptScore[2].x=nWidth-m_nXBorder-m_nXFace-80;
		m_ptScore[2].y=nHeight/2-m_nYFace-150;

		m_ptLand[2].x=nWidth-m_nXBorder-m_LandSize.cx;
		m_ptLand[2].y=nHeight/2-175;

		m_ptFace[0].x=m_nXBorder+10;   
		m_ptFace[0].y=nHeight/2-m_nYFace-65;
		
		m_ptName[0].x=m_nXBorder+m_nXFace-5;
		m_ptName[0].y=nHeight/2+m_nYFace-142;
		
		m_ptTimer[0].x=m_nXBorder+60;
		m_ptTimer[0].y=nHeight/2-m_nYFace+60-m_nYTimer;

		m_ptReady[0].x=m_nXBorder+5+155+m_nXTimer;
		m_ptReady[0].y=nHeight/2-m_nYFace-m_nYTimer/2-40;

		m_ptScore[0].x=m_nXBorder+m_nXFace+30;
		m_ptScore[0].y=nHeight/2-m_nYFace-150;

		m_ptLand[0].x=m_nXBorder;
		m_ptLand[0].y=nHeight/2-175;
	}

	/*m_ptFace[1].x=nWidth/2-m_nXFace/2-40;
	m_ptFace[1].y=nHeight-m_nYBorder-m_nYFace-40;*/

	m_ptFace[1].x=nWidth-150;
	m_ptFace[1].y=nHeight-m_nYBorder-m_nYFace-25;

	m_ptName[1].x=nWidth-130;
	m_ptName[1].y=nHeight-m_nYBorder-m_nYFace-37;

	m_ptTimer[1].x=nWidth/2-m_nXFace/2;
	m_ptTimer[1].y=nHeight-m_nYBorder-m_nYTimer-5;

	m_ptReady[1].x=nWidth/2-m_nXTimer-m_nXFace/2+30;
	m_ptReady[1].y=nHeight-m_nYBorder-m_nYTimer/2-110;

	m_ptScore[1].x=nWidth/2-35;
	m_ptScore[1].y=nHeight-m_nYBorder-m_nYFace-210;

	m_ptLand[1].x=nWidth-200;
	m_ptLand[1].y=nHeight-m_nXBorder-m_LandSize.cy-30;

	POINT *pChatPt = GetChatPt();
	pChatPt[SCP_B].x =m_ptName[1].x-25;
	pChatPt[SCP_B].y =m_ptName[1].y-60;

	//�ƶ���ť
	CRect rcButton;
	HDWP hDwp=BeginDeferWindowPos(6);
	m_btStart.GetWindowRect(&rcButton);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;
	DeferWindowPos(hDwp,m_btStart,NULL,nWidth/2-rcButton.Width()/2,nHeight-m_nYBorder-60,0,0,uFlags);
	DeferWindowPos(hDwp,m_btOutCard,NULL,nWidth/2-rcButton.Width()*3/2-10,nHeight-220-m_nYBorder,0,0,uFlags);
	DeferWindowPos(hDwp,m_btPassCard,NULL,nWidth/2-rcButton.Width()/2,nHeight-220-m_nYBorder,0,0,uFlags);
	DeferWindowPos(hDwp,m_btAutoOutCard,NULL,nWidth/2+rcButton.Width()/2+10,nHeight-220-m_nYBorder,0,0,uFlags);

	DeferWindowPos(hDwp,m_btOneScore,NULL,nWidth/2-135-rcButton.Width()/2,nHeight-220-m_nYBorder,0,0,uFlags);
	DeferWindowPos(hDwp,m_btTwoScore,NULL,nWidth/2-45-rcButton.Width()/2,nHeight-220-m_nYBorder,0,0,uFlags);
	DeferWindowPos(hDwp,m_btThreeScore,NULL,nWidth/2+45-rcButton.Width()/2,nHeight-220-m_nYBorder,0,0,uFlags);
	DeferWindowPos(hDwp,m_btGiveUpScore,NULL,nWidth/2+135-rcButton.Width()/2,nHeight-220-m_nYBorder,0,0,uFlags);

	EndDeferWindowPos(hDwp);

	//�ƶ��˿�
	//����
	m_BackCardControl.SetBenchmarkPos(nWidth/2,m_nYBorder+10,enXCenter,enYTop);
	//������
	m_HandCardControl.SetBenchmarkPos(nWidth/2,nHeight-m_nYFace-m_nYBorder-30,enXCenter,enYBottom);
	//�Լ�����
	m_UserCardControl[1].SetBenchmarkPos(nWidth/2,nHeight-220-m_nYBorder,enXCenter,enYBottom);

	//�û��˿�
	if (m_bDeasilOrder==true)
	{
		m_UserCardControl[2].SetBenchmarkPos(nWidth-m_nXFace-m_nXBorder-130,nHeight/2-80,enXRight,enYCenter);
		m_UserCardControl[0].SetBenchmarkPos(m_nXBorder+m_nXFace+130,nHeight/2-80,enXLeft,enYCenter);
		m_LeaveCardControl[1].SetBenchmarkPos(nWidth-m_nXBorder-m_nXFace-130,nHeight/2-65,enXRight,enYCenter);
		m_LeaveCardControl[0].SetBenchmarkPos(m_nXBorder+m_nXFace+130,nHeight/2-65,enXLeft,enYCenter);
	}
	else 
	{
		m_UserCardControl[2].SetBenchmarkPos(nWidth-m_nXFace-m_nXBorder-130,nHeight/2-80,enXRight,enYCenter);
		m_UserCardControl[0].SetBenchmarkPos(m_nXBorder+m_nXFace+130,nHeight/2-80,enXLeft,enYCenter);
		m_LeaveCardControl[1].SetBenchmarkPos(nWidth-m_nXBorder-m_nXFace-130,nHeight/2-65,enXRight,enYCenter);
		m_LeaveCardControl[0].SetBenchmarkPos(m_nXBorder+m_nXFace+130,nHeight/2-65,enXLeft,enYCenter);
	}

	//������ͼ
	CRect rcControl;
	m_ScoreView.GetWindowRect(&rcControl);
	//m_ScoreView.SetWindowPos(NULL,(nWidth-rcControl.Width())/2,(nHeight-rcControl.Height()-100)/2,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_ScoreView.SetWindowPos(NULL,(nWidth-50)/2,(nHeight-100)/2,0,0,SWP_NOZORDER|SWP_NOSIZE);

	return;
}

//�滭����
void CGameClientView::DrawGameView(CDC * pDC, int nWidth, int nHeight)
{
	//�滭����
	CImageHandle m_ImageCenterImg(&m_ImageCenter);
	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);
	m_ImageCenter.StretchBlt(pDC->m_hDC,CRect(0,0,nWidth,nHeight),CRect(0,0,m_ImageCenter.GetWidth(),m_ImageCenter.GetHeight()));

	CImageHandle HandleHeadBg(&m_ImageHeadBg);
	
	//�滭�û�
	TCHAR szBuffer[32];
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//��������
		WORD wUserTimer=GetUserTimer(i);
		const tagUserData * pUserData=GetUserInfo(i);

		//�滭�û�
		if (pUserData!=NULL)
		{
			//m_ImageHeadBg.AlphaDrawImage(pDC,m_ptFace[i].x-10,m_ptFace[i].y-25,RGB(255,0,255));
			m_ImageHeadBg.AlphaDrawImage(pDC,m_ptFace[i].x-3,m_ptFace[i].y-15,RGB(255,0,255));

			//�û�����
			pDC->SetTextColor((wUserTimer>0)?RGB(250,250,250):RGB(220,220,220));
			pDC->SetTextAlign(((i==0)&&(m_bDeasilOrder==true))||((i==2)&&(m_bDeasilOrder==false))?TA_CENTER:TA_CENTER);
			pDC->TextOut(m_ptName[i].x+77,m_ptName[i].y+1,pUserData->szName,lstrlen(pUserData->szName));
			
			//�û���ң�ͶӰЧ����
			pDC->SetTextColor((wUserTimer>0)?RGB(0,0,0):RGB(0,0,0));
			pDC->SetTextAlign(((i==0)&&(m_bDeasilOrder==true))||((i==2)&&(m_bDeasilOrder==false))?TA_RIGHT:TA_LEFT);
			CString s;
			s.Format("%d",pUserData->lScore);

			if(i!=2)
			{
				pDC->TextOut(m_ptName[i].x+49,m_ptName[i].y+68,s,lstrlen(s));
			}
			else
			{
				pDC->TextOut(m_ptName[i].x+90,m_ptName[i].y+67,s,lstrlen(s));
			}

			pDC->SetTextColor((wUserTimer>0)?RGB(250,250,250):RGB(255,255,0));
			pDC->SetTextAlign(((i==0)&&(m_bDeasilOrder==true))||((i==2)&&(m_bDeasilOrder==false))?TA_RIGHT:TA_LEFT);
	
			if(i!=2)
			{
				pDC->TextOut(m_ptName[i].x+48,m_ptName[i].y+67,s,lstrlen(s));
			}
			else
			{
				pDC->TextOut(m_ptName[i].x+89,m_ptName[i].y+66,s,lstrlen(s));
			}


			//�û����ǵȼ�
			if (pUserData->lExperience<=500L) 
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve1);
				if(i!=2)
				{
					m_ImageLeve1.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve1.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
			}
			if ((pUserData->lExperience>500L)&&(pUserData->lExperience<=1500L)) 
			{

				CImageHandle ImageHandleLevel(&m_ImageLeve2);
				if(i!=2)
				{
					m_ImageLeve2.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve2.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
			}
			if ((pUserData->lExperience>1500L)&&(pUserData->lExperience<=4000L)) 
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve3);
				if(i!=2)
				{
					m_ImageLeve3.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve3.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
			}
			if ((pUserData->lExperience>4000L)&&(pUserData->lExperience<=10000L))
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve4);
				if(i!=2)
				{
					m_ImageLeve4.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve4.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
			}
			if ((pUserData->lExperience>10000L)&&(pUserData->lExperience<=20000L)) 
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve5);
				if(i!=2)
				{
					m_ImageLeve5.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve5.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
			}
			if (pUserData->lExperience>20000L)
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve6);
				if(i!=2)
				{
					m_ImageLeve6.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve6.AlphaDrawImage(pDC,m_ptName[i].x+30,m_ptName[i].y+43,RGB(255,0,255));
				}
			}

			//ʣ���˿�
			if (pUserData->cbUserStatus>=US_PLAY)
			{
				if(i!=2)
				{
					if(i!=1)
					{
						_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%ld �ţ�"),m_bCardCount[i]);
						pDC->TextOut(m_ptName[i].x+18,m_ptName[i].y+18+55+20,szBuffer,lstrlen(szBuffer));
					}
				}
				else
				{
					_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%ld �ţ�"),m_bCardCount[i]);
					pDC->TextOut(m_ptName[i].x+80,m_ptName[i].y+18+55+20,szBuffer,lstrlen(szBuffer));
				}
			}

			//������Ϣ
			if (wUserTimer!=0) DrawUserTimer(pDC,m_ptTimer[i].x,m_ptTimer[i].y,wUserTimer);
			if (pUserData->cbUserStatus==US_READY) DrawUserReady(pDC,m_ptReady[i].x,m_ptReady[i].y);
			//DrawUserFace(pDC,pUserData->wFaceID,m_ptFace[i].x,m_ptFace[i].y,pUserData->cbUserStatus==US_OFFLINE);
			DrawUserBigFace(pDC,pUserData->wFaceID,m_ptFace[i].x,m_ptFace[i].y,pUserData->cbUserStatus==US_OFFLINE);
		}
	}

	//�зֱ�־
	CImageHandle ImageHnadleScore(&m_ImageScore);
	int nXImagePos,nImageWidth=m_ImageScore.GetWidth(),nImageHeight=m_ImageScore.GetHeight();
	for (WORD i=0;i<3;i++)
	{
		if ((m_bScore[i]!=0)||(m_bPass[i]==true))
		{
			if ((m_bPass[i]==true)||(m_bScore[i]==255)) nXImagePos=m_ImageScore.GetWidth()*3/4;
			else nXImagePos=(m_bScore[i]-1)*m_ImageScore.GetWidth()/4;
			m_ImageScore.AlphaDrawImage(pDC,m_ptScore[i].x,m_ptScore[i].y,nImageWidth/4,nImageHeight,nXImagePos,0,RGB(255,0,255));
			
		}
	}

	//ׯ��λ��
	if (m_wLandUser!=INVALID_CHAIR)
	{
		//��ȡ�û�
		const tagUserData * pUserData=GetUserInfo(m_wLandUser);
		if (pUserData!=NULL)
		{
			//��������
			TCHAR szBuffer[64];
			CImageHandle ImageHandleLand(&m_ImageLand);
			
			//���� DC
			pDC->SetTextAlign(TA_LEFT|TA_TOP);
			pDC->SetTextColor(RGB(250,250,250));

			CImageHandle ImageHandleLandScore(&m_ImageLandScore);
			m_ImageLandScore.AlphaDrawImage(pDC,m_nXBorder+5,m_nYBorder+m_ImageLandScore.GetHeight()-42,RGB(255,0,255));

			//�滭��Ϣ
			
			m_ImageLand.AlphaDrawImage(pDC,m_ptLand[m_wLandUser].x,m_ptLand[m_wLandUser].y,RGB(255,0,255));

			/*
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("������%s"),pUserData->szName);
			pDC->TextOut(m_nXBorder+m_nXFace+10,m_nYBorder+8,szBuffer,lstrlen(szBuffer));
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("�׷֣�%d ��"),m_cbLandScore);
			pDC->TextOut(m_nXBorder+m_nXFace+10,m_nYBorder+25,szBuffer,lstrlen(szBuffer));
			DrawUserFace(pDC,pUserData->wFaceID,m_nXBorder+5,m_nYBorder+5,false);
			*/
			
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("%s"),pUserData->szName);
			pDC->TextOut(m_nXBorder+m_nXFace+13,m_nYBorder+8,szBuffer,lstrlen(szBuffer));
			_snprintf(szBuffer,sizeof(szBuffer),TEXT("%d ��"),m_cbLandScore);
			pDC->TextOut(m_nXBorder+m_nXFace+13,m_nYBorder+32,szBuffer,lstrlen(szBuffer));
			
		}
	}

	//ը������
	if (m_wBombTime>1)
	{
		//ը����־
		CImageHandle ImageHandle(&m_ImageBomb);
		m_ImageBomb.AlphaDrawImage(pDC,nWidth-145,m_nYBorder+15,RGB(255,0,255));

		//���� DC
		pDC->SetTextColor(RGB(250,250,250));
		pDC->SetTextAlign(TA_LEFT|TA_TOP);

		//ը������
		TCHAR szBuffer[64];
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("ը��������%d"),m_wBombTime);
		pDC->TextOut(nWidth-95,m_nYBorder+35,szBuffer,lstrlen(szBuffer));
	}

	//������Ϣ
	if (m_bLandTitle==true)
	{
		//������Դ
		CFont InfoFont;
		InfoFont.CreateFont(-36,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("����"));

		//���� DC
		pDC->SetTextColor(RGB(201,229,133));
		pDC->SetTextAlign(TA_CENTER|TA_TOP);
		CFont * pOldFont=pDC->SelectObject(&InfoFont);

		//�滭��Ϣ
		pDC->TextOut(nWidth/2,200,"��  ��  ��");

		//������Դ
		pDC->SelectObject(pOldFont);
		InfoFont.DeleteObject();
	}

	//����
	if (m_Help==true)
	{
		CImageHandle HandleHelp(&m_ImageHelp);
		m_ImageHelp.AlphaDrawImage(pDC,nWidth-310,nHeight/2-275,RGB(255,0,255));
	}
	return;
}

//�û�˳��
void CGameClientView::SetUserOrder(bool bDeasilOrder)
{
	//״̬�ж�
	if (m_bDeasilOrder==bDeasilOrder) return;

	//���ñ���
	m_bDeasilOrder=bDeasilOrder;
	AfxGetApp()->WriteProfileInt(TEXT("GameOption"),TEXT("DeasilOrder"),m_bDeasilOrder?TRUE:FALSE);

	//���ý���
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyGameView(rcClient.Width(),rcClient.Height());

	//ˢ�½���
	UpdateGameView(NULL);

	return;
}

//ը������
void CGameClientView::SetBombTime(WORD wBombTime)
{
	//���ñ���
	m_wBombTime=wBombTime;

	//ˢ�½���
	UpdateGameView(NULL);

	return;
}

//��������
void CGameClientView::SetBaseScore(LONG lBaseScore)
{
	//���ñ���
	m_lBaseScore=lBaseScore;

	//ˢ�½���
	UpdateGameView(NULL);

	return;
}

//��ʾ��ʾ
void CGameClientView::ShowLandTitle(bool bLandTitle)
{
	//���ñ���
	m_bLandTitle=bLandTitle;

	//ˢ�½���
	UpdateGameView(NULL);

	return;
}

//���÷���
void CGameClientView::SetPassFlag(WORD wChairID, bool bPass)
{
	//���ñ���
	if (wChairID==INVALID_CHAIR)
	{
		for (WORD i=0;i<GAME_PLAYER;i++) m_bPass[i]=bPass;
	}
	else m_bPass[wChairID]=bPass;

	//���½���
	UpdateGameView(NULL);

	return;
}

//�˿���Ŀ
void CGameClientView::SetCardCount(WORD wChairID, BYTE bCardCount)
{
	//���ñ���
	if (wChairID==INVALID_CHAIR)
	{
		for (WORD i=0;i<GAME_PLAYER;i++) m_bCardCount[i]=bCardCount;
	}
	else m_bCardCount[wChairID]=bCardCount;

	//���½���
	UpdateGameView(NULL);

	return;
}

//�ڿӷ���
void CGameClientView::SetLandUser(WORD wChairID, BYTE bLandScore)
{
	//���ñ���
	m_wLandUser=wChairID;
	m_cbLandScore=bLandScore;

	//���½���
	UpdateGameView(NULL);

	return;
}

//�ڿӷ���
void CGameClientView::SetLandScore(WORD wChairID, BYTE bLandScore)
{
	//���ñ���
	if (wChairID!=INVALID_CHAIR) m_bScore[wChairID]=bLandScore;
	else memset(m_bScore,0,sizeof(m_bScore));

	//���½���
	UpdateGameView(NULL);

	return;
}

//��ʼ��ť
void CGameClientView::OnStart()
{

	AfxGetMainWnd()->SendMessage(IDM_START,0,0);
	return;
}

//���ư�ť
void CGameClientView::OnOutCard()
{
	AfxGetMainWnd()->SendMessage(IDM_OUT_CARD,1,1);
	return;
}

//������ť
void CGameClientView::OnPassCard()
{
	AfxGetMainWnd()->SendMessage(IDM_PASS_CARD,1,1);
	return;
}

//�зְ�ť
void CGameClientView::OnOneScore()
{
	AfxGetMainWnd()->SendMessage(IDM_LAND_SCORE,1,1);
	return;
}

//�зְ�ť
void CGameClientView::OnTwoScore()
{
	AfxGetMainWnd()->SendMessage(IDM_LAND_SCORE,2,2);
	return;
}

//�зְ�ť
void CGameClientView::OnThreeScore()
{
	AfxGetMainWnd()->SendMessage(IDM_LAND_SCORE,3,3);
	return;
}

//������ť
void CGameClientView::OnGiveUpScore()
{
	AfxGetMainWnd()->SendMessage(IDM_LAND_SCORE,255,255);
	return;
}

//������ʾ
void CGameClientView::OnAutoOutCard()
{
	AfxGetMainWnd()->SendMessage(IDM_AUTO_OUTCARD,0,0);
	return;
}

//////////////////////////////////////////////////////////////////////////


void CGameClientView::OnSize(UINT nType, int cx, int cy)
{
	CRect rc;
	GetClientRect(rc);
	m_HandCardControl.CreateCard(rc.Width(),rc.Height());
	m_BackCardControl.CreateCard(rc.Width(),rc.Height());
	m_UserCardControl[0].CreateCard(rc.Width(),rc.Height());
	m_UserCardControl[1].CreateCard(rc.Width(),rc.Height());
	m_UserCardControl[2].CreateCard(rc.Width(),rc.Height());
	m_LeaveCardControl[0].CreateCard(rc.Width(),rc.Height());
	m_LeaveCardControl[1].CreateCard(rc.Width(),rc.Height());
	CGameFrameView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void CGameClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (GetSystemMetrics(SM_CXSCREEN)>800)
	::SendMessage(GetParent()->GetSafeHwnd(),WM_NCLBUTTONDOWN, HTCAPTION,0);
	CGameFrameView::OnLButtonDown(nFlags, point);
}


//����
void CGameClientView::SetHelp(bool bHelp)
{
	if(bHelp==true&&m_Help==true) bHelp=false;

	if (bHelp!=m_Help)
	{
		//���ñ���
		m_Help=bHelp;

		//���½���
		UpdateGameView(NULL);
	}

	return;
}
