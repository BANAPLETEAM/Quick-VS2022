// CustomerSmsDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerSmsDlg.h"

#include "MentDlg.h"
#include "ReservationListDlg.h"
#include "SMSStateDlg.h"


// CCustomerSmsDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCustomerSmsDlg, CMyDialog)
CCustomerSmsDlg::CCustomerSmsDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CCustomerSmsDlg::IDD, pParent)
, m_strBalance(_T(""))
, m_strSMSCount(_T(""))
{
	m_dtDate = COleDateTime::GetCurrentTime();
	m_dtTime = COleDateTime::GetCurrentTime();
	m_bNotified = FALSE;
}

CCustomerSmsDlg::~CCustomerSmsDlg()
{
}

void CCustomerSmsDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);	

	DDX_Text(pDX, IDC_MENT_EDIT, m_strMent);	
	DDX_Text(pDX, IDC_COMPANY_PHONE_EDIT, m_m_strCompanyPhone);	
	DDX_Text(pDX, IDC_SMS_BARANCE_STATIC, m_strBalance);
	DDX_Text(pDX, IDC_SMS_COUNT_STATIC, m_strSMSCount);

	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_COUNT_STATIC, m_stcCount);
	DDX_Control(pDX, IDC_ISBRAN_STATIC, m_stcBranch);

	DDX_Control(pDX, IDC_IN_DAY_COMBO, m_cmbInDay);
	DDX_Control(pDX, IDC_DM_SENT_COMBO, m_cmbDMSent);
	DDX_Control(pDX, IDC_NEW_CUSTOMER_COMBO, m_cmbNewCustomer);
	DDX_Control(pDX, IDC_DM_COUNT_COMBO, m_cmbDmCount);
	DDX_Control(pDX, IDC_CTYPE_CHECK1, m_CTypeCheck1);
	DDX_Control(pDX, IDC_CTYPE_CHECK2, m_CTypeCheck2);	
	DDX_Control(pDX, IDC_SEND_COUNT_COMBO, m_cmbSendCount);

	DDX_Control(pDX, IDC_TIME1, m_dtpTime);
	DDX_Control(pDX, IDC_LENGTH_STATIC, m_stcLength);
	DDX_DateTimeCtrl(pDX, IDC_DATE1, m_dtDate);
	DDX_DateTimeCtrl(pDX, IDC_TIME1, m_dtTime);
	DDX_Control(pDX, IDC_DIVISION_CHECK, m_DivisionCheck);
	DDX_Control(pDX, IDC_COMPANY_PHONE_EDIT, m_edtCompanyPhone);
	DDX_Control(pDX, IDC_MENT_EDIT, m_edtMent);

	DDX_Control(pDX, IDOK, m_btnConfirm);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, ID_RESERVATION_CANCEL_BTN, m_btnReservationCancel);	
	DDX_Control(pDX, IDC_DATE1, m_dtpDate);
	DDX_Control(pDX, IDC_STATE_BUTTON, m_btnSMSState);
	DDX_Control(pDX, IDC_EDIT_MENT_BTN, m_btnSMSMent);
}


BEGIN_MESSAGE_MAP(CCustomerSmsDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_EDIT_MENT_BTN, OnBnClickedEditMentBtn)
	ON_EN_CHANGE(IDC_MENT_EDIT, OnEnChangeMentEdit)
	ON_BN_CLICKED(IDC_CTYPE_CHECK1, OnBnClickedCtypeCheck1)
	ON_BN_CLICKED(IDC_CTYPE_CHECK2, OnBnClickedCtypeCheck2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
	ON_WM_TIMER()
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST1, OnLvnDeleteitemList1)
	ON_CBN_SELCHANGE(IDC_IN_DAY_COMBO, OnCbnSelchangeInDayCombo)
	ON_CBN_SELCHANGE(IDC_DM_COUNT_COMBO, OnCbnSelchangeDmCountCombo)
	ON_CBN_SELCHANGE(IDC_NEW_CUSTOMER_COMBO, OnCbnSelchangeNewCustomerCombo)
	ON_CBN_SELCHANGE(IDC_DM_SENT_COMBO, OnCbnSelchangeDmSentCombo)
	ON_CBN_SELCHANGE(IDC_SEND_COUNT_COMBO, OnCbnSelchangeSendCountCombo)
	ON_BN_CLICKED(ID_RESERVATION_CANCEL_BTN, OnBnClickedReservationCancelBtn)
	ON_BN_CLICKED(IDC_STATE_BUTTON, OnBnClickedStateButton)
END_MESSAGE_MAP()


// CCustomerSmsDlg �޽��� ó�����Դϴ�.

BOOL CCustomerSmsDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//SetWindowPos(&CWnd::wndTopMost, 0,0,0, 0, SWP_NOSIZE | SWP_NOMOVE);

	//m_edtMent.SetFontSize(17);
	ST_SMS_INFO smsi;
	smsi = LF->GetSMSBalance(m_nCompany);
	//���ϰ����� �ܾװ� �������� ���Ѵٴ� ���� �ѷ���.  ���Աݰ� �������� ���´�.
	UpdateData(TRUE);
	if(smsi.nSMSType >= 10){ 		

		if(smsi.nSMSBarance <= DEFINE_SMS_AMOUNT - 1 )
		{
			m_strBalance = (smsi.nSMSBarance != 0) ? LF->GetMyNumberFormat(smsi.nSMSBarance) : "0";
			m_btnConfirm.EnableWindow(0);
		}
		else
		{
			m_strBalance = LF->GetMyNumberFormat(smsi.nSMSBarance);
			int nSMCount = smsi.nSMSBarance / DEFINE_SMS_AMOUNT;
			m_strSMSCount.Format("����: %s��", LF->GetMyNumberFormat((long)nSMCount));

		}
	}
	else
	{
		m_strBalance = LF->GetMyNumberFormat(smsi.nSMSBarance);
		int nSMCount = smsi.nSMSBarance / DEFINE_SMS_AMOUNT;
		m_strSMSCount.Format("����: %s��", LF->GetMyNumberFormat((long)nSMCount));
	}

	UpdateData(FALSE);

	m_List.InsertColumn(0, "��ȭ��ȣ", LVCFMT_LEFT,  105);
	m_List.InsertColumn(1, "����", LVCFMT_LEFT,  40);
	m_List.InsertColumn(2, "����", LVCFMT_LEFT, 40);
	m_List.InsertColumn(3, "��������", LVCFMT_LEFT, 75);
	m_List.InsertColumn(4, "DM����", LVCFMT_LEFT, 75);
	m_List.InsertColumn(5, "�űԵ��", LVCFMT_LEFT, 75);
	m_List.InsertColumn(6, "DM����ȸ��", LVCFMT_LEFT, 70);

	m_List.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_CTypeCheck1.SetCheck(1);
	m_CTypeCheck2.SetCheck(1);
	m_cmbSendCount.SetCurSel(0);
	m_cmbDMSent.SetCurSel(0);
	m_cmbDmCount.SetCurSel(0);
	m_cmbNewCustomer.SetCurSel(0);

	m_nInDay = AfxGetApp()->GetProfileInt("sms", "LimitDays", 0);
	m_cmbInDay.SetCurSel(m_nInDay);
	m_dtpTime.SetFormat("tth-mm");

	CString sBranchName = "";
	CBranchInfo *pBi = NULL;
	for(int i = 0; i < m_ba.GetCount(); i++) {
		pBi = m_ba.GetAt(i);
		if(m_nCompany == pBi->nCompanyCode && pBi->bIntegrated == 0)
		{
			sBranchName = pBi->strBranchName;
			break;
		}
		else if(m_nCompany == pBi->nCompanyCode && pBi->bIntegrated == 1)
		{
			pBi = m_ba.GetAt(i+1);	
			sBranchName = pBi->strBranchName;
			break;
		}
	}

	m_stcBranch.SetWindowText("SMS ���������: " + sBranchName);

	int nItem = 0, nType;
	CString strMsg;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_all_ments");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	CMkParameter *parOutCompanyPhone = pCmd.AddParameter(typeString, typeOutput, 25, "");

	if(pRs.Execute(&pCmd)) 
	{
		CString m_strCompanyPhone;
		parOutCompanyPhone->GetValue(m_strCompanyPhone);
		m_edtCompanyPhone.SetWindowText(m_strCompanyPhone);
		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("nType", nType);
			pRs.GetFieldValue("sMsg", strMsg);

			if(nType == m_nType) {
				m_edtMent.SetWindowText(strMsg);
				break;
			}
			pRs.MoveNext();
		}
	}
	pRs.Close();

	MakeCustomerList();
	CheckListCondition();


	CString m_strCompanyPhone;
	m_edtCompanyPhone.GetWindowText(m_strCompanyPhone);
	if(m_strCompanyPhone.GetLength() == 0 || m_strCompanyPhone.GetAt(0) == 'X')
	{
		MessageBox("SMS������ ���ѵ� ȸ�����Դϴ�. ��������Ʈ�� �����Ͻñ� �ٶ��ϴ�.",
			"��������", MB_ICONINFORMATION);
		PostMessage(WM_CLOSE, 0, 0L);
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCustomerSmsDlg::MakeCustomerList()
{
	//CWaitCursor wait;

	int nCount = 0;
	BOOL bNotWanted = TRUE;
	BOOL bShopCustomer = FALSE;
	for(int i = 0; i < m_pSourceList->GetItemCount(); i++)
	{
		CString strPhone = LF->GetNoneDashNumber(m_pSourceList->GetItemText(i, m_nPhoneCol));
		bShopCustomer = m_pSourceList->GetItemText(i, m_nCTypeCol).GetLength() > 0 ? TRUE : FALSE;
		bNotWanted = m_pSourceList->GetItemText(i, m_nNotWantedCol).GetLength() > 0 ? TRUE : FALSE;

		if(bNotWanted == 0 && strPhone.Left(2) == "01")
		{
			ST_CHECK_INFO *stInfo = new ST_CHECK_INFO;		

			stInfo->dtLastSms = COleDateTime();
			if(m_pSourceList->GetItemText(i, m_nLastSentCol).GetLength() > 0)
				stInfo->dtLastSms.ParseDateTime(m_pSourceList->GetItemText(i, m_nLastSentCol));
			else 
				stInfo->dtLastSms.SetStatus(COleDateTime::null);

			stInfo->dtDMLastSms = COleDateTime();
			if(m_pSourceList->GetItemText(i, m_nDMLastSentCol).GetLength() > 0)
				stInfo->dtDMLastSms.ParseDateTime(m_pSourceList->GetItemText(i, m_nDMLastSentCol));
			else 
				stInfo->dtDMLastSms.SetStatus(COleDateTime::null);


			if(m_pSourceList->GetItemText(i, m_nNewCustomerCol).GetLength() > 0)
				stInfo->dtNewCustomer.ParseDateTime(m_pSourceList->GetItemText(i, m_nNewCustomerCol));
			else 
				stInfo->dtNewCustomer.SetStatus(COleDateTime::null);

			CString sDMCount = m_pSourceList->GetItemText(i,m_nDMCount);

			int nItem = m_List.InsertItem(nCount, strPhone); 
			m_List.SetItemText(nItem, 1, bShopCustomer ? "����" : "");
			m_List.SetItemText(nItem, 2, bNotWanted ? "�ź�" : "");
			m_List.SetItemText(nItem, 3, stInfo->dtLastSms.Format("%Y-%m-%d"));
			m_List.SetItemText(nItem, 4, stInfo->dtDMLastSms.Format("%Y-%m-%d"));
			m_List.SetItemText(nItem, 5, stInfo->dtNewCustomer.Format("%Y-%m-%d"));
			m_List.SetItemText(nItem, 6, sDMCount);
			m_List.SetItemData(nItem, (DWORD_PTR)stInfo);

			nCount++;
		}


	}	

	for(int i = 0; i < m_List.GetItemCount(); i++)
	{					
		if(m_List.GetItemText(i , 0) == m_List.GetItemText(i + 1, 0))
		{
			for(int j=5; j > 0; j-- )
			{
				if(m_List.GetItemText(i,0) == m_List.GetItemText(i + j, 0))
					m_List.DeleteItem(i+j);
			}
		}

	}


}

void CCustomerSmsDlg::CheckListCondition()
{
	//CWaitCursor wait;
	CString strInDay,strDMSent,strNewCustomer;
	CString strDmCount;
	COleDateTime dtLastSmsBase, dtDMSmsBase, dtNewCustomer;
	dtLastSmsBase = dtDMSmsBase = dtNewCustomer  = COleDateTime::GetCurrentTime();
	m_cmbInDay.GetWindowText(strInDay);
	m_cmbDMSent.GetWindowText(strDMSent);
	m_cmbNewCustomer.GetWindowText(strNewCustomer);	
	m_cmbDmCount.GetWindowText(strDmCount);

	if(strInDay == "���Ѿ���")
	{
		dtLastSmsBase.SetDate(2050, 1, 1);
	}
	else
	{
		dtLastSmsBase = dtLastSmsBase + COleDateTimeSpan(1, 0, 0, 0);
		dtLastSmsBase.SetDateTime(dtLastSmsBase.GetYear(), dtLastSmsBase.GetMonth(), dtLastSmsBase.GetDay(), 0, 0, 0);
		dtLastSmsBase = dtLastSmsBase - COleDateTimeSpan(atol(strInDay), 0, 0, 0);
	}
	if(strDMSent == "���Ѿ���")
	{
		dtDMSmsBase.SetDate(2050, 1, 1);
	}
	else
	{
		dtDMSmsBase = dtDMSmsBase + COleDateTimeSpan(1, 0, 0, 0);
		dtDMSmsBase.SetDateTime(dtDMSmsBase.GetYear(), dtDMSmsBase.GetMonth(), dtDMSmsBase.GetDay(), 0, 0, 0);
		dtDMSmsBase = dtDMSmsBase - COleDateTimeSpan(atol(strDMSent), 0, 0, 0);
	}
	if(strNewCustomer == "���Ѿ���")
	{
		dtNewCustomer.SetDate(2050, 1, 1);
	}
	else
	{
		dtNewCustomer = dtNewCustomer + COleDateTimeSpan(1, 0, 0, 0);
		dtNewCustomer.SetDateTime(dtNewCustomer.GetYear(), dtNewCustomer.GetMonth(), dtNewCustomer.GetDay(), 0, 0, 0);
		dtNewCustomer = dtNewCustomer - COleDateTimeSpan(atol(strNewCustomer), 0, 0, 0);
	}
	if(strDmCount == "���Ѿ���")
		strDmCount = "0";



	for(int i = 0; i < m_List.GetItemCount(); i++)
	{	
		m_List.SetCheck(i, 1);

		if(m_List.GetItemText(i, 0).Left(2) != "01") {
			m_List.SetCheck(i, 0);
			continue;
		}

		if(m_List.GetItemText(i, 0).GetLength() > 11 ||
			m_List.GetItemText(i, 0).GetLength() < 10) {
				m_List.SetCheck(i, 0);
				continue;
			}

			if(!((m_List.GetItemText(i, 1).GetLength() > 0 && m_CTypeCheck2.GetCheck()) ||
				(m_List.GetItemText(i, 1).GetLength() == 0 && m_CTypeCheck1.GetCheck()))) {
					m_List.SetCheck(i, 0);
					continue;
				}

				if(m_List.GetItemText(i, 2).GetLength() > 0) {
					m_List.SetCheck(i, 0);
					continue;
				}

				ST_CHECK_INFO *stInfo = (ST_CHECK_INFO*)m_List.GetItemData(i);

				if(stInfo->dtLastSms.GetStatus() != COleDateTime::null &&
					dtLastSmsBase < stInfo->dtLastSms)
				{
					m_List.SetCheck(i, 0);
					continue;
				}		

				if(stInfo->dtDMLastSms.GetStatus() != COleDateTime::null &&
					dtDMSmsBase < stInfo->dtDMLastSms)
				{
					m_List.SetCheck(i, 0);
					continue;
				}

				if(stInfo->dtNewCustomer.GetStatus() != COleDateTime::null &&
					dtNewCustomer < stInfo->dtNewCustomer)
				{
					m_List.SetCheck(i, 0);
					continue;
				}


				int nCount = m_List.GetItemText(i,6).GetLength() <= 0 ? 0 : atoi(m_List.GetItemText(i,6));
				if( atoi(strDmCount) == 0 )
					continue;
				else if(nCount >= atoi(strDmCount) ) {
					m_List.SetCheck(i, 0);
					continue;

				}


	}


	CString strSendCount;
	m_cmbSendCount.GetWindowText(strSendCount);
	int nCheckCount = 0;
	if(strSendCount == "���Ѿ���")
		strSendCount = "10000000";

	long nSendCount = atol(strSendCount);	
	int i = 0;
	for(i = 0; i < m_List.GetItemCount(); i++){
		if(m_List.GetCheck(i))
			nCheckCount++;
		if(nSendCount == nCheckCount)
			break;
	}

	for(int j = i+ 1; j < m_List.GetItemCount(); j++)
		m_List.SetCheck(j,0);



	int nSelCount = 0;
	CString strCount;
	for(i = 0; i < m_List.GetItemCount(); i++)
	{
		if(m_List.GetCheck(i) > 0)
			nSelCount++;
	}
	strCount.Format("%d���� %d�� ���� ���õ�", m_List.GetItemCount(), nSelCount);
	m_stcCount.SetWindowText(strCount);
}

void CCustomerSmsDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString strPhoneChunk;
	//CWaitCursor wait;
	int nDelayMinute = 0;

	int nTotCount = 0;

	ST_SMS_INFO smsi;
	smsi = LF->GetSMSBalance(m_nCompany);
	if(smsi.nSMSType >= 10)
	{
		if(smsi.nSMSBarance < DEFINE_SMS_AMOUNT - 1){
			MessageBox("SMS�������� �����ϴ�.","SMS����",MB_ICONINFORMATION);
			return;
		}
	}


	for(int i = 0; i < m_List.GetItemCount(); i++)
	{		
		if(m_List.GetCheck(i))
			nTotCount++;
	}

	long nUseCount = -1;
	BOOL bUseLimit =  FALSE;
	if(smsi.nSMSType >= 10)
	{
		if(nTotCount > smsi.nSMSBarance / DEFINE_SMS_AMOUNT){  // �ܾ׺��� ������..
			CString strBarance;
			nUseCount = nTotCount - (smsi.nSMSBarance / DEFINE_SMS_AMOUNT);

			strBarance.Format("SMS �����Ǽ���  %d��(�ݾ�: %d��)�� �����մϴ�.\r\n �����ִ� �ܾ׸�ŭ �����ðڽ��ϱ�",
				nUseCount,nUseCount * DEFINE_SMS_AMOUNT);
			if(MessageBox(strBarance,"SMS����",MB_ICONINFORMATION | MB_YESNO) == IDYES)
				bUseLimit = TRUE;
			else
				return;
		}
	}


	if(m_strMent.GetLength() == 0) {
		MessageBox("���۸�Ʈ�� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	m_m_strCompanyPhone.Replace("-", "");

	if(m_m_strCompanyPhone.GetLength() > 12) {
		MessageBox("ȸ�� ��ȭ��ȣ ���̰� 12�� �̻��� �� �� �����ϴ�.");
		return;
	}

	if(m_strMent.GetLength() > 80) {
		MessageBox("��Ʈ ���̰� 80�� �̻��� �� �� �����ϴ�.");
		return;
	}

	if(IDYES != MessageBox("SMS�� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_ICONQUESTION | MB_YESNO))
		return;

	if(IDYES != MessageBox("�ǽð� ���ۿ����� �ϸ� ��Ұ� �Ұ����� �� �ֽ��ϴ�.\n"\
		"���� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_ICONQUESTION | MB_YESNO))
		return;

	COleDateTime dtTrans;
	dtTrans.SetDateTime(m_dtDate.GetYear(), m_dtDate.GetMonth(), m_dtDate.GetDay(),
		m_dtTime.GetHour(), m_dtTime.GetMinute(), m_dtTime.GetSecond());

	if(dtTrans.GetHour() > 21)
	{
		if(MessageBox("���� 9�����Ĵ� ���Թ��� ����Ǿ� ���� �Ǿ� �ֽ��ϴ� �׷��� �����ðڽ��ϱ�?", 
			"����", MB_ICONWARNING|MB_YESNO) == IDNO)
			return;
	}
	if(dtTrans.GetHour() >= 0 && dtTrans.GetHour() < 10  )
		throw("���� 9�������� �߼��� �ȵ˴ϴ�.");

	if(dtTrans.GetHour() >= 9 && dtTrans.GetHour() < 17  )
		if(MessageBox(" ���� 9�ú��� ���� 4�û��̿� �����ô� �ŷ� üũ�Ǿ��ֽ��ϴ�. �׷��� �����ðڽ��ϱ�?", 
			"����", MB_ICONWARNING|MB_YESNO) == IDNO) 
			return;


	COleDateTime dt(COleDateTime::GetCurrentTime());
	COleDateTimeSpan dtSpan(0,0,-20,0);
	dt = dt + dtSpan;

	if(dtTrans < dt)
	{
		MessageBox("���� �ð������� �����Ǽ� �����ϴ�.", "����", MB_ICONWARNING|MB_YESNO);
		return;
	}

	int nCount = 0;
	int nSmsCheckCount = 0;
	int noCheck = 0;
	for(int i = 0; i < m_List.GetItemCount(); i++)
	{	
		if(m_List.GetCheck(i))
		{			
			nSmsCheckCount++;

			CString strPhone = m_List.GetItemText(i, 0);
			if(strPhone.GetLength() == 10) {
				strPhoneChunk += " ";
				strPhoneChunk += strPhone;
			}
			else if(strPhone.GetLength() == 11) {
				strPhoneChunk += strPhone;
			}					
			nCount++; //���� ������ ī��Ʈ

			if(bUseLimit == TRUE)			
			{
				if(nSmsCheckCount >= smsi.nSMSBarance / DEFINE_SMS_AMOUNT)
					i = m_List.GetItemCount()-1; // �ܾ��� ���ѵ��� ����..
			}

		}		

		if(m_DivisionCheck.GetCheck())
		{
			if(i >= 1000 && (i % 1000 == 0))
				nDelayMinute += 5;
		}

		if((i == m_List.GetItemCount() - 1 && strPhoneChunk.GetLength() > 0) ||
			strPhoneChunk.GetLength() > 6000)
		{
			COleDateTime dtTrans2 = dtTrans;
			dtTrans2 = dtTrans2 + COleDateTimeSpan(0, 0, nDelayMinute, 0);


			CMkCommand pCmd(m_pMkDb, "insert_sms_queue2");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
			pCmd.AddParameter(typeString, typeInput, m_strMent.GetLength(), m_strMent);
			pCmd.AddParameter(typeString, typeInput, m_m_strCompanyPhone.GetLength(), m_m_strCompanyPhone);
			pCmd.AddParameter(typeString, typeInput, strPhoneChunk.GetLength(), strPhoneChunk);
			pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtTrans2);
			pCmd.AddParameter(typeInt, typeInput, sizeof(int), nCount);


			if(!pCmd.Execute())
			{
				MessageBox("���ۿ����߿� ������ �߻��߽��ϴ�.\n�Ϻε����͸� ���ۿ���Ǿ����ϴ�.\n"\
					"���������� ������ ������Ʈ�� ���ؼ� �������� �Ͻ��� ���ñ� �ٶ��ϴ�.",
					"���ۿ��� ����", MB_ICONINFORMATION);
				AfxGetApp()->WriteProfileInt("sms", "LimitDays", m_cmbInDay.GetCurSel());
				return;
			}



			nCount = 0;
			strPhoneChunk = "";
		}

	}
	/*
	CString str;
	str.Format("üũ:%d,��üũ:%d",nSmsCheckCount,noCheck);
	MessageBox(str);
	*/


		AfxGetApp()->WriteProfileInt("sms", "LimitDays", m_cmbInDay.GetCurSel());
	MessageBox("���� ����Ǿ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	OnOK();
}

void CCustomerSmsDlg::OnBnClickedEditMentBtn()
{
	CMentDlg dlg;
	dlg.m_pCustomerSmsDlg = this;
	dlg.DoModal();
}	

void CCustomerSmsDlg::OnEnChangeMentEdit()
{
	CString strMent, strLength;
	m_edtMent.GetWindowText(strMent);
	strLength.Format("%d/80", strMent.GetLength());
	m_stcLength.SetWindowText(strLength);
}


void CCustomerSmsDlg::OnBnClickedCtypeCheck1()
{
	CheckListCondition();
}

void CCustomerSmsDlg::OnBnClickedCtypeCheck2()
{
	CheckListCondition();
}

void CCustomerSmsDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{

	if(!m_bNotified)
	{
		MessageBox("�������� �Ŀ�, ���������� �ٲٽø� ���õ� �κ��� �ݿ����� �ʽ��ϴ�.\n"\
			"���������� ������ �����Ͻ� �Ŀ�, ���Ǽ����Ͻñ� �ٶ��ϴ�.",
			"Ȯ��", MB_ICONINFORMATION);
		m_bNotified = TRUE;
	}

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem < 0) return;

	if(m_List.GetItemText(pNMListView->iItem, 0).Left(2) != "01") {
		m_List.SetCheck(pNMListView->iItem, 0);
		MessageBox("�޴��� ��ȣ�� �ƴϹǷ�, SMS���� üũ�� �Ͻ� �� �����ϴ�.", 
			"Ȯ��", MB_ICONINFORMATION);
		m_nUncheckedItem = pNMListView->iItem;
		//		SetTimer(0, 0, NULL);
		*pResult = 0;	
		return;
	}

	if(m_List.GetItemText(pNMListView->iItem, 0).GetLength() > 11 ||
		m_List.GetItemText(pNMListView->iItem, 0).GetLength() < 10) {
			m_List.SetCheck(pNMListView->iItem, 0);
			MessageBox("��ȭ��ȣ ���̰� ���������� �ʽ��ϴ�. 10�� �̻� 11�� �����Դϴ�.", 
				"Ȯ��", MB_ICONINFORMATION);
			m_nUncheckedItem = pNMListView->iItem;
			//		SetTimer(0, 0, NULL);
			*pResult = 0;	
			return;
		}

		*pResult = 0;
}

void CCustomerSmsDlg::OnTimer(UINT nIDEvent)
{
	m_List.SetCheck(m_nUncheckedItem, 0);
	KillTimer(nIDEvent);
	CMyDialog::OnTimer(nIDEvent);
}

void CCustomerSmsDlg::OnLvnDeleteitemList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem < 0) return;
	ST_CHECK_INFO *pCheckInfo = NULL;
	pCheckInfo = (ST_CHECK_INFO*)m_List.GetItemData(pNMListView->iItem);
	if(pCheckInfo != NULL)
		delete pCheckInfo;
	*pResult = 0;
}

void CCustomerSmsDlg::OnCbnSelchangeInDayCombo()
{
	CheckListCondition();
}

void CCustomerSmsDlg::OnCbnSelchangeDmSentCombo()
{
	CheckListCondition();
}

void CCustomerSmsDlg::OnCbnSelchangeNewCustomerCombo()
{
	CheckListCondition();
}

void CCustomerSmsDlg::OnCbnSelchangeDmCountCombo()
{
	CheckListCondition();
}

void CCustomerSmsDlg::OnCbnSelchangeSendCountCombo()
{
	CheckListCondition();
	/*
	CString strSendCount;
	m_cmbSendCount.GetWindowText(strSendCount);
	int nCheckCount = 0;
	if(strSendCount == "���Ѿ���")
		strSendCount = "10000000";

	long nSendCount = atol(strSendCount);

	int i = 0;

	for(i = 0; i < m_List.GetItemCount(); i++){
		if(m_List.GetCheck(i))
			nCheckCount++;
		if(nSendCount == nCheckCount)
			break;
	}

	for(int j = i+ 1; j < m_List.GetItemCount(); j++)
		m_List.SetCheck(j,0);

	int nSelCount = 0;
	CString strCount;
	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		if(m_List.GetCheck(i) > 0)
			nSelCount++;
	}

	strCount.Format("%d���� %d�� ���� ���õ�", m_List.GetItemCount(), nSelCount);
	m_stcCount.SetWindowText(strCount);
	*/	
}


void CCustomerSmsDlg::OnBnClickedReservationCancelBtn()
{
	//2006
	BOOL bIntegrated = FALSE;
	CBranchInfo *pBi = NULL;
	for(int i = 0; i < m_ba.GetCount(); i++) {
		pBi = m_ba.GetAt(i);
		if(pBi->bIntegrated)
		{
			bIntegrated =	TRUE;
			break;
		}		
	}

	CReservationListDlg dlg;
	dlg.m_nCompany = m_nCompany;
	dlg.m_bIntegrated = bIntegrated;
	dlg.DoModal();
}

void CCustomerSmsDlg::OnBnClickedStateButton()
{
	CSMSStateDlg dlg;
	if(dlg.DoModal() == IDOK)
	{

		UpdateData(TRUE);

		COleDateTime dt;		
		dt = dlg.GetSelectTime();
		m_dtDate.SetDate(dt.GetYear(), dt.GetMonth(), dt.GetDay());
		m_dtTime.SetDateTime(dt.GetYear(), dt.GetMonth(), dt.GetDay(),
			dt.GetHour(), dt.GetMinute(), dt.GetSecond());

		UpdateData(FALSE);


	}

}
