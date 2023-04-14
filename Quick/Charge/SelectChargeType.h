#pragma once


class CChargeContainer;


// CSelectChargeType 대화 상자입니다.

class CSelectChargeType : public CMyDialog
{
	DECLARE_DYNAMIC(CSelectChargeType)

public:
	CSelectChargeType(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSelectChargeType();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SELECT_CHARGETYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOkBtn();

	long m_nCompany;
	CString m_sCompany;
	BOOL m_bIntegrated;
	afx_msg void OnBnClickedBasicOldBtn();
	afx_msg void OnBnClickedDistanceOldBtn();
	
	
	

	CChargeContainer *m_pChargeContainer;
	
	afx_msg void OnBnClickedBasicNewBtn2();
	afx_msg void OnBnClickedBasicNewBtn();
};
