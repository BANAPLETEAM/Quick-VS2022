// OrderLogDetailDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "OrderLogDetailDlg.h"
#include "MakeHtmlTable.h"
#include "RcpView.h"
#include "RcpMultiStateChange.h"

//static LOGFONT m_lfList = {14,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"���� ���"};

COrderLogRecord :: COrderLogRecord(int nCount, COleDateTime dtLog, int nState, int nWNo, int nWCompany,
								   CString sLog, int nRNo, int nRCompany, CString strWName, int nColor)
{
	AddItem(new CXTPGridRecordItemNumber(nCount));
	AddItem(new CXTPGridRecordItemMyDateTime(dtLog));
	AddItem(new CXTPGridRecordItemStateNumber(nState));

	CString strTemp = "";

	if(nWNo == m_ui.nWNo && nWCompany == m_ui.nCompany)
		strTemp = "����";
	else if(nWNo == -1)
		strTemp = "���";
	else if(nWNo == -2)
		strTemp = "����";
	else
	{
		if(!strWName.IsEmpty())
			strTemp.Format("%s(%d)", strWName, nWNo);
		else
			strTemp.Format("%d",nWNo);
	}

	AddItem(new CXTPGridRecordItemText(strTemp));

	//CXTPGridRecordItemRNoNumber *pItem = (CXTPGridRecordItemRNoNumber*)AddItem(new CXTPGridRecordItemRNoNumber(nWNo));
	//pItem->m_strWName = strWName;
	AddItem(new CXTPGridRecordItemCompanyNumber(nWCompany));
	AddItem(new CXTPGridRecordItemText(sLog));

	if(nRNo == 0)
	{
		AddItem(new CXTPGridRecordItemEmptyZeroNumber(0));
		AddItem(new CXTPGridRecordItemEmptyZeroNumber(0));
	}
	else
	{
		AddItem(new CXTPGridRecordItemEmptyZeroNumber(nRNo));
		AddItem(new CXTPGridRecordItemCompanyNumber(nRCompany));
	}

	m_nColor = nColor;
	m_nWNo = nWNo;

	m_nRiderCompany = nRCompany;
	m_nRNo = nRNo;
}


void COrderLogRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = this->GetIndex();
	int nCol = pDrawArgs->pColumn->GetItemIndex();


	CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();	
	long nColor = ((COrderLogRecord*)pRecord)->m_nColor;
	long nWNo = ((COrderLogRecord*)pRecord)->m_nWNo;

	CXTPGridColumn *pColumn = NULL;
	CString strCaption = (this->GetItem(nCol))->GetCaption(pColumn);

	//CString strCaption = ((CXTPGridRecordItemText*)m_lstOrderLog.GetRecords()->GetAt(nRow)->GetItem(3))->GetCaption(pColumn);

	if(nColor != -1) //���� ���̶� ���� ����
		pItemMetrics->clrBackground = RGB(245, 245, m_nColor);
	else
	{	
		if(nWNo == -1) //���
			pItemMetrics->clrBackground = RGB(150, 255, 230);			
		else if(nWNo == -2) //����
			pItemMetrics->clrBackground = RGB(180, 255, 180);			
		else
			pItemMetrics->clrBackground = RGB(255, 195, 252);        //������
	}
}


COrderChangeRecord :: COrderChangeRecord(int nCount, int nRNo, CString strEditor, int nWCompany, COleDateTime dtLog,
										 CString sState, CString sBeforeEtc, CString sAfterEtc, int nColor)
{
	AddItem(new CXTPGridRecordItemNumber(nCount));
	AddItem(new CXTPGridRecordItemText(strEditor + "(" + LF->GetStringFromLong(nRNo) + ")"));
	AddItem(new CXTPGridRecordItemCompanyNumber(nWCompany));
	AddItem(new CXTPGridRecordItemMyDateTime(dtLog));
	AddItem(new CXTPGridRecordItemText(sState));
	AddItem(new CXTPGridRecordItemText(sBeforeEtc));
	AddItem(new CXTPGridRecordItemText(sAfterEtc));

	m_nColor = nColor;
	m_nCount = nCount;
	m_sState = sState;
	m_sBeforeEtc = sBeforeEtc;
	m_sAfterEtc = sAfterEtc;
}

COrderChangeRecord :: COrderChangeRecord(int nCount, CString sState, CString sBeforeEtc, CString sAfterEtc, int nColor)
{
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(""));
	AddItem(new CXTPGridRecordItemText(sState));
	AddItem(new CXTPGridRecordItemText(sBeforeEtc));
	AddItem(new CXTPGridRecordItemText(sAfterEtc));

	m_nColor = nColor;
	m_nCount = nCount;
	m_sState = sState;
	m_sBeforeEtc = sBeforeEtc;
	m_sAfterEtc = sAfterEtc;
}

void COrderChangeRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	int nRow = this->GetIndex();
	int nCol = pDrawArgs->pColumn->GetItemIndex();

	CXTPGridRecord *pRecord = pDrawArgs->pRow->GetRecord();	
	long nState = ((COrderChangeRecord*)pRecord)->m_nColor;

	pItemMetrics->clrBackground = RGB(245, 245, m_nColor);
}


// COrderLogDetailDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(COrderLogDetailDlg, CMyDialog)
COrderLogDetailDlg::COrderLogDetailDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COrderLogDetailDlg::IDD, pParent)
{
	m_nTNo = 0;
	m_bCross = FALSE;
	m_nOrderCompany = -1;
}

COrderLogDetailDlg::~COrderLogDetailDlg()
{
}

void COrderLogDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_STATIC1, m_stc);
	DDX_Control(pDX, IDC_RECT_STC, m_stcRect);
	DDX_Control(pDX, IDC_ORDER_LOG_REPORT, m_lstOrderLog);
	DDX_Control(pDX, IDC_ORDER_CHANGE_REPORT, m_lstOrderChange);
	DDX_Control(pDX, IDCANCEL, m_CancelBtn);
}


BEGIN_MESSAGE_MAP(COrderLogDetailDlg, CMyDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_COMMAND(ID_REALLOCATE, OnReAllocate)
	ON_COMMAND(ID_RIDER_INFO, OnRiderInfo)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
	ON_BN_CLICKED(IDC_RIDER_INFO_BTN, &COrderLogDetailDlg::OnBnClickedRiderInfoBtn)
	ON_BN_CLICKED(IDC_RE_ALLOCATE_BTN, &COrderLogDetailDlg::OnBnClickedReAllocateBtn)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_ORDER_LOG_REPORT, OnReportItemRClick)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &COrderLogDetailDlg::OnBnClickedRefreshBtn)
END_MESSAGE_MAP()



void COrderLogDetailDlg::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
{
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
		if (IDC_ORDER_LOG_REPORT == nID)
		{
			m_lstOrderLog.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			CXTPGridRow *pRow = m_lstOrderLog.HitTest(pt);
			if(pRow)
			{
				CXTPGridColumn *pCol = NULL;
				pRow->HitTest(pt, &rcCol, &pCol);

				int nRow = pRow->GetIndex();

				CString strCaption = ((CXTPGridRecordItemText*)m_lstOrderLog.GetRecords()->GetAt(nRow)->GetItem(2))->GetCaption(pCol);
				CString strCount = ((CXTPGridRecordItemNumber*)m_lstOrderLog.GetRecords()->GetAt(nRow)->GetItem(0))->GetCaption(pCol);

				if(strCaption == "����")
				{					
					CMakeHtmlTable htable;

					CXTPGridRecord *pRecord = pRow->GetRecord();

					int nRecordCount = m_lstOrderChange.GetRows()->GetCount();

					htable.AddCol("���泻��");
					htable.AddCol("������");
					htable.AddCol("������");
					htable.AddRow();

					for(int i=0 ; i< nRecordCount; i++)
					{
						CXTPGridRow *pRow1 = m_lstOrderChange.GetRows()->GetAt(i);
						CXTPGridRecord *pRecord1 = pRow1->GetRecord();
						int nCount1 = ((COrderChangeRecord*)pRecord1)->m_nCount;

						CString strCount1;
						strCount1.Format("%d", nCount1);

						if(strCount == strCount1)
						{
							CString strState = ((COrderChangeRecord*)pRecord1)->m_sState;
							CString strBefore = ((COrderChangeRecord*)pRecord1)->m_sBeforeEtc; 
							CString strAfter = ((COrderChangeRecord*)pRecord1)->m_sAfterEtc;

							htable.AddCol(strState);
							htable.AddCol(strBefore);
							htable.AddCol(strAfter);
							htable.AddRow();
						}
					}

					CString strTitle;
					strTitle.Format("��������");
					htable.SetTitle(strTitle);
					htable.SetTableBorder(1);
					pNotify->ti->sTooltip = htable.GetHtmlTable();
					pt = *pNotify->pt;
					pt.x += 5;
					pt.y += 20;
					*pNotify->pt = pt;				

				}

			}
		} //if
	} //if
} //End NotifyDisplayTooltip

BOOL COrderLogDetailDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CString strFormat;
	strFormat.Format("������ȣ - %d", m_nTNo);

	SetWindowText(strFormat);
	GetDlgItem(IDC_TNO_EDIT)->SetWindowText(LF->GetStringFromLong(m_nTNo));

	m_tooltip.Create(this, FALSE);
	m_tooltip.SetBehaviour(PPTOOLTIP_MULTIPLE_SHOW);
	m_tooltip.SetNotify();
	m_tooltip.SetImageList(IDB_LIST, 16, 18, 14, RGB(0,255,255));
	m_tooltip.SetTransparency(30);

	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, 100);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, 50000);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, 10);
	m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, 10);

	m_tooltip.AddTool(&m_lstOrderLog, "");

	CXTPGridColumn *pCol0 = m_lstOrderLog.AddColumn(new CXTPGridColumn(0, "����", 35, FALSE));
	CXTPGridColumn *pCol1 = m_lstOrderLog.AddColumn(new CXTPGridColumn(1, "�߻�����", 90, FALSE));
	CXTPGridColumn *pCol2 = m_lstOrderLog.AddColumn(new CXTPGridColumn(2, "����", 50, FALSE));
	CXTPGridColumn *pCol3 = m_lstOrderLog.AddColumn(new CXTPGridColumn(3, "������", 80, FALSE));
	CXTPGridColumn *pCol4 = m_lstOrderLog.AddColumn(new CXTPGridColumn(4, "������ȸ��", 80, FALSE));
	CXTPGridColumn *pCol5 = m_lstOrderLog.AddColumn(new CXTPGridColumn(5, "�����α�", 255, FALSE));
	CXTPGridColumn *pCol6 = m_lstOrderLog.AddColumn(new CXTPGridColumn(6, "����ȣ", 70, FALSE));
	CXTPGridColumn *pCol7 = m_lstOrderLog.AddColumn(new CXTPGridColumn(7, "���Ҽ�ȸ��", 85, FALSE));
 
	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetAlignment(DT_CENTER);	
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->SetAlignment(DT_RIGHT);
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->SetAlignment(DT_CENTER);
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->SetAlignment(DT_CENTER);
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->SetAlignment(DT_CENTER);
	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol5->SetAlignment(DT_CENTER);
	pCol6->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol6->SetAlignment(DT_CENTER);
	pCol7->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol7->SetAlignment(DT_CENTER);

	m_lstOrderLog.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_lstOrderLog.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";
	m_lstOrderLog.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstOrderLog.GetReportHeader()->AllowColumnResize(TRUE);
	m_lstOrderLog.GetReportHeader()->AllowColumnSort(TRUE); 
	m_lstOrderLog.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstOrderLog.AllowEdit(TRUE);
	m_lstOrderLog.FocusSubItems(TRUE);
	m_lstOrderLog.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstOrderLog.SetGridColor(RGB(180, 180, 200));
	LOGFONT m_lfList = {13,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"����"};
	m_lstOrderLog.GetPaintManager()->SetTextFont(m_lfList);
	m_lstOrderLog.Populate();
	m_lstOrderChange.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);

	CXTPGridColumn *pCol10 = m_lstOrderChange.AddColumn(new CXTPGridColumn(0, "����", 40, FALSE));
	CXTPGridColumn *pCol11 = m_lstOrderChange.AddColumn(new CXTPGridColumn(1, "������", 80, FALSE));
	CXTPGridColumn *pCol12 = m_lstOrderChange.AddColumn(new CXTPGridColumn(2, "�Ҽ�ȸ��", 80, FALSE));
	CXTPGridColumn *pCol13 = m_lstOrderChange.AddColumn(new CXTPGridColumn(3, "�����ð�", 80, FALSE));
	CXTPGridColumn *pCol14 = m_lstOrderChange.AddColumn(new CXTPGridColumn(4, "���泻��", 80, FALSE));
	CXTPGridColumn *pCol15 = m_lstOrderChange.AddColumn(new CXTPGridColumn(5, "������", 175, FALSE));
	CXTPGridColumn *pCol16 = m_lstOrderChange.AddColumn(new CXTPGridColumn(6, "������", 175, FALSE));

	pCol10->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol10->SetTreeColumn(1);
	pCol10->SetAlignment(DT_RIGHT);	
	pCol11->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol11->SetAlignment(DT_RIGHT);
	pCol12->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol12->SetAlignment(DT_CENTER);
	pCol13->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol13->SetAlignment(DT_RIGHT);
	pCol14->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol14->SetAlignment(DT_CENTER);
	pCol15->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol15->SetAlignment(DT_CENTER);
	pCol16->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol16->SetAlignment(DT_CENTER);

	m_lstOrderChange.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_lstOrderChange.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";
	m_lstOrderChange.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstOrderChange.GetReportHeader()->AllowColumnResize(TRUE);
	m_lstOrderChange.GetReportHeader()->AllowColumnSort(TRUE);
	m_lstOrderChange.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_lstOrderChange.AllowEdit(TRUE);
	m_lstOrderChange.FocusSubItems(TRUE);
	m_lstOrderChange.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstOrderChange.SetGridColor(RGB(180, 180, 200));
	m_lstOrderChange.SetTreeIndent(30);

	m_lstOrderChange.Populate();

	ReFreshOrderLogReport(m_bFullSearch);
	ReFreshOrderChangeReport();

	m_lstOrderChange.Populate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void COrderLogDetailDlg::ReFreshOrderLogReport(BOOL bFullSearch)
{
	m_lstOrderLog.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_order_log_details_new");
	pCmd.AddParameter(m_nTNo);
	pCmd.AddParameter(bFullSearch);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtLog; //��¥long nState, nWno, nWCompany, nEtc1, nEtc2; //����, �����ڹ�ȣ, ���ȸ��, ����ȣ
	int nState, nWNo, nWCompany, nEtc1, nEtc2;
	CString  sEtc, sWName;  //

	int i=0;
	CString si;

	int nColor = 150;
	int nColorCount = 0;

	while(!pRs.IsEOF())  
	{
		//dtlog , nState , nWno , daeri.dbo.GetBranchName(nWCompany) as sWCompany , sEtc  
		pRs.GetFieldValue("dtLog", dtLog);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nWCompany", nWCompany);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("nEtc1", nEtc1);
		pRs.GetFieldValue("nEtc2", nEtc2); // nRNo
		pRs.GetFieldValue("sWName", sWName); // nRNo

		if(nState == 200) //����
		{
			m_lstOrderLog.AddRecord(new COrderLogRecord(i+1, dtLog, nState, nWNo, nWCompany, sEtc, nEtc2, nEtc1, sWName, nColor));

			if(nColorCount >= 50)
				nColorCount = 0;

			m_cpColor[nColorCount].x = i+1;
			m_cpColor[nColorCount].y = nColor;

			/*nColor += 20;

			if(nColor > 255)
			nColor = 255;
			*/
			if(nColorCount == 0)
			{
				nColor = 200;
			}
			else
			{
				if(nColorCount%2 == 0)
					nColor = 200;
				else
					nColor = 150;
			}			

			nColorCount++;

		}
		else
			m_lstOrderLog.AddRecord(new COrderLogRecord(i+1, dtLog, nState, nWNo, nWCompany, sEtc, nEtc2, nEtc1, sWName, -1));

		i++;
		pRs.MoveNext();
	}

	m_lstOrderLog.Populate();

}

void COrderLogDetailDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this); 

	CRect DrawRect;
 
	m_stcRect.GetClientRect(&DrawRect);
	m_stcRect.ClientToScreen(&DrawRect);
	ScreenToClient(&DrawRect);

	dc.Rectangle(DrawRect);

	int nCenter = (DrawRect.bottom + DrawRect.top) / 2;

	CFont font;
	font.CreateFont(14,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"����ü");
	dc.SelectObject(&font);

	CPen WnoPen;
	WnoPen.CreatePen(PS_SOLID, 2, RGB(255, 185, 252));
	CPen RiderPen;
	RiderPen.CreatePen(PS_SOLID, 2, RGB(120, 255, 220));
	CPen ServerPen;
	ServerPen.CreatePen(PS_SOLID, 2, RGB(160, 255, 160));


	dc.SelectObject(&WnoPen);
	dc.SetBkMode(TRANSPARENT);
	dc.MoveTo(DrawRect.left+2, nCenter);
	dc.LineTo(DrawRect.left + 15, nCenter);

	CRect strRect = DrawRect;
	strRect.left = DrawRect.left + 15;
	strRect.top += 2;
	dc.SetTextColor( RGB(255, 185, 252)); //������
	dc.DrawText("��Ȳ��", strRect, DT_LEFT | DT_VCENTER);

	dc.SelectObject(&RiderPen);
	dc.MoveTo(DrawRect.left + 75, nCenter);
	dc.LineTo(DrawRect.left + 90, nCenter);

	strRect.left = DrawRect.left + 90;
	dc.SetTextColor(RGB(120, 255, 220)); //���
	dc.DrawText("���", strRect, DT_LEFT | DT_VCENTER);

	dc.SelectObject(&ServerPen);
	dc.MoveTo(DrawRect.left + 130, nCenter);
	dc.LineTo(DrawRect.left + 145, nCenter);

	strRect.left = DrawRect.left + 145;
	dc.SetTextColor(RGB(160, 255, 160)); //����
	dc.DrawText("����", strRect, DT_LEFT | DT_VCENTER);
}

void COrderLogDetailDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

void COrderLogDetailDlg::ReFreshOrderChangeReport()
{
	if(m_bCross)
		return;

	m_lstOrderChange.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_order_edit_history_5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nTNo);

	if(!pRs.Execute(&pCmd)) return;

	//	2007-01-06 18:13:07.583		10	0	10	15990707	15990808	���ﵿ	�Ｚ��	[���5:���� ��]	9000	1000	
	COleDateTime dtLog;

	if(pRs.GetRecordCount() == 1)
		return;

	for(int i=0 ; i<pRs.GetRecordCount(); i++)
	{
		ST_EDIT_HISTORY EditHistory;

		pRs.GetFieldValue("nTNo", EditHistory.nTNo);
		pRs.GetFieldValue("dtEdit", EditHistory.dtEdit);
		pRs.GetFieldValue("nWCompany", EditHistory.nWCompany);
		pRs.GetFieldValue("nWNo", EditHistory.nWNo);
		pRs.GetFieldValue("sEditor", EditHistory.strEditor);
		pRs.GetFieldValue("nCompany", EditHistory.nCompany);

		pRs.GetFieldValue("sOName", EditHistory.strOName);
		pRs.GetFieldValue("sOPhone", EditHistory.strOPhone);
		pRs.GetFieldValue("sOMobile", EditHistory.strOMobile);
		pRs.GetFieldValue("sODepart", EditHistory.strODepart);
		pRs.GetFieldValue("sOManager", EditHistory.strOManager);
		pRs.GetFieldValue("sOAddress", EditHistory.strOAddress);
		pRs.GetFieldValue("sODetail", EditHistory.strODetail);
		pRs.GetFieldValue("sOMemo", EditHistory.strOMemo);
		pRs.GetFieldValue("sODong", EditHistory.strODong);

		pRs.GetFieldValue("sSName", EditHistory.strSName);
		pRs.GetFieldValue("sSPhone", EditHistory.strSPhone);
		pRs.GetFieldValue("sSMobile", EditHistory.strSMobile);
		pRs.GetFieldValue("sSDepart", EditHistory.strSDepart);
		pRs.GetFieldValue("sSManager", EditHistory.strSManager);
		pRs.GetFieldValue("sSAddress", EditHistory.strSAddress);
		pRs.GetFieldValue("sSDetail", EditHistory.strSDetail);
		pRs.GetFieldValue("sSDong", EditHistory.strSDong);

		pRs.GetFieldValue("sDName", EditHistory.strDName);
		pRs.GetFieldValue("sDPhone", EditHistory.strDPhone);
		pRs.GetFieldValue("sDMobile", EditHistory.strDMobile);
		pRs.GetFieldValue("sDDepart", EditHistory.strDDepart);
		pRs.GetFieldValue("sDManager", EditHistory.strDManager);
		pRs.GetFieldValue("sDAddress", EditHistory.strDAddress);
		pRs.GetFieldValue("sDDetail", EditHistory.strDDetail);
		pRs.GetFieldValue("sDDong", EditHistory.strDDong);

		pRs.GetFieldValue("sEtc", EditHistory.strEtc);
		pRs.GetFieldValue("sItemType", EditHistory.strItemType);
		pRs.GetFieldValue("nPayType", EditHistory.nPayType);
		pRs.GetFieldValue("nCarType", EditHistory.nCarType);
		pRs.GetFieldValue("nWayType", EditHistory.nWayType);
		pRs.GetFieldValue("nRunType", EditHistory.nRunType);

		pRs.GetFieldValue("nChargeAdd", EditHistory.nChargeAdd);
		pRs.GetFieldValue("nChargeBasic", EditHistory.nChargeBasic);
		pRs.GetFieldValue("nChargeTrans", EditHistory.nChargeTrans);
		pRs.GetFieldValue("nChargeDis", EditHistory.nChargeDis);
		pRs.GetFieldValue("nChargeSum", EditHistory.nChargeSum);
		pRs.GetFieldValue("nDeposit", EditHistory.nDeposit);
		pRs.GetFieldValue("nCouponCharge", EditHistory.nCouponCharge);
		pRs.GetFieldValue("sChargeBet", EditHistory.strChargeBet);
		pRs.GetFieldValue("nState", EditHistory.nState);
		pRs.GetFieldValue("nChargeReturn", EditHistory.nChargeReturn);
		pRs.GetFieldValue("nReserved" , EditHistory.nReserved);
		pRs.GetFieldValue("dtReserved" , EditHistory.dtReserved);

		pRs.GetFieldValue("nChargeDriving" , EditHistory.nChargeDriving);
		pRs.GetFieldValue("nShowPhoneTypeOrder" , EditHistory.nShowPhoneTypeOrder);
		pRs.GetFieldValue("nShowPhoneTypeStart" , EditHistory.nShowPhoneTypeStart);
		pRs.GetFieldValue("nShowPhoneTypeDest" , EditHistory.nShowPhoneTypeDest);
		pRs.GetFieldValue("nChargeCompany" , EditHistory.nChargeCompany);
		pRs.GetFieldValue("bFoodOrder" , EditHistory.bFoodOrder);
		pRs.GetFieldValue("dtFoodComplete" , EditHistory.dtFoodComplete);
		pRs.GetFieldValue("bAutoShareOrder" , EditHistory.bAutoShareOrder);
		pRs.GetFieldValue("nChargeRevision" , EditHistory.nChargeRevision);

		EditHistory.strOAddress.Trim();
		EditHistory.strSAddress.Trim();
		EditHistory.strDAddress.Trim();
 
		EditHistory.strOAddress.Replace("  ", " ");
		EditHistory.strSAddress.Replace("  ", " ");
		EditHistory.strDAddress.Replace("  ", " ");

		int nItem = 0; 

		EditHistory.item[nItem++] = EditHistory.strOName;
		EditHistory.item[nItem++] = EditHistory.strOPhone;
		EditHistory.item[nItem++] = EditHistory.strOMobile;
		EditHistory.item[nItem++] = EditHistory.strODepart;
		EditHistory.item[nItem++] = EditHistory.strOManager;
		EditHistory.item[nItem++] = EditHistory.strOAddress;
		EditHistory.item[nItem++] = EditHistory.strODetail;
		EditHistory.item[nItem++] = EditHistory.strODong;
		EditHistory.item[nItem++] = EditHistory.strOMemo;

		EditHistory.item[nItem++] = EditHistory.strSName;
		EditHistory.item[nItem++] = EditHistory.strSPhone;
		EditHistory.item[nItem++] = EditHistory.strSMobile;
		EditHistory.item[nItem++] = EditHistory.strSDepart;
		EditHistory.item[nItem++] = EditHistory.strSManager;
		EditHistory.item[nItem++] = EditHistory.strSAddress;
		EditHistory.item[nItem++] = EditHistory.strSDetail;
		EditHistory.item[nItem++] = EditHistory.strSDong;

		EditHistory.item[nItem++] = EditHistory.strDName;
		EditHistory.item[nItem++] = EditHistory.strDPhone;
		EditHistory.item[nItem++] = EditHistory.strDMobile;
		EditHistory.item[nItem++] = EditHistory.strDDepart;
		EditHistory.item[nItem++] = EditHistory.strDManager;
		EditHistory.item[nItem++] = EditHistory.strDAddress;
		EditHistory.item[nItem++] = EditHistory.strDDetail;
		EditHistory.item[nItem++] = EditHistory.strDDong;

		//CString [] = {"(��)����", "(��)��ȭ��ȣ", "(��)�޴���", "(��)�μ�", "(��)���", "(��)�ּ�", "(��)����ġ", "(��)���ص�", "(��)�޸�", 
		//	"(��)����", "(��)��ȭ��ȣ", "(��)�޴���", "(��)�μ�", "(��)���", "(��)�ּ�", "(��)����ġ", "(��)���ص�",
		//	"(��)����", "(��)��ȭ��ȣ", "(��)�޴���", "(��)�μ�", "(��)���", "(��)�ּ�", "(��)����ġ", "(��)���ص�",
		//	"����", "��ǰ", "����", "����", "���", "��", 
		//	"�߰�",	"�⺻", "Ź��", "����", "�հ�", "�Ա�", "����","����"}

		EditHistory.item[nItem++] = EditHistory.strEtc;
		EditHistory.item[nItem++] = EditHistory.strItemType;
		EditHistory.item[nItem++] = LF->GetPayTypeFromLong(EditHistory.nPayType);
		EditHistory.item[nItem++] = LF->GetCarTypeFromLong(EditHistory.nCarType);
		EditHistory.item[nItem++] = LF->GetWayTypeFromLong(EditHistory.nWayType);
		EditHistory.item[nItem++] = LF->GetRunTypeFromLong(EditHistory.nRunType);

		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeAdd);
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeBasic);
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeTrans);
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeDis);
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeSum);
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nDeposit);

		if(EditHistory.nCouponCharge < 100)
			EditHistory.item[nItem++] = "�ۼ�Ʈ : " + LF->GetMyNumberFormat(EditHistory.nCouponCharge);
		else
			EditHistory.item[nItem++] = "�ݾ� : " + LF->GetMyNumberFormat(EditHistory.nCouponCharge);

		EditHistory.item[nItem++] = EditHistory.strChargeBet;
		EditHistory.item[nItem++] = EditHistory.strSmsNumber;
		EditHistory.item[nItem++] = LF->GetStateString(EditHistory.nState);
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeReturn);
		EditHistory.item[nItem++] = GetReservedState(EditHistory.nReserved, EditHistory.dtReserved);

		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeDriving);
		EditHistory.item[nItem++] = EditHistory.nShowPhoneTypeOrder > 0 ? "üũ" : "üũ����";
		EditHistory.item[nItem++] = EditHistory.nShowPhoneTypeStart > 0 ? " üũ" : "üũ����";
		EditHistory.item[nItem++] = EditHistory.nShowPhoneTypeDest > 0 ? "üũ" : "üũ����";
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeCompany);
		EditHistory.item[nItem++] = GetFoodOrderState(EditHistory.bFoodOrder, EditHistory.dtFoodComplete);
		EditHistory.item[nItem++] = EditHistory.bAutoShareOrder > 0 ? "üũ" : "üũ����";
		EditHistory.item[nItem++] = LF->GetMyNumberFormat(EditHistory.nChargeRevision);
		
		m_EditHistoryMap[i] = EditHistory;

		pRs.MoveNext();
	}

	CompareMap();
}

CString COrderLogDetailDlg::GetFoodOrderState(BOOL bFoodOrder, COleDateTime dtFoodComplete)
{
	CString strTemp = "";
	
	strTemp += bFoodOrder == TRUE ? "Ǫ����O" : "Ǫ����X";

	if(bFoodOrder == TRUE && dtFoodComplete.m_status != 2)
		strTemp += dtFoodComplete.Format(" [%H��%M��]");

	return strTemp;
}


CString COrderLogDetailDlg::GetReservedState(long nReserved, COleDateTime dtReserved)
{
	CString strTemp = "";

	if(nReserved == 0)
		strTemp += "����(x)";
	else
	{
		strTemp.Format("����(%s)", dtReserved.Format("%m-%d %H:%M"));
	}

	return strTemp;
}


void COrderLogDetailDlg::CompareMap()
{
	CString sTitle[] = {"(��)����", "(��)��ȭ��ȣ", "(��)�޴���", "(��)�μ�", "(��)���", "(��)�ּ�", "(��)����ġ", "(��)���ص�", "(��)�޸�", "(��)����", 
				"(��)��ȭ��ȣ", "(��)�޴���", "(��)�μ�", "(��)���", "(��)�ּ�", "(��)����ġ", "(��)���ص�", "(��)����", "(��)��ȭ��ȣ", "(��)�޴���", 
				"(��)�μ�", "(��)���", "(��)�ּ�", "(��)����ġ", "(��)���ص�", "����", "��ǰ", "����", "����", "���",
				"��", "�߰�", "�⺻", "Ź��", "����", "�հ�", "�Ա�", "����", "����", "SMS��ȣ", 
				"����", "���ݳ���", "����", "�����", "��Ȳ��(�ܷ���)", "��Ȳ��(�����)", "��Ȳ��(������)", "��ü�δ��", "Ǫ����", "�����ڵ�����",
				"�������"};
//"���������","�����ѱݾ�","Ź����߽ð�", "Ź�۵����ð�","�����ȣ" 
	map<long, ST_EDIT_HISTORY>::iterator pos;
    
	CXTPGridRecord *pMainRecord = NULL;
	CXTPGridRecord *pSubMainRecord = NULL;

	int nColor = 0;

	for(pos = m_EditHistoryMap.begin(); pos != m_EditHistoryMap.end(); pos++)
	{
		bool bClick = TRUE; // Ŭ���� �ؼ� ������������
		bool bTreeHead = TRUE;

		map<long, ST_EDIT_HISTORY>::iterator pos1 = pos;
		pos1++;

		if(pos1 == m_EditHistoryMap.end())
			break;


		for(int i=0; i<COMPARE_STRING_COUNT; i++)
		{
			if(pos->second.item[i] != pos1->second.item[i])
			{
				if(bTreeHead)
				{
					pMainRecord = m_lstOrderChange.AddRecord(new COrderChangeRecord(m_cpColor[nColor].x, pos->second.nWNo, pos->second.strEditor, pos->second.nWCompany, pos->second.dtEdit,
						sTitle[i], pos->second.item[i], pos1->second.item[i], m_cpColor[nColor].y));
				}
				else 
					InsertChangeChildRecord(m_cpColor[nColor].x, sTitle[i], pos->second.item[i], pos1->second.item[i], pMainRecord, m_cpColor[nColor]);

				bClick = FALSE;
				bTreeHead = FALSE;
			}

		}

		if(bClick)
			m_lstOrderChange.AddRecord(new COrderChangeRecord(m_cpColor[nColor].x, pos->second.nWNo, pos->second.strEditor, pos->second.nWCompany, pos->second.dtEdit,
			"������������", "", "", m_cpColor[nColor].y));
	
		nColor++;
	}
}

void COrderLogDetailDlg::InsertChangeChildRecord(int nCount, CString sChange, CString sBefore, CString sAfter, CXTPGridRecord* pMainRecord, CPoint cpColor)
{
	pMainRecord->GetChilds()->Add(new COrderChangeRecord(nCount, sChange, sBefore, sAfter, cpColor.y));
	pMainRecord->SetExpanded(TRUE);
}

BOOL COrderLogDetailDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		OnCancel();
		return TRUE;
	}

	if(m_tooltip.GetSafeHwnd() && this->IsWindowVisible())
		m_tooltip.RelayEvent(pMsg);

	return CMyDialog::PreTranslateMessage(pMsg);
}

void COrderLogDetailDlg::OnBnClickedRiderInfoBtn()
{
	OnRiderInfo();
}

void COrderLogDetailDlg::OnBnClickedReAllocateBtn()
{
	OnReAllocate();
}

void COrderLogDetailDlg::OnRiderInfo()
{
	CXTPGridSelectedRows *pRows = m_lstOrderLog.GetSelectedRows();

	if(pRows == NULL) return;

	COrderLogRecord *pReport = (COrderLogRecord*)pRows->GetAt(0)->GetRecord();

	if((pReport->m_nRiderCompany == 0) || (pReport->m_nRNo == 0))
	{
		MessageBox("��������� �ִ� ���� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
//��⿡ ���ֻ� nCompany�� ��� ������
	LU->ShowRiderInfoDlg(pReport->m_nRiderCompany, pReport->m_nRNo, m_nOrderCompany);
}

void COrderLogDetailDlg::OnReAllocate()
{
	CXTPGridSelectedRows *pRows = m_lstOrderLog.GetSelectedRows();

	if(pRows == NULL) return;

	if(m_bCross)
	{
		MessageBox("ũ�ν� ������ ������ ����� �ϽǼ� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	COrderLogRecord *pReport = (COrderLogRecord*)pRows->GetAt(0)->GetRecord();

	if((pReport->m_nRiderCompany <= 0) || (pReport->m_nRNo <= 0) ||
		(pReport->m_nRiderCompany >= 100000) || (pReport->m_nRNo >= 65000))
	{
		MessageBox("��������� �ִ� ���� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
 
	if(MessageBox("����� �Ͻðڽ��ϱ�?", "Ȯ��", MB_ICONINFORMATION | MB_OKCANCEL) != IDOK)
		return;
 
	LU->GetRcpView()->GetStateChange()->Allocate(m_nTNo, pReport->m_nRNo, m_nState, pReport->m_nRiderCompany);	
	OnCancel();
	//m_pRcpView->Allocate(m_nTNo, pReport->m_nRNo, m_nState, 	pReport->m_nRiderCompany);	
}

void COrderLogDetailDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstOrderLog.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu; 
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(3);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void COrderLogDetailDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow/* || !pItemNotify->pColumn*/)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstOrderLog, pt);

}
void COrderLogDetailDlg::OnBnClickedRefreshBtn()
{
	ReFreshOrderLogReport(TRUE);
}
