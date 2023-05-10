#pragma once
#include "afxcmn.h"
#include "MyButton.h"


// CAuthManage 대화 상자입니다.

class CAuthManageDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAuthManageDlg)

public:
	CAuthManageDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAuthManageDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_AUTH_MANAGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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

