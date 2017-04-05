#ifndef GAME_FRAME_DLG_HEAD_FILE
#define GAME_FRAME_DLG_HEAD_FILE

#pragma once

#include "GameFrame.h"
#include "GameFrameView.h"
#include "ToolBarDlg.h"

//��˵��
class CGameFrameControl;
class CClientKernelSink;

//////////////////////////////////////////////////////////////////////////

#define VOICE_SIGN TEXT("/VoiceTo:")

//��Ϸ������
class GAME_FRAME_CLASS CGameFrameDlg : public CDialog
{
	//��Ԫ����
	friend class CClientKernelSink;
	friend class CGameFrameControl;

	//�ں˱���
protected:
	CClientKernelSink					* m_pKernelSink;				//���ӽӿ�
	CUserFaceResHelper					m_UserFaceResHelper;			//ͷ�����
	CClientKernelHelper					m_ClientKernelHelper;			//��Ϸ�߼�
	CMessageProxyHelper					m_MessageProxyHelper;			//�������

	//���渨��
private:
	bool								m_bReset;						//�Ƿ�����
	bool								m_bRectify;						//������־
	bool								m_bInitDialog;					//��ʼ��־

	//���ñ���
private:
	bool								m_bAllowSound;					//��������


	//�ؼ�����
protected:
	CGameFrameView						* m_pGameFrameView;				//��ͼָ��
	//CGameFrameControl					* m_pGameFrameControl;			//������ͼ

	CRgnButton							*m_btQuit;						//�˳���ť
	CRgnButton							*m_btMax;						//��󻯰�ť
	CRgnButton							*m_btMin;						//��С����ť
	bool								m_bMaxed;						//��󻯱�־

	CRgnButton							*m_btButton1;					//���ܰ�ť
	CRgnButton							*m_btButton2;					//���ܰ�ť
	CRgnButton							*m_btButton3;					//���ܰ�ť
	CRgnButton							*m_btButton4;					//���ܰ�ť
	CRgnButton							*m_btButton5;					//���ܰ�ť
	CHtmlBrower							*m_pHtmlBrower1;				//�������

	CRgnButton							*m_btOption;					//ϵͳ���ð�ť
	CRgnButton							*m_btHelp;						//������ť
public:
	CDlgToolBar							*m_ToolBar;						//������
	CDlgChatMsg							*m_ChatMsgDlg;					//��Ϣ��
	CDlgUserList						*m_DlgUserList;					//�û��б��
	CExpression							m_Expression;					//���鴰��
	CRgnButton							*m_btToolSet;					//��Ϸ����
	
	//���ܰ�ť
	afx_msg void OnBnClickedButton1();
	//���ܰ�ť
	afx_msg void OnBnClickedButton2();
	//���ܰ�ť
	afx_msg void OnBnClickedButton3();
	//���ܰ�ť
	afx_msg void OnBnClickedButton4();
	//���ܰ�ť
	afx_msg void OnBnClickedButton5();

	//��Ϸ����
public:
	WORD								m_wKindID;//��ǰ��Ϸ����
	WORD								m_wGameGenre;

	//��������
public:
	//���캯��
	CGameFrameDlg(CGameFrameView * pGameFrameView);
	//��������
	virtual ~CGameFrameDlg();

	//������ӿ�
public:
	//��ť��Ϣ
	//virtual bool __cdecl OnSplitterButton(CSkinSplitter * pSkinSplitter, CSkinButton * pSplitterButton);
	//�������Ϣ
	//virtual bool __cdecl OnSplitterEvent(CSkinSplitter * pSkinSplitter, UINT uSplitID, int nXPos, int nYPos);

	//����̳�
private:
	//��ʼ����
	virtual bool InitGameFrame()=NULL;
	//���ÿ��
	virtual void ResetGameFrame()=NULL;
	//��Ϸ����
	virtual void OnGameOptionSet()=NULL;
	//��Ϸ����
	virtual void OnGameOptionHelp(){};
	//ʱ����Ϣ
	virtual bool OnTimerMessage(WORD wChairID, UINT nElapse, UINT nTimerID)=NULL;
	//�Թ�״̬
	virtual void OnLookonChanged(bool bLookonUser, const void * pBuffer, WORD wDataSize)=NULL;
	//������Ϣ
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)=NULL;
	//��Ϸ����
	virtual bool OnGameSceneMessage(BYTE cbGameStatus, bool bLookonOther, const void * pBuffer, WORD wDataSize)=NULL;

	//����̳�
private:
	//��������
	virtual void RectifyControl(int nWidth, int nHeight);
	//�����Ϣ
	virtual bool OnFrameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);

	//���ܺ���
public:
	//���ͺ���
	bool SendData(WORD wSubCmdID);
	//���ͺ���
	bool SendData(WORD wSubCmdID, void * pData, WORD wDataSize);
	//����׼��
	bool SendUserReady(void * pBuffer, WORD wDataSize);
	//���ö�ʱ��
	bool SetGameTimer(WORD wChairID, UINT nTimerID, UINT nElapse);
	//ɾ����ʱ��
	bool KillGameTimer(UINT nTimerID);
	//��������
	bool PlayGameSound(LPCTSTR pszSoundName);
	//��������
	bool PlayGameSound(HINSTANCE hInstance, LPCTSTR pszSoundName);
	//��������
	bool PlayGameSoundFromFip(LPCTSTR pszSoundName);
	//��������
	bool PlayGameSoundFromFip2(UINT uEventType,WORD wToWho);

	//ָ���������ļ�
	bool SetWavPackage(LPCSTR szWavFile);

	//ָ�������ű��ļ�
	bool SetWavScript(LPCSTR szWavScriptFile);

	//�ҳ�������������
	HWND FindPlazaWindow();

	//��Ϣ����
public:
	//����ͼƬ
	bool InsertImage(CBitmap * pBitmap);
	//��������
	bool InsertUserName(LPCTSTR pszUserName);
	//ϵͳ��Ϣ
	bool InsertSystemString(LPCTSTR pszString);
	//��ɫ��Ϣ
	bool InsertShtickString(LPCTSTR pszString, COLORREF crColor, bool bNewLine);
	//��ͨ��Ϣ
	bool InsertGeneralString(LPCTSTR pszString, COLORREF crColor, bool bNewLine);

	//��������
public:
	//�������
	void ActiveGameFrame();
	//�л�����
	WORD SwitchViewChairID(WORD wChairID);		//����ԭ�е�ת������
	WORD GetChairCount();						//�õ�������
	WORD XChair(WORD wChairID);	//�ӷ�����id��λ��(����CGoldFlowerPlayer)
	WORD XChairUserInfo(WORD wChairID);			//�ӷ�����id��λ��(tagUserData *GetUserInfo())
	bool SetReadyIfAutoStart(CButton *pBtnStart);//�Զ����� �� ��Ӧ

	//��������
public:
	//�Ƿ�����
	bool IsEnableSound();
	//��������
	void EnableSound(bool bEnable);

	//��Ϣ����
public:
	//�Թ�ģʽ
	bool IsLookonMode();
	//�����Թ�
	bool IsAllowLookon();
	//�Լ�λ��
	WORD GetMeChairID();
	//ʱ��λ��
	WORD GetTimeChairID();
	//��ȡ�û�
	const tagUserData * GetUserData(WORD wChairID);
	//�ں˽ӿ�
	void * GetClientKernel(const IID & Guid, DWORD dwQueryVer);

	//��Ϸ״̬
public:
	//��Ϸ״̬
	BYTE GetGameStatus();
	//��Ϸ״̬
	void SetGameStatus(BYTE bGameStatus);

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//ȷ����Ϣ
	virtual void OnOK();
	//ȡ����Ϣ
	virtual void OnCancel();

	//��Ϣӳ��
public:
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnWindowPosChanging(WINDOWPOS * lpwndpos);
	afx_msg void OnBnClickedQuit();//�˳�
	afx_msg void OnBnClickedMax();//���
	afx_msg void OnBnClickedMin();//��С��
	afx_msg void OnBnClickedOption();//ϵͳ����
	afx_msg void OnBnClickedHelp();//��Ϸ����
	//������Ϣ
	LRESULT OnHitExpression(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif