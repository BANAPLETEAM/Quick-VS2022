#pragma once
// CShareOrderDlg 대화 상자입니다.

class CShareOrderDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CShareOrderDlg)

public:
	CShareOrderDlg();   // 표준 생성자입니다.
	virtual ~CShareOrderDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_ORDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()


public:
	CBranchInfo *m_pBi;
	CListCtrl m_List;

public:
	void RefreshList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
private:
	DWORD m_dwLastRefreshList;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
};
