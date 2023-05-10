// MakeGroupReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MakeGroupReportDlg.h"
#include "CommonDateDlg1.h"
#include "UnBillDlg.h"


// CMakeGroupReportDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMakeGroupReportDlg, CMyDialog)
CMakeGroupReportDlg::CMakeGroupReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMakeGroupReportDlg::IDD, pParent)
{
	m_nGNo = 0;
	m_bRefresh = FALSE;
	m_strGNoList = "";
}

CMakeGroupReportDlg::~CMakeGroupReportDlg()
{
}

void CMakeGroupReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
}


BEGIN_MESSAGE_MAP(CMakeGroupReportDlg, CMyDialog)
	ON_BN_CLICKED(IDC_MAKE_BTN, OnBnClickedMakeBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_NOTIFY(NM_RCLICK, IDC_REPORT, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDbClick)
	ON_COMMAND(ID_CHANGE_DATE, OnChangeDate)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CMakeGroupReportDlg 메시지 처리기입니다.

BOOL CMakeGroupReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();
	int nCol = 0;

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	m_btnDate.OnMenuWeek();
	m_lstReport.InsertColumn(nCol++, "No", LVCFMT_CENTER, 30);
	m_lstReport.InsertColumn(nCol++, "정산일자", LVCFMT_LEFT, 130);
	m_lstReport.InsertColumn(nCol++, "상태", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(nCol++, "생성일", LVCFMT_CENTER, 70);

	m_lstReport.InsertColumn(nCol++, "건수", LVCFMT_RIGHT, 45);
	m_lstReport.InsertColumn(nCol++, "신용금액", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(nCol++, "탁송료", LVCFMT_RIGHT, 50);

	m_lstReport.InsertColumn(nCol++, "계산서금액", LVCFMT_RIGHT, 70);
	m_lstReport.InsertColumn(nCol++, "발행", LVCFMT_CENTER, 40);


	m_lstReport.InsertColumn(nCol++, "구분", LVCFMT_CENTER, 40);
	m_lstReport.InsertColumn(nCol++, "작업자", LVCFMT_CENTER, 60);
	m_lstReport.Populate();
	RefreshList();





	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMakeGroupReportDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_report");

	pCmd.AddParameter(m_nGNo);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtReportStart, dtReportEnd, dtCreate;
	long nReportState, nID, nGNo, nException;
	long nCreditCount, nCreditCharge, nTransCharge, nUnCollection;
	BOOL bPressBill;
	CString sWName;


	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtReportStart", dtReportStart);
		pRs.GetFieldValue("dtReportEnd", dtReportEnd);
		pRs.GetFieldValue("nReportState", nReportState);
		pRs.GetFieldValue("dtCreate", dtCreate);
		pRs.GetFieldValue("nException", nException);
		pRs.GetFieldValue("sWName", sWName);		
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nGNo", nGNo);	

		pRs.GetFieldValue("nCreditCount", nCreditCount);	
		pRs.GetFieldValue("nCreditCharge", nCreditCharge);	
		pRs.GetFieldValue("nTransCharge", nTransCharge);	
		pRs.GetFieldValue("nUnCollection", nUnCollection);	
		pRs.GetFieldValue("bPressBill", bPressBill);	

		m_lstReport.InsertItem(i, GetMyNumberFormat(i+ 1));
		m_lstReport.SetItemText(i, 1, dtReportStart.Format("%y-%m-%d") + " ~ " + dtReportEnd.Format("%y-%m-%d"));
		m_lstReport.SetItemText(i, 2, GetReportState(nReportState));
		m_lstReport.SetItemText(i, 3, dtCreate.Format("%Y-%m-%d"));

		m_lstReport.SetItemText(i, 4, GetMyNumberFormat(nCreditCount));
		m_lstReport.SetItemText(i, 5, GetMyNumberFormat(nCreditCharge));
		m_lstReport.SetItemText(i, 6, GetMyNumberFormat(nTransCharge));

		m_lstReport.SetItemText(i, 7, GetMyNumberFormat(nUnCollection));
		m_lstReport.SetItemText(i, 8, bPressBill ? "발행" : "미발행");



		m_lstReport.SetItemText(i, 9, nException > 0 ? "O" : "");
		m_lstReport.SetItemText(i, 10, sWName);

		
		m_lstReport.SetItemLong(i, nID);
		m_lstReport.SetItemLong2(i, nGNo);

		m_lstReport.SetItemData(i, (long)nReportState);

		pRs.MoveNext();
	}

	m_lstReport.Populate();
}

CString CMakeGroupReportDlg::GetReportState(long nReportState)
{
	if(nReportState == 0)
		return "정산완료";
	else if(nReportState == 10)
		return "부분입금";
	else if(nReportState == 20)
		return "입금완료";

	return "알수없음";

}


void CMakeGroupReportDlg::OnBnClickedMakeBtn()
{
	UpdateData(TRUE);

	if(MessageBox("정산데이터를 생성하시겠습니까?", "확인", MB_YESNO) == IDNO)
		return;

	if(CheckDate(m_dtFrom, m_dtTo) != TRUE)
		return;

	CMkCommand pCmd(m_pMkDb, "make_customer_group_report");
	pCmd.AddParameter(m_nGNo);
	pCmd.AddParameter(m_cg.GetGroupData(m_nGNo)->strGroupName);
	pCmd.AddParameter(m_cg.GetGroupData(m_nGNo)->strDept);
	pCmd.AddParameter(m_cg.GetGroupData(m_nGNo)->strName);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);
	if(!pCmd.Execute()) return;

	m_bRefresh = TRUE;
	MessageBox("생성되었습니다", "확인", MB_ICONINFORMATION);
	RefreshList();		
}

BOOL CMakeGroupReportDlg::CheckDate(COleDateTime dtFrom, COleDateTime dtTo, BOOL bContiune, long nRow)
{
	dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), 0, 0, 0);
	dtTo.SetDateTime(dtTo.GetYear(), dtTo.GetMonth(), dtTo.GetDay(), 0, 0, 0);

	if(dtFrom > dtTo)
	{
		MessageBox("날짜를 다시 선택해 주세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CString sFrom, sTo;

	for(int i=0; i<m_lstReport.GetItemCount(); i++)
	{
		if((bContiune == TRUE) && (nRow == i))
			continue;

		BOOL bSame = FALSE;

		CString sDate = m_lstReport.GetItemText(i, 1);
		COleDateTime dtCompareFrom(_ttoi("20" + sDate.Left(2)), _ttoi(sDate.Mid(3, 2)), _ttoi(sDate.Mid(6 ,2)), 0, 0, 0);
		COleDateTime dtCompareTo(_ttoi("20" + sDate.Mid(11, 2)), _ttoi(sDate.Mid(14, 2)), _ttoi(sDate.Mid(17 ,2)), 0, 0, 0);

		if(((dtFrom >= dtCompareFrom ) && (dtFrom <= dtCompareTo)) ||
			((dtTo >= dtCompareFrom) && (dtTo <= dtCompareTo)))
			bSame = TRUE;


		if((dtFrom <= dtCompareFrom) && (dtTo >= dtCompareTo))
			bSame = TRUE;

		if(bSame)
		{
			MessageBox("정산일이 겹칩니다. 날짜를 다시 선택해 주세요", "확인", MB_ICONINFORMATION);
			//CXTPGridRow *pRow = m_lstReport.GetRows()->GetAt(i);
			//m_lstReport.GetSelectedRows()->Select(pRow);			
			return FALSE;
		}
	}

	return TRUE;
}

void CMakeGroupReportDlg::OnBnClickedCancelBtn()
{
	OnOK();
}

void CMakeGroupReportDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(15);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	

}

void CMakeGroupReportDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstReport, pt);
}

void CMakeGroupReportDlg::OnChangeDate()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return;

	CXTPGridRow *pRow = pRows->GetAt(0);

	//CString sReportState = m_lstReport.GetItemText(pRow->GetIndex(), 1);
	long nReportState =(long) m_lstReport.GetItemData(pRow->GetRecord());



	//if(sReportState == "입금완료" || sReportState == "부분입금")
	if(nReportState == 10 || nReportState == 20)
	{
		CString sMsg = "정산완료 상태에서만 날짜변경이 가능합니다\r\n\r\n작업을 계속하시려면 해당 오더삭제 후\r\n정산데이터 생성 후 수금액을 입금하세요";
		MessageBox(sMsg, "확인", MB_ICONINFORMATION);
		return;
	}

	CString sDate = m_lstReport.GetItemText(pRow->GetIndex(), 1);
	COleDateTime dtFrom(_ttoi("20" + sDate.Left(2)), _ttoi(sDate.Mid(3, 2)), _ttoi(sDate.Mid(6 ,2)), 0, 0, 0);
	COleDateTime dtTo(_ttoi("20" + sDate.Mid(11, 2)), _ttoi(sDate.Mid(14, 2)), _ttoi(sDate.Mid(17 ,2)), 0, 0, 0);

	CCommonDateDlg1 dlg;
	dlg.m_dtFrom = dtFrom;
	dlg.m_dtTo = dtTo;

	if(dlg.DoModal() == IDOK)
	{
		if(CheckDate(dlg.m_dtFrom, dlg.m_dtTo, TRUE, pRow->GetIndex()) != TRUE) 
		{
			OnChangeDate();
			return;
		}

		long nID = m_lstReport.GetItemLong(pRow->GetIndex());

		CMkCommand pCmd(m_pMkDb, "change_group_report_date");
		pCmd.AddParameter(nID);
		pCmd.AddParameter(dlg.m_dtFrom);
		pCmd.AddParameter(dlg.m_dtTo);

		if(!pCmd.Execute())
			return;

		m_bRefresh = TRUE;
		RefreshList();
		MessageBox("정산일이 수정되었습니다\r\n자동으로 재정산이 일어 납니다", "확인", MB_ICONINFORMATION);
	}    
}

void CMakeGroupReportDlg::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_lstReport.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CUnBillDlg dlg;
	dlg.m_bAlone = TRUE;

	dlg.m_bAlone = TRUE;
	dlg.m_nID = m_lstReport.GetItemLong(pRow->GetIndex());
	dlg.m_nGNo = m_lstReport.GetItemLong2(pRow->GetIndex());

	dlg.DoModal();
}
