// Report3.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"
#include "StaffPage17.h"
#include "WorkStopMemoDlg.h"
#include "RiderMsgDlg.h"
#include "RcpView.h"

#define MAX_DAY 100

// CStaffPage17 ��ȭ �����Դϴ�.

IMPLEMENT_DYNCREATE(CStaffPage17, CMyFormView)
CStaffPage17::CStaffPage17()
: CMyFormView(CStaffPage17::IDD)
{
	m_nLastCompanyCount = 0;
}

CStaffPage17::~CStaffPage17()
{

}

void CStaffPage17::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_DateTimeCtrl(pDX, IDC_DTP_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DTP_TO, m_dtTo);

	DDX_Control(pDX, IDC_LIST_REPORT, m_XTPList);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
	DDX_Control(pDX, IDC_DTP_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DTP_TO, m_ToDT);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_INCRESE_COL_BTN, m_btnIncreaseCol);
	DDX_Control(pDX, IDC_NOT_WORK_CHECK, m_chkNotWork);
}


BEGIN_MESSAGE_MAP(CStaffPage17, CMyFormView)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_COMMAND(ID_WORK_STOP, OnWorkStop)
	ON_COMMAND(ID_WORK_OK, OnWorkOk)
	ON_COMMAND(ID_SEND_MSG, OnMenuMsg)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_BN_CLICKED(IDC_INCRESE_COL_BTN, OnBnClickedIncreseColBtn)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_LIST_REPORT, OnLvnDeleteallitemsListReport)
	ON_NOTIFY(NM_CLICK, IDC_LIST_REPORT, OnNMClickListReport)
END_MESSAGE_MAP()


// CStaffPage17 �޽��� ó�����Դϴ�.


void CStaffPage17::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();

	m_stcInfo.SetWindowText("* �ܸ��� ���ӱ���");

	m_XTPList.InsertColumn(0, "����ȣ", LVCFMT_LEFT, 50);
	m_XTPList.InsertColumn(1,"�Ҽ�",LVCFMT_LEFT, 50);
	m_XTPList.InsertColumn(2, "����", LVCFMT_LEFT, 60);
	m_XTPList.InsertColumn(3, "�����", LVCFMT_RIGHT, 40);
	m_XTPList.SetFreezeColumnsCount(4);
	m_XTPList.GetPaintManager()->SetFreezeColsDividerStyle(0);
	m_XTPList.GetReportHeader()->AllowColumnReorder(FALSE);
	m_XTPList.Populate();

	MonthInit();

	SetResize(IDC_LIST_REPORT, sizingRightBottom);
}

void CStaffPage17::MonthInit(void)
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}

	dtFrom = dtFrom - COleDateTimeSpan(30, 0, 0, 0);
	m_FromDT.SetTime(dtFrom);

	//dtTo = dtTo + COleDateTimeSpan(1, 0, 0, 0); 
	m_ToDT.SetTime(dtTo);
}


void CStaffPage17::OnMenuMsg()
{
	if(!LF->POWER_CHECK(1200, "������â ����", TRUE))
		return;

	int nSelItem = m_XTPList.GetNextItem(-1, LVNI_SELECTED);

	CRiderMsgDlg dlg;
	dlg.m_nRNo = atol(m_XTPList.GetItemText(nSelItem, 0));
	dlg.DoModal();
}

void CStaffPage17::RefreshList()
{	
	CMyFormView::RefreshList();
	UpdateData(TRUE);

	//���� ���� �����ʹ� �������� �ʴ´�.
	COleDateTime dtToday = COleDateTime::GetCurrentTime() + COleDateTimeSpan(1, 0, 0, 0);
	COleDateTime dtTomorrow(dtToday.GetYear(), dtToday.GetMonth(), dtToday.GetDay(), 7, 0, 0);
	if(m_dtTo > dtTomorrow)
	{
		m_dtTo = m_dtTo - COleDateTimeSpan(1, 0, 0, 0);
		m_ToDT.SetTime(m_dtTo);
	}

	COleDateTimeSpan span = m_dtTo - m_dtFrom;
	long nDays = span.GetTotalDays();

	if(nDays > MAX_DAY)
	{ 
		MessageBox("100���̻� ��ȸ �Ͻ� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CreateHeader();
	//		CreateHeader(1); 1�Ϻ��� 31������

	m_XTPList.DeleteAllItems();
	m_RiderInfo.clear();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_device_login_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),m_dtFrom );
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),m_dtTo );
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),  m_chkNotWork.GetCheck());
	pCmd.Execute();
	
	int nDayTotAttend[MAX_DAY];

	for(int m = 0; m < MAX_DAY; m++)
		nDayTotAttend[m] = 0;

	if(pRs.Execute(&pCmd))
	{
		int nRNo, nCompany, nWorkState, nCount, nRecordIndex, nFindDay;
		COleDateTime dtDate;	
		COleDateTimeSpan dtSpan;
		CString strName, strRiderName, strTotal, strPercent, strTemp;
		RIDER_ATTEND2::iterator iter;
		float fResult = 0;
		nRNo = nCompany = nWorkState = nCount = nFindDay = 0;
		nRecordIndex = -1;

		while(!pRs.IsEOF()) 
		{
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nRNo", nRNo);
			pRs.GetFieldValue("dtDate", dtDate);
			pRs.GetFieldValue("sRName", strName);
			pRs.GetFieldValue("sRiderName", strRiderName);
			pRs.GetFieldValue("nWorkState", nWorkState);

			pair<CString, pair<int, int>> tempPair = make_pair(strName.GetLength() > 0 ? strName : strRiderName, make_pair(nCompany, nRNo));
			iter = m_RiderInfo.find(tempPair);
			if(iter == m_RiderInfo.end())
			{
				if(nRecordIndex != -1)
				{
					fResult = (float)(nCount * 100) / nDays;
					strPercent.Format("%2.1f",fResult);
					m_XTPList.SetItemText(nRecordIndex,3,strPercent);

					strTotal = LF->GetStringFromLong(nCount);
					strTotal += "��";
					m_XTPList.SetItemText(nRecordIndex, nDays + 4, strTotal);
					for(int i = nFindDay + 1; i < nDays + 4; i++)
					{
						m_XTPList.SetItemText(nRecordIndex, i, "X");
						m_XTPList.ChangeItemBackColor(nRecordIndex, i, RGB(255, 100, 100));
						m_XTPList.ChangeItemTextColor(nRecordIndex, i, RGB(255, 255, 255));
					}
				}

				nRecordIndex++;
				m_RiderInfo.insert(RIDER_ATTEND2::value_type(tempPair, nRecordIndex));

				m_XTPList.InsertItem(nRecordIndex, LF->GetStringFromLong(nRNo));
				m_XTPList.SetItemText(nRecordIndex, 1, m_ci.GetName(nCompany));
				m_XTPList.SetItemText(nRecordIndex, 2, strName.GetLength() > 0 ? strName : strRiderName);
				if(nWorkState == 1)
				{
					m_XTPList.ChangeItemBackColor(nRecordIndex, 0, RGB(255,196,196));
					m_XTPList.ChangeItemBackColor(nRecordIndex, 1, RGB(255,196,196));
				}
				m_XTPList.SetItemData(nRecordIndex, nCompany);

				nCount = 0;
			}
			else
				nRecordIndex = iter->second;

			COleDateTimeSpan dtGap(0,0,10,0); // �ڵ����� 06: 50��
			dtSpan = dtDate - (m_dtFrom - dtGap);			
			nFindDay = dtSpan.GetDays() + 4; 

			m_XTPList.SetItemText(nRecordIndex, nFindDay, "O");  // -1 ����
			m_XTPList.ChangeItemBackColor(nRecordIndex, nFindDay, RGB(100, 255, 100));
			m_XTPList.ChangeItemTextColor(nRecordIndex, nFindDay, RGB(255, 255, 255));
			nDayTotAttend[nFindDay - 4]++;
			m_XTPList.SetItemText(nRecordIndex, m_nLastCompanyCount, LF->GetStringFromLong(nCompany));
			
			nCount++;
			pRs.MoveNext();			
		}

		pRs.Close();

		if(nCount > 0)
		{
			fResult = (float)(nCount * 100) / nDays;
			strPercent.Format("%2.1f",fResult);
			m_XTPList.SetItemText(nRecordIndex, 3, strPercent);

			m_XTPList.SetItemText(nRecordIndex, nDays + 4, LF->GetStringFromLong(nCount) + "��");
			for(int i = nFindDay + 1; i < nDays + 4; i++)
			{
				m_XTPList.SetItemText(nRecordIndex, i, "X");
				m_XTPList.ChangeItemBackColor(nRecordIndex, i, RGB(255, 100, 100));
				m_XTPList.ChangeItemTextColor(nRecordIndex, i, RGB(255, 255, 255));
			}
		}

		m_XTPList.InsertItem(nRecordIndex, "�հ�");
		int nAllTotalAttend = 0;
		for(int n = 0; n < nDays; n++)
		{
			nAllTotalAttend += nDayTotAttend[n];
			m_XTPList.SetItemText(m_XTPList.GetRecords()->GetCount() - 1, n + 4, LF->GetStringFromLong(nDayTotAttend[n]));
		}
		if(nAllTotalAttend != 0)
			m_XTPList.SetItemText(m_XTPList.GetRecords()->GetCount() - 1, nDays + 4, LF->GetStringFromLong(nAllTotalAttend));
	}

	m_XTPList.Populate();
}

void CStaffPage17::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_XTPList.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_XTPList.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(2);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}
}

void CStaffPage17::OnViewExcel()
{
	if(!LF->POWER_CHECK(5900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 404, m_XTPList.GetRows()->GetCount());  
	CMyExcel::ToExcel(&m_XTPList);
}

void CStaffPage17::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CStaffPage17::CreateHeader()
{	
	COleDateTime dtRecentDay = m_dtFrom;

	DeleteColumn();

	COleDateTime dtFrom, dtTo;
	dtFrom = m_dtFrom;
	dtTo = m_dtTo - COleDateTimeSpan(1, 0, 0, 0);

	int nCol = 4;
	m_XTPList.InsertColumn( nCol++, m_dtFrom.Format("%m-%d"), LVCFMT_CENTER, 35);
	dtFrom = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	while(dtFrom <= dtTo)
	{
		if(dtFrom.GetDay() == 1)
			m_XTPList.InsertColumn( nCol++, dtFrom.Format("%m-%d"), LVCFMT_CENTER, 35);
		else
			m_XTPList.InsertColumn( nCol++, dtFrom.Format("%d"), LVCFMT_CENTER, 30);
		dtFrom = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}
	m_XTPList.InsertColumn(nCol++, "�հ�", LVCFMT_CENTER, 40);
	m_nLastCompanyCount = nCol;
	m_XTPList.InsertColumn(nCol++, "0", LVCFMT_LEFT, 0);

	m_XTPList.Populate();
}

void CStaffPage17::DeleteColumn(void)
{
	int nCount = m_XTPList.GetColumns()->GetCount();
	for(int i = 0; i < nCount; i++)
	{
		CXTPGridColumn *pColum = m_XTPList.GetColumns()->GetAt(4);
		m_XTPList.GetColumns()->Remove(pColum);
	}
}

void CStaffPage17::OnWorkStop()
{
	UINT i, uSelectedCount = m_XTPList.GetRows()->GetCount();
	int  nItem = -1;

	// Update all of the selected items.
	if(uSelectedCount > 0)
	{
		CString strWorkTitle = "";
		CString strWorkMemo = "";
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			for (i = 0;i < uSelectedCount; i++)
			{
				nItem = m_XTPList.GetNextItem(nItem, LVNI_SELECTED);
				if(nItem < 0) break;

				if(!LF->ChangeRiderWorkState(LF->GetCurBranchInfo()->nCompanyCode,
					atol(m_XTPList.GetItemText(nItem, 0)),  
					LF->GetCurBranchInfo()->bIntegrated,
					dlg.m_strWorkStopMemo,  
					dlg.m_strContent,
					TRUE))
				{
					MessageBox("�ϰ��۾��߿� �����߻�", "Ȯ��", MB_ICONERROR);
					return;
				}
			}
		}
	}
	else {
		MessageBox("������ �����Ͻʽÿ�!", "Ȯ��", MB_ICONINFORMATION);
	}

	RefreshList();
}

void CStaffPage17::OnWorkOk()
{
	UINT i, uSelectedCount = m_XTPList.GetRows()->GetCount();
	int  nItem = -1;

	// Update all of the selected items.
	if(uSelectedCount > 0)
	{
		CString strWorkTitle = "";
		CString strWorkMemo = "";
		CWorkStopMemoDlg dlg;
		if(dlg.DoModal() == IDOK)
		{
			for (i = 0;i < uSelectedCount; i++)
			{
				nItem = m_XTPList.GetNextItem(nItem, LVNI_SELECTED);
				if(nItem < 0) break;

				if(!LF->ChangeRiderWorkState(LF->GetCurBranchInfo()->nCompanyCode,
					atol(m_XTPList.GetItemText(nItem, 0)),  
					LF->GetCurBranchInfo()->bIntegrated,
					dlg.m_strWorkStopMemo,  
					dlg.m_strContent,
					FALSE))
				{
					MessageBox("�ϰ��۾��߿� �����߻�", "Ȯ��", MB_ICONERROR);
					return;
				}
			}
		}
	}
	else {
		MessageBox("������ �����Ͻʽÿ�!", "Ȯ��", MB_ICONINFORMATION);
	}

	RefreshList();
}

void CStaffPage17::OnBnClickedIncreseColBtn()
{
	for(int c = 4; c < m_XTPList.GetColumns()->GetCount() -1; c++)
	{
		CXTPGridColumn *pColum = m_XTPList.GetColumns()->GetAt(c);
		pColum->SetWidth(pColum->GetWidth() + 6);
	}
}

void CStaffPage17::OnLvnDeleteallitemsListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	m_RiderInfo.clear();	
	*pResult = 0;
}

void CStaffPage17::OnNMClickListReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	//NMITEMACTIVATE * pNMIA = (NMITEMACTIVATE*) pNMHDR;
	XTP_NM_REPORTRECORDITEM *pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNMHDR;

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_XTPList.GetNextItem(-1, LVNI_SELECTED);
	int nColumn = pItemNotify->pColumn->GetIndex();

	if(pItemNotify == NULL)
		return;

	if(nColumn>1 || index == -1) //���� �۾� �̻�
		return;

	if(m_XTPList.GetItemText(index, 0) == "��")
		return;

	long nCompany = (long)m_XTPList.GetItemData(index);
	long nRNo = _ttoi(m_XTPList.GetItemText(index, 0));

	LU->ShowRiderInfoDlg(nCompany, nRNo);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}