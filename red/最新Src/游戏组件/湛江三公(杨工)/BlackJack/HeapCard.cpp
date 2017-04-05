#include "StdAfx.h"
#include "Resource.h"
#include ".\heapcard.h"

//���캯��
CHeapCard::CHeapCard()
{
	//���Ʊ���
	m_ControlPoint.SetPoint(0,0);
	

	//�˿˱���
	m_wFullCount=0;
	m_wMinusHeadCount=0;
	m_wMinusLastCount=0;
	for(BYTE i=0;i<10;i++)m_wMinusMiddlePos[i]=0x00;

	m_ImageBack.LoadFromResource(AfxGetInstanceHandle(),IDB_CARDHEAP);

	return;
}

//��������
CHeapCard::~CHeapCard()
{
	m_ImageBack.Destroy();
}

//�滭�˿�
void CHeapCard::DrawCardControl(CDC * pDC)
{
	//�滭�˿�
	if ((m_wFullCount-m_wMinusHeadCount-m_wMinusLastCount)>0)
	{		
		//��������
		int nXPos=0,nYPos=0;		
		
		bool  bMinusMiddlePos[10];
		for(BYTE i=0;i<10;i++)bMinusMiddlePos[i]=false;
		for(BYTE i=0;i<10;i++)
		{
			if(m_wMinusMiddlePos[i]==0x00)continue;
			if(m_wFullCount+1<m_wMinusMiddlePos[i])continue;
			bMinusMiddlePos[m_wFullCount-m_wMinusMiddlePos[i]+1]=true;
		}	

		//�м��˿�
		for (WORD i=m_wMinusHeadCount;i<m_wFullCount;i++)
		{
			nYPos=m_ControlPoint.y;
			nXPos=m_ControlPoint.x+i*20;
			if(bMinusMiddlePos[i]==false)					
				m_ImageBack.AlphaDrawImage(pDC,nXPos,nYPos+10,RGB(255,0,255));		
				
		}

	}
	return;
}

//�����˿�
bool CHeapCard::SetCardData(WORD wMinusHeadCount, WORD wMinusLastCount, WORD wFullCount,WORD wAddMinusMiddleCount)
{
	//���ñ���
	m_wFullCount=wFullCount;
	m_wMinusHeadCount=wMinusHeadCount;
	m_wMinusLastCount=wMinusLastCount;	

	if(wAddMinusMiddleCount)
	{
		for(BYTE i=0;i<10;i++)
		{
			if(m_wMinusMiddlePos[i]==0x00)
			{
				m_wMinusMiddlePos[i]=wAddMinusMiddleCount;
				break;
			}
		}
		
	}

	return true;
}

// ���ñ���
void CHeapCard::ResetMinusMiddleCount()
{
	for(BYTE i=0;i<10;i++)m_wMinusMiddlePos[i]=0x00;

}
