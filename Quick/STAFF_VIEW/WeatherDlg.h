#pragma once
#include "afxwin.h"

#include "Explorer.h"
#include "KingoHttp.h"
#include "MyButton.h"

// CWeatherDlg 대화 상자입니다.

class CExplorer1 : public CExplorer
{

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

class CWeatherDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CWeatherDlg)

public:
	CWeatherDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWeatherDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEATHER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void RefreshSite();
	void MakeFile(CString sHtml);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefreshBtn();

	CKingoHttp m_Http;
	CExplorer m_Explorer;
	CMyButton m_RefreshBtn;
	CComboBox m_DoCmb;
	CComboBox m_SiCmb;
	CComboBox m_YearCmb;
	CComboBox m_MonthCmb;

	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnCbnSelchangeDoCombo();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeSiCombo();
};
