// RiderMsgAllDlg2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderMsgAllDlg2.h"
#include "MentDlg.h"


// CRiderMsgAllDlg2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderMsgAllDlg2, CMyDialog)
CRiderMsgAllDlg2::CRiderMsgAllDlg2(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderMsgAllDlg2::IDD, pParent)
{
	m_bAllRider = FALSE;
	m_bIntegrated = FALSE;
	m_nCompany = 0;
}

CRiderMsgAllDlg2::~CRiderMsgAllDlg2()
{
}

void CRiderMsgAllDlg2::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
	DDX_Control(pDX, IDC_SMS_BARANCE_STATIC, m_stcBalance);
	DDX_Control(pDX, IDC_SMS_COUNT_STATIC, m_stcSmsCount);
	DDX_Control(pDX, IDC_COUNT_STATIC, m_stcMsgLen);
	DDX_Control(pDX, IDC_WORK_STOP_CHECK, m_chkWorkStop);
	DDX_Control(pDX, IDC_PHONE_COMBO, m_cmbPhone);
}


BEGIN_MESSAGE_MAP(CRiderMsgAllDlg2, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_MENT_BTN, OnBnClickedMentBtn)
	ON_EN_CHANGE(IDC_MSG_EDIT, OnEnChangeMsgEdit)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_WORK_STOP_CHECK, OnBnClickedWorkStopCheck)
END_MESSAGE_MAP()


// CRiderMsgAllDlg2 메시지 처리기입니다.

BOOL CRiderMsgAllDlg2::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);
	m_edtMsg.SetWindowText(this->m_strMessageMent);

	int nCol = 0;
	m_List.InsertColumn(0,"No",LVCFMT_LEFT,38);
	m_List.InsertColumn(++nCol,"사번",LVCFMT_LEFT, 50);
	//if(m_bIntegrated)
		m_List.InsertColumn(++nCol,"소속",LVCFMT_LEFT, 60);
	m_List.InsertColumn(++nCol,"기사명",LVCFMT_LEFT,65);
	m_List.InsertColumn(++nCol,"중지",LVCFMT_LEFT,40);
	m_List.InsertColumn(++nCol,"휴대폰",LVCFMT_LEFT,90);
	m_List.InsertColumn(++nCol,"아이디",LVCFMT_LEFT,90);
	m_List.InsertColumn(++nCol,"상태",LVCFMT_LEFT,65);
	
	char buffer[10];
	int nItem = -1, nSourceCol = 0, nTempCol;
	nCol = 1;
	nSourceCol = 0;

	//long nCount = m_List2->GetRecords()->GetCount();
	//CXTPGridRecords *pRecords = m_List2->GetRecords();
	long nCount = m_List2->GetRows()->GetCount();
	CXTPGridRows *pRows = m_List2->GetRows();

	if(m_bAllRider)
	{
		for(int i = 0; i < nCount; i++)
		{
			CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

			m_List.InsertItem(i, itoa(i + 1,buffer,10));
			m_List.SetItemText(i, nCol++, m_List2->GetItemText(pRecord, nSourceCol++));			
			//if(m_bIntegrated)
				m_List.SetItemText(i, nCol++, m_List2->GetItemText(pRecord, nSourceCol++));
			m_List.SetItemText(i, nCol++, m_List2->GetItemText(pRecord, nSourceCol++));
			m_List.SetItemText(i, nCol++, m_List2->GetItemText(pRecord, nSourceCol++) == "1" ? "중지" : "");

			nTempCol = nSourceCol;
			CString sHp = m_List2->GetItemText(pRecord, nTempCol);
			BOOL bHp =  (sHp.GetLength() >= 10 && sHp.GetLength() <= 11) ? TRUE : FALSE;

			m_List.SetItemText(i, nCol++, bHp ?	GetDashPhoneNumber(sHp) : "");
		
			CString sID = m_List2->GetItemText(pRecord, nSourceCol++);
			BOOL bID = (sID.GetLength() >= 10 && sID.GetLength() <= 11) ? TRUE : FALSE;
			m_List.SetItemText(i, nCol++, bHp ? "" : bID ? GetDashPhoneNumber(sID) : "");
			m_List.SetItemText(i, nCol++, bHp ? "휴대폰" :bID ? "아이디" : "전송제외");
			m_List.SetItemData(i, m_List2->GetItemData(pRecord));
			nCol = 1;
			nSourceCol = 0;
		}
	}
	else
	{
		for(int i = 0; i < (int)m_List2->GetSelectedRows()->GetCount(); i++)
		{
			nItem = m_List2->GetNextItem(nItem,LVNI_SELECTED );
			CXTPGridRow *pRow = m_List2->GetSelectedRows()->GetAt(i);
			nItem = pRow->GetIndex();

			m_List.InsertItem(i, itoa(i + 1,buffer,10));			
			m_List.SetItemText(i, nCol++, m_List2->GetItemText(nItem, nSourceCol++));
			//if(m_bIntegrated)
				m_List.SetItemText(i, nCol++, m_List2->GetItemText(nItem, nSourceCol++));
			m_List.SetItemText(i, nCol++, m_List2->GetItemText(nItem, nSourceCol++));
			m_List.SetItemText(i, nCol++, m_List2->GetItemText(nItem, nSourceCol++) == "1" ? "중지" : "");
			
			nTempCol = nSourceCol;
			CString sHp = m_List2->GetItemText(nItem, nTempCol);
			BOOL bHp =  (sHp.GetLength() >= 10 && sHp.GetLength() <= 11) ? TRUE : FALSE;

			m_List.SetItemText(i, nCol++, bHp ?	GetDashPhoneNumber(sHp) : "");

			CString sID = m_List2->GetItemText(nItem, nSourceCol++);
			BOOL bID = (sID.GetLength() >= 10 && sID.GetLength() <= 11) ? TRUE : FALSE;
			m_List.SetItemText(i, nCol++, bHp ? "" : bID ? GetDashPhoneNumber(sID) : "");
			m_List.SetItemText(i, nCol++, bHp ? "휴대폰" :bID ? "아이디" : "전송제외");
			m_List.SetItemData(i, m_List2->GetItemData(nItem));
			nCol = 1;
			nSourceCol = 0;
		}
	}
	m_edtMsg.SetFontSize(13);
	//m_edtReceivePhone.SetWindowText(m_ci.m_strOfficePhone);

	ST_SMS_INFO smsi;
	//smsi = ::GetSMSBalance(m_nOrderCompany); 
	long nCompany = ::GetNowBranchCode();
	smsi = ::GetSMSBalance(nCompany);

	m_cmbPhone.InitSmsPhoneNumber(nCompany, TYPE_OFFICE_TEL);

	CString sBalance, sSMSCount, sMsgLen;
	sBalance.Format("%s원",GetMyNumberFormat(smsi.nSMSBarance));
	sSMSCount.Format("%s건", GetMyNumberFormat(smsi.nSMSBarance /DEFINE_SMS_AMOUNT) );
	m_stcBalance.SetWindowText(sBalance);
	m_stcSmsCount.SetWindowText(sSMSCount);

	m_cmbPhone.SetReadOnly(TRUE);
	
	OnEnChangeMsgEdit();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CRiderMsgAllDlg2::RefreshList(void)
{


}
void CRiderMsgAllDlg2::OnBnClickedOk()
{
	int nSendCount = 0;
	nSendCount = m_List.GetItemCount();
	if(nSendCount <= 0)
		return;
	nSendCount = 0;

	for(int i = 0; i < m_List.GetItemCount(); i++)
		if(m_List.GetItemText(i, 7) != "전송제외" )
			nSendCount++; 

	ST_SMS_INFO smsi; 
	smsi = ::GetSMSBalance(::GetNowBranchCode()); 
	if(smsi.nSMSType >= 10)
	{
		if(nSendCount* DEFINE_SMS_AMOUNT > smsi.nSMSBarance)
		{
			MessageBox("SMS잔액이 부족합니다.", "확인", MB_ICONINFORMATION);
			return;
		}
	}
				
	CString sCallBack, sMsg,strEtc = "기사메시지";
	sCallBack = m_cmbPhone.GetSmsPhoneNumber();
	//m_edtReceivePhone.GetWindowText(sCallBack);	
	m_edtMsg.GetWindowText(sMsg);

	if(sCallBack.GetLength() <= 0 || sCallBack.GetLength() >= 16)
	{
		MessageBox("회신번호가 없거나 자리수가 너무큽니다.", "확인", MB_ICONINFORMATION);
		return;
	}
	if(sMsg.GetLength() <= 0 || sMsg.GetLength() >= 90)
	{
		CString strTemp; 
		strTemp.Format("전송 글자수를 줄이세요. 현재%d바이트", sMsg.GetLength());
		MessageBox(strTemp, "확인", MB_ICONINFORMATION);
		//MessageBox("전송메시지가 없거나 자리수가 너무큽니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	sCallBack.Replace("-","");
	
	int nSuccessCount = 0;
	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		if(m_List.GetItemText(i, 7) == "휴대폰" 
			|| m_List.GetItemText(i, 7) == "아이디" )
		{
			CString sHp = m_List.GetItemText(i, 7) == "휴대폰" ? 
				m_List.GetItemText(i, 5) :
			m_List.GetItemText(i, 6);
			sHp.Replace("-","");

			/*
			CMkCommand pCmd(m_pMkDb, "insert_sms_data2");			
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), ::GetNowBranchCode());
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), 555);
			pCmd.AddParameter(typeString, typeInput, sHp.GetLength(), sHp);
			pCmd.AddParameter(typeString, typeInput, sCallBack.GetLength(), sCallBack);
			pCmd.AddParameter(typeString, typeInput, sMsg.GetLength(), sMsg);
			pCmd.AddParameter(typeString, typeInput, strEtc.GetLength(), strEtc);
			if(!pCmd.Execute()) 
				return;
			*/

			if(!::SendSmsNew(m_ci.m_nCompanyCode, 555, sHp, sCallBack, sMsg, "기사공지", "", ""))
			{
				MessageBox("SMS 전송 실패", "전송실패", MB_ICONINFORMATION);
				return;
			}

			m_List.SetItemText(i,7,"전송" );
			nSuccessCount++;
		}
	}

	CString strSuccessCount;
	if(m_strMessageMent != "")
	{
		strSuccessCount.Format("%d건 전송되었습니다.", nSuccessCount);
		strSuccessCount += "\n\n" + m_strMessageMent;
	}
		
	MessageBox(strSuccessCount, "확인", MB_ICONINFORMATION);
	OnOK();
		
	/*smsi = ::GetSMSBalance(::GetNowBranchCode()); 
	CString sBalance, sSMSCount, sMsgLen;
	sBalance.Format("%s원",GetMyNumberFormat(smsi.nSMSBarance));
	sSMSCount.Format("%s건", GetMyNumberFormat(smsi.nSMSBarance /DEFINE_SMS_AMOUNT) );
	m_stcBalance.SetWindowText(sBalance);
	m_stcSmsCount.SetWindowText(sSMSCount);*/
}

void CRiderMsgAllDlg2::OnBnClickedMentBtn()
{
	CMentDlg dlg;	
	if(dlg.DoModal() == IDOK)
	{
		m_edtMsg.SetWindowText(dlg.m_strMent);
		OnEnChangeMsgEdit();
	}
}

void CRiderMsgAllDlg2::OnEnChangeMsgEdit()
{
	CString strMent, strLength;
	m_edtMsg.GetWindowText(strMent);
	strLength.Format("글자수: %d/80", strMent.GetLength());
	m_stcMsgLen.SetWindowText(strLength);
	CRect rc;
	m_stcMsgLen.GetWindowRect(rc); 
	ScreenToClient(rc); 
	InvalidateRect(rc);
}

void CRiderMsgAllDlg2::OnBnClickedButton2()
{
	int nItem  =  -1;

	
	
	/*for(int i = 0; m_List.GetSelectedCount(); i++)
	{*/
	CUIntArray uArr;
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	
	while(pos != NULL)
	{		
		int nItem = m_List.GetNextSelectedItem(pos);
		uArr.Add(nItem);		
	}
	for(int i = uArr.GetCount() -1 ; i >= 0; i--)
	{
		nItem = uArr.GetAt(i);
		m_List.DeleteItem(nItem);
	}


	/*for(POSITION pos = m_List.GetNextItem())
		m_List.GetNextSelectedItem(pos)
		nItem = m_List.GetNextItem(nItem,LVNI_SELECTED );	
		m_List.DeleteItem(nItem);
	}*/
}

void CRiderMsgAllDlg2::OnBnClickedWorkStopCheck()
{
	int j = 1;
	for(int i = m_List.GetItemCount(); i > 0  ; i--)
	{
		CString strWorkStop = m_List.GetItemText(i,4 );
		if(strWorkStop == "중지")
		{
            m_List.DeleteItem(i);
			j = i -1;
		}
	}
	m_chkWorkStop.EnableWindow(FALSE);
}
