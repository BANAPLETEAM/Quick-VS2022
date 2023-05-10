
#define USER_NAME "dataserver"
#define USER_PASS "dataserver4163"

#define FTP_IP "211.172.242.163"
#define FTP_URL_ID_PICTURE "/mms"

#include "afxinet.h"

class CFileUpload 
{
public:
	CFileUpload(void);
	~CFileUpload(void);

private:
	CInternetSession m_session;
	CFtpConnection *m_pConnection;
	CFtpFileFind *m_pFileFind;

	CString m_strRemote;

public:
	void SetConnectInfo(CString strIP, CString strUrl, CString strUserName, CString strPassword);
	BOOL UploadFile(CString &strLocalFileName);
	BOOL DeleteFile(long nANo);
};
