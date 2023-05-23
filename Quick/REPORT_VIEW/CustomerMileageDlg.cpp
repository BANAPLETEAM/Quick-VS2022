// CustomerMileageDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerMileageDlg.h"
#include "MileageBalanceDlg.h"
#include "RcpDlg.h"


IMPLEMENT_DYNAMIC(CCustomerMileageDlg, CMyDialog)
CCustomerMileageDlg::CCustomerMileageDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCustomerMileageDlg::IDD, pParent)
{
	m_nCNo = 0;
	m_nPersonMileage = 0;
	m_nPersonMileageType = 0;
	m_bApply =FALSE;
	m_nMileageBalance = 0;
	m_pWnd = pParent;
}

CCustomerMileageDlg::~CCustomerMileageDlg()
{
}

void CCustomerMileageDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_Report);
	DDX_Control(pDX, IDC_CHANGE_MILEAGE_EDIT, m_edtChangeMileage);
	//DDX_Control(pDX, IDC_ALLOW_COMPANY_SETTING, m_chkAllowCompanySetting);
	DDX_Control(pDX, IDC_PERCENT_COMBO, m_cmbPercent);
	DDX_Control(pDX, IDC_MILEAGE_EDIT, m_edtMileage);
	DDX_Control(pDX, IDC_MILEETC_EDIT, m_edtMileEtc);
}


BEGIN_MESSAGE_MAP(CCustomerMileageDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CHANGE_MILEAGE_BTN, OnBnClickedChangeMileageBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_INIT_MILEAGE_BTN, OnBnClickedInitMileageBtn)
	//ON_BN_CLICKED(IDC_ALLOW_COMPANY_SETTING, OnBnClickedAllowCompanySetting)
	ON_BN_CLICKED(IDC_SAVE_SETTING_BTN, OnBnClickedSaveSettingBtn)
	ON_CBN_SELCHANGE(IDC_PERCENT_COMBO, OnCbnSelchangePercentCombo)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_MILEAGE_PAY_BTN, OnBnClickedMileagePayBtn)
END_MESSAGE_MAP()


// CCustomerMileageDlg 메시지 처리기입니다.

BOOL CCustomerMileageDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	int nItem = 0;

	m_Report.InsertColumn(nItem++, "오더번호", LVCFMT_LEFT, 65);
	m_Report.InsertColumn(nItem++, "회사명", LVCFMT_LEFT, 70);
	m_Report.InsertColumn(nItem++, "고객명", LVCFMT_LEFT, 70);
	m_Report.InsertColumn(nItem++, "일자", LVCFMT_LEFT, 95);		
	m_Report.InsertColumn(nItem++, "출발지",LVCFMT_LEFT, 85);
	m_Report.InsertColumn(nItem++, "도착지",LVCFMT_LEFT, 120);
	m_Report.InsertColumn(nItem++, "상태",LVCFMT_RIGHT, 75);
	m_Report.InsertColumn(nItem++, "요금",LVCFMT_RIGHT,60);
	m_Report.InsertColumn(nItem++, "마일",LVCFMT_RIGHT,50);		
	m_Report.InsertColumn(nItem++, "마일잔액",LVCFMT_RIGHT,60);		
	m_Report.InsertColumn(nItem++, "사용자메모",LVCFMT_LEFT,140);		
	m_Report.InsertColumn(nItem++, "접수자",LVCFMT_LEFT,50);
	m_Report.InsertColumn(nItem++, "",LVCFMT_LEFT,0);
	m_Report.InsertColumn(nItem++, "",LVCFMT_LEFT,0);

	m_Report.Populate();

	if(m_nCNo <= 0)
	{
		MessageBox("신규 고객은 고객을 등록후  작업 해주세요","확인",MB_ICONINFORMATION);
		OnClose();
		return TRUE;;
	}

	RefreshList();	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCustomerMileageDlg::RefreshList()
{
	m_Report.DeleteAllItems();

	long nCompanySetting = 0;
	long nCustomerSetting = 0, nCustomerMileType = 0;
	

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_mileage_search_customer_alone_rcpdlg");	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);
	CMkParameter *parCompanySetting =pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parCustomerSetting =pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	CMkParameter *parCustomerMileType =pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	if(!pRs2.Execute(&pCmd)) return ;	

	parCompanySetting->GetValue(nCompanySetting);
	parCustomerSetting->GetValue(nCustomerSetting);
	parCustomerMileType->GetValue(nCustomerMileType);

	InitSetting(nCompanySetting, nCustomerSetting,nCustomerMileType);

	CString sWName, sStart,sDest,sCName, sUserEtc ;
	long  nTNo = 0, nCompany = 0, nMileage = 0,nMileageBalance = 0, nCol = 1, 
		nState = 0, nTotalCharge = 0, nTotalMileage = 0, nCNo = 0,nChargeSum = 0;
	char buffer[20];
	BOOL bOrder = FALSE; 
	COleDateTime dt1;

	CString sState = "";

	long nItem = 0;
	while(!pRs2.IsEOF())
	{
		long nCno = 0;
		pRs2.GetFieldValue("nOCNo", nCNo);
		pRs2.GetFieldValue("nTNo", nTNo);
		pRs2.GetFieldValue("nCompany", nCompany);
		pRs2.GetFieldValue("sCName", sCName);
		pRs2.GetFieldValue("dt1", dt1);
		pRs2.GetFieldValue("sSName", sStart);
		pRs2.GetFieldValue("sDName", sDest);
		pRs2.GetFieldValue("nChargeSum", nChargeSum);
		pRs2.GetFieldValue("nState", nState);
		pRs2.GetFieldValue("nMileage", nMileage);
		pRs2.GetFieldValue("nMileageBalance", nMileageBalance);
		pRs2.GetFieldValue("bOrder", bOrder);
		pRs2.GetFieldValue("sWName", sWName);
		pRs2.GetFieldValue("sUserEtc", sUserEtc);

		if(nState >= 30 && nState <= 35 && bOrder)
		{
			switch(nState)
			{
			case 10:
				sState = "접수";
				break;
			case 11:
				sState = "개별";
				break;
			case 30:
				sState = "배차";
				break;
			case 35:
				sState = "완료";
				break;
			case 40:
				sState = "취소";
				break;

			}

		}
		else if(!bOrder && nState > 100)
		{
			switch(nState)
			{
			case 101:
				sState = "초기화";
				break;
			case 102:
				sState = "콜수정";
				break;
			case 100:
				sState = "잔액수정";
				break;
			case 103:
				sState = "개별마일";
				break;
			case 104:
				sState = "전체마일";
				break;
			case 106:
				sState = "마일사용";
				break;
			case 107:
				sState = "마일사용취소";
				break;
			case 108:
				sState = "마일금액변경";
				break;
			case 109:
				sState = "관리자지급";
				break;
			case 110:
				sState = "사용안함";
				break;
			}

		}
		

		m_Report.InsertItem(nItem, nTNo == 0 ? "" : ltoa(nTNo, buffer,10));
		m_Report.SetItemText(nItem, nCol++, m_ci.GetBranchName(nCompany));
		m_Report.SetItemText(nItem, nCol++, sCName);
		m_Report.SetItemText(nItem, nCol++, dt1.Format("%y-%m-%d %H:%M"));
		m_Report.SetItemText(nItem, nCol++, (!bOrder && nState >= 100) ? sState : sStart);
		m_Report.SetItemText(nItem, nCol++, sDest);
		m_Report.SetItemText(nItem, nCol++, sState);
		m_Report.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nChargeSum));
		m_Report.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nMileage));
		m_Report.SetItemText(nItem, nCol++, LF->GetMyNumberFormat(nMileageBalance));	
		m_Report.SetItemText(nItem, nCol++, sUserEtc);
		m_Report.SetItemText(nItem, nCol++, sWName);
		m_Report.SetItemText(nItem, nCol++, bOrder?"1":"0");
		m_Report.SetItemText(nItem, nCol++, ltoa(nState, buffer,10));
		m_Report.SetItemData(nItem, nCNo);
		m_Report.SetItemLong(nItem++, nState);

		nCol = 1;

		nTotalCharge += nChargeSum;
		nTotalMileage += nMileage;

		pRs2.MoveNext();
	}
	pRs2.Close();
	m_Report.InsertItem(nItem, "");
	m_Report.SetItemText(nItem, 5, "합계:");
	m_Report.SetItemText(nItem, 7,LF->GetMyNumberFormat(nTotalCharge) );
	//m_Report.SetItemText(nItem, 8,LF->GetMyNumberFormat(nTotalMileage) );
	m_Report.SetItemText(nItem, 8, "");
	m_Report.SetItemData(nItem, 0 );

	m_Report.Populate();

}

void CCustomerMileageDlg::OnBnClickedChangeMileageBtn()
{
	if(!LF->POWER_CHECK(2040, "마일리지금액수정", TRUE))
		return;

	CMileageBalanceDlg dlg;
	dlg.m_nCNo = m_nCNo;

	if(dlg.DoModal() == IDOK)
	{



	/*	CString sMileage, sEtc=""; 
		m_edtChangeMileage.GetWindowText(sMileage);
		if(sMileage.GetLength() == 0)
		{
			MessageBox("수정잔액이 0원 입니다", "확인", MB_ICONINFORMATION);
			return;
		}*/

		//m_edtMileEtc.GetWindowText(sEtc);


		CString sCharge = dlg.m_sCharge;
		sCharge.Replace(",", "");
		if(!LF->IsStringDigit(sCharge))
		{
			MessageBox("숫자를 입력하세요", "확인", MB_ICONINFORMATION);
			return;
		}

		long nMileAddCharge = 0;
		if(dlg.m_nType  == 1)
			nMileAddCharge = atol(sCharge) *  -1;
		else
			nMileAddCharge = atol(sCharge);


		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "update_mileage_balance4");	
		pCmd.AddParameter(m_nCNo);
		pCmd.AddParameter(nMileAddCharge);	
		pCmd.AddParameter(m_ui.strName);
		pCmd.AddParameter(m_ui.nCompany);
		pCmd.AddParameter(dlg.m_sEtc);
		CMkParameter *pParPersonCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

		if(!pRs.Execute(&pCmd))
			MessageBox("인터넷연결이 실패되었습니다.", "확인", MB_ICONINFORMATION);
		else
		{
			long nMileageSettingCount = 0;
			pParPersonCount->GetValue(nMileageSettingCount);

			if(nMileageSettingCount > 10000000 || nMileageSettingCount < -10000000)
			{
				MessageBox("마일리지 금액 천만원을 넘을수 없습니다.", "확인", MB_ICONINFORMATION);
				return;
			}

			MessageBox("수정하였습니다.", "확인", MB_ICONINFORMATION);
			
			m_nMileageBalance = nMileageSettingCount;
			//((CRcpDlg*)m_pWnd)->m_edtMileageBalance.SetWindowText(LF->GetMyNumberFormat(m_nMileageBalance));
			m_bApply = TRUE;
			
		}
		RefreshList();
	}
}

void CCustomerMileageDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CCustomerMileageDlg::OnBnClickedInitMileageBtn()
{
	if(!LF->POWER_CHECK(2040, "마일리지금액수정", TRUE))
		return;

	if(MessageBox("마일리지를 초기화 하시겠습니까?", "확인", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{		
		MileageModify(101,0);
		RefreshList();
	}
}


void CCustomerMileageDlg::MileageModify(int nType, long nAmount)
{
	if(m_nCNo <= 0 )
	{
		MessageBox("고객이 선택되어지지 않았습니다.", "확인", MB_ICONINFORMATION);
		return;		
	}
	CString sUserEtc = "";
	m_edtMileEtc.GetWindowText(sUserEtc);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_mileage_modify3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);	
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 0);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nType);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nCompany);
	pCmd.AddParameter(typeString, typeInput, sUserEtc.GetLength(),sUserEtc);
	CMkParameter *pParPersonCount = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);


	if(!pRs.Execute(&pCmd))
		MessageBox("인터넷연결이 실패되었습니다.", "확인", MB_ICONINFORMATION);
	else
	{
		long nSettingCount = 0;
		MessageBox("수정하였습니다.", "확인", MB_ICONINFORMATION);
		pParPersonCount->GetValue(nSettingCount);
		m_nMileageBalance = 0;
		m_bApply = TRUE;
	}

}
//
//void CCustomerMileageDlg::OnBnClickedAllowCompanySetting()
//{
//	BOOL bCheck = m_chkAllowCompanySetting.GetCheck();
//
//	m_edtMileage.EnableWindow(!bCheck);
//	m_cmbPercent.EnableWindow(!bCheck);
//	if(bCheck)
//	{
//		m_cmbPercent.SetCurSel(0);
//
//	}
//
//}

void CCustomerMileageDlg::OnBnClickedSaveSettingBtn()
{
	if(!LF->POWER_CHECK(2040, "마일리지금액수정", TRUE))
		return;

	UpdateData();
	CString sMileage, sUserEtc; 
	m_edtMileage.GetWindowText(sMileage);
	m_edtMileEtc.GetWindowText(sUserEtc);
	
	sMileage.Replace(",", "");
	if( (m_cmbPercent.GetCurSel() >= 1 && m_cmbPercent.GetCurSel() <= 2) && sMileage.GetLength() == 0)
	{
		LF->MsgBox("마일리지 값을 입력하세요","확인",  MB_ICONINFORMATION );
		return;
	}
	long nMileage = atol(sMileage);

	CMkCommand pCmd(m_pMkDb, "update_customer_mileage_setting3");
	pCmd.AddParameter(m_nCNo);
	//pCmd.AddParameter(m_chkAllowCompanySetting.GetCheck());
	pCmd.AddParameter(m_cmbPercent.GetCurSel());	
	pCmd.AddParameter(nMileage);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(sUserEtc);


	if(pCmd.Execute())
	{
		MessageBox("수정되었습니다", "확인" , MB_ICONINFORMATION);
		m_bApply = TRUE;
		if(m_cmbPercent.GetCurSel() <= 2)
		{
			m_nPersonMileageType = m_cmbPercent.GetCurSel();
			if(m_cmbPercent.GetCurSel() == 1 || m_cmbPercent.GetCurSel() == 2 )
				m_nPersonMileage = nMileage;
		}
		else if(m_cmbPercent.GetCurSel() == 3)
		{
			m_nPersonMileageType = 10;
		}

		RefreshList();
	}
	else
		MessageBox("저장중 오류발생\r\n다시 시도해주세요", "확인", MB_ICONINFORMATION);

}

void CCustomerMileageDlg::InitSetting(long nCompanySetting, long nCustomerSetting,long nCustomerMileType)
{
	
	char buffer[20];
	if(nCustomerMileType == 0) 
	{
		
		this->SetWindowText("마일리지 설정 - 회사설정 적용중");
		m_edtMileage.EnableWindow(FALSE);
		m_cmbPercent.SetCurSel(0);
		
	}
	else
	{
		if(nCustomerMileType <= 2)
			m_cmbPercent.SetCurSel(nCustomerMileType);
		else
			m_cmbPercent.SetCurSel(3);

		
		this->SetWindowText("마일리지 설정 - 고객설정 적용중");
		//m_chkAllowCompanySetting.SetCheck(FALSE);
		if( nCustomerMileType == 10)
		{
			m_edtMileage.EnableWindow(FALSE);
			m_edtMileage.SetWindowText("");
		}
		else
		{
			m_edtMileage.EnableWindow(TRUE);
			m_edtMileage.SetWindowText(itoa(abs(nCustomerSetting), buffer, 10));
		}
	}

	

	
	

	//OnBnClickedAllowCompanySetting();
};

void CCustomerMileageDlg::OnCbnSelchangePercentCombo()
{
	if(m_cmbPercent.GetCurSel() == 0 || m_cmbPercent.GetCurSel() == 3)
	{
		m_edtMileage.EnableWindow(FALSE);
		m_edtMileage.SetWindowText("");
	}
	else
	{
		m_edtMileage.EnableWindow(TRUE);
	}
}

void CCustomerMileageDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CCustomerMileageDlg::OnBnClickedMileagePayBtn()
{
	if(!LF->POWER_CHECK(2040, "마일리지금액수정", TRUE))
		return;

	CString sMileage, sEtc=""; 
	m_edtChangeMileage.GetWindowText(sMileage);
	if(sMileage.GetLength() == 0)
	{
		MessageBox("마일 지급액이 0원 입니다", "확인", MB_ICONINFORMATION);
		return;
	}
	long nResult = 0;
	m_edtMileEtc.GetWindowText(sEtc);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_mileage_span");	
	pCmd.AddParameter(m_nCNo);
	pCmd.AddParameter(_ttol(sMileage));	
	pCmd.AddParameter(m_ui.strName);
	pCmd.AddParameter(m_ui.nCompany);
	pCmd.AddParameter(sEtc);
	CMkParameter *pParMileageBalance = pCmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	
	if(!pRs.Execute(&pCmd))
	{
		MessageBox("인터넷연결이 실패되었습니다.", "확인", MB_ICONINFORMATION);
		return;
	}
	else
	{
		long nBalance = 0;
		pParMileageBalance->GetValue(nBalance);
		if(nBalance < 0)
		{
			MessageBox("지급하실 금액에 비하여 잔액이 적습니다", "확인", MB_ICONINFORMATION);
			return;
		}
		else
		{
			long nMileageSettingCount = 0;
			MessageBox("수정하였습니다.", "확인", MB_ICONINFORMATION);
			
			m_nMileageBalance = nBalance;
			m_bApply = TRUE;
		}

		RefreshList();
	}
	
}
