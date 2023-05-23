// ChargeInsertDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeInsertDlg.h"
#include "ChargeDongNewDlg.h"


// CChargeInsertDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeInsertDlg, CMyDialog)

CChargeInsertDlg::CChargeInsertDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CChargeInsertDlg::IDD, pParent)
, m_strCharge(_T(""))
{
	m_plstDong = NULL;
	m_nCol = 0;
}

CChargeInsertDlg::~CChargeInsertDlg()
{
}

void CChargeInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_LIST, m_lstStart);
	DDX_Control(pDX, IDC_DEST_LIST, m_lstDest);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Text(pDX, IDC_CHARGE_EDIT, m_strCharge);
}


BEGIN_MESSAGE_MAP(CChargeInsertDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CChargeInsertDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChargeInsertDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChargeInsertDlg 메시지 처리기입니다.

BOOL CChargeInsertDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstStart.AddColumn(new CXTPGridColumn(0, "동", 300, FALSE));
	m_lstDest.AddColumn(new CXTPGridColumn(0, "동", 300, FALSE));

	m_lstStart.ShowHeader(FALSE);
	m_lstDest.ShowHeader(FALSE);

	m_lstStart.Populate();
	m_lstDest.Populate();

	InitList();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChargeInsertDlg::InitList()
{
	m_lstStart.DeleteAllItems();
	m_lstDest.DeleteAllItems();

	CXTPGridSelectedRows *pSelRows = m_plstDong->GetSelectedRows();

	long nCount = pSelRows->GetCount();

	for(int i=0; i<nCount; i++)
	{
		CXTPGridRecord *pRecord = pSelRows->GetAt(i)->GetRecord();

		CString strStartDong = pRecord->GetItem(0)->GetCaption(NULL);
		m_lstStart.InsertItem(0, pRecord->GetItem(0)->GetCaption(NULL));
	}

	m_lstStart.Populate();

	CXTPGridRecord *pRecord = m_plstDong->GetRecords()->GetAt(0);
	m_lstDest.InsertItem(0, pRecord->GetItem(m_nCol)->GetCaption(NULL));

	m_lstDest.Populate(); 
}

void CChargeInsertDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_strCharge.Replace(",", "");

	if(m_strCharge.IsEmpty())
	{
		MessageBox("금액을 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtCharge.SetFocus();
		return;
	}

	if(!LF->IsStringDigit(m_strCharge))
	{
		MessageBox("금액을 숫자로 입력하세요", "확인", MB_ICONINFORMATION);
		m_edtCharge.SetFocus();
		return;
	}

	OnOK();
}

void CChargeInsertDlg::OnBnClickedCancel()
{
	OnCancel();
}
