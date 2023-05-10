#pragma once

typedef map<long, ST_FUNC_INFO> FUNC_INFO_MAP;

class CFunctionTableDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CFunctionTableDlg)

public:
	CFunctionTableDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFunctionTableDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FUNCTION_TABLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCbnSelchangeFuncCombo();
	afx_msg void OnViewExcel();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	void InitFunc();
	void RefreshList();

	CXTPListCtrl2 m_List;
	FUNC_INFO_MAP m_mapFuncInfo;

	CFlatComboBox m_cmbFunc;
	CDateButton m_btnDate;
	CEdit m_edtSearch;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;

	CButton m_btnRefresh;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeSearchEdit();
};
