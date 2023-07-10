// ChargeDongUDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeDongUDlg.h"

#include "LineDlg.h"
#include "ChargeWorkDlg.h"
#include "VarietyDlg.h"
#include "BCMenu.h"
#include "SearchGroupDlg.h"
#include "ChargeListSetDlg.h"
#include "WebChargeListDlg.h"
#include "UserDongPos.h"
#include "ChargeDongSettingDlg.h"

// CChargeDongUDlg 대화 상자입니다.


IMPLEMENT_DYNAMIC(CChargeDongUDlg, CXTResizeDialog)
CChargeDongUDlg::CChargeDongUDlg(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CChargeDongUDlg::IDD, pParent)
{
	m_pChargeWorkDlg = NULL;
	m_bIntegrated = FALSE;
	m_nCompany = 0;
	m_CopyDongDlg2 = NULL;
	m_bCopyDoc = FALSE;
	//m_nFirstWork = 0;
	m_pChargeDongSettingDlg = NULL;

	m_bDragMode = FALSE;
}

CChargeDongUDlg::~CChargeDongUDlg()
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

void CChargeDongUDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_COMBO, m_cmbCompany);
	
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_ChargeEdit);
	DDX_Control(pDX, IDC_TWOWAY_CHECK, m_chkShuttle);
	DDX_Control(pDX, IDC_GENERAL_MOTO_CHECK, m_chkGeneralMoto);
	DDX_Control(pDX, IDC_GENERAL_DAMA_CHECK, m_chkGeneralDama);
	DDX_Control(pDX, IDC_SPECIFIC_MOTO_CHECK, m_chkSpecificMoto);
	DDX_Control(pDX, IDC_SPECIFIC_DAMA_CHECK, m_chkSpecificDama);
	DDX_Control(pDX, IDC_DIS_COM_COMBO, m_cmbDiscountCompany);
	DDX_Control(pDX, IDC_ALL_DEL_CHECK, m_chkAllDel);
	DDX_Control(pDX, IDC_DISCOUNT_COMPANY_BTN, m_DisCountCompanyBtn);
	DDX_Control(pDX, IDC_COPY_DONG_BTN, m_CopyDongDlgBtn);
	DDX_Control(pDX, IDC_LINE_BTN, m_LineBtn);
	DDX_Control(pDX, IDC_DISCOUNT_COMPANY_DEL_BTN, m_DisCountCompanyDelBtn);	
	DDX_Control(pDX, IDC_CHARGE_TYPE_COMBO, m_ChargeTypeCmb);
	DDX_Control(pDX, IDC_CHARGE_LIST_BTN, m_btnChargeList);
	DDX_Control(pDX, IDC_NOTCHARGE_QUERY_CHECK, m_chkNotChargeQuery);
	DDX_Control(pDX, IDC_SELECTAREA_MEMORY_BTN, m_btnSelectAreaMemory);
	DDX_Control(pDX, IDC_SAME_CHECK_BTN, m_btnSameChekc);
	DDX_Control(pDX, IDC_CHARGE_TYPE_BTN, m_btnChargeType);	
	DDX_Control(pDX, IDC_EDIT_BTN, m_btnEdit);
	DDX_Control(pDX, IDC_DELETE_BTN, m_btnDelete);
	DDX_Control(pDX, IDC_SEARCH_COMBO1, m_cmbSearch[0]);
	DDX_Control(pDX, IDC_SEARCH_COMBO2, m_cmbSearch[1]);
	DDX_Control(pDX, IDC_SEARCH_COMBO3, m_cmbSearch[2]);
	DDX_Control(pDX, IDC_SEARCH_COMBO4, m_cmbSearch[3]);
	DDX_Control(pDX, IDC_DONG_SETTING, m_lstSet);
	DDX_Control(pDX, IDC_DEST_DONG, m_lstSetDest);
	DDX_Control(pDX, IDC_USER_DONGPOS_BTN, m_UserDongButton);
	DDX_Control(pDX, IDC_SERVERLOAD_STATIC, m_stcServerLoad);
	DDX_Control(pDX, IDC_SERVERSAVE_STATIC, m_stcServerSave);
	
}


BEGIN_MESSAGE_MAP(CChargeDongUDlg, CXTResizeDialog)
	ON_BN_CLICKED(IDC_EDIT_BTN, OnBnClickedEditBtn)	
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
	ON_CBN_SELCHANGE(IDC_DIS_COM_COMBO, OnCbnSelchangeDisComCombo)
	ON_BN_CLICKED(IDC_GENERAL_MOTO_CHECK, OnBnClickedGeneralMotoCheck)
	ON_BN_CLICKED(IDC_GENERAL_DAMA_CHECK, OnBnClickedGeneralDamaCheck)
	ON_BN_CLICKED(IDC_SPECIFIC_MOTO_CHECK, OnBnClickedSpecificMotoCheck)
	ON_BN_CLICKED(IDC_SPECIFIC_DAMA_CHECK, OnBnClickedSpecificDamaCheck)
	ON_BN_CLICKED(IDC_ALL_DEL_CHECK, OnBnClickedAllDelCheck)
	ON_BN_CLICKED(IDC_DISCOUNT_COMPANY_BTN, OnBnClickedDiscountCompanyBtn)
	ON_BN_CLICKED(IDC_LINE_BTN, OnBnClickedLineBtn)
	ON_CBN_SELCHANGE(IDC_COMPANY_COMBO, OnCbnSelchangeCompanyCombo)
	ON_CBN_SELCHANGE(IDC_CHARGE_TYPE_COMBO, OnCbnSelchangeChargeTypeCombo)
	ON_BN_CLICKED(IDC_CHARGE_TYPE_BTN, OnBnClickedChargeTypeBtn)
	ON_BN_CLICKED(IDC_COPY_DONG_BTN, OnBnClickedCopyDongBtn)
	ON_BN_CLICKED(IDC_DISCOUNT_COMPANY_DEL_BTN, OnBnClickedDiscountCompanyDelBtn)	
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_SEARCH_GROUP_BTN, OnBnClickedSearchGroupBtn)		
	ON_BN_CLICKED(IDC_SELECTAREA_MEMORY_BTN, OnBnClickedSelectareaMemoryBtn)	
	ON_COMMAND(ID_CHARGE_LIST_PRINT, OnViewListPrint)	
	ON_BN_CLICKED(IDC_CHARGE_LIST_BTN, OnBnClickedChargeListBtn)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_SEARCH_SAVE_BTN, OnBnClickedSearchSaveBtn)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_DONG_SETTING, OnLvnBegindragData)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_USER + 1500, OnInItDataLoad)
	ON_MESSAGE(WM_USER + 1510, OnUserDongPosLoad)
	ON_MESSAGE(WM_USER + 1520, OnUserDongPosSave)
	ON_MESSAGE(WM_USER + 1530, OnUserDongPosPasteDest)


	
//////////////////////////////////////////////////////////
	
	ON_NOTIFY(NM_CLICK, IDC_DONG_SETTING, OnReportNewStartItemClick)
	ON_NOTIFY(XTP_NM_GRID_VALUECHANGED , IDC_DEST_DONG, OnReportValueChanged)
	ON_NOTIFY(XTP_NM_GRID_BEGINEDIT, IDC_DEST_DONG, OnReportBeginEdit)
	ON_NOTIFY(XTP_NM_GRID_PREVIEWKEYDOWN, IDC_DEST_DONG, OnReportPREVIEWKEYDOWN)
	 
	ON_NOTIFY(NM_RCLICK, IDC_DONG_SETTING, OnReportStartItemRClick)
	ON_COMMAND(ID_DEL_BOTTOM_POI_CHARGE, OnDelBottomPoiCharge)
	ON_COMMAND(ID_DEL_BOTTOM_BOTH_POI_CHARGE, OnDelBottomBothPoiCharge)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CChargeDongUDlg 메시지 처리기입니다.
BOOL CChargeDongUDlg::OnInitDialog()
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
				m_cmbCompany.SetItemData(nItem,pBi->nPayTable); // 금액테이블적용
			}
			nItem++;
		}
		m_cmbCompany.SetCurSel(nCurSel);
	}
	else
	{
		pBi = m_ba.GetAt(0);
		m_cmbCompany.InsertString(0,pBi->strBranchName );
		m_cmbCompany.SetItemData(0,m_nCompany);
		m_cmbCompany.SetCurSel(0);
	}

	for(int i=0; i<4; i++)
		m_cmbSearch[i].SetCurSel(m_ci.m_nChargeSearchOrder[i]);

	m_lstSet.SetFont(m_FontManager.GetFont("돋움", 9, FW_BOLD));
	m_lstSet.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_lstSet.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstSet.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstSet.GetReportHeader()->AllowColumnResize(TRUE);

	m_lstSet.InsertColumn(0, "구분", DT_LEFT, 190)->SetEditable(FALSE);
	m_lstSet.InsertColumn(1, "세부", DT_LEFT, 80)->SetEditable(FALSE);


	m_lstSet.Populate();
	
	m_lstSetDest.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);		
	m_lstSetDest.SetGridColor(RGB(222, 222, 222));
	m_lstSetDest.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_lstSetDest.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_lstSetDest.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstSetDest.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstSetDest.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstSetDest.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstSetDest.AllowEdit(TRUE);
	
	m_lstSetDest.InsertColumn(0, "구분", DT_LEFT, 190)->SetEditable(FALSE);
	m_lstSetDest.InsertColumn(1, "세부", DT_LEFT, 80)->SetEditable(FALSE);
	m_lstSetDest.InsertColumn(2, "오토/짐", DT_RIGHT, 60)->SetEditable(TRUE);
	m_lstSetDest.InsertColumn(3, "다마라보", DT_RIGHT, 60)->SetEditable(TRUE);
	m_lstSetDest.InsertColumn(4, "밴/봉고", DT_RIGHT, 60)->SetEditable(TRUE);
	m_lstSetDest.InsertColumn(5, "트럭", DT_RIGHT, 60)->SetEditable(TRUE);
	
	m_lstSetDest.Populate();
	
	
	m_chkGeneralMoto.SetCheck(TRUE);
	//m_DestList.m_bMotoCharge = TRUE;

	m_UserDongButton.InitButton(this);

	ChargeTypeNameRefresh();
	
	if(m_bCopyDoc)
		GetDlgItem(IDC_COPY_DONG_BTN)->ShowWindow(SW_HIDE);
			
	m_cmbCompany.SetCurSel(0);
	m_cmbDiscountCompany.SetCurSel(0);

	SetResize(IDC_DONG_SETTING, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_DEST_DONG, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetFlag(xtpResizeNoHorizontal);
	
	
	UserDongPosLoad();

	
	CopyDestBtn();
	//InitSettingDong();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChargeDongUDlg::OnBnClickedEditBtn()
{
	if(!LF->POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	try
	{
		long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
		
		
		if(nCompany < 0)
			throw("선택한 지점명이 비정상적입니다. 회사선택을 다시하여주세요");

		if(m_chkGeneralMoto.GetCheck() + m_chkGeneralDama.GetCheck() +
			m_chkSpecificMoto.GetCheck() + m_chkSpecificDama.GetCheck() <= 0)
			throw("수정할 곳이나 입력할 곳을 하나이상 기입하여주세요!");

		int nCarType = 0;
		nCarType += (m_chkGeneralMoto.GetCheck()) ? 10 : 0;
		nCarType += (m_chkGeneralDama.GetCheck()) ? 20 : 0;
		nCarType += (m_chkSpecificMoto.GetCheck())? 40 : 0;
		nCarType += (m_chkSpecificDama.GetCheck())? 80 : 0;


		long nCur = m_cmbDiscountCompany.GetCurSel();
		long nGNo = (long)m_cmbDiscountCompany.GetItemData(nCur);

		CString strCharge;
		m_ChargeEdit.GetWindowText(strCharge);
		long nCharge = atol(strCharge);

		if(nCharge <= 0) 
			throw "요금이 설정되지 않았습니다.";

		if(!CheckAreaSelect())
			return;


		CXTPGridRecord *pDestRecord = NULL;
		CXTPGridRecord *pStartRecord = NULL;
		BOOL bSuccess = FALSE;

	

		for(int i = 0; i < m_lstSet.GetSelectedRows()->GetCount(); i++)
		{
			CXTPGridRecord *pRecord = m_lstSet.GetSelectedRows()->GetAt(i)->GetRecord();
			 CXTPGridSelectedRows *pRows = m_lstSet.GetSelectedRows();
			 CXTPGridRow *pRow = pRows->GetAt(i);
		
			if(pRecord->GetChilds()->GetCount() > 0)
			{
				for(int k = 0; k < pRow->GetChilds()->GetCount(); k++)
				{
					pRow->GetChilds()->GetAt(k)->SetSelected(FALSE);
					if(pRow->GetChilds()->GetAt(k)->GetChilds()->GetCount()>0)
						ChildUnSelect(pRow->GetChilds()->GetAt(k));
				}
			}

		}

		
		for(int i = 0; i < m_lstSetDest.GetSelectedRows()->GetCount(); i++)
		{
			CXTPGridRecord *pRecord = m_lstSetDest.GetSelectedRows()->GetAt(i)->GetRecord();		
			CXTPGridSelectedRows *pSeletedRows = m_lstSetDest.GetSelectedRows();
			CXTPGridRow *pRow = pSeletedRows->GetAt(i);


			if(pRow->GetChilds()->GetCount() > 0)
			{
				for(int k = 0; k < pRow->GetChilds()->GetCount(); k++)
				{
					if(pRow->GetChilds()->GetAt(k)->IsSelected())
					{
						pRow->GetChilds()->GetAt(k)->SetSelected(FALSE);						
					}
					
					if(pRow->GetChilds()->GetAt(k)->GetChilds()->GetCount()>0)
						ChildUnSelect(pRow->GetChilds()->GetAt(k));
				}
			}

		}




		CString sError;
		for(int i = 0; i < m_lstSet.GetSelectedRows()->GetCount(); i++)
		{
			pStartRecord = (CXTPGridRecord*)m_lstSet.GetSelectedRows()->GetAt(i);
		
			CXTPGridRow *pRow = m_lstSet.GetSelectedRows()->GetAt(i);
			pStartRecord = (CXTPGridRecord*)pRow->GetRecord();
			long nStartDongID = ((CPOIInfo*)m_lstSet.GetItemData(pStartRecord))->nDongID;
			
			for(int j=0; j < m_lstSetDest.GetSelectedRows()->GetCount(); j++)
			{
				CXTPGridRow *pRow = m_lstSetDest.GetSelectedRows()->GetAt(j);
				pDestRecord =  (CXTPGridRecord*)pRow->GetRecord();
				long nDestDongID = ((CPOIInfo*)m_lstSetDest.GetItemData(pDestRecord))->nDongID;
				

				CMkCommand pCmd(m_pMkDb, "update_charge_dong_child2009_input");
				//pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);		
				pCmd.AddParameter(nCompany);		
				//pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetType(pStartRecord, pDestRecord));
				pCmd.AddParameter(nStartDongID);
				pCmd.AddParameter(nDestDongID);
				pCmd.AddParameter(nCharge);
				pCmd.AddParameter(m_chkShuttle.GetCheck());
				pCmd.AddParameter(nCarType);
				pCmd.AddParameter(m_ChargeTypeCmb.GetCurSel());
				pCmd.AddParameter(nGNo);
				if(!pCmd.Execute()) 
				{
					sError = ((CPOIInfo*)m_lstSet.GetItemData(pStartRecord))->sName + "에서 작업이 실패됬습니다.";
					throw(sError);
				}		
						
			}
			
		}
		NewRefreshList();
		
	}
	catch (char* e)
	{
		MessageBox(e,"", MB_ICONINFORMATION);
	}
	

}

void CChargeDongUDlg::OnBnClickedDeleteBtn()
{
	if(!LF->POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	CXTPGridRecord *pDestRecord = NULL;
	CXTPGridRecord *pStartRecord = NULL;
	BOOL bSuccess = FALSE;
	//DEST_RECORD_MAP2::iterator it;
	
	
	long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	int nStartCurRow = m_lstSet.GetSelectedRows()->GetCount();
	int nDestCurRow = m_lstSetDest.GetSelectedRows()->GetCount();
	int nGNo = 0, nCur = 0;
	nCur = m_cmbDiscountCompany.GetCurSel();
	if(nCur == 0)
		nGNo = 0;
	else
		nGNo = (long)m_cmbDiscountCompany.GetItemData(nCur);

	for(int i = 0; i < nStartCurRow; i++)
	{
	
		
		CXTPGridSelectedRows *pSeletedRows = m_lstSet.GetSelectedRows();
		CXTPGridRow *pRow = pSeletedRows->GetAt(i);
		pStartRecord = (CXTPGridRecord*)pRow->GetRecord();
			
		long nStartDongID = ((CPOIInfo*)m_lstSet.GetItemData(pStartRecord))->nDongID;
		
		
		for(int j=0; j < nDestCurRow; j++)
		{
		

			CXTPGridRow *pRow = m_lstSetDest.GetSelectedRows()->GetAt(j);
			pDestRecord = (CXTPGridRecord*)pRow->GetRecord();
			long nDestDongID = ((CPOIInfo*)m_lstSetDest.GetItemData(pDestRecord))->nDongID;

			CMkCommand pCmd(m_pMkDb, "delete_charge_dong_total");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);					
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nStartDongID);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nDestDongID);
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkShuttle.GetCheck());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkGeneralDama.GetCheck());		
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkGeneralMoto.GetCheck());				
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkSpecificDama.GetCheck());
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkSpecificMoto.GetCheck());
			pCmd.AddParameter(typeLong, typeInput, sizeof(int),	 m_ChargeTypeCmb.GetCurSel());
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nGNo);
			if(!pCmd.Execute())
			{
				MessageBox("삭제시 에러가 났습니다.","확인",MB_ICONINFORMATION);
				return;
			}
			
			if(m_chkGeneralMoto.GetCheck())
                pDestRecord->GetItem(2)->SetCaption("");
			if(m_chkGeneralDama.GetCheck())			
                pDestRecord->GetItem(3)->SetCaption("");
			if(m_chkSpecificDama.GetCheck())
				pDestRecord->GetItem(4)->SetCaption("");
			if(m_chkSpecificMoto.GetCheck())
				pDestRecord->GetItem(5)->SetCaption("");
		
		}
	}

	m_lstSetDest.Populate();
	MessageBox("정상적으로 삭제되었습니다.");
}

void CChargeDongUDlg::OnCbnSelchangeDisComCombo()
{
	NewRefreshList();
}

void CChargeDongUDlg::OnBnClickedGeneralMotoCheck()
{
	if(m_chkGeneralMoto.GetCheck())
	{
		m_chkGeneralDama.SetCheck(FALSE);
		m_chkSpecificMoto.SetCheck(FALSE);
		m_chkSpecificDama.SetCheck(FALSE);
		m_chkAllDel.SetCheck(FALSE);
	}

	m_lstSetDest.Populate();
}

void CChargeDongUDlg::OnBnClickedGeneralDamaCheck()
{
	if(m_chkGeneralDama.GetCheck())
	{
		m_chkGeneralMoto.SetCheck(FALSE);
		m_chkSpecificMoto.SetCheck(FALSE);
		m_chkSpecificDama.SetCheck(FALSE);
		m_chkAllDel.SetCheck(FALSE);
	}
	
	m_lstSetDest.Populate();
}

void CChargeDongUDlg::OnBnClickedSpecificMotoCheck()
{
	if(m_chkSpecificMoto.GetCheck())
	{
		m_chkGeneralMoto.SetCheck(FALSE);
		m_chkGeneralDama.SetCheck(FALSE);
		m_chkSpecificDama.SetCheck(FALSE);
		m_chkAllDel.SetCheck(FALSE);
	}
	
	m_lstSetDest.Populate();
}

void CChargeDongUDlg::OnBnClickedSpecificDamaCheck()
{
	if(m_chkSpecificMoto.GetCheck())
	{
		m_chkGeneralMoto.SetCheck(FALSE);
		m_chkGeneralDama.SetCheck(FALSE);
		m_chkSpecificMoto.SetCheck(FALSE);
		m_chkAllDel.SetCheck(FALSE);
	}

	m_lstSetDest.Populate();
}

void CChargeDongUDlg::OnBnClickedAllDelCheck()
{
	if(m_chkAllDel.GetCheck())
	{
		m_chkGeneralMoto.SetCheck(TRUE);
		m_chkGeneralDama.SetCheck(TRUE);
		m_chkSpecificMoto.SetCheck(TRUE);
		m_chkSpecificDama.SetCheck(TRUE);
	}
	else
	{
		m_chkGeneralMoto.SetCheck(FALSE);
		m_chkGeneralDama.SetCheck(FALSE);
		m_chkSpecificMoto.SetCheck(FALSE);
		m_chkSpecificDama.SetCheck(FALSE);
	}
	m_lstSetDest.Populate();
}

void CChargeDongUDlg::OnBnClickedLineBtn()
{
	CLineDlg dlg;
	dlg.m_nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	
	dlg.DoModal();
}

void CChargeDongUDlg::OnBnClickedCopyDongBtn()
{
	if(!LF->POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	CopyDongDlg();
	
}

void CChargeDongUDlg::OnBnClickedChargeTypeBtn()
{
	if(!LF->POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	CChargeWorkDlg dlg;
	dlg.m_nCompany = m_nCompany;

	dlg.DoModal();
	
}

void CChargeDongUDlg::OnBnClickedSearchGroupBtn()
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

void CChargeDongUDlg::OnBnClickedSelectareaMemoryBtn()
{

	if(!LF->POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;

	if(m_pChargeDongSettingDlg == NULL)
	{
		m_pChargeDongSettingDlg = new CChargeDongSettingDlg(this);
		m_pChargeDongSettingDlg->Create(IDD_CHARGE_SETTING_DLG, this);
		m_pChargeDongSettingDlg->m_nCompany = m_ci.m_nCompanyCode;

	}
	
	m_pChargeDongSettingDlg->ShowWindow(SW_SHOW);	
}

void CChargeDongUDlg::OnBnClickedChargeListBtn()
{
	CChargeListSetDlg dlg;
	dlg.DoModal();
}

void CChargeDongUDlg::OnViewListPrint()
{

	CXTPGridRecord *pReocrd = (CXTPGridRecord *)m_lstSet.GetSelectedRows()->GetAt(0)->GetRecord();

	CPOIInfo * pPOIInfo = (CPOIInfo*)m_lstSet.GetItemData(pReocrd);

	
	long nDongID = pPOIInfo->nDongID;
	long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());

	if( nDongID <= 0)
	{
		LF->MsgBox("회사및 동이 적용되지 않았습니다.");
		return;
	}
	CWebChargeListDlg dlg;
	dlg.m_nCompany = nCompany;
	dlg.m_nDongID = nDongID;
	dlg.DoModal();
}


BOOL CChargeDongUDlg::CheckAreaSelect()
{
	for(int i = 0; i < m_lstSet.GetSelectedRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = m_lstSet.GetSelectedRows()->GetAt(i);
		if(pRow->GetTreeDepth() == 0)
		{
			MessageBox("출발지에서 맨상위딴은 요금작업이 안됩니다. 하위트리에서 지명에서 요금작업을 하세요", "확인" ,MB_ICONINFORMATION);
			return FALSE;
		}
	}

	for(int i = 0; i < m_lstSetDest.GetSelectedRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = m_lstSetDest.GetSelectedRows()->GetAt(i);
		if(pRow->GetTreeDepth() == 0)
		{
			MessageBox("도착지에서 맨상위딴은 요금작업이 안됩니다. 하위트리에서 지명에서 요금작업을 하세요", "확인" ,MB_ICONINFORMATION);
			return FALSE;
		}
	}

	return TRUE;
}


void CChargeDongUDlg::OnBnClickedDiscountCompanyBtn()
{
	if(!LF->POWER_CHECK(1101, "요금수정/삭제", TRUE))
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
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nPayTable);
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
	else
		return;


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


void CChargeDongUDlg::OnBnClickedDiscountCompanyDelBtn()
{
	if(!LF->POWER_CHECK(1101, "요금수정/삭제", TRUE))
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
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nPayTable);
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




void CChargeDongUDlg::OnCbnSelchangeCompanyCombo()
{
	if(m_cmbDiscountCompany.GetCurSel() > 0)
		m_ChargeTypeCmb.SetCurSel(0);

	if(m_ChargeTypeCmb.GetCurSel() > 0)
		m_cmbDiscountCompany.SetCurSel(0);

	NewRefreshList();	
}

void CChargeDongUDlg::OnCbnSelchangeChargeTypeCombo()
{
	if(m_ChargeTypeCmb.GetCurSel() > 0)
		m_cmbDiscountCompany.SetCurSel(0);

	NewRefreshList();

}


void CChargeDongUDlg::OnReportStartItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CPoint point;
	::GetCursorPos(&point);

	OnContextMenu(&m_lstSet, point);
}


void CChargeDongUDlg::OnBnClickedSearchSaveBtn()
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

void CChargeDongUDlg::CopyDongDlg()
{
	if(m_CopyDongDlg2 == NULL)
	{
		m_CopyDongDlg2 = new CChargeDongUDlg(this);
	}

	m_CopyDongDlg2->m_nCompany = m_nCompany;
	m_CopyDongDlg2->m_bIntegrated = m_bIntegrated;
	m_CopyDongDlg2->m_bCopyDoc = TRUE;
	m_CopyDongDlg2->Create(IDD_CHARGE_DONG_UDLG2,this);		
	m_CopyDongDlg2->ShowWindow(SW_SHOW);
}

void CChargeDongUDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(m_lstSet.GetSelectedRows()->GetCount() == 0)
	{
		MessageBox("출발지를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_lstSet.GetSelectedRows()->GetCount() != 1)
	{
		MessageBox("출발지 리스트에 하나만 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}
	if(pWnd->GetSafeHwnd() == m_lstSet.GetSafeHwnd())
	{
		BCMenu rChargeMenu;
		rChargeMenu.LoadMenu(IDR_GROUP_MENU1);

		BCMenu* pChargeRMenu = (BCMenu*)rChargeMenu.GetSubMenu(1);
		pChargeRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

		return;
	}

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);

	BCMenu* pRMenu = (BCMenu*)rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CChargeDongUDlg::ChargeTypeNameRefresh()
{
	m_cmbDiscountCompany.ResetContent();

	m_cmbDiscountCompany.InsertString(0, "기본요금");
	m_cmbDiscountCompany.SetItemData(0, 0);

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_charge_discount_company2");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);		

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
}

void CChargeDongUDlg::CopyDestBtn()
{	
	if(m_lstSet.GetRecords()->GetCount() == 0)
	{
		m_lstSetDest.Populate();
		return;
	}

	m_lstSetDest.ResetContent(TRUE);

	CXTPGridRecord *pPReAll[20];

	long nDongID = 0, nDepth = 0,  i = 0,  nPOIID = 0, nCount = 0;	
	CString sDong, sAllName;
	BOOL bFactPOI;
	long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	
	USER_DONGPOS_MAP *pUserDongPosMap = m_mapUDongPos.GetUserDongPos(nCompany);
	USER_DONGPOS_MAP::iterator it;
	for(it = pUserDongPosMap->begin(); it != pUserDongPosMap->end(); ++it)	
	{	
		bFactPOI	= it->second->bFactPOI;
		nDepth		= it->second->nDepth;
		nDongID		= it->second->nDongID;
		nPOIID		= it->second->nPOIID;
		sAllName	= it->second->sAllName;
		sDong		= it->second->sName;
		if(sDong.GetLength() == 0)
			sDong = sAllName;

		CXTPGridRecord *pChild = new CXTPGridRecord();					
		pChild->AddItem(new CXTPGridRecordItemText(sDong));
		pChild->AddItem(new CXTPGridRecordItemText(sAllName));
		pChild->AddItem(new CXTPGridRecordItemText(""));
		pChild->AddItem(new CXTPGridRecordItemText(""));
		pChild->AddItem(new CXTPGridRecordItemText(""));
		pChild->AddItem(new CXTPGridRecordItemText(""));

		m_lstSetDest.SetItemData(pChild, (DWORD_PTR)it->second);
		m_lstSetDest.SetItemLong(pChild, nDongID);	

		CXTPGridRecord *pRecord;
		if(nDepth == 1)
		{
			pRecord = (CXTPGridRecord *)m_lstSetDest.AddRecord(pChild);				
			pPReAll[1] = pRecord;
		}
		else
		{
			pRecord = (CXTPGridRecord *)pPReAll[nDepth-1]->GetChilds()->Add(pChild);					
			pPReAll[nDepth] = pRecord;		
		}
		
		if( (DWORD_PTR)it->second->bFactPOI )  // 나중 사용자 poi 만들시 m_mapDest[nDongID] -> m_mapDest[nPOIID] 로 바겨야 함
			m_mapDest[nDongID] = pRecord;

		m_lstSetDest.GetColumns()->GetAt(0)->SetTreeColumn(TRUE);
		nCount++;
	}

	m_lstSetDest.Populate();
}

void::CChargeDongUDlg::LoadDong2(BOOL bUser)
{
	if(!bUser && MessageBox("처음셋팅된(초기화) 값으로 작업됩니다. 그래도 작업하시겠습니까?", "확인", MB_ICONINFORMATION | MB_YESNO) ==IDNO)
		return;

	//m_Vec.clear();
	long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());	
	long nDongID = 0, nDepth = 0,  i = 0, nPre1Dept = 0, nPOIID = 0, nID = 0, nDongDepth= 0;	
	CString sDong, sAllName;
	BOOL bFactPOI;
	CXTPGridRecord *pPReAll[20];
	CPOIInfo *pPOI;
	int nCount = 0 ;
	
	USER_DONGPOS_MAP *pUserDongPosMap = NULL;
	USER_DONGPOS_MATCH_MAP *pUserDongPosMatchMap = NULL;
	pUserDongPosMap = m_mapUDongPos.GetUserDongPos(nCompany);
	if(pUserDongPosMap != NULL)
	{
		m_mapUDongPos.Clear(nCompany);  // 
		m_mapUDongPos.ClearMatch(nCompany);
		pUserDongPosMap = new USER_DONGPOS_MAP;
		pUserDongPosMatchMap = new USER_DONGPOS_MATCH_MAP;
	}
	else
	{
		pUserDongPosMap = new USER_DONGPOS_MAP;
		pUserDongPosMatchMap = new USER_DONGPOS_MATCH_MAP;
	}
	

	if(m_lstSet.GetRecords()->GetCount() > 0)
		m_lstSet.ResetContent();

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_charge_user_define_dong3");	 
	pCmd2.AddParameter(nCompany);		
	pCmd2.AddParameter(bUser);		
	if(pRs2.Execute(&pCmd2))
	{
		while(!pRs2.IsEOF())
		{	
			if(bUser)
				pRs2.GetFieldValue("nID", nID);		

			pRs2.GetFieldValue("nDepth", nDepth);			
			pRs2.GetFieldValue("sDong", sDong);
			pRs2.GetFieldValue("sAllName", sAllName);
			pRs2.GetFieldValue("bFactPOI", bFactPOI);
			pRs2.GetFieldValue("nDongID", nDongID);
			pRs2.GetFieldValue("nDongDepth", nDongDepth);

			pPOI = new CPOIInfo;
			
			if(bUser)
				pPOI->nPOIID = nID;
			else
				pPOI->nPOIID = nDongID;

			pPOI->nDepth = nDepth;
			pPOI->nDongID = nDongID;
			pPOI->sAllName = sAllName;
			if(sDong.GetLength() ==0)
				pPOI->sName = sAllName;
			else
				pPOI->sName = sDong;
			pPOI->bFactPOI = bFactPOI;
			pPOI->nDongDepth = nDongDepth;
				

			CXTPGridRecord *pChild = new CXTPGridRecord();					
			pChild->AddItem(new CXTPGridRecordItemText(sDong.GetLength() ==0 ? sAllName : sDong));
			pChild->AddItem(new CXTPGridRecordItemText(sAllName));
			m_lstSet.SetItemData(pChild, (DWORD_PTR)pPOI);

			if(nDepth == 1)
			{
				CXTPGridRecord *pRecord = (CXTPGridRecord *)m_lstSet.AddRecord(pChild);				
				pPReAll[1] = pRecord;
				((CPOIInfo*)m_lstSet.GetItemData(pRecord))->pParent = NULL;

			}
			else
			{
				CXTPGridRecord *pRecord = (CXTPGridRecord *)pPReAll[nDepth-1]->GetChilds()->Add(pChild);					
				pPReAll[nDepth] = pRecord;
				((CPOIInfo*)m_lstSet.GetItemData(pRecord))->pParent = (CPOIInfo*)m_lstSet.GetItemData(pPReAll[nDepth - 1]);

			
			}	
			if(bUser)
			{
				pUserDongPosMap->insert(USER_DONGPOS_MAP::value_type(nID, pPOI));
				pUserDongPosMatchMap->insert(USER_DONGPOS_MATCH_MAP::value_type(nDongID , nID));
			}
			else
			{
				pUserDongPosMap->insert(USER_DONGPOS_MAP::value_type(nCount, pPOI));
				pUserDongPosMatchMap->insert(USER_DONGPOS_MATCH_MAP::value_type(nDongID, nCount));
			}

			nCount++;

			m_lstSet.GetColumns()->GetAt(0)->SetTreeColumn(TRUE);
			pRs2.MoveNext();
		}
		pRs2.Close();
		CString str;
		str.Format("%s개", LF->GetMyNumberFormat(nCount));
		m_stcServerLoad.SetWindowText(str);
		
		//MessageBox(str);
	}
	m_mapUDongPos.SetUserDong(nCompany,pUserDongPosMap);
	m_mapUDongPos.SetUserDongMatch(nCompany, pUserDongPosMatchMap);
	m_lstSet.Populate();
}	

void::CChargeDongUDlg::UserDongPosLoad()
{	
	long nDongID = 0, nDepth = 0,  i = 0, nPre1Dept = 0, nPOIID = 0, nID = 0;	
	CString sDong, sAllName;	

	long nCompany  = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	CXTPGridRecord *pPReAll[20];
	int nPreDepth = 0;
	USER_DONGPOS_MAP *pUserDongPosMap = NULL;
	pUserDongPosMap = m_mapUDongPos.GetUserDongPos(nCompany);
	if(pUserDongPosMap == NULL)
	{
		MessageBox("데이터가 없습니다 데이터를 다시불러오세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_lstSet.GetRecords()->GetCount() > 0)
		m_lstSet.ResetContent();


	USER_DONGPOS_MAP::iterator it;
	for(it = pUserDongPosMap->begin(); it != pUserDongPosMap->end(); ++it)
	{
		
		nDepth = it->second->nDepth;
		sDong = it->second->sName;
		if(sDong.GetLength() == 0)
			sDong = it->second->sAllName;
		sAllName = it->second->sAllName;		

		CXTPGridRecord *pChild = new CXTPGridRecord();					
		pChild->AddItem(new CXTPGridRecordItemText(sDong));
		pChild->AddItem(new CXTPGridRecordItemText(sAllName));
		m_lstSet.SetItemData(pChild, (DWORD_PTR)it->second);

		if(nDepth == 1)
		{
			CXTPGridRecord *pRecord = (CXTPGridRecord *)m_lstSet.AddRecord(pChild);				
			pPReAll[1] = pRecord;
			((CPOIInfo*)m_lstSet.GetItemData(pRecord))->pParent = NULL;

		}
		else
		{
			CXTPGridRecord *pRecord = (CXTPGridRecord *)pPReAll[nDepth-1]->GetChilds()->Add(pChild);					
			pPReAll[nDepth] = pRecord;
			((CPOIInfo*)m_lstSet.GetItemData(pRecord))->pParent = (CPOIInfo*)m_lstSet.GetItemData(pPReAll[nDepth - 1]);

		
		}
		nPreDepth = nDepth;			

		m_lstSet.GetColumns()->GetAt(0)->SetTreeColumn(TRUE);
		
	}
	CString str;
	str.Format("%s개", LF->GetMyNumberFormat( (long)pUserDongPosMap->size() ) );
	m_stcServerLoad.SetWindowText(str)	;
	
	m_lstSet.Populate();
}	





void CChargeDongUDlg::OnLvnBegindragData(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

void CChargeDongUDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	}

	CXTResizeDialog::OnMouseMove(nFlags, point);
}

void CChargeDongUDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode )
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		::ReleaseCapture();
		m_bDragMode  = FALSE;  //순서에 주의 할것

		CRect rect; BOOL bHover = FALSE;
		m_lstSet.GetWindowRect(&rect);
		ScreenToClient(rect);
		CPoint pt;
		ClientToScreen(&pt);
		CWnd* pDropWnd = WindowFromPoint(point);
		if(pDropWnd == &m_lstSet)
			bHover = TRUE;

		point -= rect.TopLeft();	
		
		if(rect.PtInRect(point))
		{
			CXTPGridRow *pRow = m_lstSet.HitTest(point);
			int nRow = pRow->GetIndex();
			CXTPGridRecord *pSelectRecord =  (CXTPGridRecord *)pRow->GetRecord();
			CPOIInfo *pSelectPOI = (CPOIInfo *)m_lstSet.GetItemData(pSelectRecord);

			// 레코드 검사
			for(int i = 0; i < m_lstSet.GetSelectedRows()->GetCount(); i++)
			{
				CXTPGridRecord *pRecord = m_lstSet.GetSelectedRows()->GetAt(i)->GetRecord();
				CXTPGridRow *pRow = m_lstSet.GetSelectedRows()->GetAt(i);
				CPOIInfo *pSelectedPOIInfo = (CPOIInfo*)m_lstSet.GetItemData(pRecord);
				if(pSelectedPOIInfo == pSelectPOI)
				{			
					MessageBox("선택된 항목이 드래그하신 항목에 속해 있습니다.", "확인", MB_ICONINFORMATION);
					return;				
				}
				if(pSelectPOI->bFactPOI && pSelectedPOIInfo->bFactPOI)
				{
					if(pSelectPOI->nDongDepth < pSelectedPOIInfo->nDongDepth)
					{
						MessageBox("상위 지역이 하위로는 이동이 불가합니다.(예 구가 동밑으로)", "확인", MB_ICONINFORMATION);
						return;				
					}
					if( pSelectedPOIInfo->nDongDepth == 4)
					{
						MessageBox("최고 상위(시, 도)는 이동이 불가합니다.", "확인", MB_ICONINFORMATION);
						return;				
					}
				}


				if(pRecord->GetChilds()->GetCount() > 0)
				{
					for(int k = 0; k < pRecord->GetChilds()->GetCount(); k++)
					{
						
						pRow->GetChilds()->GetAt(k)->SetSelected(FALSE);
						if(pRow->GetChilds()->GetAt(k)->GetChilds()->GetCount()>0)
							ChildUnSelect(pRow->GetChilds()->GetAt(k));
					}
				}

			}
			CXTPGridSelectedRows *pMoveRows = m_lstSet.GetSelectedRows();

			// 실제 레코드 옮기기
			for(int i = 0; i < m_lstSet.GetSelectedRows()->GetCount(); i++)
			{
				CXTPGridRecord *pDelRecord = m_lstSet.GetSelectedRows()->GetAt(i)->GetRecord();
				CPOIInfo *pPOI = (CPOIInfo *)m_lstSet.GetItemData(pDelRecord);

				CXTPGridRow *pMoveRow = pMoveRows->GetAt(i);


				CXTPGridRecord *pNewRecord = new CXTPGridRecord();		// 새로운 레코드만들기	
				CXTPGridRecordItemText *pItemText = new CXTPGridRecordItemText(pPOI->sName);
				CXTPGridRecordItemText *pItemText2 = new CXTPGridRecordItemText(pPOI->sAllName);
				pNewRecord->AddItem(pItemText);			
				pNewRecord->AddItem(pItemText2);			
				m_lstSet.SetItemData(pNewRecord, DWORD_PTR(pPOI));
				int nFind = InsertFind(pSelectRecord->GetChilds(), pPOI->sName);

				if(nFind == 0)
					pSelectRecord->GetChilds()->Add(pNewRecord);
				else
					pSelectRecord->GetChilds()->InsertAt(nFind,pNewRecord);

				if(pDelRecord->GetChilds()->GetCount() > 0)
				{
					ChildInput(pDelRecord, pNewRecord); // 지워질레코드 하위거를 뉴에다 옮기기
				}
				pDelRecord->Delete();

			}		

			long nCount = 0;
			for(int i = 0; i < m_lstSet.GetRecords()->GetCount(); i++)
			{
				CXTPGridRecord *pRecord = (CXTPGridRecord *)m_lstSet.GetRecords()->GetAt(i);
				if(pRecord->GetChilds()->GetCount() > 0)
					ChildCount(pRecord, nCount);
				
				nCount++;

			}

			m_lstSet.Populate();
		}
	}

	CXTResizeDialog::OnLButtonUp(nFlags, point);
}

void CChargeDongUDlg::ChildCount(CXTPGridRecord *pReocrd,long &nCount)
{
	
	for(int i = 0; i < pReocrd->GetChilds()->GetCount(); i++)
	{
		nCount++;
		CXTPGridRecord *pChildRecord = (CXTPGridRecord *)pReocrd->GetChilds()->GetAt(i);
		if(pChildRecord->GetChilds()->GetCount() > 0)
			ChildCount(pChildRecord, nCount);


	}

}

void CChargeDongUDlg::ChildUnSelect(CXTPGridRow* pRow )
{
	for(int i =0; i < pRow->GetChilds()->GetCount(); i++)
	{
		pRow->GetChilds()->GetAt(i)->SetSelected(FALSE);
		if(pRow->GetChilds()->GetAt(i)->GetChilds()->GetCount()>0)
			ChildUnSelect(pRow->GetChilds()->GetAt(i));
	}
}

int CChargeDongUDlg::InsertFind(CXTPGridRecords* pRecords, CString strWord )
{

	
	CXTPGridColumn *pCol = m_lstSet.GetColumns()->GetAt(0);
	for(int i = 0; i < pRecords->GetCount(); i++)
	{
		CString sOldListWord = pRecords->GetAt(i)->GetItem(0)->GetCaption(pCol);
		if( sOldListWord.Compare(strWord) > 0)		
		{
			return i;
		}
	}
	return 0;
}


void CChargeDongUDlg::ChildInput(CXTPGridRecord* pDelRecord,CXTPGridRecord* pNewRecord )
{
	
	long nCount = pDelRecord->GetChilds()->GetCount();
	for(int i = 0; i < nCount; i++)
	{
		CXTPGridRecord* pChildDelRecord = (CXTPGridRecord*)pDelRecord->GetChilds()->GetAt(i);
		CPOIInfo *pPOI = (CPOIInfo *)m_lstSet.GetItemData(pChildDelRecord);

		CXTPGridRecord *pChildNewRecord = new CXTPGridRecord();			
		CXTPGridRecordItemText *pItemText = new CXTPGridRecordItemText(pPOI->sName);
		CXTPGridRecordItemText *pItemText2 = new CXTPGridRecordItemText(pPOI->sAllName);
		pChildNewRecord->AddItem(pItemText);			
		pChildNewRecord->AddItem(pItemText2);			
		m_lstSet.SetItemData(pChildNewRecord, DWORD_PTR(pPOI));

		pNewRecord->GetChilds()->Add(pChildNewRecord);

		if(pChildDelRecord->GetChilds()->GetCount() > 0)
			ChildInput(pChildDelRecord,pChildNewRecord );
	}

	pDelRecord->GetChilds()->RemoveAll();
}


void CChargeDongUDlg::GetChild(CXTPGridRecord *pRecord, int nDepth)
{
	CPOIInfo *pPOIInfo;
	for(int i = 0; i < pRecord->GetChilds()->GetCount(); i++)
	{	
		CXTPGridRecord *pChildRecord =(CXTPGridRecord *)pRecord->GetChilds()->GetAt(i);		
		pPOIInfo = (CPOIInfo *)m_lstSet.GetItemData(pChildRecord);
		pPOIInfo->nDepth = nDepth;

		m_Vec.push_back(pPOIInfo);


		if(pChildRecord->GetChilds()->GetCount() > 0)
		{
			GetChild(pChildRecord, nDepth + 1 );
		}

	}

}

void CChargeDongUDlg::OnDelBottomBothPoiCharge()
{
	if(m_lstSet.GetSelectedRows()->GetCount() > 1 || m_lstSet.GetSelectedRows()->GetCount() == 0)
	{
		MessageBox("선택을 한개만 하여주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pReocrd = m_lstSet.GetFirstSelectedRecord();
	CString sMsg, sPoi;
	sPoi = ((CPOIInfo*)m_lstSet.GetItemData(pReocrd))->sName;
	sMsg.Format("%s 이하 지역의 요금데이터를 전부 지우시겠습니까? ", sPoi);

	if(MessageBox(sPoi, "확인", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		// pRecord 자기꺼는 지울필요 없고 자식들만 지운다.		


		if(pReocrd->GetChilds()->GetCount() > 0)
		{
			ChildPoiDeleteCharge(pReocrd, TRUE);
		}

	}
}

void CChargeDongUDlg::OnDelBottomPoiCharge()
{
	int i = 0;

	if(m_lstSet.GetSelectedRows()->GetCount() > 1 || m_lstSet.GetSelectedRows()->GetCount() == 0)
	{
		MessageBox("선택을 한개만 하여주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pReocrd = m_lstSet.GetFirstSelectedRecord();
	CString sMsg, sPoi;
	sPoi = ((CPOIInfo*)m_lstSet.GetItemData(pReocrd))->sName;
	sMsg.Format("%s 이하 지역의 요금데이터를 전부 지우시겠습니까? ", sPoi);
	
	if(MessageBox(sPoi, "확인", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{
		// pRecord 자기꺼는 지울필요 없고 자식들만 지운다.		
		

		if(pReocrd->GetChilds()->GetCount() > 0)
		{
			ChildPoiDeleteCharge(pReocrd, FALSE);
		}
		
	}
}

void CChargeDongUDlg::ChildPoiDeleteCharge(CXTPGridRecord *pReocrd, BOOL bShuttle)
{
	long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	for(int i = 0; i < pReocrd->GetChilds()->GetCount(); i++)
	{
		CXTPGridRecord *pChildRecord = (CXTPGridRecord *)pReocrd->GetChilds()->GetAt(i);
		
		long nStartDongID = ((CPOIInfo*)m_lstSet.GetItemData(pChildRecord))->nDongID;
		if(nStartDongID > 0)
		{
			CMkRecordset pRs2(m_pMkDb);
			CMkCommand pCmd2(m_pMkDb, "delete_chargedounguser_delete_childcharge2");	 
			pCmd2.AddParameter(nCompany);		
			pCmd2.AddParameter(nStartDongID);		
			pCmd2.AddParameter(bShuttle);		
			pCmd2.AddParameter(m_ci.m_strName);		
			if(!pRs2.Execute(&pCmd2)) 
			{
				MessageBox("작업도중실패하였습니다.", "확인", MB_ICONINFORMATION);
				return;
			}
		}
		
		if(pChildRecord->GetChilds()->GetCount() > 0)
			ChildPoiDeleteCharge(pChildRecord, bShuttle);
	}
}


LONG CChargeDongUDlg::OnInItDataLoad(WPARAM wParam, LPARAM lParam)
{
	// LoadDong2(TRUE) // FALSe 이면 DongPos 불러오기 
	LoadDong2(FALSE);
	return 0;
}


LONG CChargeDongUDlg::OnUserDongPosLoad(WPARAM wParam, LPARAM lParam)
{
	LoadDong2(TRUE);  // TRUE 이면 UserDongPos 불러오기
	return 0;
}


LONG CChargeDongUDlg::OnUserDongPosSave(WPARAM wParam, LPARAM lParam)
{
	UserDongSave(TRUE);
	return 0;
}

LONG CChargeDongUDlg::OnUserDongPosPasteDest(WPARAM wParam, LPARAM lParam)
{
	UserDongSave(FALSE);
	CopyDestBtn();
	return 0;
}

void CChargeDongUDlg::UserDongSave(BOOL bServerSave)
{

	m_Vec.clear();
	long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	
	/*
	m_mapUDongPos.GetUserDongPos(nCompany)->clear();
	if(m_mapUDongPos.GetUserDongPos(nCompany))
		delete m_mapUDongPos.GetUserDongPos(nCompany);

	*/
	m_mapUDongPos.Clear(nCompany, FALSE);
	m_mapUDongPos.ClearMatch(nCompany);
	
	

	// ----------------------------------------------------------> 레코드테스트 시작
	/*
	long nCount2 = 0;
	for(int i = 0; i < m_lstSet.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = (CXTPGridRecord *)m_lstSet.GetRecords()->GetAt(i);
		if(pRecord->GetChilds()->GetCount() > 0)
			ChildCount(pRecord, nCount2);

		nCount2++;

	}
	CString str2;
	str2.Format("레코드행 : %d", nCount2);
	//MessageBox(str2);
	// ----------------------------------------------------------> 레코드테스트 끝*/

	CPOIInfo *pPOIInfo;
	for(int i = 0; i < m_lstSet.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = (CXTPGridRecord *)m_lstSet.GetRecords()->GetAt(i);
		CXTPGridRow *pRow = m_lstSet.GetRows()->GetAt(i);
		
		pPOIInfo = (CPOIInfo *)m_lstSet.GetItemData(pRecord);
		pPOIInfo->nDepth = 1;

		m_Vec.push_back(pPOIInfo);
		if(pRecord->GetChilds()->GetCount() > 0)
			 GetChild(pRecord, 2 );
		
	}

	POI_INFO_VEC::iterator it;
	long j = 0;
	USER_DONGPOS_MAP *pUserDongPosMap = new USER_DONGPOS_MAP;
	USER_DONGPOS_MATCH_MAP *pUserDongPosMatchMap = new USER_DONGPOS_MATCH_MAP;

	for(it = m_Vec.begin(); it != m_Vec.end(); ++it)
	{		
		CPOIInfo *pPOIInfo = (CPOIInfo*)(*it);
		pUserDongPosMap->insert(USER_DONGPOS_MAP::value_type(j, pPOIInfo) );
		pUserDongPosMatchMap->insert(USER_DONGPOS_MATCH_MAP::value_type(pPOIInfo->nDongID, j));
		j++;
	}
	
	m_mapUDongPos.SetUserDong(nCompany , pUserDongPosMap);
	m_mapUDongPos.SetUserDongMatch(nCompany, pUserDongPosMatchMap);
	CString sName,sAllName, sFactPOI, sDongID, sDepth, sPOIID;
	BOOL bFactPOI = FALSE;
	long nDongID = 0, nPOIID =0,nDepth = 0, nInputCount = 0, nOutputCount = 0;
	j = 0;
	if(bServerSave)
	{
		BOOL bUpload = TRUE;
		nInputCount = (long)m_Vec.size();
		for(it = m_Vec.begin(); it != m_Vec.end(); ++it)
		{
			if(bUpload)
			{				
				ServerDataInput(j, sName, sAllName, sFactPOI,sDepth, sDongID, sPOIID);
				sName = sAllName = sFactPOI = sDepth = sDongID = sPOIID = "";				
				bUpload = FALSE;
			}

			if(j == 0 )  // 처음일때
			{
				sName =		(*it)->sName;		
				sAllName =	(*it)->sAllName;
				sFactPOI =	CastString( (long)(*it)->bFactPOI);
				sDepth =	CastString( (*it)->nDepth);
				sDongID =	CastString( (*it)->nDongID);
				sPOIID =	CastString( (*it)->nPOIID);
				bUpload = FALSE;
			}
			else
			{
				if(sAllName.GetLength() == 0) // 서버에 한번넣었으면
				{
					sName		+= (*it)->sName;
					sAllName	+= (*it)->sAllName;
					sFactPOI	+= CastString((long)(*it)->bFactPOI);
					sDepth		+= CastString((*it)->nDepth);
					sDongID		+= CastString((*it)->nDongID);
					sPOIID		+= CastString((*it)->nPOIID);
				}
				else
				{
					sName		+= "," + (*it)->sName;
					sAllName	+= "," + (*it)->sAllName;
					sFactPOI	+= "," + CastString((long)(*it)->bFactPOI);
					sDepth		+= "," + CastString((*it)->nDepth);
					sDongID		+= "," + CastString((*it)->nDongID);
					sPOIID		+= "," + CastString((*it)->nPOIID);
				}
				

			}
			if(sAllName.GetLength() > 2000 )
				bUpload =TRUE;
			
			j++;

		}
		if(sAllName.GetLength() > 0) // 나머
			nOutputCount = ServerDataInput(j, sName, sAllName, sFactPOI,sDepth, sDongID, sPOIID);
	}
	
	CString str;
	str.Format("%s개", LF->GetMyNumberFormat(j));
	m_stcServerSave.SetWindowText(str);

	
	
	if(nInputCount == nOutputCount && bServerSave)
	{
		MessageBox("서버에 저장이 되었습니다.", "확인", MB_ICONINFORMATION);
		return;
	}
	if(nInputCount != nOutputCount && bServerSave)
	{
		MessageBox("네트웤 및 통신오류등으로 중간에 데이터가 유실되었으니 다시 저장하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}
	
	
	
}

long CChargeDongUDlg::ServerDataInput(int j, CString sName, CString sAllName, CString sFactPOI, CString sDepth, CString sDongID, CString sPOIID )
{
	long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	long nOutputCount = 0;
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "insert_user_charge_dong");	 
	pCmd2.AddParameter(nCompany);		
	pCmd2.AddParameter(j);		
	pCmd2.AddParameter(sName);
	pCmd2.AddParameter(sAllName);
	pCmd2.AddParameter(sFactPOI);
	pCmd2.AddParameter(sDepth);
	pCmd2.AddParameter(sDongID);
	pCmd2.AddParameter(sPOIID);

	CMkParameter *pPar = pCmd2.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	if(!pRs2.Execute(&pCmd2)) return 0;

	
	pPar->GetValue(nOutputCount);

	return nOutputCount;
}

CString CChargeDongUDlg::CastString(long nValue)
{
	CString str;
	str.Format("%ld", nValue);
	return str;	

}

void CChargeDongUDlg::OnReportValueChanged(NMHDR*  pNotifyStruct, LRESULT* /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify != NULL);

	try
	{
		if(pItemNotify->pRow->GetTreeDepth() == 0)
		{
			MessageBox("맨상위딴은 요금작업이 안됩니다. 하위트리에서 지명에서 요금작업을 하세요", "확인" ,MB_ICONINFORMATION);
			pItemNotify->pItem->SetCaption("");
			return;
		}

		if(!CheckAreaSelect())
		{			
			return;
		}
		

		long nCharge = 0, nDestDongID = 0, nCompany = 0;
		CXTPGridRecord *pStartRecord = NULL, *pDestRecord = NULL;
		CString sError= "";

		if (!pItemNotify->pRow || !pItemNotify->pColumn)
			return;

		if(pItemNotify->pColumn->GetIndex() <= 1)
			return;


		CLMyXTPGridRecordItemText *pItemText = (CLMyXTPGridRecordItemText *)pItemNotify->pItem;


		CString strNewData = pItemText->GetValue();
		if(strNewData.GetLength() == 0)
			return;
		if(!LF->IsStringDigit(strNewData))
		{
			pItemText->OldValueChange();			
			throw("숫자를 넣어주세요");		

		}
		
		nCharge = atol(strNewData);
		if(nCharge > 5000000 || nCharge < 0)
		{
			pItemText->OldValueChange();
			throw("금액이 너무 많거나 적습니다. ");
		}

		pDestRecord = (CXTPGridRecord*)pItemNotify->pRow->GetRecord();		
		
		nDestDongID = ((CPOIInfo*)m_lstSetDest.GetItemData(pDestRecord))->nDongID;
		nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());

		long nChargeType = m_cmbDiscountCompany.GetCurSel();
		long nGNo = (long)m_cmbDiscountCompany.GetItemData(m_cmbDiscountCompany.GetCurSel());
		long nCarType = pItemNotify->pColumn->GetIndex() - 2; 
		
		

		if(nCompany < 0)
			throw("선택한 지점명이 비정상적입니다. 회사선택을 다시하여주세요");
		

		for(int i = 0; i < m_lstSet.GetSelectedRows()->GetCount(); i++)
		{			
			pStartRecord = m_lstSet.GetSelectedRows()->GetAt(i)->GetRecord();
			long nStartDongID = ((CPOIInfo*)m_lstSet.GetItemData(pStartRecord))->nDongID;
			
			CMkCommand pCmd(m_pMkDb, "update_charge_dong_child2009_input");
			//pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);		
			pCmd.AddParameter(nCompany);		
			//pCmd.AddParameter(typeLong, typeInput, sizeof(int), GetType(pStartRecord, pDestRecord));
			pCmd.AddParameter(nStartDongID);
			pCmd.AddParameter(nDestDongID);
			pCmd.AddParameter(nCharge);
			pCmd.AddParameter(m_chkShuttle.GetCheck());
			pCmd.AddParameter(nCarType);
			pCmd.AddParameter(m_ChargeTypeCmb.GetCurSel());
			pCmd.AddParameter(nGNo);
			if(!pCmd.Execute()) 
			{
				sError = ((CPOIInfo*)m_lstSet.GetItemData(pStartRecord))->sName + "에서 작업이 실패됬습니다.";
				throw(sError);
			}

		}
	}
	catch (CString s)
	{
		MessageBox(s, "확인", MB_ICONINFORMATION);		
		pItemNotify->pItem->SetCaption("");
	}
	catch (char *e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);		
	}
//	
}




//void CChargeDongUDlg::OnReportSelChanged(NMHDR* pNMHDR, LRESULT* /*result*/)
//{
	// TODO: Handle command.
//	int i = 0;
//}

void CChargeDongUDlg::OnReportBeginEdit(NMHDR* pNMHDR, LRESULT* /*result*/)
{
	//XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

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
	
	
	//CXTPGridInplaceEdit *pEditBox = pItemNotify->pRow->GetControl()->GetInplaceEdit();
	//CString sFrontValue = pItemNotify->pItem->GetCaption(pItemNotify->pColumn);

	//if(sFrontValue.GetLength() > 0)
	//{
	//	//pEditBox->SetWindowText(sFrontValue);
	//	pEditBox->SetSel(0,sFrontValue.GetLength());
	//}

	




}

//void CChargeDongUDlg::OnReportRequestEdit(NMHDR* pNMHDR, LRESULT* /*result*/)
//{
//	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*)pNMHDR;
//}

void CChargeDongUDlg::OnReportPREVIEWKEYDOWN(NMHDR* pNMHDR, LRESULT* pResult)
{
	XTP_NM_REPORTPREVIEWKEYDOWN * pItemNotify = (XTP_NM_REPORTPREVIEWKEYDOWN *)pNMHDR;
	
	XTP_NM_REPORTRECORDITEM* pItemTotal = (XTP_NM_REPORTRECORDITEM*)pNMHDR;
	long nChar = pItemNotify->nChar;
    long nRepCnt = pItemNotify->nFlags;
	long nFlags = pItemNotify->nFlags;
	int bCancel = pItemNotify->bCancel;

return;
	if( pItemNotify->hdr.hwndFrom == m_lstSetDest.GetSafeHwnd() 
		&& ( nChar == VK_RETURN || nChar == VK_UP || nChar == VK_DOWN) 	)
	{
		int i = 0;

		CXTPGridRecordItem *pItem = m_lstSetDest.GetInplaceEdit()->GetItem();
		if(pItem == NULL)
			return;
		CXTPGridInplaceEdit *pEdit = m_lstSetDest.GetInplaceEdit();
		if(pEdit == NULL)
			return;

		CXTPGridRow *pRow = m_lstSetDest.GetSelectedRows()->GetAt(0);
		CRect rect = pRow->GetNextSiblingRow()->GetRect();
		
		CPoint pt = rect.CenterPoint();
		

		
		//m_lstSetDest.GetInplaceEdit()->HideWindow();
		m_lstSetDest.SetFocusedColumn(m_lstSetDest.GetColumns()->GetAt(pItem->GetIndex()));
		XTP_REPORTRECORDITEM_CLICKARGS *pClickArgs = new XTP_REPORTRECORDITEM_CLICKARGS;
		pClickArgs->pColumn = m_lstSetDest.GetColumns()->GetAt(pItem->GetIndex());
		pClickArgs->pControl = &m_lstSetDest;
		pClickArgs->pRow = pRow;
		pClickArgs->pItem = pRow->GetNextSiblingRow()->GetRecord()->GetItem(pItem->GetIndex());
		pClickArgs->ptClient = pt;
		
		//m_lstSetDest.SetFocus();

		XTP_NM_REPORTREQUESTEDIT nm;
		::ZeroMemory(&nm, sizeof(nm));

		nm.bCancel = FALSE;
		nm.pItem = pRow->GetNextSiblingRow()->GetRecord()->GetItem(pItem->GetIndex());
		nm.pRow = pRow->GetNextSiblingRow();
		nm.pColumn = m_lstSetDest.GetColumns()->GetAt(pItem->GetIndex());
		nm.pt = pt;
		nm.hdr.hwndFrom = m_lstSetDest.GetSafeHwnd();
		nm.hdr.idFrom = m_lstSetDest.GetDlgCtrlID();

		m_lstSetDest.PostMessage(XTP_NM_GRID_BEGINEDIT, (WPARAM)&nm);
		//m_lstSetDest.SendNotifyMessage(XTP_NM_GRID_BEGINEDIT, (NMHDR*)&nm);
		//m_lstSetDest.SendNotifyMessage(XTP_NM_GRID_REQUESTEDIT, (NMHDR*)&nm);

	
		
	
		/*
		m_lstSetDest.SetFocus();

		//((CXTPGridRecord*)pRow->GetNextSiblingRow()->GetRecord())->SetEditable(TRUE);
		//((CXTPGridRecord*)pRow->GetNextSiblingRow()->GetRecord())-
		pRow->SetSelected(FALSE);
		pRow->GetNextSiblingRow()->SetSelected(TRUE);
		pRow->GetNextSiblingRow()->OnClick(pt);


		//pEdit->HideWindow();
		
		pRow->GetNextSiblingRow()->OnClick(pt);
		pRow->GetNextSiblingRow()->OnDblClick(pt);
		
		pRow->GetNextSiblingRow()->GetRecord()->SetEditable(TRUE);

		//CXTPGridControl* pControl;    // Pointer to the main Report control.
		//CXTPGridRow* pRow;            // Pointer to the associated row.
		//CXTPGridColumn* pColumn;      // Report column at click position, if any, NULL otherwise.
		//CXTPGridRecordItem* pItem;    // Pointer to the associated item.
		//CRect rcItem;   

		XTP_REPORTRECORDITEM_CLICKARGS *pClickArgs = new XTP_REPORTRECORDITEM_CLICKARGS;
		pClickArgs->pColumn = m_lstSetDest.GetColumns()->GetAt(pItem->GetIndex());
		pClickArgs->pControl = &m_lstSetDest;
		pClickArgs->pRow = pRow;
		pClickArgs->pItem = pRow->GetNextSiblingRow()->GetRecord()->GetItem(pItem->GetIndex());
		pClickArgs->ptClient = pt;
		//m_lstSetDest.PostMessage(WM_LBUTTONDOWN,(WPARAM)0, LPARAM(MAKELONG(pt.x, pt.y)));
		*/
		//m_lstSetDest.PostMessage(WM_LBUTTONUP,(WPARAM)1,LPARAM(MAKELONG(pt.x, pt.y)));
				
		//pEdit->PostMessage(WM_LBUTTONDOWN,1,13369599);
		//pEdit->PostMessage(15,0,0);
		//pEdit->PostMessage(WM_LBUTTONUP,0,13369599);

		//pRow->OnLButtonDown(pClickArgs);
		//pRow->OnLButtonUp(pClickArgs);
		//pRow->GetNextSiblingRow()->OnLButtonDown(pClickArgs);
		//m_lstSetDest.EditOnClick(TRUE);
		/*
		XTP_REPORTRECORDITEM_ARGS ItemArgs;
		for(int i = 0; i < m_lstSetDest.GetRows()->GetCount(); i++)
		{

			//m_lstSetDest.GetSe
			CXTPGridRow *pRow = m_lstSetDest.GetRows()->GetAt(i);
			if(pRow->GetRecord() == pItem->GetRecord())
			{
				//pRow->GetNextSiblingRow()->SetSelected(TRUE);
				
				DWORD dwPoint = MAKELONG(246,450);
			


				//pEdit->HideWindow();
				////m_lstSetDest.SetFocus();

				////m_lstSetDest.PostMessage(WM_LBUTTONDOWN,dwPoint,1);
				//m_lstSetDest.PostMessage(WM_LBUTTONDOWN,1,13369599);
				//m_lstSetDest.PostMessage(15,0,0);
				//m_lstSetDest.PostMessage(WM_LBUTTONUP,0,13369599);

				//m_lstSetDest.GetInplaceEdit()->HideWindow();
				
				//ItemArgs.pColumn = m_lstSetDest.GetColumns()->GetAt(pItem->GetIndex());
				//ItemArgs.pControl = &m_lstSetDest;
				//ItemArgs.pItem = pRow->GetNextSiblingRow()->GetRecord()->GetItem(pItem->GetIndex());
				//
				//CString str = pRow->GetNextSiblingRow()->GetRecord()->GetItem(pItem->GetIndex())->GetCaption(ItemArgs.pColumn);
				//ItemArgs.pRow = pRow->GetNextSiblingRow();
				//ItemArgs.rcItem = pRow->GetNextSiblingRow()->GetRect();

				////this->SendMessage(XTP_NM_GRID_BEGINEDIT,(WPARAM)ItemArgs); 
				////SendMessage(XTP_NM_GRID_BEGINEDIT, (WPARAM)pItemArgs);
				//return;
	

			}
	*/
		
		

	}
	

}





void CChargeDongUDlg::OnReportNewStartItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();

	CXTPGridRecord *pRecord = (CXTPGridRecord *)pItemNotify->pRow->GetRecord();
	if(m_lstSet.GetItemData(pRecord) == NULL)
		return;

	if(m_lstSet.GetSelectedRows()->GetCount() > 1)
		return;

	if(this->m_chkNotChargeQuery.GetCheck())
		return;


	NewRefreshList();
}



void CChargeDongUDlg::NewChargeGeneralAllDelete()
{
	DEST_MAP::iterator it;
	

	for(it = m_mapDest.begin(); it != m_mapDest.end(); it++)
	{
		CXTPGridRecord * pDestRecord = (CXTPGridRecord *)it->second;
		
		
		((CLMyXTPGridRecordItemText*)pDestRecord->GetItem(2))->SetValue("");
		((CLMyXTPGridRecordItemText*)pDestRecord->GetItem(2))->SetCaption("");

		((CLMyXTPGridRecordItemText*)pDestRecord->GetItem(3))->SetValue("");
		((CLMyXTPGridRecordItemText*)pDestRecord->GetItem(3))->SetCaption("");
		
		
		((CLMyXTPGridRecordItemText*)pDestRecord->GetItem(4))->SetValue("");
		((CLMyXTPGridRecordItemText*)pDestRecord->GetItem(4))->SetCaption("");

		
		((CLMyXTPGridRecordItemText*)pDestRecord->GetItem(5))->SetValue("");
		((CLMyXTPGridRecordItemText*)pDestRecord->GetItem(5))->SetCaption("");


		
	}
	
}


void CChargeDongUDlg::NewSetAllCharge(long nDestID, long nMotoCharge, long nDamaCharge, long nSpecificMoto, long nSpecificDama)
{

	

	char buffer[10];
	DEST_MAP::iterator it;
	it = m_mapDest.find(nDestID);

	if(it == m_mapDest.end()) return;

	CXTPGridRecord * pDestRecord = (CXTPGridRecord *)it->second;

	CString sMoto = nMotoCharge ==0 ? "" : ltoa(nMotoCharge,buffer,10);
	CString sDama = nDamaCharge ==0 ? "" : ltoa(nDamaCharge,buffer,10);
	CString sSpecificMoto = nSpecificMoto ==0 ? "" :  ltoa(nSpecificMoto,buffer,10);
	CString sSpecificDama = nSpecificDama ==0 ? "" :  ltoa(nSpecificDama,buffer,10);
	pDestRecord->GetItem(2)->SetCaption(LF->GetMyNumberFormat(sMoto));
	pDestRecord->GetItem(3)->SetCaption(LF->GetMyNumberFormat(sDama));
	pDestRecord->GetItem(4)->SetCaption(LF->GetMyNumberFormat(sSpecificMoto));
	pDestRecord->GetItem(5)->SetCaption(LF->GetMyNumberFormat(sSpecificDama));

}

void CChargeDongUDlg::NewRefreshList()
{
	NewChargeGeneralAllDelete();

	CXTPGridRow *pRow = NULL;
	if(m_lstSet.GetSelectedRows()->GetCount() > 1)
		return;
	
	pRow = m_lstSet.GetSelectedRows()->GetAt(0);
	
	

	int nRow = pRow->GetIndex();
	CXTPGridRecord *pRecord = (CXTPGridRecord *)pRow->GetRecord();
	CPOIInfo *pPOIInfo = NULL;
	pPOIInfo = (CPOIInfo*)m_lstSet.GetItemData(pRecord);

	if(pPOIInfo->bFactPOI == FALSE || pPOIInfo == NULL) 
		return;



	long nGNo = 0,nCur = 0;
	long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	nCur = m_cmbDiscountCompany.GetCurSel();
	nGNo = (long)m_cmbDiscountCompany.GetItemData(nCur);	
	int nChargeType = m_ChargeTypeCmb.GetCurSel();


	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_charge_dong_total");
	//pCmd.AddParameter(typeLong, typeInput, sizeof(long), (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel()));
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), pPOIInfo->nDongID);    	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nGNo);	

	long nDestID = 0, nMotoCharge = 0,nDamaCharge = 0 ;
	long nBonggoCharge = 0, nTruckCharge = 0;
	int nType = 0;
	BOOL bShuttle = FALSE;
	

	if(pRs.Execute(&pCmd))
	{
		if(pRs.GetRecordCount() == 0)
		{
			m_lstSetDest.Populate();
			return;
			
		}
		else
		{
			CString sType = "";
			m_ChargeTypeCmb.GetLBText(m_ChargeTypeCmb.GetCurSel(), sType);
			CString sMoto =		(nGNo == 0) ? "nMotoCharge" + sType.Left(1) : "nMotoCharge";
			CString sDama =		(nGNo == 0) ? "nDamaCharge" + sType.Left(1) : "nDamaCharge";
			CString sBonggo =	(nGNo == 0) ? "nBonggoCharge" + sType.Left(1) : "nBonggoCharge";
			CString sTruck =	(nGNo == 0) ? "nTruckCharge" + sType.Left(1) : "nTruckCharge" ;				

			for(long i=0; i<pRs.GetRecordCount(); i++)
			{
				pRs.GetFieldValue("nDestID", nDestID);				
				pRs.GetFieldValue(sMoto, nMotoCharge);
				pRs.GetFieldValue(sDama, nDamaCharge);
				pRs.GetFieldValue(sTruck, nTruckCharge);
				pRs.GetFieldValue(sBonggo, nBonggoCharge);				

				NewSetAllCharge(nDestID,nMotoCharge, nDamaCharge, nBonggoCharge, nTruckCharge);			

				pRs.MoveNext();
			}	
		}

		pRs.Close();
	}	
	m_lstSetDest.Populate();
}


BOOL CChargeDongUDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->hwnd == m_lstSetDest.GetSafeHwnd() && pMsg->message != 512)
	{
		//if(pMsg->message == 513 || pMsg->message == 514)
		//{
		 XTP_REPORTRECORDITEM_ARGS *pArgs = (XTP_REPORTRECORDITEM_ARGS*)pMsg->lParam;
			CXTPGridRecordItem *pItem = (CXTPGridRecordItem*)pMsg->lParam;
			CXTPGridRow *pRow = (CXTPGridRow*)pMsg->lParam;
			long x  = LOWORD(pMsg->lParam);
			long y =		HIWORD(pMsg->lParam);

			int i = 0;
			
	///		TRACE("%u,%ld,%ld,%u\r\n",pMsg->message,x,y,pMsg->wParam);
	//	}
		TRACE("%u,%ld,%ld,%u\r\n",pMsg->message, pMsg->lParam,pMsg->wParam);
	}
	//WM_LBUTTONUP WM_LBUTTONDOWN
	return CXTResizeDialog::PreTranslateMessage(pMsg);
}




