#pragma once
#include "afxcmn.h"
#include "MyButton.h"


// CAuthManage ��ȭ �����Դϴ�.

class CAuthManageDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAuthManageDlg)

public:
	CAuthManageDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAuthManageDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AUTH_MANAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	void Refresh();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	HBRUSH m_WhiteBrush;
	CXTPListCtrl2 m_List;
	CMyButton m_AuthStretchBtn;
	CMyButton m_AuthDeleteBtn;
	afx_msg void OnBnClickedAuthStretchBtn();
	afx_msg void OnBnClickedAuthDelete();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult );


};

