// CVRRiderLogList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "VRRiderLogListDlg.h"
#include ".\vrriderloglistdlg.h"


// CVRRiderLogListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVRRiderLogListDlg, CMyDialog)
CVRRiderLogListDlg::CVRRiderLogListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CVRRiderLogListDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_nRNo = 0;
	m_sAccount = "";
}

CVRRiderLogListDlg::~CVRRiderLogListDlg()
{
}

void CVRRiderLogListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_List);
	DDX_Text(pDX, IDC_ACCOUNT_EDIT, m_sAccount);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_FromDT);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_ToDT);	
	DDX_Control(pDX, IDC_DATE_BTN, m_DateBtn);
	DDX_Control(pDX, IDC_RIDER_SELECT_COMBO, m_cmbRider);
	
}


BEGIN_MESSAGE_MAP(CVRRiderLogListDlg, CMyDialog)
	ON_BN_CLICKED(IDC_ONOK_BTN, OnBnClickedOnokBtn)
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CVRRiderLogListDlg::OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CVRRiderLogListDlg 메시지 처리기입니다.

void CVRRiderLogListDlg::OnBnClickedOnokBtn()
{
	OnOK();
}

BOOL CVRRiderLogListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	m_DateBtn.InitDateButton(&m_FromDT, &m_ToDT);
	m_DateBtn.OnMenuToday();
	m_cmbRider.SetCurSel(0);
	UpdateData();

	m_List.InsertColumn(0, "No.", LVCFMT_CENTER, 35);
	m_List.InsertColumn(1, "작업일", LVCFMT_LEFT, 150);
	m_List.InsertColumn(2, "지사명", LVCFMT_LEFT, 90);
	m_List.InsertColumn(3, "사번", LVCFMT_LEFT, 45);
	m_List.InsertColumn(4, "작업", LVCFMT_LEFT, 75);
	m_List.InsertColumn(5, "계좌", LVCFMT_LEFT, 180);
	m_List.InsertColumn(6, "구분", LVCFMT_LEFT, 65);
	m_List.InsertColumn(7, "은행", LVCFMT_LEFT, 80);
	m_List.InsertColumn(8, "작업자", LVCFMT_LEFT, 80);
	m_List.Populate();

	RefreshList();

	return TRUE;
}

	
void CVRRiderLogListDlg::RefreshList()
{
	try
	{
		UpdateData();
		COleDateTimeSpan dtSpan;
		dtSpan = m_dtTo - m_dtFrom;
		
		if(m_sAccount.GetLength() <= 0 && dtSpan.GetDays() > 187)
		{
			MessageBox("전체검색은 6달간격으로만 조회됩니다 일자 구간을 좁히세요", "확인", MB_ICONINFORMATION);
			return;
		}

		if(m_List.GetRecords()->GetCount() > 0)
			m_List.DeleteAllItems();

	
		CString sAccount = m_sAccount;

		if(!LF->IsStringDigit(sAccount))
		{
			MessageBox("숫자가 아닙니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		
		long nData = 0;
		if(m_cmbRider.GetCurSel() == 1 && m_sAccount.GetLength() > 5)
		{
			MessageBox("기사번호가 유효한데이터가 아닙니다.", "확인", MB_ICONINFORMATION);
			return;
		}
		
		UpdateData();
		
		CMkRecordset pRs(m_pMkDb);					
		CMkCommand pCmd(m_pMkDb, "select_vraccount_rider_allotlog2");	
		
		pCmd.AddParameter( m_nCompany);		
		pCmd.AddParameter(m_nRNo);
		pCmd.AddParameter(m_sAccount);		
		pCmd.AddParameter(m_dtFrom);			
		pCmd.AddParameter(m_dtTo);			
		pCmd.AddParameter(m_cmbRider.GetCurSel());			

		if(!pRs.Execute(&pCmd)) return;

		int nIndex = 0;
		while(!pRs.IsEOF())
		{
			int nCol = 0, nType = 0;
			CString sAccount, sWID, sBankCode, sType;
			COleDateTime dtInput;
			long nOWnerCompany, nCompany, nRNo;

			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nRNo", nRNo);
			pRs.GetFieldValue("sAccount", sAccount);
			pRs.GetFieldValue("dtInput", dtInput);		
			pRs.GetFieldValue("sWID", sWID);			
			pRs.GetFieldValue("nOWnerCompany", nOWnerCompany);			
			pRs.GetFieldValue("BankCode", sBankCode);			
			pRs.GetFieldValue("nType", nType);			

			if(nType == 40)
				sType = "계좌회수";
			else if(nType == 30)
				sType = "선택할당";
			else if(nType == 20)
				sType = "자동할당";


			m_List.InsertItem(nIndex, LF->GetStringFromLong(nIndex));
			m_List.SetItemText(nIndex, 1, dtInput.Format("%Y-%m-%d %H:%M:%S"));
			m_List.SetItemText(nIndex, 2, m_ci.GetBranchName(nCompany));
			m_List.SetItemText(nIndex, 3, LF->GetStringFromLong(nRNo));
			m_List.SetItemText(nIndex, 4, sType);
			m_List.SetItemText(nIndex, 5, sAccount);
			m_List.SetItemText(nIndex, 6, nOWnerCompany == 0 ? "로지계좌" : "자체계좌");
			m_List.SetItemText(nIndex, 7, sBankCode);
			m_List.SetItemText(nIndex, 8, sWID);

			nIndex++;
			pRs.MoveNext();
		}	
		m_List.Populate();
	}
	catch (char* e)
	{
		MessageBox(e, "확인", MB_ICONINFORMATION);
		
	}
}

void CVRRiderLogListDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}
