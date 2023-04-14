#pragma once


class CRiderDepositGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderDepositGroupDlg)

public:
	CRiderDepositGroupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderDepositGroupDlg();

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
	afx_msg void OnBnClickedCloseBtn();

	void RefreshGroupList();
	void RefreshDepositList();

	CXTPListCtrl2 m_lstGroup;
	CXTPListCtrl2 m_lstDeposit;

	BOOL m_bSelectMode;
	long m_nDepositRateGroup;
	CString m_strDepositRateGroupName;
	long  m_nCompany;
};
