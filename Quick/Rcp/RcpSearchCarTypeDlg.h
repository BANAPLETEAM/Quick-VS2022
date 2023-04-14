#pragma once

class CRcpView;

// CRcpSearchCarTypeDlg ��ȭ �����Դϴ�.

class CRcpSearchCarTypeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRcpSearchCarTypeDlg)

public:
	CRcpSearchCarTypeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRcpSearchCarTypeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RCP_SEARCH_CAR_TYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CRcpView *m_pRcpView;

	static BOOL m_bCarType0;
	static BOOL m_bCarType1;
	static BOOL m_bCarType2;
	static BOOL m_bCarType3;
	static BOOL m_bCarType4;
	static BOOL m_bCarType5;
	static BOOL m_bCarType6;
	static BOOL m_bCarType7;
	static BOOL m_bCarType8;
	static BOOL m_bCarType9;
	static BOOL m_bCarType10;
	static BOOL m_bCarType11;
	static BOOL m_bCarType12;
	static BOOL m_bCarType13;
	static BOOL m_bCarType14;
	static BOOL m_bCarType15;

	static BOOL IsUseSearchFilter();

	afx_msg void OnBnClickedSelectAllBtn();
	afx_msg void OnBnClickedNotSelectAllBtn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelectTwoBtn();
	afx_msg void OnBnClickedSelectFourBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedSearchCarTypeCheck();
	afx_msg void OnBnClickedSelectNotQuickBtn();
};

