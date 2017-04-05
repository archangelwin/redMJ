#include "StdAfx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
const BYTE	CGameLogic::m_bCardArray[52] =									//�˿�����
{
	// 1, 2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
	//14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
	//27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	//40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
	//1,2,3,4,5,6,7,8,9,10,
	//1,2,3,4,5,6,7,8,9,10,
	//1,2,3,4,5,6,7,8,9,10,
	//1,2,3,4,5,6,7,8,9,10,
	 1, 2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
	14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
};

//��ȡ�˿���ֵ
BYTE CGameLogic::GetCardValue(BYTE bCard)
{
	//BYTE bValue = bCard%13;
	//if (bValue == 0 || bValue == 11 || bValue == 12) bValue=10;
	//if (bValue == 1) bValue = 11;
	//return bValue;
	BYTE bValue = bCard%13;
	if (bValue == 10 || bValue == 11 || bValue == 12 || bValue == 13) bValue=0;
	return bValue;
}

//��ȡ�˿���ֵ
BYTE CGameLogic::GetCardSum(const BYTE bCardBuffer[], const BYTE bCardCount)
{
	BYTE cbCardSum = 0;
	
	for(int i = 0; i < bCardCount; i++)
	{
		cbCardSum += GetCardValue(bCardBuffer[i]);
	}
	
	if(cbCardSum > 21)
	{
		for(int i = 0; i < bCardCount; i++)
		{
			//�Ƿ���A
			if(GetCardValue(bCardBuffer[i]) == 11)
			{
				//��1����
				cbCardSum -= 10;
			}
		}
	}

	return cbCardSum;
}

//�Ƿ���
bool CGameLogic::IsBurst(const BYTE bCardBuffer[], BYTE bCardCount)
{
	WORD wCardSum = 0;
	
	for(int i = 0; i < bCardCount; i++)
	{
		wCardSum += GetCardValue(bCardBuffer[i]);
	}

	if(wCardSum > 21)
	{
		for(int i = 0; i < bCardCount; i++)
		{
			//�Ƿ���A
			if(GetCardValue(bCardBuffer[i]) == 11)
			{
				//��1����
				wCardSum -= 10;
			}
		}
	}

	if(wCardSum > 21) return true;
	
	return false;
}

//�ܷ����
bool CGameLogic::CanCutCard(const BYTE bFirstCard, const BYTE bLastCard)
{
	BYTE bFirstValue = bFirstCard % 13;
	BYTE bLastValue  = bLastCard  % 13;
	if (bFirstValue == bLastValue) return true;
	return false;
}

//�Ƿ�BlackJack
bool CGameLogic::IsBlackJack(const BYTE bCardBuffer[])
{
	BYTE bCardSum=0;
	if((GetCardValue(bCardBuffer[0]) == 1) && (GetCardValue(bCardBuffer[1]) == 10)) return true;
	if((GetCardValue(bCardBuffer[1]) == 1) && (GetCardValue(bCardBuffer[0]) == 10)) return true;
	return false;
}

//�Աȵ�ֻ�˿�
bool CGameLogic::CompareOnlyOne(BYTE bFirstCard, BYTE bLastCard)
{
	BYTE bFirstValue = GetCardValue(bFirstCard);
	BYTE bLastValue  = GetCardValue(bLastCard);
	if (bFirstValue == bLastValue) return bFirstValue > bLastValue;
	return bFirstValue > bLastValue;
}


//��ȡ�˿���ֵ
BYTE CGameLogic::GetCardValoe(BYTE bCard)
{
	BYTE bValue = bCard%13;
	if (bValue == 10 || bValue == 11 || bValue == 12 || bValue == 13) bValue=0;
	return bValue;
}

//�Ƿ�Ϊ����
bool CGameLogic::IsGong(BYTE bCard)
{
	BYTE bValue = bCard%13;
	if (bValue == 11 || bValue == 12 || bValue == 13) return true;
	return false;
}

//�Ƿ�333��������
bool CGameLogic::IsSanZhangSan(const BYTE bCardList[], const BYTE bCardCount)
{
	if (bCardCount<3) return false;

	BYTE c1,c2,c3;
	c1 = GetCardValoe(bCardList[0]);
	c2 = GetCardValoe(bCardList[1]);
	c3 = GetCardValoe(bCardList[2]);

	if (c1==3&&c2==3&&c3==3) return true;

	return false;
}

//�Ƿ�����һ������
bool CGameLogic::IsSanZhangGong(const BYTE bCardList[], const BYTE bCardCount)
{
	if (bCardCount<3) return false;
	
	//�ж��Ƿ�Ϊ��
	for(int i = 0; i <= bCardCount-1; i++)
	{
		if (!IsGong(bCardList[i])) return false;
	}

	BYTE c1,c2,c3;
	c1 = GetCardValoe(bCardList[0]);
	c2 = GetCardValoe(bCardList[1]);
	c3 = GetCardValoe(bCardList[2]);

	if(c1==c2&&c1==c3) return true;

	return false;
}

//�Ƿ���ӹ���
bool CGameLogic::IsSanGongDui(const BYTE bCardList[], const BYTE bCardCount)
{
	if (bCardCount<3) return false;

	//�ж��Ƿ�Ϊ��
	for(int i = 0; i <= bCardCount-1; i++)
	{
		if (!IsGong(bCardList[i])) return false;
	}

	BYTE c1,c2,c3;
	c1 = GetCardValoe(bCardList[0]);
	c2 = GetCardValoe(bCardList[1]);
	c3 = GetCardValoe(bCardList[2]);
	
	if (((c1==c2)&&c3==0) && ((c2==c3)&&c1>10) && ((c1==c3)&&c2>10)) return true;
	return false;
}

//�Ƿ�JQK����
bool CGameLogic::IsSanGong(const BYTE bCardList[], const BYTE bCardCount)
{
	if (bCardCount<3) return false;

	//�ж��Ƿ�Ϊ��
	for(int i = 0; i <= bCardCount-1; i++)
	{
		if (!IsGong(bCardList[i])) return false;
	}

	BYTE c1,c2,c3;
	c1 = GetCardValoe(bCardList[0]);
	c2 = GetCardValoe(bCardList[1]);
	c3 = GetCardValoe(bCardList[2]);

	if(c1==0&&c2==0&&c3==0) return true;

	return false;
}
//��ȡ�˿�����
BYTE CGameLogic::GetCardKind(const BYTE bCardList[], const BYTE bCardCount)
{
	//�Ƿ����
	//if (IsDuiZhi(bCardList,bCardCount)) return DUI_ZI;
	//return SHAN; //����Ϊɢ��

	//CString a;
	//a.Format("����Ϊ%d",bCardCount);
	//AfxMessageBox(a);

	//�Ƿ�333��������
	if(IsSanZhangSan(bCardList,bCardCount)) return SAN_ZHANG_SAN;
	//�Ƿ���ӹ���
	if(IsSanGongDui(bCardList,bCardCount)) return SAN_GONG_DUI;
	//�Ƿ�����һ������
	if(IsSanZhangGong(bCardList,bCardCount)) return SAN_ZHANG_GONG;	
	//�Ƿ�JQK����
	if(IsSanGong(bCardList,bCardCount)) return SAN_GONG;
	return SHAN; //����Ϊɢ��

}

//�Աȶ���
BYTE CGameLogic::CompareDuiZhi(const BYTE bFirstList[], const BYTE bLastList[], BYTE bCardCount)
{
	//return CompareOnlyOne(bFirstList[0],bLastList[0]);1
	BYTE bFirstVolae=GetCardValoe(bFirstList[0]);
	BYTE bLastVolae=GetCardValoe(bLastList[0]);
	//if(bFirstVolae==bLastVolae) return 0;
	if(bFirstVolae>bLastVolae) return 1;
	if(bFirstVolae<bLastVolae) return 2;

	return 0;
}

//�Ա�ɢ��
BYTE CGameLogic::CompareSanCard(const BYTE bFirstList[], const BYTE bLastList[], BYTE bCardCount)
{
	BYTE bFirstCard, bLastCard;

	bFirstCard = (GetCardValoe(bFirstList[0])+GetCardValoe(bFirstList[1])+GetCardValoe(bFirstList[2]))%10;
	bLastCard = (GetCardValoe(bLastList[0])+GetCardValoe(bLastList[1])+GetCardValoe(bLastList[2]))%10;
	//CString a;
	//a.Format("ׯ:%d+%d+%d=%d,��%d",bFirstList[0],bFirstList[1],bFirstList[2],bFirstCard,bLastCard);
	//a.Format("ׯ:%d,��%d",bFirstCard,bLastCard);
	//AfxMessageBox(a);
	//if(bFirstCard==bLastCard) return 0;
	if(bFirstCard>bLastCard) return 1;
	if(bFirstCard<bLastCard) return 2;

	return 0;
}

//�Աȶ��ӹ���
BYTE CGameLogic::CompareSanGongDui(const BYTE bFirstCard[], const BYTE bLastCard[])
{
	BYTE a1,a2,a3,a4,a5,b1,b2,b3,b4,b5;
	a1 = GetCardValue(bFirstCard[0]);
	a2 = GetCardValue(bFirstCard[1]);
	a3 = GetCardValue(bFirstCard[2]);

	if (a1 == a2) //�����1�ź͵�2����ͬ
	{	
		a4 = a1; //��ͬ����Ϊ��1��
		a5 = a3; //��ͬ����Ϊ��3��
	}
	else //�����1�ź͵�2�Ų���ͬ�����ǵ�1�ź͵�3����ͬ
	{
		if (a1 == a3) //�����1�ź͵�3����ͬ
		{
			a4 = a1; //��ͬ����Ϊ��1��
			a5 = a2; //��ͬ����Ϊ��2��
		}
		else
		{
			a4 = a2; //��Ϊ��1�ź͵�3�Ų���ͬ����ô��ͬ����Ϊ��2��
			a5 = a1; //��ͬ����Ϊ��1��
		}
	}

	b1 = GetCardValue(bLastCard[0]);
	b2 = GetCardValue(bLastCard[1]);
	b3 = GetCardValue(bLastCard[2]);

	if(b1 == b2) //�����1�ź͵�2����ͬ
	{	
		b4 = b1; //��ͬ����Ϊ��1��
		b5 = b3; //��ͬ����Ϊ��3��
	}
	else //�����1�ź͵�2�Ų���ͬ�����ǵ�1�ź͵�3����ͬ
	{
		if (b1 == b3) //�����1�ź͵�3����ͬ
		{
			b4 = b1; //��ͬ����Ϊ��1��
			b5 = b2; //��ͬ����Ϊ��2��
		}
		else
		{
			b4 = b2; //��Ϊ��1�ź͵�3�Ų���ͬ����ô��ͬ����Ϊ��2��
			b5 = b1; //��ͬ����Ϊ��1��
		}
	}

	if (a4 == b4) //�������һ����
	{
		if (a5 == b5) return 0; //�;�ׯӮ
		else if (a5 > b5) return 1; //ׯӮ
		else if (a5 < b5) return 2; //��Ӯ
	}
	else if (a4 > b4) return 1; //ׯӮ
	else if (a4 < b4) return 2; //��Ӯ
}

//�ƶ�ʤ��
BYTE CGameLogic::DeduceWiner(const BYTE bBankerCard[],const BYTE bBankerCardCount,
							 const BYTE bIdleCard[],  const BYTE bIdleCardCount,BYTE &cbWinnerCardType)
{
	//��ʼ������ֵ
	cbWinnerCardType=SHAN;

	BYTE bFirstKind=GetCardKind(bBankerCard,bBankerCardCount);
	BYTE bLastKind=GetCardKind(bIdleCard,bIdleCardCount);
	
	//ׯ��Ӯ
	if (bFirstKind>bLastKind) 
	{
		cbWinnerCardType=bFirstKind;
		return 1;
	}

	//�м�Ӯ
	if (bFirstKind<bLastKind)
	{
		cbWinnerCardType=bLastKind;
		return 2;
	}

	cbWinnerCardType=bFirstKind;

	//������ͬ
	switch(bFirstKind)
	{
		//ɢ��
	case SHAN:return CompareSanCard(bBankerCard,bIdleCard,3);		
		//�Ƿ�Ϊ����
	case SAN_GONG: return 1; //��ΪJQKׯӮ
		//�Ƿ���ӹ���
	case SAN_GONG_DUI: return CompareSanGongDui(bBankerCard,bIdleCard);
		//�Ƿ�����һ������
	case SAN_ZHANG_GONG: return CompareOnlyOne(bBankerCard[0],bIdleCard[0]);
		//�Ƿ�333��������
	case SAN_ZHANG_SAN: return 1; //�������1���Ʋ����ܷ����������Ƕั�ƣ�Ԥ�� ׯӮ
	}

	//ƽ,ׯӮ
	if (bFirstKind==bLastKind && bFirstKind!=0) return 0;
}

//�����˿�
void CGameLogic::RandCard(BYTE bCardBuffer[], BYTE bBufferCount)
{
	BYTE bSend = 0,bStation = 0, bCardList[CountArray(m_bCardArray)];

	CopyMemory(bCardList, m_bCardArray, sizeof(m_bCardArray));
	
	static long int dwRandCount = 0L;
	
	srand((unsigned)time(NULL) + dwRandCount++);
	
	do
	{
		bStation = rand() % (CountArray(m_bCardArray) - bSend);

		bCardBuffer[bSend++] = bCardList[bStation];
		bCardList[bStation]  = bCardList[CountArray(m_bCardArray)-bSend];
	
	} while (bSend < bBufferCount);	
}

//�����˿�
void CGameLogic::SortCard(BYTE bCardList[], BYTE bCardCount)
{
	bool bSorted     = true;
	BYTE bTemp,bLast = bCardCount - 1;
	do
	{
		bSorted = true;
		for (BYTE i = 0; i < bLast; i++) 
		{
			if (CompareOnlyOne(bCardList[i],bCardList[i+1]) == FALSE)
			{	
				bTemp = bCardList[i];
				bCardList[i]   = bCardList[i+1];
				bCardList[i+1] = bTemp;
				bSorted = false;
			}	
		}
		bLast--;
	} while (bSorted == false);

	return;
}
//////////////////////////////////////////////////////////////////////////