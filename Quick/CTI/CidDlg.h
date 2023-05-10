#pragma once


// CCidDlg ��ȭ �����Դϴ�.

class CCidDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCidDlg)

public:
	CCidDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCidDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CID_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_List;

	void OpenPreDlg();
	void OpenNewDlg();
	void RefreshList();
	BOOL SetClipboardText(const CString strData);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOpenPreBtn();
	afx_msg void OnBnClickedOpenNewBtn();
	afx_msg void OnEnChangeSearchEdit();
	CEdit m_edtSearch;
};
