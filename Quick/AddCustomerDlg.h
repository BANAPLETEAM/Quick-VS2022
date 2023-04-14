#pragma once
#include "afxwin.h"

class CRcpPlaceInfo;
class CCustomerDlg;
// CAddCustomerDlg 대화 상자입니다.

class CAddCustomerDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddCustomerDlg)

public:
	CAddCustomerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddCustomerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_CUSTOMER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOkBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeAddrDongEdit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedShowMapBtn();
	afx_msg void OnEnSetfocusAddrDongEdit();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnEnKillfocusAddrDongEdit();

public:

	HBRUSH m_hBrush1;

public:

	void SearchDong(BOOL bFocus);
	void SetDisplayAddrEdt();
	CString NowUserID(long nCompany);

	CCustomerDlg *m_pCustomerDlg;

	CMyStatic m_stcCNo;
	CMyStatic m_stcCompany;
	//CMyDongStatic m_stcBaseDong;
	CMyStatic m_stcBaseDong;
	CMyStatic m_stcDepart;
	CMyStatic m_stcTel;
	CMyStatic m_stcManager;
	CMyStatic m_stcLocate;
	CMyStatic m_stcTelAdd;
	CMyStatic m_stcMemo;
	CMyStatic m_stcAllocGroup;
	CMyStatic m_stcMobile;

	CButton m_chkCredit;
	CButton m_chkCoupon;

	CFlatEdit2 m_edtLocate;
	CFlatEdit2 m_edtCNo;
	CFlatEdit2 m_edtUserID;
	CFlatEdit2 m_edtCompany;
	CFlatEdit2 m_edtDepart;
	CFlatEdit2 m_edtDisplayDong;
	CFlatEdit2 m_edtName;
	CFlatEdit2 m_edtTel;
	CFlatEdit2 m_edtMemo;
	CFlatEdit2 m_edtMobile;
	CFlatEdit2 m_edtAddrDong;
	CFlatEdit2 m_edtFax;

	CComboBox m_cmbAllocGroup;

	CMyStatic m_stcHelp;
	CMyStatic m_stcRiderMemo;
	CMyStatic m_stcAddress;
	CMyStatic m_stcFax;
	CFlatEdit2 m_edtRiderMemo;

	CStatic m_stcUseCredit;

	CButton m_btnOK;
	CButton m_btnCancel;
	CMarkupStatic m_stcAddressDisplay;
public:
	CString m_strID;
	CString m_strCompany;
	CString m_strTel;
	CString m_strDisplayDong;
	CString m_strLocation;
	CString m_strDepart;
	CString m_strName;
	CString m_strMobile;
	CString m_strMemo;
	CString m_strRiderMemo;
	CString m_strAddressDetail;
	CString m_strAddrDong;
	CString m_strUserID;
	CString m_strFax;

	int m_nAllocGroup;
	long m_nCNo;
	long m_nCustomerTable;
	long	m_nDongID;
	long	m_nPosX;
	long	m_nPosY;
	long	m_nTempCNo;
	BOOL	m_bInternet;
	BOOL m_bCredit;
			
	CRcpPlaceInfo *m_pPlace;
	afx_msg void OnEnSetfocusTelEdit();
	afx_msg void OnEnChangeTelEdit();
};
