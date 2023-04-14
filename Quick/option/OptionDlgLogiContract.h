#pragma once

// COptionDlgLogiContract 폼 뷰입니다.

class COptionDlgLogiContract : public CMyFormView
{
	DECLARE_DYNCREATE(COptionDlgLogiContract)

protected:
	COptionDlgLogiContract();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COptionDlgLogiContract();

public:
	enum { IDD = IDD_OPTION_DLG_LOGI_CONTRACT };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();

	void RefreshData(CMkRecordset *pRs);

	CString m_strContractCompanyName;
	CString m_strContractBizNo;
	CString m_strContractCompanyOwner;
	CString m_strContractCompanyTel;
	CString m_strContractCompanyLocation;
};


