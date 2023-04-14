#include "stdafx.h"
#include "resource.h"
#include "AllocateGroupNew.h"


// CAllocateGroupNew ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAllocateGroupNew, CMyDialog)
CAllocateGroupNew::CAllocateGroupNew(CWnd* pParent /*=NULL*/)
: CMyDialog(CAllocateGroupNew::IDD, pParent)
, m_sGNo("")
, m_sName("")
{
}

CAllocateGroupNew::~CAllocateGroupNew()
{
}

void CAllocateGroupNew::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_EDIT, m_sName);
	DDX_Text(pDX, IDC_GNO_EDIT, m_sGNo);
//	DDX_Control(pDX, IDC_GNO_EDIT, m_sName);
}


BEGIN_MESSAGE_MAP(CAllocateGroupNew, CMyDialog)
	ON_BN_CLICKED(IDC_OK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DEL, &CAllocateGroupNew::OnBnClickedDel)
END_MESSAGE_MAP()


// CAllocateGroupNew �޽��� ó�����Դϴ�.
BOOL CAllocateGroupNew::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(bNewMode)
	{
		SetWindowText("���� �׷�� �߰�");
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_allocate_gno");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
		if(!pRs.Execute(&pCmd)) return FALSE;

		if(!pRs.IsEOF())
		{
			int nGNo;
			CString sName;

			pRs.GetFieldValue("nGNo", nGNo);
			m_sGNo.Format("%d", nGNo);

			UpdateData(FALSE);
		}
		pRs.Close();
	}
	else
	{
		SetWindowText("���� �׷�� ����");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CAllocateGroupNew::OnBnClickedOk()
{
	if(bNewMode)
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb,"insert_allocate_group");
		UpdateData(TRUE);

		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(m_sGNo));
		pCmd.AddParameter(typeString, typeInput, m_sName.GetLength(), m_sName);

		if(pCmd.Execute())
		{
			MessageBox("�����׷��� �߰��Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
			OnOK();
		}
		else {
			MessageBox("�����׷� ������ �����Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);	
			OnCancel();
		}
	}
	else
	{
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb,"update_allocate_group");
		UpdateData(TRUE);

		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(m_sGNo));
		pCmd.AddParameter(typeString, typeInput, m_sName.GetLength(), m_sName);

		if(pCmd.Execute())
		{
			LU->UpdateAllocateGroup(atoi(m_sGNo), m_sName);
			MessageBox("�����׷��� �����Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
			OnOK();
		}
		else {
			MessageBox("�����׷� ������ �����Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);	
			OnCancel();
		}
	}
}

void CAllocateGroupNew::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();	
}

void CAllocateGroupNew::OnBnClickedDel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
