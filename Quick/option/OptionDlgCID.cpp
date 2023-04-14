// OptionDlgCID.cpp : ���� �����Դϴ�.
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


// COptionDlgCID �����Դϴ�.

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


// COptionDlgCID �޽��� ó�����Դϴ�.
void COptionDlgCID::OnInitialUpdate()
{	
	CMyFormView::OnInitialUpdate();


	SetOptiobView(TRUE);

	if(!POWER_CHECK(1302, "Ű��"))
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

int COptionDlgCID::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return TRUE;
//	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void COptionDlgCID::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMyFormView::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void COptionDlgCID::OnEnChangeCalllingLineEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ��� �� ��Ʈ����
	// CMyFormView::����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ�
	// CRichEditCtrl().SetEventMask()�� ȣ���ϵ��� OnInitDialog() �Լ��� ���������� ������
	// �� �˸��� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
				MessageBox("�ֱ� ���� ���� ������ ���� �ϼ��� 0 ���� �Դϴ�.", "Ȯ��", MB_ICONINFORMATION);
				return FALSE;
			}
			nRevisitCustomerSendCompany = m_cmbRevisitCustomer.GetItemData(
				m_cmbRevisitCustomer.GetCurSel());
		}

		CMkCommand pCmd(m_pMkDb, "update_option_2011_cid_1");	//   ��Ī�� 2011
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
				MessageBox("�����ȣ�� ��ǥ��ȣ�� �����ʾ� Ű�������� ������� �ʽ��ϴ�.\n���� ��ǥ��ȣ ��� üũ�ڽ��� ������ �������ּ���.", "Ȯ��", MB_ICONINFORMATION);
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
						MessageBox("�ڼ��� ������ �����ϴ�.\n��������Ʈ�� �������ּ���.", "Ȯ��", MB_ICONINFORMATION);
						return TRUE;
					}

					sCIDCheckDID = CString(",") + sCIDCheckDID + CString(",");
					if(::IsDID(atol(strCallingAccountDID.Right(8)), sCIDCheckDID) == FALSE)
					{
						CString strMsg = CString("�ڼ��� ������ ��ġ���� �ʽ��ϴ�.\n") + strCallingAccountDID + CString(" ��ȣ�� Ȯ�����ּ���.");
						MessageBox(strMsg, "Ȯ��", MB_ICONINFORMATION);
						return TRUE;
					}
				}
				else
				{
					MessageBox("������ �������� ���߽��ϴ�.\n�ٽ� �õ����ּ���.", "Ȯ��", MB_ICONINFORMATION);
					return TRUE;
				}
			}
		}
		else
		{
			MessageBox("�����ȣ�� A�� ���ԵǾ� Ű�������� ������� �ʽ��ϴ�.\n���� ��ǥ��ȣ ��� üũ�ڽ��� ������ �������ּ���.", "Ȯ��", MB_ICONINFORMATION);
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
			MessageBox("�ֱ� ���� ���� ������ ���� �ϼ��� 0 ���� �Դϴ�.", "Ȯ��", MB_ICONINFORMATION);
			return FALSE;
		}
		nRevisitCustomerSendCompany = m_cmbRevisitCustomer.GetItemData(
			m_cmbRevisitCustomer.GetCurSel());

	}
	
	CMkCommand pCmd(m_pMkDb, "update_option_2011_cid_1");	//   ��Ī�� 2011
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
		//���� ��ǥ��ȣ ��Ģ
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CMyFormView::OnPaint()��(��) ȣ������ ���ʽÿ�.
}
