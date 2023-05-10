#pragma once


// CDepositJobDlg 대화 상자입니다.

class CDepositJobDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CDepositJobDlg)

public:
	CDepositJobDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDepositJobDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DEPOSIT_JOB_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMakeJobBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedGroupSettingButton();
	afx_msg void OnBnClickedUpdateLogBtn();
	afx_msg void OnBnClickedRiderLogBtn();
	virtual BOOL OnInitDialog();
	
	CXTPListCtrl32 m_List;
	CXTPListCtrl31 m_lstInclude;
	CXTPListCtrl31 m_lstNotInclude;

	ST_DEPOSIT_JOB *m_pDeposit;

	int m_nCompanyCode;
	BOOL m_bIntegrated;

	CFont *m_fontBig;
	CFont *m_fontSmall;

	CStatic m_stcDraw;

	CString GetDisplayDate(ST_DEPOSIT_JOB *st);
	CString GetLastPlayDate(BOOL bLastJobSuccess, COleDateTime dtLastJob);

	void DrawStcText(CDC *pDC, COLORREF rgbText, COLORREF rgbMainText, CString sDisplayName, CRect rc, long nType,  CFont *font);
	void RefreshList(void);	
	//void ReturnDepositFormula(CMakeDepositJobDlg dlg,int nDepositFormula);
	//void ReturnWorkState(CMakeDepositJobDlg dlg, int nWorkState);
	//void ReturnWorkTerm(CMakeDepositJobDlg dlg, int nWorkTerm);
	void RefreshIncludeList();
	void RefreshNotIncludeList();
	void DeleteMainList();
	void ChangeSelInfo();

	CString GetStringSms();
	CString GetStringEtc();
	CString GetStringUse();
	CString GetStringDate();
	CString GetStringMaker();
	CString GetStringMakeDate();
	CString GetStringWorkDate();
	CString GetStringSmsPhone();
	CString GetStringWorkState();
	CString GetStringWorkDateEnd();
	CString GetStringDepositType();

	afx_msg void OnNMclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnReportItemRClick(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnBnClickedSelectJobProcessButton();
	afx_msg void OnBnClickedUpdateJobBtn();
	afx_msg void OnBnClickedRefreshJobBtn();
	afx_msg void OnBnClickedDeleteJobBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnRefresh();
	afx_msg void OnEntryRider();
	afx_msg void OnJobMake();
	afx_msg void OnJobUpdate();
	afx_msg void OnJobDelete();
	afx_msg void OnJobPlay();
	afx_msg void OnShowHistory();
	afx_msg void OnBnClickedPlayJobBtn();
	afx_msg void OnBnClickedGroupInButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedGroupOutButton();
	afx_msg void OnBnClickedCancelButton();
};
