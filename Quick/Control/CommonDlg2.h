#pragma once
#include "afxwin.h"

#define MAX_BUTTON_COUNT 20

// CCommonDlg2 ��ȭ �����Դϴ�.

class CCommonDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDlg2)

public:
	CCommonDlg2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCommonDlg2();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMMON_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnOption[MAX_BUTTON_COUNT];
	CString m_sOption[MAX_BUTTON_COUNT];
	long m_nRowCount;
	long m_nSelItem;
	virtual BOOL OnInitDialog();
	void OnBtnClick(UINT nID);
};
