#pragma once


class CRegisterWNoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRegisterWNoDlg)

public:
	CRegisterWNoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRegisterWNoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REGISTER_WNO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CXTPListCtrl2 m_wndReport;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRegister1();
	afx_msg void OnRegister2();

	CStatic m_Stc1;
	CStatic m_Stc2;
	virtual BOOL OnInitDialog();
	void RefreshList();
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedOkBtn();
};
