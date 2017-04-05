#include "StdAfx.h"
#include "Resource.h"
#include "GameClientDlg.h"
#include "GameClientView.h"
#include ".\gameclientview.h"

//////////////////////////////////////////////////////////////////////////

//��ť��ʶ 
#define IDC_PLACEMENT				100									//���ְ�ť
#define IDC_SAVEPLACEMENT			102									//���水ť
#define IDC_LOADPLACEMENT			103									//���밴ť
#define IDC_RESETGAME				104									//������Ϸ
#define IDC_LOAD_HISTORY			105									//�������
#define IDC_PREV_STEP				106									//��һ����
#define IDC_NEXT_STEP				107									//��һ����
#define IDC_TURN_CHESS				108									//��ת����
#define IDC_LOSE					109									//���䰴ť
#define IDC_GIVEUP					110									//������ť
#define IDC_PEACE					111									//���尴ť




//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameClientView, CGameFrameView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_PLACEMENT,OnHitPlacement)
	ON_BN_CLICKED(IDC_RESETGAME , OnHitResetGame)
	ON_BN_CLICKED(IDC_SAVEPLACEMENT , OnSavePlacement)
	ON_BN_CLICKED(IDC_LOADPLACEMENT , OnHitLoadPlacement)
	ON_BN_CLICKED(IDC_LOAD_HISTORY,OnHitLoadHistory)
	ON_BN_CLICKED(IDC_PREV_STEP,OnHitPrevStep)
	ON_BN_CLICKED(IDC_NEXT_STEP,OnHitNextStep)
	ON_BN_CLICKED(IDC_TURN_CHESS,OnHitTurn)
	ON_BN_CLICKED(IDC_LOSE,OnHitLose)
	ON_BN_CLICKED(IDC_GIVEUP,OnHitGiveUp)
	ON_BN_CLICKED(IDC_PEACE,OnHitPeace)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameClientView::CGameClientView(void) : CGameFrameView(true,24)
{
	//���ñ���
	m_bFrameX = 255 ;
	m_bFrameY = 255 ;


	//����λͼ
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_ImageBack.SetLoadInfo(IDB_VIEW_BACK,hInstance);
	m_lCurrentStepCount = 0 ;

	m_ChessBoard.SetParent(this) ;

	//��ȡ��С

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
	CSize size = m_ChessBoard.GetChessBoradSize() ;
	m_ChessBoard.CleanChess() ;

	//m_ScoreView.Create(IDD_GAME_SCORE,this);
	//m_ScoreView.ShowWindow(SW_HIDE);

	//������ť

	CRect CreateRect(0,0,0,0);
	m_ScoreView.Create(NULL,NULL,WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,CreateRect,this,IDD_GAME_SCORE);
	m_ScoreView.ShowWindow(SW_HIDE);
	m_btPlacement.Create("�������",WS_CHILD,CreateRect,this,IDC_PLACEMENT);
	m_btSavePlacement.Create("���沼��",WS_CHILD,CreateRect,this,IDC_SAVEPLACEMENT);
	m_btLoadPlacement.Create("���벼��",WS_CHILD,CreateRect,this,IDC_LOADPLACEMENT);
	m_btResetGame.Create("������Ϸ",WS_CHILD,CreateRect,this,IDC_RESETGAME);
	m_btLoadHistory.Create(TEXT("װ�����"),WS_CHILD|BS_OWNERDRAW,CreateRect,this,IDC_LOAD_HISTORY);
	m_btPrevStep.Create(TEXT("��һ����"),WS_CHILD|BS_OWNERDRAW,CreateRect,this,IDC_PREV_STEP);	
	m_btNextStep.Create(TEXT("��һ����"),WS_CHILD|BS_OWNERDRAW,CreateRect,this,IDC_NEXT_STEP);	
	m_btTurn.Create(TEXT("��ת����"),WS_CHILD|BS_OWNERDRAW,CreateRect,this,IDC_TURN_CHESS);		
	m_btLose.Create(TEXT("��������"),WS_CHILD|BS_OWNERDRAW,CRect(0,0,60,20),this,IDC_LOSE);
	m_btGiveUp.Create(TEXT("����һ��"),WS_CHILD|BS_OWNERDRAW,CRect(0,0,60,20),this,IDC_GIVEUP);
	m_btPeace.Create(TEXT("�������"),WS_CHILD|BS_OWNERDRAW,CRect(0,0,60,20),this,IDC_PEACE);



	//����λͼ
	HINSTANCE hInstance=AfxGetInstanceHandle();

	m_btPlacement.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btSavePlacement.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btLoadPlacement.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btResetGame.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btLoadHistory.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btPrevStep.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btNextStep.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btTurn.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btLose.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btGiveUp.SetButtonImage(IDB_BT_BUTTON,hInstance,false);
	m_btPeace.SetButtonImage(IDB_BT_BUTTON,hInstance,false);

	m_ImageHeadBg.SetLoadInfo(IDB_HEAD_BG1,hInstance);
	m_ImageLeve1.SetLoadInfo(IDB_LEVEL1,hInstance);
	m_ImageLeve2.SetLoadInfo(IDB_LEVEL2,hInstance);
	m_ImageLeve3.SetLoadInfo(IDB_LEVEL3,hInstance);
	m_ImageLeve4.SetLoadInfo(IDB_LEVEL4,hInstance);
	m_ImageLeve5.SetLoadInfo(IDB_LEVEL5,hInstance);
	m_ImageLeve6.SetLoadInfo(IDB_LEVEL6,hInstance);

	m_btPlacement.ShowWindow(SW_SHOW) ;
	m_btPlacement.EnableWindow(TRUE) ;
	m_btSavePlacement.ShowWindow(SW_SHOW) ;
	m_btSavePlacement.EnableWindow(TRUE) ;
	m_btLoadPlacement.ShowWindow(SW_SHOW) ;
	m_btLoadPlacement.EnableWindow(TRUE) ;

	m_btLoadHistory.ShowWindow(SW_SHOW) ;
	m_btLoadHistory.EnableWindow(TRUE) ;

	m_btPrevStep.ShowWindow(SW_SHOW) ;
	m_btPrevStep.EnableWindow(FALSE) ;
	m_btNextStep.ShowWindow(SW_SHOW) ;
	m_btNextStep.EnableWindow(FALSE) ;
	m_btTurn.ShowWindow(SW_SHOW) ;
	m_btTurn.EnableWindow(FALSE) ;

	m_bDeasilOrder = (AfxGetApp()->GetProfileInt(TEXT("GameOption") , TEXT("DeasilOrder") , FALSE)) ? true : false ;

	return 0;
}

//���ý���
void CGameClientView::ResetGameView()
{
	//���̿���
	m_ChessBoard.CleanChess();

	//�ؼ�����
	if (m_PeaceRequest.GetSafeHwnd()) m_PeaceRequest.DestroyWindow();

	return;
}

//�����ؼ�
void CGameClientView::RectifyGameView(int nWidth, int nHeight)
{

	RECT btRect;
	m_btPlacement.GetClientRect(&btRect);
	CSize boardSize = m_ChessBoard.GetChessBoradSize() ;

	//��ťλ��
	m_btPlacement.MoveWindow(nWidth-btRect.right-(nWidth-boardSize.cx)/2-10,nHeight-3*btRect.bottom-80,btRect.right,btRect.bottom);
	m_btSavePlacement.MoveWindow(nWidth-btRect.right-(nWidth-boardSize.cx)/2-10,nHeight-2*btRect.bottom-80,btRect.right,btRect.bottom);
	m_btLoadPlacement.MoveWindow(nWidth-btRect.right-(nWidth-boardSize.cx)/2-10,nHeight-btRect.bottom-80,btRect.right,btRect.bottom);
	m_btResetGame.MoveWindow(nWidth-btRect.right-(nWidth-boardSize.cx)/2-10,nHeight-3*btRect.bottom-80,btRect.right,btRect.bottom);

	m_btLoadHistory.MoveWindow(nWidth-2*btRect.right-(nWidth-boardSize.cx)/2-15,nHeight-4*btRect.bottom-80,btRect.right,btRect.bottom);
	m_btPrevStep.MoveWindow(nWidth-2*btRect.right-(nWidth-boardSize.cx)/2-15,nHeight-3*btRect.bottom-80,btRect.right,btRect.bottom);
	m_btNextStep.MoveWindow(nWidth-2*btRect.right-(nWidth-boardSize.cx)/2-15,nHeight-2*btRect.bottom-80,btRect.right,btRect.bottom);
	m_btTurn.MoveWindow(nWidth-2*btRect.right-(nWidth-boardSize.cx)/2-15,nHeight-btRect.bottom-80,btRect.right,btRect.bottom);

	m_btLose.MoveWindow(nWidth-2*btRect.right-(nWidth-boardSize.cx)/2-15,nHeight-3*btRect.bottom-80,btRect.right,btRect.bottom);
	m_btGiveUp.MoveWindow(nWidth-2*btRect.right-(nWidth-boardSize.cx)/2-15,nHeight-2*btRect.bottom-80,btRect.right,btRect.bottom);
	m_btPeace.MoveWindow(nWidth-2*btRect.right-(nWidth-boardSize.cx)/2-15,nHeight-btRect.bottom-80,btRect.right,btRect.bottom);



	//����ƫ��
	//m_ChessBoard.SetExcursionX((nWidth-boardSize.cx)/2) ;
	m_ChessBoard.SetExcursionX(30) ;
	m_ChessBoard.SetExcursionY((nHeight-boardSize.cy)/2+30) ;


	//��������
	if (m_bDeasilOrder==false)
	{
		m_ptFace[3].x=nWidth-m_nXBorder-m_nXFace-145;
		m_ptFace[3].y=nHeight/2-m_nYFace-190;
		m_ptName[3].x=nWidth-m_nXBorder-m_nXFace-74;
		m_ptName[3].y=nHeight/2+m_nYFace-257;
		//m_ptTimer[3].x=nWidth-183;
		//m_ptTimer[3].y=171;
		m_ptTimer[3].x=nWidth-m_nXBorder-m_nXTimer-200;
		m_ptTimer[3].y=nHeight/2-m_nYFace-m_nYTimer/2-160;
		m_ptReady[3].x=nWidth-m_nXBorder-m_nXTimer-200;
		m_ptReady[3].y=nHeight/2-m_nYFace-m_nYTimer/2-160;

		m_ptFace[1].x=nWidth-m_nXBorder-m_nXFace-145;
		m_ptFace[1].y=nHeight/2-m_nYFace-80;
		m_ptName[1].x=nWidth-m_nXBorder-m_nXFace-74;
		m_ptName[1].y=nHeight/2+m_nYFace-147;
		m_ptTimer[1].x=nWidth-m_nXBorder-m_nXTimer-200;
		m_ptTimer[1].y=nHeight/2-m_nYFace-m_nYTimer/2-50;
		m_ptReady[1].x=nWidth-m_nXBorder-m_nXTimer-200;
		m_ptReady[1].y=nHeight/2-m_nYFace-m_nYTimer/2-50;
	}
	else
	{
		m_ptFace[3].x=nWidth-m_nXBorder-m_nXFace-145;
		m_ptFace[3].y=nHeight/2-m_nYFace-190;
		m_ptName[3].x=nWidth-m_nXBorder-m_nXFace-74;
		m_ptName[3].y=nHeight/2+m_nYFace-257;
		m_ptTimer[3].x=nWidth-m_nXBorder-m_nXTimer-200;
		m_ptTimer[3].y=nHeight/2-m_nYFace-m_nYTimer/2-160;
		m_ptReady[3].x=nWidth-m_nXBorder-m_nXTimer-200;
		m_ptReady[3].y=nHeight/2-m_nYFace-m_nYTimer/2-160;

		m_ptFace[1].x=nWidth-m_nXBorder-m_nXFace-145;
		m_ptFace[1].y=nHeight/2-m_nYFace-80;
		m_ptName[1].x=nWidth-m_nXBorder-m_nXFace-74;
		m_ptName[1].y=nHeight/2+m_nYFace-147;
		m_ptTimer[1].x=nWidth-m_nXBorder-m_nXTimer-200;
		m_ptTimer[1].y=nHeight/2-m_nYFace-m_nYTimer/2-50;
		m_ptReady[1].x=nWidth-m_nXBorder-m_nXTimer-200;
		m_ptReady[1].y=nHeight/2-m_nYFace-m_nYTimer/2-50;

		//m_ptFace[1].x=9;
		//m_ptFace[1].y=nHeight/2-m_nYFace-190;
		//m_ptName[1].x=85;
		//m_ptName[1].y=nHeight/2+m_nYFace-257;		
		//m_ptTimer[1].x=28;
		//m_ptTimer[1].y=171;
		//m_ptReady[1].x=m_nXBorder+5+145+m_nXTimer;
		//m_ptReady[1].y=nHeight/2-m_nYFace-m_nYTimer/2-30;
	}

	//m_ptFace[0].x=nWidth/2-m_nXFace/2-70;
	//m_ptFace[0].y=m_nYBorder+40;
	//m_ptName[0].x=nWidth/2+5+m_nXFace/2-35;
	//m_ptName[0].y=m_nYBorder+37;
	//m_ptTimer[0].x=nWidth/2-m_nXFace/2-m_nXTimer*2-5;
	//m_ptTimer[0].y=m_nYBorder+140;
	//m_ptReady[0].x=nWidth/2-m_nXTimer-m_nXFace/2+38;
	//m_ptReady[0].y=m_nYBorder+m_nYTimer/2+150;
	m_ptFace[0].x=nWidth-m_nXBorder-m_nXFace-145;
	m_ptFace[0].y=nHeight/2-m_nYFace+30;
	m_ptName[0].x=nWidth-m_nXBorder-m_nXFace-74;
	m_ptName[0].y=nHeight/2-m_nYFace+27;
	//m_ptTimer[0].x=nWidth-183;
	//m_ptTimer[0].y=171;
	m_ptTimer[0].x=nWidth-m_nXBorder-m_nXTimer-200;
	m_ptTimer[0].y=nHeight/2-m_nYFace-m_nYTimer/2+60;
	m_ptReady[0].x=nWidth-m_nXBorder-m_nXTimer-200;
	m_ptReady[0].y=nHeight/2-m_nYFace-m_nYTimer/2+60;

	m_ptFace[2].x=9;
	m_ptFace[2].y=nHeight-92;
	m_ptName[2].x=85;
	m_ptName[2].y=nHeight-95;
	//m_ptTimer[2].x=nWidth/2-m_nXFace/2;
	//m_ptTimer[2].y=nHeight-m_nYBorder-m_nYTimer-5;
	m_ptTimer[2].x=nWidth/2-m_nXTimer-m_nXFace/2+30;
	m_ptTimer[2].y=nHeight-m_nYBorder-m_nYTimer/2-110;
	m_ptReady[2].x=nWidth/2-m_nXTimer-m_nXFace/2+30;
	m_ptReady[2].y=nHeight-m_nYBorder-m_nYTimer/2-110;

	POINT *pChatPt = GetChatPt();
	pChatPt[SCP_B].x =m_ptName[2].x-25;
	pChatPt[SCP_B].y =m_ptName[2].y-80;

	pChatPt[SCP_L].x =m_ptName[1].x-25;
	pChatPt[SCP_L].y =m_ptName[1].y+80;

	pChatPt[SCP_R].x =m_ptName[3].x-195;
	pChatPt[SCP_R].y =m_ptName[3].y+80;

	pChatPt[SCP_T].x =m_ptName[0].x-60;
	pChatPt[SCP_T].y =m_ptName[0].y+80;


	return;
}

//�滭����
void CGameClientView::DrawGameView(CDC * pDC, int nWidth, int nHeight)
{
	//�滭����
	DrawViewImage(pDC,m_ImageBack,enMode_Spread);

	//�滭����
	m_ChessBoard.DrawBoard(pDC) ;

	//�滭�߿�
	if(255!=m_bFrameX && 255!=m_bFrameY)
	{
		LONG lXPos = m_ChessBoard.GetChessXPos(m_bFrameX) , 
			 lYPos = m_ChessBoard.GetChessYPos(m_bFrameY) ;

		pDC->Draw3dRect(lXPos-2+3,lYPos-2+3,CHESS_WIDTH+4,CHESS_HEIGTH+4,RGB(225,0,0),RGB(100,0,0));
		pDC->Draw3dRect(lXPos-1+3,lYPos-1+3,CHESS_WIDTH+2,CHESS_HEIGTH+2,RGB(225,0,0),RGB(100,0,0));
		pDC->Draw3dRect(lXPos+2+3,lYPos+2+3,CHESS_WIDTH-4,CHESS_HEIGTH-4,RGB(255,0,0),RGB(200,0,0));
	}

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
			m_ImageHeadBg.AlphaDrawImage(pDC,m_ptFace[i].x-3,m_ptFace[i].y-15,RGB(255,0,255));
			
			//�û�����
			pDC->SetTextColor((wUserTimer>0)?RGB(250,250,250):RGB(220,220,220));
			pDC->SetTextAlign(((i==0)&&(m_bDeasilOrder==true))||((i==10)&&(m_bDeasilOrder==false))?TA_CENTER:TA_LEFT);
			//pDC->TextOut(m_ptName[i].x+77,m_ptName[i].y+1,pUserData->szName,lstrlen(pUserData->szName));
			
			LPCTSTR pszMember[]={TEXT("��ͨ��Ա"),TEXT("�м���Ա"),TEXT("�߼���Ա")};
			BYTE cbMember=pUserData->cbMember;
			_snprintf(szBuffer,CountArray(szBuffer),TEXT("%s(%s)"),pUserData->szName,pszMember[cbMember]);

			pDC->TextOut(m_ptName[i].x,m_ptName[i].y,szBuffer,lstrlen(szBuffer));

			//����
			pDC->SetTextColor((wUserTimer>0)?RGB(255,255,255):RGB(255,255,255));
			pDC->SetTextAlign(((i==0)&&(m_bDeasilOrder==true))||((i==10)&&(m_bDeasilOrder==false))?TA_CENTER:TA_LEFT);
			//pDC->TextOut(m_ptName[i].x+77,m_ptName[i].y+1,pUserData->szName,lstrlen(pUserData->szName));
			
			_snprintf(szBuffer,CountArray(szBuffer),TEXT("���ţ�%s"),pUserData->szGroupName);


			pDC->TextOut(m_ptName[i].x,m_ptName[i].y+40,szBuffer,lstrlen(szBuffer));
			


			//�û���ң�ͶӰЧ����
			pDC->SetTextColor((wUserTimer>0)?RGB(0,0,0):RGB(0,0,0));
			pDC->SetTextAlign(((i==0)&&(m_bDeasilOrder==true))||((i==10)&&(m_bDeasilOrder==false))?TA_RIGHT:TA_LEFT);
			CString s;
			s.Format("��Ϸ��:%d",pUserData->lScore);

			if(i!=2)
			{
				pDC->TextOut(m_ptName[i].x,m_ptName[i].y+20,s,lstrlen(s));
			}
			else
			{
				pDC->TextOut(m_ptName[i].x,m_ptName[i].y+20,s,lstrlen(s));
			}

			pDC->SetTextColor((wUserTimer>0)?RGB(250,250,250):RGB(255,255,0));
			pDC->SetTextAlign(((i==0)&&(m_bDeasilOrder==true))||((i==10)&&(m_bDeasilOrder==false))?TA_RIGHT:TA_LEFT);
	
			if(i!=2)
			{
				pDC->TextOut(m_ptName[i].x,m_ptName[i].y+21,s,lstrlen(s));
			}
			else
			{
				pDC->TextOut(m_ptName[i].x,m_ptName[i].y+21,s,lstrlen(s));
			}


			//�û����ǵȼ�
			if (pUserData->lExperience<=500L) 
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve1);
				if(i!=2)
				{
					m_ImageLeve1.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve1.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
			}
			if ((pUserData->lExperience>500L)&&(pUserData->lExperience<=1500L)) 
			{

				CImageHandle ImageHandleLevel(&m_ImageLeve2);
				if(i!=2)
				{
					m_ImageLeve2.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve2.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
			}
			if ((pUserData->lExperience>1500L)&&(pUserData->lExperience<=4000L)) 
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve3);
				if(i!=2)
				{
					m_ImageLeve3.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve3.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
			}
			if ((pUserData->lExperience>4000L)&&(pUserData->lExperience<=10000L))
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve4);
				if(i!=2)
				{
					m_ImageLeve4.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve4.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
			}
			if ((pUserData->lExperience>10000L)&&(pUserData->lExperience<=20000L)) 
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve5);
				if(i!=2)
				{
					m_ImageLeve5.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve5.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
			}
			if (pUserData->lExperience>20000L)
			{
				CImageHandle ImageHandleLevel(&m_ImageLeve6);
				if(i!=2)
				{
					m_ImageLeve6.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
				else
				{
					m_ImageLeve6.AlphaDrawImage(pDC,m_ptName[i].x,m_ptName[i].y+67,RGB(255,0,255));
				}
			}


			//������Ϣ
			if (wUserTimer!=0) DrawUserTimer(pDC,m_ptTimer[i].x,m_ptTimer[i].y,wUserTimer);
			if (pUserData->cbUserStatus==US_READY) DrawUserReady(pDC,m_ptReady[i].x,m_ptReady[i].y);
			//DrawUserFace(pDC,pUserData->wFaceID,m_ptFace[i].x,m_ptFace[i].y,pUserData->cbUserStatus==US_OFFLINE);
			DrawUserBigFace(pDC,pUserData->wFaceID,m_ptFace[i].x+7,m_ptFace[i].y-4,pUserData->cbUserStatus==US_OFFLINE);
		}
	}
	if(m_lCurrentStepCount>0)
	{
		CFont font;
		VERIFY(font.CreateFont(
			20,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial"));                 // lpszFacename
		COLORREF defColor = pDC->SetTextColor(RGB(255,255,255)) ;

		CFont* def_font = pDC->SelectObject(&font);
		CString strMsg ;
		strMsg.Format("��ǰ����Ϊ: %ld" , m_lCurrentStepCount) ;
		pDC->TextOut(m_nXBorder+5 , m_nYBorder+5, strMsg, strMsg.GetLength());
		pDC->SelectObject(def_font);
		pDC->SetTextColor(defColor) ;

		font.DeleteObject();
	}

	return;
}

//��������
void CGameClientView::ShowPeaceRequest()
{
	if (m_PeaceRequest.m_hWnd==NULL) 
	{
		m_PeaceRequest.Create(IDD_USER_REQ,this);
		m_PeaceRequest.ShowWindow(SW_SHOW);
	}

	return;
}



//////////////////////////////////////////////////////////////////////////

void CGameClientView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CGameFrameView::OnLButtonUp(nFlags, point);

	BYTE bXPos, bYPos ;

	m_ChessBoard.SwitchMousePos(point , bXPos , bYPos) ;

	CString str ;
	str.Format("(%d,%d)" , bXPos , bYPos) ;

//	AfxMessageBox(str) ;

	//�������
	if(255!=bXPos && 255!=bYPos)
		GetParent()->SendMessage(WM_HIT_CHESS_BORAD , bXPos , bYPos) ;

}

//��������
void CGameClientView::DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos)
{
	//��������
	int nStringLength=lstrlen(pszString);
	int nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	int nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	//�滭�߿�
	pDC->SetTextColor(crFrame);
	for (int i=0;i<CountArray(nXExcursion);i++)
	{
		pDC->TextOut(nXPos+nXExcursion[i],nYPos+nYExcursion[i],pszString,nStringLength);
	}

	//�滭����
	pDC->SetTextColor(crText);
	pDC->TextOut(nXPos,nYPos,pszString,nStringLength);

	return;
}

void CGameClientView::OnHitPlacement()
{
	GetParent()->SendMessage(IDM_PLACEMENT , 0 , 0) ;
}

void CGameClientView::OnMouseMove(UINT nFlags, CPoint point)
{
	BYTE bXPos, bYPos ;

	m_ChessBoard.SwitchMousePos(point , bXPos , bYPos) ;

	//�������
	if(255!=bXPos && 255!=bYPos)
		GetParent()->SendMessage(WM_CHANGE_CURSOR , bXPos , bYPos) ;


	CGameFrameView::OnMouseMove(nFlags, point);
}

//�滭�߿�
void CGameClientView::DrawChessFrame(BYTE bXPos , BYTE bYPos)
{
	m_bFrameX = bXPos ;
	m_bFrameY = bYPos ;

	UpdateGameView(NULL) ;
}

//�õ��߿�
void CGameClientView::GetChessFrame(BYTE &bXPos , BYTE &bYPos)
{
	bXPos = m_bFrameX ;
	bYPos = m_bFrameY ;
}
//������Ϸ
void CGameClientView::OnHitResetGame() 
{
	GetParent()->SendMessage(WM_RESET_GAME , 0 , 0) ;
}

//���沼��
void CGameClientView::OnSavePlacement()
{
	GetParent()->SendMessage(WM_SAVE_PLACEMENT , 0 , 0) ;
}

//װ�ز���
void CGameClientView::OnHitLoadPlacement() 
{
    GetParent()->SendMessage(WM_LOAD_PLACEMENT , 0 , 0) ;
}

//�������
void CGameClientView::OnHitLoadHistory()
{
	GetParent()->SendMessage(IDM_LOAD_HISTORY,0,0);
}

//��һ����			
void CGameClientView::OnHitPrevStep()
{
	GetParent()->SendMessage(IDM_PREV_STEP,0,0);
}

//��һ����				
void CGameClientView::OnHitNextStep()
{
	GetParent()->SendMessage(IDM_NEXT_STEP,0,0);
}

//��ת����				
void CGameClientView::OnHitTurn()
{
	GetParent()->SendMessage(IDM_TURN_CHESS,0,0);
}

//����˳��
void CGameClientView::SetUserOrder(bool bDeasilOrder)
{
	m_bDeasilOrder = bDeasilOrder ;


	//���ý���
	CRect rcClient;
	GetClientRect(&rcClient);

	RectifyGameView(rcClient.Width(),rcClient.Height());
	//���½���
	UpdateGameView(NULL) ;
}

//����˳��
bool CGameClientView::IsDeasilOrder(bool bDeasilOrder)
{
	return bDeasilOrder ;
}

//���䰴ť
void CGameClientView::OnHitLose()
{
	if(MessageBox("���Ƿ�ȷ��Ҫ���䣿","��ʾ",MB_YESNO)==IDYES)
	{
		GetParent()->SendMessage(IDM_LOSE,0,0);
	}
}

//������ť
void CGameClientView::OnHitGiveUp()
{
	if(MessageBox("���Ƿ�ȷ��Ҫ����һ�֣�","��ʾ",MB_YESNO)==IDYES)
	{
		GetParent()->SendMessage(IDM_GIVEUP,0,0);
	}
}

//�������
void CGameClientView::OnHitPeace()
{
	if(MessageBox("���Ƿ�ȷ��Ҫ���壿","��ʾ",MB_YESNO)==IDYES)
	{
		GetParent()->SendMessage(IDM_PEACE,0,0);
	}
}

void CGameClientView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CGameFrameView::OnRButtonDown(nFlags, point);
	BYTE bXPos, bYPos ;

	m_ChessBoard.SwitchMousePos(point , bXPos , bYPos) ;

	CGameClientDlg *pParent = (CGameClientDlg *)GetParent() ;
	//�Ƿ��ж�
	if(CHESS_NULL == pParent->m_Chess[bXPos][bYPos].bChessID || CHESS_BACK!=pParent->m_Chess[bXPos][bYPos].bChessMode || CHESS_COLOR_NO==pParent->m_Chess[bXPos][bYPos].bColor)
        return ;

	//�������
	if(255!=bXPos && 255!=bYPos)
	{
		//��־ͼ��
		m_ChessBoard.ShowFlagImage(point , true) ;
		m_ChessBoard.SetFlaChessPos(bXPos , bYPos) ;
	}

}

void CGameClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//if (GetSystemMetrics(SM_CXSCREEN)>800)
	//::SendMessage(GetParent()->GetSafeHwnd(),WM_NCLBUTTONDOWN, HTCAPTION,0);
	//CGameFrameView::OnLButtonDown(nFlags, point);
	if(point.y<48 && GetSystemMetrics(SM_CXSCREEN)>800)
	{
		::SendMessage(GetParent()->GetSafeHwnd(),WM_NCLBUTTONDOWN, HTCAPTION,0);
	}
	CGameFrameView::OnLButtonDown(nFlags, point);
}

//���ò��� 	
void CGameClientView::SetStepCount(LONG lStepCount)
{
	m_lCurrentStepCount = lStepCount ;
	//���½���
	UpdateGameView(NULL) ;
}