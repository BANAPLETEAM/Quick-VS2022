#pragma once

// CWebUploadDlg 대화 상자입니다.

class CWebUploadDlg : public CDialog
{
	DECLARE_DYNAMIC(CWebUploadDlg)

public:
	CWebUploadDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebUploadDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEB_UPLOAD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
