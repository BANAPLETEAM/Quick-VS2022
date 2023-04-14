#pragma once


// CRcpMapSetupDlg 대화 상자입니다.

class CRcpMapSetupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRcpMapSetupDlg)

public:
	CRcpMapSetupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRcpMapSetupDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RCP_MAP_SETUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	ST_RCP_MAP_SET_INFO m_info;

public:
	void StructToResource();
	void ResourceToStruct();
	void OnBnClickedOk();
};
