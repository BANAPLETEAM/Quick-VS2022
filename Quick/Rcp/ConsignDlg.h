#pragma once


#include "DataBox.h"
#include "poidata.h"
#include "POIDataNew.h"


// CConsignDlg 대화 상자입니다.

class CConsignDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CConsignDlg)

public:
	CConsignDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConsignDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONSIGN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edtDest;
	CString m_sDest;
	CEdit m_edtTerminal;
	CString m_sTerminal;
	CEdit m_edtEtc;
	CDataBox m_Data;
	afx_msg void OnBnClickedSendOk();
	afx_msg void OnBnClickedNewBtn();
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnBnClickedCancel();

	void RefreshListArea();
	void RefreshListTerminal();
	CPOIUnit *m_pStartPoi;
	CPOIUnit *m_pDestPoi;
	virtual BOOL OnInitDialog();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * result);
	
	
	long m_nCharge;
	
	long GetDistance(long nPOIID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT nIDEvent);
};
