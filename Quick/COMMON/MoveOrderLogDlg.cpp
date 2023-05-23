// MoveOrderLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MoveOrderLogDlg.h"
#include "MakeHtmlTable.h"


// CMoveOrderLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMoveOrderLogDlg, CMyDialog)
CMoveOrderLogDlg::CMoveOrderLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMoveOrderLogDlg::IDD, pParent)
	, m_FromDt(COleDateTime::GetCurrentTime())
	, m_ToDt(COleDateTime::GetCurrentTime())
{
}

CMoveOrderLogDlg::~CMoveOrderLogDlg()
{
}

void CMoveOrderLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDtCtl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDtCtl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_FromDt);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_ToDt);
}


BEGIN_MESSAGE_MAP(CMoveOrderLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_NOTIFY (UDM_TOOLTIP_DISPLAY, NULL, NotifyDisplayTooltip)
END_MESSAGE_MAP()


// CMoveOrderLogDlg 메시지 처리기입니다.

BOOL CMoveOrderLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList;
	ImageList.Create(1,17,ILC_COLOR,1,1); 

	m_wndReport.InsertColumn(0,"No",LVCFMT_LEFT,30);
	m_wndReport.InsertColumn(1,"발생일",LVCFMT_LEFT,130);
	m_wndReport.InsertColumn(2,"오더번호",LVCFMT_LEFT,65);
	m_wndReport.InsertColumn(3,"출발동",LVCFMT_LEFT,65);
	m_wndReport.InsertColumn(4,"도착동",LVCFMT_LEFT,65);
	m_wndReport.InsertColumn(5,"이전회사",LVCFMT_LEFT,90);
	m_wndReport.InsertColumn(6,"현재회사",LVCFMT_LEFT,90);
	m_wndReport.InsertColumn(7,"수정자",LVCFMT_LEFT,50);
	m_wndReport.InsertColumn(8,"소속회사",LVCFMT_LEFT,90);

	m_FromDtCtl.SetFormat("yyyy-MM-dd HH:00");
	m_ToDtCtl.SetFormat("yyyy-MM-dd HH:00");

	m_DateBtn.InitDateButton((CDateTimeCtrl*)&m_FromDtCtl, (CDateTimeCtrl*)&m_ToDtCtl);
	m_DateBtn.OnMenuToday();

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

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMoveOrderLogDlg::RefreshList()
{
	UpdateData(TRUE);
	m_wndReport.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_move_order_log_1");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_FromDt);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), m_ToDt);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtGenerate;
	long nFromCompany, nToCompany, nWNo, nWCompany;
	CString strWName;

	for(int i=0 ; i<pRs.GetRecordCount(); i++)
	{
		MOVE_ORDER_STRUCT st;

        pRs.GetFieldValue("nTNo", st.nTNo);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("nFromCompany", nFromCompany);
		pRs.GetFieldValue("nToCompany", nToCompany);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nWCompany", nWCompany);
		pRs.GetFieldValue("sWName", strWName);

		pRs.GetFieldValue("dt1", st.dt1);
		pRs.GetFieldValue("dtFinal", st.dtFinal);
		pRs.GetFieldValue("sSDong", st.sStart);
		pRs.GetFieldValue("sDDong", st.sDest);
		pRs.GetFieldValue("nChargeSum", st.nChare);
		pRs.GetFieldValue("nRNo", st.nRNo);
		pRs.GetFieldValue("nRiderCompany", st.nRiderCompany);
		pRs.GetFieldValue("nState", st.nState);

		if(strWName.GetLength() > 0)
			strWName = CString("(") + strWName + (")");

		m_wndReport.InsertItem(i, LF->GetStringFromLong(i + 1));
		m_wndReport.SetItemText(i, 1, dtGenerate.Format("%Y-%m-%d %H:%M:%S"));
		m_wndReport.SetItemText(i, 2, LF->GetStringFromLong(st.nTNo));
		m_wndReport.SetItemText(i, 3, st.sStart);
		m_wndReport.SetItemText(i, 4, st.sDest);
		m_wndReport.SetItemText(i, 5, m_ci.GetBranchName(nFromCompany));
		m_wndReport.SetItemText(i, 6, m_ci.GetBranchName(nToCompany));
		m_wndReport.SetItemText(i, 7, LF->GetStringFromLong(nWNo) + strWName);
		m_wndReport.SetItemText(i, 8, m_ci.GetBranchName(nWCompany));
		m_wndReport.SetItemData(i, long(i));

		m_map[i] = st;

		pRs.MoveNext();
	}

	m_wndReport.Populate();
}

void CMoveOrderLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

BOOL CMoveOrderLogDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);

	return CMyDialog::PreTranslateMessage(pMsg);
}


void CMoveOrderLogDlg::NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result)
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
		if (IDC_REPORT_CTRL == nID)
		{
			m_wndReport.GetWindowRect(&rcCtrl);
			pt -= rcCtrl.TopLeft();
			CXTPGridRow *pRow = m_wndReport.HitTest(pt);
			if(pRow)
			{
				CXTPGridColumn *pCol = NULL;
				pRow->HitTest(pt, &rcCol, &pCol);

				MOVE_ORDER_MAP::iterator it;
				CMakeHtmlTable htable;

				long nItem = m_wndReport.GetItemData(pRow->GetIndex());
				char buffer[20];

				for(it = m_map.begin(); it != m_map.end(); it++)
				{
					if(it->first == nItem)
					{
						htable.AddCol("오더번호");
						htable.AddCol(itoa(it->second.nTNo, buffer, 10));
						htable.AddRow();

						htable.AddCol("접수시간");
						htable.AddCol(it->second.dt1.Format("%m-%d %H:%S"));
						htable.AddRow();

						htable.AddCol("종료시간");
						htable.AddCol(it->second.dtFinal.Format("%m-%d %H:%S"));
						htable.AddRow();

						htable.AddCol("출발지");
						htable.AddCol(it->second.sStart);
						htable.AddRow();

						htable.AddCol("도착지");
						htable.AddCol(it->second.sDest);
						htable.AddRow();

						htable.AddCol("요금");
						htable.AddCol(LF->GetMyNumberFormat(it->second.nChare));
						htable.AddRow();

						htable.AddCol("기사번호");
						htable.AddCol(itoa(it->second.nRNo, buffer, 10));
						htable.AddRow();

						htable.AddCol("소속회사");
						htable.AddCol(m_ci.GetBranchName(it->second.nRiderCompany));
						htable.AddRow();

						htable.AddCol("상태");
						htable.AddCol(LF->GetStateString(it->second.nState));
						htable.AddRow();

						CString strTitle;
						strTitle.Format("오더내용");
						htable.SetTitle(strTitle);
						htable.SetTableBorder(1);
						pNotify->ti->sTooltip = htable.GetHtmlTable();
						pt = *pNotify->pt;
						pt.x += 5;
						pt.y += 20;
						*pNotify->pt = pt;	

						break;
					}
				}
			}

		} //if
	} //if
} //End NotifyDisplayTooltip