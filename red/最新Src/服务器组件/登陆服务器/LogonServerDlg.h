#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "LogonService.h"

//////////////////////////////////////////////////////////////////////////



//配置对话框
class CSystemOptionDlg : public CDialog
{
	//构造函数
public:
	//构造程序
	CSystemOptionDlg();
	//析构函数
	virtual ~CSystemOptionDlg();

	//重载函数
protected:
	//初始化函数
	virtual BOOL OnInitDialog();
	//控件子类化
	virtual void DoDataExchange(CDataExchange * pDX);
	//确定函数
	virtual void OnOK();

};

//////////////////////////////////////////////////////////////////////////

//主对话框
class CLogonServerDlg : public CDialog
{
	//变量定义
protected:
	bool							m_bAskQuit;							//退出询问

	//组件变量
public:
	CLogonService					m_LogonService;						//登录服务
	CEventServiceHelper				m_EventService;						//事件服务

	//控件变量
public:
	CRichEditCtrl					m_RichEditCtrl;						//事件记录

	//构造函数
public:
	//构造程序
	CLogonServerDlg();
	//析构函数
	virtual ~CLogonServerDlg();

	//重载函数
protected:
	//控件子类化
	virtual void DoDataExchange(CDataExchange * pDX);
	//初始化函数
	virtual BOOL OnInitDialog();
	//确定消息
	virtual void OnOK();
	//取消函数
	virtual void OnCancel();
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//消息函数
protected:
	//启动服务
	afx_msg void OnBnClickedStartService();
	//停止服务
	afx_msg void OnBnClickedStopService();
	//配置服务
	afx_msg void OnBnClickedInitService();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

//////////////////////////////////////////////////////////////////////////
