#pragma once

#ifndef IMAGE_DIALOG_HEAD_FILE
#define IMAGE_DIALOG_HEAD_FILE

#include "SkinControls.h"

//////////////////////////////////////////////////////////////////////////

//�Ի�����
class SKIN_CONTROL_CLASS CImageDialog : public CDialog
{
	//��������
public:
	//���캯��
	CImageDialog(UINT nIDTemplate, CWnd * pParentWnd=NULL);
	//��������
	virtual ~CImageDialog();

	//���غ���
public:
	//��ʼ����Ϣ
	virtual BOOL OnInitDialog();

protected:
	//������
	void DrawSkinView(CDC *pDC);


	//��Ϣӳ��
protected:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	afx_msg HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CImageDialog)
};

//////////////////////////////////////////////////////////////////////////

#endif