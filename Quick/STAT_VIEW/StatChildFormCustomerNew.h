#pragma once

#include "XTPListCtrlDiff.h"
#include "XTPChartLogi.h"
#include "PPTooltip.h"
//#include "StatFormBase.h"

// CStatChildFormCustomerNew 대화 상자입니다.
class CStatChildFormCustomerNew : public CMyFormView
{
	DECLARE_DYNCREATE(CStatChildFormCustomerNew)

public:
	CStatChildFormCustomerNew();   // 표준 생성자입니다.
	virtual ~CStatChildFormCustomerNew();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STAT_FORM_CUSTOMER_NEW };

	enum{
		DAY_LIST_TYPE,
		WEEK_LIST_TYPE,
		MONTH_LIST_TYPE
	};

	enum{
		DATE,
		TOTALCUSTOMER,
		TODAYCUSTOMER,
		TOTALCOMPLETE,
		TODAYCOMPLTE,
		MONTH_3,
		MONTH_6,
		YEAR_1,
		YEAR_2,
		YEAR_3
	};

	enum{
		PERCENT_ITEM_TYPE,
		COUNT_ITEM_TYPE
	};

	typedef struct {
		long nTotalCustomer, nTotalComplete, nNewTodayCustomer, nTodayComplete, nNew3MonthCount, nNew6MonthCount, nNew1YearCount, nNew2YearCount, nNew3YearCount;
	}ST_RECORD_DATA;

protected:
	virtual void			DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	afx_msg void			OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void			OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void			OnViewExcel();
	afx_msg void			OnSize(UINT nType, int cx, int cy);
	//afx_msg void			OnPaint();

	afx_msg void			OnBnClickedGraphBtn();
	afx_msg void			OnBnClickedRefreshBtn();
	afx_msg void			OnCbnSelchangeListTypeCombo();
	afx_msg void			OnCbnSelchangeWeekDayCombo();
	afx_msg void			OnCbnSelchangeChartFieldCombo();
	afx_msg void			OnCbnSelchangeListItemTypeCombo();

	void					RefreshSize();
	void					RearrangeControlsForRightGraph();
	void					RearrangeControlsForBottomGraph();
	void					RearrangeControlsForHideGraph();

	void					InitLayoutRight();

	afx_msg void			NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	BOOL					PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	virtual void			OnInitialUpdate();

	CPPToolTip				m_tooltip;
	
	map<int, ST_RECORD_DATA>m_mapRecordData;	//<RecordCount, 값>
	CXTPListCtrlDiff		m_List;
	CXTPChartLogi			m_Chart;
	COleDateTime			m_dtFrom;
	COleDateTime			m_dtTo;

	CDateTimeCtrl			m_dtpFrom;
	CDateTimeCtrl			m_dtpTo;
	CDateButton				m_btnDate;   

	CButton					m_btnRefresh;

	CComboBox				m_cmbListType;
	int						m_nListType;
	CComboBox				m_cmbWeekDay;
	int						m_nWeekDay;
	CComboBox				m_cmbChartField;
	int						m_nChartField;
	CComboBox				m_cmbListItemType;
	int						m_nListItemType;


	int						m_nArrangeType;
	CPoint					m_ptBaseWndPos;
	
public:
	//afx_msg void			OnTimer(UINT nIDEvent);
	//void					CreateTooltip();

	void					RefreshListDay();
	void					RefreshListMonth();	
	void					RefreshListWeek();
	void					RefreshListItem();

	void					RefreshListWeekDay();

	void					ListChart();

	BOOL					m_bDivisionView;
	void					InitDivisionDate();
};
