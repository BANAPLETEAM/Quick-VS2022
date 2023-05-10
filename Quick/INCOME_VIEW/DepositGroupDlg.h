#pragma once


class CDepositGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDepositGroupDlg)

public:
	CDepositGroupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDepositGroupDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DEPOSIT_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnReportItemGroupClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemGroupDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDepositClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedMakeGroupBtn();
	afx_msg void OnBnClickedUpdateGroupBtn();
	afx_msg void OnBnClickedDeleteGroupBtn();
	afx_msg void OnBnClickedUpdateDepositBtn();

	void RefreshGroupList();
	void RefreshDepositList();

	CXTPListCtrl2 m_lstGroup;
	CXTPListCtrl2 m_lstDeposit;

	BOOL m_bSelectMode;
	long m_nDepositRateGroup;
	CString m_sDepositRateGroupName;
};
