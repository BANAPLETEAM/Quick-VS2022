#pragma once
#include "afxwin.h"
#include "RiderTraceCtrl.h"

// COrderProcessStateDlg 대화 상자입니다.

class COrderProcessStateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(COrderProcessStateDlg)

public:
	COrderProcessStateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COrderProcessStateDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ORDER_PROCESS_STATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void MakeMsg();
	void RefreshCombo(BOOL bDbRefresh);
	void FillData();
	LONG OnRefreshRiderPos(WPARAM wParam, LPARAM lParam);
	CString GetStateReplaceMent(CString strMent);
	void DrawStcText(CDC *pDC, COLORREF rgbText, COLORREF rgbMainText, CString sDisplayName, CRect rc, long nType, CFont *font);
	BOOL GetBitmapFromImageList(CImageList *imglist,int nIndex,CBitmap &bmp);	
	void Refresh();
	void OnCancel();
	void LoadPhoneMenu();
	long m_nCNo;

	afx_msg void OnBnClickedRefreshButton();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnBnClickedSignBtn();
	afx_msg void OnBnClickedRiderChk();
	afx_msg void OnBnClickedCustomerCheck();
	afx_msg void OnBnClickedSendSmsCustomerBtn();
	afx_msg void OnBnClickedSendSmsRiderBtn();
	afx_msg void OnBnClickedSendPdaBtn();
	afx_msg void OnBnClickedSaveMentBtn();
	afx_msg void OnCbnSelchangeMentCombo();
	afx_msg LONG OnGetDistance(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuPhone(UINT nFlag);
	afx_msg void OnBnClickedRcpBtn();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedChangePhoneBtn();
	afx_msg void RefreshOrderList();
	afx_msg void OnBnClickedChangePhoneRiderBtn();

	CRiderTraceCtrl m_wndRiderMap;
	ST_ORDER_SMS m_stSmsInfo;

	CXTPListCtrl2 m_lstOrder;
	
	CMyStatic m_picState;
	CMyStatic m_stcState;
	CMyStatic m_stcDt1;
	CMyStatic m_stcDt3;
	CMyStatic m_stcDtFinal;
	CMyStatic m_stcStart;
	CMyStatic m_stcRider;
	CMyStatic m_stcDest;
	CMyStatic m_stcLeft;
	CMyStatic m_stcTime;
	CMyStatic m_stcCur;
	CMyStatic m_stcCustomerPhone;
	CMyStatic m_stcRiderPhone;
	CMyStatic m_stcDraw;
	CMyStatic m_stc1;
	CMyStatic m_stc3;
	CMyStatic m_stc4;
	CMyStatic m_stcRiderSMSPhone;
	CMyStatic m_stcCustomerSMSPhone;

	CMyStatic m_stc5;
	CMyStatic m_stcDtPickup;
	CMyStatic m_stcRiderPickup;

	CComboBox m_cmbMent;

	CStringArray m_arryPhone;

	long m_nTNo;
	long m_nStartPosX;
	long m_nStartPosY;
	long m_nDestPosX;
	long m_nDestPosY;
	long m_nRiderPosX;
	long m_nRiderPosY;
	long m_nRiderCompany;
	long m_nRNo;

	CBitmap bitmap;

	CButton m_chkRider;
	CButton m_chkCustomer;

	CFlatEdit2 m_edtSMS;
	BOOL m_bPhoneMenuRiderType;

	CWnd *m_pParent;
	BOOL m_bHasRiderInfo;
	afx_msg void OnBnClickedMapButton();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
