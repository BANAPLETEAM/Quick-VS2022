#pragma once


// CRcpMapSetupDlg ��ȭ �����Դϴ�.

class CRcpMapSetupDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRcpMapSetupDlg)

public:
	CRcpMapSetupDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRcpMapSetupDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RCP_MAP_SETUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	ST_RCP_MAP_SET_INFO m_info;

public:
	void StructToResource();
	void ResourceToStruct();
	void OnBnClickedOk();
};
