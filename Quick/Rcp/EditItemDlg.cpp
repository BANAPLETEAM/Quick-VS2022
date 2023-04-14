// EditItemDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "EditItemDlg.h"


// CEditItemDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEditItemDlg, CMyDialog)

CEditItemDlg::CEditItemDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CEditItemDlg::IDD, pParent)
{
m_nCompany = 0;
}

CEditItemDlg::~CEditItemDlg()
{
}

void CEditItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEM_LIST, m_lstItem);
	DDX_Control(pDX, IDC_ADD_EDIT, m_edtAdd);
	DDX_Control(pDX, IDC_UPDATE_EDIT, m_edtUpdate);

	DDX_Control(pDX, IDC_INTEGRATED_CHECK, m_chkIntegrated);
	DDX_Control(pDX, IDC_INTERCALL_VIEW_CHECK, m_chkIntercallView);

	
}


BEGIN_MESSAGE_MAP(CEditItemDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ADD_BTN, &CEditItemDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_UPDATE_BTN, &CEditItemDlg::OnBnClickedUpdateBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CEditItemDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CEditItemDlg::OnBnClickedCloseBtn)
	ON_NOTIFY(NM_CLICK, IDC_ITEM_LIST, OnNMClickItemList)
	ON_NOTIFY(NM_RCLICK, IDC_ITEM_LIST, OnNMRClickItemList)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_WM_CONTEXTMENU()
	
	ON_BN_CLICKED(IDC_INTEGRATED_CHECK, &CEditItemDlg::OnBnClickedIntegratedCheck)
END_MESSAGE_MAP()


// CEditItemDlg 메시지 처리기입니다.

BOOL CEditItemDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog(); 

	m_lstItem.InsertColumn(0, "", LVCFMT_LEFT, 130);
	m_lstItem.ShowHeader(FALSE); 
	m_lstItem.Populate();

	if(m_ba.GetCount() < 2)
		m_chkIntegrated.ShowWindow(SW_HIDE);
	LoadItem();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CEditItemDlg::LoadItem()
{
	CString strItem = AfxGetApp()->GetProfileString("CEditItemDlg", "Item", "서류봉투;소박스;중박스;대박스;컴퓨터;");

	CStringArray strArry;
	::GetItemCommaToArray(strItem, strArry);

	for(int i=0; i<strArry.GetCount(); i++)
		m_lstItem.InsertItem(i, strArry.GetAt(i));

	m_lstItem.Populate();
}

void CEditItemDlg::OnBnClickedAddBtn()
{
	CString strItem; m_edtAdd.GetWindowText(strItem);

	if(strItem.IsEmpty() == TRUE)
	{
		MessageBox("항목을 입력하세요.", "확인", MB_ICONINFORMATION);
		m_edtAdd.SetFocus();
		return;
	}

	CXTPGridRows *pRows = m_lstItem.GetRows();

	for(int i=0; i<m_lstItem.GetItemCount(); i++)
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();
		CString strColItem = pRecord->GetItem(0)->GetCaption(NULL);

		if(strItem == strColItem)
		{
			MessageBox("이미 동일한 항목이 있습니다", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	m_lstItem.InsertItem(m_lstItem.GetItemCount(), strItem);
	m_lstItem.Populate();

	m_edtAdd.SetWindowText("");
}

void CEditItemDlg::OnBnClickedUpdateBtn()
{
	CXTPGridRecord *pRecord = m_lstItem.GetFirstSelectedRecord();

	if(pRecord == NULL)
	{
		MessageBox("수정 할 항목을 선택하세요.", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strItem; m_edtUpdate.GetWindowText(strItem);

	if(strItem.IsEmpty() == TRUE)
	{
		MessageBox("항목을 입력하세요.", "확인", MB_ICONINFORMATION);
		m_edtUpdate.SetFocus();
		return;
	}

	pRecord->GetItem(0)->SetCaption(strItem);
	m_lstItem.Populate();
}

void CEditItemDlg::OnBnClickedSaveBtn()
{
	CString strItemArry = "";

	for(int i=0; i<m_lstItem.GetItemCount(); i++)
	{
		CString strItem = m_lstItem.GetItemText(i, 0);

		if(strItem.IsEmpty() == FALSE)
			strItemArry += strItem + ";";
	}
	if(m_chkIntercallView.GetCheck())
	{

		
			

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_item_info");
		pCmd.AddParameter(m_nCompany);	
		pCmd.AddParameter(m_chkIntegrated.GetCheck());
		pCmd.AddParameter(GetBranchInfo(m_nCompany)->nShareCode1);
		pCmd.AddParameter(strItemArry);	
		if(!pRs.Execute(&pCmd)) return ;

		MessageBox("인터콜에 항목이 적용되었습니다. 인터콜 재로그인시 적용됩니다", "확인", MB_ICONINFORMATION);

	}

	AfxGetApp()->WriteProfileString("CEditItemDlg", "Item", strItemArry);	

	OnOK();
}

void CEditItemDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CEditItemDlg::OnNMClickItemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPGridRecord *pRecord = m_lstItem.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CString strItem = m_lstItem.GetItemText(pRecord, 0);
	m_edtUpdate.SetWindowText(strItem);
}

void CEditItemDlg::OnNMRClickItemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CXTPGridRecord *pRecord = m_lstItem.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	OnContextMenu(&m_lstItem, pt);
}

void CEditItemDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstItem.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(12);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CEditItemDlg::OnDelete()
{
	CXTPGridRecord *pRecord = m_lstItem.GetFirstSelectedRecord();

	if(pRecord == NULL)
	{
		MessageBox("삭제 하려는 항목을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	pRecord->Delete();
	m_lstItem.Populate();
	m_edtUpdate.SetWindowText("");
}
void CEditItemDlg::OnBnClickedIntegratedCheck()
{
	if( m_chkIntegrated.GetCheck() )
		m_chkIntercallView.SetCheck(TRUE);
}
