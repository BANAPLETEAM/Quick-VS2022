#pragma once
#include "afxwin.h"


class CShareReportTransferDlg;
class CShareReportWantTransferDlg;

// CShareReportAuthPhoneDlg 대화 상자입니다.

class CShareReportAuthPhoneDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportAuthPhoneDlg)

public:
	CShareReportAuthPhoneDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShareReportAuthPhoneDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHARE_REPORT_AUTH_PHONE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_Phone1Rdo;
	CButton m_Phone2Rdo;

	CShareReportTransferDlg *m_pShareReportTransferDlg;
	CShareReportWantTransferDlg *m_pShareReportWantTransferDlg ;

	void Init();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
