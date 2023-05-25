#pragma once

class CMyCall;

class CDIDListCtrl : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		if (nCol == 2)
			pItemMetrics->clrForeground = RGB(0, 0, 255);
	}
};

class CTelserverDIDRouteDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CTelserverDIDRouteDlg)

	enum { DIDROUTE_ADD= 0, DIDROUTE_DELETE, DIDROUTE_ALL_USE, DIDROUTE_ALL_UNUSE };

public:
	CTelserverDIDRouteDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTelserverDIDRouteDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_TELSERVER_DIDROUTE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	void SelectTelserverDIDRoute();

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnDIDRouteReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);

	afx_msg void OnBnClickedDIDRouteAddBtn();
	afx_msg void OnBnClickedDIDRouteDeleteBtn();
	afx_msg void OnBnClickedDIDRouteAllUseBtn();
	afx_msg void OnBnClickedDIDRouteAllUnuseBtn();

	BOOL SuccessDIDRouteAdd(CString strDID, CString strLine, BOOL bUse, CString strDesc);
	void SuccessDIDRouteDelete(CString strDID);
	void SuccessDIDRouteAllUse();
	void SuccessDIDRouteAllUnuse();

public:
	CMyCall *m_pCall;
	CDIDListCtrl m_lstDIDRoute;

	CString m_strDIDRouteDID;
	CString m_strDIDRouteLine;
	CString m_strDIDRouteDesc;
	BOOL m_bDIDRouteUse;
};

