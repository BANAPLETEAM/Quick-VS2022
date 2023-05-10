#pragma once

// CAddRiderShareInfoDlg 대화 상자입니다.

class CAddRiderShareInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddRiderShareInfoDlg)

public:
	CAddRiderShareInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddRiderShareInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_RIDER_SHARE_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
