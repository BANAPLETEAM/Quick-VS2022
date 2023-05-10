#pragma once

#include "RoundStatic.h"
#include "afxwin.h"

// CCustomerPage1 대화 상자입니다.
class CCustomerPage1 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage1)
public:
	enum ColumnsItemIndex
	{
		//kCNo = 0,
		kClientNumber = 0,
		kCompany,
		kDepart,
		kName,
		kPhone1,
		kUserID,
		kCustomerID,
		kDong,
		kLocation,
		kCredit,
		kDiscount,
		kAddress,
		//kTeam,
		//kAllocGroup,
		//kMobile,
		//kCouponCharge,
		kMemo,
		kColumsTotal
	};


public:
	CCustomerPage1();   // 표준 생성자입니다.
	virtual ~CCustomerPage1();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_PAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()

public:	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedTeamSearchBtn();

	afx_msg void OnBnClickedButtonSearch();
	afx_msg LONG OnEnterNotify(UINT nCtrl, LPARAM lParam);
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeListTel();
	afx_msg void OnBnClickedButtonTeladd();
	afx_msg void OnBnClickedButtonTeldel();

	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonDel2();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();

	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	void OnReportBeginDrag(NMHDR * pNotifyStruct, LRESULT * result);; //드래그앤드랍 시작

	//아이템 클릭
	void OnReportItemClick(NMHDR*  pNotifyStruct, LRESULT* /*result*/);


	void OnRefreshList();
	void AddPhoneNumber(CString strTel, CString strMobile = "", BOOL bMsgHide = FALSE);
	void SetDOrderTable(int nDOrderTable) { m_nDOrderTable = nDOrderTable; }
	void SetCustomerTable(int nCustomerTable) { m_nCustomerTable = nCustomerTable; }

	CXTPListCtrl2 m_lcData;

	CListBox m_lcTel;

	CString m_strID;
	CString m_sCompany;
	CString m_sTel1;
	CString m_sDong;
	CString m_sLocation;
	CString m_sDepart;
	CString m_sName;
	CString m_strData;
	CString m_strFilter;
	CString m_strSort;
	CString m_strKeyword;
	CString m_strMobile;
	CString m_strMemo;
	CString m_stredtID;

	CStringArray m_arLocation;

	int m_nItem;
	int m_nDiscount;
	int m_nSearchType;
	int iReturnVal;

	long m_nCNo;	

	BOOL m_bCid;
	BOOL m_bFirst;
	BOOL m_bCredit;
	BOOL m_bCoupon;

	BOOL m_bDragMode;

public:


protected:
	CFont m_ListFont;
	UINT m_nInitItem;
	BOOL m_bCheckMidWord;

	CWnd* m_pDragWnd;
	CImageList* m_pDragImage;
	HCURSOR m_hcArrow;
	HCURSOR m_hcNo;
	HCURSOR m_hcMoveHold;

protected:
	CMyStatic m_CustomerNoStatic;
	CMyStatic m_CompanyStatic;
	CMyStatic m_CreditStatic;
	CMyStatic m_BaseDongStatic;
	CMyStatic m_DepartStatic;
	CMyStatic m_TelStatic;
	CMyStatic m_DiscountStatic;
	CMyStatic m_ManagerStatic;
	CMyStatic m_LocateStatic;
	CMyStatic m_TelAddStatic;
	CMyStatic m_SearchStatic;
	CMyStatic m_MobileStatic;
	CMyStatic m_TeamStatic;
	CMyStatic m_MemoStatic;
	CMyStatic m_AllocGroupStatic;
	CMyStatic m_CouponStatic;
	CMyStatic m_IdStc;

	CFlatEdit2 m_ctrlData;
	CFlatEdit2 m_TelAddEdit;
	CFlatEdit2 m_LocateEdit;
	CFlatEdit2 m_CNoEdit;
	CFlatEdit2 m_CompanyEdit;
	CFlatEdit2 m_DepartEdit;
	CFlatEdit2 m_DiscountEdit;
	CFlatEdit2 m_DongEdit;
	CFlatEdit2 m_SNameEdit;
	CFlatEdit2 m_TelEdit;
	CFlatEdit2 m_MobileEdit;
	CFlatEdit2 m_MemoEdit;
	CFlatEdit2 m_edtID;

	CButton m_CreditCheck;
	CButton m_CouponCheck;

	long m_nDOrderTable;
	long m_nCustomerTable;

	CComboBox m_TeamCombo;
	CComboBox m_TeamSearchCombo;
	CComboBox m_AllocGroupCombo;
	CComboBox m_CouponCombo;
	CComboBox m_cmbSearch;

	CButton m_IndexBtn0;
	CButton m_IndexBtn1;
	CButton m_IndexBtn2;
	CButton m_IndexBtn3;
	CButton m_IndexBtn4;
	CButton m_IndexBtn5;
	CButton m_IndexBtn6;
	CButton m_IndexBtn7;
	CButton m_IndexBtn8;
	CButton m_IndexBtn9;
	CButton m_IndexBtn10;
	CButton m_IndexBtn11;
	CButton m_IndexBtn12;
	CButton m_IndexBtn13;
	CButton m_IndexBtn14;
	CButton m_SearchBtn;
	CButton m_TeamSearchBtn;
	CButton m_TelAddBtn;
	CButton m_TelDelBtn;
	CButton m_NewBtn;
	CButton m_EditBtn;
	CButton m_DelBtn;

private:
	CXTPGridRecord* m_pSourceRecord;
public:
	CEdit m_edtSearch;
	afx_msg void OnEnChangeEditSearch();
};
