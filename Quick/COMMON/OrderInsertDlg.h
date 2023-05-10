#pragma once


#include "msado27.tlh"
#include "afxwin.h"
// COrderInsertDlg 대화 상자입니다.



class CXTPListCtrl51 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
	{
		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();

		CString strPhone = pRecord->GetItem(4)->GetCaption(NULL);
		CString strMobile = pRecord->GetItem(5)->GetCaption(NULL);

		if(strPhone.GetLength() <= 6 && strMobile.GetLength() <= 6)
			pItemMetrics->clrBackground = RGB(255,225,225);

		CXTPListCtrl2::GetItemMetrics(pDrawArgs, pItemMetrics);
	}
};

class COrderInsertDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COrderInsertDlg)

public:
	COrderInsertDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COrderInsertDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ORDER_INSERT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedReadBtn();
	virtual BOOL OnInitDialog();
	BOOL ReadExcel();
	void ReadSheet();
	void OnCorpUpdate();
	void RefreshOtherPhone(CString strPrePhone1, CXTPGridRecord *pPreRecord);

	BOOL m_bChangeToCorp;
	BOOL m_bConnected;
	CString m_strPath;
	CString m_strConnection;

	CXTPListCtrl51 m_lstReport;

	ADODB::_Connection * m_pConnection; 
	ADODB::Fields *m_fields;
	ADODB::_RecordsetPtr   m_pRs;
	afx_msg void OnBnClickedCloseBtn();
	CComboBox m_cmbBranch;
	CComboBox m_cmbSheet;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeSheetCombo();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRefreshState();
	afx_msg void OnDelete();
	afx_msg void OnCorpInsert();
	afx_msg void OnCbnSelchangeBranchCombo();
	afx_msg void OnBnClickedOrderInsertBtn();
};
