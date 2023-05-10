#pragma once

// CFoodCompleteDlg 대화 상자입니다.

class CFoodCompleteDlg : public CMyDialog
{ 
	DECLARE_DYNAMIC(CFoodCompleteDlg)

public:
	CFoodCompleteDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFoodCompleteDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FOOD_COMPLPTE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
