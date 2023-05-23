// ReceiveMoneyDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ReceiveMoneyDlg.h"



// CReceiveMoneyDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CReceiveMoneyDlg, CMyDialog)
CReceiveMoneyDlg::CReceiveMoneyDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CReceiveMoneyDlg::IDD, pParent)
{
}

CReceiveMoneyDlg::~CReceiveMoneyDlg()
{
	m_bIntegrated = FALSE;
	m_nCompany = 0;
}

void CReceiveMoneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1,	m_wndReport);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_From);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_To);	
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);	
	DDX_Control(pDX, IDC_STATIC1, m_Stc1);
	DDX_Control(pDX, IDC_COMPANY_COMBO, m_cmbCompany);
}


BEGIN_MESSAGE_MAP(CReceiveMoneyDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_CBN_SELCHANGE(IDC_COMPANY_COMBO, OnCbnSelchangeCompanyCombo)
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CReceiveMoneyDlg �޽��� ó�����Դϴ�.

void CReceiveMoneyDlg::OnBnClickedSearchBtn()
{
	RefreshList();
}

BOOL CReceiveMoneyDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CBranchInfo *pBi = NULL;
	if(m_bIntegrated)
	{
		int nCurSel = 0;
		int nItem = 0;
		BOOL bIntegrated =FALSE;

		for(int i = 0; i < m_ba.GetCount(); i++) {
			pBi = m_ba.GetAt(i);
			if(pBi->bIntegrated)
			{
				
				m_cmbCompany.InsertString(nItem,"����");
				m_cmbCompany.SetItemData(nItem,pBi->nCompanyCode); // �ݾ����̺�����
			
			}
			else
			{
				if(m_nCompany == pBi->nCompanyCode)
					nCurSel = nItem;

				m_cmbCompany.InsertString(nItem,pBi->strBranchName);
				m_cmbCompany.SetItemData(nItem,pBi->nCompanyCode); // �ݾ����̺�����
			}
			nItem++;
		}
		m_cmbCompany.SetCurSel(nCurSel);
	}
	else
	{
		pBi = m_ba.GetAt(0);
		m_cmbCompany.InsertString(0,pBi->strBranchName );
		m_cmbCompany.SetItemData(0,m_nCompany);
		m_cmbCompany.SetCurSel(0);
	}

	m_DateBtn.InitDateButton(&m_dtFrom, &m_dtTo);
	m_DateBtn.OnMenuToday();
	m_wndReport.InsertColumn(0, "�����", DT_LEFT, 90, FALSE);
	m_wndReport.InsertColumn(1, "�Ա���", DT_LEFT, 90, FALSE);
	m_wndReport.InsertColumn(2, "�Աݾ�", DT_RIGHT, 80, FALSE);
	m_wndReport.InsertColumn(3, "��ݾ�", DT_RIGHT, 80, FALSE);
	m_wndReport.InsertColumn(4, "�Աݻ���", DT_LEFT, 70, FALSE);
	m_wndReport.InsertColumn(5, "�ΰ���", DT_RIGHT, 50, FALSE);
	m_wndReport.InsertColumn(6, "ȸ��/�μ�", DT_LEFT, 80, FALSE);
	m_wndReport.InsertColumn(7, "�����", DT_LEFT, 60, FALSE);
	m_wndReport.InsertColumn(8, "��ȭ", DT_LEFT, 80, FALSE);
	m_wndReport.InsertColumn(9, "���", DT_LEFT, 150, FALSE);

	
	RefreshList();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
void CReceiveMoneyDlg::RefreshList()
{

	
	m_wndReport.GetRecords()->RemoveAll();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_creditcard_settlepay_list");

	COleDateTime dtFrom, dtTo;

	m_dtFrom.GetTime(dtFrom);
	m_dtTo.GetTime(dtTo);
	CString sFromDate , sToDate;
	sFromDate = dtFrom.Format("%Y-%m-%d");
	sToDate = dtTo.Format("%Y-%m-%d");

	pCmd.AddParameter( m_nCompany);	
	pCmd.AddParameter( m_bIntegrated);	
	pCmd.AddParameter( 0);
	pCmd.AddParameter(sFromDate);
	pCmd.AddParameter(sToDate);
	


	if(!pRs.Execute(&pCmd)) return;

	long nCardPaySeq, nAmount, nTax, nCNo,nGNo, nType;
	BOOL bAdd;
	
	CString sTel1,sName, sDepart, sCompany, sEtc, sCompanyDepart, strBranchName;
	COleDateTime dtInput, dtCanceldate; 

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nCardPaySeq", nCardPaySeq);
		pRs.GetFieldValue("nAmount", nAmount);
		pRs.GetFieldValue("nTax", nTax);
		pRs.GetFieldValue("nCNo", nCNo);
		
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("bAdd", bAdd);

		pRs.GetFieldValue("sTel1", sTel1);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("sDepart", sDepart);
		pRs.GetFieldValue("sCompany", sCompany);
		pRs.GetFieldValue("sEtc", sEtc);
		pRs.GetFieldValue("dtInput", dtInput);
		pRs.GetFieldValue("dtCanceldate", dtCanceldate);
		pRs.GetFieldValue("sBranchName", strBranchName);


		if(sCompany.GetLength() > 0)
			sCompanyDepart = sCompany;
		if(sDepart.GetLength() > 0 )
		{
			if(sCompanyDepart.GetLength() > 0)
				sCompanyDepart += "/" + sDepart;
			else
                sCompanyDepart += sDepart;
		}		

		
		m_wndReport.MyAddItem(strBranchName);
		m_wndReport.MyAddItem(dtInput.Format("%y-%m-%d %H:%M"));
		m_wndReport.MyAddItem(bAdd? LF->GetMyNumberFormat(nAmount) : "");
		m_wndReport.MyAddItem(bAdd? "" : LF->GetMyNumberFormat(nAmount));
		m_wndReport.MyAddItem(GetSettleType(nType));
		m_wndReport.MyAddItem(LF->GetMyNumberFormat(nTax));
		m_wndReport.MyAddItem(sCompanyDepart);
		m_wndReport.MyAddItem(sName);
		m_wndReport.MyAddItem(LF->GetDashPhoneNumber(sTel1));
		m_wndReport.MyAddItem(sEtc);
		m_wndReport.EndItem();		

		pRs.MoveNext();
	}

	pRs.Close();
	m_wndReport.Populate();
}


CString CReceiveMoneyDlg::GetSettleType(int nType) 
{
	CString strType = "";

	switch(nType)
	{
	case 0:
		strType = "�ſ�ī��";
		break;
	case 1:
		strType = "�¶��μ۱�";
		break;
	case 2:
		strType = "��簡�����";
	    break;
	case 3:
		strType = "";
	    break;
	
	}
	return strType;

}
void CReceiveMoneyDlg::OnCbnSelchangeCompanyCombo()
{
	m_nCompany = m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	m_bIntegrated = m_cmbCompany.GetCurSel() == 0 ? TRUE : FALSE;
	RefreshList();
}

void CReceiveMoneyDlg::OnMove(int x, int y)
{
	CMyDialog::OnMove(x, y);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
