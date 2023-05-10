#pragma once


#include "LogiMapNew.h"
#include "SearchPOIDlg.h"
#include "afxwin.h"



// CHolidayDeliveryInfoDlg 대화 상자입니다.

class CHolidayDeliveryInfoDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CHolidayDeliveryInfoDlg)

public:
	CHolidayDeliveryInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHolidayDeliveryInfoDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_HOLIDAY_DELIVERY_INFO_DLG2 };

protected:
	afx_msg void OnBnClickedOkBtn();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CExplorer m_explorer;
	CString m_strURL;
	static BOOL m_bHolidayCompany;
	void InitData();
	static BOOL IsHolidayCompany(BOOL bIgnoreInsert);
	DECLARE_EVENTSINK_MAP()
	void BeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
