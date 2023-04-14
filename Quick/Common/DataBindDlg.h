#pragma once



// CDataBindDlg ��ȭ �����Դϴ�.

#define MAX_PAR_COUNT	10

class CDataBindDlg : public CMyResizeDialog
{
	DECLARE_DYNAMIC(CDataBindDlg)

public:
	CDataBindDlg(CString strTitle, CString strProc, CMkParameter *pPar1 = NULL,
			CMkParameter *pPar2 = NULL, CMkParameter *pPar3 = NULL,
			CMkParameter *pPar4 = NULL, CMkParameter *pPar5 = NULL,
			CMkParameter *pPar6 = NULL, CMkParameter *pPar7 = NULL,
			CMkParameter *pPar8 = NULL, CMkParameter *pPar9 = NULL,
			CMkParameter *pPar10 = NULL);   // ǥ�� �������Դϴ�.

	virtual ~CDataBindDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DATA_BIND_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedOkBtn();

public:
	virtual BOOL OnInitDialog();


protected:
	CXTPGridControl m_wndReport;
	CString m_strTitle;
	long m_nWidth;
	long m_nHeight;

public:
	CString m_strProc;
	CMkParameter *m_pParameter[MAX_PAR_COUNT];

public:
	BOOL MakeList();
	void SetWindowSize(long nWidth, long nHeight);
	
};


AFX_INLINE void CDataBindDlg::SetWindowSize(long nWidth, long nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}
