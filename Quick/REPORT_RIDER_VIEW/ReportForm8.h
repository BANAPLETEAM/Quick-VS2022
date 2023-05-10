#pragma once

class CGraph;

// CReportForm8 대화 상자입니다.

class CReportForm8 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm8)

public:
	CReportForm8();   // 표준 생성자입니다.
	virtual ~CReportForm8();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REPORT8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CFlatEdit2 m_CouponEdit;
	CXTPListCtrl2 m_List;
	CString m_strCoupon;

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CDateButton m_DateBtn;

	CMyStatic m_Static1;
	CMyStatic m_Static2;
	CButton m_500Btn;
	CButton m_1000Btn;
	CButton m_2000Btn;
	CButton m_ShowBtn;


protected:
	void RefreshList();
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedShowBtn();
	afx_msg void OnBnClickedTodayBtn();
	afx_msg void OnBnClickedWeekBtn();
	afx_msg void OnBnClickedMonthBtn();
	afx_msg void OnBnClickedExactMonthBtn();
	afx_msg void OnBnClicked500Btn();
	afx_msg void OnBnClicked1000Btn();
	afx_msg void OnBnClicked2000Btn();
	afx_msg void OnEnChangeCouponEdit();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnViewExcel();
};
