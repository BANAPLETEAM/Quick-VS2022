#pragma once
#include "DataBox.h"
#include "BtnST.h"

//
//typedef struct  
//{
//	CString sChargeName;
//	long nMemCNo;
//	CString sCompany;
//	CString sDepart;
//	CString sManager;
//	CString sTel1;
//	CString sMobile;
//	CString sDong;
//	int		nChildCount;
//	COleDateTime dtRegister;
//	BOOL bDelete;
//} MEMBER_CNO;
//// CChargeHistoryMemDlg 대화 상자입니다.
//typedef::map<long, MEMBER_CNO*>MAP_MEMBER_CNO;
//typedef::map<MEMBER_CNO*, CMyXTPGridRecord*>MAP_XTPRECORD_CNO;


#define  REGISTER_CUSOMER 100
#define  DELETE_CUSOMER 10




class CWorkBtn : public CButtonST
{
	//DECLARE_DYNAMIC(CWorkBtn)
public:
	CWorkBtn();
	virtual ~CWorkBtn();
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	//{{AFX_MSG
	//afx_msg LRESULT On_MenuCallback(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnMenuNewCharge();
	afx_msg void OnMenuDelCharge();
	afx_msg void OnMenuModifyCharge();
	afx_msg void OnMenuRefreshServer();	
	afx_msg void OnMenuSumCharge();	
	
	//}}AFX_MSG	
	void InitButton(CWnd *pWnd);
CWnd *m_pWnd;
};

class CWorkSubBtn : public CButtonST
{
	//DECLARE_DYNAMIC(CWorkSubBtn)
public:
	CWorkSubBtn();
	virtual ~CWorkSubBtn();

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	//{{AFX_MSG
	//afx_msg LRESULT On_MenuCallback(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnMenuCustomerRefresh();
	afx_msg void OnMenuSubDelBtn();
	afx_msg void OnMenuSubNewBtn();
	afx_msg void OnMenuChargeRefresh();	
	afx_msg void OnMenuDelChargeItem();	
CWnd *m_pWnd;
	//}}AFX_MSG	
	void InitButton(CWnd *pWnd);

};

class CMainChargeList : public CDataBox
{

public:
	CMainChargeList()
	{
		m_nMemCNo = 0;
	}
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pMetrics )
	{
		CString strColumn = pDrawArgs->pColumn->GetCaption();
		int nRow = pDrawArgs->pRow->GetIndex();
		int nCount = pDrawArgs->pControl->GetRows()->GetCount();
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nItemCol = pDrawArgs->pColumn->GetItemIndex();


		if(GetItemDataLong(nRow) == m_nMemCNo)
			pMetrics->clrBackground = RGB(255,125,165);


	}
public:
	long m_nMemCNo;
	void SetMemCNo(long nMemCNo){m_nMemCNo = nMemCNo;}

};

class CSubChargeList : public CDataBox
{

public:
	CSubChargeList()
	{
		m_nCNo = 0;
	}
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pMetrics )
	{
		CString strColumn = pDrawArgs->pColumn->GetCaption();
		int nRow = pDrawArgs->pRow->GetIndex();
		int nCount = pDrawArgs->pControl->GetRows()->GetCount();
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nItemCol = pDrawArgs->pColumn->GetItemIndex();


		if(GetItemDataLong(nRow) == m_nCNo)
			pMetrics->clrBackground = RGB(255,125,165);


	}
public:
	long m_nCNo;
	void SetMemCNo(long nMemCNo){m_nCNo = nMemCNo;}

};



class CChargeHistoryMemDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeHistoryMemDlg)

public:
	CChargeHistoryMemDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeHistoryMemDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_HISTORY_MEMBER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();

	afx_msg void OnMenuNewCharge();
	afx_msg void OnMenuDelCharge();
	afx_msg void OnMenuModifyCharge();
	afx_msg void OnMenuRefreshServer();
	afx_msg void OnMenuCustomerRefresh();
	afx_msg void OnMenuSubDelBtn();
	afx_msg void OnMenuSubNewBtn();
	afx_msg void OnMenuChargeRefresh();
	afx_msg void OnMenuDelChargeItem();
	afx_msg void OnReportValueChanged(NMHDR*  pNotifyStruct, LRESULT* /*result*/);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMlclkList(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnNMlRClkList(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnNMlRClkList1(NMHDR *pNMHDR, LRESULT *pResult);		
	afx_msg void OnEnChangeMainSearchEdit();
	afx_msg void OnEnChangeSubSearchEdit();	
	afx_msg void OnBnClickedChargeViewButton();	
	afx_msg void OnBnClickedChargeListInput();	
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnCbnSelchangeViewTypeCombo();
	afx_msg void OnBnClickedOtherCustomerSearchBtn();

	void RefreshMainList();	
	void SetCNoPopup(long nMemCNo,long nCNo, long nCompany, CWnd *pWndCallBack = NULL);
	void RefreshSubList();
	void RefreshSubCharge();	
	void InsertChargeMember(long nMemCNo, BOOL bDBApply = FALSE);	
	void NewCharge();
	void DeleteCharge();
	void OnModifyCharge();
	void ModifyCharge(CString sChargeName,CString sEtc);
	void RefreshServer();
	void SumCharge();
	void DeleteCustomer();
	void NewCustomer();
	void ChargeItemDelete();
	void ReinitData();

	CMainChargeList m_lstMain;
	CSubChargeList m_lstSub;

	CFlatEdit2 m_edtMainSearch;
	CFlatEdit2 m_edtSubSearch;
	CFlatEdit2 m_edtCompany;
	CFlatEdit2 m_edtTel;
	CFlatEdit2 m_edtMobile;
	CFlatEdit2 m_edtDepart;
	CFlatEdit2 m_edtName;	
	CFlatEdit2 m_edtChargeName;
	CFlatEdit2 m_edtChargeEtc;
	CFlatEdit2 m_edtHistoryName;

	CWorkBtn  m_btnWork;
	CWorkSubBtn  m_btnWorkSub;

	BOOL m_bInit;
	COleDateTime m_dtInit;

	long m_nMemCNo;
	long m_nInitMemCNo;
	long m_nCompany;
	long m_nCNo;
	long m_nResult;
	//CString m_sChargeName;

	CComboBox m_cmbViewType;
	CButton m_chkShuttle;
	CWnd *m_pWnd;  // RcpDlg 요금재계산
};
