#include "Stdafx.h"
#include "Resource.h"
#include "DlgLogon.h"
#include "GlobalUnits.h"
#include "RoomViewItem.h"
#include "DlgControlBar.h"

#include "GamePlaza.h"
#include "GameFrame.h"
#include "BCMenu.h"
#include ".\roomviewitem.h"

#define		IDC_BT_BUTTON_ROOM1	8888			//���ܰ�ť
#define		IDC_BT_BUTTON_ROOM2	8889			//���ܰ�ť
#define		IDC_BT_BUTTON_ROOM3	8890			//���ܰ�ť
#define		IDC_BT_BUTTON_ROOM4	8891			//���ܰ�ť
#define		IDC_BT_BUTTON_ROOM5	8892			//���ܰ�ť
#define		IDC_BT_BUTTON_ROOM6	8892			//���ܰ�ť

#define		IDC_BT_BUTTON_ROOMEXIT 9999			//���ܰ�ť
//////////////////////////////////////////////////////////////////////////


//��ť����
#define	BUTTON_AREA_WIDTH			200									//��ť����

//�������
#define	SR_CREATE_ERROR				0									//��������
#define	SR_CREATE_SUCCESS			1									//�����ɹ�
#define	SR_ALREADY_EXIST			2									//�Ѿ�����

#define IDI_CHECK_GAMECLIENT		501									//�����Ϸ�Ƿ�������,������˾���ʾ����

//�����
#define LEFT_FRAME_WIDTH 229

//���촰�ڵ��ױߵľ���
#define CHAT_BOTTOM_DISTANCE 0

//���촰�ڵĸ߶�
#define CHAT_HEIGHT 140


//////////////////////////////////////////////////////////////////////////
//�˵�����

//����˵�
#define	IDM_UM_WISPER				WM_USER+100							//˽�Ĳ˵�
#define	IDM_UM_COPY_NAME			WM_USER+101							//��������
#define	IDM_UM_SET_CHAT				WM_USER+102							//��������
#define	IDM_UM_CANECL_CHAT			WM_USER+103							//ȡ������
#define	IDM_UM_LOOK_LOCATION		WM_USER+104							//�鿴λ��
#define	IDM_UM_INVITE_PLAY			WM_USER+105							//������Ϸ
#define	IDM_UM_SEARCH_USER			WM_USER+106							//Ѱ���û�
#define	IDM_UM_SET_FRIEND			WM_USER+107							//��Ϊ����
#define	IDM_UM_SET_DETEST			WM_USER+108							//��Ϊ���
#define IDM_UM_SHOW	                WM_USER+109                         //�鿴SHOW

//��������
#define IDM_UM_MANAGER_USER			WM_USER+150							//Ȩ�޹���
#define IDM_UM_ISSUE_MESSAGE		WM_USER+151							//������Ϣ
#define IDM_IM_SYSTEM_OPTION		WM_USER+152							//ϵͳ����
#define IDM_UM_SEND_WARNNING		WM_USER+153							//���;���
#define IDM_UM_LOOK_USER_IP			WM_USER+154							//�鿴��ַ
#define IDM_UM_CUT_USER				WM_USER+155							//�û�����
#define IDM_UM_LIMIT_ACCOUN			WM_USER+156							//��ֹ�ʻ�

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CRoomViewItem, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_COPYDATA()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_HIT_EXPMESSTION,	OnHitExpression)
	ON_BN_CLICKED(IDC_SEND_CHAT, OnBnClickedSendChat)
	ON_BN_CLICKED(IDC_COLOR_SET, OnBnClickedColorSet)
	ON_BN_CLICKED(IDC_EXPRESSION, OnBnClickedExpression)
	ON_BN_CLICKED(IDC_CLEAN_SCREEN,	OnBnClickedCleanScreen)
	ON_BN_CLICKED(IDB_BT_AUTO_JOIN,	OnBnClickedAutoSit)
	ON_BN_CLICKED(IMG_LISTCTRL_CMD_ID,OnBnUserList_Clicked)
	ON_BN_CLICKED(IDB_BT_SEARCH_USER,	OnBnClickedFindUser)

	ON_BN_CLICKED(IDC_BT_BUTTON_ROOMEXIT,	OnBnClickedRoomExit)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

CRoomViewItem::CRoomViewItem() : CDialog(IDD_GAME_ROOM)
{
	//��������
	m_wGameGenre=0;
	m_bRectify=false;
	m_bInitDialog=false;
	m_dwMenuUserID=0L;
	m_wReqTableID=INVALID_TABLE;
	m_wReqChairID=INVALID_CHAIR;
	m_wFindTableID=INVALID_TABLE;
	memset(&m_ListColumnInfo,0,sizeof(m_ListColumnInfo));

	m_pHtmlBrower1	= NULL;
	m_pHtmlBrower2	= NULL;

	//���ñ���
	m_pGameOption=NULL;
	m_pServerOption=NULL;

	//�����û�
	m_dwChatUserID=0L;
	m_szChatName[0]=0;

	//������Ϣ
	m_szShareName[0]=0;
	m_hWndChannel=NULL;
	m_hShareMemory=NULL;
	m_pShareMemory=NULL;
	memset(&g_GameProcessInfo,0,sizeof(g_GameProcessInfo));

	//���ñ���
	m_pMeUserItem=NULL;
	m_pListServer=NULL;
	m_ServiceStatus=ServiceStatus_Null;
	memset(&m_OptionBuffer,0,sizeof(m_OptionBuffer));

	//����ͼ��
	HINSTANCE hInstance=AfxGetInstanceHandle();

	m_ImageTop.SetLoadInfo(USERLIST_TOP,hInstance);

	m_ImageInfo.SetLoadInfo(USERLIST_INFO,hInstance);
	m_ImageWeb.SetLoadInfo(USERLIST_WEB,hInstance);

	m_ImageML.SetLoadInfo(IDB_FRAME_ML,hInstance);
	m_ImageMR.SetLoadInfo(IDB_FRAME_MR,hInstance);

	m_ImageChatTL.SetLoadInfo(IDB_CHAT_TL,hInstance);
	m_ImageChatTM.SetLoadInfo(IDB_CHAT_TM,hInstance);
	m_ImageChatTR.SetLoadInfo(IDB_CHAT_TR,hInstance);

	m_QQShowL.SetLoadInfo(IDB_QQSHOW_L,hInstance);
	m_QQShowR.SetLoadInfo(IDB_QQSHOW_R,hInstance);
	m_QQShowB.SetLoadInfo(IDB_QQSHOW_B,hInstance);


	m_pFindUserDlg=NULL;
	m_pHtmlBrower = NULL;
	return;
}

CRoomViewItem::~CRoomViewItem()
{
	
	//�����ڴ�
	if (m_pShareMemory!=NULL)
	{
		UnmapViewOfFile(m_pShareMemory);
		m_pShareMemory=NULL;
	}
	if (m_hShareMemory!=NULL)
	{
		CloseHandle(m_hShareMemory);
		m_hShareMemory=NULL;
	}

	for (INT_PTR i=0;i<m_ShortMessage.GetCount();i++) 
	{
		delete ((CShortMessage *)m_ShortMessage.GetAt(i));
		m_ShortMessage.SetAt(i,NULL);
	}
	SafeDelete(m_pFindUserDlg);

	return;
}

//�ӿڲ�ѯ
void * __cdecl CRoomViewItem::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IViewItem,Guid,dwQueryVer);
	QUERYINTERFACE(IRoomViewItem,Guid,dwQueryVer);
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(IUserManagerSink,Guid,dwQueryVer);
	QUERYINTERFACE(IClientSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE(IChannelMessageSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IViewItem,Guid,dwQueryVer);
	return NULL;
}

//�ؼ���
void CRoomViewItem::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHRASE, m_btPhrase);
	DDX_Control(pDX, IDC_COLOR_SET, m_btColorSet);
	DDX_Control(pDX, IDC_SEND_CHAT, m_btSendChat);
	DDX_Control(pDX, IDC_EXPRESSION, m_btExpression);
	DDX_Control(pDX, IDC_CLEAN_SCREEN, m_btCleanScreen);
	DDX_Control(pDX, IDC_CHAT_INPUT, m_ChatInput);
	DDX_Control(pDX, IDC_CHAT_MESSAGE, m_ChatMessage);
	DDX_Control(pDX, IDC_CHAT_OBJECT, m_ChatObject);
}

//��ʼ������
BOOL CRoomViewItem::OnInitDialog()
{
	__super::OnInitDialog();

	//���ÿؼ�

	if(m_UserListView.Create(NULL, WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE,CRect(0,0,0,0), this))
	{
		HINSTANCE hInstance=AfxGetInstanceHandle();
		m_UserListView.m_xTop.SetLoadInfo(USERLIST_T,hInstance);
		m_UserListView.m_xLeft.SetLoadInfo(USERLIST_L,hInstance);
		m_UserListView.m_xRight.SetLoadInfo(USERLIST_R,hInstance);
		m_UserListView.m_xBottom.SetLoadInfo(USERLIST_B,hInstance);
		m_UserListView.m_xScrollT.SetLoadInfo(USERLIST_S_T,hInstance);
		m_UserListView.m_xScrollM.SetLoadInfo(USERLIST_S_M,hInstance);
		m_UserListView.m_xScrollB.SetLoadInfo(USERLIST_S_B,hInstance);
		m_UserListView.m_xThumb.SetLoadInfo(USERLIST_S_THUMB,hInstance);

		m_UserListView.SetHeight(250);
		
		//for(int i=100001;i<=100021;i++)
		//	m_RoomList.AddButton(FindResource(NULL,"ROOMLIST_BTN",RT_BITMAP),IMG_LISTCTRL_CMD_ID,"թ�𻨷���1",20,5,0xffffff,i);
		m_UserListView.UpdateButton();
	}

	//m_UserListView.ShowWindow(SW_HIDE);

	m_pHtmlBrower = new CHtmlBrower();
	m_pHtmlBrower->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,20,NULL);
	m_pHtmlBrower->EnableBrowser(true);

	tagGlobalUserData UserData=g_GlobalUnits.GetGolbalUserData();
	CString ShowUrl;
	ShowUrl.Format(UrlQQShow,UserData.szAccounts);
	g_GlobalUnits.AddSessionUrl(ShowUrl,ShowUrl);
	m_pHtmlBrower->Navigate(ShowUrl);

	m_ChatInput.LimitText(MAX_CHAT_LEN-1);
	m_ChatMessage.SetBackgroundColor(FALSE,RGB(212,246,255));

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();


	m_btAutoSit.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDB_BT_AUTO_JOIN);
	m_btAutoSit.LoadRgnImage(AfxGetInstanceHandle(),IDB_BT_AUTO_JOIN,0xff00ff);

	m_btFindUser.Create(NULL,WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDB_BT_SEARCH_USER);
	m_btFindUser.LoadRgnImage(AfxGetInstanceHandle(),IDB_BT_SEARCH_USER,0xff00ff);
	m_btFindUser.EnableWindow(false);

	m_btPhrase.SetButtonImage(IDB_BT_EXPESSION,hInstance,false);
	//m_btExpression.SetButtonImage(IDB_BT_EXPESSION,hInstance,false);
	m_btExpression.LoadRgnImage(AfxGetInstanceHandle(),IDB_BT_EXPESSION,0xff00ff);
	m_btColorSet.SetButtonImage(IDB_BT_COLOR_SET,hInstance,false);
	m_btCleanScreen.SetButtonImage(IDB_BT_CLEAN_SCREEN,hInstance,false);

	m_btSendChat.SetButtonImage(IDB_BT_SEND_CHAT,hInstance,false);

	//������ʾ�ؼ�
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_EXPRESSION),TEXT("����"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_COLOR_SET),TEXT("��ɫ"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_CLEAN_SCREEN),TEXT("����"));
	m_ToolTipCtrl.AddTool(GetDlgItem(IDC_SEND_CHAT),TEXT("����"));

	m_btRoom1.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_ROOM1);
	m_btRoom2.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_ROOM2);
	m_btRoom3.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_ROOM3);
	m_btRoom4.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_ROOM4);
	m_btRoom5.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_ROOM5);
	m_btRoom6.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_ROOM6);
	
	m_pHtmlBrower1 = new CHtmlBrower;
	m_pHtmlBrower1->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(12,460,157,509),this,20,NULL);
	m_pHtmlBrower1->EnableBrowser(true);
	m_pHtmlBrower1->Navigate("http://"ServerDomain"/Client/RoomNotice1.asp");

	m_pHtmlBrower2 = new CHtmlBrower;
	m_pHtmlBrower2->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(472,447,778,494),this,20,NULL);
	m_pHtmlBrower2->EnableBrowser(true);
	m_pHtmlBrower2->Navigate("http://"ServerDomain"/Client/RoomNotice1.asp");


	m_btRoomExit.Create(TEXT(""),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_ROOMEXIT);

	m_btRoom1.SetButtonImage(USERLIST_ROOM1,hInstance,false);
	m_btRoom2.SetButtonImage(USERLIST_ROOM2,hInstance,false);
	m_btRoom3.SetButtonImage(USERLIST_ROOM3,hInstance,false);
	m_btRoom4.SetButtonImage(USERLIST_ROOM4,hInstance,false);
	m_btRoom5.SetButtonImage(USERLIST_ROOM5,hInstance,false);
	m_btRoom6.SetButtonImage(USERLIST_ROOM6,hInstance,false);

	m_btRoomExit.SetButtonImage(USERLIST_ROOMEXIT,hInstance,false);

	m_btRoom1.ShowWindow(SW_SHOW);
	m_btRoom2.EnableWindow(false);
	m_btRoom3.EnableWindow(false);
	m_btRoom4.EnableWindow(false);
	m_btRoom5.EnableWindow(false);
	m_btRoom6.EnableWindow(false);
	m_btRoomExit.ShowWindow(SW_SHOW);

	//�������
	m_ChatObject.AddString(TEXT("������"));
	m_ChatObject.SetCurSel(0);

	//���ñ���
	m_bInitDialog=true;

	return TRUE;
}

HBRUSH CRoomViewItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID() == IDC_CHAT_INPUT)
	{
		m_brBkgnd.CreateSolidBrush(RGB(212,245,255));
		pDC->SetBkColor(RGB(212,245,255));	
		return (HBRUSH)m_brBkgnd;
	}
	if(pWnd->GetDlgCtrlID() == IDC_CHAT_OBJECT)
	{
		m_brBkgnd.CreateSolidBrush(RGB(212,246,255));
		pDC->SetBkColor(RGB(212,246,255));	
		return (HBRUSH)m_brBkgnd;
	}
	pDC->SetBkMode(TRANSPARENT);
	return hbr;
}


//��Ϣ����
BOOL CRoomViewItem::PreTranslateMessage(MSG * pMsg)
{
	if((pMsg->message==WM_KEYDOWN)
		&& (pMsg->wParam==VK_RETURN)
		&& (m_ServiceStatus==ServiceStatus_Serviceing))
	{
		OnBnClickedSendChat();
		return TRUE;
	}
	m_ToolTipCtrl.RelayEvent(pMsg);
	
	return __super::PreTranslateMessage(pMsg);
}

//�˵�����
BOOL CRoomViewItem::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDM_UM_WISPER:			//˽����Ϣ
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//����˽��
			if (m_dwMenuUserID!=m_pMeUserItem->GetUserID()) SendUserWhisper(pIUserItem);
			
			return TRUE;
		}
	case IDM_UM_SHOW:			//�û�SHOW
		{
		
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//�鿴SHOW
			if (m_dwMenuUserID!=m_pMeUserItem->GetUserID()) SendUserShow(pIUserItem);
			
			return TRUE;
		}
	case IDM_UM_COPY_NAME:		//��������
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//�򿪼��а�
			if (OpenClipboard()==FALSE) return TRUE;
			if (EmptyClipboard()==FALSE) { CloseClipboard(); return TRUE; }

			//��������
			HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,NAME_LEN);
			if (hData==NULL) 
			{
				CloseClipboard();
				return TRUE;
			}
			LPTSTR szMemName=(LPTSTR)GlobalLock(hData);
			lstrcpy(szMemName,pIUserItem->GetUserName());
			SetClipboardData(CF_TEXT,hData);
			GlobalUnlock(hData);
			CloseClipboard();

			//��ʾ����
			m_ChatInput.Paste();
			m_ChatInput.SetFocus();

			return TRUE;
		}
	case IDM_UM_SET_CHAT:		//��������
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//���ö���
			if (m_dwMenuUserID!=m_pMeUserItem->GetUserID())
			{
				SetChatObject(pIUserItem);
				m_ChatInput.SetFocus();
			}

			return TRUE;
		}
	case IDM_UM_CANECL_CHAT:	//ȡ������
		{
			//���ö���
			SetChatObject(NULL);
			m_ChatInput.SetFocus();

			return TRUE;
		}
	case IDM_UM_LOOK_LOCATION:	//�鿴λ��
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//��λλ��
			tagUserData * pUserData=pIUserItem->GetUserData();
			if ((pUserData->wTableID!=INVALID_TABLE)&&(pUserData->wChairID!=INVALID_CHAIR))
			{
				m_TableFrame.EnsureVisibleTable(pUserData->wTableID);
				if (pUserData->cbUserStatus==US_LOOKON) m_TableFrame.FlashTable(pUserData->wTableID);
				else m_TableFrame.FlashChair(pUserData->wTableID,pUserData->wChairID);
			}

			return TRUE;
		}
	case IDM_UM_SEARCH_USER:	//Ѱ�����
		{
			//�����ť
			OnBnClickedFindUser();

			return TRUE;
		}
	case IDM_UM_INVITE_PLAY:	//�������
		{
			//״̬�ж�
			if (m_ServiceStatus!=ServiceStatus_Serviceing) return TRUE;

			//������Ϣ
			tagUserData * pUserData=m_pMeUserItem->GetUserData();
			if (pUserData->cbUserStatus==US_PLAY) return TRUE;
			if (pUserData->wTableID==INVALID_TABLE) return TRUE;

			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//��������
			CMD_GR_UserInviteReq UserInviteReq;
			UserInviteReq.wTableID=pUserData->wTableID;
			UserInviteReq.dwUserID=pIUserItem->GetUserID();
			m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_INVITE_REQ,&UserInviteReq,sizeof(UserInviteReq));

			//��ʾ��Ϣ
			m_MessageProxyHelper->InsertSystemString(TEXT("�ɹ������û���������"),0);

			return TRUE;
		}
	case IDM_UM_SET_FRIEND:		//��Ϊ����
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//��������
			tagCompanionItem CompanionItem;
			memset(&CompanionItem,0,sizeof(CompanionItem));
			tagUserData * pUserData=pIUserItem->GetUserData();

			//���ù�ϵ
			CompanionItem.wFaceID=pUserData->wFaceID;
			CompanionItem.dwUserID=pUserData->dwUserID;
			if (pUserData->cbCompanion==enCompanion_Friend)
			{
				pUserData->cbCompanion=enCompanion_UnKnow;
				CompanionItem.Companion=enCompanion_UnKnow;
			}
			else
			{
				pUserData->cbCompanion=enCompanion_Friend;
				CompanionItem.Companion=enCompanion_Friend;
			}
			lstrcpyn(CompanionItem.szAccounts,pUserData->szName,CountArray(CompanionItem.szAccounts));
				g_GlobalUnits.m_CompanionManager->InsertCompanionItem(CompanionItem);

			//�ı�֪ͨ
			OnUserItemUpdate(pIUserItem);

			return TRUE;
		}
	case IDM_UM_SET_DETEST:		//��Ϊ���
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//��������
			tagCompanionItem CompanionItem;
			memset(&CompanionItem,0,sizeof(CompanionItem));
			tagUserData * pUserData=pIUserItem->GetUserData();

			//���ù�ϵ
			CompanionItem.wFaceID=pUserData->wFaceID;
			CompanionItem.dwUserID=pUserData->dwUserID;
			if (pUserData->cbCompanion==enCompanion_Detest)
			{
				pUserData->cbCompanion=enCompanion_UnKnow;
				CompanionItem.Companion=enCompanion_UnKnow;
			}
			else
			{
				pUserData->cbCompanion=enCompanion_Detest;
				CompanionItem.Companion=enCompanion_Detest;
			}
			lstrcpyn(CompanionItem.szAccounts,pUserData->szName,CountArray(CompanionItem.szAccounts));
			g_GlobalUnits.m_CompanionManager->InsertCompanionItem(CompanionItem);

			//�ı�֪ͨ
			OnUserItemUpdate(pIUserItem);

			//��ʾ��Ϣ
			if (pUserData->cbCompanion==enCompanion_Detest)
			{
				TCHAR szMessage[256]=TEXT("");
				_snprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] ����Ϊ�����ң�ϵͳ����������һ��������Ϣ"),pUserData->szName);
				m_MessageProxyHelper->InsertSystemString(szMessage,0);
			}

			return TRUE;
		}
	case IDM_UM_SEND_WARNNING:	//���;���
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//Ȩ���ж�
			tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
			if (CUserRight::CanSendWarning(pMeUserData->dwMasterRight)==false) return TRUE;

			//��������
			if (m_ManagerSendWarning.m_hWnd==NULL) 
			{
				m_ManagerSendWarning.Create(IDD_SEND_WARNING,this);
				m_ManagerSendWarning.SetClientUserManager(GET_OBJECT_INTERFACE(m_ClientUserManager,IUnknownEx));
				m_ManagerSendWarning.SetClientSocket(GET_OBJECTPTR_INTERFACE(m_ClientSocket.GetInterface(),IUnknownEx));
			}

			//���ñ���
			m_ManagerSendWarning.SetUserItem(pIUserItem);

			//��ʾ����
			m_ManagerSendWarning.ShowWindow(SW_SHOW);
			m_ManagerSendWarning.BringWindowToTop();

			return TRUE;
		}
	case IDM_UM_LOOK_USER_IP:	//�鿴��ַ
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//Ȩ���ж�
			tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
			if (CUserRight::CanSeeUserIP(pMeUserData->dwMasterRight)==false) return TRUE;

			//��������
			CMD_GR_LookUserIP LookUserIP;
			LookUserIP.dwTargetUserID=pIUserItem->GetUserID();
			m_ClientSocket->SendData(MDM_GR_MANAGER,SUB_GR_LOOK_USER_IP,&LookUserIP,sizeof(LookUserIP));

			return TRUE;
		}
	case IDM_UM_CUT_USER:		//�߳��û�
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//Ȩ���ж�
			tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
			if (CUserRight::CanCutUser(pMeUserData->dwMasterRight)==false) return TRUE;

			//��������
			CMD_GR_KillUser KillUser;
			KillUser.dwTargetUserID=pIUserItem->GetUserID();
			m_ClientSocket->SendData(MDM_GR_MANAGER,SUB_GR_KILL_USER,&KillUser,sizeof(KillUser));

			return TRUE;
		}
	case IDM_UM_LIMIT_ACCOUN:	//�����ʻ�
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//Ȩ���ж�
			tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
			if (CUserRight::CanForbidAccounts(pMeUserData->dwMasterRight)==false) return TRUE;

			//ȷ����ʾ
			TCHAR szMessage[128]=TEXT("");
			_snprintf(szMessage,CountArray(szMessage),TEXT("ȷʵҪ���� [ %s ] ���ʺ���"),pIUserItem->GetUserName());
			if (ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO)!=IDYES) return TRUE;

			//�û��ж�
			if (pIUserItem->GetUserID()!=m_dwMenuUserID) 
			{
				_snprintf(szMessage,CountArray(szMessage),TEXT("�û� [ %s ] �Ѿ��뿪����Ϸ���䣬�ʺŶ���ʧ��"),pIUserItem->GetUserName());
				m_MessageProxyHelper->InsertSystemString(szMessage,0);
			
				return TRUE;
			}

			//��������
			CMD_GR_LimitAccounts LimitAccounts;
			LimitAccounts.dwTargetUserID=pIUserItem->GetUserID();
			m_ClientSocket->SendData(MDM_GR_MANAGER,SUB_GR_LIMIT_ACCOUNS,&LimitAccounts,sizeof(LimitAccounts));

			return TRUE;
		}
	case IDM_UM_MANAGER_USER:	//Ȩ�޹���
		{
			//Ѱ�����
			if (m_dwMenuUserID==0L) return TRUE;
			IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(m_dwMenuUserID);
			if (pIUserItem==NULL) return TRUE;

			//��������
			if (m_ManagerUserRight.m_hWnd==NULL) 
			{
				m_ManagerUserRight.Create(IDD_MANAGER_RIGHT,this);
				m_ManagerUserRight.SetMasterRight(m_pMeUserItem->GetUserData()->dwMasterRight);
				m_ManagerUserRight.SetClientUserManager(GET_OBJECT_INTERFACE(m_ClientUserManager,IUnknownEx));
				m_ManagerUserRight.SetClientSocket(GET_OBJECTPTR_INTERFACE(m_ClientSocket.GetInterface(),IUnknownEx));
			}

			//���ñ���
			m_ManagerUserRight.SetUserItem(pIUserItem);

			//��ʾ����
			m_ManagerUserRight.ShowWindow(SW_SHOW);
			m_ManagerUserRight.BringWindowToTop();

			return TRUE;
		}
	case IDM_UM_ISSUE_MESSAGE:	//������Ϣ
		{
			//Ȩ���ж�
			tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
			if (CUserRight::CanIssueMessage(pMeUserData->dwMasterRight)==false) return TRUE;

			//��������
			if (m_ManagerMessage.m_hWnd==NULL) 
			{
				m_ManagerMessage.Create(IDD_MANAGER_MESSAGE,this);
				m_ManagerMessage.SetClientSocket(GET_OBJECTPTR_INTERFACE(m_ClientSocket.GetInterface(),IUnknownEx));
			}

			//��ʾ����
			m_ManagerMessage.ShowWindow(SW_SHOW);
			m_ManagerMessage.BringWindowToTop();

			return TRUE;
		}
	case IDM_IM_SYSTEM_OPTION:	//�������
		{
			//Ȩ���ж�
			tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
			if (CUserRight::CanServerOption(pMeUserData->dwMasterRight)==false) return TRUE;

			//��������
			if (m_ManagerServer.m_hWnd==NULL) 
			{
				m_ManagerServer.Create(IDD_MANAGER_SERVER,this);
				m_ManagerServer.SetClientSocket(GET_OBJECTPTR_INTERFACE(m_ClientSocket.GetInterface(),IUnknownEx));
			}

			//��ʾ����
			m_ManagerServer.ShowWindow(SW_SHOW);
			m_ManagerServer.BringWindowToTop();

			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//�滭��Ϣ
void CRoomViewItem::OnPaint()
{
	CPaintDC dc(this);

	//�滭����
	DrawLeftViewFrame(&dc);

	return;
}

//�滭����
BOOL CRoomViewItem::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

//λ����Ϣ
void CRoomViewItem::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	return;
}

//��ʾ��Ϣ
void CRoomViewItem::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//���ñ���
	if (bShow) UpdateTitleText();

	return;
}


//IPC ��Ϣ
BOOL CRoomViewItem::OnCopyData(CWnd *pWnd, COPYDATASTRUCT *pCopyDataStruct)
{
	if (m_IPCRecvCopyData.OnCopyData(pWnd->GetSafeHwnd(), pCopyDataStruct)==true) return TRUE;
	return __super::OnCopyData(pWnd, pCopyDataStruct);
}

//������Ϣ
LRESULT CRoomViewItem::OnHitExpression(WPARAM wParam, LPARAM lParam)
{
	CExpressionItem * pExpressionItem=m_Expression.GetExpressItem((WORD)wParam);
	if (pExpressionItem!=NULL)
	{
		CString strBuffer;
		m_ChatInput.GetWindowText(strBuffer);
		strBuffer+=pExpressionItem->m_szTrancelate;
		m_ChatInput.SetWindowText(strBuffer);
		m_ChatInput.SetFocus();
		m_ChatInput.SetSel(strBuffer.GetLength(),strBuffer.GetLength());
	}

	return 0;
}
//int Random(int b)
//{
//	srand(::GetTickCount());
//	int a = rand();
//	while( !(a >=1&&a<=b))
//	{
//		srand(::GetTickCount());
//		a = rand();
//	}
//	return a;
//}

int AverageRandom(int min,int max)
{
	srand( (unsigned)time( NULL ) );	
	int minInteger = (int)(min*10000);
	int maxInteger = (int)(max*10000);
	int randInteger = rand()*rand();
	int diffInteger = maxInteger - minInteger;
	int resultInteger = randInteger % diffInteger + minInteger;
	return resultInteger/10000;
}

//���Ͱ�ť
void CRoomViewItem::OnBnClickedSendChat()
{
	//������Ϣ
	if(::GetTickCount() - m_dwLastChat<3000)
	{
		srand( (unsigned)time( NULL ) );		
		int a = AverageRandom(1,2);
		switch(a)
		{
		case 1:
			MessageBox("���Ĵ����ٶȺÿ찡�������������ķ���Ҳ������Ŷ��");
			break;
		case 2:
			MessageBox("���Ĵ����ٶȺÿ찡�������������ķ���Ҳ������Ŷ��");
			break;
		}
		return;
	}

	TCHAR szChatMessage[MAX_CHAT_LEN]=TEXT("");
	m_ChatInput.GetWindowText(szChatMessage,CountArray(szChatMessage));
	if (szChatMessage[0]!=0)
	{
		m_ChatInput.SetWindowText(TEXT(""));
		SendChatPacket(m_dwChatUserID,szChatMessage,g_GlobalOption.m_crChatTX);
		m_dwLastChat = ::GetTickCount();
	}

	//���ý���
	m_ChatInput.SetFocus();

	return;
}

//���鰴ť
void CRoomViewItem::OnBnClickedExpression()
{
	//�������鴰��
	if (m_Expression.GetSafeHwnd()==NULL) m_Expression.CreateExpression(this);

	//�ƶ�����
	CRect rcButton;
	CSize ExpressSize;
	m_Expression.GetFixSize(ExpressSize);
	m_btExpression.GetWindowRect(&rcButton);
	m_Expression.MoveWindow(rcButton.right-ExpressSize.cx,rcButton.top-ExpressSize.cy,ExpressSize.cx,ExpressSize.cy);
	m_Expression.ShowWindow(SW_SHOW);
	m_Expression.SetFocus();

	return;
}

//��ɫ��ť
void CRoomViewItem::OnBnClickedColorSet()
{
	//������ɫ
	CColorDialog ColorDialog(g_GlobalOption.m_crChatTX,CC_FULLOPEN);
	if (ColorDialog.DoModal()==IDOK) g_GlobalOption.m_crChatTX = ColorDialog.GetColor();

	//���ý���
	m_ChatInput.SetFocus();

	return;
}

//������ť
void CRoomViewItem::OnBnClickedCleanScreen()
{
	m_MessageProxyHelper->CleanScreen();
	return;
}

//������Ϣ
tagGameKind * __cdecl CRoomViewItem::GetKindInfo()
{
	if (m_pListServer!=NULL)
	{
		CListKind * pListKind=m_pListServer->GetListKind();
		ASSERT(pListKind!=NULL);
		if (pListKind!=NULL)
		{
			return pListKind->GetItemInfo();
		}
	}
	return NULL;
}

//���밴ť
void CRoomViewItem::OnBnClickedAutoSit()
{
	//bluker:����ɷ�������������ֱ��PerformLookonAction(INVALID_TABLE, WORD INVALID_CHAIR);
	if(IsServerAllocTable())
	{
		PerformLookonAction(INVALID_TABLE, WORD INVALID_CHAIR);
		return;
	}
	//�ж�״̬
	if (m_ServiceStatus!=ServiceStatus_Serviceing) return;

	if ((m_wReqTableID!=INVALID_TABLE)||(m_wReqChairID!=INVALID_CHAIR))
	{
		TCHAR szMessage[]=TEXT("�ϴ�����û���յ���������Ӧ�����Ժ�");
		ShowMessageBox(szMessage,MB_ICONINFORMATION);
		return;
	}

	//�ж�״̬
	tagUserData * pUserData=m_pMeUserItem->GetUserData();
	if (pUserData->cbUserStatus==US_PLAY)
	{
		TCHAR szMessage[]=TEXT("��������Ϸ�У����ܻ�λ�ã����Ƚ�����Ϸ��");
		ShowMessageBox(szMessage,MB_ICONINFORMATION);
		return;
	}

	//���������Ӳ�ȫ�յ�
	tagFindTable FindInfo;
	FindInfo.bAllNull=false;
	FindInfo.bFilterPass=true;
	FindInfo.bNotFull=true;
	FindInfo.bOneNull=true;
	FindInfo.bTwoNull=(m_TableFrame.GetChairCount()!=2);
	FindInfo.wBeginTableID=m_wFindTableID+1;
	FindInfo.wResultTableID=INVALID_TABLE;
	FindInfo.wResultChairID=INVALID_CHAIR;
	bool bSuccess=FindGameTable(FindInfo);
	m_wFindTableID=FindInfo.wResultTableID;

	//����ȫ����Ϸ��
	if (bSuccess==false)
	{
		FindInfo.bAllNull=true;
		FindInfo.bFilterPass=true;
		FindInfo.bNotFull=true;
		FindInfo.bOneNull=true;
		FindInfo.bTwoNull=true;
		FindInfo.wBeginTableID=m_wFindTableID+1;
		FindInfo.wResultTableID=INVALID_TABLE;
		FindInfo.wResultChairID=INVALID_CHAIR;
		bSuccess=FindGameTable(FindInfo);
		m_wFindTableID=FindInfo.wResultTableID;
	}

	//����ж�
	if (bSuccess==true)
	{
		//Ч������
		ASSERT(FindInfo.wResultTableID!=INVALID_TABLE);
		ASSERT(FindInfo.wResultChairID!=INVALID_CHAIR);

		//��������
		WORD wChairID=FindInfo.wResultChairID;
		m_TableFrame.EnsureVisibleTable(m_wFindTableID);
		m_TableFrame.FlashChair(m_wFindTableID,wChairID);

		//�Զ�����
		PerformSitDownAction(m_wFindTableID,wChairID);
	}
	else
	{
		TCHAR szMessage[]=TEXT("�Ҳ���������������Ϸ����");
		ShowMessageBox(szMessage,MB_ICONINFORMATION);
	}

	return;
}

//���Ұ�ť
void CRoomViewItem::OnBnClickedFindUser()
{
	if (m_pFindUserDlg==NULL)
	{
		m_pFindUserDlg=new CFindUserDlg(this,0);
		m_pFindUserDlg->m_UserList.m_wGameGenre=m_wGameGenre;
		m_pFindUserDlg->m_UserList.m_wKindID=m_pListServer->GetItemInfo()->wKindID;
	}
	if (m_pFindUserDlg->GetSafeHwnd()==NULL)
	{
		m_pFindUserDlg->Create(IDD_FIND_USER,this);
		m_pFindUserDlg->m_UserList.SetColumnDescribe(m_ListColumnInfo.ColumnItem,m_ListColumnInfo.wColumnCount);
	}
	m_pFindUserDlg->ShowWindow(SW_SHOW);
	return;
}

//���Ұ�ť
void CRoomViewItem::OnBnClickedRoomExit()
{
	g_pControlBar->CloseRoomViewItem(this);
	return;
}

//������Ϣ
tagGameServer * __cdecl CRoomViewItem::GetServerInfo()
{
	if (m_pListServer==NULL) return NULL;
	return m_pListServer->GetItemInfo();
}

//�ر�֪ͨ
void __cdecl CRoomViewItem::CloseRoomViewItem()
{
	//�ر�����
	if (m_ClientSocket.GetInterface()!=NULL) m_ClientSocket->CloseSocket(false);

	//�ر���Ϸ
	CloseGameClient();

	//�����ڴ�
	if (m_pShareMemory!=NULL)
	{
		UnmapViewOfFile(m_pShareMemory);
		m_pShareMemory=NULL;
	}
	if (m_hShareMemory!=NULL)
	{
		CloseHandle(m_hShareMemory);
		m_hShareMemory=NULL;
	}

	//�رմ���
	DestroyWindow();

	return;
}

//��ť��Ϣ
bool CRoomViewItem::OnSplitterButton(CSkinSplitter * pSkinSplitter, CSkinButton * pSplitterButton)
{
	return true;
}

//�������Ϣ
bool CRoomViewItem::OnSplitterEvent(CSkinSplitter * pSkinSplitter, UINT uSplitID, int nXPos, int nYPos)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	return true;
}

//��ʼ��
bool CRoomViewItem::InitRoomViewItem(CListServer * pListServer)
{
	//���ñ���
	ASSERT(pListServer!=NULL);
	m_pListServer=pListServer;

	//��Ϣ����
	if (m_MessageProxyHelper.CreateInstance()==false) return false;
	if (m_MessageProxyHelper->SetRichEditHwnd(&m_ChatMessage)==false) return false;

	//�������
	IUnknownEx * pIUnknownEx=GET_MYSELF_INTERFACE(IUnknownEx);
	if (m_ClientSocket.CreateInstance()==false) return false;
	if (m_ClientSocket->SetSocketSink(pIUnknownEx)==false) return false;
	if (m_ClientUserManager.SetUserManagerSink(pIUnknownEx)==false) return false;
	if (m_IPCRecvCopyData.SetChannelMessageSink(pIUnknownEx)==false) return false;

	//������ɫ
	tagMessageOption MessageOption;
	memset(&MessageOption,0,sizeof(MessageOption));
	MessageOption.crName=g_GlobalOption.m_crMsgName;
	MessageOption.crSystemHead=g_GlobalOption.m_crMsgSysHead;
	MessageOption.crSystemString=g_GlobalOption.m_crMsgSysString;
	m_MessageProxyHelper->SetMessageOption(MessageOption);

	//���������ڴ�
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();
	_snprintf(m_szShareName,sizeof(m_szShareName),TEXT("0x8%ld%ld%ld%ld"),pGameServer->dwServerAddr,pGameServer->wServerPort,time(NULL),rand()%100);
	m_hShareMemory=(HANDLE)CreateFileMapping((HANDLE)0xFFFFFFFFFFFF,NULL,PAGE_READWRITE,0,sizeof(tagShareMemory),m_szShareName);
	if ((m_hShareMemory==NULL)||(GetLastError()==ERROR_ALREADY_EXISTS)) return false;
	m_pShareMemory=(tagShareMemory *)MapViewOfFile(m_hShareMemory,FILE_MAP_ALL_ACCESS,0,0,0);

	//���ù����ڴ�
	memset(m_pShareMemory,0,sizeof(tagShareMemory));
	m_pShareMemory->wDataSize=sizeof(tagShareMemory);
	m_pShareMemory->hWndGameServer=m_hWnd;
	m_pShareMemory->hWndGamePlaza=AfxGetMainWnd()->m_hWnd;

	//������Ϣ
	m_pServerOption=g_GlobalOption.GetServerOption(pListServer);
	m_pGameOption=g_GlobalOption.GetGameOption(pListServer->GetListKind());
	ASSERT(m_pGameOption!=NULL);
	ASSERT(m_pServerOption!=NULL);

	return true;
}

//���ӷ�����
bool CRoomViewItem::ConnectGameServer()
{
	m_ServiceStatus=ServiceStatus_Connecting;
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();
	m_ClientSocket->SetProxyServer(CDlgLogon::m_ProxyInfo);
	return m_ClientSocket->Connect(pGameServer->dwServerAddr,pGameServer->wServerPort);
}

//���͹���
bool CRoomViewItem::SendUserRule()
{
	if (m_ServiceStatus!=ServiceStatus_Serviceing) return false;
	return SendUserRulePacket();
}

//˽����Ϣ
bool CRoomViewItem::SendUserWhisper(IUserItem * pIUserItem)
{
	//��ȡ�û�
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem==NULL) return false;

	//�����
	CShortMessage *pShortMessageWnd = ActiveShortWnd(pIUserItem->GetUserData()->dwUserID,pIUserItem,true);
	if (pShortMessageWnd==NULL)	ShowMessageBox(TEXT("����Ϣ����̫���ˣ���رղ��ֶ���Ϣ�������ԣ�"),MB_ICONINFORMATION);

	return true;
}


//�û�SHOW��Ϣ
bool CRoomViewItem::SendUserShow(IUserItem * pIUserItem)
{
	//��ȡ�û�
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem==NULL) return false;

	CShow *pShowWnd = ActiveShowWnd(pIUserItem->GetUserData()->dwUserID,pIUserItem,true);
	if (pShowWnd==NULL)	ShowMessageBox(TEXT("�û�SHOW����̫���ˣ���رղ��ִ������ԣ�"),MB_ICONINFORMATION);

	return true;
}



//�û��˵�
bool CRoomViewItem::ShowUserInfoMenu(IUserItem * pIUserItem, CPoint Point)
{
	//�ж�״̬
	if (m_ServiceStatus!=ServiceStatus_Serviceing) return false;

	//�û��ж�
	if (pIUserItem==NULL) 
	{
		m_MessageProxyHelper->InsertGeneralString(TEXT("���û��Ѿ��뿪������ "),RGB(0,0,0),MS_NORMAL,true);
		return false;
	}

	//����˵�
	CMenu UserInfoMenu;
	if (UserInfoMenu.CreatePopupMenu()==FALSE) return false;

	//��ȡ���
	tagUserData * pUserData=pIUserItem->GetUserData();
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();

	//�û���Ϣ
	WORD wTableID=pUserData->wTableID;
	WORD wChiarID=pUserData->wChairID;
	BYTE cbUserStatus=pUserData->cbUserStatus;

	//�����Ϣ
	WORD wMeTableID=pMeUserData->wTableID;
	WORD wMeChiarID=pMeUserData->wChairID;
	BYTE cbMeUserStatus=pMeUserData->cbUserStatus;

	//���ñ���
	TCHAR szBuffer[256]=TEXT("");
	m_dwMenuUserID=pUserData->dwUserID;
	bool bMySelf=(pIUserItem==m_pMeUserItem);

	////���ò˵�
	//if (bMySelf==false) 
	//{
	//	UserInfoMenu.AppendMenu(0,IDM_UM_WISPER,TEXT("����˽����Ϣ..."));
	//	UserInfoMenu.SetDefaultItem(IDM_UM_WISPER,MF_BYCOMMAND);
	//}
	UserInfoMenu.AppendMenu(0,IDM_UM_COPY_NAME,TEXT("�����û���"));

	//�������
	if ((bMySelf==false)&&(m_dwChatUserID!=pUserData->dwUserID))
	{
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("�� [ %s ] ��̸"),pUserData->szName);
		UserInfoMenu.AppendMenu(0,IDM_UM_SET_CHAT,szBuffer);
	}
	if (m_szChatName[0]!=0)
	{
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("ȡ���� [ %s ] ��̸"),m_szChatName);
		UserInfoMenu.AppendMenu(0,IDM_UM_CANECL_CHAT,szBuffer);
	}

	//�鿴λ��
	UserInfoMenu.AppendMenu(MF_SEPARATOR);
	
	if (bMySelf==false) UserInfoMenu.AppendMenu(0,IDM_UM_LOOK_LOCATION,TEXT("�鿴��ҵ�λ��"));
	else UserInfoMenu.AppendMenu(0,IDM_UM_LOOK_LOCATION,TEXT("�鿴�ҵ�λ��"));
	if (pUserData->wTableID==INVALID_TABLE) UserInfoMenu.EnableMenuItem(IDM_UM_LOOK_LOCATION,MF_BYCOMMAND|MF_GRAYED);

	//������Ϸ
	if ((bMySelf==false)&&(cbMeUserStatus!=US_PLAY)&&(wMeTableID!=INVALID_TABLE)&&(cbUserStatus<US_PLAY))
	{
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("���� [ %s ] һ����Ϸ"),pUserData->szName);
		UserInfoMenu.AppendMenu(0,IDM_UM_INVITE_PLAY,szBuffer);
	}

	//���ܲ˵�
//	UserInfoMenu.AppendMenu(MF_SEPARATOR);
//	UserInfoMenu.AppendMenu(0,IDM_UM_SEARCH_USER,TEXT("Ѱ�����..."));
	if(bMySelf==false)
	{
		UserInfoMenu.AppendMenu(0,IDM_UM_SET_FRIEND,TEXT("��Ϊ����"));
		UserInfoMenu.AppendMenu(0,IDM_UM_SET_DETEST,TEXT("��Ϊ���"));
		if (pUserData->cbCompanion==enCompanion_Friend) 
		{
			UserInfoMenu.CheckMenuItem(IDM_UM_SET_FRIEND,MF_BYCOMMAND|MF_CHECKED);
		}
		if (pUserData->cbCompanion==enCompanion_Detest) 
		{
			UserInfoMenu.CheckMenuItem(IDM_UM_SET_DETEST,MF_BYCOMMAND|MF_CHECKED);
		}
	}

	//�����Ϣ
	double dFleeRate=0.0;
	LONG lPlayCount=pIUserItem->GetUserPlayCount();
	if (pUserData->lFleeCount>0)
	{
		dFleeRate=(double)(pUserData->lFleeCount*100)/(double)lPlayCount;
		if (dFleeRate<0.01) dFleeRate=0.0;
	}

	//if(bMySelf==false)
	//{
	//	UserInfoMenu.AppendMenu(0,MF_SEPARATOR);
	//	//�û�����SHOW
	//	UserInfoMenu.AppendMenu(0,IDM_UM_SHOW,TEXT("��������SHOW"));
	//	UserInfoMenu.SetDefaultItem(IDM_UM_SHOW,MF_BYCOMMAND);	
	//}

	//�������
	UserInfoMenu.AppendMenu(0,MF_SEPARATOR);
	LPCTSTR pszMember[]={TEXT("��ͨ��Ա"),TEXT("�м���Ա"),TEXT("�߼���Ա")};
	if ((pUserData->cbMember>0)&&(pUserData->cbMember<CountArray(pszMember)))
	{
		BYTE cbMember=pUserData->cbMember;
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("�û�����%s [ %s ]"),pUserData->szName,pszMember[cbMember]);
	}
	else 
	{
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("�û�����%s"),pUserData->szName);
	}
	UserInfoMenu.AppendMenu(0,0,szBuffer);

	
	//��Ϸ ID
	_snprintf(szBuffer,CountArray(szBuffer),TEXT("ID �ţ�%ld"),pUserData->dwUserID);
	UserInfoMenu.AppendMenu(0,0,szBuffer);
	
	//������ֵ
	_snprintf(szBuffer,CountArray(szBuffer),TEXT("����ֵ��%ld"),pUserData->lExperience);
	UserInfoMenu.AppendMenu(0,0,szBuffer);
	
	//���λ��
	if (pUserData->wTableID!=INVALID_TABLE)
	{
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("���ţ�%d"),pUserData->wTableID+1);
		UserInfoMenu.AppendMenu(0,0,szBuffer);
	}

	//��Ϸ����Ϣ
	_snprintf(szBuffer,CountArray(szBuffer),TEXT("��Ϸ�ң�%ld  �ܾ�����%ld  �����ʣ�%5.2f%%"),pUserData->lScore,lPlayCount,dFleeRate);
	UserInfoMenu.AppendMenu(0,0,szBuffer);

	//������Ϣ
	if (pUserData->szGroupName[0]!=0)
	{
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("���ţ�%s"),pUserData->szGroupName);
		UserInfoMenu.AppendMenu(0,0,szBuffer);
	}

	//�û�����
	if ((pMeUserData->dwUserID!=m_dwMenuUserID)&&(pMeUserData->dwMasterRight!=0L))
	{
		//����˵�
		UserInfoMenu.AppendMenu(0,MF_SEPARATOR);
		UserInfoMenu.AppendMenu(0,IDM_UM_SEND_WARNNING,TEXT("���;�����Ϣ..."));
		UserInfoMenu.AppendMenu(0,IDM_UM_LOOK_USER_IP,TEXT("�鿴�û� IP..."));
		UserInfoMenu.AppendMenu(0,IDM_UM_CUT_USER,TEXT("���û�����..."));
		UserInfoMenu.AppendMenu(0,IDM_UM_LIMIT_ACCOUN,TEXT("�����û��ʺ�..."));
		UserInfoMenu.AppendMenu(0,IDM_UM_MANAGER_USER,TEXT("�û�Ȩ������..."));

		//��ֹ�˵�
		DWORD dwMasterRight=pMeUserData->dwMasterRight;
		if (CUserRight::CanSendWarning(dwMasterRight)==false) UserInfoMenu.EnableMenuItem(IDM_UM_SEND_WARNNING,MF_BYCOMMAND|MF_GRAYED);
		if (CUserRight::CanSeeUserIP(dwMasterRight)==false) UserInfoMenu.EnableMenuItem(IDM_UM_LOOK_USER_IP,MF_BYCOMMAND|MF_GRAYED);
		if (CUserRight::CanCutUser(dwMasterRight)==false) UserInfoMenu.EnableMenuItem(IDM_UM_CUT_USER,MF_BYCOMMAND|MF_GRAYED);
		if (CUserRight::CanForbidAccounts(dwMasterRight)==false) UserInfoMenu.EnableMenuItem(IDM_UM_LIMIT_ACCOUN,MF_BYCOMMAND|MF_GRAYED);
	}

	//�������
	if (pMeUserData->dwMasterRight!=0L)
	{
		//����˵�
		UserInfoMenu.AppendMenu(0,MF_SEPARATOR);
		UserInfoMenu.AppendMenu(0,IDM_UM_ISSUE_MESSAGE,TEXT("����ϵͳ��Ϣ..."));
		UserInfoMenu.AppendMenu(0,IDM_IM_SYSTEM_OPTION,TEXT("��Ϸ��������..."));

		//��ֹ�˵�
		DWORD dwMasterRight=pMeUserData->dwMasterRight;
		if (CUserRight::CanIssueMessage(dwMasterRight)==false) UserInfoMenu.EnableMenuItem(IDM_UM_ISSUE_MESSAGE,MF_BYCOMMAND|MF_GRAYED);
		if (CUserRight::CanServerOption(dwMasterRight)==false) UserInfoMenu.EnableMenuItem(IDM_IM_SYSTEM_OPTION,MF_BYCOMMAND|MF_GRAYED);
	}

	//��ʾ�˵�
	//UserInfoMenu.SetMenuDrawMode(BCMENU_DRAWMODE_XP); // ��XP��ʽ��ʾ
	UserInfoMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,Point.x,Point.y,this);

	return true;
}

//���͵�½��
bool CRoomViewItem::SendLogonPacket()
{
	//��ȡ��Ϣ
	BYTE cbBuffer[SOCKET_PACKAGE];
	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();

	//��½���ݰ�
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=GlobalUserData.dwUserID;
	pLogonByUserID->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
	lstrcpyn(pLogonByUserID->szPassWord,GlobalUserData.szPassWord,sizeof(pLogonByUserID->szPassWord));

	//�������к�
	tagClientSerial ClientSerial;
	g_GlobalUnits.GetClientSerial(ClientSerial);

	//�������ݰ�
	CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GR_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GR_LogonByUserID));
	Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
	m_ClientSocket->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID)+Packet.GetDataSize());

	return true;
}

//������������
bool CRoomViewItem::SendOptionsPacket()
{
	return true;
}

//������������
bool CRoomViewItem::SendStandUpPacket()
{
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ);

	return true;
}

//����ǿ������
bool CRoomViewItem::SendLeftGamePacket()
{
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);

	return true;
}

//���ͷ������
bool CRoomViewItem::SendUserRulePacket()
{
	//�������ݰ�
	CMD_GR_UserRule UserRule;
	UserRule.bLimitWin=m_pGameOption->m_bLimitWin;
	UserRule.bLimitFlee=m_pGameOption->m_bLimitFlee;
	UserRule.wWinRate=m_pGameOption->m_wWinRate;
	UserRule.wFleeRate=m_pGameOption->m_wFleeRate;
	UserRule.wNetDelay=m_pGameOption->m_wNetDelay;
	UserRule.lMaxScore=m_pGameOption->m_lMaxScore;
	UserRule.lLessScore	=m_pGameOption->m_lLessScore;
	UserRule.bLimitScore=m_pGameOption->m_bLimitScore;
	UserRule.bLimitDelay=m_pGameOption->m_bLimitDelay;
	UserRule.bPassword=m_pServerOption->m_bPassword;
	UserRule.bCheckSameIP=g_GlobalOption.m_bCheckSameIP;
	lstrcpyn(UserRule.szPassword,m_pServerOption->m_szPassword,CountArray(UserRule.szPassword));

	//�������ݰ�
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_RULE,&UserRule,sizeof(UserRule));

	return true;
}

//�����Թ�����
bool CRoomViewItem::SendLookonPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass)
{
	//�������ݰ�
	CMD_GR_UserSitReq UserUserSitReq;
	memset(&UserUserSitReq,0,sizeof(UserUserSitReq));
	UserUserSitReq.wTableID=wTableID;
	UserUserSitReq.wChairID=wChairID;
	UserUserSitReq.wNetTimelag=0;
	lstrcpyn(UserUserSitReq.szTablePass,pszTablePass,sizeof(UserUserSitReq.szTablePass));
	UserUserSitReq.cbPassLen=CountString(UserUserSitReq.szTablePass);

	//�������ݰ�
	WORD wSendSize=sizeof(UserUserSitReq)-sizeof(UserUserSitReq.szTablePass)+UserUserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_LOOKON_REQ,&UserUserSitReq,wSendSize);

	return true;
}

//������������
bool CRoomViewItem::SendSitDownPacket(WORD wTableID, WORD wChairID, LPCTSTR pszTablePass)
{
	//�������ݰ�
	CMD_GR_UserSitReq UserSitReq;
	memset(&UserSitReq,0,sizeof(UserSitReq));
	UserSitReq.wTableID=wTableID;
	UserSitReq.wChairID=wChairID;
	UserSitReq.wNetTimelag=0;
	lstrcpyn(UserSitReq.szTablePass,pszTablePass,sizeof(UserSitReq.szTablePass));
	UserSitReq.cbPassLen=CountString(UserSitReq.szTablePass);

	//�������ݰ�
	WORD wSendSize=sizeof(UserSitReq)-sizeof(UserSitReq.szTablePass)+UserSitReq.cbPassLen;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&UserSitReq,wSendSize);

	return true;
}

//�Թ۶���
bool CRoomViewItem::PerformLookonAction(WORD wTableID, WORD wChairID)
{
	//bluker:�ɷ���������λ��
	if(IsServerAllocTable())
	{
		m_wReqTableID=INVALID_TABLE;
		m_wReqChairID=INVALID_CHAIR;
		SendSitDownPacket(1,1,m_pServerOption->m_bPassword?m_pServerOption->m_szPassword:NULL);
		return true;
	}
	//Ч������
	ASSERT(wTableID!=INVALID_TABLE);
	ASSERT(wChairID!=INVALID_CHAIR);

	//����Ч��
	if (CanSitDownTable(wTableID,wChairID,true,true)==false) return false;

	//�������
	if ((m_wReqTableID!=INVALID_TABLE)&&(m_wReqChairID!=INVALID_CHAIR))
	{
		IUserItem * pIUserItem=m_TableFrame.GetUserInfo(m_wReqTableID,m_wReqChairID);
		if (pIUserItem==m_pMeUserItem) m_TableFrame.SetUserInfo(m_wReqTableID,m_wReqChairID,NULL);
	}

	//��������

	m_wReqTableID=wTableID;
	m_wReqChairID=wChairID;
	m_wFindTableID=INVALID_TABLE;
	m_TableFrame.EnsureVisibleTable(wTableID);
	SendLookonPacket(wTableID,wChairID,NULL);

	return true;
}

//���¶���
bool CRoomViewItem::PerformSitDownAction(WORD wTableID, WORD wChairID)
{
	if(IsServerAllocTable())
	{
		m_wReqTableID=INVALID_TABLE;
		m_wReqChairID=INVALID_CHAIR;
		SendSitDownPacket(1,1,m_pServerOption->m_bPassword?m_pServerOption->m_szPassword:NULL);
		return true;
	}
	//Ч������
	ASSERT(wTableID!=INVALID_TABLE);
	ASSERT(wChairID!=INVALID_CHAIR);

	//����Ч��
	if (CanSitDownTable(wTableID,wChairID,false,true)==false) return false;

	//�������
	if ((m_wReqTableID!=INVALID_TABLE)&&(m_wReqChairID!=INVALID_CHAIR))
	{
		IUserItem * pIUserItem=m_TableFrame.GetUserInfo(m_wReqTableID,m_wReqChairID);
		if (pIUserItem==m_pMeUserItem) m_TableFrame.SetUserInfo(m_wReqTableID,m_wReqChairID,NULL);
	}

	//��������
	m_wReqTableID=wTableID;
	m_wReqChairID=wChairID;
	m_wFindTableID=INVALID_TABLE;
	m_TableFrame.EnsureVisibleTable(wTableID);
	m_TableFrame.SetUserInfo(wTableID,wChairID,m_pMeUserItem);
	SendSitDownPacket(wTableID,wChairID,m_pServerOption->m_bPassword?m_pServerOption->m_szPassword:NULL);

	return true;
}

//������������
bool CRoomViewItem::SendChatPacket(DWORD dwTargetUserID, LPCTSTR pszChatMessage, COLORREF crFontColor)
{
	//��ȡ�û�
	ASSERT(m_pMeUserItem!=NULL);
	tagUserData * pUserData=m_pMeUserItem->GetUserData();

	//��������
	CMD_GR_UserChat UserChat;
	UserChat.crFontColor=crFontColor;
	UserChat.dwTargetUserID=dwTargetUserID;
	UserChat.dwSendUserID=pUserData->dwUserID;
	lstrcpyn(UserChat.szChatMessage,pszChatMessage,CountArray(UserChat.szChatMessage));
	UserChat.wChatLength=CountString(UserChat.szChatMessage);

	//��������
	WORD wSendSize=sizeof(UserChat)-sizeof(UserChat.szChatMessage)+UserChat.wChatLength;
	m_ClientSocket->SendData(MDM_GR_USER,SUB_GR_USER_CHAT,&UserChat,wSendSize);

	return true;
}

//������Ϸ��Ϣ
bool CRoomViewItem::IPCSendGameInfo(CIPCSendCopyData * pSendCopyData)
{
	//Ч�����
	ASSERT(pSendCopyData!=NULL);
	ASSERT(m_pMeUserItem!=NULL);

	//�������
	tagUserData * pUserData=m_pMeUserItem->GetUserData();
	CListKind * pListKind=m_pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();

	//��������
	IPC_GF_ServerInfo ServerInfo;
	memset(&ServerInfo,0,sizeof(ServerInfo));
	ServerInfo.dwUserID=pUserData->dwUserID;
	ServerInfo.wTableID=pUserData->wTableID;
	ServerInfo.wChairID=pUserData->wChairID;
	ServerInfo.wKindID=pGameKind->wKindID;
	ServerInfo.wServerID=pGameServer->wServerID;
	ServerInfo.wGameGenre=m_wGameGenre;
	ServerInfo.wChairCount=m_TableFrame.GetChairCount();
	CopyMemory(&ServerInfo.OptionBuffer,&m_OptionBuffer,sizeof(ServerInfo.OptionBuffer));
	lstrcpyn(ServerInfo.szKindName,pGameKind->szKindName,CountArray(ServerInfo.szKindName));
	lstrcpyn(ServerInfo.szServerName,pGameServer->szServerName,CountArray(ServerInfo.szServerName));

	//��������
	pSendCopyData->SendData(IPC_MAIN_CONFIG,IPC_SUB_SERVER_INFO,&ServerInfo,sizeof(ServerInfo));

	return true;
}

//�����û�
bool CRoomViewItem::IPCSendTableUsers(CIPCSendCopyData * pSendCopyData)
{
	//Ч�����
	ASSERT(pSendCopyData!=NULL);

	//�����Լ���Ϣ
	ASSERT(m_pMeUserItem!=NULL);
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
	ASSERT(pMeUserData->wTableID!=(WORD)INVALID_TABLE);
	if (pMeUserData->wTableID==(WORD)INVALID_TABLE) return false;
	SendTableUser(m_pMeUserItem,pSendCopyData);

	//���������û�
	IUserItem * pIUserItem=NULL;
	tagUserData * pUserData=NULL;

	//��Ϸ�û�
	WORD wEnumIndex=0;
	while (true)
	{
		pIUserItem=m_ClientUserManager.EnumUserItem(wEnumIndex++);
		if (pIUserItem==NULL) break;
		if (pIUserItem==m_pMeUserItem) continue;
		pUserData=pIUserItem->GetUserData();
		if ((pUserData->wTableID==pMeUserData->wTableID)&&(pUserData->cbUserStatus!=US_LOOKON))
			SendTableUser(pIUserItem,pSendCopyData);
	};

	//�Թ��û�
	wEnumIndex=0;
	while (true)
	{
		pIUserItem=m_ClientUserManager.EnumUserItem(wEnumIndex++);
		if (pIUserItem==NULL) break;
		if (pIUserItem==m_pMeUserItem) continue;
		pUserData=pIUserItem->GetUserData();
		if ((pUserData->wTableID==pMeUserData->wTableID)&&(pUserData->cbUserStatus==US_LOOKON))
			SendTableUser(pIUserItem,pSendCopyData);
	};

	return true;
}

//������Ϸ
int CRoomViewItem::StartGameClient()
{
	g_GlobalOption.CloseMedia();
	//�ж��Ƿ��Ѿ�����
	ASSERT(m_pShareMemory!=NULL);
	if ((g_GameProcessInfo.hProcess!=NULL)&&(WaitForSingleObject(g_GameProcessInfo.hProcess,0)==WAIT_TIMEOUT))
	{
		if (m_pShareMemory->hWndGameFrame!=NULL)
		{
			//��ʾ����
			::ShowWindow(m_pShareMemory->hWndGameFrame,SW_SHOW);
			::SetForegroundWindow(m_pShareMemory->hWndGameFrame);

			//������Ϣ
			CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
			IPCSendGameInfo(&SendCopyData);
			IPCSendTableUsers(&SendCopyData);
			SendCopyData.SendData(IPC_MAIN_CONCTROL,IPC_SUB_START_FINISH);

			return SR_ALREADY_EXIST;
		}
		else ::TerminateProcess(g_GameProcessInfo.hProcess,0);
	}

	//��������
	m_hWndChannel=NULL;
	m_pShareMemory->hWndGameFrame=NULL;
	CloseHandle(g_GameProcessInfo.hThread);
	CloseHandle(g_GameProcessInfo.hProcess);
	memset(&g_GameProcessInfo,0,sizeof(g_GameProcessInfo));


	//����������
	CString strCommonLine;
	CListKind * pListKind=m_pListServer->GetListKind();
	tagGameKind * pGameKind=pListKind->GetItemInfo();
	strCommonLine.Format(TEXT("%s /RoomToken:%s /ServerType:%ld /WndPlaza:%d /AutoStart:%d /Title:\"%s\" /sid:%s"),
			pGameKind->szProcessName,
			m_szShareName,
			m_wGameGenre,
			::AfxGetMainWnd()->m_hWnd,IsServerAllocTable(),
			(LPCSTR)g_szGameTitle,
			g_GlobalUnits.GetGolbalUserData().szSessionId);

	//������Ϸ�ͻ���
	STARTUPINFO StartInfo;
	memset(&StartInfo,0,sizeof(StartInfo));
	StartInfo.cb=sizeof(StartInfo);
	StartInfo.wShowWindow=SW_SHOWMAXIMIZED;
	BOOL bSuccess=CreateProcess(NULL,strCommonLine.GetBuffer(),NULL,NULL,FALSE,CREATE_DEFAULT_ERROR_MODE,NULL,NULL,&StartInfo,&g_GameProcessInfo);
	strCommonLine.ReleaseBuffer();
	if (bSuccess==FALSE)
	{
		memset(&g_GameProcessInfo,0,sizeof(g_GameProcessInfo));
		return SR_CREATE_ERROR;
	}

	return SR_CREATE_SUCCESS;
}

//�ر���Ϸ
void CRoomViewItem::CloseGameClient()
{
	//������Ϣ
	if (g_GameProcessInfo.hProcess!=NULL)
	{
		SendProcessData(IPC_MAIN_CONCTROL,IPC_SUB_CLOSE_FRAME,NULL,0);
		DWORD dwResult=::WaitForSingleObject(g_GameProcessInfo.hProcess,1000);
		if (dwResult==WAIT_TIMEOUT) ::TerminateProcess(g_GameProcessInfo.hProcess,0);
	}

	//��������
	m_hWndChannel=NULL;
	m_pShareMemory->hWndGameFrame=NULL;
	CloseHandle(g_GameProcessInfo.hThread);
	CloseHandle(g_GameProcessInfo.hProcess);
	memset(&g_GameProcessInfo,0,sizeof(g_GameProcessInfo));

	return;
}

//���±���
void CRoomViewItem::UpdateTitleText()
{
	//ˢ�½���
	//CRect rcInvalidate;
	//rcInvalidate.SetRect(0,0,rcVorSplitter.left-BUTTON_AREA_WIDTH,TABLE_TOP);
	//InvalidateRect(&rcInvalidate);

	return;
}

//����ͼ��
void CRoomViewItem::DrawLeftViewFrame(CDC * pDC)
{

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	HDC hDC=pDC->m_hDC;
	int nXPos=0,nYPos=0;

	//������Դ

	CImageHandle m_ImageTopHandle(&m_ImageTop);

	CImageHandle m_ImageInfoHandle(&m_ImageInfo);
	CImageHandle m_ImageWebHandle(&m_ImageWeb);

	CImageHandle m_ImageMLHandle(&m_ImageML);
	CImageHandle m_ImageMRHandle(&m_ImageMR);

	CImageHandle ImageChatTLHandle(&m_ImageChatTL);
	CImageHandle ImageChatTMHandle(&m_ImageChatTM);
	CImageHandle ImageChatTRHandle(&m_ImageChatTR);

	CImageHandle QQShowLHandle(&m_QQShowL);
	CImageHandle QQShowRHandle(&m_QQShowR);
	CImageHandle QQShowBHandle(&m_QQShowB);

	m_ImageTop.BitBlt(hDC,m_UserListView.GetWidth()+2,0);

	m_ImageML.StretchBlt(hDC,
			CRect(0,0,m_ImageML.GetWidth(),rcClient.bottom),
			CRect(0,0,m_ImageML.GetWidth(),m_ImageML.GetHeight())
			);
	m_ImageMR.StretchBlt(hDC,
		CRect(rcClient.right-m_ImageMR.GetWidth(),0,rcClient.right,rcClient.bottom),
		CRect(0,0,m_ImageMR.GetWidth(),m_ImageMR.GetHeight())
			);

	m_ImageInfo.StretchBlt(hDC,
		CRect(2,0,m_ImageInfo.GetWidth()+2,m_ImageInfo.GetHeight()),
		CRect(0,0,m_ImageInfo.GetWidth(),m_ImageInfo.GetHeight())
		);
	CRect cr;
	GetClientRect(cr);
	m_ImageWeb.StretchBlt(hDC,
		CRect(2,cr.Height()-98,m_ImageInfo.GetWidth()+2,cr.Height()-98+m_ImageInfo.GetHeight()),
		CRect(0,0,m_ImageInfo.GetWidth(),m_ImageInfo.GetHeight())
		);




	//QQShow����
	//m_QQShowL.BitBlt(hDC,m_ImageML.GetWidth(),m_UserListView.GetHeight());
	//m_QQShowR.BitBlt(hDC,m_ImageML.GetWidth()+m_UserListView.GetWidth() - m_QQShowR.GetWidth(),m_UserListView.GetHeight());
	//m_QQShowB.BitBlt(hDC,m_ImageML.GetWidth(),rcClient.bottom - m_QQShowB.GetHeight());


	//���촰��
	///*
	//m_ImageChatTM.StretchBlt(hDC,
	//		CRect(m_UserListView.GetWidth()+231,rcClient.bottom-CHAT_HEIGHT,rcClient.right-13,rcClient.bottom),
	//		CRect(0,0,m_ImageChatTM.GetWidth(),m_ImageChatTM.GetHeight())
	//		);

	//m_ImageChatTL.BitBlt(hDC,m_UserListView.GetWidth()+5,rcClient.bottom-CHAT_HEIGHT);
	//m_ImageChatTR.BitBlt(hDC,rcClient.right-13,rcClient.bottom-CHAT_HEIGHT);


	m_ImageChatTL.BitBlt(hDC,m_UserListView.GetWidth()+2,rcClient.bottom-CHAT_HEIGHT);
	m_ImageChatTM.StretchBlt(hDC,
			CRect(m_UserListView.GetWidth()+291,rcClient.bottom-CHAT_HEIGHT,rcClient.right-326,rcClient.bottom),
			CRect(0,0,m_ImageChatTM.GetWidth(),CHAT_HEIGHT)
			);
	m_ImageChatTR.BitBlt(hDC,rcClient.right-326,rcClient.bottom-CHAT_HEIGHT);


//*/
/*
	//�������
	TCHAR szRoomTitle[128]=TEXT("");
	CListKind * pListKind=m_pListServer->GetListKind();
	_snprintf(szRoomTitle,sizeof(szRoomTitle),TEXT("[%s]%s(%ld��)"),pListKind->GetItemInfo()->szKindName,
		m_pListServer->GetItemInfo()->szServerName,m_ClientUserManager.GetOnLineCount());

	//�������
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(10,10,10));
	pDC->SelectObject(&CSkinAttribute::m_DefaultFont);
	CRect rcTitle(35,38,205,50);
	pDC->DrawText(szRoomTitle,lstrlen(szRoomTitle),&rcTitle,DT_END_ELLIPSIS|DT_VCENTER|DT_SINGLELINE);
*/

	tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();

	if (UserData.dwUserID!=0)
	{
		CRect cr;
		GetClientRect(cr);
		//���� DC
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(CSkinAttribute::m_DefaultFont);

		//�û�����
		TCHAR szBuffer[128];
		pDC->SetTextColor(RGB(255,255,255));
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("%s"),UserData.szAccounts);
		pDC->TextOut(80,42,szBuffer,lstrlen(szBuffer));

		//�û�����
		//_snprintf(szBuffer,CountArray(szBuffer),TEXT("���ţ�%s"),UserData.szGroupName);
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("���ţ�%s"),UserData.szGroupName);
		pDC->TextOut(80,62,szBuffer,lstrlen(szBuffer));

		LPCTSTR pszMember[]={TEXT("��ͨ��Ա"),TEXT("�м���Ա"),TEXT("�߼���Ա")};
		BYTE cbMember=UserData.cbMember;
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("%s"),pszMember[cbMember]);
		pDC->TextOut(80,82,szBuffer,lstrlen(szBuffer));
		//CRect re;

		//GetWindowRect(re);
		//CString aa;
		//aa.Format("%d,%d",re.right,re.bottom);
		//MessageBox(aa);
		//�û�ͷ��
		g_GlobalUnits.m_UserFaceRes->DrawBigFace(pDC,14,42,UserData.wFaceID);
	}//

	return;
}

//��������
bool CRoomViewItem::FindGameTable(tagFindTable & FindInfo)
{
	//��������
	WORD wNullCount=0;
	ITableView * pTableView=NULL;
	WORD wChairUser=m_TableFrame.GetChairCount();
	WORD wMeTableID=m_pMeUserItem->GetUserData()->wTableID;

	//��������
	for (WORD i=0;i<m_TableFrame.GetTableCount();i++)
	{
		FindInfo.wResultTableID=(FindInfo.wBeginTableID+i)%m_TableFrame.GetTableCount();
		if (wMeTableID!=FindInfo.wResultTableID)
		{
			//��ȡ����
			pTableView=m_TableFrame.GetTableArrayPtr(FindInfo.wResultTableID);
			ASSERT(pTableView!=NULL);

			//�ж��Ƿ�ʼ��Ϸ
			if (pTableView->QueryPlayFlag()==true) continue;

			//��������
			bool bTablePass=pTableView->QueryPassFlag();
			if ((FindInfo.bFilterPass==true)&&(bTablePass==true)) continue;

			//Ѱ�ҿ�λ��
			wNullCount=pTableView->GetNullChairCount(FindInfo.wResultChairID);

			//Ч�����
			if (CanSitDownTable(FindInfo.wResultTableID,FindInfo.wResultChairID,false,false)==false) continue;

			//�ж���Ŀ
			if (wNullCount>0)
			{
				if ((FindInfo.bNotFull==true)&&(wNullCount<wChairUser)) return true;
				if ((FindInfo.bOneNull==true)&&(wNullCount==1)) return true;
				if ((FindInfo.bTwoNull==true)&&(wNullCount==2)) return true;
				if ((FindInfo.bAllNull==true)&&(wNullCount==wChairUser)) return true;
			}
		}
	}

	//��������
	FindInfo.wResultTableID=INVALID_TABLE;
	FindInfo.wResultChairID=INVALID_CHAIR;

	return false;
}

//�����ؼ�
void CRoomViewItem::RectifyControl(int nWidth, int nHeight)
{
	//״̬�ж�
	if (m_bInitDialog==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//��������
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//�ƶ��ؼ�
	HDWP hDwp=BeginDeferWindowPos(32);

	//QQShow
	//DeferWindowPos(hDwp,m_pHtmlBrower->GetSafeHwnd(),NULL,43,nHeight-233,140,226,uFlags);

	//��������
	DeferWindowPos(hDwp,m_TableFrame,NULL,2+m_UserListView.GetWidth(),27 ,nWidth - m_UserListView.GetWidth()-5,
		nHeight - CHAT_HEIGHT-27,uFlags);

	//�б�����
	//m_UserListView.SetWindowPos(NULL,5,0,0,0,SWP_NOSIZE);
	//m_UserListView.SetHeight(nHeight-233);//233ΪQQShow�ĸ߶�
	m_UserListView.UpdateButton();

	//��������
	CRect rcButton;
	int nChatTop=nHeight-CHAT_BOTTOM_DISTANCE-CHAT_HEIGHT+6;

	m_btPhrase.GetWindowRect(&rcButton);
	//CButton * pButtonArray[]={&m_btExpression,&m_btColorSet,&m_btCleanScreen};
	CButton * pButtonArray[]={&m_btSendChat,&m_btExpression,&m_btColorSet};
	for (int i=0;i<CountArray(pButtonArray);i++)
	{
		DeferWindowPos(hDwp,pButtonArray[i]->m_hWnd,NULL,m_UserListView.GetWidth()+529+i*25,nHeight - 47,rcButton.Width(),rcButton.Height(),uFlags);
	}

	DeferWindowPos(hDwp,m_ChatMessage,NULL,m_UserListView.GetWidth()+10,nChatTop+39,nWidth-m_UserListView.GetWidth()-345,CHAT_HEIGHT-69,uFlags);//��Ϣ��
	//DeferWindowPos(hDwp,m_ChatObject,NULL,m_UserListView.GetWidth()+15,nHeight - 55,70,200,uFlags);//�������ѡ��
	//DeferWindowPos(hDwp,m_ChatInput,NULL,m_UserListView.GetWidth()+8,nHeight - 28,180 ,19,uFlags);//�����
	DeferWindowPos(hDwp,m_ChatObject,NULL,m_UserListView.GetWidth()+307,nHeight - 45,70,200,uFlags);//�������ѡ��
	DeferWindowPos(hDwp,m_ChatInput,NULL,m_UserListView.GetWidth()+377,nHeight - 40,150 ,19,uFlags);//�����
	m_btSendChat.GetWindowRect(&rcButton);
	//DeferWindowPos(hDwp,m_btSendChat,NULL,m_UserListView.GetWidth()+190,nHeight - 30,rcButton.Width(),rcButton.Height(),uFlags);//���Ͱ�ť


	
	int nTableCenter=m_UserListView.GetWidth() + (nWidth-m_UserListView.GetWidth())/2;
	m_btAutoSit.GetWindowRect(&rcButton);

	int RoomSpace = 62 ;
	DeferWindowPos(hDwp,m_btRoom1,NULL,m_UserListView.GetWidth()+RoomSpace+2,5,62,22,uFlags);
	DeferWindowPos(hDwp,m_btRoom2,NULL,m_UserListView.GetWidth()+RoomSpace*2+2,5,62,22,uFlags);
	DeferWindowPos(hDwp,m_btRoom3,NULL,m_UserListView.GetWidth()+RoomSpace*3+2,5,62,22,uFlags);
	DeferWindowPos(hDwp,m_btRoom4,NULL,m_UserListView.GetWidth()+RoomSpace*4+2,5,62,22,uFlags);
	DeferWindowPos(hDwp,m_btRoom5,NULL,m_UserListView.GetWidth()+RoomSpace*5+2,5,62,22,uFlags);
	DeferWindowPos(hDwp,m_btRoom6,NULL,m_UserListView.GetWidth()+RoomSpace*6+2,5,62,22,uFlags);
	//DeferWindowPos(hDwp,m_btRoomExit,NULL,m_UserListView.GetWidth()+RoomSpace*7+2,5,62,22,uFlags);
	DeferWindowPos(hDwp,m_btRoomExit,NULL,nWidth-62,5,62,22,uFlags);


	//���밴ť
	//DeferWindowPos(hDwp,m_btAutoSit,NULL,nTableCenter-130,0,rcButton.Width(),rcButton.Height(),uFlags);
	DeferWindowPos(hDwp,m_btAutoSit,NULL,m_UserListView.GetWidth()+77,nHeight-136,rcButton.Width(),rcButton.Height(),uFlags);
	//���Ұ�ť
	//m_btFindUser.ShowWindow(SW_HIDE);
	if(IsServerAllocTable())
	{
		DeferWindowPos(hDwp,m_btFindUser,NULL,m_UserListView.GetWidth()+151,nHeight-136,rcButton.Width(),rcButton.Height(),uFlags);
		m_btFindUser.EnableWindow(false);
	}
	else
		DeferWindowPos(hDwp,m_btFindUser,NULL,m_UserListView.GetWidth()+151,nHeight-136,rcButton.Width(),rcButton.Height(),uFlags);
		//DeferWindowPos(hDwp,m_btFindUser,NULL,nTableCenter+20,0,rcButton.Width(),rcButton.Height(),uFlags);

	m_UserListView.SetHeight(nHeight-213);//y��11����77
	m_UserListView.SetWindowPos(NULL,2,120,0,0,SWP_NOSIZE);//y��6����71
	m_UserListView.UpdateButton();

	EndDeferWindowPos(hDwp);

	//�ػ�����
	Invalidate(FALSE);
	UpdateWindow();

	return;
}

//��ʾ��Ϣ
int CRoomViewItem::ShowMessageBox(LPCTSTR pszMessage, UINT nType)
{
	tagGameServer * pGameServer=m_pListServer->GetItemInfo();
	int nResult=MessageBox(pszMessage,pGameServer->szServerName,nType);
	return nResult;
}

//�����û�
bool CRoomViewItem::SendTableUser(IUserItem * pIUserItem, CIPCSendCopyData * pSendCopyData)
{
	//Ч�����
	ASSERT(pIUserItem!=NULL);
	ASSERT(pSendCopyData!=NULL);

	//�������
	BYTE cbBuffer[IPC_PACKAGE];
	tagUserData * pUserData=pIUserItem->GetUserData();
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)cbBuffer;

	//��������
	memset(cbBuffer,0,sizeof(cbBuffer));
	pUserInfoHead->dwUserID=pUserData->dwUserID;
	pUserInfoHead->dwGroupID=pUserData->dwGroupID;
	pUserInfoHead->dwUserRight=pUserData->dwUserRight;
	pUserInfoHead->dwMasterRight=pUserData->dwMasterRight;
	pUserInfoHead->wFaceID=pUserData->wFaceID;
	pUserInfoHead->wTableID=pUserData->wTableID;
	pUserInfoHead->wChairID=pUserData->wChairID;
	pUserInfoHead->wNetDelay=pUserData->wNetDelay;
	pUserInfoHead->cbGender=pUserData->cbGender;
	pUserInfoHead->cbMember=pUserData->cbMember;
	pUserInfoHead->cbUserStatus=pUserData->cbUserStatus;
	pUserInfoHead->UserScoreInfo.lGold=pUserData->lGold;
	pUserInfoHead->UserScoreInfo.lScore=pUserData->lScore;
	pUserInfoHead->UserScoreInfo.lWinCount=pUserData->lWinCount;
	pUserInfoHead->UserScoreInfo.lLostCount=pUserData->lLostCount;
	pUserInfoHead->UserScoreInfo.lDrawCount=pUserData->lDrawCount;
	pUserInfoHead->UserScoreInfo.lFleeCount=pUserData->lFleeCount;
	pUserInfoHead->UserScoreInfo.lExperience=pUserData->lExperience;

	//��������
	WORD wHeadSize=sizeof(tagUserInfoHead);
	CSendPacketHelper SendPacketHelper(cbBuffer+wHeadSize,sizeof(cbBuffer)-wHeadSize);
	SendPacketHelper.AddPacket(pUserData->szName,CountString(pUserData->szName),DTP_USER_ACCOUNTS);
	SendPacketHelper.AddPacket(&pUserData->cbCompanion,sizeof(pUserData->cbCompanion),DTP_USER_COMPANION);
	SendPacketHelper.AddPacket(pUserData->szGroupName,CountString(pUserData->szGroupName),DTP_USER_GROUP_NAME);
	
	//��������
	WORD wSendSize=wHeadSize+SendPacketHelper.GetDataSize();
	pSendCopyData->SendData(IPC_MAIN_USER,IPC_SUB_USER_COME,cbBuffer,wSendSize);

	return true;
}

//������Ϣ
bool CRoomViewItem::SendProcessData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize)
{
	//������Ϣ
	CIPCSendCopyData IPCSendCopyData(m_hWndChannel,m_hWnd);
	return IPCSendCopyData.SendData(wMainCmdID,wSubCmdID,pBuffer,wDataSize);
}

//�ܷ�����
bool CRoomViewItem::CanSitDownTable(WORD wTableID, WORD wChairID, bool bLookon, bool bShowError)
{
	//Ч�����
	ASSERT(wTableID!=INVALID_TABLE);
	ASSERT(wChairID!=INVALID_CHAIR);
	if (wTableID>=m_TableFrame.GetTableCount()) return false;
	if (wChairID>=m_TableFrame.GetChairCount()) return false;
	if (m_ServiceStatus!=ServiceStatus_Serviceing) return false;

	//�ж���Ӧ
	if ((m_wReqTableID!=INVALID_TABLE)||(m_wReqChairID!=INVALID_CHAIR))
	{
		if (bShowError==true)
		{
			LPCTSTR pszDescribe=TEXT("�ϴ�����û���յ���������Ӧ,���Ժ�");
			ShowMessageBox(pszDescribe,MB_ICONINFORMATION);
			return false;
		}
	}

	//�ж����
	ITableView * pITableView=m_TableFrame.GetTableArrayPtr(wTableID);
	IUserItem * pITableUserItem=pITableView->GetUserInfo(wChairID);
	if ((bLookon==true)&&(pITableUserItem==NULL)) return false;
	if ((bLookon==false)&&(pITableUserItem!=NULL)) return false;

	//�ж�״̬
	BYTE cbUserStatus=m_pMeUserItem->GetUserData()->cbUserStatus;
	if (cbUserStatus==US_PLAY)
	{
		if (bShowError==true)
		{
			LPCTSTR pszDescribe=TEXT("��������Ϸ�У���ʱ���ܻ�λ�ã����Ƚ�����Ϸ��");
			ShowMessageBox(pszDescribe,MB_ICONINFORMATION);
		}
		return false;
	}

	//�ж���Ϸ״̬
	bool bGameStart=pITableView->QueryPlayFlag();
	if ((bGameStart==true)&&(bLookon==false))
	{
		if (bShowError==true)
		{
			LPCTSTR pszDescribe=TEXT("����Ϸ���Ѿ���ʼ��Ϸ�ˣ���ʱ���ܼ��룡");
			ShowMessageBox(pszDescribe,MB_ICONINFORMATION);
		}
		return false;
	}
	if ((bGameStart==false)&&(bLookon==true)&&(m_pMeUserItem->GetUserData()->dwMasterRight==0)) return false;

	//�ж�����
	if ((pITableView->QueryPassFlag()==true)&&(m_pServerOption->m_bPassword==false))
	{
		if (bShowError==true)
		{
			LPCTSTR pszDescribe=TEXT("����Ϸ���������������룬���������������룡");
			ShowMessageBox(pszDescribe,MB_ICONINFORMATION);
			;
			//CString s;
			//s.Format("%d",((CDlgControlBar*)GetParent())->m_rcViewItem.bottom);
			//MessageBox(s);
			//((CDlgControlBar*)GetParent())->
			//((CGameFrame*)theApp.GetMainWnd())->m_DlgControlBar.m_;
			
		}
		return false;
	}

	//�Թ��ж�
	if (bLookon==true) return true;

	//�����ж�
	tagUserData * pTableUserData=NULL;
	for (WORD i=0;i<m_TableFrame.GetTableCount();i++)
	{
		//��ȡ�û�
		pITableUserItem=pITableView->GetUserInfo(i);
		if ((pITableUserItem==NULL)||(pITableUserItem==m_pMeUserItem)) continue;
		pTableUserData=pITableUserItem->GetUserData();

		//������ʱ
		if (m_pGameOption->m_bLimitDelay==true)
		{
			if (pTableUserData->wNetDelay>m_pGameOption->m_wNetDelay)
			{
				if (bShowError==true)
				{
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("[ %s ] ��������ʱ̫���ˣ���������ò�����"),pTableUserData->szName);
					ShowMessageBox(szDescribe,MB_ICONINFORMATION);
				}
				return false;
			}
		}

		//������
		if (g_GlobalOption.m_bLimitDetest==true)
		{
			if (pTableUserData->cbCompanion==enCompanion_Detest)
			{
				if (bShowError==true)
				{
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("�������˲��벻�ܻ�ӭ�������Ϸ���������㲻��ӭ����� [ %s ] ��"),pTableUserData->szName);
					ShowMessageBox(szDescribe,MB_ICONINFORMATION);
				}
				return false;
			}
		}

		//ʤ��Ч��
		if (m_pGameOption->m_bLimitWin)
		{
			WORD wWinRate=0;
			LONG lAllCount=pITableUserItem->GetUserPlayCount();
			if (lAllCount>0) wWinRate=(WORD)(pTableUserData->lWinCount*10000/lAllCount);
			if (wWinRate<m_pGameOption->m_wWinRate)
			{
				if (bShowError==true)
				{
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("[ %s ] ��ʤ��̫���ˣ���������ò�����"),pTableUserData->szName);
					ShowMessageBox(szDescribe,MB_ICONINFORMATION);
				}
				return false;
			}
		}

		//����Ч��
		if (m_pGameOption->m_bLimitFlee)
		{
			WORD wFillRate=0;
			LONG lAllCount=pITableUserItem->GetUserPlayCount();
			if (lAllCount>0) wFillRate=(WORD)(pTableUserData->lFleeCount*10000/lAllCount);
			if ((wFillRate>0)&&(wFillRate>m_pGameOption->m_wFleeRate))
			{
				if (bShowError==true)
				{
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("[ %s ] ��������̫���ˣ���������ò�����"),pTableUserData->szName);
					ShowMessageBox(szDescribe,MB_ICONINFORMATION);
				}
				return false;
			}
		}

		//��Ϸ��Ч��
		if (m_pGameOption->m_bLimitScore)
		{
			LONG lTableUserScore=pTableUserData->lScore;
			if (lTableUserScore>m_pGameOption->m_lMaxScore)
			{
				if (bShowError==true)
				{
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("[ %s ] ����Ϸ��̫���ˣ���������ò�����"),pTableUserData->szName);
					ShowMessageBox(szDescribe,MB_ICONINFORMATION);
				}
				return false;
			}
			if (lTableUserScore<m_pGameOption->m_lLessScore)
			{
				if (bShowError==true)
				{
					TCHAR szDescribe[128]=TEXT("");
					_snprintf(szDescribe,sizeof(szDescribe),TEXT("[ %s ] ����Ϸ��̫���ˣ���������ò�����"),pTableUserData->szName);
					ShowMessageBox(szDescribe,MB_ICONINFORMATION);
				}
				return false;
			}
		}
	}

	return true;
}

//����������Ϣ
bool __cdecl CRoomViewItem::OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke)
{
	//������
	if (iErrorCode!=0)
	{
		g_GlobalAttemper.DestroyStatusWnd(this);
		ShowMessageBox(pszErrorDesc,MB_ICONINFORMATION);
		g_pControlBar->CloseRoomViewItem(this);
		return true;
	}

	//���͵�¼��Ϣ
	SendLogonPacket();
	m_ServiceStatus=ServiceStatus_EfficacyUser;

	return true;
}

//�����ȡ��Ϣ
bool __cdecl CRoomViewItem::OnSocketRead(CMD_Command Command, 
										 void * pBuffer, 
										 WORD wDataSize, 
										 IClientSocket * pIClientSocke)
{
	switch (Command.wMainCmdID)
	{
	case MDM_GR_LOGON:			//��¼��Ϣ
		{
			return OnSocketMainLogon(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case MDM_GR_USER:			//�û���Ϣ
		{
			return OnSocketMainUser(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case MDM_GR_INFO:			//������Ϣ
		{
			return OnSocketMainInfo(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case MDM_GR_STATUS:			//״̬��Ϣ
		{
			return OnSocketMainStatus(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case MDM_GR_SYSTEM:			//ϵͳ��Ϣ
		{
			return OnSocketMainSystem(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case MDM_GR_SERVER_INFO:	//������Ϣ
		{
			return OnSocketMainServerInfo(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case MDM_GF_GAME:			//��Ϸ��Ϣ
	case MDM_GF_FRAME:			//�����Ϣ
		{
			return OnSocketMainGameFrame(Command,pBuffer,wDataSize,pIClientSocke);
		}
	}

	return true;
}

//����ر���Ϣ
bool __cdecl CRoomViewItem::OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer)
{
	//�жϹر�
	bool bCloseRoomView=(m_ServiceStatus!=ServiceStatus_Serviceing);

	//�رմ���
	CloseGameClient();
	g_GlobalAttemper.DestroyStatusWnd(this);
	m_ServiceStatus=ServiceStatus_NetShutDown;
	if (bCloseByServer) 
	{
		m_MessageProxyHelper->InsertSystemString("�����������⣬���Ѿ���������Ͽ����ӣ�����������",0);
		ShowMessageBox("�����������⣬���Ѿ���������Ͽ����ӣ�����������",MB_ICONINFORMATION);
	}
	else ShowMessageBox("�����������ݰ�����ʧ�ܣ������ж���",MB_ICONINFORMATION);

	//�رշ���
	if (bCloseRoomView==true) g_pControlBar->CloseRoomViewItem(this);

	::ShowWindow(AfxGetMainWnd()->GetSafeHwnd(),SW_RESTORE);
	return true;
}

//��¼��Ϣ
bool CRoomViewItem::OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GR_LOGON);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_LOGON_SUCCESS:		//��¼�ɹ�
		{
			//���ñ���
			m_ServiceStatus=ServiceStatus_RecvConfigInfo;

			return true;
		}
	case SUB_GR_LOGON_ERROR:		//��¼ʧ��
		{
			//Ч�����
			CMD_GR_LogonError * pLogonError=(CMD_GR_LogonError *)pBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//�ر�����
			g_GlobalAttemper.DestroyStatusWnd(this);
			pIClientSocke->CloseSocket(false);
			m_ServiceStatus=ServiceStatus_NetShutDown;

			//��ʾ��Ϣ
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GR_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe,MB_ICONINFORMATION);
			}

			//�رշ���
			g_pControlBar->CloseRoomViewItem(this);

			return true;
		}
	case SUB_GR_LOGON_FINISH:		//��¼���
		{
			//���ý���
			m_TableFrame.ShowUserInfo(true);
			g_GlobalAttemper.DestroyStatusWnd(this);
			g_pControlBar->ActiveRoomViewItem(this);

			//���ñ���
			m_ServiceStatus=ServiceStatus_Serviceing;

			//���͹���
			SendUserRulePacket();

			//�����ж�
			ASSERT(m_pMeUserItem!=NULL);
			tagUserData * pUserData=m_pMeUserItem->GetUserData();
			if (pUserData->wTableID!=INVALID_TABLE)
			{
				int iResult=StartGameClient();
			}

			return true;
		}
	}

	return true;
}

//�û���Ϣ
bool CRoomViewItem::OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_USER_COME:			//�û�����
		{
			return OnSocketSubUserCome(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case SUB_GR_USER_STATUS:		//�û�״̬
		{
			return OnSocketSubStatus(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case SUB_GR_USER_SCORE:			//�û�����
		{
			return OnSocketSubScore(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case SUB_GR_SIT_FAILED:			//����ʧ��
		{
			return OnSocketSubSitFailed(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case SUB_GR_USER_CHAT:			//�û�����
		{
			return OnSocketSubChat(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case SUB_GR_USER_WISPER:		//�û�˽��
		{
			return OnSocketSubWisper(Command,pBuffer,wDataSize,pIClientSocke);
		}
	case SUB_GR_USER_INVITE:		//�������
		{
			return OnSocketSubUserInvite(Command,pBuffer,wDataSize,pIClientSocke);
		}
	}

	return true;
}

//������Ϣ
bool CRoomViewItem::OnSocketMainInfo(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GR_INFO);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_SERVER_INFO:	//������Ϣ
		{
			//Ч������
			ASSERT(wDataSize>=sizeof(CMD_GR_ServerInfo));
			if (wDataSize<sizeof(CMD_GR_ServerInfo)) return false;

			//��Ϣ����
			CMD_GR_ServerInfo * pServerInfo=(CMD_GR_ServerInfo *)pBuffer;
			m_wGameGenre=pServerInfo->wGameGenre;

			//��ȡ��Ϣ
			CListKind * pListKind=m_pListServer->GetListKind();
			tagGameKind * pGameKind=pListKind->GetItemInfo();
			IUnknownEx * pIUnknownEx=GET_MYSELF_INTERFACE(IUnknownEx);
			//m_UserListView.m_wKindID=pServerInfo->wKindID;
			//m_UserListView.m_wGameGenre=pServerInfo->wGameGenre;

			//��������
			try
			{
				m_TableFrame.CreateTableFrame(this,100);
				m_TableFrame.InitTableFrame(pServerInfo->wTableCount,pServerInfo->wChairCount,pGameKind,pIUnknownEx);
			}
			catch (...)
			{
				//�ر�����
				m_ClientSocket->CloseSocket(false);
				g_GlobalAttemper.DestroyStatusWnd(this);

				//��ʾ��Ϣ
				int nResult=ShowMessageBox(TEXT("��Ϸ������Դ����ʧ�ܣ��������ذ�װ���ܻ������⣬�Ƿ��������أ�"),MB_ICONQUESTION|MB_YESNO);
				if (nResult==IDYES) 
				{
					CListKind * pListKind=m_pListServer->GetListKind();
					tagGameKind * pGameKind=pListKind->GetItemInfo();
					g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
				}

				//�رշ���
				IRoomViewItem * pIRoomViewItem=GET_MYSELF_INTERFACE(IRoomViewItem);
				g_pControlBar->CloseRoomViewItem(pIRoomViewItem);

				return false;
			}

			return true;
		}
	case SUB_GR_COLUMN_INFO:	//�б����
		{
			//��������
			CMD_GR_ColumnInfo * pColumnInfo=(CMD_GR_ColumnInfo *)pBuffer;
			WORD wHeadSize=sizeof(CMD_GR_ColumnInfo)-sizeof(pColumnInfo->ColumnItem);

			//Ч�����
			ASSERT(wDataSize>=wHeadSize);
			ASSERT((wHeadSize+pColumnInfo->wColumnCount*sizeof(pColumnInfo->ColumnItem[0]))==wDataSize);
			if (wDataSize<wHeadSize) return false;
			if ((wHeadSize+pColumnInfo->wColumnCount*sizeof(pColumnInfo->ColumnItem[0]))!=wDataSize) return false;

			//�����б�
			CopyMemory(&m_ListColumnInfo,pColumnInfo,__min(wDataSize,sizeof(m_ListColumnInfo)));
			//m_UserListView.SetColumnDescribe(pColumnInfo->ColumnItem,pColumnInfo->wColumnCount);

			return true;
		}
	case SUB_GR_CONFIG_FINISH:	//�������
		{
			//��ʾ����
			ShowWindow(SW_SHOW);
			g_pControlBar->ActiveRoomViewItem(this);

			//���ñ���
			m_ServiceStatus=ServiceStatus_RecvRoomInfo;

			return true;
		}
	}

	return true;
}

//״̬��Ϣ
bool CRoomViewItem::OnSocketMainStatus(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GR_STATUS);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_TABLE_INFO:		//������Ϣ
		{
			//��������
			CMD_GR_TableInfo * pTableInfo=(CMD_GR_TableInfo *)pBuffer;
			const WORD wHeadSize=sizeof(CMD_GR_TableInfo)-sizeof(pTableInfo->TableStatus);

			//Ч������
			ASSERT(wDataSize>=wHeadSize);
			ASSERT((wHeadSize+pTableInfo->wTableCount*sizeof(pTableInfo->TableStatus[0]))==wDataSize);
			if (wDataSize<wHeadSize) return false;
			if ((wHeadSize+pTableInfo->wTableCount*sizeof(pTableInfo->TableStatus[0]))!=wDataSize) return false;

			//��Ϣ����
			for (WORD i=0;i<pTableInfo->wTableCount;i++)
			{
				m_TableFrame.SetPassFlag(i,pTableInfo->TableStatus[i].bTableLock?true:false);
				m_TableFrame.SetPlayFlag(i,pTableInfo->TableStatus[i].bPlayStatus?true:false);
			}

			return true;
		}
	case SUB_GR_TABLE_STATUS:	//����״̬
		{
			//Ч������
			ASSERT(wDataSize>=sizeof(CMD_GR_TableStatus));
			if (wDataSize<sizeof(CMD_GR_TableStatus)) return false;

			//��Ϣ����
			CMD_GR_TableStatus * pTableStatus=(CMD_GR_TableStatus *)pBuffer;
			ASSERT(pTableStatus->wTableID<m_TableFrame.GetTableCount());
			if (pTableStatus->wTableID<m_TableFrame.GetTableCount())
			{
				//�����û�
				IUserItem * pIUserItem=NULL;
				tagUserData * pUserData=NULL;
				BYTE cbUserStatus=pTableStatus->bPlayStatus?US_PLAY:US_SIT;
				for (WORD i=0;i<m_TableFrame.GetChairCount();i++)
				{
					pIUserItem=m_TableFrame.GetUserInfo(pTableStatus->wTableID,i);
					if (pIUserItem!=NULL)
					{
						pUserData=pIUserItem->GetUserData();
						if (pUserData->cbUserStatus!=US_OFFLINE) 
						{
							pUserData->cbUserStatus=cbUserStatus;
							OnUserItemUpdate(pIUserItem);
						}
					}
				}

				//��������
				m_TableFrame.SetPlayFlag(pTableStatus->wTableID,pTableStatus->bPlayStatus?true:false);

				//֪ͨ��Ϸ
				tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
				if (pMeUserData->wTableID==pTableStatus->wTableID)
				{
					WORD wSubCmdID=pTableStatus->bPlayStatus?IPC_SUB_GAME_START:IPC_SUB_GAME_FINISH;
					SendProcessData(IPC_MAIN_USER,wSubCmdID,NULL,0);
				}
			}

			return true;
		}
	}

	return true;
}

//ϵͳ��Ϣ
bool CRoomViewItem::OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SYSTEM);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_MESSAGE:		//ϵͳ��Ϣ
		{
			//Ч�����
			CMD_GR_Message * pMessage=(CMD_GR_Message *)pBuffer;
			ASSERT(wDataSize>(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent)));
			if (wDataSize<=(sizeof(CMD_GR_Message)-sizeof(pMessage->szContent))) return false;

			//��Ϣ����
			WORD wHeadSize=sizeof(CMD_GR_Message)-sizeof(pMessage->szContent);
			ASSERT(wDataSize==(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR)));
			if (wDataSize!=(wHeadSize+pMessage->wMessageLength*sizeof(TCHAR))) return false;
			pMessage->szContent[pMessage->wMessageLength-1]=0;

			//�ر�����
			bool bIntermet=false;
			if (pMessage->wMessageType&SMT_INTERMIT_LINE) bIntermet=true;
			else if (pMessage->wMessageType&SMT_CLOSE_ROOM) bIntermet=true;
			if (bIntermet==true) 
			{
				g_GlobalAttemper.DestroyStatusWnd(this);
				m_ClientSocket->CloseSocket(false);
				CloseGameClient();
			}

			//��ʾ��Ϣ
			if (pMessage->wMessageType&SMT_INFO) m_MessageProxyHelper->InsertSystemString(pMessage->szContent,MS_NORMAL);
			if (pMessage->wMessageType&SMT_EJECT) ShowMessageBox(pMessage->szContent,MB_ICONINFORMATION);

			//�رշ���
			if (pMessage->wMessageType&SMT_CLOSE_ROOM) 
			{
				IRoomViewItem * pIRoomViewItem=GET_MYSELF_INTERFACE(IRoomViewItem);
				g_pControlBar->CloseRoomViewItem(pIRoomViewItem);
			}

			return true;
		}
	}

	return true;
}

//������Ϣ
bool CRoomViewItem::OnSocketMainServerInfo(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GR_SERVER_INFO);
	switch (Command.wSubCmdID)
	{
	case SUB_GR_ONLINE_COUNT_INFO:		//������Ϣ
		{
			//Ч������
			ASSERT(wDataSize%sizeof(tagOnLineCountInfo)==0);
			if (wDataSize%sizeof(tagOnLineCountInfo)!=0) return false;

			//��Ϣ����
			WORD wKindID=0;
			DWORD dwKindOnLineCount=0,dwAllOnLineCount=0L;
			WORD wInfoCount=wDataSize/sizeof(tagOnLineCountInfo);
			tagOnLineCountInfo * pOnLineCountInfo=(tagOnLineCountInfo *)pBuffer;
			for (int i=0;i<wInfoCount;i++)
			{
				wKindID=(pOnLineCountInfo+i)->wKindID;
				dwKindOnLineCount=(pOnLineCountInfo+i)->dwOnLineCount;
				dwAllOnLineCount+=dwKindOnLineCount;
				g_GlobalUnits.m_ServerListManager.UpdateGameKindOnLine(wKindID,dwKindOnLineCount);
			}

			//��������
			g_GlobalUnits.m_ServerListManager.UpdateGameOnLineCount(dwAllOnLineCount);

			return true;
		}
	}

	return true;
}

//��Ϸ��Ϣ
bool CRoomViewItem::OnSocketMainGameFrame(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	//Ч������
	ASSERT(wDataSize<=SOCKET_PACKAGE);
	if (wDataSize>SOCKET_PACKAGE) return false;

	//��������
	IPC_SocketPackage SocketPackage;
	memset(&SocketPackage,0,sizeof(SocketPackage));
	SocketPackage.Command=Command;
	if (wDataSize>0)
	{
		ASSERT(pBuffer!=NULL);
		CopyMemory(SocketPackage.cbBuffer,pBuffer,wDataSize);
	}

	//��������
	WORD wSendSize=sizeof(SocketPackage.Command)+wDataSize;
	SendProcessData(IPC_MAIN_SOCKET,IPC_SUB_SOCKET_RECV,&SocketPackage,wSendSize);

	return true;
}

//�û�����
bool CRoomViewItem::OnSocketSubUserCome(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_COME);
	ASSERT(wDataSize>=sizeof(tagUserInfoHead));
	if (wDataSize<sizeof(tagUserInfoHead)) return false;

	//��ȡ������Ϣ
	tagUserData UserData;
	memset(&UserData,0,sizeof(UserData));
	tagUserInfoHead * pUserInfoHead=(tagUserInfoHead *)pBuffer;
	UserData.wFaceID=pUserInfoHead->wFaceID;
	UserData.wTableID=pUserInfoHead->wTableID;
	UserData.wChairID=pUserInfoHead->wChairID;
	UserData.wNetDelay=pUserInfoHead->wNetDelay;
	UserData.cbGender=pUserInfoHead->cbGender;
	UserData.cbMember=pUserInfoHead->cbMember;
	UserData.cbUserStatus=pUserInfoHead->cbUserStatus;
	UserData.dwUserID=pUserInfoHead->dwUserID;
	UserData.dwGroupID=pUserInfoHead->dwGroupID;
	UserData.dwUserRight=pUserInfoHead->dwUserRight;
	UserData.dwMasterRight=pUserInfoHead->dwMasterRight;
	UserData.lGold=pUserInfoHead->UserScoreInfo.lGold;
	UserData.lScore=pUserInfoHead->UserScoreInfo.lScore;
	UserData.lWinCount=pUserInfoHead->UserScoreInfo.lWinCount;
	UserData.lLostCount=pUserInfoHead->UserScoreInfo.lLostCount;
	UserData.lDrawCount=pUserInfoHead->UserScoreInfo.lDrawCount;
	UserData.lFleeCount=pUserInfoHead->UserScoreInfo.lFleeCount;
	UserData.lExperience=pUserInfoHead->UserScoreInfo.lExperience;

	//��ȡ��չ��Ϣ
	void * pDataBuffer=NULL;
	tagDataDescribe DataDescribe;
	CRecvPacketHelper RecvPacket(pUserInfoHead+1,wDataSize-sizeof(tagUserInfoHead));
	while (true)
	{
		pDataBuffer=RecvPacket.GetData(DataDescribe);
		if (DataDescribe.wDataDescribe==DTP_NULL) break;
		switch (DataDescribe.wDataDescribe)
		{
		case DTP_USER_ACCOUNTS:		//�û��ʻ�
			{
				ASSERT(pDataBuffer!=NULL);
				ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szName));
				if (DataDescribe.wDataSize<=sizeof(UserData.szName))
				{
					CopyMemory(&UserData.szName,pDataBuffer,DataDescribe.wDataSize);
					UserData.szName[CountArray(UserData.szName)-1]=0;
				}
				break;
			}
		case DTP_USER_GROUP_NAME:	//�û�����
			{
				ASSERT(pDataBuffer!=NULL);
				ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szGroupName));
				if (DataDescribe.wDataSize<=sizeof(UserData.szGroupName))
				{
					CopyMemory(&UserData.szGroupName,pDataBuffer,DataDescribe.wDataSize);
					UserData.szGroupName[CountArray(UserData.szGroupName)-1]=0;
				}
				break;
			}
		}
	}

	//�����û�
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(UserData.dwUserID);
	if (pIUserItem==NULL) 
	{
		const tagCompanionItem * pCompanionItem=NULL;
		pCompanionItem=g_GlobalUnits.m_CompanionManager->SearchCompanionItem(UserData.dwUserID);
		if (pCompanionItem!=NULL) UserData.cbCompanion=pCompanionItem->Companion;
		pIUserItem=m_ClientUserManager.ActiveUserItem(UserData);
	}
	else OnUserItemUpdate(pIUserItem);

	//�����û���Ϣ
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem!=NULL)
	{
		//�ж��Լ�
		if (m_pMeUserItem==NULL) m_pMeUserItem=pIUserItem;

		//���ý���
		BYTE cbUserStatus=UserData.cbUserStatus;
		if ((cbUserStatus>=US_SIT)&&(cbUserStatus!=US_LOOKON))
			m_TableFrame.SetUserInfo(UserData.wTableID,UserData.wChairID,pIUserItem);

		//��ʾ��Ϣ
		if (m_ServiceStatus==ServiceStatus_Serviceing)
		{
			TCHAR szMessage[256]=TEXT("");
			if (UserData.cbCompanion==enCompanion_Friend)
			{
				_snprintf(szMessage,sizeof(szMessage),TEXT("��ĺ��ѡ�%s��������"),UserData.szName);
				m_MessageProxyHelper->InsertSystemString(szMessage,0);
			}
			else
			{
				_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] ������"),UserData.szName);
				m_MessageProxyHelper->InsertGeneralString(szMessage,0,0,true);
			}
		}
	}

	//���±���
	UpdateTitleText();

	//��������
	DWORD dwOnLineCount=m_ClientUserManager.GetOnLineCount();
	g_GlobalUnits.m_ServerListManager.UpdateGameServerOnLine(m_pListServer,dwOnLineCount);
	SetAllocTableType();
	return true;
}

//�û�״̬
bool CRoomViewItem::OnSocketSubStatus(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_STATUS);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserStatus));
	if (wDataSize<sizeof(CMD_GR_UserStatus)) return false;

	//��������
	CMD_GR_UserStatus * pUserStatus=(CMD_GR_UserStatus *)pBuffer;
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(pUserStatus->dwUserID);
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem==NULL) return true;

	//�������
	tagUserData * pUserData=pIUserItem->GetUserData();
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
	WORD wNowTableID=pUserStatus->wTableID,wLastTableID=pUserData->wTableID;
	WORD wNowChairID=pUserStatus->wChairID,wLastChairID=pUserData->wChairID;
	BYTE cbNowStatus=pUserStatus->cbUserStatus,cbLastStatus=pUserData->cbUserStatus;

	//�����״̬
	if ((wLastTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		ASSERT(wLastChairID!=INVALID_CHAIR);
		IUserItem * pITableUserItem=m_TableFrame.GetUserInfo(wLastTableID,wLastChairID);
		if (pITableUserItem==pIUserItem) m_TableFrame.SetUserInfo(wLastTableID,wLastChairID,NULL);
	}

	//�û��뿪
	if (cbNowStatus==US_NULL)
	{
		//֪ͨ��Ϸ
		if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wLastTableID))
		{
			IPC_UserStatus UserStatus;
			memset(&UserStatus,0,sizeof(UserStatus));
			UserStatus.dwUserID=pUserData->dwUserID;
			UserStatus.wNetDelay=pUserData->wNetDelay;
			UserStatus.cbUserStatus=pUserData->cbUserStatus;
			SendProcessData(IPC_MAIN_USER,IPC_SUB_USER_STATUS,&UserStatus,sizeof(UserStatus));
		}

		//ɾ���û�
		m_ClientUserManager.DeleteUserItem(pIUserItem);

		//���±���
		UpdateTitleText();

		//��������
		DWORD dwOnLineCount=m_ClientUserManager.GetOnLineCount();
		g_GlobalUnits.m_ServerListManager.UpdateGameServerOnLine(m_pListServer,dwOnLineCount);

		return true;
	}

	//����״̬
	tagUserStatus UserStatus;
	UserStatus.wTableID=wNowTableID;
	UserStatus.wChairID=wNowChairID;
	UserStatus.cbUserStatus=cbNowStatus;
	UserStatus.wNetDelay=pUserStatus->wNetDelay;
	m_ClientUserManager.UpdateUserItemStatus(pIUserItem,&UserStatus);

	//������״̬
	if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
	{
		//��������
		if (cbNowStatus!=US_LOOKON)
		{
			ASSERT(wNowChairID!=INVALID_CHAIR);
			m_TableFrame.SetUserInfo(wNowTableID,wNowChairID,pIUserItem);
		}

		//�����û�
		if ((m_pMeUserItem!=pIUserItem)&&(pMeUserData->wTableID==wNowTableID))
		{
			CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
			SendTableUser(pIUserItem,&SendCopyData);
		}
	}

	//���½���
	if ((wNowTableID!=INVALID_TABLE)&&(cbNowStatus!=US_LOOKON)
		&&(wNowTableID==wLastTableID)&&(wNowChairID==wLastChairID))
	{
		ASSERT(wNowChairID!=INVALID_CHAIR);
		m_TableFrame.UpdateTableView(wNowTableID,false);
	}

	//�жϷ���
	bool bNotifyGame=false;
	if (pIUserItem==m_pMeUserItem) bNotifyGame=true;
	else if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wNowTableID)) bNotifyGame=true;
	else if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==wLastTableID)) bNotifyGame=true;

	//����״̬
	if (bNotifyGame==true)
	{
		IPC_UserStatus UserStatus;
		memset(&UserStatus,0,sizeof(UserStatus));
		UserStatus.dwUserID=pUserData->dwUserID;
		UserStatus.wNetDelay=pUserData->wNetDelay;
		UserStatus.cbUserStatus=pUserData->cbUserStatus;
		SendProcessData(IPC_MAIN_USER,IPC_SUB_USER_STATUS,&UserStatus,sizeof(UserStatus));
	}

	//�ж��Լ�
	if (pIUserItem==m_pMeUserItem)
	{
		//���ñ���
		if ((wNowTableID==m_wReqTableID)&&(wNowChairID==m_wReqChairID))
		{
			m_wReqTableID=INVALID_TABLE;
			m_wReqChairID=INVALID_CHAIR;
		}

		//������Ϸ
		if ((wNowTableID!=INVALID_TABLE)&&((wNowTableID!=wLastTableID)||(wNowChairID!=wLastChairID)))
		{
			int iResult=StartGameClient();
		}
	}

	return true;
}

//�û�����
bool CRoomViewItem::OnSocketSubScore(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_SCORE);
	ASSERT(wDataSize>=sizeof(CMD_GR_UserScore));
	if (wDataSize<sizeof(CMD_GR_UserScore)) return false;

	//��������
	CMD_GR_UserScore * pUserScore=(CMD_GR_UserScore *)pBuffer;
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(pUserScore->dwUserID);
	ASSERT(pIUserItem!=NULL);
	if (pIUserItem==NULL) return true;

	//���·���
	m_ClientUserManager.UpdateUserItemScore(pIUserItem,&pUserScore->UserScore);

	//������Ϸ
	tagUserData * pUserData=pIUserItem->GetUserData();
	tagUserData * pMeUserData=m_pMeUserItem->GetUserData();
	if ((pMeUserData->wTableID!=INVALID_TABLE)&&(pMeUserData->wTableID==pUserData->wTableID))
	{
		IPC_UserScore UserScore;
		memset(&UserScore,0,sizeof(UserScore));
		UserScore.dwUserID=pUserScore->dwUserID;
		UserScore.UserScore=pUserScore->UserScore;
		SendProcessData(IPC_MAIN_USER,IPC_SUB_USER_SCORE,&UserScore,sizeof(UserScore));
	}

	return true;
}

//����ʧ��
bool CRoomViewItem::OnSocketSubSitFailed(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_SIT_FAILED);

	//��Ϣ����
	CMD_GR_SitFailed * pSitFailed=(CMD_GR_SitFailed *)pBuffer;
	IUserItem * pISendUserItem=m_TableFrame.GetUserInfo(m_wReqTableID,m_wReqChairID);
	if (pISendUserItem==m_pMeUserItem) m_TableFrame.SetUserInfo(m_wReqTableID,m_wReqChairID,NULL);

	//���ñ���
	m_wReqTableID=INVALID_TABLE;
	m_wReqChairID=INVALID_CHAIR;

	
	if(strncmp(szLessMoney,pSitFailed->szFailedDescribe,9)==0)
	{//��Ϸ�Ҳ���
		
		int nResult=ShowMessageBox(pSitFailed->szFailedDescribe,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
		if (nResult==IDYES)
		{
			//�򿪳�ֵ��վ
			g_GlobalUnits.GoWeb("/usercenter/bank.asp?action=cz",true);
		}
	}
	else
	{//��ʾ��Ϣ
		
		ShowMessageBox(pSitFailed->szFailedDescribe,MB_ICONINFORMATION);
	}

	return true;
}

//�û�����
bool CRoomViewItem::OnSocketSubChat(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_CHAT);

	//Ч�����
	CMD_GR_UserChat * pUserChat=(CMD_GR_UserChat *)pBuffer;
	ASSERT(wDataSize>=(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)));
	ASSERT(wDataSize==(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength));
	if (wDataSize<(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage))) return false;
	if (wDataSize!=(sizeof(CMD_GR_UserChat)-sizeof(pUserChat->szChatMessage)+pUserChat->wChatLength)) return false;

	//Ѱ���û�
	IUserItem * pISendUserItem=m_ClientUserManager.SearchUserByID(pUserChat->dwSendUserID);
	if (pISendUserItem==NULL) return true;
	tagUserData * pSendUserData=pISendUserItem->GetUserData();

	//��Ϣ����
	if ((pISendUserItem!=m_pMeUserItem)&&(pSendUserData->cbCompanion==enCompanion_Detest)) return true;
	
	//��ʾ��Ϣ
	if (pUserChat->dwTargetUserID!=0L)
	{
		IUserItem * pIRecvUserItem=m_ClientUserManager.SearchUserByID(pUserChat->dwTargetUserID);
		if (pIRecvUserItem==NULL) return true;
		tagUserData * pRecvUserData=pIRecvUserItem->GetUserData();
		m_MessageProxyHelper->InsertUserChat(pSendUserData->szName,pRecvUserData->szName,pUserChat->szChatMessage,pUserChat->crFontColor,MS_NORMAL);
	}
	else m_MessageProxyHelper->InsertUserChat(pSendUserData->szName,pUserChat->szChatMessage,pUserChat->crFontColor,MS_NORMAL);

	return true;
}

//�û�˽��
bool CRoomViewItem::OnSocketSubWisper(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_WISPER);

	//Ч�����
	CMD_GR_Wisper * pWisper=(CMD_GR_Wisper *)pBuffer;
	ASSERT(wDataSize>=(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)));
	ASSERT(wDataSize==(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)+pWisper->wChatLength));
	if (wDataSize<(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage))) return false;
	if (wDataSize!=(sizeof(CMD_GR_Wisper)-sizeof(pWisper->szChatMessage)+pWisper->wChatLength)) return false;

	//Ѱ���û�
	IUserItem * pISendUserItem=m_ClientUserManager.SearchUserByID(pWisper->dwSendUserID);
	IUserItem * pIRecvUserItem=m_ClientUserManager.SearchUserByID(pWisper->dwTargetUserID);
	if ((pISendUserItem==NULL)||(pIRecvUserItem==NULL)) return true;
	tagUserData * pUserDataSend=pISendUserItem->GetUserData();
	tagUserData * pUserDataRecv=pIRecvUserItem->GetUserData();

	//��ʾ��Ϣ
	CShortMessage * pShortMessageWnd=NULL;
	if (pWisper->dwSendUserID==m_pMeUserItem->GetUserID())
	{
		//�Լ����͵���Ϣ
		pShortMessageWnd=ActiveShortWnd(pWisper->dwTargetUserID,pIRecvUserItem,true);
		if (pShortMessageWnd!=NULL) pShortMessageWnd->OnRecvMessage(pUserDataSend->szName,pWisper->szChatMessage,pWisper->crFontColor,true);
	}
	else	//������Ϸ�߷�����Ϣ
	{
		pShortMessageWnd=ActiveShortWnd(pWisper->dwSendUserID,pISendUserItem,true);
		if (pShortMessageWnd!=NULL)	pShortMessageWnd->OnRecvMessage(pUserDataSend->szName,pWisper->szChatMessage,pWisper->crFontColor,false);
	}

	return true;
}

//�û�����
bool CRoomViewItem::OnSocketSubUserInvite(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	//Ч�����
	ASSERT(Command.wMainCmdID==MDM_GR_USER);
	ASSERT(Command.wSubCmdID==SUB_GR_USER_INVITE);

	//Ч�����
	ASSERT(wDataSize==sizeof(CMD_GR_UserInvite));
	if (wDataSize!=sizeof(CMD_GR_UserInvite)) return false;

	//��Ϣ����
	CMD_GR_UserInvite * pUserInvite=(CMD_GR_UserInvite *)pBuffer;
	ASSERT(pUserInvite->wTableID<m_TableFrame.GetTableCount());
	if (m_TableFrame.QueryPlayFlag(pUserInvite->wTableID)==true) return true;

	//Ѱ���û�
	IUserItem * pIUserItem=m_ClientUserManager.SearchUserByID(pUserInvite->dwUserID);
	if (pIUserItem==NULL) return true;
	tagUserData * pUserData=pIUserItem->GetUserData();
	if (pUserData->wTableID==INVALID_TABLE) return true;

	//�û�����
	if (pUserData->cbCompanion==enCompanion_Detest) return true;
	m_TableFrame.EnsureVisibleTable(pUserInvite->wTableID);

	//��ʾ��Ϣ
	TCHAR szMessage[256]=TEXT("");
	_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] ���������� [ %ld ] ��Ϸ��������Ϸ���Ƿ�ͬ�⣿"),pUserData->szName,pUserInvite->wTableID+1);
	if (ShowMessageBox(szMessage,MB_ICONINFORMATION|MB_YESNO)==IDYES)
	{
		WORD wChairID=INVALID_CHAIR;
		WORD wNullCount=m_TableFrame.GetNullChairCount(pUserInvite->wTableID,wChairID);
		if (wNullCount==0) 
		{
			ShowMessageBox(TEXT("����Ϸ���Ѿ�û�п�λ���ˣ�"),MB_ICONINFORMATION);
			return true;
		}
		PerformSitDownAction(pUserInvite->wTableID,wChairID);
	}

	return true;
}

//IPC �ں�����
bool CRoomViewItem::OnIPCKernel(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MIAN_IPC_KERNEL);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_IPC_CLIENT_CONNECT:	//������Ϣ
		{
			//�ж�����
			if (::IsChild(m_pShareMemory->hWndGameFrame,hWndSend)) return false;

			//���ñ���
			ASSERT(m_hWndChannel==NULL);
			m_hWndChannel=hWndSend;

			//������Ϣ
			CIPCSendCopyData SendCopyData(m_hWndChannel,m_hWnd);
			IPCSendGameInfo(&SendCopyData);
			IPCSendTableUsers(&SendCopyData);
			SendCopyData.SendData(IPC_MAIN_CONCTROL,IPC_SUB_START_FINISH);

			return true;
		}
	case IPC_SUB_IPC_CLIENT_CLOSE:		//�ر���Ϣ
		{
			//�ж�����
			if (hWndSend!=m_hWndChannel) return false;

			//������Ϣ
			tagUserData * pUserData=m_pMeUserItem->GetUserData();
			if (pUserData->wTableID!=WORD(INVALID_TABLE))
			{
				if (pUserData->cbUserStatus==US_PLAY) SendLeftGamePacket();
				SendStandUpPacket();
			}

			//���ñ���
			m_hWndChannel=NULL;
			m_pShareMemory->hWndGameFrame=NULL;
			CloseHandle(g_GameProcessInfo.hThread);
			CloseHandle(g_GameProcessInfo.hProcess);
			memset(&g_GameProcessInfo,0,sizeof(g_GameProcessInfo));

			return true;
		}
	}

	return false;
}

//IPC ��������
bool CRoomViewItem::OnIPCSocket(const IPC_Head * pHead, const void * pIPCBuffer, WORD wDataSize, HWND hWndSend)
{
	ASSERT(pHead->wMainCmdID==IPC_MAIN_SOCKET);
	switch (pHead->wSubCmdID)
	{
	case IPC_SUB_SOCKET_SEND:	//������Ϣ
		{
			//Ч������
			ASSERT(wDataSize>=sizeof(CMD_Command));
			if (wDataSize<sizeof(CMD_Command)) 
			{
				return false;
			}

			//��������
			IPC_SocketPackage * pSocketPackage=(IPC_SocketPackage *)pIPCBuffer;
			CMD_Command *pCommand= &pSocketPackage->Command;
			WORD wSendSize=wDataSize-sizeof(CMD_Command);
			if (wSendSize==0) 
			{
				m_ClientSocket->SendData(pCommand->wMainCmdID,
									pCommand->wSubCmdID);
			}
			else 
			{
				m_ClientSocket->SendData(pCommand->wMainCmdID,
									pCommand->wSubCmdID,
									pSocketPackage->cbBuffer,
									wSendSize);
			}

			return true;
		}
	}

	return false;
}

//�ŵ����ݴ���
bool __cdecl CRoomViewItem::OnChannelMessage(const IPC_Head * pHead, 
											 const void * pIPCBuffer, 
											 WORD wDataSize, 
											 HWND hWndSend)
{
	switch (pHead->wMainCmdID)
	{
	//�ں���Ϣ
	case IPC_MIAN_IPC_KERNEL:		
		{
			return OnIPCKernel(pHead,pIPCBuffer,wDataSize,hWndSend);
		}

	//�����¼�
	case IPC_MAIN_SOCKET:			
		{
			return OnIPCSocket(pHead,pIPCBuffer,wDataSize,hWndSend);
		}
	}
	return false;
}

//����������
void __cdecl CRoomViewItem::OnLButtonHitTable(WORD wTableID, WORD wChairID, bool bMirror)
{
	//�ж�״̬
	if (m_ServiceStatus==ServiceStatus_NetShutDown)
	{
		if ((wTableID!=INVALID_TABLE)&&(wChairID!=INVALID_CHAIR))
		{
			LPCTSTR szMessage=TEXT("����Ϸ�������������Ѿ��жϣ��Ƿ��˳���ǰ��Ϸ���䣿");
			int iCode=ShowMessageBox(szMessage,MB_ICONINFORMATION|MB_YESNO);
			if (iCode==IDYES) g_pControlBar->CloseRoomViewItem(this);
		}
		return;
	}

	//��������
	if (m_ServiceStatus!=ServiceStatus_Serviceing) return;
	if ((wTableID==m_wReqTableID)&&(wChairID==m_wReqChairID)) return;
	if ((wTableID==INVALID_TABLE)||(wChairID==INVALID_CHAIR)) return;

	//��Ϣ����
	IUserItem * pTableUserItem=m_TableFrame.GetUserInfo(wTableID,wChairID);
	if (pTableUserItem!=NULL)
	{
		//�Թۻ�������
		if (pTableUserItem==m_pMeUserItem)
		{
			if (m_pMeUserItem->GetUserData()->cbUserStatus>=US_PLAY) 
			{
				return;
			}
			if ((m_wReqTableID!=INVALID_TABLE)||(m_wReqChairID!=INVALID_CHAIR)) 
			{
				return;
			}
			m_wFindTableID=INVALID_TABLE;
			SendStandUpPacket();
		}
		else 
		{
			tagUserData * pUserData=m_pMeUserItem->GetUserData();
			if((pUserData->wTableID==wTableID)
				&& (pUserData->wChairID==wChairID)) 
			{
				return;
			}
			PerformLookonAction(wTableID,wChairID);
		}
	}
	else 
	{
		PerformSitDownAction(wTableID, wChairID);
	}

	//�رվ��񴰿�
	//if (bMirror) 
	//{
	//	if (m_pDlgInvite->GetSafeHwnd()) m_pDlgInvite->DestroyWindow();
	//	if (m_pDlgFindTable->GetSafeHwnd()) m_pDlgFindTable->DestroyWindow();
	//}

	return;
}

//����Ҽ�����
void __cdecl CRoomViewItem::OnRButtonHitTable(WORD wTableID, 
											  WORD wChairID, 
											  bool bMirror)
{
	//��ȡ����
	ITableView * pITableView=m_TableFrame.GetTableArrayPtr(wTableID);
	if (pITableView==NULL) 
	{
		return;
	}

	//��ȡ�û�
	IUserItem * pIUserItem=pITableView->GetUserInfo(wChairID);
	if (pIUserItem==NULL) 
	{
		return;
	}

	//��ʾ�˵�
	CPoint Point;
	GetCursorPos(&Point);
	ShowUserInfoMenu(pIUserItem,Point);

	return;
}

//���˫��
void __cdecl CRoomViewItem::OnDoubleHitTable(WORD wTableID, bool bMirror)
{
}

//�û�����;����
void __cdecl CRoomViewItem::OnUserItemAcitve(IUserItem * pIUserItem)
{
	//m_UserListView.InsertUserItem(pIUserItem);
	tagUserData *User=pIUserItem->GetUserData();
	if(!User)return;

	//�������ѵ�������ɫ
	COLORREF TitleColor=0x00ffff;
	if(strcmp(g_GlobalUnits.GetGolbalUserData().szAccounts,User->szName)==0)
	{
		TitleColor = 0xddffff;
	}

	//���밴ť
	int nBtn=m_UserListView.AddButton(AfxGetInstanceHandle(),USERLIST_BTN,IMG_LISTCTRL_CMD_ID,
					User->szName,
					84 - strlen(User->szName)*4,7,TitleColor,0);
	if(!nBtn)return;

	tagImageListButton *Btn=m_UserListView.GetButtonInfo(nBtn);
	if(Btn)
	{
		UpdateUserMoney(nBtn,Btn->img,User);
	}
	return ;
}

void CRoomViewItem::UpdateUserMoney(int nBtn,CSkinImage &Img,tagUserData *User)
{
	CSkinImage tmp;
	tmp.SetLoadInfo(USERLIST_BTN,AfxGetInstanceHandle());
	CImageHandle ImgHandle(&Img);
	CImageHandle ImgHandlet(&tmp);

	HDC hdc=Img.GetDC();
	//����Money
	tmp.Draw(hdc,CRect(0,0,195,35),CRect(0,0,195,35));

	//д�µ�Money
	char Money[32];
	sprintf(Money,"��Ϸ��:%d",User->lScore);
	//m_UserListView.DrawText(nBtn,98 - strlen(Money)*4+1,25+1,Money,0xA04F19);
	//m_UserListView.DrawText(nBtn,98 - strlen(Money)*4,25,Money,0x00ffff);
	//m_UserListView.DrawText(nBtn,98 - strlen(Money)*4+1,25+1,Money,0xffffff);
	m_UserListView.DrawText(nBtn,98 - strlen(Money)*4,25,Money,0x000000);

	//��ͷ��
	g_GlobalUnits.m_UserFaceRes->DrawSmallFace(CDC::FromHandle(hdc),3,3,User->wFaceID);
	Img.ReleaseDC();
	m_UserListView.UpdateButton();
}

//�û�����
void __cdecl CRoomViewItem::OnUserItemUpdate(IUserItem * pIUserItem)
{
	tagUserData *User=pIUserItem->GetUserData();
	if(!User)return;
	int nBtn = m_UserListView.GetButtonByTitle(User->szName);
	if(!nBtn)return;

	tagImageListButton *Btn=m_UserListView.GetButtonInfo(nBtn);
	if(Btn)
	{
		UpdateUserMoney(nBtn,Btn->img,User);
	}


	if (m_pFindUserDlg!=NULL) 
	{
		m_pFindUserDlg->UpdateUserItem(pIUserItem);
	}
	return ;
}

//�û�ɾ��
void __cdecl CRoomViewItem::OnUserItemDelete(IUserItem * pIUserItem)
{
	//��ȡ�û�
	ASSERT(pIUserItem!=NULL);
	DWORD dwUserID=pIUserItem->GetUserID();

	//�������
	if (m_dwChatUserID==dwUserID)
	{
		SetChatObject(NULL);
		TCHAR szMessage[256]=TEXT("");
		_snprintf(szMessage,sizeof(szMessage),TEXT("[ %s ] �뿪�ˣ������������Ϊ������"),pIUserItem->GetUserName());
		m_MessageProxyHelper->InsertSystemString(szMessage,0);
	}

	//�������
	int nChatObjectCount=m_ChatObject.GetCount();
	for (int i=1;i<nChatObjectCount;i++)
	{
		if (m_ChatObject.GetItemData(i)==dwUserID)
		{
			if (m_ChatObject.GetCurSel()==i) 
			{
				m_dwChatUserID=0;
				m_szChatName[0]=0;
				m_ChatObject.SetCurSel(0);
			}
			m_ChatObject.DeleteString(i);
			break;
		}
	}

	//������ͼ
	//m_UserListView.DeleteUserItem(pIUserItem);
	int nItem=m_UserListView.GetButtonByTitle(pIUserItem->GetUserName());
	if(nItem)m_UserListView.DeleteButton(nItem);
	m_UserListView.UpdateButton();

	if (m_pFindUserDlg!=NULL) m_pFindUserDlg->DeleteUserItem(pIUserItem);

	return;
}

//������Ϣ����
CShortMessage * CRoomViewItem::ActiveShortWnd(long int dwUserID, IUserItem * pUserItem, bool bCreate)
{
	//��������
	INT_PTR iCloseIndex=-1,iHideIndex=-1;
	
	//Ѱ�����ϴ���
	for (INT_PTR i=0;i<m_ShortMessage.GetCount();i++)
	{
		CShortMessage * pShortMessageWnd=(CShortMessage *)m_ShortMessage.GetAt(i);
		ASSERT(pShortMessageWnd!=NULL);
		if (dwUserID==pShortMessageWnd->m_dwTargetUserID)
		{
			if (pShortMessageWnd->GetSafeHwnd()==NULL)
			{
				AfxSetResourceHandle(GetModuleHandle(NULL));
				pShortMessageWnd->Create(IDD_SHORT_MESSAGE,this);
			}
			pShortMessageWnd->ShowWindow(SW_SHOW);
			return pShortMessageWnd;
		}
		if (bCreate==true)
		{
			if ((iCloseIndex==-1)
				&&  (pShortMessageWnd->GetSafeHwnd()==NULL)) 
			{
				iCloseIndex=i;
			}
			if ((iHideIndex==-1)
				&& (pShortMessageWnd->GetSafeHwnd()!=NULL)
				&& (pShortMessageWnd->IsWindowVisible()==FALSE)) 
			{
				iHideIndex=i;
			}
		}
	}

	//ʹ�ùرյĴ���
	if ((bCreate==true)&&(iCloseIndex>=0))
	{
		CShortMessage *pShortMessageWnd = (CShortMessage *)m_ShortMessage.GetAt(iCloseIndex);
		ASSERT(pShortMessageWnd!=NULL);
		if (pShortMessageWnd->GetSafeHwnd()==NULL)
		{
			AfxSetResourceHandle(GetModuleHandle(NULL));
			pShortMessageWnd->Create(IDD_SHORT_MESSAGE,this);
		}
		pShortMessageWnd->SetTalkInfo(pUserItem,m_pListServer->GetItemInfo()->szServerName);
		pShortMessageWnd->ShowWindow(SW_SHOW);
		return pShortMessageWnd;
	}

	//ʹ�����ش���
	if ((bCreate==true)&&(iHideIndex>=0))
	{
		CShortMessage * pShortMessageWnd=(CShortMessage *)m_ShortMessage.GetAt(iHideIndex);
		ASSERT(pShortMessageWnd!=NULL);
		pShortMessageWnd->SetTalkInfo(pUserItem,m_pListServer->GetItemInfo()->szServerName);
		pShortMessageWnd->ShowWindow(SW_SHOW);
		return pShortMessageWnd;
	}

	//�����´���
	if ((bCreate==true)&&(m_ShortMessage.GetCount()<10))
	{
		try
		{
			CShortMessage * pShortMessageWnd=new CShortMessage(this);
			AfxSetResourceHandle(GetModuleHandle(NULL));
			pShortMessageWnd->SetTalkInfo(pUserItem,m_pListServer->GetItemInfo()->szServerName);
			pShortMessageWnd->Create(IDD_SHORT_MESSAGE,this);
			pShortMessageWnd->ShowWindow(SW_SHOW);
			m_ShortMessage.Add(pShortMessageWnd);
			
			return pShortMessageWnd;
		}
		catch (...) 
		{ 
			return NULL; 
		}
	}

	return NULL;
}


//�����û�����SHOW����

CShow * CRoomViewItem::ActiveShowWnd(long int dwUserID, IUserItem * pUserItem, bool bCreate)
{
	//��������
	INT_PTR iCloseIndex=-1,iHideIndex=-1;
	
	//Ѱ�����ϴ���
	for (INT_PTR i=0;i<m_ShowMessage.GetCount();i++)
	{
		CShow * pShowWnd=(CShow *)m_ShowMessage.GetAt(i);
		ASSERT(pShowWnd!=NULL);
		if (dwUserID==pShowWnd->m_dwTargetUserID)
		{
			if (pShowWnd->GetSafeHwnd()==NULL)
			{
				AfxSetResourceHandle(GetModuleHandle(NULL));
				pShowWnd->Create(IDD_SHOW,this);
			}
			pShowWnd->ShowWindow(SW_SHOW);
			return pShowWnd;
		}
		if (bCreate==true)
		{
			if ((iCloseIndex==-1)
				&&  (pShowWnd->GetSafeHwnd()==NULL)) 
			{
				iCloseIndex=i;
			}
			if ((iHideIndex==-1)
				&& (pShowWnd->GetSafeHwnd()!=NULL)
				&& (pShowWnd->IsWindowVisible()==FALSE)) 
			{
				iHideIndex=i;
			}
		}
	}

	//ʹ�ùرյĴ���
	if ((bCreate==true)&&(iCloseIndex>=0))
	{
		CShow *pShowWnd = (CShow *)m_ShowMessage.GetAt(iCloseIndex);
		ASSERT(pShowWnd!=NULL);
		if (pShowWnd->GetSafeHwnd()==NULL)
		{
			AfxSetResourceHandle(GetModuleHandle(NULL));
			pShowWnd->Create(IDD_SHOW,this);
		}
		pShowWnd->ShowWindow(SW_SHOW);
		return pShowWnd;
	}

	//ʹ�����ش���
	if ((bCreate==true)&&(iHideIndex>=0))
	{
		CShow * pShowWnd=(CShow *)m_ShowMessage.GetAt(iHideIndex);
		ASSERT(pShowWnd!=NULL);
	
		pShowWnd->ShowWindow(SW_SHOW);
		return pShowWnd;
	}

	//�����´���
	if ((bCreate==true)&&(m_ShowMessage.GetCount()<10))
	{
		try
		{
			CShow * pShowWnd=new CShow(this);
			AfxSetResourceHandle(GetModuleHandle(NULL));
			
			pShowWnd->Create(IDD_SHOW,this);
			pShowWnd->ShowWindow(SW_SHOW);
			m_ShortMessage.Add(pShowWnd);
			
			return pShowWnd;
		}
		catch (...) 
		{ 
			return NULL;
		}
	}

	return NULL;
}




//�������
bool CRoomViewItem::SetChatObject(IUserItem * pIUserItem)
{
	if (pIUserItem!=NULL)
	{
		//���ñ���
		tagUserData * pUserData=pIUserItem->GetUserData();
		m_dwChatUserID=pUserData->dwUserID;
		lstrcpyn(m_szChatName,pUserData->szName,CountArray(m_szChatName));

		//Ѱ�����
		int nItemCount=m_ChatObject.GetCount();
		for (int i=0;i<nItemCount;i++)
		{
			if (m_ChatObject.GetItemData(i)==m_dwChatUserID)
			{
				m_ChatObject.SetCurSel(i);
				return true;
			}
		}
		
		//�������
		int iItem=m_ChatObject.AddString(m_szChatName);
		m_ChatObject.SetItemData(iItem,m_dwChatUserID);
		m_ChatObject.SetCurSel(iItem);
	}
	else
	{
		//���ñ���
		m_dwChatUserID=0L;
		m_szChatName[0]=0;

		//���ý���
		m_ChatObject.SetCurSel(0);
	}

	return true;
}

afx_msg void CRoomViewItem::OnBnUserList_Clicked()
{
ULONG nButton;
tagImageListButton *BtnInfo;

	nButton=m_UserListView.GetLastButton();
	if(nButton)
	{
		//BtnInfo=m_UserListView.GetButtonInfo(nButton);
		//if(!BtnInfo)return;
		//tagGlobalUserData UserData=g_GlobalUnits.GetGolbalUserData();
		//CString ShowUrl;
		//ShowUrl.Format(UrlQQShow,BtnInfo->Title);
		//g_GlobalUnits.AddSessionUrl(ShowUrl,ShowUrl);
		//m_pHtmlBrower->Navigate(ShowUrl);
		//return;
		BtnInfo=m_UserListView.GetButtonInfo(nButton);
		if(!BtnInfo)return;
		//��ȡ�û�
		IUserItem * pIUserItem=m_ClientUserManager.SearchUserByAccounts(BtnInfo->Title);
		if (pIUserItem==NULL) 
		{
			return;
		}

		//��ʾ�˵�
		CPoint Point;
		GetCursorPos(&Point);
		ShowUserInfoMenu(pIUserItem,Point);
		return;
	}
	nButton=m_UserListView.GetLastButtonRT();
	if(nButton)
	{
		BtnInfo=m_UserListView.GetButtonInfo(nButton);
		if(!BtnInfo)return;
		//��ȡ�û�
		IUserItem * pIUserItem=m_ClientUserManager.SearchUserByAccounts(BtnInfo->Title);
		if (pIUserItem==NULL) 
		{
			return;
		}

		//��ʾ�˵�
		CPoint Point;
		GetCursorPos(&Point);
		ShowUserInfoMenu(pIUserItem,Point);
		return;
	}
}

//////////////////////////////////////////////////////////////////////////


