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

	m_edtSearch.SetMyFont("���� ���", 15, FW_BOLD);
	m_edtSearch.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "����ȣ/�̸�", FALSE, FALSE);

	InitControlData();
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRiderInfoLogDlg::InitControlData()
{
	LF->FillBankCode(TRUE, &m_cmbBankID);

	m_List.InsertColumn(0, "����", LVCFMT_CENTER, 40);
	m_List.InsertColumn(1, "����", LVCFMT_LEFT, 95);
	m_List.InsertColumn(2, "����ȣ", LVCFMT_CENTER, 60);
	m_List.InsertColumn(3, "����", LVCFMT_LEFT, 70);
	m_List.InsertColumn(4, "������", LVCFMT_CENTER, 115);
	m_List.InsertColumn(5, "������", LVCFMT_LEFT, 65);

	CXTPGridColumn *pCol1 = m_ListDetail.AddColumn(new CXTPGridColumn(0, "����", 40, FALSE));
	CXTPGridColumn *pCol2 = m_ListDetail.AddColumn(new CXTPGridColumn(1, "����ȣ", 60, FALSE));
	CXTPGridColumn *pCol3 = m_ListDetail.AddColumn(new CXTPGridColumn(2, "������", 60, FALSE));
	CXTPGridColumn *pCol4 = m_ListDetail.AddColumn(new CXTPGridColumn(3, "�����ð�", 100, FALSE));
	CXTPGridColumn *pCol5 = m_ListDetail.AddColumn(new CXTPGridColumn(4, "���泻��", 80, FALSE));
	CXTPGridColumn *pCol6 = m_ListDetail.AddColumn(new CXTPGridColumn(5, "������", 200, FALSE));
	CXTPGridColumn *pCol7 = m_ListDetail.AddColumn(new CXTPGridColumn(6, "������", 200, FALSE));

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
	m_ListDetail.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";
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
			"�̸�����", pData->strName, pOriginData->strName, pMainRecord);
	}
	if(pData->strTel != pOriginData->strTel)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"����ȭ ����", pData->strTel, pOriginData->strTel, pMainRecord);
	}
	if(pData->strHp != pOriginData->strHp)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�޴��� ����", pData->strHp, pOriginData->strHp, pMainRecord);
	}
	if(pData->strID != pOriginData->strID)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"PDA ����", pData->strID, pOriginData->strID, pMainRecord);
	}
	if(pData->strBankAccountOwner != pOriginData->strBankAccountOwner)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"������ ����", pData->strBankAccountOwner, pOriginData->strBankAccountOwner, pMainRecord);
	}
	if(pData->dtEnter != pOriginData->dtEnter)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�Ի��� ����", pData->dtEnter.Format("%Y-%m-%d %H:%M:%S"), pOriginData->dtEnter.Format("%Y-%m-%d %H:%M:%S"), pMainRecord);
	}
	if(pData->nCarType != pOriginData->nCarType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"���� ����", LF->GetCarTypeFromLong(pData->nCarType), LF->GetCarTypeFromLong(pOriginData->nCarType), pMainRecord);
	}
	if(pData->nAllocGroup != pOriginData->nAllocGroup)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�Ҽӱ׷� ����", LU->GetAllocateGroup(pData->nAllocGroup), LU->GetAllocateGroup(pOriginData->nAllocGroup), pMainRecord);
	}
	if(pData->strAddress != pOriginData->strAddress)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�ּ� ����", pData->strAddress, pOriginData->strAddress, pMainRecord);
	}
	if(pData->strEtc != pOriginData->strEtc)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�޸� ����", pData->strEtc, pOriginData->strEtc, pMainRecord);
	}
	if(pData->strInnerMemo != pOriginData->strInnerMemo)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"���θ޸� ����", pData->strInnerMemo, pOriginData->strInnerMemo, pMainRecord);
	}
	if(pData->nDepositType != pOriginData->nDepositType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�ٹ����� ����", GetDepositType(pData->nDepositType), GetDepositType(pOriginData->nDepositType), pMainRecord);
	}
	if(pData->nDepositAllocateType != pOriginData->nDepositAllocateType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�Աݹ�� ����", GetDepositAllocateType(pData->nDepositAllocateType), GetDepositAllocateType(pOriginData->nDepositAllocateType), pMainRecord);
	}
	if(pData->nBankID != pOriginData->nBankID)
	{
		LF->FillBankCode(FALSE, &m_cmbBankID, pOriginData->nBankID);
		m_cmbBankID.GetLBText(m_cmbBankID.GetCurSel(), strOriginData);
		LF->FillBankCode(FALSE, &m_cmbBankID, pData->nBankID);
		m_cmbBankID.GetLBText(m_cmbBankID.GetCurSel(), strData);

		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"������� ����", strData, strOriginData, pMainRecord);
	}
	if(pData->strRTID != pOriginData->strRTID)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"���ID ����", pData->strRTID, pOriginData->strRTID, pMainRecord);
	}
	if(pData->nAllocType != pOriginData->nAllocType)
	{
		if(pOriginData->nAllocType == TWO) 			strOriginData = "PDA";
		else if(pOriginData->nAllocType == ONE) 	strOriginData = "SMS";
		else										strOriginData = "������";

		if(pData->nAllocType == TWO)				strData = "PDA";
		else if(pData->nAllocType == ONE)			strData = "SMS";
		else										strData = "������";
		
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"������� ����", strData, strOriginData, pMainRecord);
	}
	if(pData->nPanaltyTypeShowOrder != pOriginData->nPanaltyTypeShowOrder)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�������� ����", GetShareLimit(pData->nPanaltyTypeShowOrder), GetShareLimit(pOriginData->nPanaltyTypeShowOrder), pMainRecord);
	}
	if((pData->nLockTime != pOriginData->nLockTime) || (pData->nLockCount != pOriginData->nLockCount))
	{
		if(pData->nLockTime == ZERO || pData->nLockCount >= 100)
			strData = "������";
		else
			strData.Format("%d�г� %d������", pData->nLockTime, pData->nLockCount);

		if(pOriginData->nLockTime == ZERO || pOriginData->nLockCount >= 100)
			strOriginData = "������";
		else
			strOriginData.Format("%d�г� %d������", pOriginData->nLockTime, pOriginData->nLockCount);

		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�������� ����", strData, strOriginData, pMainRecord);
	}

	if((pData->bAutoShow != pOriginData->bAutoShow) || (pData->bBigAutoShow != pOriginData->bBigAutoShow) || (pData->bDamaShow != pOriginData->bDamaShow) || 
		(pData->bRaboShow != pOriginData->bRaboShow) || (pData->bBanShow != pOriginData->bBanShow) || (pData->bTruckShow != pOriginData->bTruckShow) ||
		(pData->bSubwayShow != pOriginData->bSubwayShow) || (pData->b6BanShow != pOriginData->b6BanShow) || (pData->bParcelServiceShow != pOriginData->bParcelServiceShow))
	{
		strData.Format("%s%s%s%s%s%s%s%s%s", pData->bAutoShow ? "����," : "", pData->bBigAutoShow ? "������," : "", pData->bDamaShow ? "�ٸ�," : ""
			, pData->bRaboShow ? "��," : "", pData->bBanShow ? "��," : "", pData->bTruckShow ? "Ʈ��," : ""
			, pData->bSubwayShow ? "����ö," : "", pData->b6BanShow ? "6��," : "", pData->bParcelServiceShow ? "�ù�" : "");

		strOriginData.Format("%s%s%s%s%s%s%s%s%s", pOriginData->bAutoShow ? "����," : "", pOriginData->bBigAutoShow ? "������," : "", pOriginData->bDamaShow ? "�ٸ�," : ""
			, pOriginData->bRaboShow ? "��," : "", pOriginData->bBanShow ? "��," : "", pOriginData->bTruckShow ? "Ʈ��," : ""
			, pOriginData->bSubwayShow ? "����ö," : "", pOriginData->b6BanShow ? "6��," : "", pOriginData->bParcelServiceShow ? "�ù�" : "");
		
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�������� ����", strData, strOriginData, pMainRecord);
	}
	if(pData->nThShareExceptType != pOriginData->nThShareExceptType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"��ð������� ����", pData->nThShareExceptType > ZERO ? "�Ⱥ���" : "����", pOriginData->nThShareExceptType > ZERO ? "�Ⱥ���" : "����", pMainRecord);
	}
	if(pData->nWithdrawType != pOriginData->nWithdrawType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"������� ����", pData->nWithdrawType > ZERO ? "���" : "�̻��", pOriginData->nWithdrawType > ZERO ? "���" : "�̻��", pMainRecord);
	}

	if(pData->nMaxWithdrawMoneyPerDay != pOriginData->nMaxWithdrawMoneyPerDay)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"��ݰ��ɱݾ� ����", LF->GetMyNumberFormat(pData->nMaxWithdrawMoneyPerDay), LF->GetMyNumberFormat(pOriginData->nMaxWithdrawMoneyPerDay), pMainRecord);
	}
	if(pData->nMinLeftMoneyForWithdraw != pOriginData->nMinLeftMoneyForWithdraw)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�ּ��ܾ� ����", LF->GetMyNumberFormat(pData->nMinLeftMoneyForWithdraw), LF->GetMyNumberFormat(pOriginData->nMinLeftMoneyForWithdraw), pMainRecord);
	}
	if(pData->bUseRiderTax != pOriginData->bUseRiderTax)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"��ݿ�õ¡�� ����", pData->bUseRiderTax ? "����" : "������", pOriginData->bUseRiderTax ? "����" : "������", pMainRecord);
	}
	if(pData->strRTSerial != pOriginData->strRTSerial)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"������ȣ ����", pData->strRTSerial, pOriginData->strRTSerial, pMainRecord);
	}
	if(pData->bAutoAlloc != pOriginData->bAutoAlloc)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�ڵ����� ����", pData->bAutoAlloc ? "���" : "�̻��", pOriginData->bAutoAlloc ? "���" : "�̻��", pMainRecord);
	}
	if(pData->strMyCallRateType != pOriginData->strMyCallRateType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�ڻ��� ����", pData->strMyCallRateType, pOriginData->strMyCallRateType, pMainRecord);
	}
	if(pData->strOtherCallRateType != pOriginData->strOtherCallRateType)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"Ÿ���� ����", pData->strOtherCallRateType, pOriginData->strOtherCallRateType, pMainRecord);
	}
	if(pData->nDailyDepositCharge != pOriginData->nDailyDepositCharge)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�Ϻ� ����", LF->GetMyNumberFormat(pData->nDailyDepositCharge), LF->GetMyNumberFormat(pOriginData->nDailyDepositCharge), pMainRecord);
	}
	if(pData->nTruckMyDepositRate != pOriginData->nTruckMyDepositRate)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"Ʈ���ڻ��Աݾ� ����", LF->GetStringFromLong(pData->nTruckMyDepositRate), LF->GetStringFromLong(pOriginData->nTruckMyDepositRate), pMainRecord);
	}
	if(pData->nTruckOtherDepositRate != pOriginData->nTruckOtherDepositRate)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"Ʈ��Ÿ���Աݾ� ����", LF->GetStringFromLong(pData->nTruckOtherDepositRate), LF->GetStringFromLong(pOriginData->nTruckOtherDepositRate), pMainRecord);
	}
	if(pData->nAllocMinCharge != pOriginData->nAllocMinCharge)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"�����ּұݾ� ����", LF->GetMyNumberFormat(pData->nAllocMinCharge), LF->GetMyNumberFormat(pOriginData->nAllocMinCharge), pMainRecord);
	}
	if(pData->strCarNo != pOriginData->strCarNo)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"������ȣ ����", pData->strCarNo, pOriginData->strCarNo, pMainRecord);
	}
	if(pData->bInsRegister != pOriginData->bInsRegister)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"���繰���� ����", pData->bInsRegister ? "���" : "�̻��", pOriginData->bInsRegister ? "���" : "�̻��", pMainRecord);
	}
	if(pData->strVRCardNumber != pOriginData->strVRCardNumber)
	{
		pMainRecord = InsertChangeRecord(strCount, pData->nRNo, pData->strWName, pData->dtChange.Format("%m-%d %H:%M:%S"), 
			"����ī�� ����", LF->GetDashCardNumber(pData->strVRCardNumber), LF->GetDashCardNumber(pOriginData->strVRCardNumber), pMainRecord);
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
		return "����";
	else if(nDepositType == 30)
		return "�Ϻ�";
	else if(nDepositType == 40)
		return "�ֺ�";
	else if(nDepositType == 50)
		return "������";

	return "��������";
}

CString CRiderInfoLogDlg::GetDepositAllocateType(long nDepositAllocateType)
{
	if(nDepositAllocateType == 0)
		return "���Ա�";
	else if(nDepositAllocateType == 10)
		return "���Ա�";
	else if(nDepositAllocateType == 20)
		return "������";

	return "��������";
}

CString CRiderInfoLogDlg::GetShareLimit(long nPanaltyTypeShowOrder)
{
	if(nPanaltyTypeShowOrder == 0)
		return "������������(��ü����)";
	else if(nPanaltyTypeShowOrder == 1)
		return "���ٸ�����(1������)";
	else if(nPanaltyTypeShowOrder == 2)
		return "�Ҽӿ���������(����)";

	return "��������";
}
