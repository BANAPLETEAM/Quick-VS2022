#pragma once

// CSMSStateDlg ��ȭ �����Դϴ�.

class CSMSStateDlg : public CMyDialog
{
	DECLARE_DYNCREATE(CSMSStateDlg)

public:
	CSMSStateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSMSStateDlg();
	// ������


	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMSSTATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	void RefreshList();

	CString GetSMSStateString(long nCount);
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_List;
	CStatic m_dtChange;
	afx_msg void OnBnClickedSelectBtn();
	COleDateTime GetSelectTime();
	COleDateTime m_dtCur;
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
