#pragma once
#include "afxwin.h"

#define MAX_BUTTON_COUNT 20

// CCommonDlg2 대화 상자입니다.

class CCommonDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDlg2)

public:
	CCommonDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCommonDlg2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COMMON_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnOption[MAX_BUTTON_COUNT];
	CString m_sOption[MAX_BUTTON_COUNT];
	long m_nRowCount;
	long m_nSelItem;
	virtual BOOL OnInitDialog();
	void OnBtnClick(UINT nID);
};
