#pragma once

class CCustomerSmsDlg;
// CMentDlg ��ȭ �����Դϴ�.

class CMentDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMentDlg)

public:
	CMentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMentDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCopyBtn();
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);

	void RefreshList();
	
	CListCtrl m_List;
	CCustomerSmsDlg * m_pCustomerSmsDlg;

	CFlatEdit2 m_edtMsg;

	CButton m_btnAdd;
	CButton m_btnDelete;
	CButton m_btnCopy;
	CButton m_btnOK;
	CButton m_btnCancel;

	CStatic m_stcMsgLength;

	CString m_strMent;
};
