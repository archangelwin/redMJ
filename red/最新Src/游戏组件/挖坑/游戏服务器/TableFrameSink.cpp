#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;			//��Ϸ����
const enStartMode	CTableFrameSink::m_GameStartMode=enStartMode_FullReady;	//��ʼģʽ

//////////////////////////////////////////////////////////////////////////

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//��Ϸ����
	m_bCavernScore=0;
	m_wFirstUser=INVALID_CHAIR;
	m_wCavernUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	memset(m_bScoreInfo,0,sizeof(m_bScoreInfo));

	//������Ϣ
	m_bCount1=0;
	m_bCount2=0;
	m_bCount3=0;
	m_bTurnCardCount=0;
	m_wTurnWiner=INVALID_CHAIR;
	memset(m_bTurnCardData,0,sizeof(m_bTurnCardData));

	//�˿���Ϣ
	memset(m_bBackCard,0,sizeof(m_bBackCard));
	memset(m_bCardCount,0,sizeof(m_bCardCount));
	memset(m_bHandCardData,0,sizeof(m_bHandCardData));
	
	//�������
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;

	return;
}

//��������
CTableFrameSink::~CTableFrameSink(void)
{
}

//�ӿڲ�ѯ
void * __cdecl CTableFrameSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//��ʼ��
bool __cdecl CTableFrameSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=GET_OBJECTPTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL) return false;

	//��ȡ����
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	return true;
}

//��λ����
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	//��Ϸ����
	m_bCavernScore=0;
	m_wFirstUser=INVALID_CHAIR;
	m_wCavernUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	memset(m_bScoreInfo,0,sizeof(m_bScoreInfo));

	//������Ϣ
	m_bCount1=0;
	m_bCount2=0;
	m_bCount3=0;
	m_bTurnCardCount=0;
	m_wTurnWiner=INVALID_CHAIR;
	memset(m_bTurnCardData,0,sizeof(m_bTurnCardData));

	//�˿���Ϣ
	memset(m_bBackCard,0,sizeof(m_bBackCard));
	memset(m_bCardCount,0,sizeof(m_bCardCount));
	memset(m_bHandCardData,0,sizeof(m_bHandCardData));

	return;
}

//��ʼģʽ
enStartMode __cdecl CTableFrameSink::GetGameStartMode()
{
	return m_GameStartMode;
}

//��Ϸ״̬
bool __cdecl CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	return true;
}

//��Ϸ��ʼ
bool __cdecl CTableFrameSink::OnEventGameStart()
{
	//����״̬
	m_pITableFrame->SetGameStatus(GS_WK_SCORE);

	//�����˿�
	BYTE bRandCard[52];
	m_GameLogic.RandCardList(bRandCard,sizeof(bRandCard)/sizeof(bRandCard[0]));

	//�ַ��˿�
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		m_bCardCount[i]=16;
		CopyMemory(&m_bHandCardData[i],&bRandCard[i*m_bCardCount[i]],sizeof(BYTE)*m_bCardCount[i]);
		m_GameLogic.SortCardList(m_bHandCardData[i],m_bCardCount[i]);
	}
	CopyMemory(m_bBackCard,&bRandCard[48],sizeof(m_bBackCard));
	m_GameLogic.SortCardList(m_bBackCard,4);

	//Ѱ�ұ���
	BYTE bFlagCard=0x28;
	bool bHaveFlagCard[4]={false,false,false,false};
	for (BYTE i=0;i<4;i++)
	{
		if (m_GameLogic.GetCardColor(m_bBackCard[i])==0x20)
		{
			BYTE bCardValue=m_GameLogic.GetCardValue(m_bBackCard[i]);
			if ((bCardValue>=4)&&(bCardValue<=7)) bHaveFlagCard[bCardValue-4]=true;
		}
	}
	for (BYTE i=0;i<4;i++)
	{
		if (bHaveFlagCard[i]==false)
		{
			bFlagCard=0x24+i;
			break;
		}
	}

	//Ѱ���ڿ�
	bool bFind=false;
	BYTE bBaseValue=m_GameLogic.GetCardValue(bFlagCard);
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		for (BYTE j=m_bCardCount[i]-1;j>=0;j--)
		{
			if (m_GameLogic.GetCardValue(m_bHandCardData[i][j])>bBaseValue) break;
			if (m_bHandCardData[i][j]==bFlagCard)
			{
				bFind=true;
				m_wFirstUser=i;
				m_wCurrentUser=i;
				break;
			}
		}
		if (bFind==true) break;
	}
	ASSERT(bFind==true);

	//�����˿�
	CMD_S_SendCard SendCard;
	SendCard.wCurrentUser=m_wCurrentUser;
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		CopyMemory(SendCard.bCardData,m_bHandCardData[i],sizeof(SendCard.bCardData));
		m_pITableFrame->SendTableData(i,SUB_S_SEND_CARD,&SendCard,sizeof(SendCard));
		m_pITableFrame->SendLookonData(i,SUB_S_SEND_CARD,&SendCard,sizeof(SendCard));
	}

	return true;
}

//��Ϸ����
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_DISMISS:		//��Ϸ��ɢ
		{
			//Ч�����
			ASSERT(pIServerUserItem!=NULL);
			ASSERT(wChairID<m_wPlayerCount);

			//��������
			CMD_S_GameEnd GameEnd;
			memset(&GameEnd,0,sizeof(GameEnd));

			//ʣ���˿�
			BYTE bCardPos=0;
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				GameEnd.bCardCount[i]=m_bCardCount[i];
				CopyMemory(&GameEnd.bCardData[bCardPos],m_bHandCardData[i],m_bCardCount[i]*sizeof(BYTE));
				bCardPos+=m_bCardCount[i];
			}

			//������Ϣ
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//������Ϸ
			m_pITableFrame->ConcludeGame();

			return true;
		}
	case GER_NORMAL:		//�������
		{
			//�������
			CMD_S_GameEnd GameEnd;
			memset(&GameEnd,0,sizeof(GameEnd));

			//ʣ���˿�
			BYTE bCardPos=0;
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				GameEnd.bCardCount[i]=m_bCardCount[i];
				CopyMemory(&GameEnd.bCardData[bCardPos],m_bHandCardData[i],m_bCardCount[i]*sizeof(BYTE));
				bCardPos+=m_bCardCount[i];
			}

			//��������
			LONG lCellScore=m_pGameServiceOption->lCellScore;
			bool bCavernWin=(m_bCardCount[m_wCavernUser]==0)?true:false;

			//ͳ�ƻ���
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				if (i==m_wCavernUser) GameEnd.lGameScore[i]=m_bCavernScore*lCellScore*((bCavernWin==true)?2:-2);
				else GameEnd.lGameScore[i]=m_bCavernScore*lCellScore*((bCavernWin==true)?-1:1);
			}

			//����˰��
			if (m_pGameServiceOption->wServerType&GAME_GENRE_GOLD)
			{
				for (WORD i=0;i<m_wPlayerCount;i++)
				{
					if (GameEnd.lGameScore[i]>=100L)
					{
						GameEnd.lGameTax+=GameEnd.lGameScore[i]/10L;
						GameEnd.lGameScore[i]=GameEnd.lGameScore[i]*45L/50L;
					}
				}
			}

			//������Ϣ
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//�޸Ļ���
			tagScoreInfo ScoreInfo[m_wPlayerCount];
			memset(&ScoreInfo,0,sizeof(ScoreInfo));
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				ScoreInfo[i].lScore=GameEnd.lGameScore[i];
				ScoreInfo[i].ScoreKind=(GameEnd.lGameScore[i]>0L)?enScoreKind_Win:enScoreKind_Lost;
			}
			m_pITableFrame->WriteTableScore(ScoreInfo,m_wPlayerCount,GameEnd.lGameTax);

			//������Ϸ
			m_pITableFrame->ConcludeGame();

			return true;
		}
	case GER_USER_LEFT:		//�û�ǿ��
		{
			//Ч�����
			ASSERT(pIServerUserItem!=NULL);
			ASSERT(wChairID<m_wPlayerCount);

			//��������
			CMD_S_GameEnd GameEnd;
			memset(&GameEnd,0,sizeof(GameEnd));
			GameEnd.lGameScore[wChairID]=-20*m_pGameServiceOption->lCellScore;

			//ʣ���˿�
			BYTE bCardPos=0;
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				GameEnd.bCardCount[i]=m_bCardCount[i];
				CopyMemory(&GameEnd.bCardData[bCardPos],m_bHandCardData[i],m_bCardCount[i]*sizeof(BYTE));
				bCardPos+=m_bCardCount[i];
			}

			//������Ϣ
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//�޸Ļ���
			tagScoreInfo ScoreInfo;
			ScoreInfo.ScoreKind=enScoreKind_Draw;
			ScoreInfo.lScore=GameEnd.lGameScore[wChairID];
			m_pITableFrame->WriteUserScore(wChairID,ScoreInfo);

			//������Ϸ
			m_pITableFrame->ConcludeGame();

			return true;
		}
	}

	ASSERT(FALSE);

	return false;
}

//���ͳ���
bool __cdecl CTableFrameSink::SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	switch (cbGameStatus)
	{
	case GS_WK_FREE:		//����״̬
		{
			//��������
			CMD_S_StatusFree StatusFree;
			memset(&StatusFree,0,sizeof(StatusFree));

			//���ñ���
			StatusFree.lBaseScore=m_pGameServiceOption->lCellScore;

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));
		}
	case GS_WK_SCORE:		//�з�״̬
		{
			//��������
			CMD_S_StatusScore StatusScore;
			memset(&StatusScore,0,sizeof(StatusScore));

			//���ñ���
			StatusScore.bCavernScore=m_bCavernScore;
			StatusScore.wCurrentUser=m_wCurrentUser;
			StatusScore.lBaseScore=m_pGameServiceOption->lCellScore;
			CopyMemory(StatusScore.bScoreInfo,m_bScoreInfo,sizeof(m_bScoreInfo));
			CopyMemory(StatusScore.bCardData,m_bHandCardData[wChiarID],m_bCardCount[wChiarID]);

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusScore,sizeof(StatusScore));
		}
	case GS_WK_PLAYING:		//��Ϸ״̬
		{
			//��������
			CMD_S_StatusPlay StatusPlay;
			memset(&StatusPlay,0,sizeof(StatusPlay));

			//���ñ���
			StatusPlay.wLastOutUser=m_wTurnWiner;
			StatusPlay.wCavernUser=m_wCavernUser;
			StatusPlay.wCurrentUser=m_wCurrentUser;
			StatusPlay.bCavernScore=m_bCavernScore;
			StatusPlay.bTurnCardCount=m_bTurnCardCount;
			StatusPlay.lBaseScore=m_pGameServiceOption->lCellScore;
			CopyMemory(StatusPlay.bBackCard,m_bBackCard,sizeof(m_bBackCard));
			CopyMemory(StatusPlay.bCardCount,m_bCardCount,sizeof(m_bCardCount));
			CopyMemory(StatusPlay.bTurnCardData,m_bTurnCardData,sizeof(BYTE)*m_bTurnCardCount);
			CopyMemory(StatusPlay.bCardData,m_bHandCardData[wChiarID],sizeof(BYTE)*m_bCardCount[wChiarID]);

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
		}
	}

	return false;
}

//��ʱ���¼�
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	return false;
}

//��Ϸ��Ϣ����
bool __cdecl CTableFrameSink::OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch (wSubCmdID)
	{
	case SUB_C_CAVERN_SCORE:	//�û��з�
		{
			//Ч������
			ASSERT(wDataSize==sizeof(CMD_C_CavernScore));
			if (wDataSize!=sizeof(CMD_C_CavernScore)) return false;

			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//��Ϣ����
			CMD_C_CavernScore * pCavernScore=(CMD_C_CavernScore *)pDataBuffer;
			return OnUserCavernScore(pUserData->wChairID,pCavernScore->bCavernScore);
		}
	case SUB_C_OUT_CART:		//�û�����
		{
			//��������
			CMD_C_OutCard * pOutCard=(CMD_C_OutCard *)pDataBuffer;
			WORD wHeadSize=sizeof(CMD_C_OutCard)-sizeof(pOutCard->bCardData);

			//Ч������
			ASSERT(wDataSize>=wHeadSize);
			if (wDataSize<wHeadSize) return false;
			ASSERT(wDataSize==(wHeadSize+pOutCard->bCardCount*sizeof(pOutCard->bCardData[0])));
			if (wDataSize!=(wHeadSize+pOutCard->bCardCount*sizeof(pOutCard->bCardData[0]))) return false;

			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//��Ϣ����
			return OnUserOutCard(pUserData->wChairID,pOutCard->bCardData,pOutCard->bCardCount);
		}
	case SUB_C_PASS_CARD:
		{
			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//��Ϣ����
			return OnUserPassCard(pUserData->wChairID);
		}
	}

	return true;
}

//�����Ϣ����
bool __cdecl CTableFrameSink::OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}

//�з��¼�
bool CTableFrameSink::OnUserCavernScore(WORD wChairID, BYTE bCavernScore)
{
	//Ч��״̬
	if (m_pITableFrame->GetGameStatus()!=GS_WK_SCORE) return true;
	if (wChairID!=m_wCurrentUser) return false;

	//Ч�����
	if (((bCavernScore>3)&&(bCavernScore!=255))||(bCavernScore<=m_bCavernScore)) return false;

	//���ñ���
	if (bCavernScore!=255)
	{
		m_bCavernScore=bCavernScore;
		m_wCavernUser=m_wCurrentUser;
	}
	m_bScoreInfo[wChairID]=bCavernScore;

	//��ʼ�ж�
	if ((m_bCavernScore==3)||(m_wFirstUser==(wChairID+1)%m_wPlayerCount))
	{
		//���ñ���
		if (m_bCavernScore==0) m_bCavernScore=1;
		if (m_wCavernUser==INVALID_CHAIR) m_wCavernUser=m_wFirstUser;

		//����״̬
		m_pITableFrame->SetGameStatus(GS_WK_PLAYING);

		//���͵���
		m_bCardCount[m_wCavernUser]=20;
		CopyMemory(&m_bHandCardData[m_wCavernUser][16],m_bBackCard,sizeof(m_bBackCard));
		m_GameLogic.SortCardList(m_bHandCardData[m_wCavernUser],m_bCardCount[m_wCavernUser]);

		//������Ϣ
		m_bTurnCardCount=0;
		m_wTurnWiner=m_wFirstUser;
		m_wCurrentUser=m_wFirstUser;

		//������Ϣ
		CMD_S_GameStart GameStart;
		GameStart.wCavernUser=m_wCavernUser;
		GameStart.bCavernScore=m_bCavernScore;
		GameStart.wCurrentUser=m_wCurrentUser;
		CopyMemory(GameStart.bBackCard,m_bBackCard,sizeof(m_bBackCard));
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_START,&GameStart,sizeof(GameStart));

		return true;
	}

	//�����û�
	m_wCurrentUser=(wChairID+1)%m_wPlayerCount;

	//������Ϣ
	CMD_S_CavernScore CavernScore;
	CavernScore.bCavernUser=wChairID;
	CavernScore.bCavernScore=bCavernScore;
	CavernScore.wCurrentUser=m_wCurrentUser;
	CavernScore.bCurrentScore=m_bCavernScore;
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_CAVERN_SCORE,&CavernScore,sizeof(CavernScore));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_CAVERN_SCORE,&CavernScore,sizeof(CavernScore));

	return true;
}

//�û�����
bool CTableFrameSink::OnUserOutCard(WORD wChairID, BYTE bCardData[], BYTE bCardCount)
{
	//Ч��״̬
	if (m_pITableFrame->GetGameStatus()!=GS_WK_PLAYING) return true;
	if (wChairID!=m_wCurrentUser) return false;

	//�����ж�
	BYTE bCardType=m_GameLogic.GetCardType(bCardData,bCardCount);
	if (bCardType==CT_INVALID) return false;

	//�������
	if (m_bTurnCardCount!=0)
	{
		if (m_bTurnCardCount!=bCardCount) return false;
		if (m_GameLogic.CompareCard(bCardData,m_bTurnCardData,m_bTurnCardCount)==false) return false;
	}
	else m_bTurnCardCount=bCardCount;

	//ɾ���˿�
	if (m_GameLogic.RemoveCard(bCardData,bCardCount,m_bHandCardData[wChairID],m_bCardCount[wChairID])==false) return false;
	m_bCardCount[wChairID]-=bCardCount;

	//�����ж�
	bool bMostest=false;
	BYTE bLogicValue=m_GameLogic.GetCardValue(bCardData[0]);
	if ((bLogicValue==3)||((bLogicValue==13)&&(bCardType>=CT_ONE_LINE))) bMostest=true;
	else if ((bLogicValue==2)&&((m_bCount3+bCardCount)>4)) bMostest=true;
	else if ((bLogicValue==1)&&((m_bCount2+bCardCount)>4)&&((m_bCount3+bCardCount)>4)) bMostest=true;
	else if ((bLogicValue==1)&&((m_bCount1+bCardCount)>4)&&((m_bCount2+bCardCount)>4)&&((m_bCount3+bCardCount)>4)) bMostest=true;

	//���Ƽ�¼
	for (BYTE i=0;i<bCardCount;i++)
	{
		bLogicValue=m_GameLogic.GetCardValue(bCardData[i]);
		if (bLogicValue==3) m_bCount3++;
		else if (bLogicValue==2) m_bCount2++;
	}
	CopyMemory(m_bTurnCardData,bCardData,sizeof(BYTE)*m_bTurnCardCount);
	
	//�л��û�
	m_wTurnWiner=wChairID;
	if (m_bCardCount[wChairID]!=0)
	{
		if (bMostest==false) m_wCurrentUser=(m_wCurrentUser+1)%m_wPlayerCount;
	}
	else m_wCurrentUser=INVALID_CHAIR;

	//��������
	CMD_S_OutCard OutCard;
	OutCard.bCardCount=bCardCount;
	OutCard.wOutCardUser=wChairID;
	OutCard.wCurrentUser=m_wCurrentUser;
	CopyMemory(OutCard.bCardData,m_bTurnCardData,m_bTurnCardCount*sizeof(BYTE));

	//��������
	WORD wSendSize=sizeof(OutCard)-sizeof(OutCard.bCardData)+OutCard.bCardCount*sizeof(BYTE);
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OUT_CARD,&OutCard,wSendSize);
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OUT_CARD,&OutCard,wSendSize);

	//�������
	if (bMostest==true) m_bTurnCardCount=0;

	//�жϽ�����Ϸ
	if (m_wCurrentUser==INVALID_CHAIR) OnEventGameEnd(wChairID,NULL,GER_NORMAL);

	return true;
}

//�û�����
bool CTableFrameSink::OnUserPassCard(WORD wChairID)
{
	//Ч��״̬
	if (m_pITableFrame->GetGameStatus()!=GS_WK_PLAYING) return true;
	if ((wChairID!=m_wCurrentUser)||(m_bTurnCardCount==0)) return false;

	//���ñ���
	m_wCurrentUser=(m_wCurrentUser+1)%m_wPlayerCount;
	if (m_wCurrentUser==m_wTurnWiner) m_bTurnCardCount=0;

	//��������
	CMD_S_PassCard PassCard;
	PassCard.wPassUser=wChairID;
	PassCard.wCurrentUser=m_wCurrentUser;
	PassCard.bNewTurn=(m_bTurnCardCount==0)?TRUE:FALSE;
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_PASS_CARD,&PassCard,sizeof(PassCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_PASS_CARD,&PassCard,sizeof(PassCard));

	return true;
}

//////////////////////////////////////////////////////////////////////////
