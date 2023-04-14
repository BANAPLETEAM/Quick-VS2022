// ChargeDong2008Dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ChargeDistanceDlg2.h"
#include ".\ChargeDistanceDlg2.h"
#include "VarietyDlg.h"
#include "ChargeDistanceType.h"
#include "POIData.h"
//#include "CPeekTimeSettingDlg.h"


#define ALL_CAR_TYPE 5

// CChargeDistanceDlg2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeDistanceDlg2, CMyResizeDialog)
CChargeDistanceDlg2::CChargeDistanceDlg2(CWnd* pParent /*=NULL*/)
: CMyResizeDialog(CChargeDistanceDlg2::IDD, pParent)
{
	m_pChargeWorkDlg = NULL;
	m_bIntegrated = FALSE;
	m_nCompany = 0;
	m_CopyDongDlg2 = NULL;
	m_bCopyDoc = FALSE;
}

CChargeDistanceDlg2::~CChargeDistanceDlg2()
{

	if(m_CopyDongDlg2 != NULL)
	{
		delete m_CopyDongDlg2;
		m_CopyDongDlg2 = NULL;
	}
}

void CChargeDistanceDlg2::DoDataExchange(CDataExchange* pDX)
{

	CMyResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EX1_STATIC, m_stcEx1);
	DDX_Control(pDX, IDC_EX2_STATIC, m_stcEx2);
	DDX_Control(pDX, IDC_EX3_STATIC, m_stcEx3);		
	DDX_Control(pDX, IDC_START_LIST, m_lstStart);
	DDX_Control(pDX, IDC_DEST_LIST, m_lstDest);
	DDX_Control(pDX, IDC_TWOWAY_CHECK, m_chkShuttle);
	
	DDX_Control(pDX, IDC_CHECK_A1, m_chkA);
	DDX_Control(pDX, IDC_CHECK_B1, m_chkB);
	DDX_Control(pDX, IDC_CHECK_C1, m_chkC);
	DDX_Control(pDX, IDC_CHECK_D1, m_chkD);
	DDX_Control(pDX, IDC_CHECK_E1, m_chkE);

	DDX_Control(pDX, IDC_ABCD_TYPE_STATIC, m_stcABCD);
	DDX_Control(pDX, IDC_ABCD_TYPE_COMBO, m_cmbABCDType);		

	DDX_Control(pDX, IDC_ALL_DEL_CHECK, m_chkAllDel);
	DDX_Control(pDX, IDC_COPY_DONG_BTN, m_CopyDongDlgBtn);
	
	DDX_Control(pDX, IDC_KM_TYPE_COMBO2, m_cmbTypeNameCombo2);
	DDX_Control(pDX, IDC_TYPE_SETTING_BTN, m_btnTypeSetting);
	DDX_Control(pDX, IDC_TYPE_SETTING_TRUCK_BTN, m_btnTypeSettingTruck);

	DDX_Control(pDX, IDC_MAIN_EDIT, m_edtMain);
	DDX_Control(pDX, IDC_SUB_EDIT, m_edtSub);
	DDX_Control(pDX, IDC_MAIN_BUTTON, m_btnMain);
	DDX_Control(pDX, IDC_SUB_BUTTON, m_btnSub);

	DDX_Control(pDX, IDC_BRANCH_STATIC, m_stcBranch);

}


BEGIN_MESSAGE_MAP(CChargeDistanceDlg2, CMyResizeDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_START_LIST, OnReportStartItemClick)
	ON_NOTIFY(NM_CLICK, IDC_DEST_LIST, OnReportDestItemClick)
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_CHECK_A1, OnBnClickedGeneralMotoCheck)
	ON_BN_CLICKED(IDC_CHECK_B1, OnBnClickedGeneralDamaCheck)
	ON_BN_CLICKED(IDC_CHECK_C1, OnBnClickedGeneralLaboCheck)
							   
	ON_BN_CLICKED(IDC_CHECK_D1, OnBnClickedGeneralBanCheck)
	ON_BN_CLICKED(IDC_CHECK_E1, OnBnClickedGeneralTruckCheck)
	ON_BN_CLICKED(IDC_ALL_DEL_CHECK, OnBnClickedAllDelCheck)
	ON_CBN_SELCHANGE(IDC_COMPANY_COMBO, OnCbnSelchangeCompanyCombo)	

	ON_BN_CLICKED(IDC_COPY_DONG_BTN, OnBnClickedCopyDongBtn)
	
	ON_BN_CLICKED(IDC_TYPE_EDIT_BTN, OnBnClickedTypeEditBtn)
	ON_BN_CLICKED(IDC_TYPE_SETTING_BTN, OnBnClickedTypeSettingBtn)
	ON_MESSAGE(WM_CHANGE_BRANCH_CODE, OnChangeBrachCode)
	
	
	ON_CBN_SELCHANGE(IDC_ABCD_TYPE_COMBO, &CChargeDistanceDlg2::OnCbnSelchangeAbcdTypeCombo)
	ON_BN_CLICKED(IDC_TYPE_SETTING_TRUCK_BTN, &CChargeDistanceDlg2::OnBnClickedTypeSettingTruckBtn)
END_MESSAGE_MAP()


// CChargeDistanceDlg2 메시지 처리기입니다.

void CChargeDistanceDlg2::SetCompany(long nCompany)
{
	m_cBranch.SetCompany(m_nCompany);
}

BOOL CChargeDistanceDlg2::OnInitDialog()
{
	CMyResizeDialog::OnInitDialog();

	//m_ChargeTypeCmb.SetCurSel(0);

	

	m_cBranch.SetParent(this, TRUE);
	m_cBranch.InitData(&m_edtMain, &m_edtSub, &m_btnMain, &m_btnSub);

	m_lstStart.SetFont(m_FontManager.GetFont("돋움", 9, FW_BOLD));
	//m_lstStart.SetPaintManager(new CMyReportPaintManager());

	CXTPGridColumn* pStartColumn = m_lstStart.AddColumn(new CXTPGridColumn(0, _T("출발지"), 180, FALSE));
	pStartColumn->SetTreeColumn(1);	
	m_lstStart.AddColumn(new CXTPGridColumn(1, _T("구분"), 70));	
	m_lstStart.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	

	m_lstStart.SetTreeIndent(30);
	m_lstStart.SetGridColor(RGB(222, 222, 222));
	m_lstStart.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";


	CXTPGridColumn* pDestColumn = m_lstDest.AddColumn(new CXTPGridColumn(0, _T("출발지"), 170, FALSE));
	pDestColumn->SetTreeColumn(1);
	pDestColumn->SetEditable(FALSE);


	CXTPGridColumn* pCol1 = m_lstDest.AddColumn(new CXTPGridColumn(1, _T("구분"), 55,FALSE));			
	CXTPGridColumn* pCol2 = m_lstDest.AddColumn(new CXTPGridColumn(COL_BIKE, _T("오토"), 65, TRUE));//일반오토
	CXTPGridColumn* pCol3 = m_lstDest.AddColumn(new CXTPGridColumn(COL_SEDAN, _T("승용"), 65,TRUE));//일반다마
	CXTPGridColumn* pCol4 = m_lstDest.AddColumn(new CXTPGridColumn(COL_DAMA, _T("다마"), 65,TRUE));//일반트럭
	CXTPGridColumn* pCol5 = m_lstDest.AddColumn(new CXTPGridColumn(COL_LABO, _T("라보"), 65,TRUE));//일반트럭
	CXTPGridColumn* pCol6 = m_lstDest.AddColumn(new CXTPGridColumn(COL_TRUCK, _T("트럭"), 65,TRUE));//일반봉고

	pCol1->SetAlignment(DT_LEFT); //pCol1->SetEditable(FALSE);	
	pCol2->SetAlignment(DT_LEFT); //pCol3->SetEditable(TRUE);
	pCol3->SetAlignment(DT_LEFT); //pCol4->SetEditable(TRUE);
	pCol4->SetAlignment(DT_LEFT); //pCol5->SetEditable(TRUE);
	pCol5->SetAlignment(DT_LEFT); //pCol6->SetEditable(TRUE);	
	pCol6->SetAlignment(DT_LEFT); //pCol6->SetEditable(TRUE);	
	m_lstDest.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_lstDest.SetTreeIndent(30);
	m_lstDest.SetGridColor(RGB(222, 222, 222));
	m_lstDest.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";

	//m_lstStart.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP); //by mksong 2010-10-14
	m_lstStart.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstStart.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstStart.GetReportHeader()->AllowColumnResize(TRUE);

	//m_lstDest.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP); //by mksong 2010-10-14
	m_lstDest.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstDest.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstDest.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstDest.GetReportHeader()->AllowColumnSort(FALSE);


	m_lstDest.Populate();
	m_lstStart.Populate();

	m_chkA.SetCheck(TRUE);
	m_lstDest.m_bA = TRUE;
	m_cmbABCDType.SetCurSel(0);

	if(m_bCopyDoc)
		GetDlgItem(IDC_COPY_DONG_BTN)->ShowWindow(SW_HIDE);
	
	SetResize(IDC_START_LIST, SZ_TOP_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_DEST_LIST, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	//SetFlag(xtpResizeNoHorizontal);
	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CChargeDistanceDlg2::InitControl(void)
{	

	CBranchInfo *pBi = NULL;
	if(m_ba.GetCount() > 1)
	{		
		m_nCompany = m_cBranch.GetBranchInfo()->nCompanyCode;
		pBi = m_cBranch.GetBranchInfo();
	}
	else
	{
		pBi = m_ba.GetAt(0);
	}
	CXTPGridRecord *pStartMainRecord = NULL;
	CXTPGridRecord *pDestMainRecord = NULL;
	CXTPGridRecord *pStartSubMainRecord = NULL;
	CXTPGridRecord *pDestSubMainRecord = NULL;
	CXTPGridRecord *pStartthridMainRecord = NULL;
	CXTPGridRecord *pDestthridMainRecord = NULL;	

	CXTPGridRecord *pStartFourthMainRecord = NULL;
	CXTPGridRecord *pDestFourthMainRecord = NULL;


	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_dong_pos_all2");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long),TRUE);				

	long nID = 0;
	int nClass;
	BOOL bHasNotDong = FALSE, bPreHasNotDong = FALSE;

	CString sSido, sGugun, sGugun2,sSumGugun, sDong, sPreSido = "",sPreGugun = "", sLi = "",
		sPreGugun2 = "", sPreSumGugun = "", sPreDong = "", sPreLi = "";
	if(pRs2.Execute(&pCmd2))
	{

		int i = 0;
		while(!pRs2.IsEOF())
		{	
			pRs2.GetFieldValue("sSido", sSido);
			pRs2.GetFieldValue("sGugun", sGugun);
			pRs2.GetFieldValue("sGugun2", sGugun2);
			pRs2.GetFieldValue("sDong", sDong);
			pRs2.GetFieldValue("nClass", nClass);
			pRs2.GetFieldValue("bHasNotDong", bHasNotDong);
			pRs2.GetFieldValue("nID", nID);
			if(pBi->bDongPosLiUse)
				pRs2.GetFieldValue("sLi", sLi);

			sSumGugun = sGugun + " " + sGugun2;

			if(sPreSido != sSido)
			{					
															
				pStartMainRecord = m_lstStart.AddRecord(new CDetailDistanceChargeRecord2(0, bHasNotDong, nClass, sSido , "지역구분"));				
				pDestMainRecord = m_lstDest.AddRecord(new CDetailDistanceDestChargeRecord2(0, bHasNotDong, nClass, sSido , "지역구분"));				

				sPreSido = sSido;
				continue;

			}
			else if(sPreSido == sSido && (sGugun != sPreGugun && sDong.GetLength() == 0) )				
			{
				pStartSubMainRecord = pStartMainRecord->GetChilds()->Add(new CDetailDistanceChargeRecord2(nID, bHasNotDong, nClass,  sSumGugun , sDong));
				pDestSubMainRecord = pDestMainRecord->GetChilds()->Add(new CDetailDistanceDestChargeRecord2(nID, bHasNotDong, nClass,  sSumGugun , sDong));				
				m_pDestRecord.insert(DEST_RECORD_MAP3::value_type(nID,(CDetailDistanceDestChargeRecord2*)pDestSubMainRecord));


			}
			else if(sPreSido == sSido && ( ( sGugun == sPreGugun && sGugun2.GetLength() == 0 && sDong.GetLength() > 0 && sLi.GetLength() == 0)
				|| (sGugun == sPreGugun && sGugun2 != sPreGugun2 &&  sGugun2.GetLength() > 0 && sDong.GetLength() == 0) ) )
			{
							
				pStartthridMainRecord = pStartSubMainRecord->GetChilds()->Add(new CDetailDistanceChargeRecord2(nID, bHasNotDong, nClass,  sSumGugun + " " , sDong));
				pDestthridMainRecord = pDestSubMainRecord->GetChilds()->Add(new CDetailDistanceDestChargeRecord2(nID, bHasNotDong, nClass,  sSumGugun + " " , sDong));				
				m_pDestRecord.insert(DEST_RECORD_MAP3::value_type(nID,(CDetailDistanceDestChargeRecord2*)pDestthridMainRecord));
			}
			else if(
					(sPreSido == sSido &&
						(	
							(sGugun == sPreGugun && sGugun2.GetLength() == 0 && sDong.GetLength() > 0 && sLi.GetLength() > 0) || 
							(sGugun == sPreGugun && sGugun2 == sPreGugun2 &&  sGugun2.GetLength() > 0 && sDong.GetLength() > 0 && sLi.GetLength() == 0) 
						)
					)
				)
			{
				pStartFourthMainRecord = pStartthridMainRecord->GetChilds()->Add(new CDetailDistanceChargeRecord2(nID, bHasNotDong, nClass, nClass == 20 ? sDong : "", nClass == 20 ? sLi : sDong));
				pDestFourthMainRecord = pDestthridMainRecord->GetChilds()->Add(new CDetailDistanceDestChargeRecord2(nID, bHasNotDong, nClass, nClass == 20 ? sDong :"",   nClass == 20 ? sLi : sDong));				 
				m_pDestRecord.insert(DEST_RECORD_MAP3::value_type(nID,(CDetailDistanceDestChargeRecord2*)pDestFourthMainRecord));
			}
			else// sPreSido == sSido && ( (sGugun == sPreGugun && sGugun2 == sPreGugun2 &&  sDong != sPreDong &&  sDong.GetLength() == 0) ) )
			{
				if(pBi->bDongPosLiUse)
				{
					pStartFourthMainRecord->GetChilds()->Add(new CDetailDistanceChargeRecord2(nID, bHasNotDong, nClass, sDong, sLi));
					pDestFourthMainRecord = pDestFourthMainRecord->GetChilds()->Add(new CDetailDistanceDestChargeRecord2(nID, bHasNotDong, nClass, sDong, sLi));				 
					m_pDestRecord.insert(DEST_RECORD_MAP3::value_type(nID,(CDetailDistanceDestChargeRecord2*)pDestFourthMainRecord));
				}
			}


			i++;
			sPreSido = sSido;
			sPreGugun = sGugun;
			sPreGugun2 = sGugun2;
			sPreSumGugun = sSumGugun;
			sPreDong = sDong;
			if(pBi->bDongPosLiUse)
				sPreLi	= sLi;
			bPreHasNotDong = bHasNotDong;
			pRs2.MoveNext();
		}
		pRs2.Close();
	}
	m_lstStart.Populate();
	m_lstDest.Populate();


	//SetTypeRefresh();
}




LONG CChargeDistanceDlg2::OnChangeBrachCode(WPARAM wParam, LPARAM lParam)
{	
	
	m_nCompany =  m_cBranch.GetBranchInfo()->nPayTable;
	SetTypeRefresh();
	RefreshList();

	return 0;
}


void CChargeDistanceDlg2::SetTypeRefresh()
{
	charge_type_map_.clear();
	m_cmbTypeNameCombo2.ResetContent();	

	CMkRecordset pRs3(m_pMkDb);
	CMkCommand pCmd3(m_pMkDb, "charge_distance_type_select");	
	pCmd3.AddParameter(m_nCompany);	
	pCmd3.Execute();

	if(pRs3.Execute(&pCmd3)) {
		int index = 0;
		int id = 0; CString type_name;
		while(!pRs3.IsEOF()) {			
			pRs3.GetFieldValue("id", id);	
			pRs3.GetFieldValue("type_name", type_name);	

			charge_type_map_.insert(make_pair(id, type_name));
			m_cmbTypeNameCombo2.InsertString(index, type_name);		
			m_cmbTypeNameCombo2.SetItemData(index++, id);
			pRs3.MoveNext();
		}
	}	
}

int CChargeDistanceDlg2::GetAmountType()
{
	int index = m_cmbTypeNameCombo2.GetCurSel();

	if(index < 0)
		return -1;

	return m_cmbTypeNameCombo2.GetItemData(index);
}

void CChargeDistanceDlg2::OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	CDetailDistanceChargeRecord2 *pRecord = (CDetailDistanceChargeRecord2 *)pItemNotify->pRow->GetRecord();
	if(pRecord->m_nID == 0)
		return;

	RefreshList();	
}


void CChargeDistanceDlg2::RefreshList()
{
	ChargeAllDelete();

	CXTPGridRow *pRow = NULL;
	if(m_lstStart.GetSelectedRows()->GetCount() == 1)
		pRow = m_lstStart.GetSelectedRows()->GetAt(0);
	else {		 
		m_lstDest.Populate();
		return;
	}	

	int nRow = pRow->GetIndex();
	CDetailDistanceChargeRecord2 *pRecord = (CDetailDistanceChargeRecord2 *)pRow->GetRecord();

	if(pRecord->m_nID == 0)
		return;

	m_nCompany = m_cBranch.GetBranchInfo()->nPayTable;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "charge_distance_start_select");
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(pRecord->m_nID);
	pCmd.AddParameter(m_cmbABCDType.GetCurSel());

	if(pRs.Execute(&pCmd)) {
		int dest_id = 0, car_type = 0, amount_type = 0;

		for(long i=0; i<pRs.GetRecordCount(); i++) {
			pRs.GetFieldValue("dest_id", dest_id);
			pRs.GetFieldValue("car_type", car_type);
			pRs.GetFieldValue("amount_type", amount_type);									

			SetAllCharge(dest_id, car_type, amount_type);
			pRs.MoveNext();
		}

		pRs.Close();
	}

	m_lstDest.RedrawControl();
}


void CChargeDistanceDlg2::SetAllCharge(int dest_id, int car_type, int amount_type)
{
	DEST_RECORD_MAP3::iterator it;
	it = m_pDestRecord.find(dest_id);

	if(it == m_pDestRecord.end()) return;

	map<int, CString>::iterator it_type = charge_type_map_.find(amount_type);
	
	CDetailDistanceDestChargeRecord2 *pDestRecord = (CDetailDistanceDestChargeRecord2*)it->second;
	pDestRecord->ChangeValue(car_type, it_type != charge_type_map_.end() ? it_type->second : "");

	m_vecDest.push_back(pDestRecord);
}

void CChargeDistanceDlg2::ChargeAllDelete()
{
	DEST_RECORD_VEC3::iterator it;
	for(it = m_vecDest.begin(); it != m_vecDest.end(); ++it)
		(*it)->ChangeClear();

	m_vecDest.clear();
}


BOOL CChargeDistanceDlg2::CheckAreaSelect()
{
	int nStartCurRow = m_lstStart.GetSelectedRows()->GetCount();
	int nDestCurRow = m_lstDest.GetSelectedRows()->GetCount();

	CDetailDistanceDestChargeRecord2 *pDestRecord = NULL;
	CDetailDistanceChargeRecord2 *pStartRecord = NULL;
	for(int i = 0; i < nStartCurRow; i++)
	{
		pStartRecord = (CDetailDistanceChargeRecord2*)m_lstStart.GetSelectedRows()->GetAt(i);

		CXTPGridRow *pRow = m_lstStart.GetSelectedRows()->GetAt(i);
		pStartRecord = (CDetailDistanceChargeRecord2*)pRow->GetRecord();

		if(pStartRecord->m_nID == 0)
		{
			MessageBox("출발지에서 지역분류는 요금셋팅 작업을 하실수 없습니다.","지역선택오류",MB_ICONINFORMATION);
			return FALSE;
		}

		for(int j=0; j < nDestCurRow; j++)
		{
			CXTPGridRow *pRow = m_lstDest.GetSelectedRows()->GetAt(j);
			pDestRecord =  (CDetailDistanceDestChargeRecord2*)pRow->GetRecord();

			if(pDestRecord->m_nID == 0)
			{
				MessageBox("도착지에서 지역분류는 요금셋팅 작업을 하실수 없습니다.","지역선택오류",MB_ICONINFORMATION);
				return FALSE;
			}		

		}
	}
	return TRUE;

}



void CChargeDistanceDlg2::OnBnClickedTypeEditBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	try
	{		
		long nCompany = m_cBranch.GetBranchInfo()->nCompanyCode;
		if(nCompany < 0)
			throw("선택한 지점명이 비정상적입니다. 회사선택을 다시하여주세요");

		if( m_chkA.GetCheck() + m_chkB.GetCheck() +
			m_chkC.GetCheck() + m_chkD.GetCheck() + m_chkE.GetCheck() <= 0)
			throw("수정할 곳이나 입력할 곳을 하나이상 기입하여주세요!");

		int k = m_chkA.GetCheck() + m_chkB.GetCheck() +
			m_chkC.GetCheck() + m_chkD.GetCheck() + m_chkE.GetCheck() ;

		if(!ChargeLinkUpdate())
			return;

		int amount_type = GetAmountType();

		if(amount_type <= 0) 
			throw "요금이 설정되지 않았습니다.";

		if(!CheckAreaSelect())
			return;

		CDetailDistanceDestChargeRecord2 *pDestRecord = NULL;
		CDetailDistanceChargeRecord2 *pStartRecord = NULL;
		BOOL bSuccess = FALSE;

		int nStartCurRow = m_lstStart.GetSelectedRows()->GetCount();
		int nDestCurRow = m_lstDest.GetSelectedRows()->GetCount();
		for(int i = 0; i < nStartCurRow; i++)
		{
			pStartRecord = (CDetailDistanceChargeRecord2*)m_lstStart.GetSelectedRows()->GetAt(i);

			CXTPGridRow *pRow = m_lstStart.GetSelectedRows()->GetAt(i);
			pStartRecord = (CDetailDistanceChargeRecord2*)pRow->GetRecord();

			for(int j=0; j < nDestCurRow; j++)
			{
				CXTPGridRow *pRow = m_lstDest.GetSelectedRows()->GetAt(j);
				pDestRecord =  (CDetailDistanceDestChargeRecord2*)pRow->GetRecord();
				CMkCommand pCmd(m_pMkDb, "charge_distance_info_update");
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);		
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetType(pStartRecord, pDestRecord));
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), pStartRecord->m_nID);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), pDestRecord->m_nID);
				pCmd.AddParameter(m_chkA.GetCheck() ? CAR_AUTO : -1);
				pCmd.AddParameter(m_chkB.GetCheck() ? CAR_SEDAN : -1);
				pCmd.AddParameter(m_chkC.GetCheck() ? CAR_DAMA : -1);
				pCmd.AddParameter(m_chkD.GetCheck() ? CAR_LABO : -1);
				pCmd.AddParameter(m_chkE.GetCheck() ? CAR_TRUCK : -1);
				pCmd.AddParameter(m_cmbABCDType.GetCurSel());
				pCmd.AddParameter(amount_type);
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkShuttle.GetCheck());				
				

				if(!pCmd.Execute()) 
				{
					bSuccess = FALSE;
					throw("입력이 실패되었습니다.");
				}

				if(m_chkA.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_AUTO, amount_type);
				if(m_chkB.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_SEDAN, amount_type);
				if(m_chkC.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_DAMA, amount_type);
				if(m_chkD.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_LABO, amount_type);
				if(m_chkE.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_TRUCK, amount_type);
			}

		}
		m_lstDest.Populate();
	}
	catch (char* e)
	{
		MessageBox(e,"", MB_ICONINFORMATION);
	}
	catch(CString sMsg) 
	{
		MessageBox(sMsg, "확인", MB_ICONINFORMATION);
	}
}


void CChargeDistanceDlg2::OnBnClickedDeleteBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(!ChargeLinkUpdate())
		return;

	CDetailDistanceDestChargeRecord2 *pDestRecord = NULL;
	CDetailDistanceChargeRecord2 *pStartRecord = NULL;
	BOOL bSuccess = FALSE;
	DEST_RECORD_MAP3::iterator it;


	int nStartCurRow = m_lstStart.GetSelectedRows()->GetCount();
	int nDestCurRow = m_lstDest.GetSelectedRows()->GetCount();

	for(int i = 0; i < nStartCurRow; i++)
	{
		pStartRecord = (CDetailDistanceChargeRecord2*)m_lstStart.GetSelectedRows()->GetAt(i);

		CXTPGridRow *pRow = m_lstStart.GetSelectedRows()->GetAt(i);
		pStartRecord = (CDetailDistanceChargeRecord2*)pRow->GetRecord();

		for(int j=0; j < nDestCurRow; j++)
		{

			CXTPGridRow *pRow = m_lstDest.GetSelectedRows()->GetAt(j);
			pDestRecord = (CDetailDistanceDestChargeRecord2*)pRow->GetRecord();

			CMkCommand pCmd(m_pMkDb,  "charge_distance_info_delete");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);					
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pStartRecord->m_nID);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pDestRecord->m_nID);
			pCmd.AddParameter(m_chkA.GetCheck() ? CAR_AUTO : -1);
			pCmd.AddParameter(m_chkB.GetCheck() ? CAR_SEDAN : -1);
			pCmd.AddParameter(m_chkC.GetCheck() ? CAR_DAMA : -1);
			pCmd.AddParameter(m_chkD.GetCheck() ? CAR_LABO : -1);
			pCmd.AddParameter(m_chkE.GetCheck() ? CAR_TRUCK : -1);
			pCmd.AddParameter(m_cmbABCDType.GetCurSel());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkShuttle.GetCheck());

			if(!pCmd.Execute())
			{
				MessageBox("삭제시 에러가 났습니다.","확인",MB_ICONINFORMATION);
				return;
			}

			it = m_pDestRecord.find(pDestRecord->m_nID);			
			pDestRecord = (CDetailDistanceDestChargeRecord2 *)it->second;
		
			if(m_chkA.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_AUTO, 0);
			if(m_chkB.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_SEDAN, 0);
			if(m_chkC.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_DAMA, 0);
			if(m_chkD.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_LABO, 0);
			if(m_chkE.GetCheck()) SetAllCharge(pDestRecord->m_nID, CAR_TRUCK, 0);			
		}
	}
	m_lstDest.Populate();
	MessageBox("정상적으로 삭제되었습니다.","삭제완료", MB_ICONINFORMATION);	
}



void CChargeDistanceDlg2::OnBnClickedGeneralMotoCheck()
{
	if(m_chkA.GetCheck())
	{
		m_chkB.SetCheck(FALSE);
		m_chkC.SetCheck(FALSE);
		m_chkD.SetCheck(FALSE);
		m_chkE.SetCheck(FALSE);

		m_lstDest.m_bA = TRUE;
		m_lstDest.m_bB = FALSE;
		m_lstDest.m_bC = FALSE;
		m_lstDest.m_bD = FALSE;
		m_lstDest.m_bE = FALSE;
		m_chkAllDel.SetCheck(FALSE);
	}
	else
	{
		m_lstDest.m_bA = FALSE;		
		m_chkAllDel.SetCheck(FALSE);
	}


	m_lstDest.RedrawControl();
}

void CChargeDistanceDlg2::OnBnClickedGeneralDamaCheck()
{
	if(m_chkB.GetCheck())
	{		
		m_chkA.SetCheck(FALSE);
		m_chkC.SetCheck(FALSE);
		m_chkD.SetCheck(FALSE);
		m_chkE.SetCheck(FALSE);

		m_lstDest.m_bA = FALSE;
		m_lstDest.m_bB = TRUE;
		m_lstDest.m_bC = FALSE;
		m_lstDest.m_bD = FALSE;
		m_lstDest.m_bE = FALSE;
		m_chkAllDel.SetCheck(FALSE);
	}
	else
	{
		m_lstDest.m_bB = FALSE;		
		m_chkAllDel.SetCheck(FALSE);
	}

	m_lstDest.RedrawControl();
}


void CChargeDistanceDlg2::OnBnClickedGeneralLaboCheck()
{
	if(m_chkC.GetCheck())
	{
		m_chkA.SetCheck(FALSE);
		m_chkB.SetCheck(FALSE);		
		m_chkD.SetCheck(FALSE);
		m_chkE.SetCheck(FALSE);

		m_lstDest.m_bA = FALSE;
		m_lstDest.m_bB = FALSE;
		m_lstDest.m_bC = TRUE;
		m_lstDest.m_bD = FALSE;
		m_lstDest.m_bE = FALSE;
		m_chkAllDel.SetCheck(FALSE);
	}
	else
	{
		m_lstDest.m_bC = FALSE;		
		m_chkAllDel.SetCheck(FALSE);
	}

	m_lstDest.RedrawControl();
}

void CChargeDistanceDlg2::OnBnClickedGeneralBanCheck()
{
	if(m_chkD.GetCheck())
	{		
		m_chkA.SetCheck(FALSE);
		m_chkB.SetCheck(FALSE);
		m_chkC.SetCheck(FALSE);
		m_chkE.SetCheck(FALSE);

		m_lstDest.m_bA = FALSE;
		m_lstDest.m_bB = FALSE;
		m_lstDest.m_bC = FALSE;
		m_lstDest.m_bD = TRUE;
		m_lstDest.m_bE = FALSE;
		m_chkAllDel.SetCheck(FALSE);
	}
	else
	{
		m_lstDest.m_bD = FALSE;		
		m_chkAllDel.SetCheck(FALSE);
	}

	m_lstDest.RedrawControl();
}

void CChargeDistanceDlg2::OnBnClickedGeneralTruckCheck()
{
	if(m_chkE.GetCheck())
	{		
		m_chkA.SetCheck(FALSE);
		m_chkB.SetCheck(FALSE);
		m_chkC.SetCheck(FALSE);
		m_chkD.SetCheck(FALSE);

		m_lstDest.m_bA = FALSE;
		m_lstDest.m_bB = FALSE;
		m_lstDest.m_bC = FALSE;
		m_lstDest.m_bD = FALSE;
		m_lstDest.m_bE = TRUE;
		m_chkAllDel.SetCheck(FALSE);
	}
	else
	{
		m_lstDest.m_bE = FALSE;	
		m_chkAllDel.SetCheck(FALSE);
	}

	m_lstDest.RedrawControl();
}



void CChargeDistanceDlg2::OnBnClickedAllDelCheck()
{
	if(m_chkAllDel.GetCheck())
	{
		m_chkA.SetCheck(TRUE);
		m_lstDest.m_bA = TRUE;

		m_chkB.SetCheck(TRUE);
		m_lstDest.m_bB = TRUE;

		m_chkC.SetCheck(TRUE);
		m_lstDest.m_bC = TRUE;

		m_chkD.SetCheck(TRUE);
		m_lstDest.m_bD = TRUE;

		m_chkE.SetCheck(TRUE);
		m_lstDest.m_bE = TRUE;
	}
	else
	{		

		m_chkA.SetCheck(FALSE);
		m_lstDest.m_bA = FALSE;
		m_chkB.SetCheck(FALSE);
		m_lstDest.m_bB = FALSE;
		m_chkC.SetCheck(FALSE);
		m_lstDest.m_bC = FALSE;
		m_chkD.SetCheck(FALSE);
		m_lstDest.m_bD = FALSE;
		m_chkE.SetCheck(FALSE);
		m_lstDest.m_bE = FALSE;
	}
	m_lstDest.RedrawControl();
}

void CChargeDistanceDlg2::OnSize(UINT nType, int cx, int cy)
{
	CMyResizeDialog::OnSize(nType, cx, cy);
}

void CChargeDistanceDlg2::CarORABCDTypeChangeRefesh()
{
	RefreshList();
}

int CChargeDistanceDlg2::GetType(CDetailDistanceChargeRecord2 *pStartRecord, CDetailDistanceDestChargeRecord2 *pDestRecord)
{
	int nStartType = pStartRecord->GetTypeInfo();
	int nDestType = pDestRecord->GetTypeInfo();
	int nType = 0;

	if(nStartType == 0 || nDestType == 0)
		MessageBox("출발지및 도착지 타입이 잘못되었습니다.", "확인", MB_ICONINFORMATION);

	if(nStartType == 3 && nDestType == 3)
		nType = 8;
	else if(nStartType == 3 && nDestType == 2)
		nType = 7;
	else if(nStartType == 3 && nDestType == 1)
		nType = 6;
	else if(nStartType == 2 && nDestType == 3)
		nType = 5;
	else if(nStartType == 1 && nDestType == 3)
		nType = 4;
	else if(nStartType == 2 && nDestType == 2)
		nType = 3;
	else if(nStartType == 2 && nDestType == 1)
		nType = 2;
	else if(nStartType == 1 && nDestType == 2)
		nType = 1;
	else if(nStartType == 1 && nDestType == 1)
		nType = 0;
	return nType;
}

BOOL CChargeDistanceDlg2::ChargeLinkUpdate()
{
	CString sError = "";
	CBranchInfo *pBi = NULL;
	CBranchInfo *pCurentBi = NULL;
	CString strBranchName = m_cBranch.GetBranchInfo()->strBranchName;
	//m_cmbCompany.GetWindowText(strBranchName);

	pCurentBi = (CBranchInfo *)m_cBranch.GetBranchInfo();		
	if(pCurentBi == NULL)
		return FALSE;

	if(m_ba.GetCount() > 1)
	{			
		for(int i = 0; i < m_ba.GetCount(); i++)
		{
			pBi = (CBranchInfo *)m_ba.GetAt(i);

			if(pBi->strBranchName == strBranchName  && pBi->nCompanyCode == pCurentBi->nCompanyCode)
			{
				if(pBi->nPayTable != pBi->nCompanyCode)
				{
					//m_ci.GetMap()->
					sError.Format("요금링크 메인인 %s 사이트에서만 수정하실수 있습니다.\0",m_ci.GetBranchName(pBi->nPayTable));
					MessageBox(sError, "확인", MB_ICONINFORMATION);
					return FALSE;
				}
			}			

		}
	}
	else if(m_ba.GetCount() == 1)
	{
		pBi = (CBranchInfo *)m_ba.GetAt(0);
		if(pBi->strBranchName == strBranchName && pBi->nCompanyCode == pCurentBi->nCompanyCode)
		{
			if (pBi->nPayTable != pBi->nCompanyCode)
			{
				sError.Format("요금링크 메인인 %s에서만 수정하실수 있습니다.\0",m_ci.GetBranchName(pBi->nPayTable));
				MessageBox(sError, "확인", MB_ICONINFORMATION);
				return FALSE;
			}

		}
	}
	return TRUE;

}


void CChargeDistanceDlg2::OnReportDestItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	CDetailDistanceDestChargeRecord2 *pRecord = (CDetailDistanceDestChargeRecord2 *)pItemNotify->pRow->GetRecord();

	if(pRecord->m_nID == 0)
		return;
}

void CChargeDistanceDlg2::OnCbnSelchangeCompanyCombo()
{
	RefreshList();	
}

void CChargeDistanceDlg2::OnBnClickedCopyDongBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(m_CopyDongDlg2 == NULL)
	{
		m_CopyDongDlg2 = new CChargeDistanceDlg2(this);

	}

	m_CopyDongDlg2->m_nCompany = m_nCompany;
	m_CopyDongDlg2->m_bIntegrated = m_bIntegrated;		
	m_CopyDongDlg2->m_bCopyDoc = TRUE;
	m_CopyDongDlg2->Create(IDD_CHARGE_DISTANCE_DLG2,this);
	m_CopyDongDlg2->ShowWindow(SW_SHOW);

}


void CChargeDistanceDlg2::OnCbnSelchangeAbcdTypeCombo()
{
	CarORABCDTypeChangeRefesh();
}

void CChargeDistanceDlg2::OnBnClickedTypeSettingBtn()
{
	OpenChargeDistanceTypeDlg(FALSE);
}

void CChargeDistanceDlg2::OnBnClickedTypeSettingTruckBtn()
{
	OpenChargeDistanceTypeDlg(TRUE);
}

void CChargeDistanceDlg2::OpenChargeDistanceTypeDlg(BOOL bTruck)
{
	BOOL bIntegrated = FALSE;
	CBranchInfo *pBi = m_cBranch.GetBranchInfo();
	long nCompany = 0;
	if(m_ba.GetCount() > 1)	
	{
		for(int i = 0; i < m_ba.GetCount(); i++) {
			pBi = m_ba.GetAt(i);
			if(pBi->bIntegrated)
			{
				bIntegrated =	TRUE;
				break;
			}		
		}		
	}
	else
	{
		pBi = (CBranchInfo*)m_ba.GetAt(0);
		nCompany = pBi->nPayTable;
	}
	CString strCompany = m_cBranch.GetBranchInfo()->strBranchName;

	CChargeDistanceType dlg(this, bTruck);
	dlg.m_nCompany = m_cBranch.GetCompany(); 
	dlg.m_bIntegrated = bIntegrated;
	dlg.m_sCompany = strCompany;
	dlg.DoModal();
	SetTypeRefresh();
}
