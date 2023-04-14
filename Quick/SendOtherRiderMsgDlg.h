#pragma once


// CSendOtherRiderMsgDlg 대화 상자입니다.

class CSendOtherRiderMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSendOtherRiderMsgDlg)

public:
	CSendOtherRiderMsgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSendOtherRiderMsgDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SEND_OTHER_RIDER_MSG }; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	CEdit m_edtMsg;
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedCancelBtn();
public:
	long m_nRiderCompany;
	long m_nRNo;
};
