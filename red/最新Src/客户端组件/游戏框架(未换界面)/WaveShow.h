#pragma once

//#include <FilePackage.h>


class CWaveShow;
extern CWaveShow g_WaveShow;

struct tagWaveInfo
{
	int nEvent;
	char *szFile;
};

class CWaveShow
{
public:
	CWaveShow(void);
	virtual ~CWaveShow(void);
//
//public:
//	//��ȡ������Ϣ
//	bool SetScript(LPCSTR pszScript);
//
//	//���Ƶ�ǰWavPackageFile
//	bool SetWaveFile(LPCSTR pszWavPackageFile);
//
//	//���
//	bool Clear();
//
//
//	LPCSTR GetEventWaveFile(int nEvent);
//	LPCSTR GetEventWaveFile(int nEvent,char *szAuthorName);
//
//	bool PlayWav(int nEvent,char *szAuthorName);
//	bool PlayWav(int nEvent);
//
//	bool PlayWav(LPCTSTR pszSoundName);
//	
//
//private:
//	bool LexWaveInfo(char *pData);
//	bool GetWaveEvent(char *pData);
//private:
//	char *m_data;
//	CFilePackage m_fpack;
//	std::vector<tagWaveInfo*>	m_WaveInfo;
};
