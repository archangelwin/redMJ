#ifndef USER_FACE_HEAD_FILE
#define USER_FACE_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//ƽ̨ͷ�ļ�
#include "..\..\ģ���\Template.h"
#include "..\..\����ӿ�\IUnknownEx.h"

//////////////////////////////////////////////////////////////////////////
//�����궨��

//�궨��
#define LIT_FACE_WIDTH						24							//ͷ����
#define LIT_FACE_HEIGHT						24							//ͷ��߶�
#define NOR_FACE_WIDTH						32							//ͷ����
#define NOR_FACE_HEIGHT						32							//ͷ��߶�
#define BIG_FACE_WIDTH						48							//ͷ����
#define BIG_FACE_HEIGHT						48							//ͷ��߶�

//ģ�鶨��
#ifdef _DEBUG
	#define USER_FACE_DLL_NAME	TEXT("UserFaceD.dll")					//��� DLL ����
#else
	#define USER_FACE_DLL_NAME	TEXT("UserFace.dll")					//��� DLL ����
#endif

//////////////////////////////////////////////////////////////////////////

#define VER_IUserFaceRes INTERFACE_VERSION(1,1)
static const GUID IID_IUserFaceRes={0xd9c22bd3,0x986b,0x4513,0x83,0x5d,0x52,0xb4,0x13,0x20,0x76,0x34};

//ͷ������ӿ�
interface IUserFaceRes : public IUnknownEx
{
	//��ȡ��Ŀ
	virtual WORD __cdecl GetFaceCount()=NULL;
	//��ȡ��С
	virtual const CSize & __cdecl GetSmallFaceSize()=NULL;
	//��ȡ��С
	virtual const CSize & __cdecl GetNormalFaceSize()=NULL;
	//��ȡ��С
	virtual const CSize & __cdecl GetBigFaceSize()=NULL;
	//�滭ͷ��
	virtual void __cdecl DrawSmallFace(CDC * pDC, int nXPos, int nYPos, WORD wFaceID)=NULL;
	//�滭ͷ��
	virtual void __cdecl DrawNormalFace(CDC * pDC, int nXPos, int nYPos, WORD wFaceID)=NULL;
	//�滭ͷ��
	virtual void __cdecl DrawBigFace(CDC * pDC, int nXPos, int nYPos, WORD wFaceID)=NULL;
};

//////////////////////////////////////////////////////////////////////////

#define VER_IFaceControl INTERFACE_VERSION(1,1)
static const GUID IID_IFaceControl={0xd2c483c,0xbdfa,0x46a6,0x8e,0x60,0xf8,0xc8,0x77,0xed,0x59,0xc3};

//ͷ��ؼ��ӿ�
interface IFaceControl : public IUnknownEx
{
	//��Ϣ�ӿ�
public:
	//ͷ����
	virtual int __cdecl GetFaceWidth()=NULL;
	//ͷ��߶�
	virtual int __cdecl GetFaceHeight()=NULL;
	//ͷ����Ŀ
	virtual WORD __cdecl GetFaceItemCount()=NULL;

	//�滭�ӿ�
public:
	//�滭ͷ��
	virtual void __cdecl DrawFaceItem(CDC * pDC, int nXPos, int nYPos, WORD wFaceID)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//ͷ�����������
class CUserFaceResHelper : public CTempldateHelper<IUserFaceRes>
{
	//��������
public:
	//���캯��
	CUserFaceResHelper(void) : CTempldateHelper<IUserFaceRes>(IID_IUserFaceRes,
		VER_IUserFaceRes,USER_FACE_DLL_NAME,TEXT("CreateUserFaceRes"))
	{
	}
};

//////////////////////////////////////////////////////////////////////////

//ͷ��ؼ�������
class CFaceControlHelper : public CTempldateHelper<IFaceControl>
{
	//��������
public:
	//���캯��
	CFaceControlHelper(void) : CTempldateHelper<IFaceControl>(IID_IFaceControl,
		VER_IFaceControl,USER_FACE_DLL_NAME,TEXT("CreateFaceControl"))
	{
	}
};

//////////////////////////////////////////////////////////////////////////

#endif