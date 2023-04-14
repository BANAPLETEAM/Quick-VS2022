#pragma once

#include "RcpDlg.h"
#include "afxwin.h"
#include "RcpPlaceInfo.h"
#include "afxdtctl.h"
#include "FlatStatic.h"
#include "FlatComboBoxInsung.h"
#include "FlatButton.h"
#include "MyTitleStatic.h"

class ChistoryInsungDlg;
// CRcpInsungDlg 대화 상자입니다.
typedef struct 
{
	long nTelID;
	CString strTel;
	CString strDepart;
	CString strManager;

} ST_PHONE_INFO;


#define PAY_TYPE_CONTROL_COUNT 6
#define CAR_TYPE_CONTROL_COUNT 7
#define WAY_TYPE_CONTROL_COUNT 3
#define RUN_TYPE_CONTROL_COUNT 4 

enum {TYPE_PAY, TYPE_CAR, TYPE_WAY, TYPE_RUN};



class CRcpInsungDlg : public CRcpDlg
{
	DECLARE_DYNAMIC(CRcpInsungDlg)

public:
	//CRcpInsungDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	CRcpInsungDlg();
	virtual ~CRcpInsungDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RCP_INSUNG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brSystem;
	CBrush m_brPink;
	CBrush m_brWhite;
	CBrush m_brOrange;
	CBrush m_brBlue;
	CBrush m_brRed;
	CBrush m_brYellow;
	CBrush m_btGreen;
	CBrush m_btGreen2;
	CFont m_fntBold;
	CFont m_fntLarge;

	ChistoryInsungDlg *m_pHistoryInsung;


	afx_msg LONG OnInsungCustomerOk(WPARAM wParam, LPARAM lParam);
	void GetCRect(CWnd *pWnd, CRect &rcClient);
	long GetTodayCount();

	void DrawLeftBox(CDC *pDC);
	void DrawRightBox(CDC *pDC);
	void RepositionLeftControls();
	void RepositionRightControls();
	void MoveSameLine(CWnd *pWnd, CWnd *pNeighborX, CWnd *pNeighborY, int nAddCX = 0, int nAddCY = 0, int nOffsetX = 0, int nOffsetY = 0);
	CString GetDisplayDongAndAddress(long nDongID, CString strDong, CString strAddress);
	void SearchDong(long nType);
	static void GetJibunPos(long nDongID, long nRoadID, long nRoadSubID, long Jibun1, long nJibun2, long &nPosX, long &nPosY);
	void OpenInsungCustomerDlg(long nPlaceType);
	
	CBrush* GetOrderBrush();

	afx_msg void OnBnClickedSignBtn();

	
	CStatic m_stcStart;
	CFlatButton m_btnChangeStartDest;
	virtual BOOL OnInitDialog();
	void InsertDongInfo(CRcpPlaceInfo *pPlace, long nDongID);

	void DeleteOphoneCombo();
	void FIllOrderCombo();
	void MakeStartStatic();
	void SearchCustomer(long nType);
	void SearchPoi(long nType);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void ChangeRcpDlgSize(BOOL bOriginal, BOOL bForceChange = FALSE);
	afx_msg void OnEnSetfocusStartEdit();
	afx_msg void OnBnClickedOrderCustomerDlgBtn();
	CFlatComboBoxInsung m_cmbEtc;
	afx_msg void OnBnClickedEtcAddBtn();
	afx_msg void OnCbnSelchangeEtcCombo();
	void InitEtcCombo();

	virtual void SetButtonShowHide();
	virtual void OnInitialUpdate();
	virtual void ShowCustomerInnerMemo(CString strMemo);

	void SetCheckOptionControl(long nType, long nSubType);
	long GetTypeControl(long nType, long nSubType);
	long* GetTypeControlItem(long nType);
	long GetTypeControlCount(long nType);

	void SetRcpTimeControl(COleDateTime dtTime);

	virtual void SetCarTypeNew(long nCarType);
	virtual long GetCarTypeNew();
	virtual void SetPayTypeNew(long nPayType);
	virtual long GetPayTypeNew();
	virtual void SetWayTypeNew(long nWayType);
	virtual long GetWayTypeNew();
	virtual void SetRunTypeNew(long nRunType);
	virtual long GetRunTypeNew();

	virtual void ChangeDistance();
	virtual void DisplayRiderInfo();
	virtual BOOL IsReserve();
	virtual BOOL ReserveCheck();
	virtual long GetReleaseStateDB();
	virtual void SetReserveState(COleDateTime dtReserve, long nReserveAfter, long nReserveReleaseMin);
	virtual void InitReserveState();

	virtual COleDateTime GetReserveTime();
	virtual long GetReleaseMin();
	CString GetReserveTimeString();

	CFlatButton m_rdoPayType0;
	CFlatButton m_rdoPayType1;
	CFlatButton m_rdoPayType2;
	CFlatButton m_rdoPayType3;
	CFlatButton m_rdoPayType4;
	CFlatButton m_rdoPayType7;

	CFlatButton m_rdoCarType0;
	CFlatButton m_rdoCarType2;
	CFlatButton m_rdoCarType3;
	CFlatButton m_rdoCarType4;
	CFlatButton m_rdoCarType5;
	CFlatButton m_rdoCarType6;
	CFlatButton m_rdoCarType9;

	CFlatButton m_rdoWayType0;
	CFlatButton m_rdoWayType1;
	CFlatButton m_rdoWayType2;

	CFlatButton m_rdoRunType0;
	CFlatButton m_rdoRunType1;
	CFlatButton m_rdoRunType2;
	CFlatButton m_rdoRunType4;
	afx_msg void OnBnClickedSearchRiderBtn();
	CFlatButton m_chkReserve;
	CDateTimeCtrl m_dtpReserveData;
	CDateTimeCtrl m_dtpReserveTime;
	CFlatEditInsung m_edtReleaseMin;
	CFlatComboBoxInsung m_cmbCustomerMemo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CStatic m_stcTNoTitle;
	CStatic m_stcStateTitle;
	CStatic m_stcWNameTitle;
	CStatic m_stcRcpTime;
	CStatic m_stcBranchRight;
	CStatic m_stcOrder;
	CStatic m_stcOrderPhone;
	CFlatComboBoxInsung m_cmbOrderPhone;
	CButton m_btnStartAddress;
	CFlatButton m_btnStartClear;
	CFlatButton m_btnDestClear;
	CFlatButton m_btnDestToOName;
	CButton m_btnDestAddress;
	CFlatStatic m_stcDistanceTitle;
	CFlatStatic m_stcDistance;
	CFlatButton m_chkUseCharge;
	CFlatButton m_chkGI;
	CButton m_btnChargeStat;
	CStatic m_stcRcpTitle;
	CStatic m_stcReserveRelease;
	CStatic m_stcSMSTitle;
	CFlatComboBoxInsung m_cmbSMS;
	CStatic m_stcEtc;
	CButton m_btnEtcAdd;
	CFlatButton m_btnEtcDelete;
	CFlatEditInsung m_edtCardInfo;
	CFlatEditInsung m_edtCardInfo2;
	CFlatStatic m_stcCardTitle;
	CFlatButton m_chkTrans;
	CFlatButton m_chkTaxSheet;
	CFlatStatic m_stcKM;
	CFlatEditInsung m_edtAllocDistance;
	CFlatStatic m_stcAllocDistanceTitle;
	CStatic m_stcRiderNoTitle;
	CStatic m_stcRiderCompanyTitle;
	CStatic m_stcRiderPhoneTitle;
	CStatic m_stcRiderGroup;
	CFlatButton m_chkCargoShare;
	CFlatButton m_chkNoFee;
	CStatic m_stcItemType;
	CStatic m_stcChargeType;
	CStatic m_stcPayTypeTitle;
	CStatic m_stcCarTypeTitle;
	CStatic m_stcWayTypeTitle;
	CStatic m_stcRunTypeTitle;
	CStatic m_stcChargeBasic;
	CStatic m_stcChargeAdd;
	CStatic m_stcChargeDis;
	CStatic m_stcChargeTrans;
	CStatic m_stcChargeSum;
	CStatic m_stcChargeDriving;
	CStatic m_stcRider;
	CFlatButton m_chkSaveDest;

	BOOL m_bInsertColumn;

	void InsertListColumn();
	void InitLeftControls();
	void InitRightControls();
	afx_msg void OnStnClickedStartAddressStatic();
	afx_msg void OnStnClickedDestAddressStatic();
	virtual void ShowUsageHistory(BOOL bRefresh = FALSE, BOOL bRcpDlgForceSizing = FALSE);

	
	CButton m_btnRiderInfo;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnCbnKillfocusOrderPhoneCombo();
	afx_msg void OnCbnSelchangeOrderPhoneCombo();
	CButton m_btnAllocate;
	CButton m_btnRcp;
	CButton m_btnRcpCancel;
	CButton m_btnRcpWait;
	CButton m_btnCancel;
	CButton m_btnPrint;
	afx_msg void OnBnClickedAllocateBtn();
	afx_msg void OnBnClickedRcpBtn();
	afx_msg void OnBnClickedRcpCancelBtn();
	afx_msg void OnBnClickedRcpWaitBtn();
	afx_msg void OnBnClickedCompleteBtn();
	afx_msg void OnBnClickedCustomerChargeBtn2();
	afx_msg void OnBnClickedChangeStartDestBtn();
	afx_msg void OnBnClickedDestToOnameBtn();
	void ChangeRcpState();
	
	CButton m_btnOrderCustomerDlg;
	CMyTitleStatic m_stcCustsomerInfo;
	afx_msg virtual void OnTimer(UINT_PTR nIDEvent);
	CFlatEditInsung m_edtRiderNo;
	CFlatEditInsung m_edtRiderCompany;
	CFlatEditInsung m_edtRiderPhone;
	afx_msg void OnBnClickedRiderInfoBtn();
	afx_msg void OnBnClickedRiderSearchBtn();
	afx_msg void OnBnClickedPayTypeRadio();
	CStatic m_stcHelpStatic;
	afx_msg void OnBnClickedEtcDeleteBtn();
	
	afx_msg void OnBnClickedNoFeeCheck();
	afx_msg void OnBnClickedPickup();	
	afx_msg void OnBnClickedStartClearBtn();
	afx_msg void OnBnClickedDestClearBtn();


	CString GetOrderPhoneString(ST_PHONE_INFO *st);
	afx_msg void OnBnClickedCustomerChargeBtn();
	afx_msg void OnBnClickedCustomerSearchBtn();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnMove(int x, int y);
	afx_msg void OnBnClickedClientShareOrderCheck();

	class CInsungCustomerDlg *m_pInsungCustomerDlg;

	CRcpPlaceInfo *m_pPlaceCustomer;
	CFlatComboBoxInsung m_cmbTruckType;
	afx_msg void OnBnClickedCarTypeRadio();
	afx_msg void OnCbnSelchangeTruckTypeCombo();
	void SetCheckOptionControlCarType(long nCarType);
};
