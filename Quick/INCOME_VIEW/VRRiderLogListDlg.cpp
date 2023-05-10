// CVRRiderLogList.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "VRRiderLogListDlg.h"
#include ".\vrriderloglistdlg.h"


// CVRRiderLogListDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVRRiderLogListDlg, CMyDialog)
CVRRiderLogListDlg::CVRRiderLogListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVRRiderLogListDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_nRNo = 0;
	m_sAccount = "";
}

CVRRiderLogListDlg::~CVRRiderLogListDlg()
{
}

void CVRRiderLogListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_List);
	DDX_Text(pDX, IDC_ACCOUNT_EDIT, m_sAccount);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);	
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_RIDER_SELECT_COMBO, m_cmbRider);
	
}


BEGIN_MESSAGE_MAP(CVRRiderLogListDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ONOK_BTN, OnBnClickedOnokBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CVRRiderLogListDlg::OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CVRRiderLogListDlg �޽��� ó�����Դϴ�.

void CVRRiderLogListDlg::OnBnClickedOnokBtn()
{
	OnOK();
}

BOOL CVRRiderLogListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();
	m_cmbRider.SetCurSel(0);
	UpdateData();
	RefreshList2();

	return TRUE;
}

	
void CVRRiderLogListDlg::RefreshList2()
{
	try
	{
		UpdateData();
		COleDateTimeSpan dtSpan;
		dtSpan = m_dtTo - m_dtFrom;
		
		if(m_sAccount.GetLength() <= 0 && dtSpan.GetDays() > 187)
		{
			MessageBox("��ü�˻��� 6�ް������θ� ��ȸ�˴ϴ� ���� ������ ��������", "Ȯ��", MB_ICONINFORMATION);
			return;
		}

		if(m_List.GetRecords()->GetCount() > 0)
			m_List.DeleteAllItem();

	
		CString sAccount = m_sAccount;

		if(!IsStringDigit(sAccount))
		{
			MessageBox("���ڰ� �ƴմϴ�.", "Ȯ��", MB_ICONINFORMATION);
			return;
		}

		
		long nData = 0;
		if(m_cmbRider.GetCurSel() == 1 && m_sAccount.GetLength() > 5)
		{
			MessageBox("����ȣ�� ��ȿ�ѵ����Ͱ� �ƴմϴ�.", "Ȯ��", MB_ICONINFORMATION);
			return;
		}
		
		UpdateData();
		
		CMkRecordset pRs(m_pMkDb);					
		CMkCommand pCmd(m_pMkDb, "select_vraccount_rider_allotlog2");	
		
		pCmd.AddParameter( m_nCompany);		
		pCmd.AddParameter(m_nRNo);
		pCmd.AddParameter(m_sAccount);		
		pCmd.AddParameter(m_dtFrom);			
		pCmd.AddParameter(m_dtTo);			
		pCmd.AddParameter(m_cmbRider.GetCurSel());			

		if(!pRs.Execute(&pCmd)) return;

		int nIndex = 0;
		while(!pRs.IsEOF())
		{
			int nCol = 0, nType = 0;
			CString sAccount, sWID, sBankCode, sType;
			COleDateTime dtInput;
			long nOWnerCompany, nCompany, nRNo;

			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nRNo", nRNo);
			pRs.GetFieldValue("sAccount", sAccount);
			pRs.GetFieldValue("dtInput", dtInput);		
			pRs.GetFieldValue("sWID", sWID);			
			pRs.GetFieldValue("nOWnerCompany", nOWnerCompany);			
			pRs.GetFieldValue("BankCode", sBankCode);			
			pRs.GetFieldValue("nType", nType);			

			if(nType == 40)
				sType = "����ȸ��";
			else if(nType == 30)
				sType = "�����Ҵ�";
			else if(nType == 20)
				sType = "�ڵ��Ҵ�";


			m_List.MyAddItem(nCol++, nIndex, "No.", 35, FALSE, DT_CENTER);
			m_List.MyAddItem(nCol++, dtInput.Format("%Y-%m-%d %H:%M:%S"), "�۾���", 150, FALSE, DT_LEFT);
			m_List.MyAddItem(nCol++, m_ci.GetBranchName(nCompany), "�����", 90, FALSE, DT_LEFT);
			m_List.MyAddItem(nCol++, nRNo, "���", 45, FALSE, DT_LEFT);
			m_List.MyAddItem(nCol++, sType, "�۾�", 75, FALSE, DT_LEFT);
			m_List.MyAddItem(nCol++, sAccount, "����", 180, FALSE, DT_LEFT);
			m_List.MyAddItem(nCol++, nOWnerCompany ==  0 ? "��������" : "��ü����" , "����", 65, FALSE, DT_LEFT);
			m_List.MyAddItem(nCol++, sBankCode, "����", 80, FALSE, DT_LEFT);	
			m_List.MyAddItem(nCol++, sWID, "�۾���", 80, FALSE, DT_LEFT);	
			m_List.EndItem();

			nIndex++;
			pRs.MoveNext();
		}	
		m_List.Populate();
	}
	catch (char* e)
	{
		MessageBox(e, "Ȯ��", MB_ICONINFORMATION);
		
	}
}

void CVRRiderLogListDlg::OnBnClickedRefreshBtn()
{
	RefreshList2();
}
