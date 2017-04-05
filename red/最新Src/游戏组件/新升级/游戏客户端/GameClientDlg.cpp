#include "Stdafx.h"
#include "GameOption.h"
#include "GameClientDlg.h"

//////////////////////////////////////////////////////////////////////////

//ʱ���ʶ
#define IDI_OUT_CARD					200								//���ƶ�ʱ��
#define IDI_CALL_CARD					201								//���ƶ�ʱ��
#define IDI_START_GAME					202								//��ʼ��ʱ��
#define IDI_SEND_CONCEAL				203								//���ƶ�ʱ��
#define IDI_RERANDCARD					204								//��ϴ��ʱ��
#define IDI_OPEN_CONCEAL				205								//���׶�ʱ��

//ʱ�䷶Χ
#define TIME_OUT_CARD					30								//����ʱ��
#define TIME_CALL_CARD					10								//����ʱ��
#define TIME_START_GAME					30								//��ʼʱ��
#define TIME_SEND_CONCEAL				40								//����ʱ��
#define TIME_OPEN_CONCEAL				5								//����ʱ��


//���ܶ�ʱ��
#define IDI_CONCEAL_CARD				300								//���ƶ�ʱ��
#define IDI_DISPATCH_CARD				301								//���ƶ�ʱ��
#define IDI_LAST_TURN_CARD				302								//���ֶ�ʱ��
#define IDI_THROW_CARD_RESULT			303								//˦�ƶ�ʱ��

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameClientDlg, CGameFrameDlg)
	ON_WM_TIMER()
	ON_MESSAGE(IDM_START,OnStart)
	ON_MESSAGE(IDM_OUT_CARD,OnOutCard)
	ON_MESSAGE(IDM_CALL_CARD,OnCallCard)
	ON_MESSAGE(IDM_OUT_PROMPT,OnOutPrompt)
	ON_MESSAGE(IDM_SEND_CONCEAL,OnSendConceal)
	ON_MESSAGE(IDM_CONCEAL_CARD,OnConcealCard)
	ON_MESSAGE(IDM_REQUEST_LEAVE,OnRuquestLeave)
	ON_MESSAGE(IDM_LAST_TURN_CARD,OnLastTurnCard)
	ON_MESSAGE(IDM_TRUSTEE_CONTROL,OnStusteeControl)
	ON_MESSAGE(IDM_LEFT_HIT_CARD,OnLeftHitCard)
	ON_MESSAGE(IDM_RIGHT_HIT_CARD,OnRightHitCard)
	ON_MESSAGE(IDM_RERANDCARD,OnReRandCard)
	ON_MESSAGE(IDM_OPENCONCEALCARD,OnOpenConcealCard)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameClientDlg::CGameClientDlg() : CGameFrameDlg(&m_GameClientView)
{
	//�߼�����
	m_cbPackCount=0;
	m_cbMainColor=COLOR_ERROR;
	m_cbMainValue=VALUE_ERROR;

	//������Ϣ
	m_cbCallCard=0;
	m_cbCallCount=0;
	m_wCallCardUser=INVALID_CHAIR;

	//״̬����
	m_wBankerUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	
	//�÷���Ϣ
	m_cbScoreCardCount=0;
	ZeroMemory(m_cbScoreCardData,sizeof(m_cbScoreCardData));

	//˦�Ʊ���
	m_bThrowCard=false;
	m_cbResultCardCount=0;
	m_wThrowCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbResultCardData,sizeof(m_cbResultCardData));

	//���Ʊ���
	m_bLastTurn=false;
	m_wFirstOutUser=INVALID_CHAIR;
	ZeroMemory(m_cbOutCardData,sizeof(m_cbOutCardData));
	ZeroMemory(m_cbOutCardCount,sizeof(m_cbOutCardCount));

	//�����˿�
	m_cbConcealCount=0;
	ZeroMemory(m_cbConcealCard,sizeof(m_cbConcealCard));

	//�û��˿�
	m_cbHandCardCount=0;
	ZeroMemory(m_cbHandCardData,sizeof(m_cbHandCardData));

	//���ñ���
	m_bStustee=false;
	m_bDeasilOrder=false;
	m_dwCardHSpace=DEFAULT_PELS;

	//���ױ���
	m_bOpenConcealFlag = false;

	//��������
	m_cbRemnantCardCount=0;
	m_cbDispatchCardCount=0;
	ZeroMemory(m_cbDispatchCardData,sizeof(m_cbDispatchCardData));

	//��ʾ����
	m_GameClientView.m_btReRandCard.ShowWindow(SW_HIDE);
	m_GameClientView.m_btGiveUp.ShowWindow(SW_HIDE);
	m_GameClientView.m_btOpenConcealCard.ShowWindow(SW_HIDE);

	return;
}

//��������
CGameClientDlg::~CGameClientDlg()
{
}

//��ʼ����
bool CGameClientDlg::InitGameFrame()
{
	//���ñ���
	SetWindowText(TEXT("��������Ϸ"));

	//����ͼ��
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	//��ȡ����
	m_dwCardHSpace=AfxGetApp()->GetProfileInt(TEXT("GameOption"),TEXT("CardSpace"),DEFAULT_PELS);
	m_bDeasilOrder=AfxGetApp()->GetProfileInt(TEXT("GameOption"),TEXT("DeasilOrder"),FALSE)?true:false;

	//��������
	if ((m_dwCardHSpace>MAX_PELS)||(m_dwCardHSpace<LESS_PELS)) m_dwCardHSpace=DEFAULT_PELS;

	//���ÿؼ�
	m_GameClientView.SetUserOrder(m_bDeasilOrder);
	m_GameClientView.m_HandCardControl.SetCardSpace(m_dwCardHSpace,0,DEF_CARD_SHOOT);

	return true;
}

//���ÿ��
void CGameClientDlg::ResetGameFrame()
{
	//�߼�����
	m_cbPackCount=0;
	m_cbMainColor=COLOR_ERROR;
	m_cbMainValue=VALUE_ERROR;

	//������Ϣ
	m_cbCallCard=0;
	m_cbCallCount=0;
	m_wCallCardUser=INVALID_CHAIR;

	//״̬����
	m_wBankerUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	
	//�÷���Ϣ
	m_cbScoreCardCount=0;
	ZeroMemory(m_cbScoreCardData,sizeof(m_cbScoreCardData));

	//˦�Ʊ���
	m_bThrowCard=false;
	m_cbResultCardCount=0;
	m_wThrowCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbResultCardData,sizeof(m_cbResultCardData));

	//���Ʊ���
	m_bLastTurn=false;
	m_wFirstOutUser=INVALID_CHAIR;
	ZeroMemory(m_cbOutCardData,sizeof(m_cbOutCardData));
	ZeroMemory(m_cbOutCardCount,sizeof(m_cbOutCardCount));

	//�����˿�
	m_cbConcealCount=0;
	ZeroMemory(m_cbConcealCard,sizeof(m_cbConcealCard));

	//�û��˿�
	m_cbHandCardCount=0;
	ZeroMemory(m_cbHandCardData,sizeof(m_cbHandCardData));

	//���ױ���
	m_bOpenConcealFlag = false;

	//���ñ���
	m_bStustee=false;

	//��������
	m_cbRemnantCardCount=0;
	m_cbDispatchCardCount=0;
	ZeroMemory(m_cbDispatchCardData,sizeof(m_cbDispatchCardData));

	//ɾ����ʱ��
	KillTimer(IDI_CONCEAL_CARD);
	KillTimer(IDI_DISPATCH_CARD);
	KillTimer(IDI_LAST_TURN_CARD);
	KillTimer(IDI_THROW_CARD_RESULT);

	//��ʾ����
	m_GameClientView.m_btReRandCard.ShowWindow(SW_HIDE);
	m_GameClientView.m_btGiveUp.ShowWindow(SW_HIDE);
	m_GameClientView.m_btOpenConcealCard.ShowWindow(SW_HIDE);

	return;
}

//��Ϸ����
void CGameClientDlg::OnGameOptionSet()
{
	//��������
	CGameOption GameOption;
	GameOption.m_dwCardHSpace=m_dwCardHSpace;
	GameOption.m_bEnableSound=IsEnableSound();
	GameOption.m_bDeasilOrder=m_GameClientView.IsDeasilOrder();

	//��������
	if (GameOption.DoModal()==IDOK)
	{
		//��ȡ����
		m_bDeasilOrder=GameOption.m_bDeasilOrder;
		m_dwCardHSpace=GameOption.m_dwCardHSpace;

		//���ÿؼ�
		EnableSound(GameOption.m_bEnableSound);
		m_GameClientView.SetUserOrder(GameOption.m_bDeasilOrder);
		m_GameClientView.m_HandCardControl.SetCardSpace(m_dwCardHSpace,0,20);

		//��������
		AfxGetApp()->WriteProfileInt(TEXT("GameOption"),TEXT("CardSpace"),m_dwCardHSpace);
		AfxGetApp()->WriteProfileInt(TEXT("GameOption"),TEXT("DeasilOrder"),m_bDeasilOrder?TRUE:FALSE);
	}

	return;
}

//ʱ����Ϣ
bool CGameClientDlg::OnTimerMessage(WORD wChairID, UINT nElapse, UINT nTimerID)
{
	switch (nTimerID)
	{
	case IDI_OUT_CARD:			//�û�����
		{
			//��ʱ�ж�
			if ((nElapse==0)||((m_bStustee==true)&&(nElapse<(TIME_OUT_CARD))))
			{
				if ((IsLookonMode()==false)&&(wChairID==GetMeChairID())) AutomatismOutCard();
				return true;
			}

			//��������
			if ((nElapse<=3)&&(wChairID==GetMeChairID())&&(IsLookonMode()==false)) PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_WARN"));

			return true;
		}
	case IDI_CALL_CARD:			//�û�����
		{
			//��ʱ�ж�
			//if ((nElapse==0)||((m_bStustee==true)&&(nElapse<(TIME_CALL_CARD))))
			if(nElapse==0)
			{
				//���ؿؼ�
				m_GameClientView.m_CallCardWnd.ShowWindow(SW_HIDE);
				m_GameClientView.m_CallCardWnd.UpdateCallControl(CALL_NONE);

				//������Ϣ
				if (IsLookonMode()==false) SendData(SUB_C_CALL_FINISH);

				return true;
			}

			return true;
		}
	case IDI_START_GAME:		//��ʼ��Ϸ
		{
			if ((nElapse==0)||((m_bStustee==true)&&(nElapse<(TIME_START_GAME))))
			{
				if ((IsLookonMode()==false)&&(wChairID==GetMeChairID())) OnStart(0,0);
				return true;
			}
			if ((nElapse<=3)&&(wChairID==GetMeChairID())&&(IsLookonMode()==false)) PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_WARN"));

			return true;
		}
	case IDI_SEND_CONCEAL:		//���͵���
		{
			if ((nElapse==0)||((m_bStustee==true)&&(nElapse<(TIME_SEND_CONCEAL))))
			{
				//�Զ�����
				if ((IsLookonMode()==false)&&(wChairID==GetMeChairID()))
				{
					//ɾ����ʱ��
					KillGameTimer(IDI_SEND_CONCEAL);

					//ɾ���˿�
					m_cbHandCardCount-=m_cbConcealCount;
					m_GameLogic.RemoveCard(m_cbConcealCard,m_cbConcealCount,m_cbHandCardData,m_cbHandCardCount+m_cbConcealCount);

					//���ý���
					m_GameClientView.m_btSendConceal.ShowWindow(SW_HIDE);
					m_GameClientView.m_btSendConceal.EnableWindow(FALSE);
					SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);

					//��������
					CMD_C_ConcealCard ConcealCard;
					ConcealCard.cbConcealCount=m_cbConcealCount;
					CopyMemory(ConcealCard.cbConcealCard,m_cbConcealCard,m_cbConcealCount*sizeof(BYTE));

					//��������
					SendData(SUB_C_CONCEAL_CARD,&ConcealCard,sizeof(ConcealCard));

					//��ʾ��Ϣ
					if (m_bStustee==false) InsertSystemString(TEXT("�޶���ʱ�䵽�ˣ�ϵͳΪ���Զ������"));

					return false;
				}

				return true;
			}
			if ((nElapse<=3)&&(wChairID==GetMeChairID())&&(IsLookonMode()==false)) PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_WARN"));

			return true;
		}
	case IDI_OPEN_CONCEAL:
		{
			if(((nElapse==0)||(m_bStustee==true))&&(wChairID==GetMeChairID())&&(IsLookonMode()==false))
			{
				OnOpenConcealCard(0,0);			
				return true;			
			}
			return true;
		}
	}

	return false;
}

//�Թ�״̬
void CGameClientDlg::OnLookonChanged(bool bLookonUser, const void * pBuffer, WORD wDataSize)
{
	//�˿˿���
	m_GameClientView.m_HandCardControl.SetDisplayFlag((IsAllowLookon()==true));

	//���ܰ�ť
	m_GameClientView.m_btConcealCard.EnableWindow(((m_cbConcealCount>0)&&((IsLookonMode()==false)||(IsAllowLookon()==true)))?TRUE:FALSE);

	return;
}

//������Ϣ
bool CGameClientDlg::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//��Ϸ��ʼ
		{
			return OnSubGameStart(pBuffer,wDataSize);
		}
	case SUB_S_SEND_CARD:		//�����˿�
		{
			return OnSubSendCard(pBuffer,wDataSize);
		}
	case SUB_S_CALL_CARD:		//�û�����
		{
			return OnSubCallCard(pBuffer,wDataSize);
		}
	case SUB_S_SEND_CONCEAL:	//���͵���
		{
			return OnSubSendConceal(pBuffer,wDataSize);
		}
	case SUB_S_GAME_PLAY:		//��Ϸ��ʼ
		{
			return OnSubGamePlay(pBuffer,wDataSize);
		}
	case SUB_S_OUT_CARD:		//�û�����
		{
			return OnSubOutCard(pBuffer,wDataSize);
		}
	case SUB_S_THROW_RESULT:	//˦�ƽ��
		{
			return OnSubThrowResult(pBuffer,wDataSize);
		}
	case SUB_S_TURN_BALANCE:	//һ�ֽ���
		{
			return OnSubTurnBalance(pBuffer,wDataSize);
		}
	case SUB_S_GAME_END:		//��Ϸ����
		{
			return OnSubGameEnd(pBuffer,wDataSize);
		}
	case SUB_S_RERANDCARD:     //����ϴ��
		{
			return OnSubReRandCard();
		}
	case SUB_S_REQUIR_OPEN:    //�Ƿ񳴵�
		{
			return OnSubRequirOpen(pBuffer,wDataSize);
		}
	}

	return true;
}

//��Ϸ����
bool CGameClientDlg::OnGameSceneMessage(BYTE cbGameStation, bool bLookonOther, const void * pBuffer, WORD wDataSize)
{
	switch (cbGameStation)
	{
	case GS_UG_FREE:	//����״̬
		{
			//Ч������
			if (wDataSize!=sizeof(CMD_S_StatusFree)) return false;
			CMD_S_StatusFree * pStatusFree=(CMD_S_StatusFree *)pBuffer;

			//���ÿؼ�
			if (IsLookonMode()==false)
			{
				m_GameClientView.m_btStart.ShowWindow(TRUE);
				m_GameClientView.m_btStart.SetFocus();
			}

			//�������
			if (IsLookonMode()==false)
			{
				m_GameClientView.m_btStusteeControl.EnableWindow(TRUE);
				m_GameClientView.m_HandCardControl.SetDisplayFlag(true);
			}

			return true;
		}
	case GS_UG_CALL:	//����״̬
		{
			//Ч������
			if (wDataSize!=sizeof(CMD_S_StatusCall)) return false;
			CMD_S_StatusCall * pStatusCall=(CMD_S_StatusCall *)pBuffer;

			//�߼�����
			m_cbPackCount=pStatusCall->cbPackCount;
			m_cbMainValue=pStatusCall->cbMainValue;
			m_wBankerUser=pStatusCall->wBankerUser;

			//������Ϣ
			m_cbCallCard=pStatusCall->cbCallCard;
			m_cbCallCount=pStatusCall->cbCallCount;
			m_wCallCardUser=pStatusCall->wCallCardUser;

			//�����˿�
			m_cbHandCardCount=pStatusCall->cbCardCount;
			CopyMemory(m_cbHandCardData,pStatusCall->cbCardData,sizeof(BYTE)*m_cbHandCardCount);

			//�߼����
			m_GameLogic.SetPackCount(m_cbPackCount);
			m_GameLogic.SetMainColor(m_cbMainColor);
			m_GameLogic.SetMainValue(m_cbMainValue);

			//������Ϣ
			WORD wMeChairID=GetMeChairID();
			BYTE cbValueMySelf=pStatusCall->cbValueOrder[wMeChairID%2];
			BYTE cbValueOther=pStatusCall->cbValueOrder[(wMeChairID+1)%2];
			m_GameClientView.SetValueOrder(m_cbMainValue,cbValueMySelf,cbValueOther);

			//������Ϣ
			if (m_wCallCardUser!=INVALID_CHAIR)
			{
				WORD wViewChairID=SwitchViewChairID(m_wCallCardUser);
				BYTE cbCallColor=m_GameLogic.GetCardColor(m_cbCallCard);
				m_GameClientView.SetCallCardInfo(wViewChairID,cbCallColor,m_cbCallCount);
			}

			//���ƽ���
			BYTE cbCallCard[2];
			WORD wViewChairID=SwitchViewChairID(m_wCallCardUser);
			for (BYTE i=0;i<m_cbCallCount;i++) cbCallCard[i]=m_cbCallCard;
			m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(cbCallCard,m_cbCallCount);

			//����ׯ��
			if (m_wBankerUser!=INVALID_CHAIR) m_GameClientView.SetBankerUser(SwitchViewChairID(m_wBankerUser));

			//�������
			if (IsLookonMode()==false) 
			{
				m_GameClientView.m_btStusteeControl.EnableWindow(TRUE);
				m_GameClientView.m_HandCardControl.SetDisplayFlag(true);
			}

			//�˿�����
			if (pStatusCall->cbComplete==FALSE)
			{
				//��������
				m_GameClientView.m_CallCardWnd.ShowWindow(SW_SHOW);
				m_GameClientView.m_CallCardWnd.UpdateCallControl(CALL_NONE);

				//�ɷ��˿�
				DispatchUserCard(m_cbHandCardData,m_cbHandCardCount);

				//���ÿؼ�
				m_GameClientView.m_btReRandCard.ShowWindow(SW_HIDE);
				m_GameClientView.m_btReRandCard.EnableWindow(FALSE);
				
			}
			else
			{
				

				//�����˿�
				m_GameLogic.SortCardList(m_cbHandCardData,m_cbHandCardCount);

				//�����˿�
				SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);

				//�м����
				WORD wTotalScore=0;

				//�������
				wTotalScore=m_GameLogic.GetCardTotalScore(m_cbHandCardData,m_cbHandCardCount);

				if((wTotalScore<MIN_SCORE)&&(m_bStustee==false))
				{
					//���ÿؼ�
					m_GameClientView.m_btReRandCard.ShowWindow(SW_SHOW);
					m_GameClientView.m_btReRandCard.EnableWindow(TRUE);
					

					//�趨��ʱ��
					SetTimer(IDI_RERANDCARD,5000,0);
				}
			}

			return true;
		}
	case GS_UG_BACK:	//����״̬
		{
			//Ч������
			if (wDataSize!=sizeof(CMD_S_StatusBack)) return false;
			CMD_S_StatusBack * pStatusBack=(CMD_S_StatusBack *)pBuffer;

			//�߼�����
			m_cbPackCount=pStatusBack->cbPackCount;
			m_cbMainColor=pStatusBack->cbMainColor;
			m_cbMainValue=pStatusBack->cbMainValue;

			//������Ϣ
			m_cbCallCard=pStatusBack->cbCallCard;
			m_cbCallCount=pStatusBack->cbCallCount;
			m_wCallCardUser=pStatusBack->wCallCardUser;

			//�û�����
			m_wBankerUser=pStatusBack->wBankerUser;
			m_wCurrentUser=pStatusBack->wCurrentUser;
			m_wCallCardUser=pStatusBack->wCallCardUser;

			//�߼����
			m_GameLogic.SetPackCount(m_cbPackCount);
			m_GameLogic.SetMainColor(m_cbMainColor);
			m_GameLogic.SetMainValue(m_cbMainValue);

			//���õ���
			m_cbConcealCount=pStatusBack->cbConcealCount;
			CopyMemory(m_cbConcealCard,pStatusBack->cbConcealCard,m_cbConcealCount*sizeof(BYTE));

			//�����˿�
			m_cbHandCardCount=pStatusBack->cbCardCount;
			CopyMemory(m_cbHandCardData,pStatusBack->cbCardData,sizeof(BYTE)*m_cbHandCardCount);

			//������Ϣ
			WORD wMeChairID=GetMeChairID();
			BYTE cbValueMySelf=pStatusBack->cbValueOrder[wMeChairID%2];
			BYTE cbValueOther=pStatusBack->cbValueOrder[(wMeChairID+1)%2];
			m_GameClientView.SetValueOrder(m_cbMainValue,cbValueMySelf,cbValueOther);

			//������Ϣ
			if (m_wCallCardUser!=INVALID_CHAIR)
			{
				WORD wViewChairID=SwitchViewChairID(m_wCallCardUser);
				BYTE cbCallColor=m_GameLogic.GetCardColor(m_cbCallCard);
				m_GameClientView.SetCallCardInfo(wViewChairID,cbCallColor,m_cbCallCount);
			}

			//�����˿�
			m_GameLogic.SortCardList(m_cbHandCardData,m_cbHandCardCount);

			//��������
			SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);
			m_GameClientView.SetBankerUser(SwitchViewChairID(m_wBankerUser));

			//�������
			if (IsLookonMode()==false) 
			{
				//�˿�����
				m_GameClientView.m_btStusteeControl.EnableWindow(TRUE);
				m_GameClientView.m_HandCardControl.SetDisplayFlag(true);

				//��������
				if (m_wCurrentUser==GetMeChairID())
				{
					m_GameClientView.m_btSendConceal.EnableWindow(TRUE);
					m_GameClientView.m_btSendConceal.ShowWindow(SW_SHOW);
					m_GameClientView.m_HandCardControl.SetPositively(true);
					m_GameClientView.m_HandCardControl.SetShootCard(m_cbConcealCard,m_cbConcealCount);
				}
				else m_GameClientView.SetWaitConceal(true);
			}
			else m_GameClientView.SetWaitConceal(true);

			//ʱ������
			SetGameTimer(m_wCurrentUser,IDI_SEND_CONCEAL,TIME_SEND_CONCEAL);

			return true;
		}
	case GS_UG_PLAY:	//��Ϸ״̬
		{
			//Ч������
			if (wDataSize!=sizeof(CMD_S_StatusPlay)) return false;
			CMD_S_StatusPlay * pStatusPlay=(CMD_S_StatusPlay *)pBuffer;

			//�߼�����
			m_cbPackCount=pStatusPlay->cbPackCount;
			m_cbMainColor=pStatusPlay->cbMainColor;
			m_cbMainValue=pStatusPlay->cbMainValue;

			//������Ϣ
			m_cbCallCard=pStatusPlay->cbCallCard;
			m_cbCallCount=pStatusPlay->cbCallCount;
			m_wCallCardUser=pStatusPlay->wCallCardUser;

			//�û�����
			m_wBankerUser=pStatusPlay->wBankerUser;
			m_wCurrentUser=pStatusPlay->wCurrentUser;
			m_wFirstOutUser=pStatusPlay->wFirstOutUser;

			//�߼����
			m_GameLogic.SetPackCount(m_cbPackCount);
			m_GameLogic.SetMainColor(m_cbMainColor);
			m_GameLogic.SetMainValue(m_cbMainValue);

			//���õ���
			m_cbConcealCount=pStatusPlay->cbConcealCount;
			CopyMemory(m_cbConcealCard,pStatusPlay->cbConcealCard,m_cbConcealCount*sizeof(BYTE));

			//�����˿�
			m_cbHandCardCount=pStatusPlay->cbCardCount;
			CopyMemory(m_cbHandCardData,pStatusPlay->cbCardData,sizeof(BYTE)*m_cbHandCardCount);

			//���Ʊ���
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				m_cbOutCardCount[i][0]=pStatusPlay->cbOutCardCount[i];
				CopyMemory(m_cbOutCardData[i][0],pStatusPlay->cbOutCardData[i],sizeof(BYTE)*m_cbOutCardCount[i][0]);
			}

			//�÷���Ϣ
			m_cbScoreCardCount=pStatusPlay->cbScoreCardCount;
			CopyMemory(m_cbScoreCardData,pStatusPlay->cbScoreCardData,sizeof(BYTE)*m_cbScoreCardCount);

			//������Ϣ
			WORD wMeChairID=GetMeChairID();
			BYTE cbValueMySelf=pStatusPlay->cbValueOrder[wMeChairID%2];
			BYTE cbValueOther=pStatusPlay->cbValueOrder[(wMeChairID+1)%2];
			m_GameClientView.SetValueOrder(m_cbMainValue,cbValueMySelf,cbValueOther);

			//������Ϣ
			if (m_wCallCardUser!=INVALID_CHAIR)
			{
				WORD wViewChairID=SwitchViewChairID(m_wCallCardUser);
				BYTE cbCallColor=m_GameLogic.GetCardColor(m_cbCallCard);
				m_GameClientView.SetCallCardInfo(wViewChairID,cbCallColor,m_cbCallCount);
			}

			//�÷���ͼ
			m_GameClientView.m_CardScore.SetCardData(m_cbScoreCardData,m_cbScoreCardCount);
			m_GameClientView.SetCardScore(m_GameLogic.GetCardScore(m_cbScoreCardData,m_cbScoreCardCount));

			//���ƽ���
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				WORD wViewChairID=SwitchViewChairID(i);
				m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(m_cbOutCardData[i][0],m_cbOutCardCount[i][0]);
			}

			//�����˿�
			m_GameLogic.SortCardList(m_cbHandCardData,m_cbHandCardCount);

			//��������
			SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);
			m_GameClientView.SetBankerUser(SwitchViewChairID(m_wBankerUser));

			//�������
			if (IsLookonMode()==false) 
			{
				m_GameClientView.m_btStusteeControl.EnableWindow(TRUE);
				m_GameClientView.m_HandCardControl.SetPositively(true);
				m_GameClientView.m_HandCardControl.SetDisplayFlag(true);
			}

			//�Թ�����
			if (IsAllowLookon()==true) m_GameClientView.m_HandCardControl.SetDisplayFlag(true);

			//��������
			if ((IsLookonMode()==false)&&(m_wCurrentUser==GetMeChairID()))
			{
				m_GameClientView.m_btOutCard.ShowWindow(SW_SHOW);
				m_GameClientView.m_btOutPrompt.ShowWindow(SW_SHOW);
				m_GameClientView.m_btOutCard.EnableWindow((VerdictOutCard()==true)?TRUE:FALSE);
			}

			//���ܰ�ť
			m_GameClientView.m_btConcealCard.EnableWindow(((m_cbConcealCount>0)&&((IsLookonMode()==false)||(IsAllowLookon()==true)))?TRUE:FALSE);

			//ʱ������
			SetGameTimer(m_wCurrentUser,IDI_OUT_CARD,TIME_OUT_CARD);

			return true;
		}
	}

	return false;
}

//��Ϸ��ʼ
bool CGameClientDlg::OnSubGameStart(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_GameStart));
	if (wDataSize!=sizeof(CMD_S_GameStart)) return false;

	//��Ϣ����
	CMD_S_GameStart * pGameStart=(CMD_S_GameStart *)pBuffer;

	//����״̬
	SetGameStatus(GS_UG_CALL);

	//�߼�����
	m_cbMainColor=COLOR_ERROR;
	m_cbMainValue=pGameStart->cbMainValue;
	m_cbPackCount=pGameStart->cbPackCount;

	//���Ʊ���
	m_cbCallCard=0;
	m_cbCallCount=0;
	m_wCallCardUser=INVALID_CHAIR;

	//���Ʊ���
	m_cbConcealCount=0;
	ZeroMemory(m_cbConcealCard,sizeof(m_cbConcealCard));

	//״̬����
	m_wCurrentUser=INVALID_CHAIR;
	m_wBankerUser=pGameStart->wBankerUser;

	//�÷���Ϣ
	m_cbScoreCardCount=0;
	ZeroMemory(m_cbScoreCardData,sizeof(m_cbScoreCardData));

	//���Ʊ���
	m_wFirstOutUser=INVALID_CHAIR;
	ZeroMemory(m_cbOutCardData,sizeof(m_cbOutCardData));
	ZeroMemory(m_cbOutCardCount,sizeof(m_cbOutCardCount));

	//�߼����
	m_GameLogic.SetPackCount(m_cbPackCount);
	m_GameLogic.SetMainColor(m_cbMainColor);
	m_GameLogic.SetMainValue(m_cbMainValue);

	//��������
	m_GameClientView.SetCardScore(0xFFFF);
	m_GameClientView.m_CardScore.SetCardData(NULL,0);
	m_GameClientView.SetCallCardInfo(INVALID_CHAIR,COLOR_ERROR,0);
	m_GameClientView.SetPutConcealUser(INVALID_CHAIR);

	//���ƿ���
	m_GameClientView.m_btConcealCard.EnableWindow(FALSE);
	m_GameClientView.m_ConcealCardView.ShowWindow(SW_HIDE);
	m_GameClientView.m_ConcealCardView.SetConcealCard(NULL,0);

	//������Ϣ
	WORD wMeChairID=GetMeChairID();
	BYTE cbValueMySelf=pGameStart->cbValueOrder[wMeChairID%2];
	BYTE cbValueOther=pGameStart->cbValueOrder[(wMeChairID+1)%2];
	m_GameClientView.SetValueOrder(m_cbMainValue,cbValueMySelf,cbValueOther);

	//����ׯ��
	if (m_wBankerUser==INVALID_CHAIR) m_GameClientView.SetBankerUser(INVALID_CHAIR);
	else m_GameClientView.SetBankerUser(SwitchViewChairID(m_wBankerUser));

	//���ý���
	if (IsLookonMode()==true)
	{
		SetHandCardControl(NULL,0);
		m_GameClientView.SetWaitConceal(false);
		m_GameClientView.m_ScoreView.ShowWindow(SW_HIDE);
		m_GameClientView.m_CardScore.SetCardData(NULL,0);
		m_GameClientView.m_UserCardControl[0].SetCardData(NULL,0);
		m_GameClientView.m_UserCardControl[1].SetCardData(NULL,0);
		m_GameClientView.m_UserCardControl[2].SetCardData(NULL,0);
		m_GameClientView.m_UserCardControl[3].SetCardData(NULL,0);
	}

	//��������
	bool bPlayerMode=(IsLookonMode()==false);
	m_GameClientView.m_HandCardControl.SetDisplayFlag(bPlayerMode);
	if ((IsLookonMode()==false)&&(m_bStustee==false)) ActiveGameFrame();

	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_START2"));

	return true;
}

//�����˿�
bool CGameClientDlg::OnSubSendCard(const void * pBuffer, WORD wDataSize)
{
	//��������
	CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pBuffer;
	WORD wFirstSize=sizeof(CMD_S_SendCard)-sizeof(pSendCard->cbCardData);

	//Ч������
	ASSERT(wDataSize>=wFirstSize);
	if (wDataSize<wFirstSize) return false;
	ASSERT(wDataSize==(wFirstSize+pSendCard->cbCardCount*sizeof(BYTE)));
	if (wDataSize!=(wFirstSize+pSendCard->cbCardCount*sizeof(BYTE))) return false;

	//�����˿�
	m_cbHandCardCount=pSendCard->cbCardCount;
	CopyMemory(m_cbHandCardData,pSendCard->cbCardData,sizeof(BYTE)*m_cbHandCardCount);

	//���¿���
	m_GameClientView.m_CallCardWnd.ShowWindow(SW_SHOW);
	m_GameClientView.m_CallCardWnd.UpdateCallControl(CALL_NONE);

	//�ɷ��˿�
	DispatchUserCard(m_cbHandCardData,m_cbHandCardCount);

	//��������
	if ((IsLookonMode()==false)&&(m_bStustee==false)) ActiveGameFrame();

	return true;
}

//�û�����
bool CGameClientDlg::OnSubCallCard(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_CallCard));
	if (wDataSize!=sizeof(CMD_S_CallCard)) return false;

	//��Ϣ����
	CMD_S_CallCard * pCallCard=(CMD_S_CallCard *)pBuffer;

	//�������
	if ((m_wCallCardUser!=INVALID_CHAIR)&&(m_wCallCardUser!=pCallCard->wCallCardUser))
	{
		WORD wViewChairID=SwitchViewChairID(m_wCallCardUser);
		m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(NULL,0);
	}

	//���ñ���
	m_cbCallCard=pCallCard->cbCallCard;
	m_cbCallCount=pCallCard->cbCallCount;
	m_wCallCardUser=pCallCard->wCallCardUser;

	//���ƽ���
	BYTE cbCallCard[2];
	WORD wViewChairID=SwitchViewChairID(m_wCallCardUser);
	if(GetMeChairID()==m_wCallCardUser)
	{
		for (BYTE i=0;i<m_cbCallCount;i++) cbCallCard[i]=m_cbCallCard;
		m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(cbCallCard,m_cbCallCount);
	}
	else
	{
		for (BYTE i=0;i<m_cbCallCount;i++) cbCallCard[i]=0x00;
		m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(cbCallCard,m_cbCallCount);
	}
	

	//BYTE cbCallCard[2];
	//WORD wViewChairID=SwitchViewChairID(m_wCallCardUser);
	//	
	//for (BYTE i=0;i<m_cbCallCount;i++) cbCallCard[i]=m_cbCallCard;
	//m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(cbCallCard,m_cbCallCount);

	//��ͼ��Ϣ
	if(GetMeChairID()==m_wCallCardUser)
	{
		BYTE cbCallColor=m_GameLogic.GetCardColor(m_cbCallCard);
		m_GameClientView.SetCallCardInfo(wViewChairID,cbCallColor,m_cbCallCount);	
	}
	else
		m_GameClientView.SetCallCardInfo(wViewChairID,COLOR_ERROR,1);	
	//BYTE cbCallColor=m_GameLogic.GetCardColor(m_cbCallCard);
	//m_GameClientView.SetCallCardInfo(wViewChairID,cbCallColor,m_cbCallCount);

	//��������
	PlayGameSound(AfxGetInstanceHandle(),TEXT("CALL_CARD"));

	//���¿���
	UpdateCallCardControl();

	return true;
}

//���͵���
bool CGameClientDlg::OnSubSendConceal(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_SendConceal));
	if (wDataSize!=sizeof(CMD_S_SendConceal)) return false;

	//��Ϣ����
	CMD_S_SendConceal * pSendConceal=(CMD_S_SendConceal *)pBuffer;

	//���ñ���
	m_cbMainColor=pSendConceal->cbMainColor;
	m_wBankerUser=pSendConceal->wBankerUser;
	m_wCurrentUser=pSendConceal->wCurrentUser;

	//״̬����
	SetGameStatus(GS_UG_BACK);
	m_GameLogic.SetMainColor(m_cbMainColor);
	m_GameClientView.SetBankerUser(SwitchViewChairID(m_wBankerUser));

	//��������
	if (m_wCallCardUser!=INVALID_CHAIR)
	{
		WORD wViewChairID=SwitchViewChairID(m_wCallCardUser);
		m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(NULL,0);
	}


	//�˿�����
	if (m_wCurrentUser==GetMeChairID())
	{
		//���õ���
		m_cbConcealCount=pSendConceal->cbConcealCount;
		CopyMemory(m_cbConcealCard,pSendConceal->cbConcealCard,m_cbConcealCount*sizeof(BYTE));

		//�����˿�
		CopyMemory(&m_cbHandCardData[m_cbHandCardCount],m_cbConcealCard,m_cbConcealCount*sizeof(BYTE));
		m_cbHandCardCount+=m_cbConcealCount;

		//�����˿�
		m_GameLogic.SortCardList(m_cbHandCardData,m_cbHandCardCount);
		SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);

		//���ÿ���
		if (IsLookonMode()==false) 
		{
			//������
			if (m_bStustee==false) ActiveGameFrame();

			//���ÿؼ�
			m_GameClientView.m_btSendConceal.EnableWindow(TRUE);
			m_GameClientView.m_btSendConceal.ShowWindow(SW_SHOW);
			m_GameClientView.m_HandCardControl.SetPositively(true);
			m_GameClientView.m_HandCardControl.SetShootCard(m_cbConcealCard,m_cbConcealCount);
		}
		else 
		{
			//������ʾ
			m_GameClientView.SetWaitConceal(true);
		}
	}
	else
	{
		//������ʾ
		m_GameClientView.SetWaitConceal(true);

		//�����˿�
		m_GameLogic.SortCardList(m_cbHandCardData,m_cbHandCardCount);
		SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);
	}

	//��������
	SetGameTimer(m_wCurrentUser,IDI_SEND_CONCEAL,TIME_SEND_CONCEAL);

	return true;
}

//��Ϸ��ʼ
bool CGameClientDlg::OnSubGamePlay(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_GamePlay));
	if (wDataSize!=sizeof(CMD_S_GamePlay)) return false;

	//��Ϣ����
	CMD_S_GamePlay * pGamePlay=(CMD_S_GamePlay *)pBuffer;

	//���ñ���
	m_wCallCardUser = pGamePlay->wCallCardUser;
	m_cbCallCard = pGamePlay->cbCallCard;
	m_cbCallCount = pGamePlay->cbCallCount;	
	m_wCurrentUser=pGamePlay->wCurrentUser;
	m_wFirstOutUser=pGamePlay->wCurrentUser;
	m_cbConcealCount=pGamePlay->cbConcealCount;
	CopyMemory(m_cbConcealCard,pGamePlay->cbConcealCard,m_cbConcealCount*sizeof(BYTE));

	//��������
	if ((IsLookonMode()==true)&&(m_cbConcealCount!=0))	
	{
		//ɾ���˿�
		m_cbHandCardCount-=m_cbConcealCount;
		m_GameLogic.RemoveCard(m_cbConcealCard,m_cbConcealCount,m_cbHandCardData,m_cbHandCardCount+m_cbConcealCount);

		//�����˿�
		SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);
	}

	//���õ���
	m_GameClientView.m_ConcealCardView.SetConcealCard(m_cbConcealCard,m_cbConcealCount);
	m_GameClientView.m_btConcealCard.EnableWindow(((m_cbConcealCount!=0)&&((IsLookonMode()==false)||(IsAllowLookon()==true)))?TRUE:FALSE);


	//���ý���
	m_GameClientView.SetBankerUser(SwitchViewChairID(m_wBankerUser));
	m_GameClientView.SetCallCardInfo(SwitchViewChairID(m_wCallCardUser),m_GameLogic.GetCardColor(m_cbCallCard),m_cbCallCount);
	m_GameClientView.SetPutConcealUser(SwitchViewChairID(pGamePlay->wPutConcaelUser));

	//����״̬
	SetGameStatus(GS_UG_PLAY);
	m_GameClientView.SetCardScore(0);
	m_GameClientView.SetWaitConceal(false);

	//��������
	bool bPlayerMode=(IsLookonMode()==false);
	m_GameClientView.m_HandCardControl.SetPositively(bPlayerMode);

	//��ǰ���
	if ((IsLookonMode()==false)&&(m_wCurrentUser==GetMeChairID()))
	{
		if (m_bStustee==false) ActiveGameFrame();
		m_GameClientView.m_btOutCard.ShowWindow(SW_SHOW);
		m_GameClientView.m_btOutCard.EnableWindow(FALSE);
		m_GameClientView.m_btOutPrompt.ShowWindow(SW_SHOW);
	}

	//��������
	SetGameTimer(m_wCurrentUser,IDI_OUT_CARD,TIME_OUT_CARD);
	PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_START"));

	return true;
}

//�û�����
bool CGameClientDlg::OnSubOutCard(const void * pBuffer, WORD wDataSize)
{
	//��������
	CMD_S_OutCard * pOutCard=(CMD_S_OutCard *)pBuffer;
	WORD wFirstSize=sizeof(CMD_S_OutCard)-sizeof(pOutCard->cbCardData);

	//Ч������
	ASSERT(wDataSize>=wFirstSize);
	if (wDataSize<wFirstSize) return false;
	ASSERT(wDataSize==(wFirstSize+pOutCard->cbCardCount*sizeof(BYTE)));
	if (wDataSize!=(wFirstSize+pOutCard->cbCardCount*sizeof(BYTE))) return false;

	//��������
	WORD wMeChairID=GetMeChairID();
	WORD wOutCardUser=pOutCard->wOutCardUser;
	WORD wOutViewChairID=SwitchViewChairID(wOutCardUser);

	//���ƴ���
	SwitchToThrowResult();
	KillGameTimer(IDI_OUT_CARD);

	//�˿˽���
	if ((IsLookonMode()==true)||(wMeChairID!=wOutCardUser))
	{
		//��ʷ�˿�
		if (wOutCardUser==m_wFirstOutUser)
		{
			for (WORD i=0;i<GAME_PLAYER;i++) 
			{
				if (i==wOutCardUser) continue;
				m_GameClientView.m_UserCardControl[SwitchViewChairID(i)].SetCardData(NULL,0);
			}
		}

		//���ƽ���
		m_GameClientView.m_UserCardControl[wOutViewChairID].SetCardData(pOutCard->cbCardData,pOutCard->cbCardCount);
	}

	//��ʷ�˿�
	if ((wOutCardUser==m_wFirstOutUser)&&(m_cbOutCardCount[m_wFirstOutUser][0]!=0))
	{
		//�����˿�
		for (WORD i=0;i<GAME_PLAYER;i++) 
		{
			//�����˿�
			m_cbOutCardCount[i][1]=m_cbOutCardCount[i][0];
			CopyMemory(m_cbOutCardData[i][1],m_cbOutCardData[i][0],sizeof(BYTE)*m_cbOutCardCount[i][0]);

			//�����˿�
			m_cbOutCardCount[i][0]=0;
			ZeroMemory(m_cbOutCardData[i][0],sizeof(m_cbOutCardData[i][0]));
		}

		//���ư�ť
		m_GameClientView.m_btLastTurnCard.EnableWindow(TRUE);
	}

	//���Ƽ�¼
	m_cbOutCardCount[wOutCardUser][0]=pOutCard->cbCardCount;
	CopyMemory(m_cbOutCardData[wOutCardUser][0],pOutCard->cbCardData,pOutCard->cbCardCount*sizeof(BYTE));

	//��ǰ����
	SwitchToCurrentCard();

	//����˿�
	if ((IsLookonMode()==true)&&(wOutCardUser==wMeChairID))
	{
		//ɾ���˿� 
		BYTE cbSourceCount=m_cbHandCardCount;
		m_cbHandCardCount-=pOutCard->cbCardCount;
		m_GameLogic.RemoveCard(pOutCard->cbCardData,pOutCard->cbCardCount,m_cbHandCardData,cbSourceCount);

		//�����˿�
		SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);
	}

	BYTE m_bTurnOutType=m_GameLogic.GetCardType(pOutCard->cbCardData,pOutCard->cbCardCount);

	//��������
	//if ((IsLookonMode()==true)||(wMeChairID!=wOutCardUser)) PlayGameSound(AfxGetInstanceHandle(),TEXT("OUT_CARD"));


	WORD wChairID=SwitchViewChairID(pOutCard->wOutCardUser);
	const tagUserData * pUserData=m_GameClientView.GetUserInfo(wChairID);


	if(m_bTurnOutType==CT_SINGLE) PlayGameSound(AfxGetInstanceHandle(),TEXT("OUT_CARD"));
	else if(m_bTurnOutType==CT_TRACKOR_2)
	{
		if(pUserData->cbGender==0)
			PlayGameSound(AfxGetInstanceHandle(),TEXT("M_TUOLAJI"));
		else
			PlayGameSound(AfxGetInstanceHandle(),TEXT("W_TUOLAJI"));
	}
	else if(m_bTurnOutType==CT_TRACKOR_3)
	{
		if(pUserData->cbGender==0)
			PlayGameSound(AfxGetInstanceHandle(),TEXT("M_TUOLAJI"));
		else
			PlayGameSound(AfxGetInstanceHandle(),TEXT("W_TUOLAJI"));
	}
	else if(m_bTurnOutType==CT_TRACKOR_4)
	{
		if(pUserData->cbGender==0)
			PlayGameSound(AfxGetInstanceHandle(),TEXT("M_TUOLAJI"));
		else
			PlayGameSound(AfxGetInstanceHandle(),TEXT("W_TUOLAJI"));
	}
	else
	{
		PlayGameSound(AfxGetInstanceHandle(),TEXT("OUT_CARD"));
	}

	//���ñ���
	m_wCurrentUser=pOutCard->wCurrentUser;

	//�������
	if ((IsLookonMode()==false)&&(m_wCurrentUser==wMeChairID))
	{
		if (m_bStustee==false) ActiveGameFrame();
		m_GameClientView.m_btOutCard.ShowWindow(SW_SHOW);
		m_GameClientView.m_btOutPrompt.ShowWindow(SW_SHOW);
		m_GameClientView.m_btOutCard.EnableWindow((VerdictOutCard()==true)?TRUE:FALSE);
	}

	//����ʱ��
	if (m_wCurrentUser!=INVALID_CHAIR) SetGameTimer(m_wCurrentUser,IDI_OUT_CARD,TIME_OUT_CARD);

	return true;
}

//˦�ƽ��
bool CGameClientDlg::OnSubThrowResult(const void * pBuffer, WORD wDataSize)
{
	//��������
	CMD_S_ThrowResult * pThrowResult=(CMD_S_ThrowResult *)pBuffer;
	WORD wCardCount=pThrowResult->cbThrowCardCount+pThrowResult->cbResultCardCount;
	WORD wFirstSize=sizeof(CMD_S_ThrowResult)-sizeof(pThrowResult->cbCardDataArray);

	//Ч������
	ASSERT(wDataSize>=wFirstSize);
	if (wDataSize<wFirstSize) return false;
	ASSERT(wDataSize==(wFirstSize+wCardCount*sizeof(BYTE)));
	if (wDataSize!=(wFirstSize+wCardCount*sizeof(BYTE))) return false;

	//��������
	WORD wMeChairID=GetMeChairID();
	WORD wOutCardUser=pThrowResult->wOutCardUser;
	WORD wOutViewChairID=SwitchViewChairID(wOutCardUser);

	//�˿˱���
	BYTE cbThrowCardCount=pThrowResult->cbThrowCardCount;
	BYTE cbResultCardCount=pThrowResult->cbResultCardCount;
	BYTE * pcbThrowCardData=&pThrowResult->cbCardDataArray[0];
	BYTE * pcbResultCardData=&pThrowResult->cbCardDataArray[pThrowResult->cbThrowCardCount];

	//��ԭ����
	SwitchToCurrentCard();

	//���ƴ���
	KillGameTimer(IDI_OUT_CARD);
	PlayGameSound(AfxGetInstanceHandle(),TEXT("THROW_RESULT"));

	//�����˿�
	for (WORD i=0;i<GAME_PLAYER;i++) 
	{
		//�����˿�
		if (i!=wOutCardUser) m_GameClientView.m_UserCardControl[SwitchViewChairID(i)].SetCardData(NULL,0);
	}

	//��ʷ�˿�
	if (m_cbOutCardCount[m_wFirstOutUser][0]!=0)
	{
		//�����˿�
		for (WORD i=0;i<GAME_PLAYER;i++) 
		{
			//�����˿�
			m_cbOutCardCount[i][1]=m_cbOutCardCount[i][0];
			CopyMemory(m_cbOutCardData[i][1],m_cbOutCardData[i][0],sizeof(BYTE)*m_cbOutCardCount[i][0]);

			//�����˿�
			m_cbOutCardCount[i][0]=0;
			ZeroMemory(m_cbOutCardData[i][0],sizeof(m_cbOutCardData[i][0]));
		}
	}

	//���ƽ���
	m_GameClientView.m_UserCardControl[wOutViewChairID].SetCardData(pcbThrowCardData,cbThrowCardCount);

	//���Ƽ�¼
	m_cbOutCardCount[wOutCardUser][0]=cbResultCardCount;
	CopyMemory(m_cbOutCardData[wOutCardUser][0],pcbResultCardData,cbResultCardCount*sizeof(BYTE));

	//����˿�
	if (wOutCardUser==wMeChairID)
	{
		//��˿�
		if (IsLookonMode()==false)
		{
			//�����˿�
			BYTE cbSourceCount=m_cbHandCardCount;
			m_cbHandCardCount+=cbThrowCardCount;
			CopyMemory(&m_cbHandCardData[cbSourceCount],pcbThrowCardData,sizeof(BYTE)*cbThrowCardCount);

			//�����˿�
			m_GameLogic.SortCardList(m_cbHandCardData,m_cbHandCardCount);
		}

		//ɾ���˿�
		BYTE cbSourceCount=m_cbHandCardCount;
		m_cbHandCardCount-=cbResultCardCount;
		m_GameLogic.RemoveCard(pcbResultCardData,cbResultCardCount,m_cbHandCardData,cbSourceCount);

		//���ý���
		SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);
	}

	//���ñ���
	m_bThrowCard=true;
	m_cbResultCardCount=cbResultCardCount;
	m_wCurrentUser=pThrowResult->wCurrentUser;
	m_wThrowCardUser=pThrowResult->wOutCardUser;
	CopyMemory(m_cbResultCardData,pcbResultCardData,sizeof(BYTE)*cbResultCardCount);

	//����ʱ��
	SetTimer(IDI_THROW_CARD_RESULT,2000,NULL);

	//��������
	m_GameClientView.m_btLastTurnCard.EnableWindow(FALSE);

	return true;
}

//һ�ֽ���
bool CGameClientDlg::OnSubTurnBalance(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_TurnBalance));
	if (wDataSize!=sizeof(CMD_TurnBalance)) return false;

	//��Ϣ����
	CMD_TurnBalance * pTurnBalance=(CMD_TurnBalance *)pBuffer;

	//����÷�
	WORD wWinnerUser=pTurnBalance->wTurnWinner;
	if ((wWinnerUser!=m_wBankerUser)&&((wWinnerUser+2)%GAME_PLAYER!=m_wBankerUser))
	{
		//��ȡ����
		for (WORD i=0;i<GAME_PLAYER;i++)
		{
			BYTE * pcbScoreCard=&m_cbScoreCardData[m_cbScoreCardCount];
			BYTE cbMaxCount=CountArray(m_cbScoreCardData)-m_cbScoreCardCount;
			m_cbScoreCardCount+=m_GameLogic.GetScoreCard(m_cbOutCardData[i][0],m_cbOutCardCount[i][0],pcbScoreCard,cbMaxCount);
		}

		//���ý���
		m_GameClientView.m_CardScore.SetCardData(m_cbScoreCardData,m_cbScoreCardCount);
		m_GameClientView.SetCardScore(m_GameLogic.GetCardScore(m_cbScoreCardData,m_cbScoreCardCount));
	}

	//�����û�
	m_wCurrentUser=pTurnBalance->wCurrentUser;
	m_wFirstOutUser=pTurnBalance->wCurrentUser;

	//�������
	if ((IsLookonMode()==false)&&(m_wCurrentUser==GetMeChairID()))
	{
		if (m_bStustee==false) ActiveGameFrame();
		m_GameClientView.m_btOutCard.ShowWindow(SW_SHOW);
		m_GameClientView.m_btOutPrompt.ShowWindow(SW_SHOW);
		m_GameClientView.m_btOutCard.EnableWindow((VerdictOutCard()==true)?TRUE:FALSE);
	}

	//����ʱ��
	if (m_wCurrentUser!=INVALID_CHAIR) SetGameTimer(m_wCurrentUser,IDI_OUT_CARD,TIME_OUT_CARD);

	return true;
}

//��Ϸ����
bool CGameClientDlg::OnSubGameEnd(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_GameEnd));
	if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;

	//��Ϣ����
	CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;

	//��Ϸ��ʱ��
	KillGameTimer(IDI_OUT_CARD);
	KillGameTimer(IDI_CALL_CARD);
	KillGameTimer(IDI_SEND_CONCEAL);

	//���ܶ�ʱ��
	KillTimer(IDI_CONCEAL_CARD);
	KillTimer(IDI_DISPATCH_CARD);
	KillTimer(IDI_LAST_TURN_CARD);
	KillTimer(IDI_THROW_CARD_RESULT);

	//���ؿؼ�
	m_GameClientView.m_btOutCard.ShowWindow(SW_HIDE);
	m_GameClientView.m_CallCardWnd.ShowWindow(SW_HIDE);
	m_GameClientView.m_btOutPrompt.ShowWindow(SW_HIDE);
	m_GameClientView.m_btSendConceal.ShowWindow(SW_HIDE);
	m_GameClientView.m_btSendConceal.EnableWindow(FALSE);
	m_GameClientView.m_CallCardWnd.ShowWindow(SW_HIDE);

	//���ƽ���
	m_GameClientView.m_btConcealCard.EnableWindow(FALSE);
	m_GameClientView.m_btLastTurnCard.EnableWindow(FALSE);
	m_GameClientView.m_ConcealCardView.ShowWindow(SW_HIDE);
	m_GameClientView.m_ConcealCardView.SetConcealCard(NULL,0);

	//���ÿؼ�
	SwitchToCurrentCard();
	SwitchToThrowResult();
	m_GameClientView.SetWaitConceal(false);
	m_GameClientView.m_btOutCard.EnableWindow(FALSE);

	//���ý���
	tagScoreViewInfo ScoreViewInfo;
	ScoreViewInfo.wGameScore=pGameEnd->wGameScore;
	ScoreViewInfo.wConcealTime=pGameEnd->wConcealTime;
	ScoreViewInfo.wConcealScore=pGameEnd->wConcealScore;
	ScoreViewInfo.cbConcealCount=pGameEnd->cbConcealCount;
	CopyMemory(ScoreViewInfo.cbConcealCard,pGameEnd->cbConcealCard,sizeof(BYTE)*pGameEnd->cbConcealCount);
	m_GameClientView.m_ScoreView.SetScoreViewInfo(ScoreViewInfo);

	//���û���
	WORD wEndChairID;
	wEndChairID=-1;
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		const tagUserData * pUserData=GetUserData(i);
		m_GameClientView.m_ScoreView.SetGameScore(i,pUserData->szName,pGameEnd->lScore[i]);
		if(pGameEnd->lScore[i]<0L)	wEndChairID = SwitchViewChairID(i);
	}

	//��ʾ�ɼ�
	m_GameClientView.m_ScoreView.ShowWindow(SW_SHOW);

	//��������
	WORD wMeChairID=GetMeChairID();
	LONG lMeScore=pGameEnd->lScore[GetMeChairID()];
	if (lMeScore>0L)
	{
		DWORD meID;
		meID = SwitchViewChairID(GetMeChairID());
		const tagUserData * pUserDataMe=m_GameClientView.GetUserInfo(meID);
		if(pUserDataMe->cbGender==0)
			PlayGameSound(AfxGetInstanceHandle(),TEXT("PM_WIN"));
		else
			PlayGameSound(AfxGetInstanceHandle(),TEXT("DZ_WIN"));		
	}
	else if (lMeScore<0L) PlayGameSound(AfxGetInstanceHandle(),TEXT("GAME_LOST"));
	else
	{
		if(wEndChairID!=65535)
		{
			const tagUserData * pUserData=m_GameClientView.GetUserInfo(wEndChairID);
			if(pUserData->cbGender==0)
				PlayGameSound(AfxGetInstanceHandle(),TEXT("MTAOPAO"));
			else
				PlayGameSound(AfxGetInstanceHandle(),TEXT("WTAOPAO"));
		}
		else
		{
			PlayGameSound(GetModuleHandle(NULL),TEXT("GAME_END"));
		}

	}

	//���ý���
	if (IsLookonMode()==false)
	{
		m_GameClientView.m_btStart.ShowWindow(SW_SHOW);
		SetGameTimer(GetMeChairID(),IDI_START_GAME,TIME_START_GAME);
	}

	return true;
}

//����ϴ��
bool CGameClientDlg::OnSubReRandCard()
{	

	//��Ϸ��ʱ��
	KillGameTimer(IDI_CALL_CARD);


	//���ý���
	m_GameClientView.SetCardScore(0xFFFF);
	m_GameClientView.SetWaitConceal(false);

	//����ׯ��
	if (m_wBankerUser==INVALID_CHAIR) m_GameClientView.SetBankerUser(INVALID_CHAIR);
	else m_GameClientView.SetBankerUser(SwitchViewChairID(m_wBankerUser));

	m_GameClientView.SetCallCardInfo(INVALID_CHAIR,COLOR_ERROR,0);
	m_GameClientView.SetPutConcealUser(INVALID_CHAIR);

	//���ؿؼ�
	m_GameClientView.m_btStart.ShowWindow(FALSE);
	m_GameClientView.m_ScoreView.ShowWindow(SW_HIDE);

	//���ƿ���
	m_GameClientView.m_btConcealCard.EnableWindow(FALSE);
	m_GameClientView.m_ConcealCardView.ShowWindow(SW_HIDE);
	m_GameClientView.m_ConcealCardView.SetConcealCard(NULL,0);

	//�����˿�
	SetHandCardControl(NULL,0);
	m_GameClientView.m_CardScore.SetCardData(NULL,0);
	m_GameClientView.m_HandCardControl.SetPositively(false);
	for (WORD i=0;i<GAME_PLAYER;i++) m_GameClientView.m_UserCardControl[i].SetCardData(NULL,0);

	return true;
}

//�Ƿ񳴵�
bool CGameClientDlg::OnSubRequirOpen(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(sizeof(CMD_S_RequirOpen)==wDataSize);
	if(sizeof(CMD_S_RequirOpen)!=wDataSize)return false;

	//ת������
	CMD_S_RequirOpen * pRequirOpen = (CMD_S_RequirOpen *)pBuffer;   

	if(GetMeChairID()==pRequirOpen->wChairID)
	{
		//���ÿؼ�
		m_GameClientView.m_btOpenConcealCard.ShowWindow(SW_SHOW);
		m_GameClientView.m_btGiveUp.ShowWindow(SW_SHOW);
		m_GameClientView.m_btOpenConcealCard.EnableWindow(TRUE);		
		m_GameClientView.m_btGiveUp.EnableWindow(TRUE);
		
	}

	//�趨��ʱ��
	SetGameTimer(pRequirOpen->wChairID,IDI_OPEN_CONCEAL,TIME_OPEN_CONCEAL);

	return true;
}

//�����ж�
bool CGameClientDlg::VerdictOutCard()
{
	//״̬�ж�
	if (m_GameClientView.m_btOutCard.IsWindowVisible()==FALSE) return false;

	//��ȡ�˿�
	BYTE cbCardData[MAX_COUNT];
	BYTE cbShootCount=(BYTE)m_GameClientView.m_HandCardControl.GetShootCard(cbCardData,CountArray(cbCardData));

	//�����ж�
	if (cbShootCount>0L)
	{
		//�����˿�
		m_GameLogic.SortCardList(cbCardData,cbShootCount);

		//�׳�����
		if (m_wFirstOutUser==GetMeChairID())
		{
			//�����ж�
			BYTE cbCardType=m_GameLogic.GetCardType(cbCardData,cbShootCount);
			if (cbCardType==CT_ERROR) return false;

			return true;
		}

		//�������
		BYTE cbTurnCardCount=m_cbOutCardCount[m_wFirstOutUser][0];
		bool bLegality=m_GameLogic.EfficacyOutCard(cbCardData,cbShootCount,m_cbOutCardData[m_wFirstOutUser][0],
			cbTurnCardCount,m_cbHandCardData,m_cbHandCardCount);

		return bLegality;
	}

	return false;
}

//�Զ�����
bool CGameClientDlg::AutomatismOutCard()
{
	//��������
	tagOutCardResult OutCardResult;
	ZeroMemory(&OutCardResult,sizeof(OutCardResult));

	//��������
	BYTE cbTurnCardCount=(m_wCurrentUser==m_wFirstOutUser)?0:m_cbOutCardCount[m_wFirstOutUser][0];
	m_GameLogic.SearchOutCard(m_cbHandCardData,m_cbHandCardCount,m_cbOutCardData[m_wFirstOutUser][0],cbTurnCardCount,OutCardResult);

	//���ñ���
	KillGameTimer(IDI_OUT_CARD);
	m_wCurrentUser=INVALID_CHAIR;

	//���ÿؼ�
	m_GameClientView.m_btOutCard.ShowWindow(SW_HIDE);
	m_GameClientView.m_btOutCard.EnableWindow(FALSE);
	m_GameClientView.m_btOutPrompt.ShowWindow(SW_HIDE);

	//�����˿�
	if (m_wFirstOutUser==GetMeChairID())
	{
		for (WORD i=0;i<GAME_PLAYER;i++)
		{
			if (i!=2) m_GameClientView.m_UserCardControl[i].SetCardData(NULL,0);
		}
	}
	
	//��������
	CMD_C_OutCard OutCard;
	OutCard.cbCardCount=OutCardResult.cbCardCount;
	CopyMemory(OutCard.cbCardData,OutCardResult.cbResultCard,sizeof(BYTE)*OutCard.cbCardCount);
	SendData(SUB_C_OUT_CARD,&OutCard,sizeof(OutCard)-sizeof(OutCard.cbCardData)+OutCard.cbCardCount*sizeof(BYTE));

	//Ԥ����ʾ
	PlayGameSound(AfxGetInstanceHandle(),TEXT("OUT_CARD"));
	m_GameClientView.m_UserCardControl[2].SetCardData(OutCard.cbCardData,OutCard.cbCardCount);

	//Ԥ��ɾ��
	BYTE cbSourceCount=m_cbHandCardCount;
	m_cbHandCardCount-=OutCard.cbCardCount;
	m_GameLogic.RemoveCard(OutCard.cbCardData,OutCard.cbCardCount,m_cbHandCardData,cbSourceCount);

	//�����˿�
	SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);

	return true;
}

//��ǰ�˿�
bool CGameClientDlg::SwitchToCurrentCard()
{
	//�����ж�
	if (m_bLastTurn==false) return false;

	//��������
	m_bLastTurn=false;
	KillTimer(IDI_LAST_TURN_CARD);
	m_GameClientView.SetLastTurnCard(false);

	//�����˿�
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		WORD wViewChairID=SwitchViewChairID(i);
		m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(m_cbOutCardData[i][0],m_cbOutCardCount[i][0]);
	}

	return true;
}

//˦�ƽ��
bool CGameClientDlg::SwitchToThrowResult()
{
	//�����ж�
	if (m_bThrowCard==false) return false;
	if (m_wThrowCardUser==INVALID_CHAIR) return false;

	//ʱ������
	KillTimer(IDI_THROW_CARD_RESULT);

	//���ý���
	WORD wViewChairID=SwitchViewChairID(m_wThrowCardUser);
	m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(m_cbResultCardData,m_cbResultCardCount);

	//��������
	if (m_cbOutCardCount[0][1]!=0) m_GameClientView.m_btLastTurnCard.EnableWindow(TRUE);

	//���ñ���
	m_bThrowCard=false;
	m_cbResultCardCount=0;
	m_wThrowCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbResultCardData,sizeof(m_cbResultCardData));

	return true;
}

//���½���
bool CGameClientDlg::UpdateCallCardControl()
{
	//״̬����
	if (IsLookonMode()==true) return false;
	if (GetGameStatus()!=GS_UG_CALL) return false;

	//��������
	BYTE cbCallMask=CALL_NONE;
	BYTE cbCallColor=m_GameLogic.GetCardColor(m_cbCallCard);

	//��������
	BYTE cbCardCount[6]={0,0,0,0,0,0};
	BYTE cbCallMaskArray[6]={CALL_FANG_KUAI,CALL_MEI_HUA,CALL_HONG_TAO,CALL_HEI_TAO,CALL_NT,CALL_NT};
	BYTE cbCallColorArray[6]={COLOR_FANG_KUAI,COLOR_MEI_HUA,COLOR_HONG_TAO,COLOR_HEI_TAO,COLOR_NT,COLOR_NT};

	//���µ���
	if (m_wCallCardUser!=GetMeChairID())
	{
		//�˿�ͳ��
		for (BYTE i=0;i<m_cbDispatchCardCount;i++)
		{
			//��ȡ����
			BYTE cbCardColor=m_GameLogic.GetCardColor(m_cbDispatchCardData[i]);
			BYTE cbCardValue=m_GameLogic.GetCardValue(m_cbDispatchCardData[i]);

			//����ͳ��
			if (cbCardColor==COLOR_NT) cbCardCount[4+cbCardValue-0x0E]++;
			else if ((cbCardValue==m_cbMainValue)&&((cbCardColor!=cbCallColor)||(m_cbCallCount<2))) cbCardCount[cbCardColor>>4]++;
		}

		//���ƿ���
		for (BYTE i=0;i<CountArray(cbCardCount);i++)
		{
			//�����ж�			
			if ((cbCardCount[i]==0)||(cbCardCount[i]<m_cbCallCount)) continue;
			//if(cbCardCount[i]>=2) break;
			

			//��Ŀ�ж�
			if ((i<4)&&(cbCardCount[i]>m_cbCallCount&&m_cbCallCount<2))
			{
				cbCallMask|=cbCallMaskArray[i];
				continue;
			}

			//�����ж�
			if ((i>=4)&&(cbCardCount[i]>m_cbCallCount)&&(cbCardCount[i]>=2))
			{
				cbCallMask|=cbCallMaskArray[i];
				continue;
			}

			//��ɫ�ж�
			BYTE cbPackCount=m_GameLogic.GetPackCount();
			if ((cbCardCount[i]==cbPackCount)&&(cbCallColorArray[i]>cbCallColor))
			{
				cbCallMask|=cbCallMaskArray[i];
				continue;
			}
		}
	}
	else
	{
		//�˿�ͳ��
		BYTE cbCallCardCount=0;
		for (BYTE i=0;i<m_cbDispatchCardCount;i++)
		{
			if (m_cbDispatchCardData[i]==m_cbCallCard) cbCallCardCount++;
		}

		//���ƿ���
		if (cbCallCardCount>m_cbCallCount) cbCallMask=cbCallMaskArray[cbCallColor>>4];
	}

	//���¿���
	m_GameClientView.m_CallCardWnd.UpdateCallControl(cbCallMask);

	return true;
}

//�ɷ��˿�
bool CGameClientDlg::DispatchUserCard(BYTE cbCardData[], BYTE cbCardCount)
{
	//���ñ���
	m_cbDispatchCardCount=0;
	m_cbRemnantCardCount=cbCardCount;
	CopyMemory(m_cbDispatchCardData,cbCardData,sizeof(BYTE)*cbCardCount);

	//���ö�ʱ��
	SetTimer(IDI_DISPATCH_CARD,400,NULL);

	return true;
}

//�����˿�
bool CGameClientDlg::SetHandCardControl(BYTE cbCardData[], BYTE cbCardCount)
{
	//���ù���
	if (cbCardCount>0)
	{
		//��������
		BYTE cbRectifyCount=1;
		BYTE cbRectifyCard[MAX_COUNT+4]={cbCardData[0]};

		//��ȡ����
		BYTE cbLogicColor=m_GameLogic.GetCardLogicColor(cbCardData[0]);

		//�任�˿�
		for (BYTE i=1;i<cbCardCount;i++)
		{
			//��ȡ����
			BYTE cbCurrentColor=m_GameLogic.GetCardLogicColor(cbCardData[i]);

			//�����ж�
			if (cbCurrentColor!=cbLogicColor)
			{
				cbLogicColor=cbCurrentColor;
				cbRectifyCard[cbRectifyCount++]=255;
				cbRectifyCard[cbRectifyCount++]=cbCardData[i];
			}
			else cbRectifyCard[cbRectifyCount++]=cbCardData[i];
		}

		//�����˿�
		m_GameClientView.m_HandCardControl.SetCardData(cbRectifyCard,cbRectifyCount);

		return true;
	}
	else m_GameClientView.m_HandCardControl.SetCardData(NULL,0);

	return true;
}

//��ʱ����Ϣ
void CGameClientDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case IDI_CONCEAL_CARD:		//�鿴����
		{
			//��ʾ����
			KillTimer(IDI_CONCEAL_CARD);
			m_GameClientView.m_ConcealCardView.ShowWindow(SW_HIDE);

			return;
		}
	case IDI_DISPATCH_CARD:		//�ɷ��˿�
		{
			//�ɷ�����
			if (m_cbRemnantCardCount>0)
			{
				//��ȡ����
				BYTE cbCardColor=m_GameLogic.GetCardColor(m_cbDispatchCardData[m_cbDispatchCardCount]);
				BYTE cbCardValue=m_GameLogic.GetCardValue(m_cbDispatchCardData[m_cbDispatchCardCount]);

				//�ɷ��˿�
				m_cbRemnantCardCount--;
				m_cbDispatchCardCount++;
				m_GameLogic.SortCardList(m_cbDispatchCardData,m_cbDispatchCardCount);
				SetHandCardControl(m_cbDispatchCardData,m_cbDispatchCardCount);

				//���ƿ���
				if ((cbCardColor==COLOR_NT)||(cbCardValue==m_cbMainValue)) UpdateCallCardControl();

				//��������
				PlayGameSound(AfxGetInstanceHandle(),TEXT("OUT_CARD"));
			}
			
			//��ֹ�ж�
			if (m_cbRemnantCardCount==0) 
			{
				//ɾ����ʱ��
				KillTimer(IDI_DISPATCH_CARD);


				//�м����
				WORD wTotalScore=0;

				//�������
				wTotalScore=m_GameLogic.GetCardTotalScore(m_cbHandCardData,m_cbHandCardCount);

				if((wTotalScore<MIN_SCORE)&&(m_bStustee==false))
				{
					//���ÿؼ�
					m_GameClientView.m_btReRandCard.ShowWindow(SW_SHOW);
					m_GameClientView.m_btReRandCard.EnableWindow(TRUE);
					

					//�趨��ʱ��
					SetTimer(IDI_RERANDCARD,5000,0);
				}
				


				//��������
				SetGameTimer(GetMeChairID(),IDI_CALL_CARD,TIME_CALL_CARD);
				if ((IsLookonMode()==false)&&(m_bStustee==false)) ActiveGameFrame();
			}
			else
			{
				//���ÿؼ�
				m_GameClientView.m_btReRandCard.ShowWindow(SW_HIDE);
				m_GameClientView.m_btReRandCard.EnableWindow(FALSE);
				
			}

			return;
		}
	case IDI_LAST_TURN_CARD:	//�����˿�
		{
			//��ԭ����
			SwitchToCurrentCard();

			return;
		}
	case IDI_THROW_CARD_RESULT:	//˦�ƽ��
		{
			//��ԭ����
			SwitchToThrowResult();

			//��ǰ���
			if ((IsLookonMode()==false)&&(m_wCurrentUser==GetMeChairID()))
			{
				if (m_bStustee==false) ActiveGameFrame();
				m_GameClientView.m_btOutCard.ShowWindow(SW_SHOW);
				m_GameClientView.m_btOutPrompt.ShowWindow(SW_SHOW);
				m_GameClientView.m_btOutCard.EnableWindow((VerdictOutCard()==true)?TRUE:FALSE);
			}

			//���ö�ʱ��
			SetGameTimer(m_wCurrentUser,IDI_OUT_CARD,TIME_OUT_CARD);

			return;
		}
	case IDI_RERANDCARD:	//����ϴ��
		{

			//ɾ����ʱ��
			KillTimer(IDI_RERANDCARD);

			//�ؼ�����
			m_GameClientView.m_btReRandCard.ShowWindow(SW_HIDE);
			m_GameClientView.m_btReRandCard.EnableWindow(FALSE);
			

			return ;
		}
	}

	__super::OnTimer(nIDEvent);
}

//��ʼ��ť
LRESULT CGameClientDlg::OnStart(WPARAM wParam, LPARAM lParam)
{
	//���û���
	KillGameTimer(IDI_START_GAME);

	//���ý���
	m_GameClientView.SetCardScore(0xFFFF);
	m_GameClientView.SetWaitConceal(false);
	m_GameClientView.SetBankerUser(INVALID_CHAIR);
	m_GameClientView.SetCallCardInfo(INVALID_CHAIR,COLOR_ERROR,0);
	m_GameClientView.SetPutConcealUser(INVALID_CHAIR);

	//���ؿؼ�
	m_GameClientView.m_btStart.ShowWindow(FALSE);
	m_GameClientView.m_ScoreView.ShowWindow(SW_HIDE);

	//���ƿ���
	m_GameClientView.m_btConcealCard.EnableWindow(FALSE);
	m_GameClientView.m_ConcealCardView.ShowWindow(SW_HIDE);
	m_GameClientView.m_ConcealCardView.SetConcealCard(NULL,0);

	//�����˿�
	SetHandCardControl(NULL,0);
	m_GameClientView.m_CardScore.SetCardData(NULL,0);
	m_GameClientView.m_HandCardControl.SetPositively(false);
	for (WORD i=0;i<GAME_PLAYER;i++) m_GameClientView.m_UserCardControl[i].SetCardData(NULL,0);

	//��ʾ����
	m_GameClientView.m_btReRandCard.ShowWindow(SW_HIDE);
	m_GameClientView.m_btGiveUp.ShowWindow(SW_HIDE);
	m_GameClientView.m_btOpenConcealCard.ShowWindow(SW_HIDE);

	//������Ϣ
	SendUserReady(NULL,0);

	return 0;
}

//������Ϣ
LRESULT CGameClientDlg::OnOutCard(WPARAM wParam, LPARAM lParam)
{
	//״̬�ж�
	if (m_GameClientView.m_btOutCard.IsWindowEnabled()==FALSE) return 0;
	if (m_GameClientView.m_btOutCard.IsWindowVisible()==FALSE) return 0;

	//���ñ���
	KillGameTimer(IDI_OUT_CARD);
	m_wCurrentUser=INVALID_CHAIR;

	//���ÿؼ�
	m_GameClientView.m_btOutCard.ShowWindow(SW_HIDE);
	m_GameClientView.m_btOutCard.EnableWindow(FALSE);
	m_GameClientView.m_btOutPrompt.ShowWindow(SW_HIDE);

	//�����˿�
	if (m_wFirstOutUser==GetMeChairID())
	{
		for (WORD i=0;i<GAME_PLAYER;i++)
		{
			if (i!=2) m_GameClientView.m_UserCardControl[i].SetCardData(NULL,0);
		}
	}
	
	//��������
	CMD_C_OutCard OutCard;
	OutCard.cbCardCount=(BYTE)m_GameClientView.m_HandCardControl.GetShootCard(OutCard.cbCardData,CountArray(OutCard.cbCardData));
	m_GameLogic.SortCardList(OutCard.cbCardData,OutCard.cbCardCount);
	SendData(SUB_C_OUT_CARD,&OutCard,sizeof(OutCard)-sizeof(OutCard.cbCardData)+OutCard.cbCardCount*sizeof(BYTE));

	//Ԥ����ʾ
	PlayGameSound(AfxGetInstanceHandle(),TEXT("OUT_CARD"));
	m_GameClientView.m_UserCardControl[2].SetCardData(OutCard.cbCardData,OutCard.cbCardCount);

	//Ԥ��ɾ��
	BYTE cbSourceCount=m_cbHandCardCount;
	m_cbHandCardCount-=OutCard.cbCardCount;
	m_GameLogic.RemoveCard(OutCard.cbCardData,OutCard.cbCardCount,m_cbHandCardData,cbSourceCount);

	//�����˿�
	SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);

	return 0;
}

//������Ϣ
LRESULT CGameClientDlg::OnCallCard(WPARAM wParam, LPARAM lParam)
{
	//��������
	BYTE cbCallCount=0;
	BYTE cbCallCard=0x00;
	BYTE cbCallColor=(BYTE)lParam;

	//����ͳ��
	if (cbCallColor==COLOR_NT)
	{
		//��Ŀͳ��
		BYTE cbNTCount[2]={0,0};
		for (BYTE i=0;i<m_cbDispatchCardCount;i++)
		{
			BYTE cbCardData=m_cbDispatchCardData[i];
			if ((cbCardData==0x4E)||(cbCardData==0x4F)) cbNTCount[cbCardData-0x4E]++;
		}

		//��������
		if (cbNTCount[0]>=cbNTCount[1])
		{
			cbCallCard=0x4E;
			cbCallCount=cbNTCount[0];
		}
		else
		{
			cbCallCard=0x4F;
			cbCallCount=cbNTCount[1];
		}
	}
	else
	{
		//��Ŀͳ��
		for (BYTE i=0;i<m_cbDispatchCardCount;i++)
		{
			//��ȡ����
			BYTE cbCardData=m_cbDispatchCardData[i];
			BYTE cbCardColor=m_GameLogic.GetCardColor(cbCardData);
			BYTE cbCardValue=m_GameLogic.GetCardValue(cbCardData);

			//����ͳ��
			if ((cbCardValue==m_cbMainValue)&&(cbCardColor==cbCallColor)) 
			{
				cbCallCount++;
				cbCallCard=cbCardData;
			}
		}
	}

	if(!m_bOpenConcealFlag)
	{

		//���½���
		m_GameClientView.m_CallCardWnd.UpdateCallControl(CALL_NONE);

		//��������
		CMD_C_CallCard CallCard;
		CallCard.cbCallCard=cbCallCard;
		CallCard.cbCallCount=cbCallCount;

		//��������
		SendData(SUB_C_CALL_CARD,&CallCard,sizeof(CallCard));
	}
	else//���׽���
	{

		//���ñ���
		m_bOpenConcealFlag = false;

		//ɾ����ʱ��
		KillGameTimer(IDI_OPEN_CONCEAL);

		//�ؼ�����
		m_GameClientView.m_btOpenConcealCard.ShowWindow(SW_HIDE);
		m_GameClientView.m_btGiveUp.ShowWindow(SW_HIDE);
		m_GameClientView.m_btGiveUp.EnableWindow(FALSE);
		m_GameClientView.m_btOpenConcealCard.EnableWindow(FALSE);
		


		//���½���
		m_GameClientView.m_CallCardWnd.ShowWindow(SW_HIDE);
		m_GameClientView.m_CallCardWnd.UpdateCallControl(CALL_NONE);

		//��Ϣ����
		CMD_C_OpenConcealCard OpenConcealCard;
		OpenConcealCard.cbCallCard = cbCallCard;
		OpenConcealCard.wChairID = GetMeChairID();
		OpenConcealCard.cbCallCount = cbCallCount;

		//������Ϣ
		SendData(SUB_C_OPENCONCEALCARD,&OpenConcealCard,sizeof(OpenConcealCard));


	}

	return 0;
}

//������ʾ
LRESULT CGameClientDlg::OnOutPrompt(WPARAM wParam, LPARAM lParam)
{
	//��������
	tagOutCardResult OutCardResult;
	ZeroMemory(&OutCardResult,sizeof(OutCardResult));

	//��������
	BYTE cbTurnCardCount=(m_wCurrentUser==m_wFirstOutUser)?0:m_cbOutCardCount[m_wFirstOutUser][0];
	bool bSuccess=m_GameLogic.SearchOutCard(m_cbHandCardData,m_cbHandCardCount,m_cbOutCardData[m_wFirstOutUser][0],cbTurnCardCount,OutCardResult);

	//ʧ���ж�
	if (bSuccess==false)
	{
		InsertSystemString(TEXT("�Զ���ʾ���ƴ�������Ѵ�״̬��Ϣ��ͼ���������ṩ��лл��"));
		return false;
	}

	//���ý���
	m_GameClientView.m_btOutCard.EnableWindow(TRUE);
	m_GameClientView.m_HandCardControl.SetShootCard(OutCardResult.cbResultCard,OutCardResult.cbCardCount);

	return 0;
}

//������Ϣ
LRESULT CGameClientDlg::OnSendConceal(WPARAM wParam, LPARAM lParam)
{
	//��ȡ�˿�
	BYTE cbCardData[MAX_COUNT];
	BYTE cbCardCount=(BYTE)m_GameClientView.m_HandCardControl.GetShootCard(cbCardData,CountArray(cbCardData));

	//ɾ���˿�
	m_cbHandCardCount-=cbCardCount;
	m_GameLogic.RemoveCard(cbCardData,cbCardCount,m_cbHandCardData,m_cbHandCardCount+cbCardCount);

	//���ý���
	KillGameTimer(IDI_SEND_CONCEAL);
	m_GameClientView.m_btSendConceal.ShowWindow(SW_HIDE);
	m_GameClientView.m_btSendConceal.EnableWindow(FALSE);
	SetHandCardControl(m_cbHandCardData,m_cbHandCardCount);

	//��������
	CMD_C_ConcealCard ConcealCard;
	ConcealCard.cbConcealCount=cbCardCount;
	CopyMemory(ConcealCard.cbConcealCard,cbCardData,cbCardCount*sizeof(BYTE));

	//��������
	SendData(SUB_C_CONCEAL_CARD,&ConcealCard,sizeof(ConcealCard));

	return 0;
}

//�鿴����
LRESULT CGameClientDlg::OnConcealCard(WPARAM wParam, LPARAM lParam)
{
	//�鿴����
	if (m_GameClientView.m_ConcealCardView.IsWindowVisible())
	{
		KillTimer(IDI_CONCEAL_CARD);
		m_GameClientView.m_ConcealCardView.ShowWindow(SW_HIDE);
	}
	else
	{
		SetTimer(IDI_CONCEAL_CARD,5000,NULL);
		m_GameClientView.m_ConcealCardView.ShowWindow(SW_SHOW);
	}

	return 0;
}

//�����뿪
LRESULT CGameClientDlg::OnRuquestLeave(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

//�����˿�
LRESULT CGameClientDlg::OnLastTurnCard(WPARAM wParam, LPARAM lParam)
{
	if (m_bLastTurn==false)
	{
		//�����˿�
		for (WORD i=0;i<GAME_PLAYER;i++)
		{
			WORD wViewChairID=SwitchViewChairID(i);
			m_GameClientView.m_UserCardControl[wViewChairID].SetCardData(m_cbOutCardData[i][1],m_cbOutCardCount[i][1]);
		}

		//��������
		m_bLastTurn=true;
		m_GameClientView.SetLastTurnCard(true);
		SetTimer(IDI_LAST_TURN_CARD,3000,NULL);
	}
	else SwitchToCurrentCard();

	return 0;
}

//�Ϲܿ���
LRESULT CGameClientDlg::OnStusteeControl(WPARAM wParam, LPARAM lParam)
{
	//����״̬
	if (m_bStustee==true)
	{
		m_bStustee=false;
		m_GameClientView.m_btStusteeControl.SetButtonImage(IDB_START_TRUSTEE,AfxGetInstanceHandle(),false);
	}
	else
	{
		m_bStustee=true;
		m_GameClientView.m_btStusteeControl.SetButtonImage(IDB_STOP_TRUSTEE,AfxGetInstanceHandle(),false);
	}

	return 0;
}

//����ϴ��
LRESULT CGameClientDlg::OnReRandCard(WPARAM wParam, LPARAM lParam)
{
	//�ؼ�����
	m_GameClientView.m_btReRandCard.ShowWindow(SW_HIDE);
	m_GameClientView.m_btReRandCard.EnableWindow(FALSE);
	

	//������Ϣ
	SendData(SUB_C_RERANDCARD);
	return 0;
}

//��������
LRESULT CGameClientDlg::OnOpenConcealCard(WPARAM wParam, LPARAM lParam)
{
	
	//ɾ����ʱ��
	KillGameTimer(IDI_OPEN_CONCEAL);

	//�ؼ�����
	m_GameClientView.m_btOpenConcealCard.ShowWindow(SW_HIDE);
	m_GameClientView.m_btGiveUp.ShowWindow(SW_HIDE);
	m_GameClientView.m_btOpenConcealCard.EnableWindow(FALSE);
	m_GameClientView.m_btGiveUp.EnableWindow(FALSE);
	

	//��Ϣ�ж�
	if(wParam)//�û�����
	{

		//�趨��ʱ��
		SetGameTimer(GetMeChairID(),IDI_OPEN_CONCEAL,TIME_OPEN_CONCEAL);		
		

		//��������
		BYTE cbCallMask=CALL_NONE;
		BYTE cbCallColor=m_GameLogic.GetCardColor(m_cbCallCard);

		//��������
		BYTE cbCardCount[6]={0,0,0,0,0,0};
		BYTE cbCallMaskArray[6]={CALL_FANG_KUAI,CALL_MEI_HUA,CALL_HONG_TAO,CALL_HEI_TAO,CALL_NT,CALL_NT};
		BYTE cbCallColorArray[6]={COLOR_FANG_KUAI,COLOR_MEI_HUA,COLOR_HONG_TAO,COLOR_HEI_TAO,COLOR_NT,COLOR_NT};

	
		//�˿�ͳ��
		for (BYTE i=0;i<m_cbHandCardCount;i++)
		{
			//��ȡ����
			BYTE cbCardColor=m_GameLogic.GetCardColor(m_cbHandCardData[i]);
			BYTE cbCardValue=m_GameLogic.GetCardValue(m_cbHandCardData[i]);

			//����ͳ��
			if (cbCardColor==COLOR_NT) cbCardCount[4+cbCardValue-0x0E]++;
			else if ((cbCardValue==m_cbMainValue)&&((cbCardColor!=cbCallColor)||(m_cbCallCount<2))) cbCardCount[cbCardColor>>4]++;
		}

		//���ƿ���
		for (BYTE i=0;i<CountArray(cbCardCount);i++)
		{
			//�����ж�			
			if ((cbCardCount[i]==0)||(cbCardCount[i]!=2)) continue;

			

			//��Ŀ�ж�
			if ((i<4)&&(cbCardCount[i]==2))
			{
				cbCallMask|=cbCallMaskArray[i];
				continue;
			}

			//�����ж�
			if ((i>=4)&&(cbCardCount[i]>1)&&(cbCardCount[i]>=2))	
			{
				cbCallMask|=cbCallMaskArray[i];
				continue;
			}
			
		}

		//���ñ���
		m_bOpenConcealFlag = true;

		//���¿���
		m_GameClientView.m_CallCardWnd.ShowWindow(SW_SHOW);
		m_GameClientView.m_CallCardWnd.UpdateCallControl(cbCallMask);


	}
	else//�û�����
	{

		//���¿���
		m_GameClientView.m_CallCardWnd.ShowWindow(SW_HIDE);

		//�ؼ�����
		//m_GameClientView.m_btOpenConcealCard.ShowWindow(SW_HIDE);
		//m_GameClientView.m_btGiveUp.ShowWindow(SW_HIDE);
		//m_GameClientView.m_btOpenConcealCard.EnableWindow(FALSE);
		//m_GameClientView.m_btGiveUp.EnableWindow(FALSE);
		
		

		//��Ϣ����
		CMD_C_OpenConcealCard OpenConcealCard;
		OpenConcealCard.cbCallCard = 0;
		OpenConcealCard.wChairID = GetMeChairID();
		OpenConcealCard.cbCallCount = 0;

		//������Ϣ
		SendData(SUB_C_OPENCONCEALCARD,&OpenConcealCard,sizeof(OpenConcealCard));


	}
	
	return 0;
}

//����˿�
LRESULT CGameClientDlg::OnLeftHitCard(WPARAM wParam, LPARAM lParam)
{
	//��ȡ״̬
	BYTE cbGameStatue=GetGameStatus();

	//����״̬
	switch (cbGameStatue)
	{
	case GS_UG_BACK:	//����״̬
		{
			//״̬����
			if ((IsLookonMode()==false)&&(m_wCurrentUser==GetMeChairID()))
			{
				//��ȡ�˿�
				BYTE cbCardData[MAX_COUNT];
				BYTE cbCardCount=(BYTE)m_GameClientView.m_HandCardControl.GetShootCard(cbCardData,CountArray(cbCardData));

				//���ư�ť
				m_GameClientView.m_btSendConceal.EnableWindow((cbCardCount==m_cbConcealCount)?TRUE:FALSE);
			}

			return 0;
		}
	case GS_UG_PLAY:	//��Ϸ״̬
		{
			//���ÿؼ�
			bool bOutCard=VerdictOutCard();
			m_GameClientView.m_btOutCard.EnableWindow(bOutCard?TRUE:FALSE);

			return 0;
		}
	}

	return 0;
}

//�Ҽ��˿�
LRESULT CGameClientDlg::OnRightHitCard(WPARAM wParam, LPARAM lParam)
{
	//�û�����
	OnOutCard(0,0);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
