#pragma once


class CCustomerPage7 : public CMyFormView
{
	DECLARE_DYNCREATE(CCustomerPage7)
public:
	enum ColumnsName
	{
		kStartDong = 0,
		kArrivalDong,
		kNumber,
		kAmount,
		kColumnsNameTotal,
	};


public:
	CCustomerPage7();
	virtual ~CCustomerPage7();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_PAGE7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewExcel();

	DECLARE_MESSAGE_MAP()

protected:
	CXTPGridColumn* m_columnData[kColumnsNameTotal];
	COleDateTime m_dtFrom, m_dtTo;
	CComboBox m_MinCountCombo;
	CComboBox m_TypeCombo;
	CXTPListCtrl2 m_lcData;

	CMyStatic m_MinCountStatic;
	CMyStatic m_DateStatic;
	CMyStatic m_TypeStatic;

	long m_nDOrderTable;
	long m_nCustomerTable;
	BOOL m_bIntegrated;

public:
	void SetDOrderTable(int nDOrderTable) { m_nDOrderTable = nDOrderTable; }
	void SetCustomerTable(int nCustomerTable) { m_nCustomerTable = nCustomerTable; }
	void SetIntegrated(BOOL bIntegrated) { m_bIntegrated = bIntegrated; }
	void RefreshList();
	void InitColumn();

	afx_msg void OnCbnSelchangeTypeCombo();
};
