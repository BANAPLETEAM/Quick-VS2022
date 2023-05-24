#pragma once

// CSMSDocViewDlg 대화 상자입니다.

class CSMSDocViewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSMSDocViewDlg)

public:
	CSMSDocViewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSMSDocViewDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_VIEW_DOC_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()


public :
	CExplorer m_Explorer;
	CString m_strUrl;
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedZoomInBtn();
	afx_msg void OnBnClickedZoomOutBtn();
	void DocView();
	HRESULT GetPostData(CString strKey, LPVARIANT pvPostData);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
