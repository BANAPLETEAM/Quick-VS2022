#pragma once
#include "afxwin.h"


// CLoadInsuranceAgreeDlg 대화 상자입니다.

class CLoadInsuranceAgreeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CLoadInsuranceAgreeDlg)

public:
	CLoadInsuranceAgreeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLoadInsuranceAgreeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOAD_INSURANCE_AGREE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_edtAgree;
	afx_msg void OnBnClickedOkBtn();

	CString GetSourceHtml(CString strUrl);
	afx_msg void OnEnSetfocusAgreeEdit();
	BOOL m_bFirst;
};
