#pragma once


#include "PPTooltip.h"
#include "VirtualRecord.h"
#include "MyReportControl.h"

#define  WM_ALLOCATE		(WM_USER + 900)
#define  WM_READY_ALLOCATE	(WM_USER + 901)

class CAllocatePaneDlg : public CMyFormView
{
	DECLARE_DYNCREATE(CAllocatePaneDlg)

	
public:
	CAllocatePaneDlg();   // 표준 생성자입니다.
	virtual ~CAllocatePaneDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ALLOCATE_PANE_DLG };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();

	
	DECLARE_MESSAGE_MAP()
	
public:
	
	afx_msg void OnBnClickedRefreshBtn();	
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnBnClickedSendMsgBtn();
	afx_msg void OnEnChangeXtplistctrlEdit();
	afx_msg void OnEnSetfocusSearchEdit();	
	afx_msg void OnEnKillfocusSearchEdit();	
	afx_msg void OnBnClickedAllocateBtn();
	afx_msg LONG OnAllocate(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnReadyAllocate(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedNearorderBtn();
	afx_msg void OnBnClickedNearAllocateCheck();
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnEnChangeDepositEdit();
	afx_msg void OnStnClickedStatePicture();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedRightDockingBtn();
	afx_msg void OnBnClickedLeftDockingBtn();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedShowCompleteOrderCheck();

	void RefreshList();
	void InitRider();
	CString BetweenSetSlash(CString s1,CString s2);
	BOOL GetBitmapFromImageList(CImageList *imglist,int nIndex,CBitmap &bmp);
	int GetNearType(long nStartX1,long nStartY1, long nStartRealDongID,
		long nOrderStartX1, long nOrderStartY1, long nOrderStartRealDongID,  
		long nDestX2, long nDestY2, long nDestRealDongID, 
		long nOrderDestX2, long nOrderDestY2,long nOrderDestRealDongID, int nStartScope = 2,  int nDestScope = 2);
	
	
	void SetPaneDocking(BOOL bDocking){m_bDocking = bDocking;}
	BOOL GetPaneDocking(){return m_bDocking;}
	void DrawRiderInfo(CDC *pDC);
	void DrawEmptyInfo(CDC *pDC);
	void DrawInfoBox(CDC *pDC, CRect rc, BOOL bGreen = FALSE);
	void PrintLine(CDC *pDC, CRect &rc, CString strTitle, CString strText, 
		BOOL bNextSeparator = FALSE, COLORREF clrText = RGB(0, 0, 0));
	void RefreshOrderList();
	BOOL CheckRider();
	void NearAllocate();
	void SetTNo(long nTNo, BOOL bShareOrder = FALSE, long nShareCompany = 0, long nRiderCompany = 0, long nRNo = 0, BOOL bTodayOrder = FALSE);

	long GetTNo(){ return m_nTNo;}
	BOOL CheckAllocateData();
	void SetCustomerRefresh();
	void NearOrderRefresh(long nTNo);
	void AutoHide(BOOL bHide) { m_bAutoHide = bHide; }
	CString RemoveLeftZero(CString strText);

	CXTPListCtrl2 m_List;
	CXTPListCtrl2 m_nearReport;
	CXTFlatEdit m_edtSearch;
	CCriticalSection m_csOrder;
	MAP_RIDER_OWN_CALL2 m_mapRider;
	CMyReportControl m_xList;
	CPPToolTip m_tooltip;
	
	int m_nCount;
	long m_nTNo;	
	long m_nState;
	long m_nSelectedRNo;
	long m_nSelectedRCompany;
	long m_nShareCompany;
	long m_nRiderCompany;
	long m_nRNo;

	BOOL m_bDocking;
	BOOL m_bAutoHide;
	BOOL m_bShareOrder;
	BOOL m_bTodayOrder;

	CString m_strOrderCNo;
	CString m_strStartCNo;
	CString m_strDestCNo;

	CXTPListCtrl29 m_lstOrder;

	CButton m_chkNearAllocate;
	CButton m_chkShowCompleteOrder;

	CFlatEdit2 m_edtODONG;
	CFlatEdit2 m_edtOName;
	CFlatEdit2 m_edtOTel;
	CFlatEdit2 m_edtOEtc;
	CFlatEdit2 m_edtOMemo;
	CFlatEdit2 m_edtODetail;
	CFlatEdit2 m_edtSDONG;
	CFlatEdit2 m_edtSName;
	CFlatEdit2 m_edtSTel;
	CFlatEdit2 m_edtSEtc;
	CFlatEdit2 m_edtSDetail;
	CFlatEdit2 m_edtDDONG;
	CFlatEdit2 m_edtDName;
	CFlatEdit2 m_edtDTel;
	CFlatEdit2 m_edtDEtc;
	CFlatEdit2 m_edtDDetail;
	CFlatEdit2 m_edtEtc;
	CFlatEdit2 m_edtChargeSum;
	CFlatEdit2 m_edtDeposit;	
	CFlatEdit2 m_edtTNo;
	CFlatEdit2 m_edtState;
	CFlatEdit2 m_edtWNo;
	CFlatEdit2 m_edtTime;
	CFlatEdit2 m_edtOption;
	CFlatEdit2 m_edtChargeInfo;

	CStatic m_picState;
	CStatic m_RiderStatic;
	CStatic m_RiderStatic2;
	CMyStatic m_stcOrder;
	CMyStatic m_stcStart;
	CMyStatic m_stcDest;
	CMyStatic m_stcCharge;
	CMyStatic m_stcDeposit;
	CMyStatic m_stcOption;
	CMyStatic m_stcEtc;
	CMyStatic m_stcSearch;
	CMyStatic m_stcNearOrder;
	CMyStatic m_stcNearStart;
	CMyStatic m_stcNearDest;

	CComboBox m_cmbStartKm;
	CComboBox m_cmbDestKm;
};
