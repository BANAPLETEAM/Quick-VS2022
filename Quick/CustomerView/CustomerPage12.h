#pragma once
//#include "CustomerDlg.h"
#include "MyStaticWhite.h"
#include "MyStaticGreen.h"


#define NORMAL 0
#define LIKE_STATIC 1
#define LIKE_EDIT 2
#define LIKE_BUTTON 3
#define TEXT_LINE_COUNT 6

#define STATIC_COUNT 49
#define EDIT_COUNT 36

class CCustomerPage12 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage12)

protected:
	CCustomerPage12();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CCustomerPage12();

public:
	enum { IDD = IDD_CUSTOMER_PAGE12 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearchBtn();
	CXTPListCtrl2 m_Report;
	CEdit m_edtData;
	CString m_strData;
	CString m_strKeyword;
	long m_nSearchType;

	void DeleteListAllItems();
	void RefreshList();
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void SetText();
	void SearchListData(CString sSearchData);

public:
	CMyStaticGreen m_MyStc[STATIC_COUNT];
	CFlatEdit2 m_EditStc[EDIT_COUNT];
	CMyStaticWhite m_stcBtn[6];
	inline CString GetPrice(long nPrice)
	{
		if(nPrice == 0)
			return "A등급";
		if(nPrice == 1)
			return "B등급";
		if(nPrice == 2)
			return "C등급";
		if(nPrice == 3)
			return "D등급";
		return "A등급";
	}

	inline CString GetGrade(long nGrade)
	{
		if(nGrade == 0)
			return "보통";
		if(nGrade == 1)
			return "우수";
		if(nGrade == 2)
			return "최우수";
		if(nGrade == 3)
			return "불량";
		return "보통";
	}

	inline CString GetDiscountType(long nDiscount)
	{
		if(nDiscount == 0)
			return "퍼센트(%)";
		if(nDiscount == 1)
			return "금액(원)";
		if(nDiscount == 2)
			return "A타입";
		if(nDiscount == 3)
			return "B타입";
		if(nDiscount == 4)
			return "C타입";
		if(nDiscount == 5)
			return "D타입";
		return "퍼센트(%)";
	}
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeDataEdit();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnMakeCustomer();
	afx_msg void OnDeleteCustomer();
	CListBox m_lstTel;
	afx_msg void OnTimer(UINT nIDEvent);
	long m_nCNo;
	CMyStatic m_stcSearch;
	afx_msg void OnBnClickedSearchAllBtn();
	void ShowData(CMkRecordset *pRs);

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;
};


