#pragma once

#include "Stdafx.h"
#include "TableFrame.h"
//#include "UserManager.h"
#include "FindUserDlg.h"
#include "UserListView.h"
#include "SystemOption.h"
#include "ShortMessage.h"
#include "Show.h"
#include "ManagerClass.h"
#include "ServerItemView.h"

//////////////////////////////////////////////////////////////////////////

//�������״̬
enum enServiceStatus
{
	ServiceStatus_Null,					//û��״̬
	ServiceStatus_Connecting,			//����״̬
	ServiceStatus_EfficacyUser,			//Ч���û�
	ServiceStatus_RecvConfigInfo,		//��������
	ServiceStatus_RecvRoomInfo,			//������Ϣ
	ServiceStatus_Serviceing,			//����״̬
	ServiceStatus_NetShutDown,			//�����ж�
};

//���ҽṹ
struct tagFindTable
{
	bool								bOneNull;							//һ����λ
	bool								bTwoNull;							//������λ
	bool								bAllNull;							//ȫ��λ��
	bool								bNotFull;							//��ȫ��λ
	bool								bFilterPass;						//��������
	WORD								wBeginTableID;						//��ʼ����
	WORD								wResultTableID;						//�������
	WORD								wResultChairID;						//�������
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ����
class CRoomViewItem : public CDialog, public IRoomViewItem, public IClientSocketSink,
	public ITableFrameSink, public IUserManagerSink, public ISplitterSink, public IChannelMessageSink
{
	friend class CFindUserDlg;
	friend class CShortMessage;

	//Ӧ�ñ���
protected:
	WORD							m_wGameGenre;				//��Ϸ����
	CListServer						* m_pListServer;			//������Ϣ
	
	tagOptionBuffer					m_OptionBuffer;				//������Ϣ
	CMD_GR_ColumnInfo				m_ListColumnInfo;			//�б���Ϣ

	//��������
protected:
	bool							m_bRectify;					//������־
	bool							m_bInitDialog;				//��ʼ��־
	WORD							m_wReqTableID;				//��������
	WORD							m_wReqChairID;				//����λ��
	WORD							m_wFindTableID;				//����λ��
	DWORD							m_dwMenuUserID;				//�˵��û�

	//���ñ���
protected:
	CGameOption						* m_pGameOption;			//��Ϸ����
	CServerOption					* m_pServerOption;			//��������

	//�������
protected:
	IUserItem						* m_pMeUserItem;			//�Լ���Ϣ
	enServiceStatus					m_ServiceStatus;			//����״̬
	CClientUserManager				m_ClientUserManager;		//�û�����

	//������Ϣ
protected:
	HWND							m_hWndChannel;				//�ŵ�����
	HANDLE							m_hShareMemory;				//�����ڴ�
	TCHAR							m_szShareName[64];			//��������
	tagShareMemory					* m_pShareMemory;			//�����ڴ�

	//�������
protected:
	DWORD							m_dwChatUserID;				//�����û�
	TCHAR							m_szChatName[NAME_LEN];		//�����û�

	DWORD							m_dwLastChat;				//����ʱ����
	//����ؼ�
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush m_brBkgnd;

	CEdit							m_ChatInput;				//��������
	CComboBox						m_ChatObject;				//�������
	CSkinButton						m_btPhrase;					//���ﰴť
	TransButton						m_btSendChat;				//���Ͱ�ť

	CRgnButton						m_btExpression;				//���鰴ť
	TransButton						m_btColorSet;				//��ɫ����
	CSkinButton						m_btCleanScreen;			//������ť

	CExpression						m_Expression;				//���鴰��
	CSkinRichEdit					m_ChatMessage;				//�������

	CHtmlBrower						*m_pHtmlBrower1;		//�������
	CHtmlBrower						*m_pHtmlBrower2;		//�������

	//���ܿؼ�
public:
	CRgnButton						m_btAutoSit;				//���밴ť
	CRgnButton						m_btFindUser;				//���Ұ�ť

	//�û��ؼ�
public:
	CTableFrame						m_TableFrame;				//���ӿ��
	//CUserListView					m_UserListView;				//�û��б�
	CImageListCtrl					m_UserListView;				//�û��б�
	CHtmlBrower						*m_pHtmlBrower;


	//����ؼ�
public:
	CManagerServer					m_ManagerServer;			//�������
	CManagerMessage					m_ManagerMessage;			//ϵͳ��Ϣ
	CManagerUserRight				m_ManagerUserRight;			//Ȩ�޹���
	CManagerSendWarning				m_ManagerSendWarning;		//�������

	//����ͼ��
protected:
	CSkinButton					m_btRoom1;						//����
	CSkinButton					m_btRoom2;						//����
	CSkinButton					m_btRoom3;						//����
	CSkinButton					m_btRoom4;						//����
	CSkinButton					m_btRoom5;						//����
	CSkinButton					m_btRoom6;						//����
	CSkinButton					m_btRoomExit;						//����

	CSkinImage					m_ImageTop;						//��߿�
	CSkinImage					m_ImageInfo;					//��߿�
	CSkinImage					m_ImageWeb;						//��߿�


	CSkinImage					m_ImageML;						//��߿�
	CSkinImage					m_ImageMR;						//�ұ߿�

	


	CSkinImage					m_ImageChatTL;
	CSkinImage					m_ImageChatTM;
	CSkinImage					m_ImageChatTR;

	CSkinImage					m_QQShowL;
	CSkinImage					m_QQShowR;
	CSkinImage					m_QQShowB;

	//��������
protected:

	//�����ؼ�
public:
	CToolTipCtrl					m_ToolTipCtrl;				//��ʾ�ؼ�
	CIPCRecvCopyData				m_IPCRecvCopyData;			//�ŵ����
	CClientSocketHelper				m_ClientSocket;				//��������
	CMessageProxyHelper				m_MessageProxyHelper;		//��Ϣ����

	//��������
public:
	//���캯��
	CRoomViewItem();
	//��������
	virtual ~CRoomViewItem();

	//���غ��� 
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK() { return; };
	//ȡ������
	virtual void OnCancel() { return; };
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//�˵�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() {if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CRoomViewItem))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//��ͼ�ӿ�
public:
	//��ȡ���
	virtual HWND __cdecl GetWindowHandle() { return GetSafeHwnd(); }

	//����ӿ�
public:
	//�رշ���
	virtual void __cdecl CloseRoomViewItem();
	//������Ϣ
	virtual tagGameKind * __cdecl GetKindInfo();
	//������Ϣ
	virtual tagGameServer * __cdecl GetServerInfo();

	//������ӿ�
public:
	//��ť��Ϣ
	virtual bool __cdecl OnSplitterButton(CSkinSplitter * pSkinSplitter, CSkinButton * pSplitterButton);
	//�������Ϣ
	virtual bool __cdecl OnSplitterEvent(CSkinSplitter * pSkinSplitter, UINT uSplitID, int nXPos, int nYPos);

	//����ӿ�
public:
	//����������Ϣ
	bool __cdecl OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke);
	//�����ȡ��Ϣ
	virtual bool __cdecl OnSocketRead(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//����ر���Ϣ
	virtual bool __cdecl OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer);

	//�ŵ��ӿ�
public:
	//�ŵ����ݴ���
	virtual bool __cdecl OnChannelMessage(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);

	//���ӽӿ�
public:
	//����������
	virtual void __cdecl OnLButtonHitTable(WORD wTableID, WORD wChairID, bool bMirror);
	//����Ҽ�����
	virtual void __cdecl OnRButtonHitTable(WORD wTableID, WORD wChairID, bool bMirror);
	//���˫��
	virtual void __cdecl OnDoubleHitTable(WORD wTableID, bool bMirror);

	//�û��ӿ�
public:
	//�û�����
	virtual void __cdecl OnUserItemAcitve(IUserItem * pIUserItem);
	//�û�����
	virtual void __cdecl OnUserItemUpdate(IUserItem * pIUserItem);
	//�û�ɾ��
	virtual void __cdecl OnUserItemDelete(IUserItem * pIUserItem);

	//����������
protected:
	//��¼��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//�û���Ϣ
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//������Ϣ
	bool OnSocketMainInfo(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//״̬��Ϣ
	bool OnSocketMainStatus(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//ϵͳ��Ϣ
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//������Ϣ
	bool OnSocketMainServerInfo(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//��Ϸ��Ϣ
	bool OnSocketMainGameFrame(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);

	//����������
protected:
	//�û�����
	bool OnSocketSubUserCome(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//�û�״̬
	bool OnSocketSubStatus(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//�û�����
	bool OnSocketSubScore(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//����ʧ��
	bool OnSocketSubSitFailed(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//�û�����
	bool OnSocketSubChat(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//�û�˽��
	bool OnSocketSubWisper(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//�������
	bool OnSocketSubUserInvite(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);

	//IPC �¼�����
protected:
	//IPC �ں�����
	bool OnIPCKernel(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);
	//IPC ��������
	bool OnIPCSocket(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend);

	//���ƺ���
public:
	//��ʼ������
	bool InitRoomViewItem(CListServer * pListServer);
	//���ӷ�����
	bool ConnectGameServer();
	//���͹���
	bool SendUserRule();
	//˽����Ϣ
	bool SendUserWhisper(IUserItem * pIUserItem);
	//�û�SHOW
	bool SendUserShow(IUserItem * pIUserItem);
	//�û��˵�
	bool ShowUserInfoMenu(IUserItem * pIUserItem, CPoint Point);

	//���ܺ���
public:
	//��Ϸ����
	CGameOption * GetGameOption() { return m_pGameOption; }
	//��������
	CServerOption * GetServerOption() { return m_pServerOption; }

	//��������
protected:
	//���͵�½����
	bool SendLogonPacket();
	//������������
	bool SendOptionsPacket();
	//������������
	bool SendStandUpPacket();
	//����ǿ������
	bool SendLeftGamePacket();
	//���ͷ������
	bool SendUserRulePacket();
	//�����Թ�����
	bool SendLookonPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass);
	//������������
	bool SendSitDownPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass);
	//������������
	bool SendChatPacket(DWORD dwTargetUserID, LPCTSTR pszChatMessage, COLORREF crFontColor);

	//��������
public:
	//bluker:�����ɷ���������
	bool IsServerAllocTable()
	{
		return m_pListServer->GetItemInfo()->wSitByServer!=0;
	}
	void UpdateUserMoney(int nBtn,CSkinImage &pImg,tagUserData *User);
protected:
	void SetAllocTableType()
	{
		m_TableFrame.m_bSitByServer=IsServerAllocTable();
	}
	//�Թ۶���
	bool PerformLookonAction(WORD wTableID, WORD wChairID);
	//���¶���
	bool PerformSitDownAction(WORD wTableID, WORD wChairID);

	//IPC ����
protected:
	//������Ϸ��Ϣ
	bool IPCSendGameInfo(CIPCSendCopyData * pSendCopyData);
	//�����û���Ϣ
	bool IPCSendTableUsers(CIPCSendCopyData * pSendCopyData);

	//�ڲ�����
protected:
	//������Ϸ
	int StartGameClient();
	//�ر���Ϸ
	void CloseGameClient();
	//�����û�
	bool SendTableUser(IUserItem * pIUserItem, CIPCSendCopyData * pSendCopyData);
	//������Ϣ
	bool SendProcessData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	//��������
protected:
	//���±���
	void UpdateTitleText();
	//�滭�б�
	void DrawUserFrame(CDC * pDC);
	//�滭����
	void DrawChatFrame(CDC * pDC);
	//����ͼ��
	void DrawLeftViewFrame(CDC * pDC);
	//�������
	bool SetChatObject(IUserItem * pIUserItem);
	//��������
	bool FindGameTable(tagFindTable & FindInfo);
	//�����ؼ�
	void RectifyControl(int nWidth, int nHeight);
	//��ʾ��Ϣ
    int ShowMessageBox(LPCTSTR pszMessage, UINT nType);
	//�ܷ�����
	bool CanSitDownTable(WORD wTableID, WORD wChairID, bool bLookon, bool bShowError);

	//��Ϣӳ��
protected:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//��ť��Ϣ
protected:
	//���Ͱ�ť
	afx_msg void OnBnClickedSendChat();
	//���鰴ť
	afx_msg void OnBnClickedExpression();
	//��ɫ��ť
	afx_msg void OnBnClickedColorSet();
	//������ť
	afx_msg void OnBnClickedCleanScreen();
	//��ʾ��Ϣ
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//IPC ��Ϣ
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT * pCopyDataStruct);
	//�û��б���
	afx_msg void OnBnUserList_Clicked();
	//������Ϣ
	LRESULT OnHitExpression(WPARAM wParam, LPARAM lParam);

	//���ܰ�ť
protected:
	//���밴ť
	afx_msg void OnBnClickedAutoSit();
	//���Ұ�ť
	afx_msg void OnBnClickedFindUser();
	//�˳�����
	afx_msg void OnBnClickedRoomExit();


	CPtrArray						m_ShortMessage;						//��Ϣ����

	CPtrArray						m_ShowMessage;						//��Ϣ����
	CFindUserDlg					* m_pFindUserDlg;					//��

	//������Ϣ����
	CShortMessage * ActiveShortWnd(long int dwUserID, IUserItem * pUserItem, bool bCreate);
	CShow * ActiveShowWnd(long int dwUserID, IUserItem * pUserItem, bool bCreate);

	DECLARE_MESSAGE_MAP()

};

//////////////////////////////////////////////////////////////////////////
