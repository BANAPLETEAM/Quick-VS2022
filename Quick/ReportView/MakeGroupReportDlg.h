#pragma once

class CMakeGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMakeGroupReportDlg)

public:
	CMakeGroupReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMakeGroupReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAKE_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnChangeDate();
	void RefreshList();
	CString GetReportState(long nReportState);
	BOOL CheckDate(COleDateTime dtFrom, COleDateTime dtTo, BOOL bContiune = FALSE, long nRow = 0);

	afx_msg void OnBnClickedMakeBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	
	CXTPListCtrl21 m_lstReport;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_btnDate;

	BOOL m_bRefresh;
	CString m_strGNoList;
	long m_nGNo;
};
