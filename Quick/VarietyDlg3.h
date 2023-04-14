#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "atlcomtime.h"


// CVarietyDlg3 ��ȭ �����Դϴ�.

class CVarietyDlg3 : public CMyDialog
{
	DECLARE_DYNAMIC(CVarietyDlg3)

public:
	CVarietyDlg3(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVarietyDlg3();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VARIETY_DLG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public :
	CString m_strTitle;
	virtual BOOL OnInitDialog();
	CFlatEdit2 m_edtMemo;
	CString m_strMemo;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CDateTimeCtrl m_dtDateAuto;
	COleDateTime m_dtAuto;
	CComboBox m_cmbAlloc;
	CButton m_chkUse;
	BOOL m_bUse;
	long m_nAutoGroupCode;
	afx_msg void OnBnClickedUseCheck();
};
