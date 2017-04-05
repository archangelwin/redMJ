#include "Stdafx.h"
#include "GlobalUnits.h"
#include "Show.h"
#include "RoomViewItem.h"

#define CONTROL_SPACE						2							//�ؼ����
#define PIC_BT_WIDE							20							//��ť���
#define PIC_BT_HIGHT						20							//��ť�߶�
#define BT_BUTTON_WIDE						65							//��ť���
#define BT_BUTTON_HIGHT						21							//��ť�߶�

BEGIN_MESSAGE_MAP(CShow, CSkinDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_SHOW_CLOSE, OnBnClickedClose)
END_MESSAGE_MAP()

//���캯��
CShow::CShow(CWnd * pParentWnd) : CSkinDialogEx(IDD_SHOW)
{
	s_pParentWnd=NULL;
	m_dwTargetUserID=0L;
	m_pParentWnd=pParentWnd;
	m_pTargetUserItem=NULL;
}

//��������
CShow::~CShow()
{
}

//�ؼ��󶨺���
void CShow::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOW_CLOSE,m_BtClose);
}

//��ʼ������
BOOL CShow::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	if (m_pTargetUserItem!=NULL)
	{
		TCHAR szTitle[256];
		_snprintf(szTitle,sizeof(szTitle),TEXT("[ %s ] �� ��������SHOW"),m_pTargetUserItem->GetUserData()->szName,m_strRoomName);
		SetWindowText(szTitle);
		
	}
	return FALSE;
}




//�˳���ť
void CShow::OnBnClickedClose()
{
	DestroyWindow();
	return;
}

//��ȡλ��
void CShow::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
{
	lpMMI->ptMinTrackSize.x=300;
	lpMMI->ptMinTrackSize.y=250;
	return;
}


