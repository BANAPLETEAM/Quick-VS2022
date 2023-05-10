#pragma once


// CSumCnoDlg 대화 상자입니다.

class CSumCnoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSumCnoDlg)

public:
	CSumCnoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSumCnoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SUM_CNO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();


	CString m_strCNo1;
	CString m_strCNo2;
	CString m_strCNo3;

};
