// EditItemDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "EditItemDlg.h"


// CEditItemDlg ��ȭ �����Դϴ�.

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


// CEditItemDlg �޽��� ó�����Դϴ�.

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CEditItemDlg::LoadItem()
{
	CString strItem = AfxGetApp()->GetProfileString("CEditItemDlg", "Item", "��������;�ҹڽ�;�߹ڽ�;��ڽ�;��ǻ��;");

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
		MessageBox("�׸��� �Է��ϼ���.", "Ȯ��", MB_ICONINFORMATION);
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
			MessageBox("�̹� ������ �׸��� �ֽ��ϴ�", "Ȯ��", MB_ICONINFORMATION);
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
		MessageBox("���� �� �׸��� �����ϼ���.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CString strItem; m_edtUpdate.GetWindowText(strItem);

	if(strItem.IsEmpty() == TRUE)
	{
		MessageBox("�׸��� �Է��ϼ���.", "Ȯ��", MB_ICONINFORMATION);
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

		MessageBox("�����ݿ� �׸��� ����Ǿ����ϴ�. ������ ��α��ν� ����˴ϴ�", "Ȯ��", MB_ICONINFORMATION);

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
		MessageBox("���� �Ϸ��� �׸��� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
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
