#pragma once


// CTankTypeQDlg ��ȭ �����Դϴ�.
#include "DataBox.h"
#include "afxwin.h"

class CTankTypeQDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTankTypeQDlg)

public:
	CTankTypeQDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTankTypeQDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TANKVIEW_Q_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedApplyBtn();	
	afx_msg void OnReportCheckItem(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportClickItem(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	virtual BOOL OnInitDialog();
	void SetInitColumn(int nShowPartApply, BOOL &bCallCount, BOOL &bRiderCalculate, 
		BOOL &bRiderCount, BOOL &bBranchCalculate);
	CDataBox m_List;
	void RefreshList();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedRateAllBtn();
	CComboBox m_cmbRate;
	CComboBox m_cmbCheck;
	afx_msg void OnBnClickedCheckAllBtn();
	afx_msg void OnBnClickedCheckNotallBtn();
	void SetCheckFunction(BOOL bCheck);
	afx_msg void OnBnClickedButton1();

	long m_nCompany;
	long m_nServer;
};
