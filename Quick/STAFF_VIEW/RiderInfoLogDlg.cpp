#include "StdAfx.h"
#include "resource.h"
#include "RiderInfoLogDlg.h"

IMPLEMENT_DYNAMIC(CRiderInfoLogDlg, CMyDialog)
CRiderInfoLogDlg::CRiderInfoLogDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CRiderInfoLogDlg::IDD, pParent)
{
}

CRiderInfoLogDlg::~CRiderInfoLogDlg()
{
	int nRecordCount = m_List.GetRecords()->GetCount();
	for(int i = 0; i < nRecordCount; i++)
	{
		CXTPGridRecord *pRecord = m_List.GetRecords()->GetAt(i);
		ST_RIDER_INFO_LOG *pTemp = (ST_RIDER_INFO_LOG *)m_List.GetItemData(pRecord);
		if(pTemp)
			delete pTemp;
	}

	MAP_INFO_DATA::iterator it;
	for(it = m_mapData.begin(); it != m_mapData.end(); it++)
		delete it->second;

	m_mapData.clear();
}

void CRiderInfoLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_ALL, m_List);
	DDX_Control(pDX, IDC_REPORT_DETAIL, m_ListDetail);
	DDX_Control(pDX, IDC_BANK_ID_COMBO, m_cmbBankID);
	DDX_Control(pDX, IDC_RIDER_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CRiderInfoLogDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefresh)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_ALL, OnReportItemClick)
	ON_EN_CHANGE(IDC_RIDER_SEARCH_EDIT, OnEnChangeSearchEdit)
END_MESSAGE_MAP()

BOOL CRiderInfoLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtSearch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "기사번호/이름", FALSE, FALSE);

	InitControlData();
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderInfoLogDlg::InitControlData()
{
	LF->FillBankCode(TRUE, &m_cmbBankID);

	m_List.InsertColumn(0, "순번", LVCFMT_CENTER, 40);
	m_List.InsertColumn(1, "지사", LVCFMT_LEFT, 95);
	m_List.InsertColumn(2, "기사번호", LVCFMT_CENTER, 60);
	m_List.InsertColumn(3, "기사명", LVCFMT_LEFT, 70);
	m_List.InsertColumn(4, "수정일", LVCFMT_CENTER, 115);
	m_List.InsertColumn(5, "수정자", LVCFMT_LEFT, 65);

	CXTPGridColumn *pCol1 = m_ListDetail.AddColumn(new CXTPGridColumn(0, "순번", 40, FALSE));
	CXTPGridColumn *pCol2 = m_ListDetail.AddColumn(new CXTPGridColumn(1, "기사번호", 60, FALSE));
	CXTPGridColumn *pCol3 = m_ListDetail.AddColumn(new CXTPGridColumn(2, "수정자", 60, FALSE));
	CXTPGridColumn *pCol4 = m_ListDetail.AddColumn(new CXTPGridColumn(3, "수정시간", 100, FALSE));
	CXTPGridColumn *pCol5 = m_ListDetail.AddColumn(new CXTPGridColumn(4, "변경내역", 80, FALSE));
	CXTPGridColumn *pCol6 = m_ListDetail.AddColumn(new CXTPGridColumn(5, "변경전", 200, FALSE));
	CXTPGridColumn *pCol7 = m_ListDetail.AddColumn(new CXTPGridColumn(6, "변경후", 200, FALSE));

	pCol1->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol1->SetTreeColumn(1);
	pCol1->SetAlignment(DT_RIGHT);	
	pCol2->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol2->SetAlignment(DT_CENTER);
	pCol3->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol3->SetAlignment(DT_LEFT);
	pCol4->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol4->SetAlignment(DT_RIGHT);
	pCol5->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol5->SetAlignment(DT_CENTER);
	pCol6->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol6->SetAlignment(DT_CENTER);
	pCol7->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol7->SetAlignment(DT_CENTER);

	m_ListDetail.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_ListDetail.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_ListDetail.GetReportHeader()->AllowColumnRemove(FALSE);
	m_ListDetail.GetReportHeader()->AllowColumnResize(TRUE);
	m_ListDetail.GetReportHeader()->AllowColumnSort(TRUE);
	//m_ListDetail.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_ListDetail.AllowEdit(TRUE);
	m_ListDetail.FocusSubItems(TRUE);
	m_ListDetail.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_ListDetail.SetGridColor(RGB(180, 180, 200));
	m_ListDetail.SetTreeIndent(30);
	m_ListDetail.Populate();
}

void CRiderInfoLogDlg::RemoveControlData()
{
	m_cmbBankID.SetCurSel(ZERO);

	UpdateData();

	int nRecordCount = m_List.GetRecords()->GetCount();
	for (int i = 0; i < nRecordCount; i++)
	{
		CXTPGridRecord *pRecord = m_List.GetRecords()->GetAt(i);
		ST_RIDER_INFO_LOG *pTemp = (ST_RIDER_INFO_LOG *)m_List.GetItemData(pRecord);
		if(pTemp)
			delete pTemp;
	}

	MAP_INFO_DATA::iterator it;
	for(it = m_mapData.begin(); it != m_mapData.end(); it++)
		delete it->second;

	m_mapData.clear();
	m_ListDetail.GetRecords()->RemoveAll();
}

void CRiderInfoLogDlg::OnBnClickedRefresh()
{
	RefreshList();
}

void CRiderInfoLogDlg::RefreshList()
{
	RemoveControlData();
	m_List.DeleteAllItems();
	m_ListDetail.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_info_log_1"); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), LF->GetCurBranchInfo()->bIntegrated);

	if(!pRs.Execute(&pCmd))
		return;

	CXTPGridRecord *pPreRecord = NULL;
	long nRecordIndex = 0;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		ST_RIDER_INFO_LOG *pstLog = new ST_RIDER_INFO_LOG;

		pRs.GetFieldValue("nID", pstLog->nID);
		pRs.GetFieldValue("nCompany", pstLog->nCompany);
		pRs.GetFieldValue("nRNo", pstLog->nRNo);
		pRs.GetFieldValue("sName", pstLog->strName);
		pRs.GetFieldValue("sWName", pstLog->strWName);
		pRs.GetFieldValue("dtChange", pstLog->dtChange);

		pRs.GetFieldValue("sTel", pstLog->strTel);
		pRs.GetFieldValue("sHp", pstLog->strHp);
		pRs.GetFieldValue("sID", pstLog->strID);
		pRs.GetFieldValue("sBankAccountOwner", pstLog->strBankAccountOwner);
		pRs.GetFieldValue("sBankAccount", pstLog->strBankAccount);
		pRs.GetFieldValue("dtEnter", pstLog->dtEnter);
		pRs.GetFieldValue("nCarType", pstLog->nCarType);
		pRs.GetFieldValue("nAllocGroup", pstLog->nAllocGroup);
		pRs.GetFieldValue("sAddress", pstLog->strAddress);
		pRs.GetFieldValue("sEtc", pstLog->strEtc);
		pRs.GetFieldValue("sInnerMemo", pstLog->strInnerMemo);
		pRs.GetFieldValue("nDepositType", pstLog->nDepositType);
		pRs.GetFieldValue("nDepositAllocateType", pstLog->nDepositAllocateType);
		pRs.GetFieldValue("nBankID", pstLog->nBankID);
		pRs.GetFieldValue("sRTID", pstLog->strRTID);
		pRs.GetFieldValue("nAllocType", pstLog->nAllocType);
		pRs.GetFieldValue("nPanaltyTypeShowOrder", pstLog->nPanaltyTypeShowOrder);
		pRs.GetFieldValue("nLockTime", pstLog->nLockTime);
		pRs.GetFieldValue("nLockCount", pstLog->nLockCount);
		pRs.GetFieldValue("bAutoShow", pstLog->bAutoShow);
		pRs.GetFieldValue("bBigAutoShow", pstLog->bBigAutoShow);
		pRs.GetFieldValue("bDamaShow", pstLog->bDamaShow);
		pRs.GetFieldValue("bRaboShow", pstLog->bRaboShow);
		pRs.GetFieldValue("bBanShow", pstLog->bBanShow);
		pRs.GetFieldValue("bTruckShow", pstLog->bTruckShow);
		pRs.GetFieldValue("bSubwayShow", pstLog->bSubwayShow);
		pRs.GetFieldValue("b6BanShow", pstLog->b6BanShow);
		pRs.GetFieldValue("bParcelServiceShow", pstLog->bParcelServiceShow);
		pRs.GetFieldValue("nThShareExceptType", pstLog->nThShareExceptType);
		pRs.GetFieldValue("nWithdrawType", pstLog->nWithdrawType);
		pRs.GetFieldValue("nMaxWithdrawMoneyPerDay", pstLog->nMaxWithdrawMoneyPerDay);
		pRs.GetFieldValue("nMinLeftMoneyForWithdraw", pstLog->nMinLeftMoneyForWithdraw);
		pRs.GetFieldValue("bUseRiderTax", pstLog->bUseRiderTax);
		pRs.GetFieldValue("sRTSerial", pstLog->strRTSerial);
		pRs.GetFieldValue("bAutoAlloc", pstLog->bAutoAlloc);
		pRs.GetFieldValue("nMyCallRateType", pstLog->nMyCallRateType);
		pRs.GetFieldValue("nOtherCallRateType", pstLog->nOtherCallRateType);
		pRs.GetFieldValue("nDailyDepositCharge", pstLog->nDailyDepositCharge);
		pRs.GetFieldValue("nTruckMyDepositRate", pstLog->nTruckMyDepositRate);
		pRs.GetFieldValue("nTruckOtherDepositRate", pstLog->nTruckOtherDepositRate);
		pRs.GetFieldValue("sMyCallRateType", pstLog->strMyCallRateType);
		pRs.GetFieldValue("sOtherCallRateType", pstLog->strOtherCallRateType);
		pRs.GetFieldValue("nAllocMinCharge", pstLog->nAllocMinCharge);
		pRs.GetFieldValue("sCarNo", pstLog->strCarNo);
		pRs.GetFieldValue("bInsRegister", pstLog->bInsRegister);
		pRs.GetFieldValue("sVRCardNumber", pstLog->strVRCardNumber);
		pRs.GetFieldValue("nPreInfoID", pstLog->nPreInfoID);

		if(pstLog->nPreInfoID == 0)
		{
			m_List.InsertItem(nRecordIndex, LF->GetStringFromLong(nRecordIndex + 1));
			m_List.SetItemText(nRecordIndex, 1, m_ci.GetBranchName(pstLog->nCompany));
			m_List.SetItemText(nRecordIndex, 2, LF->GetStringFromLong(pstLog->nRNo));
			m_List.SetItemText(nRecordIndex, 3, pstLog->strName);
			m_List.SetItemText(nRecordIndex, 4, pstLog->dtChange.Format("%Y-%m-%d %H:%M:%S"));
			m_List.SetItemText(nRecordIndex, 5, pstLog->strWName);
			m_List.SetItemData(nRecordIndex, (DWORD)pstLog);
			nRecordIndex++;
		}
		else
			m_mapData.insert(MAP_INFO_DATA::value_type(pstLog->nPreInfoID, pstLog));

		pRs.MoveNext();
	}

	pRs.Close();
	m_List.Populate();
	m_ListDetail.Populate();
}

void CRiderInfoLogDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();
	if(pRecord)
	{
		ST_RIDER_INFO_LOG *pTemp = (ST_RIDER_INFO_LOG *)m_List.GetItemData(pRecord);
		if(!pTemp)
			return;

		InsertListData(m_List.GetItemText(pRecord, 0), pTemp);
	}
}

void CRiderInfoLogDlg::InsertListData(CString strCount, ST_RIDER_INFO_LOG *pData)
{
	MAP_INFO_DATA::iterator it = m_mapData.find(pData->nID);
	if(it == m_mapData.end())
		return;

	m_ListDetail.GetRecords()->RemoveAll();
	ST_RIDER_INFO_LOG *pOriginData = it->second;
	CXTPGridRecord *pMainRecord = NULL;
	CString strOriginData, strData;

	if(pData->strName != pOriginData->strName)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"이름변경", pData->strName, pOriginData->strName, pMainRecord);
	}
	if(pData->strTel != pOriginData->strTel)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"집전화 변경", pData->strTel, pOriginData->strTel, pMainRecord);
	}
	if(pData->strHp != pOriginData->strHp)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"휴대폰 변경", pData->strHp, pOriginData->strHp, pMainRecord);
	}
	if(pData->strID != pOriginData->strID)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"PDA 변경", pData->strID, pOriginData->strID, pMainRecord);
	}
	if(pData->strBankAccountOwner != pOriginData->strBankAccountOwner)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"예금주 변경", pData->strBankAccountOwner, pOriginData->strBankAccountOwner, pMainRecord);
	}
	if(pData->dtEnter != pOriginData->dtEnter)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"입사일 변경", pData->dtEnter.Format("%Y-%m-%d %H:%M:%S"), pOriginData->dtEnter.Format("%Y-%m-%d %H:%M:%S"), pMainRecord);
	}
	if(pData->nCarType != pOriginData->nCarType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"차종 변경", LF->GetCarTypeFromLong(pData->nCarType), LF->GetCarTypeFromLong(pOriginData->nCarType), pMainRecord);
	}
	if(pData->nAllocGroup != pOriginData->nAllocGroup)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"소속그룹 변경", LU->GetAllocateGroup(pData->nAllocGroup), LU->GetAllocateGroup(pOriginData->nAllocGroup), pMainRecord);
	}
	if(pData->strAddress != pOriginData->strAddress)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"주소 변경", pData->strAddress, pOriginData->strAddress, pMainRecord);
	}
	if(pData->strEtc != pOriginData->strEtc)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"메모 변경", pData->strEtc, pOriginData->strEtc, pMainRecord);
	}
	if(pData->strInnerMemo != pOriginData->strInnerMemo)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"내부메모 변경", pData->strInnerMemo, pOriginData->strInnerMemo, pMainRecord);
	}
	if(pData->nDepositType != pOriginData->nDepositType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"근무유형 변경", GetDepositType(pData->nDepositType), GetDepositType(pOriginData->nDepositType), pMainRecord);
	}
	if(pData->nDepositAllocateType != pOriginData->nDepositAllocateType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"입금방식 변경", GetDepositAllocateType(pData->nDepositAllocateType), GetDepositAllocateType(pOriginData->nDepositAllocateType), pMainRecord);
	}
	if(pData->nBankID != pOriginData->nBankID)
	{
		LF->FillBankCode(FALSE, &m_cmbBankID, pOriginData->nBankID);
		m_cmbBankID.GetLBText(m_cmbBankID.GetCurSel(), strOriginData);
		LF->FillBankCode(FALSE, &m_cmbBankID, pData->nBankID);
		m_cmbBankID.GetLBText(m_cmbBankID.GetCurSel(), strData);

		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"출금은행 변경", strData, strOriginData, pMainRecord);
	}
	if(pData->strRTID != pOriginData->strRTID)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"기기ID 변경", pData->strRTID, pOriginData->strRTID, pMainRecord);
	}
	if(pData->nAllocType != pOriginData->nAllocType)
	{
		if(pOriginData->nAllocType == TWO) 			strOriginData = "PDA";
		else if(pOriginData->nAllocType == ONE) 	strOriginData = "SMS";
		else										strOriginData = "사용안함";

		if(pData->nAllocType == TWO)				strData = "PDA";
		else if(pData->nAllocType == ONE)			strData = "SMS";
		else										strData = "사용안함";
		
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"배차방식 변경", strData, strOriginData, pMainRecord);
	}
	if(pData->nPanaltyTypeShowOrder != pOriginData->nPanaltyTypeShowOrder)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"공유제한 변경", GetShareLimit(pData->nPanaltyTypeShowOrder), GetShareLimit(pOriginData->nPanaltyTypeShowOrder), pMainRecord);
	}
	if((pData->nLockTime != pOriginData->nLockTime) || (pData->nLockCount != pOriginData->nLockCount))
	{
		if(pData->nLockTime == ZERO || pData->nLockCount >= 100)
			strData = "무제한";
		else
			strData.Format("%d분내 %d건이하", pData->nLockTime, pData->nLockCount);

		if(pOriginData->nLockTime == ZERO || pOriginData->nLockCount >= 100)
			strOriginData = "무제한";
		else
			strOriginData.Format("%d분내 %d건이하", pOriginData->nLockTime, pOriginData->nLockCount);

		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"배차제한 변경", strData, strOriginData, pMainRecord);
	}

	if((pData->bAutoShow != pOriginData->bAutoShow) || (pData->bBigAutoShow != pOriginData->bBigAutoShow) || (pData->bDamaShow != pOriginData->bDamaShow) || 
		(pData->bRaboShow != pOriginData->bRaboShow) || (pData->bBanShow != pOriginData->bBanShow) || (pData->bTruckShow != pOriginData->bTruckShow) ||
		(pData->bSubwayShow != pOriginData->bSubwayShow) || (pData->b6BanShow != pOriginData->b6BanShow) || (pData->bParcelServiceShow != pOriginData->bParcelServiceShow))
	{
		strData.Format("%s%s%s%s%s%s%s%s%s", pData->bAutoShow ? "오토," : "", pData->bBigAutoShow ? "짐받이," : "", pData->bDamaShow ? "다마," : ""
			, pData->bRaboShow ? "라보," : "", pData->bBanShow ? "밴," : "", pData->bTruckShow ? "트럭," : ""
			, pData->bSubwayShow ? "지하철," : "", pData->b6BanShow ? "6밴," : "", pData->bParcelServiceShow ? "택배" : "");

		strOriginData.Format("%s%s%s%s%s%s%s%s%s", pOriginData->bAutoShow ? "오토," : "", pOriginData->bBigAutoShow ? "짐받이," : "", pOriginData->bDamaShow ? "다마," : ""
			, pOriginData->bRaboShow ? "라보," : "", pOriginData->bBanShow ? "밴," : "", pOriginData->bTruckShow ? "트럭," : ""
			, pOriginData->bSubwayShow ? "지하철," : "", pOriginData->b6BanShow ? "6밴," : "", pOriginData->bParcelServiceShow ? "택배" : "");
		
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"세부차종 변경", strData, strOriginData, pMainRecord);
	}
	if(pData->nThShareExceptType != pOriginData->nThShareExceptType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"즉시공유오더 변경", pData->nThShareExceptType > ZERO ? "안보임" : "보임", pOriginData->nThShareExceptType > ZERO ? "안보임" : "보임", pMainRecord);
	}
	if(pData->nWithdrawType != pOriginData->nWithdrawType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"출금정보 변경", pData->nWithdrawType > ZERO ? "사용" : "미사용", pOriginData->nWithdrawType > ZERO ? "사용" : "미사용", pMainRecord);
	}

	if(pData->nMaxWithdrawMoneyPerDay != pOriginData->nMaxWithdrawMoneyPerDay)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"출금가능금액 변경", LF->GetMyNumberFormat(pData->nMaxWithdrawMoneyPerDay), LF->GetMyNumberFormat(pOriginData->nMaxWithdrawMoneyPerDay), pMainRecord);
	}
	if(pData->nMinLeftMoneyForWithdraw != pOriginData->nMinLeftMoneyForWithdraw)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"최소잔액 변경", LF->GetMyNumberFormat(pData->nMinLeftMoneyForWithdraw), LF->GetMyNumberFormat(pOriginData->nMinLeftMoneyForWithdraw), pMainRecord);
	}
	if(pData->bUseRiderTax != pOriginData->bUseRiderTax)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"출금원천징수 변경", pData->bUseRiderTax ? "차감" : "미차감", pOriginData->bUseRiderTax ? "차감" : "미차감", pMainRecord);
	}
	if(pData->strRTSerial != pOriginData->strRTSerial)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"제조번호 변경", pData->strRTSerial, pOriginData->strRTSerial, pMainRecord);
	}
	if(pData->bAutoAlloc != pOriginData->bAutoAlloc)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"자동배차 변경", pData->bAutoAlloc ? "사용" : "미사용", pOriginData->bAutoAlloc ? "사용" : "미사용", pMainRecord);
	}
	if(pData->strMyCallRateType != pOriginData->strMyCallRateType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"자사콜 변경", pData->strMyCallRateType, pOriginData->strMyCallRateType, pMainRecord);
	}
	if(pData->strOtherCallRateType != pOriginData->strOtherCallRateType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"타사콜 변경", pData->strOtherCallRateType, pOriginData->strOtherCallRateType, pMainRecord);
	}
	if(pData->nDailyDepositCharge != pOriginData->nDailyDepositCharge)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"일비 변경", LF->GetMyNumberFormat(pData->nDailyDepositCharge), LF->GetMyNumberFormat(pOriginData->nDailyDepositCharge), pMainRecord);
	}
	if(pData->nTruckMyDepositRate != pOriginData->nTruckMyDepositRate)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"트럭자사입금액 변경", LF->GetStringFromLong(pData->nTruckMyDepositRate), LF->GetStringFromLong(pOriginData->nTruckMyDepositRate), pMainRecord);
	}
	if(pData->nTruckOtherDepositRate != pOriginData->nTruckOtherDepositRate)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"트럭타사입금액 변경", LF->GetStringFromLong(pData->nTruckOtherDepositRate), LF->GetStringFromLong(pOriginData->nTruckOtherDepositRate), pMainRecord);
	}
	if(pData->nAllocMinCharge != pOriginData->nAllocMinCharge)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"배차최소금액 변경", LF->GetMyNumberFormat(pData->nAllocMinCharge), LF->GetMyNumberFormat(pOriginData->nAllocMinCharge), pMainRecord);
	}
	if(pData->strCarNo != pOriginData->strCarNo)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"차량번호 변경", pData->strCarNo, pOriginData->strCarNo, pMainRecord);
	}
	if(pData->bInsRegister != pOriginData->bInsRegister)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"적재물보험 변경", pData->bInsRegister ? "사용" : "미사용", pOriginData->bInsRegister ? "사용" : "미사용", pMainRecord);
	}
	if(pData->strVRCardNumber != pOriginData->strVRCardNumber)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"선불카드 변경", LF->GetDashCardNumber(pData->strVRCardNumber), LF->GetDashCardNumber(pOriginData->strVRCardNumber), pMainRecord);
	}

	m_ListDetail.Populate();
}

// CXTPGridRecord CRiderInfoLogDlg::InsertChangeMainRecord(CString strCount, int nRNo, CString strWName, CString strDate, CString strChange, CString strBefore, CString strAfter)
// {
// 	return m_ListDetail.AddRecord(new CRiderInfoLogDetailRecord(strCount, nRNo, strWName, strDate, strChange, strBefore, strAfter));
// }

CXTPGridRecord * CRiderInfoLogDlg::InsertChangeRecord(CString strCount, int nRNo, CString strWName, CString strDate, CString strChange, CString strBefore, CString strAfter, CXTPGridRecord* pMainRecord)
{
	if(!pMainRecord)
	{
		CXTPGridRecord *pRecord = m_ListDetail.AddRecord(new CRiderInfoLogDetailRecord(strCount, nRNo, strWName, strDate, strChange, strBefore, strAfter));
		return pRecord;
	}
	else
	{
		pMainRecord->GetChilds()->Add(new CRiderInfoLogDetailRecord(strCount, strChange, strBefore, strAfter));
		pMainRecord->SetExpanded(TRUE);
		return pMainRecord;
	}
}

void CRiderInfoLogDlg::OnEnChangeSearchEdit()
{
	CString strSearch;
	m_edtSearch.GetWindowText(strSearch);

	int nRecordCount = m_List.GetRecords()->GetCount();
	for (int i = 0; i < nRecordCount; i++)
	{
		CXTPGridRecord *pRecord = m_List.GetRecords()->GetAt(i);

		CString sRNo = m_List.GetItemText(pRecord, 2);
		CString sRName = m_List.GetItemText(pRecord, 3);

		if(sRNo.Find(strSearch) >= 0 ||
			sRName.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_List.Populate();
}

//////////////////////////////////////////////////////////////////////////

CString CRiderInfoLogDlg::GetDepositType(long nDepositType)
{
	if(nDepositType == 20)
		return "월비";
	else if(nDepositType == 30)
		return "일비";
	else if(nDepositType == 40)
		return "주비";
	else if(nDepositType == 50)
		return "프로제";

	return "정보없음";
}

CString CRiderInfoLogDlg::GetDepositAllocateType(long nDepositAllocateType)
{
	if(nDepositAllocateType == 0)
		return "선입금";
	else if(nDepositAllocateType == 10)
		return "후입금";
	else if(nDepositAllocateType == 20)
		return "프로제";

	return "정보없음";
}

CString CRiderInfoLogDlg::GetShareLimit(long nPanaltyTypeShowOrder)
{
	if(nPanaltyTypeShowOrder == 0)
		return "공유오더보기(전체보기)";
	else if(nPanaltyTypeShowOrder == 1)
		return "오다만보기(1차공유)";
	else if(nPanaltyTypeShowOrder == 2)
		return "소속오더만보기(지사)";

	return "정보없음";
}
