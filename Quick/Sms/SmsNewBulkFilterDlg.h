#pragma once

#include "FileToReportControl.h"
// CSmsNewBulkFilterDlg ��ȭ �����Դϴ�.

class CSmsNewBulkFilterDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsNewBulkFilterDlg)

public:
	CSmsNewBulkFilterDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSmsNewBulkFilterDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SMS_NEW_BULK_FILTER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CFileToReportControl m_cFileReport1;
	CFileToReportControl m_cFileReport2;

	CXTPListCtrl2 m_lstPhone1;
	CComboBox m_cmbExcelSheet1;
	CEdit m_edtPhone1;
	CXTPListCtrl2 m_lstPhone2;
	CComboBox m_cmbExcelSheet2;
	CEdit m_edtPhone2;

	CXTPListCtrl2 m_lstResult;

	afx_msg void OnBnClickedLoadExcelBtn1();
	afx_msg void OnBnClickedLoadExcelBtn2();
	afx_msg void OnCbnSelchangeExcelSheetCombo1();
	afx_msg void OnCbnSelchangeExcelSheetCombo2();
	afx_msg void OnBnClickedLoadTextBtn1();
	afx_msg void OnBnClickedLoadTextBtn2();
	afx_msg void OnBnClickedAddPhoneButton1();
	afx_msg void OnBnClickedAddPhoneButton2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedAddReportBtn();
	afx_msg void OnBnClickedMinusReportBtn();

	void MakeResult(BOOL bPlus);
	afx_msg void OnBnClickedExcelBtn();
};
