#pragma once
#include "afxwin.h"
//#include "MyCheckButton.h"

// COptionDlgCID 폼 뷰입니다.

class COptionDlgCID : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgCID)

protected:
	COptionDlgCID();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COptionDlgCID();

public:
	enum { IDD = IDD_OPTION_DLG_CID };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg long OnRefresh(WPARAM wParam,LPARAM lParam);
	afx_msg void OnEnChangeCalllingLineEdit();
	afx_msg void OnBnClickedRevisitCustomerStatic();

	BOOL Save(long nCompany, BOOL bAll);
	CString GetIPPBXOutboundCID(BOOL bOffice);

	CButton m_UseCidPoolCheck;		
	CButton m_CidNonfixedIntegrationTabCheck;
	CEdit m_CallingLineEdit;
	CButton m_chkRevisitCustomer;
	CEdit m_edtRevisitCustomer;
	CComboBox m_cmbRevisitCustomer;

	BOOL m_bCidNonfixedIntegrationTab;
	BOOL m_bUseCidPool;	
	CString m_strCallingLine;
	
	CButton m_chkCompanyCalllingLine;
	CStatic m_stcCalllingLine;
	CStatic m_stcCalllingLine2;
	CStatic m_stcCalllingLine3;

	CString m_strOriginCallingLine;
	CString m_strOriginCallingAuccountDID;
	afx_msg void OnPaint();
};