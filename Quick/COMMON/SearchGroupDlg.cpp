// SearchGroupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SearchGroupDlg.h"

// CSearchGroupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSearchGroupDlg, CMyDialog)
CSearchGroupDlg::CSearchGroupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(IDD_SEARCH_GROUP_DLG, pParent)
{
	m_nGNo = 0;
	m_nDataType = 0;
	m_nCompany = m_ci.m_nCompanyCode;
	m_strChargeName = "";
	m_nChargeID = 0;
	this->m_strGroupName = "";
	m_nAutoSearch = 0;
}

CSearchGroupDlg::~CSearchGroupDlg()
{ 
}

void CSearchGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//DDX_Control(pDX, IDC_LIST1, m_GroupList);
	
	DDX_Control(pDX, IDC_XTPLISTCTRL_EDIT, m_SearchEdit);
	DDX_Control(pDX, IDC_XTPLISTCTRL_COMBO, m_cmbSearchType);

	DDX_Text(pDX, IDC_XTPLISTCTRL_EDIT, m_strSearch);
}


BEGIN_MESSAGE_MAP(CSearchGroupDlg, CMyDialog)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_COMBO, OnCbnSelchangeXtplistctrlCombo)
	ON_EN_CHANGE(IDC_XTPLISTCTRL_EDIT, OnEnChangeXtplistctrlEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMClickList1)

	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SERVER_REFRESH_BTN, OnBnClickedServerRefreshBtn)
END_MESSAGE_MAP()


// CSearchGroupDlg 메시지 처리기입니다.

BOOL CSearchGroupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_List.SetExternalControl(GetDlgItem(IDC_XTPLISTCTRL_COMBO),
		GetDlgItem(IDC_XTPLISTCTRL_EDIT),			//SetExternalControl함수의 순서중요함
		NULL);	//반드시 InsertColumn앞에 있어야함

	m_cmbSearchType.ResetContent();

	for(int i = 0; i < m_cmbSearchType.GetCount(); i++)
		m_cmbSearchType.DeleteString(0);
	if(m_nDataType == SG_GROUP)
	{
		CXTPGridColumn* pCol0 = m_List.AddColumn(new CXTPGridColumn(0, "그룹명", 140));
		CXTPGridColumn *pCol1 = m_List.AddColumn(new CXTPGridColumn(1, "부서", 90, TRUE));
		CXTPGridColumn *pCol2 = m_List.AddColumn(new CXTPGridColumn(2, "요금제", 140, TRUE));

		pCol0->SetTreeColumn(1);

		m_List.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);
		m_List.GetReportHeader()->SetAutoColumnSizing(FALSE);
		m_List.GetReportHeader()->AllowColumnRemove(FALSE);
		m_List.GetReportHeader()->AllowColumnReorder(FALSE);
		m_List.AllowEdit(FALSE);
		m_List.SetGridColor(RGB(222, 222, 222));
		m_List.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
		m_List.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
		
		m_cmbSearchType.InsertString(0, "전체검색");
		m_cmbSearchType.InsertString(1, "그룹명");
		m_cmbSearchType.InsertString(2, "부서");
		m_cmbSearchType.InsertString(3, "요금제");		

	}
	else if(m_nDataType == SG_DISCOUNT_COMPANY)
	{
		m_List.InsertColumn(0,"요금제",LVCFMT_LEFT,340);
		m_List.InsertColumn(1,"비고",LVCFMT_LEFT,340);
		m_cmbSearchType.InsertString(0, "전체검색");
	}
	m_cmbSearchType.SetCurSel(0);
	//m_List.InsertSearchAllColumn(0);
	m_List.Populate();
	RefreshList();

	m_SearchEdit.SetFocus();

	if(m_nAutoSearch)
	{
		OnEnChangeXtplistctrlEdit();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSearchGroupDlg::RefreshList()
{
	m_List.DeleteAllItems();
	int i = 0;
	if(m_nDataType == SG_GROUP)
	{
		m_List.GetRecords()->RemoveAll();

		CXTPGridRecord *pReocrdTop = NULL;
		CXTPGridRecord *pReocrdLevel1 = NULL;
		CXTPGridRecord *pReocrdLevel2 = NULL;
		CXTPGridRecord *pReocrdLevel3 = NULL;
		CXTPGridRecord *pReocrdLevel4 = NULL;
		CXTPGridRecord *pReocrdLevel5 = NULL;

		VEC_CUSTOMER_GROUP::iterator it;
		VEC_CUSTOMER_GROUP *pGroup = m_cg.GetRefreshGroup();

		long nPreLevel = 0;
		
		for(it = pGroup->begin(); it != pGroup->end(); ++it)
		{
			ST_CUSTOMER_GROUP_INFOMATION *st = (*it);

			switch(st->nLevel)
			{
			case 0:
				pReocrdTop = m_List.AddRecord(new CSimpleGroupRecord(st));
				pReocrdTop->SetExpanded(TRUE);
				break;
			case 1:
				pReocrdLevel1 = pReocrdTop->GetChilds()->Add(new CSimpleGroupRecord(st));
				((CSimpleGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel1->SetExpanded(TRUE);
				break;
			case 2:
				pReocrdLevel2 = pReocrdLevel1->GetChilds()->Add(new CSimpleGroupRecord(st));
				((CSimpleGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel2->SetExpanded(TRUE);
				break;
			case 3:
				pReocrdLevel3 = pReocrdLevel2->GetChilds()->Add(new CSimpleGroupRecord(st));
				((CSimpleGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel3->SetExpanded(TRUE);
				break;
			case 4:
				pReocrdLevel4 = pReocrdLevel3->GetChilds()->Add(new CSimpleGroupRecord(st));
				((CSimpleGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel4->SetExpanded(TRUE);
				break;
			case 5:
				pReocrdLevel5 =pReocrdLevel4->GetChilds()->Add(new CSimpleGroupRecord(st));
				((CSimpleGroupRecord*)pReocrdTop)->AddSearchData(st);
				pReocrdLevel5->SetExpanded(TRUE);
				break;
			}
		}
	}
	else if(m_nDataType == SG_DISCOUNT_COMPANY)
	{
		MAP_CHARGE_TYPE_NAME::iterator it;
		for(it = m_mapChargeType.begin(); it != m_mapChargeType.end(); ++it)
		{
			if(it->second.strChargeName.GetLength() == 0)
				continue;

			m_List.InsertItem(i, it->second.strChargeName);
			m_List.SetItemText(i, 1, it->second.strEtc);
			m_List.SetItemData(i, it->first);
			i++;
		}		
	}
	m_List.Populate();
}

void CSearchGroupDlg::OnCbnSelchangeXtplistctrlCombo()
{
	OnEnChangeXtplistctrlEdit();
}

void CSearchGroupDlg::OnEnChangeXtplistctrlEdit()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_COMBO);
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_XTPLISTCTRL_EDIT);
	CComboBox *pTypeCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO);

	CString strText;
	pEdit->GetWindowText(strText);
	strText.Trim();
	strText.MakeUpper();

	if(strText.GetLength() == 0)
	{
		m_List.ShowAllRow();
		return;
	}

	int nSearchType = 0;
	BOOL bFind = FALSE, bAll = FALSE;
	bAll = nSearchType == 0 ? TRUE : FALSE;
	CString strWord;		
	if(m_nDataType == SG_GROUP)
	{
		CXTPGridRecords *pRecords = m_List.GetRecords();
		long nCount = pRecords->GetCount();

		for(int i=0; i<nCount; i++)
		{
			CSimpleGroupRecord* pRecord = (CSimpleGroupRecord*)pRecords->GetAt(i);

			if(pRecord->m_strSearchData.Find(strText) >=0)
				pRecord->SetVisible(TRUE);
			else
				pRecord->SetVisible(FALSE);
		}

		m_List.Populate();
		m_List.ExpandAll();
		
	}
	else
	{
		
		
		for(int i = 0; i < m_List.GetRecords()->GetCount(); i++)
		{
			CXTPGridRecord *pRecord  = m_List.GetRecords()->GetAt(i);
			long nCharge = (long)m_List.GetItemData(pRecord);
			
			bFind = FALSE;
			if(nSearchType == 1 || bAll)
			{
				strWord = m_mapChargeType[nCharge].strChargeName;				
				strWord.MakeUpper();
				if(strWord.Find(strText) >= 0 )
					bFind = TRUE;
			}
			if(nSearchType == 2 || bAll)
			{
				strWord = m_mapChargeType[nCharge].strEtc;				
				strWord.MakeUpper();
				if(strWord.Find(strText) >= 0 )
					bFind = TRUE;
			}
			
			pRecord->SetVisible(bFind);
		}


	}
	m_List.Populate();
	/*int nTypeData;
	if(pTypeCombo == NULL)
		nTypeData = -1;
	else
		nTypeData = (int)pTypeCombo->GetItemData(pTypeCombo->GetCurSel());

	m_List.Filter(strText, pCombo->GetCurSel(), nTypeData);*/
}


void CSearchGroupDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	long nRow = pNMListView->pRow->GetIndex();

	if(m_nDataType == SG_GROUP)
	{

		m_strGroupName = m_List.GetItemText(nRow, 0);
		m_strDeptName = m_List.GetItemText(nRow, 1);
		m_nGNo = m_List.GetItemData(nRow);

	}
	else
	{
		m_strChargeName = m_List.GetItemText(nRow, 0);
		m_nChargeID = m_List.GetItemData(nRow);
	}


	OnOK();

	*pResult = 0;
}


void CSearchGroupDlg::OnOK()
{
	CMyDialog::OnOK();
}

void CSearchGroupDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

void CSearchGroupDlg::OnBnClickedServerRefreshBtn()
{
	if(m_nDataType == SG_GROUP)
	{
		m_cg.FillData();
	}
	else
	{
		m_cg.FillCharge();

	}
}
