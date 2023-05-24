#pragma once

#include "afxwin.h"

// CShowRiderInfoDlg 대화 상자입니다.

class CRcpView;
class CMakeRiderStat;


class CXTPListCtrl57 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
	{		  
		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();

		long nType = GetItemLong2(pRecord);

		if(nType == 0) 
		{
			pItemMetrics->clrBackground = RGB(255, 200, 200);
		}

		CXTPListCtrl2::GetItemMetrics(pDrawArgs, pItemMetrics);
	}
};

class CShowRiderInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShowRiderInfoDlg)

public:
	CShowRiderInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShowRiderInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHOW_RIDER_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOK();
	afx_msg void OnCancel();
	afx_msg void OnBnClickedCallBtn();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkOrderList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedWorkStateBtn();
	afx_msg void OnBnClickedSendMsgBtn();
	afx_msg void OnBnClickedCancelStateBtn();
	afx_msg void OnBnClickedRcpStateBtn();
	afx_msg void OnBnClickedRcpWaitBtn();
	afx_msg void OnBnClickedLimitShareOrderBtn();
	afx_msg void OnBnClickedRiderCancelLogBtn();
	afx_msg void OnBnClickedTransferBtn();
	afx_msg void OnBnClickedAttendBtn();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedRiderShareBoardBtn();
	afx_msg void OnBnClickedTRSBtn();

public:
	long GetOtherRiderOrder();
	void RefreshRefusalList();
	void ShowRiderInfo(BOOL bShow);
	void DrawRiderInfo(CDC *pDC);
	void DrawInfoBox(CDC *pDC, CRect rc, BOOL bGreen = FALSE);
	void PrintLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
		BOOL bNextSeparator = FALSE, COLORREF clrText = RGB(0, 0, 0));
	void PrintDualLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
		BOOL bNextSeparator = FALSE, COLORREF clrText = RGB(0, 0, 0));
	void ShowRiderStatInfo(CMakeRiderStat &stat);
	void TransferReal();
	void TransferOK();
	BOOL IsTransfer();
	BOOL InsertCharge(long nSendMoney);
	long GetSendMoney();
	void TransferPayLater(long nTNo, long nCompany, long nRNo, CString strRName, long nSendMoney);
	void RiderWorkReport();
	void SetParentView(CRcpView *pView) { m_pParentView = pView; }
	BOOL m_bDaeriRider;
	void SendMsgCTIForm(CString strPhoneNumber);
	void SendOtherRiderMsg();
	CString m_strSumBlackMarks;
	CString m_strBusinessCar;
	CString m_strCarNo;
	CRect m_rcDeviceID;
	CRect m_rcPhone;
protected:
	CRcpView *m_pParentView;

public:
	CListCtrl m_OrderList;
	CListCtrl m_RiderStatList;
	CXTPListCtrl57 m_lstShareRefusal;

	CStatic m_stc1;

	CButton m_btnOk;
	CButton m_btnCall;
	CButton m_btnWorkState;
	CButton m_btnSendMsg;
	CButton m_btnHistory;
	CButton m_btnCancelState;
	CButton m_btnRcpState;
	CButton m_btnLimitShareOrder;
	CButton m_btnRiderCancelLog;
	CButton m_btnRiderWorkReport;
	CButton m_btnAttend;
	CButton m_btnRiderShareBoard;
	CButton m_btnTransfer;

	CString m_strTodaySave;
	CString m_strCompany;
	CString m_strBranch;
	CString m_strRName;
	CString m_strRealRName;
	CString m_strDeviceID;
	CString m_strDeviceType;
	CString m_strDeviceVer;
	CString m_strPhone;
	CString m_strHomePhone;
	CString m_strEnterDate;
	CString m_strDepositType;
	CString m_strTodayIncome;
	CString m_strBalance;
	CString m_strTodayCharge;
	CString m_strWorkState;
	CString m_strCountLimit;
	CString m_strTimeLimit;
	CString m_strInsInfo;
	CString m_strInsExpDate;
	CString m_strInsState;
	CString m_strHistory;
	CString m_strHistory2;
	CString m_strCompanyPhone;
	CString m_strOfficePhone;
	CString m_strLicenseState;
	CString m_strCallBranch;
	CString m_strCarType;
	CString m_strCurBranch;
	CString m_strRecvCID;
	CString m_strLoadInsState;

	BOOL m_bConfirmCall;
	BOOL m_bLicenseOK;
	BOOL m_bShowRiderInfo;
		
	CBrush m_brush;

	long m_nCompany;
	long m_nRNo;
	long m_nOrderCompany;
	long m_nTNo;
	afx_msg void OnBnClickedInitBtn();
	CButton m_btnCeritify;
	afx_msg void OnBnClickedOtherRiderTransferBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	CButton m_btnOtherRiderTransfer;
	afx_msg void OnBnClickedChargeForBtn();
	CButton m_btnChargeFor;
	afx_msg void OnBnClickedRideridAcceptBtn();
	afx_msg void OnBnClickedRiderphoneAcceptBtn();
	afx_msg void OnBnClickedCallAcceptBtn();
	afx_msg void OnStnClickedDrawStatic();
};
