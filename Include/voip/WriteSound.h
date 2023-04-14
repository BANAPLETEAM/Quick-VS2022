#pragma once


#define WM_WRITESOUND_CREATEFILE    WM_USER+701
#define WM_WRITESOUND_WRITEDATA		WM_USER+702
#define WM_WRITESOUND_CLOSEFILE		WM_USER+703
#define WM_WRITESOUND_ENDTHREAD		WM_USER+704

#define SAMPLEWSEC 8000
// CWriteSound

class CWriteSound : public CWinThread
{
	DECLARE_DYNCREATE(CWriteSound)

protected:

	MMCKINFO riffblock,fmtblock,datablock;
	HMMIO m_hwrite;		
	WAVEFORMATEX waveformat;
//	CStdioFile log;

public:
	CWriteSound();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CWriteSound();

	virtual BOOL InitInstance();
	virtual int ExitInstance();


protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnCreateFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnWriteData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCloseFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEndThread(WPARAM wParam, LPARAM lParam);

};


