// TransferRiderDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "TransferRiderDlg.h"


// CTransferRiderDlg ��ȭ �����Դϴ�.

#define WM_GET_ALLOCATE_RIDER WM_USER + 100

IMPLEMENT_DYNAMIC(CTransferRiderDlg, CMyDialog)

CTransferRiderDlg::CTransferRiderDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CTransferRiderDlg::IDD, pParent)
{
	m_nRiderCompany = 0;
	m_nRNo = 0;
	m_strRiderName = "";
}

CTransferRiderDlg::~CTransferRiderDlg()
{
}

void CTransferRiderDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_RNAME_EDIT, m_edtRName);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_btnRefresh);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_btnClose);
}


BEGIN_MESSAGE_MAP(CTransferRiderDlg, CMyDialog)
	ON_BN_CLICKED(IDC_TRANS_BUTTON, &CTransferRiderDlg::OnBnClickedTransButton)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CTransferRiderDlg::OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_SEARCH_RIDER_BTN, &CTransferRiderDlg::OnBnClickedSearchRiderBtn)
	ON_MESSAGE(WM_GET_ALLOCATE_RIDER, OnGetAllocateRider)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CTransferRiderDlg::OnBnClickedCloseBtn)
END_MESSAGE_MAP()


// CTransferRiderDlg �޽��� ó�����Դϴ�.

void CTransferRiderDlg::OnBnClickedTransButton()
{
	if(m_nRiderCompany <= ZERO ||
		m_nRNo <= ZERO)
	{
		MessageBox("������ �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CString strCharge; m_edtCharge.GetWindowText(strCharge);
	strCharge.Replace(",", "");

	if(_ttoi(strCharge) <= ZERO) 
	{
		MessageBox("��û�Ͻ� �ݾ��� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CString strTemp;
	strTemp.Format("%d�� %s���Կ��� %s���� ��ü��û �Ͻðڽ��ϱ�?", m_nRNo, m_strRiderName, LF->GetMyNumberFormat(_ttoi(strCharge)));

	if(MessageBox(strTemp, "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	CString strEtc; m_edtEtc.GetWindowText(strEtc);

	CMkCommand pCmd(m_pMkDb, "update_share_report_want_transfer_for_rider");
	pCmd.AddParameter(m_ci.m_nCompanyCode);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(_ttoi(strCharge));
	pCmd.AddParameter(strEtc);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	pCmd.AddParameter(m_strRiderName);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.strName);

	if(!pCmd.Execute())
		return;

	MessageBox("û�� ��û �Ͽ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
	RefreshList();	
}

BOOL CTransferRiderDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	LF->MakeModaless();
	CenterWindow();

	m_lstReport.InsertColumn(0, "��û��¥", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(1, "��û��ü", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "����", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(3, "�������", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(4, "��û�ݾ�", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(5, "�Աݳ�¥", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(6, "�����ݾ�", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(7, "�����޸�", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(8, "��ü����", LVCFMT_LEFT, 150);
	m_lstReport.Populate();


	RefreshList();
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTransferRiderDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CTransferRiderDlg::RefreshList()
{
	m_lstReport.DeleteAllItems();

    CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_transfer_my_request_for_rider");

    pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);

	if(!pRs.Execute(&pCmd)) return;

	CString sMemo, sReceiveMessage, strFormat, strTransferEtc, strToCompany;
	long nID, nToCompany, nRequestCharge, nReceiveCharge, nState;
    COleDateTime dtRequest, dtReceive;

	for(int i = 0 ; i < pRs.GetRecordCount(); i++)
	{ 
        pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nToCompany", nToCompany);
		pRs.GetFieldValue("sMemo", sMemo);
		pRs.GetFieldValue("dtRequest", dtRequest);
		pRs.GetFieldValue("nRequestCharge", nRequestCharge);
		pRs.GetFieldValue("dtReceive", dtReceive);
		pRs.GetFieldValue("nReceiveCharge", nReceiveCharge);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("sReceiveMessage", sReceiveMessage);
		pRs.GetFieldValue("sTransferEtc", strTransferEtc);
		pRs.GetFieldValue("sToCompany", strToCompany);


		m_lstReport.InsertItem(i, dtRequest.Format("%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, strToCompany);
		m_lstReport.SetItemText(i, 2, sMemo);
		m_lstReport.SetItemText(i, 3, ReturnType(nState));
		m_lstReport.SetItemText(i, 4, LF->GetMyNumberFormat(nRequestCharge));

		if(nState == 2 || nState == 4) //�������� 
		{
			m_lstReport.SetItemText(i, 5, dtReceive.Format("%m-%d %H:%M"));
			m_lstReport.SetItemText(i, 6, LF->GetMyNumberFormat(nReceiveCharge));
		}
		else
		{
			m_lstReport.SetItemText(i, 5, "");
			m_lstReport.SetItemText(i, 6, "");
		}

		m_lstReport.SetItemText(i, 7, sReceiveMessage);
		m_lstReport.SetItemText(i, 8, strTransferEtc);

		pRs.MoveNext();
	}

	m_lstReport.Populate();
}

void CTransferRiderDlg::OnBnClickedSearchRiderBtn()
{
	LU->OpenOtherAllocateDlg(0, 0, 0, 0, FALSE, this);
}

LONG CTransferRiderDlg::OnGetAllocateRider(WPARAM wParam, LPARAM lParam)
{	
	ST_RIDER_WORK_STATE_INFO *pInfo = (ST_RIDER_WORK_STATE_INFO*)wParam;

	m_nRiderCompany = pInfo->nCompany;
	m_nRNo = pInfo->nRNo;
	m_strRiderName = pInfo->strName;
	m_strCompanyName = pInfo->strCompanyName;

	delete pInfo;
	pInfo = NULL;

	char buffer[10];

	m_edtRNo.SetWindowText(CString(itoa(m_nRNo, buffer, 10)));
	m_edtCompany.SetWindowText(m_strCompanyName);
	m_edtRName.SetWindowText(m_strRiderName);	

	return 0;
}

CString CTransferRiderDlg::ReturnType(int nType)
{
	if(nType == 1)
		return "�Աݴ����";
	else if(nType == 2)
		return "�ԱݿϷ�";
	else if(nType == 4) //����ڰ���
		return "����";
	else
		return "�����ϰ��"; //3�� �������� ����Ͽ� �ڵ� ��� ��
}
void CTransferRiderDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(!m_lstReport.GetSafeHwnd())
		return;

	/*
	CRect rcDlg, rcList, rcRefreshBtn, rcCloseBtn;
	GetClientRect(rcDlg);

	m_btnRefresh.GetWindowRect(rcRefreshBtn);
	m_btnClose.GetWindowRect(rcCloseBtn);
	ScreenToClient(rcRefreshBtn);
	ScreenToClient(rcCloseBtn);



	m_lstReport.GetWindowRect(rcList);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 1;
	rcList.bottom = rcDlg.bottom - 1; 

	m_lstReport.MoveWindow(rcList);
	*/
}

BOOL CTransferRiderDlg::PreTranslateMessage(MSG* pMsg)
{
	

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CTransferRiderDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}
