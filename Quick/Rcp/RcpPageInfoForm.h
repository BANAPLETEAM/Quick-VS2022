#pragma once

#include "MyListCtrl4.h"
#include "NewRadioBtn.h"

class CRcpPage;

// CRcpPageInfoForm 폼 뷰입니다.

class CRcpPageInfoForm : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpPageInfoForm)

protected:
	CRcpPageInfoForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpPageInfoForm();

public:
	enum { IDD = IDD_RCP_PAGE_INFO_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedGetMsgRadio();
	afx_msg void OnBnClickedRelMsgRadio();
	afx_msg void OnBnClickedGetAllocRadio();
	afx_msg void OnBnClickedRelAllocRadio();
	afx_msg void OnBnClickedMyCallCheck();
	afx_msg void OnBnClickedHideCrossCallCheck();
	afx_msg void OnBnClickedShowCrossCallCheck();
	afx_msg void OnBnClickedRefreshIcBtn();
	afx_msg void OnBnClickedScheduleOrderCheck();
	afx_msg void OnBnClickedWebOrderCheck();
	afx_msg void OnBnClickedWebOrderBtn();

	DECLARE_MESSAGE_MAP()

public:
	BOOL m_bInitialized;
	CFlatComboBox m_cmbNotice;

	CNewRadioBtn m_GetMsgBtn;
	CNewRadioBtn m_RelMsgBtn;
	CNewRadioBtn m_GetAllocBtn;
	CNewRadioBtn m_RelAllocBtn;
	CMyListCtrl4 m_NoticeList;
	CButton m_ShowNoticeBtn;
	CButton m_btnWebOrder;
	CButton m_chkWebOrder;
	CButton m_MyCallCheck;
	CButton m_HideCrossCallCheck;
	CButton m_ShowCrossCallCheck;
	CButton m_chkScheduleOrder;

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedShowNoticeBtn();
};


