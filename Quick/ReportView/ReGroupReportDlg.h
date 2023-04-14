#pragma once

class CReGroupReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CReGroupReportDlg)

public:
	CReGroupReportDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CReGroupReportDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RE_GROUP_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
