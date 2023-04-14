#pragma once

#include "MyCheckButton.h"
#include "XTPListCtrl_Branch.h"
#include "BranchSel.h"

#define WM_REFRESH WM_USER + 1

class COptionDlgGeneral2;
class COptionDlgCharge;
class COptionDlgCID;
class COptionDlgSMS3;
class COptionDlgInterCall2;
class COptionDlgMobileNew;
class CMainOptionDlg2;
class COptionDlgSmartQ;

// CMainOptionDlg 대화 상자입니다.
class CMainOptionTabControl2 : public CXTPTabControl
{
public:
	CMainOptionTabControl2();
	void SetControl(CMainOptionDlg2 *pDlg);
protected:
	virtual void OnItemClick(CXTPTabManagerItem* pItem);
	
	CMainOptionDlg2 * m_pMainOptionDlg;
};

class CMainOptionDlg2 : public CMyDialog
{
	DECLARE_DYNAMIC(CMainOptionDlg2)

public:
	CMainOptionDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMainOptionDlg2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAIN_OPTION_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

	
public:
	CMainOptionTabControl2 m_wndTabControl;
	CWnd *m_pParentWnd;
	BOOL m_bIntegrated;	
	long m_nFirstSelectTab;
	BOOL m_bLogView;
	long m_nLogViewCompany;
	long m_nLogID;
	CDataBox m_List;
	CMainOptionDlg2 *m_pMainOptionDlg;
	BOOL m_bMainOptionDlgCreate;

	void  RefreshInfo();
	CWnd* GetTabItem(CString sCaption);
	CWnd* GetTabItem(int nTab);
	long GetSelCompanyCode();
	void Refresh();
	void RefreshLogInfo();
	LONG OnChangeBrachCode(WPARAM wParam, LPARAM lParam);
	BOOL SaveNew(long nPage, BOOL bAll);
	void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	
	void OptionControlApply(CMkRecordset *pRs,	COptionDlgGeneral2*	pOptionDlgGeneral);
	void OptionControlApply(CMkRecordset *pRs,	COptionDlgCharge*	pOptionDlgCharge);
	void OptionControlApply(CMkRecordset *pRs,	COptionDlgCID*	pOptionDlgCID);
	void OptionControlApply(CMkRecordset *pRs,	COptionDlgSMS3*	pOptionDlgSMS3);
	void OptionControlApply(CMkRecordset *pRs,	COptionDlgInterCall2*	pOptionDlgInterCall2);
	void OptionControlApply(CMkRecordset *pRs,	COptionDlgMobileNew *pOptionDlgMobileNew);
	void OptionControlApply(CMkRecordset *pRs, COptionDlgSmartQ* pOptionSmartQ);
	
	
	CComboBox m_BranchCombo;
	CButton m_ApplyAllBtn;
	CButton m_IDOK;
	CButton m_CloseBtn;
	CMyCheckButton	m_chkTest;

	CXTPListCtrl_Branch m_lstBranch;
	CBranchSel m_cBranch;
	CFlatMainEdit m_edtMain;
	CFlatSubEdit m_edtSub;
	CBranchMainBtn m_btnMain;
	CBranchSubBtn m_btnSub;
	

public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);	
	afx_msg void OnCbnSelchangeBranchCombo();
	afx_msg void OnBnClickedApplyAllBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedClose();	
};
