// PenaltySetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "PenaltySetDlg.h"
#include "MainFrm.h"

#define CANCEL_COUNT			24

char *szCancelTitle[] = {
			"전화불통",
			" ",
			"시간지연",
			" ",
			"배달지이상",
			" ",
			"물건크기불량",
			" ",
			"취급불가물건",
			" ",
			"고객없음",
			" ",
			"복수콜 일부취소",
			" ",
			"기사부족",
			" ",
			"연습오더",
			" ",
			"고객본인취소",
			" ",
			"배차실수",
			" ",
			"기타"
			" "
};

// CPenaltySetDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPenaltySetDlg, CMyDialog)
CPenaltySetDlg::CPenaltySetDlg(long nCompanyCode, CWnd* pParent /*=NULL*/)
	: CMyDialog(CPenaltySetDlg::IDD, pParent)
	
{
	m_nAmount = 0;
	m_nCompanyCode = nCompanyCode;
}

CPenaltySetDlg::~CPenaltySetDlg()
{

}

void CPenaltySetDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_AMOUNT_EDIT, m_nAmount);
	DDV_MinMaxLong(pDX, m_nAmount, 0, LONG_MAX);
	DDX_Control(pDX, IDC_ALL_APPLY_COMPANY_BUTTON, m_btnIntegrated);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranchCombo);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
	DDX_Control(pDX, IDC_ALL_NOT_BUTTON, m_AllNotButton);
	DDX_Control(pDX, IDC_ALL_NOT_BUTTON2, m_AllNotButton2);
	DDX_Control(pDX, IDC_ALL_AMOUNT_BUTTON, m_AllAmountButton);
	DDX_Control(pDX, IDC_AMOUNT_EDIT, m_AmountEdit);
	DDX_Control(pDX, IDC_COPY_BUTTON, m_CopyButton);
	DDX_Control(pDX, IDC_OK_BTN, m_OkBtn);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_CancelBtn);

}


BEGIN_MESSAGE_MAP(CPenaltySetDlg, CMyDialog)	
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_COPY_BUTTON, OnBnClickedCopyButton)
	ON_BN_CLICKED(IDC_ALL_NOT_BUTTON, OnBnClickedAllNotButton)
	ON_BN_CLICKED(IDC_ALL_AMOUNT_BUTTON, OnBnClickedAllAmountButton)
	ON_BN_CLICKED(IDC_ALL_NOT_BUTTON2, OnBnClickedAllNotButton2)
	ON_BN_CLICKED(IDC_ALL_APPLY_COMPANY_BUTTON, OnBnClickedAllApplyCompanyButton)
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, OnCbnSelchangeBranchCombo)
END_MESSAGE_MAP()


// CPenaltySetDlg 메시지 처리기입니다.

BOOL CPenaltySetDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	InitControl();
	RefreshList();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CPenaltySetDlg::OnBnClickedOk()
{
	
	CWaitCursor cusor;
	int nRow = 0;
	long	nReleaseMin[6];
	long	nForfeit[6];
	
	for(int m=0; m<6; m++)
	{
		nReleaseMin[m] = 0;
		nForfeit[m] = 0;
	}

	for(int i = 0; i< m_List.GetItemCount(); i+=2)
	{
		CMkCommand pCmd(m_pMkDb, "update_company_panalty_apply");		
		BOOL bInit = TRUE;
		for(int j= i; j< i+2; j++)
		{		
			for(int k = 3; k < 8; k++){
				bInit ? nReleaseMin[k-3] = atol(m_List.GetItemText(j,k)):
						nForfeit[k-3] = atol(m_List.GetItemText(j,k));
			
			}
			bInit = bInit ?  FALSE : TRUE;									
		}
		
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompanyCode);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bIntegrated);	
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nRow);			
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nReleaseMin[0]);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nReleaseMin[1]);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nReleaseMin[2]);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nReleaseMin[3]);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nReleaseMin[4]);		
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nForfeit[0]);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nForfeit[1]);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nForfeit[2]);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nForfeit[3]);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nForfeit[4]);	       	      

		nRow++;
		pCmd.Execute();
	}

	MessageBox("적용하였습니다.", "확인", MB_ICONINFORMATION);
	OnOK();
}

void CPenaltySetDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CPenaltySetDlg::OnBnClickedAllApplyCompanyButton()
{
	//if(m_bIntegrated == 0) return;
	if(m_cmbBranchCombo.GetCount() <= 1)
	{
		MessageBox("전체적용이 적용되지 않았습니다.","확인", MB_ICONINFORMATION);
		return;
	}
	else
	{
		CBranchInfo *pBi;
		long nCompany = 0;
		pBi = (CBranchInfo*)m_cmbBranchCombo.GetItemData(0);
		
		m_bIntegrated = 1;
		m_nCompanyCode = pBi->nCompanyCode ;
	}
	OnBnClickedOk();

}
void CPenaltySetDlg::InitControl(void)
{
	CRect ClientRect;
    GetClientRect(&ClientRect);
    
	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.ModifyStyle(NULL, LVS_EX_CHECKBOXES |LVS_EDITLABELS | LVS_REPORT);
    m_List.SetExtendedStyle(LVS_EX_GRIDLINES);
    m_List.InsertColumn(0, "순서");
    m_List.InsertColumn(1, "취소사유");
	m_List.InsertColumn(2, "적용방법");
	m_List.InsertColumn(3, " 1 회 ",LVCFMT_RIGHT);
	m_List.InsertColumn(4, " 2 회 ",LVCFMT_RIGHT);
	m_List.InsertColumn(5, " 3 회 ",LVCFMT_RIGHT);
	m_List.InsertColumn(6, " 4 회 ",LVCFMT_RIGHT);
	m_List.InsertColumn(7, " 5 회 이상 ",LVCFMT_RIGHT);

    m_List.SetColumnWidth(0, 40);
    m_List.SetColumnWidth(1, 110);
	m_List.SetColumnWidth(2, 70);
	m_List.SetColumnWidth(3, 60);
	m_List.SetColumnWidth(4, 60);
	m_List.SetColumnWidth(5, 60);
	m_List.SetColumnWidth(6, 60);
	m_List.SetColumnWidth(7, 100);

	m_List.SetDisableCol(0);
	m_List.SetDisableCol(1);
	m_List.SetDisableCol(2);

	char buffer[10];
	BOOL bTime = FALSE;
	int nCount = 1;
	for(int i = 0; i < CANCEL_COUNT; i++)
	{
		m_List.InsertItem(i,bTime ? "  ": itoa(nCount++,buffer,10) );
		m_List.SetItemText(i,1,szCancelTitle[i]);
		m_List.SetItemText(i,2,bTime ?"벌금(원)":"시간(분)");

		bTime = bTime ? FALSE : TRUE;

	}


/*
	if(m_bIntegrated)
	{		
		int nItem = 0;
		for(int i = 0; i < m_ba.GetCount(); i++) {
			CBranchInfo *pBi = m_ba.GetAt(i);			
			if(pBi->strBranchName == "통합")
				continue;

			m_cmbBranchCombo.InsertString(nItem,pBi->strBranchName);
			m_cmbBranchCombo.SetItemData(nItem++,(DWORD_PTR)pBi);			
			
		}
	}
	else
	{
		CBranchView *pBranchView = ((CMainFrame*)AfxGetMainWnd())->m_pBranchView;
		CBranchInfo *pBi = m_ba.GetAt(pBranchView->GetCurrentBranch());
		m_cmbBranchCombo.InsertString(0,pBi->strBranchName);
		m_cmbBranchCombo.SetItemData(0,(DWORD_PTR)pBi);
	}
	

	for(int i=0; m_cmbBranchCombo.GetCount(); i++)
	{
		CBranchInfo *pBi = (CBranchInfo*)m_cmbBranchCombo.GetItemData(i);
		if(pBi->nCompanyCode == m_nCompanyCode)
		{	
			m_cmbBranchCombo.SetCurSel(i);
			break;			
		}
	}

	if(m_bIntegrated)
		m_btnIntegrated.EnableWindow(TRUE);
*/
//아래로 대치함

	if(m_ba.GetCount() > 1) {
		for(int i = 0; i < m_ba.GetCount(); i++) {
			CBranchInfo *pBi = m_ba.GetAt(i);
			if(pBi->strBranchName == "통합")
				continue;
			int nItem = m_cmbBranchCombo.AddString(pBi->strBranchName);
			m_cmbBranchCombo.SetItemData(nItem, (DWORD)pBi);

			if(m_nCompanyCode == pBi->nCompanyCode)
				m_cmbBranchCombo.SetCurSel(nItem);
		}
	}
	else {
		m_cmbBranchCombo.AddString("");
		m_cmbBranchCombo.SetItemData(0, m_ci.m_nCompanyCode);
	}

	//m_cmbBranchCombo.SetCurSel(0);

	if(m_cmbBranchCombo.GetCount() > 0)
		m_btnIntegrated.EnableWindow(TRUE);
}

void CPenaltySetDlg::RefreshList(void)
{
	CMkCommand pCmd(m_pMkDb, "select_driver_cancel_settime");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompanyCode);	
	CMkRecordset pRs(m_pMkDb);
	pRs.Execute(&pCmd);

	int nCount = 0;
	char buffer[30];
	int nCancelType;
	int nPreCancelType = -1;

	if(pRs.GetRecordCount() > 0)
	{
		while(!pRs.IsEOF()) {

			long nCompany;
			int	nReleaseMin[5];
			int nForfeit[5];
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nCancelCount", nCancelType);
			pRs.GetFieldValue("nReleaseMin", nReleaseMin[0]);
			pRs.GetFieldValue("nReleaseMin2", nReleaseMin[1]);
			pRs.GetFieldValue("nReleaseMin3", nReleaseMin[2]);
			pRs.GetFieldValue("nReleaseMin4", nReleaseMin[3]);
			pRs.GetFieldValue("nReleaseMin5", nReleaseMin[4]);

			pRs.GetFieldValue("nForfeit",  nForfeit[0]);
			pRs.GetFieldValue("nForfeit2", nForfeit[1]);
			pRs.GetFieldValue("nForfeit3", nForfeit[2]);
			pRs.GetFieldValue("nForfeit4", nForfeit[3]);
			pRs.GetFieldValue("nForfeit5", nForfeit[4]);

				
			
			for(int i = 3; i < 9; i++)
				m_List.SetItemText(nCount, i,itoa(nReleaseMin[i-3],buffer,10));

			nCount++;

			for(int j = 3; j < 9; j++)
				m_List.SetItemText(nCount, j,itoa(nForfeit[j-3],buffer,10));
	
			nCount++;

			pRs.MoveNext();
		}
	}

	pRs.Close();
}



void CPenaltySetDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}


void CPenaltySetDlg::OnBnClickedCopyButton()
{
	for(int i = 0; i< m_List.GetItemCount(); i++)
	{
		for(int j=4; j<8; j++)
			m_List.SetItemText(i,j,m_List.GetItemText(i,3));		
	}
}

void CPenaltySetDlg::OnBnClickedAllNotButton()
{
	BOOL bTime = TRUE;
	for(int i=0;i < m_List.GetItemCount(); i++)
	{
		if(bTime)
		{
			for(int j=3; j<8; j++)
				m_List.SetItemText(i,j,"1000");
		}
		else
		{
			for(int j=3; j<8; j++)
				m_List.SetItemText(i,j,"0");
		}
		bTime = bTime ? FALSE : TRUE;
	}


}

void CPenaltySetDlg::OnBnClickedAllAmountButton()
{
	UpdateData(TRUE);
	BOOL bTime = TRUE;
	char buffer[10];
	for(int i=1; i < m_List.GetItemCount(); i+=2)
	{		
		for(int j=3; j<8; j++)
			m_List.SetItemText(i,j,ltoa(m_nAmount,buffer,10) );
	
	}
}

void CPenaltySetDlg::OnBnClickedAllNotButton2()
{
	for(int i = 0; i < m_List.GetItemCount(); i++)
		for(int j=4; j<8; j++)
			m_List.SetItemText(i,j,"0");
}


void CPenaltySetDlg::OnCbnSelchangeBranchCombo()
{
	CBranchInfo *pBi = (CBranchInfo*)m_cmbBranchCombo.GetItemData(
		m_cmbBranchCombo.GetCurSel());

	m_nCompanyCode = pBi->nCompanyCode;
	m_bIntegrated = 0;
	RefreshList();

}
