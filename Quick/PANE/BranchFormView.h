#pragma once

class CBranchFormRecord :public CXTPGridRecord
{
public:
	CBranchFormRecord::CBranchFormRecord(SHARE_COMPANY_INFO *info, BOOL bMain)
	{
		m_info = info;
		m_bMain = bMain;

		AddItem(new CXTPGridRecordItemText(info->strName));
		AddItem(new CXTPGridRecordItemText(info->strBranchName));
		AddItem(new CXTPGridRecordItemText(info->strOfficePhone));
		AddItem(new CXTPGridRecordItemText(info->strTel));
		AddItem(new CXTPGridRecordItemText(info->strSMSOfficePhone));
		AddItem(new CXTPGridRecordItemText(info->strCity));
		AddItem(new CXTPGridRecordItemText(info->strClientSymbol));

		m_bMain = bMain;
		m_nCompany = info->nCompany;
	}

	void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		BOOL bMain = ((CBranchFormRecord*)pDrawArgs->pRow->GetRecord())->m_bMain;

		if(bMain)
			pItemMetrics->clrBackground = RGB(230, 230, 255);

	}

	SHARE_COMPANY_INFO *m_info;
	BOOL m_bMain;
	long m_nCompany;
};
// CBranchFormView 대화 상자입니다.


typedef map<long, SHARE_COMPANY_INFO*> SHARED_COMPANY_MAP;


class CBranchFormView : public CMyFormView
{
	DECLARE_DYNCREATE(CBranchFormView)
	
public:
	CBranchFormView();   // 표준 생성자입니다.
	virtual ~CBranchFormView();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_BRANCH_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

public:
	//CListCtrl m_List;
	//CTreeListCtrl m_ctrlTreeList;
	CXTPListCtrl2 m_ctrlTreeList;
	CButton m_ShareChanelBtn;
	CButton m_EditBtn;
	CButton m_RefreshBtn;
	CFlatEdit2 m_SearchEdit;

	CMyStatic m_stc1;
	CMyStatic m_stc2;
	CMyStatic m_stc3;
	CMyStatic m_stc90;

	void RefreshList();

	afx_msg void OnBnClickedEditBtn();
	afx_msg void OnBnClickedRefreshBtn();

	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeSearchEdit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	SHARED_COMPANY_MAP m_mapShareCompany;
};
