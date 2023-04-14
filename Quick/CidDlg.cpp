// CidDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CidDlg.h"
#include "RcpView.h"

// CCidDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCidDlg, CMyDialog)
CCidDlg::CCidDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCidDlg::IDD, pParent)
{
}

CCidDlg::~CCidDlg()
{
}

void CCidDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CCidDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CCidDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_OPEN_PRE_BTN, &CCidDlg::OnBnClickedOpenPreBtn)
	ON_BN_CLICKED(IDC_OPEN_NEW_BTN, &CCidDlg::OnBnClickedOpenNewBtn)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CCidDlg::OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CCidDlg �޽��� ó�����Դϴ�.

BOOL CCidDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//SetWindowPos(&CWnd::wndTopMost, 0,0,0, 0, SWP_NOSIZE | SWP_NOMOVE);

	m_List.InsertColumn(0, "No", LVCFMT_CENTER, 40);
    m_List.InsertColumn(1, "�ð�", LVCFMT_CENTER, 90);
	m_List.InsertColumn(2, "��ȭ��ȣ", LVCFMT_LEFT, 95);
	m_List.InsertColumn(3, "Ÿ��", LVCFMT_LEFT, 45);
	m_List.InsertColumn(4, "����ȸ��", LVCFMT_LEFT, 105);
	m_List.InsertColumn(5, "��", LVCFMT_LEFT, 40);
	m_List.InsertColumn(6, "���", LVCFMT_LEFT, 40);
	m_List.InsertColumn(7, "����", LVCFMT_LEFT, 95);
	m_List.Populate();

	RefreshList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CCidDlg::RefreshList()
{
	m_List.DeleteAllItems();
	char buffer[10];

    CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_recv_cid");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	if(!pRs.Execute(&pCmd)) return;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		COleDateTime dtWrite;
		int nType;
		CString strData, sCName;
		long nCallCompany,nTNo;
		BOOL bNewCustomer = FALSE;

		pRs.GetFieldValue("dtWrite", dtWrite);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("sData", strData);
		pRs.GetFieldValue("nCallCompany", nCallCompany);
		pRs.GetFieldValue("bNewCustomer", bNewCustomer);
		pRs.GetFieldValue("nTNo", nTNo);
		pRs.GetFieldValue("sCName", sCName); 

		if((POWER_CHECK(1510, "CID") == FALSE) && (i> 20))
			break;		

		m_List.InsertItem(i, itoa(i+1, buffer, 10));
		m_List.SetItemText(i, 1, dtWrite.Format("%m-%d %H:%M:%S"));
		m_List.SetItemText(i, 2, GetDashPhoneNumber(strData));
		m_List.SetItemText(i, 3, nType == 10 ? "���" : "��");
		m_List.SetItemText(i, 4, m_ci.GetBranchName(nCallCompany));
		m_List.SetItemText(i, 5, bNewCustomer ? "�ű�" : "");
		m_List.SetItemText(i, 6, nTNo > 0 ? "O" : "");
		m_List.SetItemText(i, 7, sCName);
		m_List.SetItemData(i, nTNo > 0  ? (DWORD_PTR)nTNo : (DWORD_PTR)-1);

		pRs.MoveNext();
	}

	m_List.Populate();
}

BOOL CCidDlg::SetClipboardText(const CString strData)
{
	BOOL bRtn = FALSE;

	// Ŭ������ ����
	bRtn = OpenClipboard();
	// Ŭ������ ����
	bRtn = EmptyClipboard(); 

	//////////////////////////////////////////////////////////////////////////
	/// �۷ι��� memory ���
	HGLOBAL hglb;
	LPTSTR  lptstr;
	int cch = strData.GetLength();
	hglb = GlobalAlloc(GMEM_MOVEABLE, (cch + 1) * sizeof(TCHAR));
	if(hglb == NULL)
		return FALSE;
	lptstr = (LPTSTR)GlobalLock(hglb);
	memcpy(lptstr, strData, cch * sizeof(TCHAR));
	lptstr[cch] = (TCHAR)0;
	GlobalUnlock(hglb);    
	//////////////////////////////////////////////////////////////////////////

	// �۷ι� memory �� Ŭ�����忡 ���� �ְ�
	SetClipboardData(CF_TEXT, hglb);

	// Ŭ������ �ݰ�
	bRtn = CloseClipboard();

	return bRtn;
}


BOOL CCidDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(::GetKeyState(VK_CONTROL ) )
		{
			if(pMsg->wParam == 67)
			{
				long nIndex = m_List.GetNextItem(-1, LVNI_SELECTED);

				if(nIndex == -1) return TRUE;

				CString str = m_List.GetItemText(nIndex, 1);
				SetClipboardText(str);			
			}
		}
	}
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CCidDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

void CCidDlg::OpenPreDlg()
{
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows == NULL) {MessageBox("��ȭ��ȣ�� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;}
	if(pRows->GetCount() == 0) {MessageBox("��ȭ��ȣ�� �����ϼ���", "Ȯ��", MB_ICONINFORMATION); return;}

	long nTNo = (long)m_List.GetItemData(pRows->GetAt(0)->GetRecord());
	if(nTNo < 0)
	{
		MessageBox("�ش� CID�� ������ ������ �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	LU->GetRcpView()->SetItemSelectFromTNo(nTNo);
	LU->GetRcpView()->OnBnClickedEditBtn();
}

void CCidDlg::OnBnClickedOpenPreBtn()
{
	OpenPreDlg();
}

void CCidDlg::OnBnClickedOpenNewBtn()
{
	OpenNewDlg();
}

void CCidDlg::OpenNewDlg()
{
	CString strPhone = "";
	
	CXTPGridSelectedRows *pRows = m_List.GetSelectedRows();

	if(pRows != NULL)
	{
		if(pRows->GetCount() == 0)
			return;

		strPhone = m_List.GetItemText(pRows->GetAt(0)->GetRecord(), 2);
		strPhone.Replace("-", ""); 
	}

	char data[1024];
	COPYDATASTRUCT *cds = new COPYDATASTRUCT;

	STRCPY(data, "E", "-1", strPhone, "-1", "-1", VL_END);

	cds->cbData = strlen(data);
	cds->lpData = (void*) data;

	::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_COPYDATA, (long)this->m_hWnd, (long)cds);

	delete cds;
}

void CCidDlg::OnEnChangeSearchEdit()
{
	CString sSearch; m_edtSearch.GetWindowText(sSearch);
	CXTPGridRecords *pRecords = m_List.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString sPhone = m_List.GetItemText(pRecord, 2);
		CString sTNo = m_List.GetItemText(pRecord, 6);
		sPhone.Replace("-", "");

		if(sPhone.Find(sSearch) >= 0 ||
			sTNo.Find(sSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_List.Populate();	
}
