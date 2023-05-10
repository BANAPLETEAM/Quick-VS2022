#pragma once

// CShareRcpPageView 폼 뷰입니다.

class CShareRcpPageView : public CMyFormView
{
	DECLARE_DYNCREATE(CShareRcpPageView)

protected:
	CShareRcpPageView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CShareRcpPageView();

public:
	enum { IDD = IDD_SHARE_RCP_PAGE_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

public:
	void RefreshList();
	virtual void OnInitialUpdate();
	CWnd* GetTabItem(int nTab);

	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnEnChangeXtplistctrlEdit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeXtplistctrlCombo();

	CStatic m_stcOption;
	CXTPTabControl m_wndTabControl;
	CComboBox m_cmbSearch;
	CEdit m_edtSearch;
};


