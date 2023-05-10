// StatForm6.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "StatForm6.h"
#include "OrderLogDetailDlg.h"
#include "RcpView.h"
#include "TransferRiderDlg.h"
// CStatForm6

IMPLEMENT_DYNCREATE(CStatForm6, CMyFormView)

CStatForm6::CStatForm6()
	: CMyFormView(CStatForm6::IDD)
{
}

CStatForm6::~CStatForm6()
{
}

void CStatForm6::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lstReport);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnDate);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CStatForm6, CMyFormView)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDblClick)
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CStatForm6::OnEnChangeSearchEdit)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, &CStatForm6::OnCbnSelchangeTypeCombo)
	ON_BN_CLICKED(IDC_REQUEST_TRANSFER_BTN, &CStatForm6::OnBnClickedRequestTransferBtn)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CStatForm6 진단입니다.

#ifdef _DEBUG
void CStatForm6::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CStatForm6::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CStatForm6 메시지 처리기입니다.

void CStatForm6::OnViewExcel()
{
	if(!POWER_CHECK(8900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nCompanyCode, 306, m_ui.nWNo, m_lstReport.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_lstReport);
}


void CStatForm6::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_lstReport.SetExternalControl(GetDlgItem(IDC_SEARCH_COMBO),
		GetDlgItem(IDC_SEARCH_EDIT),			//SetExternalControl함수의 순서중요함
		GetDlgItem(NULL));	//반드시 InsertColumn앞에 있어야함

	m_btnDate.InitDateButton(&m_FromDT, &m_ToDT);
	m_btnDate.OnMenuWeek();

	m_cmbType.SetCurSel(0);

	SetResize(IDC_REPORT, sizingRightBottom);
	
	//m_lstReport.GetPaintManager()->SetTextFont(font);
	//m_lstReport.Populate();

	m_lstReport.InsertColumn(0, "일자", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(1, "상태", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "입금액", LVCFMT_RIGHT, 65);
	m_lstReport.InsertColumn(3, "출금액", LVCFMT_RIGHT, 65);
	m_lstReport.InsertColumn(4, "현재잔액", LVCFMT_RIGHT, 80);
	m_lstReport.InsertColumn(5, "설명", LVCFMT_LEFT, 300);
	m_lstReport.InsertColumn(6, "거래업체", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(7, "오더설명(기사기준)", LVCFMT_LEFT, 300);
	m_lstReport.InsertColumn(8, "기사정보", LVCFMT_LEFT, 90);

	//m_lstReport.InsertColumn(7, "오더수정적요", LVCFMT_LEFT, 500);

	m_lstReport.Populate();
}

void CStatForm6::RefreshList()
{
	m_lstReport.DeleteAllItems();

	UpdateData(TRUE); 

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_share_account_log_new");
	pCmd.AddParameter(typeLong, typeInput, sizeof(COleDateTime), GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtFrom);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_dtTo);

	const char *dayofweek[] = {"일", "월", "화", "수", "목", "금", "토"};

	if(pRs.Execute(&pCmd))
	{
		long nDeposit,nBalance, nTrafficPenalty, nRiderCompany, nRNo;
		CString strState, strEtc, strOrderEtc, strSCompany, strSEtc, strRName;
		COleDateTime dtGenerate;
		
		for(int i=0; i<pRs.GetRecordCount(); i++) 
		{
			BOOL bPlus = FALSE;
			pRs.GetFieldValue("dtGenerate", dtGenerate);
			pRs.GetFieldValue("sState", strState);
			pRs.GetFieldValue("nDeposit", nDeposit);
			pRs.GetFieldValue("nBalance", nBalance);
			pRs.GetFieldValue("sEtc", strEtc);
			pRs.GetFieldValue("nTrafficPenalty", nTrafficPenalty);
			pRs.GetFieldValue("sOrderEtc", strOrderEtc);
			pRs.GetFieldValue("nRiderCompanyR", nRiderCompany);
			pRs.GetFieldValue("nRNoR", nRNo);
			pRs.GetFieldValue("sRNameR", strRName);

			CutEtc(strEtc, strSCompany, strSEtc);

			CString strDayOfWeek;

			if (dtGenerate.GetStatus() == COleDateTime::null)
				m_lstReport.InsertItem(i, "");
			else
			{
				strDayOfWeek.Format("(%s)", dayofweek[dtGenerate.GetDayOfWeek() - 1]);
				m_lstReport.InsertItem(i, dtGenerate.Format("%y/%m/%d %H:%M") + strDayOfWeek);
			}
			
			m_lstReport.SetItemText(i, 1, strState);

			if(nDeposit >= 0)
			{
				m_lstReport.SetItemText(i, 2, ::GetMyNumberFormat(nDeposit));
				bPlus = TRUE;
			}
			else
				m_lstReport.SetItemText(i, 3, ::GetMyNumberFormat(nDeposit));

			strSEtc.Replace("에서받음 사유:", "");
			strSEtc.Replace("로보냄 사유:", "");

			m_lstReport.SetItemText(i, 4, ::GetMyNumberFormat(nBalance));
			m_lstReport.SetItemText(i, 5, strSEtc);
			m_lstReport.SetItemText(i, 6, strSCompany);
			m_lstReport.SetItemText(i, 7, strOrderEtc);
			
			if(nRNo > 0 && nRiderCompany > 0)
			{
				m_lstReport.SetItemText(i, 8, 
					(!m_ci.IsChildCompany(nRiderCompany) ? CString("ⓒ") : "") + GetStringFromLong(nRNo) + "/" + strRName);
			}
			else
				m_lstReport.SetItemText(i, 8, "");			

			m_lstReport.SetItemLong(i, bPlus);
			m_lstReport.SetItemLong2(i, nRiderCompany);
			m_lstReport.SetItemLong3(i, nRNo);
			pRs.MoveNext();
		}

		m_lstReport.Populate();
	}

}

void CStatForm6::CutEtc(CString sEtc, CString &sSCompany, CString &sSEtc)
{
	sSCompany = "";
	sSEtc = "";

	long nFirstFind = sEtc.Find("[");

	if(nFirstFind >= 0)
	{
		long nSecondFInd = sEtc.Find("]", nFirstFind);

		if(nSecondFInd > 0)
		{			
			sSCompany = sEtc.Mid(nFirstFind, nSecondFInd - nFirstFind +1);
			sSEtc = sEtc.Mid(nSecondFInd + 1, sEtc.GetLength() - nSecondFInd);

			sSEtc.Replace("로 보냄 ", "");
			sSEtc.Replace("에서 받음 ", "");
		}
	}
	else
	{
		sSCompany = "";
		sSEtc = sEtc;
	}
}

void CStatForm6::OnBnClickedRefreshBtn()
{
	RefreshList();
}

long  CStatForm6::GetTNoFromText(CString strTNo)
{
	long nStart = strTNo.Find("오더");

	if(nStart < 0)
		return 0;

	nStart+=4;
	CString strSum = "";
	BOOL bStart = FALSE;
	long nLen = strTNo.GetLength();

	for(int i=nStart; i<strTNo.GetLength(); i++)
	{
		CString strChar = strTNo.Mid(i, 1);

		if(::IsNumeric(strChar) == TRUE &&
			strChar != "")
		{
			strSum += strChar;
			bStart =TRUE;
		}
		else
		{
			if(bStart == TRUE)
				break;
			else 
				continue;
		}
	}

	return atoi(strSum);	
}

void CStatForm6::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(!pRecord)
		return;

	long nCol = pItemNotify->pColumn->GetIndex();

	if(nCol == 6)
	{
		CString strItem = (CString)pRecord->GetItem(6)->GetCaption(NULL);

		if(strItem.IsEmpty())
			return;

		CMkCommand pCmd(m_pMkDb, "select_company_info");
		pCmd.AddParameter(strItem);
		CMkParameter *parOut = pCmd.AddParameter(typeString, typeOutput, 100, "");

		if(!pCmd.Execute())
			return;

		parOut->GetValue(strItem);

		if(strItem.IsEmpty())
			return;

		MessageBox(strItem, "확인", MB_ICONINFORMATION);	
	}
	else if (nCol == 8)
	{
		long nRiderCompany = m_lstReport.GetItemLong2(pRecord);
		long nRNo = m_lstReport.GetItemLong3(pRecord);

		if(nRiderCompany > 0 && nRNo > 0)
			LU->ShowRiderInfoDlg(nRiderCompany, nRNo);
	}	
}

void CStatForm6::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL){MessageBox("해당 로우를 선택하세요", "확인", MB_ICONINFORMATION); return;};
	if(pRows->GetCount() == 0){MessageBox("해당 로우를 선택하세요", "확인", MB_ICONINFORMATION); return;};

	CString strTNo = m_lstReport.GetItemText(pRows->GetAt(0)->GetRecord(), 5);
	long nTNo = GetTNoFromText(strTNo);

	if(nTNo< 100000) return;

	CString sCName; long nState;

	if(::IsCrossOrder(nTNo, sCName, nState))
	{ 
		COrderLogDetailDlg DetailLog;
		//DetailLog.m_pCurDb = IsSecondServerOrder(nSelItem) ? m_pMkSecondDb : m_pMkDb;
		DetailLog.m_nTNo = nTNo;
		DetailLog.m_bCross = TRUE;
		DetailLog.DoModal();

		return;
	}

	if(!POWER_CHECK(2001, "접수창 열기", TRUE))
		return;

	if(LU->m_pRcpView)
	{
		LU->m_pRcpView->CreateRcpDlg(NULL, 
			sCName,
			nTNo, 
			nState, "", FALSE, -1, 0, 0, FALSE, "");
	}		
	else
	{
		MessageBox("접수탭으로 이동한 후 다시시도하세요", "확인", MB_ICONINFORMATION);
	}	
}

void CStatForm6::OnEnChangeSearchEdit()
{
	Filter();
}

void CStatForm6::Filter()
{
	CString strText; m_edtSearch.GetWindowText(strText);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strEtc = pRecord->GetItem(5)->GetCaption(NULL);

		if(strEtc.Find(strText) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}
	m_lstReport.Populate();
	/*
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_SEARCH_COMBO);
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_SEARCH_EDIT);
	CComboBox *pTypeCombo = NULL;

	CString strText;
	pEdit->GetWindowText(strText);
	strText.Trim();

	int nTypeData;
	if(pTypeCombo == NULL)
		nTypeData = -1;
	else
		nTypeData = (int)pTypeCombo->GetItemData(pTypeCombo->GetCurSel());

	m_lstReport.Filter(strText, pCombo->GetCurSel(), nTypeData);
	*/

	CheckType();
}

void CStatForm6::CheckType()
{
	//전부, 입금, 출금
	long nType = m_cmbType.GetCurSel();
	if(nType == 0) return;

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		if(!pRecord->IsVisible())
			continue;

		BOOL bPlus = m_lstReport.GetItemLong(pRecord);

		if((nType == 1 && bPlus == FALSE) ||
			(nType == 2 && bPlus == TRUE))
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
}

void CStatForm6::OnCbnSelchangeTypeCombo()
{
	Filter();
}

void CStatForm6::OnBnClickedRequestTransferBtn()
{
	CTransferRiderDlg dlg;
	dlg.DoModal();
}

void CStatForm6::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}
