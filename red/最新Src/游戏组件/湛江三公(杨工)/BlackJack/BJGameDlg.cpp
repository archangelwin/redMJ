#include "Stdafx.h"
#include "BJ.h"
#include "BJGameDlg.h"
#include "BJGameView.h"
#include "..\��Ϣ����\CMD_BlackJack.h"


//////////////////////////////////////////////////////////////////////////

//��ʱ����ʶ
#define IDI_STRAT_GAME					200								//������Ϸ��ʱ��
#define IDI_GIVE_UP						201								//������ʱ��

#define IDI_ADD_GOLD					202								//��ע��ʱ��
#define IDI_GET_CARD					203								//Ҫ�ƶ�ʱ��

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CBJGameDlg, CGameFrameDlg)
	ON_MESSAGE(IDM_GAME_START,OnStart)
	ON_MESSAGE(IDM_ADD_GOLD,OnAddGold)
	ON_MESSAGE(IDM_GIVE_UP,OnGiveUp)
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////////

//���캯��
CBJGameDlg::CBJGameDlg() : CGameFrameDlg(&m_GameView)
{	
	//��������
	m_lGoldShow    = 0L;	
	m_lTurnMaxGold = 0L;
	m_bMeAddGold   = false;
	m_wCardSum     = 0;
	m_bCutCard     = false;
	memset(m_szName, 0, sizeof(m_szName));
	return;
}

//��������
CBJGameDlg::~CBJGameDlg()
{
}

//��ʼ����
bool CBJGameDlg::InitGameFrame()
{
	//���ñ���
	SetWindowText(TEXT("տ��������Ϸ"));

	//����ͼ��
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);
	return true;
}

//���ÿ��
void CBJGameDlg::ResetGameFrame()
{	
	//��������
	m_lGoldShow    = 0L;	
	m_lTurnMaxGold = 0L;
	m_bMeAddGold   = false;
	m_wCardSum     = 0;
	memset(m_szName, 0, sizeof(m_szName));
	memset(m_GameView.m_cbPlayStatus,0,sizeof(m_GameView.m_cbPlayStatus));
	return;
}

//��Ϸ����
void CBJGameDlg::OnGameOptionSet()
{
	return;
}

//ʱ����Ϣ
bool CBJGameDlg::OnTimerMessage(WORD wChairID, UINT nElapse, UINT nTimerID)
{
	switch (nTimerID)
	{
	case IDI_ADD_GOLD:		    //��ע��ʱ��
		{
			if ((nElapse == 0)&&(wChairID==GetMeChairID()))
			{
				PlayGameSound(AfxGetInstanceHandle(),TEXT("TIME_OUT"));
				
				OnAddGold(0,0);			
				return true;
			}
			if (nElapse <= 10) PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_WARN"));

			return true;
		}	
	case IDI_STRAT_GAME:       //������Ϸ��ʱ��
		{
			if (nElapse==0)
			{
				OnStart(0,0);
				return false;
			}
			if (nElapse<=10) PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_WARN"));
			return true;
		}
	}
	return false;
}

//�Թ�״̬
void CBJGameDlg::OnLookonChanged(bool bLookonUser, const void * pBuffer, WORD wDataSize)
{

}

//��Ϸ����
bool CBJGameDlg::OnGameSceneMessage(BYTE cbGameStation, bool bLookonOther, const void * pBuffer, WORD wDataSize)
{
	switch (cbGameStation)
	{
	case GS_FREE:		//����״̬
		{		
			//Ч������
			if (wDataSize != sizeof(CMD_S_StatusFree)) return false;

			CMD_S_StatusFree * pStatusFree = (CMD_S_StatusFree *)pBuffer;

			//��������
			m_bMeAddGold = false;

			//���ý���
			m_lGoldShow      = 0L;
			m_lTurnBasicGold = 0L;
			m_GameView.SetGoldTitleInfo(0, pStatusFree->dwBasicGold);

		//	m_GameView.m_HeapCard.ResetMinusMiddleCount();
		//	m_GameView.m_HeapCard.SetCardData(0,0,10,0);

			//���ÿؼ�
			if (IsLookonMode() == false)
			{
				m_GameView.m_btBegin.ShowWindow(SW_SHOW);
				m_GameView.m_btBegin.SetFocus();
			}
			return true;
		}
	case GS_ADDGOLDING:		//��ע״̬
		{		
			//Ч������
			if (wDataSize != sizeof(CMD_S_StatusAddGold)) return false;

			CMD_S_StatusAddGold * pStatusAddGold = (CMD_S_StatusAddGold *)pBuffer;	

			for(WORD i = 0; i < GAME_PLAYER; i++)
			{
				WORD wViewChairID = SwitchViewChairID(i);			

				//��ע���
				m_GameView.SetUserGoldInfo(wViewChairID,true,pStatusAddGold->lTableGold[2 * i]);
				//m_GameView.SetUserGoldInfo(wViewChairID,false,pStatusAddGold->lTableGold[2 * i + 1]);
				
				const tagUserData * pUserData = GetUserData(i);
				if (pUserData != NULL)
				{
					lstrcpyn(m_szName[i],pUserData->szName,CountArray(m_szName[i]));
					if((IsLookonMode() == false) && (GetMeChairID() != pStatusAddGold->wBankerStation))
					{
						//��ע����
						if(!pStatusAddGold->bAddGoldEnd[GetMeChairID()])
						{
							m_GameView.m_GoldControl.SetMaxGold(pStatusAddGold->lMaxGold);
							m_GameView.m_GoldControl.ShowWindow(SW_SHOW);	
							m_GameView.m_btAddGold.ShowWindow(SW_SHOW);
							m_GameView.m_btGiveUp.ShowWindow(SW_SHOW);	
						}
						
						//���ö�ʱ��
						if(GetMeChairID() == pStatusAddGold->wCurrentUser)
						{
							SetGameTimer(GetMeChairID(), IDI_ADD_GOLD, 30);
						}						
					}
					//��ʶ״̬
					if(!pStatusAddGold->bAddGoldEnd[i] && i != pStatusAddGold->wBankerStation )
					{
						m_GameView.m_cbPlayStatus[wViewChairID] = 1;
					}		
					m_GameView.m_wBankerStation = SwitchViewChairID(pStatusAddGold->wBankerStation);
				}			
			}			
			return true;
		}

	case GS_PLAYING:	//��Ϸ״̬
		{
			//Ч������
			if (wDataSize != sizeof(CMD_S_StatusPlay)) return false;

			CMD_S_StatusPlay * pStatusPlay = (CMD_S_StatusPlay *)pBuffer;

			for(WORD i = 0; i < GAME_PLAYER; i++)
			{
				//��������
				WORD wViewChairID = SwitchViewChairID(i);
				const tagUserData * pUserData = GetUserData(i);

				if (pUserData != NULL)
				{
					lstrcpyn(m_szName[i],pUserData->szName,CountArray(m_szName[i]));			
					m_GameView.m_CardControl[wViewChairID].SetCardData(pStatusPlay->cbTableCardArray[i],pStatusPlay->cbTableCardCount[i]);

					if(i == pStatusPlay->wBankerStation) continue;				

					//ׯ�ұ�ʶ
					m_GameView.m_wBankerStation = SwitchViewChairID(pStatusPlay->wBankerStation);
				}	
				else
				{
					m_GameView.m_CardControl[wViewChairID].SetCardData(NULL,0);
				}

				//��ע���
				m_GameView.SetUserGoldInfo(wViewChairID, true,  pStatusPlay->lTableGold[2 * i]);
				//m_GameView.SetUserGoldInfo(wViewChairID, false, pStatusPlay->lTableGold[2 * i + 1]);							
			}	

			//���ÿؼ�
			m_GameView.m_CardControl[SwitchViewChairID(GetMeChairID())].ShowFirstCard(true);
			
			if (IsLookonMode() == false) 
			{
				ActiveGameFrame();
				m_GameView.m_CardControl[2].AllowPositively(true);
			}	

			m_GameView.UpdateGameView(NULL);

			return true;
		}		
	}
	return false;
}

//������Ϣ
bool CBJGameDlg::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	switch(wSubCmdID)
	{
	case SUB_S_GAME_START:           //��Ϸ��ʼ
		{
			return OnSubGameStart(pBuffer,wDataSize);
		}
	case SUB_S_ADD_GOLD:			//��ע���
		{
			return OnSubAddGold(pBuffer,wDataSize);
		}
	case SUB_S_INIT_CARD:           //��ʼ����
		{
			return OnSubInitCard(pBuffer,wDataSize);
		}	
	case SUB_S_USER_LEFT:		   //�û�ǿ��
		{						
			return OnSubUserLeft(pBuffer,wDataSize);
		}	
	case SUB_S_GAME_END:		   //��Ϸ����
		{			
			return OnSubGameEnd(pBuffer,wDataSize);
		}
	
	}
	return false;
}


//��Ϸ��ʼ
bool CBJGameDlg::OnSubGameStart(const void * pBuffer, WORD wDataSize)
{	
	//Ч������
	if (wDataSize != sizeof(CMD_S_GameStart)) return false;
	CMD_S_GameStart * pGameStart = (CMD_S_GameStart *)pBuffer;

	//��Ϸ����
	m_lTurnMaxGold   = pGameStart->lMaxGold;
	//�������
	//m_lTurnBasicGold = pGameStart->lTurnBasicGold;
	m_lTurnBasicGold = m_GameView.m_lBasicGold;
	memset(m_szName, 0, sizeof(m_szName));

	//��������
	WORD wMeChairID  = GetMeChairID();
	bool bLookonMode = IsLookonMode();
	LONG lBaseGold   = m_lTurnBasicGold;

	//����״̬
	SetGameStatus(GS_ADDGOLDING);
	m_GameView.SetGoldTitleInfo(pGameStart->lMaxGold,lBaseGold);
	//m_GameView.m_HeapCard.SetCardData(0,0,10,0);

	//���ý���
	m_GameView.m_wBankerStation = SwitchViewChairID(pGameStart->wBankerStation);	
	
	//���ÿ���
	if (bLookonMode == false && wMeChairID == pGameStart->wCurrentUser)
	{
		//���ý���
		m_GameView.m_btGiveUp.ShowWindow(SW_SHOW);
		m_GameView.m_btAddGold.ShowWindow(SW_SHOW);
		
		//m_GameView.SetUserGoldInfo(2, false, m_lTurnBasicGold);
		m_GameView.SetUserGoldInfo(2, true, m_lTurnBasicGold);
		m_GameView.m_GoldControl.SetMaxGold(pGameStart->lMaxGold - m_lTurnBasicGold);
		m_GameView.m_GoldControl.ShowWindow(SW_SHOW);

		//���ö�ʱ��	
		SetGameTimer(GetMeChairID(), IDI_ADD_GOLD, 30);		
	}

	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		//��������
		WORD wViewChairID = SwitchViewChairID(i);
		const tagUserData * pUserData = GetUserData(i);

		//���ý���
		if (pUserData != NULL)
		{
			m_GameView.SetUserGoldInfo(wViewChairID,false,0L);
			m_GameView.SetUserGoldInfo(wViewChairID,true,lBaseGold);
			lstrcpyn(m_szName[i],pUserData->szName,CountArray(m_szName[i]));			
			if(wViewChairID != m_GameView.m_wBankerStation)
				m_GameView.m_cbPlayStatus[wViewChairID] = 1;
		}
		else
		{	
			m_GameView.SetUserGoldInfo(wViewChairID,true,0L);
			m_GameView.SetUserGoldInfo(wViewChairID,false,0L);	
		}

	}
	if (bLookonMode == false) 
	{
		ActiveGameFrame();
		m_GameView.m_CardControl[2].AllowPositively(true);
	}	
	else
	{	
		//���ý���			
		m_GameView.m_ScoreView.ShowWindow(SW_HIDE);	
		for (int i=0;i<CountArray(m_GameView.m_CardControl);i++) m_GameView.m_CardControl[i].SetCardData(NULL,0);
		memset(m_GameView.m_cbTopCardSum,0,sizeof(m_GameView.m_cbTopCardSum));
		memset(m_GameView.m_cbCardType,0,sizeof(m_GameView.m_cbCardType));
		memset(m_GameView.m_cbBottomCardSum,0,sizeof(m_GameView.m_cbBottomCardSum));

	}
	m_GameView.UpdateGameView(NULL);
	
	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_BEGIN"));

	return true;
}

//��ʼ����
bool CBJGameDlg::OnSubInitCard(const void * pBuffer, WORD wDataSize)
{
	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("SEND_CARD"));

	//Ч������
	if (wDataSize != sizeof(CMD_S_InitCard)) return false;
	CMD_S_InitCard * pInitCard = (CMD_S_InitCard *)pBuffer;
	
	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		//��������
		WORD wViewChairID = SwitchViewChairID(i);
		const tagUserData * pUserData = GetUserData(i);

		//���ý���
		if (pUserData != NULL)
		{
			m_GameView.m_CardControl[wViewChairID].SetCardData(pInitCard->cbCardData[i],CARD_COUNT);	

			//��ʶ״̬
			if(wViewChairID != m_GameView.m_wBankerStation)
				m_GameView.m_cbPlayStatus[wViewChairID] = 2;
		}
		else
		{
			m_GameView.m_CardControl[wViewChairID].SetCardData(NULL,0);
		}		

		//���ÿؼ�
		m_GameView.m_CardControl[wViewChairID].ShowFirstCard(true);
	}

	//��������
	//WORD wDiceCount = pInitCard->wDiceCount;
	//for(WORD i=wDiceCount;i<wDiceCount+4;i++)
		//m_GameView.m_HeapCard.SetCardData(0,0,10,i);	

	//��ʾ�˿���ֵ
	m_GameView.m_cbTopCardSum[2] = pInitCard->cbCardSum;
	m_GameView.UpdateGameView(NULL);

	return true;
}

//�û���ע
bool CBJGameDlg::OnSubAddGold(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	if (wDataSize != sizeof(CMD_S_AddGold)) return false;
	CMD_S_AddGold * pAddGold = (CMD_S_AddGold *)pBuffer;	

	//��������
	WORD wMeChairID   = GetMeChairID();
	WORD wViewChairID = SwitchViewChairID(pAddGold->wPrevUser);

	//��������
	//m_GameView.SetUserGoldInfo(wViewChairID,false,pAddGold->lLastAddGold);

	m_GameView.SetUserGoldInfo(wViewChairID,true,pAddGold->lLastAddGold);

	if ((IsLookonMode() == false)&&(pAddGold->wPrevUser == wMeChairID))
	{
		//��������
		m_bMeAddGold = true;	
		
		PlayGameSound(AfxGetInstanceHandle(),TEXT("ADD_SCORE"));
		
		ActiveGameFrame();
	}

	if(pAddGold->wCurrentUser!=INVALID_CHAIR)
	{
		if ((IsLookonMode() == false)&&(pAddGold->wCurrentUser == wMeChairID))
		{
			//���ý���
			m_GameView.m_btGiveUp.ShowWindow(SW_SHOW);
			m_GameView.m_btAddGold.ShowWindow(SW_SHOW);
			
			//m_GameView.SetUserGoldInfo(2, false, m_lTurnBasicGold);
			m_GameView.SetUserGoldInfo(2, true, m_lTurnBasicGold);
			m_GameView.m_GoldControl.SetMaxGold(pAddGold->lMaxGold - m_lTurnBasicGold);
			m_GameView.m_GoldControl.ShowWindow(SW_SHOW);

			//���ö�ʱ��	
			SetGameTimer(GetMeChairID(), IDI_ADD_GOLD, 30);	

		}

	}
	else 
	{
		//����״̬
		SetGameStatus(GS_PLAYING);
	}


	//��ʶ״̬
	if(wViewChairID != m_GameView.m_wBankerStation)
		m_GameView.m_cbPlayStatus[wViewChairID] = 0;
	m_GameView.UpdateGameView(NULL);

	return true;
}

//�û�ǿ��
bool CBJGameDlg::OnSubUserLeft(const void * pBuffer, WORD wDataSize)
{
	return true;
}

//��Ϸ����
bool CBJGameDlg::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
{	
	//���ö�ʱ��
	KillGameTimer(IDI_GET_CARD);

	//Ч�����
	if (wDataSize != sizeof(CMD_S_GameEnd)) return false;
	CMD_S_GameEnd * pGameEnd = (CMD_S_GameEnd *)pBuffer;
    
	//��Ϸ��������
	BYTE cbCardData[13];
	m_GameView.m_ScoreView.ResetScore();

	for (WORD i = 0; i < GAME_PLAYER; i++)
	{
		//������Ϣ
		const tagUserData * pUserData = GetUserData(i);

		if (pUserData != NULL)
		{
			lstrcpyn(m_szName[i],pUserData->szName,CountArray(m_szName[i]));
		}
		
		if (m_szName[i][0] != 0) 
		{

			if(i==pGameEnd->wBankerUser)strcat(m_szName[i],TEXT("(ׯ��)"));
			m_GameView.m_ScoreView.SetGameScore(i,m_szName[i],pGameEnd->lGameGold[i]);

			if (pGameEnd->cbUserCard[i] != 0)
			{
				WORD wViewStation = SwitchViewChairID(i);
				WORD wCardCount = m_GameView.m_CardControl[wViewStation].GetCardData(cbCardData,CountArray(cbCardData));
				cbCardData[0] = pGameEnd->cbUserCard[i];
				m_GameView.m_CardControl[wViewStation].SetCardData(cbCardData,wCardCount);
				m_GameView.m_CardControl[wViewStation].SortCardData();
				m_GameView.m_CardControl[wViewStation].ShowFirstCard(true);	

				/*wCardCount = m_GameView.m_CardControl[wViewStation+4].GetCardData(cbCardData,CountArray(cbCardData));
				cbCardData[0] = pGameEnd->cbCutCard[i];
				m_GameView.m_CardControl[wViewStation+4].SetCardData(cbCardData,wCardCount);
				m_GameView.m_CardControl[wViewStation+4].SortCardData();
				m_GameView.m_CardControl[wViewStation+4].ShowFirstCard(true);	*/	
				
				//��ʾ��ֵ
				m_GameView.m_cbTopCardSum[wViewStation]    = pGameEnd->cbCardSum[i];
				m_GameView.m_cbCardType[wViewStation]  =pGameEnd->cbCardType[i];
				//m_GameView.m_cbBottomCardSum[wViewStation] = pGameEnd->cbCutCardSum[i];
			}			
		}			
	}
	m_GameView.m_ScoreView.SetTax(pGameEnd->lTax);
	m_GameView.m_ScoreView.ShowWindow(SW_SHOW);	

	//��Ϸ����
	m_lTurnMaxGold   = 0L;
	m_lTurnBasicGold = 0L;

	//�������
	m_lGoldShow  = 0L;	
	m_GameView.m_wBankerStation = 255;
	m_GameView.m_cbCutCardMark  = 0;
	memset(m_szName,0,sizeof(m_szName));
	memset(m_GameView.m_cbPlayStatus,0,sizeof(m_GameView.m_cbPlayStatus));

	//��ʶ����
	m_bCutCard = false;

	//���ý���
	if (IsLookonMode() == false)
	{
		m_GameView.m_btBegin.ShowWindow(SW_SHOW);
		m_GameView.m_btBegin.SetFocus();
		SetGameTimer(GetMeChairID(),IDI_STRAT_GAME,30);
	}
	
	m_GameView.m_GoldControl.ShowWindow(SW_HIDE);
	m_GameView.m_btGiveUp.ShowWindow(SW_HIDE);
	m_GameView.m_btAddGold.ShowWindow(SW_HIDE);
	
	m_GameView.UpdateGameView(NULL);

	//����״̬
	SetGameStatus(GS_FREE);

	//��������
	if(pGameEnd->lGameGold[GetMeChairID()] > 0)
		PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_WIN"));
	else
		PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_END"));	

	return true;
}

//��Ϸ��ʼ
LRESULT	CBJGameDlg::OnStart(WPARAM wParam, LPARAM lParam)
{
	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("HIT_BUTTON"));
	
	//���ý���	
	m_GameView.m_btBegin.ShowWindow(SW_HIDE);
	m_GameView.m_ScoreView.ShowWindow(SW_HIDE);	
	for (int i=0;i<CountArray(m_GameView.m_CardControl);i++) m_GameView.m_CardControl[i].SetCardData(NULL,0);
	memset(m_GameView.m_cbTopCardSum,0,sizeof(m_GameView.m_cbTopCardSum));
	memset(m_GameView.m_cbCardType,0,sizeof(m_GameView.m_cbCardType));
	memset(m_GameView.m_cbBottomCardSum,0,sizeof(m_GameView.m_cbBottomCardSum));
	memset(m_GameView.m_cbPlayStatus,0,sizeof(m_GameView.m_cbPlayStatus));
	//m_GameView.m_HeapCard.ResetMinusMiddleCount();
	//m_GameView.m_HeapCard.SetCardData(0,0,10,0);
	

	KillGameTimer(IDI_STRAT_GAME);

	//������Ϣ
    SendUserReady(NULL,0);

	return true;
}

//�û���ע
LRESULT	CBJGameDlg::OnAddGold(WPARAM wParam, LPARAM lParam)
{	
	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("ADD_SCORE"));
	
	LONG lGold =  m_GameView.m_GoldView[5].GetGold() + m_GameView.m_GoldControl.GetGold();

	//LONG lGold = m_lTurnBasicGold;

	lGold = __max(lGold,1);

	//������Ϣ
	CMD_C_AddGold AddPoint;
	//AddPoint.bDoubleGold = false;
	AddPoint.lGold       = lGold;
	AddPoint.wChairID    = GetMeChairID();

	SendData(SUB_C_ADD_GOLD,&AddPoint,sizeof(AddPoint));

	//���ö�ʱ��
	KillGameTimer(IDI_ADD_GOLD);	

	//���½���
	m_GameView.m_GoldControl.ShowWindow(SW_HIDE);
	m_GameView.m_btGiveUp.ShowWindow(SW_HIDE);
	m_GameView.m_btAddGold.ShowWindow(SW_HIDE);
	m_GameView.UpdateGameView(NULL);

	return 0;
}

//�û�ȡ��
LRESULT	CBJGameDlg::OnGiveUp(WPARAM wParam, LPARAM lParam)
{
	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("HIT_BUTTON"));

	CMD_C_AddGold AddPoint;
	AddPoint.lGold       = 1L;
	//AddPoint.bDoubleGold = false;
	AddPoint.wChairID    = GetMeChairID();

	//���ö�ʱ��
	KillGameTimer(IDI_ADD_GOLD);
	
	//���ý���
	m_GameView.m_GoldControl.ShowWindow(SW_HIDE);
	m_GameView.m_btGiveUp.ShowWindow(SW_HIDE);
	m_GameView.m_btAddGold.ShowWindow(SW_HIDE);
    
	//��������
	SendData(SUB_C_ADD_GOLD,&AddPoint,sizeof(AddPoint));

	return true;
}