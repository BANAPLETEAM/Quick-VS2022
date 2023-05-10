#pragma once
#include "MyCheckButton.h"
#include "afxwin.h"


typedef struct {
	long nCompany;
	long nRNo;
	COleDateTime dtConn;
	CString strName;
	CString strGugun;
	CString strDong;
	CString strPosName;
	long nAllCount;
	long nDrivingCount;
	long nDrivingCharge;
	long nBalance;
	long nAllocGroup;
	long nWorkReportState;
	long nCarType;
	COleDateTime dtWait;
	COleDateTime dtWorkState;
	CString strPreSubwayLocation;
	CString strSubwayLocation;
	COleDateTime dtSubwayLocation;

	COleDateTime dtAllocate;
	CString strAllocate;
	CString strPreAllocate;
	BOOL bRcpIntMode1;
	//1 -- 출근처리
	//	2 -- 퇴근처리
	//	3 -- 강제퇴근 
	//	0 -- 미출근
} CONN_RIDER_STRUCT;


typedef map <pair<long, long>, CONN_RIDER_STRUCT*> CONN_RIDER_MAP;

class CAllocGroupListDlg;

class CConnListDlg2 : public CMyFormView
{
	DECLARE_DYNCREATE(CConnListDlg2)

public:
	CConnListDlg2();   // 표준 생성자입니다.
	virtual ~CConnListDlg2();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CONN_LIST_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()

	CXTPListCtrl2 m_List;
	CWnd *m_pParentWnd;

	CAllocGroupListDlg *m_pAllocGroupListDlg;
public:

	CONN_RIDER_MAP m_mapConn;
	void RefreshList(BOOL bDb = TRUE);
	//	afx_msg void OnClose();


	long m_nCompanyCode;
	BOOL m_bIntegrated;

	BOOL m_bAsc;
	int m_nSubItem;

	CButton m_SendMsgBtn;
	CButton m_CloseBtn;

	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSendMsgBtn();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnLvnDeleteallitemsList1(NMHDR *pNMHDR, LRESULT *pResult);

private:
	DWORD m_dwLastRefreshList;
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedMapBtn();
	afx_msg LONG OnCloseConnRiderMapDlg(WPARAM wParam, LPARAM lParam);

	void HideAllocList();
	void ShowAllocList();
	void MoveAllocList();
	CString GetFooterData();
	void DeleteMapData();
	void RefreshMap();
	void RefreshListReal();
	void RefreshListRealSubway();
	void UpdateDrivingCount();
	void FilterList();
	CString GetAbsentState(CONN_RIDER_STRUCT *st);
	CString GetSubWayWait(CONN_RIDER_STRUCT *st);
	long GetSubWayWaitInt(CONN_RIDER_STRUCT *st);
	CString GetLocationConsiderSunway(CONN_RIDER_STRUCT *st);

	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSetWorking();
	afx_msg void OnSetLeave();
	afx_msg void OnSendMsg();
	afx_msg void OnShowRiderInfo();
	afx_msg void OnVisibleCol();
	afx_msg void OnCbnSelchangeAllocateCombo();
	afx_msg void OnCbnSelchangeRiderCombo();
	afx_msg void OnEnChangeRiderEdit();
	afx_msg void OnEnChangeLocationEdit();
	afx_msg void OnViewExcel();
	afx_msg void OnSubWayAbsent();
	
	CComboBox m_cmbCar;
	CComboBox m_cmbRider;
	CComboBox m_cmbAllocate;
	CFlatEdit2 m_edtRNo;
	CFlatEdit2 m_edtLocation;
	CFlatEdit2 m_edtAlloc;
	afx_msg void OnCbnSelchangeCarCombo();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};
