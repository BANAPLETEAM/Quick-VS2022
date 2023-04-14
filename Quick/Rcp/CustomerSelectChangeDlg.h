#pragma once


// CCustomerSelectChangeDlg 대화 상자입니다.

class CCustomerSelectChangeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCustomerSelectChangeDlg)

public:
	CCustomerSelectChangeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCustomerSelectChangeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CUSTOMER_SELECT_CHANGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bCNo;
	BOOL m_bCompany;
	BOOL m_bDepart;
	BOOL m_bManager;
	BOOL m_bTel;
	BOOL m_bMobile;
	BOOL m_bRiderMemo;
	BOOL m_bMemo;
	BOOL m_bGrade;
	BOOL m_bAllocGroup;
	BOOL m_bDetailAddress;
	BOOL m_bLocation;
	BOOL m_bDisplay;
	BOOL m_bCredit;
	BOOL m_bSendStateChangeSms;
	BOOL m_bICMapDisplayType;
	BOOL m_bUseHomepage;
	BOOL m_bPreventPosUpdate;
	BOOL m_bPriceGrade;
	BOOL m_bDiscount;
	BOOL m_bCoupon;
	BOOL m_bMileage;
	BOOL m_bEMail;
	afx_msg void OnBnClickedAllSelectBtn2();
	afx_msg void OnBnClickedAllSelectBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedNotSelectBtn();
	afx_msg void OnBnClickedNotSelectBtn2();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedOkBtn();
};
