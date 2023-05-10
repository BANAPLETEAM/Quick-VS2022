#pragma once

class CCheckGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCheckGroupReportDlg)

public:
	CCheckGroupReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCheckGroupReportDlg();
 
// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHECK_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString GetState(long nReportState);
	CString GetStateEtc(long nReportState);
	void RefreshList();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedHelpBtn();
	afx_msg void OnBnClickedMoveBtn();
	afx_msg void OnBnClickedCancelBtn();

	CXTPListCtrl20 m_lstReport;
	
	long m_nDstGNo;
	long m_nMemberCount;

	COleDateTime m_dtDate;

	CString m_strGNo;
	CString m_strNeedReReportID;
	
	CStatic m_stc1;
	CStatic m_stc2;

	CBitmapButton m_btnHelp;
};
