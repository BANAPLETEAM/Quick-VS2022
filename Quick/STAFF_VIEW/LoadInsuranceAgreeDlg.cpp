// LoadInsuranceAgreeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "LoadInsuranceAgreeDlg.h"

#include "WinInet.h"
#include "afxInet.h"

// CLoadInsuranceAgreeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLoadInsuranceAgreeDlg, CMyDialog)

CLoadInsuranceAgreeDlg::CLoadInsuranceAgreeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CLoadInsuranceAgreeDlg::IDD, pParent)
{
	m_bFirst = TRUE;
}

CLoadInsuranceAgreeDlg::~CLoadInsuranceAgreeDlg()
{
}

void CLoadInsuranceAgreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AGREE_EDIT, m_edtAgree);
}


BEGIN_MESSAGE_MAP(CLoadInsuranceAgreeDlg, CMyDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CLoadInsuranceAgreeDlg::OnBnClickedOkBtn)
	ON_EN_SETFOCUS(IDC_AGREE_EDIT, &CLoadInsuranceAgreeDlg::OnEnSetfocusAgreeEdit)
END_MESSAGE_MAP()


// CLoadInsuranceAgreeDlg �޽��� ó�����Դϴ�.

BOOL CLoadInsuranceAgreeDlg::OnInitDialog() 
{  
	CMyDialog::OnInitDialog();
	m_edtAgree.SetFont(m_FontManager.GetFont("����", 15)); 
 	
//	m_edtAgree.SetSel(-1, 0);
  
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

CString CLoadInsuranceAgreeDlg::GetSourceHtml(CString strUrl) 
{
	CInternetSession session;
	CInternetFile* fFile = NULL;
	try 
	{
		fFile = (CInternetFile*)session.OpenURL(strUrl); 
	}
	catch (CInternetException* pException)
	{
		fFile = NULL; 
		pException->Delete();
	}

	CString strSum = "";
	if(fFile)
	{
		CString strCode;

		while (fFile->ReadString(strCode) != NULL) 
		{
			strSum += strCode + "\r\n";
		}

		fFile->Close();
		delete fFile;
	}

	return strSum;
}


void CLoadInsuranceAgreeDlg::OnBnClickedOkBtn()
{	
	OnOK();
}

void CLoadInsuranceAgreeDlg::OnEnSetfocusAgreeEdit()
{
	if(m_bFirst)
	{
		m_edtAgree.SetWindowText(GetSourceHtml("http://down.logisoft.co.kr/down/SmartCallAgree/load_insurance_agree.txt"));
		m_bFirst = FALSE;
	}
}
