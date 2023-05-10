// RequestDrawingDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "RequestDrawingDlg.h"
#include ".\RequestDrawingDlg.h"
#include "MyReportPaintManager.h"
#include "ShareReportRateDlg.h"



CAccountLogRecord::CAccountLogRecord(COleDateTime dtGenerate,CString sState,long nDeposit,long nBalance,CString sEtc)
{
	AddItem(new CMyDateRecordItem(dtGenerate));
	AddItem(new CXTPGridRecordItemText(sState));
	AddItem(new CXTPGridRecordItemNumber(nDeposit));
	AddItem(new CXTPGridRecordItemNumber(nBalance));
	AddItem(new CXTPGridRecordItemText(sEtc));
}


void CAccountLogRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	long lVal = ((CXTPGridRecordItemNumber*)GetItem(2))->GetValue();
	if( lVal < 0)
	{
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(255, 222, 222);
	}
	else
	{
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(222, 222, 255);
	}

	int nCol = pDrawArgs->pColumn->GetIndex();
	if(nCol == 2 || nCol == 3)
	{
		pDrawArgs->nTextAlign = 2;
	}
}


CWaitDrawingRecord::CWaitDrawingRecord(long nCompany,
			COleDateTime dtGenerate,
			CString strCompany, 
			long nBalance,
			CString strState, 
			long nRequestBalance,
			CString strBank,
			CString strAccount,
			CString strDeposit,
			CString strEtc,
			CString strReason,
			long nBankCode,
			CString strPhone,
			BOOL bRcpIntMode1)
{
	m_nCompany = nCompany;
	m_nBalance = nBalance;
	m_nRequestBalance = nRequestBalance;
	m_nBankCode = nBankCode;
	m_strPhone = strPhone;
	m_bRcpIntMode1 = bRcpIntMode1;

	AddItem(new CXTPGridRecordItemText(strCompany));
	AddItem(new CXTPGridRecordItemMyNumber(nBalance));
	AddItem(new CXTPGridRecordItemText(strState));
	AddItem(new CXTPGridRecordItemMyNumber(nRequestBalance));
	AddItem(new CMyDateRecordItem(dtGenerate));
	AddItem(new CXTPGridRecordItemText(strBank));
	AddItem(new CXTPGridRecordItemText(strAccount));
	AddItem(new CXTPGridRecordItemText(strDeposit));
	AddItem(new CXTPGridRecordItemText(strEtc));
	AddItem(new CXTPGridRecordItemText(strReason));

	if(strState.Find("���") >= 0)
	{
		CXTPGridRecordItem *pItem = AddItem(new CXTPGridRecordItemText("���")); 
		pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));
	}
	else
	{
		CXTPGridRecordItem *pItem = AddItem(new CXTPGridRecordItemText("���")); 
		pItem->AddHyperlink(new CXTPGridHyperlink(0, 0xFFFF));
	}
}


void CWaitDrawingRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CString strState = ((CXTPGridRecordItemText*)GetItem(5))->GetValue();
	if(strState == "���")
	{
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(222, 255, 222);
	}
	else if(strState == "���")
	{
		pItemMetrics->clrForeground = RGB(0, 0, 0);
		pItemMetrics->clrBackground = RGB(255, 222, 222);
	}

}


// CRequestDrawingDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRequestDrawingDlg, CMyDialog)
CRequestDrawingDlg::CRequestDrawingDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRequestDrawingDlg::IDD, pParent)
{
	m_nCompany = m_ci.m_nCompanyCode;
}

CRequestDrawingDlg::~CRequestDrawingDlg()
{
}

void CRequestDrawingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_CTRL, m_wndReport);
	DDX_Control(pDX, IDC_REPORT_CTRL2, m_lstWait);
	DDX_Control(pDX, IDC_BANK_COMBO, m_cmbBank);
	DDX_Control(pDX, IDC_ACCOUNT_EDIT, m_edtAccount);
	DDX_Control(pDX, IDC_DEPOSIT_NAME_EDIT, m_edtDepositName);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_edtPhone);
	DDX_Control(pDX, IDC_AMOUNT_EDIT, m_edtAmount);
	DDX_Control(pDX, IDC_SHARE_BALANCE_EDIT, m_edtShareBalance);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);
	DDX_Control(pDX, IDC_LOG_TYPE_COMBO, m_cmbLogType);
}


BEGIN_MESSAGE_MAP(CRequestDrawingDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_DRAWING_BTN, OnBnClickedDarwingBtn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_CTRL2, OnReportItemClick)

	ON_CBN_SELCHANGE(IDC_LOG_TYPE_COMBO, OnCbnSelchangeLogTypeCombo)
END_MESSAGE_MAP()


// CRequestDrawingDlg �޽��� ó�����Դϴ�.

BOOL CRequestDrawingDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_wndReport.GetImageManager()->SetIcons(IDB_BMREPORT, 0, 0, CSize(16, 16));
	CXTPGridColumn* pCol0 = m_wndReport.AddColumn(new CXTPGridColumn(0, _T("����"), 120, FALSE));
	CXTPGridColumn* pCol1 = m_wndReport.AddColumn(new CXTPGridColumn(1, _T("����"), 100, FALSE));
	CXTPGridColumn* pCol2 = m_wndReport.AddColumn(new CXTPGridColumn(2, _T("��/��ݾ�"), 80, FALSE));
	CXTPGridColumn* pCol3 = m_wndReport.AddColumn(new CXTPGridColumn(3, _T("�����ܾ�"), 80, FALSE));
	CXTPGridColumn* pCol4 = m_wndReport.AddColumn(new CXTPGridColumn(4, _T("����"), 550, FALSE));

	m_wndReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_wndReport.SetTreeIndent(10);
	m_wndReport.GetPaintManager()->m_strNoItems = "ǥ���� ����� �������� ����";
	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);
	m_wndReport.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_wndReport.AllowEdit(FALSE);
	m_wndReport.FocusSubItems(FALSE);
	m_wndReport.Populate();
	m_wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_wndReport.SetGridColor(RGB(222, 222, 222));


	CXTPGridColumn* pColx0 = m_lstWait.AddColumn(new CXTPGridColumn(0, _T("ȸ���"), 80, FALSE));
	CXTPGridColumn* pColx1 = m_lstWait.AddColumn(new CXTPGridColumn(1, _T("�ܾ�"), 70, FALSE));
	CXTPGridColumn* pColx2 = m_lstWait.AddColumn(new CXTPGridColumn(2, _T("����"), 50, FALSE));
	CXTPGridColumn* pColx3 = m_lstWait.AddColumn(new CXTPGridColumn(3, _T("��û�ݾ�"), 60, FALSE));
	CXTPGridColumn* pColx4 = m_lstWait.AddColumn(new CXTPGridColumn(4, _T("��û����"), 80, FALSE));
	CXTPGridColumn* pColx5 = m_lstWait.AddColumn(new CXTPGridColumn(5, _T("����"), 40, FALSE));
	CXTPGridColumn* pColx6 = m_lstWait.AddColumn(new CXTPGridColumn(6, _T("����"), 90, FALSE));
	CXTPGridColumn* pColx7 = m_lstWait.AddColumn(new CXTPGridColumn(7, _T("������"), 50, FALSE));
	CXTPGridColumn* pColx8 = m_lstWait.AddColumn(new CXTPGridColumn(8, _T("����"), 110, FALSE));
	CXTPGridColumn* pColx9 = m_lstWait.AddColumn(new CXTPGridColumn(9, _T("��û���"), 110, FALSE));
	CXTPGridColumn* pColx10 = m_lstWait.AddColumn(new CXTPGridColumn(10, _T("��û"), 40, FALSE));

	pColx1->SetAlignment(DT_RIGHT);
	pColx2->SetAlignment(DT_CENTER);
	pColx3->SetAlignment(DT_RIGHT);
	pColx4->SetAlignment(DT_CENTER);
	pColx10->SetAlignment(DT_CENTER);

	m_lstWait.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_lstWait.SetTreeIndent(10);
	m_lstWait.GetPaintManager()->m_strNoItems = "��� �ܾ��� �ִ� ���簡 ������������";
	m_lstWait.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstWait.GetReportHeader()->AllowColumnResize(TRUE);
	m_lstWait.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstWait.GetReportHeader()->AllowColumnSort(TRUE);
	m_lstWait.AllowEdit(FALSE);
	m_lstWait.FocusSubItems(FALSE);
	m_lstWait.Populate();
	m_lstWait.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstWait.SetGridColor(RGB(222, 222, 222));

	m_cmbLogType.SetCurSel(1);

	MakeBankList(&m_cmbBank);
	RefreshDrawingInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CRequestDrawingDlg::RefreshDrawingInfo()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_request_drawing_info");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);

	CString strAccount;
	m_lstWait.GetRecords()->RemoveAll();

	if(pRs.Execute(&pCmd))
	{
		long nID, nBalance, nRequestBalance;
		CString strBranchName;
		COleDateTime dtGenerate;
		CString strBank, strAccount, strOwner;
		CString strPhone;
		CString strEtc;
		CString strDepositName;
		BOOL bCompleted;
		COleDateTime dtCompleted;
		BOOL bReject;
		CString strRejectReason;
		long nBankCode;
		BOOL bRcpIntMode1;

		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("nID", nID);
			pRs.GetFieldValue("sBranchName", strBranchName);
			pRs.GetFieldValue("nBalance", nBalance);
			pRs.GetFieldValue("dtGenerate", dtGenerate);
			pRs.GetFieldValue("sBank", strBank);
			pRs.GetFieldValue("sAccount", strAccount);
			pRs.GetFieldValue("sOwner", strOwner);
			pRs.GetFieldValue("sPhone", strPhone);
			pRs.GetFieldValue("sEtc", strEtc);
			pRs.GetFieldValue("sDepositName", strDepositName);
			pRs.GetFieldValue("bCompleted", bCompleted);
			pRs.GetFieldValue("dtCompleted", dtCompleted);
			pRs.GetFieldValue("bReject", bReject);
			pRs.GetFieldValue("sRejectReason", strRejectReason);
			pRs.GetFieldValue("nRequestBalance", nRequestBalance);
			pRs.GetFieldValue("nBankCode", nBankCode);
			pRs.GetFieldValue("bRcpIntMode1", bRcpIntMode1);

			CString strState;
			if(bCompleted)
				strState = "�Ϸ�";
			else if(bReject)
				strState = "���";
			else if(nRequestBalance != 0)
				strState = "���";
	

			m_lstWait.AddRecord(new CWaitDrawingRecord(nID, 
					dtGenerate, 
					strBranchName,
					nBalance, 
					strState,
					nRequestBalance,
					strBank,
					strAccount, 
					strDepositName,
					strEtc, 
					strRejectReason, 
					nBankCode,
					strPhone, 
					bRcpIntMode1));

					
			pRs.MoveNext();
		}

		m_lstWait.Populate();
	}
}

void CRequestDrawingDlg::OnBnClickedOk()
{
	OnOK();
}

void CRequestDrawingDlg::OnBnClickedRefreshBtn()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_branch_share_account_log_simple");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(m_cmbLogType.GetCurSel());

	CString strAccount;

	m_wndReport.GetRecords()->RemoveAll();

	if(pRs.Execute(&pCmd))
	{
		long nDeposit,nBalance;
		CString sState,sEtc;
		COleDateTime dtGenerate;


		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("dtGenerate", dtGenerate);
			pRs.GetFieldValue("sState", sState);
			pRs.GetFieldValue("nDeposit", nDeposit);
			pRs.GetFieldValue("nBalance", nBalance);
			pRs.GetFieldValue("sEtc", sEtc);

			m_wndReport.AddRecord(new CAccountLogRecord(dtGenerate, sState, nDeposit, nBalance, sEtc) );

			pRs.MoveNext();
		}

		m_wndReport.Populate();
	}
}

void CRequestDrawingDlg::OnBnClickedDarwingBtn()
{
	if(!POWER_CHECK(1040, "��ݿ�û", TRUE))
		return;

	long nBankCode = m_cmbBank.GetItemData(m_cmbBank.GetCurSel());
	CString strAccount, strDepositName, strPhone, strAmount, strShareBalance;
	CString strEtc;

	m_edtAccount.GetWindowText(strAccount);
	m_edtDepositName.GetWindowText(strDepositName);
	m_edtPhone.GetWindowText(strPhone);
	m_edtAmount.GetWindowText(strAmount);
	m_edtShareBalance.GetWindowText(strShareBalance);
	m_edtEtc.GetWindowText(strEtc);

	int nAmount = 0, nShareBalance = 0;

	try {
		if(nBankCode < 0)
			throw "������ �����ϼ���.";

		if(strAccount.GetLength() < 7)
			throw "���¹�ȣ�� �Է��ϼ���.";

		if(strDepositName.GetLength() < 2)
			throw "�����ָ� �Է��Ͻñ� �ٶ��ϴ�.";

		if(strPhone.GetLength() < 8)
			throw "SMS���� ������ �޴�����ȣ�� �Է��ϼ���.";

		nAmount = GetNoneCommaNumber(strAmount);

		if(nAmount < 100 || nAmount > 50000000)
			throw "1ȸ ��� ���ɱݾ��� 100��~5000�����Դϴ�.";

		nShareBalance = GetNoneCommaNumber(strShareBalance);

		if(nShareBalance < nAmount)
			throw "�ܾ��� �����մϴ�. ��ݿ�û�ݾ��� �ٿ��ֽñ� �ٶ��ϴ�.";
	}
	catch(char *msg)
	{
		MessageBox(msg, "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "insert_balance_drawing_info2");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(nBankCode);
	pCmd.AddParameter(strAccount);
	pCmd.AddParameter(strDepositName);
	pCmd.AddParameter(strPhone);
	pCmd.AddParameter(nAmount);
	pCmd.AddParameter(strEtc);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(m_ei.strMac1);
	pCmd.AddParameter(GetHddId().TrimLeft());

	if(!pCmd.Execute())
	{
		MessageBox("��ݿ�û�� ���еǾ����ϴ�. ��õ� �Ͻñ� �ٶ��ϴ�.", "����", MB_ICONERROR);
	}
	else
	{
		if(parRet->GetLong() == 9)
		{
			MessageBox("�̹� ��ݿ�û�� �Ͻ� �����Դϴ�.\n\n����Ŀ� ���û���ֽñ� �ٶ��ϴ�.", 
				"Ȯ��",
				MB_ICONINFORMATION);
		}
		else if(parRet->GetLong() == 10)
		{
			MessageBox("���� ��������� �������� �����, ��ݿ�û�� �ϽǼ� �����ϴ�.\n\n"\
					"�ִ� 30�� ���� �ɸ� �����Դϴ�. ������ ����� �˼��մϴ�.", 
					"Ȯ��",
					MB_ICONINFORMATION);
		}
		else if(parRet->GetLong() == 11)
		{
			MessageBox("��û�Ͻűݾ��� ����Ͻ� �� �����ϴ�.", 
				"Ȯ��",
				MB_ICONINFORMATION);
		}
		else if(parRet->GetLong() == 12)
		{
			MessageBox("��� ��û ó���� ������ �߻��Ͽ����ϴ�.\n\n��õ� �Ͻñ� �ٶ��ϴ�!", 
				"Ȯ��",
				MB_ICONINFORMATION);
		}
		else
		{
			RefreshDrawingInfo();
			OnBnClickedRefreshBtn();
			MessageBox("���������� ��ݿ�û�Ǿ����ϴ�.\n\n�����̳��� �Ա�ó���˴ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		}
	}
}

void CRequestDrawingDlg::MakeBankList(CComboBox *pCombo)
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_bank_list");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);

	if(pRs.Execute(&pCmd))
	{
		while(!pRs.IsEOF())
		{
			long nID;
			CString strBankName;

			pRs.GetFieldValue("nID", nID);
			pRs.GetFieldValue("sBankName", strBankName);

			int nItem = pCombo->AddString(strBankName);
			pCombo->SetItemData(nItem, nID);

			pRs.MoveNext();
		}
	}
}


void CRequestDrawingDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CXTPGridRecords *pRecords = m_lstWait.GetRecords();
	CXTPGridRecord *pRecord = pItemNotify->pRow->GetRecord();

	CXTPGridColumn* pColumn = NULL;
	CString strCompany = ((CXTPGridRecordItemText*)pRecord->GetItem(0))->GetCaption(pColumn);
	long nBalance = ((CWaitDrawingRecord*)pRecord)->m_nBalance;
	long nRequestBalance = ((CWaitDrawingRecord*)pRecord)->m_nRequestBalance;
	CString strBank = ((CXTPGridRecordItemText*)pRecord->GetItem(5))->GetCaption(pColumn);
	CString strAccount = ((CXTPGridRecordItemText*)pRecord->GetItem(6))->GetCaption(pColumn);
	CString strDeposit = ((CXTPGridRecordItemText*)pRecord->GetItem(7))->GetCaption(pColumn);
	CString strEtc = ((CXTPGridRecordItemText*)pRecord->GetItem(8))->GetCaption(pColumn);
	CString strReason = ((CXTPGridRecordItemText*)pRecord->GetItem(9))->GetCaption(pColumn);
	long nBankCode =  ((CWaitDrawingRecord*)pRecord)->m_nBankCode;
	CString strPhone = ((CWaitDrawingRecord*)pRecord)->m_strPhone;
	m_nCompany = ((CWaitDrawingRecord*)pRecord)->m_nCompany;

	m_edtCompany.SetWindowText(strCompany);
	m_edtShareBalance.SetWindowText(GetMyNumberFormat(nBalance));
	m_edtAmount.SetWindowText(GetMyNumberFormat(nRequestBalance));
	m_edtDepositName.SetWindowText(strDeposit);

	for(int i = 0; i < m_cmbBank.GetCount(); i++) {
		if(m_cmbBank.GetItemData(i) == nBankCode)
			m_cmbBank.SetCurSel(i);
	}
	
	m_edtAccount.SetWindowText(strAccount);
	m_edtPhone.SetWindowText(strPhone);

	if(nCol == 10)
	{
		MessageBox("�����ҿ�û�� �ϽǼ� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;

		CString strState = ((CXTPGridRecordItemText*)pRecord->GetItem(10))->GetCaption(pColumn);
		if(strState == "���")
		{
			if(IDYES == MessageBox("��ݿ�û�� ����Ͻðڽ��ϱ�?", "��ݿ�û���", MB_ICONQUESTION | MB_YESNO))
			{
				CancelRequestDrawing();
			}
		}

	}

	OnBnClickedRefreshBtn();
}


void CRequestDrawingDlg::OnCbnSelchangeLogTypeCombo()
{
	OnBnClickedRefreshBtn();
}

void CRequestDrawingDlg::CancelRequestDrawing()
{
	CMkCommand pCmd(m_pMkDb, "update_request_drawing_state_cancel");
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter("�������");

	if(!pCmd.Execute())
	{
		MessageBox("��ݿ�û ���ó���� ���еǾ����ϴ�.\n\n��õ� �Ͻñ� �ٶ��ϴ�.", "����", MB_ICONERROR);
	}
	else
	{
		if(parRet->GetLong() == 10)
		{
			MessageBox("���� ��������� �������� �����, ���ó���� �ϽǼ� �����ϴ�.",
				"Ȯ��",
				MB_ICONINFORMATION);
		}
		else if(parRet->GetLong() == 12)
		{
			MessageBox("ó���߿� ������ �߻��Ͽ����ϴ�.\n\n��õ� �ٶ��ϴ�.",
				"Ȯ��",
				MB_ICONINFORMATION);
		}
		else
		{
			RefreshDrawingInfo();
			MessageBox("��ҵǾ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		}
	}
}