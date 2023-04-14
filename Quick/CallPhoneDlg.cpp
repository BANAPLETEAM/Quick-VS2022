// CallPhoneDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CallPhoneDlg.h"
#include "RcpView.h"

// CCallPhoneDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCallPhoneDlg, CMyDialog)
CCallPhoneDlg::CCallPhoneDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCallPhoneDlg::IDD, pParent)
{
	m_nOrderCompany = 0;
}

CCallPhoneDlg::~CCallPhoneDlg()
{
}

void CCallPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CCallPhoneDlg, CMyDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CCallPhoneDlg �޽��� ó�����Դϴ�.

#define INSERT_CALL_NUMBER(x, title)  \
		if(x.GetLength() > 0)\
		{\
			m_List.InsertItem(nItem, title);\
			m_List.SetItemText(nItem++, 1, GetDashPhoneNumber(x));\
		}

BOOL CCallPhoneDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0, "���", LVCFMT_LEFT, 150);
	m_List.InsertColumn(1, "��ȭ��ȣ", LVCFMT_LEFT, 170);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCallPhoneDlg::RefreshList()
{
	m_List.DeleteAllItems();

	//m_strDeviceID.Replace("82", "0");

	if(m_strDeviceID.Left(2) == "82")
		m_strDeviceID = m_strDeviceID.Right(m_strDeviceID.GetLength() - 2);

	m_strDeviceID.Replace("+", "");
	m_strDeviceID.Replace("B", "");
	m_strDeviceID.Replace("C", "");

	long nItem = 0;
	INSERT_CALL_NUMBER(m_strPhone, "���� �޴���");
	INSERT_CALL_NUMBER(m_strDeviceID, "���� PDA");
	INSERT_CALL_NUMBER(m_strHomePhone, "���� ����ȭ");
	INSERT_CALL_NUMBER(m_strCompanyPhone, "���Ҽ�ȸ�� ��ǥ��ȣ");
	INSERT_CALL_NUMBER(m_strOfficePhone, "���Ҽ�ȸ�� ��Ȳ��");
}

void CCallPhoneDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem < 0) return;

	m_pRcpView->MakeCall(m_nOrderCompany, GetNoneDashNumber(m_List.GetItemText(nItem, 1)), TRUE);

	*pResult = 0;
}


void CCallPhoneDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}
