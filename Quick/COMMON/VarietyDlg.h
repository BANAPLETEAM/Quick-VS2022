#pragma once


// CVarietyDlg ��ȭ �����Դϴ�.

class CVarietyDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CVarietyDlg)

public:
	CVarietyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVarietyDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VARIETY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	//CStatic m_Title;
	//CString m_sValue;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_sValue;
protected:
//	virtual void PreInitDialog();
public:
	virtual BOOL OnInitDialog();
	CString m_sTitleDlg;
};
