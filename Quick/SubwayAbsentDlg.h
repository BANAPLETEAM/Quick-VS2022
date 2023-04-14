#pragma once


// CSubwayAbsentDlg 대화 상자입니다.

class CSubwayAbsentDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSubwayAbsentDlg)

public:
	CSubwayAbsentDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSubwayAbsentDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SUBWAY_ABSENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	long m_nCompany;
	long m_nRNo;

	CButton m_chkAbsent;
	CButton m_chkGetOff;
	CButton m_chkWaitTime;
	CFlatEdit2 m_edtLocation;
	afx_msg void OnBnClickedAbsentCheck();
	afx_msg void OnBnClickedGetOffCheck();
};
