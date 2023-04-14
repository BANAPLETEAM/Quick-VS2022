// AuthManageLog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "AuthManageLogDlg.h"



// CAuthManageLog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAuthManageLogDlg, CMyDialog)
CAuthManageLogDlg::CAuthManageLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAuthManageLogDlg::IDD, pParent)
{
}

CAuthManageLogDlg::~CAuthManageLogDlg()
{
}

void CAuthManageLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CAuthManageLogDlg, CMyDialog)
END_MESSAGE_MAP()


void CAuthManageLogDlg::Refresh()
{
	m_List.DeleteAllItems();

	int nRcpType = 10;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_auth_group_by_pc_log");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);

	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nRcpType);

	if(nRcpType == 100)
	{
		MessageBox("���ձ����� �����ϴ�", "Ȯ��", MB_ICONERROR);
		OnCancel();
	}
	else if(nRcpType == 1000)
	{
		MessageBox("������ �ƴմϴ�", "Ȯ��", MB_ICONERROR);
		OnCancel();
	}

	int nClientNo;
	COleDateTime dtFirst, dtLast, newdtLast, dtFinal;

	int count = 0;
	int frontClientNo, afterClientNo = 0;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nClientNo", nClientNo);
		pRs.GetFieldValue("dtFirstAuth", dtFirst);
		pRs.GetFieldValue("dtLastAuth", dtLast);
		pRs.GetFieldValue("newdtLastAuth", newdtLast);
		//pRs.GetFieldValue("dtWorkdate" , dtdate);
		pRs.GetFieldValue("dtFinalAuth", dtFinal);

		frontClientNo = nClientNo;

		CString sClientNo;
		sClientNo.Format("%d", nClientNo);

		if(newdtLast.GetYear() == -1)   // �� ������ �� ���� ���°��
		{
			if(count != 0)
				m_List.InsertItem(count++, "");

			m_List.InsertItem(count, sClientNo);
			m_List.SetItemText(count, 1, dtFirst.Format("%y-%m-%d %H:%M"));
			m_List.SetItemText(count, 2, dtLast.Format("%y-%m-%d %H:%M"));
			m_List.SetItemText(count, 3, dtFinal.Format("%y-%m-%d"));

		}
		else  //�� ������ ������ �ִ°��
		{
			if(frontClientNo == afterClientNo)  //���� ���� �ǽ� ��ȣ���� Ȯ��
			{
				m_List.InsertItem(count, "");
				m_List.SetItemText(count, 1, "");
				m_List.SetItemText(count, 2, newdtLast.Format("%y-%m-%d %H:%M"));
				m_List.SetItemText(count, 3, dtFinal.Format("%y-%m-%d"));
			}
			else
			{
				if(count != 0)
					m_List.InsertItem(count++, "");

				m_List.InsertItem(count, sClientNo);
				m_List.SetItemText(count, 1, dtFirst.Format("%y-%m-%d %H:%M"));
				m_List.SetItemText(count, 2, newdtLast.Format("%y-%m-%d %H:%M"));
				m_List.SetItemText(count, 3, dtFinal.Format("%y-%m-%d"));
			}
		}

		count++;

		afterClientNo = frontClientNo;

		pRs.MoveNext();   
		m_List.Populate();
	}


}

// CAuthManageLog �޽��� ó�����Դϴ�.

BOOL CAuthManageLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0, "PC��ȣ", LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, "��������", LVCFMT_LEFT, 95);
	m_List.InsertColumn(2, "����������", LVCFMT_LEFT, 95);
	m_List.InsertColumn(3, "����������", LVCFMT_LEFT, 95);

	m_List.Populate();
	Refresh();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
