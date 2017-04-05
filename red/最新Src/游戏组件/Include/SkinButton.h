#pragma once

#ifndef SKIN_BUTTON_HEAD_FILE
#define SKIN_BUTTON_HEAD_FILE

#include "SkinImage.h"
#include "SkinControls.h"
#include "SkinAttribute.h"

//////////////////////////////////////////////////////////////////////////

//属性名字
#define SKIN_BUTTON_CRTEXTCOLOR			TEXT("按钮字体颜色")			// COLORREF 类型 （读写）
#define SKIN_BUTTON_STRIMAGEPATH		TEXT("按钮背景图")				// CString 类型 （读写）

//////////////////////////////////////////////////////////////////////////

//按钮类属性
class CSkinButtonAttribute : public CSkinAttribute
{
	friend class CSkinButton;

	//设置部分
public:
	COLORREF							m_crTextColor;					//字体颜色
	CString								m_strImagePath;					//位图路径

	//GDI 对象
public:
	CSkinImage							m_ImageBack;					//按钮位图

	//函数定义
protected:
	//构造函数
	CSkinButtonAttribute();
	//析构函数
	virtual ~CSkinButtonAttribute();

	//接口函数
public:
	//加载配置
	virtual bool __cdecl LoadSkinOption();
	//保存配置
	virtual bool __cdecl SaveSkinOption();
};

//////////////////////////////////////////////////////////////////////////

//按钮类
class SKIN_CONTROL_CLASS CSkinButton : public CButton
{
	friend class CRgnButton;

	//变量定义
protected:
	bool								m_bExpand;						//是否拉伸
	bool								m_bHovering;					//盘旋标志
	HICON								m_hIcon;						//按钮图标
	COLORREF							m_crTextColor;					//字体颜色
	CSkinImage							m_ImageBack;					//按钮位图
	POINT								m_TitlePt;						//标题位置
	//接口指针
protected:
	IMouseEvent							* m_pIMouseEvent;				//鼠标事件

	//按钮类属性
public:
	static CSkinButtonAttribute			m_SkinAttribute;				//按钮属性

	//函数定义
public:
	//构造函数
	CSkinButton();
	//析构函数
	virtual ~CSkinButton();

	//重载函数
protected:
	//控件子类化
	virtual void PreSubclassWindow();
	//界面绘画函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//默认回调函数
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//功能函数
public:
	//获取鼠标回调接口
	IMouseEvent * GetMouseEventCallBack() { return m_pIMouseEvent; }
	//设置鼠标回调接口
	void SetMouseEventCallBack(IMouseEvent * pIMouseEvent) { m_pIMouseEvent=pIMouseEvent; };

	//设置函数
public:
	//调整位置
	bool FixButtonSize();
	//设置图标
	bool SetButtonIcon(HICON hIcon);
	//设置颜色
	bool SetTextColor(COLORREF crTextColor);
	//加载位图
	bool SetButtonImage(LPCTSTR pszFileName, bool bExpandImage);
	//加载位图
	bool SetButtonImage(UINT uBitmapID, HINSTANCE hInstance, bool bExpandImage);
	//默认按钮
	void SetDefaultButton(bool bResetIcon=true, bool bResetColor=true, bool bResetImage=true);

	//设置标题位置
	void SetTitlePos(int x,int y);
	//查询函数
public:
	//获取图标
	HICON GetButtonIcon() { return m_hIcon; }
	//获取颜色
	COLORREF GetButtonColor() { return m_crTextColor; }
	//获取位图参数
	bool GetButtonLoadInfo(tagImageLoadInfo & LoadInfo);
	//获取属性接口
	static CSkinButtonAttribute * GetSkinAttribute() { return &m_SkinAttribute; }

	//消息函数
protected:
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//鼠标离开
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//背景消息
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinButton)
};

//////////////////////////////////////////////////////////////////////////

//区域按钮类
class SKIN_CONTROL_CLASS CRgnButton : public CButton
{
	//变量定义
protected:
	bool								m_bHovering;					//盘旋标志
	COLORREF							m_crTrans;						//透明颜色
	COLORREF							m_crTextColor;					//字体颜色
	CSkinImage							m_ImageBack;					//背景位图
	POINT								m_TitlePt;						//标题位置

	//接口指针
protected:
	IMouseEvent							* m_pIMouseEvent;				//鼠标事件

	//函数定义
public:
	//构造函数
	CRgnButton();
	//析构函数
	virtual ~CRgnButton();

	//重载函数
protected:
	//控件子类化
	virtual void PreSubclassWindow();
	//界面绘画函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//默认回调函数
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//功能函数
public:
	//创建区域
	static HRGN MakeRegion(HDC hdc,LONG width,LONG height,COLORREF crTrans);

	//加载位图
	bool LoadRgnImage(LPCTSTR pszFileName, COLORREF crTrans,HRGN hrgn=NULL);
	//加载位图
	bool LoadRgnImage(HINSTANCE hInstance, UINT uBitmapID, COLORREF crTrans,HRGN hrgn=NULL);
	//获取鼠标回调接口
	IMouseEvent * GetMouseEventCallBack() { return m_pIMouseEvent; }
	//设置鼠标回调接口
	void SetMouseEventCallBack(IMouseEvent * pIMouseEvent) { m_pIMouseEvent=pIMouseEvent; };

	//设置标题位置
	void SetTitlePos(int x,int y);

	//内部函数 
private:
	//创建区域
	bool CreateControlRgn(COLORREF crTrans,HRGN hrgn=NULL);

	//消息函数
protected:
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//背景消息
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//鼠标离开
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CRgnButton)
};

//////////////////////////////////////////////////////////////////////////

#endif