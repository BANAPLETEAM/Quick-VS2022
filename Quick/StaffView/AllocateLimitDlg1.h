#pragma once



class CAllocateLimitDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateLimitDlg1)

public:
	CAllocateLimitDlg1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocateLimitDlg1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLOCATE_LIMIT_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	long m_nRiderCompany;
	int m_nRNo;

public:
	afx_msg void OnBnClickedIdcancel();
	afx_msg void OnBnClickedAutoChk();
	afx_msg void OnBnClickedBigAutoChk();
	afx_msg void OnBnClickedDamaChk();
	afx_msg void OnBnClickedRaboChk();
	afx_msg void OnBnClickedBanChk();
	afx_msg void OnBnClickedTruckChk();
	afx_msg void OnBnClickedAllChk();
	afx_msg void OnBnClickedIdok();
	afx_msg void OnBnClickedCheckTimelimit();
	afx_msg void OnBnClickedCheckInsurance();
	afx_msg void OnBnClickedCheckServicestop();
	afx_msg void OnBnClickedCheckAllocatelimit();	
	afx_msg void OnBnClickedCheckOtherOrderAllocatelimit();
	afx_msg void OnBnClickedCheckMyOrderAllocatelimit();

	BOOL ModfiyProcess();
	BOOL CheckData();
	void CheckAll();
	void InitData();


	void InitControl();	

	ST_RIDER_INFO_ALLOCATE m_stRiderAllocate;

	CComboBox m_cmbLockTime;
	CComboBox m_cmbLockCount;
	CComboBox m_cmbLockTime4OCOrder;
	CComboBox m_cmbLockCount4OCOrder;
	CComboBox m_cmbLockTime4MyOrder;
	CComboBox m_cmbLockCount4MyOrder;
	CComboBox m_cmbAllocateRelease;	
	CComboBox m_cmbWorkStopMemo;
	CComboBox m_cmbShareLimit;
	CComboBox m_cmbElapseLimitAllocateLocal;
	CComboBox m_cmbElapseLimitPickupLocal;
	CComboBox m_cmbElapseLimitAllocateGlobal;
	CComboBox m_cmbElapseLimitPickupGlobal;

	CButton m_chkInsurance;	
	CButton m_chkLock;
	CButton m_chkJobStop;
	CButton	m_chkAllocate;
	CButton m_chkJobTime;
	CButton m_chkServiceRentLimit;	
	CButton m_chkLock4OCOrder;	
	CButton m_chkLock4MyOrder;
	CButton m_chkAuto;
	CButton m_chkBigAuto;
	CButton m_chkDama;
	CButton m_chkRabo;
	CButton m_chkBan;
	CButton m_chkTruck;
	CButton m_chkAll;

	CDateTimeCtrl m_dtpInsuranceStart;
	CDateTimeCtrl m_dtpInsuranceEnd;
	CDateTimeCtrl m_dtpJobStop;
	CDateTimeCtrl m_dtpAllocateTime;
	CDateTimeCtrl m_dtpJobStart;
	CDateTimeCtrl m_dtpJobEnd;
	CDateTimeCtrl m_dtpAllocateDate;
	CDateTimeCtrl m_dtpJobStopTime;

	CFlatEdit2 m_edtInsuranceCompany;
	CFlatEdit2 m_edtInsuranceID;

	CStatic m_stcJobTime;
	CMyStatic m_Static5;
	CMyStatic m_Static6;
	CMyStatic m_Static7;
	CMyStatic m_Static8;
	CMyStatic m_Static9;
	CMyStatic m_Static10;
	CMyStatic m_Static11;
	CMyStatic m_Static12;
	CMyStatic m_Static13;
	CMyStatic m_Static14;
	CMyStatic m_Static15;
	CMyStatic m_Static21;
	CMyStatic m_Static23;
	CMyStatic m_Static24;
	CMyStatic m_Static25;
};


