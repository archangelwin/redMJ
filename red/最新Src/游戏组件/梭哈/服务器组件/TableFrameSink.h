#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//����˿�����
#define SHAN								0
#define DUI_ZI								1
#define LAING_DUI							2
#define SAN_TIAO							3
#define SHUN_ZI								4
#define	TONG_HUA							5
#define HU_LU								6
#define TIE_ZHI								7
#define TONG_HUA_SHUN						8

//�˿˻�ɫ����
#define FANG_KUAI							0
#define MEI_HUA								1
#define HONG_TAO							2
#define HEI_TAO								3

//����ԭ��
#define GER_NO_PLAYER						0x10						//û�����

//////////////////////////////////////////////////////////////////////////

//��Ϸ�߼���
class CGameLogic
{
	//��������
private:
	static const BYTE				m_bCardArray[28];					//�˿˶���

	//��������
private:
	//��ȡ�˿˻�ɫ
	BYTE GetHuaKind(BYTE bCard);
	//��ȡ�˿���ֵ
	BYTE GetCardValoe(BYTE bCard);
	//��ȡ�˿�����
	BYTE GetCardKind(BYTE bCardList[], BYTE bCardCount);
	//���Ҷ���
	BYTE FindDoubleCard(BYTE bCardList[], BYTE bCardCount, BYTE * bOutDoubleCard);

	//���ͺ���
public:
	//�Ƿ�ͬ��˳
	bool IsTongHuaShun(BYTE bCardList[], BYTE bCardCount);
	//�Ƿ���֧
	bool IsTieZhi(BYTE bCardList[], BYTE bCardCount);
	//�Ƿ��«
	bool IsHuLu(BYTE bCardList[], BYTE bCardCount);
	//�Ƿ�ͬ��
	bool IsTongHua(BYTE bCardList[], BYTE bCardCount);
	//�Ƿ�˳��
	bool IsShunZhi(BYTE bCardList[], BYTE bCardCount);
	//�Ƿ�����
	bool IsSanTiao(BYTE bCardList[], BYTE bCardCount);
	//�Ƿ�����
	bool IsLiangDui(BYTE bCardList[], BYTE bCardCount);
	//�Ƿ����
	bool IsDuiZhi(BYTE bCardList[], BYTE bCardCount);

	//�ԱȺ���
public:
	//�Աȵ�ֻ�˿�
	bool CompareOnlyOne(BYTE bFirstCard, BYTE bLastCard);
	//�Ա�ͬ��˳
	bool CompareTongHuaShun(BYTE bFirstList[], BYTE bLastList[]);
	//�Ա���֧
	bool CompareTeiZhi(BYTE bFirstList[], BYTE bLastList[]);
	//�ԱȺ�«
	bool CompareHuLu(BYTE bFirstList[], BYTE bLastList[]);
	//�Ա�ͬ��
	bool CompareTongHua(BYTE bFirstList[], BYTE bLastList[]);
	//�Ա�˳��
	bool CompareShunZhi(BYTE bFirstList[], BYTE bLastList[]);
	//�Ա�����
	bool CompareSanTiao(BYTE bFirstList[], BYTE bLastList[]);
	//�Ա�����
	bool CompareLiangDui(BYTE bFirstList[], BYTE bLastList[], BYTE bCardCount);
	//�Աȶ���
	bool CompareDuiZhi(BYTE bFirstList[], BYTE bLastList[], BYTE bCardCount);
	//�Ա�ɢ��
	bool CompareSanCard(BYTE bFirstList[], BYTE bLastList[], BYTE bCardCount);

	//���ܺ���
public:
	//�����˿�
	void RandCard(BYTE bCardBuffer[], BYTE bBufferCount);
	//�����˿�
	void SortCard(BYTE bCardList[], BYTE bCardCount);
	//�Ա��˿�
	bool CompareCard(BYTE bFirstList[], BYTE bLastList[], BYTE bCardCount);
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ������
class CTableFrameSink : public ITableFrameSink
{
	//��Ϸ����
protected:
	WORD							m_wOperaCount;							//��������
	WORD							m_wCurrentUser;							//��ǰ�û�
	BYTE							m_bSendCardCount;						//������Ŀ
	BYTE							m_bTableCardCount[GAME_PLAYER];			//�˿���Ŀ
	BYTE							m_bTableCardArray[GAME_PLAYER][5];		//�����˿�

	//�����Ϣ
protected:
	LONG							m_lMaxGold;								//�����ע
	LONG							m_lTurnBasicGold;						//������ע
	LONG							m_lTableGold[2*GAME_PLAYER];			//��ע���

	//��������
protected:
	BYTE							m_bPlayStatus[GAME_PLAYER];				//��Ϸ״̬

	//�������
protected:
	CGameLogic						m_GameLogic;							//��Ϸ�߼�
	ITableFrame						* m_pITableFrame;						//��ܽӿ�
	const tagGameServiceOption		* m_pGameServiceOption;					//���ò���

	//���Ա���
protected:
	static const WORD				m_wPlayerCount;							//��Ϸ����
	static const enStartMode		m_GameStartMode;						//��ʼģʽ

	//��������
public:
	//���캯��
	CTableFrameSink();
	//��������
	virtual ~CTableFrameSink();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CTableFrameSink))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//����ӿ�
public:
	//��ʼ��
	virtual bool __cdecl InitTableFrameSink(IUnknownEx * pIUnknownEx);
	//��λ����
	virtual void __cdecl RepositTableFrameSink();

	//��Ϣ�ӿ�
public:
	//��ʼģʽ
	virtual enStartMode __cdecl GetGameStartMode();
	//��Ϸ״̬
	virtual bool __cdecl IsUserPlaying(WORD wChairID);

	//��Ϸ�¼�
public:
	//��Ϸ��ʼ
	virtual bool __cdecl OnEventGameStart();
	//��Ϸ����
	virtual bool __cdecl OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//���ͳ���
	virtual bool __cdecl SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE bGameStatus, bool bSendSecret);

	//�¼��ӿ�
public:
	//��ʱ���¼�
	virtual bool __cdecl OnTimerMessage(WORD wTimerID, WPARAM wBindParam);
	//��Ϸ��Ϣ����
	virtual bool __cdecl OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//�����Ϣ����
	virtual bool __cdecl OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);

	//��Ϸ�¼�
protected:
	//�����¼�
	bool OnUserGiveUp(WORD wChairID);
	//��ע�¼�
	bool OnUserAddGold(WORD wChairID, LONG lGold, bool bCancel);

	//��Ϸ����
protected:
	//�ƶ�ʤ��
	WORD DeduceWiner(BYTE bBeginPos, BYTE bEndPos);
};

//////////////////////////////////////////////////////////////////////////

#endif