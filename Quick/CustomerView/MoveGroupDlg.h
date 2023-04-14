#pragma once

// CMoveGroupDlg ��ȭ �����Դϴ�.

class CMoveGroupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMoveGroupDlg)

public:
	CMoveGroupDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMoveGroupDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MOVE_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
