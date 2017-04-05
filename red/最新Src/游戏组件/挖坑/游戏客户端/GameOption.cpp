#include "Stdafx.h"
#include "GameOption.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameOption, CSkinDialogEx)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameOption::CGameOption() : CSkinDialogEx(IDD_OPTION)
{
	//���ñ���
	m_bDeasilOrder=true;
	m_dwCardHSpace=DEFAULT_PELS;
	m_GameSoundMode=enMandarinSound;

	return;
}

//��������
CGameOption::~CGameOption()
{
}

//�ؼ���
void CGameOption::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_DEFAULT, m_btDefault);
}

//��ʼ������
BOOL CGameOption::OnInitDialog()
{
	__super::OnInitDialog();

	//���ÿؼ�
	SetWindowText(TEXT("��Ϸ����"));

	//��������
	if ((m_dwCardHSpace>MAX_PELS)||(m_dwCardHSpace<LESS_PELS)) m_dwCardHSpace=DEFAULT_PELS;
	if ((m_GameSoundMode>enShanXiSound)||(m_GameSoundMode<enNoSound)) m_GameSoundMode=enMandarinSound;

	//����˳��
	if (m_bDeasilOrder==true) ((CButton *)GetDlgItem(IDC_DEASIL_ORDER))->SetCheck(BST_CHECKED);

	//�˿�����
	int nItem=0;
	TCHAR szBuffer[32]=TEXT("");
	CComboBox * pComboBox=(CComboBox *)GetDlgItem(IDC_CARD_SPACE);
	for (DWORD i=LESS_PELS;i<=MAX_PELS;i++)
	{
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("%2ld"),i);
		nItem=pComboBox->InsertString((i-LESS_PELS),szBuffer);
		pComboBox->SetItemData(nItem,i);
		if (m_dwCardHSpace==i) pComboBox->SetCurSel(nItem);
	}

	//����Ч��
	if (m_GameSoundMode==enNoSound) ((CButton *)GetDlgItem(IDC_NO_SOUND))->SetCheck(BST_CHECKED);
	else if (m_GameSoundMode==enNormalSound) ((CButton *)GetDlgItem(IDC_NORMAL_SOUND))->SetCheck(BST_CHECKED);
	else if (m_GameSoundMode==enMandarinSound) ((CButton *)GetDlgItem(IDC_MANDARIN_SOUND))->SetCheck(BST_CHECKED);
	else if (m_GameSoundMode==enShanXiSound) ((CButton *)GetDlgItem(IDC_SHANXI_SOUND))->SetCheck(BST_CHECKED);

	return TRUE;
}

//ȷ����Ϣ
void CGameOption::OnOK()
{
	//����˳��
	m_bDeasilOrder=(((CButton *)GetDlgItem(IDC_DEASIL_ORDER))->GetCheck()==BST_CHECKED);

	//�˿�����
	CComboBox * pComboBox=(CComboBox *)GetDlgItem(IDC_CARD_SPACE);
	m_dwCardHSpace=(DWORD)pComboBox->GetItemData(pComboBox->GetCurSel());

	//����Ч��
	if (((CButton *)GetDlgItem(IDC_NO_SOUND))->GetCheck()==BST_CHECKED) m_GameSoundMode=enNoSound;
	else if (((CButton *)GetDlgItem(IDC_NORMAL_SOUND))->GetCheck()==BST_CHECKED) m_GameSoundMode=enNormalSound;
	else if (((CButton *)GetDlgItem(IDC_MANDARIN_SOUND))->GetCheck()==BST_CHECKED) m_GameSoundMode=enMandarinSound;
	else if (((CButton *)GetDlgItem(IDC_SHANXI_SOUND))->GetCheck()==BST_CHECKED) m_GameSoundMode=enShanXiSound;

	__super::OnOK();
}

//Ĭ�ϲ���
void CGameOption::OnDefault()
{
	//���ÿؼ�
	((CButton *)GetDlgItem(IDC_NO_SOUND))->SetCheck(BST_UNCHECKED);
	((CButton *)GetDlgItem(IDC_NORMAL_SOUND))->SetCheck(BST_UNCHECKED);
	((CButton *)GetDlgItem(IDC_MANDARIN_SOUND))->SetCheck(BST_CHECKED);
	((CButton *)GetDlgItem(IDC_SHANXI_SOUND))->SetCheck(BST_UNCHECKED);
	((CComboBox *)GetDlgItem(IDC_CARD_SPACE))->SetCurSel(DEFAULT_PELS-LESS_PELS);

	return;
}

//////////////////////////////////////////////////////////////////////////
