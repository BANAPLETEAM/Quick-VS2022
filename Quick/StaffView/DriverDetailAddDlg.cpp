// DriverDetailAddDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DriverDetailAddDlg.h"



// CDriverDetailAddDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDriverDetailAddDlg, CMyDialog)
CDriverDetailAddDlg::CDriverDetailAddDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDriverDetailAddDlg::IDD, pParent)
	, m_dtDate(COleDateTime::GetCurrentTime())
	, m_dtTime(COleDateTime::GetCurrentTime())
	, m_strCustomer(_T(""))		
	, m_strContent(_T(""))
	
{
	m_nCompany = 0;
	m_nRNo = 0;
}


CDriverDetailAddDlg::~CDriverDetailAddDlg()
{
}

void CDriverDetailAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATE_DATETIMEPICKER, m_dtDate);
	DDX_DateTimeCtrl(pDX, IDC_TIME_DATETIMEPICKER, m_dtTime);	
	DDX_Text(pDX, IDC_CUSTOMER_EDIT, m_strCustomer);
	DDX_Control(pDX, IDC_TITLE_COMBO, m_FixedCombo);	
	DDX_Text(pDX, IDC_CONTENT_EDIT, m_strContent);
	DDV_MaxChars(pDX, m_strContent, 500);

	DDX_Control(pDX, IDC_TIME_DATETIMEPICKER, m_dtpTime);
	DDX_Control(pDX, IDC_REWORD_COMBO, m_cmbReward);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);

	DDX_Control(pDX, IDC_CUSTOMER_EDIT, m_edtCustomer);
	DDX_Control(pDX, IDC_CONTENT_EDIT, m_edtContent);

	DDX_Control(pDX, IDC_CONFIRM_BUTTON, m_btnConfirm);
	DDX_Control(pDX, IDC_CANCEL_BUTTON, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CDriverDetailAddDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CONFIRM_BUTTON, OnBnClickedConfirmButton)	
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, OnBnClickedCancelButton)	
	
END_MESSAGE_MAP()


// CDriverDetailAddDlg 메시지 처리기입니다.

void CDriverDetailAddDlg::OnBnClickedConfirmButton()
{
	if(!CheckData()) return;

	CWaitCursor wait;
	
	UpdateData(TRUE);
	int nPoint = 0;	
	COleDateTime dtRegister;
	dtRegister.SetDateTime(m_dtDate.GetYear(),m_dtDate.GetMonth(), m_dtDate.GetDay(),
		m_dtTime.GetHour(), m_dtTime.GetMinute(), m_dtTime.GetSecond());
	CString strReward;
	m_cmbReward.GetWindowText(strReward);

	CMkCommand pCmd(m_pMkDb, "insert_driver_detail");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRNo);	
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),dtRegister);		
	CString strFixed;
	m_FixedCombo.GetWindowText(strFixed);
	pCmd.AddParameter(typeString, typeInput, strFixed.GetLength(),strFixed);	
	pCmd.AddParameter(typeString, typeInput, m_strContent.GetLength(), m_strContent);	
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCustomerNO);
	pCmd.AddParameter(typeString, typeInput, m_strCustomer.GetLength(), m_strCustomer);
	pCmd.AddParameter(typeString, typeInput, strReward.GetLength(), strReward);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	
		
	if(!pCmd.Execute()) return;		
	
	MessageBox("등록되었습니다.","등록",MB_ICONINFORMATION);
	OnOK();
}

BOOL CDriverDetailAddDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_dtDate = COleDateTime::GetCurrentTime();
	m_dtTime = COleDateTime::GetCurrentTime();
	m_dtpTime.SetFormat("tth:mm:ss");
	m_cmbReward.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CDriverDetailAddDlg::CheckData()
{
	CString strTitle;
	m_FixedCombo.GetWindowText(strTitle);
	if(strTitle.GetLength() <= 0 && m_strTitle.GetLength() > 40)
	{
		MessageBox("제목에 1자이상이거나 40자이하로 기입해주세요","확인",MB_ICONINFORMATION);
		return FALSE;
	}	
	return TRUE;
}



/*
void CDriverDetailAddDlg::OnBnClickedCustomerButton()
{
	CWaitCursor wait;
	char buffer[20];

	UpdateData(TRUE);
	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_detail_customer_search");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), this->m_strSearchCustomer);
		
	if(!pRs.Execute(&pCmd)) return;		
	int nCount = 0;
	int nCNo, nGrade;
	CString sCName, sDong, sLocation, sTel1, sTitle;
	COleDateTime dtLastUse;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		int nID, nCompany, nPoint,nRNo, nCustomerNo;
		CString sTitle, sCustomer,sContent;

		COleDateTime dtRegister;
	
		int nSubItem = 1;

		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sCName", sCName);
		pRs.GetFieldValue("sDong", sDong);
		pRs.GetFieldValue("sLocation", sLocation);		
		pRs.GetFieldValue("sTel1", sTel1);		
		pRs.GetFieldValue("dtLastUse", dtLastUse);
		pRs.GetFieldValue("nGrade", nGrade);
			

		m_List.InsertItem(i, ltoa(nCNo, buffer, 10));
		m_List.SetItemText(i, nSubItem++, sCName);
		m_List.SetItemText(i, nSubItem++, sDong);
		m_List.SetItemText(i, nSubItem++, sLocation);
		m_List.SetItemText(i, nSubItem++, GetDashPhoneNumber(sTel1));
		m_List.SetItemText(i, nSubItem++, dtLastUse.Format("%m-%d %H:%M"));

		CString strGrade;
		switch(nGrade)
		{
			case 0:
				strGrade = "우수함";	break;
			case 1:
				strGrade = "좋음"; break;
			case 2:
				strGrade = "보통"; break;
			case 3:
				strGrade = "안좋음"; break;
			case 4:
				strGrade = "불량함"; break;
		}
				
		m_List.SetItemText(i, nSubItem++, strGrade);					

		nCount++;
		
		pRs.MoveNext();
	}
	
	pRs.Close();
		
	
	
}
*/

void CDriverDetailAddDlg::OnBnClickedCancelButton()
{
	OnCancel();
}


