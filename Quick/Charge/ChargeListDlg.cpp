// ChargeListDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeListDlg.h"
#include "ChargenameNewDlg.h"
#include "MainFrm.h"
// CChargeListDlg ��ȭ �����Դϴ�.

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


// CChargeListDlg �޽��� ó�����Դϴ�.


BOOL CChargeListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_edtSearchChargeWord.SetFontSize(12);
	m_edtSearchChargeWord.SetFocus();

	

	
	RefreshList();
	return TRUE;  
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CChargeListDlg::RefreshList()
{

	//m_lstChargeList.DeleteAllItems();

	//m_lstChargeList.DeleteAllItem();
	//m_lstChargeList.SetQuery("select_charge_list");
	//m_lstChargeList.AddPa("kkk");
	//m_lstChargeList.AddPa("kkk");
	//m_lstChargeList.AddPa("kkk");
	//m_lstChargeList.AddPa("kkk");
	//m_lstChargeList.Excute(TRUE);

	m_lstChargeList.DeleteAllItem();

	
	MAP_CHARGE_TYPE_NAME::iterator it;		

	long nItem =0, nCompany = 0;
	CString strChargeName;
	

	for(it = m_mapChargeType.begin(); it != m_mapChargeType.end(); ++it)
	{/*
		int nGNo = it->first;
		int nCompany = it->second->nCompany;*/

		strChargeName = it->second.strChargeName;
		nCompany = it->second.nCompany;

		if(strChargeName.GetLength() == 0)
			continue;

		m_lstChargeList.MyAddItem(0, m_ci.GetBranchName(nCompany),	"ȸ���",100, FALSE, DT_LEFT );
		m_lstChargeList.MyAddItem(1, strChargeName, "������̸�",120, FALSE, DT_LEFT );
		m_lstChargeList.MyAddItem(2, it->second.strEtc, "���", 90, FALSE ,DT_LEFT);
		m_lstChargeList.InsertItemDataLong(it->first);
		m_lstChargeList.EndItem();	
	}
	m_lstChargeList.Populate();
	
	AllGroupRefresh();
}

void CChargeListDlg::AllGroupRefresh()
{
	m_lstAllGroupList.DeleteAllItem();

	MAP_CUSTOMER_GROUP::iterator it;

	for(it = m_cg.GetGroup()->begin(); it != m_cg.GetGroup()->end(); ++it)
	{
		if(it->second->strGroupName.GetLength() == 0)
			continue;

		m_lstAllGroupList.TreeChildDepthAddItem(0,it->second->strKeyRef,it->second->nGNoKey,
						it->second->strGroupName,"�׷��̸�",130, FALSE, DT_LEFT );
		m_lstAllGroupList.MyAddItem(1,it->second->strDept,"�μ�",90, FALSE, DT_LEFT );
		m_lstAllGroupList.MyAddItem(2,it->second->strChargeName, "������̸�", 90, FALSE ,DT_LEFT);
		m_lstAllGroupList.InsertItemDataLong(it->first);
		m_lstAllGroupList.EndItem();	

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	
	CMyXTPGridRecord *pRecord = NULL;
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
		pRecord = (CMyXTPGridRecord*)m_lstChargeList.GetRecords()->GetAt(i);	


		for(int j=0; j < IntArray.GetCount(); j++)
		{
			//int m = pRecord->GetItemDataLong();

			if(pRecord->GetItemDataLong() == IntArray.GetAt(j))
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
	if(m_lstChargeList.GetSelectedCount() == 0 )
		return;

	CMyXTPGridRecord *pRecord = NULL;
	pRecord = m_lstChargeList.GetSelectedRecord(0);

	if(pRecord  == NULL)
		return;	
	long nChargeID = pRecord->GetItemDataLong();	
	
	if(nChargeID <= 0)
	{
		MessageBox("��ϵ� ����� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	m_lstRegisterChargeList.DeleteAllItem();




	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_charge_id_list");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nChargeID);
	
	if(!pRs.Execute(&pCmd)) return;

	CString sChargeName, sStartGu, sStartDong, sTypeView, sDestGu, sDestDong;
	long nRsChargeID, nStartID,nTypeCode, nDestID,nMoto, nDama, nBonggo,nTruck,nRegisterChargeID;
	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("�������ȣ", nRsChargeID);
		pRs.GetFieldValue("������̸�", sChargeName);			
		pRs.GetFieldValue("��������̵�", nStartID);			
		pRs.GetFieldValue("��߱�", sStartGu);
		pRs.GetFieldValue("��ߵ�", sStartDong);
		pRs.GetFieldValue("Ÿ���ڵ�", nTypeCode);
		pRs.GetFieldValue("Ÿ��", sTypeView);		
		pRs.GetFieldValue("�������ڵ�", nDestID);
		pRs.GetFieldValue("������", sDestGu);
		pRs.GetFieldValue("������", sDestDong);
		pRs.GetFieldValue("�������", nMoto);
		pRs.GetFieldValue("�ٸ���", nDama);
		pRs.GetFieldValue("����", nBonggo);
		pRs.GetFieldValue("Ʈ��", nTruck);
		pRs.GetFieldValue("��ݼ���", nRegisterChargeID);
		/*
		//m_lstRegisterChargeList.AddHeader(TRUE, "�������ȣ", "�������ȣ" );
		m_lstRegisterChargeList.AddHeader(TRUE, "������̸�", "������̸�", 100 );	
		m_lstRegisterChargeList.AddHeader(TRUE, "��߱�", "��߱�", 80 );
		m_lstRegisterChargeList.AddHeader(TRUE, "��ߵ�", "��ߵ�" ,60);
		m_lstRegisterChargeList.AddHeader(TRUE, "Ÿ���ڵ�", "Ÿ���ڵ�",50 );
		//m_lstRegisterChargeList.AddHeader(TRUE, "Ÿ��", "Ÿ��", 80 );
		//m_lstRegisterChargeList.AddHeader(TRUE, "nDestID", "nDestID", 80 );
		m_lstRegisterChargeList.AddHeader(TRUE, "������", "������",70 );
		m_lstRegisterChargeList.AddHeader(TRUE, "������", "������",50 );
		m_lstRegisterChargeList.AddHeader(TRUE, "�������", "����",50,DT_RIGHT );
		m_lstRegisterChargeList.AddHeader(TRUE, "�ٸ������", "�ٸ���",50,DT_RIGHT );
		m_lstRegisterChargeList.AddHeader(TRUE, "������", "����",50,DT_RIGHT );
		m_lstRegisterChargeList.AddHeader(TRUE, "Ʈ�����", "Ʈ��",50,DT_RIGHT );
		//m_lstRegisterChargeList.AddHeader(TRUE, "��Ÿ", "��Ÿ",50 );
		//m_lstRegisterChargeList.AddHeader(TRUE, "��ݼ���", "��ݼ���",50 );
		m_lstRegisterChargeList.m_bHeader = TRUE;
		//m_lstRegisterChargeList.Populate();
		*/
		m_lstRegisterChargeList.MyAddItem(0,sChargeName,"������̸�",100, FALSE, DT_LEFT);
		m_lstRegisterChargeList.MyAddItem(1,sStartGu,"��߱�",90, FALSE, DT_LEFT);
		m_lstRegisterChargeList.MyAddItem(2,sStartDong,"��ߵ�",65, FALSE, DT_LEFT);
		m_lstRegisterChargeList.MyAddItem(3,sTypeView,"Ÿ��",60, FALSE, DT_LEFT);
		m_lstRegisterChargeList.MyAddItem(4,sDestGu,"������",90, FALSE, DT_LEFT);
		m_lstRegisterChargeList.MyAddItem(5,sDestDong,"������",65, FALSE, DT_LEFT);
		m_lstRegisterChargeList.MyAddItem(6,nMoto,"�������",70, TRUE, DT_RIGHT);
		m_lstRegisterChargeList.MyAddItem(7,nDama,"�ٸ���",70, TRUE, DT_RIGHT);
		m_lstRegisterChargeList.MyAddItem(8,nBonggo,"����",70, TRUE, DT_RIGHT);
		m_lstRegisterChargeList.MyAddItem(9,nTruck,"Ʈ��",70, TRUE, DT_RIGHT);		
		m_lstRegisterChargeList.InsertItemDataLong(nRegisterChargeID);
		m_lstRegisterChargeList.InsertItemDataLong2(nRsChargeID);
		m_lstRegisterChargeList.AllowEdit(TRUE);
		m_lstRegisterChargeList.EndItem();
			
		/*m_lstRegisterChargeList.MyAddItem(sChargeName);
		m_lstRegisterChargeList.MyAddItem(sStartGu);	
		m_lstRegisterChargeList.MyAddItem(sStartDong);	
		m_lstRegisterChargeList.MyAddItem(sTypeView);	
		m_lstRegisterChargeList.MyAddItem(sDestGu);	
		m_lstRegisterChargeList.MyAddItem(sDestDong);	
		m_lstRegisterChargeList.MyAddItem(nMoto);	
		m_lstRegisterChargeList.MyAddItem(nDama);	
		m_lstRegisterChargeList.MyAddItem(nBonggo);	
		m_lstRegisterChargeList.MyAddItem(nTruck);	
		m_lstRegisterChargeList.SetItemDataLong(nRegisterChargeID);		
		m_lstRegisterChargeList.EndItem();*/
		pRs.MoveNext();
	}
	pRs.Close();
	m_lstRegisterChargeList.Populate();

	/*m_lstRegisterChargeList.MyAddItem(,	"ȸ���",100, FALSE, DT_LEFT );
	m_lstRegisterChargeList.MyAddItem(sChargeName,								"������̸�",120, FALSE, DT_LEFT );
	m_lstRegisterChargeList.MyAddItem(it->second.sEtc, "���", 90, FALSE ,DT_LEFT);
	m_lstRegisterChargeList.SetItemDataLong(it->first);
	m_lstRegisterChargeList.EndItem();	

	

	m_lstRegisterChargeList.SetQuery("select_charge_id_list");
	m_lstRegisterChargeList.AddParameter(2800);
	m_lstRegisterChargeList.AddParameter(854);
	m_lstRegisterChargeList.Excute(TRUE);*/
		
	


}

void CChargeListDlg::RegisterGroupView()
{
	m_lstGroupList.DeleteAllItem();

	CMyXTPGridRecord *pRecord = m_lstChargeList.GetSelectedRecord(0);
	long nChargeID = pRecord->GetItemDataLong();
	if(nChargeID <= 0)
	{
		MessageBox("����� ������ �ٽ��Ͽ��ּ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	MAP_CUSTOMER_GROUP::iterator it;
	MAP_CUSTOMER_GROUP::iterator itAll;	
	MAP_CUSTOMER_GROUP SearchGroupMap, TempSearchGroupMap;
	MAP_CUSTOMER_GROUP *pGroupMap;

	pGroupMap = m_cg.GetGroup();
	// �ش����� �׷�μ��� �ű��.
	for(itAll = pGroupMap->begin(); itAll != pGroupMap->end(); ++itAll)
	{
		if(itAll->second->nCharge == nChargeID) 		
			TempSearchGroupMap[itAll->first] = (*itAll).second;		
		
	}

	// �׷�μ��� ��� �ش� �׷��� �ű��.
	for(it = TempSearchGroupMap.begin(); it != TempSearchGroupMap.end(); ++it)
	{
		for(itAll = m_cg.GetGroup()->begin(); itAll != m_cg.GetGroup()->end(); ++ itAll )
		{
			if(it->second->nGNoKey == itAll->second->nGNoKey)
				SearchGroupMap[itAll->first] = (*itAll).second;
			
		}
	}	

	int nCount = m_lstGroupList.GetRecords()->GetCount();
	for(it = SearchGroupMap.begin(); it != SearchGroupMap.end(); ++it)
	{
		m_lstGroupList.TreeChildDepthAddItem(0, it->second->strKeyRef, it->second->nGNoKey, it->second->strGroupName, "�׷��̸�",130,FALSE,DT_LEFT);
		m_lstGroupList.MyAddItem(1, it->second->strDept, "�μ�",90,FALSE,DT_LEFT);
		m_lstGroupList.MyAddItem(2,	it->second->nCharge > 0 ? m_mapChargeType[it->second->nCharge].strChargeName : "", "�������",100,FALSE,DT_LEFT);
		m_lstGroupList.InsertItemDataLong(it->first);
		m_lstGroupList.EndItem();
	}

	m_lstGroupList.Populate();
	m_lstGroupList.ExpandAll();	
}

void CChargeListDlg::OnBnClickedChargeNameModifyBtn()
{
	if(m_lstChargeList.GetSelectedCount() ==0)
		return;

	int nRow = m_lstChargeList.GetSelectedRecord(0)->GetIndex();

	ChargeGroupModify(nRow);
}


void CChargeListDlg::ChargeGroupModify(int nRow)
{
	if(nRow < 0)
		return;

	long	nChargeID = m_lstChargeList.GetItemDataLong(nRow);
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

		MessageBox("����� �̸��� ��� ���� �Ǿ����ϴ�.","Ȯ��", MB_ICONINFORMATION);

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
			MessageBox("����� �̸��� �־��ּ���","Ȯ��", MB_ICONINFORMATION);
			return;
		}

		int nReturnValue = 0;
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_chargetype_name_2008_1");
		pCmd.AddParameter(GetCurBranchInfo()->nPayTable);
		pCmd.AddParameter(strChargeName);
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(strEtc);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd)) return;
			pPar->GetValue(nReturnValue);

		if(nReturnValue < 0)
			MessageBox("������ ����� �̸��� ��ġ�մϴ�.", "Ȯ��", MB_ICONINFORMATION);
		else
		{
			MessageBox("������� �űԷ� �����Ǿ����ϴ�.","Ȯ��", MB_ICONINFORMATION);

			ST_CHARGE_TYPE_NAME_INFO st;
			st.nID = nReturnValue;
			st.nCompany = GetCurBranchInfo()->nCompanyCode;
			st.strChargeName = strChargeName;

			m_mapChargeType[nReturnValue] = st;

			RefreshList();
		}	
	}
}

void CChargeListDlg::OnBnClickedChargeTypenameInputBtn()
{
	if(!m_lstAllGroupList.IsRowSelectCheck("�ű�� �׷��� �������� �����Ͽ��ּ���"))
		return;

	long nGNo = m_lstAllGroupList.GetSelectedRecord(0)->GetItemDataLong();

	long nChargeID = 	m_lstChargeList.GetSelectedRecord()->GetItemDataLong();
	m_cg.GetGroupData(nGNo)->nCharge = nChargeID;
    	
	RegisterGroupView();
	m_lstGroupList.ExpandAll();
}

void CChargeListDlg::OnBnClickedChargeTypenameDelBtn()
{
	if(!m_lstGroupList.IsRowSelectCheck("��ݿ� ��ϵ� �׷��� �������ּ���"))
		return;

	for(int i = 0; i < m_lstGroupList.GetSelectedCount(); i++)
	{

		CMyXTPGridRecord *pRecord = m_lstGroupList.GetSelectedRecord(i);
		long nGNo = pRecord->GetItemDataLong();
		if(nGNo == 0)
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

	CMyXTPGridRecord *pRecord = NULL;
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
		pRecord = (CMyXTPGridRecord*)m_lstAllGroupList.GetRecords()->GetAt(i);
		for(int j=0; j < IntArray.GetCount();j++)
		{
			if(pRecord->GetItemDataLong() == IntArray.GetAt(j))			
			{
				bFind = TRUE;
				break;
			}			
		}
		pRecord->SetVisible(bFind);
	}

	m_lstAllGroupList.Populate();
	m_lstAllGroupList.ExpandAll();
}

void CChargeListDlg::OnBnClickedModifyChargeBtn()
{
	if(m_lstRegisterChargeList.GetRecords()->GetCount() == 0)
	{
		MsgBox("�����Ͻ� �����Ͱ� �����ϴ�.");
		return;
	}

	for(int i = 0; i < m_lstRegisterChargeList.GetRecords()->GetCount(); i++)
	{
		CMyXTPGridRecord *pRecord = m_lstRegisterChargeList.GetRecordsGetAt(i);
		if(pRecord->m_bDirtyFlag)
		{
			long nRegisterChargeID = pRecord->GetItemDataLong();
			long nChargeID = pRecord->GetItemDataLong2();

			if(nRegisterChargeID <= 0 || nChargeID <= 0)
			{
				MsgBox("������ �����Ͱ� �̻��մϴ� ��������Ʈ�� �����ϼ���" );
				return;
			}

			long nChargeType = m_cmbType.GetCurSel();
			
			for(int nCol = 6; nCol < 10; nCol++)
			{
				CLMyXTPGridRecordItemNumber *pItem = (CLMyXTPGridRecordItemNumber *)pRecord->GetItem(nCol);
				int nChargeType = m_cmbType.GetCurSel();
				BOOL bTwoWay = m_chkTwoWay.GetCheck();
				BOOL bMotoCharge = 0, bDamaCharge = 0, bBonggoCharge = 0, bTruckCharge = 0;
				if(pItem->m_bItemDirtyFlag)
				{
					bMotoCharge = (nCol == 6 ) ? TRUE : FALSE;
					bDamaCharge = (nCol == 7 ) ? TRUE : FALSE;
					bBonggoCharge= (nCol == 8 ) ? TRUE : FALSE;
					bTruckCharge = (nCol == 9 ) ? TRUE : FALSE;
					long nAmount = (long)pItem->GetValue();						
					
					m_lstRegisterChargeList.CreateComandSetQuery("update_register_charge_customer");			
					m_lstRegisterChargeList.AddParameter(nRegisterChargeID);
					m_lstRegisterChargeList.AddParameter(nChargeID);
					m_lstRegisterChargeList.AddParameter(nAmount);
					m_lstRegisterChargeList.AddParameter(bTwoWay,TRUE);
					m_lstRegisterChargeList.AddParameter(bMotoCharge,TRUE);
					m_lstRegisterChargeList.AddParameter(bDamaCharge,TRUE);
					m_lstRegisterChargeList.AddParameter(bBonggoCharge,TRUE);
					m_lstRegisterChargeList.AddParameter(bTruckCharge,TRUE);
					m_lstRegisterChargeList.AddParameter(nChargeType);					
					m_lstRegisterChargeList.ExcuteCmd(FALSE);
				}
			}
		}
	}
	RegisterChargeView();
}

void CChargeListDlg::OnBnClickedExcelBtn()
{
	if(m_lstRegisterChargeList.GetItemCount() == 0)
		return;

	CMyXTPGridRecord *pRecord = m_lstChargeList.GetSelectedRecord(0);
	long nChargeID = pRecord->GetItemDataLong();
	if(nChargeID <= 0)
		return;
	CString strChargeName = m_mapChargeType[nChargeID].strChargeName;

	if(!POWER_CHECK(3900, "������ȯ", TRUE))
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
	if(m_lstChargeList.GetSelectedCount() == 0)
	{
		MsgBox("�����Ͻ� ������� �����ϼ���");
		return;
	}

	int nDeleteChargeCount = m_lstChargeList.GetSelectedCount();
	CString  strChargeTypeName = "";
	long nChargeTypeID = m_lstChargeList.GetSelectedRecord()->GetItemDataLong();
	strChargeTypeName.Format("%s�� %d���� �ش������� �����Ͻðڽ��ϱ�?\n\r\n\r ������� �����Ǹ� ��ϵ� ��ݵ� �����˴ϴ�.\n\r\n\r �����Ͻ÷��� ��(Y)�� �����ּ���",
		m_mapChargeType[nChargeTypeID].strChargeName, nDeleteChargeCount - 1);
	if(MessageBox(strChargeTypeName,"Ȯ��", MB_ICONINFORMATION| MB_YESNO) == IDYES)
	{
		for(int i = 0; i < m_lstChargeList.GetSelectedCount(); i++)
		{
			nChargeTypeID = m_lstChargeList.GetSelectedRecord(i)->GetItemDataLong();
			strChargeTypeName  =  m_mapChargeType[nChargeTypeID].strChargeName;
			
			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "delete_chargetype_name");
			pCmd.AddParameter(GetCurBranchInfo()->nPayTable);
			pCmd.AddParameter(strChargeTypeName);
			pCmd.AddParameter(nChargeTypeID);
			CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

			if(!pRs.Execute(&pCmd)) return;
			long nReturnValue = 0;
			pPar->GetValue(nReturnValue);

			if(nReturnValue < 0)
				MessageBox("������ �ش����� ������ �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
			else
			{
				MessageBox("������� ���� �Ǿ����ϴ�.","Ȯ��", MB_ICONINFORMATION);

				MAP_CHARGE_TYPE_NAME::iterator it = m_mapChargeType.find(nChargeTypeID);

				if(it != m_mapChargeType.end())
					m_mapChargeType.erase(it);			
			}
		}
		RefreshList();
	}
}
