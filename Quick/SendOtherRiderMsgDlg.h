#pragma once


// CSendOtherRiderMsgDlg ��ȭ �����Դϴ�.

class CSendOtherRiderMsgDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSendOtherRiderMsgDlg)

public:
	CSendOtherRiderMsgDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSendOtherRiderMsgDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEND_OTHER_RIDER_MSG }; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	CEdit m_edtMsg;
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedCancelBtn();
public:
	long m_nRiderCompany;
	long m_nRNo;
};
