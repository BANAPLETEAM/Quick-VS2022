#pragma once


// CMsgPowerDlg ��ȭ �����Դϴ�.
class CMkDatabase;

class CMsgPowerDlg : public CMyResizeDialog
{
	DECLARE_DYNAMIC(CMsgPowerDlg)

public:
	CMsgPowerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMsgPowerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MSG_POWER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();

protected:
	CXTPGridControl m_wndReportCtrl;
	CImageList m_ilIcons;

public:
	virtual BOOL OnInitDialog();
	void RefreshList();
	void SaveList();

public:
	CMkDatabase *m_pDB;
};
