// NewCustomerSmsDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "NewCustomerSmsDlg.h"



// CNewCustomerSmsDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CNewCustomerSmsDlg, CMyDialog)
CNewCustomerSmsDlg::CNewCustomerSmsDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CNewCustomerSmsDlg::IDD, pParent)
	, m_strMent(_T(""))
{
	m_XTPGridRecords = NULL;
}

CNewCustomerSmsDlg::~CNewCustomerSmsDlg()
{
}

void CNewCustomerSmsDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_wndReport);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
	DDX_Control(pDX, IDC_TOTAL_STATIC, m_stcTotal);
	DDX_Control(pDX, IDC_SEND_STATIC, m_stcSend);
	DDX_Control(pDX, IDC_COUNT_STATIC, m_stcCount);
	DDX_Text(pDX, IDC_MSG_EDIT, m_strMent);
	DDX_Control(pDX, IDC_CALL_BACK_STATIC, m_stcCallBack);
	DDX_Control(pDX, IDC_CHECK1, m_chkAll);
	DDX_Control(pDX, IDC_CHECK2, m_chkNotAll);
}


BEGIN_MESSAGE_MAP(CNewCustomerSmsDlg, CMyDialog)
	ON_BN_CLICKED(IDC_SEND_BTN, OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CHANGE_MENT_BTN, OnBnClickedChangeMentBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_EN_CHANGE(IDC_MSG_EDIT, OnEnChangeMsgEdit)
	ON_NOTIFY(NM_CLICK, IDC_REPORT, OnReportItemClick)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
END_MESSAGE_MAP()


// CNewCustomerSmsDlg �޽��� ó�����Դϴ�.

BOOL CNewCustomerSmsDlg::OnInitDialog()
{ 
	CMyDialog::OnInitDialog();
 
	m_wndReport.InsertColumn(0, "��", LVCFMT_LEFT, 25);
	m_wndReport.InsertColumn(1, "����", LVCFMT_LEFT, 40);
	m_wndReport.InsertColumn(2, "����", LVCFMT_LEFT, 100);
	m_wndReport.InsertColumn(3, "��ȭ��ȣ", LVCFMT_LEFT, 110); 

	m_wndReport.Populate();

	CString sMsg = AfxGetApp()->GetProfileString("NewCustomerMsg", "NewCustomerMsg", "");
	m_edtMsg.SetWindowText(sMsg);

	m_stcCallBack.SetWindowText("ȸ�Ź�ȣ : " + m_ci.m_strPhone);
	
	RefreshList();
	InitCount();
	OnEnChangeMsgEdit();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CNewCustomerSmsDlg::RefreshList()
{
	m_wndReport.DeleteAllItems();

	long nItem = 0;
	char buffer[20];

	for(int i=0; i<m_XTPGridRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_XTPGridRecords->GetAt(i);
		CString sCompany = ((CXTPGridRecordItemText*)pRecord->GetItem(1))->GetCaption(NULL);
		CString sTel1 = ((CXTPGridRecordItemText*)pRecord->GetItem(4))->GetCaption(NULL);
		CString sMoile = ((CXTPGridRecordItemText*)pRecord->GetItem(5))->GetCaption(NULL);

		CString sPhone = "";

		if(sMoile.Left(2) == "01")
			sPhone = sMoile;
		else if(sTel1.Left(2) == "01")
			sPhone = sTel1;
		else 
			continue; 
	
		m_wndReport.InsertCheckItem(nItem, "", -1, TRUE);
		m_wndReport.SetItemText(nItem, 1, itoa(nItem + 1, buffer, 10));
		m_wndReport.SetItemText(nItem, 2, sCompany);
		m_wndReport.SetItemText(nItem++, 3, sPhone);
	}

	m_wndReport.Populate();
}

void CNewCustomerSmsDlg::OnBnClickedSendBtn()
{
	UpdateData(TRUE);
	CString strPhoneChunk;
	//CWaitCursor wait;
	int nDelayMinute = 0;

	int nTotCount = 0;

	ST_SMS_INFO smsi;
	smsi = ::GetSMSBalance(m_ci.m_nCompanyCode);
	if(smsi.nSMSType >= 10)
	{
		if(smsi.nSMSBarance < DEFINE_SMS_AMOUNT - 1){
			MessageBox("SMS�������� �����ϴ�.","SMS����",MB_ICONINFORMATION);
			return;
		}
	}


	if(m_strMent.GetLength() == 0) {
		MessageBox("���۸�Ʈ�� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	if(m_strMent.GetLength() > 80) {
		MessageBox("��Ʈ ���̰� 80�� �̻��� �� �� �����ϴ�.");
		return;
	}

	if(IDYES != MessageBox("SMS�� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_ICONQUESTION | MB_YESNO))
		return;

	COleDateTime dtTrans = COleDateTime::GetCurrentTime();

	if(dtTrans.GetHour() > 21)
	{
		if(MessageBox("���� 9�����Ĵ� ���Թ��� ����Ǿ� ���� �Ǿ� �ֽ��ϴ� �׷��� �����ðڽ��ϱ�?", 
			"����", MB_ICONWARNING|MB_YESNO) == IDNO)
			return;
	}
	if(dtTrans.GetHour() >= 0 && dtTrans.GetHour() < 10  )
		throw("���� 9�������� �߼��� �ȵ˴ϴ�.");


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
	for(int i = 0; i < m_wndReport.GetItemCount(); i++)
	{	
		if(m_wndReport.GetChecked(i, 0))
		{			
			nSmsCheckCount++;

			CString strPhone = m_wndReport.GetItemText(i, 3);
			strPhone.Replace("-", "");

			if(strPhone.GetLength() == 10) {
				strPhoneChunk += " ";
				strPhoneChunk += strPhone;
			}
			else if(strPhone.GetLength() == 11) {
				strPhoneChunk += strPhone;
			}					
		}		

		if((i == m_wndReport.GetItemCount() - 1 && strPhoneChunk.GetLength() > 0) ||
			strPhoneChunk.GetLength() > 6000)
		{
			COleDateTime dtTrans2 = dtTrans;
			dtTrans2 = dtTrans2 + COleDateTimeSpan(0, 0, 0, 0);

			CString sTranEtc = "�ű԰�";

			CMkCommand pCmd(m_pMkDb, "insert_sms_queue3");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
			pCmd.AddParameter(typeString, typeInput, m_strMent.GetLength(), m_strMent);
			pCmd.AddParameter(typeString, typeInput, m_ci.m_strPhone.GetLength(), m_ci.m_strPhone);
			pCmd.AddParameter(typeString, typeInput, strPhoneChunk.GetLength(), strPhoneChunk);
			pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtTrans2);
			pCmd.AddParameter(typeInt, typeInput, sizeof(int), nCount);
			pCmd.AddParameter(typeString, typeInput, sTranEtc.GetLength(), "�ű԰�");

			if(!pCmd.Execute())
			{
				MessageBox("�����߿� ������ �߻��߽��ϴ�.\r\n��������Ʈ�� ���ǹٶ��ϴ�,",
					"���� ����", MB_ICONINFORMATION);
				return;
			}

			nCount = 0;
			strPhoneChunk = "";
		}

	}

	MessageBox("���� �Ǿ����ϴ�.\r\n�ִ� 5�б��� �ɸ� �� �ֽ��ϴ�", "Ȯ��", MB_ICONINFORMATION);
	OnOK();
}

void CNewCustomerSmsDlg::InitCount()
{
	char buffer[10];

	m_nCount = 0;
	m_nSendCount = 0;

	CXTPGridRecords *pReocords = m_wndReport.GetRecords();

	for(int i=0;i<pReocords->GetCount(); i++)
	{
		if(m_wndReport.GetChecked(i, 0) == TRUE)
			m_nSendCount++;

		m_nCount++;                
	}

	m_stcTotal.SetWindowText("�� : " + CString(itoa(m_nCount, buffer, 10)) + "��");
	m_stcSend.SetWindowText("���� : " + CString(itoa(m_nSendCount, buffer, 10)) + "��");

}

void CNewCustomerSmsDlg::OnBnClickedChangeMentBtn()
{
	CString sMsg; m_edtMsg.GetWindowText(sMsg);
	AfxGetApp()->WriteProfileString("NewCustomerMsg", "NewCustomerMsg", sMsg);

	MessageBox("���� �Ǿ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
}

void CNewCustomerSmsDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CNewCustomerSmsDlg::OnEnChangeMsgEdit()
{
	CString strMsg, strCount;
	m_edtMsg.GetWindowText(strMsg);
	strCount.Format("���ڼ�: %d", strMsg.GetLength());
	m_stcCount.SetWindowText(strCount);
}



void CNewCustomerSmsDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	InitCount();

}
void CNewCustomerSmsDlg::OnBnClickedCheck1()
{
	if(m_chkAll.GetCheck() == FALSE)
		return;

	for(int i=0;i<m_wndReport.GetItemCount(); i++)
		m_wndReport.SetChecked(i, 0, TRUE);

	m_wndReport.Populate();
}

void CNewCustomerSmsDlg::OnBnClickedCheck2()
{	
	if(m_chkNotAll.GetCheck() == FALSE)
		return;

	for(int i=0;i<m_wndReport.GetItemCount(); i++)
		m_wndReport.SetChecked(i, 0, FALSE);

	m_wndReport.Populate();               
}
