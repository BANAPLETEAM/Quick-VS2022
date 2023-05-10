#pragma once

class CCaptureUpload
{
public:
	CCaptureUpload(void);
	~CCaptureUpload(void);

	UINT Run();

protected:
	BOOL CaptureImage();
	BOOL Upload();

	HWND m_hWnd;
	char *m_pImageBuffer;
	ULONG m_nFileSize;
};
 