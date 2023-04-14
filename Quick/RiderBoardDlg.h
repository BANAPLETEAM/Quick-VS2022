#pragma once


// CRiderBoardDlg ��ȭ �����Դϴ�.

class CRiderBoardDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderBoardDlg)

public:
	CRiderBoardDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderBoardDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_BOARD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_lstReport;
	CComboBox m_cmbState;
public:
	virtual BOOL OnInitDialog();
	void RefreshList();
	void OnDelete();

	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * result);	
	afx_msg void OnCbnSelchangeStateCombo();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
