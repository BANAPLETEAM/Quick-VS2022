// ChangeAllocGroupInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "ChangeAllocGroupInfoDlg.h"
#include ".\changeallocgroupinfodlg.h"
#include "ChangeAllocGroupInfoLogDlg.h"
#include "LogiUtil.h"

// CChangeAllocGroupInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChangeAllocGroupInfoDlg, CMyDialog)
CChangeAllocGroupInfoDlg::CChangeAllocGroupInfoDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChangeAllocGroupInfoDlg::IDD, pParent)
	, m_bUseAutoDownGrade(FALSE)
	, m_bNotUseAutoDownGrade(FALSE)
	, m_bDownGradeOnlyMyCall(FALSE)
{
	m_nGroupAllocID = 0;
	m_nCompany = 0;
}

CChangeAllocGroupInfoDlg::~CChangeAllocGroupInfoDlg()
{
}

void CChangeAllocGroupInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALLOC_GROUP_NAME_EDIT, m_edtAllocGroupName);
	DDX_Control(pDX, IDC_ORDER_DELAY_COMBO, m_cmbOrderDelay);
	DDX_Control(pDX, IDC_MY_ORDER_DELAY_COMBO, m_cmbMyOrderDelay);
	DDX_Control(pDX, IDC_OTHER_ORDER_DELAY_COMBO, m_cmbOtherOrderDelay);
	DDX_Control(pDX, IDC_MY_CORP_ORDER_DELAY_COMBO, m_cmbMyCorpOrderDelay);
	DDX_Control(pDX, IDC_SHOW_ORDER_COMBO, m_cmbShowOrder);
	DDX_Control(pDX, IDC_USE_AUTO_ALLOC_CHECK, m_chkUseAutoAlloc);
	DDX_Control(pDX, IDC_NOT_USE_AUTO_ALLOC_CHECK, m_chkNotUseAutoAlloc);
	DDX_Control(pDX, IDC_USE_AUTO_GRADE_CHECK, m_chkUseAutoGrade);
	DDX_Control(pDX, IDC_NOT_USE_AUTO_GRADE_CHECK, m_chkNotUseAutoGrade);
	DDX_Control(pDX, IDC_ALLOC_GRADE_EDT, m_edtAllocGrade);
	DDX_Control(pDX, IDC_USE_DOWN_GRADE_CHECK, m_chkUseDownGrade);
	DDX_Control(pDX, IDC_NOT_USE_DOWN_GRADE_CHECK, m_chkNotUseDownGrade);
	DDX_Check(pDX, IDC_USE_DOWN_GRADE_CHECK, m_bUseAutoDownGrade);
	DDX_Check(pDX, IDC_NOT_USE_DOWN_GRADE_CHECK, m_bNotUseAutoDownGrade);
	DDX_Control(pDX, IDC_DOWN_GRADE_DAY_COMBO, m_cmbDownGradeDay);
	DDX_Control(pDX, IDC_DOWN_GRADE_COUNT_COMBO, m_cmbDownGradeCount);

	DDX_Control(pDX, IDC_TEXT_COLOR_BTN, m_btnTextColor);
	DDX_Control(pDX, IDC_BACK_COLOR_BTN, m_btnBackColor);
	DDX_Control(pDX, IDC_DOWN_GRADE_ONLY_MY_CALL_CHEKC, m_chkDownGradeOnlyMyCall);
	DDX_Check(pDX, IDC_DOWN_GRADE_ONLY_MY_CALL_CHEKC, m_bDownGradeOnlyMyCall);
}


BEGIN_MESSAGE_MAP(CChangeAllocGroupInfoDlg, CMyDialog)
	ON_CPN_XT_SELENDOK(IDC_TEXT_COLOR_BTN, OnSelEndOkTextColor)
	ON_CPN_XT_SELENDOK(IDC_BACK_COLOR_BTN, OnSelEndOkBackColor)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_EDIT_LOG_BTN, OnBnClickedEditLogBtn)
	ON_BN_CLICKED(IDC_USE_AUTO_ALLOC_CHECK, OnBnClickedUseAutoAllocCheck)
	ON_BN_CLICKED(IDC_NOT_USE_AUTO_ALLOC_CHECK, OnBnClickedNotUseAutoAllocCheck)
	ON_BN_CLICKED(IDC_USE_AUTO_GRADE_CHECK, OnBnClickedUseAutoGradeCheck)
	ON_BN_CLICKED(IDC_NOT_USE_AUTO_GRADE_CHECK, OnBnClickedNotUseAutoGradeCheck)
	
	ON_BN_CLICKED(IDC_USE_DOWN_GRADE_CHECK, &CChangeAllocGroupInfoDlg::OnBnClickedUseDownGradeCheck)
	ON_BN_CLICKED(IDC_NOT_USE_DOWN_GRADE_CHECK, &CChangeAllocGroupInfoDlg::OnBnClickedNotUseDownGradeCheck)
	ON_CBN_SELCHANGE(IDC_MY_ORDER_DELAY_COMBO, &CChangeAllocGroupInfoDlg::OnCbnSelchangeMyOrderDelayCombo)
END_MESSAGE_MAP()


// CChangeAllocGroupInfoDlg 메시지 처리기입니다.

BOOL CChangeAllocGroupInfoDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	LF->MakeModaless();
	CenterWindow();
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChangeAllocGroupInfoDlg::RefreshList()
{
	CMkRecordset rs(m_pMkDb); 
	CMkCommand cmd(m_pMkDb, "select_alloc_group_by_group_id");
	cmd.AddParameter(m_nGroupAllocID);
	cmd.AddParameter(m_nCompany);
	CMkParameter *pPar = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	long nCompanyAutoAllocType;

	if(!rs.Execute(&cmd)) return;
	pPar->GetValue(nCompanyAutoAllocType);

	long nGrade, nPanaltyDelayTime4Order, nPanaltyDelayTime4MyOrder, nPanaltyDelayTime4OCOrder, nPanaltyTypeShowOrder;
	long nPenaltyDelayTime4MyCorpOrder;
	CString strGroupName;
	BOOL bAutoAllocType, bAutoGradeAdjByLogic, bAutoDownGrade;
	long nAutoDownGradeDay, nAutoDownGradeCount, nAutoDownGradeOnlyMyCall;
	long nTextColor = 0, nBackColor = 0;

	rs.GetFieldValue("nGrade", nGrade);
	rs.GetFieldValue("nPanaltyDelayTime4Order", nPanaltyDelayTime4Order);
	rs.GetFieldValue("nPanaltyDelayTime4MyOrder", nPanaltyDelayTime4MyOrder);
	rs.GetFieldValue("nPanaltyDelayTime4OCOrder", nPanaltyDelayTime4OCOrder);
	rs.GetFieldValue("nPanaltyTypeShowOrder", nPanaltyTypeShowOrder);
	rs.GetFieldValue("nPenaltyDelayTime4MyCorpOrder", nPenaltyDelayTime4MyCorpOrder);
	rs.GetFieldValue("sGroupName", strGroupName);
	rs.GetFieldValue("bAutoAllocType", bAutoAllocType);
	rs.GetFieldValue("bAutoGradeAdjByLogic", bAutoGradeAdjByLogic); 
	rs.GetFieldValue("bAutoDownGrade", bAutoDownGrade); 
	rs.GetFieldValue("nAutoDownGradeDay", nAutoDownGradeDay); 
	rs.GetFieldValue("nAutoDownGradeCount", nAutoDownGradeCount); 
	rs.GetFieldValue("nTextColor", nTextColor); 
	rs.GetFieldValue("nBackColor", nBackColor);
	rs.GetFieldValue("nAutoDownGradeOnlyMyCall", nAutoDownGradeOnlyMyCall);

	if(nTextColor == nBackColor)
	{
		m_btnBackColor.SetColor(RGB(255, 255, 255));
		m_btnTextColor.SetColor(RGB(0, 0, 0));
		m_edtAllocGroupName.SetUserBkColor(RGB(255, 255, 255));
		m_edtAllocGroupName.SetUserTextColor(nTextColor);
	}
	else
	{
		m_btnBackColor.SetColor(nBackColor);
		m_btnTextColor.SetColor(nTextColor);
		m_edtAllocGroupName.SetUserBkColor(nBackColor);
		m_edtAllocGroupName.SetUserTextColor(nTextColor);
	}

	m_edtAllocGrade.SetWindowText(LF->GetStringFromLong(nGrade) + " 등급");
	m_edtAllocGroupName.SetWindowText(strGroupName);
	m_cmbOrderDelay.SetWindowText(LF->GetStringFromLong(nPanaltyDelayTime4Order));
	m_cmbMyOrderDelay.SetWindowText(LF->GetStringFromLong(nPanaltyDelayTime4MyOrder));
	m_cmbOtherOrderDelay.SetWindowText(LF->GetStringFromLong(nPanaltyDelayTime4OCOrder));
	m_cmbMyCorpOrderDelay.SetWindowText(LF->GetStringFromLong(nPenaltyDelayTime4MyCorpOrder));
	m_cmbShowOrder.SetCurSel(nPanaltyTypeShowOrder);

	m_chkUseAutoAlloc.SetCheck(bAutoAllocType);
	m_chkNotUseAutoAlloc.SetCheck(!bAutoAllocType);

	m_chkUseAutoGrade.SetCheck(bAutoGradeAdjByLogic);
	m_chkNotUseAutoGrade.SetCheck(!bAutoGradeAdjByLogic);

	m_chkUseDownGrade.SetCheck(bAutoDownGrade);
	m_chkNotUseDownGrade.SetCheck(!bAutoDownGrade);

	m_cmbDownGradeDay.SetWindowText(LF->GetStringFromLong(nAutoDownGradeDay));
	m_cmbDownGradeCount.SetWindowText(LF->GetStringFromLong(nAutoDownGradeCount));
	m_chkDownGradeOnlyMyCall.SetCheck(nAutoDownGradeOnlyMyCall);

	if(nCompanyAutoAllocType <= 0) 
	{
		m_chkUseAutoAlloc.EnableWindow(FALSE); //회사가 자동배차 사용해야함
		m_chkNotUseAutoAlloc.EnableWindow(FALSE);
	} 

	OnBnClickedUseDownGradeCheck();
}

void CChangeAllocGroupInfoDlg::OnBnClickedOk()
{
	CString strTemp;
	m_edtAllocGroupName.GetWindowText(m_strGroupName);
	m_cmbOrderDelay.GetWindowText(strTemp); m_nPanaltyDelayTime4Order = atoi(strTemp);
	m_cmbMyOrderDelay.GetWindowText(strTemp); m_nPanaltyDelayTime4MyOrder = atoi(strTemp);
	m_cmbOtherOrderDelay.GetWindowText(strTemp); m_nPanaltyDelayTime4OCOrder = atoi(strTemp);
	m_cmbMyCorpOrderDelay.GetWindowText(strTemp); m_nPenaltyDelayTime4MyCorpOrder = atoi(strTemp);
	m_nPanaltyTypeShowOrder = m_cmbShowOrder.GetCurSel();
	
	if(m_chkUseAutoAlloc.GetCheck())
		m_bAutoAllocType = TRUE;
	else
		m_bAutoAllocType = FALSE;

	if(m_chkUseAutoGrade.GetCheck())
		m_bAutoGradeAdjByLogic = TRUE;
	else
		m_bAutoGradeAdjByLogic = FALSE;

	if(m_chkUseDownGrade.GetCheck())
	{
		m_bUseAutoDownGrade = TRUE;
		m_cmbDownGradeDay.GetWindowText(strTemp); m_nDownGradeDay = atoi(strTemp);
		m_cmbDownGradeCount.GetWindowText(strTemp); m_nDownGradeCount = atoi(strTemp);
		m_bDownGradeOnlyMyCall = m_chkDownGradeOnlyMyCall.GetCheck();

		if(m_nDownGradeDay == 0) {MessageBox("[자동등급하향] 기능을 사용하시려면 0일 이상으로 입력해주세요", "확인", MB_ICONINFORMATION); return;}
		if(m_nDownGradeCount == 0) {MessageBox("[자동등급하향] 기능을 사용하시려면 0건 이상으로 입력해주세요", "확인", MB_ICONINFORMATION); return;}	
	}
	else
	{
		m_bUseAutoDownGrade = FALSE;
		m_nDownGradeDay = 0;
		m_nDownGradeCount = 0;
		m_bDownGradeOnlyMyCall = FALSE;
	}

	m_clrBack = m_btnBackColor.GetColor();
	m_clrText = m_btnTextColor.GetColor();

	OnOK();
}

void CChangeAllocGroupInfoDlg::OnBnClickedEditLogBtn()
{
	CChangeAllocGroupInfoLogDlg dlg; 
	dlg.m_nGroupAllocID = m_nGroupAllocID;
	dlg.DoModal();
}

void CChangeAllocGroupInfoDlg::OnBnClickedUseAutoAllocCheck()
{
	if(m_chkUseAutoAlloc.GetCheck())
		m_chkNotUseAutoAlloc.SetCheck(FALSE);
	else
		m_chkNotUseAutoAlloc.SetCheck(TRUE);
}

void CChangeAllocGroupInfoDlg::OnBnClickedNotUseAutoAllocCheck()
{
	if(m_chkNotUseAutoAlloc.GetCheck())
		m_chkUseAutoAlloc.SetCheck(FALSE);
	else
		m_chkNotUseAutoAlloc.SetCheck(TRUE);
}

void CChangeAllocGroupInfoDlg::OnBnClickedUseAutoGradeCheck()
{
	if(m_chkUseAutoGrade.GetCheck())
		m_chkNotUseAutoGrade.SetCheck(FALSE);
	else
		m_chkNotUseAutoGrade.SetCheck(TRUE);
}

void CChangeAllocGroupInfoDlg::OnBnClickedNotUseAutoGradeCheck()
{
	if(m_chkNotUseAutoGrade.GetCheck())
		m_chkUseAutoGrade.SetCheck(FALSE);
	else
		m_chkUseAutoGrade.SetCheck(TRUE);
}

void CChangeAllocGroupInfoDlg::OnBnClickedUseDownGradeCheck()
{
	if(m_chkUseDownGrade.GetCheck())
		m_chkNotUseDownGrade.SetCheck(FALSE);
	else
		m_chkNotUseDownGrade.SetCheck(TRUE); 

	EnableControl();
}

void CChangeAllocGroupInfoDlg::OnBnClickedNotUseDownGradeCheck()
{
	if(m_chkNotUseDownGrade.GetCheck())
		m_chkUseDownGrade.SetCheck(FALSE);
	else
		m_chkUseDownGrade.SetCheck(TRUE);

	EnableControl();
}

void CChangeAllocGroupInfoDlg::EnableControl()
{
	BOOL bEnable = m_chkUseDownGrade.GetCheck();

	m_cmbDownGradeDay.EnableWindow(bEnable);
	m_cmbDownGradeCount.EnableWindow(bEnable);
	m_chkDownGradeOnlyMyCall.EnableWindow(bEnable);
}

void CChangeAllocGroupInfoDlg::OnSelEndOkTextColor()
{
	m_edtAllocGroupName.SetUserTextColor(m_btnTextColor.GetColor());
	m_edtAllocGroupName.Invalidate(TRUE);
}

void CChangeAllocGroupInfoDlg::OnSelEndOkBackColor()
{
	m_edtAllocGroupName.SetUserBkColor(m_btnBackColor.GetColor());
	m_edtAllocGroupName.Invalidate(TRUE);
}

void CChangeAllocGroupInfoDlg::OnCbnSelchangeMyOrderDelayCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
