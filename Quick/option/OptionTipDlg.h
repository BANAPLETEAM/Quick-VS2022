#pragma once


// COptionTipDlg ��ȭ �����Դϴ�.

class COptionTipDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionTipDlg)

public:
	COptionTipDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COptionTipDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OPTION_TIP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
