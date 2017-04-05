#include "StdAfx.h"
#include "Resource.h"
#include "ScoreCard.h"

//////////////////////////////////////////////////////////////////////////
//��̬����

bool					CScoreCard::m_bLoad=false;					//���ر�־
CSize					CScoreCard::m_CardSize;						//�˿˴�С
CSkinImage		CScoreCard::m_ImageCard;						//ͼƬ��Դ

bool					CUserScoreCard::m_bLoad=false;				//���ر�־
CSize					CUserScoreCard::m_CardSize;					//�˿˴�С
CSkinImage		CUserScoreCard::m_ImageCard;					//ͼƬ��Դ

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CScoreCard, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CUserScoreCard, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CScoreCard::CScoreCard()
{
	//���ñ���
	m_bDisplay=false;
	m_bHorizontal=true;
	m_bPositively=false;

	//�������
	m_dwCardHSpace=DEF_CARD_H_SPACE_SCORE;
	m_dwCardVSpace=DEF_CARD_V_SPACE_SCORE;
	m_dwShootAltitude=DEF_CARD_SHOOT_SCORE;

	//λ�ñ���
	m_XCollocateMode=enScoreXCenter;
	m_YCollocateMode=enScoreYCenter;
	m_BenchmarkPos.SetPoint(0,0);

	//���б���
	m_dwCurrentIndex=0xFFFFFFFF;

	//�ڲ�����
	m_pSinkWindow=NULL;

	//��Դ����
	if (m_bLoad==false)
	{
		//������Դ
		m_bLoad=true;
		m_ImageCard.SetLoadInfo(IDB_CARD_800,AfxGetInstanceHandle());

		//��ȡ��С
		CImageHandle CardImageHandle(&m_ImageCard);
		m_CardSize.cx=m_ImageCard.GetWidth()/13;
		m_CardSize.cy=m_ImageCard.GetHeight()/5;
	}

	return;
}

//��������
CScoreCard::~CScoreCard()
{
}

//���ô���
void CScoreCard::SetSinkWindow(CWnd * pSinkWindow)
{
	//���ñ���
	m_pSinkWindow=pSinkWindow;

	return;
}

//���÷���
void CScoreCard::SetDirection(bool bHorizontal)
{
	//״̬�ж�
	if (m_bHorizontal==bHorizontal) return;

	//���ñ���
	m_bHorizontal=bHorizontal;

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return;
}

//�����˿�
void CScoreCard::ShootAllCard(bool bShoot)
{
	//��������
	bool bRectify=false;
	tagScoreCardItem * pCardItem=NULL;
	DWORD dwCardCount=(DWORD)m_CardDataItem.GetCount();

	//�����˿�
	for (DWORD i=0;i<dwCardCount;i++)
	{
		//��ȡ�˿�
		pCardItem=&m_CardDataItem[i];

		//�˿˷���
		if (pCardItem->bShoot!=bShoot)
		{
			bRectify=true;
			pCardItem->bShoot=bShoot;
		}
	}

	//�����ؼ�
	if (bRectify==true) RectifyControl();

	return;
}

//������ʾ
void CScoreCard::SetDisplayFlag(bool bDisplay)
{
	//״̬�ж�
	if (m_bDisplay==bDisplay) return;

	//���ñ���
	m_bDisplay=bDisplay;

	//�ػ��ؼ�
	if (m_hWnd!=NULL) Invalidate(FALSE);

	return;
}

//������Ӧ
void CScoreCard::SetPositively(bool bPositively)
{
	//���ñ���
	m_bPositively=bPositively;

	return;
}

//���ü��
void CScoreCard::SetCardSpace(DWORD dwCardHSpace, DWORD dwCardVSpace, DWORD dwShootAltitude)
{
	//���ñ���
	m_dwCardHSpace=dwCardHSpace;
	m_dwCardVSpace=dwCardVSpace;
	m_dwShootAltitude=dwShootAltitude;

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return;
}

//��׼λ��
void CScoreCard::SetBenchmarkPos(int nXPos, int nYPos, enScoreXCollocateMode XCollocateMode, enScoreYCollocateMode YCollocateMode)
{
	//���ñ���
	m_BenchmarkPos.x=nXPos;
	m_BenchmarkPos.y=nYPos;
	m_XCollocateMode=XCollocateMode;
	m_YCollocateMode=YCollocateMode;

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return;
}

//��׼λ��
void CScoreCard::SetBenchmarkPos(const CPoint & BenchmarkPos, enScoreXCollocateMode XCollocateMode, enScoreYCollocateMode YCollocateMode)
{
	//���ñ���
	m_BenchmarkPos=BenchmarkPos;
	m_XCollocateMode=XCollocateMode;
	m_YCollocateMode=YCollocateMode;

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return;
}

//��ȡ��Ŀ
DWORD CScoreCard::GetCardCount()
{
	return (DWORD)m_CardDataItem.GetCount();
}

//��ȡ�˿�
DWORD CScoreCard::GetShootCard(BYTE cbCardData[], DWORD dwMaxCount)
{
	//��������
	DWORD bShootCount=0L;
	DWORD dwCardCount=(DWORD)m_CardDataItem.GetCount();

	//�����˿�
	tagScoreCardItem * pCardItem=NULL;
	for (DWORD i=0;i<dwCardCount;i++)
	{
		//��ȡ�˿�
		pCardItem=&m_CardDataItem[i];

		//�˿˷���
		if (pCardItem->bShoot==true) cbCardData[bShootCount++]=pCardItem->cbCardData;
	}

	return bShootCount;
}

//�����˿�
DWORD CScoreCard::SetShootCard(BYTE cbCardData[], DWORD dwCardCount)
{
	//��������
	bool bChangeStatus=false;

	//�����˿�
	for (INT_PTR i=0;i<m_CardDataItem.GetCount();i++) 
	{
		if (m_CardDataItem[i].bShoot==true)
		{
			bChangeStatus=true;
			m_CardDataItem[i].bShoot=false;
		}
	}

	//�����˿�
	for (DWORD i=0;i<dwCardCount;i++)
	{
		for (INT_PTR j=0;j<m_CardDataItem.GetCount();j++)
		{
			tagScoreCardItem * pCardItem=&m_CardDataItem[j];
			if ((pCardItem->bShoot==false)&&(pCardItem->cbCardData==cbCardData[i])) 
			{
				bChangeStatus=true;
				pCardItem->bShoot=true;
				break;
			}
		}
	}

	//���ý���
	if (m_hWnd!=NULL) RectifyControl();

	return dwCardCount;
}

//�����˿�
DWORD CScoreCard::SetCardData(const BYTE cbCardData[], DWORD dwCardCount)
{
	//�����˿�
	m_CardDataItem.SetSize(dwCardCount);
	for (DWORD i=0;i<dwCardCount;i++)
	{
		m_CardDataItem[i].bShoot=false;
		m_CardDataItem[i].cbCardData=cbCardData[i];
	}

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return dwCardCount;
}

//��ȡ�˿�
DWORD CScoreCard::GetCardData(tagScoreCardItem CardItemArray[], DWORD dwMaxCount)
{
	//Ч�����
	ASSERT(dwMaxCount>=(DWORD)m_CardDataItem.GetCount());

	//�����˿�
	DWORD dwCardCount=(DWORD)m_CardDataItem.GetCount();
	tagScoreCardItem * pCardItemData=m_CardDataItem.GetData();
	CopyMemory(CardItemArray,pCardItemData,dwCardCount*sizeof(tagScoreCardItem));

	return dwCardCount;
}

//�����˿�
DWORD CScoreCard::SetCardItem(const tagScoreCardItem CardItemArray[], DWORD dwCardCount)
{
	//�����˿�
	m_CardDataItem.SetSize(dwCardCount);
	CopyMemory(m_CardDataItem.GetData(),CardItemArray,dwCardCount*sizeof(tagScoreCardItem));

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();
 
	return 0;
}

//����λ��
void CScoreCard::RectifyControl()
{
	//��������
	DWORD dwCardCount=(DWORD)m_CardDataItem.GetCount();

	//�����С
	CSize ControlSize;
	if (m_bHorizontal==true)
	{
		ControlSize.cy=m_CardSize.cy+m_dwShootAltitude;
		ControlSize.cx=(dwCardCount>0)?(m_CardSize.cx+(dwCardCount-1)*m_dwCardHSpace):0;
	}
	else
	{
		ControlSize.cx=m_CardSize.cx;
		ControlSize.cy=(dwCardCount>0)?(m_CardSize.cy+(dwCardCount-1)*m_dwCardVSpace):0;
	}

	//����λ��
	int nXPos=0;
	switch (m_XCollocateMode)
	{
	case enScoreXLeft:	{ nXPos=m_BenchmarkPos.x; break; }
	case enScoreXCenter: { nXPos=m_BenchmarkPos.x-ControlSize.cx/2; break; }
	case enScoreXRight:	{ nXPos=m_BenchmarkPos.x-ControlSize.cx; break; }
	}

	//����λ��
	int nYPos=0;
	switch (m_YCollocateMode)
	{
	case enScoreYTop:	{ nYPos=m_BenchmarkPos.y; break; }
	case enScoreYCenter: { nYPos=m_BenchmarkPos.y-ControlSize.cy/2; break; }
	case enScoreYBottom: { nYPos=m_BenchmarkPos.y-ControlSize.cy; break; }
	}

	//�ƶ�λ��
	SetWindowPos(NULL,nXPos,nYPos,ControlSize.cx,ControlSize.cy,SWP_NOZORDER);

	//��������
	CRgn CardRegion,SignedRegion;
	tagScoreCardItem * pCardItem=NULL;

	//��������
	CardRegion.CreateRectRgn(0,0,0,0);
	for (DWORD i=0;i<dwCardCount;i++)
	{
		//��ȡ�˿�
		pCardItem=&m_CardDataItem[i];

		//���ù���
		if (pCardItem->cbCardData==255) continue;

		//����λ��
		if (m_bHorizontal==true)
		{
			nXPos=m_dwCardHSpace*i;
			nYPos=(pCardItem->bShoot==false)?m_dwShootAltitude:0;
		}
		else 
		{
			nXPos=0;
			nYPos=m_dwCardVSpace*i;
		}

		//�ϲ�����
		SignedRegion.CreateRoundRectRgn(nXPos,nYPos,nXPos+m_CardSize.cx+1,nYPos+m_CardSize.cy+1,2,2);
		CardRegion.CombineRgn(&CardRegion,&SignedRegion,RGN_OR);
		SignedRegion.DeleteObject();
	}

	//��������
	SetWindowRgn(CardRegion,TRUE);
	m_CardRegion.DeleteObject();
	m_CardRegion.Attach(CardRegion.Detach());

	//�ػ�����
	Invalidate(FALSE);

	return;
}

//�����л�
DWORD CScoreCard::SwitchCardPoint(const CPoint & MousePoint)
{
	if (m_bHorizontal==true)
	{
		//��������
		DWORD dwCardCount=(DWORD)m_CardDataItem.GetCount();

		//��ȡ����
		DWORD dwCardIndex=MousePoint.x/m_dwCardHSpace;
		if (dwCardIndex>=dwCardCount) dwCardIndex=(dwCardCount-1);

		//�жϰ���
		bool bCurrentCard=true;
		if (m_CardDataItem[dwCardIndex].cbCardData!=255)
		{
			bool bCardShoot=m_CardDataItem[dwCardIndex].bShoot;
			if ((bCardShoot==true)&&(MousePoint.y>m_CardSize.cy)) bCurrentCard=false;
			if ((bCardShoot==false)&&(MousePoint.y<(INT)m_dwShootAltitude)) bCurrentCard=false;
		}
		else bCurrentCard=false;

		//��ǰѰ��
		if (bCurrentCard==false)
		{
			while (dwCardIndex>0)
			{
				//��������
				dwCardIndex--;

				//�жϹ���
				if (m_CardDataItem[dwCardIndex].cbCardData==255) continue;

				//�жϰ���
				bool bCardShoot=m_CardDataItem[dwCardIndex].bShoot;
				if ((bCardShoot==true)&&(MousePoint.y<(INT)m_CardSize.cy)) break;
				if ((bCardShoot==false)&&(MousePoint.y>(INT)m_dwShootAltitude)) break;
			}
		}

		return dwCardIndex;
	}

	return DWORD(-1);
}

//�ػ�����
void CScoreCard::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//����λͼ
	CImageHandle HandleCard(&m_ImageCard);

	//����λͼ
	CBitmap BufferImage;
	BufferImage.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());

	//���� DC
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(&dc);
	BufferDC.SelectObject(&BufferImage);

	//�滭�˿�
	DWORD dwXImagePos,dwYImagePos;
	DWORD dwXScreenPos,dwYScreenPos;
	for (INT i=0;i<m_CardDataItem.GetCount();i++)
	{
		//��ȡ�˿�
		tagScoreCardItem * pCardItem=&m_CardDataItem[i];

		//��϶����
		if (pCardItem->cbCardData==255) continue;

		//ͼƬλ��
		if ((m_bDisplay==true)&&(pCardItem->cbCardData!=0))
		{
			if ((pCardItem->cbCardData==0x4E)||(pCardItem->cbCardData==0x4F))
			{
				dwYImagePos=((pCardItem->cbCardData&CARD_MASK_COLOR)>>4)*m_CardSize.cy;
				dwXImagePos=((pCardItem->cbCardData&CARD_MASK_VALUE)%14)*m_CardSize.cx;
			}
			else
			{
				dwXImagePos=((pCardItem->cbCardData&CARD_MASK_VALUE)-1)*m_CardSize.cx;
				dwYImagePos=((pCardItem->cbCardData&CARD_MASK_COLOR)>>4)*m_CardSize.cy;
			}
		}
		else
		{
			dwXImagePos=m_CardSize.cx*2;
			dwYImagePos=m_CardSize.cy*4;
		}

		//��Ļλ��
		if (m_bHorizontal==true) 
		{
			dwXScreenPos=m_dwCardHSpace*i;
			dwYScreenPos=(pCardItem->bShoot==false)?m_dwShootAltitude:0;
		}
		else
		{
			dwXScreenPos=0;
			dwYScreenPos=m_dwCardVSpace*i;
		}

		//�滭�˿�
		m_ImageCard.AlphaDrawImage(&BufferDC,dwXScreenPos,dwYScreenPos,m_CardSize.cx,m_CardSize.cy,dwXImagePos,dwYImagePos,RGB(255,0,255));
	}

	//�滭����
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//������Դ
	BufferDC.DeleteDC();
	BufferImage.DeleteObject();

	return;
}

//������Ϣ
int CScoreCard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ñ���
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	return 0;
}

//�����Ϣ
void CScoreCard::OnRButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnRButtonUp(nFlags, Point);

	//״̬�ж�
	if ((m_bHorizontal==false)||(m_bPositively==false)) return;

	//������Ϣ
	if (m_pSinkWindow!=NULL) m_pSinkWindow->PostMessage(IDM_RIGHT_HIT_CARD,0,0);

	return;
}

//�����Ϣ
void CScoreCard::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags, Point);

	//״̬�ж�
	if (m_dwCurrentIndex==0xFFFFFFFF) return;
	if ((m_bHorizontal==false)||(m_bPositively==false)) return;

	//��ȡ����
	DWORD dwCurrentIndex=SwitchCardPoint(Point);
	if (dwCurrentIndex!=m_dwCurrentIndex) return;

	//���ÿؼ�
	tagScoreCardItem * pCardItem=&m_CardDataItem[dwCurrentIndex];
	if (pCardItem->cbCardData!=255) pCardItem->bShoot=!pCardItem->bShoot;

	//������Ϣ
	if (m_pSinkWindow!=NULL) m_pSinkWindow->PostMessage(IDM_LEFT_HIT_CARD,0,0);

	//�����ؼ�
	RectifyControl();

	return;
}

//�����Ϣ
void CScoreCard::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags, Point);

	//״̬�ж�
	if ((m_bHorizontal==false)||(m_bPositively==false)) return;

	//��ȡ����
	m_dwCurrentIndex=SwitchCardPoint(Point);

	return;
}

//�����Ϣ
BOOL CScoreCard::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message)
{
	//���ù��
	if (m_bPositively==true)
	{
		SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_CARD_CUR)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,message);
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CUserScoreCard::CUserScoreCard()
{
	//���ñ���
	m_bDisplay=false;
	m_bHorizontal=true;

	//�������
	m_dwCardHSpace=DEF_CARD_H_SPACE_SCORE;
	m_dwCardVSpace=DEF_CARD_V_SPACE_SCORE;

	//λ�ñ���
	m_XCollocateMode=enScoreXCenter;
	m_YCollocateMode=enScoreYCenter;
	m_BenchmarkPos.SetPoint(0,0);

	//��Դ����
	if (m_bLoad==false)
	{
		//������Դ
		m_bLoad=true;
		m_ImageCard.SetLoadInfo(IDB_SMALL_CARD,AfxGetInstanceHandle());

		//��ȡ��С
		CImageHandle CardImageHandle(&m_ImageCard);
		m_CardSize.cx=m_ImageCard.GetWidth()/13;
		m_CardSize.cy=m_ImageCard.GetHeight()/5;
	}

	return;
}

//��������
CUserScoreCard::~CUserScoreCard()
{
}

//���÷���
void CUserScoreCard::SetDirection(bool bHorizontal)
{
	//״̬�ж�
	if (m_bHorizontal==bHorizontal) return;

	//���ñ���
	m_bHorizontal=bHorizontal;

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return;
}

//������ʾ
void CUserScoreCard::SetDisplayFlag(bool bDisplay)
{
	//״̬�ж�
	if (m_bDisplay==bDisplay) return;

	//���ñ���
	m_bDisplay=bDisplay;

	//�ػ��ؼ�
	if (m_hWnd!=NULL) Invalidate(FALSE);

	return;
}

//���ü��
void CUserScoreCard::SetCardSpace(DWORD dwCardHSpace, DWORD dwCardVSpace)
{
	//���ñ���
	m_dwCardHSpace=dwCardHSpace;
	m_dwCardVSpace=dwCardVSpace;

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return;
}

//��׼λ��
void CUserScoreCard::SetBenchmarkPos(int nXPos, int nYPos, enScoreXCollocateMode XCollocateMode, enScoreYCollocateMode YCollocateMode)
{
	//���ñ���
	m_BenchmarkPos.x=nXPos;
	m_BenchmarkPos.y=nYPos;
	m_XCollocateMode=XCollocateMode;
	m_YCollocateMode=YCollocateMode;

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return;
}

//��׼λ��
void CUserScoreCard::SetBenchmarkPos(const CPoint & BenchmarkPos, enScoreXCollocateMode XCollocateMode, enScoreYCollocateMode YCollocateMode)
{
	//���ñ���
	m_BenchmarkPos=BenchmarkPos;
	m_XCollocateMode=XCollocateMode;
	m_YCollocateMode=YCollocateMode;

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return;
}

//��ȡ��Ŀ
DWORD CUserScoreCard::GetCardCount()
{
	return (DWORD)m_CardDataItem.GetCount();
}

//�����˿�
DWORD CUserScoreCard::SetCardData(const BYTE cbCardData[], DWORD dwCardCount)
{
	//�����˿�
	m_CardDataItem.SetSize(dwCardCount);
	for (DWORD i=0;i<dwCardCount;i++) m_CardDataItem[i]=cbCardData[i];

	//�����ؼ�
	if (m_hWnd!=NULL) RectifyControl();

	return dwCardCount;
}

//����λ��
void CUserScoreCard::RectifyControl()
{
	//��������
	DWORD dwCardCount=(DWORD)m_CardDataItem.GetCount();

	//�����С
	CSize ControlSize;
	if (m_bHorizontal==true)
	{
		ControlSize.cy=m_CardSize.cy;
		ControlSize.cx=(dwCardCount>0)?(m_CardSize.cx+(dwCardCount-1)*m_dwCardHSpace):0;
	}
	else
	{
		ControlSize.cx=m_CardSize.cx;
		ControlSize.cy=(dwCardCount>0)?(m_CardSize.cy+(dwCardCount-1)*m_dwCardVSpace):0;
	}

	//����λ��
	int nXPos=0;
	switch (m_XCollocateMode)
	{
	case enScoreXLeft:	{ nXPos=m_BenchmarkPos.x; break; }
	case enScoreXCenter: { nXPos=m_BenchmarkPos.x-ControlSize.cx/2; break; }
	case enScoreXRight:	{ nXPos=m_BenchmarkPos.x-ControlSize.cx; break; }
	}

	//����λ��
	int nYPos=0;
	switch (m_YCollocateMode)
	{
	case enScoreYTop:	{ nYPos=m_BenchmarkPos.y; break; }
	case enScoreYCenter: { nYPos=m_BenchmarkPos.y-ControlSize.cy/2; break; }
	case enScoreYBottom: { nYPos=m_BenchmarkPos.y-ControlSize.cy; break; }
	}

	//�ƶ�λ��
	SetWindowPos(NULL,nXPos,nYPos,ControlSize.cx,ControlSize.cy,SWP_NOZORDER);

	//��������
	CRgn CardRegion,SignedRegion;
	tagScoreCardItem * pCardItem=NULL;

	//��������
	CardRegion.CreateRectRgn(0,0,0,0);
	for (DWORD i=0;i<dwCardCount;i++)
	{
		//��ȡ�˿�
		BYTE cbCardData=m_CardDataItem[i];

		//����λ��
		if (m_bHorizontal==true)
		{
			nYPos=0;
			nXPos=m_dwCardHSpace*i;
		}
		else 
		{
			nXPos=0;
			nYPos=m_dwCardVSpace*i;
		}

		//�ϲ�����
		SignedRegion.CreateRoundRectRgn(nXPos,nYPos,nXPos+m_CardSize.cx+1,nYPos+m_CardSize.cy+1,2,2);
		CardRegion.CombineRgn(&CardRegion,&SignedRegion,RGN_OR);
		SignedRegion.DeleteObject();
	}

	//��������
	SetWindowRgn(CardRegion,TRUE);
	m_CardRegion.DeleteObject();
	m_CardRegion.Attach(CardRegion.Detach());

	//�ػ�����
	Invalidate(TRUE);

	return;
}

//�ػ�����
void CUserScoreCard::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//����λͼ
	CImageHandle HandleCard(&m_ImageCard);

	//����λͼ
	CBitmap BufferImage;
	BufferImage.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());

	//���� DC
	CDC BufferDC;
	BufferDC.CreateCompatibleDC(&dc);
	BufferDC.SelectObject(&BufferImage);

	//�滭�˿�
	DWORD dwXImagePos,dwYImagePos;
	DWORD dwXScreenPos,dwYScreenPos;
	for (INT i=0;i<m_CardDataItem.GetCount();i++)
	{
		//��ȡ�˿�
		BYTE cbCardData=m_CardDataItem[i];

		//ͼƬλ��
		if ((m_bDisplay==true)&&(cbCardData!=0))
		{
			dwXImagePos=((cbCardData&CARD_MASK_VALUE)-1)*m_CardSize.cx;
			dwYImagePos=((cbCardData&CARD_MASK_COLOR)>>4)*m_CardSize.cy;
		}
		else
		{
			dwXImagePos=m_CardSize.cx*2;
			dwYImagePos=m_CardSize.cy*4;
		}

		//��Ļλ��
		if (m_bHorizontal==true) 
		{
			dwYScreenPos=0;
			dwXScreenPos=m_dwCardHSpace*i;
		}
		else
		{
			dwXScreenPos=0;
			dwYScreenPos=m_dwCardVSpace*i;
		}

		//�滭�˿�
		m_ImageCard.AlphaDrawImage(&BufferDC,dwXScreenPos,dwYScreenPos,m_CardSize.cx,m_CardSize.cy,dwXImagePos,dwYImagePos,RGB(255,0,255));
	}

	//�滭����
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//������Դ
	BufferDC.DeleteDC();
	BufferImage.DeleteObject();

	return;
}

//������Ϣ
int CUserScoreCard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ñ���
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	return 0;
}

//////////////////////////////////////////////////////////////////////////

