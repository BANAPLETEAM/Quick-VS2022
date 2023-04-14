#pragma once

class CRcpView;
// CRcpSearchPayTypeDlg 대화 상자입니다.

class CRcpSearchPayTypeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRcpSearchPayTypeDlg)

public:
	CRcpSearchPayTypeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRcpSearchPayTypeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RCP_SEARCH_PAY_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	static BOOL m_bPayType0;
	static BOOL m_bPayType1;
	static BOOL m_bPayType2;
	static BOOL m_bPayType3;
	static BOOL m_bPayType4;
	static BOOL m_bPayType7;

	CRcpView *m_pRcpView;

	static BOOL IsUseSearchFilter();

	afx_msg void OnBnClickedSelectAllBtn();
	afx_msg void OnBnClickedNotSelectAllBtn();
	afx_msg void OnBnClickedCashBtn();
	afx_msg void OnBnClickedNoneCashBtn();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSearchPayType0Check();
	afx_msg void OnBnClickedSearchPayType1Check();
	afx_msg void OnBnClickedSearchPayType2Check();
	afx_msg void OnBnClickedSearchPayType3Check();
	afx_msg void OnBnClickedSearchPayType4Check();
	afx_msg void OnBnClickedSearchPayType7Check();
};
