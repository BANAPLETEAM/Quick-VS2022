#pragma once


// CSubwayAbsentDlg ��ȭ �����Դϴ�.

class CSubwayAbsentDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSubwayAbsentDlg)

public:
	CSubwayAbsentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSubwayAbsentDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SUBWAY_ABSENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	long m_nCompany;
	long m_nRNo;

	CButton m_chkAbsent;
	CButton m_chkGetOff;
	CButton m_chkWaitTime;
	CFlatEdit2 m_edtLocation;
	afx_msg void OnBnClickedAbsentCheck();
	afx_msg void OnBnClickedGetOffCheck();
};
