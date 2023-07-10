#pragma once
class CRcpPlaceInfo;

typedef vector<ST_CASH_CHARGE> VEC_CASH_CHARGE;


class CConsignLinkDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CConsignLinkDlg)

public:
	
	CConsignLinkDlg(CWnd* pParent = NULL);   
	
	virtual ~CConsignLinkDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONSIGN_LINK_DLG };

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	CFlatEdit2 m_edtTitleStartTerminal;
	CFlatEdit2 m_edtTitleDestTerminal;	

	CFlatEdit2 m_edtTitleDestTerminalLink;
	CFlatEdit2 m_edtTitleStartTerminalLink;

	CFlatEdit2 m_edtTitleDest;
	CFlatEdit2 m_edtTitleStart;

	CFlatEdit2 m_edtDestCharge;
	CFlatEdit2 m_edtStartCharge;
	CFlatEdit2 m_edtTransCharge;

	CFlatEdit2 m_edtTempCharge;
	CFlatEdit2 m_edtCommissionCharge;
	CFlatEdit2 m_edtTotalCharge;
	CXTPListCtrl2 m_List;
	CXTPListCtrl2 m_CompanyOrderList;
	CConsignDrawManager2* m_pPaintManager;
	VEC_CASH_CHARGE m_vecCashCharge;

	CStatic m_stcBackCharge;
	CStatic m_stcFrontCharge;

	
	CButton m_btnConsignLink;
	CButton m_btnConsign;

	CString	m_sStartCharge;
	CString	m_sDestCharge;
	CString	m_sTransCharge;
	CString	m_sTempCharge;
	CString	m_sCommissionCharge;
	CString	m_sTotalCharge;
	
	COleDateTime m_dtStart;
	COleDateTime m_dtDest;

	CFlatEdit2 m_edtBusName; 
	CFlatEdit2 m_edtBusNo; 
	CFlatEdit2 m_edtInvoiceNo; 
	CFlatEdit2 m_edtEtc; 

	CDateTimeCtrl m_dtpStart;
	CDateTimeCtrl m_dtpDest;
	
    CComboBox m_cmbElapsed;
	CButton m_btnConsignInputInfo;
	CButton m_btnConsignCancle;
public:
	CRcpDlg *m_pRcpDlgWndFront;
	CRcpDlg *m_pRcpDlgWndBack;
	
	long m_nCompany;
	long m_nConCommissionCharge;
	CRcpPlaceInfo *m_pStartPlaceInfo;
	CRcpPlaceInfo *m_pDestPlaceInfo;
	CRcpPlaceInfo *m_pDestPlaceInfoTemp;
	
	BOOL m_bRcpDlgForgroudView; // 접수창에서 열시
	long m_nConsignTNo;
	long m_nTerminalWayID;
	long m_nTerminalTempWayID; // 가선택
	long m_nOrderTNo;
	CString m_sDestSido;
	long m_nWindowType;
	CString GetViewTime(int nMinute);
	void InitControl();
	void NewRefreshOrder(); // 신규오더
	void EditRefreshOrder(); //  수정시오더
	void RcpViewShow();
	void RefreshCharge();
	void RefreshList();
	void AddNewConsignLink();
	void EditConsignLink();
	void AddNewConsign();
	void EditConsign();
	void ConsingLinkOrderCancel();
	void ConsignListSelect(BOOL bListSelect, int nModifySelectRow = 0);
	void RefreshBusInfo();
	void RefreshDestOrder(long nRealConsignTNo = 0);
	void SetRcpDlg(CRcpDlg *pRcpDlg);
	//long GetStartDestCalculate(CConsignListInfo2 *pListInfo, BOOL bStart);
	void MakePlaceInfo2(CRcpDlg *pRcpDlg, BOOL bStart);
	void FrontOrderEtcMake(BOOL bDelete = FALSE);
	void DelList();
	void CommissionEditFocus();
	void BusNameEditFocus();
	//afx_msg void OnNMReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnNMReportItemCelChanged(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnEnChangeCommissionChargeEdit();
	afx_msg void OnBnClickedConsignLinkBtn();
	afx_msg void OnBnClickedConsignBtn();
	afx_msg void OnBnClickedCancelBtn();
	
	afx_msg void OnBnClickedWayChangeBtn();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedBusInfoBtn();
	afx_msg void OnCbnSelchangeElapsedCombo();
	afx_msg void OnBnClickedOrderRefreshBtn();
	afx_msg void OnBnClickedConsignBusCloseBtn();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnCancel();
	virtual void OnOK();

	
};


