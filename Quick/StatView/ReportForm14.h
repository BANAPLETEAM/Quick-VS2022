#pragma once

typedef map<long, ST_SHARE*> SHARE_MAP;

// CReportForm14 폼 뷰입니다.

class CReportForm14 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm14)

protected:
	CReportForm14();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm14();

public:
	enum { IDD = IDD_REPORT14 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	afx_msg void OnViewExcel();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl7 m_wndReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;
	CButton m_RefreshBtn;

	SHARE_MAP m_map;
	SHARE_MAP m_mapTake;
	SHARE_MAP m_mapGive;

	virtual void OnInitialUpdate();
	void PrintList(SHARE_MAP *pMap, long nStartIndex, CString sTotal);
	void RefreshList();
	void PrintList();
	afx_msg void OnBnClickedRefreshBtn();
	CButton m_CreditChk;
};


