#pragma once


class CStaffPage19 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage19)

public:
	CStaffPage19();
	virtual ~CStaffPage19();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAFF_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

protected:
	COleDateTime m_dtDate;

public:
	afx_msg void OnBnClickedRefreshBtn();
	virtual void OnInitialUpdate();
	void RefreshList();

protected:
	CXTPListCtrl31 m_List;
	long m_nCompanyCode;
	BOOL m_bIntegrated;
	CDateTimeCtrl m_DateDT;
	CStatic m_ChargeStatic;
	CString m_strSearch;
	CStatic m_stcInfo;

	CFlatEdit2 m_SearchEdit;

	CButton m_RefreshBtn;

public:
	void SetCompanyCode(int nCompanyCode) { m_nCompanyCode = nCompanyCode; }
	void SetIntegrated(BOOL bIntegrated) { m_bIntegrated = bIntegrated; }

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnMenuMsg();
	afx_msg void OnWorkStop();
	afx_msg void OnWorkOk();
	afx_msg void OnEnChangeSearchEdit();
};
