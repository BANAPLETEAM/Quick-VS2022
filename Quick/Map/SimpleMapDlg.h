#pragma once


#include "LogiMapNew.h"


#define SHOW_SIMPLE_MAP(dlg, AutoClose) 	\
	if(!dlg)\
	{\
		dlg = new CSimpleMapDlg(this);\
		dlg->CreateDlg(AutoClose);\
		dlg->ShowWindow(SW_SHOW);\
	}\
	else\
	{\
		dlg->ShowWindow(SW_SHOW);\
	}\


// CSimpleMapDlg 대화 상자입니다.

class CSimpleMapDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CSimpleMapDlg)

public:
	CSimpleMapDlg(UINT nID = CSimpleMapDlg::IDD, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSimpleMapDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SIMPLE_MAP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
public:
	CLogiMapNew m_wndMap;
	CWnd *m_pParent;
	BOOL m_bAutoDelete;
	BOOL m_bSendPOISelect;
	BOOL m_bStartPlace;

public:
	void CreateDlg(BOOL bAutoDelete = TRUE);
	CLogiMapNew *GetMap() { return &m_wndMap; }
	void OnCreateMap(long Value);
	void OnPOIClick(LPDISPATCH POI, long nFlag, long X, long Y);
	void SetSendPOISelect(BOOL bSend = TRUE, BOOL bStartPlace = TRUE) 
	{ m_bSendPOISelect = bSend; m_bStartPlace = bStartPlace;}
};
