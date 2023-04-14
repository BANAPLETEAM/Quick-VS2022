// TestDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "TestDlg.h"



CK2Record::CK2Record() :CXTPGridRecord()
{
	
}
void CK2Record::SetMyRecord2(int nItem)
{
	m_nItem1 = nItem;
}
void CK2Record::SetMyRecord()
{

	AddItem(new CXTPGridRecordItemNumber(m_nItem1));
	AddItem(new CXTPGridRecordItemNumber(m_nItem2));
	AddItem(new CXTPGridRecordItemText(m_s1));
	AddItem(new CXTPGridRecordItemDateTime(m_dt1));
}



// CTestDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTestDlg, CMyDialog)
CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTestDlg::IDD, pParent)
{
	
}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_data);
}


BEGIN_MESSAGE_MAP(CTestDlg, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(65535, OnBnClicked65535)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM1, OnReportItemClick)
END_MESSAGE_MAP()


// CTestDlg 메시지 처리기입니다.

void CTestDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CString s1 = pItemNotify->pColumn->GetCaption();
	CString t1 = pItemNotify->pRow->GetRecord()->GetItem(0)->GetCaption(NULL);
	CString t2 = pItemNotify->pRow->GetRecord()->GetItem(1)->GetCaption(NULL);
	CString t3 = pItemNotify->pRow->GetRecord()->GetItem(2)->GetCaption(NULL);
}

void CTestDlg::OnBnClickedButton1() 
{
	
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_alloc_rider_list2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 10);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), 1);	
	if(!pRs.Execute(&pCmd)) return;


	long lCode =0 , nMNo =0, nCarType = 0,nAllocGroup = 0, nDepositType = 0;
	CString sHp = "", sBranchName = "", sName = "", sDong = "", sGugun = "";
	long nID = 0, nDongID = 0, nPosX = 0, nPosY = 0;
	COleDateTime dtConn;
	BOOL bGPSUsage = FALSE, bConnection = FALSE;

	int i = 0;
	m_pRecord3 = new CK2Record();
	
	while(!pRs.IsEOF())
	{
		m_Record[i] = new CK2Record();		
		
		
		pRs.GetFieldValue("lCode", lCode);
		pRs.GetFieldValue("nMNo", nMNo);	
		pRs.GetFieldValue("sName",sName );		
		m_Record[i]->m_nItem1 = lCode;
		m_Record[i]->m_nItem2 = nMNo;
		m_Record[i]->m_s1 = sName;

		//m_pRecord4[i]->m_nItem1 = lCode;
		//m_pRecord4[i]->m_nItem2 = nMNo;
		//m_pRecord4[i]->m_s1 = sName;


		m_Record[i]->m_dt1 = COleDateTime::GetCurrentTime();		
		m_Record[i]->SetMyRecord();
		m_data.AddRecord(m_Record[i]);

		
		
		m_pRecord3->data[i].m_nItem1 = lCode;
		m_pRecord3->data[i].m_nItem2 = nMNo;
		m_pRecord3->data[i].m_s1 = sName;
		m_pRecord3->SetMyRecord();

		i++;
		pRs.MoveNext();
	}	
	m_data.m_pRecord3 = m_pRecord3;
	m_data.SetRecord(m_Record);

	m_data.InternalAddRef();
	m_data.SetVirtualMode( m_pRecord3, m_Record.size());
	m_data.Populate();
	//m_data.SetVirtualMode(m_Record)
	
}
CK2Record *pRs = NULL;


void CTestDlg::OnBnClickedButton2()
{
	int nItemCount = m_Record.size();
	int nCount = m_data.GetRecords()->GetCount();
	int nMapSize = m_Record.size();
	//int nMapCount = m_Record.count();
	CK2Record *pRecord = m_Record[2];
	MyData::iterator it1;
	int nMapCount = 0;
	for(it1 = m_Record.begin(); it1 != m_Record.end(); ++it1)
		nMapCount++;
	//pRecord->m_nItem1 = 20;
	//m_Record[2]->m_nItem1 = 40;

	m_data.Populate();
	//CString s = m_Record[3]->m_s1;

	//pRecord->RemoveAll();
	int nRecordCount = m_Record.size();
	CXTPGridRow *pRow = m_data.GetRows()->GetAt(4);
	//m_data.GetRecords()->RemoveAt(4);
	
	nRecordCount = m_Record.size();
	MyData::iterator it;

	int i = 0;
	for(it = m_Record.begin(); it != m_Record.end(); ++it)
	{
		if(i == 2)
		{
			pRs = m_Record[2];
			int nTestItem = pRs->m_nItem1;
			

			
			int k = m_Record.size();
			m_data.GetRows()->RemoveAt(2);
			m_data.GetRecords()->RemoveAt(2);
			if(pRs)		
			{
				int i = pRs->m_nItem1;
				delete pRs;
				pRs = NULL;
			}
			m_Record.erase(it);

			
			int nItemCount = m_Record.size();
			//pRs->InternalRelease();
			
			//m_data.Populate();

			
			//m_data.InternalRelease();
			//m_data.InternalAddRef();
			break;

		}
		i++;

	}
	if(pRs)
		delete pRs;
	
	m_data.Populate();
	
}

BOOL CTestDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_data.InsertColumn(0,"아이템1",DT_LEFT, 100);
	m_data.InsertColumn(1,"아이템2",DT_LEFT, 100);
	m_data.InsertColumn(2,"문자",DT_LEFT, 100);
	m_data.InsertColumn(3,"날짜",DT_LEFT, 100);
	
	m_data.GetReportHeader()->AllowColumnRemove(FALSE);
	m_data.GetReportHeader()->AllowColumnResize(FALSE);
	m_data.GetReportHeader()->AllowColumnSort(TRUE);
	//m_wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE); // 사이즈 자동조정
	m_data.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_data.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";
	m_data.AllowEdit(FALSE);
	m_data.FocusSubItems(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
class CTest {
public:
	int a;
	int b;
};
typedef map<long , CTest> Test;
Test test;

void CTestDlg::OnBnClickedButton3()
{
/*
	int nSize = test.size();
	CTest a, b, c;
	a.a = 4;
	a.b = 5;
	//c = test[0];
	int nTest1 = c.a;

	test[0] = a;
	test[1] = b;
	 nSize = test.size();
	Test::iterator it;
	it = test.begin();
	test.erase(it);
	 nSize = test.size();

	nSize = test.size();
*/
}

typedef map<long , long> Test2;
Test2 test2;
void CTestDlg::OnBnClickedButton4()
{
	for(int i = 0; i < 10; i++)
	{

		//test2[i]. = i;
	}
}

void CTestDlg::OnBnClicked65535()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
