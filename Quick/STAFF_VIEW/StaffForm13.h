#pragma once


// CStaffPage13 대화 상자입니다

typedef struct {
	long nCompany;
	int nMNo;
	int nWorkState;
	COleDateTime dtJobStart;
	COleDateTime dtJobEnd;
	COleDateTime dtAttend;
	COleDateTime dtLeave;
	COleDateTime dtWorkStateDate;
	COleDateTime dtAllocateLimitDate;
	COleDateTime dtInsuranceStart;
	COleDateTime dtInsuranceEnd;
	int nLockTime;
	int nLockCount;
	int nLockTime4MyOrder;
	int nLockCount4MyOrder;
	int nLockTime4OCOrder;
	int nLockCount4OCOrder;
	int nReleaseMin;
	BOOL bUseSMS;
	BOOL bInsurance;
	BOOL bAllocateLimit;
	long nPanaltyTypeShowOrder;

	BOOL bCheckInsurance;
	BOOL bEnableCancel;
	BOOL blimitTodayCharge;

	long nElapseLimitAllocateLocal;
	long nElapseLimitPickupLocal;
	long nElapseLimitAllocateGlobal;
	long nElapseLimitPickupGlobal;
} RIDER_INFO_NEW;


class CStaffPage13 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage13)

public:
	CStaffPage13();
	virtual ~CStaffPage13();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAFF_PAGE13 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

protected:

	CString m_strMNo;
	CString m_strID;
	CString m_strName;
	CString m_strPhone;
	CString m_strMP;
	CString m_strSSN1;
	CString m_strSSN2;
	CString m_strAddress;
	CString m_strMemo;
	COleDateTime m_dtEnter;
	COleDateTime m_dtOut;
	COleDateTime m_dtAttend;
	COleDateTime m_dtLeave;

public:
	BOOL ReConFirm(long nCount);
	void ModifyPopup();
	void InitControl();
	void RefreshList();
	BOOL DoEmploy();
	void DeleteAllItems();
	BOOL UpdateWorkTime_Sub(RIDER_INFO_NEW *ri, COleDateTime dtStart, COleDateTime dtEnd);
	void UpdateWorkState(BOOL bWorkState);
	BOOL UpdateWorkState_sub(RIDER_INFO_NEW *ri, CString sWorkMemo, BOOL bWorkState);
	void UpdateShareLimit(long nPanaltyTypeShowOrder);
	BOOL UpdateShareLimit_sub(RIDER_INFO_NEW *ri, long nPanaltyTypeShowOrder);
	void RefreshListOne(RIDER_INFO_NEW *ri, CXTPGridRecord *pRecord);
	void RefreshListSub(CMkRecordset *pRs, RIDER_INFO_NEW *ri, CXTPGridRecord *pRecord);
	void UpdateLockLimit(BOOL bApply);
	BOOL UpdateLockLimit_sub(RIDER_INFO_NEW *ri, long nLock, long nCount);
	void UpdateTimeLimit(BOOL bApply);
	BOOL UpdateTimeLimit_sub(RIDER_INFO_NEW *ri, COleDateTime dtDate, long nMinute, BOOL bApply);
	void UpdateServiceRentLimit(BOOL bApply);
	BOOL UpdateServiceRentLimit_sub(RIDER_INFO_NEW *ri, BOOL bApply);
	void ChangeAllocType(long nType);
	BOOL ChangeAllocType_sub(RIDER_INFO_NEW *ri, long nType);
	void UpdateElapseLimitLocal(BOOL bApply);
	BOOL UpdateElapseLimitLocal_sub(RIDER_INFO_NEW *ri, long nAllocate, long nPickup);
	void UpdateElapseLimitGlobal(BOOL bApply);
	BOOL UpdateElapseLimitGlobal_sub(RIDER_INFO_NEW *ri, long nAllocate, long nPickup);
	void ApplyRiderInsurance(BOOL bApply);
	BOOL ApplyRiderInsurance_sub(RIDER_INFO_NEW *ri, BOOL bApply);

	BOOL UpdateInsuranceDate_sub(RIDER_INFO_NEW *ri, COleDateTime dtStart, COleDateTime dtEnd);
	BOOL UpdateInsuranceCompany_sub(RIDER_INFO_NEW *ri, CString sInsCompany, CString sInsNumber);

	CXTPGridSelectedRows* GetSelectRiderRows();
	//	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnViewExcel();
	afx_msg void OnWorkStop();
	afx_msg void OnWorkOk();
	afx_msg void OnMenuMsg();

	afx_msg void OnWorkTime();
	afx_msg void OnAllocPDA();
	afx_msg void OnAllocSMS();
	afx_msg void OnShareLimit0();
	afx_msg void OnShareLimit1();
	afx_msg void OnShareLimit2();
	afx_msg void OnLockApply();
	afx_msg void OnLockNotApply();
	afx_msg void OnTimeLimitApply();
	afx_msg void OnTimeLimitNotApply();
	afx_msg void OnServiceRentLimitApply();
	afx_msg void OnServiceRentLimitNotApply();
	afx_msg void OnElapseLimitAllocateLocalApply();
	afx_msg void OnElapseLimitAllocateLocalNotApply();
	afx_msg void OnElapseLimitAllocateGlobalApply();
	afx_msg void OnElapseLimitAllocateGlobalNotApply();
	afx_msg void OnInsuranceApply();
	afx_msg void OnInsuranceNotApply();
	afx_msg void OnInsuranceDate();
	afx_msg void OnInsuranceCompany();
	

	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedAllapplyBtn();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public :

	int m_nANo;
	int m_nItem;
	BOOL m_bInsurance;
	BOOL m_bCancelCount;
	CStringArray m_stData;
	CFlatEdit2 m_RiderEdit;
	CString m_strRider;
	CString m_sPenalty;
	CString m_sMount;
	CString m_sInsurance;
	CXTPListCtrl2 m_List;

	CButton m_btnAllSearch;
	CButton m_btnModify;
	CButton m_btnAllAppy;
	CButton m_btnLimittOff;

	CMyStatic m_stcAmount;
	CMyStatic m_stcInsurance;
	CMyStatic m_stcCancelCount;
	CMyStatic m_stcSearchWord;
};
