#pragma once


// CGenerateOpenAPIStateDlg ��ȭ �����Դϴ�.

class CGenerateOpenAPIStateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CGenerateOpenAPIStateDlg)

public:
	CGenerateOpenAPIStateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGenerateOpenAPIStateDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GENERATE_OPENAPI_STATE_DLG };

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
