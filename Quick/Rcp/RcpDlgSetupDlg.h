#pragma once


// CRcpDlgSetupDlg ��ȭ �����Դϴ�.

class CRcpDlgSetupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRcpDlgSetupDlg)

public:
	CRcpDlgSetupDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRcpDlgSetupDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RCP_DLG_SETUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	static ST_RCP_DLG_SET_INFO m_info;
	void StructToResource();
	void ResourceToStruct();
	void OnBnClickedOk();
};
