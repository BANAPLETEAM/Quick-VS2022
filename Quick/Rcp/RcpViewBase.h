#pragma once

#include "RcpViewDef.h"
#include "MyReportControl.h"
#include "PPTooltip.h"

class CRcpPageInfoForm;
class CRcpPageCTIForm;
class CRcpPageMapForm;
class CRcpPageMemoForm;
class CRcpPageWCountForm;
class CRcpDlg;
class CRcpPageRecordFileForm;
class CRcpPageMissingCallForm;


// CRcpViewBase 뷰입니다.

class CRcpViewBase : public CMyFormView
{
	DECLARE_DYNCREATE(CRcpViewBase)

protected:
	CRcpViewBase();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CRcpViewBase();
	virtual void OnInitialUpdate();
	virtual void MoveClient();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()

public:
	long m_nFormHeight;
	int m_nSavedFormHegiht;
	BOOL m_bDialogMode;
	CPPToolTip m_tooltip;
	CXTPPopupControl m_wndPopupControl;


public:
	CXTPGridSubListControl m_wndSubList;
	CMyReportControl m_xList;
	CRcpFormTabControl m_wndTabControl;
	CPtrArray m_arrSavedHideWnd;
	CCriticalSection m_csOrder;

	CRcpPageRecordFileForm* m_pRecordFileForm;
	CRcpPageMissingCallForm* m_pMissingCallForm;


public:
	void AddMapForm(BOOL bActive = FALSE);
	void InitForm();
	void LoadListFont(BOOL bRedraw);
	void RefreshStateColor();
	void LoadReportState();
	void SaveReportState(CString &strSave, long &nSize);
	void OnShowFieldChooser();

	void ShowAllControl(BOOL bShow, CWnd* pwndExcept = NULL);
	BOOL RcpCreate(CRcpDlg* pDlg, UINT nServiceType);

	void ChangeFormHeight(long nTop) { m_nFormHeight = nTop; MoveClient(); }
	void IncFormHeight() { m_nFormHeight += 10; MoveClient(); }
	void DecFormHeight() { m_nFormHeight -= 10; MoveClient(); }
	void SetFormHeightBig() { m_nFormHeight = TAB_FORM_HEIGHT_BIG; MoveClient(); }
	void SetFormHeightNormal() { m_nFormHeight = TAB_FORM_HEIGHT; MoveClient(); }
	void SetFormHeightMax();
	void SetFormHeightRestore();
	BOOL IsDialogMode() { return m_bDialogMode; }
};


