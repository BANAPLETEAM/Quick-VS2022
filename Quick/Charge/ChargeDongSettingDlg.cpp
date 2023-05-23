// ChargeDongSettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeDongSettingDlg.h"
#include "ChargeDongDlg2.h"
#include "VarietyDlg.h"
#include "SearchGroupDlg.h"

// CChargeDongSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeDongSettingDlg, CXTResizeDialog)
CChargeDongSettingDlg::CChargeDongSettingDlg(CWnd* pParent)
	: CXTResizeDialog(CChargeDongSettingDlg::IDD, pParent)
{
	m_pChargeDongDlg  = (CChargeDongDlg2*)pParent;
	m_nMoto = m_nDama = m_nBonggo = m_nTruck = 0;
	m_nCompany = 0;
}

CChargeDongSettingDlg::~CChargeDongSettingDlg()
{
}

void CChargeDongSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_SECTION_NAME,m_lstSectionName);
	DDX_Control(pDX,IDC_START,m_lstStart);
	DDX_Control(pDX,IDC_DEST,m_lstDest);

	DDX_Control(pDX, IDC_MOTO_CHECK, m_chkMoto);
	DDX_Control(pDX, IDC_DAMA_CHECK, m_chkDama);
	DDX_Control(pDX, IDC_BONGGO_CHECK, m_chkBonggo);
	DDX_Control(pDX, IDC_TRUCK_CHECK, m_chkTruck);

	DDX_Text(pDX, IDC_MOTO_EDIT, m_nMoto);
	DDX_Text(pDX, IDC_DAMA_EDIT, m_nDama);
	DDX_Text(pDX, IDC_BONGGO_EDIT, m_nBonggo);
	DDX_Text(pDX, IDC_TRUCK_EDIT, m_nTruck);

	DDX_Control(pDX, IDC_MOTO_EDIT, m_edtMoto);
	DDX_Control(pDX, IDC_DAMA_EDIT, m_edtDama);
	DDX_Control(pDX, IDC_BONGGO_EDIT, m_edtBonggo);
	DDX_Control(pDX, IDC_TRUCK_EDIT, m_edtTruck);
	DDX_Control(pDX, IDC_DIS_COM_COMBO, m_cmbDiscountCompany);
	DDX_Control(pDX, IDC_CHARGE_TYPE_CMB, m_cmbChargeType);
	DDX_Control(pDX, IDC_COMPANY_COMBO, m_cmbCompany);
	DDX_Control(pDX, IDC_SERVER_REFRSH_BTN, m_btnServerRefreshSection);
	DDX_Control(pDX, IDC_NEW_AREA_BTN, m_btnNewArea);
	DDX_Control(pDX, IDC_DELETE_AREA_BTN, m_btnDeleteArea);
	DDX_Control(pDX, IDC_SAVE_BTN, m_btnStartSave);
	DDX_Control(pDX, IDC_SAVE_BTN2, m_btnDestSave);
	DDX_Control(pDX, IDC_SAVE_AMOUNT_BTN, m_btnSaveAmount);
	DDX_Control(pDX, IDC_START_BILL_BTN_SERVER, m_btnStartBillServerSave);
	DDX_Control(pDX, IDC_START_LIST_DEL_BTN_SERVER, m_btnStartListDelServerSave);
	DDX_Control(pDX, IDC_DEST_BILL_BTN_SERVER, m_btnDestBillServerSave);
	DDX_Control(pDX, IDC_DEST_LIST_DEL_BTN_SERVER, m_btnDestListDelServerSave);
	DDX_Control(pDX, IDC_STARTDEST_SAVE_BTN, m_btnStartDestServerSave);
	DDX_Control(pDX, IDC_SHUTTLE_CHECK, m_chkShuttle);
}

BEGIN_MESSAGE_MAP(CChargeDongSettingDlg, CXTResizeDialog)
	ON_NOTIFY(NM_CLICK, IDC_SECTION_NAME, OnReportSectionNameItemClick)
	
	ON_BN_CLICKED(IDC_START_BILL_BTN, OnBnClickedStartBillBtn)
	
	ON_BN_CLICKED(IDC_DEST_BILL_BTN, OnBnClickedDestBillBtn)
	ON_BN_CLICKED(IDC_START_LIST_DEL_BTN, OnBnClickedStartListDelBtn)
	ON_BN_CLICKED(IDC_DEST_LIST_DEL_BTN, OnBnClickedDestListDelBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN2, OnBnClickedSaveBtn2)
	
	ON_BN_CLICKED(IDC_MOTO_CHECK, OnBnClickedMotoCheck)
	ON_BN_CLICKED(IDC_SAVE_AMOUNT_BTN, OnBnClickedSaveAmountBtn)
	ON_BN_CLICKED(IDC_DAMA_CHECK, OnBnClickedDamaCheck)
	ON_BN_CLICKED(IDC_BONGGO_CHECK, OnBnClickedBonggoCheck)
	ON_BN_CLICKED(IDC_TRUCK_CHECK, OnBnClickedTruckCheck)
	ON_BN_CLICKED(IDC_STARTDEST_DEL_BTN, OnBnClickedStartdestDelBtn)
	ON_BN_CLICKED(IDC_STARTDEST_BRINNG_BTN, OnBnClickedStartdestBrinngBtn)
	ON_BN_CLICKED(IDC_STARTDEST_SAVE_BTN, OnBnClickedStartdestSaveBtn)
	
	ON_BN_CLICKED(IDC_NEW_AREA_BTN, OnBnClickedNewAreaBtn)
	ON_BN_CLICKED(IDC_DELETE_AREA_BTN, OnBnClickedDeleteAreaBtn)
	ON_BN_CLICKED(IDC_SERVER_REFRSH_BTN, OnBnClickedServerRefrshBtn)
	
	
	ON_BN_CLICKED(IDC_SEARCH_GROUP_BTN, OnBnClickedSearchGroupBtn)
	ON_BN_CLICKED(IDC_SEARCH_GROUP_REFRESH_BTN, OnBnClickedSearchGroupRefreshBtn)
	ON_BN_CLICKED(IDC_START_BILL_BTN_SERVER, OnBnClickedStartBillBtnServer)
	ON_BN_CLICKED(IDC_DEST_BILL_BTN_SERVER, OnBnClickedDestBillBtnServer)
	ON_BN_CLICKED(IDC_START_LIST_DEL_BTN_SERVER, OnBnClickedStartListDelBtnServer)
	ON_BN_CLICKED(IDC_DEST_LIST_DEL_BTN_SERVER, OnBnClickedDestListDelBtnServer)
	ON_CBN_SELCHANGE(IDC_COMPANY_COMBO, OnCbnSelchangeCompanyCombo)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CChargeDongSettingDlg 메시지 처리기입니다.

BOOL CChargeDongSettingDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	m_lstStart.AddHeader(0, TRUE, "sStartName", "출발지", 180, DT_LEFT,FALSE);		
	m_lstStart.AddHeader(1, TRUE, "sType", "표", 60, DT_LEFT,FALSE);			
	m_lstStart.AddHeader(-1, FALSE, "nDongID",	"", 80, DT_LEFT,FALSE,TRUE);		
	m_lstStart.AddHeader(-1, FALSE, "nType",	"", 80, DT_LEFT,FALSE,FALSE, TRUE);		
	m_lstStart.SetExtendedStyle(NULL);
	m_lstStart.Populate();


	m_lstDest.AddHeader(0, TRUE, "sStartName", "도착지", 180, DT_LEFT,FALSE);		
	m_lstDest.AddHeader(1, TRUE, "sType",		"구분", 60, DT_LEFT,FALSE);			
	m_lstDest.AddHeader(-1, FALSE, "nDongID",	"", 80, DT_LEFT,FALSE,TRUE);		
	m_lstDest.AddHeader(-1, FALSE, "nType",		"", 80, DT_LEFT,FALSE,FALSE,TRUE);		
	m_lstDest.SetExtendedStyle(NULL);
	m_lstDest.Populate();
	
	m_lstSectionName.AddHeader(0, TRUE, "sChargeAreaName", "구간이름", 180, DT_LEFT,FALSE);		
	m_lstSectionName.AddHeader(-1, FALSE, "nChargeAreaID", "No", 150, DT_CENTER,FALSE, TRUE);
	//m_lstSectionName.AddHeader(1, TRUE, "nChargeAreaID", "nChargeAreaID", 50, DT_LEFT);		
	m_lstSectionName.SetExtendedStyle(NULL);
	m_lstSectionName.Populate();

	m_chkMoto.SetCheck(TRUE);

	m_cmbChargeType.SetCurSel(0);

	CBranchInfo *pBi = NULL;
	
	if(m_ci.m_bRcpIntMode1 || m_ci.m_bRcpIntMode2 || m_ci.m_bRcpIntMode3 || m_ci.m_bRcpIntMode4 || m_ci.m_bRcpIntMode5)
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

	ChargeTypeNameRefresh();
	m_cmbDiscountCompany.SetCurSel(0);

	
	m_cmbChargeType.InsertString(0, "A타입");
	m_cmbChargeType.InsertString(1, "B타입");
	m_cmbChargeType.InsertString(2, "C타입");
	m_cmbChargeType.InsertString(3, "D타입");
	m_cmbChargeType.SetCurSel(0);


	SetResize(IDC_SECTION_NAME, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_START, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_DEST, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);

	RefreshSection();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	
}
void CChargeDongSettingDlg::RefreshSection()
{

	m_lstSectionName.DeleteAllItem();

	m_lstSectionName.CreateRsSetQuery("select_charge_setting_area_name");
	m_lstSectionName.AddParameter(m_ci.m_nCompanyCode);	
	m_lstSectionName.ExcuteBinding(TRUE);


}


void CChargeDongSettingDlg::OnReportSectionNameItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;


	BOOL bNoSavedItem = FALSE;
	CMyXTPGridRecord *pNoSaveRecord;
	for(int i = 0; i < this->m_lstSectionName.GetItemCount(); i++)
	{
		pNoSaveRecord = m_lstSectionName.GetRecordsGetAt(i);
		int nSavedChargeAreaID = pNoSaveRecord->GetItemDataLong();
		if(nSavedChargeAreaID ==-1)
		{
			bNoSavedItem = TRUE;
			break;
		}

	}



	if(bNoSavedItem)
	{
		if((CMyXTPGridRecord*)pItemNotify->pRow->GetRecord() == pNoSaveRecord)
			return;

		CString strNoSaveAreaName = pNoSaveRecord->GetItem(0)->GetCaption(NULL);
		strNoSaveAreaName += " 구역이 저장되지않아 타지역을 선택하시면 데이터가 사라집니다\n\r \n\r";
		strNoSaveAreaName += " 저장하지 않고 타구역을 보시겠습니까? ";
		if(MessageBox(strNoSaveAreaName, "확인", MB_ICONINFORMATION | MB_YESNO) == IDNO)
		{

			pItemNotify->pRow->SetSelected(FALSE);

				
			return;
		}
			
	}


	
	int nRow = pItemNotify->pRow->GetIndex();
	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pItemNotify->pRow->GetRecord();
	long nChargeAreaID = pRecord->GetItemDataLong();
	if(nChargeAreaID <= 0)
	{
		LF->MsgBox("아직 저장되지 않은 지역입니다");
		return;
	}
	RefreshRegisterStartArea(nChargeAreaID);
	RefreshRegisterDestArea(nChargeAreaID);
}
void CChargeDongSettingDlg::RefreshRegisterStartArea(long nChargeAreaID)
{



	m_lstStart.DeleteAllItem();
	
	m_lstStart.CreateRsSetQuery("select_charge_setting_area_start_list");
	m_lstStart.AddParameter(nChargeAreaID);	
	m_lstStart.AddParameter(TRUE,0);	
	m_lstStart.ExcuteBinding(TRUE);

}
void CChargeDongSettingDlg::RefreshRegisterDestArea(long nChargeAreaID)
{

	m_lstDest.DeleteAllItem();
	
	m_lstDest.CreateRsSetQuery("select_charge_setting_area_start_list");
	m_lstDest.AddParameter(nChargeAreaID);	
	m_lstDest.AddParameter(FALSE,0);	
	m_lstDest.ExcuteBinding(TRUE);
	

}


void CChargeDongSettingDlg::OnBnClickedStartBillBtn()
{
	GetStartDongID(FALSE);
}


void CChargeDongSettingDlg::OnBnClickedStartBillBtnServer()
{
	GetStartDongID(TRUE);
}
void CChargeDongSettingDlg::GetStartDongID(BOOL bServer)
{
	CXTPGridRecord *pRecord = m_lstSectionName.GetSelectedRecord();

	if(bServer && pRecord == NULL)
	{
		LF->MsgBox("지역선택을 다시하여주세요");
		return;
	}

	long nChargeAreaID = pRecord != NULL ? m_lstSectionName.GetSelectedRecord()->GetItemDataLong() : 0;

	if(bServer && nChargeAreaID < 0 )
	{
		LF->MsgBox("지역선택을 다시하여주세요");
		return;
	}

	
	for(int i = 0; i < m_pChargeDongDlg->m_lstStart.GetSelectedRows()->GetCount(); i++)
	{
		CDetailChargeRecord *pRecord = (CDetailChargeRecord *)m_pChargeDongDlg->m_lstStart.GetSelectedRows()->GetAt(i)->GetRecord();
		
		BOOL bFind = FALSE;
		long nStartListCount = m_lstStart.GetRecords()->GetCount();
		for(int j = 0; j < nStartListCount; j++)
		{
			if(m_lstStart.GetRecordsGetAt(j)->GetItemDataLong() == pRecord->m_nDongID)
			{
				bFind = TRUE;
				break;
			}
		}

		if(bFind)  // 
			continue;

		CString strTemp = pRecord->GetItem(1)->GetCaption(NULL);
		if(strTemp.Compare("지역구분") == 0)
			continue;

		long nDongID = pRecord->m_nDongID;
		
		CString sType = "",sStartName = "";		
		sStartName.Format("%s %s ", pRecord->m_sArea,  pRecord->m_sDong);
		int nType = 0;
		
		switch(pRecord->GetTypeInfo())
		{
		case 3:
			nType = 3;
			sType = "시";
			break;
		case 2:
			nType = 2;
			sType = "구";
			break;
		case 1:
			nType = 1;
			sType = "동";
			break;
		}
		if(bServer)
		{
			m_lstStart.CreateComandSetQuery("insert_chargedong_setting");
			m_lstStart.AddParameter(nChargeAreaID);
			m_lstStart.AddParameter(nDongID);
			m_lstStart.AddParameter(nType);
			m_lstStart.AddParameter("");
			m_lstStart.AddParameter(m_ci.m_nCompanyCode);
			m_lstStart.AddParameter(TRUE);  // START or DEST
			m_lstStart.AddParameter(nChargeAreaID);
			m_lstStart.ExcuteCmd();

		}

		
		m_lstStart.MyAddItem(sStartName);
		CMyXTPGridRecord *pStartRecord = m_lstStart.MyAddItem(sType);
		pStartRecord->m_bDirtyFlag = TRUE;
		m_lstStart.InsertItemDataLong(nDongID);
		m_lstStart.InsertItemDataLong2(nType);
		m_lstStart.EndItem();		
	}
	m_lstStart.Populate();

}



void CChargeDongSettingDlg::OnBnClickedDestBillBtn()
{
	this->GetDestDongID(FALSE);
	
}

void CChargeDongSettingDlg::OnBnClickedDestBillBtnServer()
{
	this->GetDestDongID(TRUE);
}

void CChargeDongSettingDlg::GetDestDongID(BOOL bServer)
{
	long nChargeAreaID = this->m_lstSectionName.GetSelectedRecord()->GetItemDataLong();
	if(bServer && nChargeAreaID < 0 )
	{
		LF->MsgBox("지역선택을 다시하여주세요");
		return;
	}
	for(int i = 0; i < m_pChargeDongDlg->m_lstDest.GetSelectedRows()->GetCount(); i++)
	{
		CDetailDestChargeRecord *pRecord = (CDetailDestChargeRecord *)m_pChargeDongDlg->m_lstDest.GetSelectedRows()->GetAt(i)->GetRecord();
		
		BOOL bFind = FALSE;
		long nDestListCount = m_lstDest.GetRecords()->GetCount();
		for(int j = 0; j < nDestListCount; j++)
		{
			if(m_lstDest.GetRecordsGetAt(j)->GetItemDataLong() == pRecord->m_nDongID)
			{
				bFind = TRUE;
				break;
			}
		}

		if(bFind)  // 
			continue;
		CString strTemp = pRecord->GetItem(1)->GetCaption(NULL);

		if(strTemp.Compare("지역구분") == 0)
			continue;

		long nDongID = pRecord->m_nDongID;
		CString  sType = "",sStartName = "";		
		sStartName.Format("%s %s ", pRecord->m_sArea, pRecord->m_sDong);
		int nType = 0;
		switch(pRecord->GetTypeInfo())
		{
		case 3:
			nType = 3;
			sType = "시";
			break;
		case 2:
			nType = 2;
			sType = "구";
			break;
		case 1:
			nType = 1;
			sType = "동";
			break;
		}

		if(bServer)
		{
			m_lstDest.CreateComandSetQuery("insert_chargedong_setting");
			m_lstDest.AddParameter(nChargeAreaID);
			m_lstDest.AddParameter(nDongID);
			m_lstDest.AddParameter(nType);
			m_lstDest.AddParameter("");
			m_lstDest.AddParameter(m_ci.m_nCompanyCode);
			m_lstDest.AddParameter(FALSE);  // START or DEST
			m_lstDest.AddParameter(nChargeAreaID);
			m_lstDest.ExcuteCmd();

		}
		
		m_lstDest.MyAddItem(sStartName);
		CMyXTPGridRecord *pDestRecord = m_lstDest.MyAddItem(sType);
		pDestRecord->m_bDirtyFlag = TRUE;
		m_lstDest.InsertItemDataLong(nDongID);
		m_lstDest.InsertItemDataLong2(nType);
		m_lstDest.EndItem();
		

		

		/*m_lstDest.AddHeader(0, TRUE, "sStartName", "출발지", 80, DT_LEFT,TRUE);		
		m_lstDest.AddHeader(1, TRUE, "sType", "표", 80, DT_LEFT,TRUE);			
		m_lstDest.AddHeader(-1, TRUE, "nDongID",	"", 80, DT_LEFT,TRUE);		
		m_lstDest.AddHeader(-1, TRUE, "nType", "출발지", 80, DT_LEFT,FALSE,TRUE);		*/
	}
	m_lstDest.Populate();
}




void CChargeDongSettingDlg::SaveDestList()
{

	if(m_lstDest.GetSelectedCount() == 0)
		return;

	CMyXTPGridRecord *pSectionNameRecord = this->m_lstSectionName.GetSelectedRecord();
	long nChargeAreaID = pSectionNameRecord->GetItemDataLong();
	CString sChargeAreaName = m_lstSectionName.GetSelectedRecord()->GetItem(0)->GetCaption(NULL);
	if(nChargeAreaID == -1 && sChargeAreaName.GetLength() == 0)
	{
		LF->MsgBox("지역 신규는 이름이 있어야 합니다.");
		return;
	}

	BOOL bFail = FALSE;
	BOOL bStart = FALSE;
	long nNewChargeAreaID = nChargeAreaID;
	for(int i= 0; i< m_lstDest.GetRecords()->GetCount(); i++)
	{
		CMyXTPGridRecord *pRecord = m_lstDest.GetRecordsGetAt(i);
		
		long nDongID = pRecord->GetItemDataLong();
		long nType = pRecord->GetItemDataLong2();
		

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_chargedong_setting_delete");

		pCmd.AddParameter(nChargeAreaID == -1 && i == 0 ? -1 : nNewChargeAreaID);
		pCmd.AddParameter(nDongID);
		pCmd.AddParameter(nType);			
		pCmd.AddParameter(sChargeAreaName);
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		pCmd.AddParameter(bStart);
		pCmd.AddParameter(i); // nRow 처음 0이면 지운다.
		CMkParameter *parNewChargeAreaID = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		bFail =  pRs.Execute(&pCmd);
			

		parNewChargeAreaID->GetValue(nNewChargeAreaID);
		
		pSectionNameRecord->SetItemDataLong(nNewChargeAreaID);  ///
		if(bFail)
			pRecord->m_bDirtyFlag = FALSE;
		else
		{
			MessageBox("저장중 오류가 났습니다 다시 시도하세요");
			return;
		}

		
		

	}
	if(bFail)
		LF->MsgBox("도착지 동이 저장되었습니다");
	m_lstDest.Populate();


}


void CChargeDongSettingDlg::SaveStartList()
{
	if(m_lstStart.GetSelectedCount() == 0)
		return;
	CMyXTPGridRecord *pSectionNameRecord = this->m_lstSectionName.GetSelectedRecord();
	long nChargeAreaID = pSectionNameRecord->GetItemDataLong();
	CString sChargeAreaName = m_lstSectionName.GetSelectedRecord()->GetItem(0)->GetCaption(NULL);

	if(nChargeAreaID == -1 && sChargeAreaName.GetLength() == 0)
	{
		LF->MsgBox("지역 신규는 이름이 있어야 합니다.");
		return;
	}


	BOOL bFail = FALSE;
	BOOL bStart = TRUE;
	long nNewChargeAreaID = nChargeAreaID;
	for(int i= 0; i< m_lstStart.GetRecords()->GetCount(); i++)
	{
		CMyXTPGridRecord *pRecord = m_lstStart.GetRecordsGetAt(i);
		
		long nDongID = pRecord->GetItemDataLong();
		long nType = pRecord->GetItemDataLong2();		
		
			

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_chargedong_setting_delete");

		pCmd.AddParameter(nChargeAreaID == -1 && i == 0 ? -1 : nNewChargeAreaID);
		pCmd.AddParameter(nDongID);
		pCmd.AddParameter(nType);			
		pCmd.AddParameter(sChargeAreaName);
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		pCmd.AddParameter(bStart);
		pCmd.AddParameter(i); // nRow 처음 0이면 지운다.
		CMkParameter *parNewChargeAreaID = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		bFail =  pRs.Execute(&pCmd);
		

		parNewChargeAreaID->GetValue(nNewChargeAreaID);
		pSectionNameRecord->SetItemDataLong(nNewChargeAreaID);  ///
		
		/*m_lstStart.CreateComandSetQuery("insert_chargedong_setting");
		m_lstStart.AddParameter(nChargeAreaID);
		m_lstStart.AddParameter(nDongID);
		m_lstStart.AddParameter(nType);
		bFail += m_lstDest.ExcuteCmd();*/
		if(bFail)
			pRecord->m_bDirtyFlag = FALSE;
		else
		{
			MessageBox("저장중 오류가 났습니다 다시 시도하세요");
			return;
		}


	}
	if(bFail)
		LF->MsgBox("출발지 동이 저장되었습니다");
	m_lstStart.Populate();


}


void CChargeDongSettingDlg::OnBnClickedStartListDelBtn()
{
	DelStartList(FALSE);
}

void CChargeDongSettingDlg::OnBnClickedStartListDelBtnServer()
{
	DelStartList(TRUE);
}


void CChargeDongSettingDlg::DelStartList(BOOL bServer)
{

	if(m_lstStart.GetSelectedCount() == 0)
		return;

	long nChargeAreaID = this->m_lstSectionName.GetSelectedRecord()->GetItemDataLong();
	if(bServer && nChargeAreaID < 0 )
	{
		LF->MsgBox("지역선택을 다시하여주세요");
		return;
	}

	///*int nRowcount = m_lstStart.GetRows()->GetCount();
	//int nRecordcount = m_lstStart.GetRecords()->GetCount();
	//CString sCount;
	//sCount.Format("레코드: %d, 로우 : %d", nRecordcount, nRowcount);
	//LF->MsgBox(sCount);*/
	for(int i= 0 ; i <  m_lstStart.GetSelectedCount(); i++)
	{
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)m_lstStart.GetSelectedRows()->GetAt(i)->GetRecord();
		if(pRecord == NULL)
		{
			LF->MsgBox("작업중 오류가 있습니다. 로지소프트로 문의하세요");
			return;
		}
		if(bServer)
		{
			m_lstStart.CreateComandSetQuery("delete_charge_area_setting_detail");
			m_lstStart.AddParameter(nChargeAreaID);
			m_lstStart.AddParameter(pRecord->GetItemDataLong());
			m_lstStart.AddParameter(m_ci.m_nCompanyCode);
			m_lstStart.AddParameter(TRUE);
			if(!m_lstStart.ExcuteCmd())
				return;

		}
		
		pRecord->RemoveAll();
		m_lstStart.GetRecords()->RemoveAt(pRecord->GetIndex());
		
	/*	CXTPGridRow *pRow = m_lstStart.GetSelectedRows()->GetAt(i);
		m_lstStart.GetRows()->RemoveAt(pRow->GetIndex());	*/	
		
		
	}
	/*nRowcount = m_lstStart.GetRows()->GetCount();
	nRecordcount = m_lstStart.GetRecords()->GetCount();
	
	sCount.Format("레코드: %d, 로우 : %d", nRecordcount, nRowcount);
	LF->MsgBox(sCount);*/

	
	
	m_lstStart.Populate();

}


void CChargeDongSettingDlg::DelDestList(BOOL bServer)
{

	if(m_lstDest.GetSelectedCount() == 0)
		return;

	long nChargeAreaID = this->m_lstSectionName.GetSelectedRecord()->GetItemDataLong();
	if(bServer && nChargeAreaID < 0 )
	{
		LF->MsgBox("지역선택을 다시하여주세요");
		return;
	}

	for(int i= 0; i< m_lstDest.GetSelectedCount(); i++)
	{
		CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)m_lstDest.GetSelectedRows()->GetAt(i)->GetRecord();

		if(pRecord == NULL)
		{
			LF->MsgBox("작업중 오류가 있습니다. 로지소프트로 문의하세요");
			return;
		}
		if(bServer)
		{
			m_lstDest.CreateComandSetQuery("delete_charge_area_setting_detail");
			m_lstDest.AddParameter(nChargeAreaID);
			m_lstDest.AddParameter(pRecord->GetItemDataLong());
			m_lstDest.AddParameter(m_ci.m_nCompanyCode);
			m_lstDest.AddParameter(FALSE);
			if(!m_lstDest.ExcuteCmd())
				return;

		}
		pRecord->RemoveAll();
		m_lstDest.GetRecords()->RemoveAt(pRecord->GetIndex());


	}
	m_lstDest.Populate();


}

void CChargeDongSettingDlg::OnBnClickedDestListDelBtn()
{
	DelDestList(FALSE);
}

void CChargeDongSettingDlg::OnBnClickedDestListDelBtnServer()
{
		DelDestList(TRUE);
}
void CChargeDongSettingDlg::OnBnClickedSaveBtn()
{
	this->SaveStartList();
}

void CChargeDongSettingDlg::OnBnClickedSaveBtn2()
{
	this->SaveDestList();
}



void CChargeDongSettingDlg::OnBnClickedMotoCheck()
{
	m_edtMoto.EnableWindow(m_chkMoto.GetCheck());
}

void CChargeDongSettingDlg::OnBnClickedSaveAmountBtn()
{

	if(!LF->POWER_CHECK(1101, "요금수정/삭제", TRUE))
		return;
	try
	{
		UpdateData();

		if(!m_chkMoto.GetCheck() && !m_chkDama.GetCheck() 
			&& !m_chkBonggo.GetCheck() && !m_chkTruck.GetCheck())
			throw("체크가 모두 빠져있습니다");			


		long nCompany = (long)m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());		
		if(nCompany < 0)
			throw("선택한 지점명이 비정상적입니다. 회사선택을 다시하여주세요");

	
		long nCur = m_cmbDiscountCompany.GetCurSel();
		long nChargeID = (long)m_cmbDiscountCompany.GetItemData(nCur);

		if(this->m_chkMoto.GetCheck() && m_nMoto <= 0 )
		{
			m_edtMoto.SetFocus();		
			throw("오토바이에 금액을 입력하세요");
		}
		if(this->m_chkDama.GetCheck() && m_nDama <= 0 )
		{
			m_edtDama.SetFocus();		
			throw("다마스에 금액을 입력하세요");
		}
		if(this->m_chkBonggo.GetCheck() && m_nBonggo <= 0 )
		{
			m_edtBonggo.SetFocus();		
			throw("봉고에 금액을 입력하세요");
		}
		if(this->m_chkTruck.GetCheck() && m_nTruck <= 0 )
		{
			m_edtTruck.SetFocus();		
			throw("트럭에 금액을 입력하세요");
		}

		CMyXTPGridRecord *pDestRecord = NULL, *pStartRecord = NULL;
		BOOL bSuccess = FALSE;
		int nStartCurRow = this->m_lstStart.GetRecords()->GetCount();
		int nDestCurRow = this->m_lstDest.GetRecords()->GetCount();
		if(nStartCurRow == 0)
			throw("출발지에 데이터가 있어야 합니다");
	
		if(nDestCurRow == 0)
			throw("도착지에 데이터가 있어야 합니다");
		for(int i = 0; i < nStartCurRow; i++)
		{
			pStartRecord = (CMyXTPGridRecord *)m_lstStart.GetRecords()->GetAt(i);			
			for(int j=0; j < nDestCurRow; j++)
			{
				pDestRecord = (CMyXTPGridRecord *)m_lstDest.GetRecords()->GetAt(j);				
				CMkCommand pCmd(m_pMkDb, "update_charge_dong_info_batch");
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),	nCompany);		
				pCmd.AddParameter(typeLong, typeInput, sizeof(int),		GetType(pStartRecord, pDestRecord));
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),	pStartRecord->GetItemDataLong());
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),	pDestRecord->GetItemDataLong());
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),	m_nMoto);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),	m_nDama);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),	m_nBonggo);
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),	m_nTruck);
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),	m_chkShuttle.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),	m_chkMoto.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),	 m_chkDama.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),	m_chkBonggo.GetCheck());
				pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),	m_chkTruck.GetCheck());
				pCmd.AddParameter(typeLong, typeInput, sizeof(int),		m_cmbChargeType.GetCurSel());
				pCmd.AddParameter(typeLong, typeInput, sizeof(long),	nChargeID);
				if(!pCmd.Execute()) 
				{
					bSuccess = FALSE;
					throw("입력이 실패되었습니다.");
				}			
			}
		}
		throw("입력되었습니다.");
		
	}
	catch(char *e)
	{
		LF->MsgBox(e);
	}
	catch(CString s)
	{
		LF->MsgBox(s);
	}
}

int CChargeDongSettingDlg::GetType(CMyXTPGridRecord *pStartRecord, CMyXTPGridRecord *pDestRecord)
{
	int nStartType = pStartRecord->GetItemDataLong2();
	int nDestType = pDestRecord->GetItemDataLong2();
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

void CChargeDongSettingDlg::OnBnClickedDamaCheck()
{
	m_edtDama.EnableWindow(m_chkDama.GetCheck());
}

void CChargeDongSettingDlg::OnBnClickedBonggoCheck()
{
	m_edtBonggo.EnableWindow(m_chkBonggo.GetCheck());
}

void CChargeDongSettingDlg::OnBnClickedTruckCheck()
{
	m_edtTruck.EnableWindow(m_chkTruck.GetCheck());
}

void CChargeDongSettingDlg::OnBnClickedStartdestDelBtn()
{
	if(MessageBox("출발지 아이템과 도착지 아이템을 전부 삭제하시겠습니까?", 
		"확인", MB_ICONINFORMATION | MB_YESNO) == IDYES) 
		AllStartDestDelList();
}
void CChargeDongSettingDlg::AllStartDestDelList()
{
	m_lstStart.DeleteAllItem();
	m_lstDest.DeleteAllItem();
}

void CChargeDongSettingDlg::OnBnClickedStartdestBrinngBtn()
{
	int nStartSelection = 0, nDestSelection = 0;
	for(int i = 0; i < m_pChargeDongDlg->m_lstStart.GetSelectedRows()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_pChargeDongDlg->m_lstStart.GetSelectedRows()->GetAt(i)->GetRecord();
	
		CString strTemp = pRecord->GetItem(1)->GetCaption(NULL);
			if(strTemp.Compare("지역구분") != 0)
				nStartSelection++;
	}
	for(int i = 0; i < m_pChargeDongDlg->m_lstDest.GetSelectedRows()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_pChargeDongDlg->m_lstDest.GetSelectedRows()->GetAt(i)->GetRecord();
	
		CString strTemp = pRecord->GetItem(1)->GetCaption(NULL);
			if(strTemp.Compare("지역구분") != 0)
				nDestSelection++;
	}

		
	if(nStartSelection ==0 && nDestSelection == 0)
	{
		LF->MsgBox("요금표에서 출발지 도착지를 선택해주세요(지역구분은 지명이 아님)");
		return;
	}

	CXTPGridRecord *pRecord = m_lstSectionName.GetSelectedRow()->GetRecord();
	CString strAreaName = "";
	strAreaName = pRecord->GetItem(0)->GetCaption(NULL);
	if(strAreaName.GetLength() == 0)
	{
		LF->MsgBox("지역이름이 없습니다.");
		return;
	}
	strAreaName.Format("%s의 구간이름으로 가지고 옵니다. 맞습니까?",strAreaName);
	if(MessageBox(strAreaName, "확인", MB_ICONINFORMATION | MB_YESNO) == IDNO)
		return;	

	this->GetStartDongID(TRUE);
	this->GetDestDongID(TRUE);
}

void CChargeDongSettingDlg::OnBnClickedStartdestSaveBtn()
{
	this->SaveStartList();
	this->SaveDestList();
}

void CChargeDongSettingDlg::OnBnClickedNewAreaBtn()
{
	CVarietyDlg dlg;
	dlg.m_sTitleDlg = "신규 선택영역의 명칭을 적으세요";
	if(dlg.DoModal() == IDOK)
	{
		long nResult =0 , nNewChargeID = 0;
		CString sChargeName = dlg.m_sValue;
		if(sChargeName.GetLength() > 0 )
		{
			CMkRecordset pRs2(m_pMkDb);
			CMkCommand pCmd2(m_pMkDb, "insert_chargedong_name");	
			pCmd2.AddParameter(m_ci.m_nCompanyCode);		
			pCmd2.AddParameter(sChargeName);		
			CMkParameter *parResult = pCmd2.AddParameter(typeLong, typeOutput, sizeof(int), 0);
			CMkParameter *parNewChargeID = pCmd2.AddParameter(typeLong, typeOutput, sizeof(int), 0);

			if(!pRs2.Execute(&pCmd2)) return;

			parResult->GetValue(nResult);
			parNewChargeID->GetValue(nNewChargeID);

			if(nResult == 100 ) //  같은이름 존재
			{
				LF->MsgBox("같은이름이 존재합니다.");
				return;
			}

			for(int k = 0; k < m_lstSectionName.GetRows()->GetCount(); k++)
				m_lstSectionName.GetRows()->GetAt(k)->SetSelected(FALSE);
			m_lstSectionName.RedrawControl();

			
			CMyXTPGridRecord *pRecord = m_lstSectionName.MyAddItem(sChargeName);
			m_lstSectionName.InsertItemDataLong(nNewChargeID);
			m_lstSectionName.EndItem();
			m_lstSectionName.Populate();

			long nCount = m_lstSectionName.GetRows()->GetCount();
			m_lstSectionName.GetRows()->GetAt(nCount - 1)->SetSelected(TRUE);
	
		}
	}
}

void CChargeDongSettingDlg::OnBnClickedDeleteAreaBtn()
{
	if(this->m_lstSectionName.GetSelectedCount() == 0)
		return;
	
	if(MessageBox("해당 아이템을 삭제하시겠습니까?", "확인", MB_ICONINFORMATION | MB_YESNO) == IDYES)
	{		
		for(int i = 0; i < m_lstSectionName.GetSelectedCount(); i++)
		{
			CMyXTPGridRecord *pRecord = m_lstSectionName.GetSelectedRecord(i);
			long nChargeAreaID = pRecord->GetItemDataLong();
			if(nChargeAreaID <= 0)
			{
				m_lstSectionName.GetRecords()->RemoveAt(pRecord->GetIndex());
				m_lstSectionName.Populate();
			}
			else
			{
				m_lstSectionName.CreateComandSetQuery("delete_charge_area_setting");
				m_lstSectionName.AddParameter(nChargeAreaID);
				m_lstSectionName.AddParameter(m_ci.m_nCompanyCode);
				BOOL bSuccess = m_lstSectionName.ExcuteCmd();
				
				if(bSuccess == 0)
				{
					LF->MsgBox("삭제중오류가 났습니다. 다시시도하세요");
					return; 
				}
				else
				{
					m_lstSectionName.GetRecords()->RemoveAt(pRecord->GetIndex());
				}			
			}
		}					
		m_lstSectionName.Populate();
	}
}

void CChargeDongSettingDlg::OnBnClickedServerRefrshBtn()
{
	RefreshSection();
}




void CChargeDongSettingDlg::OnBnClickedSearchGroupBtn()
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

void CChargeDongSettingDlg::ChargeTypeNameRefresh()
{
	m_cmbDiscountCompany.ResetContent();
	m_cmbDiscountCompany.InsertString(0, "기본요금");
	m_cmbDiscountCompany.SetItemData(0, 0);

	int i = 1;
	MAP_CHARGE_TYPE_NAME::iterator it;
	for(it = m_mapChargeType.begin(); it != m_mapChargeType.end(); ++it)
	{
		if(it->second.strChargeName.GetLength() == 0)
			continue;

		m_cmbDiscountCompany.InsertString(i, it->second.strChargeName);
		m_cmbDiscountCompany.SetItemData(i, (DWORD_PTR)it->first);

		i++;
	}
	
}


void CChargeDongSettingDlg::OnBnClickedSearchGroupRefreshBtn()
{
	m_cg.FillCharge();
	ChargeTypeNameRefresh();
	this->m_cmbDiscountCompany.SetCurSel(0);
}




void CChargeDongSettingDlg::OnCbnSelchangeCompanyCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CChargeDongSettingDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CXTResizeDialog::OnShowWindow(bShow, nStatus);

	if(!bShow)
	{
		m_lstStart.DeleteAllItems();
		m_lstDest.DeleteAllItems();
	}
	
	
	
	
}

void CChargeDongSettingDlg::OnClose()
{
	
	for(int i = 0; i < m_lstSectionName.GetRows()->GetCount(); i++)
		m_lstSectionName.GetRows()->GetAt(i)->SetSelected(FALSE);

	m_lstStart.DeleteAllItems();
	m_lstDest.DeleteAllItems();

	CDialog::OnClose();
}


