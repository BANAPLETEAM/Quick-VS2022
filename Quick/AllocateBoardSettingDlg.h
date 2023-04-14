#pragma once


class CAllocateBoardSettingDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateBoardSettingDlg)

public:
	CAllocateBoardSettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocateBoardSettingDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLOCATE_BOARD_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnSelEndColor();

	DECLARE_MESSAGE_MAP()
public:

	CFlatEdit2 m_edtAL;
	CFlatEdit2 m_edtPL;
	CFlatEdit2 m_edtAG;
	CFlatEdit2 m_edtPG;

	CFlatEdit2 m_edtAL2;
	CFlatEdit2 m_edtPL2;
	CFlatEdit2 m_edtAG2;
	CFlatEdit2 m_edtPG2;

	CMyStatic m_stcDelayColor;
	CMyStatic m_stcOtherOrderColor;
	CMyStatic m_stcOtherRiderColor;

	CXTColorPicker m_cpDelayBackColor;
	CXTColorPicker m_cpOtherOrderTextColor;
	CXTColorPicker m_cpOtherOrderBackColor;
	CXTColorPicker m_cpOtherRiderTextColor;
	CXTColorPicker m_cpOtherRiderBackColor;

	CButton m_chkFinishTest;
	CButton m_chkLinearType;
	CButton m_chkOtherOrderHaveMyOrder;
	CButton m_chkOtherOrderHaveMyOrderSplitSort;

	BOOL m_bNeedRefresh;

	afx_msg void OnBnClickedOtherRiderHaveMyOrderChk();
	afx_msg void OnBnClickedOtherRiderHaveMyOrderSplitSortChk();
};
