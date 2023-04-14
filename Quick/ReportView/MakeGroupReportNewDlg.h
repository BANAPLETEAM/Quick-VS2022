#pragma once

#include "FlatEdit2.h"

#include "Explorer.h"

class CMakeGroupReportNewDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CMakeGroupReportNewDlg)

public:
	CMakeGroupReportNewDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMakeGroupReportNewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAKE_GROUP_REPORT_NEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void OnChangeDate();
	void RefreshList();
	CString GetReportState(long nReportState);
	BOOL CheckDate(COleDateTime dtFrom, COleDateTime dtTo, BOOL bContiune = FALSE, long nRow = 0);
	double round( double value, int pos );
	void MakeReport();
	void LoadReport();
	BOOL IsMake();
	void ReInit();
	BOOL SendKindReport(int nSendType,  BOOL bReSend, BOOL nAutoSend);
	BOOL SendKindReportCheckData(int nSendType);
	HRESULT GetPostData(CString strKey, LPVARIANT pvPostData);
	void SendKindReportWeb(int nSendType,  BOOL bReSend);
	void ChangeReport();
	BOOL IsTimeValid(COleDateTime dt);
	long GetEditTextByLong(CFlatEdit2 *pEdit);

	afx_msg void OnBnClickedMakeBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	
	CXTPListCtrl21 m_lstReport;
	CButton		m_chkPayMent;
	CButton		m_chkBillPressCollection;
	COleDateTime m_dtFrom;
	COleDateTime m_dtTo;
	COleDateTime m_dtBillCollection;
	COleDateTime m_dtPayMent;	
	CDateTimeCtrl m_FromDT;
	CDateTimeCtrl m_ToDT;
	CDateTimeCtrl m_dtpBillCollection;
	CDateTimeCtrl m_dtpPayMent;
	CDateButton m_btnDate;

	BOOL m_bRefresh;
	CString m_strGNoList;
	long m_nGNo;
	long m_nCalculateCount;
	long m_nCalculateSum;
	long m_nCalculateTrans;


	long m_nNewMode;   // 신규 1 뷰 0
	long m_nGroupReportID; // 뷰  x > 0 

	CButton m_chkTestEmail;
	CExplorer m_Explorer;
	CFlatEdit2 m_edtReportNo;
	CFlatEdit2 m_edtCredit;
	CFlatEdit2 m_edtDiscountCharge;
	
	CFlatEdit2 m_edtSubToal;
	CFlatEdit2 m_edtTransCharge;
	
	CFlatEdit2 m_edtBillTotal;
	CFlatEdit2 m_edtTax;
	
	CFlatEdit2 m_edtUncollection;
	CFlatEdit2 m_edtCount;
	CFlatEdit2 m_edtDiscount;
	CComboBox m_cmbReportFirst;
	
	CComboBox m_cmbAddTaxApplyType;
	
	/*CFlatEdit2 m_edtGroupName;
	CFlatEdit2 m_edtGroupManager;
	CFlatEdit2 m_edtGroupManagerHP;
	CFlatEdit2 m_edtEmail;
	CFlatEdit2 m_edtEtc;*/

	CEdit m_edtGroupName;
	CEdit m_edtGroupManager;
	CEdit m_edtGroupManagerHP;
	CEdit m_edtEmail;
	CEdit m_edtEtc;
	
	CButton m_chkSMSSend;
	CFlatEdit2 m_edtSMSDate;
	
	CButton m_chkEmailSend;
	

	



	
	afx_msg void OnBnClickedEtcSaveBtn();
	
	afx_msg void OnBnClickedSendTaxViewBtn();
	afx_msg void OnBnClickedTestMailBtn();
	afx_msg void OnBnClickedGroupSettingBtn();
	afx_msg void OnEnChangeDiscountChargeEdit();
	afx_msg void OnCbnSelchangeAddtaxApplytypeCombo();
	afx_msg void OnBnClickedBillpressCheck();
	afx_msg void OnBnClickedPaymentCheck();
	afx_msg void OnClose();
};
