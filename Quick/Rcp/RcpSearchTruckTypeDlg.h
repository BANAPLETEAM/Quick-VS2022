#pragma once

class CRcpView;
// CRcpSearchTruckTypeDlg ��ȭ �����Դϴ�.

class CRcpSearchTruckTypeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRcpSearchTruckTypeDlg)

public:
	CRcpSearchTruckTypeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRcpSearchTruckTypeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RCP_SEARCH_TRUCK_TYPE_DLG }; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	CRcpView *m_pRcpView;
	
	static BOOL m_bTruckType0;
	static BOOL m_bTruckType1;
	static BOOL m_bTruckType2;
	static BOOL m_bTonType0;
	static BOOL m_bTonType1;
	static BOOL m_bTonType2;
	static BOOL m_bTonType3;
	static BOOL m_bTonType4;
	static BOOL m_bTonType5;
	static BOOL m_bTonType6;

	static BOOL IsUseTruckSearchFilter();
	static BOOL IsUseTonSearchFilter();

	afx_msg void OnBnClickedSearchTruckType0Check();
	afx_msg void OnBnClickedSearchTruckType1Check();
	afx_msg void OnBnClickedSearchTruckType2Check();
	afx_msg void OnBnClickedSearchTruckTypeTon10Check();
	afx_msg void OnBnClickedSearchTruckTypeTon14Check();
	afx_msg void OnBnClickedSearchTruckTypeTon25Check();
	afx_msg void OnBnClickedSearchTruckTypeTon35Check();
	afx_msg void OnBnClickedSearchTruckTypeTon45Check();
	afx_msg void OnBnClickedSearchTruckTypeTon50Check();
	afx_msg void OnBnClickedSearchTruckTypeTon110Check();
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelect3tonUpBtn();
	afx_msg void OnBnClickedSelectCarAllBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSelectTonAllBtn();
	afx_msg void OnBnClickedSelect3tonDownBtn();
};
