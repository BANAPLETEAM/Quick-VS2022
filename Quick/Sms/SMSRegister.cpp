// CSMSRegister.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SMSRegister.h"
#include "LogiUtil.h"
#include "SMSFileUpload.h"
#include "WebUploadDlg.h"

#define  TYPE_DAERI 0
#define  TYPE_QUICK 1

#define  TELECOM_DOC 0
#define  BUSINESS_DOC 1



#define TEL_USE_CHECK 0
#define CORP_USE_CHECK 1
#define LOGI_USE_CHECK 2


#define ADD_NEW 1
#define MODIFY	2

#define IS_COMPANY_TEL_CONTENT "����(ȸ��)�� ��ǥ��ȣ�� ��Ȳ�ǹ�ȣ�� ��ϵǾ� �ֽ��ϴ�"
#define IS_COMPANY_TEL	110

#define IS_GENERAL_TEL_CONTENT "����(ȸ��)�� ��ϵ� ��ȣ�� �ֽ��ϴ�"
#define IS_GENERAL_TEL	111

#define CERTIFICATE_NOT_CONTENT "�ڵ��� ������ȣ �ùٸ��� �ʽ��ϴ�."
#define CERTIFICATE_NOT 200



#define EMPTY_STATE		0
#define REGISTER_STATE	1
#define LOGI_STATE		2
#define FINISH_STATE	3
#define REJECT_STATE	4
#define ERROR_STATE		5

#define  COMPANY_TEL	0
#define  OFFICE_TEL		1
#define  GENERAL_TEL	2
#define  GENERAL_HP		3


// CSMSRegister ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSMSRegister, CMyDialog)

CSMSRegister::CSMSRegister(CWnd* pParent /*=NULL*/)
: CMyDialog(CSMSRegister::IDD, pParent)
{
	InitData();


}



CSMSRegister::~CSMSRegister()
{
}

void CSMSRegister::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_SMSCALLBACK_EDIT ,		m_edtSMSCallBack);
	DDX_Control(pDX, IDC_HELP_BTN,				m_btnHelp);
	DDX_Control(pDX, IDC_CALLBACK_TYPE_COMBO,	m_cmbCallBackType);
	DDX_Control(pDX, IDC_HP_REGISTER_BTN,		m_btnHPRegister);

	DDX_Control(pDX, IDC_HP_REGISTER_STATIC,	m_stcHPRegister);
	DDX_Control(pDX, IDC_HP_REGISTER_EDIT,		m_edtHPRegister);

	DDX_Control(pDX, IDC_SMS_CALLBACK_ETC_EDIT, m_edtSMSCallBackEtc);
	DDX_Control(pDX, IDC_CORP_RADIO,			m_rdoCorp);
	DDX_Control(pDX, IDC_CORP_NOT_RADIO,		m_rdoCorpNot);

	DDX_Control(pDX, IDC_USE_RADIO,				m_rdoUse);
	DDX_Control(pDX, IDC_USE_NOT_RADIO,			m_rdoUseNot);								   

	DDX_Control(pDX, IDC_REGISTER_BTN,			m_btnRegister);
	DDX_Control(pDX, IDC_CLOSE_BTN,				m_btnClose);
	DDX_Control(pDX, IDC_REGISTER_NO_STATIC,	m_stcRegisterNo);

	DDX_Control(pDX, IDC_TELECOM_DOC_EDIT,		m_edtTelecomDoc);
	DDX_Control(pDX, IDC_TELECOM_UPLOAD_BTN,	m_btnTelecomUpload);
	DDX_Control(pDX, IDC_BUSSINESS_DOC_EDIT,	m_edtBussinessDoc);
	DDX_Control(pDX, IDC_BUSINESS_UPLOAD_BTN,	m_btnBussindessUpload);


	DDX_Control(pDX, IDC_BRANCH_LIST, m_lstBranch);
	DDX_Control(pDX, IDC_MAIN_EDIT, m_edtMain);
	DDX_Control(pDX, IDC_SUB_EDIT, m_edtSub);
	DDX_Control(pDX, IDC_MAIN_BUTTON, m_btnMain);
	DDX_Control(pDX, IDC_SUB_BUTTON, m_btnSub);

	DDX_Control(pDX, IDC_NAME_EDIT,				m_edtContactName	);
	DDX_Control(pDX, IDC_JOBTITLE_EDIT,			m_edtContactJobTitle);
	DDX_Control(pDX, IDC_CONTECT_NUMBER_EDIT,	m_edtContactNumber	);

	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSMSRegister, CMyDialog)

	ON_CBN_SELCHANGE(	IDC_CALLBACK_TYPE_COMBO,	OnCbnSelchangeTelTypeCombo)
	ON_BN_CLICKED(		IDC_REGISTER_BTN,			OnBnClickedRegister)
	ON_BN_CLICKED(		IDC_CLOSE_BTN,				OnBnClickedClose)

	ON_BN_CLICKED(		IDC_TELECOM_UPLOAD_BTN,		OnBnClickedTelecomUpload)
	ON_BN_CLICKED(		IDC_BUSINESS_UPLOAD_BTN,	OnBnClickedBussinessUpload)

	ON_BN_CLICKED(IDC_HP_REGISTER_BTN, &CSMSRegister::OnBnClickedHpRegisterBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN2, &CSMSRegister::OnBnClickedCloseBtn2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSMSRegister �޽��� ó�����Դϴ�.

BOOL CSMSRegister::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CString strSubKey = "Software\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION";
	LF->WriteRegistryInt(HKEY_CURRENT_USER, strSubKey, "Quick.exe", 11000);

	m_cBranch.SetParent(this, TRUE);
	m_cBranch.InitData(&m_edtMain, &m_edtSub, &m_btnMain, &m_btnSub);
	m_lstBranch.SetMapData(&m_cBranch);
	m_lstBranch.SetAllNoCheckRow();
	m_lstBranch.Populate();

	if(m_lstBranch.GetRecords()->GetCount() <= 0)
	{
		OneBranchList();		
	}

	m_rdoCorp.SetCheck(FALSE);	
	m_rdoCorpNot.SetCheck(FALSE);
	m_bInitDialog = TRUE;
	if(! m_bNew )  
	{
		CRect r;
		this->GetWindowRect(&r);		
		r.right -= 294;	
		this->MoveWindow(r);				
		m_btnRegister.SetWindowText("�� ��");

		LoadModifyData();

	}
	else
	{
		//m_rdoUse.SetCheck(TRUE);
		m_cmbCallBackType.SetCurSel(2);

	}
	OnCbnSelchangeTelTypeCombo();

	return TRUE;
}


void CSMSRegister::OneBranchList()
{

	long nCompany = m_ui.nCompany;


	CXTPGridRecord *pTopRecord  = m_lstBranch.AddRecord(new CXTPGridRecord_Branch(TRUE, "����", "")); //, "", ""
	pTopRecord->SetExpanded(TRUE);
	m_lstBranch.SetItemData(pTopRecord, NULL);


	CXTPGridRecord *pSubrecord = pTopRecord->GetChilds()->Add(new CXTPGridRecord_Branch(TRUE, "", m_ci.GetBranchName(nCompany))); //, m_ci.GetPhone(nCompany), m_ci.GetShareCompanyOfficePhone(nCompany)
	pSubrecord->SetExpanded(TRUE);

	//m_lstBranch.SetItemData(pSubrecord, (DWORD)CI()->GetBranchInfo(nCompany));

	m_lstBranch.Populate();



}


void CSMSRegister::InitData()
{
	m_bNew = FALSE;
	m_nModifyNo = 0;
	m_nModifyCompany = 0;
	m_bModifyData = FALSE;

	m_nLoadTelecomState = 0;	
	m_nLoadIdentityCardState = 0;
	m_strLoadTelecomUrl = "";
	m_strLoadIdentityCardUrl = "";
	m_bInitDialog = FALSE;
	if(m_bInitDialog)
	{


		m_pParent = NULL;
		m_strInsertedSMSCallBackNo = "";

		m_rdoCorp.SetCheck(FALSE);
		m_rdoCorpNot.SetCheck(FALSE);
		m_rdoUse.SetCheck(FALSE);
		m_rdoUseNot.SetCheck(FALSE);
		m_edtSMSCallBack.SetWindowText("");

		m_edtTelecomDoc.SetWindowText("");
		m_edtBussinessDoc.SetWindowText("");
		m_edtHPRegister.SetWindowText("");
	}
}


void CSMSRegister::LoadModifyData()
{

	if(m_nModifyNo<= 0) return;
	long nState = LOGI_STATE;

	CMkRecordset rs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_smscallback_data_one"); 
	pCmd.AddParameter(m_nModifyCompany);
	pCmd.AddParameter(m_nModifyNo);
	if(!rs.Execute(&pCmd)) return;

	if(rs.GetRecordCount() <= 0 )
		OnClose();

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		CString strTel,strEtc;		
		long	nTelType,nCorpType, nUse ;		

		rs.GetFieldValue("sTel",				strTel);
		rs.GetFieldValue("nTelType",			nTelType);
		rs.GetFieldValue("sEtc",				strEtc);
		rs.GetFieldValue("nUse",				nUse);
		rs.GetFieldValue("nCorpType",			nCorpType);
		rs.GetFieldValue("nState",				nState);
		rs.GetFieldValue("nTelecomState",		m_nLoadTelecomState);
		rs.GetFieldValue("sTelecomUrl",			m_strLoadTelecomUrl);
		rs.GetFieldValue("nIdentityCardState",	m_nLoadIdentityCardState);
		rs.GetFieldValue("sIdentityCardUrl",	m_strLoadIdentityCardUrl);

		if(nUse == 1) m_rdoUse.SetCheck(TRUE);
		if(nUse == 2) m_rdoUseNot.SetCheck(TRUE);

		m_edtSMSCallBack.SetWindowText(strTel);
		m_cmbCallBackType.SetCurSel(nTelType);
		if(nTelType == COMPANY_TEL || nTelType == OFFICE_TEL )
			m_edtSMSCallBackEtc.EnableWindow(TRUE);

		m_edtSMSCallBackEtc.SetWindowText(strEtc);
		if(nCorpType == 1 )
			m_rdoCorp.SetCheck(TRUE);
		else if(nCorpType == 2)
			m_rdoCorpNot.SetCheck(TRUE);


		rs.MoveNext();
	}
	rs.Close();

	if(nState == FINISH_STATE || nState == LOGI_STATE )
	{
		m_edtSMSCallBack.EnableWindow(FALSE);
		m_cmbCallBackType.EnableWindow(FALSE);
		m_btnTelecomUpload.EnableWindow(FALSE);
		m_btnBussindessUpload.EnableWindow(FALSE);

		m_btnHPRegister.EnableWindow(FALSE);
		m_rdoCorp.EnableWindow(FALSE);
		m_rdoCorpNot.EnableWindow(FALSE);
		m_edtHPRegister.EnableWindow(FALSE);
		m_edtSMSCallBackEtc.SetFocus();
	}
}

void CSMSRegister::HPRegiserViewType(BOOL bTrue)
{

	if(bTrue)
	{
		m_btnHPRegister.ShowWindow(SW_SHOW);
		m_edtHPRegister.ShowWindow(SW_SHOW);		
		m_stcHPRegister.ShowWindow(SW_SHOW);
		m_edtSMSCallBackEtc.EnableWindow(SW_SHOW);

		GetDlgItem(IDC_REGISTTER_NO_STATIC)->ShowWindow(SW_SHOW);


		m_rdoCorp.ShowWindow(SW_HIDE);
		m_rdoCorpNot.ShowWindow(SW_HIDE);
		m_edtTelecomDoc.ShowWindow(SW_HIDE);
		m_edtBussinessDoc.ShowWindow(SW_HIDE);
		m_btnTelecomUpload.ShowWindow(SW_HIDE);
		m_btnBussindessUpload.ShowWindow(SW_HIDE);			
		GetDlgItem(IDC_CORP_STATIC)->ShowWindow(SW_HIDE);		
		GetDlgItem(IDC_TELECOM_DOC_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUSSINESS_DOC_STATIC)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_REGISTTER_NO_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CORP_GROUP_STATIC)->ShowWindow(SW_HIDE);	

	}
	else
	{
		m_btnHPRegister.ShowWindow(SW_HIDE);
		m_edtHPRegister.ShowWindow(SW_HIDE);		
		m_stcHPRegister.ShowWindow(SW_HIDE);
		m_edtSMSCallBackEtc.EnableWindow(SW_HIDE);
		GetDlgItem(IDC_CORP_GROUP_STATIC)->ShowWindow(SW_HIDE);	



		m_rdoCorp.ShowWindow(SW_SHOW);
		m_rdoCorpNot.ShowWindow(SW_SHOW);
		//m_edtTelecomDoc.ShowWindow(SW_SHOW);
		//m_edtBussinessDoc.ShowWindow(SW_SHOW);
		m_btnTelecomUpload.ShowWindow(SW_SHOW);
		m_btnBussindessUpload.ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CORP_STATIC)->ShowWindow(SW_SHOW);		
		GetDlgItem(IDC_TELECOM_DOC_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUSSINESS_DOC_STATIC)->ShowWindow(SW_SHOW);
		//GetDlgItem(IDC_REGISTTER_NO_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CORP_GROUP_STATIC)->ShowWindow(SW_SHOW);	
	}


}

void CSMSRegister::OnCbnSelchangeTelTypeCombo()
{
	long nTelType = m_cmbCallBackType.GetCurSel();

	switch (nTelType)
	{
	case COMPANY_TEL:
		HPRegiserViewType(FALSE);
		m_edtSMSCallBackEtc.SetWindowText("��ǥ��ȣ");
		break;
	case OFFICE_TEL:
		HPRegiserViewType(FALSE);
		m_edtSMSCallBackEtc.SetWindowText("��Ȳ�ǹ�ȣ");

		break;
	case GENERAL_TEL:
		HPRegiserViewType(FALSE);
		m_edtSMSCallBackEtc.EnableWindow(TRUE);
		//m_edtSMSCallBackEtc.SetWindowText("");
		break;
	case GENERAL_HP:
		HPRegiserViewType(TRUE);
		//m_edtSMSCallBackEtc.SetWindowText("");
		break;
	}

}


BOOL CSMSRegister::CheckData()
{
	try
	{
		CString strRegisterTel = "", strEtc = "";
		m_edtSMSCallBack.GetWindowText(strRegisterTel);

		if( !LF->CheckTel(strRegisterTel))
			return FALSE;

		if(m_cmbCallBackType.GetCurSel() ==  GENERAL_TEL || m_cmbCallBackType.GetCurSel() ==  GENERAL_HP )
		{

			m_edtSMSCallBackEtc.GetWindowText(strEtc);
			if(strEtc == "��ǥ��ȣ" || strEtc == "��Ȳ�ǹ�ȣ"  )
				throw("�Ϲݹ�ȣ�� �ڵ��� ��ȣ�Ͻ� ��ǥ��ȣ�� ��Ȳ�ǹ�ȣ��� ������Ͻ� �� �����ϴ�.");


		}
		if(m_cmbCallBackType.GetCurSel() ==  COMPANY_TEL )
		{

			m_edtSMSCallBackEtc.GetWindowText(strEtc);
			if(strEtc != "��ǥ��ȣ"  )
			{
				throw("��ǥ��ȣ�� ��� ��ǥ��ȣ�� ����Ͻ� �� �ֽ��ϴ�"); 

			}
		}
		if(m_cmbCallBackType.GetCurSel() ==  OFFICE_TEL )
		{

			m_edtSMSCallBackEtc.GetWindowText(strEtc);
			if(strEtc != "��Ȳ�ǹ�ȣ"  )
				throw("��Ȳ�ǹ�ȣ ��� ��Ȳ�ǹ�ȣ ����Ͻ� �� �ֽ��ϴ�");

		}

		int nTelType = m_cmbCallBackType.GetCurSel();
		int nCorpType = 0;

		if( nTelType != GENERAL_HP &&  
			!( m_rdoCorp.GetCheck() || m_rdoCorpNot.GetCheck() ) 
			)
			throw "����/���� ������ üũ�Ͽ� �ּ���";


		if(!m_rdoUse.GetCheck() && !m_rdoUseNot.GetCheck())
		{
			throw "��� /�̻�� �����Ͽ��ּ���";
		}


	}
	catch (char* e)
	{
		MessageBox(e, "Ȯ��",MB_ICONERROR );
		return FALSE;

	}
	catch (CString strMsg)
	{
		MessageBox(strMsg, "Ȯ��",MB_ICONERROR );
		return FALSE;

	}
	return TRUE;

}
void CSMSRegister::AddNew()
{

	try
	{
		if( ! CheckData()) return;	

		CString strRegisterTel = "", strHPRegister = "", strSMSCallBackEtc = "";
		m_edtSMSCallBack.GetWindowText(strRegisterTel);
		m_edtHPRegister.GetWindowText(strHPRegister);
		m_edtSMSCallBackEtc.GetWindowText(strSMSCallBackEtc);
		int nCorpType = (m_rdoCorp.GetCheck() ?  1 : 2 );
		int nTelType = m_cmbCallBackType.GetCurSel();
		long nIsErrorCompany = 0;
		long nError = 0;
		CString strContactName ="", strContactJobTitle = "", strContactNumber = "";

		if( nTelType == GENERAL_HP )
		{
			if( ! HPCheckData(strRegisterTel) ) 
				return;

			if(strRegisterTel.Left(2) != "01")
				throw "�Ϲݹ�ȣ, ��ǥ��ȣ, ��Ȳ�� ��ȣ Ÿ������ ����ϼ���";

		}
		else if(  nTelType == COMPANY_TEL || nTelType == OFFICE_TEL)
		{
			if(! ( m_rdoCorp.GetCheck() || m_rdoCorpNot.GetCheck()) )
				throw "����/���� ������ üũ�Ͽ� �ּ���";
		}
		else if( nTelType == GENERAL_TEL )
		{
			if(strRegisterTel.Left(2) == "01")
				throw "�ڵ��� Ÿ�� ��ȭ�Դϴ� ";

			if(! ( m_rdoCorp.GetCheck() || m_rdoCorpNot.GetCheck()) )
				throw "����/���� ������ üũ�Ͽ� �ּ���";
		}

		if( LF->GetStringFromEdit(  (CEdit*)&m_edtContactName ).GetLength() > 6 )
			throw "����ó�̸��� 3���̻� ������ �� �����ϴ�.";

		if( LF->GetStringFromEdit(  (CEdit*)&m_edtContactJobTitle).GetLength() > 6 )
			throw "���� ��å�� 3���̻� ������ �� �����ϴ�.";

		if( LF->GetStringFromEdit(   (CEdit*)&m_edtContactNumber).GetLength() > 20 )
			throw "����ó�� 20���̻� ������ �� �����ϴ�.";

		strContactName		= LF->GetStringFromEdit((CEdit*)&m_edtContactName		);
		strContactJobTitle	= LF->GetStringFromEdit((CEdit*)&m_edtContactJobTitle	);
		strContactNumber	= LF->GetStringFromEdit((CEdit*)&m_edtContactNumber		);

		if(! ( m_rdoUse.GetCheck() || m_rdoUseNot.GetCheck()) )
			throw "�߽Ź�ȣ ��뿩�θ� üũ�Ͽ� �ּ���";

		CStringArray strCompanyArray;
		long nCount = m_lstBranch.GetCheckCount(strCompanyArray);

		CString strTemp = ""; 
		strTemp.Format("[%d]���� ���翡 ���� �Ͻðڽ��ϱ�?", nCount);

		if(nCount <= 0)
		{
			MessageBox("������ ���縦 üũ�Ͽ��ּ���", "Ȯ��",MB_ICONERROR);
			return;
		}

		if(MessageBox(strTemp, "Ȯ��", MB_OKCANCEL) != IDOK)
			return ;

		CString strCompanyList =  "", strErrMsg = "";
		for(int i = 0; i < strCompanyArray.GetCount(); i++)
			strCompanyList += strCompanyArray.GetAt(i) + ",";



		CMkRecordset rs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_sms_callback_tel2"); 
		pCmd.AddParameter(nCount);
		pCmd.AddParameter(strCompanyList);
		pCmd.AddParameter(m_bNew ? ADD_NEW : MODIFY);
		pCmd.AddParameter(strRegisterTel);
		pCmd.AddParameter(nTelType);
		pCmd.AddParameter(strSMSCallBackEtc);
		pCmd.AddParameter(nCorpType);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ci.GetBranchName(m_ui.nCompany));
		pCmd.AddParameter(strHPRegister);
		pCmd.AddParameter(m_rdoUse.GetCheck() ? 1 : 2);
		pCmd.AddParameter(strContactName);
		pCmd.AddParameter(strContactJobTitle);
		pCmd.AddParameter(strContactNumber);
		pCmd.AddParameter(m_bNew); // -- ������
		CMkParameter *pIsCompany		= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		CMkParameter *pIsSMSCallBackNo	= pCmd.AddParameter(typeString, typeOutput, 30, "");  //  ������
		CMkParameter *pInsertedSMSCallBackNo	= pCmd.AddParameter(typeString, typeOutput, 600, "");  // �űԷ� �Է��� No
		CMkParameter *pErrorNo			= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		if(!rs.Execute(&pCmd)) return;

		long nIsCompany = 0, nErroNo = 0;
		CString strIsErrorSMSCallBackNo = "", strInsertedSMSCallBackNo = "" ;

		pIsCompany->GetValue(nIsErrorCompany);
		pIsSMSCallBackNo->GetValue(strIsErrorSMSCallBackNo);
		pInsertedSMSCallBackNo->GetValue(m_strInsertedSMSCallBackNo);
		pErrorNo->GetValue(nError);


		if(m_strInsertedSMSCallBackNo.Left(1) == ",")
			m_strInsertedSMSCallBackNo = m_strInsertedSMSCallBackNo.Mid(1);

		if(nError == IS_COMPANY_TEL )
		{
			strErrMsg.Format("%s %s,\n\r������ȭ��ȣ : %s", 
				m_ci.GetBranchName(m_ui.nCompany), IS_COMPANY_TEL_CONTENT,
				LF->GetDashPhoneNumber( strIsErrorSMSCallBackNo)	);
			MessageBox(strErrMsg,"Ȯ��", MB_ICONERROR);
			return ;


		}
		if(nError == IS_GENERAL_TEL )
		{
			strErrMsg.Format("%s %s,\n\r������ȭ��ȣ : %s", 
				m_ci.GetBranchName(m_ui.nCompany), IS_GENERAL_TEL_CONTENT,
				LF->GetDashPhoneNumber( strIsErrorSMSCallBackNo)	);

			MessageBox(strErrMsg,"Ȯ��", MB_ICONERROR);
			return ;
		}
		if(nError == CERTIFICATE_NOT)
		{
			strErrMsg.Format("%s %s,\n\r������ȭ��ȣ : %s", 
				m_ci.GetBranchName(m_ui.nCompany), CERTIFICATE_NOT_CONTENT,
				LF->GetDashPhoneNumber( strIsErrorSMSCallBackNo)	);

			MessageBox(strErrMsg,"Ȯ��", MB_ICONERROR);
			return ;
		}

		if( nTelType == 3 ) // �ڵ���������
		{
			AllControlClear(TRUE);
			MessageBox("��ϵǾ����ϴ� ", "Ȯ��", MB_ICONINFORMATION);


		}
		else
		{
			m_btnRegister.EnableWindow(FALSE);
			MessageBox("��ϵǾ����ϴ� ", "Ȯ��", MB_ICONINFORMATION);
			//m_strRegisterCompanyList = strCompanyList;

		}
		m_btnRegister.EnableWindow(FALSE);
		m_bModifyData = TRUE;
		if( LF->IsStringDigit(  m_strInsertedSMSCallBackNo.Mid(m_strInsertedSMSCallBackNo.Find(",")) ) )
			m_nModifyNo =  atol( m_strInsertedSMSCallBackNo.Mid(m_strInsertedSMSCallBackNo.Find(",")) );

	}
	catch (char* e)
	{
		MessageBox(e, "Ȯ��", MB_ICONERROR);
	}
	catch (CString strMsg)
	{
		MessageBox(strMsg, "Ȯ��", MB_ICONERROR);
	}


}
void CSMSRegister::ModifyEdit()
{

	try
	{
		if( ! CheckData()) return;	

		CString strRegisterTel = "", strHPRegister = "", strSMSCallBackEtc = "";
		m_edtSMSCallBack.GetWindowText(strRegisterTel);
		m_edtHPRegister.GetWindowText(strHPRegister);
		m_edtSMSCallBackEtc.GetWindowText(strSMSCallBackEtc);
		int nCorpType = (m_rdoCorp.GetCheck() ?  1 : 2 );
		int nTelType = m_cmbCallBackType.GetCurSel();
		long nIsErrorCompany = 0;
		long nError = 0;
		CString strContactName ="", strContactJobTitle = "", strContactNumber = "";

		if( nTelType == GENERAL_HP )
		{
			if( ! HPCheckData(strRegisterTel) ) 
				return;

			if(strRegisterTel.Left(2) != "01")
				throw "�Ϲݹ�ȣ, ��ǥ��ȣ, ��Ȳ�� ��ȣ Ÿ������ ����ϼ���";

		}
		else if(  nTelType == COMPANY_TEL || nTelType == OFFICE_TEL)
		{
			if(! ( m_rdoCorp.GetCheck() || m_rdoCorpNot.GetCheck()) )
				throw "����/���� ������ üũ�Ͽ� �ּ���";
		}
		else if( nTelType == GENERAL_TEL )
		{
			if(strRegisterTel.Left(2) == "01")
				throw "�ڵ��� Ÿ�� ��ȭ�Դϴ� ";

			if(! ( m_rdoCorp.GetCheck() || m_rdoCorpNot.GetCheck()) )
				throw "����/���� ������ üũ�Ͽ� �ּ���";
		}

		if( LF->GetStringFromEdit(  (CEdit*)&m_edtContactName ).GetLength() > 6 )
			throw "����ó�̸��� 3���̻� ������ �� �����ϴ�.";

		if( LF->GetStringFromEdit(  (CEdit*)&m_edtContactJobTitle).GetLength() > 6 )
			throw "���� ��å�� 3���̻� ������ �� �����ϴ�.";

		if( LF->GetStringFromEdit(   (CEdit*)&m_edtContactNumber).GetLength() > 20 )
			throw "����ó�� 20���̻� ������ �� �����ϴ�.";

		strContactName		= LF->GetStringFromEdit((CEdit*)&m_edtContactName		);
		strContactJobTitle	= LF->GetStringFromEdit((CEdit*)&m_edtContactJobTitle	);
		strContactNumber	= LF->GetStringFromEdit((CEdit*)&m_edtContactNumber		);


		if(! ( m_rdoUse.GetCheck() || m_rdoUseNot.GetCheck()) )
			throw "�߽Ź�ȣ ��뿩�� üũ�Ͽ� �ּ���";

		if(MessageBox("�����Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
			return ;

		CString strErrMsg	= "";


		CMkRecordset rs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_sms_callback_tel2"); 
		pCmd.AddParameter(1);
		pCmd.AddParameter(m_nModifyCompany);
		pCmd.AddParameter(m_bNew ? ADD_NEW : MODIFY);
		pCmd.AddParameter(strRegisterTel);
		pCmd.AddParameter(nTelType);
		pCmd.AddParameter(strSMSCallBackEtc);
		pCmd.AddParameter(nCorpType);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ci.GetBranchName((m_ui.nCompany)));
		pCmd.AddParameter(strHPRegister);
		pCmd.AddParameter(m_rdoUse.GetCheck() ? 1 : 2);
		pCmd.AddParameter(strContactName);
		pCmd.AddParameter(strContactJobTitle);
		pCmd.AddParameter(strContactNumber);
		pCmd.AddParameter(m_nModifyNo); // -- ������
		CMkParameter *pIsCompany		= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		CMkParameter *pIsSMSCallBackNo	= pCmd.AddParameter(typeString, typeOutput, 30, "");
		CMkParameter *pInsertedSMSCallBackNo	= pCmd.AddParameter(typeString, typeOutput, 600, "");  // �űԷ� �Է��� No
		CMkParameter *pErrorNo			= pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!rs.Execute(&pCmd)) return;
		long nIsCompany = 0, nErroNo = 0;
		CString strIsErrorSMSCallBackNo = "";

		pIsCompany->GetValue(nIsErrorCompany);
		pIsSMSCallBackNo->GetValue(strIsErrorSMSCallBackNo);
		pErrorNo->GetValue(nError);

		if(nError == IS_COMPANY_TEL )
		{
			strErrMsg.Format("%s %s,\n\r������ȭ��ȣ : %s", 
				m_ci.GetBranchName((m_ui.nCompany)), IS_COMPANY_TEL_CONTENT,
				LF->GetDashPhoneNumber( strIsErrorSMSCallBackNo)	);
			MessageBox(strErrMsg,"Ȯ��", MB_ICONERROR);
			return ;


		}
		if(nError == IS_GENERAL_TEL )
		{
			strErrMsg.Format("%s %s,\n\r������ȭ��ȣ : %s", 
				m_ci.GetBranchName((m_ui.nCompany)), IS_GENERAL_TEL_CONTENT,
				LF->GetDashPhoneNumber( strIsErrorSMSCallBackNo)	);

			MessageBox(strErrMsg,"Ȯ��", MB_ICONERROR);
			return ;
		}
		if(nError == CERTIFICATE_NOT)
		{
			strErrMsg.Format("%s %s,\n\r������ȭ��ȣ : %s", 
				m_ci.GetBranchName((m_ui.nCompany)), CERTIFICATE_NOT_CONTENT,
				LF->GetDashPhoneNumber( strIsErrorSMSCallBackNo)	);

			MessageBox(strErrMsg,"Ȯ��", MB_ICONERROR);
			return ;
		}

		if( nTelType == 3 ) // �ڵ���������
		{
			AllControlClear(TRUE);
			MessageBox("�����Ͽ����ϴ� ", "Ȯ��", MB_ICONINFORMATION);
		}
		else
		{
			m_btnRegister.EnableWindow(FALSE);
			MessageBox("�����Ͽ����ϴ� ", "Ȯ��", MB_ICONINFORMATION);
		}

		m_bModifyData = TRUE;
	}
	catch (char* e)
	{
		MessageBox(e,"Ȯ��", MB_ICONERROR);
	}
	catch (CString strMsg)
	{
		MessageBox(strMsg,"Ȯ��", MB_ICONERROR);
	}


}


void CSMSRegister::OnBnClickedRegister()
{
	if(m_bNew)
		AddNew();
	else
		ModifyEdit();


}	


void CSMSRegister::AllControlClear(BOOL bHP)
{

	if(bHP)
	{

		UpdateData();
		m_edtSMSCallBack.SetWindowText("");
		m_edtSMSCallBackEtc.SetWindowText("");
		//m_strRegisterCompanyList = "";
		m_edtHPRegister.SetWindowText("");

	}
	m_rdoCorp.SetCheck(FALSE);	
	m_rdoCorpNot.SetCheck(FALSE);


}
BOOL CSMSRegister::HPCheckData(CString strSMSCallBack)
{


	if(! (strSMSCallBack.Left(3) == "010" || strSMSCallBack.Left(3) == "016" ||
		strSMSCallBack.Left(3) == "017" || strSMSCallBack.Left(3) == "018" ||
		strSMSCallBack.Left(3) == "019")
		)
	{
		MessageBox("�ڵ��� ��ȣ�� �ƴմϴ�.","Ȯ��", MB_ICONERROR);
		return FALSE;
	}

	strSMSCallBack.Replace("-", "");
	if( !(strSMSCallBack.GetLength() >= 10 && strSMSCallBack.GetLength() <= 11  )
		)
	{
		MessageBox("�ڵ��� �ڸ����� 10 ~ 11�ڸ� �Դϴ�.","Ȯ��", MB_ICONERROR);
		return FALSE;

	}


	if( !( LF->IsStringDigit(strSMSCallBack) )
		)
	{
		MessageBox("�߽Ź�ȣ�� ���ڰ� �ƴմϴ�.","Ȯ��", MB_ICONERROR);
		return FALSE;

	}

	return TRUE;
}

void CSMSRegister::OnBnClickedClose()
{
	OnCancel();
}

void CSMSRegister::OnBnClickedHpRegisterBtn()
{


	CString strSMSCallBack = "", strMsg = "";
	m_edtSMSCallBack.GetWindowText(strSMSCallBack);

	if(m_cmbCallBackType.GetCurSel() != GENERAL_HP) 
	{
		MessageBox("�ڵ�����ȣ ������ ������ �� �ֽ��ϴ�.","Ȯ��", MB_ICONERROR);
		return;
	}

	strMsg.Format("%s %s", LF->GetDashPhoneNumber(strSMSCallBack), "�� ������ȣ�� �߼��Ͻðڽ��ϱ�?" );

	if( MessageBox(strMsg, "Ȯ��", MB_YESNO ) == IDNO) return;

	strSMSCallBack = LF->GetNoneDashNumber(strSMSCallBack);

	if( ! HPCheckData(strSMSCallBack)  ) return;



	if( !(strSMSCallBack.GetLength() >= 10 && strSMSCallBack.GetLength() <= 11) )
	{
		MessageBox("�ڸ����� ������ ������ 11~ 12�ڸ� �̾�� �մϴ�","Ȯ��", MB_ICONERROR);
		return;
	}

	CStringArray strCompanyArray;
	long nCount = m_lstBranch.GetCheckCount(strCompanyArray);
	CString strCompanyList = "";
	for(int i = 0; i < strCompanyArray.GetCount(); i++)
		strCompanyList += strCompanyArray.GetAt(i) + ",";

	if(strCompanyList.GetLength() <= 0)
	{
		MessageBox("������ ȸ�縦 �����Ͽ� �ּ���","Ȯ��", MB_ICONERROR);
		return;
	}


	int nError = 0;
	CMkRecordset rs(m_pMkDb);
	CMkCommand Cmd(m_pMkDb, "insert_sms_callback_hp_certificate"); 	
	Cmd.AddParameter(strCompanyList);
	Cmd.AddParameter(strSMSCallBack);
	Cmd.AddParameter(m_ui.nCompany);
	Cmd.AddParameter(m_ui.nWNo);
	Cmd.AddParameter(m_ci.GetBranchName((m_ui.nCompany)));	
	CMkParameter *pError = Cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	if(!rs.Execute(&Cmd) ) return ;

	pError->GetValue(nError);
	if(nError == 100)
	{
		MessageBox("�Ϸ翡 SMS �߼��� 150�� �̻� ���� �� �����ϴ�. ","Ȯ��", MB_ICONERROR);
		return;
	}
	else if(nError == 102)
	{
		MessageBox("SMS �߼��� ������ �߻��Ͽ����ϴ�. ��������Ʈ�� �����ϼ��� ","Ȯ��", MB_ICONERROR);
		return;
	}



	MessageBox("SMS �߼��� �Ͽ����ϴ�.\n\r2~3�� �ȿ� �߼��� �ȵɽ� ��߼� ��ư�� �ٽ� �����ּ���.\n\r"\
		"6�ð����� ��ȿ�ϸ�\n\r�߼۵ȹ�ȣ�� ������ȣ�� �Է��ϼ���","Ȯ��", MB_ICONINFORMATION);


}


void CSMSRegister::OnBnClickedTelecomUpload()
{
	if(!m_rdoCorp.GetCheck() && !m_rdoCorpNot.GetCheck())
	{
		MessageBox("����/���� ���θ� �����Ͽ� �ּ���", "Ȯ��",  MB_ICONINFORMATION);
		return;
	}

	if(!m_rdoUse.GetCheck() && !m_rdoUseNot.GetCheck())
	{
		MessageBox("���/�̻�� ���θ� �����Ͽ� �ּ���", "Ȯ��",  MB_ICONINFORMATION);
		return;
	}

	if(m_bNew)
		FileUploads(TELECOM_DOC);
	else
		FileUpload(TELECOM_DOC, m_strLoadTelecomUrl);


}
void CSMSRegister::OnBnClickedBussinessUpload()
{
	if(!m_rdoCorp.GetCheck() && !m_rdoCorpNot.GetCheck())
	{
		MessageBox("����/���� ���θ� �����Ͽ� �ּ���", "Ȯ��",  MB_ICONINFORMATION);
		return;
	}

	if(!m_rdoUse.GetCheck() && !m_rdoUseNot.GetCheck())
	{
		MessageBox("���/�̻�� ���θ� �����Ͽ� �ּ���", "Ȯ��",  MB_ICONINFORMATION);
		return;
	}

	if(m_bNew)
		FileUploads(BUSINESS_DOC);
	else
		FileUpload(BUSINESS_DOC,m_strLoadIdentityCardUrl);

}

BOOL CSMSRegister::FileUploads(int nType)
{
	MessageBox("��ȭ��ȣ�� ����� ������ �ø�����", "Ȯ��",MB_ICONERROR);
	return FALSE;
}

BOOL CSMSRegister::FileUpload(int nType, CString strOldFileName)
{
	CString strSMSCallback;
	m_edtSMSCallBack.GetWindowText(strSMSCallback);
	return FileUpload(nType, m_nModifyCompany, m_nModifyNo, strSMSCallback, TRUE);
}

BOOL CSMSRegister::FileUpload(int nType, int nCompany, int nNo, CString strSMSCallback,  BOOL bMsgBox)
{	
	CString strFileName;
	BOOL bSuccess = FALSE;

	strSMSCallback = LF->GetNoneDashNumber(strSMSCallback);
	if(strSMSCallback.GetLength() < 6 || !LF->CheckTel(strSMSCallback))
	{
		::MessageBox(NULL, "�߽���ȭ��ȣ ���ų� ��ȭ��ȣ ���Ŀ� ���� �ʽ��ϴ�.\r\n", "�ٽýõ��ϼ���", MB_ICONINFORMATION);		
		return FALSE;
	}

	CWebUploadDlg dlg;
	dlg.m_strURL = LF->GetWebUploadUrl("SMS_CALLBACK_DOCUMENT", nType);

	if(dlg.m_strURL.IsEmpty()) {
		::MessageBox(NULL, "���ε� ������ Ȯ�� �� �� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return FALSE;
	}

	dlg.m_strURL += "&system=smscallback/quick/";
	dlg.m_strURL += (nType == TELECOM_DOC ? "telecom" : "business");
	dlg.m_strURL += "&fileName=" + LF->GetStringFromLong(nCompany) + "_" + LF->GetStringFromLong(nNo) + "_" + strSMSCallback;

	if(dlg.DoModal() != IDOK)
		return FALSE;

	CMkCommand cmd(m_pMkDb, "insert_smscallback_document3");
	cmd.AddParameter(nType); // 1 TelecomeDoc  2 BusssinessDoc
	cmd.AddParameter(nNo);
	cmd.AddParameter(nCompany);
	cmd.AddParameter(dlg.m_strResult);
	cmd.AddParameter("");
	cmd.AddParameter("");

	if(!cmd.Execute()) 
	{
		return FALSE;
	}

	if(bMsgBox)
		::MessageBox(NULL, "��ϵǾ����ϴ�", "Ȯ��", MB_ICONINFORMATION);

	return TRUE;
}

void CSMSRegister::OnBnClickedCloseBtn2()
{
	if(m_bModifyData)
	{
		m_pParent->PostMessage((UINT)(WM_USER + 200) ,(WPARAM)m_nModifyNo, 0);
		m_bModifyData = FALSE;
	}
	OnClose();
}

void CSMSRegister::OnClose()
{

	if(m_bModifyData)
	{
		m_pParent->PostMessage((UINT)(WM_USER + 200) ,(WPARAM)m_nModifyNo, 0);
		m_bModifyData = FALSE;
	}

	CMyDialog::OnClose();
}