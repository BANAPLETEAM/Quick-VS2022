#include "StdAfx.h"
#include "Quick.h"
#include "TelserverDIDRouteDlg.h"
#include "MyCall.h"
#include "RcpView.h"
#include "RcpPageCTIForm.h"
#include "RcpDlgAdmin.h"

IMPLEMENT_DYNAMIC(CTelserverDIDRouteDlg, CMyDialog)
CTelserverDIDRouteDlg::CTelserverDIDRouteDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CTelserverDIDRouteDlg::IDD, pParent)
{
	m_bDIDRouteUse = FALSE;
}

CTelserverDIDRouteDlg::~CTelserverDIDRouteDlg()
{
	m_pCall->SetDIDRouteDlg(NULL);
}

void CTelserverDIDRouteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIDROUTE_REPORT_LIST, m_lstDIDRoute);

	DDX_Text(pDX, IDC_DIDROUTE_DID_EDIT, m_strDIDRouteDID);
	DDX_Text(pDX, IDC_DIDROUTE_TOLINE_EDIT, m_strDIDRouteLine);
	DDX_Text(pDX, IDC_DIDROUTE_DESC_EDIT, m_strDIDRouteDesc);
	DDX_Check(pDX, IDC_DIDROUTE_CHECK, m_bDIDRouteUse);
}


BEGIN_MESSAGE_MAP(CTelserverDIDRouteDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_DIDROUTE_REPORT_LIST, OnDIDRouteReportItemClick)
	ON_BN_CLICKED(IDC_DIDROUTE_ADD_BTN, OnBnClickedDIDRouteAddBtn)
	ON_BN_CLICKED(IDC_DIDROUTE_DELETE_BTN, OnBnClickedDIDRouteDeleteBtn)
	ON_BN_CLICKED(IDC_DIDROUTE_ALL_USE_BTN, OnBnClickedDIDRouteAllUseBtn)
	ON_BN_CLICKED(IDC_DIDROUTE_ALL_UNUSE_BTN, OnBnClickedDIDRouteAllUnuseBtn)
END_MESSAGE_MAP()

BOOL CTelserverDIDRouteDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_pCall = &(LU->GetRcpDlgAdmin()->m_pCTIForm->m_call);
	m_pCall->SetDIDRouteDlg(this);

	m_lstDIDRoute.InsertColumn(0, "���� DID", LVCFMT_CENTER, 80);
	m_lstDIDRoute.InsertColumn(1, "��ȯ ��ȣ", LVCFMT_CENTER, 100);
	m_lstDIDRoute.InsertColumn(2, "��� ����", LVCFMT_CENTER, 80);
	m_lstDIDRoute.InsertColumn(3, "����", LVCFMT_CENTER, 110);

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_DIDROUTE_DID_EDIT);
	pEdit->SetLimitText(8);

	SelectTelserverDIDRoute();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTelserverDIDRouteDlg::OnDIDRouteReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nRow >= 0)
	{
		CXTPGridRow *pRow = m_lstDIDRoute.GetRows()->GetAt(nRow);
		CXTPGridRecord *pRecord = (CXTPGridRecord*)pRow->GetRecord();

		m_strDIDRouteDID = m_lstDIDRoute.GetItemText(pRecord, 0);
		m_strDIDRouteLine = m_lstDIDRoute.GetItemText(pRecord, 1);
		m_bDIDRouteUse = m_lstDIDRoute.GetItemText(pRecord, 2) == "���" ? TRUE : FALSE;
		m_strDIDRouteDesc = m_lstDIDRoute.GetItemText(pRecord, 3);

		if(nCol == 2)
		{
			if(LF->POWER_CHECK(8121, "�ڼ�������ü���", TRUE))
			{
				if(!m_pCall->IsConnected())
					MessageBox("�ڼ����� ���ӵ��� �ʾ� ���� �Ͻ� �� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
				else
				{
					//m_bDIDRouteUse = !m_bDIDRouteUse;

					g_bana_log->Print("DIDROUTE_ADD List %s Use %d \n", m_strDIDRouteDID, !m_bDIDRouteUse);
					m_pCall->DIDRoute(DIDROUTE_ADD, m_strDIDRouteDID, m_strDIDRouteLine, !m_bDIDRouteUse, m_strDIDRouteDesc);
					CString strMsg;
					strMsg.Format("%s DID�� %s���� �ڼ����� ��û�Ͽ����ϴ�.", m_strDIDRouteDID, !m_bDIDRouteUse ? "���" : "�̻��");
					MessageBox(strMsg, "DID ���� ����", MB_ICONINFORMATION);
				}
			}
		}
	}

	UpdateData(FALSE);
}

void CTelserverDIDRouteDlg::OnBnClickedDIDRouteAddBtn()
{
	if(!LF->POWER_CHECK(8121, "�ڼ�������ü���", TRUE))
		return;

	if(!m_pCall->IsConnected())
	{
		MessageBox("�ڼ����� ���ӵ��� �ʾ� ���� �Ͻ� �� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	if(m_strDIDRouteDID.GetLength() <= 0)
		return;

	g_bana_log->Print("DIDROUTE_ADD Button %s Use %d \n", m_strDIDRouteDID, m_bDIDRouteUse);
	m_pCall->DIDRoute(DIDROUTE_ADD, m_strDIDRouteDID, m_strDIDRouteLine, m_bDIDRouteUse, m_strDIDRouteDesc);
	CString strMsg;
	strMsg.Format("%s DID�� %s���� �ڼ����� ��û�Ͽ����ϴ�.", m_strDIDRouteDID, m_bDIDRouteUse ? "���" : "�̻��");
	MessageBox(strMsg, "DID ���� ����", MB_ICONINFORMATION);
}

void CTelserverDIDRouteDlg::OnBnClickedDIDRouteDeleteBtn()
{
	if(!LF->POWER_CHECK(8121, "�ڼ�������ü���", TRUE))
		return;

	if(!m_pCall->IsConnected())
	{
		MessageBox("�ڼ����� ���ӵ��� �ʾ� ���� �Ͻ� �� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	UpdateData(TRUE);

	if(m_strDIDRouteDID.GetLength() <= 0)
		return;

	m_pCall->DIDRoute(DIDROUTE_DELETE, m_strDIDRouteDID);
	MessageBox("DID ���� ������ �ڼ����� ��û�Ͽ����ϴ�.", "DID ���� ����", MB_ICONINFORMATION);
}


void CTelserverDIDRouteDlg::OnBnClickedDIDRouteAllUseBtn()
{
	if(!LF->POWER_CHECK(8121, "�ڼ�������ü���", TRUE))
		return;

	if(!m_pCall->IsConnected())
	{
		MessageBox("�ڼ����� ���ӵ��� �ʾ� ���� �Ͻ� �� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	m_pCall->DIDRoute(DIDROUTE_ALL_USE, "");
	MessageBox("DID ���� ���� ����� �ڼ����� ��û�Ͽ����ϴ�.", "DID ���� ����", MB_ICONINFORMATION);
}

void CTelserverDIDRouteDlg::OnBnClickedDIDRouteAllUnuseBtn()
{
	if(!LF->POWER_CHECK(8121, "�ڼ�������ü���", TRUE))
		return;

	if(!m_pCall->IsConnected())
	{
		MessageBox("�ڼ����� ���ӵ��� �ʾ� ���� �Ͻ� �� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	m_pCall->DIDRoute(DIDROUTE_ALL_UNUSE, "");
	MessageBox("DID ���� ���� �̻���� �ڼ����� ��û�Ͽ����ϴ�.", "DID ���� ����", MB_ICONINFORMATION);
}

//DB �κ�

void CTelserverDIDRouteDlg::SelectTelserverDIDRoute()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_New_Telserver_DIDRoute");	
	cmd.AddParameter(m_ci.m_nCompanyCode);

	if(rs.Execute(&cmd))
	{
		CString strDID, strLine, strDesc;
		BOOL bUse;

		while(!rs.IsEOF())
		{
			rs.GetFieldValue("sDID" , strDID);
			rs.GetFieldValue("sLine", strLine);
			rs.GetFieldValue("sDesc", strDesc);
			rs.GetFieldValue("bUse", bUse);

			SuccessDIDRouteAdd(strDID, strLine, bUse, strDesc);
			rs.MoveNext();
		}
	}

	rs.Close();
	m_lstDIDRoute.Populate();
}

BOOL CTelserverDIDRouteDlg::SuccessDIDRouteAdd(CString strDID, CString strLine, BOOL bUse, CString strDesc)
{
	int nItemCount = -1, nSize = m_lstDIDRoute.GetRecords()->GetCount();
	CXTPGridRecord *pRecord;
	for(int i = 0 ; i < nSize ;i++)
	{
		pRecord = m_lstDIDRoute.GetRecords()->GetAt(i);

		if(m_lstDIDRoute.GetItemText(pRecord, 0) == strDID)
		{
			nItemCount = i;
			break;
		}
	}

	if(nItemCount == -1)
	{
		m_lstDIDRoute.InsertItem(nSize, strDID);
		nItemCount = nSize;
	}

	m_lstDIDRoute.SetItemText(nItemCount, 1, strLine);
	m_lstDIDRoute.SetItemText(nItemCount, 2, bUse ? "���" : "�̻��");
	m_lstDIDRoute.SetItemText(nItemCount, 3, strDesc);

	m_lstDIDRoute.Populate();

	return TRUE;
}

void CTelserverDIDRouteDlg::SuccessDIDRouteDelete(CString strDID)
{
	int nItemCount = -1, nSize = m_lstDIDRoute.GetRecords()->GetCount();
	CXTPGridRecord *pRecord;
	for(int i = 0 ; i < nSize ;i++)
	{
		pRecord = m_lstDIDRoute.GetRecords()->GetAt(i);

		if(m_lstDIDRoute.GetItemText(pRecord, 0) == strDID)
		{
			nItemCount = i;
			break;
		}
	}

	if(nItemCount != -1)
		pRecord->Delete();

	m_lstDIDRoute.Populate();
}

void CTelserverDIDRouteDlg::SuccessDIDRouteAllUse()
{
	int nItemCount = -1, nSize = m_lstDIDRoute.GetRecords()->GetCount();
	CXTPGridRecord *pRecord;
	for(int i = 0 ; i < nSize ;i++)
	{
		pRecord = m_lstDIDRoute.GetRecords()->GetAt(i);
		m_lstDIDRoute.SetItemText(pRecord, 2, "���");
	}

	m_lstDIDRoute.Populate();
}

void CTelserverDIDRouteDlg::SuccessDIDRouteAllUnuse()
{
	int nItemCount = -1, nSize = m_lstDIDRoute.GetRecords()->GetCount();
	CXTPGridRecord *pRecord;
	for(int i = 0 ; i < nSize ;i++)
	{
		pRecord = m_lstDIDRoute.GetRecords()->GetAt(i);
		m_lstDIDRoute.SetItemText(pRecord, 2, "�̻��");
	}

	m_lstDIDRoute.Populate();
}