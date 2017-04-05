#pragma once

//�����˿�
class CHeapCard
{
	//���Ʊ���
protected:
	CPoint							m_ControlPoint;						//��׼λ��
	CSkinImage						m_ImageBack;						//��ԴͼƬ

	//�˿˱���
protected:
	WORD							m_wFullCount;						//ȫ����Ŀ
	WORD							m_wMinusHeadCount;					//ͷ����ȱ
	WORD							m_wMinusLastCount;					//β����ȱ	
	WORD							m_wMinusMiddlePos[10];				//�в���ȱ

	//��������
public:
	//���캯��
	CHeapCard();
	//��������
	virtual ~CHeapCard();

	//���ܺ���
public:
	//�滭�˿�
	void DrawCardControl(CDC * pDC);
	//�����˿�	
	bool SetCardData(WORD wMinusHeadCount, WORD wMinusLastCount, WORD wFullCount,WORD wAddMinusMiddleCount);	
	

	//�ؼ�����
public:	
	//��׼λ��
	void SetControlPoint(int nXPos, int nYPos) { m_ControlPoint.SetPoint(nXPos,nYPos); }
	// ���ñ���
	void ResetMinusMiddleCount(void);
};