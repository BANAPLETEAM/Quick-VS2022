#pragma once
#include "afxwin.h"


class CShareReportTransferDlg;
class CShareReportWantTransferDlg;

// CShareReportAuthPhoneDlg ��ȭ �����Դϴ�.

class CShareReportAuthPhoneDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CShareReportAuthPhoneDlg)

public:
	CShareReportAuthPhoneDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShareReportAuthPhoneDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHARE_REPORT_AUTH_PHONE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
