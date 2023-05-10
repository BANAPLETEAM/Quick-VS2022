// CidGroupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CidGroupDlg.h"



// CCidGroupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCidGroupDlg, CMyDialog)
CCidGroupDlg::CCidGroupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCidGroupDlg::IDD, pParent)
{
}

CCidGroupDlg::~CCidGroupDlg()
{
}

void CCidGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_LINE_EDIT1, m_edtLine1);
	DDX_Control(pDX, IDC_LINE_EDIT2, m_edtLine2);
}


BEGIN_MESSAGE_MAP(CCidGroupDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ADD_BULK_BTN, OnBnClickedAddBulkBtn)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCidGroupDlg 메시지 처리기입니다.

BOOL CCidGroupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	//m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.ModifyStyle(NULL, LVS_EX_CHECKBOXES | LVS_EDITLABELS | LVS_REPORT);
	m_List.SetGridStyle(TRUE, xtpGridSolid);
	m_List.SetGridColor(RGB(212, 208, 200));
	m_List.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);

	//m_List.InsertColumn(0, "순번", LVCFMT_LEFT, 40);
	//m_List.InsertColumn(1, "회사명", LVCFMT_LEFT, 100);
 //   m_List.InsertColumn(2, "지사명", LVCFMT_LEFT, 100);
	//m_List.InsertColumn(3, "대표전화", LVCFMT_LEFT, 100);
	//m_List.InsertColumn(4, "국선그룹설정 (ex)701,702,703", LVCFMT_LEFT, 380);

	m_List.AddColumn(new CXTPGridColumn(kNumber, "순번" , 40));
	m_List.AddColumn(new CXTPGridColumn(kCompanyName, "회사명" , 100));
	m_List.AddColumn(new CXTPGridColumn(kBranchName, "지사명" , 100));
	m_List.AddColumn(new CXTPGridColumn(kPhoneNumber, "대표전화" , 100));
	m_List.AddColumn(new CXTPGridColumn(kCentralOfficeGroup, "국선그룹설정" , 380));
	//m_List.AddColumn(new CXTPGridColumn(kID, "ID" , 0));


	//m_List.SetDisableCol(0);
	//m_List.SetDisableCol(1);
	//m_List.SetDisableCol(2);
	//m_List.SetDisableCol(3);

	m_List.AllowEdit(TRUE);

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCidGroupDlg::RefreshList()
{
	char buffer[10] = {""};
	int nItemCount = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_share_company2_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	if(!pRs.Execute(&pCmd)) return;

	while(!pRs.IsEOF())
	{
		int nCompany;
		int nShareCode1, nShareCode2, nShareCode3, nShareCode4, nShareCode5;

		pRs.GetFieldValue("nShareCode1", nShareCode1);
		pRs.GetFieldValue("nShareCode2", nShareCode2);
		pRs.GetFieldValue("nShareCode3", nShareCode3);
		pRs.GetFieldValue("nShareCode4", nShareCode4);
		pRs.GetFieldValue("nShareCode5", nShareCode5);
		pRs.GetFieldValue("nID", nCompany);

		if((m_ci.m_nCompanyCode == nCompany) ||
			(m_ci.m_bRcpIntMode1 && m_ci.m_nShareCode1 == nShareCode1) ||
			(m_ci.m_bRcpIntMode2 && m_ci.m_nShareCode2 == nShareCode2) ||
			(m_ci.m_bRcpIntMode3 && m_ci.m_nShareCode3 == nShareCode3) ||
			(m_ci.m_bRcpIntMode4 && m_ci.m_nShareCode4 == nShareCode4) ||
			(m_ci.m_bRcpIntMode5 && m_ci.m_nShareCode5 == nShareCode5))
		{
			long nID;
			CString strName, strBranchName, strPhone, strLineGroup;

			pRs.GetFieldValue("sName", strName);
			pRs.GetFieldValue("sBranchName", strBranchName);
			pRs.GetFieldValue("sTel", strPhone);
			pRs.GetFieldValue("sLineGroup", strLineGroup);
			pRs.GetFieldValue("nID", nID);
			
			CXTPGridRecord* pNewRecord = new CXTPGridRecord();


			CXTPGridRecordItemNumber* pItemNumber = new CXTPGridRecordItemNumber(nItemCount);
			pItemNumber->SetEditable(FALSE);
			pNewRecord->AddItem(pItemNumber);

			CXTPGridRecordItemText* pItemCompanyName = new CXTPGridRecordItemText(strName);
			pItemCompanyName->SetEditable(FALSE);
			pNewRecord->AddItem(pItemCompanyName);

			CXTPGridRecordItemText* pItemBranchName = new CXTPGridRecordItemText(strBranchName);
			pItemBranchName->SetEditable(FALSE);
			pNewRecord->AddItem(pItemBranchName);

			CXTPGridRecordItemText* pItemPhone = new CXTPGridRecordItemText(GetDashPhoneNumber(strPhone));
			pItemPhone->SetEditable(FALSE);
			pNewRecord->AddItem(pItemPhone);

			CXTPGridRecordItemText* pItemCentralOfficeGroup = new CXTPGridRecordItemText(strLineGroup);
			pItemCentralOfficeGroup->SetEditable(TRUE);
			pNewRecord->AddItem(pItemCentralOfficeGroup);


			//invisiable item
			CXTPGridRecordItemNumber* pItemID = new CXTPGridRecordItemNumber(nID);
			pItemID->SetEditable(FALSE);
			pNewRecord->AddItem(pItemID);
			pItemID->SetItemData(nCompany);

			m_List.AddRecord(pNewRecord);

			//데이터 넣습니다.
			//m_List.InsertItem(nItem, ltoa(nItem + 1, buffer, 10));
			//m_List.SetItemText(nItem, 1, strName);
			//m_List.SetItemText(nItem, 2, strBranchName);
			//m_List.SetItemText(nItem, 3, GetDashPhoneNumber(strPhone));
			//m_List.SetItemText(nItem, 4, strLineGroup);
			//m_List.SetItemData(nItem++, nID);



		}
		++nItemCount;
		pRs.MoveNext();
		
	}
	m_List.Populate();
}


void CCidGroupDlg::OnBnClickedAddBulkBtn()
{
	//int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) 
		return;
	if(pRows->GetCount() == 0) 
		return;

	CXTPGridRecord* pSelectRecord = pRows->GetAt(0)->GetRecord();

	if(pSelectRecord)
	{
		CString strLine1, strLine2;

		m_edtLine1.GetWindowText(strLine1);
		m_edtLine2.GetWindowText(strLine2);

		if(atol(strLine1) >= atol(strLine2)) {
			MessageBox("첫째값이 둘째값보다 작아야합니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		//CString strItem = m_List.GetItemText(nItem, 4);
		CString strItem = pSelectRecord->GetItem(kCentralOfficeGroup)->GetCaption();

		if(strItem.GetLength() > 0 && strItem.GetAt(strItem.GetLength() - 1) != ',')
			strItem += ",";

		for(int i = atol(strLine1); i <= atol(strLine2); i++) {
			char buffer[10];
			strItem += ltoa(i, buffer, 10);
			strItem += ",";
		}

		//m_List.SetItemText(nItem, 4, strItem);
		pSelectRecord->GetItem(kCentralOfficeGroup)->SetCaption(strItem);
	}
	m_List.Populate();
}

//확인하는 작업
BOOL CCidGroupDlg::CheckIntegrity()
{
	CString strLineGroup, strTemp, strTemp2;
		
	//for(int i = 0; i < m_List.GetItemCount(); i++)
	for(int i = 0 ; i < m_List.GetRows()->GetCount() ; ++i)
	{
		//strLineGroup = m_List.GetItemText(i, 4);
		strLineGroup = m_List.GetRecords()->GetAt( i )->GetItem(kCentralOfficeGroup)->GetCaption();

		while( strLineGroup.Replace(" ","") > 0 ) {}; //Remove Space

		strLineGroup.Trim();
		strLineGroup.Trim("'");
		
		int curPos = 0;
		strTemp = strLineGroup.Tokenize(",", curPos);
//		strTemp += ",";
		strTemp = "," + strTemp + ",";
		while(strTemp != ",,")
		{
			for(int k = 0; k < m_List.GetRows()->GetCount(); k++)
			{
				if(i == k) continue;

				strTemp2 = ","+ m_List.GetRecords()->GetAt( k )->GetItem(kCentralOfficeGroup)->GetCaption()+",";
				while( strTemp2.Replace(" ","") > 0 ) {}; //Remove Space

				if(strTemp2.Find(strTemp) >= 0) {
					CString strMsg;
					strMsg.Format("%d번 지사의 %s 국선이, %d번 지사에도 존재함", i + 1, strTemp, k + 1);
					MessageBox(strMsg, "확인", MB_ICONINFORMATION);
					return FALSE;
				}
			}

			strTemp = strLineGroup.Tokenize(",", curPos);
//			strTemp += ",";
			strTemp = "," + strTemp + ",";
		}
	}
	
	return TRUE;
}



void CCidGroupDlg::OnBnClickedOk()
{

	if(CheckIntegrity())
	{
		CWaitCursor wait;
		for(int i = 0; i < m_List.GetRows()->GetCount(); i++)
		{
			//int nCompany = m_List.GetItemData(i);
			int nCompany = m_List.GetRecords()->GetAt( i )->GetItem(kID)->GetItemData();
			//CString strLineGroup = m_List.GetItemText(i, 4);
			CString strLineGroup = m_List.GetRecords()->GetAt( i )->GetItem(kCentralOfficeGroup)->GetCaption();

			CMkCommand pCmd(m_pMkDb, "update_line_group");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
			pCmd.AddParameter(typeString, typeInput, strLineGroup.GetLength(), strLineGroup);
			if(!pCmd.Execute()) {
				MessageBox("업데이트 실패, 재시도 바랍니다.", "확인", MB_ICONINFORMATION);
				return;
			}
			
			for(int k = 0; k < m_ba.GetCount(); k++) {
				CBranchInfo *pBi = m_ba.GetAt(k);
				if(pBi->nCompanyCode == nCompany) {
					pBi->strLineGroup = strLineGroup;
					pBi->strLineGroup += ",";
				}
			}
		}

		MessageBox("저장되었습니다.", "확인", MB_ICONINFORMATION);
		OnOK();
	}
	m_List.Populate();
}
