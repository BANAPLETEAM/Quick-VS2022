#pragma once


// CSetPoiDlg ��ȭ �����Դϴ�.

class CSetPoiDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSetPoiDlg)

public:
	CSetPoiDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetPoiDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SET_POI_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedClearPoiBtn();
	afx_msg void OnBnClickedClearNewAddressBtn();
	afx_msg void OnBnClickedCancel();
};
