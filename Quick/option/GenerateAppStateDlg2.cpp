// EtcDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Resource.h"
#include "GenerateAppStateDlg2.h"
#include "GeneralAppRegisterDlg2.h"


// CGenerateAppStateDlg2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGenerateAppStateDlg2, CMyDialog)

CGenerateAppStateDlg2::CGenerateAppStateDlg2(CWnd* pParent /*=NULL*/)
: CMyDialog(CGenerateAppStateDlg2::IDD, pParent)
{
}

CGenerateAppStateDlg2::~CGenerateAppStateDlg2()
{
}

void CGenerateAppStateDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_lstReport);
}


BEGIN_MESSAGE_MAP(CGenerateAppStateDlg2, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, OnBnClickedAddBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_CTRL, OnReportItemDbClick)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGenerateAppStateDlg2 �޽��� ó�����Դϴ�.

void CGenerateAppStateDlg2::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CGenerateAppStateDlg2::RefreshList()
{
	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_generate_app_register_2");
	cmd.AddParameter(m_ci.GetShareCode1());

	if(!rs.Execute(&cmd))
		return;

	long nIndex, nAppRegisterCompany, nState, nType;
	CString strAppName, strBizNumber, strMainTel, strShortUrl, strGoogleID, strGooglePW;
	COleDateTime dtUserRegister, dtAppRegister;
	CString strAppleID, strApplePW;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nIndex", nIndex);
		rs.GetFieldValue("nAppRegisterCompany", nAppRegisterCompany);
		rs.GetFieldValue("nState", nState); 
		rs.GetFieldValue("sAppName", strAppName);
		rs.GetFieldValue("sBizNumber", strBizNumber);
		rs.GetFieldValue("sMainTel", strMainTel);
		rs.GetFieldValue("sShortUrl", strShortUrl);
		rs.GetFieldValue("dtUserRegister", dtUserRegister);
		rs.GetFieldValue("dtAppRegister", dtAppRegister);
		rs.GetFieldValue("sGoogleID", strGoogleID);
		rs.GetFieldValue("sGooglePW", strGooglePW);
		rs.GetFieldValue("sAppleID", strAppleID);
		rs.GetFieldValue("sApplePW", strApplePW);
		rs.GetFieldValue("nType", nType);

		if(nAppRegisterCompany == 0)
			m_lstReport.InsertItem(i, "");
		else
			m_lstReport.InsertItem(i, m_ci.GetBranchName(nAppRegisterCompany));

		m_lstReport.SetItemText(i, 1, strAppName);


		CString strTemp = "";
		if(nState == 1) strTemp = "��û��";
		else if(nState == 2) strTemp = "����";

		m_lstReport.SetItemText(i, 2, strTemp);
		m_lstReport.SetItemText(i, 3, strBizNumber);
		m_lstReport.SetItemText(i, 4, dtUserRegister.Format("%y-%m-%d %H:%M"));

		if(dtAppRegister.m_status != 2)
			m_lstReport.SetItemText(i, 5, dtAppRegister.Format("%y-%m-%d %H:%M"));
		else
			m_lstReport.SetItemText(i, 5, "");

		m_lstReport.SetItemText(i, 6, LF->GetDashPhoneNumber(strMainTel));
		m_lstReport.SetItemText(i, 7, strShortUrl);
		m_lstReport.SetItemText(i, 8, strGoogleID);
		m_lstReport.SetItemText(i, 9, strGooglePW);
		m_lstReport.SetItemText(i, 10, strAppleID);
		m_lstReport.SetItemText(i, 11, strApplePW);

		CString strTemp1 = "";

		if(nType == 0)
			strTemp1 = "�ȵ���̵�";
		else if(nType == 1)
			strTemp1 = "IOS";
		else if(nType == 2)
			strTemp1 = "�ȵ���̵�+IOS";

		m_lstReport.SetItemText(i, 12, strTemp1);
		m_lstReport.SetItemLong(i, nIndex);

		rs.MoveNext();		
	}

	m_lstReport.Populate();
}

BOOL CGenerateAppStateDlg2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "�۵������", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(1, "���̸�", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(2, "����", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(3, "����ڵ����", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(4, "��û��", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(5, "�۵����", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(6, "��ǥ��ȣ", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(7, "����URL", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(8, "����ID", LVCFMT_LEFT, 78);
	m_lstReport.InsertColumn(9, "����PW", LVCFMT_LEFT, 78);
	m_lstReport.InsertColumn(10, "����ID", LVCFMT_LEFT, 78);
	m_lstReport.InsertColumn(11, "����PW", LVCFMT_LEFT, 78);
	m_lstReport.InsertColumn(12, "Ÿ��", LVCFMT_LEFT, 78);

	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGenerateAppStateDlg2::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridRecord *pRecord = GetFirstSelectRecord();

	if(pRecord == NULL)
		return;

	long nIndex = m_lstReport.GetItemLong(pRecord);

	CGeneralAppRegisterDlg2 dlg;
	dlg.m_nIndex =	nIndex;

	if(dlg.DoModal() == IDOK)
		RefreshList();
}

void CGenerateAppStateDlg2::OnBnClickedAddBtn()
{
	CGeneralAppRegisterDlg2 dlg;
	dlg.m_nIndex = 0;

	if(dlg.DoModal() == IDOK)
		RefreshList();
}
void CGenerateAppStateDlg2::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd() != NULL)
	{
		CRect rc;
		m_lstReport.GetWindowRect(rc);
		ScreenToClient(rc);

		rc.right = cx - 5;
		rc.bottom = cy - 5;

		m_lstReport.MoveWindow(rc, TRUE);
	}
}

CXTPGridRecord* CGenerateAppStateDlg2::GetFirstSelectRecord()
{
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	if(pRows == NULL) return NULL;
	if(pRows->GetCount() == 0) return NULL;

	return pRows->GetAt(0)->GetRecord();
}