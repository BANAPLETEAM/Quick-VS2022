#pragma once


class CChargeContainer;


// CSelectChargeType ��ȭ �����Դϴ�.

class CSelectChargeType : public CMyDialog
{
	DECLARE_DYNAMIC(CSelectChargeType)

public:
	CSelectChargeType(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSelectChargeType();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SELECT_CHARGETYPE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
