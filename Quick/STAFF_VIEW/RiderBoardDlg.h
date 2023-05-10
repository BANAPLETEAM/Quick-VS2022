#pragma once


// CRiderBoardDlg 대화 상자입니다.

class CRiderBoardDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderBoardDlg)

public:
	CRiderBoardDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderBoardDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_BOARD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
