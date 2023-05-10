// WebIDPWDDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "WebIDPWDDlg.h"
#include "CustomerSmsDlg2.h"
#include "RcpPlaceInfo.h"
#include "CustomerDlg.h"
#include "RcpDlg.h"

// CWebIDPWDDlg ��ȭ �����Դϴ�.

#define  NO_MEMBER 20
#define  MEMBER 10

IMPLEMENT_DYNAMIC(CWebIDPWDDlg, CMyDialog)

CWebIDPWDDlg::CWebIDPWDDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWebIDPWDDlg::IDD, pParent)
{
	Clear();
}

//
//CWebIDPWDDlg::CWebIDPWDDlg()
//: CMyDialog(CWebIDPWDDlg::IDD)
//{
//	Clear();
//}

CWebIDPWDDlg::~CWebIDPWDDlg()
{
}

void CWebIDPWDDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TNO_ID_EDIT, m_strWebID);
	DDX_Control(pDX, IDC_TNO_ID_EDIT, m_edtWebID);

	DDX_Text(pDX, IDC_TNO_PWD_EDIT, m_strWebPWD);
	DDX_Control(pDX, IDC_TNO_PWD_EDIT, m_edtWebPWD);

	DDX_Text(pDX, IDC_TNO_EDIT, m_nTNo);
	DDX_Control(pDX, IDC_TNO_EDIT, m_edtTNo);

	

	
}




BEGIN_MESSAGE_MAP(CWebIDPWDDlg, CMyDialog)
	ON_BN_CLICKED(IDC_WEB_SITE_WINDOW_BTN, OnBnClickedWebSiteWindow)
	ON_BN_CLICKED(IDC_NOMEMBER_SMS_PWD_BTN, OnBnClickedNomemberSendSMS)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancel)
END_MESSAGE_MAP()




// CWebIDPWDDlg �޽��� ó�����Դϴ�.
//�޽��� ó�����Դϴ�.

BOOL CWebIDPWDDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CWebIDPWDDlg::Clear()
{
	m_nTNo		= 0;
	m_nCompany	= 0;
	m_nCNo		= 0;
	m_nType		= 0;

	m_strWebID	= "";
	m_strWebPWD = "";
	m_strPhone	= "";
	m_strWebAddress = "";
}


BOOL CWebIDPWDDlg::CheckData()
{
	try
	{
		if(m_nTNo <= 100)
			throw "���� ��ȣ�� �����ϴ�. ";

		if(m_nCompany <= 1)
			throw "ȸ�� ������ �����ϴ� ";


		return TRUE;
	}
	catch (char *cMsg)
	{
		MessageBox(cMsg, "Ȯ��",MB_ICONINFORMATION);
		return FALSE;
	}
	catch (CString str)
	{
		MessageBox(str, "Ȯ��",MB_ICONINFORMATION);
		return FALSE;
	}
	

	return TRUE;
}

void CWebIDPWDDlg::OnBnClickedWebSiteWindow()
{
	if( !CheckData() ) return;

	
	
	
	if(m_strWebAddress.GetLength() <= 6)
	{
		MessageBox("��ϵ� ���ּҰ� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);

		return;

	}

	CString str, strForm;
	str = "C:\\Program Files\\Internet Explorer\\iexplore.exe";

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;

	//	if(!strArg.IsEmpty())

	strForm = " http://" +m_strWebAddress;
	str += strForm;

	BOOL fSuccess = CreateProcess(NULL, (LPSTR)(LPCTSTR)str, NULL, NULL, 0, 
		CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);

	if(fSuccess) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);	


	}


}

void CWebIDPWDDlg::GetOrderData(long nTNo, long nCompany)
{
	if(!CheckData()) return;

	UpdateData();
	long nCNo = 0;
	CString strPhone = "";

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_web_id_pwd");
	pCmd.AddParameter(nTNo); 	
	pCmd.AddParameter(nCompany);
	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() > 0)
	{
		pRs.GetFieldValue("nCNo", nCNo); 
		pRs.GetFieldValue("sWebID", m_strWebID);
		pRs.GetFieldValue("sWebPWD", m_strWebPWD);		
		pRs.GetFieldValue("sPhone", m_strPhone);	
		pRs.GetFieldValue("sWebAddress", m_strWebAddress);	
		
	}
	if(m_strWebID.GetLength() <= 0)
		m_nType = NO_MEMBER;
	else
		m_nType = MEMBER;

	m_nCNo = nCNo;
	m_nTNo = nTNo;

	UpdateData(FALSE);
	pRs.Close();

}

void CWebIDPWDDlg::OnBnClickedNomemberSendSMS()
{


	if(! CheckData() ) return;

	if(m_nType <= 0 ) return;

	CString strMsg = "";

	if(m_nType == NO_MEMBER)
	{
		strMsg.Format("������ �н������ %s �Դϴ�");	
	}
	else if (m_nType == MEMBER)
	{
		strMsg.Format("������ ���̵� [%s], �н������ [%s] �Դϴ�", m_strWebID, m_strWebPWD);	
	}
	else
	{

	}

	//CString str = GetItemPhone(nIndex);

	CString sPhone = "";
	CCustomerSmsDlg2 dlg;
	dlg.m_nCompany = m_nCompany;
	dlg.m_strCustomerPN = m_strPhone;	
	dlg.m_strRecvPhone = GetCurBranchInfo()->strPhone;
	dlg.m_nCompany = GetCurBranchInfo()->nCompanyCode;	
	dlg.m_nContent = 0; //  ���� ���� �޼�������
	dlg.m_strMsg = strMsg;
	if(IDOK == dlg.DoModal())
	{
		

	}

}
void CWebIDPWDDlg::OnBnClickedCancel()
{
	OnCancel();
}
