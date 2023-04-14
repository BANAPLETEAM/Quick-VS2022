#pragma once


// CTestDlg2 대화 상자입니다.


#include "DataBox.h"
#include "SplitterControl.h"

class CGroupListCtrl : public CDataBox
{
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs, XTP_REPORTRECORDITEM_METRICS *pItemMetrics )
	{
		CString strColumn = pDrawArgs->pColumn->GetCaption();
		int nRow = pDrawArgs->pRow->GetIndex();
		int nCount = pDrawArgs->pControl->GetRows()->GetCount();
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nItemCol = pDrawArgs->pColumn->GetItemIndex();

		long nGroupOwnerCNo = GetItemDataLong2(nRow);
		if(nGroupOwnerCNo > 0)
		{	
			LOGFONT accesscontrol_static_lfont = {14,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};			
			pDrawArgs->pControl->GetPaintManager()->m_fontText.GetLogFont(&accesscontrol_static_lfont);
			pItemMetrics->clrForeground = RGB(0, 200, 0);
		}
	}
};

class CTabControl2 : public CXTPTabControl
{
	//DECLARE_DYNAMIC(CTabControl2)
public:
	CTabControl2(){}
	/*
	~CTabControl2(){
	int k = 0;
	}
	*/
protected:
	virtual void OnItemClick(CXTPTabManagerItem* pItem);
};

class CCorporationDlg2 : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CCorporationDlg2)

public:
	CCorporationDlg2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCorporationDlg2();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_CORPORATION_DLG2 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	afx_msg LONG OnTabItemClick(WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnLButtonUp( XTP_REPORTRECORDITEM_CLICKARGS* pClickArgs);
	afx_msg void OnNMClickGroupList(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMClickMemberList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnBnClickedPasteColBtn();
	afx_msg void OnBnClickedPasteRowBtn();
	afx_msg void OnMenuClickedCopyBtn();
	afx_msg void OnMenuClickedPasteColBtn();
	afx_msg void OnMenuClickedPasteRowBtn();
	afx_msg void  OnMenuClickedReceiptBtn();
	afx_msg void OnMenuClickedGroupOwnerBtn();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint /*point*/);
	afx_msg void OnBnClickedCopyBtn();
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnBnClickedReceiptBtn();
	afx_msg void OnBnClickedGroupOwner();
	afx_msg void OnStnClickedSplitter1();

	void LocalRefeshGroup();
	void RefreshMember();	
	void DoResize1(int delta);
	CWnd* GetTabItem(CString strCaption);
	CWnd* GetTabItem(int nTab);
	BOOL OnInitDialog();	
	void SetGNo(long nGNo);
	void Refresh();
	void BatchWork(BOOL bAll);
	void GroupOwnerSelect(long nGroupOwnerCNo);

	CXTPGridRow *m_pPreRow;
	CTabControl2 m_wndTabControl;
	CSplitterControl m_wndSplitter1;
	CGroupListCtrl m_GroupList;

	long m_nCustomerCompany;
	long m_nGNo;
	long m_nReceiptCNo;
	long m_nCopyCNo;
	long m_nCopyGNo;

	BOOL m_bChild;
	BOOL m_bPartView;
	BOOL m_bBegin;
	BOOL m_bIntegrated;
	BOOL m_bReceipt;
	BOOL m_bDragMode;
	
	CFlatEdit2 m_edtSearch;	
	CButton m_btnServerRefresh;	

	CStatic m_stcOption;
	CString m_strSearch;

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

