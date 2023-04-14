#pragma once

class CRcpPageMissingCallForm : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpPageMissingCallForm)

protected:
	CRcpPageMissingCallForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpPageMissingCallForm();

public:
	enum { IDD = IDD_RCP_PAGE_MISSINGCALL_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewExcel();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedRefresh();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnDtnDatetimechangeDatetimepicker(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeSearchEdit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void RefreshList();
public:
	CXTPListCtrl2 m_List;

	COleDateTime m_dtLast;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;

	CDateTimeCtrl m_dtpFrom;
	CDateTimeCtrl m_dtpTo;
	CDateButton m_btnDate;

	CFlatEdit2 m_edtSearch;
	CString m_strSearchNumber;
};


