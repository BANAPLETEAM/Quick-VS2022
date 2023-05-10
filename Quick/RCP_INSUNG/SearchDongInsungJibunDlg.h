#pragma once
#include "afxwin.h"


// CSearchDongInsungJibunDlg ��ȭ �����Դϴ�.

class CSearchDongInsungJibunDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchDongInsungJibunDlg)

public:
	CSearchDongInsungJibunDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSearchDongInsungJibunDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEARCH_DONG_INSUNG_JIBUN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void RefreshList(CString strSearch);
	CString m_strSearch;
	CEdit m_edtSearch;
	CXTPListCtrl2 m_lstJibun;
	CXTPListCtrl2 m_lstDong;
	afx_msg void OnBnClickedSearchButton();

	afx_msg void OnReportItemJibunDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDongDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	void SelectJibun();
	void SelectDong();

	long m_nJibun1;
	long m_nJibun2;
	long m_nDongID;
	long m_nRoadID;
	long m_nRoadSubID;
	CString m_strJibun;
	CString m_strRoad;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
