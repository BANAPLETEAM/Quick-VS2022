#pragma once


// CGenerateAppStateDlg2 ��ȭ �����Դϴ�.

class CGenerateAppStateDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CGenerateAppStateDlg2)

public:
	CGenerateAppStateDlg2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGenerateAppStateDlg2();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GENERATE_APP_STATE_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_lstReport;
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedAddBtn();
	void RefreshList();
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CXTPGridRecord* GetFirstSelectRecord();
};
