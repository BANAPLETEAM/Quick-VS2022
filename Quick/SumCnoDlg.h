#pragma once


// CSumCnoDlg ��ȭ �����Դϴ�.

class CSumCnoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSumCnoDlg)

public:
	CSumCnoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSumCnoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SUM_CNO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();


	CString m_strCNo1;
	CString m_strCNo2;
	CString m_strCNo3;

};
