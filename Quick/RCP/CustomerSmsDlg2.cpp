// CustomerSmsDlg2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerSmsDlg2.h"
#include "MenuEtcUserDlg.h"
#include "AllocateSMSFSettingDlg.h"
#include "SmsMentDlg.h"
#include "RcpDlg.h"
// CCustomerSmsDlg2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCustomerSmsDlg2, CMyDialog)

UINT getPopup(int popup_type)
{
	UINT nIDD = IDD_CUSTOMER_SMS_DLG2;
	if (popup_type == POPUP_ALLOCATE)
		nIDD = IDD_ALLOCATE_SMS_DLG;

	return nIDD;
}

CCustomerSmsDlg2::CCustomerSmsDlg2(CWnd* pParent /*=NULL*/, int popup_type)
: CMyDialog(getPopup(popup_type), pParent)
, m_strBalance(_T(""))
, m_strSMSCount(_T(""))
, m_dtReservationDate(COleDateTime::GetCurrentTime())
, m_dtReservationTime(COleDateTime::GetCurrentTime())
, m_bReservation(FALSE)
{
	m_ePopupType = (POPUP_TYPE)popup_type;
	m_bRiderSMS = FALSE;
	m_nCompany = 0;
	m_bHideCustomerPN = FALSE;
	m_nContent = 0;
}

CCustomerSmsDlg2::~CCustomerSmsDlg2()
{
}

void CCustomerSmsDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CUSTOMER_PN_EDIT, m_strCustomerPN);
	DDX_Text(pDX, IDC_MSG_EDIT, m_strMsg);
	DDX_Text(pDX, IDC_COUNT_STATIC, m_strCount);
	DDX_Control(pDX, IDC_CUSTOMER_PN_EDIT, m_edtCustomerPN);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
	DDX_Control(pDX, IDC_COUNT_STATIC, m_stcCount);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);

	DDX_Control(pDX, IDOK, m_btnConfirm);
	DDX_Text(pDX, IDC_SMS_BARANCE_STATIC, m_strBalance);
	DDX_Text(pDX, IDC_SMS_COUNT_STATIC, m_strSMSCount);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_SMS_MENT_SETTING_BUTTON, m_btnMentSet);
	DDX_Control(pDX, IDC_MENT_SAVE_BUTTON, m_btnMentSave);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_CHANGE_CUSTOMER_CHECK, m_chkChangeTelCustomer);
	DDX_Control(pDX, IDC_RESERVATION_CHECK, m_chkReservation);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtpReservationDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtpReservationTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtReservationDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtReservationTime);
	DDX_Control(pDX, ID_CONTINUE_SEND_BTN, m_btnContinueSend);

	DDX_Check(pDX, IDC_RESERVATION_CHECK, m_bReservation);
	DDX_Control(pDX, IDC_PHONE_COMBO, m_cmbPhone);
}

BEGIN_MESSAGE_MAP(CCustomerSmsDlg2, CMyDialog)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_CHANGE(IDC_MSG_EDIT, OnEnChangeMsgEdit)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
	ON_BN_CLICKED(IDC_SMS_MENT_SETTING_BUTTON, OnBnClickedSmsMentSettingButton)
	ON_BN_CLICKED(IDC_MENT_SAVE_BUTTON, OnBnClickedMentSaveButton)
	ON_BN_CLICKED(IDC_CHANGE_CUSTOMER_CHECK, OnBnClickedChangeCustomerCheck)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO, OnCbnSelchangeSelectCombo)
	ON_BN_CLICKED(IDC_RESERVATION_CHECK, OnBnClickedReservationCheck)
	ON_BN_CLICKED(ID_CONTINUE_SEND_BTN, OnBnClickedContinueSendBtn)
	ON_BN_CLICKED(IDC_MENT_BTN, &CCustomerSmsDlg2::OnBnClickedMentBtn)
	ON_BN_CLICKED(IDC_SMS_MENT_ALLOCATE_BUTTON, &CCustomerSmsDlg2::OnBnClickedAllocateBtn)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_URGE, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_RECALL, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_JUST_CALL, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_SPECIAL, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER1, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER2, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER3, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER4, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER5, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_USER_UPDATE, OnMenuContextEtc)
	ON_COMMAND_RANGE_SINGLE(ID_MENU_ETC_TO_INTERCALL_ETC, OnMenuContextEtc)
END_MESSAGE_MAP()


// CCustomerSmsDlg2 �޽��� ó�����Դϴ�.


BOOL CCustomerSmsDlg2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	if(m_bHideCustomerPN)
	{
		m_strCustomerPN2 = m_strCustomerPN;
		m_strCustomerPN = "Ÿ��� ��ȭ��ȣ ��ǥ�� ����";
		m_edtCustomerPN.SetReadOnly(TRUE); 
	}
	//m_edtMsg.SetFontSize(13);

	ST_SMS_INFO smsi;
	smsi = LF->GetSMSBalance(m_nCompany); 

	m_cmbPhone.InitSmsPhoneNumber(m_nCompany, -1, 160);

	//���ϰ����� �ܾװ� �������� ���Ѵٴ� ���� �ѷ���.	
	UpdateData(TRUE);

	m_strBalance =  LF->GetMyNumberFormat(smsi.nSMSBarance);
	//if(smsi.nSMSType >= 10)
	//{
	//	if(smsi.nSMSBarance  <= DEFINE_SMS_AMOUNT - 1)
	//	{
	//		m_strBalance =  LF->GetMyNumberFormat(smsi.nSMSBarance);
	//		int nCount = smsi.nSMSBarance / DEFINE_SMS_AMOUNT;
	//		m_strSMSCount.Format("����: %d", nCount);
	//		m_btnConfirm.EnableWindow(0);
	//		m_btnContinueSend.EnableWindow(FALSE);

	//	}
	//	else
	//	{
	//		m_strBalance = LF->GetMyNumberFormat(smsi.nSMSBarance);
	//		int nSMCount = smsi.nSMSBarance / DEFINE_SMS_AMOUNT;
	//		m_strSMSCount.Format("����: %s��", LF->GetMyNumberFormat((long)nSMCount));
	//	}
	//}
	//else
	//{
	//	int nSMCount = smsi.nSMSBarance / DEFINE_SMS_AMOUNT;
	//	m_strSMSCount.Format("����: %s��", LF->GetMyNumberFormat((long)nSMCount));
	//	m_strBalance = LF->GetMyNumberFormat(smsi.nSMSBarance);
	//}

	UpdateData(FALSE);

	if(m_bRiderSMS)
	{
		m_stc1.SetWindowText("��� ��ȭ��ȣ");
		SetWindowText("��� SMS����");
	}

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_List.InsertColumn(0,"ID", LVCFMT_LEFT, 30);
	m_List.InsertColumn(1,"���Ź�ȣ", LVCFMT_LEFT, 85);
	m_List.InsertColumn(2,"�߽Ź�ȣ", LVCFMT_LEFT, 85);
	m_List.InsertColumn(3,"�⺻", LVCFMT_LEFT, 40);
	m_List.InsertColumn(4,"����", LVCFMT_LEFT, 210);


	RefreshList();
	m_cmbPhone.SetReadOnly(TRUE);

	//m_chkChangeTelCustomer.SetCheck(AfxGetApp()->GetProfileInt("Sms", "Change_tel", 1));

	OnEnChangeMsgEdit();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
void CCustomerSmsDlg2::RefreshList()
{
	m_List.DeleteAllItems();

	BOOL bIntegrated = FALSE;
	if(m_ba.GetCount() > 1)
		bIntegrated = TRUE;
	BOOL bDefault = FALSE;
	int  nRandomCompanyTel = 0;
	//CWaitCursor wait;
	//if(m_nContent == 6)  // ����sms �̸�
	//	return;


	CMkCommand pCmd2(m_pMkDb, "select_sms_save_ment3");	
	CMkParameter *parRet = pCmd2.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);	
	pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), bIntegrated);	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_nContent);	

	CMkRecordset pRs2(m_pMkDb);

	if(pRs2.Execute(&pCmd2))
	{		
		parRet->GetValue(nRandomCompanyTel);


		int	nNum = 1,nItem = 0, nID = 0;
		CString sReceiveTel, sSendTel, sContent, sTel;
		sReceiveTel =  sSendTel = sContent = sTel = "";	

		char buffer[10];
		while(!pRs2.IsEOF()) {
			pRs2.GetFieldValue("nID", nID);
			pRs2.GetFieldValue("sReceiveTel", sReceiveTel);			
			pRs2.GetFieldValue("sSendTel", sSendTel);
			pRs2.GetFieldValue("sContent", sContent);						
			pRs2.GetFieldValue("sTel", sTel);		
			pRs2.GetFieldValue("bDefault", bDefault);						

			m_List.InsertItem(nItem,itoa(nNum, buffer,10));						
			m_List.SetItemText(nItem,1,LF->GetDashPhoneNumber(sReceiveTel));
			m_List.SetItemText(nItem,2,LF->GetDashPhoneNumber(sSendTel));
			m_List.SetItemText(nItem,3,bDefault ? "����":"");
			m_List.SetItemText(nItem,4,sContent);
			m_List.SetItemData(nItem, (DWORD_PTR)nID);

			if(bDefault)
			{				
				m_edtCustomerPN.SetWindowText(sReceiveTel);
				sSendTel = m_cmbPhone.GetSmsPhoneNumber();
				m_edtMsg.SetWindowText(sContent);
			}
			nItem++; nNum++;
			pRs2.MoveNext();
		}
		pRs2.Close();
	}	

	if(m_nContent == 6)  // ����sms �̸�
		return;

	if(!bDefault)
	{
		if(nRandomCompanyTel)
			m_cmbPhone.ChangeSelType(TYPE_OFFICE_TEL);
		else
		{
			m_cmbPhone.ChangeSelType(TYPE_MAIN_TEL);
		}
	}




}

void CCustomerSmsDlg2::OnBnClickedOk()
{
	UpdateData(TRUE);	 

	if(m_strMsg.GetLength() > 90)
	{	
		MessageBox("���۳����� 90�ڸ� �ʰ��մϴ�. 90���̳��� �ۼ��Ͽ� �ֽñ� �ٶ��ϴ�.", 
			"Ȯ��", MB_ICONINFORMATION);

		return;
	}

	if(m_strMsg.IsEmpty()){
		MessageBox("���۳����� �Է��ϼ���", 
			"Ȯ��", MB_ICONINFORMATION);

		return;
	}


	CString strCustPN = "";

	if(m_bHideCustomerPN)
		strCustPN = m_strCustomerPN2;
	else
		strCustPN = m_strCustomerPN;
	strCustPN.Replace("-","");

	if(strCustPN == "������ȭ�κ�ȯ" || strCustPN == "������ȭ�κ�ȯ")
	{}
	else if(strCustPN.Left(2) != "01" || 
		strCustPN.GetLength() < 10 ||
		strCustPN.GetLength() > 11)
	{
		MessageBox("�� �޴��� ��ȣ�� �Է��Ͻñ� �ٶ��ϴ�.", 
			"Ȯ��", MB_ICONINFORMATION);
		return;
	}

	m_strCustomerPN = strCustPN;
	m_strRecvPhone = m_cmbPhone.GetSmsPhoneNumber();
	OnOK();
}

void CCustomerSmsDlg2::OnEnChangeMsgEdit()
{
	SetMsgCount();
}

void CCustomerSmsDlg2::SetMsgCount()
{
	CString strMsg, strCount;
	m_edtMsg.GetWindowText(strMsg);
	strCount.Format("���ڼ�: %d", strMsg.GetLength());
	m_stcCount.SetWindowText(strCount);
}

void CCustomerSmsDlg2::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

void CCustomerSmsDlg2::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(!(pNMListView->uNewState & LVIS_SELECTED)) return;
	int nItem = pNMLV->iItem;
	int nCol = pNMLV->iSubItem;
	if(nItem < 0)
	{
		*pResult = 0;
		return;
	}

	
	if(m_chkChangeTelCustomer.GetCheck())
	{
		m_edtCustomerPN.SetWindowText(m_List.GetItemText(nItem,1));
		m_edtRecvPn.SetWindowText(m_List.GetItemText(nItem,2));
	}
	

	if(nCol == 1)
		m_edtCustomerPN.SetWindowText(m_List.GetItemText(nItem,1));
	else if(nCol == 2)
		m_edtRecvPn.SetWindowText(m_List.GetItemText(nItem,2));
	else if(nCol == 4)
		m_edtMsg.SetWindowText(m_List.GetItemText(nItem,4));	
	*/
	*pResult = 0;
}

void CCustomerSmsDlg2::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nItem = pNMLV->iItem;
	int nCol = pNMLV->iSubItem;
	if(nItem < 0)
	{
		*pResult = 0;
		return;
	}

	/*
	if(m_chkChangeTelCustomer.GetCheck())
	{
		m_edtCustomerPN.SetWindowText(m_List.GetItemText(nItem,1));
		m_edtRecvPn.SetWindowText(m_List.GetItemText(nItem,2));
	}
	*/

	if(nCol == 1)
		m_edtCustomerPN.SetWindowText(m_List.GetItemText(nItem,1));
	//else if(nCol == 2)
	//	m_edtRecvPn.SetWindowText(m_List.GetItemText(nItem,2));
	else if(nCol == 4) {
		if (m_ePopupType == POPUP_CUSTOMER)
			m_edtMsg.SetWindowText(m_List.GetItemText(nItem,4));
		else if (m_ePopupType == POPUP_ALLOCATE) {
			CString sSendTel, sReceiveTel;
			CString msg = m_List.GetItemText(nItem,4);
			m_edtCustomerPN.GetWindowText(sReceiveTel);
			sSendTel = m_cmbPhone.GetSmsPhoneNumber();
			
			if (msg.Find("[@") >= 0)
				m_edtMsg.SetWindowText(LU->GetReplaceChar(msg, sSendTel, sReceiveTel, m_strRiderPN));
			else
				m_edtMsg.SetWindowText(msg);
		}

		SetMsgCount();
	}
	/*
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int nItem = pNMLV->iItem;
	if(nItem < 0)
	return;
	if(m_chkChangeTelCustomer.GetCheck() )
	{
	m_edtCustomerPN.SetWindowText(m_List.GetItemText(nItem,1));
	m_edtRecvPn.SetWindowText(m_List.GetItemText(nItem,2));
	}

	m_edtMsg.SetWindowText(m_List.GetItemText(nItem,4));	
	OnEnChangeMsgEdit();
	*/
	*pResult = 0;
}

void CCustomerSmsDlg2::OnBnClickedSmsMentSettingButton()
{
	CSmsMentDlg dlg;
	dlg.DoModal();
	RefreshList();	
}

void CCustomerSmsDlg2::OnBnClickedMentSaveButton()
{
	UpdateData();
	if(m_strMsg.GetLength() <= 0)
	{
		MessageBox("����� �޼����� �����Ͽ� �ּ���","Ȯ��",MB_ICONINFORMATION);
		return;
	}
	else
	{	
		CBranchInfo *Brinfo = NULL;
		long nCompany = 0;
		CString sReceiveTel, sSendTel;
		sReceiveTel = sSendTel = "";

		int nIndex = m_nContent;
		nCompany = m_nCompany;		

		m_edtCustomerPN.GetWindowText(sReceiveTel);
		sSendTel = m_cmbPhone.GetSmsPhoneNumber();
		//m_edtRecvPn.GetWindowText(sSendTel);
		if(sSendTel.GetLength() <= 0 || sReceiveTel.GetLength() <= 0){
			MessageBox("�޴��̹� ���������� �׸� ���� �Է����ּ���", "Ȯ��",MB_ICONINFORMATION);
			return;
		}
		sReceiveTel.Replace("-","");	
		sSendTel.Replace("-","");

		//CWaitCursor wait;		
		CMkCommand pCmd2(m_pMkDb, "insert_sms_save_ment");	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(int), m_nContent);
		pCmd2.AddParameter(typeString, typeInput, sReceiveTel.GetLength(),sReceiveTel);	
		pCmd2.AddParameter(typeString, typeInput, sSendTel.GetLength(),sSendTel);	
		pCmd2.AddParameter(typeString, typeInput, m_strMsg.GetLength(),m_strMsg);	
		pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), 0);	

		if(!pCmd2.Execute())
			MessageBox("��Ͽ� �����Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		else
			MessageBox("��� �Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	}
	RefreshList();	
}

void CCustomerSmsDlg2::OnBnClickedChangeCustomerCheck()
{
	AfxGetApp()->WriteProfileInt("Sms", "Change_tel", m_chkChangeTelCustomer.GetCheck() ? 1 : 0);
}

void CCustomerSmsDlg2::OnCbnSelchangeSelectCombo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CCustomerSmsDlg2::OnBnClickedReservationCheck()
{
	if(m_chkReservation.GetCheck())
	{
		m_dtpReservationDate.EnableWindow(TRUE);
		m_dtpReservationTime.EnableWindow(TRUE);

	}
	else
	{
		m_dtpReservationDate.EnableWindow(FALSE);
		m_dtpReservationTime.EnableWindow(FALSE);

	}
}

void CCustomerSmsDlg2::OnBnClickedContinueSendBtn()
{	

	UpdateData(TRUE);

	try
	{
		ST_SMS_INFO smsi;
		smsi = LF->GetSMSBalance(LF->GetNowBranchCode());
		if(smsi.nSMSType >= 10)
			if(DEFINE_SMS_AMOUNT > smsi.nSMSBarance)
				throw("SMS�ܾ��� �����մϴ�.");

		COleDateTime dtDate(COleDateTime::GetCurrentTime());

		dtDate.SetDateTime(m_dtReservationDate.GetYear(), m_dtReservationDate.GetMonth(),
			m_dtReservationDate.GetDay(), m_dtReservationTime.GetHour(), 
			m_dtReservationTime.GetMinute(), m_dtReservationTime.GetSecond());	

		CString strRecvPN = "", strCustomerPN = "", strEtc = "", strMsg = "";
		strRecvPN = m_cmbPhone.GetSmsPhoneNumber();
		strCustomerPN = m_strCustomerPN;
		strCustomerPN.Replace("-","");
		strMsg = m_strMsg;

		if(m_strCustomerPN.GetLength() <= 0 || strMsg.GetLength() <= 0)
			return;

		CMkCommand pCmd(m_pMkDb, "insert_sms_data_reservation");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), LF->GetNowBranchCode());
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 100);
		pCmd.AddParameter(typeString, typeInput,m_strCustomerPN.GetLength(), strCustomerPN);
		pCmd.AddParameter(typeString, typeInput,strRecvPN.GetLength(), strRecvPN);
		pCmd.AddParameter(typeString, typeInput,strMsg.GetLength(),strMsg );
		pCmd.AddParameter(typeString, typeInput, strEtc.GetLength(), strEtc);
		pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkReservation.GetCheck());
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtDate);

		if(!pCmd.Execute()) 
		{


			throw("SMS ������ �����Ͽ����ϴ�.");
		}
		else 
		{
			smsi = LF->GetSMSBalance(LF->GetNowBranchCode());
			CString sBalance = "", sSMSCount ="";
			sBalance.Format("%d��",LF->GetMyNumberFormat(smsi.nSMSBarance));
			sSMSCount.Format("%d��", LF->GetMyNumberFormat(smsi.nSMSBarance /DEFINE_SMS_AMOUNT) );
			m_strBalance = sBalance;
			m_strSMSCount ="����:" + sSMSCount + "��";
			UpdateData(FALSE);
			throw("���۵Ǿ����ϴ�.");
		}



	}
	catch(char *e)
	{
		MessageBox(e,"Ȯ��", MB_ICONINFORMATION);
		return;

	}


}

void CCustomerSmsDlg2::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if (nItem < 0)
		return;

	CMenu pMenu;
	pMenu.CreatePopupMenu();
	pMenu.AppendMenu(MF_BYCOMMAND, 1, "����");
	int cmd = pMenu.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	if (cmd == 1) {
		if (MessageBox("�ش� ��Ʈ�� �����Ͻðڽ��ϱ�?", "Ȯ��", MB_ICONINFORMATION | MB_YESNO) == IDYES) {
			int nID = (int)m_List.GetItemData(nItem);

			CMkCommand pCmd2(m_pMkDb, "delete_sms_save_ment");	
			pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
			pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nID);
			if (!pCmd2.Execute())
				MessageBox("������ �����Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
			else
				MessageBox("���� �Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);

			RefreshList();
		}
	}
}

void CCustomerSmsDlg2::OnBnClickedAllocateBtn()
{
	CAllocateSMSFSettingDlg dlg;
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	dlg.m_strInput = nItem < 0 ? "" : m_List.GetItemText(nItem, 4);

	if(dlg.DoModal() != IDOK)
		return;
	CString msg = dlg.m_strInput;
	if (msg.IsEmpty())
		return;
	else
		m_strMsg = msg;
	CBranchInfo *Brinfo = NULL;
	long nCompany = 0;
	CString sReceiveTel, sSendTel;
	sReceiveTel = sSendTel = "";

	int nIndex = m_nContent;
	nCompany = m_nCompany;		

	m_edtCustomerPN.GetWindowText(sReceiveTel);
	sSendTel = m_cmbPhone.GetSmsPhoneNumber();
	if(sSendTel.GetLength() <= 0 || sReceiveTel.GetLength() <= 0){
		MessageBox("�޴��̹� ���������� �׸� ���� �Է����ּ���", "Ȯ��",MB_ICONINFORMATION);
		return;
	}
	sReceiveTel.Replace("-","");	
	sSendTel.Replace("-","");

	m_edtMsg.SetWindowText(LU->GetReplaceChar(msg, sSendTel, sReceiveTel, m_strRiderPN));

	//CWaitCursor wait;		
	CMkCommand pCmd2(m_pMkDb, "insert_sms_save_ment");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(int), m_nContent);
	pCmd2.AddParameter(typeString, typeInput, sReceiveTel.GetLength(),sReceiveTel);	
	pCmd2.AddParameter(typeString, typeInput, sSendTel.GetLength(),sSendTel);	
	pCmd2.AddParameter(typeString, typeInput, m_strMsg.GetLength(),m_strMsg);	
	pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), 0);	

	if(!pCmd2.Execute())
		MessageBox("��Ͽ� �����Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else
		MessageBox("��� �Ͽ����ϴ�.", "Ȯ��", MB_ICONINFORMATION);

	RefreshList();	
}

void CCustomerSmsDlg2::OnBnClickedMentBtn()
{
	CBranchInfo *pBi = LF->GetBranchInfo(m_nCompany);

	if(pBi == NULL)
		return;

	CPoint pt;
	GetCursorPos(&pt);

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CHECK_MENU);
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(0);

	if(pBi->sEtcUserTitle1 != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER1, pBi->sEtcUserTitle1, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER1, MF_BYCOMMAND);

	if(pBi->sEtcUserTitle2 != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER2, pBi->sEtcUserTitle2, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER2, MF_BYCOMMAND);

	if(pBi->sEtcUserTitle3 != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER3, pBi->sEtcUserTitle3, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER3, MF_BYCOMMAND);

	if(pBi->sEtcUserTitle4 != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER4, pBi->sEtcUserTitle4, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER4, MF_BYCOMMAND);

	CString sRegTitle, sRegMemo;

	sRegTitle =	AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Title", "");
	sRegMemo =	AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Memo", "");

	if(sRegTitle != "")
		pRMenu->SetMenuText(ID_MENU_ETC_USER5, sRegTitle, MF_BYCOMMAND);
	else 
		pRMenu->RemoveMenu(ID_MENU_ETC_USER5, MF_BYCOMMAND);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}


void CCustomerSmsDlg2::OnMenuContextEtc(UINT nFlag)
{

	CBranchInfo *pBI = LF->GetBranchInfo(m_nCompany);

	if(nFlag == ID_MENU_ETC_USER_UPDATE)
	{
		CMenuEtcUserDlg dlg;
		dlg.m_pBi = pBI;
		dlg.DoModal();
		return;
	}
	else if(nFlag == ID_MENU_ETC_TO_INTERCALL_ETC)
	{
		return;
	}

	CString strUrge;
	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
	strUrge.Format("[����%s]", dtCurrent.Format("%H:%M"));

	CString strRecall;
	strRecall.Format("[����%s]", dtCurrent.Format("%H:%M"));

	CString strReg = AfxGetApp()->GetProfileString(m_ui.strID + "_Etc", "Memo", "");

	CString strArry[]  = {strUrge, strRecall, "[��ȭ����]", "[Ư�����]", pBI->sEtcUserMemo1,
		pBI->sEtcUserMemo2, pBI->sEtcUserMemo3, pBI->sEtcUserMemo4, strReg};

	BOOL bFront = AfxGetApp()->GetProfileInt(m_ui.strID + "_Etc", "Front", 0);

	LF->SetEditText(&m_edtMsg, strArry[nFlag - ID_MENU_ETC_URGE], bFront);
}
