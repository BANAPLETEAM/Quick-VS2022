// BillDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "FoodCompleteDlg.h"


// CFoodCompleteDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFoodCompleteDlg, CMyDialog)
CFoodCompleteDlg::CFoodCompleteDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CFoodCompleteDlg::IDD, pParent)
{
	m_bFoodOrder = FALSE;
	m_dtFoodComplete = COleDateTime::GetCurrentTime();
}

CFoodCompleteDlg::~CFoodCompleteDlg()
{
}

void CFoodCompleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FOOD_ORDER_CHECK, m_chkFoodOrder);
	DDX_Control(pDX, IDC_RESERVE_DATE_DTP, m_dtpDate);
	DDX_Control(pDX, IDC_RESERVE_TIME_DTP, m_dtpTime);
	DDX_Control(pDX, IDC_ADD_TIME_COMBO, m_cmbAddTime);	
}


BEGIN_MESSAGE_MAP(CFoodCompleteDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_ADD_TIME_COMBO, OnCbnSelchangeAddTimeCombo)
END_MESSAGE_MAP()


// CFoodCompleteDlg 메시지 처리기입니다.

void CFoodCompleteDlg::OnCbnSelchangeAddTimeCombo()
{
	long nIndex = m_cmbAddTime.GetCurSel();
	long nTime = m_cmbAddTime.GetItemData(nIndex);

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	dtCur = dtCur + COleDateTimeSpan(0, 0, nTime, 0);

	m_dtpDate.SetTime(dtCur);
	m_dtpTime.SetTime(dtCur);
}

BOOL CFoodCompleteDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	CenterWindow();

	COleDateTime dtTime = COleDateTime::GetCurrentTime();

	if(m_bFoodOrder)
	{
		dtTime  = m_dtFoodComplete;
		m_chkFoodOrder.SetCheck(TRUE);
	}

	m_dtpDate.SetTime(dtTime );
	m_dtpDate.SetFormat("yyyy-MM-dd");
	m_dtpDate.SetFont(m_FontManager.GetFont("맑은 고딕", 16, FW_NORMAL));

	m_dtpDate.SetTime(dtTime );
	m_dtpTime.SetTime(dtTime );
	m_dtpTime.SetFormat("HH:mm");
	m_dtpTime.SetFont(m_FontManager.GetFont("맑은 고딕", 16, FW_NORMAL));

	m_cmbAddTime.InsertString(0, "빠른입력"); m_cmbAddTime.SetItemData(0, 0);
	m_cmbAddTime.InsertString(1, "5분후"); m_cmbAddTime.SetItemData(1, 5);
	m_cmbAddTime.InsertString(2, "10분후"); m_cmbAddTime.SetItemData(2, 10);
	m_cmbAddTime.InsertString(3, "15분후"); m_cmbAddTime.SetItemData(3, 15);
	m_cmbAddTime.InsertString(4, "20분후"); m_cmbAddTime.SetItemData(4, 20);
	m_cmbAddTime.InsertString(5, "25분후"); m_cmbAddTime.SetItemData(5, 25);
	m_cmbAddTime.InsertString(6, "30분후"); m_cmbAddTime.SetItemData(6, 30);
	m_cmbAddTime.InsertString(7, "35분후"); m_cmbAddTime.SetItemData(7, 35);
	m_cmbAddTime.InsertString(8, "40분후"); m_cmbAddTime.SetItemData(8, 40);
	m_cmbAddTime.InsertString(9, "45분후"); m_cmbAddTime.SetItemData(9, 45);
	m_cmbAddTime.InsertString(10, "50분후"); m_cmbAddTime.SetItemData(10, 50);
	m_cmbAddTime.InsertString(11, "55분후"); m_cmbAddTime.SetItemData(11, 55);
	m_cmbAddTime.InsertString(12, "1시간후"); m_cmbAddTime.SetItemData(12, 60);

	m_cmbAddTime.SetCurSel(0);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CFoodCompleteDlg::OnBnClickedOk()
{
	m_bFoodOrder = m_chkFoodOrder.GetCheck();

	COleDateTime dtDate, dtTime;

	m_dtpDate.GetTime(dtDate);
	m_dtpTime.GetTime(dtTime);

	m_dtFoodComplete = COleDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), dtTime.GetHour(), dtTime.GetMinute(), dtTime.GetSecond());
	OnOK();
}

void CFoodCompleteDlg::OnBnClickedCancel()
{
	OnCancel();
}