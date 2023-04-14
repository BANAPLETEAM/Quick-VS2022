#pragma once


class CIncomeForm3 : public CMyFormView
{
	DECLARE_DYNCREATE(CIncomeForm3)

public:
	CIncomeForm3();
	virtual ~CIncomeForm3();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INCOME_PAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedChargeBtn();
	afx_msg void OnLvnItemchangedSearchList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnDtnDatetimechangeDatetimepickerFrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedSearchBtn();

protected:
	BOOL IsCountOne();
	void SearchRider();
	void MoveClient();
	void RefreshList();
	void RefreshHistory();
	void RefreshAllLog();
	void FillListData();
	void SelectRider();

	long m_nCompany;
	long m_nRNo;

	CXTPListCtrl2 m_AllList;
	CXTPListCtrl2 m_lstSearch;
	CXTPListCtrl36 m_lstHistory;

	CFlatEdit2 m_edtSearch;
	CFlatEdit2 m_edtCompany;
	CFlatEdit2 m_edtRName;
	CFlatEdit2 m_edtBalance;
	CFlatEdit2 m_edtRNo;
	CFlatEdit2 m_edtEtc;

	CFlatComboBox m_cmbCharge;
	
	CButton m_btnRefresh;
	CButton m_btnCharge;
	CButton m_btnSearch;
};
