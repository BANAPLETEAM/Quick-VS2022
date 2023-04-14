// OrderPassDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "OrderPassDlg.h"


// COrderPassDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COrderPassDlg, CMyDialog)

COrderPassDlg::COrderPassDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COrderPassDlg::IDD, pParent)
{
	m_nRiderCompany = 0;
	m_nRNo = 0;
}

COrderPassDlg::~COrderPassDlg()
{
}

void COrderPassDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_DUPLICATE_LIST, m_lstDuplicate);
}


BEGIN_MESSAGE_MAP(COrderPassDlg, CMyDialog)
	ON_EN_CHANGE(IDC_RNO_EDIT, &COrderPassDlg::OnEnChangeRnoEdit)
	ON_BN_CLICKED(IDC_ALLOCATE_BTN, &COrderPassDlg::OnBnClickedAllocateBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &COrderPassDlg::OnBnClickedCancelBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_DUPLICATE_LIST, OnNMDblclkDuplicateList)
END_MESSAGE_MAP()

void COrderPassDlg::OnNMDblclkDuplicateList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedAllocateBtn();
}
// COrderPassDlg 메시지 처리기입니다.

void COrderPassDlg::OnEnChangeRnoEdit()
{
	if(m_rm.size() == 0)
	{
		FillVaildRiderData();
	}

	BOOL bFirst = TRUE;

	CString sSearch; m_edtRNo.GetWindowText(sSearch);
	CXTPGridRecords *pRecords = m_lstDuplicate.GetRecords(); 

	long nLength = sSearch.GetLength(); 

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		if(nLength == 0)
		{
			pRecord->SetVisible(TRUE);
			continue;
		}

		CString sRNo = pRecord->GetItem(1)->GetCaption(NULL);
		CString sRName = pRecord->GetItem(2)->GetCaption(NULL);

		if( sRName.Find(  sSearch) >= 0 || (sRNo.Find(  sSearch) >= 0  && sRNo.Mid(0, nLength ) == sSearch.Mid(0,nLength )) )				
		{				
			pRecord->SetVisible(TRUE);
		}
		else
			pRecord->SetVisible(FALSE);

	}

	m_lstDuplicate.Populate();
}

BOOL COrderPassDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstDuplicate.InsertColumn(0,"지사명", LVCFMT_CENTER, 120);
	m_lstDuplicate.InsertColumn(1,"기사번호",LVCFMT_CENTER, 80);
	m_lstDuplicate.InsertColumn(2,"기사명", LVCFMT_CENTER, 120);
	m_lstDuplicate.Populate();

	m_lstDuplicate.Populate();
	InsertListData();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COrderPassDlg::InsertListData()
{
	if(m_rm.size() == 0)
		FillVaildRiderData();

	char buffer[10];

	MAP_RIDER::iterator it;
	long nItem = 0;

	for(it = m_rm.begin(); it != m_rm.end(); it++)
	{
		if(it->second.nWorkState > 0)
			continue;

		CXTPGridRecord *pRecord = m_lstDuplicate.InsertItem(nItem, m_ci.GetBranchName(it->second.nCompany));
		m_lstDuplicate.SetItemText(nItem, 1, itoa(it->second.nRNo, buffer, 10));
		m_lstDuplicate.SetItemText(nItem, 2, it->second.strName);
		m_lstDuplicate.SetItemLong(nItem++, it->second.nCompany);
	}	

	m_lstDuplicate.Populate();
}


void COrderPassDlg::OnBnClickedAllocateBtn()
{
	CXTPGridSelectedRows *pRows = m_lstDuplicate.GetSelectedRows();

	if(pRows == NULL)
	{
		MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(pRows->GetCount() == 0)
	{
		MessageBox("기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	m_nRiderCompany = m_lstDuplicate.GetItemLong(pRecord);
	m_nRNo = atoi(pRecord->GetItem(1)->GetCaption(NULL));
	
	OnOK();
}

void COrderPassDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

BOOL COrderPassDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN) 
		{
			if(pMsg->hwnd == m_lstDuplicate.GetSafeHwnd() ||
				pMsg->hwnd == m_edtRNo.GetSafeHwnd())
				OnBnClickedAllocateBtn();

			return TRUE;
		}

	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
