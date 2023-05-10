#pragma once

#include "MyGiveStatic.h"
#include "MyTakeStatic.h"
#include "MyReportPaintManager.h"
#include "KingoHttp.h"
#include "MyStaticRed.h"

#define MY_CALL_CASH 0 
#define OTHER_CALL_CASH 1
#define MY_CALL_CREDIT 2
#define MY_CALL_ONLINE 3
#define OTHER_CALL_CREDIT 4
#define OTHER_CALL_ONLINE 5

//class CIncomeForm7;


typedef map<long, ST_RIDER_CREDIT> RIDER_CREDIT_MAP;
typedef map<long, ST_RIDER_REPORT> RIDER_REPORT_MAP1;

//CMyTakeStatic //CMyGiveStatic

class CRiderReportOrderDlg;

class CRiderReportDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderReportDlg)

public:
	CRiderReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bInitList;
	long GetOrderType(long nShareCode1, long nRiderShareCode1, long nPayType);
	void InitData();
	void InitCharge();
	void RefreshCharge();
	long GetReportCharge(CXTPListCtrl2 *pList);	
	void InitReport(CXTPListCtrl2 *pList);
	long GetEditTextByLong(CFlatEdit2 *pEdit);
	void ReportComplete(BOOL bPrint);	
	void SaveEtcList(CXTPListCtrl2 *pList);
	void DeleteEtcList(CXTPListCtrl2 *pList); 
	void RefreshEtcList(CXTPListCtrl2 *pList, CString sEtcSum, CString sEtcChargeSum);
	void GetReportEtc(CXTPListCtrl2 *pList, CString &sEtc, CString &sEtcCharge);
	void FindNotAvailabilityRow(CXTPListCtrl2 *pList, long nIndex);
	void MakeMsg();
	void ApplyDT();
	void RefreshEtcListByRiderCredit();
	long GetReportEmtpyRow();
	CString GetRiderCredit();
	BOOL SendPDA(CString strMsg);
	BOOL SendSMS(CString strMsg);
	void SetTextStc();
	void CallCompleteReport();
	CString Print(BOOL bShow);
	BOOL MakeFile(CString strHtml,CString strFileName);

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedDeleteBtn2();
	afx_msg void OnBnClickedRefreshOrderBtn();
	afx_msg void OnBnClickedCompleteBtn();
	afx_msg void OnBnClickedPrintBtn();
	afx_msg void OnBnClickedApplicationBtn();
	afx_msg void OnBnClickedApplicationBtn2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemChange2(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedOpenBtn();
	afx_msg void OnBnClickedOpenBtn2();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick2(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedDeleteReportBtn();
	afx_msg void OnBnClickedOtherCallOnlineFeeBtn();
	afx_msg void OnBnClickedSaveOptionBtn();
	afx_msg void OnBnClickedMyCallCashWonBtn();
	afx_msg void OnBnClickedOtherCallCashWonBtn();
	afx_msg void OnBnClickedMyCallOnlineWonBtn();
	afx_msg void OnBnClickedOtherCallCreditWonBtn();
	afx_msg void OnBnClickedOtherCallOnlineWonBtn();
	afx_msg void OnBnClickedCashDeductingTaxFeeBtn();
	afx_msg void OnBnClickedAfterMyCallCreditOnlineDeductingTaxWonBtn();
	afx_msg void OnBnClickedBeforeMyCallCreditOnlineDeductingTaxWonBtn();
	afx_msg void OnBnClickedBeforeOtherCallCreditOnlineDeductingWonBtn();
	afx_msg void OnBnClickedAfterOtherCallCreditOnlineDeductingWonBtn();
	afx_msg void OnBnClickedCashMyCallDeductingTaxCheck();
	afx_msg void OnBnClickedOtherCallBeforeCheck();
	afx_msg void OnBnClickedOtherCallAfterCheck();
	afx_msg void OnBnClickedMyCallBeforeCheck();
	afx_msg void OnBnClickedMyCallAfterCheck();
	afx_msg void OnBnClickedCashOtherCallDeductingTaxCheck();
	afx_msg void OnEnChangeMyCallCashFeeEdit();
	afx_msg void OnEnChangeOtherCallCashFeeEdit();
	afx_msg void OnEnChangeCashDeductingTaxFeeEdit();
	afx_msg void OnEnChangeBeforeMyCallCreditOnlineDeductingTaxFeeEdit();
	afx_msg void OnEnChangeMyCallCreditFeeEdit();
	afx_msg void OnEnChangeMyCallOnlineFeeEdit();
	afx_msg void OnEnChangeOtherCallCreditFeeEdit();
	afx_msg void OnEnChangeOtherCallOnlineFeeEdit();
	afx_msg void OnEnChangeAfterOtherCallCreditOnlineDeductingTaxFeeEdit();
	afx_msg void OnBnClickedMyCallCreditWonBtn();
	afx_msg void OnEnChangeFixedDepositEdit();
	afx_msg void OnEnChangeAfterMyCallCreditOnlineDeductingTaxFeeEdit();
	afx_msg void OnEnChangeBeforeOtherCallAllCreaditOnlineDeductingTaxFeeEdit();
	afx_msg void OnEnChangeMsgEdit();
	afx_msg void OnEnChangeCouponPlusEdit();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedSaveBtn2();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSendBtn();

	CWnd *m_pParentWnd;
	CRiderReportOrderDlg *m_pRiderReportOrderDlg;
	RIDER_REPORT_MAP1 m_map;
	RIDER_CREDIT_MAP m_mapCredit;
	
	CFlatEdit2 m_edtMemo;
	CFlatEdit2 m_edtFixedDeposit;
	CFlatEdit2 m_edtReceiveCharge;
	CFlatEdit2 m_edtMyCallAllCashCount;
	CFlatEdit2 m_edtMyCallAllCashCharge;
	CFlatEdit2 m_edtMyCallApplyCashCount;
	CFlatEdit2 m_edtMyCallApplyCashCharge;
	CFlatEdit2 m_edtMyCallCashFee;
	CFlatEdit2 m_edtMyCallCashFeeTotal;
	CFlatEdit2 m_edtOtherCallAllCashCount;
	CFlatEdit2 m_edtOtherCallAllCashCharge;
	CFlatEdit2 m_edtOtherCallApplyCashCount;
	CFlatEdit2 m_edtOtherCallApplyCashCharge;
	CFlatEdit2 m_edtOtherCallCashFee;
	CFlatEdit2 m_edtOtherCallCashFeeTotal;
	CFlatEdit2 m_edtCashCallAllCount;
	CFlatEdit2 m_edtCashCallAllCharge;
	CFlatEdit2 m_edtCashFeeTotal;
	CFlatEdit2 m_edtLastMonth;
	CFlatEdit2 m_edtCashDeductingTaxFee;
	CFlatEdit2 m_edtCashDeductingTaxFeeTotal;
	CFlatEdit2 m_edtTakeTotal;
	CFlatEdit2 m_edtTakeTotal1;
	CFlatEdit2 m_edtMyCallAllCreditCount;
	CFlatEdit2 m_edtMyCallAllCreditCharge;
	CFlatEdit2 m_edtMyCallNotApplyCreditCount;
	CFlatEdit2 m_edtMyCallNotApplyCreditCharge;
	CFlatEdit2 m_edtMyCallApplyCreditCount;
	CFlatEdit2 m_edtMyCallApplyCreditCharge;
	CFlatEdit2 m_edtMyCallCreditFee;
	CFlatEdit2 m_edtMyCallCreditFeeTotal;
	CFlatEdit2 m_edtMyCallAllCreditOnlineCount;
	CFlatEdit2 m_edtMyCallAllCreditOnlineCharge;
	CFlatEdit2 m_edtMyCallNotApplyCreditOnlineCount;
	CFlatEdit2 m_edtMyCallNotApplyCreditOnlineCharge;
	CFlatEdit2 m_edtMyCallCreditOnlineFeeTotal;
	CFlatEdit2 m_edtMyCallAllOnlineCount;
	CFlatEdit2 m_edtMyCallAllOnlineCharge;
	CFlatEdit2 m_edtMyCallNotApplyOnlineCount;
	CFlatEdit2 m_edtMyCallNotApplyOnlineCharge;
	CFlatEdit2 m_edtMyCallApplyOnlineCount;
	CFlatEdit2 m_edtMyCallApplyOnlineCharge;
	CFlatEdit2 m_edtMyCallOnlineFee;
	CFlatEdit2 m_edtMyCallOnlineFeeTotal;
	CFlatEdit2 m_edtBeforeMyCallCreditOnlineDeductingTaxFee;
	CFlatEdit2 m_edtBeforeMyCallCreditOnlineDeductingTaxFeeTotal;
	CFlatEdit2 m_edtAfterMyCallCreditOnlineDeductingTaxFee;
	CFlatEdit2 m_edtAfterMyCallCreditOnlineDeductingTaxFeeTotal;
	CFlatEdit2 m_edtOtherCallAllCreditCount;
	CFlatEdit2 m_edtOtherCallAllCreditCharge;
	CFlatEdit2 m_edtOtherCallNotApplyCreditCount;
	CFlatEdit2 m_edtOtherCallNotApplyCreditCharge;
	CFlatEdit2 m_edtOtherCallApplyCreditCount;
	CFlatEdit2 m_edtOtherCallApplyCreditCharge;
	CFlatEdit2 m_edtOtherCallCreditFee;
	CFlatEdit2 m_edtOtherCallCreditFeeTotal;
	CFlatEdit2 m_edtOtherCallAllOnlineCount;
	CFlatEdit2 m_edtOtherCallAllOnlineCharge;
	CFlatEdit2 m_edtOtherCallNotApplyOnlineCount;
	CFlatEdit2 m_edtOtherCallNotApplyOnlineCharge;
	CFlatEdit2 m_edtOtherCallApplyOnlineCount;
	CFlatEdit2 m_edtOtherCallApplyOnlineCharge;
	CFlatEdit2 m_edtOtherCallOnlineFee;
	CFlatEdit2 m_edtOtherCallOnlineFeeTotal;
	CFlatEdit2 m_edtOtherCallAllCreditOnlineCount;
	CFlatEdit2 m_edtOtherCallAllCreditOnlineCharge;
	CFlatEdit2 m_edtOtherCallNotApplyCreditOnlineCount;
	CFlatEdit2 m_edtOtherCallNotApplyCreditOnlineCharge;
	CFlatEdit2 m_edtOtherCallCreditOnlineFeeTotal;
	CFlatEdit2 m_edtBeforeOtherCallCreditOnlineDeductingTaxFee;
	CFlatEdit2 m_edtBeforeOtherCallCreditOnlineDeductingTaxFeeTotal;
	CFlatEdit2 m_edtAfterOtherCallCreditOnlineDeductingTaxFee;
	CFlatEdit2 m_edtAfterOtherCallCreditOnlineDeductingTaxFeeTotal;
	CFlatEdit2 m_edtGiveTotal;
	CFlatEdit2 m_edtGiveTotal1;
	CFlatEdit2 m_edtGiveEtcTotal;
	CFlatEdit2 m_edtTakeEtcTotal;
	CFlatEdit2 m_edtTransCount;
	CFlatEdit2 m_edtTransCharge;
	CFlatEdit2 m_edtTotal;
	CFlatEdit2 m_edtCoupon;
	CFlatEdit2 m_edtCouponPlus;
	CFlatEdit2 m_edtCouponTotal;
	CFlatEdit2 m_edtMsg;

	CXTButton m_btnOtherCallOnlineWon;
	CXTButton m_btnOtherCallCreditWon;
	CXTButton m_btnOtherCallCashWon;
	CXTButton m_btnMyCallCashWon;
	CXTButton m_btnCashDeductingTaxFee;
	CXTButton m_btnMyCallCreditWon;
	CXTButton m_btnMyCallOnlineWon;
	CXTButton m_btnBeforeOtherCallCreditOnlineDeductingWon;
	CXTButton m_btnAfterOtherCallCreditOnlineDeductingWon;
	CXTButton m_btnBeforeMyCallCreditOnlineDeductingTaxWon;
	CXTButton m_btnAfterMyCallCreditOnlineDeductingTaxWon;

	CButton m_btnRefresh;
	CButton m_btnComplete;
	CButton m_btnPrint;
	CButton m_btnSaveOption;
	CButton m_btnDeleteReport;
	CButton m_chkOtherCallBefore;
	CButton m_chkOtherCallAfter;
	CButton m_chkMyCallBefore;
	CButton m_chkMyCallAfter;
	CButton m_chkCashMyCallDeductingTax;
	CButton m_chkCashOtherCallDeductingTax;		
	CButton m_chkSMS;
	CButton m_chkPDA;
	
	CMyStatic m_stcTotal;
	CStatic m_stcReportNo;
	CStatic m_stcCount;
	CStatic m_stcGiveGroup;
	CStatic m_stcTakeGroup;
	CStatic m_stcRider;

	CMyTakeStatic m_stcTakeEtc100;
	CMyTakeStatic m_stcTakeEtc101;
	CMyTakeStatic m_stcTakeEtc102;
	CMyTakeStatic m_stcTakeEtc103;
	CMyTakeStatic m_stcTakeEtc104;
	CMyTakeStatic m_stcTakeEtc105;
	CMyTakeStatic m_stcTakeEtc106;
	CMyTakeStatic m_stcTakeEtc107;
	CMyTakeStatic m_stcTakeEtc108;
	CMyTakeStatic m_stcTakeEtc109;
	CMyTakeStatic m_stcTakeEtc111;
	CMyTakeStatic m_stcTakeEtc112;
	CMyTakeStatic m_stcTakeEtc113;
	CMyTakeStatic m_stcTakeEtc114;
	CMyTakeStatic m_stcTakeEtc115;
	CMyTakeStatic m_stcTakeEtc116;
	CMyTakeStatic m_stcTakeEtc117;

	CMyGiveStatic m_stcGiveEtc100;
	CMyGiveStatic m_stcGiveEtc101;
	CMyGiveStatic m_stcGiveEtc102;
	CMyGiveStatic m_stcGiveEtc103;
	CMyGiveStatic m_stcGiveEtc104;
	CMyGiveStatic m_stcGiveEtc105;
	CMyGiveStatic m_stcGiveEtc106;
	CMyGiveStatic m_stcGiveEtc107;
	CMyGiveStatic m_stcGiveEtc108;
	CMyGiveStatic m_stcGiveEtc109;
	CMyGiveStatic m_stcGiveEtc110;
	CMyGiveStatic m_stcGiveEtc111;
	CMyGiveStatic m_stcGiveEtc112;
	CMyGiveStatic m_stcGiveEtc113;
	CMyGiveStatic m_stcGiveEtc114;
	CMyGiveStatic m_stcGiveEtc115;
	CMyGiveStatic m_stcGiveEtc116;
	CMyGiveStatic m_stcGiveEtc117;
	CMyGiveStatic m_stcGiveEtc118;
	CMyGiveStatic m_stcGiveEtc119;
	CMyGiveStatic m_stcGiveEtc120;
	CMyGiveStatic m_stcGiveEtc121;

	CMyStaticRed m_stcMyGiveCharge;
	CMyStaticRed m_stcOtherGiveCharge;

	CXTPListCtrl2 m_lstReport;
	CXTPListCtrl2 m_lstReport2;

	long m_nID;
	long m_nCashDTType;
	long m_bCashDTWon;
	long m_nMyCallDTType;
	long m_bMyCallDTWon;
	long m_nOtherCallDTType;
	long m_bOtherCallDTWon;
	long m_nRiderCharge;
	long m_nRiderCompany;
	long m_nRNo;
	long m_nFixedDepositCharge; 
	long m_nCouponCount;
	long m_nMyCallGiveToRiderCount;
	long m_nMyCallGiveToRiderCharge;
	long m_nOtherCallGiveToRiderCount;
	long m_nOtherCallGiveToRiderCharge;
	long m_nMyCashApplyCharge;
	long m_nOtherCashApplyCharge;
	long m_nMyCreditApplyCharge;
	long m_nOtherCreditApplyCharge;
	long m_nMyOnlineApplyCharge;
	long m_nOtherOnlineApplyCharge;
	long m_nMyCallCash;
	long m_nOtherCallCash;
	long m_nMyCallCredit;
	long m_nOtherCallCredit;
	long m_nMyCallOnline;
	long m_nOtherCallOnline;
	long m_nFixedDepositIncomeOnline;
	int m_nDT;

	BOOL m_bAbleMove;
	BOOL m_bUseDTPercent;
	BOOL m_bMyCallCashWon;
	BOOL m_bOtherCallCashWon;
	BOOL m_bMyCallCreditWon;
	BOOL m_bOtherCallCreditWon;
	BOOL m_bMyCallOnlineWon;
	BOOL m_bOtherCallOnlineWon;
	BOOL m_bComplete;
	
	CFont* m_Font;

	CKingoHttp m_Http;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_btnDate;

	CString m_strRName;
	CString m_strCashDTFee;
	CString m_strMyCallDTFee;
	CString m_strOtherCallDTFee;
	CString m_strRiderPhone;
	CString m_strRiderID;

};

