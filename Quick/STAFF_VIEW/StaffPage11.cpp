// StaffPage11.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "StaffPage11.h"

#include "InDoorDlg.h"
#include "WorkStopMemoDlg.h"

// CStaffPage11

IMPLEMENT_DYNCREATE(CStaffPage11, CMyFormView)

CStaffPage11::CStaffPage11()
	: CMyFormView(CStaffPage11::IDD)
{
}

CStaffPage11::~CStaffPage11()
{
	m_List.SaveReportOrder("CStaffPage11", "m_List");
}

void CStaffPage11::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CON_WORKING_COMBO, m_ConWorkingCombo);
	DDX_Control(pDX, IDC_WNO_LIST, m_List);
	DDX_Control(pDX, IDC_RIDER_EDIT, m_RiderEdt);	
	DDX_Control(pDX, IDC_DRAW_STATIC, m_DrawStc);
}

BEGIN_MESSAGE_MAP(CStaffPage11, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnBnClickedButtonModify)
	ON_CBN_SELCHANGE(IDC_CON_WORKING_COMBO, OnCbnSelchangeConWorkingCombo)
	ON_EN_CHANGE(IDC_RIDER_EDIT, OnEnChangeRiderEdit)
	ON_NOTIFY(NM_CLICK, IDC_WNO_LIST, OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_WNO_LIST, OnReportItemDblClick)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_WORK_STOP, OnWorkStop)
	ON_COMMAND(ID_WORK_OK, OnWorkOk)
	ON_COMMAND(ID_MENU_MSG, OnMenuMsg)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_WNO_LIST, OnReportItemChange)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CStaffPage11 �����Դϴ�.

#ifdef _DEBUG
void CStaffPage11::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CStaffPage11::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CStaffPage11 �޽��� ó�����Դϴ�.

void CStaffPage11::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CStaffPage11::RefreshList()
{
	CMyFormView::RefreshList();


	long nLastSel = max(0, m_List.GetNextItem(-1, LVNI_SELECTED));

	m_WnoMap.clear();
	m_List.DeleteAllItems();
	InitControl();

	const char *szRoleString[] = {"������", "������", "���", "UNKNOWN"};
	char buffer[20];
	int nCurSel = -1;

	CWaitCursor wait;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_worker_wno"); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ConWorkingCombo.GetCurSel());

	if(!pRs.Execute(&pCmd)) return;

	long nCompany, nWNo, nWorkPart, nWorkState, nWorkType, nANo, nRole;
	CString sName, sID, sPhone, sMp, sSSN1, sSSN2, sPosition;
	COleDateTime dtEnter, dtWorkStateDate;
	BOOL bWorking, bApplyInsurance;

	CString sAddress, sMemo, strAuthPhone;

	long nItem = 1; 
 
	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		CString strWorkStop = "";
		WNO_STRUCT st;

		pRs.GetFieldValue("lANo", nANo); 
		pRs.GetFieldValue("lCode", nCompany);
		pRs.GetFieldValue("nMNo", nWNo);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sID", sID);
		pRs.GetFieldValue("nWorkPart", nWorkPart);
		pRs.GetFieldValue("sTel", sPhone);
		pRs.GetFieldValue("sHp", sMp);
		pRs.GetFieldValue("dtEnter", dtEnter);
		pRs.GetFieldValue("sSSN1", sSSN1);
		pRs.GetFieldValue("sSSN2", sSSN2);
		pRs.GetFieldValue("bApplyInsurance", bApplyInsurance);
		pRs.GetFieldValue("nWorkStateReal", nWorkState);
		pRs.GetFieldValue("dtWorkStateDate", dtWorkStateDate);
		pRs.GetFieldValue("sPosition", sPosition);
		pRs.GetFieldValue("nWorkType", nWorkType);
		pRs.GetFieldValue("bWorking", bWorking);
		pRs.GetFieldValue("nRole", nRole);
		pRs.GetFieldValue("nWorkPart", nWorkPart);
		pRs.GetFieldValue("sID", sID);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sSSN1", sSSN1);
		pRs.GetFieldValue("sSSN2", sSSN2);
		pRs.GetFieldValue("nWorkType", nWorkType);
		pRs.GetFieldValue("sAddress", sAddress);
		pRs.GetFieldValue("sEtc", sMemo); 
		pRs.GetFieldValue("sAuthPhone", strAuthPhone); 

		m_List.InsertItem(i, "");
		m_List.SetItemText(i, nItem++, itoa(nWNo, buffer, 10));

		if(LF->GetCurBranchInfo()->bIntegrated)
			m_List.SetItemText(i, nItem++, m_ci.GetName(nCompany));

		m_List.SetItemText(i, nItem++, sID);
		m_List.SetItemText(i, nItem++, sName);
		m_List.SetItemText(i, nItem++, sPosition);
		m_List.SetItemText(i, nItem++, nRole == 0 ? "������" : "");
		m_List.SetItemText(i, nItem++, GetWorkPart(nWorkPart));
		m_List.SetItemText(i, nItem++, GetWorkType(nWorkType));
		m_List.SetItemText(i, nItem++, LF->GetDashPhoneNumber(sPhone));
		m_List.SetItemText(i, nItem++, LF->GetDashPhoneNumber(sMp));
		m_List.SetItemText(i, nItem++, dtEnter.Format("%Y-%m-%d"));
		m_List.SetItemText(i, nItem++, sSSN1 + "-" +sSSN2);
		m_List.SetItemText(i, nItem++, bApplyInsurance ? "����" : "");

	
		if(nWorkState > 0)
		{
			if(dtWorkStateDate.m_dt == 0)
				strWorkStop = "��������";
			else
			{
				strWorkStop.Format("%4d-%02d-%02d %02d:%02d:%02d",dtWorkStateDate.GetYear(),
					dtWorkStateDate.GetMonth(),dtWorkStateDate.GetDay(),dtWorkStateDate.GetHour(),
					dtWorkStateDate.GetMinute(),dtWorkStateDate.GetSecond());

			}
		}
 
		m_List.SetItemText(i, nItem++, strWorkStop);
		m_List.SetItemText(i, nItem++, LF->GetDashPhoneNumber(strAuthPhone));		
		m_List.SetItemData(i, (DWORD)nWorkState);
		m_List.SetItemLong(i, nCompany);

		st.nANo = nANo;
		st.nCompany = nCompany;
		st.nWNo = nWNo;
		st.nWorkState = nWorkState;
		st.nWorkPart = nWorkPart;
		st.sID = sID;
		st.sName = sName;
		st.sSSN1 = sSSN1;
		st.sSSN2 = sSSN2;
		st.sMp = sMp;
		st.sPhone = sPhone;
		st.nWorkType = nWorkType;
		st.sAddress = sAddress;
		st.sMemo = sMemo;
		st.dtEnter = dtEnter;

		m_WnoMap[i] = st;
		nItem = 1;

		pRs.MoveNext();
	}

	m_List.Populate();

	if(nLastSel < m_List.GetItemCount())  
	{ 
		CXTPGridRows *pRows = m_List.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(min(max(nLastSel + 10, nLastSel), m_List.GetItemCount()-1));
		m_List.EnsureVisible(pRow);
		m_List.SetSelectedRow(nLastSel);
	}
}

void CStaffPage11::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	SetResize(IDC_WNO_LIST, sizingRightBottom);

	m_ConWorkingCombo.SetCurSel(1);

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
		LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	InitControl();

	m_List.LoadReportOrder("CStaffPage11", "m_List");
}

void CStaffPage11::InitControl()
{
	int nItem = 0;

	//�÷� ��� ����
	//int nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();
	int nColumnCount = m_List.GetColumns()->GetCount();
	for(int i=0;i < nColumnCount;i++)
	{
		CXTPGridColumns *pColums = m_List.GetColumns();
		pColums->Remove(pColums->GetAt(0));
	}

	m_List.InsertColumn(nItem++, "NO", LVCFMT_CENTER, 40);
	m_List.InsertColumn(nItem++, "���", LVCFMT_CENTER, 50);
	if(LF->GetCurBranchInfo()->bIntegrated)
		m_List.InsertColumn(nItem++, "�� ��", LVCFMT_CENTER, 85);

	m_List.InsertColumn(nItem++, "���̵�",	LVCFMT_LEFT, 100);
	m_List.InsertColumn(nItem++, "�� ��", LVCFMT_LEFT, 80);
	m_List.InsertColumn(nItem++, "����", LVCFMT_CENTER, 60);
	m_List.InsertColumn(nItem++, "����", LVCFMT_CENTER, 60);
	m_List.InsertColumn(nItem++, "��������", LVCFMT_CENTER, 70);	
	m_List.InsertColumn(nItem++, "�ٹ�����",LVCFMT_CENTER, 110);
	m_List.InsertColumn(nItem++, "��ȭ��ȣ", LVCFMT_LEFT, 100);
	m_List.InsertColumn(nItem++, "�޴���", LVCFMT_LEFT, 100);
	m_List.InsertColumn(nItem++, "�Ի���", LVCFMT_CENTER, 80);	
	m_List.InsertColumn(nItem++, "�ֹι�ȣ",LVCFMT_CENTER, 110);
	m_List.InsertColumn(nItem++, "4�뺸��",LVCFMT_CENTER, 60);
	m_List.InsertColumn(nItem++, "��������",LVCFMT_CENTER, 100);	
	m_List.InsertColumn(nItem++, "����ƮQ Tab ������ȣ",LVCFMT_CENTER, 150);	

	m_List.SetOrderIndexCol(0);

	m_List.Populate();

}

void CStaffPage11::OnBnClickedButtonNew()
{
	CInDoorDlg dlg(this);
	dlg.m_bNewMode = TRUE;
	dlg.DoModal();
}

CString CStaffPage11::GetWorkPart(long nWorkPart)
{
	CString sWorkPart = "�˼�����";

	switch (nWorkPart)
	{
	case 0:
		sWorkPart = "�ݼ���";
		break;
	case 1:
		sWorkPart = "������";
		break;
	case 2:
		sWorkPart = "�ѹ���";
		break;
	case 3:
		sWorkPart = "������";
		break;
	case 4:
		sWorkPart = "��Ȳ��";
		break;
	case 5:
		sWorkPart = "ȫ����";
		break;
	case 6:
		sWorkPart = "��Ÿ";
		break;
	}

	return sWorkPart;
}

CString CStaffPage11::GetWorkType(long nWorkType)
{
	CString sWorkType = "�˼�����";

	switch (nWorkType)
	{
	case 0:
		sWorkType = "������";
		break;
	case 1:
		sWorkType = "�ӽ���";
		break;
	case 2:
		sWorkType = "�Ƹ�����Ʈ";
		break;
	case 3:
		sWorkType = "�Ͽ���";
		break;
	case 4:
		sWorkType = "��Ÿ";
		break;
	}

	return sWorkType;
}

void CStaffPage11::OnBnClickedButtonModify()
{
	long nIndex = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == -1) return;

	//if(m_List.GetItemText(nIndex, 1) == "0")
	//{
	//	MessageBox("�ְ�����ڴ� �����Ͻ� �� �����ϴ�", "Ȯ��",MB_ICONINFORMATION);
	//	return;
	//}

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();
	CXTPGridRow *pRow = pRows->GetAt(0);
	nIndex = pRow->GetRecord()->GetIndex();

	CInDoorDlg dlg(this);
	dlg.m_nCompany = m_WnoMap[nIndex].nCompany;
	dlg.m_nWNo = m_WnoMap[nIndex].nWNo;
	dlg.m_nANo = m_WnoMap[nIndex].nANo;
	dlg.m_nWorkState = m_WnoMap[nIndex].nWorkState;
	dlg.m_bNewMode = FALSE;

	dlg.DoModal();
	//dlg.m_nCompany = m_WnoMap[nIndex].nCompany;
}


void CStaffPage11::OnCbnSelchangeConWorkingCombo()
{
	RefreshList();
}


void CStaffPage11::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

//	CRect rc;
//	m_DrawStc.GetWindowRect(rc); 
//	ScreenToClient(rc); 

//	InvalidateRect(rc);
}


void CStaffPage11::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	OnBnClickedButtonModify();
}

void CStaffPage11::ChangeStaff(CDC &pDC)
{
	CRect rc;
	m_DrawStc.GetWindowRect(rc);
	ScreenToClient(rc);

	pDC.FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(), RGB(230, 255, 230)); 
	rc.DeflateRect(5, 5, 5, 5);

	long nTop = rc.top;
	long nBottom = rc.bottom;
	pDC.SelectObject(m_FontManager.GetFont("���� ���", 17, FW_BOLD));

	long nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	BOOL bSelect = FALSE;

	if(nItem == -1) 
		bSelect = FALSE;
	else
		bSelect = TRUE;

	rc.right = rc.left + 200;

	char buffer[20];

	PrintLine(&pDC, rc, "ȸ �� ��", bSelect ? m_ci.GetName(m_WnoMap[nItem].nCompany) : "");
	PrintLine(&pDC, rc, "�� �� ��", bSelect ? m_ci.GetBranchName(m_WnoMap[nItem].nCompany) : "");
	PrintLine(&pDC, rc, "��    ��", bSelect ? m_WnoMap[nItem].sName : "");
	PrintLine(&pDC, rc, "�� �� ��", bSelect ? m_WnoMap[nItem].sID : "");
	PrintLine(&pDC, rc, "�� �� ��", bSelect ? m_WnoMap[nItem].dtEnter.Format("%y-%m-%d") : "");

	rc.left =  rc.right + 20;
	rc.right = rc.left + 200;
	rc.top = nTop;
	rc.bottom = nBottom;

	//dc.SelectObject(RGB(255, 255, 255));
	pDC.MoveTo(rc.left - 10, rc.top);
	pDC.LineTo(rc.left - 10, rc.bottom);

	PrintLine(&pDC, rc, "��    ��", bSelect ? itoa(m_WnoMap[nItem].nWNo, buffer, 10) : "");
	if(bSelect)
	{
		if(m_WnoMap[nItem].nWorkState == 0)
			PrintLine(&pDC, rc, "��������", bSelect ? "����" : "");
		else if(m_WnoMap[nItem].nWorkState == 1)
			PrintLine(&pDC, rc, "��������", bSelect ? "����(��������)" : "");
		else
			PrintLine(&pDC, rc, "��������", bSelect ? "����" : "");
	}
	else
		PrintLine(&pDC, rc, "��������", "");

	PrintLine(&pDC, rc, "�ٹ�����", bSelect ? GetWorkType(m_WnoMap[nItem].nWorkType) : "");
	PrintLine(&pDC, rc, "��������", bSelect ? GetWorkPart(m_WnoMap[nItem].nWorkPart) : "");
	PrintLine(&pDC, rc, "��    ��", bSelect ? m_WnoMap[nItem].sAddress : "");

	rc.left =  rc.right + 20;
	rc.right = rc.left + 200;
	rc.top = nTop;
	rc.bottom = nBottom;

	pDC.MoveTo(rc.left - 10, rc.top);
	pDC.LineTo(rc.left - 10, rc.bottom);

	if(m_WnoMap[nItem].sMemo.GetLength() > 20) 
	{
		PrintLine(&pDC, rc, "�޸�", "");
		rc.right = rc.left + 500; 
		pDC.SetTextColor(RGB(0, 255, 0));
		pDC.DrawText(m_WnoMap[nItem].sMemo, rc, DT_LEFT);
	}
	else
		PrintLine(&pDC, rc, "�޸�", bSelect ? m_WnoMap[nItem].sMemo : "");

}

void CStaffPage11::OnEnChangeRiderEdit()
{
	CXTPGridRows *pRows = m_List.GetRows();
	CXTPGridRecords *pRecords = m_List.GetRecords();
	CXTPGridColumn *pColumn = NULL;

	CString strName, strRNo, strID;

	CString strSearchData; m_RiderEdt.GetWindowText(strSearchData);
	m_List.m_strSearchData = strSearchData;  

	for(int i=0; i<m_List.GetRecords()->GetCount(); i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		strRNo = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(1))->GetCaption(pColumn);
		strID= ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(3))->GetCaption(pColumn);
		strName = ((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(4))->GetCaption(pColumn);

		if((strName.Find(strSearchData) >= 0) ||
			(strID.Find(strSearchData) >= 0) ||
			(strRNo.Find(strSearchData) >= 0) )
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_List.Populate();
}

void CStaffPage11::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(3);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}



void CStaffPage11::OnViewExcel()
{
	if(!LF->POWER_CHECK(5900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 401, m_ui.nWNo, m_List.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_List);
}


void CStaffPage11::OnWorkStop()
{
	UINT i, uSelectedCount = m_List.GetSelectedRows()->GetCount();
	int  nItem = -1;

	// Update all of the selected items.
	if(uSelectedCount > 0)
	{
		CString strWorkMemo;
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
			strWorkMemo = dlg.m_strWorkStopMemo;
		else
			return;

		for (i = 0;i < uSelectedCount; i++)
		{
			nItem = m_List.GetNextItem(nItem, LVNI_SELECTED);
			if(nItem < 0) break;

			CString sRNo = m_List.GetItemText(nItem, 1);
 
			if(_ttoi(sRNo) == 0)
			{
				MessageBox("�����ڴ� �����Ͻ� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
				return;
			}
	
			CWaitCursor wait;
			CMkCommand pCmd(m_pMkDb, "update_RC_workstate_2008");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_List.GetItemLong(nItem));
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), _ttoi(sRNo));		
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), 1);
			pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
			pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
			pCmd.Execute();
		}
	}
	else {
		MessageBox("������ �����Ͻʽÿ�!", "Ȯ��", MB_ICONINFORMATION);
	}

	RefreshList();
}

void CStaffPage11::OnWorkOk()
{
	UINT i, uSelectedCount = m_List.GetSelectedRows()->GetCount();
	int  nItem = -1;

	// Update all of the selected items.
	if(uSelectedCount > 0)
	{
		CString strWorkMemo;
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
			strWorkMemo = dlg.m_strWorkStopMemo;
		else
			return;

		for (i = 0;i < uSelectedCount; i++)
		{
			nItem = m_List.GetNextItem(nItem, LVNI_SELECTED);
			if(nItem < 0) break;

			CString sRNo = m_List.GetItemText(nItem, 1);

			if(_ttoi(sRNo) == 0)
			{
				MessageBox("�����ڴ� �����Ͻ� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
				return;
			}

			CWaitCursor wait;
			CMkCommand pCmd(m_pMkDb, "update_RC_workstate_2008");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_List.GetItemLong(nItem));
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), _ttoi(sRNo));		
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);
			pCmd.AddParameter(typeString, typeInput, strWorkMemo.GetLength(), strWorkMemo);
			pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
			pCmd.Execute();
		}
	}
	else {
		MessageBox("������ �����Ͻʽÿ�!", "Ȯ��", MB_ICONINFORMATION);
	}

	RefreshList();
}

void CStaffPage11::OnMenuMsg()
{
	return;
}


void CStaffPage11::OnBnClickedButtonDelete()
{
	if(!LF->POWER_CHECK(5012, "���/����/���Ի�ó��", TRUE))
		return;

	int nSelect = MessageBox("������ �Ͻø� ����Ÿ�� ������ �������ϴ�.\n\n"\
		"���ó���� ���Ͻø� ���� ������ ���Ͻø�\n\n"\
		"�ƴϿ��� �����ּ���","����Ȯ��â",MB_ICONQUESTION | MB_YESNOCANCEL);

	long nIndex = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(nIndex == -1) return;

	CXTPGridColumn *pColumn = NULL;

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();
	CXTPGridRow *pRow = pRows->GetAt(0);
	nIndex = pRow->GetRecord()->GetIndex();

	if((pRow->GetRecord()->GetItem(1)->GetCaption(pColumn)) == "0")
	{
		MessageBox("�ְ�����ڴ� �����Ͻ� �� �����ϴ�", "Ȯ��",MB_ICONINFORMATION);
		return;
	}

	switch(nSelect)
	{
	case IDYES:
		{
			int nItem = m_List.GetNextItem(0, LVNI_SELECTED);	
			if(nItem >= 0) {
				CWaitCursor wait;
				CMkCommand pCmd(m_pMkDb, "deploy_worker3");
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_WnoMap[nIndex].nANo);
				pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), COleDateTime::GetCurrentTime());
				if(pCmd.Execute()) 
				{
					MessageBox("��� ó���Ǿ����ϴ�.", "���Ȯ��", MB_ICONINFORMATION);
					RefreshList();
				}
			}
		}
		break;
	case IDNO:
		{

			UpdateData(TRUE);
			try
			{			
				int nSelItem;
				if((nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED)) < 0)
					throw "�����ϰ��� �ϴ� ����� �����Ͻñ� �ٶ��ϴ�.";

				if(IDYES == MessageBox("���� �����Ͻðڽ��ϱ�?", "����Ȯ��", MB_YESNO | MB_ICONQUESTION))
				{
					CString strStoredProc;

					long nWorkState = m_List.GetItemData(nSelItem);

					if(nWorkState < 2) 
						strStoredProc = "delete_worker_3";
					else
						strStoredProc = "delete_deploy_worker_1";

					CMkCommand pCmd(m_pMkDb, strStoredProc);
					pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_WnoMap[nIndex].nANo);
					pCmd.Execute();
					/*
					CString strRNo = m_List.GetItemText(nSelItem,0);						
					CMkCommand pCmd2(m_pMkDb, "delete_driver_group_alone");
					pCmd2.AddParameter(typeLong, typeInput, sizeof(int), m_nCompanyCode);										
					pCmd2.AddParameter(typeLong, typeInput, sizeof(int), atoi(strRNo));											
					pCmd2.Execute();
					*/

					RefreshList();
				}
			}
			catch(char *str)
			{
				MessageBox(str, "Ȯ��", MB_ICONEXCLAMATION);
			}
		}
		break;
	case IDCANCEL:
		{}
		break;
	}
}


void CStaffPage11::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CRect rc;
	m_DrawStc.GetWindowRect(rc); 
	ScreenToClient(rc); 

	InvalidateRect(rc);
}

void CStaffPage11::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this); 
	ChangeStaff(dc);
}

void CStaffPage11::PrintLine(CDC *pDC, CRect &rc, CString strTitle, CString strText)
{
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->DrawText(strTitle, rc, DT_LEFT);
	pDC->SetTextColor(RGB(0, 255, 0));
	pDC->DrawText(strText, rc, DT_RIGHT);

	rc.top += 20;
}
