#pragma once


// CRcpDlgSetupDlg 대화 상자입니다.

class CRcpDlgSetupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRcpDlgSetupDlg)

public:
	CRcpDlgSetupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRcpDlgSetupDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RCP_DLG_SETUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	static ST_RCP_DLG_SET_INFO m_info;
	void StructToResource();
	void ResourceToStruct();
	void OnBnClickedOk();
};
