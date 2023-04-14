#pragma once

class CStaffPage18 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage18)

public:
	CStaffPage18();   // 표준 생성자입니다.
	virtual ~CStaffPage18();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAFF_PAGE18 };

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedRefresh();

	DECLARE_MESSAGE_MAP()

public:
	void RefreshList();

public:
	CXTPListCtrl2 m_XTPList;
	CFlatEdit2 m_edtSearch;
};
