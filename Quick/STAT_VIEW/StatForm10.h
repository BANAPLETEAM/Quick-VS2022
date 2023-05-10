#pragma once



// CStatForm10 폼 뷰입니다.

class CStatForm10 : public CMyFormView
{
	DECLARE_DYNCREATE(CStatForm10)

protected:
	CStatForm10();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CStatForm10();

public:
	enum { IDD = IDD_STAT_FORM10 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;

	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRefreshBtn();

	void RefreshList();

	CXTPListCtrl2 m_lstReport;
};


