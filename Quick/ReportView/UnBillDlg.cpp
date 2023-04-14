// UnBillDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "UnBillDlg.h"

#include "GroupIncomeDlg.h"
#include "OrderSeeDlg.h"
#include "WebGroupReportDlg.h"
#include "ReGroupReportDlg.h"
#include "DeleteGroupReportDlg.h"
#include "VarietyDlg2.h"

// CUnBillDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnBillDlg, CMyDialog)
CUnBillDlg::CUnBillDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CUnBillDlg::IDD, pParent)
{
	m_bChangeItem = FALSE;
	m_bAlone = FALSE;
}

CUnBillDlg::~CUnBillDlg()
{
}

void CUnBillDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_1, m_lstReport);
	DDX_Control(pDX, ID_OPEN_TREE_CHECK, m_chkOpenTree);
}


BEGIN_MESSAGE_MAP(CUnBillDlg, CMyDialog)
	ON_BN_CLICKED(ID_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_REPORT_1, OnReportItemRClick)
	
	ON_COMMAND(ID_ORDER_SEE, OnOrderSee)

	ON_COMMAND(ID_TAXACCOUNT, OnTaxAccount) // 계산서
	ON_COMMAND(ID_RE_GROUP_REPORT, OnReGroupReport) // 재정산

	ON_COMMAND(ID_INCOME, OnIncome)
	ON_COMMAND(ID_DELETE_GROUP_REPORT, OnDeleteGroupReport) // 정산삭제

	ON_COMMAND(ID_PAY_INCOME, OnPayIncome)
	ON_COMMAND(ID_PAY_CANCEL, OnPayCancel) // 정산출금
	ON_COMMAND(ID_PAY_END, OnPayEnd)
	ON_COMMAND(ID_REPORT_DELETE, OnReportDelete) // 정산삭제
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel) // 정산삭제

	ON_COMMAND(ID_PAY_INCOME_CANCEL, OnPayInComeCancel) // 입금취소
	ON_COMMAND(ID_PAY_END_CANCEL, OnPayEndCancel)  // 전액입금취소
	
	
	
	
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_PRINT_BTN, OnBnClickedPrintBtn)
	ON_BN_CLICKED(ID_OPEN_TREE_CHECK, OnBnClickedOpenTreeCheck)
END_MESSAGE_MAP()


// CUnBillDlg 메시지 처리기입니다.

BOOL CUnBillDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow(); 

	m_chkOpenTree.SetCheck(FALSE);

	SetWindowText(m_cg.GetGroupData(m_nGNo)->strGroupName + "/" + m_cg.GetGroupData(m_nGNo)->strDept);	



	CXTPGridColumn* pCol0 = m_lstReport.AddColumn(new CXTPGridColumn(0, _T("그룹명"), 150));
	CXTPGridColumn* pCol1 = m_lstReport.AddColumn(new CXTPGridColumn(1, _T("체크"), 30));
	CXTPGridColumn* pCol2 = m_lstReport.AddColumn(new CXTPGridColumn(2, _T("일자"), 90));
	CXTPGridColumn* pCol3 = m_lstReport.AddColumn(new CXTPGridColumn(3, _T("상태"), 140));
	CXTPGridColumn* pCol4 = m_lstReport.AddColumn(new CXTPGridColumn(4, _T("금액"), 80));
	CXTPGridColumn* pCol5 = m_lstReport.AddColumn(new CXTPGridColumn(5, _T("미수잔액"), 80));
	CXTPGridColumn* pCol6 = m_lstReport.AddColumn(new CXTPGridColumn(6, _T("수금일"), 75));    
	CXTPGridColumn* pCol7 = m_lstReport.AddColumn(new CXTPGridColumn(7, _T("계산서"), 50));
	CXTPGridColumn* pCol8 = m_lstReport.AddColumn(new CXTPGridColumn(8, _T("재수금일"), 60));

	CXTPGridColumn* pCol9 = m_lstReport.AddColumn(new CXTPGridColumn(9, _T("담당자"), 50));
	CXTPGridColumn* pCol10 = m_lstReport.AddColumn(new CXTPGridColumn(10, _T("비고"), 360));


	
	pCol4->SetAlignment(DT_RIGHT);
	pCol5->SetAlignment(DT_RIGHT);
	pCol6->SetAlignment(DT_RIGHT);
	pCol7->SetAlignment(DT_RIGHT);
	pCol8->SetAlignment(DT_RIGHT);

	m_lstReport.GetPaintManager()->m_strNoItems = "미수금 내역이 없습니다"; 
	m_lstReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_lstReport.SetGridColor(RGB(222, 222, 222));
	m_lstReport.GetReportHeader()->SetAutoColumnSizing(FALSE);

	pCol0->SetTreeColumn(1);	
	m_lstReport.SetTreeIndent(10);


	m_lstReport.Populate();

	m_chkOpenTree.SetCheck(TRUE);
	OnBnClickedRefreshBtn();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CUnBillDlg::OnBnClickedRefreshBtn()
{

	RefreshList();	
	OnBnClickedOpenTreeCheck();
}

void CUnBillDlg::RefreshList()
{
	m_lstReport.GetRecords()->RemoveAll();
	m_lstReport.Populate();

	long nRet = 0; 

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd;
	
	if(m_bAlone)
	{
		pCmd.SetMkCommand(m_pMkDb, "select_un_bill_report_alone_1");
		pCmd.AddParameter(m_nID);
	}
	else
	{
		pCmd.SetMkCommand(m_pMkDb, "select_un_bill_report_by_group_1");
		pCmd.AddParameter(m_nGNo);
		pCmd.AddParameter(m_bAll);
	}

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtGenerate, dtReportStart, dtReportEnd, dtBillCollEction;
	long nAccount, nBalance, nID;
	CString strFormat, strType; 
	long nGNo = 0, nPrenGNo = 0, nPrenID = 0;


	CXTPGridRecord *pTopRecord;
	CXTPGridRecord *pSecondRecord;
	CXTPGridRecord *pBottomRecord;

	BOOL bOpen = TRUE;//m_chkOpenTree.GetCheck(); 


	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		long nReceivableAmount, nUnCollection, nIndex;
		CString sSendEmail = "", sWName = "", sEtc = "";
		COleDateTime dtPayMent, dtSendBill, dtSendEmail, dtInputDebit;
		BOOL bCancel = FALSE;
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("nID", nID);

		if(nGNo != nPrenGNo)
		{
			pTopRecord = m_lstReport.AddRecord(new CUnBillRecord(nGNo));
			pTopRecord->SetExpanded(bOpen);;
		}		

		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nAccount", nAccount);
		pRs.GetFieldValue("nBalance", nBalance);
		pRs.GetFieldValue("sType", strType);
		pRs.GetFieldValue("dtReportStart", dtReportStart);
		pRs.GetFieldValue("dtReportEnd", dtReportEnd);		
		pRs.GetFieldValue("dtBillCollEction", dtBillCollEction);
		pRs.GetFieldValue("dtPayMent", dtPayMent);
		pRs.GetFieldValue("dtSendBill", dtSendBill);
		pRs.GetFieldValue("dtSendEmail", dtSendEmail);
		pRs.GetFieldValue("dtInputDebit", dtInputDebit);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("nReceivableAmount", nReceivableAmount);
		pRs.GetFieldValue("nUnCollection", nUnCollection);
		pRs.GetFieldValue("nIndex", nIndex);
		pRs.GetFieldValue("bCancel", bCancel);

		if(dtSendBill.GetStatus() == COleDateTime::null && dtSendEmail.GetStatus() == COleDateTime::null )
		{
			sSendEmail = "";
		}
		else if(dtSendBill.GetStatus() == COleDateTime::null && dtSendEmail.GetStatus() == COleDateTime::valid)
		{
			sSendEmail.Format("%02d-%02d", dtSendEmail.GetMonth(), dtSendEmail.GetDay());
		}
		else if(dtSendBill.GetStatus() == COleDateTime::valid && dtSendEmail.GetStatus() == COleDateTime::null)
		{
			sSendEmail.Format("%02d-%02d", dtSendBill.GetMonth(), dtSendBill.GetDay());
		}
		else if(dtSendBill.GetStatus() == COleDateTime::valid && dtSendEmail.GetStatus() == COleDateTime::valid)
		{
			if(dtSendBill > dtSendEmail)
				sSendEmail.Format("%02d-%02d", dtSendBill.GetMonth(), dtSendBill.GetDay());
			else
				sSendEmail.Format("%02d-%02d", dtSendEmail.GetMonth(), dtSendEmail.GetDay());
		}

		if(nID != nPrenID)
		{
			pSecondRecord = pTopRecord->GetChilds()->Add(new CUnBillRecord(
				nGNo, dtGenerate, nID, nAccount, nBalance, strType, 
				dtReportStart, dtReportEnd, dtBillCollEction, dtPayMent, dtInputDebit,
				sSendEmail, sWName, sEtc ,nReceivableAmount,nUnCollection,nIndex,bCancel, TRUE));
			pSecondRecord->SetExpanded(bOpen);
		}

		pBottomRecord = pSecondRecord->GetChilds()->Add(new CUnBillRecord(
			nGNo, dtGenerate, nID, nAccount, nBalance, strType, dtReportStart, dtReportEnd, dtBillCollEction, dtPayMent,dtInputDebit,
				sSendEmail, sWName, sEtc, nReceivableAmount,nUnCollection,nIndex,bCancel, FALSE));
		pBottomRecord->SetExpanded(bOpen);

		nPrenGNo = nGNo;
		nPrenID = nID;

		pRs.MoveNext();
	}

	m_lstReport.Populate();

	
}

void CUnBillDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{	
	if(pWnd->GetSafeHwnd() == m_lstReport.GetSafeHwnd())
	{
		CRect rect;
		m_lstReport.GetWindowRect(&rect);
		if(!rect.PtInRect(point)) return;
	

		CMenu rMenu;
		rMenu.LoadMenu(IDR_GROUP_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(7);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CUnBillDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstReport, pt);
}



void CUnBillDlg::OnIncome()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("입금 처리 하려는 해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRecord->m_nUnBill <= 0)
	{
		MessageBox("이미 모두 입금처리 되었습니다", "확인", MB_ICONINFORMATION);
		return;		
	}

	CGroupIncomeDlg dlg;
	dlg.m_nID = pRecord->m_nID;
	dlg.m_nDebit = pRecord->m_nReceivableAmount;
	dlg.m_sDate = pRecord->m_strDate;
	dlg.m_nUnCollection = pRecord->m_nUnCollection;
	dlg.m_nAllIncome = 0;
	dlg.m_strInputEtc = pRecord->m_strEtc;
	if(dlg.DoModal() == IDOK)
	{
		RefreshList();
		m_bChangeItem = TRUE;
	}
}


void CUnBillDlg::OnPayIncome()
{


	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("입금 처리 하려는 해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRecord->m_nUnBill <= 0)
	{
		MessageBox("이미 모두 입금처리 되었습니다", "확인", MB_ICONINFORMATION);
		return;		
	}

	CGroupIncomeDlg dlg;
	dlg.m_nID = pRecord->m_nID;
	dlg.m_nDebit = pRecord->m_nReceivableAmount;
	dlg.m_sDate = pRecord->m_strDate;
	dlg.m_nUnCollection = pRecord->m_nUnCollection;
	dlg.m_nAllIncome = 0;
	//dlg.m_strInputEtc = pRecord->m_strEtc;
	if(dlg.DoModal() == IDOK)
	{
		RefreshList();
		m_bChangeItem = TRUE;
	}

}
void CUnBillDlg::OnPayCancel()
{


	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("입금 처리 하려는 해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRecord->m_nUnBill <= 0)
	{
		MessageBox("이미 모두 입금처리 되었습니다", "확인", MB_ICONINFORMATION);
		return;		
	}

	CGroupIncomeDlg dlg;
	dlg.m_nID = pRecord->m_nID;
	dlg.m_nDebit = pRecord->m_nReceivableAmount;
	dlg.m_sDate = pRecord->m_strDate;
	dlg.m_nUnCollection = pRecord->m_nUnCollection;
	dlg.m_nAllIncome = 1;
	//dlg.m_strInputEtc = pRecord->m_strEtc;
	if(dlg.DoModal() == IDOK)
	{
		RefreshList();
		m_bChangeItem = TRUE;
	}

}



void CUnBillDlg::OnViewExcel()
{

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 316, m_ui.nWNo, m_lstReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_lstReport);
}


void CUnBillDlg::OnPayInComeCancel()
{
	InputCancel(100); // 100 입금취소 102 전액입금취소
	
}
void CUnBillDlg::OnPayEndCancel()
{
	InputCancel(102); // 100 입금취소 102 전액입금취소
}

void CUnBillDlg::InputCancel(int nType )
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();
	if(pRecord)
	{	
		BOOL bCancel = FALSE;
		long  nIndex, nGNo, nReportID;
		CString strEtc = "",strType = pRecord->m_strType;
		nIndex = pRecord->m_nIndex;		
		nGNo = pRecord->m_nGNo;
		nReportID = pRecord->m_nID;
		bCancel = pRecord->m_bCancel;
		CString strCompareType ;
		strCompareType = nType == 100 ? "(+)부분입금" : "(+)전액입금";

		if(bCancel)
		{
			MsgBox("취소가 되었던 항목입니다.", "확인",MB_ICONINFORMATION  );
			return;
		}			

		if(strType.Compare(strCompareType) != 0 )
		{
			MsgBox("(+)부분입금 된 항목만 취소할 수 있습니다.", "확인",MB_ICONINFORMATION  );
			return;
		}			

		if( MessageBox("해당 입금한것에 대해 정말로 취소하시겠습니까?", "확인",  MB_YESNO) == IDNO  )
			return;

		if(nIndex <= 0 )
		{
			MsgBox("취소할 해당 데이터를 선택하세요");
			return;
		}

		if(nReportID <= 0 )
		{
			MsgBox("정산리스트가 선택이 되지 않았습니다.");
			return;
		}
		if(nGNo <= 0 )
		{
			MsgBox("그룹정보가 없습니다.");
			return;
		}

		CVarietyDlg2 dlg;
		dlg.m_sTitle = "취소사유를 꼭 기입하세요";
		if(dlg.DoModal() != IDOK)
			return;

		strEtc = dlg.m_sEtc;
		if(strEtc.GetLength() <= 0 )
		{
			MsgBox("취소 사유를 입력하세요", "확인",MB_ICONINFORMATION  );
			return;
		}



		CMkCommand pCmd(m_pMkDb, "update_group_unbill_income_cancel"); 
		pCmd.AddParameter(nIndex);
		pCmd.AddParameter(nReportID);
		pCmd.AddParameter(nGNo);
		pCmd.AddParameter(nType);		
		pCmd.AddParameter(m_ui.strName);	
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(strEtc);
		if(!pCmd.Execute()) return;

		MessageBox("취소 되었습니다", "확인", MB_ICONINFORMATION);
		RefreshList();



	}
}




void CUnBillDlg::OnPayEnd()
{


	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("입금 처리 하려는 해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRecord->m_nUnBill <= 0)
	{
		MessageBox("이미 모두 입금처리 되었습니다", "확인", MB_ICONINFORMATION);
		return;		
	}

	CGroupIncomeDlg dlg;
	dlg.m_nID = pRecord->m_nID;
	dlg.m_nDebit = pRecord->m_nReceivableAmount;
	dlg.m_sDate = pRecord->m_strDate;
	dlg.m_nUnCollection = pRecord->m_nUnCollection;
	dlg.m_nAllIncome = 2;
	//dlg.m_strInputEtc = pRecord->m_strEtc;
	if(dlg.DoModal() == IDOK)
	{
		RefreshList();
		m_bChangeItem = TRUE;
	}

}


void CUnBillDlg::OnDeleteGroupReport()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("재정산 처리 하려는 해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}


	CDeleteGroupReportDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;
	dlg.DoModal();

	if(dlg.m_bRefresh == TRUE)
	{
		CString sGNo = "";
		sGNo.Format("%d;", dlg.m_nGNo);
		m_bChangeItem = TRUE;
	}

}

void CUnBillDlg::OnReportDelete()
{
	CXTPGridRow *pRow = m_lstReport.GetSelectedRows()->GetAt(0);
	if(pRow == NULL) return;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("재정산 처리 하려는 해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if( MessageBox("정말로 정산삭제를 하시겠습니까? \n\r\n\r정산삭제가 되면 해당 입금된 내역도 삭제됩니다.\n\r(입금내역 백업요망)",
		"확인", MB_YESNO) == IDNO) 
		return;


	

	long nBillID = pRecord->m_nID;
	long nGNo = pRecord->m_nGNo;


	CDeleteGroupReportDlg dlg;
	dlg.m_nGNo = nGNo;
	dlg.m_nApplyReportID = nBillID;
	dlg.DoModal();
	if(dlg.m_bRefresh == TRUE)
	{
		RefreshList();
	}



}
void CUnBillDlg::OnOrderSee()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	COrderSeeDlg dlg;

	dlg.m_nID = pRecord->m_nID;
	dlg.m_nGNo = pRecord->m_nGNo;
	dlg.m_strDate = pRecord->m_strDate;

	dlg.DoModal();		
}

void CUnBillDlg::OnBnClickedOk()
{
	OnOK();
}

void CUnBillDlg::OnBnClickedPrintBtn()
{
	CWebGroupReportDlg dlg;

	CString strGNo = "";
	CString strID = "";
	CString strDate = "";
	long nCount = 0;
	char buffer[20];

	CXTPGridRows *pRows = m_lstReport.GetRows();
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);
		CUnBillRecord *pRecord = (CUnBillRecord*)pRow->GetRecord();

		if(((CXTPGridRecordItemCheck*)pRecord->GetItem(1))->IsChecked() == TRUE)
		{
			strGNo = (CString)itoa(pRecord->m_nGNo, buffer, 10);
			strID = (CString)itoa(pRecord->m_nID, buffer, 10);
			strDate = pRecord->m_strDate;
			dlg.m_strGNo.Add(strGNo);
			dlg.m_strID.Add(strID);
			dlg.m_strTitle.Add(m_cg.GetGroupData(_ttoi(strGNo))->strGroupName + " [" + strDate + "]");

			nCount++;
		}
	}

	dlg.m_nCount = nCount;

	dlg.DoModal();
}

void CUnBillDlg::OnTaxAccount()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("입금 처리 하려는 해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	BOOL bPressBill = pRecord->m_bPressBill; 
	CString strMsg = "";
 
	if(bPressBill)
		strMsg.Format("[%s]의 세금계산서 발행을 취소 하시겠습니까?", pRecord->m_strDate);		
	else
		strMsg.Format("[%s]의 세금계산서를 발행 하시겠습니까?", pRecord->m_strDate);
		
	if(MessageBox(strMsg, "확인", MB_YESNO) != IDYES) return;

	CMkCommand pCmd(m_pMkDb, "update_group_report_bill_press");
	pCmd.AddParameter(pRecord->m_nID);
	pCmd.AddParameter(!bPressBill);

	if(pCmd.Execute())
	{
		if(bPressBill) 
			MessageBox("발행취소됨", "확인", MB_ICONINFORMATION);
		else
			MessageBox("발행됨", "확인", MB_ICONINFORMATION);

		m_bChangeItem = TRUE;
		pRecord->m_bPressBill = !bPressBill;
	}
}

void CUnBillDlg::OnReGroupReport()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();
	if(pRows == NULL) return;

	CUnBillRecord * pRecord = (CUnBillRecord*)pRows->GetAt(0)->GetRecord();

	if(pRecord->m_nID <= 0)
	{
		MessageBox("재정산 처리 하려는 해당 월을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CReGroupReportDlg dlg;
	dlg.m_nGNo = pRecord->m_nGNo;

	dlg.DoModal();

	if(dlg.m_bRefresh == TRUE)
	{
		CString sGNo = "";
		sGNo.Format("%d;", dlg.m_nGNo);
		m_bChangeItem = TRUE;
	}

}

void CUnBillDlg::OnBnClickedOpenTreeCheck()
{
	BOOL bChk = m_chkOpenTree.GetCheck();

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();
	
	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecords *pRecordChilds = pRecords->GetAt(i)->GetChilds();

		for(int j=0; j<pRecordChilds->GetCount(); j++)
		{
			CXTPGridRecord *pRecordSecondChild = pRecordChilds->GetAt(j);
			pRecordSecondChild->SetExpanded(bChk);

		}
		
	}

	m_lstReport.Populate();
}
