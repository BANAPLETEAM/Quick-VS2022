#pragma once


// CVarietyDlg1 ��ȭ �����Դϴ�.

class CVarietyDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CVarietyDlg1)

public:
	CVarietyDlg1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVarietyDlg1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VARIETY_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_sValue;
	CString m_sValue2;
protected:
	//	virtual void PreInitDialog();
public:
	virtual BOOL OnInitDialog();
	CString m_sTitleDlg;
};
