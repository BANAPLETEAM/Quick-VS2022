// ProperChargeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ProperChargeDlg.h"
#include "ProperChargePaintManager.h"


// CProperChargeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CProperChargeDlg, CMyDialog)

CProperChargeDlg::CProperChargeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CProperChargeDlg::IDD, pParent)
{
	m_nStartID = 0;
	m_nDestID = 0;
}

CProperChargeDlg::~CProperChargeDlg()
{
	DeleteList();
}

void CProperChargeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CONTROL, m_lstReport);
	DDX_Control(pDX, IDC_CHARE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_PROPER_CHARGE_EDIT1, m_edtProperCharge);
	DDX_Control(pDX, IDC_PROPER_CHARGE_EDIT2, m_edtProperCharge2);
	DDX_Control(pDX, IDC_CAR_TYPE_COMBO, m_cmbCarType);
}


BEGIN_MESSAGE_MAP(CProperChargeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CProperChargeDlg::OnBnClickedCloseBtn)

	ON_EN_CHANGE(IDC_EDIT1, &CProperChargeDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_SELECT_BTN1, &CProperChargeDlg::OnBnClickedSelectBtn1)
	ON_BN_CLICKED(IDC_SELECT_BTN2, &CProperChargeDlg::OnBnClickedSelectBtn2)
	ON_CBN_SELCHANGE(IDC_CAR_TYPE_COMBO, &CProperChargeDlg::OnCbnSelchangeCarTypeCombo)
END_MESSAGE_MAP()

void CProperChargeDlg::DeleteList()
{
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();
	long nCount = pRecords->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CProperChargeReportRecord *pRecord = (CProperChargeReportRecord*)pRecords->GetAt(i);
		delete pRecord->m_st;
		pRecord->m_st = NULL;
	}

	m_lstReport.GetRecords()->RemoveAll();
	m_lstReport.Populate();
}

void CProperChargeDlg::SetCarTypeIndex()
{
	long nIndex = m_cmbCarType.GetCurSel();

	if(nIndex == 0)
		m_nCarType = 0;
	else if(nIndex == 1)
		m_nCarType = 2;
	else if(nIndex == 2)
		m_nCarType = 4;
	else if(nIndex == 3)
		m_nCarType = 5;
}

long CProperChargeDlg::GetCarTypeIndex()
{
	long nIndex = 0;

	if(m_nCarType == 0 || m_nCarType == 1)
		nIndex = 0;
	else if(m_nCarType == 2 || m_nCarType == 3)
		nIndex = 1;
	else if(m_nCarType == 4)
		nIndex = 2;
	else if(m_nCarType == 5 || m_nCarType == 9)
		nIndex = 3;
	
	m_cmbCarType.SetCurSel(nIndex);
	return 0;
}
// CProperChargeDlg 메시지 처리기입니다.

BOOL CProperChargeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtCharge.SetWindowText(LF->GetMyNumberFormat(m_nCharge));
	m_edtProperCharge.SetWindowText(LF->GetMyNumberFormat(m_nProperCharge1));
	m_edtProperCharge2.SetWindowText(LF->GetMyNumberFormat(m_nProperCharge2));
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_pReportPaint = new CProperChargePaintManager;
	m_lstReport.SetPaintManager(m_pReportPaint);
	m_lstReport.SetTreeIndent(10);
	m_lstReport.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_lstReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstReport.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstReport.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstReport.AllowEdit(FALSE);
	m_lstReport.FocusSubItems(FALSE);
	m_lstReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstReport.SetGridColor(RGB(150, 150, 180));
	//m_pReportPaint->m_nCarType = m_nCarType;

	GetCarTypeIndex();

	CXTPGridColumn *p1 = m_lstReport.AddColumn(new CXTPGridColumn(0, _T("금액"), 70, FALSE));
	p1->SetEditable(FALSE);
	p1 = m_lstReport.AddColumn(new CXTPGridColumn(1, _T("전체"), 85));
	p1->SetEditable(FALSE);
	p1 = m_lstReport.AddColumn(new CXTPGridColumn(2, "오토/짐받이", 75)); 
	p1->SetEditable(FALSE); 
	p1 = m_lstReport.AddColumn(new CXTPGridColumn(3, "다마/라보", 75)); 
	p1->SetEditable(FALSE);
	p1 = m_lstReport.AddColumn(new CXTPGridColumn(4, "밴", 75)); 
	p1->SetEditable(FALSE);
	p1 = m_lstReport.AddColumn(new CXTPGridColumn(5, "트럭/1.4톤", 75)); 
	p1->SetEditable(FALSE);

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CProperChargeDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CProperChargeDlg::RefreshList()
{	
	SetHilight();
	DeleteList();
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_proper_charge_detail");
	cmd.AddParameter(m_nStartID);
	cmd.AddParameter(m_nDestID);
	cmd.AddParameter(m_nCarType);

	if(!rs.Execute(&cmd)) 
		return;

	for(int i=0; i< rs.GetRecordCount(); i++)
	{
		ST_PROPER_CHARGE * st = new ST_PROPER_CHARGE;

		rs.GetFieldValue("nCharge", st->nCharge);
		rs.GetFieldValue("nTotalCount", st->nTotalCount);
		rs.GetFieldValue("nCancelCount", st->nCancelCount);
		rs.GetFieldValue("nTotalCountCarType0", st->nTotalCountCarType0);
		rs.GetFieldValue("nCancelCountCarType0", st->nCancelCountCarType0);
		rs.GetFieldValue("nTotalCountCarType2", st->nTotalCountCarType2);
		rs.GetFieldValue("nCancelCountCarType2", st->nCancelCountCarType2);
		rs.GetFieldValue("nTotalCountCarType4", st->nTotalCountCarType4);
		rs.GetFieldValue("nCancelCountCarType4", st->nCancelCountCarType4);
		rs.GetFieldValue("nTotalCountCarType5", st->nTotalCountCarType5);
		rs.GetFieldValue("nCancelCountCarType5", st->nCancelCountCarType5);

		m_lstReport.AddRecord(new CProperChargeReportRecord(st));  
		rs.MoveNext();

		if(i >= 8)
			break;
	}	

	m_lstReport.Populate();
}


void CProperChargeDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CMyDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CProperChargeDlg::OnBnClickedSelectBtn1()
{
	m_nProperCharge = LF->GetLongFromEdit(&m_edtProperCharge);
	OnOK();
}

void CProperChargeDlg::OnBnClickedSelectBtn2()
{
	m_nProperCharge = LF->GetLongFromEdit(&m_edtProperCharge2);
	OnOK();
}

void CProperChargeDlg::OnCbnSelchangeCarTypeCombo()
{
	SetCarTypeIndex();
	RefreshList();
}

void CProperChargeDlg::SetHilight()
{
	long nHilightol = -1;

	if(m_nCarType == 0 || m_nCarType == 1)
		nHilightol = 2;
	else if(m_nCarType == 2 || m_nCarType == 3)
		nHilightol = 3;
	else if(m_nCarType == 4)
		nHilightol = 4;
	else if(m_nCarType == 5 || m_nCarType == 9)
		nHilightol = 5;

	m_pReportPaint->SetHilightCol(nHilightol);
};