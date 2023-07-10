// ConsignSettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ConsignSettingDlg.h"


// CConsignSettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConsignSettingDlg, CDialog)

CConsignSettingDlg::CConsignSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConsignSettingDlg::IDD, pParent)
	, m_From(COleDateTime::GetCurrentTime())
	, m_To(COleDateTime::GetCurrentTime())
{

	m_bNew = FALSE;
	m_nShareCode1 = 0;

	m_sOtherCompanyName = "";
	m_nOtherCompany = 0;

	m_dtReserveDate = COleDateTime::GetCurrentTime();
	

m_nModifyID = 0;
	
	
}

CConsignSettingDlg::~CConsignSettingDlg()
{
}

void CConsignSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONSIGNMENT_COMPANY_EDIT , m_edtOtherCompanyName);
	DDX_Control(pDX, IDC_NOW_RATE_EDIT , m_edtNowApplyRate);
	DDX_Control(pDX, IDC_NOW_APPLY_DATE_EDIT , m_edtNowApplyDate);

	DDX_Control(pDX, IDC_CHANGE_RATE_COMBO , m_cmbChangeRate);
	DDX_Control(pDX, IDC_RESERVE_COMBO , m_cmbReserved);

	DDX_Control(pDX, IDC_CHANGE_RATE_DATE , m_dtpReserveDate);
	DDX_DateTimeCtrl(pDX, IDC_CHANGE_RATE_DATE ,m_dtReserveDate );	
	DDX_Control(pDX, IDC_ALL_LOG_CHECK,m_chkAlllog);
	DDX_Control(pDX, IDC_SETTING_REPORT,m_SettingReport);
	DDX_Control(pDX, IDC_OK_BTN,m_btnConfirm); 
	DDX_Control(pDX, IDC_MODIFY_BTN,m_btnModify); 
	DDX_Control(pDX, IDC_REQUEST_CANCEL_BTN,m_btnCancelRequest);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_From);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_To);
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_INNER_SEARCH_EDIT, m_edtSearch);
	
}



BEGIN_MESSAGE_MAP(CConsignSettingDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_RESERVE_COMBO, &CConsignSettingDlg::OnCbnSelchangeReserveCombo)
	ON_BN_CLICKED(IDC_OK_BTN, &CConsignSettingDlg::OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CConsignSettingDlg::OnBnClickedCancelBtn)
	
	ON_BN_CLICKED(IDC_MODIFY_BTN, &CConsignSettingDlg::OnBnClickedModifyBtn)
	ON_BN_CLICKED(IDC_REQUEST_CANCEL_BTN, &CConsignSettingDlg::OnBnClickedRequestCancelBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CConsignSettingDlg::OnBnClickedSearchBtn)
	ON_EN_CHANGE(IDC_INNER_SEARCH_EDIT, &CConsignSettingDlg::OnEnChangeInnerSearchEdit)
END_MESSAGE_MAP()


// CConsignSettingDlg 메시지 처리기입니다.

BOOL CConsignSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_DateBtn.InitDateButton(&m_dtFrom, &m_dtTo);
	m_DateBtn.OnMenuMonth();


	InitControl();
	DataInput();

	int nCol = 0;
	m_SettingReport.InsertColumn(nCol++, "생성일",DT_LEFT,  90,FALSE);
	m_SettingReport.InsertColumn(nCol++, "타입",DT_LEFT,  45,FALSE);
	m_SettingReport.InsertColumn(nCol++, "연계회사",DT_LEFT,  110,FALSE);
	m_SettingReport.InsertColumn(nCol++,    "도시", DT_LEFT, 55, FALSE);	
	m_SettingReport.InsertColumn(nCol++, "기존이율",DT_LEFT,  60,FALSE);
	m_SettingReport.InsertColumn(nCol++, "변경이율",DT_LEFT,  60,FALSE);
	m_SettingReport.InsertColumn(nCol++, "작업회사",DT_LEFT,  80,FALSE);
	m_SettingReport.InsertColumn(nCol++, "작업자",DT_LEFT,  50,FALSE);
	m_SettingReport.InsertColumn(nCol++, "예약",DT_LEFT,  50,FALSE);
	m_SettingReport.InsertColumn(nCol++, "예약일",DT_LEFT,  90,FALSE);


	if(m_bNew)
	{
		m_btnConfirm.EnableWindow(TRUE);
		m_btnCancelRequest.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);
	}
	else
	{
		m_btnConfirm.EnableWindow(FALSE);
		m_btnCancelRequest.EnableWindow(TRUE);
		m_btnModify.EnableWindow(TRUE);
	}
	
	m_SettingReport.Populate();

	if(!m_bNew)
	{
		LogList();
		
			
	}
	else
	{		

	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CConsignSettingDlg::InitControl()
{

	m_DateBtn.InitDateButton(&m_dtFrom, &m_dtTo);
	m_DateBtn.OnMenuMonth();


	m_edtOtherCompanyName.SetMyFont("맑은 고딕", 17,  FW_BOLD);
	m_edtOtherCompanyName.SetUserOption(RGB(0, 0, 255), RGB(252, 237, 100), "", TRUE);
	m_edtNowApplyRate.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtNowApplyRate.SetUserOption(RGB(0, 0, 255), RGB(252, 237, 100), "", TRUE);
	m_edtNowApplyDate.SetMyFont("맑은 고딕", 17, FW_BOLD);
	m_edtNowApplyDate.SetUserOption(RGB(0, 0, 255), RGB(252, 237, 100), "", TRUE);


	CString str = "";
	for(int i = 0; i < 21; i++)
	{
		str.Format("%d%%", i * 5);
		m_cmbChangeRate.InsertString(i , str);
	}
	if(m_bNew)
	{
		m_cmbChangeRate.SetCurSel(0);
		m_cmbReserved.SetCurSel(0);
	}
}


void CConsignSettingDlg::DataInput()
{

	CString sAcceptCompany = "", sNowRate = "", sAcceptApplyDate = "";
	int nNowRate = 0, nRequestRate = 0;
	COleDateTime dtAcceptApply, dtApplyReserve;
	BOOL bReserveAccept = FALSE, bReserve = FALSE;
	long nRequestRegisterCompany = 0;
	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_consignment_modify2011"); 
	pCmd.AddParameter(m_ci.GetShareCode1());	
	pCmd.AddParameter(m_nOtherCompany);
	pCmd.AddParameter(m_nModifyID);
	
	if(!pRs.Execute(&pCmd)) return;

	if(pRs.GetRecordCount() == 0) return;
	
	pRs.GetFieldValue("sAcceptCompany", sAcceptCompany);
	pRs.GetFieldValue("nNowRate", nNowRate);
	pRs.GetFieldValue("dtAcceptApply", dtAcceptApply);
	pRs.GetFieldValue("nRequestRate", nRequestRate);
	pRs.GetFieldValue("bReserve", bReserve);
	pRs.GetFieldValue("bReserveAccept", bReserveAccept);
	pRs.GetFieldValue("dtApplyReserve", dtApplyReserve);
	pRs.GetFieldValue("nRequestRegisterCompany", nRequestRegisterCompany);
	
	if(dtAcceptApply.m_status == COleDateTime::null  || dtAcceptApply.m_status == COleDateTime::invalid)
	{
		sNowRate = "";
		sAcceptApplyDate = "미적용";
	}
	else
	{
		sNowRate.Format("%d%%", nNowRate);
		sAcceptApplyDate = dtAcceptApply.Format("%Y-%m-%d %H:%M:%S");
		
	}

	UpdateData();
	m_edtNowApplyDate.SetWindowText(sAcceptApplyDate);
	m_edtNowApplyRate.SetWindowText(sNowRate);
	m_edtOtherCompanyName.SetWindowText(sAcceptCompany);

	if(nRequestRegisterCompany  > 0 && bReserve ) //bReserve && nRequestRate > 0)
	{
		m_cmbReserved.SetCurSel(1);
		if(bReserve)
		{
			if(dtApplyReserve.m_status == COleDateTime::null  || dtApplyReserve.m_status == COleDateTime::invalid)
			{
				MessageBox("예약일자가 오류입니다. ", "확인", MB_ICONINFORMATION);
				dtApplyReserve = COleDateTime::GetCurrentTime();
			}
			m_dtpReserveDate.EnableWindow(TRUE);
		
			m_dtReserveDate.SetDateTime(dtApplyReserve.GetYear(), dtApplyReserve.GetMonth(), dtApplyReserve.GetDay(),
				0,0,0);
			
		}
		
	}
	else
		m_cmbReserved.SetCurSel(0);

		// 요청한거는 수락한 회사는 다시수정금지
	if(nRequestRegisterCompany > 0 && nRequestRegisterCompany != m_ci.GetShareCode1() && !m_bNew)
	{
		m_btnConfirm.EnableWindow(FALSE);
		
	}

	m_cmbChangeRate.SetCurSel(nRequestRate / 5 );
	UpdateData(FALSE);

}

void CConsignSettingDlg::LogList()
{
	if(m_SettingReport.GetRecords()->GetCount() > 0)
		m_SettingReport.DeleteAllItems();

	int nNowRate = 0, nLogType = 0;
	long nCompany= 0,nReceiveCompany = 0, nBeforeRate= 0,nAfterRate = 0,
		nWNo = 0,nWCompany = 0, nID= 0, nRequestCompany = 0 ;
	CString sAcceptCompany = "", sNowRate = "",sCompanyName ="",
		sReceiveCompanyName ="", sCityCompany="", sCityReceiveCompany="", 
		sOterLinkCompanyName = "", sWorkCompanyName = "",		sWName ="", sCity = "";
	COleDateTime dtAcceptApply, dtLog, dtApplyReserve;
	BOOL bReserve = FALSE, bReserveAccept = FALSE;

	CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_consignment_log_list2"); 
	pCmd.AddParameter(m_nOtherCompany);
	pCmd.AddParameter(m_ci.GetShareCode1());	
	pCmd.AddParameter(m_chkAlllog.GetCheck());	
	pCmd.AddParameter(m_From);	
	pCmd.AddParameter(m_To);	



	if(!pRs.Execute(&pCmd)) return;

	for(int i =0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtLog", dtLog);
		pRs.GetFieldValue("nLogType", nLogType);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("sCompanyName", sCompanyName);
		pRs.GetFieldValue("nReceiveCompany", nReceiveCompany);
		pRs.GetFieldValue("sReceiveCompanyName", sReceiveCompanyName);

		
		pRs.GetFieldValue("nBeforeRate", nBeforeRate);
		pRs.GetFieldValue("nAfterRate", nAfterRate);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("nWCompany", nWCompany);
		pRs.GetFieldValue("sCityCompany", sCityCompany);
		pRs.GetFieldValue("sCityReceiveCompany", sCityReceiveCompany);
		pRs.GetFieldValue("nID", nID);

		pRs.GetFieldValue("bReserve", bReserve);
		pRs.GetFieldValue("dtApplyReserve", dtApplyReserve);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("bReserveAccept", bReserveAccept);

		sOterLinkCompanyName = (nCompany == m_ci.GetShareCode1()) 
			? sReceiveCompanyName : sCompanyName;
		sWorkCompanyName = (nWCompany == m_ci.GetShareCode1())
			? m_ci.GetCompanyName() : sCompanyName;
		sCity = (nWCompany == m_ci.GetShareCode1())	
			?  sCityReceiveCompany : sCityCompany  ;

		m_SettingReport.InsertItem(i, dtLog.Format("%y-%m-%d %H:%M"));
		m_SettingReport.SetItemText(i, 1, GetLogType(nLogType));
		m_SettingReport.SetItemText(i, 2, sOterLinkCompanyName);
		m_SettingReport.SetItemText(i, 3, sCity);	
		m_SettingReport.SetItemText(i, 4, nBeforeRate);
		m_SettingReport.SetItemText(i, 5, nAfterRate);
		m_SettingReport.SetItemText(i, 6, sWorkCompanyName);
		m_SettingReport.SetItemText(i, 7, sWName);
		m_SettingReport.SetItemText(i, 8, bReserve ? "예약" : "");
		m_SettingReport.SetItemText(i, 9, bReserve ? dtApplyReserve.Format("%y-%m-%d %H:%M") : "");
		pRs.MoveNext();
	}

	pRs.Close();

	m_SettingReport.Populate();
}

CString CConsignSettingDlg::GetLogType(int nType)
{

	CString sType = "";
	//1. 등록,  2 수정  3, 수락  4. 거부  5 . 삭제		 
	switch(nType)
	{
	case 0:
		sType = "신규요청";
		break;
	case 1:
		sType = "적용됨";
		break;
	case 2:
		sType = "수정요청";
		break;
	case 3:
		sType = "변경";
		break;
	case 4:
		sType = "거부";
		break;
	case 5:
		sType = "삭제";
		break;
	case 6:
		sType = "취소";
		break;
	case 7:
		sType = "수락";
		break;
	default:
		sType = "";
		break;

	}
	return sType;
}

void CConsignSettingDlg::OnCbnSelchangeReserveCombo()
{
		m_dtpReserveDate.EnableWindow(m_cmbReserved.GetCurSel());
		
	
}


void CConsignSettingDlg::OnBnClickedModifyBtn()
{
	EditChaeckData();

}
void CConsignSettingDlg::OnBnClickedOkBtn()
{

	
		NewCheckData();
	
}
void CConsignSettingDlg::OnBnClickedRequestCancelBtn()
{
		DeleteCheckData();
}


void CConsignSettingDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}


void CConsignSettingDlg::DeleteCheckData()
{
	try{

	

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "delete_consignment_company2011" );
		pCmd.AddParameter( m_ci.GetShareCode1());
		pCmd.AddParameter(m_nOtherCompany);		
		pCmd.AddParameter(m_cmbChangeRate.GetCurSel() );
		pCmd.AddParameter(m_cmbReserved.GetCurSel());
		pCmd.AddParameter(GetReserveTime());
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.nWNo);
		pCmd.AddParameter(m_nModifyID);
		CMkParameter *pParOUTPUT = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		if(!pCmd.Execute()) return;	

		int nOUTPUT = 0;
		pParOUTPUT->GetValue(nOUTPUT);

		if(nOUTPUT == 100 )
			throw "해당시도에 연계되어 있는 업체가 있습니다. ";
		if(nOUTPUT == 300 )
			throw " 삭제할 수정 요청건 아닙니다.";
		if(nOUTPUT == 400 )
			throw " 수정한 회사의 내역이 아니라 삭제불가능 ";
		/*if(nOUTPUT == 500 )
		throw "고객님의 정산잔액이 없습니다. 충전하시고 연계하세요 ";
		if(nOUTPUT == 600 )
		throw " 연계회사의 정산금이 없습니다.  ";*/
		

		MessageBox("변경한 요청한 내역을 삭제했습니다", "확인" , MB_ICONINFORMATION);

		OnOK();
	}
	catch(char *e)
	{
		MessageBox(e , "확인" , MB_ICONINFORMATION);
	}
	catch(CString s)
	{
		MessageBox(s, "확인" , MB_ICONINFORMATION);
	}
}

void CConsignSettingDlg::NewCheckData()
{
	try{
		
		if(m_cmbReserved.GetCurSel() == 1 && COleDateTime::GetCurrentTime() > GetReserveTime() )
			throw "예약으로 지정한 시간이 현재시간보다 이전입니다.";


		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "insert_consignment_add_company2011" );
		pCmd.AddParameter( m_ci.GetShareCode1());
		pCmd.AddParameter(m_nOtherCompany);		
		pCmd.AddParameter(m_cmbChangeRate.GetCurSel() );
		pCmd.AddParameter(m_cmbReserved.GetCurSel());
		pCmd.AddParameter(GetReserveTime());
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.nWNo);

		CMkParameter *pParOUTPUT = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		if(!pCmd.Execute()) return;	

		int nOUTPUT = 0;
		pParOUTPUT->GetValue(nOUTPUT);
		
		if(nOUTPUT == 100 )
			throw "해당시도에 연계되어 있는 업체가 있습니다. ";
		if(nOUTPUT == 300 )
			throw " 예약이 수락되어 있어 수정및 신규가 불가능합니다. 수락업체에서 요청거부 ";
		/*if(nOUTPUT == 500 )
			throw "고객님의 정산잔액이 없습니다. 충전하시고 연계하세요 ";
		if(nOUTPUT == 600 )
			throw " 연계회사의 정산금이 없습니다.  ";*/
		if(nOUTPUT == 700 )
			throw "요청회사의 도시지역이 올바르지 않습니다";
		if(nOUTPUT == 800 )
			throw " 연계회사의 도시지역이 올바르지 않습니다.  ";

		MessageBox("연계등록을 시켰습니다.", "확인" , MB_ICONINFORMATION);

		OnOK();
	}
	catch(char *e)
	{
		MessageBox(e , "확인" , MB_ICONINFORMATION);
	}
	catch(CString s)
	{
		MessageBox(s, "확인" , MB_ICONINFORMATION);
	}
	

}
void CConsignSettingDlg::EditChaeckData( )
{

	try{
		

		if(m_cmbReserved.GetCurSel() == 1 && COleDateTime::GetCurrentTime() > GetReserveTime() )
			throw "예약으로 지정한 시간이 현재시간보다 이전입니다.";


		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_consignment_add_company2011" );
		pCmd.AddParameter( m_ci.GetShareCode1());
		pCmd.AddParameter(m_nOtherCompany);
		pCmd.AddParameter(m_cmbChangeRate.GetCurSel() );
		pCmd.AddParameter(m_cmbReserved.GetCurSel());							      
		pCmd.AddParameter(GetReserveTime());
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(m_ui.nWNo);		
		pCmd.AddParameter(m_nModifyID);	
		CMkParameter *pParOUTPUT = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		pCmd.Execute();	

		int nOUTPUT = 0;
		pParOUTPUT->GetValue(nOUTPUT);
		if(nOUTPUT == 100 )
			throw "연계할 회사가 없습니다. 다시 갱신하세요";

		
		if(nOUTPUT == 300 )
			throw "요청한곳에서만 수정이 가능합니다. ";
		if(nOUTPUT == 400 )
			throw "요청한곳에서만 수정이 가능합니다. ";
		/*if(nOUTPUT == 500 )
			throw "고객님의 정산잔액이 없습니다. 충전하시고 연계하세요 ";
		if(nOUTPUT == 600 )
			throw " 연계회사의 정산금이 없습니다.  ";*/

		if(nOUTPUT == 1000 )
			MessageBox("수정되었습니다." , "확인" , MB_ICONINFORMATION);
			
		OnOK();
		
	}
	catch(char *e)
	{
		MessageBox(e , "확인" , MB_ICONINFORMATION);
	}
	catch(CString s)
	{
		MessageBox(s, "확인" , MB_ICONINFORMATION);
	}



}

COleDateTime CConsignSettingDlg::GetReserveTime()
{
	UpdateData();
	COleDateTime dt (m_dtReserveDate.GetYear(), m_dtReserveDate.GetMonth(), m_dtReserveDate.GetDay(), 
		0, 0, 0 );

	//CString sDt; sDt.Format("%d-%d-%d %d:%d:%d", dt.GetYear(), dt.GetMonth(), dt.GetDay(), dt.GetHour(), dt.GetMinute(),dt.GetSecond());
	//MessageBox(sDt);
	return dt;

}
void CConsignSettingDlg::OnBnClickedSearchBtn()
{
LogList();
}
void CConsignSettingDlg::OnEnChangeInnerSearchEdit()
{
	CString sSearch = "";
	
	m_edtSearch.GetWindowText(sSearch);

	m_SettingReport.Filter(sSearch);
}
