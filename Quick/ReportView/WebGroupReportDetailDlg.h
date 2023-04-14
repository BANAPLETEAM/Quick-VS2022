#pragma once

#include "explorer.h"
#include "KingoHttp.h"
// CWebGroupReportDetailDlg 대화 상자입니다.

class CWebGroupReportDetailDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CWebGroupReportDetailDlg)
	//DECLARE_DYNAMIC(CWebGroupReportDetailDlg)

public:
	CWebGroupReportDetailDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebGroupReportDetailDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEB_GROUP_REPORT_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedNotIncludeOrderCheck();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedRefreshBtn2();
	afx_msg void OnBnClickedRefreshBtn3();
	afx_msg void OnBnClickedRefreshBtn4();
	afx_msg void OnBnClickedRefreshBtn5();
	afx_msg void OnBnClickedExcelBtn();
	afx_msg void OnBnClickedIncludeOrderCheck();

	void InitCheckBox(BOOL bEnable);
	void SetCheckBox(BOOL bCheck);
	void Refresh();
	void InitControl();
	BOOL MakeFile(CString sHtml,CString sFileName);

	CKingoHttp m_Http;
	CExplorer m_Explorer;

	CButton m_chkIncludeOrder;
	CButton m_chkNotIncludeOrder;

	CString m_strTitle;

	long m_nID;
	long m_nGNo;

	BOOL m_bSelect[21];
};
