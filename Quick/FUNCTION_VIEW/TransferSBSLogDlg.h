#pragma once


// CTransferSBSLogDlg ��ȭ �����Դϴ�.


class CTransferSBSLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CTransferSBSLogDlg)

public:
	CTransferSBSLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTransferSBSLogDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TRANSFER_SBS_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
