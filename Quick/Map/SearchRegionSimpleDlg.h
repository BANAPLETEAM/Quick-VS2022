#pragma once

class CPOIUnit;

// CSearchRegionSimpleDlg 대화 상자입니다.

class CSearchRegionSimpleDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSearchRegionSimpleDlg)

public:
	CSearchRegionSimpleDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSearchRegionSimpleDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEARCH_REGION_SIMPLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
