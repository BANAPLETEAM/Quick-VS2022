// OrderProcessStateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "OrderProcessStateDlg.h"
#include "PoiData.h"
#include "RcpView.h"
#include "SignDlg.h"
#include "RcpDlg.h"
#include "MyMkMessenger.h"
#include "SaveMentDlg.h" 
#include "RiderSubInfo.h"
#include "RiderMapNormalForm.h"

// COrderProcessStateDlg 대화 상자입니다.

#define ID_PHONE 10000

IMPLEMENT_DYNAMIC(COrderProcessStateDlg, CMyDialog)
COrderProcessStateDlg::COrderProcessStateDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(COrderProcessStateDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_nRiderCompany = ZERO;
	m_nRNo = ZERO;
	m_bHasRiderInfo = FALSE;
	m_bPhoneMenuRiderType = FALSE;
}

COrderProcessStateDlg::~COrderProcessStateDlg()
{
	if(LU->GetMessenger())
		LU->GetMessenger()->DeleteRiderPosWnd(this);
}

void COrderProcessStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RIDER_MAP_CTRL, m_wndRiderMap);
	DDX_Control(pDX, IDC_STATE_PIC, m_picState);
	DDX_Control(pDX, IDC_STATE_STATIC, m_stcState);
	DDX_Control(pDX, IDC_DT1_STATIC, m_stcDt1);
	DDX_Control(pDX, IDC_DT3_STATIC, m_stcDt3);
	DDX_Control(pDX, IDC_DT_FINAL_STATIC, m_stcDtFinal);
	DDX_Control(pDX, IDC_START_STATIC, m_stcStart);
	DDX_Control(pDX, IDC_RIDER_STATIC, m_stcRider);
	DDX_Control(pDX, IDC_DEST_STATIC, m_stcDest);
	DDX_Control(pDX, IDC_LEFT_STATIC, m_stcLeft);
	DDX_Control(pDX, IDC_TIME_STATIC, m_stcTime);
	DDX_Control(pDX, IDC_CUR_STATIC, m_stcCur);
	DDX_Control(pDX, IDC_RIDER_CHK, m_chkRider);
	DDX_Control(pDX, IDC_CUSTOMER_CHECK, m_chkCustomer);
	DDX_Control(pDX, IDC_SMS_EDIT, m_edtSMS);
	DDX_Control(pDX, IDC_CUSTOMER_PHONE_STATIC, m_stcCustomerPhone);
	DDX_Control(pDX, IDC_RIDER_PHONE_STATIC, m_stcRiderPhone);
	DDX_Control(pDX, IDC_MENT_COMBO, m_cmbMent);
	DDX_Control(pDX, IDC_DRAW_STATIC, m_stcDraw);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC3, m_stc3);
	DDX_Control(pDX, IDC_STATIC4, m_stc4);
	DDX_Control(pDX, IDC_ORDER_REPORT, m_lstOrder);
	DDX_Control(pDX, IDC_RIDER_SMS_STATIC, m_stcRiderSMSPhone);
	DDX_Control(pDX, IDC_CUSTOMER_SMS_STATIC, m_stcCustomerSMSPhone);

	DDX_Control(pDX, IDC_STATIC5, m_stc5);
	DDX_Control(pDX, IDC_DT_PICKUP_STATIC, m_stcDtPickup);
	DDX_Control(pDX, IDC_RIDER_PICKUP_STATIC, m_stcRiderPickup);
}


BEGIN_MESSAGE_MAP(COrderProcessStateDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BUTTON, OnBnClickedRefreshButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_SIGN_BTN, OnBnClickedSignBtn)
	ON_BN_CLICKED(IDC_RIDER_CHK, OnBnClickedRiderChk)
	ON_BN_CLICKED(IDC_CUSTOMER_CHECK, OnBnClickedCustomerCheck)
	ON_BN_CLICKED(IDC_SEND_SMS_CUSTOMER_BTN, OnBnClickedSendSmsCustomerBtn)
	ON_MESSAGE(WM_REFRESH_RIDER_POS, OnRefreshRiderPos)
	ON_BN_CLICKED(IDC_SEND_SMS_RIDER_BTN, OnBnClickedSendSmsRiderBtn)
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_SEND_PDA_BTN, OnBnClickedSendPdaBtn)
	ON_BN_CLICKED(IDC_SAVE_MENT_BTN, &COrderProcessStateDlg::OnBnClickedSaveMentBtn)
	ON_CBN_SELCHANGE(IDC_MENT_COMBO, &COrderProcessStateDlg::OnCbnSelchangeMentCombo)
	ON_MESSAGE(WM_USER + 5656, OnGetDistance)
	ON_MESSAGE(WM_USER + 6000, OnGetDistance)
	ON_COMMAND_RANGE(ID_PHONE, ID_PHONE + 20, OnMenuPhone)

	ON_BN_CLICKED(IDC_RCP_BTN, &COrderProcessStateDlg::OnBnClickedRcpBtn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHANGE_PHONE_BTN, &COrderProcessStateDlg::OnBnClickedChangePhoneBtn)
	ON_BN_CLICKED(IDC_MAP_BUTTON, &COrderProcessStateDlg::OnBnClickedMapButton)
	ON_BN_CLICKED(IDC_CHANGE_PHONE_RIDER_BTN, &COrderProcessStateDlg::OnBnClickedChangePhoneRiderBtn)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void COrderProcessStateDlg::OnMenuPhone(UINT nFlag)
{ 
	int nPhoneType = 0;
	CString strPhone = m_arryPhone.GetAt(nFlag - ID_PHONE);
	if(m_ci.m_strPhone == strPhone)
		nPhoneType = 1;
	else if(m_ci.m_strOfficePhone == strPhone)
		nPhoneType = 2;

	if(m_bPhoneMenuRiderType)
	{
		m_stcRiderPhone.SetWindowText("기사 : " + ::GetDashPhoneNumber(strPhone));
		if(nPhoneType == 0)
			m_stcCustomerSMSPhone.SetWindowText("<- 기사번호로 전송됨");
		else if(nPhoneType == 1)
			m_stcCustomerSMSPhone.SetWindowText("<- 대표번호로 전송됨");
		else if(nPhoneType == 2)
			m_stcCustomerSMSPhone.SetWindowText("<- 상황실번호로 전송됨");
	}
	else
	{
		m_stcCustomerPhone.SetWindowText("고객 : " + ::GetDashPhoneNumber(strPhone));
		if(nPhoneType == 0)
			m_stcRiderSMSPhone.SetWindowText("<- 고객번호로 전송됨");
		else if(nPhoneType == 1)
			m_stcRiderSMSPhone.SetWindowText("<- 대표번호로 전송됨");
		else if(nPhoneType == 2)
			m_stcRiderSMSPhone.SetWindowText("<- 상황실번호로 전송됨");
	}
}

void COrderProcessStateDlg::OnBnClickedRefreshButton()
{
	Refresh();
}

void COrderProcessStateDlg::OnBnClickedCloseButton()
{
	OnCancel();
}

void COrderProcessStateDlg::Refresh()
{
	SetForegroundWindow();

	m_stcDtPickup.SetWindowText("-"); 
	m_stcRiderPickup.SetWindowText("");

	m_stcDtFinal.SetWindowText("-");
	m_stcDest.SetWindowText("");

	char buffer[10];
	SetWindowText("현재오더 진행상태 [오더:" + CString(itoa(m_nTNo, buffer, 10)) + "]");

	long nLastState = 0;
	long nRiderPosX = 0;
	long nDestPosX = 0;
	long nRiderPosY = 0;
	long nDestPosY = 0;
	long nStartPosX = 0;
	long nStartPosY = 0;
	CString sSDong = "";
	CString sDDong = "";
	CString sPosName = "";
	COleDateTime dtPosLog = COleDateTime::GetCurrentTime();

    CMkRecordset pRs(m_pMkDb); 
	CMkCommand pCmd(m_pMkDb, "select_order_cur_state_3");
	pCmd.AddParameter(m_nTNo); 
	CMkParameter * pParState = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter * pParStart = pCmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter * pParDest = pCmd.AddParameter(typeString, typeOutput, 50, "");
	CMkParameter * pParPosName = pCmd.AddParameter(typeString, typeOutput, 30, "");
	CMkParameter * pParPosLog = pCmd.AddParameter(typeDate, typeOutput, sizeof(COleDateTime), dtPosLog);
	CMkParameter * pParRiderPosX = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter * pParRiderPosY = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter * pParStartPosX = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter * pParStartPosY = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter * pParDestPosX = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter * pParDestPosY = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter * pParCNo = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;

	pParState->GetValue(nLastState);
	pParStart->GetValue(sSDong);
	pParDest->GetValue(sDDong);
	pParPosName->GetValue(sPosName);
	pParPosLog->GetValue(dtPosLog);
	pParRiderPosX->GetValue(nRiderPosX);
	pParRiderPosY->GetValue(nRiderPosY);
	pParStartPosX->GetValue(nStartPosX);
	pParStartPosY->GetValue(nStartPosY);
	pParDestPosX->GetValue(nDestPosX);
	pParDestPosY->GetValue(nDestPosY);
	pParCNo->GetValue(m_nCNo);


    m_stcDest.SetWindowText(sDDong);

	COleDateTime dtLog;
	long nState;

	if(pRs.GetRecordCount() == 0)
		return;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("dtLog", dtLog);
		pRs.GetFieldValue("nState", nState);
		pRs.GetFieldValue("nEtc1", m_nRiderCompany);
		pRs.GetFieldValue("nEtc2", m_nRNo);

		CRiderSubInfoMap::iterator it = LU->m_mapRiderSub.find(std::make_pair(m_nRiderCompany, m_nRNo));

		if(it != LU->m_mapRiderSub.end())
			it->second.GetPrevPos(nRiderPosX, nRiderPosY);

		CString sMsg = "";
		COleDateTimeSpan span = COleDateTime::GetCurrentTime() - dtPosLog;

		switch(nState)
		{
		case 10 :
			m_stcDt1.SetWindowText(dtLog.Format("%m-%d %H:%M"));
			m_stcStart.SetWindowText(sSDong);
			break;
		case 30 :
			m_stcDt3.SetWindowText(dtLog.Format("%m-%d %H:%M"));

			if(nRiderPosX == 0 || nRiderPosY == 0)
			{
				sMsg = "GPS위치없음";
			}
			else
			{
				if(span.GetSeconds() > 60) 
					sMsg.Format("%s[%d분전]", sPosName, span.GetMinutes());
				else
					sMsg.Format("%s[%d초전]", sPosName, span.GetSeconds());
			}
			
			m_stcRider.SetWindowText(sMsg);
			break;
		case 31 :
			m_stcDtPickup.SetWindowText(dtLog.Format("%m-%d %H:%M"));

			if(nRiderPosX == 0 || nRiderPosY == 0)
			{
				sMsg = "GPS위치없음"; 
			}
			else
			{
				if(span.GetSeconds() > 60) 
					sMsg.Format("%s[%d분전]", sPosName, span.GetMinutes());
				else
					sMsg.Format("%s[%d초전]", sPosName, span.GetSeconds());
			}

			m_stcRider.SetWindowText("");
			m_stcRiderPickup.SetWindowText(sMsg);
			break;
		case 35 :
			m_stcDtFinal.SetWindowText(dtLog.Format("%m-%d %H:%M"));
			m_stcDest.SetWindowText(sDDong);
			break;
		}

		pRs.MoveNext();
	}

	CRect rcCur, rcDt1, rcDt3, rcDtFinal, rcDtPickup;

	m_stcCur.GetWindowRect(rcCur);
	m_stc1.GetWindowRect(rcDt1);
	m_stc3.GetWindowRect(rcDt3);
	m_stc4.GetWindowRect(rcDtFinal);
	m_stc5.GetWindowRect(rcDtPickup);

	ScreenToClient(rcCur);
	ScreenToClient(rcDt1);
	ScreenToClient(rcDt3);
	ScreenToClient(rcDtFinal); 
	ScreenToClient(rcDtPickup);

	switch(nLastState)
	{
	case 10 :
		rcCur.top = rcDt1.top;
		rcCur.bottom = rcDt1.bottom;
		m_stcCur.MoveWindow(rcCur);
		break;
	case 30 :
		rcCur.top = rcDt3.top;
		rcCur.bottom = rcDt3.bottom;
		m_stcCur.MoveWindow(rcCur);
		break;
	case 31 :
		rcCur.top = rcDtPickup.top;
		rcCur.bottom = rcDtPickup.bottom;
		m_stcCur.MoveWindow(rcCur);
		break;
		
	case 35 :
		rcCur.top = rcDtFinal.top;
		rcCur.bottom = rcDtFinal.bottom;
		m_stcCur.MoveWindow(rcCur);

		break;
	}

	bitmap.DeleteObject();
	m_stcState.SetWindowText(::GetStateString(nLastState));
	GetBitmapFromImageList(LU->GetRcpView()->GetImageList(), GetImageNumber(nLastState), bitmap);
	m_picState.SetBitmap((HBITMAP)bitmap.GetSafeHandle());
	Invalidate(TRUE);

	if(nLastState == 30 || nLastState == 31) 
	{
		if(nRiderPosX != 0 && nRiderPosY != 0) 
		{
			nDestPosX = nDestPosX / 1000000.0 * 360000;
			nDestPosY = nDestPosY / 1000000.0 * 360000;
			double fKm = CPOIData::GetDistanceKMeter(nRiderPosX / 1000000.0, nRiderPosY / 1000000.0, nDestPosX / 1000000.0, nDestPosY / 1000000.0);

			CString sLeft; sLeft.Format("%0.1fKm [도착지 - 기사위치](직선)", fKm);
			m_stcLeft.SetWindowText(sLeft);
			//m_stcTime.SetWindowText(sKm);

			//nRiderPosX = nRiderPosX / 0.36;
			//nRiderPosY = nRiderPosY / 0.36;
			//nDestPosX = nDestPosX / 0.36;
			//nDestPosY = nDestPosY / 0.36;

			if(nRiderPosX > 100000000)
			{
				nRiderPosX = nRiderPosX * 0.36;
				nRiderPosY = nRiderPosY * 0.36;
			}
	
			GetOnlyDistance(nRiderPosX, nRiderPosY, nDestPosX, nDestPosY, this);
		}
	}
/*
	nStartPosX = nStartPosX * 360000.0 / 1000000;
	nStartPosY = nStartPosY * 360000.0 / 1000000;
	nDestPosX = nDestPosX * 360000.0 / 1000000;
	nDestPosY = nDestPosY * 360000.0 / 1000000;
	*/
 
	m_wndRiderMap.MoveMapRider(m_nRiderCompany, m_nRNo);
	m_wndRiderMap.SetTraceRider(m_nRiderCompany, m_nRNo); 
	m_wndRiderMap.AddPointPOI(FALSE, CString("출발지:") + sSDong, nStartPosX, nStartPosY, "", "POINT", -1,
					POINT_POI, 3); 
	m_wndRiderMap.AddPointPOI(FALSE, CString("도착지:") + sDDong, nDestPosX, nDestPosY, "", "POINT", -1,
					POINT_POI, 4);

}

BOOL COrderProcessStateDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CBitmap bitmap;
	CImageList imageList;
	bitmap.LoadBitmap(IDB_LIST);
	imageList.Create(16,18,ILC_COLOR24 | ILC_MASK,1,1); 
	imageList.Add(&bitmap,RGB(0, 255, 255));
	m_lstOrder.SetImageList(&imageList,LVSIL_SMALL);
	m_lstOrder.GetPaintManager()->m_strNoItems = "";
	m_lstOrder.InsertColumn(0, "시간",LVCFMT_LEFT, 55);
	m_lstOrder.InsertColumn(1, "의뢰인",LVCFMT_LEFT, 67);
	m_lstOrder.InsertColumn(2, "출발지",LVCFMT_LEFT, 63);
	m_lstOrder.InsertColumn(3, "도착지",LVCFMT_LEFT, 63);
	m_lstOrder.InsertColumn(4, "요금",LVCFMT_RIGHT, 50);
	m_lstOrder.EnableToolTips(FALSE);

	m_stcCur.SetTextColor(RGB(255, ZERO, ZERO));

	m_wndRiderMap.SetMapLevel(AfxGetApp()->GetProfileInt("CRcpPageMapForm", "RiderMapLevel", 6));
	m_wndRiderMap.SetRefereshAdminState();
	m_wndRiderMap.CreateWait();

	//CLogiUtil::OpenCurOrderState(long nTNo) 에서 호출
	//FillData();
    //Refresh();
	//RefreshOrderList();
	
	BOOL bRider = AfxGetApp()->GetProfileInt("OrderProcessStateDlg", "Rider", ZERO);

	if(bRider == TRUE)
	{
		m_chkRider.SetCheck(TRUE);
		m_chkCustomer.SetCheck(FALSE);
		OnBnClickedRiderChk();
	}
	else
	{
		m_chkRider.SetCheck(FALSE);
		m_chkCustomer.SetCheck(TRUE);
		OnBnClickedCustomerCheck();
	}

	//이부분은 창생성이 완료된후에 넣는게 좋다.
	LU->GetMessenger()->AddRecvRiderPosWnd(this);
	//RefreshCombo(TRUE);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COrderProcessStateDlg::FillData()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_cur_sms_info_2"); 
	pCmd.AddParameter(m_nTNo);

	if(pRs.Execute(&pCmd) && (pRs.GetRecordCount() != 0))
	{
		pRs.GetFieldValue("nTNo", m_stSmsInfo.nTNo);
		pRs.GetFieldValue("sOName", m_stSmsInfo.strOName);
		pRs.GetFieldValue("sOPhone", m_stSmsInfo.strOPhone);
		pRs.GetFieldValue("sOMobile", m_stSmsInfo.strOMobile);
		pRs.GetFieldValue("sSDong", m_stSmsInfo.strSDong);
		pRs.GetFieldValue("sDDong", m_stSmsInfo.strDDong);
		pRs.GetFieldValue("sRMobile", m_stSmsInfo.strRiderPhone);
		pRs.GetFieldValue("nRNo", m_stSmsInfo.nRNo);
		pRs.GetFieldValue("sRName", m_stSmsInfo.strRName);
		pRs.GetFieldValue("sID", m_stSmsInfo.strID);
		pRs.GetFieldValue("nRiderCompany", m_stSmsInfo.nRiderCompany);
		pRs.GetFieldValue("nCarType", m_stSmsInfo.nCarType);

		if(m_stSmsInfo.nRiderCompany > 0 &&
			m_stSmsInfo.nRNo > 0)
			m_bHasRiderInfo = TRUE;
		else
			m_bHasRiderInfo = FALSE;
	}
	else
		m_bHasRiderInfo = FALSE;

	if(m_stSmsInfo.strOMobile.IsEmpty())
		m_stcCustomerPhone.SetWindowText("고객 : " + ::GetDashPhoneNumber(m_stSmsInfo.strOPhone));
	else
		m_stcCustomerPhone.SetWindowText("고객 : " + ::GetDashPhoneNumber(m_stSmsInfo.strOMobile));

	m_stcRiderPhone.SetWindowText("기사 : " + ::GetDashPhoneNumber(m_stSmsInfo.strRiderPhone));
}

BOOL COrderProcessStateDlg::GetBitmapFromImageList(CImageList *imglist,int nIndex,CBitmap &bmp)
{
	IMAGEINFO pImageInfo;
	imglist->GetImageInfo(0, &pImageInfo);
	int nWidth = pImageInfo.rcImage.right - pImageInfo.rcImage.left;
	int nHeight = pImageInfo.rcImage.bottom - pImageInfo.rcImage.top;

	CDC dc, *pDC = GetDC();
	HICON hIcon = imglist->ExtractIcon(nIndex);

	dc.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, nWidth, nHeight);
	CBitmap* pOldBmp = dc.SelectObject(&bmp);
	CBrush brush ;
	COLORREF m_newclrBack;
	m_newclrBack=GetSysColor(COLOR_3DFACE);
	brush.CreateSolidBrush(m_newclrBack);
	::DrawIconEx(
		dc.GetSafeHdc(),
		0,
		0,
		hIcon,
		nWidth,
		nHeight,
		0,
		(HBRUSH)brush,
		DI_NORMAL);

	dc.SelectObject(pOldBmp);
	dc.DeleteDC();
	// the icon is not longer needed
	::DestroyIcon(hIcon);

	ReleaseDC(pDC);
	return(TRUE);
}
void COrderProcessStateDlg::OnBnClickedSignBtn()
{
	CSignDlg dlg;
	dlg.m_nTNo = m_nTNo;
	dlg.m_nCNo = m_nCNo;
	dlg.DoModal();
}

void COrderProcessStateDlg::OnBnClickedRiderChk()
{
	if(m_chkRider.GetCheck() == BST_CHECKED)
		m_chkCustomer.SetCheck(FALSE);
	else
		m_chkCustomer.SetCheck(TRUE);

	AfxGetApp()->WriteProfileInt("OrderProcessStateDlg", "Rider", ZERO);
	RefreshCombo(FALSE);
	//MakeMsg();	
}

void COrderProcessStateDlg::OnBnClickedCustomerCheck()
{
	if(m_chkCustomer.GetCheck() == BST_CHECKED)
		m_chkRider.SetCheck(FALSE);
	else
		m_chkRider.SetCheck(TRUE);

	AfxGetApp()->WriteProfileInt("OrderProcessStateDlg", "Rider", ONE);
	RefreshCombo(FALSE);
	//MakeMsg();	
}

void COrderProcessStateDlg::MakeMsg()
{

	if(m_cmbMent.GetCurSel() >= ZERO)
	{
		CString strMsg = "";

		m_cmbMent.GetLBText(m_cmbMent.GetCurSel(), strMsg);
		m_edtSMS.SetWindowText(strMsg);
	}

	/*
	if(m_chkRider.GetCheck())
	{
		
		sMsg = m_stSmsInfo.sOName + "[" + m_stSmsInfo.sSDong + "->" + m_stSmsInfo.sDDong + "] ";
		sMsg += "고객님에게 독촉전화가 왔습니다.";
		sMsg += "연락바랍니다.";   
	}
	else if(m_chkCustomer.GetCheck())
	{
        sMsg = m_stSmsInfo.sRName + "기사님에게 ";
		sMsg += "연락드렸습니다.";
		sMsg += "감사합니다.";
	}

	m_edtSMS.SetWindowText(sMsg);
	*/
}

void COrderProcessStateDlg::OnBnClickedSendSmsCustomerBtn()
{
	CString sMsg; m_edtSMS.GetWindowText(sMsg);

	if(sMsg.IsEmpty())
	{
		MessageBox("내용을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sTranPhone; m_stcCustomerPhone.GetWindowText(sTranPhone);
	sTranPhone.Replace("고객 : ", "");

	if(sTranPhone.Left(2) != "01")
	{
		MessageBox("고객전화번호가 휴대폰이 아니어서 전송할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sCallBackPhone; m_stcRiderPhone.GetWindowText(sCallBackPhone);
	sCallBackPhone.Replace("기사 : ", "");

	::SendSmsNew(m_ci.m_nCompanyCode, m_stSmsInfo.nTNo, sTranPhone,
		sCallBackPhone, sMsg, "독촉문자",  "", "", TRUE);
}


void COrderProcessStateDlg::OnBnClickedSendSmsRiderBtn()
{
	CString sMsg; m_edtSMS.GetWindowText(sMsg);

	if(sMsg.IsEmpty())
	{
		MessageBox("내용을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_stSmsInfo.strRiderPhone.Left(2) != "01")
	{
		MessageBox("기사전화번호가 휴대폰이 아니어서 전송할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sCallBackPhone; m_stcCustomerPhone.GetWindowText(sCallBackPhone);
	sCallBackPhone.Replace("고객 : ", "");

	::SendSmsNew(m_ci.m_nCompanyCode, m_stSmsInfo.nTNo, m_stSmsInfo.strRiderPhone,
		sCallBackPhone, sMsg, "독촉문자", "", "", TRUE);
}


void COrderProcessStateDlg::OnCancel()
{
	ShowWindow(SW_HIDE);
	//DestroyWindow();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CMyDialog::OnCancel();
}

void COrderProcessStateDlg::OnBnClickedSendPdaBtn()
{
	CString sMsg; m_edtSMS.GetWindowText(sMsg);

	if(sMsg.IsEmpty())
	{
		MessageBox("내용을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(m_stSmsInfo.strID.Left(2) != "01")
	{
		MessageBox("기사단말기 번호가 정확하지 않아 전송할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "edit_rider_msg4");
	pCmd.AddParameter(m_stSmsInfo.nRiderCompany);
	pCmd.AddParameter(0);
	pCmd.AddParameter(m_stSmsInfo.nRiderCompany);
	pCmd.AddParameter(m_stSmsInfo.nRNo);
	pCmd.AddParameter(sMsg);
	pCmd.AddParameter(m_ui.nWNo);
	pCmd.AddParameter(m_ui.nCompany);

	if(pCmd.Execute())
		MessageBox("기사님에게 전송되었습니다", "확인", MB_ICONINFORMATION);
}

LONG COrderProcessStateDlg::OnRefreshRiderPos(WPARAM wParam, LPARAM lParam)
{
	if(m_wndRiderMap.IsTraceRider(wParam, lParam))
		m_wndRiderMap.RefreshRiderPos();

	return 0;
}

void COrderProcessStateDlg::OnBnClickedSaveMentBtn()
{
	CSaveMentDlg dlg;
	dlg.DoModal();

	RefreshCombo(TRUE);
}

void COrderProcessStateDlg::RefreshCombo(BOOL bDbRefresh)
{
	if(m_mapStateMent.size() == ZERO || bDbRefresh == TRUE)
		::FillStateMent();

	m_cmbMent.ResetContent();
	
	long nType = m_chkRider.GetCheck() ? ZERO : ONE;

	long nCount = ZERO;

	MAP_STATE_MENT::iterator it;
 
	for(it = m_mapStateMent.begin(); it != m_mapStateMent.end(); it++)
	{
		if(nType == it->second.nType)
		{
			m_cmbMent.InsertString(nCount++, GetStateReplaceMent(it->second.strMent));
		}
	}

	if(m_cmbMent.GetCount() >= ZERO)
	{
		long nSel = AfxGetApp()->GetProfileInt("OrderProcessStateDlg", "ComboSel", ZERO);

		if(nSel < m_cmbMent.GetCount())
			m_cmbMent.SetCurSel(nSel);
		else
			m_cmbMent.SetCurSel(ZERO);

		MakeMsg();
	}
}

CString COrderProcessStateDlg::GetStateReplaceMent(CString strMent)
{
	strMent.Replace("[@F1]", m_stSmsInfo.strOName);
	strMent.Replace("[@F2]", m_stSmsInfo.strSDong); 
	strMent.Replace("[@F3]", m_stSmsInfo.strDDong);
	strMent.Replace("[@F4]", m_stSmsInfo.strRName);
	strMent.Replace("[@F5]", m_stSmsInfo.strRiderPhone);

	return strMent;
}

void COrderProcessStateDlg::OnCbnSelchangeMentCombo()
{
	AfxGetApp()->WriteProfileInt("OrderProcessStateDlg", "ComboSel", m_cmbMent.GetCurSel());

	CString strMent; m_cmbMent.GetLBText(m_cmbMent.GetCurSel(), strMent);
	m_edtSMS.SetWindowText(strMent);
}

LONG COrderProcessStateDlg::OnGetDistance(WPARAM wParam, LPARAM lParam)
{
	double* pdDistance = (double*)wParam;
	if(pdDistance == NULL)
	return 0;

	float fDirectDistance = (float)*pdDistance;
	CString strDistance; strDistance.Format("%0.1fKm [도착지 - 기사위치]", fDirectDistance);
	m_stcLeft.SetWindowText(strDistance);

	DELETE_OBJECT(pdDistance);

	return 0;
}

void COrderProcessStateDlg::OnBnClickedRcpBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COrderProcessStateDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	LF->FillBackground(&dc, this); 

	char buffer[10];

	CRect rc;  
	m_stcDraw.GetWindowRect(rc);
	ScreenToClient(rc);  

	//dc.SetBkMode(TRANSPARENT); 
  
	dc.FillSolidRect(rc, RGB(0, 0, 0)); 
	rc.DeflateRect(1, 1, 1, 1);
	dc.FillSolidRect(rc, RGB(255, 255, 255));

	CFont* pOldFont = dc.SelectObject(m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	
	if(m_bHasRiderInfo == TRUE) 
	{
		#define FONT_HEIGHT 16 
		#define FONT_SPACE 3
 
		rc.top += 5; rc.bottom = rc.top + FONT_HEIGHT;
 		dc.DrawText("기사정보", rc, DT_CENTER | DT_VCENTER);
		dc.SetTextColor(RGB(0, 0, 255));
	 
		rc.left += 10;  
		rc.top = rc.bottom + FONT_SPACE + 4; rc.bottom = rc.top + FONT_HEIGHT;
		dc.DrawText("소   속 : " + m_ci.GetName(m_stSmsInfo.nRiderCompany), rc, DT_LEFT | DT_VCENTER);
  
		rc.top = rc.bottom + FONT_SPACE; rc.bottom = rc.top + FONT_HEIGHT;
		dc.DrawText("기사명 : " + m_stSmsInfo.strRName + "(" + CString(itoa(m_stSmsInfo.nRNo, buffer, 10)) + ")", rc, DT_LEFT | DT_VCENTER);

		rc.top = rc.bottom + FONT_SPACE; rc.bottom = rc.top + FONT_HEIGHT;
		dc.DrawText("차   종 : " + ::GetCarTypeFromLong(m_stSmsInfo.nCarType), rc, DT_LEFT | DT_VCENTER);

		rc.top = rc.bottom + FONT_SPACE; rc.bottom = rc.top + FONT_HEIGHT;
		dc.DrawText("단말ID : " + ::GetDashPhoneNumber(m_stSmsInfo.strID), rc, DT_LEFT | DT_VCENTER);

		rc.top = rc.bottom + FONT_SPACE; rc.bottom = rc.top + FONT_HEIGHT;
		dc.DrawText("휴대폰 : " + ::GetDashPhoneNumber(m_stSmsInfo.strRiderPhone), rc, DT_LEFT | DT_VCENTER);
	}
	else
	{
		dc.SetTextColor(RGB(0, 0, 0));
		dc.DrawText("기사정보 없음", rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

void COrderProcessStateDlg::DrawStcText(CDC *pDC, COLORREF rgbText, COLORREF rgbMainText, CString sDisplayName, CRect rc, long nType, CFont *font)
{
	CFont* pOldFont = pDC->SelectObject(font);
	pDC->SetTextColor(rgbText);  
	pDC->DrawText(sDisplayName, rc, nType);

	long nStartFind = sDisplayName.Find("[");
	if(nStartFind >= 0) 
	{ 
		long  nEndFind = sDisplayName.Find("]");
		CString sMainWord = sDisplayName.Mid(nStartFind, nEndFind - nStartFind + 1);
		CString sStartWord = sDisplayName.Left(nStartFind);

		CSize szMain = pDC->GetTextExtent(sMainWord);
		CSize szStartWord = pDC->GetTextExtent(sStartWord);

		rc.left = rc.left + szStartWord.cx;

		pDC->SetTextColor(rgbMainText);  
		pDC->DrawText(sMainWord, rc, nType);
	}
	
	pDC->SelectObject(pOldFont);
}

void COrderProcessStateDlg::OnBnClickedChangePhoneBtn()
{
	m_bPhoneMenuRiderType = FALSE;
	LoadPhoneMenu();
}

void COrderProcessStateDlg::OnBnClickedChangePhoneRiderBtn()
{
	m_bPhoneMenuRiderType = TRUE;
	LoadPhoneMenu();
}

void COrderProcessStateDlg::RefreshOrderList()
{
	m_lstOrder.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_have_order");
	pCmd.AddParameter(m_nRiderCompany);
	pCmd.AddParameter(m_nRNo);
	if(pRs.Execute(&pCmd))
	{
		for(int i = 0; i < pRs.GetRecordCount(); i++)
		{
			long nCompany, nState, nCharge;
			COleDateTime dtState;
			CString strCName, strStart, strDest;

			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nState", nState);
			pRs.GetFieldValue("dtState", dtState);
			pRs.GetFieldValue("sOName", strCName);
			pRs.GetFieldValue("sSDong", strStart);
			pRs.GetFieldValue("sDDong", strDest);
			pRs.GetFieldValue("nChargeSum", nCharge);

			if(!m_ci.IsChildCompany(nCompany))
				strCName = "타사오더";

			CRiderMapNormalForm::AddRiderHaveOrderToList(&m_lstOrder, i, dtState, nState, strCName, strStart, strDest, nCharge);

			pRs.MoveNext();
		}
	}

	m_lstOrder.Populate();
}
void COrderProcessStateDlg::OnBnClickedMapButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void COrderProcessStateDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_wndRiderMap.GetSafeHwnd() &&
		m_lstOrder.GetSafeHwnd())
	{
		CRect rcForm, rcList, rcMap;
		GetClientRect(rcForm);
		m_lstOrder.GetWindowRect(rcList);
		ScreenToClient(rcList);
		m_wndRiderMap.GetWindowRect(rcMap);
		ScreenToClient(rcMap);

		rcList.bottom = rcForm.bottom - 5;
		m_lstOrder.MoveWindow(rcList);

		rcMap.right = rcForm.right - 5;
		rcMap.bottom = rcForm.bottom - 5;
		m_wndRiderMap.MoveWindow(rcMap);

		RedrawWindow();
	}
}

void COrderProcessStateDlg::LoadPhoneMenu()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_customer_phone");
	pCmd.AddParameter(m_nTNo);

	if(pRs.Execute(&pCmd) == FALSE)
		return;

	if(pRs.GetRecordCount() == ZERO)
		return;

	CPoint pt;
	GetCursorPos(&pt);
	BCMenu *pMenu = new BCMenu;
	pMenu->CreatePopupMenu();

	m_arryPhone.RemoveAll();
	CString strPhone;
	long nCount = pRs.GetRecordCount();

	for(int i=ZERO; i<nCount; i++)
	{
		pRs.GetFieldValue("sPhone", strPhone);
		pMenu->AppendMenu(MF_BYCOMMAND, ID_PHONE + i, ::GetDashPhoneNumber(strPhone));
		m_arryPhone.Add(strPhone);
		pRs.MoveNext(); 
	}

	if(!m_ci.m_strPhone.IsEmpty())
	{
		pMenu->AppendMenu(MF_BYCOMMAND, ID_PHONE + nCount++, ::GetDashPhoneNumber(m_ci.m_strPhone) + " [대표번호]");
		m_arryPhone.Add(m_ci.m_strPhone);
	} 

	if(!m_ci.m_strOfficePhone.IsEmpty())
	{
		pMenu->AppendMenu(MF_BYCOMMAND, ID_PHONE + nCount++, ::GetDashPhoneNumber(m_ci.m_strOfficePhone) + " [상황실]");
		m_arryPhone.Add(m_ci.m_strOfficePhone);
	}

	if(nCount > ZERO)
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	delete pMenu;
	pMenu = NULL;
}