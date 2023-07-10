// ConsignLinkDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "ConsignLinkDlg.h"
#include "POIUnit.h"
#include "RcpPlaceInfo.h"
//#include "RcpPlaceInfo.cpp"
#include "POIDataNew.h"
#include "RcpDlg.h"
#include "RcpView.h"
#include "Charge.h"
#define TEMP_PLACE	0x1000
// CConsignLinkDlg 대화 상자입니다.
#define  CONSIGN_TYPE_START 100
#define  CONSIGN_TYPE_DEST 200
#define  ALL_WINDOW 677
#define  TOP_WINDOW 400
#define  BOTTOM_WINDOW 277



IMPLEMENT_DYNAMIC(CConsignLinkDlg, CMyDialog)

CConsignLinkDlg::CConsignLinkDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CConsignLinkDlg::IDD, pParent)
{


	m_bRcpDlgForgroudView = FALSE;
	m_nCompany = 0;
	m_nTerminalWayID =  0;
	m_nTerminalTempWayID = 0;
	m_sDestSido = "";
	m_pRcpDlgWndFront = NULL;
	m_pRcpDlgWndBack = NULL;
	m_pDestPlaceInfoTemp = NULL;
	m_pDestPlaceInfoTemp = new CRcpPlaceInfo(pParent, TEMP_PLACE);
	m_nConsignTNo = 0;
	m_nOrderTNo = 0;
	m_nConCommissionCharge = 0;


	m_sStartCharge = "0";
	m_sDestCharge = "0";
	m_sTransCharge= "0";
	m_sTempCharge= "0";
	m_sCommissionCharge= "0";
	m_sTotalCharge= "0";
	m_sDestSido = "";
	COleDateTime dtCurrent(COleDateTime::GetCurrentTime());
	m_dtStart = dtCurrent;
	m_dtDest = dtCurrent;

	m_nWindowType = ALL_WINDOW;
}




CConsignLinkDlg::~CConsignLinkDlg()
{
	DelList();
	/*if(m_pPaintManager)
		delete m_pPaintManager;*/
	if(m_pDestPlaceInfoTemp)
		delete m_pDestPlaceInfoTemp;
}

void CConsignLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_START_DONG_EDIT, m_edtTitleStart);
	DDX_Control(pDX, IDC_START_TERMINAL_LINK_EDIT, m_edtTitleStartTerminalLink);

	DDX_Control(pDX, IDC_START_TERMINAL_EDIT, m_edtTitleStartTerminal);
	DDX_Control(pDX, IDC_DEST_TERMINAL_EDIT, m_edtTitleDestTerminal);

	DDX_Control(pDX, IDC_DEST_TERMINAL_LINK_EDIT, m_edtTitleDestTerminalLink);
	DDX_Control(pDX, IDC_DEST_DONG_EDIT, m_edtTitleDest);
	DDX_Control(pDX, IDC_START_CHARGE_EDIT, m_edtStartCharge);
	DDX_Control(pDX, IDC_TERMINAL_CHARGE_EDIT, m_edtTransCharge);
	DDX_Control(pDX, IDC_DEST_CHARGE_EDIT, m_edtDestCharge);
	
	DDX_Control(pDX, IDC_TEMP_CHARGE_EDIT, m_edtTempCharge);
	DDX_Control(pDX, IDC_COMMISSION_CHARGE_EDIT, m_edtCommissionCharge);
	DDX_Control(pDX, IDC_TOTAL_CHARGE_EDIT, m_edtTotalCharge);		
	DDX_Control(pDX, IDC_CUSTOM1, m_List);
	DDX_Control(pDX, IDC_CONSIGN_BTN, m_btnConsign);
	DDX_Control(pDX, IDC_CONSIGN_LINK_BTN, m_btnConsignLink);

	DDX_Text(pDX, IDC_START_CHARGE_EDIT,	m_sStartCharge);
	DDX_Text(pDX, IDC_DEST_CHARGE_EDIT,		m_sDestCharge);
	DDX_Text(pDX, IDC_TERMINAL_CHARGE_EDIT, m_sTransCharge);
	DDX_Text(pDX, IDC_TEMP_CHARGE_EDIT, m_sTempCharge);

	DDX_Text(pDX, IDC_COMMISSION_CHARGE_EDIT, m_sCommissionCharge);
	DDX_Text(pDX, IDC_TOTAL_CHARGE_EDIT, m_sTotalCharge);
	DDX_Control(pDX, IDC_BACK_CHARGE_STATIC, m_stcBackCharge);
	DDX_Control(pDX, IDC_FRONT_CHARGE_STATIC, m_stcFrontCharge);
	DDX_DateTimeCtrl(pDX, IDC_CON_START_DTP, m_dtStart);
	DDX_DateTimeCtrl(pDX, IDC_CON_DEST_DTP, m_dtDest);	

	DDX_Control(pDX, IDC_BUSNAME_EDIT, m_edtBusName);
	DDX_Control(pDX, IDC_BUSNO_EDIT, m_edtBusNo);
	DDX_Control(pDX, IDC_INVOICE_NO_EDIT, m_edtInvoiceNo);
	DDX_Control(pDX, IDC_CON_START_DTP, m_dtpStart);
	DDX_Control(pDX, IDC_CON_DEST_DTP, m_dtpDest);	
	DDX_Control(pDX, IDC_ELAPSED_COMBO, m_cmbElapsed);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);

	DDX_Control(pDX, IDC_CUSTOM2, m_CompanyOrderList);
	DDX_Control(pDX, IDC_BUS_INFO_BTN, m_btnConsignInputInfo);
	
	
	DDX_Control(pDX, IDC_CANCEL_BTN, m_btnConsignCancle);


}


BEGIN_MESSAGE_MAP(CConsignLinkDlg, CMyDialog)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_CUSTOM1, OnNMReportItemCelChanged)
	//ON_NOTIFY(NM_CLICK, IDC_CUSTOM1, OnNMReportItemClick)
	ON_EN_CHANGE(IDC_COMMISSION_CHARGE_EDIT, &CConsignLinkDlg::OnEnChangeCommissionChargeEdit)
	ON_BN_CLICKED(IDC_CONSIGN_LINK_BTN, &CConsignLinkDlg::OnBnClickedConsignLinkBtn)
	ON_BN_CLICKED(IDC_CONSIGN_BTN, &CConsignLinkDlg::OnBnClickedConsignBtn)
	
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CConsignLinkDlg::OnBnClickedCancelBtn)	
	ON_BN_CLICKED(IDC_WAY_CHANGE_BTN, &CConsignLinkDlg::OnBnClickedWayChangeBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CConsignLinkDlg::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_BUS_INFO_BTN, &CConsignLinkDlg::OnBnClickedBusInfoBtn)
	ON_CBN_SELCHANGE(IDC_ELAPSED_COMBO, &CConsignLinkDlg::OnCbnSelchangeElapsedCombo)
	ON_BN_CLICKED(IDC_ORDER_REFRESH_BTN, &CConsignLinkDlg::OnBnClickedOrderRefreshBtn)
	ON_BN_CLICKED(IDC_CONSIGN_BUS_CLOSE_BTN, &CConsignLinkDlg::OnBnClickedConsignBusCloseBtn)
	
	
END_MESSAGE_MAP()


BOOL CConsignLinkDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	m_pPaintManager = new CConsignDrawManager2();

	m_List.SetPaintManager((CXTPGridPaintManager*)m_pPaintManager);
	int nCol = 0;
	m_List.InsertColumn(0, "적용", LVCFMT_LEFT, 60);
	m_List.InsertColumn(1, "차종", LVCFMT_LEFT, 90);
	m_List.InsertColumn(2, "출발정류장,역", LVCFMT_LEFT, 150);
	m_List.InsertColumn(3, "도착정류장,역", LVCFMT_LEFT, 150);
	m_List.InsertColumn(4, "금액", LVCFMT_LEFT, 80);
	m_List.InsertColumn(5, "첫차", LVCFMT_LEFT, 60);
	m_List.InsertColumn(6, "막착", LVCFMT_LEFT, 60);
	m_List.InsertColumn(7, "시간", LVCFMT_LEFT, 60);
	m_List.InsertColumn(8, "기타", LVCFMT_LEFT, 90);



	m_List.InsertColumn(9, "출점", LVCFMT_LEFT, 0);
	m_List.InsertColumn(10, "도점", LVCFMT_LEFT, 0);
	m_List.InsertColumn(11, "총점", LVCFMT_LEFT, 0);

	m_List.GetReportHeader()->AllowColumnSort(FALSE);
	m_List.Populate();


	m_edtTitleStartTerminal.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtTitleStartTerminal.SetUserOption(RGB(0, 0, 0),RGB(230,255,155), "출발지터미널" );
	m_edtTitleDestTerminal.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtTitleDestTerminal.SetUserOption(RGB(0, 0, 0),RGB(230,255,155), "도착지터미널" );


	m_edtTitleDestTerminalLink.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtTitleDestTerminalLink.SetUserOption(RGB(0, 0, 0),RGB(230,255,155), "출발지터미널" );
	m_edtTitleStartTerminalLink.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtTitleStartTerminalLink.SetUserOption(RGB(0, 0, 0),RGB(230,255,155), "도착지터미널" );

	m_edtTitleStart.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtTitleStart.SetUserOption(RGB(0, 0, 0),RGB(230,255,155), "출발지" );
	m_edtTitleDest.SetMyFont("맑은 고딕", 20, FW_BOLD);
	m_edtTitleDest.SetUserOption(RGB(0, 0, 0),RGB(230,255,155), "도착지" );


	COleDateTime dtCurrent(COleDateTime::GetCurrentTime());
	m_dtStart = dtCurrent;
	m_dtDest = dtCurrent;


	m_dtpStart.SetFormat("yyyy-MM-dd tth:mm:ss");
	m_dtpDest.SetFormat("yyyy-MM-dd tth:mm:ss");

	nCol = 0;
	m_CompanyOrderList.InsertColumn(nCol++, "오더번호",	DT_LEFT, 65);
	m_CompanyOrderList.InsertColumn(nCol++, "출발지",	DT_LEFT, 90);
	m_CompanyOrderList.InsertColumn(nCol++, "도착지",	DT_LEFT, 90);
	m_CompanyOrderList.InsertColumn(nCol++, "상태",		DT_LEFT, 40);
	m_CompanyOrderList.InsertColumn(nCol++, "접수",		DT_LEFT, 100);
	m_CompanyOrderList.InsertColumn(nCol++, "배차",		DT_LEFT, 50);
	m_CompanyOrderList.InsertColumn(nCol++, "픽업",		DT_LEFT, 50);
	m_CompanyOrderList.InsertColumn(nCol++, "종료",		DT_LEFT, 50);
	m_CompanyOrderList.InsertColumn(nCol++, "금액",		DT_RIGHT, 45);
	m_CompanyOrderList.InsertColumn(nCol++, "기사",		DT_LEFT, 45);
	m_CompanyOrderList.InsertColumn(nCol++, "접수자",	DT_LEFT, 60);
	m_CompanyOrderList.Populate();
	
	return 0;
}

// CConsignLinkDlg 메시지 처리기입니다.
void CConsignLinkDlg::NewRefreshOrder()
{
	CRect rectBody;
	GetWindowRect(rectBody);

	if(rectBody.Height() != TOP_WINDOW && m_nWindowType == ALL_WINDOW)
	{
		rectBody.bottom -= BOTTOM_WINDOW;
		m_nWindowType = TOP_WINDOW;
		//rectBody.bottom = rectBody.top + 400 ;
		MoveWindow(rectBody);
	}
	else if(rectBody.Height() != TOP_WINDOW && m_nWindowType == BOTTOM_WINDOW)
	{
		rectBody.top -= TOP_WINDOW;
		rectBody.bottom = rectBody.top +400;
		m_nWindowType = TOP_WINDOW;
		MoveWindow(rectBody);
	}

	long nDestCompanyCNo = 0, nDestCompanyCNoTelID = 0;
	nDestCompanyCNo = LU->GetConsignCustomerCNo(m_sDestSido);
	nDestCompanyCNoTelID = LU->GetConsignCustomerCNoTelID(m_sDestSido);
	if(nDestCompanyCNo <= 0)
	{
		MessageBox("탁송할 회사의 고객정보가 없습니다. 로지소프트로 문의하세요" , "확인", MB_ICONINFORMATION);

		return ;
	}

	m_btnConsignLink.SetWindowText("연 계 등 록");
	m_btnConsign.SetWindowText("탁송만 등록");
	m_btnConsignCancle.EnableWindow(FALSE);

	CBranchInfo *pConsignBi = LU->GetConsignMakeBranchInfo(m_sDestSido);
	m_pRcpDlgWndBack  = LU->GetRcpView()->CreateRcpDlg(pConsignBi, "탁송후오더", -1);
	if(m_pRcpDlgWndBack)
	{
		m_pRcpDlgWndBack->m_pOrder->SearchCustomerCNo(nDestCompanyCNo,TRUE, TRUE, nDestCompanyCNoTelID);
		
		m_pDestPlaceInfoTemp->Copy(m_pDestPlaceInfo);
		m_pRcpDlgWndBack->m_pDest->Copy(m_pDestPlaceInfo);
		m_pRcpDlgWndBack->ShowWindow(SW_HIDE);
		// 개발전m_pRcpDlgWndBack->ShowWindow(SW_SHOW);
		RefreshList();
	}
	m_bRcpDlgForgroudView = TRUE;
	
}

void CConsignLinkDlg::RcpViewShow()
{

	CRect rectBody, rConsignLinkBtn, rOrderList;
	GetWindowRect(rectBody);
	if(rectBody.Height() != ALL_WINDOW && m_nWindowType == TOP_WINDOW)
	{
		rectBody.bottom += BOTTOM_WINDOW;

		m_nWindowType = ALL_WINDOW;
		//rectBody.bottom = rectBody.top + 400 ;
		MoveWindow(rectBody);
	}

	long nDestCompanyCNo = 0, nDestCompanyCNoTelID = 0;
	nDestCompanyCNo = LU->GetConsignCustomerCNo(m_sDestSido);
	nDestCompanyCNoTelID = LU->GetConsignCustomerCNoTelID(m_sDestSido);
	if(nDestCompanyCNo <= 0)
	{
		MessageBox("탁송할 회사의 고객정보가 없습니다. 로지소프트로 문의하세요" , "확인", MB_ICONINFORMATION);
		return ;
	}

	if(m_pRcpDlgWndFront == NULL)
	{
		CBranchInfo *pConsignFrontBi = LF->GetBranchInfo(m_nCompany);
		m_pRcpDlgWndFront  = LU->GetRcpView()->CreateRcpDlg(pConsignFrontBi, "", m_nOrderTNo,FALSE, "", FALSE, -1, 0, 0, 0,"",0,0,TRUE);
		m_pRcpDlgWndFront->ShowWindow(SW_HIDE);
	}
	m_btnConsignLink.SetWindowText("연 계 수 정");
	m_btnConsign.SetWindowText("탁송으로 수 정");

	m_btnConsign.EnableWindow(FALSE);
	m_btnConsignLink.EnableWindow(FALSE);
	m_btnConsignCancle.EnableWindow(FALSE);

	if(m_pRcpDlgWndFront)
	{
		m_edtStartCharge.SetWindowText(LF->GetMyNumberFormatEdit(m_pRcpDlgWndFront->m_EDT_CHARGE_SUM.pEdit));
		m_edtTransCharge.SetWindowText(LF->GetMyNumberFormatEdit(m_pRcpDlgWndFront->m_EDT_CHARGE_TRANS.pEdit));
		m_edtDestCharge.SetWindowText(LF->GetMyNumberFormatEdit(&m_pRcpDlgWndFront->m_edtConBackOrderCharge));
		m_edtCommissionCharge.SetWindowText(LF->GetMyNumberFormatEdit(&m_pRcpDlgWndFront->m_edtConCommissionCharge));
	}
	RefreshCharge();

	CBranchInfo *pConsignBi = LU->GetConsignMakeBranchInfo("부산");
	m_pRcpDlgWndBack  = LU->GetRcpView()->CreateRcpDlg(pConsignBi, "탁송후오더", m_nConsignTNo,FALSE, "", FALSE, -1, 0, 0, 0,"",0,0,TRUE);

	if(m_pRcpDlgWndBack)
	{	
		m_pStartPlaceInfo = m_pRcpDlgWndFront->m_pDest;
		m_pDestPlaceInfo = m_pRcpDlgWndBack->m_pStart;

		m_pDestPlaceInfoTemp->Copy(m_pRcpDlgWndBack->m_pDest);
		
		RefreshList();
		m_pRcpDlgWndBack->ShowWindow(SW_HIDE); // 개발후
	}
	RefreshBusInfo();
	RefreshDestOrder();
	m_bRcpDlgForgroudView = TRUE;
	BusNameEditFocus();

}
void CConsignLinkDlg::EditRefreshOrder()
{

	CRect rectBody, rOrderList;
	GetWindowRect(rectBody);

	if(rectBody.Height() != ALL_WINDOW && m_nWindowType == TOP_WINDOW)
	{
		rectBody.bottom += BOTTOM_WINDOW;

		m_nWindowType = ALL_WINDOW;
		//rectBody.bottom = rectBody.top + 400 ;
		MoveWindow(rectBody);
	}
	else if(rectBody.Height() != ALL_WINDOW && m_nWindowType == BOTTOM_WINDOW)
	{
		rectBody.top -= TOP_WINDOW;
		//rectBody.bottom = rectBody.top + BOTTOM_WINDOW;
		m_nWindowType = ALL_WINDOW;
		MoveWindow(rectBody);
	}

	/*m_CompanyOrderList.GetWindowRect(rOrderList);
	ScreenToClient(rOrderList);
	if(rectBody.Height() <= 400)
	{
		rectBody.bottom = rectBody.top + rOrderList.bottom + 50;
		
		MoveWindow(rectBody);
	}*/

	long nDestCompanyCNo = 0, nDestCompanyCNoTelID = 0;
	nDestCompanyCNo = LU->GetConsignCustomerCNo(m_sDestSido);
	nDestCompanyCNoTelID = LU->GetConsignCustomerCNoTelID(m_sDestSido);
	if(nDestCompanyCNo <= 0)
	{
		MessageBox("탁송할 회사의 고객정보가 없습니다. 로지소프트로 문의하세요" , "확인", MB_ICONINFORMATION);

		return ;
	}

	m_btnConsignLink.SetWindowText("연 계 수 정");
	m_btnConsign.SetWindowText("탁송으로 수 정");

	if(m_pRcpDlgWndFront)
	{
		m_edtStartCharge.SetWindowText(LF->GetMyNumberFormatEdit(m_pRcpDlgWndFront->m_EDT_CHARGE_SUM.pEdit));
		m_edtTransCharge.SetWindowText(LF->GetMyNumberFormatEdit(m_pRcpDlgWndFront->m_EDT_CHARGE_TRANS.pEdit));
		m_edtDestCharge.SetWindowText(LF->GetMyNumberFormatEdit(&m_pRcpDlgWndFront->m_edtConBackOrderCharge));
		m_edtCommissionCharge.SetWindowText(LF->GetMyNumberFormatEdit(&m_pRcpDlgWndFront->m_edtConCommissionCharge));
	}
	RefreshCharge();

	CBranchInfo *pConsignBi = LU->GetConsignMakeBranchInfo("부산");
	m_pRcpDlgWndBack  = LU->GetRcpView()->CreateRcpDlg(pConsignBi, "탁송후오더", m_nConsignTNo,FALSE, "", FALSE, -1, 0, 0, 0,"",0,0,TRUE);
		  
	if(m_pRcpDlgWndBack)
	{		
		m_pDestPlaceInfoTemp->Copy(m_pRcpDlgWndBack->m_pDest);
		RefreshList();
		m_pRcpDlgWndBack->ShowWindow(SW_HIDE);
		// 개발후
	}
	
	RefreshBusInfo();
	RefreshDestOrder();
	BusNameEditFocus();
m_bRcpDlgForgroudView = TRUE;
}

void CConsignLinkDlg::RefreshBusInfo()
{
	if(m_nOrderTNo > 0 )
	{
		UpdateData();
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "select_traninfo2011");															  
		pCmd.AddParameter(m_nCompany);
		pCmd.AddParameter(m_nOrderTNo);
		if(!pRs.Execute(&pCmd)) return;			

		for(int i = 0; i < pRs.GetRecordCount(); i++)	
		{	
			long nTNo, nCompany, nConsignType,  nDestCompanyTNo;
			CString sExpressName, sExpressNumber, sEtc, sItemNo, sName;
			COleDateTime dtDeparture, dtArrival;
			
			pRs.GetFieldValue("nTNo", nTNo);
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("sExpressName", sExpressName);
			pRs.GetFieldValue("sExpressNumber", sExpressNumber);
			pRs.GetFieldValue("dtDeparture", dtDeparture);
			pRs.GetFieldValue("dtArrival", dtArrival);
			pRs.GetFieldValue("sEtc", sEtc);

			pRs.GetFieldValue("sName", sName);
			pRs.GetFieldValue("sItemNo", sItemNo);
			pRs.GetFieldValue("nConsignType", nConsignType);
			pRs.GetFieldValue("nDestCompanyTNo", nDestCompanyTNo);

			m_edtBusName.SetWindowText(sExpressName);
			m_edtBusNo.SetWindowText(sExpressNumber);
			m_edtInvoiceNo.SetWindowText(sItemNo);
			m_edtEtc.SetWindowText(sEtc);
			m_dtStart = dtDeparture;
			m_dtDest = dtArrival;		


		}
		pRs.Close();
		UpdateData(FALSE);
	}
}


void CConsignLinkDlg::OnBnClickedBusInfoBtn()
{

	if(m_nOrderTNo > 0 )
	{
		try
		{
			UpdateData();

			if(m_dtStart == m_dtDest)
				throw "출발시간과 도착시간이 같습니다.";

			if(m_dtStart > m_dtDest)
				throw "출발시간이 도착시간에 비해 더큽니다.";

			if(LF->GetEditString(&m_edtBusName).GetLength() <= 0 )
				throw "버스명이나  KTX 번호를 입력하세요";

			if(LF->GetEditString(&m_edtInvoiceNo).GetLength() <= 0 )
				throw "송장번호를 입력하세요";


			if( MessageBox("탁송정보의 시간에 따라 상대방 오더가 공유됩니다.  정확히 입력하셨습니까 ? " ,
				"확인", MB_YESNO) == IDNO)
				return;


			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "insert_traninfo_wname");															  
			pCmd.AddParameter(m_nCompany);
			pCmd.AddParameter(m_nOrderTNo);
			pCmd.AddParameter(m_nConsignTNo);
			pCmd.AddParameter(LF->GetEditString(&m_edtTitleStartTerminal));
			pCmd.AddParameter(LF->GetEditString(&m_edtTitleDestTerminal));
			pCmd.AddParameter(LF->GetEditString(&m_edtBusName));
			pCmd.AddParameter(LF->GetEditString(&m_edtBusNo));
			pCmd.AddParameter(LF->GetEditString(&m_edtInvoiceNo));
			pCmd.AddParameter(m_dtStart);
			pCmd.AddParameter(m_dtDest);
			pCmd.AddParameter(LF->GetEditString(&m_edtEtc));
			pCmd.AddParameter(m_ui.strName);
			pCmd.AddParameter(m_ui.nWNo);
			CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
			if(!pRs.Execute(&pCmd)) return;	
			long nRealTNo = 0;
			pPar->GetValue(nRealTNo);
			if(nRealTNo > 0)
			{
				RefreshDestOrder(nRealTNo);
				MessageBox("탁송정보가 입력되었으며 탁송을 받는회사에 오더가 등록되었습니다.", "확인", MB_ICONINFORMATION);
			}
			else
				MessageBox("탁송정보를 입력하였습니다.", "확인", MB_ICONINFORMATION);
		}
		catch (CString s)
		{
			MessageBox(s, "확인", MB_ICONINFORMATION);
		}
		catch (char* e)
		{
			MessageBox(e, "확인", MB_ICONINFORMATION);
		}
	

	
	}


}

	
void CConsignLinkDlg::RefreshDestOrder(long nRealConsignTNo)
{
	if(nRealConsignTNo <= 0 && m_nConsignTNo <= 0)
		return;

	if(nRealConsignTNo > 0)		
		m_nConsignTNo = nRealConsignTNo;

	if(m_nConsignTNo < 55000000)
		return;
		
	if(m_CompanyOrderList.GetRecords()->GetCount() > 0)
		m_CompanyOrderList.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_consign_condition_list2011");		
	pCmd.AddParameter(m_nConsignTNo);		
	//pCmd.AddParameter(m_nDestCompany);
	if(!pRs.Execute(&pCmd)) return;					

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		CString sItemNo = "", sEtc = "", sCarBusName = "",sCarNo = "",
			sWName = "", sRName = "",sDestWName = "", sSName = "", sDName ="",
			sDAddress = "", sStartTerminalTel = "", sDestTerminalTel = "";
		COleDateTime dtRegister, dtStartTerminal, dtDestTerminal, dt1, dt3, dt4,dtFinal;
		long  nChargeSum,nState, nRNo ; // nDestConsignCompany

		pRs.GetFieldValue("sSName"	,sSName);
		pRs.GetFieldValue("sDName"	,sDName);
		pRs.GetFieldValue("dt1"	,dt1 );
		pRs.GetFieldValue("dt3"	,dt3);
		pRs.GetFieldValue("dt4"	,dt4);
		pRs.GetFieldValue("dtFinal"	,dtFinal);
		pRs.GetFieldValue("nState"	,nState);
		pRs.GetFieldValue("nChargeSum"	,nChargeSum);
		pRs.GetFieldValue("sRName"	,sRName);
		pRs.GetFieldValue("nRNo"	,nRNo);
		pRs.GetFieldValue("sDestWName"	,sDestWName);

		m_CompanyOrderList.InsertItem(i, LF->GetStringFromLong(m_nConsignTNo));
		m_CompanyOrderList.SetItemText(i, 1, sSName);
		m_CompanyOrderList.SetItemText(i, 2, sDName);
		m_CompanyOrderList.SetItemText(i, 3, LF->GetStateString(nState));
		m_CompanyOrderList.SetItemText(i, 4, dt1.Format("%Y-%m-%d %H:%M"));
		m_CompanyOrderList.SetItemText(i, 5, nState >= 30 ? dt3.Format("%H:%M") : "");
		m_CompanyOrderList.SetItemText(i, 6, nState >= 30 ? dt4.Format("%H:%M") : "");
		m_CompanyOrderList.SetItemText(i, 7, nState >= 35 ? dtFinal.Format("%H:%M") : "");
		m_CompanyOrderList.SetItemText(i, 8, LF->GetMyNumberFormat(nChargeSum));
		m_CompanyOrderList.SetItemText(i, 9, nRNo);
		m_CompanyOrderList.SetItemText(i, 10, sWName);
		m_CompanyOrderList.Populate();

		pRs.Close();

	}


}

void CConsignLinkDlg::OnBnClickedOrderRefreshBtn()
{
	RefreshDestOrder();
}


void CConsignLinkDlg::InitControl()
{

	// 창닫을때도 초기화합니다.

	UpdateData();
	DelList();
	m_pStartPlaceInfo = NULL;
	m_pDestPlaceInfo = NULL;
	
	m_nCompany = 0;
	m_sDestSido = "";
	m_pRcpDlgWndFront = NULL;

	m_nConsignTNo = 0;
	m_nOrderTNo = 0;
	m_nConCommissionCharge = 0;

	m_sStartCharge = "0";
	m_sDestCharge = "0";
	m_sTransCharge= "0";
	m_sTempCharge= "0";
	m_sCommissionCharge= "0";
	m_sTotalCharge= "0";

	COleDateTime dtCurrent(COleDateTime::GetCurrentTime());
	m_dtStart = dtCurrent;
	m_dtDest = dtCurrent;
	m_bRcpDlgForgroudView = FALSE;
	m_btnConsignLink.SetWindowText("연계등록");
	m_btnConsign.SetWindowText("탁송등록");

	m_edtBusNo.SetWindowText("");
	m_edtBusName.SetWindowText("");
	m_edtEtc.SetWindowText("");
	m_edtInvoiceNo.SetWindowText("");
	m_cmbElapsed.SetCurSel(-1);


	m_btnConsign.EnableWindow(TRUE);
	m_btnConsignLink.EnableWindow(TRUE);
	m_btnConsignCancle.EnableWindow(TRUE);
	CRect r;
	GetWindowRect(r);
	r.bottom  = r.top + ALL_WINDOW;
	m_nWindowType = ALL_WINDOW;
	MoveWindow(r);
	

	UpdateData(FALSE);
}

void CConsignLinkDlg::DelList()
{
	if(m_List.GetRecords()->GetCount() > 0)
	{
		for(int i = 0; i < m_List.GetRecords()->GetCount(); i++)
		{
			CXTPGridRecord* pRecord = m_List.GetRecords()->GetAt(i);
			ST_CONSIGN *pListInfo =(ST_CONSIGN *) m_List.GetItemData(pRecord);
			if(pListInfo)
			{
				delete pListInfo;
				pListInfo = NULL;
			}
			//pRecord->Delete();
		}

	}
	m_List.DeleteAllItems();
}

void CConsignLinkDlg::RefreshList()
{
	if(m_List.GetRecords()->GetCount() > 0)
		DelList();

	if(m_pStartPlaceInfo== NULL || m_pDestPlaceInfo ==  NULL)
		return;

	int nRowNum= 0; BOOL bCheck = FALSE, bBus = FALSE, bKTX = FALSE;
	int nModifySelectRow = 0 , nPreWayType = 0;
	long nStartPosX = 0, nStartPosY = 0, nDestPosX = 0, nDestPosY = 0;
	nStartPosX = m_pStartPlaceInfo->GetPOI()->m_nPosX;
	nStartPosY = m_pStartPlaceInfo->GetPOI()->m_nPosY;
	nDestPosX = m_pDestPlaceInfoTemp->GetPOI()->m_nPosX;
	nDestPosY = m_pDestPlaceInfoTemp->GetPOI()->m_nPosY;

	nStartPosX = nStartPosX / 0.36;
	nStartPosY = nStartPosY / 0.36;
	nDestPosX = nDestPosX / 0.36;
	nDestPosY = nDestPosY / 0.36;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_consign_near_terminal2011");															  
	pCmd.AddParameter(nStartPosX);
	pCmd.AddParameter(nStartPosY);
	pCmd.AddParameter(m_pStartPlaceInfo->GetPOI()->GetDongID());
	pCmd.AddParameter(m_pStartPlaceInfo->GetPOI()->GetSido());
	pCmd.AddParameter(nDestPosX);
	pCmd.AddParameter(nDestPosY);
	pCmd.AddParameter(m_pDestPlaceInfoTemp->GetPOI()->GetDongID());
	pCmd.AddParameter(m_pDestPlaceInfoTemp->GetPOI()->GetSido());	
	pCmd.AddParameter(FALSE);	
	pCmd.AddParameter(m_nOrderTNo);
	//pCmd.AddParameter(m_nTerminalWayID);

	if(!pRs.Execute(&pCmd)) return;	

	m_vecCashCharge.clear();	

	for(int i = 0; i < pRs.GetRecordCount(); i++)	
	{	
		ST_CASH_CHARGE cashCharge;
		cashCharge.bLoad = FALSE; cashCharge.nDestCharge = 0; cashCharge.nStartCharge = 0; 
		cashCharge.nTerminalCharge = 0; cashCharge.nTotalCharge = 0; cashCharge.nTempCharge = 0;
		m_vecCashCharge.push_back(cashCharge);

		CString strStartTime, strStartTerminalName, strWayType;
		CString strDestTime, strListInterval, strInterval, strEtc, strDestTerminalName;
		long nStartTerminalID, nStartPosX, nStartPosY, nStartNearKm, nCharge, nStartTerminalPoi;
		long nKm,nElapsedTime,nDestTerminalID, nDestPosX,nDestPosY, nDestNearKm, nDestTerminalPoi;
		long nStartJumsu,nDestJumsu, nCID= 0;
		int nWayType = -1, nTotalRank, nCol = 0;
		CString strStartNearKm, strDestNearKm,sTotalKm, strStartTerminalTel, strDestTerminalTel;	

		pRs.GetFieldValue("nCID", nCID);
		pRs.GetFieldValue("nStartTerminalID", nStartTerminalID);
		pRs.GetFieldValue("sStartTerminalName", strStartTerminalName);
		pRs.GetFieldValue("nStartPosX", nStartPosX);
		pRs.GetFieldValue("nStartPosY", nStartPosY);
		pRs.GetFieldValue("nStartNearKm", nStartNearKm);
		pRs.GetFieldValue("nStartTerminalPoi", nStartTerminalPoi);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("sStartTime", strStartTime);
		pRs.GetFieldValue("sDestTime", strDestTime);
		pRs.GetFieldValue("sListInterval", strListInterval);
		pRs.GetFieldValue("sInterval", strInterval);
		pRs.GetFieldValue("sEtc", strEtc);
		pRs.GetFieldValue("nKm", nKm);
		pRs.GetFieldValue("nElapsedTime", nElapsedTime);
		pRs.GetFieldValue("nDestTerminalID", nDestTerminalID);
		pRs.GetFieldValue("sDestTerminalName", strDestTerminalName);
		pRs.GetFieldValue("nDestPosX", nDestPosX);
		pRs.GetFieldValue("nDestPosY", nDestPosY);
		pRs.GetFieldValue("nDestNearKm", nDestNearKm);		
		pRs.GetFieldValue("nDestTerminalPoi", nDestTerminalPoi);		

		pRs.GetFieldValue("nWayType", nWayType);		
		pRs.GetFieldValue("nTotalRank", nTotalRank);		
		pRs.GetFieldValue("sStartTerminalTel", strStartTerminalTel);		
		pRs.GetFieldValue("sDestTerminalTel", strDestTerminalTel);	

		pRs.GetFieldValue("nStartJumsu", nStartJumsu);		
		pRs.GetFieldValue("nDestJumsu", nDestJumsu);	

	/*	if(bBus)
			continue;

		if(bKTX)
			continue;*/

		if(nWayType == 0)
			strWayType ="버스";
		else
			strWayType ="KTX";

		if(nTotalRank >= 90 && nWayType == 0)
			bBus = TRUE;

		if(nTotalRank >= 90 && nWayType == 1)
			bKTX = TRUE;

		ST_CONSIGN *pListInfo = new ST_CONSIGN;
		pListInfo->nStartTerminalID = nStartTerminalID;
		pListInfo->strStartTerminalName = strStartTerminalName;
		pListInfo->nStartPosX = nStartPosX;
		pListInfo->nDestPosY = nDestPosY;
		pListInfo->nStartNearKm;
		pListInfo->nStartTerminalPoi = nStartTerminalPoi;
		pListInfo->nTerminalCharge = nCharge;
		pListInfo->nKm = nKm;
		pListInfo->nElapsedTime = nElapsedTime;
		pListInfo->nDestTerminalID = nDestTerminalID;
		pListInfo->strDestTerminalName = strDestTerminalName;
		pListInfo->nDestPosX = nDestPosX;
		pListInfo->nDestPosY = nDestPosY;
		pListInfo->nDestNearKm = nDestNearKm;
		pListInfo->nDestTerminalPoi = nDestTerminalPoi;
		pListInfo->nWayType = nWayType;
		pListInfo->strWayType = strWayType;
		pListInfo->strStartTerminalTel = strStartTerminalTel;
		pListInfo->strDestTerminalTel = strDestTerminalTel;
		pListInfo->nCID = nCID;
	
		strStartNearKm.Format("%dKm", nStartNearKm);
		strDestNearKm.Format("%dKm", nDestNearKm);
		sTotalKm.Format("%dKm", nKm);

		if(m_nConsignTNo > 0 && m_nTerminalWayID > 0)
		{
			if(m_nTerminalWayID == pListInfo->nCID )
			{
				bCheck = TRUE;
				nModifySelectRow = nRowNum;				
			}
			else
			{
				bCheck = FALSE;
			}
		}		
		
		m_List.InsertItem(i, bCheck ? "연계중" : "");
		m_List.SetItemText(i, 1, strWayType);
		m_List.SetItemText(i, 2, strStartTerminalName);
		m_List.SetItemText(i, 3, strDestTerminalName);
		m_List.SetItemText(i, 4, LF->GetMyNumberFormat(nCharge));
		m_List.SetItemText(i, 5, strStartTime);
		m_List.SetItemText(i, 6, strDestTime);
		m_List.SetItemText(i, 7, GetViewTime(nElapsedTime));
		m_List.SetItemText(i, 8, LF->GetMyNumberFormat(nStartJumsu));
		m_List.SetItemText(i, 9, LF->GetMyNumberFormat(nDestJumsu));
		m_List.SetItemText(i, 10, LF->GetMyNumberFormat(nTotalRank));

		m_List.SetItemLong(i, bCheck);
		m_List.SetItemLong2(i, nDestTerminalPoi);
		m_List.SetItemLong3(i, nCID);
		m_List.SetItemData(i, (DWORD_PTR)pListInfo);

		nRowNum++;
		nPreWayType = nWayType;
		bCheck = FALSE;
		pRs.MoveNext();
	}

	pRs.Close();
	m_List.Populate();

	if(m_nOrderTNo <= 0) // 신규일때
	{
		if(nModifySelectRow <= 0)
			m_List.SetSelectedRow(0);
		
		ConsignListSelect(TRUE, 0);
	}
	else // 수정일때
	{
		for(int i = 0; i < m_List.GetRows()->GetCount(); i++)
			m_List.GetRows()->GetAt(i)->SetSelected(i == nModifySelectRow ? TRUE : FALSE);
				
		ConsignListSelect(TRUE, nModifySelectRow);
	}
	
	if(m_nOrderTNo > 0)
	{
		CString sCommission = ""; m_edtCommissionCharge.GetWindowText(sCommission);
		m_edtCommissionCharge.SetSel(0xFFFF);
	}
}

void CConsignLinkDlg::AddNewConsignLink( )
{
	long nTNo = 0;
	CString sBackOrderPhone = "";


	sBackOrderPhone = m_pRcpDlgWndBack->m_pOrder->GetPhone();
	if(sBackOrderPhone.GetLength() <= 6)
	{
		MessageBox("탁송후 상대방 오더의 전화번호를 입력하세요", "확인",MB_ICONINFORMATION);
		return;
	}
	
	m_pRcpDlgWndFront->SetConsignMode(TRUE);
	m_pRcpDlgWndFront->RefreshConsignCharge();

	if(m_List.GetSelectedRows()->GetCount() <= 0  )
	{
		MessageBox("노선을 선택하여주세요", "확인", MB_ICONINFORMATION);
		return;
	}
	CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();
	ST_CONSIGN *pListInfo = (ST_CONSIGN*)m_List.GetItemData(pRecord);
	m_pRcpDlgWndFront->m_nTerminalWayID = pListInfo->nCID;
	
	if(m_nOrderTNo > 0	)
	{
		m_pRcpDlgWndFront->EditOrder();
		nTNo = m_nOrderTNo;
	}
	else
		nTNo = m_pRcpDlgWndFront->AddNewOrder(TRUE);
	//아래 nTNo 값을 받아오는건  뒤오더의 연계오더를 표시하기위하여
	m_pRcpDlgWndFront->m_nConsignTNo = nTNo;
	
		
	// 뒤오더등록
	if(nTNo > 0)
	{
		//nTNo = m_pRcpDlgWndBack->AddNewOrder(TRUE); 아래에 nTNo를 붙여주면 DorderTodayConsign 으로 들어간다
		nTNo = m_pRcpDlgWndBack->AddNewOrder(TRUE,TRUE,FALSE, nTNo);

		if(nTNo > 0)
		{
			
			InitControl();
			OnOK();			
			m_pRcpDlgWndBack->m_EDT_ETC.pEdit->SetFocus();
			
		}
	}

}
void CConsignLinkDlg::EditConsignLink()
{
	long nTNo = 0;
	CString sBackOrderPhone = "";

	sBackOrderPhone = m_pRcpDlgWndBack->m_pOrder->GetPhone();
	if(sBackOrderPhone.GetLength() <= 6)
	{
		MessageBox("탁송후 상대방 오더의 전화번호를 입력하세요", "확인",MB_ICONINFORMATION);
		return;
	}

	for(int i = 0; i < m_List.GetRecords()->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = m_List.GetFirstSelectedRecord();
		ST_CONSIGN *pListInfo = (ST_CONSIGN *)m_List.GetItemData(pRecord);
		if(pListInfo->nCID)
		{
			m_pRcpDlgWndFront->m_nTerminalWayID = pListInfo->nCID;
			break;
		}
	}

	m_pRcpDlgWndFront->SetConsignMode(TRUE);
	m_pRcpDlgWndFront->EditOrder();
	
	// 뒤오더수정
	m_pRcpDlgWndBack->EditOrder();
	InitControl();
	OnOK();			
}


void CConsignLinkDlg::AddNewConsign( )
{
	m_pRcpDlgWndFront->SetConsignMode(FALSE);
	
	if(m_nOrderTNo > 0	)
		m_pRcpDlgWndFront->EditOrder();	
	else
		m_pRcpDlgWndFront->AddNewOrder(TRUE);

	if(m_pRcpDlgWndBack)
		m_pRcpDlgWndBack->OnBnClickedCloseBtn();
	InitControl();
	OnOK();		
}


void CConsignLinkDlg::OnBnClickedWayChangeBtn()
{
	if(m_List.GetSelectedRows()->GetCount() <= 0)
		return;

	if(m_List.GetRecords()->GetCount() <= 0)
		return;

	CXTPGridRecord *pSeletedRecord = m_List.GetFirstSelectedRecord();
	CXTPGridRecord *pRecord;
	long nSelect = FALSE;
	for(int i = 0; i < m_List.GetRecords()->GetCount(); i++)
	{
		pRecord = m_List.GetRecords()->GetAt(i);
		nSelect = m_List.GetItemLong(pRecord);
		if(pRecord == pSeletedRecord && nSelect == TRUE)
		{
			MessageBox("적용된 노선과 같습니다.", "확인", MB_ICONINFORMATION);
			return;
		}
	}
	ST_CONSIGN *pListInfo = (ST_CONSIGN*)m_List.GetItemData(pSeletedRecord);
	m_nTerminalWayID = pListInfo->nCID;
	m_List.SetItemLong(pSeletedRecord, TRUE);
	for(int i = 0; i < m_List.GetRecords()->GetCount(); i++)
	{
		((CXTPGridRecordItemText*)m_List.GetRecords()->GetAt(i)->GetItem(0))->SetCaption(" ");
		m_List.SetItemLong(i, FALSE);
	}

	((CXTPGridRecordItemText*)pSeletedRecord->GetItem(0))->SetCaption("연계중");

	ConsignListSelect(TRUE, FALSE);
	m_List.Populate();
}

void CConsignLinkDlg::ConsingLinkOrderCancel()
{
	if(m_nOrderTNo > 0 && m_nConsignTNo > 0)  // 연계오더
	{	
		long nDeleteReturn = 0;
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "delete_consign_link_order");															  
		pCmd.AddParameter(m_nConsignTNo);
		pCmd.AddParameter(m_nOrderTNo);		
		pCmd.AddParameter(m_ui.nWNo);		
		pCmd.AddParameter(m_ui.nCompany);		
		pCmd.AddParameter(m_ui.strName);		
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);		
		if(!pRs.Execute(&pCmd)) return;	
		pPar->GetValue(nDeleteReturn);

		if(nDeleteReturn == 1)
		{
			MessageBox("연계중인 오더를 취소하였습니다.","확인", MB_ICONINFORMATION);
			m_pRcpDlgWndFront->m_nConsignTNo = 0;
			m_pRcpDlgWndFront->m_nTerminalWayID = 0;
			m_pRcpDlgWndFront->SetConsignInit();
			m_pRcpDlgWndFront->SetConsignMode(FALSE);
		}
		else if (nDeleteReturn == 200)
		{
			MessageBox("오더가 상대방 퀵회사에 등록이 되어있습니다. 상대방 회사에 연계중인 오더를 취소요청하시고 연계취소하세요","확인", MB_ICONINFORMATION);
			return;
		}
		if(nDeleteReturn == 300)
			MessageBox("연계중인 오더를 취소되지 못하였습니다.","확인", MB_ICONINFORMATION);	
	}
}

void CConsignLinkDlg::OnBnClickedConsignBtn()
{	
	if(m_nConsignTNo > 0)
		EditConsign();	//탁송으로 수정
	else
		AddNewConsign(); //탁송만
}

void CConsignLinkDlg::OnBnClickedConsignLinkBtn()
{	
	if(m_nConsignTNo > 0)	
		EditConsignLink();	
	else
	{
		if(MessageBox("연계등록을 하시겠습니까? " , "확인", MB_YESNO) == IDNO)
			return;
		AddNewConsignLink(); //연계
		}
}

void CConsignLinkDlg::OnBnClickedCancelBtn()
{

	if(MessageBox("연계 오더를 취소하시겠습니까? ", "확인", MB_YESNO ) == IDNO)
		return;

	if(m_nOrderTNo > 0 && m_nConsignTNo > 0)  
	{
		ConsingLinkOrderCancel();
		FrontOrderEtcMake(TRUE);
		m_pDestPlaceInfo->Exchange(m_pDestPlaceInfoTemp);
	}
	m_pRcpDlgWndFront->SetConsignMode(FALSE);
	m_pRcpDlgWndFront->SetConsignInit();
	
	if(m_pRcpDlgWndBack)
		m_pRcpDlgWndBack->OnBnClickedCloseBtn();

	InitControl();

	
	OnOK();


}
void CConsignLinkDlg::EditConsign()
{
	
	if(MessageBox("연계오더를 취소하고 탁송만 보내시겠습니까? ", "확인", MB_YESNO ) == IDNO)
		return;

	
	if(m_nOrderTNo > 0 && m_nConsignTNo > 0)  
	{
		ConsingLinkOrderCancel(); // 연계된오더 있으면 삭제
		if(m_pRcpDlgWndBack)
		{
			m_pRcpDlgWndBack->OnBnClickedCloseBtn();
		}
	}
	m_pRcpDlgWndFront->SetConsignMode(FALSE);
	m_pRcpDlgWndFront->EditOrder();


	if(m_pRcpDlgWndBack)
		m_pRcpDlgWndBack->OnBnClickedCloseBtn();

	InitControl();
	OnOK();			


}

void CConsignLinkDlg::FrontOrderEtcMake(BOOL bDelete)
{

	CString sRcpEtc = "", sCompany = "", sDept = "", sName = "", sTel1 = "" , sTel2 = "", sAddress = "",
		sDong = "", sPreRcpEtc = "", sReplaceWord = "", sAddressDetail = "";

	if(!bDelete && m_pDestPlaceInfoTemp )
	{
		sCompany = m_pDestPlaceInfoTemp->GetCompany();
		sDept = m_pDestPlaceInfoTemp->GetDepart();
		sName = m_pDestPlaceInfoTemp->GetManager();
		sTel1 = m_pDestPlaceInfoTemp->GetMP();
		sTel2 = m_pDestPlaceInfoTemp->GetPhone();
		sAddress = m_pDestPlaceInfoTemp->GetAddress();
		sAddressDetail = m_pDestPlaceInfoTemp->GetDetail();

		sRcpEtc = "탁송정보";
		if(sCompany.GetLength() > 0) sRcpEtc += "●회사:" + sCompany  +", ";
		if(sDept.GetLength() > 0)	sRcpEtc += "●부서:"+ sDept + ", " ;
		if(sName.GetLength() > 0 ) sRcpEtc += "●담당:" + sName + ", ";
		if(sTel1.GetLength() > 0 ) sRcpEtc += "●전화1:" + sTel1 + ", ";
		if(sTel2.GetLength() > 0 ) sRcpEtc += "●전화2:" + sTel2 + ", ";
		if(sAddress.GetLength() > 0 ) sRcpEtc += "●주소:" + sAddress; 
		if(sAddressDetail.GetLength() > 0 ) sRcpEtc += " " + sAddressDetail;
		if(sRcpEtc.GetLength() > 0 ) sRcpEtc = sRcpEtc.Mid(0, sRcpEtc.GetLength());		
		sRcpEtc.Replace("[", ""); sRcpEtc.Replace("]", "");
		sRcpEtc = "[" + sRcpEtc + "]";
	}	
	
	m_pRcpDlgWndFront->m_EDT_ETC.pEdit->GetWindowText(sPreRcpEtc);
	if( sPreRcpEtc.Find("[탁송정보") >= 0 )
	{
		int nStartPosition = 0, nEndPosition = 0;
		nStartPosition =  sPreRcpEtc.Find("[탁송정보") ;
		nEndPosition = sPreRcpEtc.Find("]");
		if(nStartPosition < nEndPosition)
		{
			sReplaceWord = sPreRcpEtc.Mid(nStartPosition, nEndPosition - nStartPosition + 1);
			if(bDelete)
				sPreRcpEtc.Replace(sReplaceWord, "");
			else
				sPreRcpEtc.Replace(sReplaceWord, sRcpEtc);

			sRcpEtc = sPreRcpEtc;
		}		
	}
	else
		sRcpEtc += sPreRcpEtc;
	
	m_pRcpDlgWndFront->m_EDT_ETC.pEdit->SetWindowText(sRcpEtc);
	
}

void CConsignLinkDlg::MakePlaceInfo2(CRcpDlg *pRcpDlg, BOOL bStart)
{
	CXTPGridRecord * pRecord = NULL;
	pRecord = m_List.GetFirstSelectedRecord();
	if(pRecord == NULL)
		return;

	ST_CONSIGN *pListInfo = (ST_CONSIGN *)m_List.GetItemData(pRecord);
	long nDongID = 0 , nPosX = 0, nPosY = 0; CString strTerminal = "";
	CPOIUnit *pPoi;

	nDongID = bStart ?		pListInfo->nStartTerminalPoi : pListInfo->nDestTerminalPoi;
	strTerminal =  bStart ? pListInfo->strStartTerminalName : pListInfo->strDestTerminalName;
	pPoi = m_poiNew.GetDongPOIFromCache(nDongID);

	if(bStart)
	{
		if(pRcpDlg)
		{
			pRcpDlg->m_pDest->Clear();
			pRcpDlg->m_pDest->SetData(
				nDongID, pPoi->GetPosX(), pPoi->GetPosY(), "","","", "",
				0, 0, "", 0, "", "", pPoi->GetDong(),
				strTerminal, FALSE, "", 0, FALSE, 0, 0, 0 , FALSE);
			pRcpDlg->m_pDest->SetCompany(strTerminal);
			pRcpDlg->m_pDest->SetDisplayDong(pPoi->GetDong());
			pRcpDlg->m_EDT_CHARGE_TRANS.pEdit->SetWindowText(LF->GetMyNumberFormat(pListInfo->nTerminalCharge ));
			pRcpDlg->m_edtConCommissionCharge.SetWindowText(LF->GetMyNumberFormatEdit(&m_edtCommissionCharge));
			pRcpDlg->SetConsignMode(TRUE);
		}
	

		//pRcpDlg->m_pDest->SetCNo()
	}
	else
	{
		if(pRcpDlg)
		{
			pRcpDlg->m_pStart->SetData(
				nDongID, pPoi->GetPosX(), pPoi->GetPosY(), "","","", "",
				0, 0, "", 0, "", "", pPoi->GetDong(),
				strTerminal, FALSE, "", 0, FALSE, 0, 0, 0 , FALSE);
			pRcpDlg->m_pStart->SetCompany(strTerminal);
			pRcpDlg->m_pStart->SetDisplayDong(pPoi->GetDong());
		}
	
	}
}

void CConsignLinkDlg::ConsignListSelect(BOOL bListSelect,  int nModifySelectRow)
{
	if(m_List.GetRecords()->GetCount() <= 0)
		return;

	CXTPGridRecord * pRecord = NULL;
	pRecord = !bListSelect  ? m_List.GetRecords()->GetAt(0) : m_List.GetFirstSelectedRecord(); // nModifySelectRow
	int nRowIndex = !bListSelect  ? 0 :  m_List.GetSelectedRows()->GetAt(0)->GetIndex();
	if(pRecord == NULL)
		return;

	ST_CASH_CHARGE cashCharge;
	long nBackOrderCompany = 0;
	cashCharge = m_vecCashCharge[nRowIndex];	
	ST_CONSIGN *pListInfo = (ST_CONSIGN*)m_List.GetItemData(pRecord);
	
	// 작업0. 앞오더를 만든다		(도착지 만들기 )CRcpPlaceInfo =   MakePlaeInfo()
	// 0-1 앞오더에  탁송료및 커미션 을 넣는다.	
	MakePlaceInfo2(m_pRcpDlgWndFront, TRUE);


// 1. 뒤오더를 만든다 (출발지 만들고 , 도착지는 그대로쓰고 MakePlaceInfo
	// 2. 입금액확인;
	// 2. 뒤에 요금도 바꾸고          RefreshRcpDlg
	MakePlaceInfo2(m_pRcpDlgWndBack, FALSE);
	
	m_edtTitleStartTerminal.SetWindowText(pListInfo->strStartTerminalName);
	m_edtTitleStartTerminalLink.SetWindowText(pListInfo->strStartTerminalName);
	m_edtTitleDestTerminal.SetWindowText(pListInfo->strDestTerminalName);
	m_edtTitleDestTerminalLink.SetWindowText(pListInfo->strDestTerminalName);
	m_edtTitleStart.SetWindowText(m_pRcpDlgWndFront->m_pStart->GetPOI()->GetDong());
	m_edtTitleDest.SetWindowText(m_pRcpDlgWndBack->m_pDest->GetPOI()->GetDong());	
	m_edtTransCharge.SetWindowText(LF->GetMyNumberFormat(pListInfo->nTerminalCharge));
	//m_nTerminalTempWayID = pListInfo->nCID;			

	if(!cashCharge.bLoad)	{
		
		cashCharge.nStartCharge = m_pRcpDlgWndFront->GetSectionCharge(TRUE);
		// 기본요금 문의필요 
		if( cashCharge.nStartCharge > 0 &&
			m_pRcpDlgWndFront->m_pCharge->m_bDefaultCharge  && 
			cashCharge.nStartCharge == m_pRcpDlgWndFront->m_pBi->nDefaultCharge)
		{
			cashCharge.bStartNomalCharge = FALSE;
		}
		else
		{
			cashCharge.bStartNomalCharge = TRUE;			
		}
		cashCharge.nDestCharge = m_pRcpDlgWndBack->GetSectionCharge(TRUE);
		if( cashCharge.nDestCharge > 0 &&
			m_pRcpDlgWndBack->m_pCharge->m_bDefaultCharge  && 
			cashCharge.nDestCharge == m_pRcpDlgWndBack->m_pBi->nDefaultCharge)
		{
			// 기본요금 문의필요 
			cashCharge.bDestNomalCharge = FALSE;
		}
		else
		{
			cashCharge.bDestNomalCharge = TRUE;
		}
		cashCharge.bLoad = TRUE;
		cashCharge.nTerminalCharge = pListInfo->nTerminalCharge;
		cashCharge.nTempCharge = cashCharge.nStartCharge + cashCharge.nDestCharge + 
			cashCharge.nTerminalCharge;
		m_vecCashCharge[nRowIndex] = cashCharge;

	}	

	if(bListSelect && nModifySelectRow <= 0) // 수정한거에 대해서는 자동요금 계산안하게
	{
		m_edtStartCharge.SetWindowText(LF->GetMyNumberFormat(cashCharge.nStartCharge));
		m_stcFrontCharge.SetWindowText(cashCharge.bStartNomalCharge ? "정상요금" : "요금문의");
		m_edtDestCharge.SetWindowText(LF->GetMyNumberFormat(cashCharge.nDestCharge));
		m_stcBackCharge.SetWindowText(cashCharge.bDestNomalCharge ? "정상요금" : "요금문의");
		
		m_edtTransCharge.SetWindowText(LF->GetMyNumberFormat(cashCharge.nTerminalCharge));
		m_edtTempCharge.SetWindowText(LF->GetMyNumberFormat(cashCharge.nTempCharge));
		m_edtTotalCharge.SetWindowText(LF->GetMyNumberFormat(
			cashCharge.nTempCharge +LF->GetMyUnNumberFormatEdit(&m_edtCommissionCharge)));

		FrontOrderEtcMake(); // 비고를 만든다.
		m_pRcpDlgWndFront->m_nTerminalWayID = pListInfo->nCID;
		m_pRcpDlgWndFront->m_edtConBackOrderCharge.SetWindowText(LF->GetMyNumberFormat(cashCharge.nDestCharge));
		m_pRcpDlgWndFront->m_edtConTotalCharge.SetWindowText(LF->GetMyNumberFormat(cashCharge.nTotalCharge));
	}


	
}
void CConsignLinkDlg::RefreshCharge()
{

	long nStartCharge = 0, nDestCharge = 0, nTransCharge = 0, nCommissionCharge = 0, nTempCharge;
	nStartCharge = LF->GetMyUnNumberFormatEdit(&m_edtStartCharge);
	nDestCharge = LF->GetMyUnNumberFormatEdit(&m_edtDestCharge);
	nTransCharge = LF->GetMyUnNumberFormatEdit(&m_edtTransCharge);
	nTempCharge = nStartCharge + nDestCharge + nTransCharge;
	m_edtTempCharge.SetWindowText(LF->GetMyNumberFormat(nTempCharge));
	m_edtTotalCharge.SetWindowText(LF->GetMyNumberFormat(nTempCharge + LF->GetMyUnNumberFormatEdit(&m_edtCommissionCharge)));

}


void CConsignLinkDlg::OnEnChangeCommissionChargeEdit()
{
	RefreshCharge();
	m_pRcpDlgWndFront->m_edtConCommissionCharge.SetWindowText(LF->GetMyNumberFormatEdit(&m_edtCommissionCharge));
	m_pRcpDlgWndFront->m_edtConTotalCharge.SetWindowText(LF->GetMyNumberFormatEdit(&m_edtTotalCharge));
	
}

CString CConsignLinkDlg::GetViewTime(int nMinute)
{
	if(nMinute <= 0)
	{

		return "";
	}
	COleDateTimeSpan dtSpan;
	dtSpan.SetDateTimeSpan(0, 0,nMinute, 0);
	CString sViewTime = "";
	sViewTime.Format("%2d:%02d", dtSpan.GetHours(), dtSpan.GetMinutes());
	return sViewTime;

}



void CConsignLinkDlg::OnNMReportItemCelChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if(pNMListView->pRow == NULL)
		return;
	if (!pNMListView->pRow || !pNMListView->pColumn)
		return;

	//long nRow = pNMListView->pRow->GetIndex();
	CXTPGridRow *pRow  = pNMListView->pRow;
	if(m_List.GetRecords()->GetCount() > 0)
	{		
		ConsignListSelect(TRUE);
		//m_edtCommissionCharge.SetFocus();
	}
}

void CConsignLinkDlg:: CommissionEditFocus()
{
	m_edtCommissionCharge.SetFocus();
	m_edtCommissionCharge.SetSel(0,LF->GetEditString(&m_edtCommissionCharge).GetLength(),FALSE);

}
void CConsignLinkDlg:: BusNameEditFocus()
{
	m_edtBusName.SetFocus();
	m_edtBusName.SetSel(0,LF->GetEditString(&m_edtBusName).GetLength(),FALSE);
}


void CConsignLinkDlg::OnBnClickedCloseBtn()
{

	if(m_pRcpDlgWndBack)
		m_pRcpDlgWndBack->OnBnClickedCloseBtn();
	OnOK();
}

BOOL CConsignLinkDlg::PreTranslateMessage(MSG* pMsg)
{


	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)		 
		{  
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
			case IDC_BUSNAME_EDIT:
				m_edtBusNo.SetFocus();				
				return TRUE;

			case IDC_BUSNO_EDIT:
				m_edtInvoiceNo.SetFocus();
				return TRUE;

			case IDC_INVOICE_NO_EDIT:
				m_edtEtc.SetFocus();
				return TRUE;

			case IDC_ETC_EDIT:
				m_cmbElapsed.SetFocus();
				return TRUE;

			case IDC_ELAPSED_COMBO:
				m_btnConsignInputInfo.SetFocus();
				return TRUE;
			case IDC_BUS_INFO_BTN:
				OnBnClickedBusInfoBtn();
				return TRUE;
			case IDC_COMMISSION_CHARGE_EDIT:
				m_btnConsignLink.SetFocus();
				return TRUE;

			case IDC_CONSIGN_LINK_BTN:
				OnBnClickedConsignLinkBtn();
				return TRUE;
			}
		}


	}
	return CMyDialog::PreTranslateMessage(pMsg);
}


//---------------------------------------------------------------------------------------------------->

void CConsignLinkDlg::OnCbnSelchangeElapsedCombo()
{
	UpdateData();
	COleDateTimeSpan dtSpan;
	int nCurSel = m_cmbElapsed.GetCurSel();

	dtSpan.SetDateTimeSpan(0,0, (nCurSel + 1) *30,0);
	m_dtDest = m_dtStart + dtSpan;
	UpdateData(FALSE);
}

void CConsignLinkDlg::OnBnClickedConsignBusCloseBtn()
{
	if(m_pRcpDlgWndBack)
		m_pRcpDlgWndBack->OnBnClickedCloseBtn();
	OnOK();
}


void CConsignLinkDlg::OnCancel()
{
	InitControl();
	CMyDialog::OnCancel();
}

void CConsignLinkDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	InitControl();
	
	CMyDialog::OnOK();
}

