// MoveGroupDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "MoveGroupDlg.h"
#include "CommonDateDlg.h"
#include "CheckGroupReportDlg.h"
#include "CustomerPage11.h"
// CMoveGroupDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMoveGroupDlg, CMyDialog)
CMoveGroupDlg::CMoveGroupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMoveGroupDlg::IDD, pParent)
{
	m_strSearch = "";
}

CMoveGroupDlg::~CMoveGroupDlg()
{
}

void CMoveGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SRC_LIST, m_lstSrc);
	DDX_Control(pDX, IDC_CUSTOMER_LIST, m_lstCustomer);
	DDX_Control(pDX, IDC_DST_LIST, m_lstDst);
	DDX_Control(pDX, IDC_SEARCH_GROUP_EDIT, m_edtSearchGroup);
	DDX_Control(pDX, IDC_SEARCH_GROUP_EDIT2, m_edtSearchGroup2);
}


BEGIN_MESSAGE_MAP(CMoveGroupDlg, CMyDialog)
	ON_BN_CLICKED(IDC_MOVE_BTN, OnBnClickedMoveBtn)
	ON_NOTIFY(NM_CLICK, IDC_SRC_LIST, OnReportItemClick)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_SRC_LIST, OnReportItemChange)
	ON_EN_CHANGE(IDC_SEARCH_GROUP_EDIT, OnEnChangeSearchGroupEdit)
	ON_EN_CHANGE(IDC_SEARCH_GROUP_EDIT2, OnEnChangeSearchGroupEdit2)
END_MESSAGE_MAP()


// CMoveGroupDlg �޽��� ó�����Դϴ�.

void CMoveGroupDlg::OnBnClickedMoveBtn()
{
	CXTPGridSelectedRows * pSrcSelRows = m_lstSrc.GetSelectedRows();
	CXTPGridSelectedRows * pDstSelRows = m_lstDst.GetSelectedRows();

	if(pSrcSelRows == NULL || pDstSelRows == NULL ||
		pSrcSelRows->GetCount() == 0 || pDstSelRows->GetCount() == 0)
	{
		MessageBox("�̵� �� �׷��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CXTPGridSelectedRows * pSrcSelCustomerRows = m_lstCustomer.GetSelectedRows();

	if(pSrcSelCustomerRows == NULL || pSrcSelCustomerRows->GetCount() == 0)
	{
		MessageBox("�̵� �� �׷� �������� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(pSrcSelCustomerRows->GetCount() > 60)
	{
		MessageBox("�ִ� 60����� �۾� �����մϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	long nSrcGNo = ((CCustomerGroupRecord*)pSrcSelRows->GetAt(0)->GetRecord())->m_nGNo;
	long nDstGNo = ((CCustomerGroupRecord*)pDstSelRows->GetAt(0)->GetRecord())->m_nGNo;

	CString strCNo = "";
	CString strCNo1 = "";
	CString strCNo2 = "";
	CString strGNo = "";
	long nPreGNo = 0;

	for(int i=0; i<pSrcSelCustomerRows->GetCount(); i++)
	{
		CString strCNoTemp = "";
		CString strGNoTemp = "";
		CXTPGridRow *pRow = pSrcSelCustomerRows->GetAt(i);

		long nCNo = (long)m_lstCustomer.GetItemLong(pRow->GetIndex());
		long nGNo = (long)m_lstCustomer.GetItemData(pRow->GetIndex());

		if(nDstGNo == nGNo) // �̵� �Ϸ��� ���� �ɹ��� ����
		{
			CXTPGridColumn *pColumn = NULL;

			CXTPGridRecord *pReocrd = pRow->GetRecord();
			CString strGroupName = ((CXTPGridRecordItemText*)pReocrd->GetItem(0))->GetCaption(pColumn);
			CString strDept = ((CXTPGridRecordItemText*)pReocrd->GetItem(1))->GetCaption(pColumn);
			CString strNo = ((CXTPGridRecordItemText*)pReocrd->GetItem(2))->GetCaption(pColumn);
			CString strCompany = ((CXTPGridRecordItemText*)pReocrd->GetItem(3))->GetCaption(pColumn);

			CString strMsg = "";
			strMsg.Format("%s/%s/%s/%s �� �׷� �ɹ���\r\n�̵��Ϸ��� �׷쿡 �����ֽ��ϴ�", strGroupName, strDept, strNo, strCompany);

			pRow->SetSelected(FALSE);

			MessageBox(strMsg, "Ȯ��", MB_ICONINFORMATION);
			return;
		}

		strCNoTemp.Format("%d", nCNo);
		strGNoTemp.Format("%d", nGNo);
		
		strCNo += strCNoTemp + ";";

		if(nGNo != nPreGNo)
			strGNo += strGNoTemp + ";";

		nPreGNo = nGNo;
	}

	COleDateTime dtDate; 

	CCommonDateDlg dlg;
	if(dlg.DoModal()  != IDOK) //��¥����
		return;

	dtDate = dlg.m_dtDate;

	CString strNeedReReport;

	if(LF->CheckGroupReport(strGNo, nDstGNo, dtDate, LF->GetCommaCount(strCNo), strNeedReReport) == FALSE) // �������� �ʿ��� ����Ʈ�� ����
		return;

	if(strCNo.GetLength() > 300)
	{
		strCNo1 = strCNo.Left(300);
		strCNo2 = strCNo.Mid(300, strCNo.GetLength() - 300);
	}
	else
		strCNo1 = strCNo;

	CMkCommand pCmd(m_pMkDb, "change_group");
	pCmd.AddParameter(nSrcGNo);
	pCmd.AddParameter(nDstGNo);
	pCmd.AddParameter(strCNo1);
	pCmd.AddParameter(strCNo2);
	pCmd.AddParameter(dtDate);

	if(pCmd.Execute())
	{
		if(!strNeedReReport.IsEmpty())
		{
			if(LF->ReReport(strNeedReReport) == FALSE)
			{
				MessageBox("�̵��� ���� �Ͽ����ϴ�\r\n�ٽ� �õ��� �ּ���", "Ȯ��", MB_ICONINFORMATION);
			}	
		}

		MessageBox("�̵� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
	}
}

BOOL CMoveGroupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	InitReport(&m_lstSrc);
	InitReport(&m_lstDst);

	RefreshList(&m_lstSrc);
	RefreshList(&m_lstDst);

	CXTPGridColumn* pCol10 = m_lstCustomer.AddColumn(new CXTPGridColumn(0, "�׷��̸�", 120));
	CXTPGridColumn *pCol11 = m_lstCustomer.AddColumn(new CXTPGridColumn(1, "�μ���", 90, TRUE));
	CXTPGridColumn *pCol12 = m_lstCustomer.AddColumn(new CXTPGridColumn(2, "��No", 50, TRUE));
	CXTPGridColumn *pCol13 = m_lstCustomer.AddColumn(new CXTPGridColumn(3, "��ȣ��", 90, TRUE));
	CXTPGridColumn *pCol14 = m_lstCustomer.AddColumn(new CXTPGridColumn(4, "�����", 60, TRUE));
	CXTPGridColumn *pCol15 = m_lstCustomer.AddColumn(new CXTPGridColumn(5, "��ȭ", 70, TRUE));
	CXTPGridColumn *pCol16 = m_lstCustomer.AddColumn(new CXTPGridColumn(6, "�����", 70, TRUE));
	CXTPGridColumn *pCol17 = m_lstCustomer.AddColumn(new CXTPGridColumn(7, "�޸�", 120, TRUE));



	m_lstCustomer.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	m_lstCustomer.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstCustomer.AllowEdit(FALSE);
	m_lstCustomer.SetGridColor(RGB(222, 222, 222));
	m_lstCustomer.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";

	pCol10->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol10->SetTreeColumn(1);	
	m_lstCustomer.SetTreeIndent(10);

	m_lstCustomer.Populate();

	if(m_strSearch != "")
	{
		m_edtSearchGroup.SetWindowText(m_strSearch);
		m_edtSearchGroup2.SetWindowText(m_strSearch);
		OnEnChangeSearchGroupEdit();
		OnEnChangeSearchGroupEdit2();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMoveGroupDlg::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridRow *pRow = m_lstSrc.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CCustomerGroupRecord *pRecord = (CCustomerGroupRecord*)pRow->GetRecord();
	m_nGNo = pRecord->m_nGNo;
}

void CMoveGroupDlg::InitReport(CXTPGridControl *pRecord)
{
	CXTPGridColumn* pCol0 = pRecord->AddColumn(new CXTPGridColumn(0, "�׷��̸�", 120));
	CXTPGridColumn *pCol1 = pRecord->AddColumn(new CXTPGridColumn(1, "�μ���", 90, TRUE));
	CXTPGridColumn *pCol9 = pRecord->AddColumn(new CXTPGridColumn(2, "�����", 70, TRUE));
	CXTPGridColumn *pCol2 = pRecord->AddColumn(new CXTPGridColumn(3, "�ο�", 35, TRUE));
	CXTPGridColumn *pCol3 = pRecord->AddColumn(new CXTPGridColumn(4, "���ο��", 90, TRUE));	
	CXTPGridColumn *pCol4 = pRecord->AddColumn(new CXTPGridColumn(5, "���", 50, TRUE));	
	CXTPGridColumn *pCol5 = pRecord->AddColumn(new CXTPGridColumn(6, "���", 50, TRUE));
	CXTPGridColumn *pCol6 = pRecord->AddColumn(new CXTPGridColumn(7, "���������", 80, TRUE));
	CXTPGridColumn *pCol7 = pRecord->AddColumn(new CXTPGridColumn(8, "���", 90, TRUE));
	CXTPGridColumn *pCol8 = pRecord->AddColumn(new CXTPGridColumn(9, "��ǥ��ȭ", 90, TRUE));


	pCol4->SetAlignment(DT_RIGHT);
	pCol5->SetAlignment(DT_RIGHT);
	pCol6->SetAlignment(DT_RIGHT);

	pRecord->GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
	pRecord->GetReportHeader()->SetAutoColumnSizing(FALSE);
	pRecord->AllowEdit(FALSE);
	pRecord->SetGridColor(RGB(222, 222, 222));
	pRecord->GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";

	pCol0->GetEditOptions()->m_bAllowEdit = FALSE;
	pCol0->SetTreeColumn(1);	
	pRecord->SetTreeIndent(10);

	pRecord->Populate();
}

void CMoveGroupDlg::RefreshList(CXTPGridControl *pReport)
{
	long nSel = 0;

	if(pReport->GetSelectedRows()->GetCount() != 0)
		nSel = pReport->GetSelectedRows()->GetAt(0)->GetIndex();

	pReport->GetRecords()->RemoveAll();

	CXTPGridRecord *pReocrdTop = NULL;
	CXTPGridRecord *pReocrdLevel1 = NULL;
	CXTPGridRecord *pReocrdLevel2 = NULL;
	CXTPGridRecord *pReocrdLevel3 = NULL;
	CXTPGridRecord *pReocrdLevel4 = NULL;
	CXTPGridRecord *pReocrdLevel5 = NULL;

	VEC_CUSTOMER_GROUP::iterator it;
	VEC_CUSTOMER_GROUP *pGroup = m_cg.GetRefreshGroup();

	long nPreLevel = 0;

	for(it = pGroup->begin(); it != pGroup->end(); it++)
	{
		ST_CUSTOMER_GROUP_INFOMATION *st = (*it);

		switch(st->nLevel)
		{
		case 0:
			pReocrdTop = pReport->AddRecord(new CCustomerGroupRecord(st));
			((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdTop->SetExpanded(TRUE);
			break;
		case 1:
			pReocrdLevel1 = pReocrdTop->GetChilds()->Add(new CCustomerGroupRecord(st));
			((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel1->SetExpanded(TRUE);
			break;
		case 2:
			pReocrdLevel2 = pReocrdLevel1->GetChilds()->Add(new CCustomerGroupRecord(st));
			((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel2->SetExpanded(TRUE);
			break;
		case 3:
			pReocrdLevel3 = pReocrdLevel2->GetChilds()->Add(new CCustomerGroupRecord(st));
			((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel3->SetExpanded(TRUE);
			break;
		case 4:
			pReocrdLevel4 = pReocrdLevel3->GetChilds()->Add(new CCustomerGroupRecord(st));
			((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel4->SetExpanded(TRUE);
			break;
		case 5:
			pReocrdLevel5 =pReocrdLevel4->GetChilds()->Add(new CCustomerGroupRecord(st));
			((CCustomerGroupRecord*)pReocrdTop)->AddSearchData(st);
			pReocrdLevel5->SetExpanded(TRUE);
			break;
		}
	}

	pReport->Populate();

	CXTPGridRows *pRows = pReport->GetRows();
	CXTPGridRow *pRow = pRows->GetAt(min(nSel, pReport->GetRows()->GetCount() -1));

	pReport->GetSelectedRows()->Select(pRow);
}

void CMoveGroupDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_lstSrc.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	RefreshCustomerList();
}

void CMoveGroupDlg::RefreshCustomerList()
{
	m_lstCustomer.DeleteAllItems();

	if(m_nGNo == 0 )
		return;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_member_2008");

	pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(m_nGNo);

	if(!pRs.Execute(&pCmd))
		return;

	BOOL bGroupOwner = FALSE;
	CString sCompany, sName, sTel1, sDate, sMemo;
	long nID,nCNo, nGNo;
	COleDateTime dtRegister;
	char buffer [20];

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("sCompany", sCompany);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sTel1", sTel1);
		pRs.GetFieldValue("sMemo", sMemo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("dtRegister", dtRegister);
		pRs.GetFieldValue("bGroupOwner", bGroupOwner);

		m_lstCustomer.InsertItem(i, m_cg.GetGroupData(nGNo)->strGroupName);
		m_lstCustomer.SetItemText(i, 1, m_cg.GetGroupData(nGNo)->strDept);
		m_lstCustomer.SetItemText(i, 2, itoa(nID, buffer, 10));
		m_lstCustomer.SetItemText(i, 3, sCompany);
		m_lstCustomer.SetItemText(i, 4, sName);
		m_lstCustomer.SetItemText(i, 5, LF->GetDashPhoneNumber(sTel1));
		m_lstCustomer.SetItemText(i, 6, dtRegister.Format("%y-%m-%d"));
		m_lstCustomer.SetItemText(i, 7, sMemo);

		m_lstCustomer.SetItemLong(i, nCNo);
		m_lstCustomer.SetItemData(i, nGNo);
		m_lstCustomer.SetItemLong2(i,bGroupOwner);

		pRs.MoveNext();
	}

	m_lstCustomer.Populate();
}

void CMoveGroupDlg::OnEnChangeSearchGroupEdit()
{
	CString strSearchWord = "";
	m_edtSearchGroup.GetWindowText(strSearchWord);

	CXTPGridRecords *pRecords = m_lstSrc.GetRecords();
	long nCount = pRecords->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CCustomerGroupRecord* pRecord = (CCustomerGroupRecord*)pRecords->GetAt(i);

		if(pRecord->m_strSearchData.Find(strSearchWord) >=0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstSrc.Populate();
	m_lstSrc.ExpandAll();
}

void CMoveGroupDlg::OnEnChangeSearchGroupEdit2()
{ 
	CString strSearchWord = "";
	m_edtSearchGroup2.GetWindowText(strSearchWord);

	CXTPGridRecords *pRecords = m_lstDst.GetRecords();
	long nCount = pRecords->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CCustomerGroupRecord* pRecord = (CCustomerGroupRecord*)pRecords->GetAt(i);

		if(pRecord->m_strSearchData.Find(strSearchWord) >=0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstDst.Populate();
	m_lstDst.ExpandAll();
}
