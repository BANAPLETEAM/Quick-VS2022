#pragma once


// CVarietyDlg 대화 상자입니다.

class CVarietyDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CVarietyDlg)

public:
	CVarietyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVarietyDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VARIETY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
