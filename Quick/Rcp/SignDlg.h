#pragma once
#include "explorer.h"


// CSignDlg ��ȭ �����Դϴ�.

class CSignDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSignDlg)

public:
	CSignDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSignDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SIGN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CExplorer m_Explorer;
	long m_nTNo;
	long m_nCNo;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
