#pragma once
 
class CRcpView;

// COtherRiderDlg 대화 상자입니다.

class COtherRiderDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COtherRiderDlg)

public:
	COtherRiderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COtherRiderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OTHER_RIDER_ALLOCATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedFindBtn();
	afx_msg void OnBnClickedAllocateBtn();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedColseBtn();

	CRcpView *m_pRcpView;
	CWnd *m_pParent;
	CXTPListCtrl2 m_lstReport;

	CFlatEdit2 m_edtMNo;

	CButton m_btnFind;
	CButton m_btnAllocate;
	CButton m_btnClose;

	long m_nRiderCompany;
	long m_nCompany;
	long m_nRNo;
	long m_nTNo;

	long m_nDeposit;
	long m_nState;
	BOOL m_bToRcpView;
public:
	CString GetEtc(long nOrderDeposit, long nRiderBalance, long nDepositType, long nOCompany, long nRCompany, long nWorkState);
 };
