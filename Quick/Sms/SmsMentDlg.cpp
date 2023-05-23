// SmsMentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsMentDlg.h"

#include "MainFrm.h"

// CSmsMentDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsMentDlg, CMyDialog)
CSmsMentDlg::CSmsMentDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSmsMentDlg::IDD, pParent)
	, m_strHpContent(_T(""))
	
{
	m_strSpecialSymbol = "";
	m_bIntegrated = FALSE;
	m_nCompany = 0;
}

CSmsMentDlg::~CSmsMentDlg()
{
}

void CSmsMentDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_lstRegister);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranchCombo);
	DDX_Control(pDX, IDC_CONTENT_COMBO, m_cmbContent);	
	DDX_Control(pDX, IDC_RECEIVE_TEL_COMBO, m_cmbReceiveTel);
	DDX_Control(pDX, IDC_HP_CONTENT_EDIT, m_edtHpContent);
	DDX_Text(pDX, IDC_SPECIAL_SYMBOL_EDIT, m_strSpecialSymbol);	
	DDX_Control(pDX, IDC_SEND_TEL_COMBO, m_cmbSendTel);	
	DDX_Text(pDX, IDC_HP_CONTENT_EDIT, m_strHpContent);
	DDV_MaxChars(pDX, m_strHpContent, 80);
	DDX_Control(pDX, IDC_STRING_LENGTH_STATIC, m_stcStringLength);
	DDX_Control(pDX, IDC_SPECIAL_SYMBOL_EDIT, m_edtSpecialSymbol);
	DDX_Control(pDX, IDC_CHECK, m_chkDefault);
	DDX_Control(pDX, IDC_TIME_CHECK, m_chkTime);
	DDX_Control(pDX, IDC_COM_NAME_CHECK, m_chkCompanyName);
	DDX_Control(pDX, IDC_RNAME_CHECK, m_chkRiderName);
	DDX_Control(pDX, IDC_INSU_NAME_CHECK, m_chkInsuranceName);
	DDX_Control(pDX, IDC_RNO_CHECK, m_chkRNo);
	DDX_Control(pDX, IDC_INSU_NO_CHECK, m_chkInsuranceNo);
	DDX_Control(pDX, IDC_INSU_START_CHECK, m_chkInsuranceStart);
	DDX_Control(pDX, IDC_INSU_END_CHECK, m_chkInsuranceEnd);
	DDX_Control(pDX, IDC_START_CHECK, m_chkStart);
	DDX_Control(pDX, IDC_DEST_CHECK, m_chkDest);
	DDX_Control(pDX, IDC_AMOUNT_CHECK, m_chkAmount);
	DDX_Control(pDX, IDC_LIST1, m_lstPublic);
	DDX_Control(pDX, IDC_TIME_CHECK2, m_chkTime2);
	DDX_Control(pDX, IDC_ORDER_COMPANY_CHECK, m_chkOrderCompanyCheck);
	
	
}


BEGIN_MESSAGE_MAP(CSmsMentDlg, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
	ON_CBN_SELCHANGE(IDC_CONTENT_COMBO, OnCbnSelchangeContentCombo)
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, OnCbnSelchangeBranchCombo)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnNMClickList)
	
	ON_BN_CLICKED(IDC_REGISTER_BUTTON, OnBnClickedRegisterButton)
	ON_BN_CLICKED(IDC_MODIFY_BUTTON, OnBnClickedModifyButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, OnBnClickedDeleteButton)
	ON_EN_CHANGE(IDC_HP_CONTENT_EDIT, OnEnChangeHpContentEdit)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_TIME_CHECK, OnBnClickedTimeCheck)
	ON_BN_CLICKED(IDC_COM_NAME_CHECK, OnBnClickedComNameCheck)
	ON_BN_CLICKED(IDC_RNAME_CHECK, OnBnClickedRnameCheck)
	ON_BN_CLICKED(IDC_RNO_CHECK, OnBnClickedRnoCheck)
	ON_BN_CLICKED(IDC_INSU_NAME_CHECK, OnBnClickedInsuNameCheck)
	ON_BN_CLICKED(IDC_INSU_NO_CHECK, OnBnClickedInsuNoCheck)
	ON_BN_CLICKED(IDC_TIME_CHECK2, OnBnClickedTimeCheck2)
	ON_BN_CLICKED(IDC_INSU_START_CHECK, OnBnClickedInsuStartCheck)
	ON_BN_CLICKED(IDC_INSU_END_CHECK, OnBnClickedInsuEndCheck)
	ON_BN_CLICKED(IDC_START_CHECK, OnBnClickedStartCheck)
	ON_BN_CLICKED(IDC_DEST_CHECK, OnBnClickedDestCheck)
	ON_BN_CLICKED(IDC_AMOUNT_CHECK, OnBnClickedAmountCheck)
	ON_BN_CLICKED(IDC_ORDER_COMPANY_CHECK, OnBnClickedOrderCompanyCheck)
END_MESSAGE_MAP()


// CSmsMentDlg 메시지 처리기입니다.


BOOL CSmsMentDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lstRegister.SetImageList(&ImageList,LVSIL_SMALL); 
	m_lstRegister.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lstRegister.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	CImageList ImageList2; 
	ImageList2.Create(1,17,ILC_COLOR,1,1); 
	m_lstPublic.SetImageList(&ImageList2,LVSIL_SMALL); 
	m_lstPublic.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lstPublic.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_lstPublic.InsertColumn(0, "번호",  LVCFMT_LEFT, 40);
	m_lstPublic.InsertColumn(1, "선택한내용",LVCFMT_LEFT, 90);
	m_lstPublic.InsertColumn(2, "길이",  LVCFMT_LEFT, 40);

	m_lstRegister.InsertColumn(0, "번호",  LVCFMT_LEFT, 40);
	m_lstRegister.InsertColumn(1, "회사명",  LVCFMT_LEFT, 90);
	m_lstRegister.InsertColumn(2, "등록일",LVCFMT_LEFT, 60);
	m_lstRegister.InsertColumn(3, "선택",  LVCFMT_LEFT, 40);
	m_lstRegister.InsertColumn(4, "내용",  LVCFMT_LEFT, 450);
	m_lstRegister.InsertColumn(5, "수신이", LVCFMT_LEFT, 90);
	m_lstRegister.InsertColumn(6, "발신이", LVCFMT_LEFT, 90);

	m_edtHpContent.SetFontSize(16);
	m_edtSpecialSymbol.SetFontSize(16);
	CString sSymbol;

	sSymbol =	"■□▣▤▥▦▧▨▩▲△▶▷▼▽◀◁?◆◇◈⊙?○◎●◐◑、。★☆∥＼～〔〕〈〉《》「」­―＃＄％▼＆"\
				"『』【】±×≠≤≥∞∴°′″℃Å￠￡￥♂♀∠⊥⌒∂∇≡≒§※☆★○●◎◇◆□■△▲▽"\
				"→←↑↓↔〓≪≫√∽∝∵∫∬∈∋⊆⊇⊂⊃∪∩∧∨￢⇒⇔∀∃∑∏¤☎☏☜?☞♀♂♠♣♤♥♧♨♩♪♬"\
				"‰◁◀▷▶♤♠♡♥♧♣⊙▣◐◑▤▥▨▧▦▩♨☜☞¶†‡↕↗↙↖↘♭♩♪♬㉿㈜！☆★ㅁ";

	UpdateData();
	m_strSpecialSymbol = sSymbol;
	UpdateData(FALSE);

	CBranchInfo *pBi;
	if(m_ba.GetCount() > 1) {				
		for(int i = 0; i < m_ba.GetCount(); i++) {
			pBi = m_ba.GetAt(i);			
			int nItem = m_cmbBranchCombo.AddString(pBi->strBranchName);
			m_cmbBranchCombo.SetItemData(nItem,(DWORD_PTR)pBi);
			
		}
		m_bIntegrated = TRUE;
	}
	else {
		m_cmbBranchCombo.AddString("");		
		m_cmbBranchCombo.SetItemData(0, m_ci.m_nCompanyCode);
		m_bIntegrated = FALSE;			
	}

	m_cmbBranchCombo.SetCurSel(0);
	m_cmbContent.SetCurSel(0);
	
	OnCbnSelchangeContentCombo();


	return TRUE;	
}

void CSmsMentDlg::OnBnClickedButton7()
{
	
}
void CSmsMentDlg::CheckBoxEnable(int nIndex)
{
	switch(nIndex)
	{		
		case 0:			
		//	m_chkRiderName.EnableWindow(FALSE);						
			m_chkRNo.EnableWindow(FALSE);
			m_chkInsuranceName.EnableWindow(FALSE);
			m_chkInsuranceNo.EnableWindow(FALSE);
			m_chkInsuranceStart.EnableWindow(FALSE);
			m_chkInsuranceEnd.EnableWindow(FALSE);
			m_chkStart.EnableWindow(FALSE);
			m_chkDest.EnableWindow(FALSE);
			m_chkAmount.EnableWindow(FALSE);
			this->m_chkOrderCompanyCheck.EnableWindow(FALSE);
			break;
		case 1: 
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			m_chkRiderName.EnableWindow();			
			m_chkRNo.EnableWindow();
			m_chkInsuranceName.EnableWindow();
			m_chkInsuranceNo.EnableWindow();
			m_chkInsuranceStart.EnableWindow();
			m_chkInsuranceEnd.EnableWindow();
			m_chkStart.EnableWindow();
			m_chkDest.EnableWindow();
			m_chkAmount.EnableWindow();
			this->m_chkOrderCompanyCheck.EnableWindow();
			break;		
		case 7:		
			m_chkRiderName.EnableWindow();						
			m_chkRNo.EnableWindow();
			m_chkInsuranceName.EnableWindow();
			m_chkInsuranceNo.EnableWindow();
			m_chkInsuranceStart.EnableWindow();
			m_chkInsuranceEnd.EnableWindow();
			m_chkStart.EnableWindow();
			m_chkDest.EnableWindow();
			m_chkAmount.EnableWindow();
			this->m_chkOrderCompanyCheck.EnableWindow();
			break;
		case 8:
			m_chkRiderName.EnableWindow(FALSE);						
			m_chkRNo.EnableWindow(FALSE);
			m_chkInsuranceName.EnableWindow(FALSE);
			m_chkInsuranceNo.EnableWindow(FALSE);
			m_chkInsuranceStart.EnableWindow(FALSE);
			m_chkInsuranceEnd.EnableWindow(FALSE);
			m_chkStart.EnableWindow(FALSE);
			m_chkDest.EnableWindow(FALSE);
			m_chkAmount.EnableWindow(FALSE);
			this->m_chkOrderCompanyCheck.EnableWindow(FALSE);
			break;
	}

}
void CSmsMentDlg::OnCbnSelchangeContentCombo()
{
	m_lstRegister.DeleteAllItems();
	int nIndex = m_cmbContent.GetCurSel();
	int nCompanyIndex = m_cmbBranchCombo.GetCurSel();

	if(nIndex < 0){
		MessageBox("내용을 선택을 다시하여주세요","확인",MB_ICONINFORMATION);
		return;
	}
	m_cmbReceiveTel.ResetContent();
	switch(nIndex)
	{
		case 0:
			break;
		case 1: 
		case 2:
		case 3:
		case 4:	
			m_cmbReceiveTel.InsertString(0,"고객님전화로변환");
			break;
		case 5:					
		case 6:
		case 7:				
			m_cmbReceiveTel.InsertString(0,"기사님전화로변환");
			break;
		case 8:
			m_cmbReceiveTel.InsertString(0,"고객님전화로변환");
			break;
		
			
	}
	CheckBoxEnable(nIndex);
	m_cmbReceiveTel.SetCurSel(0);

	if(nCompanyIndex < 0){
		MessageBox("지사선택을 다시하여주세요","확인",MB_ICONINFORMATION);
		return;
	}
	
	if(m_lstRegister.GetItemCount() > 0)
		m_lstRegister.DeleteAllItems();	
		
	CBranchInfo *pBi = NULL;
	long nCompany = 0; BOOL bIntegrated = FALSE;
	if(m_cmbBranchCombo.GetCount() > 1)
	{
		pBi = (CBranchInfo*)m_cmbBranchCombo.GetItemData(nCompanyIndex);
		if(pBi == NULL)
			return;
		nCompany = pBi->nCompanyCode;
		bIntegrated = pBi->bIntegrated;
	}
	else
		nCompany = (long)m_cmbBranchCombo.GetItemData(0);

	//CWaitCursor wait;
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_sms_save_ment2_1");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);	
	pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), bIntegrated);	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(int), nIndex);	
	
	if(pRs2.Execute(&pCmd2))
	{		
		long nID = 0;
        CString sReceiveTel, sSendTel, sContent, sTel,  sBranchName;
		sReceiveTel =  sSendTel = sContent = sTel = sBranchName = "";		
		COleDateTime dtRegister;	
		BOOL bDefault = FALSE;
		int nItem = 0;
		int nNum = 1;
		char buffer[10];

		while(!pRs2.IsEOF()) {
			
			pRs2.GetFieldValue("nID", nID);			
			pRs2.GetFieldValue("sReceiveTel", sReceiveTel);			
			pRs2.GetFieldValue("sSendTel", sSendTel);
			pRs2.GetFieldValue("sContent", sContent);			
			pRs2.GetFieldValue("dtRegister", dtRegister);			
			pRs2.GetFieldValue("sTel", sTel);		
			pRs2.GetFieldValue("bDefault", bDefault);				
			pRs2.GetFieldValue("sBranchName", sBranchName);				

			m_lstRegister.InsertItem(nItem,itoa(nNum, buffer,10));
			m_lstRegister.SetItemText(nItem,1,sBranchName);
			m_lstRegister.SetItemText(nItem,2,dtRegister.Format("%y-%m-%d"));
			m_lstRegister.SetItemText(nItem,3,bDefault ? "적용":"");
			m_lstRegister.SetItemText(nItem,4,sContent);
			m_lstRegister.SetItemText(nItem,5,LF->GetDashPhoneNumber(sReceiveTel));
			m_lstRegister.SetItemText(nItem,6,LF->GetDashPhoneNumber(sSendTel));
			
			m_lstRegister.SetItemData(nItem, nID);
			nItem++; nNum++;
			pRs2.MoveNext();
		}
		pRs2.Close();

		if(sTel.GetLength() > 0)
		{
			m_cmbSendTel.ResetContent();
			m_cmbSendTel.InsertString(0,sTel);
		}
		m_cmbSendTel.SetCurSel(0);
	}	

}

void CSmsMentDlg::OnCbnSelchangeBranchCombo()
{
	OnCbnSelchangeContentCombo();
}

void CSmsMentDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{	
	int nItem = 0;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;	
	nItem = pNMListView->iItem;

	if(nItem < 0)
		return;

	if(m_lstRegister.GetItemText(nItem,3) == "적용")
		m_chkDefault.SetCheck(TRUE);
	else
		m_chkDefault.SetCheck(FALSE);

	m_edtHpContent.SetWindowText(m_lstRegister.GetItemText(nItem,4));
	m_cmbReceiveTel.SetWindowText(m_lstRegister.GetItemText(nItem,5));
	m_cmbSendTel.SetWindowText(m_lstRegister.GetItemText(nItem,6));	
	OnEnChangeHpContentEdit();
	*pResult = 0;
}


void CSmsMentDlg::OnBnClickedRegisterButton()
{
	UpdateData();
	if(m_strHpContent.GetLength() <= 0)
	{
		MessageBox("등록할 메세지를 기입하여 주세요","확인",MB_ICONINFORMATION);
		return;
	}
	else
	{	
		CBranchInfo *Brinfo = NULL;
		long nCompany = 0;
		CString sReceiveTel, sSendTel;
		sReceiveTel = sSendTel = "";
		BOOL bIntegrated = FALSE;
		int nIndex = m_cmbContent.GetCurSel();
		if(m_cmbBranchCombo.GetCount() > 1)
		{
			Brinfo = (CBranchInfo*)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel() );
			nCompany = Brinfo->nCompanyCode;
			bIntegrated = Brinfo->bIntegrated;
		}
		else
			nCompany = (long)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel() );

		m_cmbReceiveTel.GetWindowText(sReceiveTel);
		m_cmbSendTel.GetWindowText(sSendTel);
		if(sSendTel.GetLength() <= 0 || sReceiveTel.GetLength() <= 0){
			MessageBox("받는이및 보내는이의 항목에 값을 입력해주세요", "확인",MB_ICONINFORMATION);
			return;
		}
		sReceiveTel.Replace("-","");	
		sSendTel.Replace("-","");
	
		//CWaitCursor wait;		
		CMkCommand pCmd2(m_pMkDb, "insert_sms_save_ment");	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);	
		pCmd2.AddParameter(typeInt, typeInput, sizeof(int), nIndex);			
		pCmd2.AddParameter(typeString, typeInput, sReceiveTel.GetLength(),sReceiveTel);	
		pCmd2.AddParameter(typeString, typeInput, sSendTel.GetLength(),sSendTel);	
		pCmd2.AddParameter(typeString, typeInput, m_strHpContent.GetLength(),m_strHpContent);	
		pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkDefault.GetCheck());	

		if(!pCmd2.Execute())
			MessageBox("등록에 실패하였습니다.", "확인", MB_ICONINFORMATION);
		else
			MessageBox("등록 하였습니다.", "확인", MB_ICONINFORMATION);

		OnCbnSelchangeContentCombo();

	}
}

void CSmsMentDlg::OnBnClickedModifyButton()
{
	UpdateData(TRUE);
	
	if(m_strHpContent.GetLength() <= 0)
	{
		MessageBox("등록할 메세지를 기입하여 주세요","확인",MB_ICONINFORMATION);
		return;
	}
	else
	{	
		CBranchInfo *Brinfo = NULL;
		long nCompany = 0;
		CString sReceiveTel, sSendTel;
		sReceiveTel = sSendTel = "";

		int nIndex = m_cmbContent.GetCurSel();
		int nSelectListIndex = m_lstRegister.GetSelectionMark();
		if(m_cmbBranchCombo.GetCount() > 1)
		{
			Brinfo = (CBranchInfo*)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel());
			nCompany = Brinfo->nCompanyCode;
		}
		else
			nCompany = (long)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel() );

		m_cmbReceiveTel.GetWindowText(sReceiveTel);
		m_cmbSendTel.GetWindowText(sSendTel);
		sReceiveTel.Replace("-","");	
		sSendTel.Replace("-","");

		if(sSendTel.GetLength() <= 0 || sReceiveTel.GetLength() <= 0){
			MessageBox("받는이및 보내는이의 항목에 값을 입력해주세요", "확인",MB_ICONINFORMATION);
			return;
		}
		int nCurrentListIndex =  m_lstRegister.GetSelectionMark();		
		if(nCurrentListIndex < 0)
		{
			MessageBox("수정할 메세지를 다시선택 해주세요", "확인",MB_ICONINFORMATION);
			return;
		}
		nCurrentListIndex = (long)m_lstRegister.GetItemData(nCurrentListIndex);

	
		//CWaitCursor wait;
		CMkRecordset pRs2(m_pMkDb);
		CMkCommand pCmd2(m_pMkDb, "update_sms_save_ment");	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCurrentListIndex);	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(int), nIndex);					
		pCmd2.AddParameter(typeString, typeInput, sReceiveTel.GetLength(),sReceiveTel);	
		pCmd2.AddParameter(typeString, typeInput, sSendTel.GetLength(),sSendTel);	
		pCmd2.AddParameter(typeString, typeInput, m_strHpContent.GetLength(),m_strHpContent);	
		pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), m_chkDefault.GetCheck());	
		if(!pCmd2.Execute())
			MessageBox("수정에 실패하였습니다.", "확인", MB_ICONINFORMATION);
		else
			MessageBox("수정 하였습니다.", "확인", MB_ICONINFORMATION);

		OnCbnSelchangeContentCombo();
	}
	
}

void CSmsMentDlg::OnBnClickedDeleteButton()
{
	CBranchInfo *Brinfo = NULL;
	long nCompany = 0;
	
	if(m_cmbBranchCombo.GetCount() > 1)
	{
		Brinfo = (CBranchInfo*)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel() );
		nCompany = Brinfo->nCompanyCode;
	}
	else
		nCompany = (long)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel() );
	
	int nCurrentListIndex =  m_lstRegister.GetSelectionMark();		
	if(nCurrentListIndex < 0)
	{
		MessageBox("수정할 메세지를 다시선택 해주세요", "확인",MB_ICONINFORMATION);
		return;
	}
	nCurrentListIndex = (long)m_lstRegister.GetItemData(nCurrentListIndex);


	//CWaitCursor wait;
	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "delete_sms_save_ment");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);		
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCurrentListIndex);	
	if(!pCmd2.Execute())
		MessageBox("삭제에 실패하였습니다.", "확인", MB_ICONINFORMATION);
	else
		MessageBox("삭제 하였습니다.", "확인", MB_ICONINFORMATION);

	OnCbnSelchangeContentCombo();
}

void CSmsMentDlg::OnEnChangeHpContentEdit()
{
	UpdateData();	
	char buffer[10];
	int nLen = 0;	
	nLen = m_strHpContent.GetLength();	
	m_stcStringLength.SetWindowText(itoa(nLen,buffer,10));
	
}

void CSmsMentDlg::OnBnClickedCloseButton()
{
	OnCancel();
}

void CSmsMentDlg::OnBnClickedTimeCheck()
{
	
	UpdateData();
	CString str = m_strHpContent + "[시간]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkTime.GetCheck())
		m_strHpContent += "[시간]";
	else
		m_strHpContent.Replace("[시간]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();
}

void CSmsMentDlg::OnBnClickedComNameCheck()
{
	UpdateData();
	if(m_chkCompanyName.GetCheck())
	{
		m_lstPublic.DeleteAllItems();
		CBranchInfo *pBrinfo = NULL;
		long nCompany = 0;
		BOOL bIntegrated = FALSE;
		char buffer[10];
		int nItem = 0;
		int nNum = 1;	
		if(m_cmbBranchCombo.GetCount() > 1)
		{		
			for(int i = 1; i < m_cmbBranchCombo.GetCount() -1; i++)
			{
				pBrinfo = (CBranchInfo*)m_cmbBranchCombo.GetItemData(i);
				m_lstPublic.InsertItem(nItem,itoa(nNum, buffer,10));
				m_lstPublic.SetItemText(nItem,1,pBrinfo->strBranchName);
				m_lstPublic.SetItemText(nItem,2,
					itoa(pBrinfo->strBranchName.GetAllocLength(), buffer,10));
								
				nItem++; nNum++;				
			}
			
		}
		else{
				m_lstPublic.InsertItem(nItem,itoa(nNum, buffer,10));
				m_lstPublic.SetItemText(nItem,1,m_ci.m_strName);
				m_lstPublic.SetItemText(nItem,2,
					itoa(m_ci.m_strName.GetAllocLength(), buffer,10));
		}
			

	}
	CString str = m_strHpContent + "[퀵회사명]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkRiderName.GetCheck())
		m_strHpContent += "[퀵회사명]";
	else
		m_strHpContent.Replace("[퀵회사명]","");
	UpdateData(FALSE);
}

void CSmsMentDlg::OnBnClickedRnameCheck()
{
	return;

	UpdateData();
	CString str = m_strHpContent + "[기사명]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkRiderName.GetCheck())
	{
		m_lstPublic.DeleteAllItems();
		CBranchInfo *pBrinfo = NULL;
		long nCompany = 0;
		BOOL bIntegrated = FALSE;
		if(m_cmbBranchCombo.GetCount() > 1)
		{
			pBrinfo = (CBranchInfo*)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel());
			nCompany = pBrinfo->nCompanyCode;
			bIntegrated = pBrinfo->bIntegrated;
		}
		else		
			nCompany = m_ci.m_nCompanyCode;

		char buffer[10];
		//CWaitCursor wait;
		CMkRecordset pRs2(m_pMkDb);
		CMkCommand pCmd2(m_pMkDb, "select_rider_name_list_1");	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
		pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), bIntegrated);
		
		if(pRs2.Execute(&pCmd2))
		{		
			CString sName = "";
			int nItem = 0;
			int nNum = 1;			

			while(!pRs2.IsEOF()) {				
				pRs2.GetFieldValue("sName", sName);			
				m_lstPublic.InsertItem(nItem,itoa(nNum, buffer,10));
				m_lstPublic.SetItemText(nItem,1,sName);
				m_lstPublic.SetItemText(nItem,2,itoa(sName.GetAllocLength(), buffer,10));
								
				nItem++; nNum++;
				pRs2.MoveNext();
			}
			pRs2.Close();
		}
	}

	if(m_chkRiderName.GetCheck())
		m_strHpContent += "[기사명]";
	else
		m_strHpContent.Replace("[기사명]","");
	UpdateData(FALSE);
	
}

void CSmsMentDlg::OnBnClickedRnoCheck()
{
	UpdateData();
	CString str = m_strHpContent + "[사]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkRNo.GetCheck())
		m_strHpContent += "[사]";
	else
		m_strHpContent.Replace("[사]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();

}

void CSmsMentDlg::OnBnClickedInsuNameCheck()
{
	UpdateData();
	CString str = m_strHpContent +"[보험사]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkInsuranceName.GetCheck())
	{
		m_lstPublic.DeleteAllItems();
		CBranchInfo *pBrinfo = NULL;
		long nCompany = 0;
		BOOL bIntegrated = FALSE;
		if(m_cmbBranchCombo.GetCount() > 1)
		{
			pBrinfo = (CBranchInfo*)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel());
			nCompany = pBrinfo->nCompanyCode;
			bIntegrated = pBrinfo->bIntegrated;
		}
		else		
			nCompany = m_ci.m_nCompanyCode;

		char buffer[10];
		//CWaitCursor wait;
		CMkRecordset pRs2(m_pMkDb);
		CMkCommand pCmd2(m_pMkDb, "select_insurance_name_list_1");	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);	
		pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), bIntegrated);	
		
		if(pRs2.Execute(&pCmd2))
		{		
			CString sName = "";
			int nItem = 0;
			int nNum = 1;			

			while(!pRs2.IsEOF()) {				
				pRs2.GetFieldValue("sName", sName);			
				m_lstPublic.InsertItem(nItem,itoa(nNum, buffer,10));
				m_lstPublic.SetItemText(nItem,1,sName);
				m_lstPublic.SetItemText(nItem,2,itoa(sName.GetAllocLength(), buffer,10));
								
				nItem++; nNum++;
				pRs2.MoveNext();
			}
			pRs2.Close();
		}
	}
	if(m_chkInsuranceName.GetCheck())
		m_strHpContent += "[보험사]";
	else
		m_strHpContent.Replace("[보험사]","");
	UpdateData(FALSE);	
}

void CSmsMentDlg::OnBnClickedInsuNoCheck()
{
	UpdateData();
	CString str = m_strHpContent +"[보험증권번호]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkInsuranceNo.GetCheck())
	{
		m_lstPublic.DeleteAllItems();
		CBranchInfo *pBrinfo = NULL;
		long nCompany = 0;
		BOOL bIntegrated = FALSE;
		if(m_cmbBranchCombo.GetCount() > 1)
		{
			pBrinfo = (CBranchInfo*)m_cmbBranchCombo.GetItemData(m_cmbBranchCombo.GetCurSel());
			nCompany = pBrinfo->nCompanyCode;
			bIntegrated = pBrinfo->bIntegrated;
		}
		else		
			nCompany = m_ci.m_nCompanyCode;

		char buffer[10];
		//CWaitCursor wait;
		CMkRecordset pRs2(m_pMkDb);
		CMkCommand pCmd2(m_pMkDb, "select_insurance_no_list_1");	
		pCmd2.AddParameter(typeLong, typeInput, sizeof(long), nCompany);	
		pCmd2.AddParameter(typeBool, typeInput, sizeof(BOOL), bIntegrated);
		
		if(pRs2.Execute(&pCmd2))
		{		
			CString sName = "";
			int nItem = 0;
			int nNum = 1;			

			while(!pRs2.IsEOF()) {				
				pRs2.GetFieldValue("sName", sName);			
				m_lstPublic.InsertItem(nItem,itoa(nNum, buffer,10));
				m_lstPublic.SetItemText(nItem,1,sName);
				m_lstPublic.SetItemText(nItem,2,itoa(sName.GetAllocLength(), buffer,10));
								
				nItem++; nNum++;
				pRs2.MoveNext();
			}
			pRs2.Close();
		}
	}
	if(m_chkInsuranceNo.GetCheck())
		m_strHpContent += "[보험증권번호]";
	else
		m_strHpContent.Replace("[보험증권번호]","");
	UpdateData(FALSE);	
}

void CSmsMentDlg::OnBnClickedTimeCheck2()
{
	UpdateData();
	
	CString str = m_strHpContent +"[년월일]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkTime2.GetCheck())
		m_strHpContent += "[년월일]";
	else
		m_strHpContent.Replace("[년월일]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();
}

void CSmsMentDlg::OnBnClickedInsuStartCheck()
{
	UpdateData();
	CString str = m_strHpContent +"[보시작]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkInsuranceStart.GetCheck())
		m_strHpContent += "[보시작]";
	else
		m_strHpContent.Replace("[보시작]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();
}

void CSmsMentDlg::OnBnClickedInsuEndCheck()
{
	UpdateData();
		CString str = m_strHpContent +"[보종료]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkInsuranceEnd.GetCheck())
		m_strHpContent += "[보종료]";
	else
		m_strHpContent.Replace("[보종료]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();
}

void CSmsMentDlg::OnBnClickedStartCheck()
{
	UpdateData();
		CString str = m_strHpContent + "[출발지정]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkStart.GetCheck())
		m_strHpContent += "[출발지정]";
	else
		m_strHpContent.Replace("[출발지정]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();
}

void CSmsMentDlg::OnBnClickedDestCheck()
{
	UpdateData();
		CString str = m_strHpContent + "[도착지정]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkDest.GetCheck())
		m_strHpContent += "[도착지정]";
	else
		m_strHpContent.Replace("[도착지정]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();
}

void CSmsMentDlg::OnBnClickedAmountCheck()
{
	UpdateData();
	CString str = m_strHpContent + "[금액]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkAmount.GetCheck())
		m_strHpContent += "[금액]";
	else
		m_strHpContent.Replace("[금액]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();
}

void CSmsMentDlg::OnBnClickedOrderCompanyCheck()
{
	UpdateData();
	CString str = m_strHpContent + "[오더회사]";
	if(str.GetAllocLength() > 80){
		MessageBox("80자가 넘어갑니다.","확인",MB_ICONINFORMATION);
		return;
	}
	if(m_chkAmount.GetCheck())
		m_strHpContent += "[오더회사]";
	else
		m_strHpContent.Replace("[오더회사]","");
	UpdateData(FALSE);

	OnEnChangeHpContentEdit();
}