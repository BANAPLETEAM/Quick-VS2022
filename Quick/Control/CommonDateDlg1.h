#pragma once


class CCommonDateDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CCommonDateDlg1)

public:
	CCommonDateDlg1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCommonDateDlg1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COMMON_DATE_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateButton m_DateBtn;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
};
