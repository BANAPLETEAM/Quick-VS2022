#pragma once
#include "databox.h"
#include "afxwin.h"

class CRiderAllocateLimit : public CDataBox
{
public:
	void CRiderAllocateLimit::GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nRow = pDrawArgs->pRow->GetIndex();

		if(nCol == 1 || nCol == 3)
		{	
			LOGFONT accesscontrol_static_lfont = {18,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"돋움"};			
			pDrawArgs->pControl->GetPaintManager()->m_fontText.GetLogFont(&accesscontrol_static_lfont);
			pItemMetrics->clrBackground = RGB(220, 230, 220);
			//pItemMetrics->clrForeground = RGB(0, 200, 0);
		}

		if(this->GetItemDataString(nRow) == "0" && nCol == 8)
		{
			pItemMetrics->clrBackground = RGB(220, 230, 220);
			//pItemMetrics->clrForeground = RGB(0, 0, 255);
		}
		else if(this->GetItemDataString(nRow) == "1" && nCol == 5)
		{
			pItemMetrics->clrBackground = RGB(220, 230, 220);
			//pItemMetrics->clrForeground = RGB(0, 0, 255);
		}
		else if(this->GetItemDataString(nRow) == "2" && (nCol == 6 || nCol == 7) )
		{
			pItemMetrics->clrBackground = RGB(220, 230, 220);
			//pItemMetrics->clrForeground = RGB(0, 0, 255);
		}
	}

};

// CRiderAllocateDlg 대화 상자입니다.

#define  RIDER_ALLOCATE_LIMIT_SEARCH 0
#define  RIDER_ONLY_SEARCH 1

class CRiderAllocateDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CRiderAllocateDlg)

public:
	CRiderAllocateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRiderAllocateDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_RIDER_ALLOCATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	int m_nSearchType;
	
	DECLARE_MESSAGE_MAP()
public:
	long m_nGetRiderCompany;
	long m_nGetRNo;
	CString m_strGetRName;
	afx_msg void OnBnClickedCloseBtn();

	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);

	virtual BOOL OnInitDialog();
	CXTPListCtrl2 m_List;
	CFlatEdit2 m_edtSearch;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SearchRiderList();

	long GetRiderCompany() {return m_nGetRiderCompany;}
	long GetRiderNo() {return m_nGetRNo;}
	CString GetRiderName() {return m_strGetRName;}

	afx_msg void OnBnClickedSearchBtn();
};
