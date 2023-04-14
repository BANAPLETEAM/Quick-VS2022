
// #define USER_NAME "dataserver"
// #define USER_PASS "data@@server230"

#define FTP_IP "211.172.242.170"
#define FTP_IP2 "210.127.244.199"
#define FTP_URL_ID_PICTURE "/mms"
#define FTP_URL_ID_SMARTCALL "smartcall"

#include "afxinet.h"

class CSMSFileUpload
{
public:
	CSMSFileUpload(void);
	~CSMSFileUpload(void);

private:
	CInternetSession m_session;
	CFtpConnection *m_pConnection;
	CFtpFileFind *m_pFileFind;

	CString m_strRemote;
public:

	void SetConnectInfoSMS(CString strUrl);
	BOOL UploadSMSCallBackFile(CString strLocalFileName ,CString &strFileName,CString strOldFileName = "");
	BOOL SMSCallBackFileDelete(CString strDirectory ,CString strFileName);


	void SetConnectInfo(CString strIP, CString strUrl, CString strUserName, CString strPassword);
	BOOL UploadFile(CString &strLocalFileName, CString strNameString = "");
	BOOL DeleteFile(long nANo);
	CString m_strID;
	CString m_strPass;
};
