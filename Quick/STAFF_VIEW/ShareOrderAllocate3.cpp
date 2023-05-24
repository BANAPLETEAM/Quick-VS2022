// CShareOrderAllocate3.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareOrderAllocate3.h"

typedef struct{
	long nCompany;
	CString sCompany;
	CString sBranchName;
} BRANCHINFO;


// CShareOrderAllocate3 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShareOrderAllocate3, CMyDialog)
CShareOrderAllocate3::CShareOrderAllocate3(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShareOrderAllocate3::IDD, pParent)
	, m_nRider(0)
	, m_sDetailEdit(_T(""))
	, m_sRiderName(_T(""))
{
	m_nID = -1;
	m_ModifyButtonEnable = FALSE;
	m_nRiderCompany = -1;

	m_nSeletedCompany = -1;
}

CShareOrderAllocate3::~CShareOrderAllocate3()
{
}

void CShareOrderAllocate3::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompanyName);
	DDX_Control(pDX, IDC_SELECTED_COMPANY_EDIT, m_edtSelectedCompanyName);
	DDX_Text(pDX, IDC_RIDER_EDIT, m_nRider);	
	DDX_Text(pDX, IDC_DETAIL_EDIT, m_sDetailEdit);
	DDX_Text(pDX, IDC_EDIT3, m_sRiderName);
	DDX_Control(pDX, IDC_BUTTON1, m_btnModify);
	DDX_Control(pDX, IDC_BUTTON_APPLY_ALL, m_btnApplyAll);	
	DDX_Control(pDX, IDC_RIDER_EDIT, m_edtRiderNO);
	DDX_Control(pDX, IDC_DETAIL_EDIT, m_DetailEdit);
	DDX_Control(pDX, IDC_EDIT3, m_edtRiderName);
	DDX_Control(pDX, IDC_DAY_COMBO, m_cmbDay);
}


BEGIN_MESSAGE_MAP(CShareOrderAllocate3, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
	ON_BN_CLICKED(IDC_TEST_BUTTON, OnBnClickedTestButton)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_DETAIL_EDIT, OnEnChangeDetailEdit)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_ALL, OnBnClickedButtonApplyAll)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnNMClickList)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST, OnLvnDeleteitemList)
END_MESSAGE_MAP()


// CShareOrderAllocate3 �޽��� ó�����Դϴ�.

BOOL CShareOrderAllocate3::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_cmbDay.SetCurSel(ZERO);
	InitControl();
	m_btnApplyAll.EnableWindow(LF->GetCurBranchInfo()->bIntegrated);
	if(!m_nMode) // 1�ű� 0 ����
	{
		m_edtCompanyName.EnableWindow(FALSE);
		m_btnModify.EnableWindow(m_ModifyButtonEnable);
		ModifyUser();
	}

	return TRUE;
	
}
void CShareOrderAllocate3::InitControl()
{
	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0,"ȸ���", LVCFMT_LEFT, 100);
	m_List.InsertColumn(1,"�����",LVCFMT_LEFT,  100);
	m_List.InsertColumn(2,"��������",LVCFMT_LEFT,  50);
	m_List.InsertColumn(3,"���",LVCFMT_LEFT,  60);
	m_List.InsertColumn(4,"�̸�",LVCFMT_LEFT,  60);
}

void CShareOrderAllocate3::ModifyUser()
{
	m_edtRiderNO.EnableWindow(FALSE);

	//CWaitCursor wait;
	CMkCommand pCmd(m_pMkDb, "select_share_order_modify_2");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nID);
	if(!pRs.Execute(&pCmd))
		return;

	long nID,nCompany,nRiderCompany, nRNo, nDay;
	nID = nCompany = nRiderCompany = nRNo = 0;

	CString		sRName,sMemo;

	pRs.GetFieldValue("nID", nID);
	pRs.GetFieldValue("nCompany", nCompany);
	pRs.GetFieldValue("nRiderCompany", nRiderCompany);
	pRs.GetFieldValue("nRNo", nRNo);
	pRs.GetFieldValue("sRName", sRName);
	pRs.GetFieldValue("sMemo", sMemo);
	pRs.GetFieldValue("nDay", nDay);

	UpdateData();
	m_nRider = nRNo;
	m_sDetailEdit = sMemo;
	m_sRiderName = sRName;
	m_nRiderCompany = nRiderCompany;
	m_nSeletedCompany = m_nCompany;
	m_sDetailEdit = sMemo;
	m_edtSelectedCompanyName.SetWindowText(m_ci.GetBranchName(nRiderCompany));
	UpdateData(FALSE);

	char buffer [10];

	if(nDay > 0)
		m_cmbDay.SetWindowText(itoa(nDay, buffer, 10));
}


void CShareOrderAllocate3::ModifyUserOk(BOOL bAll)
{
	try
	{
		if(m_nID <= 0)
			throw "������ �ٽ� ���ּ���";

		if(m_nRiderCompany <= 0 )
			throw "���缱���� ���ּ���";
			
		if(m_nRider <= 0 )
			throw "��縦 �ٽñ������ּ���";

		CString strDay; m_cmbDay.GetWindowText(strDay);
		long nDay = 0;

		if(strDay != "������")
			nDay = atoi(strDay);			

		int nParameter = -1; 
		UpdateData(TRUE);
		CMkCommand pCmd(m_pMkDb, "update_share_order_rider_register_1");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nID);
		pCmd.AddParameter(typeString, typeInput, m_sDetailEdit.GetLength(), m_sDetailEdit );
		pCmd.AddParameter(nDay);
		if(!pRs.Execute(&pCmd))
			return;		
	
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"Ȯ��",MB_ICONINFORMATION);
		return;
	}

	MessageBox("�����Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
	OnOK();
}

void CShareOrderAllocate3::NewUserOk(BOOL bAll)
{
	try
	{	
		if(m_nRiderCompany <= 0 )
			throw "���缱���� ���ּ���";
			
		if(m_nRider <= 0 )
			throw "����ȣ�� �ٽñ������ּ���";

		CString strDay; m_cmbDay.GetWindowText(strDay);
		long nDay = 0;

		if(strDay != "������")
			nDay = atoi(strDay);	

		int nParameter = -1; 
		UpdateData(TRUE);
		CMkCommand pCmd(m_pMkDb, "insert_share_order_rider_register_4");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetCurBranchInfo()->nCompanyCode);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bAll);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRiderCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRider );
		pCmd.AddParameter(typeString, typeInput, m_sRiderName.GetLength(), m_sRiderName);
		pCmd.AddParameter(typeString, typeInput, m_sDetailEdit.GetLength(), m_sDetailEdit);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode );	
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL),m_ci.m_bRcpIntMode1 );
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nDay);
		CMkParameter *parReturn = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
		if(!pRs.Execute(&pCmd))
			throw("����� �����ʾҽ��ϴ�. �ٽ��ѹ� �õ��Ͽ� �ּ���");

		parReturn->GetValue(nParameter);
		if(nParameter <= 0)
			throw "��ȸ�Ͻ� �������δ� ��ġ���� �ʽ��ϴ�. �ٽõ�� ���ּ���";
		
		else if(nParameter == 200)
			throw "���տ� ���������� �ɷ��ֽ��ϴ�. ";
		else if(nParameter == 300)
			throw " ���������� �ɷ��ֽ��ϴ�. ";
		else
		{
			MessageBox("��ȸ�Ͻ� �������� ��ϵǾ����ϴ�. ","����̸� Ȯ��",MB_ICONINFORMATION);
			OnOK();
		}
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"Ȯ��",MB_ICONINFORMATION);
		return;
	}
}

void CShareOrderAllocate3::OnBnClickedButton7()
{
	OnCancel();
}

void CShareOrderAllocate3::OnBnClickedTestButton()
{
	VerifyRider();
}

void CShareOrderAllocate3::VerifyRider(BOOL bNoMsg)
{
	UpdateData();
	
	if(m_nRiderCompany <= 0 )
	{
		MessageBox("���缱���� ���ּ���", "���缱��", MB_ICONINFORMATION);
		return;
	}
	if(m_nRider <= 0 )
	{
		MessageBox("��縦 �ٽñ������ּ���", "��缱��", MB_ICONINFORMATION);
		return;
	}
	
	int nReturn;
	CString strRiderName;
	
	CMkCommand pCmd(m_pMkDb, "select_share_order_allocate_rider_test");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRider);
	CMkParameter *parReturn = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	CMkParameter *parReturnName = pCmd.AddParameter(typeString, typeOutput, 20, CString(""));
	
	if(!pRs.Execute(&pCmd))
		return;

	parReturn->GetValue(nReturn);
	parReturnName->GetValue(strRiderName);
	if(nReturn)
	{
		if(!bNoMsg)
			MessageBox(strRiderName + "�����Դϴ�.","����̸� Ȯ��",MB_ICONINFORMATION);		

		m_sRiderName = strRiderName;
		UpdateData(FALSE);
	}
	else
	{
		if(!bNoMsg)
			MessageBox("��ȸ�Ͻ� ��簡 ��ϵǾ� ���� �ʽ��ϴ�. �ٽ�Ȯ�� ���ּ���!","����̸� Ȯ��",MB_ICONINFORMATION);
	}
	
}



HBRUSH CShareOrderAllocate3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_DETAIL_EDIT) {
		pDC->SetTextColor(RGB(255, 0, 0));
	}	

	return hbr;
}


void CShareOrderAllocate3::OnEnChangeDetailEdit()
{
	if(m_DetailEdit.GetWindowTextLength() > 255)
	{
		CString strDetail;
		m_DetailEdit.GetWindowText(strDetail);
		m_DetailEdit.SetWindowText(strDetail.Left(strDetail.GetLength() - 1));
		MessageBox("255�� ���Ϸ� �Է��Ͻñ� �ٶ��ϴ�.", "���� �ʰ�", MB_ICONINFORMATION);
	}
}

void CShareOrderAllocate3::OnBnClickedButtonApplyAll()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_nMode) // 1�ű� 0 ����
	{
		NewUserOk(TRUE);
	}
	else
		ModifyUserOk(TRUE);
}

void CShareOrderAllocate3::OnBnClickedButton1()
{
	if(m_nMode) // 1�ű� 0 ����
	{
		NewUserOk(FALSE);
	}
	else
		ModifyUserOk(FALSE);
}
BOOL CShareOrderAllocate3::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN &&pMsg->wParam == VK_RETURN 
		&& ::GetDlgCtrlID(pMsg->hwnd) == IDC_COMPANY_EDIT)	
	{
		
			SearchCompanyList();		
			return FALSE;
	}
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CShareOrderAllocate3::SearchCompanyList()
{
	m_List.DeleteAllItems();

	CString strSearch; m_edtCompanyName.GetWindowText(strSearch);

	if(strSearch == "0" || strSearch == "")
	{
		MessageBox("�ٽ� �Է��� �ּ���" , "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_other_allocate_rider_new");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode1);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode2);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode3);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode4);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nShareCode5);
	pCmd.AddParameter(strSearch);

	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == 0) return;

	long nCompany, nRNo, nRiderBalance, nDepositType, nWorkState;
	long nShareCode2, nShareCode3, nShareCode4, nShareCode5;
	CString sName;
	char buffer[20]; 

	//long nOrderDeposit = 0; pDeposit->GetValue(nOrderDeposit);

	//if(nOrderDeposit > 20000)
	//{
	//	MessageBox("�Աݾ� 2���� �̻��� �����Ҽ� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
	//	OnCancel();
	//}

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("nRiderBalance", nRiderBalance);
		pRs.GetFieldValue("nDepositType", nDepositType);
		pRs.GetFieldValue("nWorkState", nWorkState);

		pRs.GetFieldValue("nShareCode2", nShareCode2);
		pRs.GetFieldValue("nShareCode3", nShareCode3);
		pRs.GetFieldValue("nShareCode4", nShareCode4);
		pRs.GetFieldValue("nShareCode5", nShareCode5);

		m_List.InsertItem(i, m_ci.GetName(nCompany));
		m_List.SetItemText(i, 1, m_ci.GetBranchName(nCompany));

		CString strFormat = "";
		if(m_ci.m_nShareCode2 == nShareCode2 && nShareCode2 != 0)
			strFormat += "��";
		if(m_ci.m_nShareCode3 == nShareCode3 && nShareCode3 != 0)
			strFormat += "��";
		if(m_ci.m_nShareCode4 == nShareCode4 && nShareCode4 != 0)
			strFormat += "��";
		if(m_ci.m_nShareCode5 == nShareCode5 && nShareCode5 != 0)
			strFormat += "��";			

		m_List.SetItemText(i, 2, strFormat);

		m_List.SetItemText(i, 3, itoa(nRNo, buffer, 10));
		m_List.SetItemText(i, 4, sName);


		//m_ReportList.SetItemText(i, 4, GetEtc(nOrderDeposit, nRiderBalance, nDepositType, m_nCompany, nCompany, nWorkState));
		m_List.SetItemData(i, nCompany);

		pRs.MoveNext();
	}

	//m_ReportList.Populate();

	//CXTPGridRows *pRows = m_ReportList.GetRows();
	//CXTPGridRow *pRow = pRows->GetAt(0);

	//m_ReportList.GetSelectedRows()->Select(pRow);

	/*
	CString sCompany= "";
	m_edtCompanyName.GetWindowText(sCompany);
	if(sCompany.GetLength() <= 0)
		return;
	
	sCompany.MakeUpper();
	
	m_List.DeleteAllItems();
	SHARED_COMPANY_MAP::iterator it;
	int n = 0, nItem = 0;
	char buffer[10];
	for(it = m_ci.GetShareMapBegin(); it != m_ci.GetShareMapEnd(); it++)
	{	
		CString s1 = (*it).second.strBranchName;
		CString s2 = (*it).second.strName;
		s1.MakeUpper();
		s2.MakeUpper();
		if(s1.Find(sCompany) >= 0 || s1.Compare(sCompany) == 0
			|| s2.Find(sCompany) >= 0 || s2.Compare(sCompany) == 0)
		{
			m_List.InsertItem(nItem,itoa(nItem,buffer,10));
			m_List.SetItemText(nItem,1,(*it).second.strName);
			m_List.SetItemText(nItem,2,(*it).second.strBranchName);
			m_List.SetItemText(nItem,3,(*it).second.strPhone);

			BRANCHINFO *pBranch = new BRANCHINFO;
			pBranch->nCompany = (*it).first;
			pBranch->sBranchName = (*it).second.strBranchName;
			pBranch->sCompany = (*it).second.strName;

			m_List.SetItemData(nItem++,(DWORD_PTR)pBranch);

			TRACE("n = %d\n", (*it).second.nCompany);			
		}
		
	}
	*/
}
void CShareOrderAllocate3::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if(m_List.GetItemCount() <= 0)
	{
		*pResult = 0;
		return;
	}

	long nIndex = m_List.GetNextItem(-1, LVNI_SELECTED);
	
	if(nIndex == -1)
		return;
	//BRANCHINFO *pBranch = NULL;
	//pBranch = (BRANCHINFO *)m_List.GetItemData(pNMLV->iItem);
	//if(pBranch == NULL)
	//	return;
 
	char buffer[20];
	
	m_nRiderCompany = (long)m_List.GetItemData(nIndex);
	m_nRider = _ttoi(m_List.GetItemText(nIndex, 3));

	m_edtSelectedCompanyName.SetWindowText(
		m_List.GetItemText(nIndex, 1) + "/" + m_List.GetItemText(nIndex, 2));

	m_edtRiderNO.SetWindowText(itoa(m_nRider, buffer, 10));
	m_edtRiderName.SetWindowText(m_List.GetItemText(nIndex, 4));
	
	*pResult = 0;
}

void CShareOrderAllocate3::OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//BRANCHINFO *pBranch = NULL;
	//pBranch = (BRANCHINFO *)m_List.GetItemData(pNMLV->iItem);
	//if(pBranch != NULL)
	//	delete pBranch;

	*pResult = 0;
}
