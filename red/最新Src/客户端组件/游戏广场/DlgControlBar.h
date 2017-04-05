#ifndef DLG_CONTROL_BAR_HEAD_FILE
#define DLG_CONTROL_BAR_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "RoomViewItem.h"
#include "PlazaViewItem.h"

//�궨��
#define MAX_SERVER						2								//��󷿼�
#define CONTROL_BAR_HEIGHT				10								//��������

//////////////////////////////////////////////////////////////////////////

//�������Ի���
class CDlgControlBar : public CDialog
{
	//״̬����
public:
	CRect								m_rcViewItem;					//����λ��
	IViewItem							* m_pActiveViewItem;			//��ǰ��ͼ
	CPlazaViewItem						* m_pPlazaViewItem;				//�㳡��ͼ
	CRoomViewItem						* m_pRoomViewItemCreate;		//��������
	CRoomViewItem						* m_pRoomViewItem[MAX_SERVER];	//����ӿ�
	
	//��Դ����
protected:
	CSkinImage							m_Frame_BL;					//ͼƬ��Դ
	CSkinImage							m_Frame_BM;					//ͼƬ��Դ
	//CSkinImage							m_ImageMin;						//ͼƬ��Դ
	//CSkinImage							m_ImageRight;					//ͼƬ��Դ

	//�ؼ�����
public:
	CSkinButton							m_btGamePlaza;					//��Ϸ�㳡
	CSkinButton							m_btViewItem1;					//���䰴ť
	CSkinButton							m_btViewItem2;					//���䰴ť
	CSkinButton							m_btSwitchUser;					//�л��ʺ�
	CSkinButton							m_btGlobalOption;				//ϵͳ����
	CSkinButton							m_btPrisonSet;					//��������
	CSkinButton							m_btCompanion;					//��ϵ����
	CSkinButton							m_btChangeTheme;				//��������

	//�Ի�������
	enum { IDD = IDD_CONTROL_BAR };

	//��������
public:
	//���캯��
	CDlgControlBar();
	//��������
	virtual ~CDlgControlBar();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();

	//���ܺ���
public:
	//����λ��
	void SetViewItemRect(int nXPos, int nYPos, int nWidth, int nHeight);
	//��ȡ�㳡
	CPlazaViewItem * GetPlazaViewItem() { return m_pPlazaViewItem; }
	//���ù㳡
	void SetPlazaViewItem(CPlazaViewItem * pPlazaViewItem) { m_pPlazaViewItem=pPlazaViewItem; }

	//���ܺ���
public:
	//��ʾ��ҳ
	void WebBrowse(LPCTSTR lpszUrl, bool bForceBrowse);
	//��ʾ��Ϣ
    int ShowMessageBox(LPCTSTR pszMessage, UINT nType);

	//���亯��
public:
	//����㳡
	void ActivePlazaViewItem();
	//�����
	void ActiveRoomViewItem(CRoomViewItem * pRoomViewItem);
	//���ҷ���
	CRoomViewItem * SearchRoomViewItem(WORD wKindID, WORD wServerID);

	//���뷿��
	CRoomViewItem * CreateRoomViewItem(CListServer * pListServer);
	//bluker:���뷿��,g_pControlBar->CreateRoomViewItem(7,7);
	CRoomViewItem * CreateRoomViewItem(WORD wKindID,WORD wServerID);

	//�رշ���
	void CloseRoomViewItem(IRoomViewItem * pIRoomViewItem);
	//�رշ���
	void CloseAllRoomViewItem();
	//�رյ�ǰ
	void CloseCurrentViewItem();

	//�ڲ�����
private:
	//���¿���
	void UpdateControlButton();

	//��Ϣ����
protected:

	//��������
	afx_msg void OnBnClickedChangeTheme();
	//�ػ�����
	afx_msg void OnPaint();
	//��Ϸ�㳡
	afx_msg void OnBnClickedPlaza();
	//��Ϸ����
	afx_msg void OnBnClickedViewItem1();
	//��Ϸ����
	afx_msg void OnBnClickedViewItem2();
	//��Ϸ����
	afx_msg void OnBnClickedViewItem3();
	//��Ϸ����
	afx_msg void OnBnClickedViewItem4();
	//�л���ť
	afx_msg void OnBnClickedSwitchAccounts();
	//��������
	afx_msg void OnBnClickedPrisonSet();
	//��ϵ��ť
	afx_msg void OnBnClickedCompanion();
	//���ð�ť
	afx_msg void OnBnClickedGlobalOption();
	//�˳���ť
	afx_msg void OnBnClickedQuitGame();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//�رշ���
	LRESULT OnCloseRoomViewItem(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//������ָ��
extern CDlgControlBar * g_pControlBar;

//////////////////////////////////////////////////////////////////////////

#endif