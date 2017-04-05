#include "StdAfx.h"
#include "TableFrameSink.h"
#include ".\tableframesink.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
const enStartMode	CTableFrameSink::m_GameStartMode = enStartMode_AllReady;	//��ʼģʽ

//////////////////////////////////////////////////////////////////////////

//���캯��
CTableFrameSink::CTableFrameSink()
{	
	//��Ϸ����							
	m_wCurrentUser   = INVALID_CHAIR;	
	m_wPlayerCount   = 0;		

	//��Ϸׯ��
	m_nBankerStation = -1;
	m_lBankerScore   = 0L;
	m_bBankerWin     = false;


	//��ʶ��ע
	m_bAddGoldEnd    = false;	
	memset(m_bAddGold,0,sizeof(m_bAddGold));
	memset(m_lUserAddGold,0,sizeof(m_lUserAddGold));
	m_cbAddCount = 0;

	//�����Ϣ
	m_lMaxGold       = 0L;
	m_lTurnBasicGold = 1L;
	memset(m_lTableGold,0,sizeof(m_lTableGold));
	m_lTotalAddGold = 0L;	


	//��ʼ�˿�	
  	memset(m_cbTableCardCount,0,sizeof(m_cbTableCardCount));	
	memset(m_cbTableCardArray,0,sizeof(m_cbTableCardArray));  
    
	//���Ʊ���
	memset(m_cbRandCardArray,0,sizeof(m_cbRandCardArray)); 
	m_cbSendCardCount = 0;

	//���״̬		
	memset(m_cbCardStatus,0,sizeof(m_cbCardStatus));
	
	
	//�������
	m_pITableFrame     = NULL;
	pGameServiceOption = NULL;

	return;
}

//��������
CTableFrameSink::~CTableFrameSink(void)
{
}

//�ӿڲ�ѯ
void * __cdecl CTableFrameSink::QueryInterface(const IID & Guid,
											   DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink, Guid, dwQueryVer);
	
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink, Guid, dwQueryVer);
	return NULL;
}

//��ʼ��
bool __cdecl CTableFrameSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx != NULL);

	m_pITableFrame = GET_OBJECTPTR_INTERFACE(pIUnknownEx, ITableFrame);
	
	if (m_pITableFrame == NULL)
	{
		return false;
	}

	//��ȡ����
	pGameServiceOption = m_pITableFrame->GetGameServiceOption();

	ASSERT(pGameServiceOption != NULL);

	m_pITableFrame->SetGameStatus(GS_FREE);

	return true;
}

//��λ����
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	//��Ϸ����							
	m_wCurrentUser   = INVALID_CHAIR;	
	m_wPlayerCount   = 0;		

	//��Ϸׯ��
	m_lBankerScore   = 0L;


	//��ʶ��ע
	m_bAddGoldEnd    = false;	
	memset(m_bAddGold,0,sizeof(m_bAddGold));
	memset(m_lUserAddGold,0,sizeof(m_lUserAddGold));
	m_cbAddCount = 0;

	//�����Ϣ
	m_lMaxGold       = 0L;
	m_lTurnBasicGold = 1L;
	memset(m_lTableGold,0,sizeof(m_lTableGold));
	m_lTotalAddGold = 0L;
	

	//��ʼ�˿�	
  	memset(m_cbTableCardCount,0,sizeof(m_cbTableCardCount));	
	memset(m_cbTableCardArray,0,sizeof(m_cbTableCardArray));
	memset(m_cbRandCardArray,0,sizeof(m_cbRandCardArray));  
    
	//���Ʊ���
	memset(m_cbRandCardArray,0,sizeof(m_cbRandCardArray)); 
	m_cbSendCardCount = 0;

	//���״̬		
	memset(m_cbCardStatus,0,sizeof(m_cbCardStatus));


	//����״̬
	m_pITableFrame->SetGameStatus(GS_FREE);

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
	return  true;
}

//���ͳ���
bool __cdecl CTableFrameSink::SendGameScene(WORD wChiarID, 
											IServerUserItem * pIServerUserItem, 
											BYTE bGameStatus, 
											bool bSendSecret)
{
	bool bWatchUser;

	const tagServerUserData *pUserData = pIServerUserItem->GetUserData();
	
	if (pUserData->cbUserStatus != US_LOOKON)
		bWatchUser = false; 
	
	switch (bGameStatus)
	{
	case GS_FREE:
		{			
			//��������
			CMD_S_StatusFree StatusFree;

			memset(&StatusFree, 0, sizeof(StatusFree));

			StatusFree.dwBasicGold = pGameServiceOption->lCellScore;

			//���ͳ���
			return 	m_pITableFrame->SendGameScene(pIServerUserItem,
			                                      &StatusFree,
												  sizeof(StatusFree));

	
		}
	case GS_ADDGOLDING:
		{
			//��������
			CMD_S_StatusAddGold StatusAddGold;
			memset(&StatusAddGold,0,sizeof(StatusAddGold));

			StatusAddGold.dwBasicGold    = pGameServiceOption->lCellScore;
			StatusAddGold.lMaxGold       = m_lMaxGold;		
			StatusAddGold.wBankerStation = m_nBankerStation;
			StatusAddGold.wCurrentUser   = wChiarID;
			CopyMemory(StatusAddGold.bAddGoldEnd,m_bAddGold,sizeof(m_bAddGold));
			CopyMemory(StatusAddGold.lTableGold,m_lTableGold,sizeof(m_lTableGold));
		
			//���ͳ���
			return 	m_pITableFrame->SendGameScene(pIServerUserItem,
			                                      &StatusAddGold,
												  sizeof(StatusAddGold));
		}

	case GS_PLAYING:
		{
			//��������
			CMD_S_StatusPlay StatusPlay;
			memset(&StatusPlay,0,sizeof(StatusPlay));

			StatusPlay.wCurrentUser   = m_wCurrentUser;
			StatusPlay.wBankerStation = m_nBankerStation;
			StatusPlay.lMaxGold       = m_lMaxGold;				
			StatusPlay.lBasicGold     = pGameServiceOption->lCellScore;
			CopyMemory(StatusPlay.cbPlayStatus,m_cbCardStatus,sizeof(m_cbCardStatus));
			CopyMemory(StatusPlay.lTableGold,m_lTableGold,sizeof(m_lTableGold));

			//�����˿�
			for (WORD i = 0; i < GAME_PLAYER; i++)
			{
				if (m_cbCardStatus[i] != NO_CARD)
				{
					ASSERT(m_pITableFrame->GetServerUserItem(i) != NULL);
					StatusPlay.cbTableCardCount[i] = m_cbTableCardCount[i];								
				
					CopyMemory(&StatusPlay.cbTableCardArray[i][0],&m_cbTableCardArray[i][0],m_cbTableCardCount[i]*sizeof(BYTE));
				}
			}
			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
		}

	}
	//Ч����
	ASSERT(FALSE);
	return false;
}

//��ʱ���¼�
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	return false;
}

//��Ϸ��Ϣ����
bool __cdecl CTableFrameSink::OnGameMessage(WORD wSubCmdID, 
											const void * pDataBuffer, 
											WORD wDataSize, 
											IServerUserItem * pIServerUserItem)
{
	bool bWatchUser = false;

	const tagServerUserData *pUserData = pIServerUserItem->GetUserData();

	if(pUserData->cbUserStatus == US_LOOKON)
	{
		bWatchUser = true;
	}

	WORD wChairID = pIServerUserItem->GetChairID();

	switch (wSubCmdID)
	{
	case SUB_C_ADD_GOLD:	//�û���ע
		{
			//У������
			tagServerUserData * pUserData = pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus != US_PLAY) return true;
			ASSERT(m_cbCardStatus[pUserData->wChairID] == INIT_CARD);
			if (m_cbCardStatus[pUserData->wChairID] != INIT_CARD) return true;

			//��ȡ����
			CMD_C_AddGold * pAddGold = (CMD_C_AddGold *)pDataBuffer;

					
			//������Ϣ
			CMD_S_AddGold  AddGoldResult;
			AddGoldResult.wPrevUser = pUserData->wChairID;
			AddGoldResult.wCurrentUser = INVALID_CHAIR;
			AddGoldResult.lMaxGold = 0;

			//У������
			ASSERT(pAddGold->lGold <= m_lMaxGold);
			if(pAddGold->lGold > m_lMaxGold) return false;

            //���ñ���
			m_cbAddCount++;
			m_lTotalAddGold += pAddGold->lGold;				

			AddGoldResult.lLastAddGold = pAddGold->lGold;
			//AddGoldResult.bDoubleGold  = false;

			m_bAddGold[pUserData->wChairID]     = true;	
			m_lUserAddGold[pUserData->wChairID] = pAddGold->lGold;
			m_lTableGold[pUserData->wChairID * 2]     = 1L;
			m_lTableGold[pUserData->wChairID * 2 + 1] = m_lUserAddGold[pUserData->wChairID] - 1L;

			//��ʶ��ע
			m_bAddGold[pUserData->wChairID] = true;	

			//��������
			const tagUserScore * pUserScore=NULL;
			IServerUserItem * pIServer=NULL;

			if(m_cbAddCount>=(m_wPlayerCount-1))m_bAddGoldEnd = true;

			//��һ���
			LONG lMaxScore=0;
			WORD wCurrentUser = pUserData->wChairID;
			do
			{
				wCurrentUser = (wCurrentUser+1)%GAME_PLAYER;	

				if(wCurrentUser==m_nBankerStation)
				{
					m_bAddGoldEnd = true;
					break;
				}

				if((m_cbCardStatus[wCurrentUser] == INIT_CARD)&&(m_bAddGold[wCurrentUser]==false))
				{
					pIServer = m_pITableFrame->GetServerUserItem(wCurrentUser);
					pUserScore = pIServer->GetUserScore();
					lMaxScore = pUserScore->lScore;
					m_bAddGoldEnd = false;
					break;
				}

			}while(true);

			//��ע��δ����
			if(m_bAddGoldEnd==false)
			{
				LONG lTmpMaxScore=0;
				pIServer = m_pITableFrame->GetServerUserItem(m_nBankerStation);
				pUserScore = pIServer->GetUserScore();

				lTmpMaxScore = (pUserScore->lScore-m_lTotalAddGold)/(m_wPlayerCount-m_cbAddCount-1);

				lMaxScore = __min(lMaxScore,lTmpMaxScore);

				AddGoldResult.wCurrentUser = wCurrentUser;
				AddGoldResult.lMaxGold = lMaxScore;

			}

			//������Ϣ
			for (WORD i = 0; i < GAME_PLAYER; i++)
			{		
				if (m_cbCardStatus[i] == INIT_CARD)
				{						
					m_pITableFrame->SendTableData(i,SUB_S_ADD_GOLD,&AddGoldResult,sizeof(AddGoldResult));
				}
				m_pITableFrame->SendLookonData(i,SUB_S_ADD_GOLD,&AddGoldResult,sizeof(AddGoldResult));
			}

				

			//��ע����
			//��ʼ����
			//if(m_bAddGoldEnd && !pAddGold->bDoubleGold)
			if(m_bAddGoldEnd)
			{
				//����״̬
				m_pITableFrame->SetGameStatus(GS_PLAYING);

				//���ñ���
				m_cbAddCount=0;
			
				//��ʼ����
				for (BYTE i = 0; i < GAME_PLAYER; i++) 
				{
					if (m_cbCardStatus[i] == INIT_CARD)
					{
						m_cbTableCardCount[i] = CARD_COUNT;
					}
				}

				//������
				WORD wDiceCount = rand()%6+1;

				//������Ϣ
				CMD_S_InitCard InitCard;

				InitCard.wDiceCount = wDiceCount;
		
				for (WORD i = 0; i < GAME_PLAYER; i++) 
				{
					for(BYTE j=0;j<CARD_COUNT;j++)
					{
						m_cbTableCardArray[i][j] = GetRandCard();
						InitCard.cbCardData[i][j]   = m_cbTableCardArray[i][j];	
					}
				}

				for (WORD i = 0; i < GAME_PLAYER; i++)
				{		
					

					if (m_cbCardStatus[i] != NO_CARD)
					{															
						InitCard.cbCardSum     = m_GameLogic.GetCardSum(m_cbTableCardArray[i],m_cbTableCardCount[i]);						

						//������Ϣ
						m_pITableFrame->SendTableData(i,SUB_S_INIT_CARD,&InitCard,sizeof(InitCard));
					}
					m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_INIT_CARD,&InitCard,sizeof(InitCard));
				}

				//��Ϸ����
				OnEventGameEnd(INVALID_CHAIR,NULL,GO_NORMAL_FINISH);
			}

			return true;
		}	

	}
	return false;
}

//�����Ϣ����
bool __cdecl CTableFrameSink::OnFrameMessage(WORD wSubCmdID, 
											 const void * pDataBuffer, 
											 WORD wDataSize, 
											 IServerUserItem * pIServerUserItem)
{
	return false;
}

//��Ϸ��ʼ
bool __cdecl CTableFrameSink::OnEventGameStart()
{
	//����״̬
	m_pITableFrame->SetGameStatus(GS_ADDGOLDING);

	//��������
	const tagUserScore * pUserScore=NULL;
	IServerUserItem * pIServerUserItem=NULL;

	//ɢ���˿�
	m_GameLogic.RandCard(m_cbRandCardArray,52);

	//����״̬	
	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		pIServerUserItem = m_pITableFrame->GetServerUserItem(i);

		if (pIServerUserItem != NULL)
		{		
			m_wPlayerCount++;

			m_cbCardStatus[i] = INIT_CARD;
		}
	}	

	//ȷ��ׯ��
	int nBankerStation=-1;
	LONG lMaxScore=0;
	for(WORD i=0;i<GAME_PLAYER;i++)
	{
		pIServerUserItem = m_pITableFrame->GetServerUserItem(i);
		if (pIServerUserItem != NULL)
		{
			pUserScore = pIServerUserItem->GetUserScore();
			if(nBankerStation<0)
			{
				nBankerStation=i;
				lMaxScore=pUserScore->lScore;
			}
			else
			{
				if(lMaxScore<pUserScore->lScore)
				{
					lMaxScore=pUserScore->lScore;
					nBankerStation=i;
				}
			}

		}

	}
	m_nBankerStation = nBankerStation;	
	
	//��һ���
	int m_wCurrentUser=m_nBankerStation;
	do
	{
		m_wCurrentUser = (m_wCurrentUser+1)%GAME_PLAYER;		

		if(m_cbCardStatus[m_wCurrentUser] == INIT_CARD)
		{
			pIServerUserItem = m_pITableFrame->GetServerUserItem(m_wCurrentUser);
			pUserScore = pIServerUserItem->GetUserScore();
			m_lMaxGold = pUserScore->lScore;
			break;
		}

	}while(true);
	
	pIServerUserItem = m_pITableFrame->GetServerUserItem(m_nBankerStation);
	pUserScore = pIServerUserItem->GetUserScore();
	m_lMaxGold = __min(m_lMaxGold,lMaxScore/(m_wPlayerCount-1));

	

	//���Ϳ�ʼ
	CMD_S_GameStart GameStart;
	memset(&GameStart,0,sizeof(GameStart));
	
	GameStart.wBankerStation  = m_nBankerStation;
	GameStart.wCurrentUser    = m_wCurrentUser;
	GameStart.lMaxGold        = m_lMaxGold;
	GameStart.lTurnBasicGold  = m_lTurnBasicGold;


	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		if (m_cbCardStatus[i] ==TRUE)
		{
			m_lTableGold[2*i] = 1L;
			m_pITableFrame->SendTableData(i,
				                          SUB_S_GAME_START,
										  &GameStart,
										  sizeof(GameStart));
		}
		m_pITableFrame->SendLookonData(i, 
			                           SUB_S_GAME_START, 
									   &GameStart, 
									   sizeof(GameStart));
	}

	

	return true;
}


//��Ϸ����
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, 
											 IServerUserItem * pIServerUserItem, 
											 BYTE cbReason)
{	
	tagScoreInfo	   ScoreInfo[GAME_PLAYER];
	memset(&ScoreInfo, 0, sizeof(ScoreInfo));

	//�������
	CMD_S_GameEnd GameEnd;
	memset(&GameEnd,0,sizeof(GameEnd));	

	LONG	lBankerScore = 0;
	LONG	lTempTax       = 0;

	switch(cbReason)
	{
	case GER_USER_LEFT:			//�û�ǿ��
		{	
			//ǿ�˴���
			if(wChairID == m_nBankerStation)
			{			
				 return OnUserLeft(m_bAddGoldEnd);			
			}
			else
			{	
				return OnUserLeft(wChairID,m_bAddGoldEnd);					
			}			
			return true;
		}				
	case GO_NORMAL_FINISH: 
		{	
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				//������Ϣ
				if ((m_cbCardStatus[i] == NO_CARD)) GameEnd.cbUserCard[i]=0;
				else GameEnd.cbUserCard[i] = m_cbTableCardArray[i][0];	

				if(m_nBankerStation == i) continue;

				//ͳ�Ƴɼ�
				if(m_cbCardStatus[i] != NO_CARD)
				{
					IServerUserItem * pIUserItem = m_pITableFrame->GetServerUserItem(i);
					ASSERT(pIUserItem != NULL);	

					LONG lGameGold = 0L, lBankerScore = 0L;
					

					BYTE cbCardStatus = m_cbCardStatus[i];
					CalcScore(cbCardStatus, i, lGameGold, lBankerScore);

					GameEnd.lGameGold[i]  = lGameGold;
					m_lBankerScore       += lBankerScore;
														
				}	
			}	

			//��������
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				GameEnd.cbCardSum[i]    = m_GameLogic.GetCardSum(m_cbTableCardArray[i],m_cbTableCardCount[i]);

				if(m_nBankerStation == i) continue;

				if(m_cbCardStatus[i] != NO_CARD)
				{
					IServerUserItem * pIUserItem = m_pITableFrame->GetServerUserItem(i);
					ASSERT(pIUserItem != NULL);		

					if(GameEnd.lGameGold[i] > 0)
					{
						GameEnd.lTax += (GameEnd.lGameGold[i] >= 100L) ? GameEnd.lGameGold[i] / 20L : 0L;
						GameEnd.lGameGold[i] -= (GameEnd.lGameGold[i] >= 100L) ? GameEnd.lGameGold[i] / 20L : 0L;
						ScoreInfo[i].ScoreKind = enScoreKind_Win;
					}
					else if(GameEnd.lGameGold[i] == 0)
					{
						ScoreInfo[i].ScoreKind = enScoreKind_Draw;
					}
					else
					{
						ScoreInfo[i].ScoreKind = enScoreKind_Lost;
					}	

					ScoreInfo[i].lScore = GameEnd.lGameGold[i];
				}
			}	

			//��Ϸ˰��
			GameEnd.lTax += (m_lBankerScore >= 100L) ? m_lBankerScore / 20L : 0L;
			GameEnd.lGameGold[m_nBankerStation]   = m_lBankerScore - ((m_lBankerScore >= 100L) ? m_lBankerScore / 20L : 0L);

			//ׯ�ҷ���
			ScoreInfo[m_nBankerStation].lScore    = GameEnd.lGameGold[m_nBankerStation];				
			if(ScoreInfo[m_nBankerStation].lScore > 0)
			{
				ScoreInfo[m_nBankerStation].ScoreKind = enScoreKind_Win;
			}
			else if(ScoreInfo[m_nBankerStation].lScore == 0)
			{
				ScoreInfo[m_nBankerStation].ScoreKind = enScoreKind_Draw;
			}
			else
			{
				ScoreInfo[m_nBankerStation].ScoreKind = enScoreKind_Lost;
			}	

			//��������
			m_bBankerWin = ScoreInfo[m_nBankerStation].lScore > 0 ? true : false;

			//������Ϣ
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//�޸ķ���
			m_pITableFrame->WriteTableScore(ScoreInfo,GAME_PLAYER,GameEnd.lTax);

			//������Ϸ
			m_pITableFrame->ConcludeGame();
			break;
		}	
	}
	return true;
}

//����ɼ�
bool CTableFrameSink::CalcScore(BYTE cbCardStatus,WORD wChairID,
								LONG &lGameGold,  LONG &lBankerScore)
{
	BYTE bWin = 0;
	//�ƶ�ʤ��
	
	BYTE cbWinnerCardType=SHAN;
	BYTE cbTimerCount=1;

	bWin = m_GameLogic.DeduceWiner(m_cbTableCardArray[m_nBankerStation],
				m_cbTableCardCount[m_nBankerStation],
				m_cbTableCardArray[wChairID],
				m_cbTableCardCount[wChairID],cbWinnerCardType);

	switch(cbWinnerCardType)
	{
	case SHAN:
		{
			cbTimerCount=1;
			break;
		}
	case SHAN8:
		{
			cbTimerCount=2;
			break;
		}
	case SanGong:
	case SanGongDui:
		{
			cbTimerCount=3;
			break;
		}
	case SanZhangGong:
		{
			cbTimerCount=5;
			break;
		}
	case SanZhangSan:
		{
			cbTimerCount=9;
			break;
		}
	default:
		break;
	}
			
	switch (bWin)
	{
			//ƽ��
		case 0:
			{
				lGameGold     = -m_lUserAddGold[wChairID];
				lBankerScore  = m_lUserAddGold[wChairID];	

				break;
			}
			//ׯ��ʤ
		case 1:
			{
				lGameGold     = -m_lUserAddGold[wChairID]*cbTimerCount;
				lBankerScore  = m_lUserAddGold[wChairID]*cbTimerCount;							

				break;
			}
			//�м�ʤ
		case 2:
			{
				lGameGold     = m_lUserAddGold[wChairID]*cbTimerCount;					
				lBankerScore  = -m_lUserAddGold[wChairID]*cbTimerCount;

				break;
			}
	}
	return true;
}


//�м�ǿ��
bool CTableFrameSink::OnUserLeft(WORD wChairID,bool bAddGoldEnd)
{
	//�������
	CMD_S_GameEnd GameEnd;
	memset(&GameEnd,0,sizeof(GameEnd));	

	m_cbCardStatus[wChairID] = NO_CARD;
	m_wPlayerCount--;

	//�жϽ���
	WORD wPlayerCount = 0;
	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		IServerUserItem * pIServerUserItem = m_pITableFrame->GetServerUserItem(i);

		if (pIServerUserItem != NULL && m_cbCardStatus[i] == INIT_CARD)
		{		
			wPlayerCount++;
		}
	}

	//�޸ķ���
	if(!m_bAddGoldEnd)	
	{
		//�޸ķ���	
		tagScoreInfo ScoreInfo;					
		ScoreInfo.ScoreKind = enScoreKind_Flee;
		ScoreInfo.lScore    = -m_lNotBankerScore[wChairID]*2;	
		m_lBankerScore      += m_lTurnBasicGold;

		m_pITableFrame->WriteUserScore(wChairID,ScoreInfo);		

	}
	else
	{
		//�޸ķ���	
		tagScoreInfo ScoreInfo;					
		ScoreInfo.ScoreKind = enScoreKind_Flee;
		ScoreInfo.lScore    = -m_lNotBankerScore[wChairID]*2;	
		m_lBankerScore      += m_lUserAddGold[wChairID];

		m_pITableFrame->WriteUserScore(wChairID,ScoreInfo);	
	}

	if(wPlayerCount >= 2)
	{
		return true;
	}
	//��ʣׯ��
	else 
	{
		tagScoreInfo	   ScoreInfo[GAME_PLAYER];
		memset(&ScoreInfo, 0, sizeof(ScoreInfo));

		LONG lTax = 0L;

		//ׯ�ҷ���		
		lTax = (m_lBankerScore >= 100L) ? m_lBankerScore / 50L : 0L;
		ScoreInfo[m_nBankerStation].lScore    = m_lBankerScore - lTax;	
		ScoreInfo[m_nBankerStation].ScoreKind = enScoreKind_Win;					

		m_pITableFrame->WriteTableScore(ScoreInfo,GAME_PLAYER,lTax);		

		for(int i = 0; i < GAME_PLAYER; i++)
		{
			if(!m_bAddGoldEnd) GameEnd.lGameGold[i] = -m_lTurnBasicGold;
			else GameEnd.lGameGold[i] = -m_lNotBankerScore[wChairID]*2;
		}

		GameEnd.lGameGold[m_nBankerStation] = ScoreInfo[m_nBankerStation].lScore;	
		GameEnd.lTax = lTax;

		//������Ϣ
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
		
		//������Ϸ
		m_pITableFrame->ConcludeGame();
	}
	return true;
}

//ׯ��ǿ��
bool CTableFrameSink::OnUserLeft(bool bAddGoldEnd)
{
	//�������
	CMD_S_GameEnd GameEnd;
	memset(&GameEnd,0,sizeof(GameEnd));		

	//�޸ķ���
	if(!m_bAddGoldEnd)
	{	
		//ׯ�ҷ���	
		tagScoreInfo ScoreInfo;					
		ScoreInfo.ScoreKind = enScoreKind_Flee;
		ScoreInfo.lScore    = -m_lMaxGold;

		m_pITableFrame->WriteUserScore(m_nBankerStation,ScoreInfo);	

		GameEnd.lGameGold[m_nBankerStation] = -m_lMaxGold;	

		//������Ϣ
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
	}
	else
	{
		tagScoreInfo	   ScoreInfo[GAME_PLAYER];
		memset(&ScoreInfo, 0, sizeof(ScoreInfo));	

		LONG lBankerScore = 0;

		for (WORD i=0;i<GAME_PLAYER;i++)
		{
			//������Ϣ
			if ((m_cbCardStatus[i] == NO_CARD)) GameEnd.cbUserCard[i]=0;
			else GameEnd.cbUserCard[i] = m_cbTableCardArray[i][0];

			if(m_nBankerStation == i) continue;

			//ͳ�Ƴɼ�
			if(m_cbCardStatus[i] != NO_CARD)
			{
				IServerUserItem * pIUserItem=m_pITableFrame->GetServerUserItem(i);
				ASSERT(pIUserItem!=NULL);					

				GameEnd.lGameGold[i] = m_lUserAddGold[i];		

				GameEnd.lTax += (GameEnd.lGameGold[i] >= 100L) ? GameEnd.lGameGold[i] / 50L : 0L;
				GameEnd.lGameGold[i] -= (GameEnd.lGameGold[i] >= 100L) ? GameEnd.lGameGold[i] / 50L : 0L;		

				lBankerScore += -m_lUserAddGold[i]*2;	

				ScoreInfo[i].lScore    = GameEnd.lGameGold[i];	
				ScoreInfo[i].ScoreKind = enScoreKind_Win;
			}					
		}	

		GameEnd.lGameGold[m_nBankerStation]   = lBankerScore;		
		ScoreInfo[m_nBankerStation].lScore    = lBankerScore;
		ScoreInfo[m_nBankerStation].ScoreKind = enScoreKind_Flee;

		//������Ϣ
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

		//�޸ķ���
		m_pITableFrame->WriteTableScore(ScoreInfo,GAME_PLAYER,GameEnd.lTax);
	}

	m_bBankerWin = false;

	//������Ϸ
	m_pITableFrame->ConcludeGame();

	return true;
}

//��ȡ�˿�
BYTE CTableFrameSink::GetRandCard()
{
	m_cbSendCardCount++;
	return 	m_cbRandCardArray[m_cbSendCardCount];
}
//////////////////////////////////////////////////////////////////////////

