#pragma once


// CAddBoxChargeDlg 대화 상자입니다.

class CAddBoxChargeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAddBoxChargeDlg)

public:
	CAddBoxChargeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddBoxChargeDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_BOX_CHARGE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	void InsertApplyCombo(CComboBox *pBox);
	void InsertApplyBikeWeightCombo(CComboBox *pBox);
	void InsertBikeWeightType(CComboBox *pBox);
	void RefreshDlg();
	void SetComboSelect(CComboBox *pBox, long nOption);

	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedInsertDocumentOptionBtn();
	BOOL InsertBoxChargeOption(long nType, long nStart, long nEnd, long nApply, BOOL bDelete);
	BOOL InsertUseLargeSumOption();
	BOOL InsertDocumentChargeOption();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	CButton m_chkUseLargeSum;
	void Swap(BOOL bUp);
public:
	long m_nCompany;
	CXTPListCtrl2 m_lstDocument;

	CEdit m_edtDocument;
	CEdit m_edtDocumentAdd;
	void RefreshDocumentList();

	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnDelete();
};
