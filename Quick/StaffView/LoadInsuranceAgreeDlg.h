#pragma once
#include "afxwin.h"


// CLoadInsuranceAgreeDlg ��ȭ �����Դϴ�.

class CLoadInsuranceAgreeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CLoadInsuranceAgreeDlg)

public:
	CLoadInsuranceAgreeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLoadInsuranceAgreeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOAD_INSURANCE_AGREE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_edtAgree;
	afx_msg void OnBnClickedOkBtn();

	CString GetSourceHtml(CString strUrl);
	afx_msg void OnEnSetfocusAgreeEdit();
	BOOL m_bFirst;
};
