// RiderCreditDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderCreditDlg.h"



// CRiderCreditDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderCreditDlg, CMyDialog)
CRiderCreditDlg::CRiderCreditDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderCreditDlg::IDD, pParent)
	, m_dtDate(COleDateTime::GetCurrentTime())
	, m_dtTime(COleDateTime::GetCurrentTime())
{
}

CRiderCreditDlg::~CRiderCreditDlg()
{
}

void CRiderCreditDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);

	DDX_Control(pDX, IDC_CHARGE_EDIT, m_ChargeEdt);
	DDX_Control(pDX, IDC_MEMO_EDIT, m_MemoEdt);
	DDX_Control(pDX, IDC_SUM_STATIC, m_SumStc);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctlDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_ctlTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtTime);
}


BEGIN_MESSAGE_MAP(CRiderCreditDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_BN_CLICKED(IDC_INPUT_BTN, OnBnClickedInputBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DELETE, OnDelete)
END_MESSAGE_MAP()


// CRiderCreditDlg 메시지 처리기입니다.

BOOL CRiderCreditDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_List.InsertColumn(0, "순번", LVCFMT_LEFT, 30);
	m_List.InsertColumn(1, "날짜", LVCFMT_LEFT, 80); 
	m_List.InsertColumn(2, "적요", LVCFMT_LEFT, 150);
	m_List.InsertColumn(3, "금액", LVCFMT_LEFT, 60);

	m_List.Populate();

	char buffer[20];
	SetWindowText(m_sRName + "(" + itoa(m_nRNo, buffer, 10) + ")");

	OnBnClickedRefreshBtn();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderCreditDlg::OnBnClickedRefreshBtn()
{
	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_credit_log");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);

	if(!pRs.Execute(&pCmd)) return;

	char buffer[20];
	long nCharge, nID, nChargeSum = 0, nIndex;
	CString sMemo;
	COleDateTime dtGenerate, dtDeleted;
	COleDateTime dtDeleteCompare = COleDateTime(2000, 1, 1, 1, 1, 1);
 
	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nIndex", nIndex);
		pRs.GetFieldValue("nCharge", nCharge);
		pRs.GetFieldValue("dtGenerate", dtGenerate);
		pRs.GetFieldValue("sMemo", sMemo);
		pRs.GetFieldValue("dtDeleted", dtDeleted);
		pRs.GetFieldValue("nID", nID);

		if(nID < 1) 
			nChargeSum += nCharge;


		m_List.InsertItem(i, itoa(i, buffer, 10));
		m_List.SetItemText(i, 1, dtGenerate.Format("%m-%d %H:%M"));
		m_List.SetItemText(i, 2, sMemo);
		m_List.SetItemText(i, 3, LF->GetMyNumberFormat(nCharge));

		m_List.SetItemLong(i, nIndex);

		pRs.MoveNext();
	}
 
	m_SumStc.SetWindowText("* 합계 : " + LF->GetMyNumberFormat(nChargeSum) + " 원");
    m_List.Populate();
}

void CRiderCreditDlg::OnBnClickedInputBtn()
{
	UpdateData(TRUE);

	COleDateTime dtCur;
	dtCur.SetDateTime(m_dtDate.GetYear(), m_dtDate.GetMonth(), m_dtDate.GetDay(),
					m_dtDate.GetHour(), m_dtDate.GetMinute(), m_dtDate.GetDay());

	CMkCommand pCmd(m_pMkDb, "insert_rider_credit_1");

	CString sCharge; m_ChargeEdt.GetWindowText(sCharge);
	CString sMemo; m_MemoEdt.GetWindowText(sMemo); 

	if(sCharge.GetLength() == 0){MessageBox("금액을 입력하세요", "확인", MB_ICONINFORMATION);return;};
	if(sMemo.GetLength() == 0){MessageBox("적요를 입력하세요", "확인", MB_ICONINFORMATION);return;}

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nRNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sCharge));
	pCmd.AddParameter(typeString, typeInput, sMemo.GetLength(), sMemo);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur);

	if(!pCmd.Execute()) return;
	
	OnBnClickedRefreshBtn();
}

void CRiderCreditDlg::OnBnClickedDeleteBtn()
{
	long nItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(nItem == -1)
		return;

	CMkCommand pCmd(m_pMkDb, "delete_rider_credit");
	pCmd.AddParameter(m_List.GetItemLong(nItem));

	if(pCmd.Execute()) OnBnClickedRefreshBtn();
}

void CRiderCreditDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_List.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMenu rMenu;
		rMenu.LoadMenu(IDR_CONTEXT_MENU);
		CMenu *pRMenu=rMenu.GetSubMenu(3);
		pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
	}	
}

void CRiderCreditDlg::OnDelete()
{
	OnBnClickedDeleteBtn();
}
