#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "..\..\�������\��������\HtmlBrowser.h"

class CDlgChangeTheme :	public CSkinDialogEx
{
public:
	CSkinButton							m_btButton1;				//��������


	CDlgChangeTheme(void);
	~CDlgChangeTheme(void);

	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);

	afx_msg void OnBnClickedButton1();

	DECLARE_MESSAGE_MAP()
};
