#pragma once


// CRiderBoardAddDlg ��ȭ �����Դϴ�.

class CRiderBoardAddDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderBoardAddDlg)

public:
	CRiderBoardAddDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRiderBoardAddDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RIDER_BOARD_ADD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	
public:
	CString m_strTitle;
	CString m_strMemo;
	BOOL m_bShow;
	long m_nIndex;
public:
	virtual BOOL OnInitDialog();
	void RefreshDlg();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
