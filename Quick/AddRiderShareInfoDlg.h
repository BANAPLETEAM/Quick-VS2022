#pragma once

// CAddRiderShareInfoDlg ��ȭ �����Դϴ�.

class CAddRiderShareInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddRiderShareInfoDlg)

public:
	CAddRiderShareInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddRiderShareInfoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_RIDER_SHARE_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedShowRiderInfoBtn();
	afx_msg void OnBnClickedOkBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CFlatEdit2 m_edtRNo;
	CFlatEdit2 m_edtRider;
	CFlatEdit2 m_edtEtc;

	long m_nRiderCompany;
	long m_nRNo;

	CString m_strRName;
	CString m_strMsg;	
};
