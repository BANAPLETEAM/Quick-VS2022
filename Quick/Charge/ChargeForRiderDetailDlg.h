#pragma once


// CChargeForRiderDetailDlg 대화 상자입니다.

class CChargeForRiderDetailDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChargeForRiderDetailDlg)

public:
	CChargeForRiderDetailDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChargeForRiderDetailDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHARGE_FOR_RIDER_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
