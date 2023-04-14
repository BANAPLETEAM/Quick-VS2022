// OptionDlgCID.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OptionDlgCID.h"

#include "MainOptionDlg2011.h"

// COptionDlgCID

IMPLEMENT_DYNCREATE(COptionDlgCID, CMyFormView)

COptionDlgCID::COptionDlgCID()
	: CMyFormView(COptionDlgCID::IDD)
{
}

COptionDlgCID::~COptionDlgCID()
{
}

void COptionDlgCID::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_CID_POOL_CHECK, m_UseCidPoolCheck);
	DDX_Check(pDX, IDC_USE_CID_POOL_CHECK, m_bUseCidPool);
	DDX_Control(pDX, IDC_CID_NONFIXED_INTEGRATION_TAB, m_CidNonfixedIntegrationTabCheck);
	DDX_Check(pDX, IDC_CID_NONFIXED_INTEGRATION_TAB, m_bCidNonfixedIntegrationTab);
	DDX_Control(pDX, IDC_CALLING_LINE_EDIT, m_CallingLineEdit);
	DDX_Text(pDX, IDC_CALLING_LINE_EDIT, m_strCallingLine);
	DDX_Control(pDX, IDC_REVISIT_CUSTOMER_STATIC, m_chkRevisitCustomer);
	DDX_Control(pDX, IDC_REVISIT_EDIT, m_edtRevisitCustomer);
	DDX_Control(pDX, IDC_REVISIT_CUSTOMER_COMBO, m_cmbRevisitCustomer);
	DDX_Control(pDX, IDC_COMPANY_CALLING_CHECK, m_chkCompanyCalllingLine);
	DDX_Control(pDX, IDC_CALLING_STATIC, m_stcCalllingLine);
	DDX_Control(pDX, IDC_CALLING_STATIC2, m_stcCalllingLine2);
	DDX_Control(pDX, IDC_CALLING_STATIC3, m_stcCalllingLine3);
}

BEGIN_MESSAGE_MAP(COptionDlgCID, CMyFormView)
	ON_WM_ACTIVATE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_MDIACTIVATE()
	ON_MESSAGE(WM_REFRESH, OnRefresh )
	ON_EN_CHANGE(IDC_CALLING_LINE_EDIT, OnEnChangeCalllingLineEdit)		 
	ON_BN_CLICKED(IDC_REVISIT_CUSTOMER_STATIC, OnBnClickedRevisitCustomerStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// COptionDlgCID 진단입니다.

#ifdef _DEBUG
void COptionDlgCID::AssertValid() const
{
	CMyFormView::AssertValid();
}

void COptionDlgCID::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// COptionDlgCID 메시지 처리기입니다.
void COptionDlgCID::OnInitialUpdate()
{	
	CMyFormView::OnInitialUpdate();


	SetOptiobView(TRUE);

	if(!POWER_CHECK(1302, "키폰"))
		EnableWindow(FALSE);



}

long COptionDlgCID::OnRefresh(WPARAM wParam,LPARAM lParam)
{
	CMkRecordset* pRs = (CMkRecordset*)lParam;
/*
	pRs->GetFieldValue("bUseCidPool", m_bUseCidPool);
	pRs->GetFieldValue("bCidNonfixedIntegrationTab", m_bCidNonfixedIntegrationTab);
	pRs->GetFieldValue("sCallingLine", m_strCallingLine);

	if(m_bUseCidPool) m_bUseCidPool = TRUE;
	if(m_bCidNonfixedIntegrationTab) m_bCidNonfixedIntegrationTab = TRUE;
	UpdateData(FALSE);
*/
	return 0L;
}

void COptionDlgCID::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CMyFormView::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

int COptionDlgCID::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;
//	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void COptionDlgCID::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMyFormView::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void COptionDlgCID::OnEnChangeCalllingLineEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우 이 컨트롤은
	// CMyFormView::마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여
	// CRichEditCtrl().SetEventMask()를 호출하도록 OnInitDialog() 함수를 재지정하지 않으면
	// 이 알림을 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COptionDlgCID::OnBnClickedRevisitCustomerStatic()
{
	m_edtRevisitCustomer.EnableWindow(m_chkRevisitCustomer.GetCheck());
	m_cmbRevisitCustomer.EnableWindow(m_chkRevisitCustomer.GetCheck());
}

BOOL COptionDlgCID::Save(long nCompany, BOOL bAll)
{
	UpdateData(TRUE);

	if(m_strCallingLine == m_strOriginCallingLine + m_strOriginCallingAuccountDID)
	{
		long nRevisitCustomerSendDay = 0, nRevisitCustomerSendCompany = 0;
		CString sRevisitDay = "";
		if(m_chkRevisitCustomer.GetCheck())
		{
			m_edtRevisitCustomer.GetWindowText(sRevisitDay);
			nRevisitCustomerSendDay = atol(sRevisitDay);
			if(sRevisitDay.GetLength() ==0 || nRevisitCustomerSendDay < 0 )
			{
				MessageBox("최근 몇일 동안 사용안한 고객의 일수가 0 이하 입니다.", "확인", MB_ICONINFORMATION);
				return FALSE;
			}
			nRevisitCustomerSendCompany = m_cmbRevisitCustomer.GetItemData(
				m_cmbRevisitCustomer.GetCurSel());
		}

		CMkCommand pCmd(m_pMkDb, "update_option_2011_cid_1");	//   명칭을 2011
		pCmd.AddParameter(bAll);
		pCmd.AddParameter(nCompany);
		pCmd.AddParameter( m_UseCidPoolCheck.GetCheck());
		pCmd.AddParameter(m_CidNonfixedIntegrationTabCheck.GetCheck());
		pCmd.AddParameter(m_strCallingLine);
		pCmd.AddParameter(m_chkRevisitCustomer.GetCheck());	
		pCmd.AddParameter(nRevisitCustomerSendDay);
		pCmd.AddParameter(nRevisitCustomerSendCompany);	
		pCmd.AddParameter(m_ui.strID);

		return pCmd.Execute();
	}

	if(m_strCallingLine.Find("A") != -1)
	{
		if(m_chkCompanyCalllingLine.GetCheck())
		{
			CString strTemp = GetIPPBXOutboundCID(FALSE);
			CString strCallingAccountDID = "";
			if(m_strCallingLine.Find("B") != -1)
			{
				int nAIndex = m_strCallingLine.Find("A");
				int nBIndex = m_strCallingLine.Find("B");
				if(nAIndex < nBIndex)
					strCallingAccountDID = m_strCallingLine.Right(m_strCallingLine.GetLength() - nAIndex - 1);
			}

			if(m_strCallingLine != strTemp + strCallingAccountDID)
			{
				MessageBox("연결번호와 대표번호가 맞지않아 키폰설정은 저장되지 않습니다.\n지사 대표번호 사용 체크박스를 선택후 저장해주세요.", "확인", MB_ICONINFORMATION);
				return TRUE;
			}

			if(strCallingAccountDID.GetLength() > 0)
			{
				strCallingAccountDID.Replace("B", "");
				
				CMkCommand pCmd(m_pMkDb, "select_New_Telserver_Info_1");
				CMkRecordset pRs(m_pMkDb);
				pCmd.AddParameter(m_ba.GetAt(0)->nCompanyCode);

				if(pRs.Execute(&pCmd))
				{
					CString sCIDCheckDID;
					while(!pRs.IsEOF()) 
					{
						pRs.GetFieldValue("sCIDCheckDID", sCIDCheckDID);

						pRs.MoveNext();
					}
					
					if(sCIDCheckDID.GetLength() == 0)
					{
						MessageBox("텔서버 정보가 없습니다.\n로지소프트로 문의해주세요.", "확인", MB_ICONINFORMATION);
						return TRUE;
					}

					sCIDCheckDID = CString(",") + sCIDCheckDID + CString(",");
					if(::IsDID(atol(strCallingAccountDID.Right(8)), sCIDCheckDID) == FALSE)
					{
						CString strMsg = CString("텔서버 정보가 일치하지 않습니다.\n") + strCallingAccountDID + CString(" 번호를 확인해주세요.");
						MessageBox(strMsg, "확인", MB_ICONINFORMATION);
						return TRUE;
					}
				}
				else
				{
					MessageBox("정보를 가져오지 못했습니다.\n다시 시도해주세요.", "확인", MB_ICONINFORMATION);
					return TRUE;
				}
			}
		}
		else
		{
			MessageBox("연결번호에 A가 포함되어 키폰설정은 저장되지 않습니다.\n지사 대표번호 사용 체크박스를 선택후 저장해주세요.", "확인", MB_ICONINFORMATION);
			return TRUE;
		}
	}

	long nRevisitCustomerSendDay = 0, nRevisitCustomerSendCompany = 0;
	CString sRevisitDay = "";
	if(m_chkRevisitCustomer.GetCheck())
	{
		m_edtRevisitCustomer.GetWindowText(sRevisitDay);
		nRevisitCustomerSendDay = atol(sRevisitDay);
		if(sRevisitDay.GetLength() ==0 || nRevisitCustomerSendDay < 0 )
		{
			MessageBox("최근 몇일 동안 사용안한 고객의 일수가 0 이하 입니다.", "확인", MB_ICONINFORMATION);
			return FALSE;
		}
		nRevisitCustomerSendCompany = m_cmbRevisitCustomer.GetItemData(
			m_cmbRevisitCustomer.GetCurSel());

	}
	
	CMkCommand pCmd(m_pMkDb, "update_option_2011_cid_1");	//   명칭을 2011
	pCmd.AddParameter(bAll);
	pCmd.AddParameter(nCompany);
	pCmd.AddParameter( m_UseCidPoolCheck.GetCheck());
	pCmd.AddParameter(m_CidNonfixedIntegrationTabCheck.GetCheck());
	pCmd.AddParameter(m_strCallingLine);
	pCmd.AddParameter(m_chkRevisitCustomer.GetCheck());	
	pCmd.AddParameter(nRevisitCustomerSendDay);
	pCmd.AddParameter(nRevisitCustomerSendCompany);	
	pCmd.AddParameter(m_ui.strID);
	
	return pCmd.Execute();
}

CString COptionDlgCID::GetIPPBXOutboundCID(BOOL bOffice)
{
	CMainOptionDlg2* pDlg = (CMainOptionDlg2*)GetParent()->GetParent(); 

	long nCompanyCode = pDlg->GetSelCompanyCode(); 

	CBranchInfo *pBI = GetBranchInfo(nCompanyCode);

	CString strDDD = "", strLine;

	if(bOffice == FALSE)
		strLine = ::GetNoneDashNumber(pBI->strPhone);
	//else
	//	strLine = ::GetNoneDashNumber(pBI->strOfficePhone);

	if(strLine.GetLength() < 7 || !::IsStringDigit(strLine))
		strLine = "";
	else
		strDDD = pBI->strDDD;

	if(strLine.GetLength() > 0)
	{
		//전국 대표번호 세칙
		if(strLine.Left(1).Compare("1") == 0)
		{
			if(strLine.GetLength() > 8)
				strLine = strLine.Left(8);
		}

		if(strLine.Left(1) != "0")
			strLine = strDDD + strLine;

		return strLine + "A";
	}
	
	return "";
}

void COptionDlgCID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CMyFormView::OnPaint()을(를) 호출하지 마십시오.
}
