// ChargeListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeListDlg.h"
#include "ChargenameNewDlg.h"
#include "MainFrm.h"
// CChargeListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeListDlg, CMyDialog)
CChargeListDlg::CChargeListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeListDlg::IDD, pParent)
{
	m_nCompany = 0;
}

CChargeListDlg::~CChargeListDlg()
{
}

void CChargeListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_CHARGE_EDIT, m_edtSearchChargeWord);
	DDX_Control(pDX, IDC_GROUP_LIST,	m_lstGroupList);
	DDX_Control(pDX, IDC_CHARGE_LIST,	m_lstChargeList);
	DDX_Control(pDX, IDC_ALLGROUP_LIST,	m_lstAllGroupList);
	DDX_Control(pDX, IDC_REGISTER_CHARGE_LIST,	m_lstRegisterChargeList);

	DDX_Control(pDX, IDC_CHECK1, m_chkRegisterView);
	DDX_Control(pDX, IDC_SEARCH_GROUP_EDIT, m_edtSearchGroup);
	DDX_Control(pDX, IDC_TYPE_CMB, m_cmbType);
	DDX_Control(pDX, IDC_TWOWAY_CHECK, m_chkTwoWay);
}


BEGIN_MESSAGE_MAP(CChargeListDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ALL_CHARGE_BTN, OnBnClickedAllChargeBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_SEARCH_CHARGE_EDIT, OnEnChangeSearchChargeEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_CHARGE_LIST, OnReportItemDblClick)
	ON_NOTIFY(NM_CLICK, IDC_CHARGE_LIST, OnReportItemClick)
	
	
	
	ON_BN_CLICKED(IDC_CHARGE_NAME_MODIFY_BTN, OnBnClickedChargeNameModifyBtn)
	ON_BN_CLICKED(IDC_CHARGE_NAME_NEW_BTN, OnBnClickedChargeNameNewBtn)
	ON_BN_CLICKED(IDC_CHARGE_TYPENAME_INPUT_BTN, OnBnClickedChargeTypenameInputBtn)
	ON_BN_CLICKED(IDC_CHARGE_TYPENAME_DEL_BTN, OnBnClickedChargeTypenameDelBtn)
	ON_EN_CHANGE(IDC_SEARCH_GROUP_EDIT, OnEnChangeSearchGroupEdit)
	ON_BN_CLICKED(ID_MODIFY_CHARGE_BTN, OnBnClickedModifyChargeBtn)
	ON_BN_CLICKED(ID_EXCEL_BTN, OnBnClickedExcelBtn)
	ON_BN_CLICKED(ID_CHARGE_WINDOW_BTN, OnBnClickedChargeWindowBtn)
	ON_BN_CLICKED(IDC_CHARGE_DELETE_BTN, OnBnClickedChargeDeleteBtn)
END_MESSAGE_MAP()


// CChargeListDlg 메시지 처리기입니다.


BOOL CChargeListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstChargeList.InsertColumn(0, "회사명", LVCFMT_LEFT, 100);
	m_lstChargeList.InsertColumn(1, "요금제이름", LVCFMT_LEFT, 120);
	m_lstChargeList.InsertColumn(2, "비고", LVCFMT_LEFT, 90);
	m_lstChargeList.Populate();

	m_lstGroupList.InsertColumn(0, "그룹 이름", LVCFMT_LEFT, 130)->SetTreeColumn(TRUE);
	m_lstGroupList.InsertColumn(1, "부서", LVCFMT_LEFT, 80);
	m_lstGroupList.InsertColumn(2, "요금제 이름", LVCFMT_LEFT, 90);

	m_lstGroupList.SetTreeIndent(10);
	m_lstGroupList.Populate();

	m_lstAllGroupList.InsertColumn(0, "그룹 이름", LVCFMT_LEFT, 130)->SetTreeColumn(TRUE);
	m_lstAllGroupList.InsertColumn(1, "부서", LVCFMT_LEFT, 80);
	m_lstAllGroupList.InsertColumn(2, "요금제 이름", LVCFMT_LEFT, 90);
	m_lstAllGroupList.SetTreeIndent(10);
	m_lstAllGroupList.Populate();

	m_lstRegisterChargeList.InsertColumn(0, "요금제이름", LVCFMT_LEFT, 100);
	m_lstRegisterChargeList.InsertColumn(1, "출발구", LVCFMT_LEFT, 90);
	m_lstRegisterChargeList.InsertColumn(2, "출발동", LVCFMT_LEFT, 65);
	m_lstRegisterChargeList.InsertColumn(3, "타입", LVCFMT_LEFT, 60);
	m_lstRegisterChargeList.InsertColumn(4, "도착구", LVCFMT_LEFT, 90);
	m_lstRegisterChargeList.InsertColumn(5, "도착동", LVCFMT_LEFT, 65);
	m_lstRegisterChargeList.InsertColumn(6, "오토바이", LVCFMT_RIGHT, 70);
	m_lstRegisterChargeList.InsertColumn(7, "다마스", LVCFMT_RIGHT, 70);
	m_lstRegisterChargeList.InsertColumn(8, "봉고", LVCFMT_RIGHT, 70);
	m_lstRegisterChargeList.InsertColumn(9, "트럭", LVCFMT_RIGHT, 70);
	m_lstRegisterChargeList.Populate();

	RefreshList();
	return TRUE;  
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChargeListDlg::RefreshList()
{
	m_lstChargeList.DeleteAllItems();

	MAP_CHARGE_TYPE_NAME::iterator it;

	long nItem = 0;

	for(it = m_mapChargeType.begin(); it != m_mapChargeType.end(); ++it)
	{
		if (it->second.strChargeName.GetLength() == 0)
			continue;

		m_lstChargeList.InsertItem(nItem, m_ci.GetBranchName(it->second.nCompany));
		m_lstChargeList.SetItemText(nItem, 1, it->second.strChargeName);
		m_lstChargeList.SetItemText(nItem, 2, it->second.strEtc);
		m_lstChargeList.SetItemLong(nItem, it->first);
		nItem++;
	}
	m_lstChargeList.Populate();
	
	AllGroupRefresh();
}

void CChargeListDlg::AllGroupRefresh()
{
	m_lstAllGroupList.DeleteAllItems();

	MAP_CUSTOMER_GROUP::iterator it;

	CChargeListRecord* record = nullptr;

	for(it = m_cg.GetGroup()->begin(); it != m_cg.GetGroup()->end(); ++it)
	{
		if(it->second->strGroupName.GetLength() == 0)
			continue;

		if (record) {
			if (record->GetGNoKey() == it->second->nGNoKey) {
				record = new CChargeListRecord(it->second->strGroupName, it->second->strDept, it->second->strChargeName, it->first, it->second->nGNoKey);
				m_lstAllGroupList.AddRecord(record);
			}
			else {
				CXTPGridRecord* child_record =
					new CChargeListRecord(it->second->strGroupName, it->second->strDept, it->second->strChargeName, it->first, it->second->nGNoKey);
				record->GetChilds()->Add(child_record);
			}
		}
		else {
			record = new CChargeListRecord(it->second->strGroupName, it->second->strDept, it->second->strChargeName, it->first, it->second->nGNoKey);
			m_lstAllGroupList.AddRecord(record);
		}
	}

	m_lstAllGroupList.Populate();
	m_lstAllGroupList.ExpandAll();
}


void CChargeListDlg::OnBnClickedAllChargeBtn()
{
	m_lstChargeList.ShowAllRow();
}

void CChargeListDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CChargeListDlg::OnEnChangeSearchChargeEdit()
{
	CString strSearchChargeName = "";
	m_edtSearchChargeWord.GetWindowText(strSearchChargeName);
	if(strSearchChargeName.GetLength() == 0)
	{
		m_lstChargeList.ShowAllRow();
		return;
	}
	
	CXTPGridRecord *pRecord = NULL;
	MAP_CHARGE_TYPE_NAME::iterator it;
	
	CUIntArray IntArray;
	CString strChargeName;
	for(it = m_mapChargeType.begin(); it != m_mapChargeType.end(); ++it)
	{
		strChargeName = it->second.strChargeName;
		if(strChargeName.GetLength() == 0)
			continue;
		strChargeName.MakeUpper();
		strSearchChargeName.MakeUpper();

		if(strChargeName.Find(strSearchChargeName, 0) >= 0 )
			IntArray.Add(it->first);		
	}	

	if(IntArray.GetCount() == 0)
		return;

	for(int i = 0; i < m_lstChargeList.GetRecords()->GetCount(); i++)
	{
		pRecord = m_lstChargeList.GetRecords()->GetAt(i);


		for (int j = 0; j < IntArray.GetCount(); j++)
		{
			//int m = pRecord->GetItemDataLong();

			if (m_lstChargeList.GetItemLong(pRecord) == IntArray.GetAt(j))
				pRecord->SetVisible(TRUE);
			else
				pRecord->SetVisible(FALSE);
		}
	}
	
	m_lstChargeList.Populate();
}

void CChargeListDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
	return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nRow < 0)
		return;

	ChargeGroupModify(nRow);
	

	
}
void CChargeListDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nRow < 0)
		return;

	RegisterGroupView();

	if(m_chkRegisterView.GetCheck())
		RegisterChargeView();

}


void CChargeListDlg::RegisterChargeView()
{
	if(m_lstChargeList.GetSelectedRows()->GetCount() == 0 )
		return;

	CXTPGridRecord *pRecord = NULL;
	pRecord = m_lstChargeList.GetFirstSelectedRecord();

	if(pRecord  == NULL)
		return;	
	long nChargeID = m_lstChargeList.GetItemLong(pRecord);
	
	if(nChargeID <= 0)
	{
		MessageBox("등록된 요금이 없습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	m_lstRegisterChargeList.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_charge_id_list");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nChargeID);
	
	if(!pRs.Execute(&pCmd)) return;

	int nItem = 0;
	CString sChargeName, sStartGu, sStartDong, sTypeView, sDestGu, sDestDong;
	long nRsChargeID, nStartID,nTypeCode, nDestID,nMoto, nDama, nBonggo,nTruck,nRegisterChargeID;
	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("요금제번호", nRsChargeID);
		pRs.GetFieldValue("요금제이름", sChargeName);			
		pRs.GetFieldValue("출발지아이디", nStartID);			
		pRs.GetFieldValue("출발구", sStartGu);
		pRs.GetFieldValue("출발동", sStartDong);
		pRs.GetFieldValue("타입코드", nTypeCode);
		pRs.GetFieldValue("타입", sTypeView);		
		pRs.GetFieldValue("도착지코드", nDestID);
		pRs.GetFieldValue("도착구", sDestGu);
		pRs.GetFieldValue("도착동", sDestDong);
		pRs.GetFieldValue("오토바이", nMoto);
		pRs.GetFieldValue("다마스", nDama);
		pRs.GetFieldValue("봉고", nBonggo);
		pRs.GetFieldValue("트럭", nTruck);
		pRs.GetFieldValue("요금순번", nRegisterChargeID);

		m_lstRegisterChargeList.InsertItem(nItem, sChargeName);
		m_lstRegisterChargeList.SetItemText(nItem, 1, sStartGu);
		m_lstRegisterChargeList.SetItemText(nItem, 2, sStartDong);
		m_lstRegisterChargeList.SetItemText(nItem, 3, sTypeView);
		m_lstRegisterChargeList.SetItemText(nItem, 4, sDestGu);
		m_lstRegisterChargeList.SetItemText(nItem, 5, sDestDong);
		m_lstRegisterChargeList.SetItemText(nItem, 6, nMoto);
		m_lstRegisterChargeList.SetItemText(nItem, 7, nDama);
		m_lstRegisterChargeList.SetItemText(nItem, 8, nBonggo);
		m_lstRegisterChargeList.SetItemText(nItem, 9, nTruck);
		m_lstRegisterChargeList.SetItemLong(nItem, nRegisterChargeID);
		m_lstRegisterChargeList.SetItemLong2(nItem, nRsChargeID);
		m_lstRegisterChargeList.AllowEdit(TRUE);
			
		pRs.MoveNext();
	}
	pRs.Close();
	m_lstRegisterChargeList.Populate();
}

void CChargeListDlg::RegisterGroupView()
{
	m_lstGroupList.DeleteAllItems();

	CXTPGridRecord *pRecord = m_lstChargeList.GetFirstSelectedRecord();
	long nChargeID = m_lstChargeList.GetItemLong(pRecord);
	if(nChargeID <= 0)
	{
		MessageBox("요금제 선택을 다시하여주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	MAP_CUSTOMER_GROUP::iterator it;
	MAP_CUSTOMER_GROUP::iterator itAll;	
	MAP_CUSTOMER_GROUP SearchGroupMap, TempSearchGroupMap;
	MAP_CUSTOMER_GROUP *pGroupMap;

	pGroupMap = m_cg.GetGroup();
	// 해당요금의 그룹부서를 옮긴다.
	for(itAll = pGroupMap->begin(); itAll != pGroupMap->end(); ++itAll)
	{
		if(itAll->second->nCharge == nChargeID) 		
			TempSearchGroupMap[itAll->first] = (*itAll).second;		
		
	}

	// 그룹부서의 모든 해당 그룹을 옮긴다.
	for(it = TempSearchGroupMap.begin(); it != TempSearchGroupMap.end(); ++it)
	{
		for(itAll = m_cg.GetGroup()->begin(); itAll != m_cg.GetGroup()->end(); ++ itAll )
		{
			if(it->second->nGNoKey == itAll->second->nGNoKey)
				SearchGroupMap[itAll->first] = (*itAll).second;
			
		}
	}	

	int nCount = m_lstGroupList.GetRecords()->GetCount();
	CChargeListRecord* record = nullptr;
	for (it = SearchGroupMap.begin(); it != SearchGroupMap.end(); ++it)
	{
		if (record) {
			if (record->GetGNoKey() == it->second->nGNoKey) {
				record = new CChargeListRecord(it->second->strGroupName, it->second->strDept, it->second->strChargeName, it->first, it->second->nGNoKey);
				m_lstGroupList.AddRecord(record);
			}
			else {
				CXTPGridRecord* child_record =
					new CChargeListRecord(it->second->strGroupName, it->second->strDept, it->second->strChargeName, it->first, it->second->nGNoKey);
				record->GetChilds()->Add(child_record);
			}
		}
		else {
			record = new CChargeListRecord(it->second->strGroupName, it->second->strDept, it->second->strChargeName, it->first, it->second->nGNoKey);
			m_lstGroupList.AddRecord(record);
		}
	}

	m_lstGroupList.Populate();
	m_lstGroupList.ExpandAll();	
}

void CChargeListDlg::OnBnClickedChargeNameModifyBtn()
{
	if(m_lstChargeList.GetSelectedRows()->GetCount() ==0)
		return;

	int nRow = m_lstChargeList.GetFirstSelectedRecord()->GetIndex();

	ChargeGroupModify(nRow);
}


void CChargeListDlg::ChargeGroupModify(int nRow)
{
	if(nRow < 0)
		return;

	long	nChargeID = m_lstChargeList.GetItemLong(nRow);
	CString strChargeName = m_lstChargeList.GetItemText(nRow, 1);
	CString strEtc = m_lstChargeList.GetItemText(nRow, 2);

	CChargeNameNewDlg dlg;
	dlg.m_strChargeName = strChargeName;
	dlg.m_strChargeEtc = strEtc;

	if(dlg.DoModal() == IDOK )
	{
		if(strChargeName.Compare(dlg.m_strChargeName) == 0 && strEtc.Compare(dlg.m_strChargeEtc) == 0 )
			return;

		strChargeName = dlg.m_strChargeName;
		strEtc = dlg.m_strChargeEtc;

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_charge_type_name");
		pCmd.AddParameter(nChargeID);
		pCmd.AddParameter(strChargeName);
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(strEtc);

		if(!pRs.Execute(&pCmd)) return;

		MessageBox("요금제 이름및 비고가 수정 되었습니다.","확인", MB_ICONINFORMATION);

		m_mapChargeType[nChargeID].strChargeName = strChargeName;
		m_mapChargeType[nChargeID].strEtc = strEtc;

		RefreshList();
	}
}

void CChargeListDlg::OnBnClickedChargeNameNewBtn()
{	
	CChargeNameNewDlg dlg;
	if(dlg.DoModal() == IDOK)
	{		
		CString strChargeName = dlg.m_strChargeName;
		CString strEtc = dlg.m_strChargeEtc;

		if(strChargeName.GetLength() == 0)
		{
			MessageBox("요금제 이름을 넣어주세요","확인", MB_ICONINFORMATION);
			return;
		}

		int nReturnValue = 0;
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_chargetype_name_2008_1");
		pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(strChargeName);
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(strEtc);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd)) return;
			pPar->GetValue(nReturnValue);

		if(nReturnValue < 0)
			MessageBox("기존의 등록할 이름과 일치합니다.", "확인", MB_ICONINFORMATION);
		else
		{
			MessageBox("요금제가 신규로 생성되었습니다.","확인", MB_ICONINFORMATION);

			ST_CHARGE_TYPE_NAME_INFO st;
			st.nID = nReturnValue;
			st.nCompany = LF->GetCurBranchInfo()->nCompanyCode;
			st.strChargeName = strChargeName;

			m_mapChargeType[nReturnValue] = st;

			RefreshList();
		}	
	}
}

void CChargeListDlg::OnBnClickedChargeTypenameInputBtn()
{
	if (m_lstAllGroupList.GetSelectedItemCount() <= 0) {
		MessageBox("옮기실 그룹의 아이템을 선택하여주세요");
		return;
	}

	CChargeListRecord* record = (CChargeListRecord*)m_lstAllGroupList.GetFirstSelectedRecord();
	long nGNo = record->GetGNo();

	long nChargeID = m_lstChargeList.GetItemLong(m_lstChargeList.GetFirstSelectedRecord());
	m_cg.GetGroupData(nGNo)->nCharge = nChargeID;
    	
	RegisterGroupView();
	m_lstGroupList.ExpandAll();
}

void CChargeListDlg::OnBnClickedChargeTypenameDelBtn()
{
	if (m_lstGroupList.GetSelectedItemCount() <= 0) {
		MessageBox("요금에 등록된 그룹을 선택하여주세요");
		return;
	}

	for(int i = 0; i < m_lstGroupList.GetSelectedRows()->GetCount(); i++)
	{
		CChargeListRecord* record = (CChargeListRecord*)m_lstGroupList.GetSelectedRows()->GetAt(i)->GetRecord();
		long nGNo = record->GetGNo();
		if (nGNo == 0)
			continue;

		m_cg.GetGroupData(nGNo)->nCharge = 0;
	}
	RegisterGroupView();
	m_lstGroupList.ExpandAll();
}

void CChargeListDlg::OnEnChangeSearchGroupEdit()
{
	CString strSearchGroupWord="";
	m_edtSearchGroup.GetWindowText(strSearchGroupWord);
	if(strSearchGroupWord.GetLength() == 0)
	{
		m_lstAllGroupList.ShowAllRow();
		return;
	}

	CXTPGridRecord *pRecord = NULL;
	MAP_CUSTOMER_GROUP::iterator it;

	CUIntArray IntArray;
	CString strGroupName;

	for(it = m_cg.GetGroup()->begin(); it != m_cg.GetGroup()->end(); ++it)
	{
		strGroupName = it->second->strGroupName;
		if(strGroupName.GetLength() == 0)
			continue;

		strGroupName.MakeUpper();
		strSearchGroupWord.MakeUpper();

		if(strGroupName.Find(strSearchGroupWord,0) >= 0 )
			IntArray.Add(it->first);
	}

    if(IntArray.GetCount() == 0)
		return;

	for(int i = 0;  i < m_lstAllGroupList.GetRecords()->GetCount(); i++)
	{
		BOOL bFind = FALSE;
		CChargeListRecord* record = (CChargeListRecord*)m_lstAllGroupList.GetRecords()->GetAt(i);
		if (record) {
			for (int j = 0; j < IntArray.GetCount(); j++)
			{
				if (record->GetGNo() == IntArray.GetAt(j))
				{
					bFind = TRUE;
					break;
				}
			}
			record->SetVisible(bFind);
		}
	}

	m_lstAllGroupList.Populate();
	m_lstAllGroupList.ExpandAll();
}

void CChargeListDlg::OnBnClickedModifyChargeBtn()
{
	if(m_lstRegisterChargeList.GetRecords()->GetCount() == 0)
	{
		LF->MsgBox("수정하실 데이터가 없습니다.");
		return;
	}

	for(int i = 0; i < m_lstRegisterChargeList.GetRecords()->GetCount(); i++)
	{
		if (CXTPGridRecord* pRecord = m_lstRegisterChargeList.GetRecords()->GetAt(i))
		{
			long nRegisterChargeID = m_lstRegisterChargeList.GetItemLong(pRecord);
			long nChargeID = m_lstRegisterChargeList.GetItemLong2(pRecord);

			if (nRegisterChargeID <= 0 || nChargeID <= 0)
			{
				LF->MsgBox("수정중 데이터가 이상합니다 로지소프트로 문의하세요");
				return;
			}

			long nChargeType = m_cmbType.GetCurSel();

			for (int nCol = 6; nCol < 10; nCol++)
			{
				CXTPGridRecordItemNumber* pItem = (CXTPGridRecordItemNumber*)pRecord->GetItem(nCol);
				int nChargeType = m_cmbType.GetCurSel();
				BOOL bTwoWay = m_chkTwoWay.GetCheck();
				BOOL bMotoCharge = 0, bDamaCharge = 0, bBonggoCharge = 0, bTruckCharge = 0;
				//if(pItem->m_bItemDirtyFlag)
				//{
				bMotoCharge = (nCol == 6) ? TRUE : FALSE;
				bDamaCharge = (nCol == 7) ? TRUE : FALSE;
				bBonggoCharge = (nCol == 8) ? TRUE : FALSE;
				bTruckCharge = (nCol == 9) ? TRUE : FALSE;
				long nAmount = (long)pItem->GetValue();

				CMkRecordset rs(m_pMkDb);
				CMkCommand cmd(m_pMkDb, "update_register_charge_customer");
				cmd.AddParameter(nRegisterChargeID);
				cmd.AddParameter(nChargeID);
				cmd.AddParameter(nAmount);
				cmd.AddParameter(bTwoWay);
				cmd.AddParameter(bMotoCharge);
				cmd.AddParameter(bDamaCharge);
				cmd.AddParameter(bBonggoCharge);
				cmd.AddParameter(bTruckCharge);
				cmd.AddParameter(nChargeType);
				rs.Execute(&cmd);
				//}
			}
		}
	}
	RegisterChargeView();
}

void CChargeListDlg::OnBnClickedExcelBtn()
{
	if(m_lstRegisterChargeList.GetItemCount() == 0)
		return;

	long nChargeID = m_lstChargeList.GetItemLong(m_lstChargeList.GetFirstSelectedRecord());
	if(nChargeID <= 0)
		return;
	CString strChargeName = m_mapChargeType[nChargeID].strChargeName;

	if(!LF->POWER_CHECK(3900, "엑셀변환", TRUE))
		return;
	m_lstRegisterChargeList.ToExcel(strChargeName);
}

void CChargeListDlg::OnBnClickedChargeWindowBtn()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->ViewCharge();
}

void CChargeListDlg::OnBnClickedChargeDeleteBtn()
{	
	if(m_lstChargeList.GetSelectedRows()->GetCount() == 0)
	{
		LF->MsgBox("삭제하실 요금제를 선택하세요");
		return;
	}

	int nDeleteChargeCount = m_lstChargeList.GetSelectedRows()->GetCount();
	CString  strChargeTypeName = "";
	long nChargeTypeID = m_lstChargeList.GetItemLong(m_lstChargeList.GetFirstSelectedRecord());
	strChargeTypeName.Format("%s외 %d개의 해당요금제를 삭제하시겠습니까?\n\r\n\r 요금제가 삭제되면 등록된 요금도 삭제됩니다.\n\r\n\r 삭제하시려면 예(Y)를 눌러주세요",
		m_mapChargeType[nChargeTypeID].strChargeName, nDeleteChargeCount - 1);
	if(MessageBox(strChargeTypeName,"확인", MB_ICONINFORMATION| MB_YESNO) == IDYES)
	{
		for(int i = 0; i < m_lstChargeList.GetSelectedRows()->GetCount(); i++)
		{
			nChargeTypeID = m_lstChargeList.GetItemLong(m_lstChargeList.GetRecords()->GetAt(i));
			strChargeTypeName  =  m_mapChargeType[nChargeTypeID].strChargeName;
			
			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "delete_chargetype_name");
			pCmd.AddParameter(LF->GetCurBranchInfo()->nPayTable);
			pCmd.AddParameter(strChargeTypeName);
			pCmd.AddParameter(nChargeTypeID);
			CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

			if(!pRs.Execute(&pCmd)) return;
			long nReturnValue = 0;
			pPar->GetValue(nReturnValue);

			if(nReturnValue < 0)
				MessageBox("삭제할 해당요금이 서버에 없습니다.", "확인", MB_ICONINFORMATION);
			else
			{
				MessageBox("요금제가 삭제 되었습니다.","확인", MB_ICONINFORMATION);

				MAP_CHARGE_TYPE_NAME::iterator it = m_mapChargeType.find(nChargeTypeID);

				if(it != m_mapChargeType.end())
					m_mapChargeType.erase(it);			
			}
		}
		RefreshList();
	}
}
