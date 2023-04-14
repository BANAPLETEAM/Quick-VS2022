#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

#include "MyStaticGreen.h"
#include "FlatEdit2.h"
#include "MyButton.h"

// CTransInfoDlg 대화 상자입니다.

class CTransInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTransInfoDlg)

public:
	CTransInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTransInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRANS_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bNew;
	CString m_sTitle;
	virtual BOOL OnInitDialog();
	void Clear();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedUpdateBtn();
	CString GetStart();
	void SetData();

	CMyButton m_UpdateBtn;
	CMyButton m_ColseBtn;

	CDateTimeCtrl m_RegisterDateDtp;
	CDateTimeCtrl m_RegisterTimeDtp;
	CDateTimeCtrl m_ArrivalDateDtp;
	CDateTimeCtrl m_ArrivalTimeDtp;
	CDateTimeCtrl m_DepartureDateDtp;
	CDateTimeCtrl m_DepartureTimeDtp;

	CFlatEdit2	m_StartEdt;
	CFlatEdit2	m_DestEdt;
	CFlatEdit2	m_ExpressNameEdt;
	CFlatEdit2	m_ExpressNumberEdt;
	CFlatEdit2	m_ItemNoEdt;
	CFlatEdit2	m_NameEdt;
	CFlatEdit2	m_EtcEdt;

	CMyStaticGreen m_Stc1;
	CMyStaticGreen m_Stc2;
	CMyStaticGreen m_Stc3;
	CMyStaticGreen m_Stc4;
	CMyStaticGreen m_Stc5;
	CMyStaticGreen m_Stc6;
	CMyStaticGreen m_Stc7;
	CMyStaticGreen m_Stc8;
	CMyStaticGreen m_Stc9;
	CMyStaticGreen m_Stc10;

	COleDateTime m_dtRegister;
	COleDateTime m_dtDeparture;
	COleDateTime m_dtArrival;

	CString m_sStart;
	CString m_sDest;
	CString m_sExpressName;
	CString m_sExpressNumber;
	CString m_sItemNo;
	CString m_sName;
	CString m_sEtc;

	long m_nTNo;
	long m_nCompany;

	long m_nReturn; // 오더 접수보다 먼저 입력될경
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
