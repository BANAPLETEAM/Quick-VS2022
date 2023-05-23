// ScheduleOrderListDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ScheduleOrderListDlg.h"
#include "RcpView.h"
#include "RcpDlg.h"
#include "ScheduleOrderDlg.h"
#include "MainFrm.h"

// CScheduleOrderListDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CScheduleOrderListDlg, CMyDialog)
CScheduleOrderListDlg::CScheduleOrderListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CScheduleOrderListDlg::IDD, pParent)
{
}

CScheduleOrderListDlg::~CScheduleOrderListDlg()
{
	((CMainFrame*)AfxGetMainWnd())->m_pScheduleOrderListDlg = NULL;
}

void CScheduleOrderListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_XTPLISTCTRL_EDIT, m_edtSearch);
	DDX_Text(pDX, IDC_XTPLISTCTRL_EDIT, m_strSearch);
}


BEGIN_MESSAGE_MAP(CScheduleOrderListDlg, CMyDialog)
	ON_CBN_SELCHANGE(IDC_XTPLISTCTRL_COMBO, OnCbnSelchangeXtplistctrlCombo)
	ON_EN_CHANGE(IDC_XTPLISTCTRL_EDIT, OnEnChangeXtplistctrlEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblClickList1)

	ON_BN_CLICKED(IDC_ADD_BTN, OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_MAKE_ORDER_JUST_BTN, OnBnClickedMakeOrderJustBtn)
	ON_BN_CLICKED(IDC_EDIT_ORDER_BTN, OnBnClickedEditOrderBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
END_MESSAGE_MAP()


// CScheduleOrderListDlg 메시지 처리기입니다.

BOOL CScheduleOrderListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();


	((CMainFrame*)AfxGetMainWnd())->m_pScheduleOrderListDlg = this;

	m_List.SetExternalControl(GetDlgItem(IDC_XTPLISTCTRL_COMBO),
		GetDlgItem(IDC_XTPLISTCTRL_EDIT),			//SetExternalControl함수의 순서중요함
		NULL);	//반드시 InsertColumn앞에 있어야함

	m_List.InsertColumn(0,"오더소속",LVCFMT_LEFT,100);
	m_List.InsertColumn(1,"예약시간",LVCFMT_CENTER, 65);
	m_List.InsertColumn(2,"생성요일",LVCFMT_LEFT,100);
	m_List.InsertColumn(3,"고객명",LVCFMT_LEFT,120);
	m_List.InsertColumn(4,"출발지",LVCFMT_LEFT,80);
	m_List.InsertColumn(5,"출발동",LVCFMT_LEFT,70);
	m_List.InsertColumn(6,"도착지",LVCFMT_LEFT,80);
	m_List.InsertColumn(7,"도착지",LVCFMT_LEFT,70);
	m_List.InsertColumn(8,"요금",LVCFMT_RIGHT,50);
	m_List.InsertColumn(9,"사용중",LVCFMT_CENTER,50);
	m_List.InsertColumn(10,"3일치생성",LVCFMT_CENTER,60);
	m_List.InsertSearchAllColumn(2);
	m_List.InsertSearchAllColumn(3);
	m_List.InsertSearchAllColumn(4);

	RefreshList();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CScheduleOrderListDlg::RefreshList()
{
	m_List.DeleteAllItems();

	long nItem = 0;

	CMkRecordset pRs2(m_pMkDb);
	CMkCommand pCmd2(m_pMkDb, "select_schedule_order_list");	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);		

	long nCompany, nTNo, nChargeSum, nNextWeekAdvance;
	CString strTime, strOName, strStart, strDest, strStartDong, strDestDong;
	BOOL bDay1, bDay2, bDay3, bDay4, bDay5, bDay6, bDay7, bUse;

	if(pRs2.Execute(&pCmd2))
	{

		while(!pRs2.IsEOF())
		{	
			pRs2.GetFieldValue("nCompany", nCompany);
			pRs2.GetFieldValue("sTime", strTime);
			pRs2.GetFieldValue("bDay1", bDay1);
			pRs2.GetFieldValue("bDay2", bDay2);
			pRs2.GetFieldValue("bDay3", bDay3);
			pRs2.GetFieldValue("bDay4", bDay4);
			pRs2.GetFieldValue("bDay5", bDay5);
			pRs2.GetFieldValue("bDay6", bDay6);
			pRs2.GetFieldValue("bDay7", bDay7);
			pRs2.GetFieldValue("sOName", strOName);
			pRs2.GetFieldValue("sSName", strStart);
			pRs2.GetFieldValue("sSDong", strStartDong);
			pRs2.GetFieldValue("sDName", strDest);
			pRs2.GetFieldValue("sDDong", strDestDong);
			pRs2.GetFieldValue("nChargeSum", nChargeSum);
			pRs2.GetFieldValue("bUse", bUse);
			pRs2.GetFieldValue("nTNo", nTNo);
			pRs2.GetFieldValue("nNextWeekAdvance", nNextWeekAdvance);

			CString strMakeWeek;
			strMakeWeek += bDay1 ? "일" : "";
			strMakeWeek += bDay2 ? "월" : "";
			strMakeWeek += bDay3 ? "화" : "";
			strMakeWeek += bDay4 ? "수" : "";
			strMakeWeek += bDay5 ? "목" : "";
			strMakeWeek += bDay6 ? "금" : "";
			strMakeWeek += bDay7 ? "토" : "";

			m_List.InsertItem(nItem, m_ci.GetBranchName(nCompany));
			m_List.SetItemText(nItem, 1, strTime);
			m_List.SetItemText(nItem, 2, strMakeWeek);
			m_List.SetItemText(nItem, 3, strOName);
			m_List.SetItemText(nItem, 4, strStart);
			m_List.SetItemText(nItem, 5, strStartDong);
			m_List.SetItemText(nItem, 6, strDest);
			m_List.SetItemText(nItem, 7, strDestDong);
			m_List.SetItemText(nItem, 8, LF->GetMyNumberFormat(nChargeSum));
			m_List.SetItemText(nItem, 9, bUse ? "사용" : "X");
			m_List.SetItemText(nItem, 10, nNextWeekAdvance > 0 ? "O" : "X");
			m_List.SetItemData(nItem, nTNo);
			m_List.SetItemLong(nItem, nCompany);
			nItem++;

			pRs2.MoveNext();
		}
		pRs2.Close();
	}

	m_List.Populate();
}

void CScheduleOrderListDlg::OnCbnSelchangeXtplistctrlCombo()
{
	OnEnChangeXtplistctrlEdit();
}

void CScheduleOrderListDlg::OnEnChangeXtplistctrlEdit()
{
	CComboBox *pCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_COMBO);
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_XTPLISTCTRL_EDIT);
	CComboBox *pTypeCombo = (CComboBox*)GetDlgItem(IDC_XTPLISTCTRL_TYPE_COMBO);

	CString strText;
	pEdit->GetWindowText(strText);
	strText.Trim();

	int nTypeData;
	if(pTypeCombo == NULL)
		nTypeData = -1;
	else
		nTypeData = (int)pTypeCombo->GetItemData(pTypeCombo->GetCurSel());

	m_List.Filter(strText, pCombo->GetCurSel(), nTypeData);
}


void CScheduleOrderListDlg::OnNMDblClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pNMListView = (XTP_NM_REPORTRECORDITEM*)pNMHDR;

	long nRow = pNMListView->pRow->GetIndex();

	if(nRow >= 0)
	{
		long nTNo = m_List.GetItemData(nRow);

		CScheduleOrderDlg dlg;
		dlg.m_nSrcTNo = nTNo;
		dlg.m_nCompany = m_List.GetItemLong(nRow);
		if(dlg.DoModal() == IDOK)
		{
			RefreshList();
		}
	}

	*pResult = 0;
}


void CScheduleOrderListDlg::OnOK()
{
	CMyDialog::OnOK();
}

void CScheduleOrderListDlg::OnBnClickedAddBtn()
{


	if(!LU->GetRcpView() )
	{
		MessageBox(
			"접수페이지로 이동후에 다시 클릭하시기 바랍니다.", 
			"확인", MB_ICONINFORMATION);
		return;
	}

	CBranchInfo *pBranchInfo =LF->GetCurBranchInfo();
	if(pBranchInfo)
	{
		LU->GetRcpView()->CreateRcpDlg(NULL, "정기오더 등록", -1, 0, "", FALSE, -10,GetTickCount(), 0, TRUE);
		RefreshList();
	}
}

void CScheduleOrderListDlg::OnBnClickedEditOrderBtn()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) 
	{

		long nCompany = m_List.GetItemLong(nItem);
		CBranchInfo *pBranchInfo = LF->GetBranchInfo(nCompany);
		if(pBranchInfo)
		{
			if(!LU->GetRcpView() )
			{
				MessageBox(
					"접수페이지로 이동후에 다시 클릭하시기 바랍니다.", 
					"확인", MB_ICONINFORMATION);
				return;
			}

			LU->GetRcpView()->CreateRcpDlg(pBranchInfo, "정기오더 수정", m_List.GetItemData(nItem), 10, 
				"", FALSE, -10,0, 0, TRUE);
			RefreshList();

		}

		
	}
}



void CScheduleOrderListDlg::OnBnClickedMakeOrderJustBtn()
{
	MessageBox("개발중입니다.");
}


void CScheduleOrderListDlg::OnBnClickedDeleteBtn()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) 
	{
		if(IDYES == MessageBox("정말 삭제하시겠습니까?", "삭제확인", MB_ICONQUESTION | MB_YESNO))
		{
			long nTNo = m_List.GetItemData(nItem);
			CMkCommand pCmd(m_pMkDb, "delete_schedule_order");
			pCmd.AddParameter(nTNo);
			if(pCmd.Execute())
			{
				MessageBox("삭제되었습니다", "확인", MB_ICONINFORMATION);
			}
		}
	}
}
