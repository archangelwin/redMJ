#include "Stdafx.h"
#include <AfxPriv.h>
#include "ImageDialog.h"


//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CImageDialog, CDialog)

BEGIN_MESSAGE_MAP(CImageDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////

//���캯��
CImageDialog::CImageDialog(UINT nIDTemplate, CWnd * pParentWnd) 
	: CDialog(nIDTemplate,pParentWnd)
{
}

//��������
CImageDialog::~CImageDialog()
{
}

//��ʼ����Ϣ
BOOL CImageDialog::OnInitDialog()
{
	__super::OnInitDialog();

	//��ʼ��
	ModifyStyle(WS_CAPTION,0,SWP_DRAWFRAME);
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	return TRUE;
}


//�滭��Ϣ 
void CImageDialog::OnPaint()
{
	CPaintDC dc(this);
	DrawSkinView(&dc);
	return;
}

//�滭����
BOOL CImageDialog::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//�ؼ���ɫ
HBRUSH CImageDialog::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(0xdddddd);
			pDC->SetTextColor(0xff);
			return NULL;
		}
	}
	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

void CImageDialog::DrawSkinView(CDC *pDC)
{
}

//////////////////////////////////////////////////////////////////////////
