#pragma once


#include "MyPaintManager.h"
#include "afxwin.h"

#define ROW_SPACE 2
#define ROW_HEIGHT 15


static COLORREF colorText17[11] = {RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF), RGB(0x00, 0x00, 0x33), 
RGB(0x33, 0x00, 0x00), RGB(0x33, 0x99, 0x00), RGB(0x99, 0x00, 0x00)};
static COLORREF colorBack17[11] = {RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF), RGB(0x00, 0x00, 0x33), 
RGB(0x33, 0x00, 0x00), RGB(0x33, 0x99, 0x00), RGB(0x99, 0x00, 0x00)};


class CXTPListCtrl56 : public CXTPListCtrl2
{
public:
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics) 
	{		  
		CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();

		long nCol = pDrawArgs->pColumn->GetIndex();
		long nRow = pDrawArgs->pRow->GetIndex(); 
		CString strTemp = pItemMetrics->strText;
		CString strItem = ((CXTPGridRecordItemText*)pRecord->GetItem(3))->GetCaption(NULL);

		if(strItem == "중지")
			pItemMetrics->clrBackground = RGB(255,200,200);
   
		if(nCol<= 2)
		{
			pItemMetrics->pFont = m_pfntBold;
		} 

		if(GetItemLong3(nRow) == TRUE)
		{
			pItemMetrics->clrBackground = RGB(125, 125, 255);
		} 
  
		if(nCol == 4) 
		{ 
			pItemMetrics->pFont = m_pfntBold;
			long nGrade = (long)GetItemData(pRecord);
			pItemMetrics->clrForeground = colorText17[nGrade];
			pItemMetrics->clrBackground = colorBack17[nGrade];
		}

		CXTPListCtrl2::GetItemMetrics(pDrawArgs, pItemMetrics);
	}
};

typedef struct{
	long nID;
	long nGrade;
	CString strGroupName;
	long nPanaltyDelayTime4Order;
	long nPanaltyDelayTime4MyOrder;
	long nPanaltyDelayTime4OCOrder;
	long nPanaltyTypeShowOrder;
	long nPenaltyDelayTime4MyCorpOrder;
	BOOL bAutoAllocType;
	BOOL bAutoGradeAdjByLogic;
	long nCompanyAutoAllocType;

	BOOL bAutoDownGrade;
	long nAutoDownGradeDay;
	long nAutoDownGradeCount;

	long nTextColor;
	long nBackColor;
}ALLOC_GROUP;


class CStaffPage21Record : public CXTPGridRecord
{
public:
	CStaffPage21Record::CStaffPage21Record(ALLOC_GROUP st)
	{
		m_stAlloc = st;
		AddItem(new CXTPGridRecordItemText(""));
	}

	void CStaffPage21Record::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{   
		CDC *pDC = pDrawArgs->pDC;
		CStaffPage21Record *pRecord = (CStaffPage21Record*)pDrawArgs->pRow->GetRecord();
		ALLOC_GROUP st = pRecord->m_stAlloc;

		if((st.nTextColor == st.nBackColor) ||
			(st.nGrade == 0))
		{
			pItemMetrics->clrBackground = RGB(255, 255, 255);
			pItemMetrics->clrForeground = RGB(0, 0, 0);
		}
		else
		{
			pItemMetrics->clrBackground = st.nBackColor;
			pItemMetrics->clrForeground = st.nTextColor;
		}
	}

	ALLOC_GROUP m_stAlloc;

};

class CStaffFormPaintManager17 : public CMyPaintManager
{
public:

	CStaffFormPaintManager17::CStaffFormPaintManager17()
	{		
	}

	CStaffFormPaintManager17::~CStaffFormPaintManager17()
	{
	}
  

	int GetRowHeight(CDC* /*pDC*/, CXTPGridRow* pRow)
	{
		return (m_nRowHeight * 5) + 12;  
	} 

	void DrawItemCaption(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, 
		XTP_REPORTRECORDITEM_METRICS* pMetrics)
	{		
		
		int nCol = pDrawArgs->pColumn->GetIndex();
		int nRow = pDrawArgs->pRow->GetIndex();
		CString strText = pMetrics->strText;
		CRect rc = pDrawArgs->rcItem;
		CDC *pDC = pDrawArgs->pDC;	

		CStaffPage21Record *pRecord = (CStaffPage21Record*)pDrawArgs->pRow->GetRecord();
		ALLOC_GROUP st = pRecord->m_stAlloc;
 
		if(st.nGrade != 0)
		{ 
			CRect rcTitle = rc; 
			rcTitle.top = rc.top + 2; 
			rcTitle.bottom = rcTitle.top + 23;
			rcTitle.left = rc.left + 7;

			CString strText = st.strGroupName + " " + "[" + LF->GetStringFromLong(st.nGrade) + "등급]";

			pDC->SelectObject(m_FontManager.GetFont("맑은 고딕", 19, FW_BOLD));
			pDC->DrawText(strText, rcTitle, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

			pDC->SelectObject(m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
			CRect rcDelayTime = rcTitle; 
			rcDelayTime.left = rcDelayTime.left + 7;
 
			//////////왼쪽(딜레이시간) 
  
			rcDelayTime.top = rcDelayTime.bottom + 4; rcDelayTime.bottom = rcDelayTime.top + ROW_HEIGHT; 
			strText = "오더 딜레이 : " + LF->GetStringFromLong(st.nPanaltyDelayTime4Order) + "초";
			pDC->DrawText(strText, rcDelayTime, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

			rcDelayTime.top = rcDelayTime.bottom + ROW_SPACE; rcDelayTime.bottom = rcDelayTime.top + ROW_HEIGHT; 
			strText = "자사 딜레이 : " + LF->GetStringFromLong(st.nPanaltyDelayTime4MyOrder) + "초";
			pDC->DrawText(strText, rcDelayTime, DT_VCENTER | DT_LEFT | DT_SINGLELINE); 

			rcDelayTime.top = rcDelayTime.bottom + ROW_SPACE; rcDelayTime.bottom = rcDelayTime.top + ROW_HEIGHT;
			strText = "타사 딜레이 : " + LF->GetStringFromLong(st.nPanaltyDelayTime4OCOrder) + "초";
			pDC->DrawText(strText, rcDelayTime, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

			rcDelayTime.top = rcDelayTime.bottom + ROW_SPACE; rcDelayTime.bottom = rcDelayTime.top + ROW_HEIGHT;
			strText = "자사 법인 딜레이 : " + LF->GetStringFromLong(st.nPenaltyDelayTime4MyCorpOrder) + "초";
			pDC->DrawText("", rcDelayTime, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			//pDC->DrawText(strText, rcDelayTime, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

			////////////// 오른쪽 
 
			CRect rcEtc = rcTitle;       
			//rcEtc.top = rcEtc.bottom + 9; rcEtc.bottom = rcEtc.top + 15; 
			rcEtc.top = rcTitle.bottom + 4; 
			rcEtc.bottom = rcEtc.top  + ROW_HEIGHT;  
			rcEtc.left = rcEtc.left + 160;

			if(st.nPanaltyTypeShowOrder == 0)
				strText = "오더보기 : 전체공유콜";
			else if(st.nPanaltyTypeShowOrder == 1)
				strText = "오더보기 : 1차공유콜";
			else if(st.nPanaltyTypeShowOrder == 2)
				strText = "오더보기 : 기사소속콜";

			pDC->DrawText(strText, rcEtc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

			if(st.nCompanyAutoAllocType == 0)
				strText = "자동배차 : 미사용";
			else
			{
				if(st.bAutoAllocType == 1)
					strText = "자동배차 : 적용";
				else
					strText = "자동배차 : 미적용";
			}
	
			rcEtc.top = rcEtc.bottom + ROW_SPACE; rcEtc.bottom = rcEtc.top + ROW_HEIGHT;
			pDC->DrawText(strText, rcEtc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

			rcEtc.top = rcEtc.bottom + ROW_SPACE; rcEtc.bottom = rcEtc.top + ROW_HEIGHT;
			strText = st.bAutoGradeAdjByLogic ? "자동등급조정 : 적용" : "자동등급조정 : 미적용";
			pDC->DrawText(strText, rcEtc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

			rcEtc.top = rcEtc.bottom + ROW_SPACE; rcEtc.bottom = rcEtc.top + ROW_HEIGHT;

			if(st.bAutoDownGrade == TRUE)
			{
				strText = "자동등급하향 : " + LF->GetStringFromLong(st.nAutoDownGradeDay) + "일 " + LF->GetStringFromLong(st.nAutoDownGradeCount) + "건";
			}
			else
				strText = "자동등급하향 : 미적용";

			pDC->DrawText(strText, rcEtc, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
			}
		else
		{
			pDC->SelectObject(m_FontManager.GetFont("맑은 고딕", 28, FW_BOLD));
			pDC->DrawText("그룹 등록 안함", rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		}
 	}
};

class CStaffPage21 : public CMyFormView
{
	DECLARE_DYNCREATE(CStaffPage21)

protected:
	CStaffPage21();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CStaffPage21();

public:
	enum { IDD = IDD_STAFF_PAGE21 };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDragMode;
	CXTPGridControl m_lstGrade;
	CXTPListCtrl56 m_lstRider;

	void RefreshList();
	void RefreshRiderList();

	void SearchFilter();
	void InsertCombo();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRefreshGradeBtn();
	afx_msg void OnBnClickedRefreshRiderBtn();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/);
	void ChangeRiderGroup(ALLOC_GROUP st);
	CComboBox m_cmbType;
	CFlatEdit2 m_edtSearch;
	afx_msg void OnEnChangeSearchEdit();
	afx_msg void OnCbnSelchangeTypeCombo();
	afx_msg void OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnReportItemClickRider(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	CMyStatic m_stcHelp;
	void RefreshRiderListOne(long nItem, long nRiderCompany, long nRNo);
	void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/);
	afx_msg void OnBnClickedSendMsgBtn();
};


