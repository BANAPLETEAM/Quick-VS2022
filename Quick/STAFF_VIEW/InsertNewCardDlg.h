#pragma once


// CInsertNewCardDlg ��ȭ �����Դϴ�.

class CInsertNewCardDlg : public CDialog
{
	DECLARE_DYNAMIC(CInsertNewCardDlg)

public:
	CInsertNewCardDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInsertNewCardDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INSERT_NEW_CARD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCardNumber;
	CXTMaskEdit m_edtCardNumber;
	afx_msg void OnBnClickedInsertCardBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCloseBtn();
};
