#pragma once

#include "afxwin.h"


// CChangeAllocGroupInfoDlg 대화 상자입니다.

class CChangeAllocGroupInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CChangeAllocGroupInfoDlg)

public:
	CChangeAllocGroupInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CChangeAllocGroupInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHANGE_ALLOC_GROUP_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	long m_nGroupAllocID;
	long m_nCompany;

	void RefreshList();
	afx_msg void OnBnClickedOk();
	CFlatEdit2 m_edtAllocGroupName;
	CComboBox m_cmbOrderDelay;
	CComboBox m_cmbMyOrderDelay;
	CComboBox m_cmbOtherOrderDelay;
	CComboBox m_cmbMyCorpOrderDelay;
	CComboBox m_cmbShowOrder;
	CButton m_chkUseAutoAlloc;
	CButton m_chkNotUseAutoAlloc;
	CButton m_chkUseAutoGrade;
	CButton m_chkNotUseAutoGrade;
	CFlatEdit2 m_edtAllocGrade;

	CString m_strGroupName;
	long m_nPanaltyDelayTime4Order;
	long m_nPanaltyDelayTime4MyOrder;
	long m_nPanaltyDelayTime4OCOrder;
	long m_nPanaltyTypeShowOrder;
	long m_nPenaltyDelayTime4MyCorpOrder;
	BOOL m_bAutoAllocType;
	BOOL m_bAutoGradeAdjByLogic;
	long m_nCompanyAutoAllocType;

	afx_msg void OnBnClickedEditLogBtn();
	afx_msg void OnBnClickedUseAutoAllocCheck();
	afx_msg void OnBnClickedNotUseAutoAllocCheck();
	afx_msg void OnBnClickedUseAutoGradeCheck();
	afx_msg void OnBnClickedNotUseAutoGradeCheck();

	CButton m_chkUseDownGrade;
	CButton m_chkNotUseDownGrade;
	BOOL m_bUseAutoDownGrade;
	BOOL m_bNotUseAutoDownGrade;

	CComboBox m_cmbDownGradeDay;
	CComboBox m_cmbDownGradeCount;

	long m_nDownGradeDay;
	long m_nDownGradeCount;

	afx_msg void OnBnClickedUseDownGradeCheck();
	afx_msg void OnBnClickedNotUseDownGradeCheck();
	void EnableControl();

	CXTColorPicker m_btnTextColor;
	CXTColorPicker m_btnBackColor;

	afx_msg void OnSelEndOkTextColor();
	afx_msg void OnSelEndOkBackColor();

	long m_clrBack;
	long m_clrText;
	CButton m_chkDownGradeOnlyMyCall;
	BOOL m_bDownGradeOnlyMyCall;
	afx_msg void OnCbnSelchangeMyOrderDelayCombo();
};
