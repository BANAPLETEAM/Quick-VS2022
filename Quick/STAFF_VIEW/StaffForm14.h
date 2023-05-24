#pragma once

#include "explorer.h"
#include "afxwin.h"
#include "afxdtctl.h"

#define CARD_COUNT 10

typedef map<pair<BOOL, long>, ST_RIDER_INFO*> RIDER_INFO_MAP;
typedef map<long, ST_RATE*> RATE_INFO_MAP;
// CStaffForm14 폼 뷰입니다.

class CRiderDepositLogDlg;

class CStaffForm14 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffForm14)

protected:
	CStaffForm14();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CStaffForm14();

public:
	enum { IDD = IDD_STAFF_PAGE14 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CRiderDepositLogDlg *m_pRiderDepositDlg;

	long GetCardID(long nID);
	long GetIndexFromCardID(long nID);
	afx_msg void OnCardNumber(UINT nFlag);
	afx_msg void OnCardInsertNew();
	afx_msg void OnCardRelease();
	afx_msg void OnRiderIncome();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedRiderConfidenceBtn();
	afx_msg void OnBnClickedLicenseQueryButton();
	afx_msg void OnBnClickedRiderPicInsertBtn();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedIncomeBtn();
	afx_msg void OnBnClickedMyCallRateTypeBtn();
	afx_msg void OnBnClickedOtherCallRateTypeBtn();
	afx_msg void OnCbnSelchangeIncomeCombo();
	afx_msg void OnBnClickedRiderPicInsertBtn2();
	afx_msg void OnBnClickedIncomeSettingBtn();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnEnChangeSaerchEdit();
	afx_msg void OnBnClickedPdaAllocateCheck();
	afx_msg void OnBnClickedSmsAllocateCheck();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);	
	afx_msg void OnWorkStop();
	afx_msg void OnWorkOk();
	afx_msg void OnMenuMsg();
	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedAllCheck();
	afx_msg void OnBnClickedAutoCheck();
	afx_msg void OnBnClickedBigAutoCheck();
	afx_msg void OnBnClickedDamaCheck();
	afx_msg void OnBnClickedRaboCheck();
	afx_msg void OnBnClickedBanCheck();
	afx_msg void OnBnClickedTruckCheck();
	afx_msg void OnCbnSelchangeBranchCombo();
	afx_msg void OnBnClickedMycallCheck();
	afx_msg void OnBnClickedOthercallCheck();
	afx_msg void OnCbnSelchangeCarTypeCombo();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedJobAddButton();
	afx_msg void OnBnClickedJobDeleteButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMenuAddJob(UINT nFlag);
	afx_msg void OnMenuDeleteJob(UINT nFlag);
	afx_msg void OnCbnSelchangeDepositTypeCombo1();
	afx_msg void OnChangeRiderColor();
	afx_msg void OnBnClickedRiderInfoLog();


	void UpdateCancelType(long nCancelType);
	void ChangeSSNColor();

	void OnCancelType0();
	void OnCancelType1();
	void OnCancelType2();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();

	ST_RIDER_INFO* GetCurSelRiderInfo(CXTPGridRecord *pRecord = NULL);
	void MakeContextMenu();
	void RefreshList();
	void DeleteMapData();
	void SetDataFromMap();
	void OnDeletePic();
	void OnShowDepositLog();
	void OnUploadPic();
	void ReLoadImage();
	BOOL GetRSData(CMkRecordset *pRs, ST_RIDER_INFO *pInfo, long nIndex, BOOL bInsert = TRUE);
	void RefreshOneRider(CXTPGridRecord *pRecord = NULL, BOOL bPopulate = TRUE);
	void MakeBranchCombo();
	BOOL UpdateUser();
	BOOL CheckLocal();
	void InitData();
	BOOL InsertUser();
	void ChangeWorkState(BOOL nWorkState);
	//void IncomeRider(long nCompany, long nRNo, CString strName);
	void IncomeRider(long nCompany, long nRNo, CString strName, long nIncome, CString strIncomeMemo, long nType, CXTPGridRecord *pRecord = NULL, BOOL bPopulate = FALSE);
	long GetDepositType();
	long GetAllocateType();
	long GetDepositAllocateType();
	void CheckAll();
	void SetDefaultDepositRate();
	void RefreshJobList();
	void InitControl();

	BOOL CheckRetireAble(int nRiderCompany, int nRNo, CString strSSN);

	void ShowDepositLog(BOOL bShow);
	RIDER_INFO_MAP m_map;
	RATE_INFO_MAP m_mapRate;

	CXTPListCtrl42 m_lstReport;
	CXTPListCtrl43 m_wndJobReport;

	CFlatEdit2 m_edtName;
	CFlatEdit2 m_edtRNo;
	CFlatEdit2 m_edtMp;
	CFlatEdit2 m_edtPhone;
	CFlatEdit2 m_edtRT;
	CFlatEdit2 m_edtPDA;
	CFlatEdit2 m_edtBankOwner;
	CFlatEdit2 m_edtBankName;
	CFlatEdit2 m_edtBankAccount;
	CFlatEdit2 m_edtMarketLine;
	CFlatEdit2 m_edtAddress;
	CFlatEdit2 m_edtMemo;
	CFlatEdit2 m_edtInnerMemo;
	CFlatEdit2 m_edtIncome;
	CFlatEdit2 m_edtIncomeMemo;
	CFlatEdit2 m_edtSearch;
	CFlatEdit2 m_edtMyCallRateType;
	CFlatEdit2 m_edtOtherCallRateType;
	CFlatEdit2 m_edtMaxWithDrawMoneyPerDay;
	CFlatEdit2 m_edtMinLeftMoneyForWithDraw;
	CFlatEdit2 m_edtDailyDepositCharge;
	CFlatEdit2 m_edtSSN1;
	CFlatEdit2 m_edtSSN2;
	CFlatEdit2 m_edtLicenceNo;
	CFlatEdit2 m_edtRtSerial;

	CExplorer m_Explorer;

	CDateTimeCtrl m_dtpEnter;
	
	CButton m_btnNew;
	CButton m_btnIncome;
	CButton m_chkPDAAllocate;
	CButton m_chkSmsAllocate;
	CButton m_chkAllocateLimit;
	CButton m_chkAuto;
	CButton m_chkBigAuto;
	CButton m_chkDama;
	CButton m_chkRabo;
	CButton m_chkTruck;
	CButton m_chkAll;
	CButton m_chkMyCall;
	CButton m_chkOtherCall;
	CButton m_chkWithDrawType;
	CButton m_chkNotShowRightOrder;
	CButton m_chkUseRiderTax;

	CComboBox m_cmbLicence;
	CComboBox m_cmbCarType;
	CComboBox m_cmbShareLimit;
	CComboBox m_cmbAllocateLimitMinute;
	CComboBox m_cmbAllocateLimitCount;
	CComboBox m_cmbWorkState;
	CComboBox m_cmbAllocGroup;
	CComboBox m_cmbIncome;
	CComboBox m_cmbDepositType;
	CComboBox m_cmbDepositAllocateType;
	CComboBox m_cmbConWorking;	
	CComboBox m_cmbBankID;
	CComboBox m_cmbBranch;

	CButton m_chkSedan;
	BOOL m_bSedan;

	BOOL m_bAuto;
	BOOL m_bBigAuto;
	BOOL m_bDama;
	BOOL m_bRabo;
	BOOL m_bTruck;
	BOOL m_bAll;
	BOOL m_bAddRiderMode;
	BOOL m_bNotShowRightOrder;
	BOOL m_bLastAdminTable;
	
	long m_nLastANo;
	long m_nMyCallRateType;
	long m_nOtherCallRateType;
	long m_nLicenceValid;

	int m_nArryID[100];

	COleDateTime m_dtEnter;	

	CString m_strName;
	CString m_strRNo;
	CString m_strMp;
	CString m_strPhone;
	CString m_strRT;
	CString m_strPDA;
	CString m_strBankOwner;
	CString m_strBankName;
	CString m_strBankAccount;
	CString m_strMarketLine;
	CString m_strSSN1;
	CString m_strSSN2;
	CString m_strLicenceNo;
	CString m_strAddress;
	CString m_strMemo;
	CString m_strInnerMemo;
	CString m_strIncome;
	CString m_strIncomeMemo;
	CString m_strSearch;
	CString m_strMyCallRateType;
	CString m_strOtherCallRateType;
	CString m_strDailyReportCharge;
	CString m_strRtSerial;

	CDateTimeCtrl m_dtlIns;
	COleDateTime m_dtIns;
	CComboBox m_cmbInsType;
	afx_msg void OnBnClicked6banCheck();
	CButton m_chkAutoAllocate;
	afx_msg void OnBnClickedChangeLogBtn();
	CFlatEdit2 m_edtTruckMyDepositRate;
	CFlatEdit2 m_edtTruckOtherDepositRate;
	CString m_strTruckMyDepositRate;
	CString m_strTruckOtherDepositRate;
	afx_msg void OnCbnSelchangeConWorkingCombo();

	CString m_strCardNumber[CARD_COUNT];
	CFlatEdit2 m_edtCardNumber;
	CFlatEdit2 m_edtCarNo;
	CString m_strCarNo;
	CFlatEdit2 m_edtAllocMinCharge;
	CString m_strAllocMinCharge;

	CButton m_cmbSearch;
	afx_msg void OnBnClickedInitLogBtn();
	afx_msg void OnBnClickedLoadInsuranceBtn();
	afx_msg void OnBnClickedInsRegisterCheck();
	CButton m_chkInsNotRegister;
	BOOL IsRiderInsOk(CString strSSN);
	BOOL LoadInsRegister(BOOL bRegister);
	void CheckLoadIns(CString strSSN, BOOL bRegister);
	BOOL CheckCarNo(CString strCarNo);

	BOOL InsertTRSRider();
	CComboBox m_cmbBusinessCar;
	afx_msg void OnEnChangeSsnEdit1();
	afx_msg void OnEnChangeSsnEdit2();
};


