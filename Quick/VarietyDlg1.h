#pragma once


// CVarietyDlg1 대화 상자입니다.

class CVarietyDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CVarietyDlg1)

public:
	CVarietyDlg1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVarietyDlg1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VARIETY_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
