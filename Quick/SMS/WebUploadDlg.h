#pragma once

// CWebUploadDlg ��ȭ �����Դϴ�.

class CWebUploadDlg : public CDialog
{
	DECLARE_DYNAMIC(CWebUploadDlg)

public:
	CWebUploadDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWebUploadDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WEB_UPLOAD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:

	CExplorer m_explorer;
	CString m_strURL;
	CString m_strResult;
	BOOL m_bAutoSelect;
	virtual BOOL OnInitDialog();	
	void BeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
};
