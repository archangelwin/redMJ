#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "..\..\�������\��������\HtmlBrowser.h"
#include "PictureEx.h"

//////////////////////////////////////////////////////////////////////////


//ע�������
#define REG_OPTION_LOGON		TEXT("OptionLogon")
#define REG_APP_PATH			TEXT("Software\\"szSystemRegKey"\\GamePlaza")
#define REG_USER_INFO			TEXT("Software\\"szSystemRegKey"\\GamePlaza\\UserInfo")
#define REG_LOGON_SERVER		TEXT("Software\\"szSystemRegKey"\\GamePlaza\\LogonServer")

//////////////////////////////////////////////////////////////////////////


//�û�ע��
class CDlgRegister : public CSkinDialogEx
{
	friend class CDlgLogon;

	//��½��Ϣ
public:
	WORD								m_wFaceID;
	TCHAR								m_szAccounts[NAME_LEN];			//��Ϸ�ʺ�
	CString								m_strPassWord;					//��¼����

	//�ؼ�����
public:
	CImageList							m_ImageList;
	CComboBoxEx							m_FaceSelect;
	CSkinButton							m_btLogon;						//��½��ť
	CSkinButton							m_btCancel;						//ȡ����ť
	CSkinHyperLink						m_LineMainPage;					//��Ϸ��ҳ
	CSkinHyperLink						m_LinePassWord;					//���뱣��

	//��������
public:
	//���캯��
	CDlgRegister();
	//��������
	virtual ~CDlgRegister();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK();
	//ȡ����Ϣ
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//��½�Ի���
class CDlgLogon : public CDialog
{
	friend class CRoomViewItem;
	friend class CPlazaViewItem;

	//��½��Ϣ
protected:
	WORD								m_wFaceID;						//ͷ���ʶ
	DWORD								m_dwUserID;						//�û� I D
	TCHAR								m_szAccounts[NAME_LEN];			//��Ϸ�ʺ�
	CString								m_strPassWord;					//��¼����

	CxImage								m_AdImage;
	CPictureEx							m_Picture;


	//������Ϣ
protected:
	bool								m_bRegister;					//ע���־
	CString								m_strLogonServer;				//��������ַ
	static tagProxyInfo					m_ProxyInfo;					//������Ϣ

	//λ�ñ���
protected:
	int									m_nFullWidth;					//ȫ�����
	int									m_nFullHeight;					//ȫ���߶�
	bool								m_bNetOption;					//��������
	CRect								m_rcNormalFrame;				//���λ��

	//�ؼ�����
public:
	CSkinButton							m_btLogon;						//��½��ť
	CSkinButton							m_btCancel;						//ȡ����ť
	CSkinButton							m_btClear;						//ɾ����ť
	CSkinButton							m_btNetOption;					//���簴ť
	CSkinButton							m_btFindPass;					//�һ�����
	CSkinButton							m_btWebSite;					//�ٷ���վ
	CSkinButton							m_btReg;						//��Ϸע��
	CSkinButton							m_btReg2;						//��Ϸע��
	CSkinButton							m_btFindPass2;					//�һ�����

	CTextRenderWnd						m_TR;
public:
	CxImage								m_Logon_T;
	CxImage								m_Logon_L;
	CxImage								m_Logon_R;
	CxImage								m_Logon_M;
	CxImage								m_Logon_B;
	CxImage								m_Logon;

	//��������
public:
	//���캯��
	CDlgLogon();
	//��������
	virtual ~CDlgLogon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush m_brBkgnd;

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK();
	//ȡ����Ϣ
	virtual void OnCancel();
	//���ܺ���
public:
	//��ȡ������
	LPCTSTR GetLogonServer() { return m_strLogonServer; }
	//���͵�¼��
	bool SendLogonPacket(IClientSocket * pIClientSocke);
	//��½�ɹ�����
	bool OnLogonSuccess();

	//�ڲ�����
private:
	//���ط�����
	void LoadLogonServer();
	//��ȡ�ʺ�
	void LoadAccountsInfo();
	//Ч������
	bool CheckLogonInput(bool bShowError);

    void Setup();
	//��������
private:
	//��ʾ�û���½��Ϣ
	void SelectAccounts(LPCSTR pszAccounts,bool bChangeUser);
	//�����ַ�
	int ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString);

	//��Ϣ����
public:
	//ע���ʺ�
	afx_msg void OnRegisterAccounts();
	//ɾ����½�û���Ϣ
	afx_msg void OnDeleteAccounts();
	//ѡ��ı�
	afx_msg void OnSelchangeAccounts();
	//��������
	afx_msg void OnBnClickedNetOption();

	//�һ�����
	afx_msg void OnBnClickedFindPass();;
	//�ٷ���վ
	afx_msg void OnBnClickedWebSite();
	//��Ϸע��
	afx_msg void OnBnClickedReg();



	//�˳�
	afx_msg void OnExit();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

//////////////////////////////////////////////////////////////////////////

#endif