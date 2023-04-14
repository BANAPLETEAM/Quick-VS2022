#pragma once

#include "POIData.h"
#include "POIDataNew.h"

// CConsignModiDlg ��ȭ �����Դϴ�.

class CConsignModiDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CConsignModiDlg)

public:
	CConsignModiDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConsignModiDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONSIGN_MODI_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbTerminal;
	CEdit m_edtStart;
	CEdit m_edtDetail;
	CEdit m_edtEnd;
	CEdit m_edtInterval;
	CComboBox m_cmbCarWay;
	CEdit m_edtDest;
	CEdit m_edtDestDetail;
	CEdit m_edtEtc;
	CEdit m_edtCharge;
	CEdit m_edtTel;
	long m_nMod;
	
	virtual BOOL OnInitDialog();
	void SearchData();
	long m_nPOIID;
	void EditConsign();
	void NewConsign();
	
	
	
	void SearchStartSection();
	CPOIUnit *m_pDestPoi;
	BOOL SearchRegion(long nFlag);

	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSaveOk();
	afx_msg void OnEnChangeDestEdit();
	
	afx_msg void OnTimer(UINT nIDEvent);
	
};
