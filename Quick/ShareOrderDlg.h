#pragma once
// CShareOrderDlg ��ȭ �����Դϴ�.

class CShareOrderDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CShareOrderDlg)

public:
	CShareOrderDlg();   // ǥ�� �������Դϴ�.
	virtual ~CShareOrderDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_ORDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
