#pragma once
#include "afxwin.h"
#include "MyStaticRed.h"
#include "AllocateSMSFSettingDlg.h"

class CSmsDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSmsDlg)

public:
	CSmsDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmsDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

protected:

	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnEnChangeMsgEdit();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOrdernumCheck();
	afx_msg void OnBnClickedCnameCheck();
	afx_msg void OnBnClickedTotalCheck();
	afx_msg void OnBnClickedDisCheck();
	afx_msg void OnBnClickedPickupCheck();
	afx_msg void OnBnClickedPickupPhoneCheck();
	afx_msg void OnBnClickedEtcCheck();
	afx_msg void OnCbnSelchangeCombo1();	
	afx_msg void OnBnClickedStartCheck();
	afx_msg void OnBnClickedDestCheck();
	afx_msg void OnCbnSelchangeFirstPageCombo();
	afx_msg void OnCbnSelchangeSecondPageCombo();
	afx_msg void OnCbnSelchangeThirdPageCombo();

	virtual BOOL DestroyWindow();
	void RefreshDisplay();
	void SendPda(CStringArray &saMsg);
	CString MsgMake(ST_ALLOCATE_SMS *asi);
	CString MakeMsg();
	void MakeCallBackPhone();
	CString SearchFindTelNumber(CString str);
	CString GetRealNumber(CString strMobile, CString strPhone);
	CString GetAType();
	CString GetBType();
	CString GetCType();
	CString GetDType();
	CString GetEType();
	CString GetFType();
	void SetStatic();
	CString GetManager(long nPage);

	CAllocateSMSFSettingDlg m_AllocateSMSFSettingDlg;	

	CFlatEdit2 m_edtMsg;

	CButton m_chkOnePage;
	CButton m_btnSend;
	CButton m_chkOrderNum;
	CButton m_chkCName;
	CButton m_chkTotal;
	CButton m_chkDis;
	CButton m_chkPickup;
	CButton m_chkPickupPhone;
	CButton m_chkEtc;	
	CButton m_chkStart;
	CButton m_chkDest;

	CStatic m_stcFirst;
	CStatic m_stcSecond;
	CStatic m_stcThird;
	CMyStatic m_stcInfo;
    CMyStatic m_stcInfo2;
	CMyStatic m_stcInfo3;
	CMyStatic m_stcInfo4;
	CMyStatic m_stcInfo5;
	CMyStaticRed m_stcInfo6;

	CComboBox m_cmbSendType;
	CComboBox m_cmbFirstPage;
	CComboBox m_cmbSecondPage;
	CComboBox m_cmbThirdPage;

public:
	long m_nRCompany;
	long m_nRNo;
	long m_nNumber;
	long m_nTNo;
	long m_nRemainCount;
	long m_nNumOrder;
	long m_nTotal;
	long m_nCon;

	BOOL m_bOrderNum;
	BOOL m_bCName;
	BOOL m_bTotal;
	BOOL m_bDis;
	BOOL m_bPickup;
	BOOL m_bPickupPhone;
	BOOL m_bEtc;
	BOOL m_bDT;
	BOOL m_bSendPDA;

	COleDateTime m_dtRcp;

	CString m_strCName;
	CString m_strLocation;
	CString m_strEtc;
	CString m_strRiderPhone;
	CString m_strDDD;
	CString m_strStart;
	CString m_strDest;

	CString m_strTel[3];
	ST_ALLOCATE_SMS *m_ASI;
};
