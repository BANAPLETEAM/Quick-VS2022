#pragma once


// CSearchDongInsungDlg 대화 상자입니다.


class CXTPListCtrl53 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics) 
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		
		if(nCol == 3) 
			pItemMetrics->clrForeground = RGB(0, 0, 235);
	}
};

class CSearchDongInsungDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchDongInsungDlg)

public:
	CSearchDongInsungDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchDongInsungDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_DONG_INSUNG_DLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	
	CXTPListCtrl2 m_lstDong;
	CXTPListCtrl2 m_lstCustomer;
	CXTPListCtrl53 m_lstPoi;

	CString m_strSearch;
	long m_nCustomerTable;

	long m_nDongID;
	long m_nCNo;
	long m_nTelID;
	long m_nCurNaverID;

	CPOIUnit *m_pDetailPOI;
	CString m_strAddress;

	long m_nOkType;

	afx_msg LONG OnRecvWebRecord(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReportItemPoiClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDongDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemCustomerDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemPoiDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	BOOL IsLastRowSelect(CXTPGridControl *pControl);
	void RefreshList();

	void SelectPoi();
	void SelectDong();
	void SelectCustomer();

	void RefreshDongList();
	void RefreshCustomerList();
	void RefreshPoiList();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
