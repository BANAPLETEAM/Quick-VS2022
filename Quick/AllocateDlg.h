#pragma once
#include "RoundStatic.h"

class CRcpView;

// CAllocateDlg 대화 상자입니다.
typedef struct {
	long nCompany;
	int		nRNo;
 }ALLOCATE_RIDER_INFO;

class CAllocateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CAllocateDlg)

public:
	CAllocateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocateDlg();

// 대화 상자 데이터입니다.
//	enum { IDD = IDD_ALLOCATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	int m_nRNo;


public:
	afx_msg void OnBnClickedOrderInsertBtn();
	afx_msg void OnBnClickedAllocateBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedAutoSelectBtn();
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeRnoEdit();
	afx_msg void OnCbnSelchangeCompanyCombo();
	afx_msg void OnNMDblclkDuplicateList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnDeleteitemDuplicateList(NMHDR *pNMHDR, LRESULT *pResult);
	
	virtual BOOL OnInitDialog();
	void RefreshList(long nAdminCode);
	void InsertListData();

	virtual BOOL DestroyWindow();	
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CRcpView *m_pRcpView;
	CXTPGridRecord *m_pSelRecord;
	CWnd *m_pParent;

	CXTPListCtrl2 m_List;
	CXTPListCtrl2 m_lstDuplicate;
	
	CComboBox m_cmbRider;
	CComboBox m_cmbCompany;

	CRoundStatic m_stcAvailRider;
	CRoundStatic m_stcTitle;

	CStatic m_stcCarType;
	CStatic m_stcRiderCount;
	CStatic m_stcCompany;
	CStatic m_stcCross;

	CImageList m_imgList;

	CFlatEdit2 m_edtCount;
	CFlatEdit2 m_edtRNo;

	long m_nDOrderTable;
	long m_nCompanyCode;
	long m_nTNo;
	long m_nState;
	long m_nRCompanyCode;

	int m_nCarType;

	BOOL m_bToRcpView;
	BOOL m_bChangeDisable;

	CString m_strRNo;
protected:
	virtual void OnCancel();
	virtual void OnOK();
};
