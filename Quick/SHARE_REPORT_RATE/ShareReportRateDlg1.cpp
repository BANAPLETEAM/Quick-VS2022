// ShareReportRateDlg1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareReportRateDlg1.h"
#include "ShareReportRateLogDlg.h"
#include "RcpView.h"
#include "MyAllianceManagerDlg.h"
#include "RequestDrawingDlg.h"

#define SR_SHARETIMEA_COL	7
#define SR_SHARETIMEB_COL	8
#define SR_HISTORY_COL	10
#define SR_TRANSFER_COL	11
#define SR_REQUEST_COL	12
#define SR_INTRO_COL	13	


// CShareReportRateDlg1

IMPLEMENT_DYNCREATE(CShareReportRateDlg1, CMyFormView)

CShareReportRateDlg1::CShareReportRateDlg1()
	: CMyFormView(CShareReportRateDlg1::IDD)
{
	m_bHasAlliancePower = FALSE;
}

CShareReportRateDlg1::~CShareReportRateDlg1()
{
}

void CShareReportRateDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_SearchEdit);
}

BEGIN_MESSAGE_MAP(CShareReportRateDlg1, CMyFormView)
	ON_BN_CLICKED(IDC_EDIT_BTN, OnBnClickedEditBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_MOUSEACTIVATE()
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	ON_WM_ACTIVATE()
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
	ON_BN_CLICKED(IDC_REQUEST_BTN, OnBnClickedRequestBtn)
	ON_BN_CLICKED(IDC_MY_REQUEST_BTN, OnBnClickedMyRequestBtn)
	ON_BN_CLICKED(IDC_SHARE_TIME_EDIT, OnBnClickedShareTimeEdit)
	
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDC_MY_ALLIANCE_MANAGER_BTN, OnBnClickedMyAllianceManagerBtn)
	ON_BN_CLICKED(IDC_CORP_BTN, OnBnClickedCorpBtn)
	ON_BN_CLICKED(IDC_REQUEST_DRAWING_BTN, &CShareReportRateDlg1::OnBnClickedRequestDrawingBtn)
END_MESSAGE_MAP()


// CShareReportRateDlg1 �����Դϴ�.

#ifdef _DEBUG
void CShareReportRateDlg1::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CShareReportRateDlg1::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CShareReportRateDlg1 �޽��� ó�����Դϴ�.

UINT RequestBoxOpenThread(LPVOID arg)
{
	CShareReportRateDlg1 *ptr = (CShareReportRateDlg1 *) arg;
    ptr->OpenRequestBox();

//	ptr->SetTimer(100, 1000, NULL);

	return 0;
}

void CShareReportRateDlg1::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_wndReport.GetImageManager()->SetIcons(IDB_BMREPORT, 0, 0, CSize(16, 16));
	CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("ȸ���"), 110, FALSE));
	pCol0->SetTreeColumn(TRUE);

	CXTPGridColumn* pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, _T("��ǥ��ȣ"), 80, FALSE));
	CXTPGridColumn* pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, _T("��Ȳ����"), 80, FALSE));
	CXTPGridColumn* pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, _T("����ä��"), 60, FALSE));
	CXTPGridColumn* pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, _T("�ݺ�"), 40, FALSE));
	//CXTPGridColumn* pCol5 = m_wndReport.AddColumn(new CXTPGridColumn(5, _T("ó����"), 50, FALSE));
	CXTPGridColumn* pCol6 = m_wndReport.AddColumn(new CXTPGridColumn(5, _T("Ÿ���Է�"), 60, FALSE));

	CXTPGridColumn* pCol7 = m_wndReport.AddColumn(new CXTPGridColumn(6, _T("�����ð�"), 55, FALSE));
	CXTPGridColumn* pCol8 = m_wndReport.AddColumn(new CXTPGridColumn(7, _T("Ÿ���Է�"), 55, FALSE));

	CXTPGridColumn* pCol9 = m_wndReport.AddColumn(new CXTPGridColumn(8, _T("�����Է�"), 70, FALSE));
	CXTPGridColumn* pCol10 = m_wndReport.AddColumn(new CXTPGridColumn(9, _T("��������"), 70, FALSE));
	CXTPGridColumn* pCol11 = m_wndReport.AddColumn(new CXTPGridColumn(10, _T("����"), 35, FALSE));
	CXTPGridColumn* pCol12 = m_wndReport.AddColumn(new CXTPGridColumn(11, _T("��ü"), 35, FALSE));
	CXTPGridColumn* pCol13 = m_wndReport.AddColumn(new CXTPGridColumn(12, _T("û��"), 35, FALSE));
	//CXTPGridColumn* pCol14 = m_wndReport.AddColumn(new CXTPGridColumn(14, _T("�Ұ�"), 35, FALSE));

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->GetEditOptions()->m_bAllowEdit = TRUE;
//	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol6->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol7->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol8->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol8->GetEditOptions()->m_bAllowEdit = FALSE;

	pCol9->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol10->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol11->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol12->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol13->GetEditOptions()->m_bAllowEdit = FALSE;
	//pCol14->GetEditOptions()->m_bAllowEdit = FALSE;

	//pCol5->SetVisible(FALSE);
	//pCol6->SetVisible(FALSE);
	pCol11->SetVisible(FALSE);

	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_wndReport.SetTreeIndent(10);
	m_wndReport.GetPaintManager()->m_strNoItems = "���� ��ü����Ʈ Ȯ���� �Ұ����մϴ�.";

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(TRUE);
	m_wndReport.FocusSubItems(TRUE);
	m_wndReport.Populate();
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	//m_wndReport.SetFocus();

	m_tooltip.Create(this, FALSE);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
	m_tooltip.SetNotify();
	m_tooltip.SetImageList(IDB_LIST, 16, 18, 14, RGB(0,255,255));
	m_tooltip.SetTransparency(30);

	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);

	m_tooltip.AddTool(&m_wndReport, "");

	//AfxBeginThread(RequestBoxOpenThread, this);

	//static bool IsCheck = true;

	//if(IsCheck == true)
	//	SetTimer(100, 1000, NULL);

	//IsCheck = false;

}

void CShareReportRateDlg1::RefreshList()
{
	BOOL bShowData = FALSE;

	if(m_ui.strLogiStaffName.IsEmpty() == FALSE)
		bShowData = TRUE;
	else
		bShowData = FALSE;

	if(LF->IsThisCompany("���ֿ���"))
		bShowData = TRUE;

	CShareReportRateDlg* pShareReportRateDlg = (CShareReportRateDlg*)(GetParent()->GetParent());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_call_share_rate_a4", TRUE);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(bShowData);
	CMkParameter *parBalance = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parBasicRate = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parAccount = pCmd.AddParameter(typeString, typeOutput, 50, CString(""));
	CMkParameter* parAccountOwner = pCmd.AddParameter(typeString, typeOutput, 50, CString(""));
	CMkParameter *parYesterday = pCmd.AddParameter(typeLong, typeOutput, 50, CString(""));
	CMkParameter *parGlobalSharTime = pCmd.AddParameter(typeLong, typeOutput, 0, CString(""));
	CMkParameter *parHasAlliancePower = pCmd.AddParameter(typeBool, typeOutput, sizeof(int), 0);

	long nBalance, nBasicRate;
	CString strAccount;

	m_wndReport.GetRecords()->RemoveAll();

	if(pRs.Execute(&pCmd))
	{
		long nShareCode1, nShareCode1A, nShareCode1B;
		CString strName, strPhone, strOfficePhone;
		BOOL bShareLevel2, bShareLevel3, bShareLevel4, bShareLevel5;
		BOOL bShareLevel6, bShareLevel7, bShareLevel8, bShareLevel9, bShareLevel10;
		long nRcpRateA, nRcpRateB, nYesterday, nGlobalShareTime;
		long nShareTimeA, nShareTimeB;
		COleDateTime dtInsert, dtLastEdit;
		long nCompany, nAllianceID;
		CString strAllianceName, strAllianceSymbol, strAccountOwner;
		BOOL bNoShareA, bNoShareB;
		BOOL bAlliancePower;

		parBalance->GetValue(nBalance);
		parBasicRate->GetValue(nBasicRate);
		parAccount->GetValue(strAccount);
		parAccountOwner->GetValue(strAccountOwner);
		parYesterday->GetValue(nYesterday);
		parGlobalSharTime->GetValue(nGlobalShareTime);
		parHasAlliancePower->GetValue(bAlliancePower);

		m_bHasAlliancePower = bAlliancePower;
		if(m_bHasAlliancePower)
			GetDlgItem(IDC_MY_ALLIANCE_MANAGER_BTN)->ShowWindow(SW_SHOW);

		pShareReportRateDlg->m_nBalance = nBalance;
		pShareReportRateDlg->m_nBasicRate = nBasicRate;

		pShareReportRateDlg->m_BalanceEdit.SetWindowText(LF->GetMyNumberFormat(nBalance) + "��");
		pShareReportRateDlg->m_BasicRateEdit.SetWindowText(LF->GetMyNumberFormat(nBasicRate) + "��");
		pShareReportRateDlg->m_AccountEdit.SetWindowText(strAccount);
		pShareReportRateDlg->m_AccountEdit2.SetWindowText(strAccountOwner);
		pShareReportRateDlg->m_YesterdayEdit.SetWindowText(LF->GetMyNumberFormat(nYesterday) + "��");

		CString strFormat;
		BOOL bIntro;
		strFormat.Format("%d", nGlobalShareTime);
		pShareReportRateDlg->m_GlobalShareTimeEdt.SetWindowText(strFormat);

		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("nShareCode1", nShareCode1);
			pRs.GetFieldValue("nShareCode1A", nShareCode1A);
			pRs.GetFieldValue("nShareCode1B", nShareCode1B);
			pRs.GetFieldValue("sName", strName);
			pRs.GetFieldValue("sTel", strPhone);
			pRs.GetFieldValue("sOfficePhone", strOfficePhone);
			pRs.GetFieldValue("bShareLevel2", bShareLevel2);
			pRs.GetFieldValue("bShareLevel3", bShareLevel3);
			pRs.GetFieldValue("bShareLevel4", bShareLevel4);
			pRs.GetFieldValue("bShareLevel5", bShareLevel5);
			pRs.GetFieldValue("bShareLevel6", bShareLevel6);
			pRs.GetFieldValue("bShareLevel7", bShareLevel7);
			pRs.GetFieldValue("bShareLevel8", bShareLevel8);
			pRs.GetFieldValue("bShareLevel9", bShareLevel9);
			pRs.GetFieldValue("bShareLevel10", bShareLevel10);
			pRs.GetFieldValue("nRcpRateA", nRcpRateA);
			pRs.GetFieldValue("nRcpRateB", nRcpRateB);
			pRs.GetFieldValue("dtInsert", dtInsert);
			pRs.GetFieldValue("dtLastEdit", dtLastEdit);
			pRs.GetFieldValue("nID", nCompany);
			pRs.GetFieldValue("nShareTimeA", nShareTimeA);
			pRs.GetFieldValue("nShareTimeB", nShareTimeB);
			pRs.GetFieldValue("bIntro", bIntro);
			pRs.GetFieldValue("nAllianceID", nAllianceID);
			pRs.GetFieldValue("sAllianceName", strAllianceName);
			pRs.GetFieldValue("sAllianceSymbol", strAllianceSymbol);
			pRs.GetFieldValue("bNoShareA", bNoShareA);
			pRs.GetFieldValue("bNoShareB", bNoShareB);

			if(bNoShareA) bNoShareA = TRUE;
			if(bNoShareB) bNoShareB = TRUE;

			if((nShareCode1A == nShareCode1 && nShareCode1A < nShareCode1B) ||
				(nShareCode1B == nShareCode1 && nShareCode1A > nShareCode1B))
			{
				long nTemp;
				nTemp = nRcpRateA;
				nRcpRateA = nRcpRateB;
				nRcpRateB = nTemp;

				nTemp = nShareTimeA;
				nShareTimeA = nShareTimeB;
				nShareTimeB = nTemp;

				BOOL bTemp;
				bTemp = bNoShareA;
				bNoShareA = bNoShareB;
				bNoShareB = bTemp;
			}

			CString strChannel, strEditHistory;
			strChannel = (bShareLevel2 ? "��" : "");
			strChannel += (bShareLevel3 ? "��" : "");
			strChannel += (bShareLevel4 ? "��" : "");
			strChannel += (bShareLevel5 ? "��" : "");
			strChannel += (bShareLevel6 ? "��" : "");
			strChannel += (bShareLevel7 ? "��" : "");
			strChannel += (bShareLevel8 ? "��" : "");
			strChannel += (bShareLevel9 ? "��" : "");
			strChannel += (bShareLevel10 ? "��" : "");

			strEditHistory = nShareCode1A > 0 ? "����" : "";

			InsertCompany(new CMyRecord(nShareCode1, strName, strPhone, strOfficePhone, strChannel, 
				nRcpRateA, nRcpRateB, nShareTimeA, nShareTimeB, dtInsert, dtLastEdit, strEditHistory, nCompany, bIntro,
				nAllianceID, strAllianceName, strAllianceSymbol, FALSE, bNoShareA, bNoShareB));

			pRs.MoveNext();
		}
		pRs.Close();
		
		
	}
	m_wndReport.Populate();
}



void CShareReportRateDlg1::InsertCompany(CMyRecord *pMyRecord)
{
	CXTPGridRecord *pInserted = NULL;

	for(int i = 0; i < m_wndReport.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_wndReport.GetRecords()->GetAt(i);
		if(pRecord->HasChildren())
		{
			CMyRecord *pAllianceRecord = (CMyRecord*)pRecord;
			if(pAllianceRecord->CheckAllianceID(pMyRecord->m_nAllianceID))
			{
				pInserted = pAllianceRecord;
				break;
			}
		}
	}

	if(pMyRecord->m_nAllianceID == 0)
	{
		m_wndReport.AddRecord(pMyRecord);
	}
	else
	{
		if(!pInserted)
		{
			long nRcpRateA = 0;
			long nRcpRateB = 0;
			long nShareTimeA = 0;
			long nShareTimeB = 0;
			COleDateTime dtInsert = COleDateTime::GetCurrentTime();
			COleDateTime dtLastEdit = COleDateTime::GetCurrentTime();
			long nCompany = pMyRecord->m_nAllianceID;
			BOOL bIntro = FALSE;

			if(m_ci.m_nAllianceID > 0)
			{
				nRcpRateA = ((CMyRecord*)pMyRecord)->m_nOriRcpRateA;
				nRcpRateB = nRcpRateA;
				nShareTimeA = ((CMyRecord*)pMyRecord)->m_nOriShareTimeA;
				nShareTimeB = nShareTimeA;
			}

//			char bufffer[10];
			pInserted = m_wndReport.AddRecord((CMyRecord*)new CMyRecord(pMyRecord->m_nAllianceID, 
					pMyRecord->m_strAllianceName + "����", 
					CString("(") + pMyRecord->m_strAllianceSymbol + ")", "",
					"", nRcpRateA, nRcpRateB, nShareTimeA, nShareTimeB, dtInsert, dtLastEdit,
					"", nCompany, bIntro,
				pMyRecord->m_nAllianceID, 
				pMyRecord->m_strAllianceName, 
				pMyRecord->m_strAllianceSymbol,
				TRUE, 0, 0));
		}

		pInserted->GetChilds()->Add(pMyRecord);
		pInserted->SetExpanded(TRUE);
	}
}

void CShareReportRateDlg1::OnBnClickedEditBtn()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "Is_Modify_call_share_rate");
	CMkParameter *parIsRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	long nModify;
	if(pRs.Execute(&pCmd))
	{		
		parIsRet->GetValue(nModify);
	}
	else  return;

	int nCanNotModifyRecord = 0;

	for(int i = 0; i < m_wndReport.GetRows()->GetCount(); i++)
	{

		CXTPGridRow *pRow = (CXTPGridRow*)m_wndReport.GetRows()->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long nShareCode1A = m_ci.m_nShareCode1;
		long nShareCode1B = ((CMyRecord*)pRecord)->m_nShareCode1;
		CString strTCompanyName = ((CXTPGridRecordItemText*)((CMyRecord*)pRecord)->GetItem(0))->GetValue();
		long nRcpRate = ((CMyRecord*)pRecord)->GetRcpRate();
		long nRcpRate_other = (long)((CXTPGridRecordItemNumber*)((CMyRecord*)pRecord)->GetItem(6))->GetValue();
		BOOL bIsAllianceHead = ((CMyRecord*)pRecord)->m_bIsAllianceHead;
		BOOL bNoShareA = ((CMyRecord*)pRecord)->m_bNoShareA;

		if(bIsAllianceHead)
			continue;

		if(((CMyRecord*)pRecord)->GetDirtyFlag())
		{
			if(nRcpRate > 0 && nRcpRate < 10)
				nRcpRate = 5;				

			if(nModify || (nRcpRate == nRcpRate_other || nRcpRate_other <= 0 ))
			{
				int nRet = UpdateShareReportRate(nShareCode1A, nShareCode1B, strTCompanyName, nRcpRate, 
							m_ci.m_nCompanyCode, m_ui.nWNo, m_ui.strName, bNoShareA);

				if(nRet == 0)	//������ �����߻�
				{
					RefreshList();
					return;
				}
				else if(nRet == 10) //������ �̰�� �����Ұ�
				{
					nCanNotModifyRecord++;
				}
			}
			else
			{
				nCanNotModifyRecord++;
			}
		}
	}

	if(0 ==nCanNotModifyRecord)	MessageBox("�����Ǿ����ϴ�.", "Ȯ��", MB_OK);
	else
	{
		CString strMsg;
		strMsg.Format("�����Ǿ����ϴ�\r\n%d���� �ڷ�� ���� �����ɼ� ���� �ð��Դϴ�.\r\n�ٽ� ���ŵ˴ϴ�.",nCanNotModifyRecord);
		MessageBox(strMsg, "Ȯ��", MB_OK);
		RefreshList();
	}
}

int CShareReportRateDlg1::UpdateShareReportRate(long nShareCode1A, long nShareCode1B, CString strTCompany, 
												 long nRcpRate, long nWCompany, long nWNo, CString strName,
												BOOL bNoShareA)
{
	CMkCommand pCmd(m_pMkDb, "update_call_share_rate_a1");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nShareCode1A);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nShareCode1B);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRcpRate);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nWCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nWNo);
	pCmd.AddParameter(typeString, typeInput, strName.GetLength(), strName);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bNoShareA);
	CMkParameter *parLogDate = pCmd.AddParameter(typeDate, typeOutput, sizeof(COleDateTime), COleDateTime::GetCurrentTime());
	if(pCmd.Execute())
	{
		long nRet;
		parRet->GetValue(nRet);
		if(nRet == 10)
		{
			COleDateTime dtLastEdit;
			parLogDate->GetValue(dtLastEdit);

			CString strMsg;
			strMsg.Format("%s����� ����������� ���� �������� %s ���Դϴ�.\n"\
						"���� �����Ϸ� ���� �������� ������� ������ ������ �Ұ����մϴ�.\n",
						strTCompany, dtLastEdit.Format("%Y-%m-%d"));
			MessageBox(strMsg, "����", MB_ICONINFORMATION);
			return 10;
		}
		return 1;
	}

	MessageBox("������Ʈ ����\n\n��õ��Ͻñ� �ٶ��ϴ�.", "����", MB_ICONINFORMATION);
	return 0;
}



void CShareReportRateDlg1::OnBnClickedOk()
{

	//	OnOK();
}

BOOL CShareReportRateDlg1::CheckValidate()
{
	CShareReportRateDlg* pShareReportRateDlg = (CShareReportRateDlg*)(GetParent()->GetParent());

/*
	for(int i = 0; i < m_wndReport.GetRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = (CXTPGridRow*)m_wndReport.GetRows()->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long nShareCode1A = m_ci.m_nShareCode1;
		long nShareCode1B = ((CMyRecord*)pRecord)->m_nShareCode1;
		long nRcpRate = ((CMyRecord*)pRecord)->GetRcpRate();

		if(nRcpRate == 0)
		{
			MessageBox("������ ���� ������ �Էµ��� ���� ȸ���簡 �����մϴ�.!\n\n"\
				"��� �Է��Ͻñ� �ٶ��ϴ�.", 
				"Ȯ��", 
				MB_ICONINFORMATION);
			return FALSE;
		}
	}
*/
	if(pShareReportRateDlg->m_nBasicRate > pShareReportRateDlg->m_nBalance)
	{
		MessageBox("������ �ܾ��� �ּ��ܾ׺��� �����ϴ�.\n"\
			"������·� �ּ��ܾ��̻��� �ݾ��� �Ա��Ͻ��� �����ø�,\n "\
			"2��ä�� �̻��� ������ ���� ������� �ʽ��ϴ�.",
			"������ �ܾ� ����",
			MB_ICONEXCLAMATION);
	}

	return TRUE;
}

void CShareReportRateDlg1::OnBnClickedRefreshBtn()
{
	RefreshList();
}

int CShareReportRateDlg1::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return 0;
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CShareReportRateDlg1::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	static BOOL isDoModal = FALSE;
	if(TRUE == isDoModal) return;
	isDoModal = TRUE;

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecords *pRecords = m_wndReport.GetRecords();

	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();
	long nShareCode1A = m_ci.m_nShareCode1;
	long nShareCode1B = ((CMyRecord*)pRecord)->m_nShareCode1;

	if(nCol == SR_HISTORY_COL)
	{
		//CShareReportRateLogDlg dlg;
		//dlg.m_nShareCode1A = nShareCode1A;
		//dlg.m_nShareCode1B = nShareCode1B;
		//dlg.DoModal();
	}
	else if(nCol == SR_TRANSFER_COL)
	{
		CShareReportTransferDlg dlg;
		dlg.m_nToCompany = ((CMyRecord*)pRecord)->m_nCompany;

		CShareReportRateDlg* pShareReportRateDlg = (CShareReportRateDlg*)(GetParent()->GetParent());

		CString sBalance, sMinBalance;
		pShareReportRateDlg->m_BalanceEdit.GetWindowText(sBalance);
		pShareReportRateDlg->m_BasicRateEdit.GetWindowText(sMinBalance);
		sBalance.Replace(",", "");
		sBalance.Replace("��", "");
		sMinBalance.Replace(",", "");
		sMinBalance.Replace("��", "");
		//dlg.m_pShareReportRateDlg1 = this;

		int nAbilityMoney;
		
		if(m_ci.m_nCompanyCode == 2958) //������ ����â
			nAbilityMoney = _ttoi(sBalance);
		else
			nAbilityMoney = _ttoi(sBalance) - _ttoi(sMinBalance);

		dlg.m_nAbilityMoney = nAbilityMoney;

		if(dlg.DoModal() == IDOK )
		{
			RefreshMoney();
		} //DoModal if
	}// (nCol == SR_TRANSFER_COL) if
	else if(nCol == SR_REQUEST_COL)
	{
		CShareReportWantTransferDlg dlg;
		dlg.m_nToCompany = ((CMyRecord*)pRecord)->m_nCompany;
		dlg.DoModal();	
	}
	else if(nCol == SR_INTRO_COL)
	{
		/*
		if(! ((CMyRecord*)pRecord)->m_bIsAllianceHead )
		{
			CCompanyIntroDlg dlg;
			dlg.m_nIntroCompany = ((CMyRecord*)pRecord)->m_nCompany;
			dlg.m_nWriteMode = 0;
			dlg.DoModal();
		}
		*/
		

		//MessageBox("�غ��߿� �ֽ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	}

	isDoModal =  FALSE;
}
void CShareReportRateDlg1::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	return;
	CMyFormView::OnActivate(nState, pWndOther, bMinimized);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CShareReportRateDlg1::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
	/*
	*result = 0;
	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	if (NULL == pNotify->hwndTool)
	{
		//Order to update a tooltip for a current Tooltip Help
		//He has not a handle of the window
		//If you want change tooltip's parameter than make it's here
	}
	else
	{
		//Order to update a tooltip for a specified window as tooltip's tool

		//Gets a ID of the window if needed
		UINT nID = CWnd::FromHandle(pNotify->hwndTool)->GetDlgCtrlID();

		//Change a tooltip's parameters for a current window (control)
		BOOL bOutside = FALSE;
		CPoint pt = *pNotify->pt;
		CRect rect, rcCtrl, rcCol;
		if (IDC_REPORT_LIST == nID)
		{
			m_wndReport.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			CXTPGridRow *pRow = m_wndReport.HitTest(pt);
			if(pRow)
			{
				CXTPGridColumn *pCol = NULL;
				pRow->HitTest(pt, &rcCol, &pCol);

				if(pCol)
				{
					if(pCol->GetItemIndex() <= 2)
					{
						CMakeHtmlTable htable;
						long nCompany = ((CMyRecord*)pRow->GetRecord())->m_nCompany;
						if(CRcpView::GetCrossCompanyInfo(&htable, nCompany))
						{
							htable.SetTitle("����ȸ���� ����");
							htable.SetTableBorder(1);
							pNotify->ti->sTooltip = htable.GetHtmlTable();
							pt = *pNotify->pt;
							pt.x += 5;
							pt.y += 20;
							*pNotify->pt = pt;
						}
					}
					else if(pCol->GetItemIndex() == SR_SHARETIMEA_COL || 
							pCol->GetItemIndex() == SR_SHARETIMEB_COL)
					{
						CMakeHtmlTable htable;
						long nCompany = ((CMyRecord*)pRow->GetRecord())->m_nCompany;

						htable.SetTitle("1:1���� ����");
						htable.SetTableBorder(1);

						CString strInfo;
						if(GetFirstShareTimeInfo(nCompany, strInfo))
						{
							htable.AddCol(strInfo);							
							htable.AddRow();
						}

						htable.AddCol("1. �ڻ�, Ÿ�� ���� ���߿� �ϳ��� �������̸�, ä�ΰ����ð����� ������");
						htable.AddRow();
						htable.AddCol("2. �ϴ��ϰ������� ������ �ð��� ä�ΰ����ð����� ������츸 �����");
						htable.AddRow();
						htable.AddCol("3. ��ȣ������ Ʋ����, ���� �ð��� �������� ������");
						htable.AddRow();
						htable.AddCol("4. �ϴ��ϰ����ð��� ä�ΰ����ð����� �ʰ��Ѵٰ� ������ �������� ����");
						htable.AddRow();
						htable.AddCol("5. ����9�ú��� ����3�ñ����� ������ ������ �� ����");
						htable.AddRow();
						htable.AddCol("6. ��������� �����ϰ�, �ѹ������� �����ϰ� �����Ұ���");
						htable.AddRow();

						pNotify->ti->sTooltip = htable.GetHtmlTable();
						pt = *pNotify->pt;
						pt.x += 5;
						pt.y += 20;
						*pNotify->pt = pt;
					}
				}
				/*
				else
				{
				pNotify->ti->sTooltip = m_vrCur->GetOrderRecord(pRow->GetIndex())->info[pCol->GetItemIndex()].c_str();
				pt = *pNotify->pt;
				pt.x += 5;
				pt.y += 20;
				*pNotify->pt = pt;
				}
				*/
//			}

//		} //if
//	} //if
	
} //End NotifyDisplayTooltip




void CShareReportRateDlg1::OnBnClickedRequestBtn()
{
	OpenRequestBox();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CShareReportRateDlg1::OpenRequestBox()
{
	if(IsRequest(m_ci.m_nCompanyCode))
	{
		CShareTranferRequestDlg dlg;

		CShareReportRateDlg* pShareReportRateDlg = (CShareReportRateDlg*)(GetParent()->GetParent());
		CString sBalance, sMinBalance;
		pShareReportRateDlg->m_BalanceEdit.GetWindowText(sBalance);
		pShareReportRateDlg->m_BasicRateEdit.GetWindowText(sMinBalance);
		sBalance.Replace(",", "");
		sBalance.Replace("��", "");
		sMinBalance.Replace(",", "");
		sMinBalance.Replace("��", "");

		int nAbilityMoney = _ttoi(sBalance) - _ttoi(sMinBalance);

		dlg.m_nAbilityMoney = nAbilityMoney;
		dlg.m_pShareReportRateDlg1 = this;
		dlg.m_sSql = "select_transfer_request_1";

		dlg.DoModal();		

	}
	else
		MessageBox("Ÿ�翡���� ��û�� �����ϴ�", "Ȯ��", MB_ICONERROR);
}

bool CShareReportRateDlg1::IsRequest(int nCompany)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_request");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);

	if(!pRs.Execute(&pCmd)) return false;

	if(pRs.GetRecordCount() > 0)
		return true;
	else
		return false;

}
void CShareReportRateDlg1::OnBnClickedMyRequestBtn()
{
	CShareTansferMyRequest pDlg;
	pDlg.DoModal();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CShareReportRateDlg1::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CShareReportRateDlg1::OnBnClickedShareTimeEdit()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "Is_Modify_share_time");
	CMkParameter *parIsRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	long nModify;
	if(pRs.Execute(&pCmd))
	{		
		parIsRet->GetValue(nModify);
		if(!nModify)
		{
			MessageBox("���� 9�ú��� ~ ���� 3�ñ����� �����ð� ������ �Ұ��� �մϴ�.", 
						"�����ð� ���� �Ұ�", 
						MB_ICONINFORMATION);
			return;
		}
	}
	else  return;

	int nCanNotModifyRecord = 0;

	for(int i = 0; i < m_wndReport.GetRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = (CXTPGridRow*)m_wndReport.GetRows()->GetAt(i);
		CXTPGridRecord *pRecord = pRow->GetRecord();
		long nShareCode1A = m_ci.m_nShareCode1;
		long nShareCode1B = ((CMyRecord*)pRecord)->m_nShareCode1;
		CString strTCompanyName = ((CXTPGridRecordItemText*)((CMyRecord*)pRecord)->GetItem(0))->GetValue();
		long nShareTimeA = ((CMyRecord*)pRecord)->GetShareTimeA();
		//long nShareTimeB = ((CXTPGridRecordItemNumber*)((CMyRecord*)pRecord)->GetItem(8))->GetValue();


		if(((CMyRecord*)pRecord)->GetShareTimeDirtyFlag())
		{
			int nRet = UpdateShareTime(nShareCode1A, nShareCode1B, strTCompanyName, nShareTimeA, m_ci.m_nCompanyCode, m_ui.nWNo, m_ui.strName);

			if(nRet == 0)	//������ �����߻�
			{
				RefreshList();
				return;
			}
			else if(nRet == 10) //������ �̰�� �����Ұ�
			{
				nCanNotModifyRecord++;
			}
		}
	}

	if(0 ==nCanNotModifyRecord)	MessageBox("�����Ǿ����ϴ�.", "Ȯ��", MB_OK);
	else
	{
		CString strMsg;
		strMsg.Format("�����Ǿ����ϴ�\r\n%d���� �ڷ�� ���� �����ɼ� ���� �ð��Դϴ�.\r\n�ٽ� ���ŵ˴ϴ�.",nCanNotModifyRecord);
		MessageBox(strMsg, "Ȯ��", MB_OK);
		RefreshList();
	}
}


int CShareReportRateDlg1::UpdateShareTime(long nShareCode1A, long nShareCode1B, CString strTCompany, 
												long nShareTime, long nWCompany, long nWNo, CString strName)
{
	CMkCommand pCmd(m_pMkDb, "update_share_time_a1");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nShareCode1A);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nShareCode1B);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nShareTime);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nWCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nWNo);
	pCmd.AddParameter(typeString, typeInput, strName.GetLength(), strName);
	CMkParameter *parLogDate = pCmd.AddParameter(typeDate, typeOutput, sizeof(COleDateTime), COleDateTime::GetCurrentTime());
	if(pCmd.Execute())
	{
		long nRet;
		parRet->GetValue(nRet);
		if(nRet == 10)
		{
			COleDateTime dtLastEdit;
			parLogDate->GetValue(dtLastEdit);

			CString strMsg;
			strMsg.Format("%s����� �����ð� ���� �������� %s ���Դϴ�.\n"\
				"���� �����Ϸ� ���� �������� ������� ������ ������ �Ұ����մϴ�.\n"\
				"�ٸ�, �ð��� �մ��°��� �������� �����մϴ�.",
				strTCompany, dtLastEdit.Format("%Y-%m-%d"));
			MessageBox(strMsg, "����", MB_ICONINFORMATION);
			return 10;
		}
		return 1;
	}

	MessageBox("������Ʈ ����\n\n��õ��Ͻñ� �ٶ��ϴ�.", "����", MB_ICONINFORMATION);
	return 0;
}

void CShareReportRateDlg1::Filter(CString strData)
{
	CXTPGridRecords *pRecords = m_wndReport.GetRecords();		
	CXTPGridColumns *pCols = m_wndReport.GetColumns();
	CXTPGridColumn* pColumn = NULL;
	BOOL bDigit = FALSE;

	CString strData2 = strData;
	strData2.Replace("-", "");


	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CXTPGridRecords *pChildRecords = pRecord->GetChilds();

		if(pChildRecords)
		{
			if(pChildRecords->GetCount() == 0)
			{
				CString strName = ((CXTPGridRecordItemText*)pRecord->GetItem(0))->GetCaption(pColumn);
				CString strPhone = ((CXTPGridRecordItemText*)pRecord->GetItem(1))->GetCaption(pColumn);
				CString strOfficePhone = ((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetCaption(pColumn);
				
				if(strName.Find(strData) >= 0 ||
					strPhone.Find(strData) >= 0 ||
					strOfficePhone.Find(strData) >= 0)
					pRecord->SetVisible(TRUE);
				else
					pRecord->SetVisible(FALSE);
			}
			else
			{
				for(int j=0; j<pChildRecords->GetCount(); j++)
				{
					if(strData.GetLength() == 0) 
					{
						pChildRecords->GetAt(j)->SetVisible(TRUE);
						continue;
					}

					CString strName = ((CXTPGridRecordItemText*)pChildRecords->GetAt(j)->GetItem(0))->GetCaption(pColumn);
					CString strPhone = ((CXTPGridRecordItemText*)pChildRecords->GetAt(j)->GetItem(1))->GetCaption(pColumn);
					CString strOfficePhone = ((CXTPGridRecordItemText*)pChildRecords->GetAt(j)->GetItem(2))->GetCaption(pColumn);


					if(strName.Find(strData) >= 0 ||
						strPhone.Find(strData) >= 0 ||
						strOfficePhone.Find(strData) >= 0)
						pChildRecords->GetAt(j)->SetVisible(TRUE);
					else
						pChildRecords->GetAt(j)->SetVisible(FALSE);
				}
			}
		}
	}

	m_wndReport.Populate();
}

void CShareReportRateDlg1::OnEnChangeSearchEdit()
{
	CString strData;
	m_SearchEdit.GetWindowText(strData);
	Filter(strData);
}


void CShareReportRateDlg1::OnBnClickedMyAllianceManagerBtn()
{
	if(m_bHasAlliancePower)
	{
		CMyAllianceManagerDlg dlg;
		dlg.DoModal();
	}
}

void CShareReportRateDlg1::OnBnClickedCorpBtn()
{
	CCorpOrderDlg dlg;
	dlg.DoModal();

}

void CShareReportRateDlg1::RefreshMoney()
{
	CShareReportRateDlg* pShareReportRateDlg = (CShareReportRateDlg*)(GetParent()->GetParent());

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_call_share_rate_a2", TRUE);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	CMkParameter *parBalance = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parBasicRate = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parAccount = pCmd.AddParameter(typeString, typeOutput, 50, CString(""));
	CMkParameter *parYesterday = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parGlobalSharTime = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parHasAlliancePower = pCmd.AddParameter(typeBool, typeOutput, sizeof(BOOL), 0);

	long nBalance, nBasicRate, nYesterday, nGlobalShareTime;
	CString strAccount;
	BOOL bAlliancePower;

	if(pRs.Execute(&pCmd))
	{
		parBalance->GetValue(nBalance);
		parBasicRate->GetValue(nBasicRate);
		parAccount->GetValue(strAccount);
		parYesterday->GetValue(nYesterday);
		parGlobalSharTime->GetValue(nGlobalShareTime);
		parHasAlliancePower->GetValue(bAlliancePower);

		pShareReportRateDlg->m_nBalance = nBalance;
		pShareReportRateDlg->m_nBasicRate = nBasicRate;

		/*
		pShareReportRateDlg->m_BalanceEdit.SetWindowText(LF->GetMyNumberFormat(nBalance) + "��");
		pShareReportRateDlg->m_BasicRateEdit.SetWindowText(LF->GetMyNumberFormat(nBasicRate) + "��");
		pShareReportRateDlg->m_AccountEdit.SetWindowText(CString("�ϳ����� ") + strAccount);
		pShareReportRateDlg->m_YesterdayEdit.SetWindowText(LF->GetMyNumberFormat(nYesterday) + "��");
		*/
		//RefreshList();
	}
}

void CShareReportRateDlg1::OnBnClickedRequestDrawingBtn()
{
	if(!LF->POWER_CHECK(1040, "��ݿ�û", TRUE))
		return;

	CRequestDrawingDlg dlg;
	dlg.DoModal();
}
