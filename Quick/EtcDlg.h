#pragma once


// CEtcDlg ��ȭ �����Դϴ�.

class CEtcDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CEtcDlg)

public:
	CEtcDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEtcDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ETC_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEtc;
	CString m_strTitle;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
