#pragma once
#include "afxwin.h"


// CSumCNoNewDlg ��ȭ �����Դϴ�.

class CSumCNoNewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSumCNoNewDlg)

public:
	CSumCNoNewDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSumCNoNewDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SUM_CNO_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	long m_nDelCNo;
	long m_nSumCNo;

	CStatic m_stcDelName;
	CStatic m_stcDelNo;
	CStatic m_stcSumName;
	CStatic m_stcSumNo;
	CListBox m_lstDelPhone;
	CListBox m_lstSumPhone;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	void RefreshInfo(long nCNo, CListBox *pListBox, CStatic *stcName, CStatic *strNo);
};
