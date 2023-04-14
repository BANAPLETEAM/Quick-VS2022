#pragma once

class CDepositJopUpdateLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDepositJopUpdateLogDlg)

public:
	CDepositJopUpdateLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDepositJopUpdateLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DEPOSIT_JOB_UPDATE_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnEnChangeSearchEdit();

	void InitJopLogColumn();
	void RefreshJobLogList();
	void InitRiderLogColumn();
	void RefreshRiderLogList();

	CXTPListCtrl31 m_List;
	CFlatEdit2 m_edtSearch;

	BOOL m_bRiderLog;
	long m_nCompanyCode;
	BOOL m_bIntegrated;
};
