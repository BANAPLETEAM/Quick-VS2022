#pragma once


// CSetPoiDlg 대화 상자입니다.

class CSetPoiDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSetPoiDlg)

public:
	CSetPoiDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetPoiDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SET_POI_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedClearPoiBtn();
	afx_msg void OnBnClickedClearNewAddressBtn();
	afx_msg void OnBnClickedCancel();
};
