#pragma once
#include "afxwin.h"
#include "BranchSel.h"
#include "SmsBaseDlg.h"
#include "CheckBitmap.h"
#include "msado27.tlh"

// CSmsNewBulkDlg 대화 상자입니다.

typedef struct{
	CString strPhone;
	BOOL bOverlap;
	BOOL bRiderPhone;
	BOOL bNosms;
} ST_SMS_FILTER;

class CEmoticonDlg;
class CSmsNewBulkConfirmDlg;
class CSmsNewBulkTestDlg;
class CSmsNewBulkFilterDlg;
class CSmsNewBulkMentDlg;

class CXTPListCtrlSms1 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetItemIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		BOOL bDefault = GetItemLong2(nRow);

		if(bDefault)
			pItemMetrics->clrBackground = RGB(180, 255, 180);
	}
};


typedef map<long, ST_SMS_FILTER> MAP_SMS_PHONE;

class CSmsNewBulkDlg : public CSmsBaseDlg
{
	DECLARE_DYNAMIC(CSmsNewBulkDlg)

public:
	CSmsNewBulkDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSmsNewBulkDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SMS_NEW_BULK_DLG };

protected:
	afx_msg void OnBnClickedMent();
	afx_msg void OnBnClickedFilter();
	afx_msg void OnPaint();

	afx_msg void OnBnClickedRemoveOverlapCheck();
	afx_msg void OnBnClickedRemoveRiderCheck();
	afx_msg void OnBnClickedRemoveNosmsCheck();
	afx_msg void OnBnClickedTest();
	afx_msg void OnBnClickedConfirmBtn();

	void OnDelete();
	void OnUpdate();

	afx_msg void OnDeletePhone();
	afx_msg void OnExcel();

	afx_msg LONG OnRecvMent(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnClickedButton(WPARAM wParam, LPARAM lParam);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CXTPListCtrl2 m_lstPhone;

	CCheckBitmap m_chkRemoveOverlap;
	CCheckBitmap m_chkRemoveRider;
	CCheckBitmap m_chkRemoveNosms;

	MAP_SMS_PHONE m_mapRealPhone;
	MAP_PHONE m_mapOverlap;


public:
	CSmsNewBulkConfirmDlg *m_pConfirmDlg;
	CSmsNewBulkTestDlg *m_pTestDlg;
	CSmsNewBulkFilterDlg *m_pFilterDlg;
	CSmsNewBulkMentDlg *m_pMentDlg;;

	CCheckBitmap m_chkReserve;
	CDateTimeCtrl m_dtpRedate;
	CDateTimeCtrl m_dtpRetime;

	BOOL m_bFirstRefresh;

	afx_msg void OnCbnSelchangeExcelSheetCombo();
	afx_msg void OnBnClickedLoadExcelBtn();
	afx_msg void OnBnClickedLoadTextBtn();
	afx_msg void OnBnClickedSendBtn();
	CComboBox m_cmbExcelSheet;

	void InitData(MAP_PHONE *pMap);

	BOOL ReadExcel();
	void ReadSheet();
	void RefreshList();
	void FilterData();
	void AddRealPhoneMap(CString strPhone);
	void DeleteRealPhoneMap(CString strPhone);
	BOOL IsNosmsPhone(CString strPhone);
	BOOL IsOverPhone(CString strPhone);
	BOOL IsRiderPhone(CString strPhone);

	CString m_strPath;
	CString m_strConnection;
	BOOL m_bConnected;

	ADODB::_Connection * m_pConnection; 
	ADODB::Fields *m_fields;
	ADODB::_RecordsetPtr   m_pRs;

	afx_msg LONG OnChangeBrachCode(WPARAM wParam, LPARAM lParam);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	void OpenEmotionDlg(long nID, CWnd *pWndMain);

	afx_msg void OnBnClickedSelectBtn1();
	afx_msg void OnBnClickedUpdateBtn1();
	afx_msg void OnBnClickedEmoticonBtn1();
	afx_msg void OnBnClickedSelectBtn2();
	afx_msg void OnBnClickedUpdateBtn2();
	afx_msg void OnBnClickedEmoticonBtn2();
	afx_msg void OnBnClickedInsertPhoneBtn();
	CEdit m_edtInsertPhone;
};
