// ChargeHistoryMemDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChargeHistoryMemDlg.h"
#include "MainFrm.h"
#include "ChargeDongDlg2.h"
#include "POIDataNew.h"
#include "POIUnit.h"
#include "SearchCustomerDlg.h"
#include "ChangeHistoryNameDlg.h"


//IMPLEMENT_DYNAMIC(CWorkBtn, CButtonST)
CWorkBtn::CWorkBtn()
{
	m_pWnd = NULL;
}

CWorkBtn::~CWorkBtn()
{
}


BEGIN_MESSAGE_MAP(CWorkBtn, CButtonST)	
	ON_COMMAND(ID_NEW_CHARGE_BUTTON, OnMenuNewCharge)
	ON_COMMAND(ID_DEL_CHARGE_BUTTON, OnMenuDelCharge)	
	ON_COMMAND(ID_MODIFY_CHARGE_BUTTON, OnMenuModifyCharge)
	ON_COMMAND(ID_REFRESH_BTN, OnMenuRefreshServer)	
	ON_COMMAND(ID_SUM_CHARGE_BTN, OnMenuSumCharge)	
	
	//ON_MESSAGE(WM_USER + 100, On_MenuCallback)
END_MESSAGE_MAP()


void CWorkBtn::InitButton(CWnd *pWnd)
{
	short	shBtnColor = 40;
	m_pWnd =  pWnd;

	OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	OffsetColor(CButtonST::BTNST_COLOR_BK_OUT, 28);

	SetMenu(IDR_GROUP_MENU2,GetSafeHwnd());


}    
void CWorkBtn::OnMenuNewCharge()
{
	((CChargeHistoryMemDlg*)m_pWnd)->NewCharge();	
}

void CWorkBtn::OnMenuDelCharge()
{
	((CChargeHistoryMemDlg*)m_pWnd)->DeleteCharge();
}

void CWorkBtn::OnMenuModifyCharge()
{
	((CChargeHistoryMemDlg*)m_pWnd)->OnModifyCharge();
}

void CWorkBtn::OnMenuRefreshServer()
{
	((CChargeHistoryMemDlg*)m_pWnd)->RefreshServer();
}

void CWorkBtn::OnMenuSumCharge()
{
	((CChargeHistoryMemDlg*)m_pWnd)->SumCharge();
}

//---------------------------------------------------------------

//IMPLEMENT_DYNAMIC(CWorkSubBtn, CButtonST)
CWorkSubBtn::CWorkSubBtn()
{
	m_pWnd = NULL;
}

CWorkSubBtn::~CWorkSubBtn()
{
}


BEGIN_MESSAGE_MAP(CWorkSubBtn, CButtonST)
	//{{AFX_MSG_MAP(CDlgAdvanced)
	ON_COMMAND(ID_CUSTOMER_VIEW_REFRESH, OnMenuCustomerRefresh)
	ON_COMMAND(ID_SUB_DEL_BUTTON, OnMenuSubDelBtn)	
	ON_COMMAND(ID_SUB_NEW_BUTTON, OnMenuSubNewBtn)
	ON_COMMAND(ID_CHARGE_VIEW_REFRESH, OnMenuChargeRefresh)
	ON_COMMAND(ID_DEL_CHARGE_ITEM, OnMenuDelChargeItem)

	//}}AFX_MSG_MAP
	//ON_MESSAGE(WM_USER + 100, On_MenuCallback)
END_MESSAGE_MAP()

void CWorkSubBtn::InitButton(CWnd *pWnd)
{
	short	shBtnColor = 40;	
	m_pWnd =  pWnd;
	OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
	OffsetColor(CButtonST::BTNST_COLOR_BK_OUT, 28);	
	SetMenu(IDR_GROUP_MENU3,GetSafeHwnd());


}   
void CWorkSubBtn::OnMenuCustomerRefresh()
{
	((CChargeHistoryMemDlg*)m_pWnd)->m_cmbViewType.SetCurSel(0);
	((CChargeHistoryMemDlg*)m_pWnd)->OnCbnSelchangeViewTypeCombo();
}
void CWorkSubBtn::OnMenuSubDelBtn()
{
	((CChargeHistoryMemDlg*)m_pWnd)->DeleteCustomer();
}
void CWorkSubBtn::OnMenuSubNewBtn()
{
	((CChargeHistoryMemDlg*)m_pWnd)->NewCustomer();
}
void CWorkSubBtn::OnMenuChargeRefresh()
{
	((CChargeHistoryMemDlg*)m_pWnd)->m_cmbViewType.SetCurSel(1);
	((CChargeHistoryMemDlg*)m_pWnd)->OnCbnSelchangeViewTypeCombo();
}
void CWorkSubBtn::OnMenuDelChargeItem()
{
	((CChargeHistoryMemDlg*)m_pWnd)->ChargeItemDelete();
}



//---------------------------------------------------------------


// CChargeHistoryMemDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChargeHistoryMemDlg, CMyDialog)

CChargeHistoryMemDlg::CChargeHistoryMemDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChargeHistoryMemDlg::IDD, pParent)
{
	m_bInit = FALSE;
	m_dtInit.m_dt = 0;
	m_nCNo = 0;
	//m_sChargeName = "";
	m_nResult = 0;
	m_nMemCNo = 0;
	m_nInitMemCNo = 0;
	m_pWnd  = NULL;
}

CChargeHistoryMemDlg::~CChargeHistoryMemDlg()
{

}

void CChargeHistoryMemDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_SEARCH_EDIT, m_edtMainSearch);	
	DDX_Control(pDX, IDC_CUSTOM1, m_lstMain);
	DDX_Control(pDX, IDC_CUSTOM2, m_lstSub);
	DDX_Control(pDX, IDC_SUB_SEARCH_EDIT, m_edtSubSearch);	
	DDX_Control(pDX, IDC_WORK_BTN, m_btnWork);
	DDX_Control(pDX, IDC_WORK_SUB_BTN, m_btnWorkSub);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_edtCompany);
	DDX_Control(pDX, IDC_TEL_EDIT, m_edtTel);
	DDX_Control(pDX, IDC_MOBILE_EDIT, m_edtMobile);
	DDX_Control(pDX, IDC_DEPART_EDIT, m_edtDepart);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_VIEW_TYPE_COMBO, m_cmbViewType);
	DDX_Control(pDX, IDC_CHARGE_NAME_EDIT, m_edtChargeName);
	DDX_Control(pDX, IDC_CHARGE_ETC_EDIT, m_edtChargeEtc);
	DDX_Control(pDX, IDC_TEL_EDIT3, m_edtHistoryName);
	DDX_Control(pDX, IDC_SHUTTLE_CHECK, m_chkShuttle);
}


BEGIN_MESSAGE_MAP(CChargeHistoryMemDlg, CMyDialog)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM1, OnNMlclkList)
	ON_NOTIFY(NM_DBLCLK, IDC_CUSTOM1, OnNMDblclkList)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_RCLICK, IDC_CUSTOM1, OnNMlRClkList)
	ON_NOTIFY(NM_RCLICK, IDC_CUSTOM2, OnNMlRClkList1)
	ON_NOTIFY(XTP_NM_GRID_VALUECHANGED , IDC_CUSTOM2,OnReportValueChanged )
	ON_EN_CHANGE(IDC_MAIN_SEARCH_EDIT, &CChargeHistoryMemDlg::OnEnChangeMainSearchEdit)
	ON_EN_CHANGE(IDC_SUB_SEARCH_EDIT, &CChargeHistoryMemDlg::OnEnChangeSubSearchEdit)
	ON_BN_CLICKED(IDC_CHARGE_LIST_INUT_BTN, &CChargeHistoryMemDlg::OnBnClickedChargeListInput)
	ON_BN_CLICKED(IDC_CHARGE_VIEW_BUTTON, &CChargeHistoryMemDlg::OnBnClickedChargeViewButton)
	ON_CBN_SELCHANGE(IDC_VIEW_TYPE_COMBO, &CChargeHistoryMemDlg::OnCbnSelchangeViewTypeCombo)
	ON_BN_CLICKED(ID_NEW_CHARGE_BUTTON, NewCharge)
	ON_BN_CLICKED(ID_DEL_CHARGE_BUTTON, DeleteCharge)	
	ON_BN_CLICKED(ID_MODIFY_CHARGE_BUTTON, OnModifyCharge)
	ON_BN_CLICKED(ID_REFRESH_BTN, RefreshServer)	
	ON_BN_CLICKED(ID_SUM_CHARGE_BTN, SumCharge)	

	ON_BN_CLICKED(ID_CUSTOMER_VIEW_REFRESH, RefreshSubList)
	ON_BN_CLICKED(ID_SUB_DEL_BUTTON, DeleteCustomer)	
	ON_BN_CLICKED(ID_SUB_NEW_BUTTON, NewCustomer)
	ON_BN_CLICKED(ID_CHARGE_VIEW_REFRESH, OnCbnSelchangeViewTypeCombo)
	ON_BN_CLICKED(ID_DEL_CHARGE_ITEM, ChargeItemDelete)
	ON_BN_CLICKED(IDC_OTHER_CUSTOMER_SEARCH_BTN, &CChargeHistoryMemDlg::OnBnClickedOtherCustomerSearchBtn)
END_MESSAGE_MAP()


// CChargeHistoryMemDlg 메시지 처리기입니다.

BOOL CChargeHistoryMemDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	//m_edtMainSearch.SetWindowText(m_sChargeName);
	
	RefreshMainList();
	m_cmbViewType.SetCurSel(0);

	m_btnWork.InitButton(this);
	
	m_btnWorkSub.InitButton(this);
	m_chkShuttle.SetCheck(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChargeHistoryMemDlg::RefreshMainList()
{
	if(m_cmbViewType.GetCurSel() == 1)
		m_cmbViewType.SetCurSel(0);

	if(m_lstMain.GetRecords()->GetCount() > 0)
		m_lstMain.DeleteAllItem();

	LU->LoadMemberCharge();

	int nRow = 0, nSelectRow = -1;
	MAP_MEMBER_CHARGE_CNO::iterator it;
	for(it = m_mapMemberCharge1.begin(); it != m_mapMemberCharge1.end(); ++it)
	{		
		int nCol = 0;
		m_lstMain.MyCheckAddItem(nCol++, (*it).second->bView, "노출", 45, DT_CENTER, TRUE);
		m_lstMain.MyAddItem(nCol++,(*it).second->strMemCompany, "요금명", 170, FALSE, DT_LEFT);			
		m_lstMain.MyAddItem(nCol++,(*it).second->dtRegister.Format("%Y-%m-%d"), "등록일", 60, FALSE, DT_LEFT);
		m_lstMain.MyAddItem(nCol++,LF->GetMyNumberFormat((*it).second->nCusCount), "고객수", 40, FALSE, DT_RIGHT);
		m_lstMain.MyAddItem(nCol++,LF->GetMyNumberFormat( (*it).second->nChargeCount ), "요금갯수", 40, FALSE, DT_RIGHT);
		CMyXTPGridRecord *pRecord =m_lstMain.MyAddItem(nCol++,(*it).second->strMemo, "내용", 150, FALSE, DT_LEFT);		
		m_lstMain.InsertItemDataLong((*it).second->nMemCNo);
		m_lstMain.InsertItemDataLong2((*it).second->nCompany);
		m_lstMain.InsertItemDataLong3((*it).second->nChargeCount);

		m_lstMain.InsertItemDataString((*it).second->strMemCompany);
		m_lstMain.InsertItemDataString2((*it).second->strMemo);
		m_lstMain.EndItem();

		if(m_nMemCNo == (*it).second->nMemCNo)
			nSelectRow = nRow;
		nRow++;
	}

	m_lstMain.Populate();
	m_lstMain.SetSelectedRow(nSelectRow);

}



void CChargeHistoryMemDlg::RefreshSubCharge()
{	
	if(m_cmbViewType.GetCurSel() == 0)
		m_cmbViewType.SetCurSel(1);


	m_lstSub.DeleteAllColumns();


	if(m_lstSub.GetRecords()->GetCount() > 0)
		m_lstSub.DeleteAllItem();

	if(m_lstMain.GetRecords()->GetCount() == 0)
		return;

	long nMemCNo = m_lstMain.GetSelectedRecord(0)->GetItemDataLong();
	long nChargeInputCount = m_lstMain.GetSelectedRecord(0)->GetItemDataLong3();
	if(nChargeInputCount > 300000)
	{
		MessageBox("요금등록이 3만개 이상은 요금창으로 작업하세요");
		return;
	}

	CMkCommand pCmd(m_pMkDb, "select_history_charge_sub");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter( m_nCompany);
	pCmd.AddParameter(nMemCNo);

	pRs.Execute(&pCmd);
	COleDateTime dtChangeTime;
	m_lstSub.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstSub.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstSub.GetReportHeader()->AllowColumnReorder(FALSE);
	m_lstSub.AllowEdit(TRUE);

	long nMemCNoA, nType, nStartID, nDestID,nCompany, 
		nMotoCharge, nDamaCharge, nBonggoCharge, nTruckCharge;
	CString strStartSido, strStartGugun, strStartDong, strDestSido, strDestGugun, strDestDong, strType;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nMemCNo", nMemCNoA);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("sType", strType);
		pRs.GetFieldValue("nStartID", nStartID);
		pRs.GetFieldValue("nDestID", nDestID);

		pRs.GetFieldValue("nMotoCharge", nMotoCharge);
		pRs.GetFieldValue("nDamaCharge", nDamaCharge);
		pRs.GetFieldValue("nBonggoCharge", nBonggoCharge);
		pRs.GetFieldValue("nTruckCharge", nTruckCharge);		

		pRs.GetFieldValue("sStartSido", strStartSido);		
		pRs.GetFieldValue("sStartGugun", strStartGugun);		
		pRs.GetFieldValue("sStartDong", strStartDong);		

		pRs.GetFieldValue("sDestSido", strDestSido);		
		pRs.GetFieldValue("sDestGugun", strDestGugun);		
		pRs.GetFieldValue("sDestDong", strDestDong);		

		int nCol = 0;
		m_lstSub.MyAddItem(nCol++, LF->GetMyNumberFormat(i + 1), "No", 30, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(nCol++, strType, "구분", 45, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(nCol++, strStartSido, "시", 35, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(nCol++, strStartGugun, "출발구", 50, FALSE, DT_LEFT);		
		m_lstSub.MyAddItem(nCol++, strStartDong, "출발동", 60, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(nCol++, "->", "->", 27, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(nCol++, strDestSido, "시", 35, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(nCol++, strDestGugun, "도착구", 50, FALSE, DT_LEFT);		
		m_lstSub.MyAddItem(nCol++, strDestDong, "도착동", 60, FALSE, DT_LEFT);

		m_lstSub.MyAddItem(nCol++, LF->GetMyNumberFormat(nMotoCharge), "오토", 50, TRUE, DT_RIGHT);
		m_lstSub.MyAddItem(nCol++, LF->GetMyNumberFormat(nDamaCharge), "다마", 50, TRUE, DT_RIGHT);
		m_lstSub.MyAddItem(nCol++, LF->GetMyNumberFormat(nBonggoCharge), "봉고", 50, TRUE, DT_RIGHT);
		m_lstSub.MyAddItem(nCol++, LF->GetMyNumberFormat(nTruckCharge), "트럭", 50, TRUE, DT_RIGHT);

		m_lstSub.InsertItemDataLong(nStartID);		
		m_lstSub.InsertItemDataLong2(nDestID);
		
		m_lstSub.EndItem();

		pRs.MoveNext();
	}

	m_lstSub.Populate();
}

void CChargeHistoryMemDlg::RefreshSubList()
{	
	m_lstSub.DeleteAllColumns();

	if(m_lstSub.GetRecords()->GetCount() > 0)
		m_lstSub.DeleteAllItem();

	CMkCommand pCmd(m_pMkDb, "select_history_charge_member_sub2");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter( m_nCompany);
	pCmd.AddParameter(m_nMemCNo);
	
	pRs.Execute(&pCmd);
	COleDateTime dtChangeTime;

	m_lstSub.GetReportHeader()->AllowColumnResize(FALSE);
	m_lstSub.GetReportHeader()->AllowColumnRemove(FALSE);
	m_lstSub.GetReportHeader()->AllowColumnReorder(FALSE);
	m_lstSub.AllowEdit(FALSE);

	long nCNo, nMemCNo;
	CString strCompany, strDepart, strName, strTel1, strMobile, strDong, strManager;
	COleDateTime dtRegister;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCNo", nCNo);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sDepart", strDepart);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("sTel1", strTel1);
		pRs.GetFieldValue("sMobile", strMobile);
		pRs.GetFieldValue("sDong", strDong);
		pRs.GetFieldValue("dtRegister", dtRegister);
		pRs.GetFieldValue("nMemCNo", nMemCNo);		

		m_lstSub.MyAddItem(0, strCompany, "회사명", 100, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(1, strDepart, "부서명", 90, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(2, strName, "담당자", 90, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(3, LF->GetDashPhoneNumber(strTel1), "대표번호", 80, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(4, LF->GetDashPhoneNumber(strMobile), "휴대폰", 80, FALSE, DT_LEFT);
		m_lstSub.MyAddItem(5, strDong, "해당동", 80, FALSE, DT_LEFT);		
		m_lstSub.MyAddItem(6, dtRegister.Format("%y-%m-%d"), "등록일", 90, FALSE, DT_LEFT);
		m_lstSub.InsertItemDataLong(nCNo);		
		m_lstSub.InsertItemDataLong2(nMemCNo);		
		m_lstSub.EndItem();

		pRs.MoveNext();
	}

	m_lstSub.Populate();

}

void CChargeHistoryMemDlg::OnBnClickedChargeListInput()
{
	BOOL bSectionCharge = TRUE;
	if(m_nCNo <= 0) // 임시 신규고객이면 일단 히스토리에만 넣고 금액만 계산하게끔 작업
	{
		InsertChargeMember(m_nMemCNo);

		if(MessageBox("요금계산을 다시하시겠습니까? ", "확인", MB_YESNO ) == IDYES )
			bSectionCharge = TRUE;
		if(m_pWnd)
		{						
			m_pWnd->SendMessage(WM_USER+6005, (WPARAM)m_nMemCNo, (LPARAM)bSectionCharge);
			OnCancel();
		}
	}
	else
	{
		InsertChargeMember(m_nMemCNo);
	}
}

void CChargeHistoryMemDlg::InsertChargeMember(long nMemCNo, BOOL bDBApply)
{
	CMkCommand pCmd(m_pMkDb, "select_history_charge_member_update2");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(nMemCNo);
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(m_nCompany);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);	
	pRs.Execute(&pCmd);

	if(bDBApply)
		return;

	int nOUTPUT = 0;
	pPar->GetValue(nOUTPUT);
	if(nOUTPUT == 200)
	{
		m_nResult = REGISTER_CUSOMER;
		MessageBox("등록되었습니다.","확인", MB_ICONINFORMATION);
		OnOK();
	}
	else if (nOUTPUT == 100)
	{
		MessageBox("이미 등록되어 있습니다.", "확인", MB_ICONINFORMATION);

	}
	else
		MessageBox("등록되지 않았습니다.", "확인", MB_ICONINFORMATION);
}

void CChargeHistoryMemDlg::SetCNoPopup(long nMemCNo, long nCNo, long nCompany, CWnd *pWndCallBack)
{
 	RefreshServer();

	m_pWnd = pWndCallBack;
	m_nCompany = nCompany;
	m_nMemCNo = nMemCNo;
	m_nInitMemCNo = nMemCNo;
	m_nCNo = nCNo;
	CMkCommand pCmd(m_pMkDb, "select_customer_one_2011");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(nCNo);
	pCmd.AddParameter(nCompany);
	pRs.Execute(&pCmd);
	CString strCompany, strDepart, strManager, strPhone, strDisplayDong;
	CString strAddress, strDetail, strMemo, strUserID, strMobile, sHistoryName;
	long nDongID, nPosX, nPosY,  nGNo, nDBMemCNo = 0;

	MAP_MEMBER_CHARGE_CNO::iterator itMemCNo;
	for(int i =0; i < pRs.GetRecordCount(); i++)
	{		
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sDepart", strDepart);
		pRs.GetFieldValue("sName", strManager);
		pRs.GetFieldValue("sTel1", strPhone);
		pRs.GetFieldValue("nDongIDA", nDongID);

		pRs.GetFieldValue("nPosXA", nPosX);
		pRs.GetFieldValue("nPosYA", nPosY);
		pRs.GetFieldValue("sAddressA", strAddress);
		pRs.GetFieldValue("sLocationA", strDetail);
		pRs.GetFieldValue("sMemo", strMemo);
		pRs.GetFieldValue("sUserID", strUserID);
		pRs.GetFieldValue("nCustDisplayCharge", nDBMemCNo);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("sMobile", strMobile);

	   	itMemCNo = m_mapMemberCharge1.find(nMemCNo);
		if(m_mapMemberCharge1.end() != itMemCNo)
			sHistoryName = (*itMemCNo).second->strMemCompany; //->second->sMemCompany;
		else
			sHistoryName = "";

		m_edtCompany.SetWindowText(strCompany);
		m_edtTel.SetWindowText(LF->GetDashPhoneNumber(strPhone));
		m_edtMobile.SetWindowText(LF->GetDashPhoneNumber(strMobile));
		m_edtDepart.SetWindowText(strDepart);
		m_edtName.SetWindowText(strManager);		
		m_edtHistoryName.SetWindowText(sHistoryName);

		pRs.MoveNext();
	}
	pRs.Close();

	
	if(nDBMemCNo > 0 && m_nMemCNo <= 0)
		m_nMemCNo = nDBMemCNo;
	
	
	m_lstMain.SetMemCNo(m_nMemCNo);
	m_lstSub.SetMemCNo(nCNo);

	RefreshMainList();
	RefreshSubList();

	this->ShowWindow(SW_SHOW);

}


void CChargeHistoryMemDlg::NewCharge()
{
	
	CChangeHistoryNameDlg dlg;
	if( dlg.DoModal() == IDCANCEL)
		return;
	CString strAddName = "";
	CString strEtc = "";

	strAddName = dlg.m_sChargeEtc;
	strEtc = dlg.m_sChargeName;
	
		
	if(m_nCNo <= 0)
	{
		MessageBox("고객이 입력되지  않은거 같습니다 창을 닫고 다시 시도하세요",
			"확인", MB_ICONINFORMATION);
		return;
	}

	CMkCommand pCmd(m_pMkDb, "select_history_charge_member_insert2");
	CMkRecordset pRs(m_pMkDb);
	pCmd.AddParameter(0);
	pCmd.AddParameter(m_nCompany);
	pCmd.AddParameter(m_ci.m_strName);
	CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *pParString = pCmd.AddParameter(typeString, typeOutput, strAddName.GetLength(), strAddName);
	CMkParameter *pParString2 = pCmd.AddParameter(typeString, typeOutput, strEtc.GetLength(), strEtc);
	pRs.Execute(&pCmd);

	CString sChargeCompany = "";
	long nOUTPUT = 0;
	pPar->GetValue(nOUTPUT);
	pParString->GetValue(sChargeCompany);
	if(nOUTPUT == 100)
	{
		CString sTemp = ""; sTemp.Format("%s 에 등록되어 있습니다.", sChargeCompany );
		MessageBox(sTemp, "확인", MB_ICONINFORMATION);
		return;
	}

	LU->LoadMemberCharge();

	// 로드해서 새로갱신하는거 확인

}


void CChargeHistoryMemDlg::DeleteCharge()
{
	if( m_lstMain.GetSelectedCount() <= 0)
	{
		LF->MsgBox("수정할 아이템을 선택하여 주세요");
		return;
	}

	if( m_lstMain.GetSelectedCount() > 0)
	{
		if(MessageBox("개별 요금을 정말로 삭제하시겠습니까?(※고객은 삭제안됨)" , "확인",  MB_YESNO) == IDNO)
			return;		
	}

	for(int nItem =0;  nItem < m_lstMain.GetSelectedCount(); nItem++)
	{	
		long nMemCNo = m_lstMain.GetSelectedRecord(nItem)->GetItemDataLong();
		CMyXTPGridRecord *pRecord =  (CMyXTPGridRecord *)m_lstMain.GetSelectedRecord(nItem);

		CMkCommand pCmd(m_pMkDb, "select_history_charge_member_delete");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(nMemCNo);
		pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		CMkParameter *pParString = pCmd.AddParameter(typeString, typeOutput, 20, "");
		pRs.Execute(&pCmd);
		int nOUTPUT = 0; CString sDeleteCompany = "";
		pPar->GetValue(nOUTPUT);
		pParString->GetValue(sDeleteCompany);
		if(nOUTPUT == 100)
		{
			CString sTemp = ""; sTemp.Format("%s 의 데이터가 없어 삭제못했습니다. ", sDeleteCompany);
			MessageBox(sTemp, "확인", MB_ICONINFORMATION);
			return;
		}	
		pRecord->Delete();


		MAP_MEMBER_CHARGE_CNO::iterator it;
		it = m_mapMemberCharge1.find(nMemCNo);
		if(it != m_mapMemberCharge1.end() )
		{
			if( (*it).second )
				delete (*it).second;

			m_mapMemberCharge1.erase(it);
		}

	}


	m_lstMain.Populate();

	m_lstSub.DeleteAllItem();
	m_lstSub.Populate();


}
void CChargeHistoryMemDlg::OnModifyCharge()
{
	if( m_lstMain.GetSelectedCount() <= 0)
	{
		LF->MsgBox("수정할 아이템을 선택하여 주세요");
		return;
	}

	CString sChargeName = m_lstMain.GetSelectedRecord(0)->GetItemSValue(0);
	CString sEtc = m_lstMain.GetSelectedRecord(0)->GetItemSValue(4);
	ModifyCharge(sChargeName, sEtc);
}
void CChargeHistoryMemDlg::ModifyCharge(CString sChargeName,CString sEtc)
{
	if( m_lstMain.GetSelectedCount() <= 0)
	{
		LF->MsgBox("수정할 아이템을 선택하여 주세요");
		return;
	}
	CString strAddName = "";
	CString strEtc = "";

	UpdateData()	;

	CChangeHistoryNameDlg dlg;
	dlg.m_sChargeName = sChargeName;
	dlg.m_sChargeEtc = sEtc;
	UpdateData(FALSE);
	if( dlg.DoModal() == IDCANCEL)
		return;

	strAddName =  dlg.m_sChargeName;
	strEtc = dlg.m_sChargeEtc;
	
	if(strAddName.GetLength() <= 0)
	{
		MessageBox("명칭을 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	for(int i = 0; i < m_lstMain.GetSelectedCount(); i++)
	{
		
		CMyXTPGridRecord *pRecord = m_lstMain.GetSelectedRecord(i);
		long nMemCNo = pRecord->GetItemDataLong();
		CMkCommand pCmd(m_pMkDb, "select_history_charge_name_update3");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(nMemCNo);		
		pCmd.AddParameter(pRecord->GetItemDataLong2());
		pCmd.AddParameter(strAddName);	
		pCmd.AddParameter(strEtc);	
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		pRs.Execute(&pCmd);
		int nOUTPUT = 0;
		pPar->GetValue(nOUTPUT);

		if(nOUTPUT == 100)
		{
			CString sTemp = ""; sTemp.Format("수정할 데이터가 없습니다.");
			MessageBox(sTemp, "확인", MB_ICONINFORMATION);
			return;
		}

		MAP_MEMBER_CHARGE_CNO::iterator it;
		it = m_mapMemberCharge1.find(nMemCNo);
		if(it != m_mapMemberCharge1.end())
		{
			(*it).second->strMemCompany = strAddName;
		}
		
		pRecord->GetItem(0)->SetCaption(strAddName);
		pRecord->GetItem(4)->SetCaption(strEtc);
		pRecord->SetItemDataString(strAddName);
		pRecord->SetItemDataString(strEtc);
	}
	m_lstMain.Populate();
}

void CChargeHistoryMemDlg::RefreshServer()
{
	m_bInit = TRUE;
	LU->LoadMemberCharge();
	RefreshMainList();
	m_dtInit = COleDateTime::GetCurrentTime();
	m_bInit = FALSE;
}

void CChargeHistoryMemDlg::OnNMlclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if (!pNMListView->pRow || !pNMListView->pColumn)
		return;

	long nRow = pNMListView->pRow->GetIndex();

	if(nRow < 0)
		return;

	if(m_lstMain.GetSelectedCount() <= 0)
		return;

	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)m_lstMain.GetSelectedRecord(0);
		
	if(pNMListView->pColumn->GetIndex() == 0)
	{
		long nCompany = pRecord->GetItemDataLong2();
		long nMemCNo = pRecord->GetItemDataLong();
		if(nCompany <= 0  && nMemCNo <= 0)
		{
			MessageBox("해당요금의 정보가 오류입니다 로지소프트로 문의하세요", "확인" , MB_ICONINFORMATION);
			return;
		}
		CMyCheckRecordItem *pRecordItem =  (CMyCheckRecordItem *)pRecord->GetItem(0);
		if(pRecordItem)
		{
			BOOL bCheck = pRecordItem->GetCheck();
			CMkCommand pCmd(m_pMkDb, "update_history_charge_name_view");
			CMkRecordset pRs(m_pMkDb);
			pCmd.AddParameter(nMemCNo);		
			pCmd.AddParameter(nCompany);
			pCmd.AddParameter(bCheck);			
			if(!pRs.Execute(&pCmd) )return;

			MAP_MEMBER_CHARGE_CNO::iterator itMem;
			itMem = m_mapMemberCharge1.find(nMemCNo);
			if(m_mapMemberCharge1.end() != itMem)
				itMem->second->bView = bCheck;

		}	

		return;


		
	}

	CString sChargeName = "", sEtc = "";
	sChargeName = pRecord->GetItemSValue(0);
	sEtc = pRecord->GetItemSValue(5);

	m_edtChargeName.SetWindowText(sChargeName);
	m_edtChargeEtc.SetWindowText(sEtc);
	m_nMemCNo = pRecord->GetItemDataLong();

	if(m_cmbViewType.GetCurSel() == 0 )
		RefreshSubList();
	else
		RefreshSubCharge();

	*pResult = 0;
}
void CChargeHistoryMemDlg::OnNMlRClkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if (!pNMListView->pRow || !pNMListView->pColumn)
		return;

	CPoint point;
	::GetCursorPos(&point);

	OnContextMenu(this, point);
}
void CChargeHistoryMemDlg::OnNMlRClkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if (!pNMListView->pRow || !pNMListView->pColumn)
		return;

	CPoint point;
	::GetCursorPos(&point);

	OnContextMenu(this, point);
}


void CChargeHistoryMemDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	if (!pNMListView->pRow || !pNMListView->pColumn)
		return;

	long nRow = pNMListView->pRow->GetIndex();

	if(nRow < 0)
		return;

	if(m_lstMain.GetSelectedCount() <= 0)
		return;

	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)m_lstMain.GetSelectedRecord(0);

	if(pRecord == NULL)
		return;

	CString sChargeName = pRecord->GetItemSValue(0);
	CString sEtc = pRecord->GetItemSValue(2);
	ModifyCharge(sChargeName, sEtc);

	*pResult = 0;
}



void CChargeHistoryMemDlg::OnEnChangeMainSearchEdit()
{
	CString strMainSearch = "";
	m_edtMainSearch.GetWindowText(strMainSearch);
	if(strMainSearch.GetLength() <= 0)
		m_lstMain.ShowAllRow();
	else
		m_lstMain.Filter(strMainSearch,0, -1, "-", FALSE);
}

void CChargeHistoryMemDlg::OnEnChangeSubSearchEdit()
{
	CString strSubSearch = "";
	m_edtSubSearch.GetWindowText(strSubSearch);

	if(strSubSearch.GetLength() <= 0)
		m_lstSub.ShowAllRow();
	else
		m_lstSub.Filter(strSubSearch);
}

void CChargeHistoryMemDlg::OnBnClickedChargeViewButton()
{
	CString strMemName = "";

	MAP_MEMBER_CHARGE_CNO::iterator it;
	it = m_mapMemberCharge1.find(m_nMemCNo);
	if(it != m_mapMemberCharge1.end() )
		strMemName = (*it).second->strMemCompany;
	
	((CMainFrame*)AfxGetMainWnd())->ViewCharge();

	if(((CMainFrame*)AfxGetMainWnd())->m_pChargeDongDlg)
	{
		((CMainFrame*)AfxGetMainWnd())->
			m_pChargeDongDlg->SetHTypeViewMode(TRUE, m_nMemCNo, strMemName);
	}
}

void CChargeHistoryMemDlg::SumCharge()
{
	if( m_lstMain.GetSelectedCount() <= 0)
	{
		LF->MsgBox("수정할 아이템을 선택하여 주세요");
		return;
	}

	MessageBox("준비중입니다.");
}

void CChargeHistoryMemDlg::OnCbnSelchangeViewTypeCombo()
{
	if(m_cmbViewType.GetCurSel() == 0)
		RefreshSubList();
	else
		RefreshSubCharge();
}

void CChargeHistoryMemDlg::DeleteCustomer()
{

	if(m_cmbViewType.GetCurSel() == 1)
	{
		MessageBox("요금 리스트 타입니다. 고객타입으로 전환하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if( m_lstSub.GetSelectedCount() <= 0)
	{
		LF->MsgBox("수정할 아이템을 선택하여 주세요");
		return;
	}

	for(int nItem =0;  nItem < m_lstSub.GetSelectedCount(); nItem++)
	{	
		long nSubCNo = m_lstSub.GetSelectedRecord(nItem)->GetItemDataLong();
		CMyXTPGridRecord *pRecord =  (CMyXTPGridRecord *)m_lstSub.GetSelectedRecord(nItem);

		CMkCommand pCmd(m_pMkDb, "select_history_charge_member_sub_delete3");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(nSubCNo);
		pCmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);		
		pCmd.AddParameter(m_nMemCNo);
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
		CMkParameter *pParString = pCmd.AddParameter(typeString, typeOutput, 20, "");
		
		pRs.Execute(&pCmd);
		int nOUTPUT = 0; CString strDeleteCompany = "";
		pPar->GetValue(nOUTPUT);
		pParString->GetValue(strDeleteCompany);

		if(nOUTPUT >= 1000)
		{
			MessageBox("요금제에 등록된 고객이 없습니다. 요금제까지 삭제하여주시기 바랍니다.", 
				"확인",MB_ICONINFORMATION);
			nOUTPUT -= 1000;
		}

		if(nOUTPUT == 100)
		{
			CString strTemp = ""; strTemp.Format("%s 의 데이터가 없어 삭제못했습니다. ", strDeleteCompany);
			MessageBox(strTemp, "확인", MB_ICONINFORMATION);
			return;
		}

		pRecord->Delete();
	}

	m_lstSub.Populate();
}

void CChargeHistoryMemDlg::OnBnClickedOtherCustomerSearchBtn()
{

	NewCustomer();
	/*CSearchCustomerDlg dlg;
	dlg.m_nCompany = m_nCompany;
	dlg.m_bTypeCustomerChange = TRUE;
	if( dlg.DoModal() == IDOK)
	{
		CString sMemberChargeName = "";

		if(dlg.m_nReturnMemCNo > 0)
		{
			MAP_MEMBER_CHARGE_CNO::iterator it;
			it = m_mapMemberCharge1.find(dlg.m_nReturnMemCNo);
			if(it != m_mapMemberCharge1.end() )
			{
				sMemberChargeName = (*it).second->sMemCompany;
				m_nInitMemCNo = dlg.m_nReturnMemCNo;
			}
		}		

		m_edtChargeName.SetWindowText(dlg.m_sReturnCustomer);
		m_edtTel.SetWindowText(dlg.m_sReturnTel);
		m_edtChargeName.SetWindowText(sMemberChargeName);
		m_edtMobile.SetWindowText(LF->GetDashPhoneNumber(dlg.m_sReturnHP));
		m_edtDepart.SetWindowText(dlg.m_sReturnDept);
		m_edtName.SetWindowText(dlg.m_sReturnName);

		m_nCNo = dlg.m_nReturnCNo;


	}*/

}


void CChargeHistoryMemDlg::NewCustomer()
{
	if(m_cmbViewType.GetCurSel() == 1)
	{
		MessageBox("요금 리스트 타입니다. 고객타입으로 전환하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CSearchCustomerDlg dlg;
	dlg.m_nCompany = m_nCompany;
	if( dlg.DoModal() == IDOK)
	{
		CString strCNoList = dlg.m_strCNoList;
		long nOUTPUT = 0;
		CMkCommand pCmd(m_pMkDb, "select_history_members_insert");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(m_nMemCNo);
		pCmd.AddParameter(m_nCompany);		
		pCmd.AddParameter(strCNoList);		
		CMkParameter *pPar = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);		
		if(! pCmd.Execute()) return;

		pPar->GetValue(nOUTPUT);
		if(nOUTPUT == 100 )
		{
			MessageBox("개별요금이 없습니다. 개별요금을 신규로 만들거나 다른 개별요금을 선택하여 주세요", 
				"확인", MB_ICONINFORMATION);
			return;
		}

		MessageBox("해당 고객(들)을 개별요금으로 편입하였습니다.", "확인", MB_ICONINFORMATION);
		RefreshSubList();
		return;
	}
	
}
void CChargeHistoryMemDlg::ChargeItemDelete()
{
	if(m_cmbViewType.GetCurSel() == 0)
	{
		MessageBox("고객 리스트 타입니다. 요금타입으로 전환하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(  m_lstSub.GetSelectedCount() <= 0 )
	{
		MessageBox("삭제할 요금을 선택하여 주세요", "확인", MB_ICONINFORMATION);
		return;
	}	
	long nMemCNo = m_lstMain.GetSelectedRecord(0)->GetItemDataLong();
	vector <CMyXTPGridRecord*> vecRecord;
	for(int i = 0; i < m_lstSub.GetSelectedCount(); i++)
	{
		CMyXTPGridRecord *pRecord = m_lstSub.GetSelectedRowsGetAtGetRecord(i);
		long nStartID = pRecord->GetItemDataLong();
		long nDestID = pRecord->GetItemDataLong2();

		CMkCommand pCmd(m_pMkDb, "delete_history_charge_item2011");
		CMkRecordset pRs(m_pMkDb);
		pCmd.AddParameter(nMemCNo);
		pCmd.AddParameter(m_nCompany);
		pCmd.AddParameter(nStartID);
		pCmd.AddParameter(nDestID);		
		pCmd.AddParameter(m_chkShuttle.GetCheck());		
		pRs.Execute(&pCmd);
			
		vecRecord.push_back(pRecord);
	}
	if(m_chkShuttle.GetCheck())
	{
		RefreshSubCharge();
	}
	else
	{
		vector <CMyXTPGridRecord*>::iterator it;
		for(it = vecRecord.begin(); it != vecRecord.end(); ++ it)
		{
			(*it)->Delete();
		}
	}
	
	m_lstSub.Populate();
}


void CChargeHistoryMemDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rectMain = NULL, rectSub = NULL;
	
	m_lstMain.GetWindowRect(&rectMain);
	m_lstSub.GetWindowRect(&rectSub);
	BCMenu rMenu;
	if(rectMain.PtInRect(point))
	{	
		rMenu.LoadMenu(IDR_GROUP_MENU2);		
		BCMenu* pRMenu = (BCMenu*)rMenu.GetSubMenu(0);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else if (rectSub.PtInRect(point))
	{		
		rMenu.LoadMenu(IDR_GROUP_MENU3);	
		BCMenu* pRMenu = (BCMenu*)rMenu.GetSubMenu(0);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

}


void CChargeHistoryMemDlg::OnReportValueChanged(NMHDR*  pNotifyStruct, LRESULT* /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
	ASSERT(pItemNotify != NULL);

	try
	{
		long nCharge = 0, nDestDongID = 0, nCompany = 0;
		CMyXTPGridRecord  *pRecord = NULL;
		CString sError= "";

		if (!pItemNotify->pRow || !pItemNotify->pColumn)
			return;

		if(pItemNotify->pColumn->GetIndex() <= 4)
			return;

		CLMyXTPGridRecordItemText *pItemText = (CLMyXTPGridRecordItemText *)pItemNotify->pItem;

		CString strNewData = pItemText->GetValue();
		if(strNewData.GetLength() == 0)
			return;
		if(!LF->IsStringDigit(strNewData))
		{
			pItemText->OldValueChange();			
			throw("숫자를 넣어주세요");		
		}

		nCharge = atol(strNewData);
		if(nCharge > 5000000 || nCharge < 0)
		{
			pItemText->OldValueChange();
			throw("금액이 너무 많거나 적습니다. ");
		}

		pRecord = (CMyXTPGridRecord*)pItemNotify->pRow->GetRecord();		


		long nStartID = pRecord->GetItemDataLong();
		long nDestID = pRecord->GetItemDataLong2();
		
		int nCarType = 0;

		switch(pItemNotify->pItem->GetIndex())
		{
		case 9:
			nCarType = 0;
			break;
		case 10:
			nCarType = 1;
			break;
		case 11:
			nCarType = 2;
			break;
		case 12:
			nCarType = 3;
			break;

		}

		/*CMkCommand pCmd(m_pMkDb, " update_history_charge_item2");
		pCmd.AddParameter(m_nMemCNo);		
		pCmd.AddParameter(m_nCompany);				
		pCmd.AddParameter(nStartID);
		pCmd.AddParameter(nDestID);
		pCmd.AddParameter(nCharge);
		pCmd.AddParameter(nCarType);		
		pCmd.AddParameter(m_chkShuttle.GetCheck());		*/
		long nStartDestType = -1;
		
		CPOIUnit *pStartPoiUnit = m_poiNew.GetDongPOI(nStartID);
		CPOIUnit *pDestPoiUnit = m_poiNew.GetDongPOI(nDestID);

		int nStartType = 0, nDestType = 0;
		nStartType = LF->GetChargeDongTypeInfo(nStartID);
		nDestType = LF->GetChargeDongTypeInfo(nDestID);
		if(nStartType <= -1  && nDestType <= -1)
		{
			MessageBox("출발지 타입및 도착지 타입의 데이터가 불일치 합니다 로지소프트로 문의하세요 ", 
				"확인" , MB_ICONINFORMATION);
				return;
		}
		nStartDestType = LF->GetChargeType(nStartType, nDestType);
		

		CMkCommand pCmd(m_pMkDb, "insert_charge_history_data");
		pCmd.AddParameter(m_nCompany);				
		pCmd.AddParameter(nStartDestType);
		pCmd.AddParameter(nStartID);
		pCmd.AddParameter(nDestID);
		pCmd.AddParameter(nCharge);		
		pCmd.AddParameter(m_chkShuttle.GetCheck());		
		pCmd.AddParameter(nCarType);				
		pCmd.AddParameter(m_nMemCNo);		
		if(!pCmd.Execute()) return;

		if(m_chkShuttle.GetCheck())
			RefreshSubCharge();
		else
			pItemText->SetCaption(LF->GetMyNumberFormat(nCharge));

	}
	catch (CString s)
	{
		MessageBox(s, "확인", MB_ICONINFORMATION);		
		pItemNotify->pItem->SetCaption("");
	}
	catch (char *e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);		
	}
	//	
}

void CChargeHistoryMemDlg::OnCancel()
{
	ReinitData();

	CMyDialog::OnCancel();
}
void CChargeHistoryMemDlg::ReinitData()
{
	m_nInitMemCNo = 0;
	m_nMemCNo = 0;
	m_nCompany = 0;
	m_nResult = 0;
	m_edtCompany .SetWindowText("");
	m_edtTel .SetWindowText("");
	m_edtMobile .SetWindowText("");
	m_edtDepart .SetWindowText("");
	m_edtName .SetWindowText("");
	m_edtChargeName .SetWindowText("");
	m_edtChargeEtc .SetWindowText("");
	m_edtHistoryName .SetWindowText("");
	m_cmbViewType.SetCurSel(0);
	m_chkShuttle.SetCheck(TRUE);
	m_pWnd = NULL;
	m_edtMainSearch.SetWindowText("");
	m_edtSubSearch.SetWindowText("");

	

}

