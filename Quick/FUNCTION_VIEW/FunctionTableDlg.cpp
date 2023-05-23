// FunctionTableDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "FunctionTableDlg.h"

 
// CFunctionTableDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFunctionTableDlg, CMyDialog)

CFunctionTableDlg::CFunctionTableDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CFunctionTableDlg::IDD, pParent)
{

}

CFunctionTableDlg::~CFunctionTableDlg()
{
}

void CFunctionTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FUNC_COMBO, m_cmbFunc);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	
}


BEGIN_MESSAGE_MAP(CFunctionTableDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_CBN_SELCHANGE(IDC_FUNC_COMBO, &CFunctionTableDlg::OnCbnSelchangeFuncCombo)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CFunctionTableDlg::OnEnChangeSearchEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnReportItemDblClick)
END_MESSAGE_MAP()


// CFunctionTableDlg 메시지 처리기입니다.

void CFunctionTableDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

BOOL CFunctionTableDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	m_btnDate.OnMenuYesterday();

	InitFunc();

	//SetResize(IDC_LIST1, sizingRightBottom);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CFunctionTableDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CFunctionTableDlg::OnCbnSelchangeFuncCombo()
{
	InitFunc();
}

void CFunctionTableDlg::InitFunc()
{
	static BOOL bInit = FALSE;

	if(bInit) return;
	else bInit = TRUE;


	char buffer[12];
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_function_table");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);	
	if(!pRs.Execute(&pCmd)) return;

	long nID;
	CString strTitle, strQuery;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sTitle", strTitle);
		pRs.GetFieldValue("sQuery", strQuery);

		m_mapFuncInfo[nID].nID = nID;
		strcpy(m_mapFuncInfo[nID].szTitle, CString(ltoa(i+1, buffer, 10)) + CString(". ") + strTitle);
		strcpy(m_mapFuncInfo[nID].szQuery, strQuery);				

		pRs.MoveNext();
	}


	long nItem = 0;
	FUNC_INFO_MAP::iterator it;
	for(it = m_mapFuncInfo.begin(); it != m_mapFuncInfo.end(); it++)
	{
		int nItem = m_cmbFunc.AddString((*it).second.szTitle);
		m_cmbFunc.SetItemData(nItem, (*it).second.nID);
	}
}

#define MAX_COLUMN_COUNT 30


void CFunctionTableDlg::RefreshList()
{
	if(m_cmbFunc.GetCurSel() < 0)
		return;

	//CWaitCursor wait;
	UpdateData(TRUE);
 
	CString strQuery = m_mapFuncInfo[m_cmbFunc.GetItemData(m_cmbFunc.GetCurSel())].szQuery;
	CString strPar1, strPar2;

	int nSize[MAX_COLUMN_COUNT];

	for(int i=0; i<MAX_COLUMN_COUNT; i++)
		nSize[i] = ZERO; 
 
	CPaintDC DC(this); 
	CFont *pOldFont = DC.SelectObject(m_FontManager.GetFont("돋움", 13, FW_NORMAL));

	char buffer[20];
	strPar1 = itoa(m_ci.m_nCompanyCode, buffer, 10);

	CMkRecordset pRs(m_pMkDb);	
	CMkCommand pCmd(m_pMkDb, strQuery);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);
	pCmd.AddParameter(typeString, typeInput, strPar1.GetLength(), strPar1);	 
	pCmd.AddParameter(typeString, typeInput, strPar2.GetLength(), strPar2);	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->bIntegrated); 

	if(!pRs.Execute(&pCmd)) return;

	//컬럼 모두 지움
	int nItem = 0;
	//int nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();
	//for(int i=0;i < nColumnCount;i++)
	//	m_List.DeleteColumn(0);

	m_List.GetColumns()->Clear();

	m_List.DeleteAllItems();

	for(int i = 0; i < pRs.GetFiledCount(); i++)
	{
		m_List.InsertColumn(nItem++, pRs.GetFieldName(i), LVCFMT_LEFT, 100);

		CSize szSize = DC.GetTextExtent(pRs.GetFieldName(i));
		nSize[i] = max(nSize[i], szSize.cx);
	}

	m_List.Populate();

	for(int k = 0; k < pRs.GetRecordCount(); k++)
	{
		for(int i = 0; i < pRs.GetFiledCount(); i++)
		{
			if(i == 0)
				m_List.InsertItem(k, pRs.GetFieldValueToString(i));	
			else
				m_List.SetItemText(k, i, pRs.GetFieldValueToString(i));

			CSize szSize = DC.GetTextExtent(pRs.GetFieldValueToString(i));
			nSize[i] = max(nSize[i], szSize.cx);
		}
		pRs.MoveNext();
	}

	CXTPGridColumns *pCols = m_List.GetColumns();

	for(int i=0; i<pCols->GetCount(); i++) 
	{ 
		CXTPGridColumn *pCol = pCols->GetAt(i);
		pCol->SetWidth(max(min(nSize[i], 200), 60));
	}

	m_List.Populate();
	DC.SelectObject(pOldFont);
}

void CFunctionTableDlg::OnViewExcel()
{
	if(!LF->POWER_CHECK(1900, "상황 엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(m_ci.m_nCompanyCode, 104, m_List.GetItemCount());  
	CMyExcel::ToExcel(&m_List);
}

void CFunctionTableDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_List.GetSafeHwnd() == NULL ||
		this->GetSafeHwnd() == NULL)
		return;

	CRect rcDlg, rcList;
	GetWindowRect(rcDlg);
	m_List.GetWindowRect(rcList);
	ScreenToClient(rcDlg);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 13;
	rcList.bottom = rcDlg.bottom - 13; 

	m_List.MoveWindow(rcList);
}

void CFunctionTableDlg::OnEnChangeSearchEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CMyDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString sSearch = "";
	m_edtSearch.GetWindowText(sSearch);

	m_List.Filter(sSearch);
}

void CFunctionTableDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	if(m_cmbFunc.GetItemData(m_cmbFunc.GetCurSel()) != 14)
		return;

	int nRow = pItemNotify->pRow->GetIndex();

	if(nRow >= 0)
	{
		CXTPGridRow *pRow = m_List.GetRows()->GetAt(nRow);
		CXTPListCtrlRecord2 *pRecord = (CXTPListCtrlRecord2*)pRow->GetRecord();

		if(pRecord)
		{
			CString strTNo = m_List.GetItemText(pRecord, 3);

		}
	}
}