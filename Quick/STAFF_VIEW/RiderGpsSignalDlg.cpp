// RiderGpsSignalDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderGpsSignalDlg.h"

#include "RGSPaintManager.h"


// CRiderGpsSignalDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderGpsSignalDlg, CMyDialog)
CRiderGpsSignalDlg::CRiderGpsSignalDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderGpsSignalDlg::IDD, pParent)
{
}

CRiderGpsSignalDlg::~CRiderGpsSignalDlg()
{
}

void CRiderGpsSignalDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
}


BEGIN_MESSAGE_MAP(CRiderGpsSignalDlg, CMyDialog)
END_MESSAGE_MAP()


// CRiderGpsSignalDlg 메시지 처리기입니다.

BOOL CRiderGpsSignalDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	m_pRGS = new CRGSPaintManager;
	m_wndReport.SetPaintManager(m_pRGS);
	m_wndReport.SetTreeIndent(10);
	m_wndReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(FALSE);
	m_wndReport.FocusSubItems(FALSE);
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	//m_wndReport.GetPaintManager()->SetTextFont(lfBoldFont);
	m_wndReport.SetGridColor(RGB(150, 150, 180));

	CXTPGridColumn *p1 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("번호"), 50, FALSE));
	p1->SetEditable(FALSE);
	p1 = m_wndReport.AddColumn(new CXTPGridColumn(1, _T("이름"), 70));
	p1->SetEditable(FALSE);
	p1 = m_wndReport.AddColumn(new CXTPGridColumn(2, _T("신호"), 600));
	p1->SetEditable(FALSE);


	RefreshRiderList();
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderGpsSignalDlg::RefreshRiderList()
{
	m_pRGS->m_mapSignal.clear();
	m_wndReport.GetRecords()->RemoveAll();
	
	CMkCommand pCmd(m_pMkDb, "select_simple_rider_list");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(TRUE);
	CMkRecordset pRs(m_pMkDb);
	if(pRs.Execute(&pCmd))
	{
		long nCompany, nMNo;
		CString strName;


		m_wndReport.AddRecord(new CRGSReportRecord(0, 0, "시각"));


		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			pRs.GetFieldValue("lCode", nCompany);
			pRs.GetFieldValue("nMNo", nMNo);
			pRs.GetFieldValue("sName", strName);

			m_wndReport.AddRecord(new CRGSReportRecord(nCompany, nMNo, strName));

			SIGNAL_VECTOR vecSignal;
			m_pRGS->m_mapSignal.insert(SIGNAL_MAP::value_type(make_pair(nCompany, nMNo), 
				vecSignal));

			pRs.MoveNext();
		}
	}
	m_wndReport.Populate();
}

void CRiderGpsSignalDlg::RefreshList()
{

	CMkCommand pCmd(m_pMkDb, "select_gps_signal_info");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(TRUE);
	CMkRecordset pRs(m_pMkDb);
	if(pRs.Execute(&pCmd))
	{
		long nCompany, nRNo, nCount;
		COleDateTime dtMin;
		SIGNAL_MAP::iterator it;

		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nRNo", nRNo);
			pRs.GetFieldValue("dtMin", dtMin);
			pRs.GetFieldValue("nCount", nCount);

			it = m_pRGS->m_mapSignal.find(make_pair(nCompany, nRNo));
			if(it != m_pRGS->m_mapSignal.end())
			{
				SIGNAL_DATA sd;
				sd.dtMin = dtMin;
				sd.nCount = nCount;
				it->second.push_back(sd);
			}
		
			pRs.MoveNext();
		}
	}
}


