
#include "DataBox.h"

class CReportForm28List : public CDataBox
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics) 
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		

		if(nCol == 14) //글자
		{
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		}
		else if(nCol == 18)
		{
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		}
		else if(nCol == 20)
		{
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		}

	}
};



class CReportForm28 : public CMyFormView
{
	DECLARE_DYNCREATE(CReportForm28)

protected:
	CReportForm28();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CReportForm28();

public:
	enum { IDD = IDD_REPORT28 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRefreshBtn();


afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnViewExcel();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual void OnInitialUpdate();
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void RefreshList();

public:
	CReportForm28List m_wndReport;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_dtFromCtl;
	CDateTimeCtrl m_dtToCtl;
	CDateButton m_DateBtn;
	CButton m_RefreshBtn;

	
	CComboBox m_cmbSortType;

	CEdit m_edtSearch;


};



