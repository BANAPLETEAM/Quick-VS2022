#pragma once

// CStatForm5 �� ���Դϴ�.

typedef map<long, ST_WNO_DATE> MAP_WNO;

class CStatForm5 : public CMyFormView
{
	DECLARE_DYNCREATE(CStatForm5)

protected:
	CStatForm5();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CStatForm5();

public:
	enum { IDD = IDD_STAT_FORM5 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	MAP_WNO m_mapWNo;

	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_btnDate;

	CXTPListCtrl27 m_wndReport;

	void InitColumn();
	void RefreshList();
	void RefreshCount();

	afx_msg void OnViewExcel();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
};


