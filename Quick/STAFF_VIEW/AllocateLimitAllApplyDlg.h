#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"

#include "afxcmn.h"
#include "afxcoll.h"

#include "ColorListCtrl.h"


struct KEYDATA
{
	long lCode;
	int	 nMno;
};

typedef map<std::pair<long,long>, long> RIDER_NO_MAP;
// CAllocateLimitAllApplyDlg 대화 상자입니다.

class CAllocateLimitAllApplyDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateLimitAllApplyDlg)

	
public:
	CAllocateLimitAllApplyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocateLimitAllApplyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLOCATE_LIMIT_ALLAPPLY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
protected:
	KEYDATA *m_pkey;
public:
	RIDER_NO_MAP m_map;
	
	


	CButton m_chkSms;
	
	
	CButton m_chkJobTime;
	CDateTimeCtrl m_dtpJobStart;
	CDateTimeCtrl m_dtpJobEnd;
	COleDateTime m_dtJobStart;
	COleDateTime m_dtJobEnd;
	

	CButton m_chkJobStop;
	CDateTimeCtrl m_dtpJobStop;
	COleDateTime m_dtJobStop;
	CComboBox m_cmbWorkStopMemo;

	CButton m_chkAuto;
	CButton m_chkBigAuto;
	CButton m_chkDama;
	CButton m_chkRabo;
	CButton m_chkBan;
	CButton m_chkTruck;
	CButton m_chkAll;

	CButton m_chkOrder;
	CButton m_chkLock;
	CButton m_chkMyOrderLock;
	CButton m_chkOtherOrderLock;
	CComboBox m_cmbLockTime;
	CComboBox m_cmbLockCount;
	CString m_sLockTime;
	CString m_sLockCount;

	CComboBox m_cmbMyOrderLockTime;
	CComboBox m_cmbMyOrderLockCount;
	CString m_sMyOrderLockTime;
	CString m_sMyOrderLockCount;

	CComboBox m_cmbOtherOrderLockTime;
	CComboBox m_cmbOtherOrderLockCount;
	CString m_sOtherOrderLockTime;
	CString m_sOtherOrderLockCount;

	CButton m_chkAllocate;
	CDateTimeCtrl m_dtpAllocateDate;
	CDateTimeCtrl m_dtpAllocateTime;
	CComboBox m_cmbReleaseMin;
	COleDateTime m_dtAllocateDate;
	COleDateTime m_dtAllocateTime;
	CString m_sReleaseMin;
	
	
	CButton m_chkInsurance;
	CDateTimeCtrl m_dtpInsuranceStart;
	CDateTimeCtrl m_dtpInsuranceEnd;
	CEdit m_edtInsuranceCompany;
	CEdit m_edtInsuranceID;	
	COleDateTime m_dtInsuranceStart;
	COleDateTime m_dtInsuranceEnd;
	CString m_sInsuranceCompany;
	CString m_sInsuranceID;

	
	virtual BOOL OnInitDialog();	
	

	afx_msg void OnBnClickedIdok();

	afx_msg void OnBnClickedAutoChk();
	afx_msg void OnBnClickedBigAutoChk();
	afx_msg void OnBnClickedDamaChk();
	afx_msg void OnBnClickedRaboChk();
	afx_msg void OnBnClickedBanChk();
	afx_msg void OnBnClickedTruckChk();

	afx_msg void OnBnClickedCheckApplySms();
	afx_msg void OnBnClickedCheckWorktime();	
	afx_msg void OnBnClickedCheckOrder();
	afx_msg void OnBnClickedCheckAll();
	afx_msg void OnBnClickedCheckLock();
	afx_msg void OnBnClickedCheckMyOrderLock();
	afx_msg void OnBnClickedCheckOtherOrderLock();
	afx_msg void OnBnClickedCheckTimelimit();
	afx_msg void OnBnClickedCheckInsurance();
	afx_msg void OnBnClickedIdcancel();	
	afx_msg void OnBnClickedCheckServicestop();
	
	CButton m_rdoSmsApply;
	CButton m_rdoJobStopApply;
	CButton m_rdoLockApply;	
	CButton m_rdoMyOrderLockApply;	
	CButton m_rdoOtherOrderLockApply;	
	CButton m_rdoAllocateApply;
	CButton m_rdoInsuranceApply;
	
	afx_msg void OnBnClickedRadioJobstop();
	afx_msg void OnBnClickedRadioLocktimeApply();
	afx_msg void OnBnClickedRadioMyOrderLocktimeApply();
	afx_msg void OnBnClickedRadioOtherOrderLocktimeApply();
	afx_msg void OnBnClickedRadioAllocateApply();
	afx_msg void OnBnClickedRadioInsuranceApply();
	afx_msg void OnBnClickedRadioAllocateNoapply();
	afx_msg void OnBnClickedRadioInsuranceNoapply();
	afx_msg void OnBnClickedRadioLocktimeNoapply();
	afx_msg void OnBnClickedRadioMyOrderLocktimeNoapply();
	afx_msg void OnBnClickedRadioOtherOrderLocktimeNoapply();
	afx_msg void OnBnClickedRadioJobing();
	bool CheckData(void);
	bool ModifyProcess(void);
	int m_nAllocate;
	int m_nLockTime;
	int m_nMyOrderLockTime;
	int m_nOtherOrderLockTime;
	int m_nJobStop;
	int m_nSms;
	int m_nInsurance;
	int m_nServiceRentLimit;
	afx_msg void OnBnClickedRadioSmsApply();
	afx_msg void OnBnClickedRadioSmsNoapply();
	CButton m_rdoSelectApply;
	
	
	
	BOOL m_bSelectApply;
	bool m_bAllApply;

	afx_msg void OnBnClickedRadioSelectApply();
	//CListCtrl m_ListCtrl;
	CListCtrl m_ListCtrl;
	afx_msg void OnBnClickedRadioAllApply();
	
	void InitList();
	
	CWnd* m_pParentWnd;
	void SelectModifyProcess();
	void CheckAll();
	
	CButton m_chkServiceRentLimit;
	
	afx_msg void OnBnClickedRadioServiceRentLimitApply();
	afx_msg void OnBnClickedRadioServiceRentNoapply();
	CButton m_rdoServiceRentLimit;
	afx_msg void OnBnClickedCheckServiceRentLimit();
	CDateTimeCtrl m_dtpJobStopTime;
	COleDateTime m_dtJobStopTime;
	
	afx_msg void OnHdnItemclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	
	
	CButton m_TimeLimitChk;
	CComboBox m_ElapseLimitAllocateLocalCmb;
	CComboBox m_ElapseLimitAllocateGlobalCmb;
	CComboBox m_ElapseLimitPickupLocalCmb;
	CComboBox m_ElapseLimitPickupGlobalCmb;
	afx_msg void OnBnClickedTimeLimitCheck();
	CButton m_chkShareLimit;
	CComboBox m_cmbShareLimit;
	afx_msg void OnBnClickedCheckShareLimit();
};
