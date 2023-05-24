#pragma once

// CSMSDocViewDlg ��ȭ �����Դϴ�.

class CSMSDocViewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSMSDocViewDlg)

public:
	CSMSDocViewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSMSDocViewDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMS_VIEW_DOC_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
