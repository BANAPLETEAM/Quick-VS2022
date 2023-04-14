#pragma once


// CGenerateAppStateDlg2 대화 상자입니다.

class CGenerateAppStateDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CGenerateAppStateDlg2)

public:
	CGenerateAppStateDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGenerateAppStateDlg2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GENERATE_APP_STATE_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
