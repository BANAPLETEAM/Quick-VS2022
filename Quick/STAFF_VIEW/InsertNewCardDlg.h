#pragma once


// CInsertNewCardDlg 대화 상자입니다.

class CInsertNewCardDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertNewCardDlg)

public:
	CInsertNewCardDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInsertNewCardDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INSERT_NEW_CARD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCardNumber;
	CXTMaskEdit m_edtCardNumber;
	afx_msg void OnBnClickedInsertCardBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCloseBtn();
};
