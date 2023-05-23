// ReportForm27.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "ReportForm27.h"
#include "ColumnSelDlg.h"


// CReportForm27

IMPLEMENT_DYNCREATE(CReportForm27, CMyFormView)

CReportForm27::CReportForm27()
	: CMyFormView(CReportForm27::IDD)
{
	m_bDragMode = FALSE;
}

CReportForm27::~CReportForm27()
{
	m_lstRight.SaveReportOrder("CReportForm27", "m_lstRight");
}

void CReportForm27::RefreshList()
{
	CMyFormView::RefreshList();

	RefreshCustomerList(TRUE);
}

void CReportForm27::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEFT_LIST, m_lstLeft);
	DDX_Control(pDX, IDC_RIGHT_LIST, m_lstRight);

	DDX_Control(pDX, IDC_DTP_FROM, m_dtFromCtl);
	DDX_Control(pDX, IDC_DTP_TO, m_dtToCtl);
	DDX_DateTimeCtrl(pDX, IDC_DTP_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}

BEGIN_MESSAGE_MAP(CReportForm27, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CReportForm27::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_SEARCH_ALL_BTN, &CReportForm27::OnBnClickedSearchAllBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CReportForm27::OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CReportForm27::OnBnClickedRefreshBtn)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LEFT_LIST, OnReportBeginDrag)
	ON_NOTIFY(XTP_NM_GRID_HEADER_RCLICK, IDC_RIGHT_LIST, OnReportColumnRClick)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_VISIBLE_COL, OnVisibleCol)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
END_MESSAGE_MAP()


// CReportForm27 �����Դϴ�.

void CReportForm27::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

#ifdef _DEBUG
void CReportForm27::AssertValid() const
{
	CMyFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CReportForm27::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CReportForm27 �޽��� ó�����Դϴ�.

void CReportForm27::OnBnClickedSearchBtn()
{
	RefreshCustomerList(FALSE);
}

void CReportForm27::OnBnClickedSearchAllBtn()
{
	RefreshCustomerList(TRUE);
}

void CReportForm27::RefreshCustomerList(BOOL bAll)
{
	m_lstLeft.DeleteAllItems();
	char buffer[10]; 
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	if(strSearch.GetLength() <= ONE && bAll == FALSE)
	{ 
		MessageBox("�˻���� ���� �̻����� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_credit_customer");

	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(strSearch);
	pCmd.AddParameter(bAll);

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	long nCNo, nID;
	CString strCompany, strDong;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("nID", nID);

		m_lstLeft.InsertItem(i, itoa(nID, buffer, 10));
		m_lstLeft.SetItemText(i, 1, strCompany);
		m_lstLeft.SetItemText(i, 2, strDong);
		m_lstLeft.SetItemLong(i, nCNo);

		pRs.MoveNext();
	}	

	m_lstLeft.Populate();
}

void CReportForm27::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_dtFromCtl, &m_dtToCtl);
	m_DateBtn.OnMenuMonth();

	m_lstLeft.InsertColumn(0, "No.", LVCFMT_LEFT, 45);
	m_lstLeft.InsertColumn(1, "����", LVCFMT_LEFT, 130);
	m_lstLeft.InsertColumn(2, "���ص�", LVCFMT_LEFT, 65);
	m_lstLeft.Populate();

	m_lstRight.InsertColumn(0,"No.",LVCFMT_LEFT,40);
	m_lstRight.InsertColumn(1,"����No",LVCFMT_RIGHT, 55);
	m_lstRight.InsertColumn(2,"�ֹ���",LVCFMT_LEFT,50);
	m_lstRight.InsertColumn(3,"ó����",LVCFMT_LEFT,50);
	m_lstRight.InsertColumn(4,"�Ƿ���",LVCFMT_LEFT, 90);
	m_lstRight.InsertColumn(5,"�μ�",LVCFMT_LEFT, 60);
	m_lstRight.InsertColumn(6,"���",LVCFMT_LEFT, 50);
	m_lstRight.InsertColumn(7,"��ȭ��ȣ",LVCFMT_LEFT, 90);

	m_lstRight.InsertColumn(8,"�����",LVCFMT_LEFT,90);
	m_lstRight.InsertColumn(9,"��������",LVCFMT_LEFT,90);
	m_lstRight.InsertColumn(10,"�μ�",LVCFMT_LEFT,70);
	m_lstRight.InsertColumn(11,"��ȭ��ȣ",LVCFMT_LEFT, 90);

	m_lstRight.InsertColumn(12,"������",LVCFMT_LEFT,90);
	m_lstRight.InsertColumn(13,"���������",LVCFMT_LEFT,90);
	m_lstRight.InsertColumn(14,"�μ�",LVCFMT_LEFT,90);
	m_lstRight.InsertColumn(15,"��ȭ��ȣ",LVCFMT_LEFT, 90);

	m_lstRight.InsertColumn(16,"�����ȸ��",LVCFMT_RIGHT,100);
	m_lstRight.InsertColumn(17,"�����",LVCFMT_RIGHT,60);
	m_lstRight.InsertColumn(18,"�⺻",LVCFMT_RIGHT,40);
	m_lstRight.InsertColumn(19,"�߰�",LVCFMT_RIGHT,40);
	m_lstRight.InsertColumn(20,"����",LVCFMT_RIGHT,40);
	m_lstRight.InsertColumn(21,"�հ�",LVCFMT_RIGHT,40);

	//m_lstRight.InsertColumn(22,"�ΰ���",LVCFMT_RIGHT,40);
	//m_lstRight.InsertColumn(23,"�ΰ��� ����",LVCFMT_RIGHT,40);

	m_lstRight.InsertColumn(22,"Ź�۷�",LVCFMT_RIGHT,50);
	m_lstRight.InsertColumn(23,"�պ�",LVCFMT_CENTER,40);
	m_lstRight.InsertColumn(24,"����",LVCFMT_CENTER,40);
	m_lstRight.InsertColumn(25,"����",LVCFMT_CENTER,40);
	m_lstRight.InsertColumn(26,"���",LVCFMT_CENTER,40);
	m_lstRight.InsertColumn(27,"����",LVCFMT_CENTER,120);
	m_lstRight.InsertColumn(28,"����",LVCFMT_CENTER,50);
	m_lstRight.InsertColumn(29,"����",LVCFMT_CENTER,50);
	m_lstRight.InsertColumn(30,"�Ⱦ�",LVCFMT_CENTER,50);
	m_lstRight.InsertColumn(31,"�Ϸ�",LVCFMT_CENTER,50);
	m_lstRight.InsertColumn(32,"���ͳ�",LVCFMT_CENTER,60);
	m_lstRight.InsertColumn(33,"����",LVCFMT_CENTER,50);
	m_lstRight.InsertColumn(34,"�����ð�",LVCFMT_CENTER,70);
	m_lstRight.Populate();

	m_lstRight.LoadReportOrder("CReportForm27", "m_lstRight");
 
	SetResize(IDC_LEFT_LIST, sizingBottom);
	SetResize(IDC_RIGHT_LIST, sizingRightBottom);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CReportForm27::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstLeft.GetRecords();

	for(int i=ZERO; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strCompany = (CString)pRecord->GetItem(1)->GetCaption(NULL);

		if(strCompany.Find(strSearch) >= ZERO)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstLeft.Populate();
}

void CReportForm27::OnBnClickedRefreshBtn()
{
	m_lstRight.DeleteAllItems();
	CXTPGridSelectedRows *pRows = m_lstLeft.GetSelectedRows();


	if(pRows == NULL || pRows->GetCount() == ZERO)
	{
		MessageBox("��ȸ�Ϸ��� ���� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(pRows->GetCount() > 300)
	{
		MessageBox("300���̻� ���� ��ȸ �ϽǼ� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CString strCNoSum = GetSelectedCNo();
	//long nLen = strCNoSum.GetLength();

	UpdateData(TRUE);

	int nItem = 0;
	CString csNo,csTemp,csTemp1;

	long nTNo, nCash =0, nCredit =0 , nOnline= 0;
	COleDateTime dt0, dt1, dt2, dt3, dt4, dtFinal;
	CString strOWNER, strDepart, strName;
	CString strStart, strDest;
	int nRNo, nCarType, nPayType, nWayType, nState;
	long nTotalFee = 0, nTotalConFee = 0, nTotalSum = 0;
	char buffer[20];
	BOOL bInternet;
	CString strSDong, strDDong, sEtc, sRiderCompany, strSManager, strDManager;
	long nChargeBasic, nChargeDis, nChargeAdd, nChargeTrans, nChargeSum;
	long nSChargeBasic = 0, nSChargeDis = 0, nSChargeAdd = 0, nSChargeTrans = 0, nSChargeSum = 0;
	long nSChargeCreditTrans = 0, nSignType;
	CString strOPhone, strOMobile, strSPhone, strSMobile, strDPhone, strDMobile, strSDepart, strDDepart;
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_credit_customer_report_4");
	pCmd.AddParameter(strCNoSum);
	pCmd.AddParameter(m_dtFrom);
	pCmd.AddParameter(m_dtTo);

	if(pRs.Execute(&pCmd) == FALSE) return;
 
	while(!pRs.IsEOF()) 
	{	
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("OWNER", strOWNER);
		pRs.GetFieldValue("dt0", dt0);
		pRs.GetFieldValue("dt1", dt1);
		pRs.GetFieldValue("dt2", dt2);
		pRs.GetFieldValue("dt3", dt3);
		pRs.GetFieldValue("dt4", dt4);
		pRs.GetFieldValue("dtFinal", dtFinal);
		pRs.GetFieldValue("sStart", strStart);
		pRs.GetFieldValue("sDest", strDest);
		pRs.GetFieldValue("sSDong", strSDong);
		pRs.GetFieldValue("sDDong", strDDong);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nChargeBasic", nChargeBasic);
		pRs.GetFieldValue("nChargeDis", nChargeDis);
		pRs.GetFieldValue("nChargeAdd", nChargeAdd);
		pRs.GetFieldValue("nChargeSum", nChargeSum);
		pRs.GetFieldValue("nChargeTrans", nChargeTrans);
		pRs.GetFieldValue("nCarType", nCarType);
		pRs.GetFieldValue("nWayType", nWayType);
		pRs.GetFieldValue("nPayType", nPayType);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sDepart", strDepart);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("nChargeDis", nChargeDis);
		pRs.GetFieldValue("sEtc", sEtc); 
		pRs.GetFieldValue("sRiderCompany", sRiderCompany);
		pRs.GetFieldValue("bInternet", bInternet);
		pRs.GetFieldValue("sSManager", strSManager);
		pRs.GetFieldValue("sDManager", strDManager);
		pRs.GetFieldValue("sOPhone", strOPhone);
		pRs.GetFieldValue("sOMobile", strOMobile);
		pRs.GetFieldValue("sSPhone", strSPhone);
		pRs.GetFieldValue("sSMobile", strSMobile);
		pRs.GetFieldValue("sDPhone", strDPhone);
		pRs.GetFieldValue("sDMobile", strDMobile);
		pRs.GetFieldValue("nSignType", nSignType);
		pRs.GetFieldValue("sSDepart", strSDepart);
		pRs.GetFieldValue("sDDepart", strSDepart);
					
		int nCol = 1;

		//if(nItem == 0) m_sCompany = strOWNER;
		m_lstRight.InsertItem(nItem, ltoa(nItem + 1, buffer, 10));
		m_lstRight.SetItemText(nItem,nCol++, ltoa(nTNo, buffer, 10));
		m_lstRight.SetItemText(nItem, nCol++, dt0.Format("%m-%d"));
		m_lstRight.SetItemText(nItem, nCol++, dt1.Format("%m-%d"));
		m_lstRight.SetItemText(nItem, nCol++, strOWNER);
		m_lstRight.SetItemText(nItem, nCol++, strDepart);
		m_lstRight.SetItemText(nItem, nCol++, strName);
		m_lstRight.SetItemText(nItem, nCol++, LF->GetTwoPhone(strOPhone, strOMobile));

		if(strStart != strSDong)
            m_lstRight.SetItemText(nItem, nCol++, strStart + "(" + strSDong + ")");
		else 
            m_lstRight.SetItemText(nItem, nCol++, strStart); //7

		m_lstRight.SetItemText(nItem, nCol++, strSManager);
		m_lstRight.SetItemText(nItem, nCol++, strSDepart);

		m_lstRight.SetItemText(nItem, nCol++, LF->GetTwoPhone(strSPhone, strSMobile));

		if(strDest != strDDong)
			m_lstRight.SetItemText(nItem, nCol++, strDest + "(" + strDDong + ")");
		else 
            m_lstRight.SetItemText(nItem, nCol++, strDest);

		m_lstRight.SetItemText(nItem, nCol++, strDManager);
		m_lstRight.SetItemText(nItem, nCol++, strDDepart);
		m_lstRight.SetItemText(nItem, nCol++, LF->GetTwoPhone(strDPhone, strDMobile));

		m_lstRight.SetItemText(nItem, nCol++, sRiderCompany);

		csTemp.Format("%d ȣ", nRNo);
		m_lstRight.SetItemText(nItem, nCol++, csTemp);


 		nSChargeBasic += nChargeBasic;
		nSChargeDis += nChargeDis;
		nSChargeAdd += nChargeAdd; 		
		nSChargeTrans += nChargeTrans;
		nSChargeSum += nChargeSum;

		switch(nPayType)
		{
		case 0:
		case 1:
		case 5:
			nCash += nChargeSum;
			break;
		case 2:
			nCredit += nChargeSum;
			nSChargeCreditTrans += nChargeTrans;
			break;
		case 3:
			nOnline += nChargeSum;
			nSChargeCreditTrans += nChargeTrans;
			break;
		}

		m_lstRight.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nChargeBasic)); //11
		m_lstRight.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nChargeAdd));
		m_lstRight.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nChargeDis));
		m_lstRight.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nChargeSum));
		m_lstRight.SetItemText(nItem, nCol++, LF->RemoveZero(LF->GetMyNumberFormat(nChargeTrans)));
		m_lstRight.SetItemText(nItem, nCol++, LF->GetWayTypeFromLong(nWayType)); 
		m_lstRight.SetItemText(nItem, nCol++, LF->GetCarTypeFromLong(nCarType));
		m_lstRight.SetItemText(nItem, nCol++, LF->GetPayTypeFromLong(nPayType));//18
		m_lstRight.SetItemText(nItem, nCol++, LF->GetStateString(nState)); 
		m_lstRight.SetItemText(nItem, nCol++, sEtc); 
		m_lstRight.SetItemText(nItem, nCol++, dt1.Format("%H:%M"));
		m_lstRight.SetItemText(nItem, nCol++, dt3.Format("%H:%M"));
		m_lstRight.SetItemText(nItem, nCol++, dt4.Format("%H:%M")); 
		m_lstRight.SetItemText(nItem, nCol++, dtFinal.Format("%H:%M"));
		m_lstRight.SetItemText(nItem, nCol++, bInternet ? "O" : "X");
		
		if(nSignType == 3)
			m_lstRight.SetItemText(nItem, nCol++, "��,��");
		else if(nSignType == 1)
			m_lstRight.SetItemText(nItem, nCol++, "��");
		else if(nSignType == 2)
			m_lstRight.SetItemText(nItem, nCol++, "��");
		else 
			m_lstRight.SetItemText(nItem, nCol++, "");

		m_lstRight.SetItemText(nItem, nCol++, dt1.Format("%y-%m-%d %H:%M"));

		m_lstRight.SetItemNoSort(nItem++, FALSE);

		pRs.MoveNext();
	}
	pRs.Close();

	if(nItem > 0)
	{
		int nChargeSum = nSChargeSum + nSChargeCreditTrans;
		int nSurTax = nChargeSum * 0.1;

		m_lstRight.InsertItem(nItem,""); 
		m_lstRight.SetItemText(nItem, 18, LF->GetMyNumberFormat(nSChargeBasic)); 
		m_lstRight.SetItemText(nItem, 19, LF->GetMyNumberFormat(nSChargeAdd));
		m_lstRight.SetItemText(nItem, 20, LF->GetMyNumberFormat(nSChargeDis));
		m_lstRight.SetItemText(nItem, 21, LF->GetMyNumberFormat(nSChargeSum));
		m_lstRight.SetItemNoSort(nItem++, TRUE);

		m_lstRight.InsertItem(nItem,"");
		m_lstRight.SetItemText(nItem,3,"�հ�(�����+Ź��)");
		m_lstRight.SetItemText(nItem,4,"�ΰ���");  
		m_lstRight.SetItemText(nItem,5,"�ΰ��� ���� �ݾ�");
		m_lstRight.SetItemText(nItem,6,"�����");
		m_lstRight.SetItemText(nItem,7,"Ź�۷�");
		m_lstRight.SetItemNoSort(nItem++, TRUE);

		m_lstRight.InsertItem(nItem,"");
		m_lstRight.SetItemText(nItem,3, LF->GetMyNumberFormat(nSChargeSum + nSChargeCreditTrans));
		m_lstRight.SetItemText(nItem,4, LF->GetMyNumberFormat(nSurTax));
		m_lstRight.SetItemText(nItem,5, LF->GetMyNumberFormat(nChargeSum + nSurTax));
		m_lstRight.SetItemText(nItem,6, LF->GetMyNumberFormat(nSChargeSum));
		m_lstRight.SetItemText(nItem,7, LF->GetMyNumberFormat(nSChargeCreditTrans));

		m_lstRight.SetItemNoSort(nItem++, TRUE);

		m_lstRight.InsertItem(nItem,"");
		m_lstRight.SetItemNoSort(nItem++, TRUE);

		m_lstRight.InsertItem(nItem,"");	
		m_lstRight.SetItemText(nItem, 2, "�ſ�");
		m_lstRight.SetItemText(nItem, 3, LF->GetMyNumberFormat(nCredit));
		m_lstRight.SetItemText(nItem, 4, "�¶���");
		m_lstRight.SetItemText(nItem, 5, LF->GetMyNumberFormat(nOnline));
		m_lstRight.SetItemText(nItem, 6, "����");
		m_lstRight.SetItemText(nItem, 7, LF->GetMyNumberFormat(nCash));
		m_lstRight.SetItemText(nItem, 8, "Ź��");
		m_lstRight.SetItemText(nItem, 9, LF->GetMyNumberFormat(nTotalConFee));
		m_lstRight.SetItemNoSort(nItem++, TRUE);
	}

	m_lstRight.Populate();
}

CString CReportForm27::GetSelectedCNo()
{
	char buffer[10];
	CString strCNo = "";

	CXTPGridSelectedRows *pRows = m_lstLeft.GetSelectedRows();

	for(int i=ZERO; i<pRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		strCNo += CString(itoa(m_lstLeft.GetItemLong(pRecord), buffer, 10)) + ";";
	}

	return strCNo;
}

void CReportForm27::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));

	CMyFormView::OnMouseMove(nFlags, point);
}

void CReportForm27::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		CRect rect;
		m_lstRight.GetWindowRect(&rect);
		ScreenToClient(rect);

		if(rect.PtInRect(point))
		{
			OnBnClickedRefreshBtn();
		}
	}

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	::ReleaseCapture();
	m_bDragMode  = FALSE;  //������ ���� �Ұ�

	CMyFormView::OnLButtonUp(nFlags, point);
}

BOOL CReportForm27::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN) 
		{
			if(pMsg->hwnd == m_edtSearch.GetSafeHwnd())
			{
				RefreshCustomerList(FALSE);
			}
		}
	}

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CReportForm27::OnReportColumnRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CPoint pt;
	::GetCursorPos(&pt);

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	menu.AppendMenu(MF_STRING, ID_VISIBLE_COL, "�÷�����");
	menu.TrackPopupMenu(TPM_NONOTIFY | TPM_RETURNCMD | TPM_LEFTALIGN |TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL);
}

void CReportForm27::OnVisibleCol()
{ 
	CColumnSelDlg dlg;
	dlg.m_plstReport = (CXTPListCtrl2*)&m_lstRight;
	dlg.m_sClass = "CReportForm27";

	//if(m_lstRight.GetColumns()->GetCount() > 22)
		dlg.m_sList = "m_lstRight";

	if(dlg.DoModal())
	{
		m_lstRight.LoadReportOrder(dlg.m_sClass, dlg.m_sList);
		m_lstRight.Populate();
	}
}
void CReportForm27::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstRight.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CXTPGridColumn *p = m_lstRight.GetColumns()->GetAt(0); 
	if(p == NULL) return; 

	long h = m_lstRight.GetReportHeader()->GetGroupByHeight();

	CRect rcHeader = p->GetRect(); 

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu = NULL;

	if(point.y >= rect.top && 
		point.y <= rect.top + h )
	{
		pRMenu=rMenu.GetSubMenu(22);
	}
	else
		pRMenu=rMenu.GetSubMenu(2);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}


void CReportForm27::OnViewExcel()
{
	if(!LF->POWER_CHECK(3900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 351, m_ui.nWNo, m_lstRight.GetItemCount());  
	CMyExcel::ToExcel(&m_lstRight);
}