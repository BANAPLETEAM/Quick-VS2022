#pragma once

class CCustomerSmsDlg;
// CMentDlg 대화 상자입니다.

class CMentDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMentDlg)

public:
	CMentDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMentDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
