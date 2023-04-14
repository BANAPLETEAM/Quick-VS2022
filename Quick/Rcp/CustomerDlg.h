#pragma once
#define TIMER_TEL_LIST 0

#include "POIDataNew.h"

class CRcpPlaceInfo;

class CCustomerDlgSub1;
class CCustomerDlgSub2;
class CCustomerDlgSub3;

typedef map<long, ST_TEL> MAP_TEL;

#define WM_FOCUS_ON_SEARCH_EVENT		WM_USER + 600

// CCustomerDlg 대화 상자입니다.
class CRcpDlg;
class CAddCustomerDlg;

class CCustomerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCustomerDlg)

public:
	CCustomerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCustomerDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_DLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

	POINT m_DragStartPoint;
public:

	BOOL m_bModalMode;

	afx_msg void OnReportColumnChangeChanged(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnCustomerRecover();
	afx_msg void OnBnClickedNewBtn();
	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnBnClickedDelBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeDongEdit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LONG OnFocusOnSearchEvent(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeGroupCombo();
	afx_msg void OnBnClickedCopyCustomerBtn();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMlclkAddressList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkAddressList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnEnSetfocusDongEdit();
	afx_msg void OnEnChangeDisplayDongEdit();
	afx_msg void OnReportBeginDrag(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnEnChangeDataEdit();
	afx_msg void OnBnClickedCoporationBtn();
	afx_msg void OnBnClickedEditGroupAllBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnSetGroupOwner();
	afx_msg void OnSetReleaseGroupOwner();
	afx_msg void OnMakeNewCustomer();
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedSumCusBtn();
	afx_msg void OnBnClickedSearchGroupCheck();
	afx_msg void OnBnClickedAddressBtn();
	afx_msg void OnMakeMainAddress();
	afx_msg void OnDeleteAddress();
	afx_msg void OnBnClickedAddressCloseBtn();
	afx_msg void OnCbnSelchangePriceGradeCombo();
	afx_msg void OnEnChangeAddrTitleEdit();
	afx_msg void OnBnClickedEditPersonBtn();
	afx_msg void OnDeleteCall();
	afx_msg void OnMakeMain();
	afx_msg void OnMove(int x, int y);

	static int staticInitDialog(CCustomerDlg *pDlg)
	{ return pDlg->InitDialog(); }
	void InitList(BOOL bDongFirst = FALSE);
	void InitDongFirstList();
	void InitOneList();
	BOOL EditCustomer();
	BOOL CheckLoginID();
	void SetListItem(long nItem, ST_CUSTOMER_INFO *pc);
	void GetCurInfo(ST_CUSTOMER_INFO *pc);
	void GetCurDongInfo(CPOIUnit *pc);
	void SearchListDate(CString strSearchData);
	BOOL SumCustomer(CPoint pt);
	void ChangeGroup( long nOldGNo, long nNewGNo, BOOL bChange, CXTPGridRecord *pRecord);
	void DeleteListAllItems();
	void InitControl(BOOL bEnable);
	void SetCompanyApplyCharge(long nMemCNo);
	BOOL GetCustomerInfo(int &nItem, CString &strGNoSUM, int nCorporationDirectReceipt = 0);
	void BatchUpdateGetCustomerInfo(CString strCNoList);
	void DeleteGroupItem();
	void InsertGroupStartLine();
	BOOL SearchGroupData(CString strGNo, BOOL bOneGroup = FALSE);
	static void GetPcInfo(CMkRecordset *pRs, ST_CUSTOMER_INFO *pc, COleDateTime &dtPRDate, BOOL bInsungQuery = FALSE);
	void ShowAddress();
	void ShowControl(BOOL bShow);
	void HistoryChargeAdd(int nOriginalCurSel);
	void HistoryChargeDelete(int nOriginalCurSel);
	void SetDisplayAddrEdt();
	void SetAddressInfo();	
	void InsertCustomerOk();
	void RefreshTelList(long nTelID = 0);
	int InitDialog();
	CWnd* GetTabItem(int nTab);
	void ClearCustomerDlg();
	void ChangeTelDepartInfo();
	BOOL IsDataHas(ST_TEL *st);
	void GetCustomerPhoneNumber(long nTelID, CString &strPhone1, CString &strPhone2, CString &strPhone3);
	void FillCompanyChargeList();
	void OnOK();
	void OnCancel();
	long GetLastSelRow();
	void SetCopyMode(BOOL bCopyMode);
	BOOL IsCopyMode();
public:
	CAddCustomerDlg *m_pAddCustomerDlg;
	CRcpPlaceInfo *m_pPlace;
	CRcpPlaceInfo *m_pParent;
	CRcpDlg *m_pRcpDlg;
	CXTPListCtrl10 m_List;
	BOOL m_bCIDSearch;
	BOOL m_bLoadList;

	CXTPTabControl m_wndTabControl;
	CXTPListCtrl2 m_lstAddress;

	CCustomerDlgSub1 *m_pSub1;
	CCustomerDlgSub2 *m_pSub2;
	CCustomerDlgSub3 *m_pSub3;

	CWnd* m_pDragWnd;
	CImageList* m_pDragImage;
	ST_CUSTOMER_INFO *m_pCusInfo;

	MAP_TEL m_mapTel;

	HCURSOR m_hcArrow;
	HCURSOR m_hcNo;
	HCURSOR m_hcMoveHold;

	static HBRUSH m_hBrush1;
	static HBRUSH m_hBrush2;
	static HBRUSH m_hBrush3;
	static HBRUSH m_hBrush4;
	static HBRUSH m_hBrush5;
	static HBRUSH m_hBrush6;
	static HBRUSH m_hBrush7;	

	POINT m_ptDrag;
	CFont m_ListFont;

	CMyStatic m_stcSearch;

	CFlatEdit2 m_edtData;

	CButton m_chkCoupon;
	CButton m_chkMoveList;
	CButton m_chkShowDeleteCustomer;
	CButton m_chkSearchGroup;
	CButton m_btnNew;
	CButton m_btnCopyCustomer;
	CButton m_btnEdit;
	CButton m_btnDel;
	CButton m_btnOK;
	CButton m_btnSearch;
	CButton m_btnCancel;
	CButton m_btnEditGroupAll;
	CButton m_btnEditPersonBatch;
	CButton m_btnSumCus;
	CButton m_btnAddress;
	CButton m_btnAddressClose;
	CButton m_btnCoporation;

	long m_nCNo;
	long m_nID;
	long m_nGNo;
	long m_nTelID;
	long m_nPersonCopySrcCNo;
	long m_nCompanyCode;
	long m_nDOrderTable;
	long m_nCustomerTable;
	long m_nPayTable;
	long m_nMileageBalance;
	long m_nTempCNo;
	long m_nMileage;
	long m_nDongID;
	long m_nPosX;
	long m_nPosY;
	long m_nUseCount;
	long m_nCancelCount;
	long m_nCreditCount;
	long m_nCreditCharge;
	long m_nSalesCompany;
	long m_nSalesWNol;	
	long m_nMainAddressID;
	long m_nPcMainAddressID;
	long m_nFirstTelID;
	long m_nSecondTelID;
	long m_nThirdTelID;
	long m_nRefreshTelID;
	long m_nLastCNo;
	long m_nDiscountType;

	UINT m_nInitItem;
	int m_nItem;
	int m_nCouponCharge;
	int m_nPriceGrade;
	int m_nReturnVal;
	int m_nBranchCode;
	int	m_nMileageType;
	int m_nSearchType;
	int m_nAllocGroup;

	BOOL m_bDoNotRefresh;
	BOOL m_bDirty;
	BOOL m_bGroupChangeReady;
	BOOL m_bDongFirst;
	BOOL m_bFirst;
	BOOL m_bNoDelay;	
	BOOL m_bCustomerTelInsert;
	BOOL m_bCustomerAddressInsert;
	BOOL m_bHasDetailPos;
	BOOL m_bGroup;
	BOOL m_bFocusInSearch;		
	BOOL m_bCopyMode;
	BOOL m_bDragMode;
	BOOL m_bClicking;
	BOOL m_bOrderCustomerSearch;
	BOOL m_bOnOk; // 정보입력이 창닫을때
	BOOL m_bNoneItemAutoCanceled;
	BOOL m_bCloseDlg;

	COleDateTime m_dtRegister;
	COleDateTime m_dtLast;
	COleDateTime m_dtSales;

	CString m_strAddress;
	CString m_strLastTel;
	CString m_strKeyword;	
	CString m_strSearchName;
	CString m_strSearchPhone;
	CString m_strData;
	CString	m_strTempCompany;
	CString m_strTempDong;
	CString m_strTempTel;
	CString m_strTempMobile;
	CString m_strTempDepart;
	CString m_strTempName;
	CString m_strTempLocation;
	CString m_strBranchName;
	CString	m_strCompany2;
	CString m_strDong2;
	CString m_strTel2;
	CString m_strDepart2;
	CString m_strName2;
	CString m_strLocation2;

};
