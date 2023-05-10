#pragma once

// CMoveGroupDlg 대화 상자입니다.

class CMoveGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMoveGroupDlg)

public:
	CMoveGroupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMoveGroupDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MOVE_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMoveBtn();
	afx_msg void OnEnChangeSearchGroupEdit();
	afx_msg void OnEnChangeSearchGroupEdit2();

	virtual BOOL OnInitDialog();
	void RefreshList(CXTPGridControl *pReport);
	void InitReport(CXTPGridControl *pRecord);
	void RefreshCustomerList();
	void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	CXTPGridControl m_lstSrc;
	CXTPListCtrl2 m_lstCustomer;
	CXTPGridControl m_lstDst;
	
	CFlatEdit2 m_edtSearchGroup;
	CFlatEdit2 m_edtSearchGroup2;
	
	CString m_strSearch;
	long m_nGNo;
};
