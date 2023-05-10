#pragma once
#include "afxwin.h"

#include "Explorer.h"
#include "KingoHttp.h"
#include "MyButton.h"

// CWeatherDlg ��ȭ �����Դϴ�.

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
	CWeatherDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWeatherDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WEATHER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
