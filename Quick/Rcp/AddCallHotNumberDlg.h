#pragma once


class CMkDatabase;

// CAddCallHotNumberDlg ��ȭ �����Դϴ�.

class CAddCallHotNumberDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddCallHotNumberDlg)

public:
	CAddCallHotNumberDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddCallHotNumberDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_CALL_HOT_NUMBER_DLG };

	CMkDatabase *m_pMyDb; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnOK();
	afx_msg void OnBnClickedOKBtn();

	DECLARE_MESSAGE_MAP()

	CEdit m_edtPhone;
	CEdit m_edtName;
};
