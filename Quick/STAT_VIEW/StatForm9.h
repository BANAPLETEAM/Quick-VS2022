#pragma once



// CStatForm9 �� ���Դϴ�.

class CStatForm9 : public CMyFormView
{
	DECLARE_DYNCREATE(CStatForm9)

protected:
	CStatForm9();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CStatForm9();

public:
	enum { IDD = IDD_STAT_FORM9 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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


