#pragma once

// CTakerPage3 �� ���Դϴ�.
#include "afxwin.h"


typedef struct {
	long	nNo;
	long	nCompany;
	CString	strTel;
	int		nState;
	int		nIdentityCardState;
	CString strIdentityCardUrl;
	int		nTelecomState;
	CString	strTelecomUrl;

	long	nPBXBoth;
	CString sPBXDocUrl;
	long	nPBXDocState;
	CString	sRandChar;
} TakePage3Struct;

class CXTPListCtrlLogiStaff4 : public CXTPListCtrl2
{
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		//CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();
		//CXTPGridRecordItem *pItem = pRecord->GetItem(6);
		//CString sBeforeCnt = pItem->GetCaption();

		CString strColName = pDrawArgs->pColumn->GetCaption();

		
		if(strColName  == "�������" || strColName == "��Ż�ǻ���" || strColName == "�ź�������")
		{

			CString strState = pDrawArgs->pItem->GetCaption(pDrawArgs->pColumn);			

			if(strState ==  "�ݷ�")							
				pItemMetrics->clrForeground = RGB(255, 0, 0);

			/*
			if(strState == "���")
				pItemMetrics->clrForeground = RGB(255,0,0);
			else if(strState ==  "����")
				pItemMetrics->clrForeground = RGB(0,0,255);
			else if(strState ==  "��������")				
				pItemMetrics->clrForeground = RGB(0,255,0);
			else if(strState ==  "�ݷ�")							
				pItemMetrics->clrForeground = RGB(0,0,255);
			else if(strState ==  "����")				
				pItemMetrics->clrForeground = RGB(189,85,242);
			*/				
		}

		if(strColName  == "��Ż�������" || strColName == "�ź���/����ڵ����")
		{
			pItemMetrics->clrForeground = RGB(0, 0, 255);
		}
		//if(strColName == "�߽Ź�ȣ" || strColName == "��ǥ/��Ȳ��" )
		/*
		if(strColName == "����" ) //|| strColName == "��ǥ/��Ȳ��" )
		{
			CString strState = pDrawArgs->pItem->GetCaption(pDrawArgs->pColumn);

			if(strState == "��ǥ��ȣ" ||strState == "��Ȳ�ǹ�ȣ" )
				pItemMetrics->clrForeground = RGB(0,0,255);

		}

		if(strColName == "��ǥ/��Ȳ��" ) //|| strColName == "��ǥ/��Ȳ��" )
		{
			CString strState = pDrawArgs->pItem->GetCaption(pDrawArgs->pColumn);

			if(strState.GetLength() > 0 )
				pItemMetrics->clrForeground = RGB(0,0,255);

		}
		*/
	}
};


 
class CTakerPage3 : public CMyFormView
{
	DECLARE_DYNCREATE(CTakerPage3)

protected:
	CTakerPage3();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CTakerPage3();

public:
	enum { IDD = IDD_TAKER_PAGE3 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	class CSMSDocViewDlg *m_pSMSDocViewDlg;
	CXTPListCtrlLogiStaff4 m_lstReport;
	virtual void OnInitialUpdate();
	void RefreshList();
	void RefreshSub(CMkRecordset *pRs, CXTPGridRecord *pRecord);
	void FilterList();

	void ShowDocView(CString strUrl);

	void InnerDeleteAllItem();
	void WorkGofromRefresh(long nModifyNo);
	//void OnBnClickedBranchMemoBtn();
	
	afx_msg void OnReportItemSMSCallBackLog(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg LONG OnReportRefresh(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedAllRegisterBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnToExcel();
	afx_msg void OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);


	afx_msg void OnMenuUse();
	afx_msg void OnMenuNotUse();
	afx_msg void OnMenCorpType0();
	afx_msg void OnMenCorpType1();
	afx_msg void OnMenuManager();
	afx_msg void OnMenuShowDetail();
	afx_msg void OnMenuShowLog();
	afx_msg void OnMenuCancelAgree();
		
	CComboBox m_cmbTelType;
	CFlatEdit2 m_edtSearch;
	 

	CMyStatic m_stc1;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnBnClickedRegisterBtn();
	afx_msg void OnReportHyperlinkClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedModifyBtn();

	CXTPGridRecord* FindRecordFromNo(long nNo);
	void UpdateMenuUse(BOOL bUse);
	BOOL RefreshOneRecord(long nNo, CXTPGridRecord *pRecord);
	void UpdateMenuCorpType(long nCorpType);
	CString GetWebFolder(long nServiceType, long nDocType);

	CMyStatic m_stc10;
	CMyStatic m_stc75;
	afx_msg void OnBnClickedShowBtn();
};


