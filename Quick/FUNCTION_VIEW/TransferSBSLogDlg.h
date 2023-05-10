#pragma once


// CTransferSBSLogDlg 대화 상자입니다.


class CTransferSBSLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CTransferSBSLogDlg)

public:
	CTransferSBSLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTransferSBSLogDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRANSFER_SBS_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnData;

	CXTPListCtrl55 m_lstReport;

	void RefreshList();
	CString GetTransferType(long nType);
	afx_msg void OnBnClickedRefreshBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedCancel();
};
