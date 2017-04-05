//***********************************************
//File		: PlazaViewItem.cpp 
//Time		: 
//Author	: Anson
//Comment	: ��Ϸ�㳡��
//***********************************************


#include "Stdafx.h"
#include "../../�����ļ�/GlobalDef.h"
#include "GamePlaza.h"
#include "GlobalUnits.h"
#include "RoomViewItem.h"
#include "PlazaViewItem.h"
#include "DlgControlBar.h"

#include "BCMenu.h"
#include ".\plazaviewitem.h"

#define GAME_LIST_X     11
#define GAME_LIST_Y     11


#define		LIST_TOP			119				//�б�ͷ��
#define		LIST_LEFT			24				//�б����
#define		LIST_RIGHT			9				//�б��ҿ�
#define		LIST_BOTTOM			4				//�б�׸�

#define		IDC_WEB_BEFORE		101
#define		IDC_WEB_BRUSH		102
#define		IDC_WEB_HOME		103
#define		IDC_WEB_NEXT		104
#define		IDC_WEB_STOP		105
#define		IDC_GAMEBUTTONS		8888

#define		IDC_BT_BUTTON_GAME1	7777			//���ܰ�ť
#define		IDC_BT_BUTTON_GAME2	7778			//���ܰ�ť
#define		IDC_BT_BUTTON_GAME3	7779			//���ܰ�ť

BEGIN_MESSAGE_MAP(CPlazaViewItem, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_GAMEBUTTONS,	OnBnClicked_GameButtons)
	ON_COMMAND(IDM_LOGON_PLAZA,		OnCommandLogon)
	ON_COMMAND(IDM_CONNECT_SERVER,	OnCommandConnect)
	ON_COMMAND(IDM_CANCEL_CONNECT,	OnCommandCancelConnect)
END_MESSAGE_MAP()


UINT GetGameIco(const char *pszGameKind)
{
	//if(!strcmpi(pszGameKind,"������"))
	//	return IDB_ICO_DDZ;
	//else if(!strcmpi(pszGameKind,"թ��"))
	//	return IDB_ICO_ZJH;
	//else if(!strcmpi(pszGameKind,"��ɳ�齫"))
	//	return IDB_ICO_MJ;
	//else if(!strcmpi(pszGameKind,"���"))
	//	return IDB_ICO_SH;
	//else if(!strcmpi(pszGameKind,"�����"))
	//	return IDB_ICO_SDH;
	//else if(!strcmpi(pszGameKind,"�н���Ϸ"))
	//	return IDB_ICO_YJYX;
	//else
	//{
		return IDB_ICO_DDZ;
	//}
}


CPlazaViewItem::CPlazaViewItem() : CDialog(IDD_GAME_PLAZA)
{
	//���ñ���
	m_bRectify		= false;
	m_bInitDialog	= false;
	m_bLogonPlaza	= false;
	m_pHtmlBrower1	= NULL;
	//�������б�
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_ImageBGMain.SetLoadInfo(IDB_BG_MAIN,hInstance);
	m_ImageBGMain2.SetLoadInfo(IDB_BG_MAIN2,hInstance);

	m_ImageML.SetLoadInfo(IDB_FRAME_ML,hInstance);
	m_ImageMR.SetLoadInfo(IDB_FRAME_MR,hInstance);

	m_GameListT2.SetLoadInfo(GAMELIST_T3,hInstance);     //����
	m_GameListT.LoadResource(FindResource(NULL,"GAMELIST_T",RT_BITMAP),CXIMAGE_FORMAT_BMP);
	m_GameListL.LoadResource(FindResource(NULL,"GAMELIST_L",RT_BITMAP),CXIMAGE_FORMAT_BMP);
	m_GameListR.LoadResource(FindResource(NULL,"GAMELIST_R",RT_BITMAP),CXIMAGE_FORMAT_BMP);
	m_GameListM.LoadResource(FindResource(NULL,"GAMELIST_M",RT_BITMAP),CXIMAGE_FORMAT_BMP);
	m_GameListB2.SetLoadInfo(GAMELIST_B3,hInstance);     //����
	m_GameListB.LoadResource(FindResource(NULL,"GAMELIST_B",RT_BITMAP),CXIMAGE_FORMAT_BMP);
	m_GameListScroll.LoadResource(FindResource(NULL,"GAMELIST_SCROLL",RT_BITMAP),CXIMAGE_FORMAT_BMP);

	m_StatusL.SetLoadInfo(IDB_STATUS_L,hInstance);
	m_StatusM.SetLoadInfo(IDB_STATUS_M,hInstance);
	return ;
}

CPlazaViewItem::~CPlazaViewItem()
{
	ClearGameButtons();
}

//�ؼ���
void CPlazaViewItem::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERVER_LIST, m_ServerItemView);
}

//��ʼ������
BOOL CPlazaViewItem::OnInitDialog()
{
	__super::OnInitDialog();
//	m_ImageBGMain.LoadFromResource(IDB_BG_MAIN,hInstance);
	
	//���ýӿ�
	g_pControlBar->SetPlazaViewItem(this);

	if(m_RoomList.Create(NULL, WS_CHILD|SS_LEFT|SS_NOTIFY,CRect(0,0,0,0), this))
	{
		HINSTANCE hInstance=AfxGetInstanceHandle();
		m_RoomList.m_xTop.SetLoadInfo(ROOMLIST_T,hInstance);
		m_RoomList.m_xLeft.SetLoadInfo(ROOMLIST_L1,hInstance);
		m_RoomList.m_xRight.SetLoadInfo(ROOMLIST_R1,hInstance);
		m_RoomList.m_xBottom.SetLoadInfo(ROOMLIST_B,hInstance);
		m_RoomList.m_xScrollT.SetLoadInfo(ROOMLIST_S_T,hInstance);
		m_RoomList.m_xScrollM.SetLoadInfo(ROOMLIST_S_M,hInstance);
		m_RoomList.m_xScrollB.SetLoadInfo(ROOMLIST_S_B,hInstance);
		m_RoomList.m_xThumb.SetLoadInfo(ROOMLIST_S_THUMB,hInstance);

		m_RoomList.SetHeight(191);
		//char *p = "թ�𻨷���1";
		//for(int i=100001;i<=100021;i++)
		//	m_RoomList.AddButton((HINSTANCE)FindResource(NULL,"ROOMLIST_BTN",RT_BITMAP),IMG_LISTCTRL_CMD_ID,(DWORD)p,20,5,0xffffff,i);
		m_RoomList.UpdateButton();
			SetWindowRgnFromRes(m_RoomList.m_hWnd,AfxGetInstanceHandle(),TEXT("RGN_ROOMLIST"),TEXT("BIN"));
	}
////////////////////////////////////////////////////////////////////////////

	if(m_ServerList.Create(NULL, WS_CHILD|SS_LEFT|SS_NOTIFY,CRect(0,0,0,0), this))
	{
		HINSTANCE hInstance=AfxGetInstanceHandle();
		m_ServerList.m_xTop.SetLoadInfo(GAMELIST_T2,hInstance);
		m_ServerList.m_xLeft.SetLoadInfo(ROOMLIST_L,hInstance);
		m_ServerList.m_xRight.SetLoadInfo(ROOMLIST_R,hInstance);
		m_ServerList.m_xBottom.SetLoadInfo(GAMELIST_B2,hInstance);
		m_ServerList.m_xScrollT.SetLoadInfo(ROOMLIST_S_T,hInstance);
		m_ServerList.m_xScrollM.SetLoadInfo(ROOMLIST_S_M,hInstance);
		m_ServerList.m_xScrollB.SetLoadInfo(ROOMLIST_S_B,hInstance);
		m_ServerList.m_xThumb.SetLoadInfo(ROOMLIST_S_THUMB,hInstance);

		m_ServerList.UpdateButton();
			//BUG,ȡ���б�ͷ����ɫ����,����λͼ,����ס��OnPaint()����Ⱦ����
			//SetWindowRgnFromRes(m_ServerList.m_hWnd,AfxGetInstanceHandle(),TEXT("RGN_SERVERLIST"),TEXT("BIN"));
	}

	m_btGame1.Create(TEXT("������Ϸ"),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_GAME1);
	m_btGame1.SetButtonImage(TABCARD,AfxGetInstanceHandle(),false);
	m_btGame2.Create(TEXT("������Ϸ"),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_GAME2);
	m_btGame2.SetButtonImage(TABCARD,AfxGetInstanceHandle(),false);
	m_btGame3.Create(TEXT("��������"),WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_BT_BUTTON_GAME3);
	m_btGame3.SetButtonImage(TABCARD,AfxGetInstanceHandle(),false);
	
	m_btGame1.ShowWindow(SW_HIDE);
	m_btGame2.ShowWindow(SW_HIDE);
	m_btGame3.ShowWindow(SW_HIDE);
	//m_btGame3.ShowWindow(SW_HIDE);
	

	//m_ServerList.ShowWindow(SW_SHOW);

///////////////////////////////////////////////////////////////////////


	//�����ؼ�
	m_pHtmlBrower1 = new CHtmlBrower;
	m_pHtmlBrower1->Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(320,511,751,535),this,20,NULL);
	m_pHtmlBrower1->EnableBrowser(true);
	m_pHtmlBrower1->Navigate("http://"ServerDomain"/Client/StatusNotice.asp");

	//���ÿؼ�
	m_ServerItemView.InitServerItemView(this);
	m_ServerItemView.ShowWindow(SW_HIDE);
	g_GlobalUnits.m_ServerListManager.InitServerListManager(&m_ServerItemView);

	::EnableWindow(GetParent()->m_hWnd,false);
	//��½�㳡
	SendLogonMessage();

	//���ñ���
	m_bInitDialog=true;

	theApp.m_MainPlaza = this->GetSafeHwnd();

	return TRUE;
}

//�ӿڲ�ѯ
void * __cdecl CPlazaViewItem::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IViewItem,Guid,dwQueryVer);
	QUERYINTERFACE(IPlazaViewItem,Guid,dwQueryVer);
	QUERYINTERFACE(IClientSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IViewItem,Guid,dwQueryVer);
	return NULL;
}


//�������
void __cdecl CPlazaViewItem::OnTreeLeftClick(CListItem *pListItem, HTREEITEM hTreeItem, CTreeCtrl * pTreeCtrl)
{
	//Ч�����
	if (pListItem==NULL) 
	{
		return;
	}

	//��Ϣ����
	switch (pListItem->GetItemGenre())
	{
	case ItemGenre_Inside:
		{
			//��������
			CListInside * pListInside=(CListInside *)pListItem;
			tagGameInside * pGameInside=pListInside->GetItemInfo();

			//WebBrowse(TEXT("http://"ServerDomain),false);

			return;
		}
	case ItemGenre_Kind:		//��Ϸ����
		{
			//��������
			CListKind * pListKind=(CListKind *)pListItem;
			tagGameKind * pGameKind=pListKind->GetItemInfo();

			//���ӹ���
			//TCHAR szRuleUrl[256]=TEXT("");
			//_snprintf(szRuleUrl,sizeof(szRuleUrl),TEXT("http://"ServerDomain"/cn/game/GameRule.asp?KindID=%ld"),pGameKind->wKindID);
			//WebBrowse(szRuleUrl,true);

			return;
		}
	}

	return;
}

//�Ҽ�����
void __cdecl CPlazaViewItem::OnTreeRightClick(CListItem *pListItem, 
											  HTREEITEM hTreeItem, 
											  CTreeCtrl *pTreeCtrl)
{
	return;
}

//���˫��
void __cdecl CPlazaViewItem::OnTreeLeftDBClick(CListItem *pListItem, 
											   HTREEITEM hTreeItem, 
											   CTreeCtrl *pTreeCtrl)
{
	//Ч�����
	if(pListItem==NULL) 
	{
		return ;
	}

	//��Ϣ����
	switch (pListItem->GetItemGenre())
	{
	//��Ϸ����
	case ItemGenre_Kind:
		{
			CListKind *pListKind	= (CListKind *)pListItem;
			tagGameKind *pGameKind	= pListKind->GetItemInfo();

			//��װ�ж�
			if (pListKind->m_bInstall==false)
			{
				//TCHAR szBuffer[512]=TEXT("");
				//_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%s����û�а�װ�������Ƿ����أ�"),pGameKind->szKindName);
				//int nResult = ShowMessageBox(szBuffer,
				//						MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
				//if(nResult == IDYES)	
				{
					g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,
													pGameKind->wKindID,
													true);
				}
			}

			return;
		}

	//��������
	case ItemGenre_Process:	
		{
			CListProcess *pListProcess	= (CListProcess *)pListItem;
			tagGameProcess *pGameProcess= pListProcess->GetItemInfo();

			//����������
			CString strCommonLine;
			tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
			strCommonLine.Format(TEXT("%s /UserToken:%ld#%s#%s /KindID:%ld /WndPlaza:%ld"),
							pGameProcess->szProcessName,
							UserData.dwUserID,
							UserData.szAccounts,
							UserData.szPassWord,
							pGameProcess->wKindID,
							m_hWnd);

			//������Ϸ�ͻ���
			STARTUPINFO			StartInfo;
			
			memset(&StartInfo,0,sizeof(StartInfo));
			memset(&g_GameProcessInfo,0,sizeof(g_GameProcessInfo));

			StartInfo.cb=sizeof(StartInfo);
			StartInfo.wShowWindow=SW_SHOWMAXIMIZED;
			BOOL bSuccess=CreateProcess(NULL,strCommonLine.GetBuffer(),NULL,NULL,FALSE,CREATE_DEFAULT_ERROR_MODE,NULL,NULL,&StartInfo,&g_GameProcessInfo);
			strCommonLine.ReleaseBuffer();
			if(bSuccess == FALSE)
			{
				//����ѯ��
				//TCHAR szBuffer[512]=TEXT("");
				//_snprintf(szBuffer,sizeof(szBuffer),TEXT("��%s����û�а�װ�������Ƿ����أ�"),pGameProcess->szKindName);
				//int nResult=ShowMessageBox(szBuffer,MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
				//if (nResult==IDYES)
					g_GlobalAttemper.DownLoadClient(pGameProcess->szKindName,pGameProcess->wKindID,true);
			}
			else
			{
				CloseHandle(g_GameProcessInfo.hThread);
				CloseHandle(g_GameProcessInfo.hProcess);
			}
			return;
		}

	//��Ϸ����
	case ItemGenre_Server:	
		{
			CListServer * pListServer=(CListServer *)pListItem;
			//bluker:���������������ֻҪ�������OK��
			g_pControlBar->CreateRoomViewItem(pListServer);
			return;
		}
	}

	return;
}

//�Ҽ�˫��
void __cdecl CPlazaViewItem::OnTreeRightDBClick(CListItem *pListItem, 
												HTREEITEM hTreeItem, 
												CTreeCtrl *pTreeCtrl)
{
	return;
}

//ѡ��ı�
void __cdecl CPlazaViewItem::OnTreeSelectChanged(CListItem *pListItem, 
												 HTREEITEM hTreeItem, 
												 CTreeCtrl *pTreeCtrl)
{
	return;
}

//����չ��
void __cdecl CPlazaViewItem::OnTreeItemexpanded(CListItem *pListItem, 
												HTREEITEM hTreeItem, 
												CTreeCtrl * pTreeCtrl)
{
	return;
}

//����������Ϣ
bool __cdecl CPlazaViewItem::OnSocketConnect(int iErrorCode, 
											LPCTSTR pszErrorDesc, 
											IClientSocket *pIClientSocke)
{
	//������
	if (iErrorCode!=0)
	{
		g_GlobalAttemper.DestroyStatusWnd(this);
		ShowMessageBox(pszErrorDesc,MB_ICONINFORMATION);
		SendLogonMessage();
		return true;
	}

	//���͵�¼��
	if (m_bLogonPlaza==false)
	{
		m_DlgLogon.SendLogonPacket(pIClientSocke);
		g_GlobalAttemper.ShowStatusMessage(TEXT("������֤�û���¼��Ϣ..."),this);
	}

	return true;
}

//�����ȡ��Ϣ
bool __cdecl CPlazaViewItem::OnSocketRead(CMD_Command Command, 
										  void *pBuffer, 
										  WORD wDataSize, 
										  IClientSocket *pIClientSocke)
{
	switch (Command.wMainCmdID)
	{
	//��½��Ϣ
	case MDM_GP_LOGON:				
		{
			return OnSocketMainLogon(Command,
								pBuffer,
								wDataSize,
								pIClientSocke);
		}

	//�б���Ϣ
	case MDM_GP_SERVER_LIST:		
		{
			return OnSocketMainServerList(Command,
								pBuffer,
								wDataSize,
								pIClientSocke);
		}

	//ϵͳ��Ϣ
	case MDM_GP_SYSTEM:				
		{
			return OnSocketMainSystem(Command,
								pBuffer,
								wDataSize,
								pIClientSocke);
		}
	}
	return true;
}

//����ر���Ϣ
bool __cdecl CPlazaViewItem::OnSocketClose(IClientSocket *pIClientSocke, 
										   bool bCloseByServer)
{
	if (m_bLogonPlaza==false)
	{
		g_GlobalAttemper.DestroyStatusWnd(this);
		if(pIClientSocke->GetRecvPacketCount()==0)
		{
			ShowMessageBox(TEXT("��������æ����ѡ��������������½��"),MB_ICONINFORMATION);
		}
		SendLogonMessage();
	}
	return true;
}

//��½��Ϣ
bool CPlazaViewItem::OnSocketMainLogon(CMD_Command Command, 
									   void *pBuffer, 
									   WORD wDataSize, 
									   IClientSocket *pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GP_LOGON);
	switch (Command.wSubCmdID)
	{
	//��½�ɹ�
	case SUB_GP_LOGON_SUCCESS:		
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GP_LogonSuccess));
			if (wDataSize<sizeof(CMD_GP_LogonSuccess)) 
			{
				return false;
			}

			//������Ϣ
			tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
			CMD_GP_LogonSuccess * pLogonSuccess=(CMD_GP_LogonSuccess *)pBuffer;
			UserData.wFaceID=pLogonSuccess->wFaceID;
			UserData.cbGender=pLogonSuccess->cbGender;
			UserData.cbMember=pLogonSuccess->cbMember;
			UserData.dwUserID=pLogonSuccess->dwUserID;
			UserData.dwGroupID=pLogonSuccess->dwGroupID;
			UserData.dwExperience=pLogonSuccess->dwExperience;
			UserData.dwUserRight=pLogonSuccess->dwUserRight;
			UserData.dwMasterRight=pLogonSuccess->dwMasterRight;

			//��չ��Ϣ
			void * pDataBuffer=NULL;
			tagDataDescribe DataDescribe;
			CRecvPacketHelper RecvPacket(pLogonSuccess+1,wDataSize-sizeof(CMD_GP_LogonSuccess));
			while (true)
			{
				pDataBuffer=RecvPacket.GetData(DataDescribe);
				if (DataDescribe.wDataDescribe==DTP_NULL) break;
				switch (DataDescribe.wDataDescribe)
				{
				case DTP_USER_ACCOUNTS:		//�û��ʻ�
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szAccounts));
						if (DataDescribe.wDataSize<=sizeof(UserData.szAccounts))
						{
							CopyMemory(UserData.szAccounts,pDataBuffer,DataDescribe.wDataSize);
							UserData.szAccounts[CountArray(UserData.szAccounts)-1]=0;
						}
						break;
					}
				case DTP_USER_PASS:			//�û�����
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szPassWord));
						if (DataDescribe.wDataSize<=sizeof(UserData.szPassWord))
						{
							CopyMemory(UserData.szPassWord,pDataBuffer,DataDescribe.wDataSize);
							UserData.szPassWord[CountArray(UserData.szPassWord)-1]=0;
						}
						break;
					}
				case DTP_USER_GROUP_NAME:	//��������
					{
						ASSERT(pDataBuffer!=NULL);
						ASSERT(DataDescribe.wDataSize>0);
						ASSERT(DataDescribe.wDataSize<=sizeof(UserData.szGroupName));
						if (DataDescribe.wDataSize<=sizeof(UserData.szGroupName))
						{
							CopyMemory(UserData.szGroupName,pDataBuffer,DataDescribe.wDataSize);
							UserData.szGroupName[CountArray(UserData.szGroupName)-1]=0;
						}
						break;
					}
				case DTP_STATION_PAGE:		//��Ϸ��վ
					{
						ASSERT(pDataBuffer!=NULL);
						if (pDataBuffer!=NULL) 
						{
							g_GlobalUnits.SetStationPage((LPCTSTR)pDataBuffer);
							////m_pHtmlBrower->Navigate(g_GlobalUnits.GetStationPage());
						}
						break;
					}
				case DTP_SESSIONID:		//��Ϸ��վ
					{
						ASSERT(pDataBuffer!=NULL);
						if (pDataBuffer!=NULL) 
						{
							memcpy(UserData.szSessionId,pDataBuffer,sizeof(UserData.szSessionId));
						}
						break;
					}
				default: { ASSERT(FALSE); }
				}
			}

			//������ʾ
			g_GlobalAttemper.ShowStatusMessage(TEXT("���ڶ�ȡ�������б���Ϣ..."),this);

			return true;
		}

	//��½ʧ��
	case SUB_GP_LOGON_ERROR:		
		{
			//Ч�����
			CMD_GP_LogonError *pLogonError = (CMD_GP_LogonError *)pBuffer;
			ASSERT(wDataSize>=(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe)));
			if (wDataSize<(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe))) return false;

			//�ر�����
			g_GlobalAttemper.DestroyStatusWnd(this);
			pIClientSocke->CloseSocket(false);

			//��ʾ��Ϣ
			WORD wDescribeSize=wDataSize-(sizeof(CMD_GP_LogonError)-sizeof(pLogonError->szErrorDescribe));
			if (wDescribeSize>0)
			{
				pLogonError->szErrorDescribe[wDescribeSize-1]=0;
				ShowMessageBox(pLogonError->szErrorDescribe,MB_ICONINFORMATION);
			}

			//���͵�½
			SendLogonMessage();

			return true;
		}

	//��½���
	case SUB_GP_LOGON_FINISH:
		{
			//�ر���ʾ
			g_GlobalAttemper.DestroyStatusWnd(this);

			//չ������
			INT_PTR nIndex=0;
			CListType * pListType=NULL;
			do
			{
				pListType=g_GlobalUnits.m_ServerListManager.EnumTypeItem(nIndex++);
				if (pListType==NULL) break;
				//bluker:����:����,�˿���,�齫��,������
				//tagGameType *gtype=pListType->GetItemInfo();
				//MessageBox(gtype->szTypeName);
				g_GlobalUnits.m_ServerListManager.ExpandListItem(pListType);
			} while (true);

			//չ���б�
			nIndex=0;
			CListInside * pListInside=NULL;
			do
			{
				pListInside=g_GlobalUnits.m_ServerListManager.EnumInsideItem(nIndex++);
				if (pListInside==NULL) break;
				//bluker:����:"��ң��������Ϸ���� [ 0 ��]"
				//tagGameInside *gInside=pListInside->GetItemInfo();
				//MessageBox(gInside->szDisplayName);
				g_GlobalUnits.m_ServerListManager.ExpandListItem(pListInside);
			} while (true);
			//��¼��Ϣ
			m_bLogonPlaza=true;
			::EnableWindow(GetParent()->m_hWnd,true);
			::LockWindowUpdate(GetParent()->m_hWnd);

			//bluker:ö�ٿ��õ���Ϸ
			nIndex=0;
			CListKind * pListKind=NULL;
			//ClearGameButtons();�ڸ���ע���������

			////////////////////////////////////////////////////
			do
			{
				pListKind=g_GlobalUnits.m_ServerListManager.EnumKindItem(nIndex++);
				if (!pListKind) break;
				tagGameKind *pGameKind=pListKind->GetItemInfo();
				if(!pGameKind)break;

				if(g_GlobalUnits.m_ServerListManager.IsExistKindServerRunning(pGameKind->wKindID))
				{
					//bluker:��̬����Ϸ��ť(�Ѱ�װ����Ϸ)
					tagGameButton *tagButton=new tagGameButton();
					char GameTitle[32];
					sprintf(GameTitle,"[%d]",pGameKind->dwOnLineCount);
					//if(!tagButton->Button.Create(/*GameTitle*/"�� ��",WS_CHILD|WS_VISIBLE,CRect(-999,0,0,0),this,IDC_GAMEBUTTONS))
					//{
					//	SafeDelete(tagButton);
					//	break;
					//}
					//tagButton->Button.SetTitlePos(158,11);

					//if(!tagButton->Button.LoadRgnImage(AfxGetInstanceHandle(),GetGameIco(pGameKind->szKindName),RGB(255,0,255),0))
					///////if(!tagButton->Button.SetButtonImage(GetGameIco(pGameKind->szKindName),AfxGetInstanceHandle(),false))
					//{
					//	SafeDelete(tagButton);
					//	break;
					//}
					//else
					{
						tagButton->wKindID=pGameKind->wKindID;
						lstrcpyn(tagButton->szKindName,pGameKind->szKindName,CountArray(tagButton->szKindName));


						int nBtn = m_ServerList.AddButton(AfxGetInstanceHandle(),GetGameIco(pGameKind->szKindName),IDC_GAMEBUTTONS,"����",//tagButton->szKindName,
				123,10,0x000000,tagButton->wKindID);

						tagImageListButton *Btn=m_ServerList.GetButtonInfo(nBtn);
						if(Btn)
						{
							CSkinImage tmp;
							tmp.SetLoadInfo(GetGameIco(pGameKind->szKindName),AfxGetInstanceHandle());
							CImageHandle ImgHandle(&Btn->img);
							CImageHandle ImgHandlet(&tmp);

							HDC hdc=Btn->img.GetDC();
							//����Money
							tmp.Draw(hdc,CRect(37,0,164,30),CRect(37,0,164,30));

							//д�µ�Money
							char Money[32];
							sprintf(Money,"%s",pGameKind->szKindName);
							m_ServerList.DrawText(nBtn,77 - strlen(Money)*4+1,10+1,Money,0xffffff);
							m_ServerList.DrawText(nBtn,77 - strlen(Money)*4,10,Money,0x000000);

							//��LOGO
//							g_GlobalUnits.m_UserFaceRes->DrawSmallFace(CDC::FromHandle(hdc),5,6,User->wFaceID);
							Btn->img.ReleaseDC();
							m_ServerList.UpdateButton();
						}

						//CString strServer;
						//strServer.Format("%s    ����",pGameKind->szKindName);
						//m_ServerList.AddButton(AfxGetInstanceHandle(),GetGameIco(pGameKind->szKindName),IDC_GAMEBUTTONS,strServer,//tagButton->szKindName,
				//80,10,0x000000,tagButton->wKindID);
						
						//tagButton = m_ServerList.m_xButtons.back()->UserData
						m_GameButtons.push_back(tagButton);
						//m_GameButtons.push_back(tagButton);

						//��Ϸ��ʾ����
						//if(m_GameButtons.size()==999)break;
					}
				}
			} while (true);

////////////////////////////////////////////////////
			CRect rc;
			GetClientRect(&rc);
			RectifyControl(rc.Width(),rc.Height());
			//m_ServerItemView.ShowWindow(SW_NORMAL);
			::LockWindowUpdate(NULL);
			::ShowWindow(GetParent()->m_hWnd,SW_NORMAL);
			::SetActiveWindow(GetParent()->m_hWnd); // hoho,��һ����ǹؼ�Ŷ����
			::SetForegroundWindow(GetParent()->m_hWnd);

			m_DlgLogon.OnLogonSuccess();
			//m_pHtmlBrower->EnableBrowser(true);


			m_ServerList.UpdateButton();
			m_ServerList.ShowWindow(SW_SHOW);

			g_GlobalOption.PlayMedia("Welcome.mp3");
			return true;
		}
	}

	return true;
}

//��Ϸ�б���Ϣ
bool CPlazaViewItem::OnSocketMainServerList(CMD_Command Command, 
											void * pBuffer, 
											WORD wDataSize, 
											IClientSocket * pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GP_SERVER_LIST);
	
	switch (Command.wSubCmdID)
	{
	//������Ϣ
	case SUB_GP_LIST_TYPE:			
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameType)==0);
			if (wDataSize%sizeof(tagGameType)!=0) return false;

			//������Ϣ
			tagGameType * pGameType=(tagGameType *)pBuffer;
			WORD wItemCount=wDataSize/sizeof(tagGameType);
			g_GlobalUnits.m_ServerListManager.InsertTypeItem(pGameType,wItemCount);

			return true;
		}

	//������Ϣ
	case SUB_GP_LIST_KIND:			
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameKind)==0);
			if (wDataSize%sizeof(tagGameKind)!=0) return false;

			//������Ϣ
			tagGameKind * pGameKind=(tagGameKind *)pBuffer;
			WORD wItemCount=wDataSize/sizeof(tagGameKind);
			g_GlobalUnits.m_ServerListManager.InsertKindItem(pGameKind,wItemCount);

			return true;
		}

	//������Ϣ
	case SUB_GP_LIST_PROCESS:		
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameProcess)==0);
			if (wDataSize%sizeof(tagGameProcess)!=0) return false;

			//������Ϣ
			tagGameProcess * pGameProcess=(tagGameProcess *)pBuffer;
			WORD wItemCount=wDataSize/sizeof(tagGameProcess);
			g_GlobalUnits.m_ServerListManager.InsertProcessItem(pGameProcess,wItemCount);

			return true;
		}

	//վ����Ϣ
	case SUB_GP_LIST_STATION:		
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameStation)==0);
			if (wDataSize%sizeof(tagGameStation)!=0) return false;

			//������Ϣ
			tagGameStation * pGameStation=(tagGameStation *)pBuffer;
			WORD wItemCount=wDataSize/sizeof(tagGameStation);
			g_GlobalUnits.m_ServerListManager.InsertStationItem(pGameStation,wItemCount);

			return true;
		}

	//����������
	case SUB_GP_LIST_SERVER:		
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(tagGameServer)==0);
			if (wDataSize%sizeof(tagGameServer)!=0) return false;

			//������Ϣ
			tagGameServer * pGameServer=(tagGameServer *)pBuffer;
			WORD wItemCount=wDataSize/sizeof(tagGameServer);
			g_GlobalUnits.m_ServerListManager.InsertServerItem(pGameServer,wItemCount);

			return true;
		}

	//�б������
	case SUB_GP_LIST_FINISH:		
		{
			//��������
			INT_PTR nIndex=0;
			DWORD dwAllOnLineCount=0L;
			CListKind * pListKind=NULL;
			do
			{
				pListKind=g_GlobalUnits.m_ServerListManager.EnumKindItem(nIndex++);
				if (pListKind==NULL) break;
				//bluker:����:ÿ����Ϸ���������,id����Ϣ
				//tagGameKind *gKind=pListKind->GetItemInfo();

				//------------------------------------------------(+)���±���
				for(UINT i=0;i<m_GameButtons.size();i++)
				{
					if(pListKind->GetItemInfo()->wKindID==m_GameButtons[i]->wKindID)
					{
						char GameTitle[32];
						sprintf(GameTitle,"[%d]",pListKind->GetItemInfo()->dwOnLineCount);
						m_GameButtons[i]->Button.SetWindowText(/*GameTitle*/"�� ��");
						break;
					}
				}
				//------------------------------------------------(-)���±���

				dwAllOnLineCount+=pListKind->GetItemInfo()->dwOnLineCount;
			} while (true);
			g_GlobalUnits.m_ServerListManager.UpdateGameOnLineCount(dwAllOnLineCount);

			return true;
		}

	//�б�����
	case SUB_GP_LIST_CONFIG:		
		{
			//Ч�����
			ASSERT(wDataSize%sizeof(CMD_GP_ListConfig)==0);
			if (wDataSize%sizeof(CMD_GP_ListConfig)!=0) return false;

			//������Ϣ
			CMD_GP_ListConfig * pListConfig=(CMD_GP_ListConfig *)pBuffer;
			m_ServerItemView.ShowOnLineCount(pListConfig->bShowOnLineCount?true:false);

			return true;
		}
	}

	return true;
}

//ϵͳ��Ϣ
bool CPlazaViewItem::OnSocketMainSystem(CMD_Command Command, 
										void * pBuffer, 
										WORD wDataSize, 
										IClientSocket * pIClientSocke)
{
	ASSERT(Command.wMainCmdID==MDM_GP_SYSTEM);
	
	switch (Command.wSubCmdID)
	{
	//�汾��Ϣ
	case SUB_GP_VERSION:			
		{
			//Ч�����
			ASSERT(wDataSize>=sizeof(CMD_GP_Version));
			if (wDataSize<sizeof(CMD_GP_Version)) return false;

			//��Ϣ����
			CMD_GP_Version * pVersion=(CMD_GP_Version *)pBuffer;
			if (pVersion->bAllowConnect)
			{
				TCHAR szMessage[]=TEXT("��Ϸ�����汾�Ѿ����������ڵİ汾�����Լ���ʹ�ã������Ƿ����������°汾��");
				int iResult=::MessageBox(m_hWnd,szMessage,TEXT("��Ϸ�㳡"),MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON1);
				if (iResult==IDYES)
				{
					g_GlobalAttemper.DestroyStatusWnd(this);
					m_ClientSocket->CloseSocket(false);
					tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
					memset(&GlobalUserData,0,sizeof(GlobalUserData));
					g_GlobalAttemper.DownLoadClient(TEXT("��Ϸ�㳡"),0,true);
				}
			}
			else
			{
				g_GlobalAttemper.DestroyStatusWnd(this);
				m_ClientSocket->CloseSocket(false);
				//TCHAR szMessage[]=TEXT("��Ϸ�����汾�Ѿ����������ڵİ汾�����Լ���ʹ�ã������Ƿ����������°汾��");
				//int iResult=::MessageBox(m_hWnd,szMessage,TEXT("��Ϸ�㳡"),MB_ICONSTOP|MB_YESNO|MB_DEFBUTTON1);
				//if(iResult != IDYES)
				//{
				//	tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
				//	memset(&GlobalUserData,0,sizeof(GlobalUserData));
				//	AfxGetMainWnd()->PostMessage(WM_CLOSE);
				//}
				//else 
				{
					g_GlobalAttemper.DownLoadClient(TEXT("��Ϸ�㳡"),0,true);
				}
			}

			return true;
		}
	}
	return true;
}

//��¼��Ϣ
bool __cdecl CPlazaViewItem::SendLogonMessage()
{
	m_bLogonPlaza=false;
	PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
	return true;
}

//������Ϣ
bool __cdecl CPlazaViewItem::SendConnectMessage()
{
	PostMessage(WM_COMMAND,IDM_CONNECT_SERVER,0);
	return true;
}

/*
//��ʾ��ҳ
void CPlazaViewItem::WebBrowse(LPCTSTR lpszUrl, bool bForceBrowse)
{
	if (m_pHtmlBrower->GetSafeHwnd())
	{
		m_pHtmlBrower->Navigate(lpszUrl);
		if (bForceBrowse==true) 
		{
			m_pHtmlBrower->EnableBrowser(true);
		}
	}
	return;
}
*/

//��ʾ��Ϣ
int CPlazaViewItem::ShowMessageBox(LPCTSTR pszMessage, UINT nType)
{
	int nResult = MessageBox(pszMessage,TEXT("��Ϸ����"),nType);
	return nResult;
}

//λ����Ϣ
void CPlazaViewItem::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	//�����ؼ�
	RectifyControl(cx,cy);
	//���µ���ʽ��������
	return;
}

//��ʾ��Ϣ
void CPlazaViewItem::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//���ñ���
	if (bShow) 
	{
		UpdateTitleText();
	}

	return;
}

//�滭��Ϣ
void CPlazaViewItem::OnPaint()
{
	CPaintDC dc(this);
	//�滭����

	DrawListFrame(&dc);

	CRect rcClient;
	GetClientRect(&rcClient);
	CImageHandle StatusLHandle(&m_StatusL);
	CImageHandle StatusMHandle(&m_StatusM);
	//m_StatusL.BitBlt(dc,275,rcClient.bottom-83);
	//m_StatusM.StretchBlt(dc,
	//		CRect(573,rcClient.bottom-83,rcClient.right,rcClient.bottom),
	//		CRect(0,0,m_StatusM.GetWidth(),m_StatusM.GetHeight())
	//		);
	m_StatusL.BitBlt(dc,267,rcClient.bottom-78);
	m_StatusM.BitBlt(dc,565,rcClient.bottom-78);
	//m_StatusM.StretchBlt(dc,
	//		CRect(573,rcClient.bottom-78,rcClient.right,rcClient.bottom),
	//		CRect(0,0,m_StatusM.GetWidth(),m_StatusM.GetHeight())
	//	);

	return;
}

//�滭����
BOOL CPlazaViewItem::OnEraseBkgnd(CDC * pDC)
{
	//Invalidate(FALSE);
	//UpdateWindow();
	return TRUE;
}

//��¼�㳡
void CPlazaViewItem::OnCommandLogon()
{
	//������½��
	if (m_DlgLogon.m_hWnd==NULL) 
	{
		m_DlgLogon.Create(IDD_LOGON,this);
	}
/*
HRSRC   hrsrc=FindResource(0,(LPCSTR)IDD_LOGON,RT_DIALOG);   
HGLOBAL   hglobal=LoadResource(0,hrsrc);   
CDialog   dialog;   
dialog.InitModalIndirect(hglobal,this);
dialog.DoModal();
*/

	//��ʾ��½��
	m_DlgLogon.ShowWindow(SW_SHOW);
	m_DlgLogon.SetActiveWindow();
	m_DlgLogon.SetForegroundWindow();

	return;
}

//���ӷ�����
void CPlazaViewItem::OnCommandConnect()
{
	//�������
	if (m_ClientSocket.GetInterface()==NULL)
	{
		try
		{
			IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
			if (m_ClientSocket.CreateInstance()==false) 
			{
				throw TEXT("�����������ʧ��");
			}
			if (m_ClientSocket->SetSocketSink(pIUnknownEx)==false) 
			{
				throw TEXT("��������ص��ӿ�����ʧ��");
			}
		}
		catch (...)
		{
			ShowMessageBox(TEXT("�����������ʧ�ܣ�������������Ϸ������"),MB_ICONSTOP);
			PostMessage(WM_COMMAND,IDM_LOGON_PLAZA,0);
			return;
		}
	}

	//��ַ����
	CRegKey RegServer;
	LPCTSTR pszServerIP="219.148.111.182"; //m_DlgLogon.GetLogonServer();
	TCHAR szRegServer[256]=TEXT(""),szServerAddr[64]=TEXT("");
	_snprintf(szRegServer,sizeof(szRegServer),TEXT("%s\\%s"),REG_LOGON_SERVER,pszServerIP);
	
	if (RegServer.Open(HKEY_CURRENT_USER,szRegServer,KEY_READ)==ERROR_SUCCESS)
	{
		TCHAR szReadData[1024]=TEXT("");
		DWORD dwReadData=0L,dwDataType=0L,dwDataSize=sizeof(szReadData);
		LONG lErrorCode=RegServer.QueryValue(TEXT("ServerAddr"),&dwDataType,szReadData,&dwDataSize);
		if (lErrorCode==ERROR_SUCCESS) 
		{
			CXOREncrypt::CrevasseData(szReadData,szServerAddr,sizeof(szServerAddr));
			pszServerIP=szServerAddr;
		}
	}

	//���ӷ�����
	try
	{
		//���ô���
		m_ClientSocket->SetProxyServer(m_DlgLogon.m_ProxyInfo);

		//���ӷ�����
		m_ClientSocket->CloseSocket(false);
		if (m_ClientSocket->Connect(pszServerIP,PORT_LOGON_SERVER)==false)
		{
			throw TEXT("���������Ӵ��󣬿��������ϵͳ��û�гɹ����������磡");
		}
	}
	catch (LPCTSTR pszError)
	{
		ShowMessageBox(pszError,MB_ICONINFORMATION);
		SendLogonMessage();
		return;
	}

	//��ʾ��ʾ��
	CString strMessage=TEXT("�������ӷ����������Ժ�...");
	g_GlobalAttemper.ShowStatusMessage(strMessage,this);
	
	return;
}

//ȡ������
void CPlazaViewItem::OnCommandCancelConnect()
{
	g_GlobalAttemper.DestroyStatusWnd(this);
	m_ClientSocket->CloseSocket(false);
	SendLogonMessage();
	return;
}

//���±���
void CPlazaViewItem::UpdateTitleText()
{
	#ifndef ADMIN_PLAZA
		AfxGetMainWnd()->SetWindowText(szProductName);
	#else
		AfxGetMainWnd()->SetWindowText(TEXT(szProductName"Admin"));
	#endif
	return;
}


//�滭�б�
void CPlazaViewItem::DrawListFrame(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//������Դ
	HDC hDC=pDC->m_hDC;

	CImageHandle ImageImageBGMainHandle(&m_ImageBGMain);
	CImageHandle ImageImageBGMainHandle2(&m_ImageBGMain2);
	CImageHandle ImageMLHandle(&m_ImageML);
	CImageHandle ImageMRHandle(&m_ImageMR);
	//�滭
	//*
	if(rcClient.Width()<850){
		if(theApp.m_intTheme == 1)
		{
			m_ImageBGMain.BitBlt(hDC,0,0);
		}
		else
		{
			m_ImageBGMain2.BitBlt(hDC,0,0);
		}
	}
	else
	{
		SetStretchBltMode(hDC,STRETCH_HALFTONE);
		m_ImageBGMain.StretchBlt(hDC,CRect(rcClient.left+0,rcClient.top,rcClient.right-10,rcClient.bottom),CRect(0,0,m_ImageBGMain.GetWidth(),m_ImageBGMain.GetHeight()));
	}

	tagGlobalUserData UserData=g_GlobalUnits.GetGolbalUserData();
	if (UserData.dwUserID!=0)
	{
		if(!m_ServerList.IsWindowVisible())
			m_ServerList.ShowWindow(SW_SHOW);
		//CDC BufferDC;
		//CBitmap BufferBmp;
		//BufferBmp.LoadBitmap(ROOMLIST_T);

		//pDC->TransparentBlt(100,200,GAME_LIST_X,GAME_LIST_Y,&BufferDC,0,0,GAME_LIST_X+10,GAME_LIST_Y+20,(0xff00ff));
		//RGBQUAD m_rgbTable;
		//COLORREF m_Color(RGB(255,0,255));
		//m_rgbTable.rgbBlue = GetBValue(m_Color);
		//m_rgbTable.rgbGreen = GetGValue(m_Color);
		//m_rgbTable.rgbRed = GetRValue(m_Color);
	
		//m_GameListT.Draw2(hDC,-999,-999);
		CImageHandle HandleGameListT(&m_GameListT2);
		m_GameListT2.AlphaDrawImage(pDC,GAME_LIST_X,GAME_LIST_Y,RGB(255,0,255));
		//int cx=m_GameListT.GetWidth()+GAME_LIST_X;
		//int cy=m_GameListT.GetHeight()+GAME_LIST_Y;
		//m_GameListT.Stretch(hDC,CRect(GAME_LIST_X,GAME_LIST_Y,cx,cy));
		//m_GameListT.SetTransIndex(0);
		//m_GameListT.SetTransColor(m_rgbTable);
		//m_GameListL.Draw2(hDC,GAME_LIST_X,GAME_LIST_Y+49);
		//m_GameListR.Draw2(hDC,GAME_LIST_X+252,GAME_LIST_Y+49);
		//m_GameListM.Draw2(hDC,GAME_LIST_X+6,GAME_LIST_Y+49);
		CRect cr;
		GetClientRect(cr);

		CImageHandle HandleGameListB(&m_GameListB2);
		m_GameListB2.AlphaDrawImage(pDC,GAME_LIST_X,cr.bottom-88,RGB(255,0,255));

		
		m_btGame1.ShowWindow(SW_SHOW);
		m_btGame2.ShowWindow(SW_SHOW);
		m_btGame3.ShowWindow(SW_SHOW);

		m_btGame2.EnableWindow(false);
		m_btGame3.EnableWindow(false);
		//m_GameListB.Draw(hDC,GAME_LIST_X,cr.bottom-88);
		//m_GameListB.SetTransColor(m_rgbTable);
		//m_GameListB.AlphaStrip();
	//TransparentBlt(
		//m_GameListScroll.Draw2(hDC,GAME_LIST_X+252-13,GAME_LIST_Y+49);
		////�滭��Ϸ�б��
		//m_GameListT.TransparentBlt(hDC,0,(0xff00ff),GAME_LIST_X,GAME_LIST_Y);
		//m_GameListL.TransparentBlt(hDC,0,(0xff00ff),GAME_LIST_X,GAME_LIST_Y+49);
		//m_GameListR.TransparentBlt(hDC,0,(0xff00ff),GAME_LIST_X+252,GAME_LIST_Y+49);
		//m_GameListM.TransparentBlt(hDC,40,(0xff00ff),GAME_LIST_X+6,GAME_LIST_Y+49);
		//m_GameListB.TransparentBlt(hDC,0,(0xff00ff),GAME_LIST_X,GAME_LIST_Y+352);
		//m_GameListScroll.TransparentBlt(hDC,0,(0xff00ff),GAME_LIST_X+252-17,GAME_LIST_Y+49);
	}


	/*char text[] =	"\\b0�������С������Ϸ�ң�\\par"
					"�ֿ�ͨ�������ֳ�ֵ��ʽ��\\par\\par"
					"��1.������ͨ���������̵깺�����⿨���г�ֵ��[\\a1��������\\a0](9.5��)\\par"
					"��2.�������ö��ţ��ƶ�����111��1234567����ͨ����111��7654321���ж��ų�ֵ��\\par"
					"��3.�������ù̶��绰������1601234567���г�ֵ��\\par";
	DWORD textAlignment = THA_LEFT | TVA_TOP;
	RECT margins = {2,2,2,2};
	pDC->SetBkMode(TRANSPARENT);
	g_TextRender.m_color=0x942525;//0x111197
	g_TextRender.SetFontFace("����",12);
	g_TextRender.EnhDrawText( pDC->m_hDC, text, strlen(text), &CRect(20,rcClient.bottom-109,250,rcClient.bottom-5), &margins, textAlignment );

*/

	/*m_ImageMsgBarT.AlphaDrawImage(CDC::FromHandle(hDC),
			8,rcClient.bottom-129,m_ImageMsgBarT.GetWidth(),m_ImageMsgBarT.GetHeight(),0,0,(COLORREF)0);
	m_ImageMsgBarB.AlphaDrawImage(CDC::FromHandle(hDC),
			8,rcClient.bottom-5,m_ImageMsgBarB.GetWidth(),m_ImageMsgBarB.GetHeight(),0,0,(COLORREF)0);
	m_ImageMsgBarL.BitBlt(hDC,8,rcClient.bottom-109);
	m_ImageMsgBarR.BitBlt(hDC,471,rcClient.bottom-109);*/



	//�滭���ҵ�����
	m_ImageML.StretchBlt(hDC,
			CRect(0,0,m_ImageML.GetWidth(),rcClient.bottom),
			CRect(0,0,m_ImageML.GetWidth(),m_ImageML.GetHeight())
			);
	m_ImageMR.StretchBlt(hDC,
		CRect(rcClient.right-m_ImageMR.GetWidth(),0,rcClient.right,rcClient.bottom),
		CRect(0,0,m_ImageMR.GetWidth(),m_ImageMR.GetHeight())
			);

	//bluker:����ʾ�û�����ͷ��
	
	//�滭��Ϣ
	//tagGlobalUserData UserData=g_GlobalUnits.GetGolbalUserData();
	UserData=g_GlobalUnits.GetGolbalUserData();

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
		pDC->TextOut(50,cr.bottom-78,szBuffer,lstrlen(szBuffer));

		//�û�����
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("���ţ�%s"),UserData.szGroupName);
		//_snprintf(szBuffer,CountArray(szBuffer),TEXT("���ţ�δ����"),UserData.szGroupName);
		pDC->TextOut(50,cr.bottom-58,szBuffer,lstrlen(szBuffer));

		LPCTSTR pszMember[]={TEXT("��ͨ��Ա"),TEXT("�м���Ա"),TEXT("�߼���Ա")};
		BYTE cbMember=UserData.cbMember;
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("%s"),pszMember[cbMember]);
		pDC->TextOut(50,cr.bottom-38,szBuffer,lstrlen(szBuffer));
		//CRect re;

		//GetWindowRect(re);
		//CString aa;
		//aa.Format("%d,%d",re.right,re.bottom);
		//MessageBox(aa);
		//�û�ͷ��
		g_GlobalUnits.m_UserFaceRes->DrawBigFace(pDC,160,cr.bottom-82,UserData.wFaceID);
	}//

	return;
}

//�����ؼ�
void CPlazaViewItem::RectifyControl(int nWidth, int nHeight)
{
	//״̬�ж�
	if (m_bInitDialog==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;
	//�ƶ��ؼ�
	HDWP hDwp=BeginDeferWindowPos(32);
	DeferWindowPos(hDwp,m_ServerItemView,NULL,22,40,260,460,uFlags);

	//DeferWindowPos(hDwp,m_pHtmlBrower->GetSafeHwnd(),NULL,117,nHeight-109,354,104,uFlags);

	tagGlobalUserData UserData=g_GlobalUnits.GetGolbalUserData();
	
	for(UINT i=0;i<m_GameButtons.size();i++)
	{
		if (UserData.dwUserID!=0)
		{
			m_GameButtons[i]->Button.ShowWindow(SW_NORMAL);
			DeferWindowPos(hDwp,m_GameButtons[i]->Button.m_hWnd,NULL,GAME_LIST_X+8,GAME_LIST_Y+52 + i * 35,0,0,uFlags|SWP_NOSIZE);
		}
		else
			m_GameButtons[i]->Button.ShowWindow(SW_HIDE);
			
	}

	m_ServerList.SetHeight(nHeight-165);//y��11����77
	m_ServerList.SetWindowPos(NULL,11,77,0,0,SWP_NOSIZE);//y��6����71
	m_ServerList.UpdateButton();

	DeferWindowPos(hDwp,m_btGame1,NULL,34,57,65,16,uFlags);
	DeferWindowPos(hDwp,m_btGame2,NULL,28+65,57,65,16,uFlags);
	DeferWindowPos(hDwp,m_btGame3,NULL,22+65*2,57,65,16,uFlags);

	EndDeferWindowPos(hDwp);
	Invalidate(FALSE);
	return;
}


//bluker:��ʾ�����б�
void CPlazaViewItem::ShowServers(tagGameButton* pGameButton)
{
int nIndex=0;
CListServer * pListServer=NULL;

		m_RoomList.ClearButton();
	//ö�����п��÷�����
	while(true)
	{
		pListServer=g_GlobalUnits.m_ServerListManager.EnumServerItem(nIndex++);
		if(!pListServer)break;
		tagGameServer *pGameServer=pListServer->GetItemInfo();
		if(pGameButton->wKindID == pGameServer->wKindID)
		{
	//		AfxMessageBox("�г���ǰѡ���������Ϸ");
			//�г���ǰѡ���������Ϸ
			//pGameServer->wServerID,pGameButton->szKindName,pGameServer->szServerName;
			CString strServer;
			//strServer.Format("%s    %d",pGameServer->szServerName,pGameServer->dwOnLineCount);
			strServer.Format("%s",pGameServer->szServerName);
			int nBtn = m_RoomList.AddButton(AfxGetInstanceHandle(),ROOMLIST_BTN,IMG_LISTCTRL_CMD_ID,strServer,
				20,5,0xffffff,(pGameServer->wServerID <<16) | pGameServer->wKindID);

			tagImageListButton *Btn=m_RoomList.GetButtonInfo(nBtn);
			if(Btn)
			{
				CSkinImage tmp;
				tmp.SetLoadInfo(ROOMLIST_BTN,AfxGetInstanceHandle());
				CImageHandle ImgHandle(&Btn->img);
				CImageHandle ImgHandlet(&tmp);

				HDC hdc=Btn->img.GetDC();
				//����Money
				tmp.Draw(hdc,CRect(110,0,164,30),CRect(110,0,164,30));

				//д�µ�Money
				char Money[32];
				sprintf(Money,"%d",pGameServer->dwOnLineCount);
				m_RoomList.DrawText(nBtn,130 - strlen(Money)*4+1,5+1,Money,0xffffff);
				m_RoomList.DrawText(nBtn,130 - strlen(Money)*4,5,Money,0x000000);

				Btn->img.ReleaseDC();
				m_RoomList.UpdateButton();
			}

		}
	}


CRect rc;
CRect rcView;
POINT pt;
	pGameButton->Button.GetWindowRect(rc);
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	//GetWindowRect(rcView);
	GetClientRect(&rcView);
	//if(pt.y > rcView.bottom - m_RoomList.GetHeight())
	//	pt.y = rcView.bottom - m_RoomList.GetHeight();
	if(rcView.bottom - pt.y  < m_RoomList.GetHeight())
		pt.y = rcView.bottom - m_RoomList.GetHeight();

	//CString aa;
	//aa.Format("%d,%d,%d",pt.y,rcView.bottom,m_RoomList.GetHeight());
	//MessageBox(aa);
	//aa.Format("%d,%d,%d",pt.y,rcView.bottom,m_RoomList.GetHeight());
	//MessageBox(aa);
//	ScreenToClient(rc);
	//m_RoomList.SetWindowPos(NULL,GAME_LIST_X + m_GameListT.GetWidth()+1,pt.y,0,0,SWP_NOSIZE);

	//m_ServerList.GetClientRect(&rcView);
	m_RoomList.SetWindowPos(NULL,m_ServerList.m_xTop.GetWidth() + m_GameListT.GetWidth()+20,pt.y,0,0,SWP_NOSIZE);

	m_RoomList.ShowWindow(SW_NORMAL);
	m_RoomList.UpdateButton();

}
void CPlazaViewItem::ClearGameButtons()
{
	for(UINT i=0;i<m_GameButtons.size();i++)
	{
		delete m_GameButtons[i];
	}
	m_GameButtons.clear();
}

//bluker:��Ϸ����ͼ�갴ť[����¼�]
afx_msg void CPlazaViewItem::OnBnClicked_GameButtons()
{/*
	CWnd *hwnd=this->GetFocus();
	for(UINT i=0;i<m_GameButtons.size();i++)
	{
		//if(hwnd->m_hWnd==m_GameButtons[i]->Button.m_hWnd)
		//if(hwnd == m_ServerList.GetWindow(i))
		ULONG nButton;
		tagImageListButton *BtnInfo;
		nButton=m_ServerList.GetLastButton();
		if(nButton)
		{
			BtnInfo=m_ServerList.GetButtonInfo(nButton);
			if(!BtnInfo)return;
			if(BtnInfo->UserData>0)
			{
			AfxMessageBox("asd2");
			ShowServers(m_GameButtons[i]);
			return;
			}
		}
	}*/
	ULONG nButton;
		tagImageListButton *BtnInfo;
		nButton=m_ServerList.GetLastButton();
		if(nButton)
		{
			BtnInfo=m_ServerList.GetButtonInfo(nButton);
			if(!BtnInfo)return;
			for(int i = 0; i < (int)m_GameButtons.size();i++)
			{
				if(BtnInfo->UserData == m_GameButtons[i]->wKindID)
				{
					ShowServers(m_GameButtons[i]);
				}
			}
		}
}

BOOL CPlazaViewItem::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if(wParam == IMG_LISTCTRL_CMD_ID)
	{
		ULONG nButton;
		tagImageListButton *BtnInfo;

		nButton=m_RoomList.GetLastButton();
		if(nButton)
		{
			BtnInfo=m_RoomList.GetButtonInfo(nButton);
			if(!BtnInfo)return true;
			if(BtnInfo->UserData>0)
			{
				WORD wKindID = BtnInfo->UserData & 0xffff;
				WORD wServerID = BtnInfo->UserData>>16;

				if(wKindID==PRIZE_GAME_ID)
				{
					//����������
					CString strCommonLine;
					CListServer * pListServer=g_GlobalUnits.m_ServerListManager.SearchServerItem(wKindID,wServerID);
					if(!pListServer)return true;

					tagGameServer *pGameServer = pListServer->GetItemInfo();
					tagGameKind * pGameKind = pListServer->GetListKind()->GetItemInfo();

					strCommonLine.Format(TEXT("%s /WndPlaza:%d /GameName:\"%s\" /sid:%s"),
						pGameKind->szProcessName,
						::AfxGetMainWnd()->m_hWnd,
						pGameServer->szServerName,
						g_GlobalUnits.GetGolbalUserData().szSessionId);

					CWinFileInfo WinFileInfo;
					if (WinFileInfo.OpenWinFile(pGameKind->szProcessName)==false)
					{
						g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
						return NULL;
					}
					DWORD dwFileVerMS=0L,dwFileVerLS=0L;
					WinFileInfo.GetFileVersion(dwFileVerMS,dwFileVerLS);//��ȡ�汾

					//�汾����
					BYTE cbFileVer1=(BYTE)(HIWORD(dwFileVerMS));
					BYTE cbFileVer2=(BYTE)(LOWORD(dwFileVerMS));
					BYTE cbFileVer3=(BYTE)(HIWORD(dwFileVerLS));
					BYTE cbFileVer4=(BYTE)(LOWORD(dwFileVerLS));
					BYTE cbListVer1=(BYTE)(LOWORD(LOWORD(pGameKind->dwMaxVersion)));
					BYTE cbListVer2=(BYTE)(HIBYTE(LOWORD(pGameKind->dwMaxVersion)));
					BYTE cbListVer3=(BYTE)(LOBYTE(HIWORD(pGameKind->dwMaxVersion)));
					BYTE cbListVer4=(BYTE)(HIBYTE(HIWORD(pGameKind->dwMaxVersion)));
					//�жϰ汾
					if ((cbFileVer1!=cbListVer1)||(cbFileVer2!=cbListVer2)||(cbFileVer3!=cbListVer3)||(cbFileVer4!=cbListVer4))
					{
						g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
						return false;
					}

					//������Ϸ�ͻ���
					STARTUPINFO StartInfo;
					memset(&StartInfo,0,sizeof(StartInfo));
					StartInfo.cb=sizeof(StartInfo);
					StartInfo.wShowWindow=SW_SHOWMAXIMIZED;
					BOOL bSuccess=CreateProcess(NULL,strCommonLine.GetBuffer(),NULL,NULL,FALSE,CREATE_DEFAULT_ERROR_MODE,NULL,NULL,&StartInfo,&g_GameProcessInfo);
					strCommonLine.ReleaseBuffer();
					if (bSuccess==FALSE)
					{
						g_GlobalAttemper.DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,true);
						memset(&g_GameProcessInfo,0,sizeof(g_GameProcessInfo));
					}
					else
					{
						AfxGetMainWnd()->ShowWindow(SW_HIDE);
					}
					return true;
				}
				else
				{
					g_pControlBar->CreateRoomViewItem(wKindID,wServerID);
					m_RoomList.ShowWindow(SW_HIDE);

					g_szGameTitle = TEXT(szProductName);
					CListKind * pListKind = g_GlobalUnits.m_ServerListManager.SearchKindItem(wKindID);
					tagGameKind *pGameKind=pListKind->GetItemInfo();
					g_szGameTitle += pGameKind->szKindName;
					g_szGameTitle += TEXT(" ");

					CListServer *pListServer=g_GlobalUnits.m_ServerListManager.SearchServerItem(wKindID,wServerID);
					tagGameServer *pGameServer=pListServer->GetItemInfo();
					g_szGameTitle += pGameServer->szServerName;
				}
			}
		}
		/*
		nButton=m_RoomList.GetLastButtonRT();
		if(nButton)
		{
			MessageBox("OK");
			return;
		}//*/
		return true;
	}
	return __super::OnCommand(wParam,lParam);
}



//-----------------------------------------------
//					the end
//-----------------------------------------------




