#pragma once

class CPOIUnit;

// CSearchRegionSimpleDlg ��ȭ �����Դϴ�.

class CSearchRegionSimpleDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchRegionSimpleDlg)

public:
	CSearchRegionSimpleDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchRegionSimpleDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH_REGION_SIMPLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedShowAllDongCheck();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
public:
	CXTPListCtrl2 m_List;
	CString m_strKeyword;
	CButton m_chkShowAllDong;
	CPOIUnit *m_pPOI;

	void Search(CString strKeyword);
	void SelectPOI(int nRow);
};
