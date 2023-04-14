#pragma once


// CChargeMemberDlg 대화 상자입니다.

class CChargeMemberDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeMemberDlg)

public:
	CChargeMemberDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeMemberDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_MEMER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedYes();
	afx_msg void OnBnClickedNo();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

	CFlatEdit2 m_edtChargeName;

	int m_nReturn;
	CString m_strChargeName;
	CString m_strEtc;
};
