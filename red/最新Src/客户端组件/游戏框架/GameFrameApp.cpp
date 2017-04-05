#include "Stdafx.h"
#include "Resource.h"
#include "GameFrameApp.h"
#include "GlobalOption.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameApp, CWinApp)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameApp::CGameFrameApp()
{
	m_pGameFrame=NULL;
}

//��������
CGameFrameApp::~CGameFrameApp()
{
}

//��ʼ������
BOOL CGameFrameApp::InitInstance()
{
	__super::InitInstance();

	//�ڲ���ʼ��
	AfxOleInit();
	AfxInitRichEdit2();
	InitCommonControls();
	AfxEnableControlContainer();

	//��ʼ�������
	IUnknownEx * pIUnknownEx=(IUnknownEx *)m_SkinRecordFile.QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
	CSkinAttribute::LoadSkinAttribute(pIUnknownEx);

	//��������
	g_GlobalOption.LoadOptionParameter();

	try
	{
		//����������
		m_pGameFrame=GetGameFrameDlg();
		ASSERT(m_pGameFrame!=NULL);
		if (m_pGameFrame==NULL) throw TEXT("��Ϸ�����ڴ���ʧ��");

		//MessageBox(0,"1",0,0);
		//����������
		m_pMainWnd=m_pGameFrame;
		AfxSetResourceHandle(GetModuleHandle(GAME_FRAME_DLL_NAME));
		//MessageBox(0,"2",0,0);
		m_pGameFrame->Create(IDD_EMPTY_MAINFRAME,NULL);
		//MessageBox(0,"3",0,0);
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}
	catch (LPCTSTR pszMesssage)
	{
		CString strBuffer;
		strBuffer.Format(TEXT("���� [ %s ] ��Ϸ���򼴽��˳���"),pszMesssage);
		AfxMessageBox(strBuffer,MB_ICONSTOP);
		if (m_pGameFrame!=NULL) SafeDelete(m_pGameFrame);
		return FALSE;
	}

	return TRUE;
}

//�˳���Ϣ
int CGameFrameApp::ExitInstance()
{
	//ɾ������
	if (m_pGameFrame!=NULL) SafeDelete(m_pGameFrame);
	return __super::ExitInstance();
}

//////////////////////////////////////////////////////////////////////////
