#pragma once


// CChargeForRiderDetailDlg ��ȭ �����Դϴ�.

class CChargeForRiderDetailDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeForRiderDetailDlg)

public:
	CChargeForRiderDetailDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChargeForRiderDetailDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARGE_FOR_RIDER_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	void RefreshDlg();
public:
	long m_nID;

	CEdit m_edtCompanyName;
	CEdit m_edtCompanyTel;
	CEdit m_edtWName;
	CEdit m_edtType;
	CEdit m_edtRequestTime;
	CEdit m_edtRequestEtc;
	CEdit m_edtRiderCompanyName;
	CEdit m_edtRiderCompanyTel;
	CEdit m_edtRName;
	CEdit m_edtResultTime;
	CEdit m_edtResultWName;
	CEdit m_edtResultEtc;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCloseBtn();
};
