#include "StdAfx.h"
#include "SkinImage.h"

/////////////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinImage::CSkinImage(void)
{
	m_nRefCount=0;
	m_bLoadAlways=false;
}

//��������
CSkinImage::~CSkinImage(void)
{
	Destroy();
}

//��������
int CSkinImage::LockResource()
{
	if (m_nRefCount==0)
	{
		if (m_LoadInfo.hResourceDLL==NULL) Load(m_LoadInfo.strFileName);
		else LoadFromResource(m_LoadInfo.hResourceDLL,m_LoadInfo.uResourceID);
		if (IsNull()) return 0;
	}
	return ++m_nRefCount;
}

//��������
int CSkinImage::UnLockResource()
{
	try
	{
		if (m_nRefCount>0) m_nRefCount--;
		if (m_nRefCount==0) Destroy();
	}
	catch (...) {}
	return m_nRefCount;
}

//�Ƿ����ü�����Ϣ
bool CSkinImage::IsSetLoadInfo()
{
	return ((m_LoadInfo.hResourceDLL)||(m_LoadInfo.strFileName.IsEmpty()==false));
}

//������ز���
bool CSkinImage::RemoveLoadInfo()
{
	m_LoadInfo.uResourceID=0;
	m_LoadInfo.hResourceDLL=NULL;
	m_LoadInfo.strFileName.Empty();
	return true;
}

//��ȡ���ز���
bool CSkinImage::GetLoadInfo(tagImageLoadInfo & LoadInfo)
{
	LoadInfo=m_LoadInfo;
	return IsSetLoadInfo();
}

//���ü��ز���
bool CSkinImage::SetLoadInfo(LPCTSTR pszFileName, bool bLoadAlways)
{
	//�������
	int nOldRefCount=m_nRefCount;
	bool bOldLoadAlways=m_bLoadAlways;

	//������Դ
	Destroy();
	m_nRefCount=0;
	m_bLoadAlways=bLoadAlways;

	//���ñ���
	m_LoadInfo.uResourceID=0;
	m_LoadInfo.hResourceDLL=NULL;
	m_LoadInfo.strFileName=pszFileName;

	//�ָ�����
	if (bOldLoadAlways) nOldRefCount--;
	if (m_bLoadAlways) nOldRefCount++;
	while (nOldRefCount>0)
	{
		nOldRefCount--;
		LockResource();
	};

	return true;
}

//���ü��ز���
bool CSkinImage::SetLoadInfo(UINT uResourceID, HINSTANCE hResourceDLL, bool bLoadAlways)
{
	//�������
	int nOldRefCount=m_nRefCount;
	bool bOldLoadAlways=m_bLoadAlways;

	//������Դ
	Destroy();
	m_nRefCount=0;
	m_bLoadAlways=bLoadAlways;
	m_LoadInfo.strFileName.Empty();

	//���ñ���
	m_LoadInfo.uResourceID=uResourceID;
	m_LoadInfo.hResourceDLL=hResourceDLL;

	//�ָ�����
	if (bOldLoadAlways) nOldRefCount--;
	if (m_bLoadAlways) nOldRefCount++;
	while (nOldRefCount>0)
	{
		nOldRefCount--;
		LockResource();
	};

	return true;
}

//͸���滭
bool CSkinImage::AlphaDrawImage(CDC * pDestDC, int xDest, int yDest, COLORREF crTrans)
{
	return AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,crTrans);
}

//͸���滭
bool CSkinImage::AlphaDrawImage(CDC * pDestDC, int xDest, int yDest, int cxDest, int cyDest, int xSrc, int ySrc, COLORREF crTrans)
{
	//Ч��״̬
	if (IsNull()) return false;
	//this->BitBlt(pDestDC->m_hDC,0,0,SRCCOPY);
	//return true;
	//���� DC
	CDC DCImage;
	DCImage.CreateCompatibleDC(pDestDC);
	DCImage.SelectObject(HBITMAP(*this));
	DCImage.SetBkColor(crTrans);
	DCImage.SetBkMode(TRANSPARENT);

	//��������ͼ
	CDC DCMask;
	CBitmap BMPMask;
	BMPMask.CreateBitmap(cxDest,cyDest,1,1,NULL);
	DCMask.CreateCompatibleDC(pDestDC);
	DCMask.SelectObject(&BMPMask);
	DCMask.BitBlt(0,0,cxDest,cyDest,&DCImage,xSrc,ySrc,SRCCOPY);

	//�滭Ŀ��ͼ
	CDC DCDest;
	CBitmap BMPDest;
	DCDest.CreateCompatibleDC(pDestDC);
	BMPDest.CreateCompatibleBitmap(pDestDC,cxDest,cyDest);
	DCDest.SelectObject(&BMPDest);
	DCDest.BitBlt(0,0,cxDest,cyDest,pDestDC,xDest,yDest,SRCCOPY);
	DCDest.BitBlt(0,0,cxDest,cyDest,&DCImage,xSrc,ySrc,SRCINVERT);
	DCDest.BitBlt(0,0,cxDest,cyDest,&DCMask,0,0,SRCAND);
	DCDest.BitBlt(0,0,cxDest,cyDest,&DCImage,xSrc,ySrc,SRCINVERT);
	pDestDC->BitBlt(xDest,yDest,cxDest,cyDest,&DCDest,0,0,SRCCOPY);

	//������Դ
	DCMask.DeleteDC();
	DCDest.DeleteDC();
	DCImage.DeleteDC();
	BMPMask.DeleteObject();
	BMPDest.DeleteObject();
	
	return true;
}

//͸���滭
bool CSkinImage::AlphaDrawImageEx(CDC * pDestDC, int xDest, int yDest, COLORREF crTrans)
{
	return AlphaDrawImageEx(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,crTrans);
}

//͸���滭
bool CSkinImage::AlphaDrawImageEx(CDC * pDestDC, int xDest, int yDest, int cxDest, int cyDest, int xSrc, int ySrc, COLORREF crTrans)
{
	//Ч��״̬
	if (IsNull()) return false;

	//���� DC
	CDC DCImage;
	DCImage.CreateCompatibleDC(pDestDC);
	DCImage.SelectObject(HBITMAP(*this));
	DCImage.SetBkColor(crTrans);
	DCImage.SetBkMode(TRANSPARENT);

	//��������ͼ
	CDC DCMask;
	CBitmap BMPMask;
	BMPMask.CreateBitmap(cxDest,cyDest,1,1,NULL);
	DCMask.CreateCompatibleDC(pDestDC);
	DCMask.SelectObject(&BMPMask);
	DCMask.BitBlt(0,0,cxDest,cyDest,&DCImage,xSrc,ySrc,SRCCOPY);

	//�滭Ŀ��ͼ
	pDestDC->BitBlt(xDest,yDest,cxDest,cyDest,pDestDC,xDest,yDest,SRCCOPY);
	pDestDC->BitBlt(xDest,yDest,cxDest,cyDest,&DCImage,xSrc,ySrc,SRCINVERT);
	pDestDC->BitBlt(xDest,yDest,cxDest,cyDest,&DCMask,0,0,SRCAND);
	pDestDC->BitBlt(xDest,yDest,cxDest,cyDest,&DCImage,xSrc,ySrc,SRCINVERT);

	//������Դ
	DCMask.DeleteDC();
	DCImage.DeleteDC();
	BMPMask.DeleteObject();
	
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

//���캯��
CImageHandle::CImageHandle(CSkinImage * pImageObject)
{
	m_pImage=NULL;
	AttachResource(pImageObject);
	return;
}

//��������
CImageHandle::~CImageHandle()
{
	DetchResource();
	return;
}

//����Դ
bool CImageHandle::AttachResource(IGDIResource * pImageObject)
{
	DetchResource();
	if (pImageObject)
	{
		CSkinImage * pSkinImage=(CSkinImage *)pImageObject;
		if (pImageObject->LockResource()>0)
		{
			m_pImage=pSkinImage;
			return true;
		}
	}
	return false;
}

//�����
bool CImageHandle::DetchResource()
{
	if (m_pImage) 
	{
		m_pImage->UnLockResource();
		m_pImage=NULL;
		return true;
	} 
	return false;
}

//�Ƿ��
bool CImageHandle::IsAttached()
{
	return (m_pImage!=NULL);
}

//�Ƿ���Ч
bool CImageHandle::IsResourceValid()
{
	return ((m_pImage)&&(m_pImage->IsNull()==false));
}

//��ȡ���
HBITMAP CImageHandle::GetBitmapHandle()
{
	if (IsResourceValid()==false) return NULL;
	return (HBITMAP)(*m_pImage);
}

/////////////////////////////////////////////////////////////////////////////////////////
