#pragma once


// CInsuranceDateDlg ��ȭ �����Դϴ�.

class CInsuranceDateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CInsuranceDateDlg)

public:
	CInsuranceDateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInsuranceDateDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INSURANCE_DATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	COleDateTime m_dtStart;
	COleDateTime m_dtEnd;
};
