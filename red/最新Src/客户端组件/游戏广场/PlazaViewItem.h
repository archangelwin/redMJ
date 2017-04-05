//***********************************************
//File		: PlazaViewItem.h 
//Time		: 
//Author	: Anson
//Comment	: ��Ϸ�㳡��
//***********************************************


#pragma once


#include "Stdafx.h"
#include "DlgLogon.h"
#include "ServerItemView.h"
#include "vector"

#include "TextRender.h"



struct tagGameButton
{
	CRgnButton Button;
	WORD wKindID;
	TCHAR szKindName[KIND_LEN];//��Ϸ����
};

//
//CPlazaViewItem(��Ϸ�㳡��)
//
class CPlazaViewItem : public CDialog, public IPlazaViewItem, 
						public IClientSocketSink, 
						public ITreeCtrlSink
{
	//״̬����
protected:
	bool						m_bRectify;				//������־
	bool						m_bInitDialog;			//��ʼ��־
	bool						m_bLogonPlaza;			//��¼��־

	//�ؼ�����
public:
	CDlgLogon					m_DlgLogon;				//��½�Ի���
	//CHtmlBrower				*m_pHtmlBrower;			//�������
	CHtmlBrower					*m_pHtmlBrower1;		//�������
	CServerItemView				m_ServerItemView;		//��������ͼ
	CClientSocketHelper			m_ClientSocket;			//��������

	TransButton					m_btGame1;
	TransButton					m_btGame2;
	TransButton					m_btGame3;

public:
	//��Ϸͼ�갴ť��
	std::vector<tagGameButton*>		m_GameButtons;
	CImageListCtrl					m_RoomList;
	CImageListCtrl					m_ServerList;

	CSkinImage							m_StatusL;						//״̬��
	CSkinImage							m_StatusM;						//״̬��

	//��Ϸ�б�
protected:
	CSkinImage							m_ImageBGMain;					//������ͼƬ
	CSkinImage							m_ImageBGMain2;
	CSkinImage							m_ImageML;						//��߿�
	CSkinImage							m_ImageMR;						//�ұ߿�


	CSkinImage						m_GameListT2;						//��Ϸ�б�
	CxImage							m_GameListT;						//��Ϸ�б�
	CxImage							m_GameListL;						//��Ϸ�б�
	CxImage							m_GameListR;						//��Ϸ�б�
	CxImage							m_GameListM;						//��Ϸ�б�
	CxImage							m_GameListB;						//��Ϸ�б�
	CSkinImage						m_GameListB2;						//��Ϸ�б�
	CxImage							m_GameListScroll;					//��Ϸ�б�


	CTextRenderWnd g_TextRender;											//�ı����Ӷ���

	//��������
public:
	CPlazaViewItem();
	virtual ~CPlazaViewItem();

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


	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CPlazaViewItem))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//��ͼ�ӿ�
public:
	//��ȡ���
	virtual HWND __cdecl GetWindowHandle() { return GetSafeHwnd(); }

	//����ӿ�
public:
	//�������
	virtual void __cdecl OnTreeLeftClick(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//�Ҽ�����
	virtual void __cdecl OnTreeRightClick(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//���˫��
	virtual void __cdecl OnTreeLeftDBClick(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//�Ҽ�˫��
	virtual void __cdecl OnTreeRightDBClick(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//ѡ��ı�
	virtual void __cdecl OnTreeSelectChanged(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);
	//����չ��
	virtual void __cdecl OnTreeItemexpanded(CListItem * pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl);

	//����ӿ�
public:
	//����������Ϣ
	virtual bool __cdecl OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke);
	//�����ȡ��Ϣ
	virtual bool __cdecl OnSocketRead(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//����ر���Ϣ
	virtual bool __cdecl OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer);

	//��Ϣ����
protected:
	//��½��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//�б���Ϣ
	bool OnSocketMainServerList(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//ϵͳ��Ϣ
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);

	//�㳡�ӿ�
public:
	//��¼��Ϣ
	virtual bool __cdecl SendLogonMessage();
	//������Ϣ
	virtual bool __cdecl SendConnectMessage();

	//���ܺ���
public:
	//��ʾ��ҳ
	//void WebBrowse(LPCTSTR lpszUrl, bool bForceBrowse);
	//��ʾ��Ϣ
    int ShowMessageBox(LPCTSTR pszMessage, UINT nType);

	//�ڲ�����
private:
	//���±���
	void UpdateTitleText();
	//�滭�б�
	void DrawListFrame(CDC * pDC);
	//�����ؼ�
	void RectifyControl(int nWidth, int nHeight);

public:
	//bluker:��ʾ�����б�
	void ShowServers(tagGameButton* pGameButton);
	void ClearGameButtons();
	//��Ϣ����
protected:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//��¼�㳡
	afx_msg void OnCommandLogon();
	//���ӷ�����
	afx_msg void OnCommandConnect();
	//ȡ������
	afx_msg void OnCommandCancelConnect();
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��ʾ��Ϣ
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	//bluker:��Ϸ����ͼ�갴ť[����¼�]
	afx_msg void OnBnClicked_GameButtons();


	//�����б��
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};



//-----------------------------------------------
//					the end
//-----------------------------------------------
