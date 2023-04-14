#pragma once

#include "ColorListCtrl.h"
#include "ReportForm5.h"
#include "DataBox.h"
#include "OtherRegionBranchDlg.h"
// CShareReportRateDlg6 폼 뷰입니다.


//typedef map<CString, CXTPGridRecord*> CITY_MAP2;

typedef map<CString, CString> GROUP_MAP2;  // 왼쪽 도시그룹

typedef vector<CMyXTPGridRecord*> CONSIGNCOMPANY_VEC;

class CShareReport6 : public CDataBox
{

	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pItemMetrics )
	{
		CString strColumn = pDrawArgs->pColumn->GetCaption();
		int nRow = pDrawArgs->pRow->GetIndex();
		int nCount = pDrawArgs->pControl->GetRows()->GetCount();
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nItemCol = pDrawArgs->pColumn->GetItemIndex();

		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pDrawArgs->pRow->GetRecord();

		CString sContent = pDrawArgs->pItem->GetCaption(pDrawArgs->pColumn);

		CString sCity = GetItemDataString(nRow);
		if(sCity.GetLength() > 0 &&  pDrawArgs->pRow->GetRecord()->GetChilds()->GetCount() > 0)
		{	
			LOGFONT accesscontrol_static_lfont = {14,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};			
			pDrawArgs->pControl->GetPaintManager()->m_fontText.GetLogFont(&accesscontrol_static_lfont);
			if(nCol ==0)
				pItemMetrics->clrBackground = RGB(200, 255, 200);
		}

		if( pDrawArgs->pRow->GetRecord()->GetChilds()->GetCount() ==  0)
		{
			/*if(nCol == 4 && pRecord->GetItemDataLong3() > 0)
				pItemMetrics->clrBackground = RGB(255, 0,0);*/
			if(nCol == 3 )
				pItemMetrics->clrBackground = RGB(255 ,0,0);
			else if(nCol >= 4 && nCol <= 7 )
			{
					if( pRecord->GetItemDataInt() == 0 || pRecord->GetItemDataInt() == 2 ) // 0, 2 신규, 변경
						pItemMetrics->clrBackground = RGB(255, 255,0);
					else
						pItemMetrics->clrBackground = RGB(230, 230, 255);
			}
			else if(nCol == 8 && pRecord->GetItemDataLong3() > 0)
				pItemMetrics->clrBackground = RGB(255, 0,0);
			else 
				pItemMetrics->clrBackground = RGB(230, 230, 255);
			


		}



	}

};

class CShareReportRateDlg6 : public CMyFormView
{
	DECLARE_DYNCREATE(CShareReportRateDlg6)

protected:
	CShareReportRateDlg6();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CShareReportRateDlg6();
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

protected:
	
public:
	enum { IDD = IDD_SHARE_REPORT_RATE_DLG6 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	CShareReport6 m_SettingReport;
	CXTPListCtrl2 m_lstReport;
	CFlatEdit2 m_edtSearch;

	CITY_MAP m_map2;
	//COMPANY_APPLY_FROM_CITY_MAP3 m_mapCitySeing;
	CONSIGNCOMPANY_VEC m_vecConsignCompany;

	GROUP_MAP2 m_gpMap2;  // 왼쪽 그룹
	
public:
	void OnViewExcel();
	void InitRegionGroup();
	void CompanyRefreshList();
	BOOL IsTransCheckMode();
	CString GetGroupRegion(CString sCity);
	BOOL GeneralCheckData();
	BOOL CheckData();
	CMyXTPGridRecord*  InitSettingRegionGroup(CString sCity);
	CMyXTPGridRecord* GetParentSettingRecord(CString sCity);
	void LinkRefreshList();
	BOOL IsConsignService(long nShareCode);
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnReportLogItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedRefreshBtn();
	afx_msg void OnBnClickedLinkBtn();
	afx_msg void OnBnClickedLinkModifyBtn();
	afx_msg void OnBnClickedRejectBtn();
	afx_msg void OnBnClickedAcceptBtn();
};


