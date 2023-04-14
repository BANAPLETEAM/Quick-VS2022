#pragma once

#include "explorer.h"
#include "POIDataNew.h"

// CWebChargeListDlg 대화 상자입니다.

class CWebChargeListDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWebChargeListDlg)

public:
	CWebChargeListDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebChargeListDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEB_CHARGELIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedStandartCheck();
	afx_msg void OnBnClickedExcelCheck();
	afx_msg void OnBnClickedChargeCheck();
	afx_msg void OnBnClickedEmailBtn();
	afx_msg void OnBnClickedChargeInqueryBtn2();
	afx_msg void OnBnClickedGroupInqueryBtn();
	afx_msg void OnBnClickedChargelistLoadBtn();

	void Refresh(CString sEmail);
	HRESULT GetPostData(CString strKey, LPVARIANT pvPostData);

	CPOIUnit *m_pDongPoi;

	CExplorer m_Explorer;
		
	CButton m_chkType;
	CButton m_chkCharge;
	CButton m_chkStandardCharge;	
	CButton m_chkOneThousand;
	CButton m_chkModifyData;

	CComboBox m_cmbChargeDongList;
	CComboBox m_cmbType;
	CComboBox m_cmbCarType;
	
	CFlatEdit2 m_edtDong;
	CFlatEdit2 m_edtDongDetail;
	CFlatEdit2 m_edtChargeName;
	CFlatEdit2 m_edtGroupName;
	CFlatEdit2 m_edtEmail;
	CFlatEdit2 m_edtTitle;
	CFlatEdit2 m_edtSendMailAddress;
	CFlatEdit2 m_edtCustomerName;
	CFlatEdit2 m_edtRow;
	CFlatEdit2 m_edtCol;
	
	CButton m_chkExcel;
	
	int m_nRow;
	int m_nCol;
	long m_nCompany;
	long m_nDongID;
	long m_nChargeID;
	long m_nGNo;	
};
