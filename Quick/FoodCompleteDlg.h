#pragma once

// CFoodCompleteDlg ��ȭ �����Դϴ�.

class CFoodCompleteDlg : public CMyDialog
{ 
	DECLARE_DYNAMIC(CFoodCompleteDlg)

public:
	CFoodCompleteDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CFoodCompleteDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FOOD_COMPLPTE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()		
public:

	BOOL m_bFoodOrder;
	COleDateTime m_dtFoodComplete;
	CComboBox m_cmbAddTime;
	CDateTimeCtrl m_dtpDate;
	CDateTimeCtrl m_dtpTime;
	CButton m_chkFoodOrder;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeAddTimeCombo();
	virtual BOOL OnInitDialog();
};
