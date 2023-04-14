// ChargeDongDlg2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeDongDlg2.h"

#include "LineDlg.h"
#include "ChargeWorkDlg.h"
#include "VarietyDlg.h"
#include "BCMenu.h"
#include "SearchGroupDlg.h"
#include "ChargeListSetDlg.h"
#include "WebChargeListDlg.h"
#include "ChargeDongUDlg.h"
#include "ChargeDongSettingDlg.h"


// CChargeDongDlg2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeDongDlg2, CXTResizeDialog)
CChargeDongDlg2::CChargeDongDlg2(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CChargeDongDlg2::IDD, pParent)
{
	m_pChargeWorkDlg = NULL;
	m_bIntegrated = FALSE;
	m_nCompany = 0;
	m_CopyDongDlg2 = NULL;
	m_bCopyDoc = FALSE;
	m_nFirstWork = 0;
	m_pChargeDongSettingDlg = NULL;
	m_bHTypeViewMode = FALSE;
	m_nMemCNo = 0;
}

CChargeDongDlg2::~CChargeDongDlg2()
{
	if(m_pChargeWorkDlg != NULL)
	{
		delete m_pChargeWorkDlg;
		m_pChargeWorkDlg = NULL;
	}

	if(m_CopyDongDlg2 != NULL)
	{
		delete m_CopyDongDlg2;
		m_CopyDongDlg2 = NULL;
	}
	if(m_pChargeDongSettingDlg != NULL)
	{
		delete m_pChargeDongSettingDlg;
		m_pChargeDongSettingDlg = NULL;
	}
}

void CChargeDongDlg2::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_COMBO, m_cmbCompany);
	DDX_Control(pDX, IDC_START_LIST, m_lstStart);
	DDX_Control(pDX, IDC_DEST_LIST, m_lstDest);
	DDX_Control(pDX, IDC_TWOWAY_CHECK, m_chkShuttle);
	DDX_Control(pDX, IDC_GENERAL_MOTO_CHECK, m_chkGeneralMoto);
	DDX_Control(pDX, IDC_GENERAL_DAMA_CHECK, m_chkGeneralDama);
	DDX_Control(pDX, IDC_SPECIFIC_MOTO_CHECK, m_chkSpecificMoto);
	DDX_Control(pDX, IDC_SPECIFIC_DAMA_CHECK, m_chkSpecificDama);
	DDX_Control(pDX, IDC_SUBWAY_CHECK, m_chkSubWay);

	DDX_Control(pDX, IDC_DIS_COM_COMBO, m_cmbDiscountCompany);
	DDX_Control(pDX, IDC_ALL_DEL_CHECK, m_chkAllDel);
	DDX_Control(pDX, IDC_DISCOUNT_COMPANY_BTN, m_DisCountCompanyBtn);
	DDX_Control(pDX, IDC_COPY_DONG_BTN, m_CopyDongDlgBtn);
	DDX_Control(pDX, IDC_LINE_BTN, m_LineBtn);
	DDX_Control(pDX, IDC_DISCOUNT_COMPANY_DEL_BTN, m_DisCountCompanyDelBtn);	
	DDX_Control(pDX, IDC_CHARGE_TYPE_COMBO, m_ChargeTypeCmb);
	DDX_Control(pDX, IDC_SAME_VIEW_BTN, m_btnSameView);
	DDX_Control(pDX, IDC_CHARGE_LIST_BTN, m_btnChargeList);

	DDX_Control(pDX, IDC_NOTCHARGE_QUERY_CHECK, m_chkNotChargeQuery);
	DDX_Control(pDX, IDC_SELECTAREA_MEMORY_BTN, m_btnSelectAreaMemory);
	DDX_Control(pDX, IDC_SAME_CHECK_BTN, m_btnSameChekc);
	DDX_Control(pDX, IDC_CHARGE_TYPE_BTN, m_btnChargeType);
	DDX_Control(pDX, IDC_SAVE_BTN, m_btnSave);
	DDX_Control(pDX, IDC_EDIT_BTN, m_btnEdit);
	DDX_Control(pDX, IDC_DELETE_BTN, m_btnDelete);

	DDX_Control(pDX, IDC_SEARCH_COMBO1, m_cmbSearch[0]);
	DDX_Control(pDX, IDC_SEARCH_COMBO2, m_cmbSearch[1]);
	DDX_Control(pDX, IDC_SEARCH_COMBO3, m_cmbSearch[2]);
	DDX_Control(pDX, IDC_SEARCH_COMBO4, m_cmbSearch[3]);
	DDX_Control(pDX, IDC_STATIC1, m_stcSearch1);
	DDX_Control(pDX, IDC_STATIC2, m_stcSearch2);
	DDX_Control(pDX, IDC_STATIC3, m_stcSearch3);

	DDX_Control(pDX, IDC_USER_BTN, m_btnText);
	DDX_Control(pDX, IDC_TYPE_RANK_STATIC, m_stcRankEx);

	DDX_Control(pDX, IDC_BRANCH_NAME_STATIC, m_stcBranch);
	DDX_Control(pDX, IDC_TYPECHARGE_STATIC, m_stcChargeType);
	DDX_Control(pDX, IDC_GROUP_STATIC, m_stcGroup);
	DDX_Control(pDX, IDC_TYPE_RANK_STATIC, m_stcRankEx);

	DDX_Control(pDX, IDC_SEARCH_SAVE_BTN, m_btnChargeTypeRank);
	DDX_Control(pDX, IDC_SEARCH_GROUP_BTN, m_btnSearchGroup);

	DDX_Control(pDX, IDC_HCUSTOMER_COMBO, m_cmbHCustomer);
	DDX_Control(pDX, IDC_SEARCH_HCUSTOMER_BTN, m_btnSearchHCustomer);

	//DDX_Control(pDX, IDC_STATIC5, m_stc5);
	//DDX_Control(pDX, IDC_STATIC6, m_stc6);
	//DDX_Control(pDX, IDC_STATIC7, m_stc7);
	//DDX_Control(pDX, IDC_STATIC8, m_stc8);

	DDX_Control(pDX, IDC_GENERAL_RABO_CHECK, m_chkGeneralRabo);

	DDX_Control(pDX, IDC_CHARGE_EDIT11, m_edtCharge11);
	DDX_Control(pDX, IDC_CHARGE_EDIT12, m_edtCharge12);
	DDX_Control(pDX, IDC_CHARGE_EDIT13, m_edtCharge13);
	DDX_Control(pDX, IDC_CHARGE_EDIT14, m_edtCharge14);
	DDX_Control(pDX, IDC_CHARGE_EDIT15, m_edtCharge15);
	DDX_Control(pDX, IDC_CHARGE_EDIT16, m_edtCharge16);
}


BEGIN_MESSAGE_MAP(CChargeDongDlg2, CXTResizeDialog)
	ON_BN_CLICKED(IDC_EDIT_BTN, OnBnClickedEditBtn)
	ON_NOTIFY(NM_CLICK, IDC_START_LIST, OnReportStartItemClick)
	ON_NOTIFY(NM_CLICK, IDC_DEST_LIST, OnReportDestItemClick)
	ON_NOTIFY(NM_RCLICK, IDC_START_LIST, OnReportStartItemRClick)
	ON_NOTIFY(NM_RCLICK, IDC_DEST_LIST, OnReportDestItemRClick)
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
	ON_CBN_SELCHANGE(IDC_DIS_COM_COMBO, OnCbnSelchangeDisComCombo)
	ON_BN_CLICKED(IDC_ALL_DEL_CHECK, OnBnClickedAllDelCheck)
	ON_BN_CLICKED(IDC_DISCOUNT_COMPANY_BTN, OnBnClickedDiscountCompanyBtn)
	ON_BN_CLICKED(IDC_LINE_BTN, OnBnClickedLineBtn)
	ON_CBN_SELCHANGE(IDC_COMPANY_COMBO, OnCbnSelchangeCompanyCombo)
	ON_CBN_SELCHANGE(IDC_CHARGE_TYPE_COMBO, OnCbnSelchangeChargeTypeCombo)
	ON_BN_CLICKED(IDC_CHARGE_TYPE_BTN, OnBnClickedChargeTypeBtn)
	ON_BN_CLICKED(IDC_COPY_DONG_BTN, OnBnClickedCopyDongBtn)
	ON_BN_CLICKED(IDC_DISCOUNT_COMPANY_DEL_BTN, OnBnClickedDiscountCompanyDelBtn)
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_SEARCH_GROUP_BTN, OnBnClickedSearchGroupBtn)	
	ON_BN_CLICKED(IDC_SAME_CHECK_BTN, OnBnClickedSameCheckBtn)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_SELECTAREA_MEMORY_BTN, OnBnClickedSelectareaMemoryBtn)	
	ON_BN_CLICKED(IDC_SAME_VIEW_BTN, OnBnClickedSameViewBtn)
	ON_COMMAND(ID_CHARGE_LIST_PRINT, OnViewListPrint)
	
	ON_NOTIFY(XTP_NM_GRID_VALUECHANGED , IDC_DEST_LIST, OnReportValueChanged)
	ON_NOTIFY(XTP_NM_GRID_BEGINEDIT, IDC_DEST_LIST, OnReportBeginEdit)
	ON_BN_CLICKED(IDC_CHARGE_LIST_BTN, OnBnClickedChargeListBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_SEARCH_SAVE_BTN, OnBnClickedSearchSaveBtn)
	ON_BN_CLICKED(IDC_USER_BTN, OnBnClickedUserBtn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TWOWAY_CHECK, &CChargeDongDlg2::OnBnClickedTwowayCheck)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_GENERAL_RABO_CHECK, &CChargeDongDlg2::OnBnClickedGeneralRaboCheck)
END_MESSAGE_MAP()


// CChargeDongDlg2 메시지 처리기입니다.



BOOL CChargeDongDlg2::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	m_ChargeTypeCmb.SetCurSel(0);

	CBranchInfo *pBi = NULL;
	if(m_bIntegrated)
	{
		int nCurSel = 0;
		int nItem = 0;
		BOOL bIntegrated =FALSE;
		
		for(int i = 0; i < m_ba.GetCount(); i++) {
			pBi = m_ba.GetAt(i);
			if(pBi->bIntegrated)
			{
				bIntegrated =	TRUE;
				continue;
			}
			else
			{
				if(m_nCompany == pBi->nCompanyCode)
					nCurSel = nItem;

				m_cmbCompany.InsertString(nItem,pBi->strBranchName);
				m_cmbCompany.SetItemData(nItem, (DWORD_PTR)pBi); // 금액테이블적용
			}
			nItem++;
		}
		m_cmbCompany.SetCurSel(nCurSel);
	}
	else
	{
		pBi = m_ba.GetAt(0);
		m_cmbCompany.InsertString(0,pBi->strBranchName );
		m_cmbCompany.SetItemData(0,(DWORD_PTR)pBi);
		m_cmbCompany.SetCurSel(0);
	}

	for(int i=0; i<4; i++)
		m_cmbSearch[i].SetCurSel(m_ci.m_nChargeSearchOrder[i]);

	m_lstStart.SetFont(m_FontManager.GetFont("돋움", 9, FW_BOLD));
	m_lstStart.SetPaintManager(new CMyReportPaintManager());

	CXTPGridColumn* pStartColumn = m_lstStart.AddColumn(new CXTPGridColumn(0, _T("출발지"), 150, FALSE));
	pStartColumn->SetTreeColumn(1);	
	m_lstStart.AddColumn(new CXTPGridColumn(1, _T("구분"), 80));
	m_lstStart.SetTreeIndent(30);
	m_lstStart.SetGridColor(RGB(222, 222, 222));
	m_lstStart.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	


	CXTPGridColumn* pDestColumn = m_lstDest.AddColumn(new CXTPGridColumn(0, _T("출발지"), 150, FALSE));
	pDestColumn->SetTreeColumn(1);	
	
	CXTPGridColumn* pCol1 = m_lstDest.AddColumn(new CXTPGridColumn(1, _T("구분"), 80,FALSE));		
	CXTPGridColumn* pCol2 = m_lstDest.AddColumn(new CXTPGridColumn(2, _T("오토짐받이"), 60,FALSE));//일반오토
	CXTPGridColumn* pCol3 = m_lstDest.AddColumn(new CXTPGridColumn(3, _T("다마"), 55,FALSE));//일반다마
	CXTPGridColumn* pCol4 = m_lstDest.AddColumn(new CXTPGridColumn(4, _T("라보"), 55,FALSE));//일반다마
	CXTPGridColumn* pCol5 = m_lstDest.AddColumn(new CXTPGridColumn(5, _T("밴"), 55,FALSE));//일반트럭
	CXTPGridColumn* pCol6 = m_lstDest.AddColumn(new CXTPGridColumn(6, _T("트럭"), 55,FALSE));//일반봉고
	CXTPGridColumn* pCol7 = m_lstDest.AddColumn(new CXTPGridColumn(7, _T("지하철"), 55,FALSE));//일반봉고

	pCol1->SetAlignment(DT_CENTER);	
	pCol2->SetAlignment(DT_CENTER);
	pCol3->SetAlignment(DT_CENTER);
	pCol4->SetAlignment(DT_CENTER);
	pCol5->SetAlignment(DT_CENTER);
	pCol6->SetAlignment(DT_CENTER);
	pCol7->SetAlignment(DT_CENTER);

	pDestColumn->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol3->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol4->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol5->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol6->GetEditOptions()->m_bAllowEdit = TRUE;
	pCol7->GetEditOptions()->m_bAllowEdit = TRUE;
	
	m_lstDest.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_lstDest.SetTreeIndent(30);
	m_lstDest.SetGridColor(RGB(222, 222, 222));
	m_lstDest.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	//m_lstDest.SetPaintManager(new CPaintManager24);

	m_lstStart.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_lstStart.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstStart.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstStart.GetReportHeader()->AllowColumnResize(TRUE);

	m_lstDest.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_lstDest.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstDest.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstDest.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstDest.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstDest.AllowEdit(TRUE);
	
	
	m_lstDest.Populate();
	m_lstStart.Populate();
	
	m_chkGeneralMoto.SetCheck(TRUE);
	m_lstDest.m_bMotoCharge = TRUE;

	

	ChargeTypeNameRefresh();
	
	if(m_bCopyDoc)
		GetDlgItem(IDC_COPY_DONG_BTN)->ShowWindow(SW_HIDE);
			
	m_cmbCompany.SetCurSel(0);
	m_cmbDiscountCompany.SetCurSel(0);

	SetResize(IDC_START_LIST, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_DEST_LIST, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetFlag(xtpResizeNoHorizontal);
	
	InitControl();
	
	if(m_ci.m_nCompanyCode == 10 )
		m_btnText.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChargeDongDlg2::CopyDongDlg()
{
	if(m_CopyDongDlg2 == NULL)
	{
		m_CopyDongDlg2 = new CChargeDongDlg2(this);
		
	}

	m_CopyDongDlg2->m_nCompany = m_nCompany;
	m_CopyDongDlg2->m_bIntegrated = m_bIntegrated;
	m_CopyDongDlg2->m_bCopyDoc = TRUE;
	m_CopyDongDlg2->Create(IDD_CHARGE_DONG_DLG1,this);		
	m_CopyDongDlg2->ShowWindow(SW_SHOW);
	

}

void CChargeDongDlg2::ChargeTypeNameRefresh()
{
	m_cmbDiscountCompany.ResetContent();

	m_cmbDiscountCompany.InsertString(0, "기본요금");
	m_cmbDiscountCompany.SetItemData(0, 0);
	 
	CBranchInfo *p = (CBranchInfo*)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_charge_discount_company2");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), p->nCompanyCode);		
	//pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);		

	long nID = 0;
	int  i = 1;
	CString sChargeName = "";

	if(pRs2.Execute(&pCmd2))
	{

		while(!pRs2.IsEOF())
		{	
			pRs2.GetFieldValue("nID", nID);
			pRs2.GetFieldValue("sChargeName", sChargeName);
			

			m_cmbDiscountCompany.InsertString(i, sChargeName);
			m_cmbDiscountCompany.SetItemData(i++, (DWORD_PTR)nID);
			pRs2.MoveNext();
		}
		pRs2.Close();
	}

	m_cmbDiscountCompany.SetCurSel(0);
}



void CChargeDongDlg2::OnBnClickedDiscountCompanyBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	CString sChargeName = "";
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "신규요금명을 적으세요";
	if(dlg.DoModal() == IDOK)
	{

		sChargeName = dlg.m_sValue;
		if(sChargeName.GetLength() == 0)
			return;

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_chargetype_name");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
		pCmd.AddParameter(typeString, typeInput, sChargeName.GetLength(), sChargeName);
		pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd)) return;
		long nReturnValue = 0;
		pPar->GetValue(nReturnValue);

		if(nReturnValue < 0)
			MessageBox("기존의 등록할 이름과 일치합니다.", "확인", MB_ICONINFORMATION);
		else
		{
			MessageBox("요금제가 신규로 생성되었습니다.","확인", MB_ICONINFORMATION);
			m_cg.FillCharge();
		}

	}
	

	ChargeTypeNameRefresh();
	CString sTypeName = "";
	for(int i = 0; i < m_cmbDiscountCompany.GetCount(); i++)
	{
		m_cmbDiscountCompany.GetLBText(i,sTypeName);
		if(sTypeName == sChargeName)
		{
			m_cmbDiscountCompany.SetCurSel(i);
			return;
		}

	}


}


void CChargeDongDlg2::OnBnClickedDiscountCompanyDelBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(m_cmbDiscountCompany.GetCount() <= 0 )
			return;
	if(m_cmbDiscountCompany.GetCurSel() == 0 )
	{
		MessageBox("기본요금은 삭제하실수 없습니다", "확인",  MB_ICONINFORMATION);
		return;
	}
	if(m_cmbDiscountCompany.GetCurSel() < 0 )
	{
		MessageBox("요금제가 선택되지 않았습니다", "확인",  MB_ICONINFORMATION);
		return;
	}
	
	CString strChargeTypeName = "", sTemp = "";

	int nCur = m_cmbDiscountCompany.GetCurSel();
	m_cmbDiscountCompany.GetLBText(nCur,strChargeTypeName);
	long nChargeTypeID = (long)m_cmbDiscountCompany.GetItemData(nCur);
	sTemp = strChargeTypeName + " 의 해당요금제를 삭제하시겠습니까?\n\r\n\r 요금제가 삭제되면 법인등록된 요금제도 삭제됩니다.\n\r\n\r 삭제하시려면 예(Y)를 눌러주세요";
	if(MessageBox(sTemp,"확인", MB_ICONINFORMATION| MB_YESNO) == IDYES)
	{

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "delete_chargetype_name2");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nChargeTypeID);
		
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd)) return;
		long nReturnValue = 0;
		pPar->GetValue(nReturnValue);

		if(nReturnValue < 0)
			MessageBox("삭제할 해당요금이 서버에 없습니다.", "확인", MB_ICONINFORMATION);
		else
		{
			MessageBox("요금제가 삭제 되었습니다.","확인", MB_ICONINFORMATION);			
			ChargeTypeNameRefresh();
		}

	}
	m_cmbDiscountCompany.SetCurSel(0);
}

void CChargeDongDlg2::InitControl(void)
{	

	if(m_ba.GetCount() > 1)
	{
		int nCurSel = m_cmbCompany.GetCurSel();
		if(nCurSel >= 0)
		{
			CBranchInfo *p = (CBranchInfo*)m_cmbCompany.GetItemData(nCurSel);			
			m_nCompany = p->nCompanyCode;
		}
	}
	CXTPGridRecord *pStartMainRecord = NULL;
	CXTPGridRecord *pDestMainRecord = NULL;
	CXTPGridRecord *pStartSubMainRecord = NULL;
	CXTPGridRecord *pDestSubMainRecord = NULL;
	CXTPGridRecord *pStartthridMainRecord = NULL;
	CXTPGridRecord *pDestthridMainRecord = NULL;	

	CXTPGridRecord *pDestFourthMainRecord = NULL;
	
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_dong_pos_all_1");	 

	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_bUseDetailDong);		

	long nID = 0;
	int nClass;
	BOOL bHasNotDong = FALSE, bPreHasNotDong = FALSE;
	
	CString sSido, sGugun, sGugun2,sSumGugun, sDong, sPreSido = "",sPreGugun = "", 
			sPreGugun2 = "", sPreSumGugun = "", sPreDong = "";
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

			sSumGugun = sGugun + " " + sGugun2;
		
			if(sPreSido != sSido)
			{					
				pStartMainRecord = m_lstStart.AddRecord(new CDetailChargeRecord(0, bHasNotDong, nClass, sSido , "지역구분", FALSE, nID));				
				pDestMainRecord = m_lstDest.AddRecord(new CDetailDestChargeRecord(0, bHasNotDong, nClass, sSido , "지역구분","","", "", "","", "", TRUE, nID));				
				
				sPreSido = sSido;
				continue;
				
			}
			else if(sPreSido == sSido && (sGugun != sPreGugun && sDong.GetLength() == 0) )				
			{
				pStartSubMainRecord = pStartMainRecord->GetChilds()->Add(new CDetailChargeRecord(nID, bHasNotDong, nClass,  sSumGugun , sDong, TRUE, nID));
				pDestSubMainRecord = pDestMainRecord->GetChilds()->Add(new CDetailDestChargeRecord(nID, bHasNotDong, nClass,  sSumGugun , sDong, "","", "", "","","", TRUE, nID));					

				m_pDestRecord.insert(DEST_RECORD_MAP::value_type(nID,(CDetailDestChargeRecord*)pDestSubMainRecord));
			}
			else if(sPreSido == sSido && ( ( sGugun == sPreGugun && sGugun2.GetLength() == 0 && sDong.GetLength() > 0)
									|| (sGugun == sPreGugun && sGugun2 != sPreGugun2 &&  sGugun2.GetLength() > 0 && sDong.GetLength() == 0) ) )
			{				
				pStartthridMainRecord = pStartSubMainRecord->GetChilds()->Add(new CDetailChargeRecord(nID, bHasNotDong, nClass,  sSumGugun + " " , sDong, TRUE, nID));
				pDestthridMainRecord = pDestSubMainRecord->GetChilds()->Add(new CDetailDestChargeRecord(nID, bHasNotDong, nClass,  sSumGugun + " " , sDong,"","","","","","", FALSE, nID));				
				m_pDestRecord.insert(DEST_RECORD_MAP::value_type(nID,(CDetailDestChargeRecord*)pDestthridMainRecord));
			}
			else// sPreSido == sSido && ( (sGugun == sPreGugun && sGugun2 == sPreGugun2 &&  sDong != sPreDong &&  sDong.GetLength() == 0) ) )
			{
				 pStartthridMainRecord->GetChilds()->Add(new CDetailChargeRecord(nID, bHasNotDong, nClass, "", sDong, TRUE, nID));
				 pDestFourthMainRecord = pDestthridMainRecord->GetChilds()->Add(new CDetailDestChargeRecord(nID, bHasNotDong, nClass, "", sDong,"","","","","","", FALSE, nID));		 
				 m_pDestRecord.insert(DEST_RECORD_MAP::value_type(nID,(CDetailDestChargeRecord*)pDestFourthMainRecord));
			}
			
			
			i++;
			sPreSido = sSido;
			sPreGugun = sGugun;
			sPreGugun2 = sGugun2;
			sPreSumGugun = sSumGugun;
			sPreDong = sDong;
			bPreHasNotDong = bHasNotDong;
			pRs2.MoveNext();
		}
		pRs2.Close();
	}
	m_lstStart.Populate();
	m_lstDest.Populate();
}

BOOL CChargeDongDlg2::CheckAreaSelect()
{
	int nStartCurRow = m_lstStart.GetSelectedRows()->GetCount();
	int nDestCurRow = m_lstDest.GetSelectedRows()->GetCount();

	CDetailDestChargeRecord *pDestRecord = NULL;
	CDetailChargeRecord *pStartRecord = NULL;
	for(int i = 0; i < nStartCurRow; i++)
	{
		pStartRecord = (CDetailChargeRecord*)m_lstStart.GetSelectedRows()->GetAt(i);

		CXTPGridRow *pRow = m_lstStart.GetSelectedRows()->GetAt(i);
		pStartRecord = (CDetailChargeRecord*)pRow->GetRecord();

		if(pStartRecord->m_nID == 0)
		{
			MessageBox("출발지에서 맨상위레벨은 요금작업을 하실수 없습니다.(하위레벨참조)","지역선택오류",MB_ICONINFORMATION);
			return FALSE;
		}

		for(int j=0; j < nDestCurRow; j++)
		{
			CXTPGridRow *pRow = m_lstDest.GetSelectedRows()->GetAt(j);
			pDestRecord =  (CDetailDestChargeRecord*)pRow->GetRecord();

			if(pDestRecord->m_nID == 0)
			{
				MessageBox("도착지에서 맨상위레벨은 요금작업을 하실수 없습니다.(하위레벨참조)","지역선택오류",MB_ICONINFORMATION);
				return FALSE;
			}		
			
		}
	}
	return TRUE;

}

BOOL CChargeDongDlg2::IsUpdateOk()
{
	CBranchInfo *p = (CBranchInfo*)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());

	if(p->nCompanyCode == p->nPayTable)
		return TRUE;

	if(p->nPayTable == m_ui.nCompany)
		return TRUE;

	MessageBox("요금 링크를 사용하는 업체는 요금을 수정 하실수 없습니다", "확인", MB_ICONINFORMATION);
	return FALSE;
}

void CChargeDongDlg2::OnBnClickedEditBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	try 
	{		
		if(m_nCompany < 0)
			throw("선택한 지점명이 비정상적입니다. 회사선택을 다시하여주세요");

		if(m_chkGeneralMoto.GetCheck() + m_chkGeneralDama.GetCheck() + m_chkGeneralRabo.GetCheck() +
			m_chkSpecificMoto.GetCheck() + m_chkSpecificDama.GetCheck() +  m_chkSubWay.GetCheck() <= 0)
			throw("수정할 곳이나 입력할 곳을 하나이상 기입하여주세요!");

		int k = m_chkGeneralMoto.GetCheck() + m_chkGeneralDama.GetCheck() + m_chkGeneralRabo.GetCheck() +
			m_chkSpecificMoto.GetCheck() + m_chkSpecificDama.GetCheck() + m_chkSubWay.GetCheck();
		long nCur = m_cmbDiscountCompany.GetCurSel();
		long nGNo = (long)m_cmbDiscountCompany.GetItemData(nCur);


		if(!CheckAreaSelect())
			return;


		CDetailDestChargeRecord *pDestRecord = NULL;
		CDetailChargeRecord *pStartRecord = NULL;
		BOOL bSuccess = FALSE;

		int nStartCurRow = m_lstStart.GetSelectedRows()->GetCount();
		int nDestCurRow = m_lstDest.GetSelectedRows()->GetCount();

		if(!IsUpdateOk())
			return;

		CBranchInfo *p = (CBranchInfo*)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());

		long nPayTable = p->nPayTable;

		for(int i = 0; i < nStartCurRow; i++)
		{
			pStartRecord = (CDetailChargeRecord*)m_lstStart.GetSelectedRows()->GetAt(i);
		
			CXTPGridRow *pRow = m_lstStart.GetSelectedRows()->GetAt(i);
			pStartRecord = (CDetailChargeRecord*)pRow->GetRecord();
			
			for(int j=0; j < nDestCurRow; j++)
			{
				CXTPGridRow *pRow = m_lstDest.GetSelectedRows()->GetAt(j);
				pDestRecord =  (CDetailDestChargeRecord*)pRow->GetRecord();

				 
				CMkCommand pCmd(m_pMkDb, "update_charge_dong_info2012_2");
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nPayTable);		
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nMemCNo);		
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetType(pStartRecord, pDestRecord));
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), pStartRecord->m_nID);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), pDestRecord->m_nID);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), ::GetLongFromEdit(&m_edtCharge11));
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), ::GetLongFromEdit(&m_edtCharge12));
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), ::GetLongFromEdit(&m_edtCharge13));
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), ::GetLongFromEdit(&m_edtCharge14));
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), ::GetLongFromEdit(&m_edtCharge15));
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), ::GetLongFromEdit(&m_edtCharge16));
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkShuttle.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkGeneralMoto.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkGeneralDama.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkGeneralRabo.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkSpecificMoto.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkSpecificDama.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkSubWay.GetCheck());
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ChargeTypeCmb.GetCurSel());
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),nGNo);
				if(!pCmd.Execute()) 
				{
					bSuccess = FALSE;
					throw("입력이 실패되었습니다.");
				}
				/*
				if(m_chkGeneralDama.GetCheck() && m_chkGeneralMoto.GetCheck() &&
					m_chkSpecificDama.GetCheck() && m_chkGeneralMoto.GetCheck() &&
					m_chkSubWay.GetCheck()
					)
				{
					SetAllCharge(pDestRecord->m_nID, nCharge);
				}
				else
				{*/
				 
				if(m_chkGeneralMoto.GetCheck())
					SetCharge(pDestRecord->m_nID,2, ::GetLongFromEdit(&m_edtCharge11)); 

				if(m_chkGeneralDama.GetCheck())
					SetCharge(pDestRecord->m_nID,3, ::GetLongFromEdit(&m_edtCharge12));

				if(m_chkGeneralRabo.GetCheck())
					SetCharge(pDestRecord->m_nID,4, ::GetLongFromEdit(&m_edtCharge13));

				if(m_chkSpecificDama.GetCheck())
					SetCharge(pDestRecord->m_nID,5, ::GetLongFromEdit(&m_edtCharge14));

				if(m_chkSpecificMoto.GetCheck())
					SetCharge(pDestRecord->m_nID,6, ::GetLongFromEdit(&m_edtCharge15));
				
				if(m_chkSubWay.GetCheck())
					SetCharge(pDestRecord->m_nID,7, ::GetLongFromEdit(&m_edtCharge16));
				//}				
			}
			
		}
		m_lstDest.Populate();
	}
	catch (char* e)
	{
		MessageBox(e,"", MB_ICONINFORMATION);
	}
	

}
int CChargeDongDlg2::GetType(CDetailChargeRecord *pStartRecord, CDetailDestChargeRecord *pDestRecord)
{
	int nStartType = pStartRecord->GetTypeInfo();
	int nDestType = pDestRecord->GetTypeInfo();
	int nType = 0;

	if (nStartType <= 0 || nStartType > 3 || nDestType <= 0 || nDestType > 3	)
		MessageBox("출발지및 도착지 타입이 잘못되었습니다.", "확인",	MB_ICONINFORMATION);

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

void CChargeDongDlg2::OnViewListPrint()
{

	CDetailChargeRecord *pReocrd = (CDetailChargeRecord *)m_lstStart.GetSelectedRows()->GetAt(0)->GetRecord();
	
	
	
	long nDongID = pReocrd->m_nDongID;

	if(m_nCompany <= 0 && nDongID <= 0)
	{
		MsgBox("회사및 동이 적용되지 않았습니다.");
		return;
	}
	CWebChargeListDlg dlg;
	dlg.m_nCompany = m_nCompany;
	dlg.m_nDongID = nDongID;
	dlg.DoModal();


}


void CChargeDongDlg2::OnReportStartItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CPoint point;
	::GetCursorPos(&point);

	OnContextMenu(&m_lstStart, point);
}


void CChargeDongDlg2::OnReportBeginEdit(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*)pNotifyStruct;

	int nCol = pItemNotify->pColumn->GetIndex();
	if(nCol > 1)
	{
		if(!CheckAreaSelect())
		{
			pItemNotify->pItem->SetCaption("");
			return;
		}
	}
	return;


}
void CChargeDongDlg2::OnReportDestItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	//if (!pItemNotify->pRow || !pItemNotify->pColumn)
	//	return;

	CPoint point;
	::GetCursorPos(&point);

	OnContextMenu(&m_lstDest, point);
}

void CChargeDongDlg2::OnReportStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;
	
	int nRow = pItemNotify->pRow->GetIndex();

	CDetailChargeRecord *pRecord = (CDetailChargeRecord *)pItemNotify->pRow->GetRecord();
	if(pRecord->m_nID == 0)
		return;

	if(m_lstStart.GetSelectedRows()->GetCount() > 1)
		return;

	if(this->m_chkNotChargeQuery.GetCheck())
		return;

	//SaveCharge(FALSE);
	RefreshList();
}

void CChargeDongDlg2::OnReportDestItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;  
 
	m_pPreSelectRow = m_lstStart.GetSelectedRows()->GetAt(0);

	CDetailDestChargeRecord *pRecord = (CDetailDestChargeRecord*)pItemNotify->pRow->GetRecord();
	long nRow = pItemNotify->pRow->GetIndex();
	long nCol = pItemNotify->pColumn->GetIndex();

	if(nCol > 1)
	{
		m_vecDest.push_back(pRecord); 
		((CXTPGridRecordItemText*)pRecord->GetItem(nCol))->SetValue("");
		((CXTPGridRecordItemText*)pRecord->GetItem(nCol))->SetCaption("");
	}
}


void CChargeDongDlg2::OnBnClickedDeleteBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	CDetailDestChargeRecord *pDestRecord = NULL;
	CDetailChargeRecord *pStartRecord = NULL;
	BOOL bSuccess = FALSE;
	DEST_RECORD_MAP::iterator it;
	
	
	int nStartCurRow = m_lstStart.GetSelectedRows()->GetCount();
	int nDestCurRow = m_lstDest.GetSelectedRows()->GetCount();
	int nGNo = 0, nCur = 0;
	nCur = m_cmbDiscountCompany.GetCurSel();
	if(nCur == 0)
		nGNo = 0;
	else
		nGNo = (long)m_cmbDiscountCompany.GetItemData(nCur);

	for(int i = 0; i < nStartCurRow; i++)
	{
		pStartRecord = (CDetailChargeRecord*)m_lstStart.GetSelectedRows()->GetAt(i);

		CXTPGridRow *pRow = m_lstStart.GetSelectedRows()->GetAt(i);
		pStartRecord = (CDetailChargeRecord*)pRow->GetRecord();

		for(int j=0; j < nDestCurRow; j++)
		{
		
			CXTPGridRow *pRow = m_lstDest.GetSelectedRows()->GetAt(j);
			pDestRecord = (CDetailDestChargeRecord*)pRow->GetRecord();
 
			CMkCommand pCmd(m_pMkDb, "delete_charge_dong_info2012_1");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);					
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pStartRecord->m_nID);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pDestRecord->m_nID);
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkShuttle.GetCheck());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkGeneralDama.GetCheck());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkGeneralMoto.GetCheck());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkGeneralRabo.GetCheck());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkSpecificDama.GetCheck());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkSpecificMoto.GetCheck());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkSubWay.GetCheck());

			pCmd.AddParameter(typeLong, typeInput, sizeof(int),	this->m_ChargeTypeCmb.GetCurSel());
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nGNo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nMemCNo);	

			if(!pCmd.Execute())
			{
				MessageBox("삭제시 에러가 났습니다.","확인",MB_ICONINFORMATION);
				return;
			}

			it = m_pDestRecord.find(pDestRecord->m_nID);
			
			pDestRecord = (CDetailDestChargeRecord *)it->second;
			if(m_chkGeneralDama.GetCheck())
                pDestRecord->SetGeneralDaMa("");
			if(m_chkGeneralMoto.GetCheck())
                pDestRecord->SetGeneralMoto("");
			if(m_chkGeneralRabo.GetCheck())
				pDestRecord->SetGeneralRabo("");
			if(m_chkSpecificDama.GetCheck())
				pDestRecord->SetSpecificDaMa("");
			if(m_chkSpecificMoto.GetCheck())
				pDestRecord->SetSpecificMoto("");
			if(m_chkSubWay.GetCheck())
				pDestRecord->SetSpecificSubWay("");
			
		}
	}
	m_lstDest.Populate();
	MessageBox("정상적으로 삭제되었습니다.");
		


	

}

void CChargeDongDlg2::SetAllCharge(long nID, long nCharge)
{
	char buffer[10];
	DEST_RECORD_MAP::iterator it;
	it = m_pDestRecord.find(nID);
	CDetailDestChargeRecord * pDestRecord = (CDetailDestChargeRecord *)it->second;	
	CString sCharge = ltoa(nCharge, buffer,10);
	pDestRecord->SetGeneralMoto(sCharge);
	pDestRecord->SetGeneralDaMa(sCharge);
	pDestRecord->SetSpecificMoto(sCharge);
	pDestRecord->SetSpecificDaMa(sCharge);
	pDestRecord->SetSpecificSubWay(sCharge);
	
	
}
void CChargeDongDlg2::OnSize(UINT nType, int cx, int cy)
{
	CXTResizeDialog::OnSize(nType, cx, cy);
}
void CChargeDongDlg2::ChargeAllDelete()
{
	DEST_RECORD_MAP::iterator it;

	for(it = m_pDestRecord.begin(); it != m_pDestRecord.end(); it++)
	{
		CDetailDestChargeRecord * pDestRecord = (CDetailDestChargeRecord *)it->second;
		pDestRecord->SetGeneralMoto("");
		pDestRecord->SetGeneralDaMa("");
		pDestRecord->SetGeneralRabo("");
		pDestRecord->SetSpecificMoto("");
		pDestRecord->SetSpecificDaMa("");
		pDestRecord->SetSpecificSubWay("");
		
	}

}
void CChargeDongDlg2::SetCharge(long nDestID, int nCol, long nCharge)
{
	char buffer[10];
	DEST_RECORD_MAP::iterator it;
	it = m_pDestRecord.find(nDestID);
	CDetailDestChargeRecord * pDestRecord = (CDetailDestChargeRecord *)it->second;
	if(nCol == 2)
		pDestRecord->SetGeneralMoto(ltoa(nCharge, buffer,10));
	else if(nCol == 3)
		pDestRecord->SetGeneralDaMa(ltoa(nCharge, buffer,10));
	else if(nCol == 4)
		pDestRecord->SetGeneralRabo(ltoa(nCharge, buffer,10));
	else if(nCol == 5)
		pDestRecord->SetSpecificDaMa(ltoa(nCharge, buffer,10));
	else if(nCol == 6)
		pDestRecord->SetSpecificMoto(ltoa(nCharge, buffer,10));
	else if(nCol == 7)
		pDestRecord->SetSpecificSubWay(ltoa(nCharge, buffer,10));
}

void CChargeDongDlg2::SetAllCharge(long nDestID, long nMotoCharge, long nDamaCharge, long nRaboCharge,
								   long nSpecificMoto, long nSpecificDama, long nSubWayCharge)
{
	char buffer[10];
	DEST_RECORD_MAP::iterator it;
	it = m_pDestRecord.find(nDestID);

	if(it == m_pDestRecord.end()) return;

	CDetailDestChargeRecord * pDestRecord = (CDetailDestChargeRecord *)it->second;

	
	CString sMoto = ltoa(nMotoCharge, buffer, 10);
	CString sDama = ltoa(nDamaCharge, buffer, 10);
	CString sRabo = ltoa(nRaboCharge, buffer, 10);
	CString sSpecificMoto = ltoa(nSpecificMoto, buffer, 10);
	CString sSpecificDama = ltoa(nSpecificDama, buffer, 10);
	CString sSpecificSubWay = ltoa(nSubWayCharge, buffer, 10);

	pDestRecord->SetGeneralMoto(sMoto);
	pDestRecord->SetGeneralDaMa(sDama);
	pDestRecord->SetGeneralRabo(sRabo);
	pDestRecord->SetSpecificMoto(sSpecificMoto);
	pDestRecord->SetSpecificDaMa(sSpecificDama);
	pDestRecord->SetSpecificSubWay(sSpecificSubWay);
}
void CChargeDongDlg2::OnCbnSelchangeDisComCombo()
{
	RefreshList();
}

void CChargeDongDlg2::RefreshList()
{
	ChargeAllDelete();
	
	CXTPGridRow *pRow = NULL;
	if(m_lstStart.GetSelectedRows()->GetCount() == 1)
	{
		pRow = m_lstStart.GetSelectedRows()->GetAt(0);
	}
	else
	{		
		m_lstDest.Populate();
		return;
	}	

	int nRow = pRow->GetIndex();
	CDetailChargeRecord *pRecord = (CDetailChargeRecord *)pRow->GetRecord();
	
	if(pRecord->m_nID == 0)
		return;

	long nGNo = 0,nCur = 0,nCompany = 0, nCompanySel = 0;
	nCur = m_cmbDiscountCompany.GetCurSel();
	nGNo = (long)m_cmbDiscountCompany.GetItemData(nCur);	
	nCompanySel = m_cmbCompany.GetCurSel();

	CBranchInfo *p = (CBranchInfo*)m_cmbCompany.GetItemData(nCompanySel);

	//nCompany = m_cmbCompany.GetItemData(nCompanySel);
	

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, ""); 
	//CMkCommand pCmd(m_pMkDb, "select_charge_dong_total2012_1"); 안쓰는듯 에러나게함 choe
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), p->nPayTable);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), pRecord->m_nID); 
	pCmd.AddParameter(IsHTypeViewMode());	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nGNo);	
	pCmd.AddParameter(GetHTypeCNo());	

	long nDestID = 0, nMotoCharge = 0,nDamaCharge = 0 ;
	long nBonggoCharge = 0, nTruckCharge = 0, nSubWayCharge = 0, nRaboCharge = 0;
	int nType = 0;
	BOOL bShuttle = FALSE;
	CDetailDestChargeRecord *pDestRecord = NULL;	
	CString sType = "";

	if(pRs.Execute(&pCmd))
	{
		if(pRs.GetRecordCount() == 0)
		{
			ChargeAllDelete();
		}
		else
		{			
			m_ChargeTypeCmb.GetLBText(m_ChargeTypeCmb.GetCurSel(), sType);
			CString sMoto =		(nGNo == 0 && m_nMemCNo == 0) ? "nMotoCharge" + sType.Left(1) : "nMotoCharge";
			CString sDama =		(nGNo == 0 && m_nMemCNo == 0) ? "nDamaCharge" + sType.Left(1) : "nDamaCharge";
			CString sRabo =		(nGNo == 0 && m_nMemCNo == 0) ? "nRaboCharge" + sType.Left(1) : "nRaboCharge";
			CString sBonggo =	(nGNo == 0 && m_nMemCNo == 0) ? "nBonggoCharge" + sType.Left(1) : "nBonggoCharge";
			CString sTruck =	(nGNo == 0 && m_nMemCNo == 0) ? "nTruckCharge" + sType.Left(1) : "nTruckCharge" ;			
			CString sSubWay =	(nGNo == 0 && m_nMemCNo == 0) ? "nSubWayCharge" + sType.Left(1) : "nSubWayCharge" ;			
			

			for(long i=0; i<pRs.GetRecordCount(); i++)
			{
				pRs.GetFieldValue("nDestID", nDestID);				
				pRs.GetFieldValue(sMoto, nMotoCharge);
				pRs.GetFieldValue(sDama, nDamaCharge);
				pRs.GetFieldValue(sRabo, nRaboCharge);
				pRs.GetFieldValue(sTruck, nTruckCharge);
				pRs.GetFieldValue(sBonggo, nBonggoCharge);				
				pRs.GetFieldValue(sSubWay, nSubWayCharge);				

				SetAllCharge(nDestID,nMotoCharge, nDamaCharge, nRaboCharge, nTruckCharge, nBonggoCharge, nSubWayCharge);			

				pRs.MoveNext();
			}	
		}

		pRs.Close();
	}


	////---------------------------> 동위의 구간접 표시

	//pRecord->GetTypeInfo()
	//pRow->GetParentRow()
	CXTPGridRow *pParentRow = pRow->GetParentRow();
	CXTPGridRow *pPParentRow = (pRow->GetParentRow())->GetParentRow();
	int nDepth =  pRow->GetTreeDepth(); 
    int nTypeInfo = pRecord->GetTypeInfo();

	m_lstDest.Populate();
}

void CChargeDongDlg2::OnBnClickedAllDelCheck()
{
	if(m_chkAllDel.GetCheck())
	{
		m_chkGeneralMoto.SetCheck(TRUE);
		//m_lstDest.m_bMotoCharge = TRUE;
		m_chkGeneralDama.SetCheck(TRUE);
		m_chkGeneralRabo.SetCheck(TRUE);
		//m_lstDest.m_bDamaCharge = TRUE;
		m_chkSpecificMoto.SetCheck(TRUE);
		//m_lstDest.m_bTruckCharge = TRUE;
		m_chkSpecificDama.SetCheck(TRUE);
		//m_lstDest.m_bBonggoCharge = TRUE;

		m_chkSubWay.SetCheck(TRUE);
		//m_lstDest.m_bSubWayCharge = TRUE;
	}
	else
	{
		m_chkGeneralMoto.SetCheck(FALSE);
		//m_lstDest.m_bMotoCharge = FALSE;
		m_chkGeneralDama.SetCheck(FALSE);
		m_chkGeneralRabo.SetCheck(FALSE);
		//m_lstDest.m_bDamaCharge = FALSE;
		m_chkSpecificMoto.SetCheck(FALSE);
		//m_lstDest.m_bTruckCharge = FALSE;
		m_chkSpecificDama.SetCheck(FALSE);
		//m_lstDest.m_bBonggoCharge = FALSE;

		m_chkSubWay.SetCheck(FALSE);
		//m_lstDest.m_bSubWayCharge = FALSE;
	}
	m_lstDest.Populate();
}



void CChargeDongDlg2::OnBnClickedLineBtn()
{
	CLineDlg dlg;
	dlg.m_nCompany = m_nCompany;
	
	dlg.DoModal();
}

void CChargeDongDlg2::OnCbnSelchangeCompanyCombo()
{
	if(m_cmbDiscountCompany.GetCurSel() > 0)
		m_ChargeTypeCmb.SetCurSel(0);

	if(m_ChargeTypeCmb.GetCurSel() > 0)
		m_cmbDiscountCompany.SetCurSel(0);

	long nCompanySel  = 0;
	//m_nCompany = m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());

	

	RefreshList();	
	ChargeTypeNameRefresh();
}

void CChargeDongDlg2::OnCbnSelchangeChargeTypeCombo()
{
	if(m_ChargeTypeCmb.GetCurSel() > 0)
		m_cmbDiscountCompany.SetCurSel(0);

	RefreshList();
	
}
void CChargeDongDlg2::OnBnClickedCopyDongBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	CopyDongDlg();
	
}

void CChargeDongDlg2::OnBnClickedChargeTypeBtn()
{
	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	CChargeWorkDlg dlg;
	dlg.m_nCompany = m_nCompany;

	dlg.DoModal();
	
}


void CChargeDongDlg2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(m_lstStart.GetSelectedRows()->GetCount() == 0)
	{
		MessageBox("출발지를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_lstStart.GetSelectedRows()->GetCount() != 1)
	{
		MessageBox("출발지 리스트에 하나만 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	if(pWnd->GetSafeHwnd() == m_lstStart.GetSafeHwnd())
	{
		BCMenu rChargeMenu;
		rChargeMenu.LoadMenu(IDR_GROUP_MENU1);

		BCMenu* pChargeRMenu = (BCMenu*)rChargeMenu.GetSubMenu(1);
		pChargeRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		
		return;
	}

	if(m_lstDest.GetSelectedRows()->GetCount() == 0)
	{
		MessageBox("도착지를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_lstDest.GetSelectedRows()->GetCount() != 1)
	{
		MessageBox("도착지 리스트에 하나만 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CDetailChargeRecord *pStartRecord = NULL;
	CDetailDestChargeRecord *pDestRecord = NULL;

	pStartRecord = (CDetailChargeRecord*)m_lstStart.GetSelectedRows()->GetAt(0)->GetRecord();
	pDestRecord = (CDetailDestChargeRecord*)m_lstDest.GetSelectedRows()->GetAt(0)->GetRecord();

	CXTPGridColumn *pColumn = NULL; 

	CString sDong = ((CXTPGridRecordItemText*)pStartRecord->GetItem(1))->GetCaption(pColumn);

	if(FALSE == pStartRecord->m_bExcel)
	{
		MessageBox("출발지(동)을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	} 

	if(FALSE ==pDestRecord->m_bExcel) 
	{
		MessageBox("도착시 구(시) 이상 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);

	BCMenu* pRMenu = (BCMenu*)rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CChargeDongDlg2::OnViewExcel()
{

	CXTPGridRow *pStartRow = NULL;
	pStartRow = m_lstStart.GetSelectedRows()->GetAt(0);

	CXTPGridRow *pDestRow = NULL;
	pDestRow = m_lstDest.GetSelectedRows()->GetAt(0);

	CDetailChargeRecord *pStartRecord = (CDetailChargeRecord *)pStartRow->GetRecord();
	CDetailDestChargeRecord *pDestRecord = (CDetailDestChargeRecord *)pDestRow->GetRecord();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_chargedong_for_excel"); 
	
	CXTPGridColumn *pColumn = NULL;   

	CString sStart = ((CXTPGridRecordItemText*)(pStartRecord->GetItem(0)))->GetCaption(pColumn) + "/" +
		((CXTPGridRecordItemText*)(pStartRecord->GetItem(1)))->GetCaption(pColumn);
	 
	CString sDest = ((CXTPGridRecordItemText*)(pDestRecord->GetItem(0)))->GetCaption(pColumn) + "/" +
		((CXTPGridRecordItemText*)(pDestRecord->GetItem(1)))->GetCaption(pColumn);

	sStart.Replace(" ", "");
	sDest.Replace(" ", "");
					

	//지역구분 이라는 단어가 시;

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);		
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), pStartRecord->m_nDongID);
	pCmd.AddParameter(typeString, typeInput, sStart.GetLength(), sStart);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), pDestRecord->m_nDongID);
	pCmd.AddParameter(typeString, typeInput, sDest.GetLength(), sDest);

	if(!pRs.Execute(&pCmd))
	{
		MessageBox("잠시후에 다시 시도하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(!POWER_CHECK(1900, "엑셀변환", TRUE))
		return;

	AddSecurityLog(GetCurBranchInfo()->nDOrderTable, 801, pRs.GetRecordCount());  
	CMyExcel::ToExcel(&pRs);

	pRs.Close();

}


void CChargeDongDlg2::OnBnClickedSearchGroupBtn()
{
	CSearchGroupDlg dlg;
	dlg.m_nDataType = SG_DISCOUNT_COMPANY;
	dlg.m_nCompany = m_nCompany;

	if(dlg.DoModal() == IDOK)
	{
		for(int i = 0; i < m_cmbDiscountCompany.GetCount(); i++)
		{
			long nGNo = (long)m_cmbDiscountCompany.GetItemData(i);
			if(dlg.m_nChargeID == nGNo)
			{
                m_cmbDiscountCompany.SetCurSel(i);				
				break;
			}
		}
	}
}




void CChargeDongDlg2::OnBnClickedSameCheckBtn()
{
	if(m_lstStart.GetSelectedRows()->GetCount() == 0)
		MsgBox("한개라도 체크해주세요");

	/*g_bana_log->Print("갯수: %d", m_lstStart.GetSelectedRows()->GetCount());

	g_bana_log->Print("총갯수:%d", m_lstStart.GetRecords()->GetCount());
	g_bana_log->Print("총레코드갯수:%d", m_lstStart.GetRecords()->GetCount());
	g_bana_log->Print("총로우갯수:%d", m_lstStart.GetRows()->GetCount());*/
	
	
	//DEST_RECORD_MAP::iterator it;
	//it = m_pDestRecord.find(nID);	
	//this->m_lstDest.ExpandAll();

	if(m_nFirstWork == 0)
	{
		MsgBox("이작업을 하기 위해서는 양쪽 트리를 전부 여셔야 합니다.");
		m_nFirstWork++;
	}

	long nStartDongID = 0,nSameCount = 0;
	for(int nRow = 0; nRow < m_lstDest.GetSelectedRows()->GetCount(); nRow++)
	{
		CXTPGridRow *pRow = (CXTPGridRow *)m_lstDest.GetSelectedRows()->GetAt(nRow);
		pRow->SetSelected(FALSE);
	}
	
	int i = 0;
	for(i = 0; i < m_lstStart.GetSelectedRows()->GetCount(); i++)
	{
		CDetailChargeRecord *pRecord = (CDetailChargeRecord *)m_lstStart.GetSelectedRows()->GetAt(i)->GetRecord();
		long nStartDongID = pRecord->m_nDongID;

		
		for(int i = 0; i<  m_lstDest.GetRows()->GetCount(); i++)
		{
			CXTPGridRow *pRow = m_lstDest.GetRows()->GetAt(i);
			if(pRow == NULL)
				continue;

			long nDestDongID = ((CDetailChargeRecord*)pRow->GetRecord())->m_nDongID;
		
			if(nStartDongID == nDestDongID)
			{
				pRow->GetRecord()->SetExpanded(TRUE);
				pRow->SetSelected(TRUE);
				nSameCount++;
				//g_bana_log->Print("Same = %d", i); 
				//pRow->GetRecord()->SetVisible(TRUE);

			}
		}
	}
	CString sViewText;
	sViewText.Format("L:%d - R:%d", i, nSameCount);
	m_btnSameView.SetWindowText(sViewText);
	
	
	
}

void CChargeDongDlg2::OnBnClickedButton2()
{
	int nRows = m_lstDest.GetSelectedRows()->GetCount();
	g_bana_log->Print("GetRow : %d\n" , nRows);
}

void CChargeDongDlg2::OnBnClickedSelectareaMemoryBtn()
{

	if(!POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(m_pChargeDongSettingDlg == NULL)
	{
		m_pChargeDongSettingDlg = new CChargeDongSettingDlg(this);
		m_pChargeDongSettingDlg->Create(IDD_CHARGE_SETTING_DLG, this);
		m_pChargeDongSettingDlg->m_nCompany = m_ci.m_nCompanyCode;

	}
	
	m_pChargeDongSettingDlg->ShowWindow(SW_SHOW);
	
}



void CChargeDongDlg2::OnBnClickedSameViewBtn()
{

}

void CChargeDongDlg2::OnBnClickedChargeListBtn()
{
	CChargeListSetDlg dlg;
	dlg.DoModal();
}

void CChargeDongDlg2::OnBnClickedSaveBtn()
{
	SaveCharge(TRUE);	
}



void CChargeDongDlg2::OnReportValueChanged(NMHDR*  pNotifyStruct, LRESULT* /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify != NULL);

	try
	{
		long nCharge = 0, nDestDongID = 0, nCompany = 0;
		CDetailChargeRecord *pStartRecord = NULL;
		CDetailDestChargeRecord	*pDestRecord = NULL;
		CString sError= "", sCharge = "";

		if (!pItemNotify->pRow || !pItemNotify->pColumn)
			return;

		if(pItemNotify->pColumn->GetIndex() <= 1)
			return;

		long nGNo = (long)m_cmbDiscountCompany.GetItemData(m_cmbDiscountCompany.GetCurSel());
		long bToWay = m_chkShuttle.GetCheck();
		long nChargeType = m_ChargeTypeCmb.GetCurSel();
		
		

		CXTPGridRecordItemText *pItemNumber = (CXTPGridRecordItemText *)pItemNotify->pItem;
		sCharge   = pItemNumber->GetValue(); sCharge.Replace(",", "");
		if(!IsStringDigit(sCharge))
			throw("숫자가 아닙니다.");

		nCharge = atol(sCharge);
		if(nCharge > 5000000 || nCharge < 0)
			throw("금액이 너무 많거나 적습니다. ");


		pDestRecord = (CDetailDestChargeRecord*)pItemNotify->pRow->GetRecord();		
		nDestDongID = pDestRecord->m_nID;
		//nCompany =  (long)GET_CUR_BRANCH(m_cmbCompany.GetCurSel());
		nCompany = m_nCompany; // m_cBranch.GetBranchInfo()->nCompanyCode;

		if(nCompany < 0)
			throw("선택한 지점명이 비정상적입니다. 회사선택을 다시하여주세요");


		int nStartCurRow = m_lstStart.GetSelectedRows()->GetCount();
		int nDestCurRow = m_lstDest.GetSelectedRows()->GetCount();

		if(!IsUpdateOk())
			return;

		CBranchInfo *p = (CBranchInfo*)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());

		long nPayTable = p->nPayTable;
		

		for(int i = 0; i < m_lstStart.GetSelectedRows()->GetCount(); i++)
		{			
			pStartRecord = (CDetailChargeRecord *)m_lstStart.GetSelectedRows()->GetAt(i)->GetRecord();
			long nStartDongID = pStartRecord->m_nID; //((CPOIInfo*)pStartRecord->GetItemData())->nDongID;
			long nType = GetType(pStartRecord, pDestRecord);

			long nPreGenerateMoto = pDestRecord->m_nGeneralMoto;
			long nPreGenerateDama = pDestRecord->m_nGeneralDama;
			long nPreSpecificMoto = pDestRecord->m_nSpecificMoto;
			long nPreSpecificDama = pDestRecord->m_nSpecificDama;
			long nPreSpecificSubWay = pDestRecord->m_nSubWay;
			long nPreGenerateRabo = pDestRecord->m_nGeneralRabo;

			CString sCurGenerateMoto = (CString)(pDestRecord->GetItem(2)->GetCaption(NULL));
			CString sCurGenerateDama = (CString)(pDestRecord->GetItem(3)->GetCaption(NULL));
			CString sCurGenerateRabo = (CString)(pDestRecord->GetItem(4)->GetCaption(NULL));
			CString sCurSpecificMoto = (CString)(pDestRecord->GetItem(5)->GetCaption(NULL));
			CString sCurSpecificDama = (CString)(pDestRecord->GetItem(6)->GetCaption(NULL));
			CString sCurSpecificSubWay = (CString)(pDestRecord->GetItem(7)->GetCaption(NULL));

			sCurGenerateMoto.Replace(",", "");
			sCurGenerateDama.Replace(",", "");
			sCurSpecificMoto.Replace(",", "");
			sCurSpecificDama.Replace(",", "");
			sCurSpecificSubWay.Replace(",", "");
			sCurGenerateRabo.Replace(",", "");

			long nCurGenerateMoto = _ttoi(sCurGenerateMoto);
			long nCurGenerateDama = _ttoi(sCurGenerateDama);
			long nCurSpecificMoto = _ttoi(sCurSpecificMoto);
			long nCurSpecificDama = _ttoi(sCurSpecificDama);
			long nCurSpecificSubWay = _ttoi(sCurSpecificSubWay);
			long nCurGenerateRabo = _ttoi(sCurGenerateRabo);
			
			if((nPreGenerateMoto != nCurGenerateMoto) ||
				(nPreGenerateDama != nCurGenerateDama) ||
				(nPreGenerateRabo != nCurGenerateRabo) ||
				(nPreSpecificMoto != nCurSpecificMoto) ||
				(nPreSpecificDama != nCurSpecificDama)	||
				(nPreSpecificSubWay != nCurSpecificSubWay)	
				)
			{ 
				long nDestID = pDestRecord->m_nID;

				CMkCommand pCmd(m_pMkDb, "update_charge_dong_real2012_1");
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nPayTable);		
				//pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetType(pStartRecord, pDestRecord));
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), nType);
				//pCmd.AddParameter(typeLong, typeInput, sizeof(int), pStartRecord->m_nID);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), nStartDongID);
				//pCmd.AddParameter(typeLong, typeInput, sizeof(int), pDestRecord->m_nID);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), nDestID);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), bToWay);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurGenerateMoto);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurGenerateDama);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurGenerateRabo);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurSpecificMoto);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurSpecificDama);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurSpecificSubWay);
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), nChargeType);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),nGNo);
				pCmd.AddParameter(IsHTypeViewMode());
				pCmd.AddParameter(m_nMemCNo);

				if(pCmd.Execute())
				{
					pDestRecord->m_nGeneralMoto = nCurGenerateMoto;
					pDestRecord->m_nGeneralDama = nCurGenerateDama;
					pDestRecord->m_nSpecificMoto = nCurSpecificMoto;
					pDestRecord->m_nSpecificDama = nCurSpecificDama;
					pDestRecord->m_nSubWay = nCurSpecificSubWay;
				}

			}



		}

		//pDestRecord->Set>SetDirtyFlag()>m_bDirtyFlag = FALSE;



	}
	catch (CString s)
	{
		MessageBox(s, "확인", MB_ICONINFORMATION);		

	}
	catch (char *e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);		
	}
	//	
}

void CChargeDongDlg2::SaveCharge(BOOL bClick)
{
	long nCount = m_vecDest.size();

	if(nCount == 0)
		return; 

	CXTPGridRow *pRow = NULL;
	
	if(bClick)
		pRow = m_lstStart.GetSelectedRows()->GetAt(0);
	else
		pRow = m_pPreSelectRow;

	CDetailChargeRecord *pStartReport = (CDetailChargeRecord*)pRow->GetRecord();

	
	long nStartID = pStartReport->m_nID;
	long nGNo = (long)m_cmbDiscountCompany.GetItemData(m_cmbDiscountCompany.GetCurSel());
	long bToWay = m_chkShuttle.GetCheck();
	long nChargeType = m_ChargeTypeCmb.GetCurSel();
	
	for(int i=0; i<m_vecDest.size(); i++)
	{
		CDetailDestChargeRecord * pDestReport = m_vecDest.at(i);
		long nType = GetType(pStartReport, pDestReport);

		long nPreGenerateMoto = pDestReport->m_nGeneralMoto;
		long nPreGenerateDama = pDestReport->m_nGeneralDama;
		long nPreGenerateRabo = pDestReport->m_nGeneralRabo;
		long nPreSpecificMoto = pDestReport->m_nSpecificMoto;
		long nPreSpecificDama = pDestReport->m_nSpecificDama;
		long nPreSpecificSubWay = pDestReport->m_nSubWay;

		CString sCurGenerateMoto = (CString)(pDestReport->GetItem(2)->GetCaption(NULL));
		CString sCurGenerateDama = (CString)(pDestReport->GetItem(3)->GetCaption(NULL));
		CString sCurGenerateRabo = (CString)(pDestReport->GetItem(4)->GetCaption(NULL));
		CString sCurSpecificMoto = (CString)(pDestReport->GetItem(5)->GetCaption(NULL));
		CString sCurSpecificDama = (CString)(pDestReport->GetItem(6)->GetCaption(NULL));
		CString sCurSpecificSubWay = (CString)(pDestReport->GetItem(7)->GetCaption(NULL));

		sCurGenerateMoto.Replace(",", "");
		sCurGenerateDama.Replace(",", "");
		sCurGenerateRabo.Replace(",", "");
		sCurSpecificMoto.Replace(",", "");
		sCurSpecificDama.Replace(",", "");
		sCurSpecificSubWay.Replace(",", "");

		long nCurGenerateMoto = _ttoi(sCurGenerateMoto);
		long nCurGenerateDama = _ttoi(sCurGenerateDama);
		long nCurGenerateRabo = _ttoi(sCurGenerateRabo);
		long nCurSpecificMoto = _ttoi(sCurSpecificMoto);
		long nCurSpecificDama = _ttoi(sCurSpecificDama);
		long nCurSpecificSubWay = _ttoi(sCurSpecificSubWay);

		if((nPreGenerateMoto != nCurGenerateMoto) ||
			(nPreGenerateDama != nCurGenerateDama) ||
			(nPreGenerateRabo != nCurGenerateRabo) ||
			(nPreSpecificMoto != nCurSpecificMoto) ||
			(nPreSpecificDama != nCurSpecificDama)	||
			(nPreSpecificSubWay != nCurSpecificSubWay)	
			)
		{ 
			long nDestID = pDestReport->m_nID;

			CMkCommand pCmd(m_pMkDb, "update_charge_dong_real2012_1");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);		
			//pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetType(pStartRecord, pDestRecord));
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nType);
			//pCmd.AddParameter(typeLong, typeInput, sizeof(int), pStartRecord->m_nID);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nStartID);
			//pCmd.AddParameter(typeLong, typeInput, sizeof(int), pDestRecord->m_nID);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nDestID);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), bToWay);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurGenerateMoto);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurGenerateDama);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurGenerateRabo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurSpecificMoto);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurSpecificDama);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCurSpecificSubWay);

			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nChargeType);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long),nGNo);
			pCmd.AddParameter(IsHTypeViewMode());
			pCmd.AddParameter(m_nMemCNo);

			if(pCmd.Execute())
			{
				pDestReport->m_nGeneralMoto = nCurGenerateMoto;
				pDestReport->m_nGeneralDama = nCurGenerateDama;
				pDestReport->m_nSpecificMoto = nCurSpecificMoto;
				pDestReport->m_nSpecificDama = nCurSpecificDama;
				pDestReport->m_nSubWay = nCurSpecificSubWay;
			}

		}

	}

	m_vecDest.clear();
}

void CChargeDongDlg2::OnLButtonUp(UINT nFlags, CPoint point)
{
	CXTResizeDialog::OnLButtonUp(nFlags, point);
}

void CChargeDongDlg2::OnBnClickedSearchSaveBtn()
{
	long nFirst = m_cmbSearch[0].GetCurSel();
	long nSecond = m_cmbSearch[1].GetCurSel();
	long nThird = m_cmbSearch[2].GetCurSel();
	long nFourth = m_cmbSearch[3].GetCurSel();
	

	if((nFirst == nSecond) || (nFirst == nThird) || (nFirst == nFourth) ||
		(nSecond == nThird) || (nSecond == nFourth) || (nThird == nFourth))
	{
		MessageBox("순서가 중복되어있습니다\r\n 다시 설정해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strTemp = "";
	strTemp.Format("%d;%d;%d;%d;", nFirst, nSecond, nThird, nFourth);

	CMkCommand pCmd(m_pMkDb, "update_charge_search_order");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(strTemp);

	if(pCmd.Execute())
	{
		m_ci.m_nChargeSearchOrder[0] = nFirst;
		m_ci.m_nChargeSearchOrder[1] = nSecond;
		m_ci.m_nChargeSearchOrder[2] = nThird;
		m_ci.m_nChargeSearchOrder[3] = nFourth;
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
	}
}


void CChargeDongDlg2::OnBnClickedUserBtn()
{
CChargeDongUDlg dlg;
dlg.DoModal();
}

BOOL CChargeDongDlg2::PreTranslateMessage(MSG* pMsg)
{
	return CXTResizeDialog::PreTranslateMessage(pMsg);
}


void CChargeDongDlg2::FocusUp(CXTPGridControl *pControl)
{
	POSITION pos = pControl->GetSelectedRows()->GetFirstSelectedRowPosition();
	int index = pControl->GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();

	if(index == -1) return;

	CXTPGridRows *pRows = pControl->GetRows();
	CXTPGridRow *pRow = pRows->GetAt(index);
	CXTPGridRow *pRow1;


	if(index != 0) 
	{
		pRow1 = pRows->GetAt(index - 1);

		pControl->EnsureVisible(pRow1);
		pControl->GetSelectedRows()->Select(pRow1);
	}

}

void CChargeDongDlg2::FocusDown(CXTPGridControl *pControl)
{
	POSITION pos = pControl->GetSelectedRows()->GetFirstSelectedRowPosition();
	int index = pControl->GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();

	int nRowCount = pControl->GetRecords()->GetCount();

	if(index == -1) return;

	CXTPGridRows *pRows = pControl->GetRows();
	CXTPGridRow *pRow = pRows->GetAt(index);
	CXTPGridRow *pRow1;

	if(index != nRowCount - 1) 
	{
		pRow1 = pRows->GetAt(index + 1);

		pControl->EnsureVisible(pRow1);
		pControl->GetSelectedRows()->Select(pRow1);
	}

}

void CChargeDongDlg2::FocusLeft(CXTPGridControl *pControl)
{
	POSITION pos = pControl->GetSelectedRows()->GetFirstSelectedRowPosition();
	int index = pControl->GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();

	if(index == -1) return;

	CXTPGridRows *pRows = pControl->GetRows();
	CXTPGridRow *pRow = pRows->GetAt(index);

	if(pControl->GetSafeHwnd() == m_lstDest.GetSafeHwnd())
	{
		long nRowCount0 = pControl->GetRecords()->GetCount();
		long nRowCount1 = m_lstDest.GetRecords()->GetCount();

		CXTPGridRows *pRows1 = m_lstDest.GetRows();
		CXTPGridRow *pRow1;

		if(index == 0)     
		{
			return;
		}
		else
		{
			pRow1 = pRows1->GetAt(index - 1);
		}


		m_lstDest.SetFocus();
		m_lstDest.EnsureVisible(pRow1);
		m_lstDest.GetSelectedRows()->Select(pRow1);
		m_lstDest.SetFocusedRow(pRow1);

	}
	else if(pControl->GetSafeHwnd() == m_lstDest.GetSafeHwnd())
	{
		CXTPGridRows *pRows1 = m_lstDest.GetRows();
		CXTPGridRow *pRow1 =	pRows1->GetAt(index);



		m_lstDest.SetFocus();
		m_lstDest.EnsureVisible(pRow1);
		m_lstDest.GetSelectedRows()->Select(pRow1);
		m_lstDest.SetFocusedRow(pRow1);
	}


}

void CChargeDongDlg2::FocusRight(CXTPGridControl *pControl)
{
	POSITION pos = pControl->GetSelectedRows()->GetFirstSelectedRowPosition();
	int index = pControl->GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();


	if(index == -1) return;

	CXTPGridRows *pRows = pControl->GetRows();
	CXTPGridRow *pRow = pRows->GetAt(index);
	CXTPGridRow *pRow1;

	if(pControl->GetSafeHwnd() == m_lstDest.GetSafeHwnd())
	{
		CXTPGridRows *pRows1 = m_lstDest.GetRows();
		pRow1 =	pRows1->GetAt(index);

		m_lstDest.SetFocus();
		m_lstDest.EnsureVisible(pRow1);
		m_lstDest.GetSelectedRows()->Select(pRow1);
		m_lstDest.SetFocusedRow(pRow1);

	}
	else if(pControl->GetSafeHwnd() == m_lstDest.GetSafeHwnd())
	{
		long nRowCount = m_lstDest.GetRecords()->GetCount();

		CXTPGridRows *pRows1 = m_lstDest.GetRows();

		pRow1 = pRows1->GetAt(index + 1);

		m_lstDest.SetFocus();
		m_lstDest.EnsureVisible(pRow1);
		m_lstDest.GetSelectedRows()->Select(pRow1);		
		m_lstDest.SetFocusedRow(pRow1);

	}
}

BOOL CMyDestReport::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_UP)
		{
			m_pChargeDongDlg->FocusUp(this);
		}
		else if(pMsg->wParam == VK_DOWN)
		{
			m_pChargeDongDlg->FocusDown(this);
		}
		else if(pMsg->wParam == VK_LEFT)
		{
			m_pChargeDongDlg->FocusLeft(this);
		}
		else if(pMsg->wParam == VK_RIGHT)
		{
			m_pChargeDongDlg->FocusRight(this);
		}
	}

	return CXTPGridControl::PreTranslateMessage(pMsg);
}

void  CChargeDongDlg2::SetHTypeViewMode(BOOL bTRUE, long nMemCNo, CString sMemName)
{
	m_bHTypeViewMode = bTRUE;
	int nShow = 0;
	if(bTRUE)
		nShow = SW_HIDE;
	else
		nShow = SW_SHOW;

	m_nMemCNo = nMemCNo;
	
	m_stcBranch.ShowWindow(nShow);
	m_cmbCompany.ShowWindow(nShow);
	m_stcChargeType.ShowWindow(nShow);
	m_ChargeTypeCmb.ShowWindow(nShow);
	m_stcGroup.ShowWindow(nShow);
	m_cmbDiscountCompany.ShowWindow(nShow);
	m_stcRankEx.ShowWindow(nShow);
	m_cmbSearch[0].ShowWindow(nShow);
	m_cmbSearch[1].ShowWindow(nShow);
	m_cmbSearch[2].ShowWindow(nShow);
	m_cmbSearch[3].ShowWindow(nShow);	
	m_btnChargeTypeRank.ShowWindow(nShow);
	m_stcSearch1.ShowWindow(nShow);
	m_stcSearch2.ShowWindow(nShow);
	m_stcSearch3.ShowWindow(nShow);

	((CButton *)GetDlgItem(IDC_SELECTAREA_MEMORY_BTN))->ShowWindow(nShow);
	((CButton *)GetDlgItem(IDC_CHARGE_TYPE_BTN))->ShowWindow(nShow);
	((CButton *)GetDlgItem(IDC_SAVE_BTN))->ShowWindow(nShow);
	((CButton *)GetDlgItem(IDC_DISCOUNT_COMPANY_BTN))->ShowWindow(nShow);

	((CButton *)GetDlgItem(IDC_DISCOUNT_COMPANY_DEL_BTN))->ShowWindow(nShow);
	((CButton *)GetDlgItem(IDC_COPY_DONG_BTN))->ShowWindow(nShow);
	((CButton *)GetDlgItem(IDC_CHARGE_LIST_BTN))->ShowWindow(nShow);

	((CButton *)GetDlgItem(IDC_LINE_BTN))->ShowWindow(FALSE);
	((CButton *)GetDlgItem(IDC_USER_BTN))->ShowWindow(nShow);

	((CButton *)GetDlgItem(IDC_CHARGE_TYPE_COMBO))->ShowWindow(nShow);
	((CButton *)GetDlgItem(IDC_TYPECHARGE_STATIC))->ShowWindow(nShow);

	((CButton *)GetDlgItem(IDC_SEARCH_GROUP_BTN))->ShowWindow(nShow);
	((CButton *)GetDlgItem(IDC_SEARCH_HCUSTOMER_BTN))->ShowWindow(SW_HIDE);
		

	m_cmbHCustomer.InsertString(0,(bTRUE) ? sMemName : "");
	m_cmbHCustomer.SetItemData(0, (bTRUE) ? nMemCNo : 0);	
	m_cmbHCustomer.SetCurSel(0);
	m_cmbHCustomer.ShowWindow(bTRUE);
	m_btnSearchHCustomer.ShowWindow(bTRUE);
}

long CChargeDongDlg2::GetHTypeCNo()
{
	return m_cmbHCustomer.GetItemData(0);
}

BOOL  CChargeDongDlg2::IsHTypeViewMode()
{
	return m_bHTypeViewMode;
}


void CChargeDongDlg2::OnCancel()
{
	SetHTypeViewMode(FALSE, 0, ""); //초기화

	CXTResizeDialog::OnCancel();
}

void CChargeDongDlg2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this); 
}

void CChargeDongDlg2::OnBnClickedTwowayCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

HBRUSH CChargeDongDlg2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CXTResizeDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	HBRUSH hUserBrush;
	if(pWnd == (CWnd*)&m_chkShuttle ||
		pWnd == (CWnd*)&m_chkNotChargeQuery ||
		pWnd == (CWnd*)&m_chkGeneralMoto ||
		pWnd == (CWnd*)&m_chkGeneralDama ||
		pWnd == (CWnd*)&m_chkSpecificMoto ||
		pWnd == (CWnd*)&m_chkSpecificDama ||
		pWnd == (CWnd*)&m_chkSubWay		 ||
		pWnd == (CWnd*)&m_chkAllDel) 
	{
		if(LF->OnMyCtlColor(pDC, pWnd, nCtlColor, hUserBrush))
			return hUserBrush;
	}

	return hbr;
}

void CChargeDongDlg2::OnBnClickedGeneralRaboCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
