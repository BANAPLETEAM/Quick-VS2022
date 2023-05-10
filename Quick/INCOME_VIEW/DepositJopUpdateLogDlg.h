#pragma once

class CDepositJopUpdateLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDepositJopUpdateLogDlg)

public:
	CDepositJopUpdateLogDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDepositJopUpdateLogDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DEPOSIT_JOB_UPDATE_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
