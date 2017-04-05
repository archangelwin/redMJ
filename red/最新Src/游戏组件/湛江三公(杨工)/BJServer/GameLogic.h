#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

#define SHAN								0
#define SAN_GONG							1
#define	SAN_GONG_DUI						2
#define	SAN_ZHANG_GONG						3
#define	SAN_ZHANG_SAN						4

//��Ϸ�߼���
class CGameLogic
{
	//��������
private:
	static const BYTE				m_bCardArray[52];					//�˿˶���

	//���ܺ���
public:	
	//�����˿�
	void RandCard(BYTE bCardBuffer[], BYTE bBufferCount);
	//��ȡ�˿���ֵ
	BYTE GetCardValoe(BYTE bCard);
	//�Ƿ�333��������
	bool IsSanZhangSan(const BYTE bCardList[], const BYTE bCardCount);
	//�Ƿ�����һ������
	bool IsSanZhangGong(const BYTE bCardList[], const BYTE bCardCount);
	//�Ƿ���ӹ���
	bool IsSanGongDui(const BYTE bCardList[], const BYTE bCardCount);
	//�Ƿ�JQK����
	bool IsSanGong(const BYTE bCardList[], const BYTE bCardCount);
	//�Ƿ�Ϊ����
	bool IsGong(const BYTE bCardList);
	//��ȡ�˿�����
	BYTE GetCardKind(const BYTE bCardList[], const BYTE bCardCount);
	//��ȡ�˿���ֵ
	BYTE GetCardValue(BYTE bCard);
	//��ȡ�˿���ֵ
	BYTE GetCardSum(const BYTE bCardBuffer[], const BYTE bCardCount);	
	//�Աȶ���
	BYTE CompareDuiZhi(const BYTE bFirstList[], const BYTE bLastList[], BYTE bCardCount);
	//�Ա�ɢ��
	BYTE CompareSanCard(const BYTE bFirstList[], const BYTE bLastList[], BYTE bCardCount);
	//�Աȶ��ӹ���
	BYTE CompareSanGongDui(const BYTE bFirstCard[], const BYTE bLastCard[]);
	//�Աȵ�ֻ�˿�
	bool CompareOnlyOne(BYTE bFirstCard, BYTE bLastCard);		
	//�����˿�
	void SortCard(BYTE bCardList[], BYTE bCardCount);
	
	//�Ƿ���
	bool IsBurst(const BYTE bCardBuffer[], BYTE bCardCount);
	//�Ƿ�BlackJack
	bool IsBlackJack(const BYTE bCardBuffer[]);
	//�ܷ����
	bool CanCutCard(const BYTE bFirstCard, const BYTE bLastCard);
	
	//�ƶ�ʤ��
	BYTE DeduceWiner(const BYTE bBankerCard[],const BYTE bBankerCardCount,
	                  const BYTE bIdleCard[],const BYTE bIdleCardCount,BYTE &cbWinnerCardType);

};

//////////////////////////////////////////////////////////////////////////

#endif