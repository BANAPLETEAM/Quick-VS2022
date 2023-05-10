#pragma once
#include "afxwin.h"


// CDirectChargeInputDlg1 ��ȭ �����Դϴ�.

class CDirectChargeInputDlg1 : public CMyDialog
{
	DECLARE_DYNAMIC(CDirectChargeInputDlg1)

public:
	CDirectChargeInputDlg1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDirectChargeInputDlg1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIRECT_CHARGE_INPUT_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CXTPListCtrl2 m_lstCharge;
	CXTPListCtrl2 m_lstChargeGNo;
	CXTPListCtrl2 m_lstChargeCNo;

	CPOIUnit *m_pStartPoi;
	CPOIUnit *m_pDestPoi;

	long GetExceptionID(CPOIUnit *pPoi);
	void RefreshChargeList();
	void RefreshChargeGNoList();
	void RefreshChargeCNoList();
	void SetRecordText(CXTPGridRecord *pRecord, long nCol, long nItem);
	void SetRecordText(CXTPGridRecord *pRecord, long nCol, CString strItem);
	long GetRecordText(CXTPGridRecord *pRecord, long nCol);

	BOOL m_bUpdateChargeOk;
	long m_nCompany;
	long m_nStartDongID;
	long m_nDestDongID;
	long m_nGNo;
	long m_nCNo;
	afx_msg void OnBnClickedSaveBtn();
	CButton m_chkTwoWay;
	CButton m_chkTwoWayGNo;
	CButton m_chkTwoWayCNo;
	afx_msg void OnBnClickedSaveGnoBtn();
	afx_msg void OnBnClickedSaveCnoBtn();
	afx_msg void OnBnClickedHtypeModifyBtn();
};
