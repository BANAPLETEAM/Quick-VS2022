#pragma once

class CReGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CReGroupReportDlg)

public:
	CReGroupReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CReGroupReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RE_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	long m_nGNo;
	long m_nApplyReportID;
	BOOL m_bRefresh;
	CXTPListCtrl2 m_Report;
	void RefreshList();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMakeBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void CheckReportAbil(long &nCount, BOOL &bHasBillCollection, CString &sID);
	CButton m_chkIncludeToday;
};
