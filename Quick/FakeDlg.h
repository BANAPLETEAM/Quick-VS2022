#pragma once


// CFakeDlg ��ȭ �����Դϴ�.

class CFakeDlg : public CDialog
{
	DECLARE_DYNAMIC(CFakeDlg)

public:
	CFakeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFakeDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FAKE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
