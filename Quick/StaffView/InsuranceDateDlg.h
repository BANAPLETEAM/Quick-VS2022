#pragma once


// CInsuranceDateDlg 대화 상자입니다.

class CInsuranceDateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CInsuranceDateDlg)

public:
	CInsuranceDateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInsuranceDateDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INSURANCE_DATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	COleDateTime m_dtStart;
	COleDateTime m_dtEnd;
};
