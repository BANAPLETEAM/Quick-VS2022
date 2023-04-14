#pragma once


class CMkDatabase;

// CAddCallHotNumberDlg 대화 상자입니다.

class CAddCallHotNumberDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddCallHotNumberDlg)

public:
	CAddCallHotNumberDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddCallHotNumberDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_CALL_HOT_NUMBER_DLG };

	CMkDatabase *m_pMyDb; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnOK();
	afx_msg void OnBnClickedOKBtn();

	DECLARE_MESSAGE_MAP()

	CEdit m_edtPhone;
	CEdit m_edtName;
};
