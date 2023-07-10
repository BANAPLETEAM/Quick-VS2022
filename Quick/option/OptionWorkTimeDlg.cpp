// WorkTimeDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "resource.h"
#include "OptionWorkTimeDlg.h"


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.


// COptionWorkTimeDlg ��ȭ ����


COptionWorkTimeDlg::COptionWorkTimeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COptionWorkTimeDlg::IDD, pParent)	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCompany = 0;
	m_bInitData = FALSE;

	
	COleDateTime dt(COleDateTime::GetCurrentTime());
	for(int i = 0; i < MAX_SUB_COUNT; i++)
	{
		m_dtSubFrom[i].SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), 8, 0, 0);
		m_dtSubTo[i].SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), 19, 0, 0);
	}
	for(int i = 0; i < MAX_MAIN_COUNT; i++)
	{
		m_dtMainFrom[i].SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), 8, 0, 0);
		m_dtMainTo[i].SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), 19, 0, 0);
	}
	
}

COptionWorkTimeDlg::~COptionWorkTimeDlg()
{
}


void COptionWorkTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DAY9_CHECK , m_chkAll);
	DDX_Control(pDX, IDC_NOWORK_SAT_CHECK, m_chkNoWork6);
	DDX_Control(pDX, IDC_NOWORK_SUN_CHECK, m_chkNoWork7);

	for(int i = 0; i < MAX_MAIN_COUNT; i++ )
		DDX_Control(pDX, IDC_DAY6_CHECK + i, m_chkMain[i]);

	for(int i = 0; i < MAX_SUB_COUNT; i++ )
		DDX_Control(pDX, IDC_DAY1_CHECK + i, m_chkSub[i]);

	for(int i = 0; i < MAX_SUB_COUNT; i++ )
	{
		DDX_Control(pDX, IDC_DATETIME_FROM1 + i, m_dtpSubFrom[i]);
		DDX_DateTimeCtrl(pDX, IDC_DATETIME_FROM1 + i, m_dtSubFrom[i]);
	}

	for(int i = 0; i < MAX_SUB_COUNT; i++ )
	{
		DDX_Control(pDX, IDC_DATETIME_TO1 + i, m_dtpSubTo[i]);
		DDX_DateTimeCtrl(pDX, IDC_DATETIME_TO1 + i, m_dtSubTo[i]);
	}

	for(int i = 0; i < MAX_MAIN_COUNT; i++ )
	{
		DDX_Control(pDX, IDC_DATETIME_FROM6 + i, m_dtpMainFrom[i]);
		DDX_DateTimeCtrl(pDX, IDC_DATETIME_FROM6 + i, m_dtMainFrom[i]);
	}
	for(int i = 0; i < MAX_MAIN_COUNT; i++ )
	{
		DDX_Control(pDX, IDC_DATETIME_TO6 + i, m_dtpMainTo[i]);
		DDX_DateTimeCtrl(pDX, IDC_DATETIME_TO6 + i, m_dtMainTo[i]);
	}

	DDX_Control(pDX, IDC_CUSTOM1, m_ChargeList);
	DDX_Control(pDX, IDC_DAY_COMBO, m_cmbChargeDay);
	DDX_Control(pDX, IDC_NOWORK_INTERCALL_CHECK, m_chkInterCallWork);
	DDX_Control(pDX, IDC_DATAROW_STATIC, m_stcTimeChareDataRow);
	DDX_Control(pDX, IDC_DATA_TIME_ROW_STATIC, m_stcIntercallTimeDataRow);
	
	
}

BEGIN_MESSAGE_MAP(COptionWorkTimeDlg, CMyDialog)
	
	ON_WM_PAINT()
	
	//ON_BN_CLICKED(IDC_TEST_BTN, OnBnClickedTestBtn)
	ON_BN_CLICKED(IDC_BRANCH_ALL_BTN2, OnBnClickedBranchAllBtn2)
	ON_BN_CLICKED(IDC_DAY9_CHECK, OnBnClickedDay9Check)
	ON_BN_CLICKED(IDC_DAY8_CHECK, OnBnClickedDay8Check)
	ON_BN_CLICKED(IDC_BRANCH_ALL_BTN, OnBnClickedBranchAllBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_ALL_DEL_BTN, OnBnClickedAllDelBtn)
	ON_BN_CLICKED(IDC_ROW_DEL_BTN, OnBnClickedRowDelBtn)
	ON_CBN_SELCHANGE(IDC_DAY_COMBO, OnCbnSelchangeDayCombo)
	ON_BN_CLICKED(IDC_ROW_ADD_BTN, OnBnClickedRowAddBtn)
	ON_BN_CLICKED(IDC_BRANCH_BTN2, OnBnClickedBranchBtn2)
	ON_BN_CLICKED(IDC_BRANCH_BTN, OnBnClickedBranchBtn)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_DAY1_CHECK, IDC_DAY7_CHECK, OnCheckClickedItem)
	
	ON_BN_CLICKED(IDC_CANCEL_BTN3, &COptionWorkTimeDlg::OnBnClickedCancelBtn3)
	ON_STN_CLICKED(IDC_DATAROW_STATIC, &COptionWorkTimeDlg::OnStnClickedDatarowStatic)
END_MESSAGE_MAP()


// COptionWorkTimeDlg �޽��� ó����

BOOL COptionWorkTimeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	
	
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	
	InitControl();
	LoadData();
	LoadTime();
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}


// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void COptionWorkTimeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CMyDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR COptionWorkTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define  ALL_CHECK 9
#define  WEEK_CHECK 8

#define  SAT_CHECK 7
#define  FRI_CHECK 6
#define  THU_CHECK 5
#define  WED_CHECK 4
#define  TUE_CHECK 3
#define  MON_CHECK 2
#define  SUN_CHECK 1


void COptionWorkTimeDlg::LoadTime()
{
	UpdateData();
	long nIsRowData = 0; CString strSaveRowData = "";
	BOOL bInterCallWorkTimeCheck = FALSE;
	CMkRecordset pRs(m_pMkDb);	
	CMkCommand pCmd(m_pMkDb, "select_option_charge_time_list2");	  	
	pCmd.AddParameter(m_nCompany);
	CMkParameter *pPar = pCmd.AddParameter(typeLong,typeOutput, sizeof(long), 0);
	
	if(!pRs.Execute(&pCmd))  return;

	pPar->GetValue(nIsRowData);
	strSaveRowData.Format("%d��", nIsRowData);
	m_stcIntercallTimeDataRow.SetWindowText(strSaveRowData);

	if(pRs.GetRecordCount() > 0)
	{        	
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			//CString sFromTime, sToTime;
			COleDateTime dtFromTime(COleDateTime::GetCurrentTime()), dtToTime(COleDateTime::GetCurrentTime());
			long nDayType, nWorkStop;

			COleDateTime dtFromTemp(2000,1,1,0,0,0);
			COleDateTime dtToTemp(2000,1,1,0,0,0);
			COleDateTimeSpan dtFromSpan,dtToSpan;
			
			pRs.GetFieldValue("nDayType", nDayType);
			pRs.GetFieldValue("sFromTime", dtFromTime);
			pRs.GetFieldValue("sToTime", dtToTime);
			pRs.GetFieldValue("nWorkStop", nWorkStop);
			pRs.GetFieldValue("bInterCallWorkTimeCheck", bInterCallWorkTimeCheck);

			

			dtFromSpan.SetDateTimeSpan(0,dtFromTime.GetHour(), dtFromTime.GetMinute(),0);
			dtToSpan.SetDateTimeSpan(0, dtToTime.GetHour(), dtToTime.GetMinute(), 0);

			dtFromTemp +=dtFromSpan;
			dtToTemp += dtToSpan;
				

			if(nDayType == ALL_CHECK)
			{
				m_chkAll.SetCheck(TRUE);
				//OnBnClickedDay9Check();
				Day9Check();
				m_dtMainFrom[2].SetDateTime(
					dtFromTemp.GetYear(), dtFromTemp.GetMonth(), dtFromTemp.GetDay(),
					dtFromTemp.GetHour(), dtFromTemp.GetMinute(), dtFromTemp.GetSecond());

				m_dtMainTo[2].SetDateTime(
					dtToTemp.GetYear(), dtToTemp.GetMonth(), dtToTemp.GetDay(),
					dtToTemp.GetHour(), dtToTemp.GetMinute(), dtToTemp.GetSecond());
				
			}
			else
			{
				m_chkAll.SetCheck(FALSE);
				//OnBnClickedDay9Check();
				if(i == 0)
					Day9Check();

				if (nDayType ==WEEK_CHECK )
				{					
					m_chkMain[2].SetCheck(TRUE);
					OnBnClickedDay8Check();
					m_dtMainFrom[2].SetDateTime(
						dtFromTemp.GetYear(), dtFromTemp.GetMonth(), dtFromTemp.GetDay(),
						dtFromTemp.GetHour(), dtFromTemp.GetMinute(), dtFromTemp.GetSecond());
					m_dtMainTo[2].SetDateTime(
						dtToTemp.GetYear(), dtToTemp.GetMonth(), dtToTemp.GetDay(),
						dtToTemp.GetHour(), dtToTemp.GetMinute(), dtToTemp.GetSecond());
					
					
				}		
				else
				{
					
					if(nDayType == SAT_CHECK)
					{
						m_dtMainFrom[0].SetDateTime(
							dtFromTemp.GetYear(), dtFromTemp.GetMonth(), dtFromTemp.GetDay(),
							dtFromTemp.GetHour(), dtFromTemp.GetMinute(), dtFromTemp.GetSecond());
						m_dtMainTo[0].SetDateTime(
							dtToTemp.GetYear(), dtToTemp.GetMonth(), dtToTemp.GetDay(),
							dtToTemp.GetHour(), dtToTemp.GetMinute(), dtToTemp.GetSecond());

						m_chkNoWork6.SetCheck(nWorkStop);
					}
					else if(nDayType == SUN_CHECK)
					{
						m_dtMainFrom[1].SetDateTime(
							dtFromTemp.GetYear(), dtFromTemp.GetMonth(), dtFromTemp.GetDay(),
							dtFromTemp.GetHour(), dtFromTemp.GetMinute(), dtFromTemp.GetSecond());
						m_dtMainTo[1].SetDateTime(
							dtToTemp.GetYear(), dtToTemp.GetMonth(), dtToTemp.GetDay(),
							dtToTemp.GetHour(), dtToTemp.GetMinute(), dtToTemp.GetSecond());

						m_chkNoWork7.SetCheck(nWorkStop);
					}		
					else
					{
						
						m_chkMain[EVERY_DAY_CHECK].SetCheck(FALSE);
						((CButton*)GetDlgItem(IDC_DAY8_CHECK))->SetCheck(FALSE);
						m_dtpMainFrom[EVERY_DAY_CHECK].EnableWindow(TRUE);
						m_dtpMainTo[EVERY_DAY_CHECK].EnableWindow(TRUE);

						OnBnClickedDay8Check();	
						m_dtSubFrom[nDayType -2].SetDateTime(
							dtFromTemp.GetYear(), dtFromTemp.GetMonth(), dtFromTemp.GetDay(),
							dtFromTemp.GetHour(), dtFromTemp.GetMinute(), dtFromTemp.GetSecond());

						m_dtSubTo[nDayType -2].SetDateTime(
							dtToTemp.GetYear(), dtToTemp.GetMonth(), dtToTemp.GetDay(),
							dtToTemp.GetHour(), dtToTemp.GetMinute(), dtToTemp.GetSecond());
					}
				}
			
				
			
				
			}
			pRs.MoveNext();
		}
	}
	m_chkInterCallWork.SetCheck(bInterCallWorkTimeCheck);
	pRs.Close();		
	UpdateData(FALSE);

}
void COptionWorkTimeDlg::LoadData()
{

	m_ChargeList.DeleteAllItems();

	CString strTimeChargeCount = ""; long nTimeChargeCount = 0;
	CMkRecordset pRs(m_pMkDb);	
	CMkCommand pCmd(m_pMkDb, "select_option_charge_day_list2");	  	
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_cmbChargeDay.GetCurSel());
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	if(!pRs.Execute(&pCmd))  return;

	pPar->GetValue(nTimeChargeCount);
	strTimeChargeCount.Format("%d��", nTimeChargeCount);
	m_stcTimeChareDataRow.SetWindowText(strTimeChargeCount);

	
	if(pRs.GetRecordCount() > 0)
	{        	
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			COleDateTime dtFromTime, dtToTime;
			long nMotoCharge, nDamaCharge, nBonggoCharge, nTruckCharge, nLaboCharge;
			

			pRs.GetFieldValue("sFromTime", dtFromTime);
			pRs.GetFieldValue("sToTime", dtToTime);
			pRs.GetFieldValue("nMotoCharge", nMotoCharge);
			pRs.GetFieldValue("nDamaCharge", nDamaCharge);
			pRs.GetFieldValue("nLaboCharge", nLaboCharge);
			pRs.GetFieldValue("nBonggoCharge", nBonggoCharge);
			pRs.GetFieldValue("nTruckCharge", nTruckCharge);

			CXTPGridRecord* record = new CXTPGridRecord;
			record->AddItem(new CXTPGridRecordItemText(dtFromTime.Format("%H:%M")));
			record->AddItem(new CXTPGridRecordItemText(dtToTime.Format("%H:%M")));
			record->AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nMotoCharge)));
			record->AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nDamaCharge)));
			record->AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nLaboCharge)));
			record->AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nBonggoCharge)));
			record->AddItem(new CXTPGridRecordItemText(LF->GetMyNumberFormat(nTruckCharge)));
			m_ChargeList.AddRecord(record);

			pRs.MoveNext();
		}

		

	}
	pRs.Close();
	m_ChargeList.Populate();
}
void COptionWorkTimeDlg::InitControl()
{
	m_cmbChargeDay.SetCurSel(0);

	CXTPGridColumn* pCol0 = m_ChargeList.AddColumn(new CXTPGridColumn(0, "���۽ð�", 80, FALSE));
	CXTPGridColumn* pCol1 = m_ChargeList.AddColumn(new CXTPGridColumn(1, "�Ϸ�ð�", 80, FALSE));
	CXTPGridColumn* pCol2 = m_ChargeList.AddColumn(new CXTPGridColumn(2, "����", 60, FALSE));
	CXTPGridColumn* pCol3 = m_ChargeList.AddColumn(new CXTPGridColumn(3, "�ٸ�", 60, FALSE));
	CXTPGridColumn* pCol4 = m_ChargeList.AddColumn(new CXTPGridColumn(4, "��", 60, FALSE));
	CXTPGridColumn* pCol5 = m_ChargeList.AddColumn(new CXTPGridColumn(5, "����", 60, FALSE));
	CXTPGridColumn* pCol6 = m_ChargeList.AddColumn(new CXTPGridColumn(6, "Ʈ��", 60, FALSE));

	pCol0->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol1->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol2->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol3->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol4->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol5->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol6->GetEditOptions()->m_bAllowEdit = TRUE;

	pCol0->SetAlignment(DT_CENTER);
	pCol1->SetAlignment(DT_CENTER);
	pCol2->SetAlignment(DT_RIGHT);
	pCol3->SetAlignment(DT_RIGHT);
	pCol4->SetAlignment(DT_RIGHT);
	pCol5->SetAlignment(DT_RIGHT);
	pCol6->SetAlignment(DT_RIGHT);

	m_ChargeList.AllowEdit(TRUE);
	m_ChargeList.GetReportHeader()->AllowColumnRemove(FALSE);
	m_ChargeList.GetReportHeader()->AllowColumnSort(FALSE);
	m_ChargeList.GetReportHeader()->AllowColumnReorder(FALSE);
	m_ChargeList.Populate();

	m_ChargeList.EnableDragDrop("COptionWorkTimeDlg", xtpReportAllowDrag | xtpReportAllowDrop);

	for(int i = 0; i < MAX_MAIN_COUNT; i++)
	{
		m_dtpMainFrom[i].SetFormat("HH:mm");
		m_dtpMainTo[i].SetFormat("HH:mm");
	}

	for(int i = 0; i < MAX_SUB_COUNT; i++)
	{
		m_dtpSubFrom[i].SetFormat("HH:mm");
		m_dtpSubTo[i].SetFormat("HH:mm");
	}

	m_chkAll.SetCheck(TRUE);

	// 
	
	


}
void COptionWorkTimeDlg::OnBnClickedBranchAllBtn2()
{
	SaveCharge(TRUE);
}

void COptionWorkTimeDlg::Day9Check(int nWeekDayException)
{
	for(int i = 0; i < MAX_MAIN_COUNT; i++)
	{
		m_chkMain[i].EnableWindow(!m_chkAll.GetCheck());
		if(nWeekDayException && i ==  2)
		{
			//m_chkMain[i].SetCheck(!m_chkAll.GetCheck());
		}
		else
		{
			m_chkMain[i].SetCheck(!m_chkAll.GetCheck());
		}


		m_dtpMainFrom[i].EnableWindow(!m_chkAll.GetCheck());
		m_dtpMainTo[i].EnableWindow(!m_chkAll.GetCheck());		

	}
	m_dtpMainFrom[2].EnableWindow(TRUE);
	m_dtpMainTo[2].EnableWindow(TRUE);		



	if(m_chkAll.GetCheck())
	{
		m_chkNoWork6.SetCheck(!m_chkAll.GetCheck());
		m_chkNoWork7.SetCheck(!m_chkAll.GetCheck());

		for(int j = 0; j < MAX_SUB_COUNT; j++)
		{
			m_chkSub[j].SetCheck(!m_chkAll.GetCheck());
			m_chkSub[j].EnableWindow(!m_chkAll.GetCheck());
			m_dtpSubFrom[j].EnableWindow(!m_chkAll.GetCheck());
			m_dtpSubTo[j].EnableWindow(!m_chkAll.GetCheck());
		}

	}


	m_chkNoWork6.EnableWindow(!m_chkAll.GetCheck());
	m_chkNoWork7.EnableWindow(!m_chkAll.GetCheck());
}

void COptionWorkTimeDlg::OnBnClickedDay9Check()
{	
	Day9Check();
	
	
}

void COptionWorkTimeDlg::OnBnClickedDay8Check()
{

	
	if(!m_chkAll.GetCheck())
	{
		for(int i = 0; i < MAX_SUB_COUNT; i++)
		{
			
			m_chkSub[i].SetCheck(!m_chkMain[EVERY_DAY_CHECK].GetCheck());
			m_chkSub[i].EnableWindow(!m_chkMain[EVERY_DAY_CHECK].GetCheck());
			m_dtpSubFrom[i].EnableWindow(!m_chkMain[EVERY_DAY_CHECK].GetCheck());
			m_dtpSubTo[i].EnableWindow(!m_chkMain[EVERY_DAY_CHECK].GetCheck());
		}
	
		m_dtpMainFrom[EVERY_DAY_CHECK].EnableWindow(m_chkMain[EVERY_DAY_CHECK].GetCheck());
		m_dtpMainTo[EVERY_DAY_CHECK].EnableWindow(m_chkMain[EVERY_DAY_CHECK].GetCheck());
	
		
		
	}
	


}



void COptionWorkTimeDlg::OnBnClickedBranchAllBtn()
{
	SetWorkTime(TRUE);
	

}

void COptionWorkTimeDlg::OnBnClickedCancelBtn()
{
	OnOK();
}

void COptionWorkTimeDlg::OnBnClickedAllDelBtn()
{
	m_ChargeList.DeleteAllItems();
	m_ChargeList.Populate();
}

void COptionWorkTimeDlg::OnBnClickedRowDelBtn()
{
	for(int i =0; i < m_ChargeList.GetSelectedRows()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_ChargeList.GetSelectedRows()->GetAt(i)->GetRecord();
		pRecord->Delete();

	}
	m_ChargeList.Populate();
}

void COptionWorkTimeDlg::OnCbnSelchangeDayCombo()
{
	LoadData();
}

void COptionWorkTimeDlg::OnBnClickedRowAddBtn()
{
	CXTPGridRecord* record = new CXTPGridRecord;
	record->AddItem(new CXTPGridRecordItemText(""));
	record->AddItem(new CXTPGridRecordItemText(""));
	record->AddItem(new CXTPGridRecordItemText(""));
	record->AddItem(new CXTPGridRecordItemText(""));
	record->AddItem(new CXTPGridRecordItemText(""));
	record->AddItem(new CXTPGridRecordItemText(""));
	record->AddItem(new CXTPGridRecordItemText(""));
	m_ChargeList.AddRecord(record);

	m_ChargeList.Populate();
}

void COptionWorkTimeDlg::OnBnClickedBranchBtn2()
{
	SaveCharge();
	LoadData();
}

void COptionWorkTimeDlg::SaveCharge(BOOL bAllBranch)
{
	
	if(m_cmbChargeDay.GetCurSel() == 0)
	{
		if(MessageBox("��ü�� �����Ͻø� �� ~ ��(������)���� ���»����˴ϴ�\n\r�����ϰ� �Է��Ͻðڽ��ϱ�? ",
			"Ȯ��" , MB_ICONINFORMATION | MB_YESNO) == IDNO)
		{
			return;
		}
	}
	if(m_cmbChargeDay.GetCurSel() == 1)
	{
		if(MessageBox("������ �����Ͻø� (��~�ݿ���) �������� �����Ͱ� �����˴ϴ�\n\r�����ϰ� �Է��Ͻðڽ��ϱ�?",
			"Ȯ��" , MB_ICONINFORMATION | MB_YESNO) == IDNO)
		{
			return;
		}
	}
	if(m_cmbChargeDay.GetCurSel() > 1 && m_cmbChargeDay.GetCurSel() < 7)
	{
		if(MessageBox("��~�ݿ����� ���������� �����Ͻø� ��ü�� ������ ������ �����˴ϴ�\n\r�����ϰ� �Է��Ͻðڽ��ϱ�?",
			"Ȯ��" , MB_ICONINFORMATION | MB_YESNO) == IDNO)
		{
			return;
		}
	}


	if(!CheckCharge() ) return;


	CString sStartTime, sDestTime, sMoto, sDama, sLabo, sBonggo, sTruck;
	CString sMotoTemp, sDamaTemp, sLaboTemp, sBonggoTemp, sTruckTemp;
	for (int i = 0; i < m_ChargeList.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord* pRecord = m_ChargeList.GetRecords()->GetAt(i);
		sStartTime += pRecord->GetItem(0)->GetCaption() + ",";
		sDestTime += pRecord->GetItem(1)->GetCaption() + ",";

		sMotoTemp = pRecord->GetItem(2)->GetCaption(); sMotoTemp.Replace(",", "");
		sDamaTemp = pRecord->GetItem(3)->GetCaption(); sDamaTemp.Replace(",", "");
		sLaboTemp = pRecord->GetItem(4)->GetCaption(); sLaboTemp.Replace(",", "");
		sBonggoTemp = pRecord->GetItem(5)->GetCaption(); sBonggoTemp.Replace(",", "");
		sTruckTemp = pRecord->GetItem(6)->GetCaption(); sTruckTemp.Replace(",", "");

		if (sMotoTemp.GetLength() <= 0) sMotoTemp = "0";
		if (sDamaTemp.GetLength() <= 0) sDamaTemp = "0";
		if (sLaboTemp.GetLength() <= 0) sLaboTemp = "0";
		if (sBonggoTemp.GetLength() <= 0) sBonggoTemp = "0";
		if (sTruckTemp.GetLength() <= 0) sTruckTemp = "0";

		sMoto += sMotoTemp + ",";
		sDama += sDamaTemp + ",";
		sLabo += sLaboTemp + ",";
		sBonggo += sBonggoTemp + ",";
		sTruck += sTruckTemp + ",";
	}


	int nDelRowCount = -1;
	nDelRowCount = m_ChargeList.GetRecords()->GetCount();

	CMkRecordset pRs(m_pMkDb);	
	CMkCommand pCmd(m_pMkDb, "select_option_charge_day_insert3");	  	
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(bAllBranch);	
	pCmd.AddParameter(TRUE);
	pCmd.AddParameter(m_cmbChargeDay.GetCurSel());		
	pCmd.AddParameter(nDelRowCount);
	pCmd.AddParameter(sStartTime);
	pCmd.AddParameter(sDestTime);
	pCmd.AddParameter(sMoto);
	pCmd.AddParameter(sDama);
	pCmd.AddParameter(sLabo);
	pCmd.AddParameter(sBonggo);
	pCmd.AddParameter(sTruck);

	if(!pRs.Execute(&pCmd))  return;

	MessageBox("�ԷµǾ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);


}
BOOL COptionWorkTimeDlg::CheckCharge()
{
	try
	{
		if(m_ChargeList.GetRecords()->GetCount() <= 0)
		{
			if(MessageBox("�ش� �����͸� ����ðڽ��ϱ�?" , "Ȯ��", MB_YESNO) ==IDNO)
				return FALSE;
		}

		CString sMsg = "";
		for(int i = 0; i < m_ChargeList.GetRecords()->GetCount(); i++)
		{
			CXTPGridRecord *pRecord = (CXTPGridRecord *)m_ChargeList.GetRecords()->GetAt(i);
			
			int nMoto = 0, nDama = 0, nBonggo = 0, nTruck = 0;
			CString sMoto = "", sDama = "", sBonggo = "", sTruck = "";
			sMoto = pRecord->GetItem(2)->GetCaption();		sMoto.Replace(",", ""); nMoto = atol(sMoto);
			sDama = pRecord->GetItem(3)->GetCaption();		sDama.Replace(",", ""); nDama = atol(sDama);
			sBonggo = pRecord->GetItem(4)->GetCaption();	sBonggo.Replace(",", ""); nBonggo = atol(sBonggo);
			sTruck = pRecord->GetItem(5)->GetCaption();		sTruck.Replace(",", ""); nTruck = atol(sTruck);

			if ((nMoto + nDama + nBonggo + nTruck) == 0)
			{
				sMsg.Format("���۽ð� %s �п� �ݾ��� 0�Դϴ�.", pRecord->GetItem(0)->GetCaption());
				throw sMsg;
			}

			if ((nMoto + nDama + nBonggo + nTruck) >= 4000000)
			{
				sMsg.Format("���۽ð� %s �п� �ݾ��� ���ļ� ��鸸���̻� �Դϴ�..", pRecord->GetItem(0)->GetCaption());
				throw sMsg;
			}
			if (nMoto > 1000000 || nDama > 1000000 || nBonggo > 1000000 || nTruck > 1000000)
			{
				sMsg.Format("���۽ð� %s �п� �ݾ��� �鸸���� �ʰ��� �� �����ϴ�.", pRecord->GetItem(0)->GetCaption());
				throw sMsg;
			}
		}
		//  �ð�üũ
		COleDateTime dtOldSTemp(2000, 1,1,1,1,1), dtOldDTemp(2000, 1,1, 1,1,1);
		for(int i = 0; i < m_ChargeList.GetRecords()->GetCount(); i++)
		{
			CXTPGridRecord* pRecord = m_ChargeList.GetRecords()->GetAt(i);
			if (
				(pRecord->GetItem(0)->GetCaption().GetLength() <= 0 || pRecord->GetItem(0)->GetCaption().GetLength() <= 0)
				||
				(pRecord->GetItem(1)->GetCaption().GetLength() > 5 || pRecord->GetItem(1)->GetCaption().GetLength() > 5)
				)
			{
				sMsg.Format("%d�࿡ �ð��� ���̰� 0 �����̰ų� 5 �ڸ��� �ѽ��ϴ�.", i + 1);
				throw sMsg;

			}
			if (pRecord->GetItem(0)->GetCaption().Mid(2, 1).Find(":") != 0 || pRecord->GetItem(1)->GetCaption().Mid(2, 1).Find(":") != 0)
			{
				sMsg.Format("%d�࿡ �ð� ������ �ƴϰų� : ǥ�ð� �����ϴ�.", i + 1);
				throw sMsg;
			}

			long  nMinite = 0, nHour = 0;

			nHour = atol(pRecord->GetItem(0)->GetCaption().Left(2));
			nMinite = atol(pRecord->GetItem(0)->GetCaption().Right(2));
			COleDateTime dt(COleDateTime::GetCurrentTime()), dtSTemp, dtDTemp;

			if (nHour <= 9 && i > 0)  // ����ó��  // ù���� 00:00 ~ 23:59
				dtSTemp.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay() + 1, nHour, nMinite, 0);
			else
				dtSTemp.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), nHour, nMinite, 0);


			if (dtSTemp.GetStatus() != COleDateTime::valid)
			{
				sMsg.Format("%d�࿡  ���� �ð��� �ùٸ��� �ʽ��ϴ�.", i + 1);
				throw(sMsg);
			}
			nHour = atol(pRecord->GetItem(1)->GetCaption().Left(2));
			nMinite = atol(pRecord->GetItem(1)->GetCaption().Right(2));
			if (nHour <= 9) // ����  6����������
				dtDTemp.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay() + 1, nHour, nMinite, 0);
			else
				dtDTemp.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(), nHour, nMinite, 0);

			if (dtDTemp.GetStatus() != COleDateTime::valid)
			{
				sMsg.Format("%d�࿡ �� �ð��� �ùٸ��� �ʽ��ϴ�.", i + 1);
				throw(sMsg);
			}

			if (dtSTemp > dtDTemp)
			{
				sMsg.Format("%d �࿡ ���۽ð��� ������ �ð��� �۰ų� �����ϴ�.", i + 1);
				throw sMsg;
			}


			if (dtOldDTemp >= dtSTemp || dtOldDTemp >= dtDTemp)
			{
				sMsg.Format("%d �࿡ ���� �ຸ�� �ð��� �����Դϴ�.", i + 1);
				throw sMsg;
			}
			dtOldSTemp.SetDateTime(dtSTemp.GetYear(), dtSTemp.GetMonth(),
				dtSTemp.GetDay(), dtSTemp.GetHour(), dtSTemp.GetMinute(), dtSTemp.GetSecond());
			dtOldDTemp.SetDateTime(dtDTemp.GetYear(), dtDTemp.GetMonth(),
				dtDTemp.GetDay(), dtDTemp.GetHour(), dtDTemp.GetMinute(), dtDTemp.GetSecond());
		}
		return TRUE;
	}
	
	catch (char* e)
	{
		MessageBox(e, "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}
	catch (CString s)
	{
		MessageBox(s, "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}
	return FALSE;



}
void COptionWorkTimeDlg::OnBnClickedBranchBtn()
{
	SetWorkTime();	
	LoadTime();
}

void COptionWorkTimeDlg::SetWorkTime(BOOL bAllBranch)
{

	CString sMainFrom[MAX_MAIN_COUNT], sMainTo[MAX_MAIN_COUNT];
	CString sSubFrom[MAX_SUB_COUNT], sSubTo[MAX_SUB_COUNT];

	for(int i = 0; i <MAX_MAIN_COUNT; i++ )
	{
		m_dtpMainFrom[i].GetWindowText(sMainFrom[i]);
		m_dtpMainTo[i].GetWindowText(sMainTo[i]);
	}

	for(int i = 0; i <MAX_SUB_COUNT; i++ )
	{
		m_dtpSubFrom[i].GetWindowText(sSubFrom[i]);
		m_dtpSubTo[i].GetWindowText(sSubTo[i]);

	}
	CMkRecordset pRs(m_pMkDb);	
	CMkCommand pCmd(m_pMkDb, "select_option_charge_work_insert");	  	
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(bAllBranch);	
	pCmd.AddParameter(FALSE);
	pCmd.AddParameter(m_chkAll.GetCheck());	
	for(int i = 0; i < MAX_MAIN_COUNT; i++)
	{
		pCmd.AddParameter(m_chkMain[i].GetCheck());
		pCmd.AddParameter(sMainFrom[i]);
		pCmd.AddParameter(sMainTo[i]);
	}
	for(int i = 0; i < MAX_SUB_COUNT; i++)
	{
		pCmd.AddParameter(m_chkSub[i].GetCheck());
		pCmd.AddParameter(sSubFrom[i]);
		pCmd.AddParameter(sSubTo[i]);
	}
	pCmd.AddParameter(m_chkNoWork6.GetCheck());
	pCmd.AddParameter(m_chkNoWork7.GetCheck());
	pCmd.AddParameter(m_chkInterCallWork.GetCheck());


	if(!pRs.Execute(&pCmd))  return;

	MessageBox("�ԷµǾ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
}



void COptionWorkTimeDlg::OnCheckClickedItem(UINT nItem)
{
	MessageBox("���Ϲ� ��ü�� üũ�ϼ���","Ȯ��", MB_ICONINFORMATION);

	((CButton*)GetDlgItem(nItem))->SetCheck(TRUE);

}
void COptionWorkTimeDlg::OnBnClickedCancelBtn3()
{
	OnOK();
}

void COptionWorkTimeDlg::OnStnClickedDatarowStatic()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
