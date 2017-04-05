#include "Stdafx.h"
#include "Resource.h"
#include "DlgLogon.h"
#include "GlobalUnits.h"
#include "DlgControlBar.h"
#include ".\dlglogon.h"

#define FACE_COUNT			50									//ͷ����Ŀ

#define LOGON_BGCOLOR      ((COLORREF)0xffffff)

//��ɫ����
#define SELECT_COLOR		RGB(37,56,220)						//ѡ����ɫ

#define AD_LEFT				194
#define AD_TOP				39

//������Ϣ
tagProxyInfo				CDlgLogon::m_ProxyInfo;					//������Ϣ


//////////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CDlgRegister, CSkinDialogEx)
END_MESSAGE_MAP()
//���캯��
CDlgRegister::CDlgRegister() : CSkinDialogEx(IDD_REGISTER)
{
	//��¼��Ϣ
	m_wFaceID=0;
	m_szAccounts[0]=0;

	return;
}

//��������
CDlgRegister::~CDlgRegister()
{
}
//�ؼ���
void CDlgRegister::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btLogon);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_USER_FACE, m_FaceSelect);
	DDX_Control(pDX, IDC_MAIN_PAGE, m_LineMainPage);
	DDX_Control(pDX, IDC_PASSWORD_PROTECT, m_LinePassWord);
}

//��ʼ������
BOOL CDlgRegister::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("�ʺ�ע��"));

	//��������
	((CComboBox *)(GetDlgItem(IDC_ACCOUNTS)))->LimitText(NAME_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD)))->LimitText(PASS_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD2)))->LimitText(PASS_LEN-1);
	m_LineMainPage.SetHyperLinkUrl(TEXT("http://"ServerDomain));
	m_LinePassWord.SetHyperLinkUrl(TEXT("http://"ServerDomain));

	CBitmap Image;
	//Image.LoadBitmap(IDB_FACE_NORMAL);
	m_ImageList.Create(32,32,ILC_COLOR16|ILC_MASK,0,0);
	m_ImageList.Add(&Image,RGB(255,0,255));
	m_FaceSelect.SetImageList(&m_ImageList);

	COMBOBOXEXITEM Item;
	ZeroMemory(&Item,sizeof(Item));
	Item.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	for (int i=0;i<50;i++) 
	{
		Item.iImage=i;
		Item.iSelectedImage=i;
		m_FaceSelect.InsertItem(&Item);
	}

	m_wFaceID=rand()%50;
	m_FaceSelect.SetCurSel(m_wFaceID);

	return TRUE;
}

//ȷ������
void CDlgRegister::OnOK()
{
	CString strBuffer;

	GetDlgItemText(IDC_ACCOUNTS,strBuffer);
	strBuffer.TrimLeft();
	strBuffer.TrimRight();
	if (strBuffer.IsEmpty())
	{
		AfxMessageBox(TEXT("�ʺ����ֲ���Ϊ�գ�����������ע���ʺţ�"),MB_ICONQUESTION);
		GetDlgItem(IDC_ACCOUNTS)->SetFocus();
		return;
	}
	lstrcpyn(m_szAccounts,strBuffer,CountArray(m_szAccounts));

	GetDlgItemText(IDC_PASSWORD,strBuffer);
	if (strBuffer.IsEmpty())
	{
		AfxMessageBox(TEXT("��Ϸ���벻��Ϊ�գ�������������Ϸ���룡"),MB_ICONQUESTION);
		GetDlgItem(IDC_PASSWORD)->SetFocus();
		return;
	}

	GetDlgItemText(IDC_PASSWORD2,m_strPassWord);
	if (strBuffer!=m_strPassWord)
	{
		AfxMessageBox(TEXT("��Ϸ������ȷ�����벻һ�£�����������ȷ�����룡"),MB_ICONQUESTION);
		GetDlgItem(IDC_PASSWORD2)->SetFocus();
		return;
	}

	m_wFaceID=(FACE_COUNT-m_FaceSelect.GetCurSel()-1);

	__super::OnOK();
}

//ȡ����Ϣ
void CDlgRegister::OnCancel()
{
	__super::OnCancel();
}


//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CDlgLogon, CDialog)
	ON_CBN_SELCHANGE(IDC_ACCOUNTS, OnSelchangeAccounts)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_NET_OPTION, OnBnClickedNetOption)
	ON_BN_CLICKED(IDC_DELETE_RECORD, OnDeleteAccounts)
	ON_BN_CLICKED(IDB_LOGON_FINDPASS,  OnBnClickedFindPass)

	ON_BN_CLICKED(IDC_FORGET,  OnBnClickedFindPass)
	ON_BN_CLICKED(IDC_REGISTER,  OnBnClickedReg)

	ON_BN_CLICKED(IDB_LOGON_WEBSITE,  OnBnClickedWebSite)
	ON_BN_CLICKED(IDB_LOGON_REG,  OnBnClickedReg)
	
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

HBRUSH CDlgLogon::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID() == IDC_REMEMBER_PASSWORD)
	{
		//pDC->SetTextColor(RGB(0,255,0));
		//pDC->SetBkColor(RGB(251,255,255));
		m_brBkgnd.CreateSolidBrush(RGB(183,223,227));
		pDC->SetBkColor(RGB(183,223,227));
		//pDC->SetBkMode(TRANSPARENT);		
		return (HBRUSH)m_brBkgnd;
		//return hbr;
	}
	//pDC->SetTextColor(RGB(0,0,255));

	pDC->SetBkMode(TRANSPARENT);
	return hbr;
}


//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgLogon::CDlgLogon() : CDialog(IDD_LOGON)
{
	//��¼��Ϣ
	m_wFaceID=0;
	m_dwUserID=0;
	m_szAccounts[0]=0;

	//������Ϣ
	m_ProxyInfo.wProxyPort=0;
	m_ProxyInfo.cbProxyType=PROXY_NONE;


	//λ����Ϣ
	m_nFullWidth=0;
	m_nFullHeight=0;
	m_bNetOption=false;
	m_bRegister = false;

	return;
}

//��������
CDlgLogon::~CDlgLogon()
{
}

//�ؼ���
void CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_NET_OPTION, m_btNetOption);//��������
		DDX_Control(pDX, IDCANCEL, m_btCancel);//ȡ��
		DDX_Control(pDX, IDOK, m_btLogon);//��½
		
		DDX_Control(pDX, IDC_REGISTER, m_btReg2);//��½
		DDX_Control(pDX, IDC_FORGET, m_btFindPass2);//��½

		DDX_Control(pDX, IDC_DELETE_RECORD, m_btClear);//��½

		DDX_Control(pDX, IDC_STATIC, m_Picture);
}

//��ʼ������
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();

	//дAppPath��ע���
	CRegKey RegAppPath;
	RegAppPath.Open(HKEY_CURRENT_USER,REG_APP_PATH,KEY_WRITE);
	char fpath[MAX_PATH];
	::GetModuleFileName(NULL,fpath,MAX_PATH);
	*strrchr(fpath,'\\')=0;
	RegAppPath.SetStringValue("Path",fpath);


	//SetWindowRgnFromRes(this->GetSafeHwnd(),AfxGetInstanceHandle(),TEXT("RGN_LOGON"),TEXT("BIN"));

	LayerWindow(this->GetSafeHwnd(),230);

	//if(!m_AdImage.Load("./AD.png",CXIMAGE_FORMAT_PNG))
	//{
	//	m_AdImage.LoadResource(FindResource(NULL,TEXT("IDB_LOGON_AD"),RT_BITMAP),CXIMAGE_FORMAT_BMP);
	//}

	if (!m_Picture.Load("./ad.gif"))
	{
		m_Picture.Load(MAKEINTRESOURCE(IDR_AD),_T("GIF"));
	}

	m_Picture.Draw();		

	m_Logon.LoadResource(FindResource(NULL,TEXT("IDB_LOGON"),RT_BITMAP),CXIMAGE_FORMAT_BMP);
	//m_Logon_T.LoadResource(FindResource(NULL,TEXT("IDB_LOGON_T"),RT_BITMAP),CXIMAGE_FORMAT_BMP);
	//m_Logon_L.LoadResource(FindResource(NULL,TEXT("IDB_LOGON_L"),RT_BITMAP),CXIMAGE_FORMAT_BMP);
	//m_Logon_R.LoadResource(FindResource(NULL,TEXT("IDB_LOGON_R"),RT_BITMAP),CXIMAGE_FORMAT_BMP);
	//m_Logon_M.LoadResource(FindResource(NULL,TEXT("IDB_LOGON_M"),RT_BITMAP),CXIMAGE_FORMAT_BMP);
	//m_Logon_B.LoadResource(FindResource(NULL,TEXT("IDB_LOGON_B"),RT_BITMAP),CXIMAGE_FORMAT_BMP);

	//m_btFindPass.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(140,26,0,0),this,IDB_LOGON_FINDPASS);
	//m_btWebSite.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(200,26,0,0),this,IDB_LOGON_WEBSITE);
	//m_btReg.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(260,26,0,0),this,IDB_LOGON_REG);

	//����ͼƬ
	//m_btFindPass.SetButtonImage(IDB_LOGON_FINDPASS,AfxGetInstanceHandle(),false);
	//m_btWebSite.SetButtonImage(IDB_LOGON_WEBSITE,AfxGetInstanceHandle(),false);
	//m_btReg.SetButtonImage(IDB_LOGON_REG,AfxGetInstanceHandle(),false);

	//���ñ���
	SetWindowText(TEXT("��Ϸ��¼"));
    COLORREF BGColor=RGB(255,224,125);
	COLORREF NormalTextColor=RGB(143,107,29);
	COLORREF HoverTextColor=RGB(0,0,255);
	COLORREF VisitedTextColor=RGB(255,0,0);



	//��������
	((CComboBox *)(GetDlgItem(IDC_ACCOUNTS)))->LimitText(NAME_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PASSWORD)))->LimitText(PASS_LEN-1);
	((CEdit *)(GetDlgItem(IDC_PROXY_PORT)))->LimitText(5);

	//��������
	m_ProxyInfo.wProxyPort=AfxGetApp()->GetProfileInt(REG_OPTION_LOGON,TEXT("ProxyPort"),8080);
	m_ProxyInfo.cbProxyType=AfxGetApp()->GetProfileInt(REG_OPTION_LOGON,TEXT("ProxyType"),PROXY_NONE);
	m_ProxyInfo.strProxyName=AfxGetApp()->GetProfileString(REG_OPTION_LOGON,TEXT("ProxyName"),TEXT(""));
	m_ProxyInfo.strProxyPass=AfxGetApp()->GetProfileString(REG_OPTION_LOGON,TEXT("ProxyPass"),TEXT(""));
	m_ProxyInfo.strProxyServer=AfxGetApp()->GetProfileString(REG_OPTION_LOGON,TEXT("ProxyServer"),TEXT(""));

	//���ÿؼ�
	CComboBox * pProxyCom=(CComboBox *)GetDlgItem(IDC_PROXY_TYPE);
	pProxyCom->AddString(TEXT("��ʹ�ô���"));
	int iItem=pProxyCom->AddString(TEXT("SOCK 4 ����"));
	pProxyCom->SetItemData(iItem,PROXY_SOCKS4);
	if (m_ProxyInfo.cbProxyType==PROXY_SOCKS4) pProxyCom->SetCurSel(iItem);
	iItem=pProxyCom->AddString(TEXT("SOCK 5 ����"));
	pProxyCom->SetItemData(iItem,PROXY_SOCKS5);
	if (m_ProxyInfo.cbProxyType==PROXY_SOCKS5) pProxyCom->SetCurSel(iItem);
	if (pProxyCom->GetCurSel()==CB_ERR) pProxyCom->SetCurSel(0);

	//���ô���
	SetDlgItemText(IDC_PROXY_SERVER,m_ProxyInfo.strProxyServer);
	SetDlgItemText(IDC_PROXY_USER,m_ProxyInfo.strProxyName);
	SetDlgItemText(IDC_PROXY_PASS,m_ProxyInfo.strProxyPass);
	SetDlgItemInt(IDC_PROXY_PORT,m_ProxyInfo.wProxyPort);

	//�ƶ�λ��
	GetWindowRect(&m_rcNormalFrame);

	m_nFullWidth=m_rcNormalFrame.Width();
	m_nFullHeight=m_rcNormalFrame.Height();
	m_rcNormalFrame.bottom=m_rcNormalFrame.top+348;

	MoveWindow(m_rcNormalFrame.right,m_rcNormalFrame.top,510,310,1);
	//MoveWindow(&m_rcNormalFrame);
	CenterWindow();

	GetWindowRect(&m_rcNormalFrame);
	m_nFullWidth=m_rcNormalFrame.Width();
	m_nFullHeight=409;

	//��¼����
	if (g_GlobalOption.m_enAcountsRule==enAcountsRule_AccountsAndPass)
		((CButton *)GetDlgItem(IDC_REMEMBER_PASSWORD))->SetCheck(BST_CHECKED);

	//������Ϣ
	LoadLogonServer();
	LoadAccountsInfo();

	//��������
	if ((m_ProxyInfo.cbProxyType!=PROXY_NONE)&&(m_bNetOption==false))
	{
		OnBnClickedNetOption();
	}

	//���ý���
	if (GetDlgItem(IDC_ACCOUNTS)->GetWindowTextLength()==0)
	{
		GetDlgItem(IDC_ACCOUNTS)->SetFocus();
		((CComboBox *)GetDlgItem(IDC_ACCOUNTS))->SetEditSel(0,-1);
	}
	else 
	{
		GetDlgItem(IDC_PASSWORD)->SetFocus();
		((CEdit *)GetDlgItem(IDC_PASSWORD))->SetSel(0,-1);
	}

	return FALSE;
}

//��Ϣ����
BOOL CDlgLogon::PreTranslateMessage(MSG * pMsg)
{
	return __super::PreTranslateMessage(pMsg);
}




//ȷ������
void CDlgLogon::OnOK()
{
	//Ч������
	if (CheckLogonInput(true)==false) return;

	//��½�㳡
	//ShowWindow(SW_HIDE);
	IPlazaViewItem * pIPlazaViewItem=g_pControlBar->GetPlazaViewItem();
	ASSERT(pIPlazaViewItem!=NULL);
	pIPlazaViewItem->SendConnectMessage();

	return;
}

//ȡ����Ϣ
void CDlgLogon::OnCancel()
{
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	return;
}

//ȡ����Ϣ
void CDlgLogon::OnExit()
{
	AfxMessageBox(TEXT("������������"),MB_ICONQUESTION);
    DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	return;
}

//���͵�¼��
bool CDlgLogon::SendLogonPacket(IClientSocket * pIClientSocke)
{
	//��������
	TCHAR szPassword[33];
	BYTE cbBuffer[SOCKET_PACKAGE];
	CMD5Encrypt::EncryptData(m_strPassWord,szPassword);

	if (m_bRegister==false)
	{
		//��������
		CMD_GP_LogonByAccounts * pLogonByAccounts=(CMD_GP_LogonByAccounts *)cbBuffer;
		memset(pLogonByAccounts,0,sizeof(CMD_GP_LogonByAccounts));
		pLogonByAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
		CopyMemory(pLogonByAccounts->szPassWord,szPassword,sizeof(pLogonByAccounts->szPassWord));
		lstrcpyn(pLogonByAccounts->szAccounts,m_szAccounts,CountArray(pLogonByAccounts->szAccounts));
		lstrcpyn(pLogonByAccounts->szRealityPass,m_strPassWord,CountArray(pLogonByAccounts->szRealityPass));

		//�������к�
		tagClientSerial ClientSerial;
		g_GlobalUnits.GetClientSerial(ClientSerial);

		//�������ݰ�
		CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LogonByAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_LogonByAccounts));
		Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
		pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_LOGON_ACCOUNTS,cbBuffer,sizeof(CMD_GP_LogonByAccounts)+Packet.GetDataSize());
	}
	else
	{
		//��������
		CMD_GP_RegisterAccounts * pRegisterAccounts=(CMD_GP_RegisterAccounts *)cbBuffer;
		memset(pRegisterAccounts,0,sizeof(CMD_GP_RegisterAccounts));
		pRegisterAccounts->wFaceID=m_wFaceID;
		pRegisterAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
		CopyMemory(pRegisterAccounts->szPassWord,szPassword,sizeof(pRegisterAccounts->szPassWord));
		lstrcpyn(pRegisterAccounts->szAccounts,m_szAccounts,CountArray(pRegisterAccounts->szAccounts));

		//�������к�
		tagClientSerial ClientSerial;
		g_GlobalUnits.GetClientSerial(ClientSerial);

		//�������ݰ�
		CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_RegisterAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_RegisterAccounts));
		Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
		pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_REGISTER_ACCOUNTS,cbBuffer,sizeof(CMD_GP_RegisterAccounts)+Packet.GetDataSize());
		m_bRegister=false;
	}
	return true;
}

//��½�ɹ�����
bool CDlgLogon::OnLogonSuccess()
{
	//��¼����
	BOOL bRemPassword=(((CButton *)GetDlgItem(IDC_REMEMBER_PASSWORD))->GetCheck()==BST_CHECKED);
	AfxGetApp()->WriteProfileString(REG_OPTION_LOGON,TEXT("LogonServer"),m_strLogonServer);

	//������Ϣ
	if (bRemPassword) g_GlobalOption.m_enAcountsRule=enAcountsRule_AccountsAndPass;

	//�û���Ϣ
	//
	tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
	AfxGetApp()->WriteProfileString(REG_OPTION_LOGON,TEXT("LastAccounts"),UserData.szAccounts);


	//д���û���¼
	TCHAR szBuffer[256];
	if (g_GlobalOption.m_enAcountsRule!=enAcountsRule_None)
	{
		CRegKey RegUserInfo;
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%s\\%s"),REG_USER_INFO,UserData.szAccounts);
		if (RegUserInfo.Create(HKEY_CURRENT_USER,szBuffer)==ERROR_SUCCESS)
		{
			TCHAR szPassBuffer[256]=TEXT("");
			if (bRemPassword) CXOREncrypt::EncryptData(m_strPassWord,szPassBuffer,CountArray(szPassBuffer));
			RegUserInfo.SetKeyValue(TEXT(""),UserData.szAccounts,TEXT("UserAccount"));
			RegUserInfo.SetKeyValue(TEXT(""),UserData.szPassWord,TEXT("UserPassToken"));
			RegUserInfo.SetKeyValue(TEXT(""),szPassBuffer,TEXT("UserPassword"));
		}
	}
	else
	{
		CRegKey RegUserID;
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%ld"),UserData.dwUserID);
		if (RegUserID.Open(HKEY_CURRENT_USER,REG_USER_INFO)==ERROR_SUCCESS)	RegUserID.RecurseDeleteKey(szBuffer);
	}

	//�رմ���
	DestroyWindow();

	return true;
}

//��ȡ�ʺ�
void CDlgLogon::LoadAccountsInfo()
{
	//��������
	CComboBox * pComBoxAccounts=(CComboBox *)GetDlgItem(IDC_ACCOUNTS);

	//��ȡ��Ϣ
	CRegKey RegUserInfo;
	RegUserInfo.Open(HKEY_CURRENT_USER,REG_USER_INFO,KEY_READ);
	if (RegUserInfo!=NULL)
	{
		int iInsertItem=CB_ERR;
		LONG lErrorCode=ERROR_SUCCESS;
		DWORD dwType=REG_SZ,dwIndex=0,dwUserDBID=0;
		TCHAR szUserIDBuffer[32]=TEXT(""),szTempBuffer[256]=TEXT("");
		do
		{
			//���ñ���
			szTempBuffer[0]=0;
			szUserIDBuffer[0]=0;

			//��ȡ��Ϸ ID
			DWORD dwBufferSize=sizeof(szUserIDBuffer);
			if (RegUserInfo.EnumKey(dwIndex++,szUserIDBuffer,&dwBufferSize,NULL)!=ERROR_SUCCESS) break;
			if(strlen(szUserIDBuffer)<1)
				continue;
			//����������Ϣ
			CRegKey RegUserAccount;
			_snprintf(szTempBuffer,sizeof(szTempBuffer),TEXT("%s\\%s"),REG_USER_INFO,szUserIDBuffer);
			RegUserAccount.Open(HKEY_CURRENT_USER,szTempBuffer,KEY_READ);
			if (RegUserAccount!=NULL)
			{
				//��Ϸ�ʺ�
				dwBufferSize=sizeof(szTempBuffer);
				lErrorCode=RegUserAccount.QueryValue(TEXT("UserAccount"),&dwType,szTempBuffer,&dwBufferSize);
				if ((lErrorCode==ERROR_SUCCESS)&&(szTempBuffer[0]!=0)&&(ComboBoxFindString(pComBoxAccounts,szTempBuffer)==LB_ERR))
				{
					iInsertItem=pComBoxAccounts->AddString(szTempBuffer);
					pComBoxAccounts->SetItemData(iInsertItem,dwUserDBID);
				}
			}
		} while (true);
	}

	//��ȡ�����½�û�
	CString strLastUserID=AfxGetApp()->GetProfileString(REG_OPTION_LOGON,TEXT("LastAccounts"),NULL);
	if (strLastUserID.IsEmpty()==FALSE)
	{
		SelectAccounts(strLastUserID,true);
	}

	return;
}

void CDlgLogon::SelectAccounts(LPCSTR pszAccounts,bool bChangeUser)
{
	if(bChangeUser)
	{
		CComboBox * pComBoxAccounts=(CComboBox *)GetDlgItem(IDC_ACCOUNTS);
		pComBoxAccounts->SelectString(-1,pszAccounts);
	}

	CEdit * pPassWord=(CEdit *)(GetDlgItem(IDC_PASSWORD));

	TCHAR szTempBuffer[256]=TEXT("");
	CRegKey RegPassword;
	_snprintf(szTempBuffer,sizeof(szTempBuffer),TEXT("%s\\%s"),REG_USER_INFO,pszAccounts);
	RegPassword.Open(HKEY_CURRENT_USER,szTempBuffer,KEY_READ);

	//��Ϸ�ʺ�
	ULONG dwBufferSize=sizeof(szTempBuffer);
	DWORD dwType;
	dwBufferSize=RegPassword.QueryValue(TEXT("UserPassword"),&dwType,szTempBuffer,&dwBufferSize);
	if ((dwBufferSize==ERROR_SUCCESS)&&(szTempBuffer[0]!=0))
	{
		m_strPassWord.Empty();
		LPTSTR pszScrPass=m_strPassWord.GetBuffer(PASS_LEN+1);
		CXOREncrypt::CrevasseData(szTempBuffer,pszScrPass,PASS_LEN+1);
		m_strPassWord.ReleaseBuffer();
		SetDlgItemText(IDC_PASSWORD,m_strPassWord);
		((CButton *)GetDlgItem(IDC_REMEMBER_PASSWORD))->SetCheck(BST_CHECKED);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_REMEMBER_PASSWORD))->SetCheck(BST_UNCHECKED);
		SetDlgItemText(IDC_PASSWORD,TEXT(""));
	}
}



//ѡ��ı�
void CDlgLogon::OnSelchangeAccounts()
{
CString szUser;
	CComboBox * pComBoxAccounts=(CComboBox *)GetDlgItem(IDC_ACCOUNTS);
	pComBoxAccounts->GetLBText(pComBoxAccounts->GetCurSel(),szUser);
	SelectAccounts(szUser,false);
	return;
}

//���ط�����
void CDlgLogon::LoadLogonServer()
{
	//��ȡ�����½������
	CComboBox * pComBoxServer=(CComboBox *)GetDlgItem(IDC_SERVER);
	m_strLogonServer=AfxGetApp()->GetProfileString(REG_OPTION_LOGON,TEXT("LogonServer"),NULL);
	if (m_strLogonServer.IsEmpty()==FALSE)
	{
		pComBoxServer->AddString(m_strLogonServer);
		pComBoxServer->SetWindowText(m_strLogonServer);
	}

	//��ȡ�������б�
	CRegKey RegLogonServer;
	RegLogonServer.Open(HKEY_CURRENT_USER,REG_LOGON_SERVER,KEY_READ);
	if (RegLogonServer!=NULL)
	{
		TCHAR szLogonServer[128]=TEXT("");
		DWORD dwIndex=0,dwBufferSize=sizeof(szLogonServer);
		do
		{
			dwBufferSize=sizeof(szLogonServer);
			if (RegLogonServer.EnumKey(dwIndex++,szLogonServer,&dwBufferSize,NULL)!=ERROR_SUCCESS) break;
			if (szLogonServer[0]!=0)
			{
				if (m_strLogonServer.IsEmpty()) m_strLogonServer=szLogonServer;
				if (ComboBoxFindString(pComBoxServer,szLogonServer)==LB_ERR) pComBoxServer->AddString(szLogonServer);
			}
		} while (true);
	}

	//����ѡ��
	if ((pComBoxServer->GetWindowTextLength()==0)&&(pComBoxServer->GetCount()>0)) pComBoxServer->SetCurSel(0);
	if (pComBoxServer->GetCount()==0)
	{
		pComBoxServer->AddString(ServerDomain);
		pComBoxServer->SetCurSel(0);
	}

	return;
}

//��������
int CDlgLogon::ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString)
{
	CString strBuffer;
	int iItemHandle=LB_ERR,iItemFind=LB_ERR;
	int nStringLen=lstrlen(pszFindString);
	do 
	{
		iItemFind=pComboBox->FindString((iItemHandle==LB_ERR)?0:(iItemHandle+1),pszFindString);
		if ((iItemFind==LB_ERR)||(iItemHandle==iItemFind)||(iItemFind<iItemHandle)) return LB_ERR;
		iItemHandle=iItemFind;
		pComboBox->GetLBText(iItemHandle,strBuffer);
		if (pComboBox->GetLBTextLen(iItemHandle)==nStringLen) return iItemHandle;
	} while (true);
	return LB_ERR;
}

//Ч������
bool CDlgLogon::CheckLogonInput(bool bShowError)
{
	//�������
	UINT uControlID=0;
	CString strBuffer;

	try
	{
		//��¼������
		GetDlgItemText(IDC_SERVER,m_strLogonServer);
		m_strLogonServer.TrimLeft();
		m_strLogonServer.TrimRight();
		if (m_strLogonServer.IsEmpty())
		{
			uControlID=IDC_SERVER;
			throw TEXT("��¼����������Ϊ�գ�������ѡ����������¼��������");
		}

		//��¼�ʺ�

		GetDlgItemText(IDC_ACCOUNTS,strBuffer);
		strBuffer.TrimLeft();
		strBuffer.TrimRight();
		if (strBuffer.IsEmpty())
		{
			uControlID=IDC_ACCOUNTS;
			throw TEXT("�û���¼�ʺŲ���Ϊ�գ������������¼�ʺţ�");
		}
		lstrcpyn(m_szAccounts,strBuffer,CountArray(m_szAccounts));


		//�û�����
		GetDlgItemText(IDC_PASSWORD,m_strPassWord);
		if (m_strPassWord.IsEmpty())
		{
			uControlID=IDC_PASSWORD;
			throw TEXT("��¼���벻��Ϊ�գ������������¼���룡");
		}

		//������Ϣ
		m_ProxyInfo.wProxyPort=GetDlgItemInt(IDC_PROXY_PORT,NULL,FALSE);
		GetDlgItemText(IDC_PROXY_USER,m_ProxyInfo.strProxyName);
		GetDlgItemText(IDC_PROXY_PASS,m_ProxyInfo.strProxyPass);
		GetDlgItemText(IDC_PROXY_SERVER,m_ProxyInfo.strProxyServer);
		CComboBox * pProxyCom=(CComboBox *)GetDlgItem(IDC_PROXY_TYPE);
		int iItem=pProxyCom->GetCurSel();
		m_ProxyInfo.cbProxyType=(BYTE)pProxyCom->GetItemData(iItem);
		if (m_ProxyInfo.cbProxyType!=PROXY_NONE)
		{
			if (m_ProxyInfo.strProxyServer.IsEmpty())
			{
				uControlID=IDC_PROXY_SERVER;
				throw TEXT("�����������ַ����Ϊ�գ���������������������ַ��");
			}
		}

		return true;
	}
	catch (LPCTSTR pszError)
	{
		if (bShowError)
		{
			ShowWindow(SW_SHOW);
			BringWindowToTop();
			AfxMessageBox(pszError,MB_ICONQUESTION);
			if (uControlID!=0) GetDlgItem(uControlID)->SetFocus();
		}

	}
	return false;
}


//��������
void CDlgLogon::OnBnClickedNetOption()
{
	m_bNetOption=!m_bNetOption;
	GetDlgItem(IDC_PROXY_TYPE)->EnableWindow(m_bNetOption);
	GetDlgItem(IDC_PROXY_SERVER)->EnableWindow(m_bNetOption);
	GetDlgItem(IDC_PROXY_PORT)->EnableWindow(m_bNetOption);
	GetDlgItem(IDC_PROXY_USER)->EnableWindow(m_bNetOption);
	GetDlgItem(IDC_PROXY_PASS)->EnableWindow(m_bNetOption);
	int nHeight=m_bNetOption?m_nFullHeight:m_rcNormalFrame.Height();
	SetWindowPos(GetParent(),0,0,m_nFullWidth,nHeight,SWP_NOMOVE);

	return;
}

//�һ�����
afx_msg void CDlgLogon::OnBnClickedFindPass()
{
	g_GlobalUnits.GoWeb("/Client/Forget.asp");
}

//�ٷ���վ
afx_msg void CDlgLogon::OnBnClickedWebSite()
{
	g_GlobalUnits.GoWeb("/");
}
//��Ϸע��
afx_msg void CDlgLogon::OnBnClickedReg()
{
	g_GlobalUnits.GoWeb("/Client/Reg.asp");
	//OnRegisterAccounts();
}

//ע���ʺ�
void CDlgLogon::OnRegisterAccounts()
{
	//*

	CDlgRegister DlgRegister;
	ShowWindow(SW_HIDE);
	if (DlgRegister.DoModal()!=IDOK) 
	{
		ShowWindow(SW_SHOW);
		return;
	}

	//���ñ���
	m_bRegister=true;
	m_wFaceID=DlgRegister.m_wFaceID;
	m_strPassWord=DlgRegister.m_strPassWord;
	lstrcpy(m_szAccounts,DlgRegister.m_szAccounts);

	//������
	GetDlgItemText(IDC_SERVER,m_strLogonServer);
	if (m_strLogonServer.IsEmpty()) m_strLogonServer=ServerDomain;

	//��½�㳡
	ShowWindow(SW_HIDE);
	IPlazaViewItem * pIPlazaViewItem=g_pControlBar->GetPlazaViewItem();
	ASSERT(pIPlazaViewItem!=NULL);
	pIPlazaViewItem->SendConnectMessage();
	return;
    
	//*/
}

//ɾ����½�û���Ϣ
void CDlgLogon::OnDeleteAccounts() 
{
	//��ȡ����
	UINT uComboBoxID=0;

	CComboBox * pComboBox=(CComboBox *)GetDlgItem(IDC_ACCOUNTS);

	//ɾ����Ϣ
	CString strBuffer;
	pComboBox->GetWindowText(strBuffer);
	pComboBox->SetWindowText(TEXT(""));
	if (strBuffer.IsEmpty()) return;
	int iSelectItem=ComboBoxFindString(pComboBox,strBuffer);
	if (iSelectItem!=LB_ERR)
	{
		CRegKey RegAccounts;
		CString strAccounts;

		pComboBox->GetWindowText(strAccounts);

		RegAccounts.Open(HKEY_CURRENT_USER,REG_USER_INFO);
		if (RegAccounts!=NULL) RegAccounts.RecurseDeleteKey(strAccounts);

		//ɾ��ѡ����Ϣ
		CComboBox * pOtherComboBox=NULL;

		pOtherComboBox=(CComboBox *)GetDlgItem(IDC_ACCOUNTS);
		for (int j=0;j<pOtherComboBox->GetCount();j++)
		{
			pOtherComboBox->DeleteString(j);
		}

	}

	return;
}

//////////////////////////////////////////////////////////////////////////

void CDlgLogon::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CRect rc;
	GetClientRect(rc);

	dc.FillRect(rc,&CBrush((COLORREF)LOGON_BGCOLOR));

	m_Logon.Draw(dc,0,0);

	m_AdImage.Draw(dc,AD_LEFT,AD_TOP);
	//m_Logon_T.Draw(dc,0,0);
	//m_Logon_L.Draw(dc,0,48);
	//m_Logon_R.Draw(dc,322-6,48);
	////m_Logon_M.Draw(dc,6,260);
	//m_Logon_B.Draw(dc,0,rc.bottom-7);

	DWORD textAlignment = THA_LEFT | TVA_TOP;
	RECT margins = {0,0,0,0};
	dc.SetBkMode(TRANSPARENT);
	m_TR.m_color=0x942525;//0x111197
	m_TR.SetFontFace("����",12);
	//m_TR.EnhDrawText2( dc, "\\b0��������",35,174);
	//m_TR.EnhDrawText2( dc, "\\b0�û�����",35,198);
	//m_TR.EnhDrawText2( dc, "\\b0���룺",35,222);

	//m_TR.EnhDrawText2( dc, "\\b0��ס����",195,222);

	m_TR.EnhDrawText2( dc, "\\b0���ͣ�",20,329);
	m_TR.EnhDrawText2( dc, "\\b0��ַ��",20,351);
	m_TR.EnhDrawText2( dc, "\\b0�û���",20,371);

	m_TR.EnhDrawText2( dc, "\\b0�˿ڣ�",170,351);
	m_TR.EnhDrawText2( dc, "\\b0���룺",170,371);

	//m_TR.EnhDrawText( dc, "\\b0��������", (11), &CRect(20,120,(100),(100)), &margins, textAlignment );

}






BOOL CDlgLogon::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return false;
}

void CDlgLogon::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if(point.y<25)
	//{
		SendMessage(WM_NCLBUTTONDOWN, HTCAPTION,0);
	//}
	//CRect rc(AD_LEFT,AD_TOP,AD_LEFT + m_Picture.GetWidth(),AD_TOP+m_Picture.GetHeight());
	
	CRect rect;
	m_Picture.GetWindowRect(&rect);
	ScreenToClient(&rect);

	if(PtInRect(rect,point))
	{
		g_GlobalUnits.GoWeb("/Client/LoginAd.asp",false);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CDlgLogon::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);
	
	CRect rect;
	m_Picture.GetWindowRect(&rect);
	ScreenToClient(&rect);


	if(PtInRect(rect,MousePoint))
	{
		SetCursor(LoadCursor(0,MAKEINTRESOURCE(32649)));
		return true;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}
