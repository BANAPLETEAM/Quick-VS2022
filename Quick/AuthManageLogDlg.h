#pragma once
#include "afxcmn.h"


// CAuthManageLog ��ȭ �����Դϴ�.

class CAuthManageLogDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAuthManageLogDlg)

public:
	CAuthManageLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAuthManageLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_AUTH_MANAGE_LOG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_List;
	void Refresh();
	virtual BOOL OnInitDialog();
};
