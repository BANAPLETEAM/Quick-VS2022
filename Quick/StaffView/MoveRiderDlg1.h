#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MyCheckButton.h"
#include "MyButton.h"

// CMoveRiderDlg1 대화 상자입니다.
typedef struct
{
	int nCompany;
	int nMNo;
	CString strBranchName;

} RIDER_INFO6;

class CMoveRiderDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CMoveRiderDlg1)

public:
	CMoveRiderDlg1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMoveRiderDlg1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MOVE_RIDER_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_RiderList;
	CComboBox m_cmbBranch;
	CListCtrl m_DepositList;
	CComboBox m_cmbSelectCombo;
	int m_nCompany;
	int m_nOptionStart;
	int m_nOptionEnd;
	int m_nPersonRiderNum;
	int m_nCountNum;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedAllApplyButton();
	afx_msg void OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckboxCancelButton();
	afx_msg void OnBnClickedCheckboxAllSelectButton();
	afx_msg void OnBnClickedCloseButton();	
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnBnClickedPersonApplyButton();

	void DepositListIn(int nItemData);
	void GroupListIn(int nItemData);	
	BOOL CheckData();
	BOOL ImPossibleMoveCheck();
	BOOL ImPossibleMoveAllCheck();
	BOOL ImPossIbleMoveOriginalAllCheck();
	void RefreshList();
	void InitControl();
	void SetIntegrated(BOOL bIntegrated){m_bIntegrated = bIntegrated;}
	void SetCompanyCode(int nCompanyCode) {m_nCompany = nCompanyCode;}

	
	int m_cmbSequence;
	CStatic m_stcProcessNum;
	CListCtrl m_GroupList;
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedGroupButton();
	BOOL m_bIntegrated;
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedOldRiderCheck();
	afx_msg void OnBnClickedNewRiderCheck();
	CMyCheckButton m_chkOldRider;
	CMyCheckButton m_chkNewRider;

	CMyButton m_AllSelectBtn;
	CMyButton m_CancelBtn;
	CMyButton m_AllApplyBtn;
	CMyButton m_PersonApplyBtn;
	CMyButton m_DepositBtn;
	CMyButton m_GroupBtn;
};
