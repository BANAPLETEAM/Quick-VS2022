// RcpPowerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpPowerDlg.h"
#include "MyReportPaintManager.h"
#include "MakeRcpPower.h"
#include "RcpPowerSetDlg.h"


// CRcpPowerDlg 대화 상자입니다.


class CRcpPowerRecord : public CXTPGridRecord
{
protected:
	class CRcpPowerRecordItemLong : public CXTPGridRecordItem
	{
	public:
		CRcpPowerRecordItemLong(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T("X"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("부분"), 1);
			GetEditOptions(NULL)->AddConstraint(_T("전체"), 2);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;		
			GetEditOptions(NULL)->AddComboButton();
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* /*pItemArgs*/, CXTPGridRecordItemConstraint* pConstraint)
		{
			if((long)pConstraint->m_dwData == 1)
			{
//				::MessageBox(NULL, "[부분]으로 변경은 불가능합니다.", "확인", MB_ICONINFORMATION);
				return;
			}

			if(((CRcpPowerRecord*)GetRecord())->m_nRole == 0 && 
				((CRcpPowerRecord*)GetRecord())->m_nCompany == m_ci.m_nCompanyCode)
			{
//				::MessageBox(NULL, "관리자는 수정이 불가능합니다.", "확인", MB_ICONINFORMATION);
				return;
			}

			m_nValue = (BOOL)pConstraint->m_dwData;
			((CRcpPowerRecord*)GetRecord())->SetDirtyFlag();
		}
		BOOL GetValue()
		{
			return m_nValue;
		}
	protected:
		BOOL m_nValue;
	};


	class CStatusRecordItemLong : public CXTPGridRecordItem
	{
	public:
		CStatusRecordItemLong(UINT nValue)
		{
			m_nValue = nValue;
			GetEditOptions(NULL)->AddConstraint(_T(" 정상"), 0);
			GetEditOptions(NULL)->AddConstraint(_T("제한됨"), 1);
			GetEditOptions(NULL)->m_bConstraintEdit = FALSE;
			GetEditOptions(NULL)->m_bAllowEdit = FALSE;		
			GetEditOptions(NULL)->AddComboButton();
		}

		CString GetCaption(CXTPGridColumn* /*pColumn*/)
		{
			CXTPGridRecordItemConstraint* pConstraint = GetEditOptions(NULL)->FindConstraint(m_nValue);
			ASSERT(pConstraint);
			return pConstraint->m_strConstraint;
		}

		void OnConstraintChanged(XTP_REPORTRECORDITEM_ARGS* /*pItemArgs*/, CXTPGridRecordItemConstraint* pConstraint)
		{
			if(((CRcpPowerRecord*)GetRecord())->m_nRole == 0 && 
				((CRcpPowerRecord*)GetRecord())->m_nCompany == m_ci.m_nCompanyCode)
			{
//				::MessageBox(NULL, "관리자는 수정이 불가능합니다.", "확인", MB_ICONINFORMATION);
				return;
			}

			m_nValue = (BOOL)pConstraint->m_dwData;
			RefreshIconIndex();
			((CRcpPowerRecord*)GetRecord())->SetDirtyFlag();
		}
		BOOL GetValue()
		{
			return m_nValue;
		}

		void RefreshIconIndex()
		{
			if(m_nValue == 0)
				((CRcpPowerRecord*)GetRecord())->GetItem(0)->SetIconIndex(0);
			else
				((CRcpPowerRecord*)GetRecord())->GetItem(0)->SetIconIndex(3);
		}

	protected:
		BOOL m_nValue;
	};




public:
	CRcpPowerRecord(long nCompany, long nWNo, CString strBranchName, CString strName, CString strID, 
			long nMonitor, long nRcp, long nStaff, long nCustomerReport, long nRiderReport, long nCustomer, long nIncome, long nStat,
			BOOL bPreventUser, long nRole, CString strPower)
	{
		m_nCompany = nCompany;
		m_nWNo = nWNo;
		m_nRole = nRole;
		m_strPower = strPower;
		m_bDirtyFlag = FALSE;
		CXTPGridRecordItem* pItem = AddItem(new CXTPGridRecordItemText(strBranchName));
		pItem->SetIconIndex(0);
		AddItem(new CXTPGridRecordItemNumber(nWNo));
		AddItem(new CXTPGridRecordItemText(strName));
		AddItem(new CXTPGridRecordItemText(strID));
		pItem = AddItem(new CRcpPowerRecordItemLong(nMonitor));
		pItem->SetItemData(nMonitor);
		pItem = AddItem(new CRcpPowerRecordItemLong(nRcp));
		pItem->SetItemData(nRcp);
		pItem = AddItem(new CRcpPowerRecordItemLong(nStaff));
		pItem->SetItemData(nStaff);
		pItem = AddItem(new CRcpPowerRecordItemLong(nCustomerReport));
		pItem->SetItemData(nCustomerReport);
		pItem = AddItem(new CRcpPowerRecordItemLong(nRiderReport));
		pItem->SetItemData(nRiderReport);
		pItem = AddItem(new CRcpPowerRecordItemLong(nCustomer));
		pItem->SetItemData(nCustomer);
		pItem = AddItem(new CRcpPowerRecordItemLong(nIncome));
		pItem->SetItemData(nIncome);
		pItem = AddItem(new CRcpPowerRecordItemLong(nStat));
		pItem->SetItemData(nStat);
		pItem = AddItem(new CStatusRecordItemLong(bPreventUser));
		pItem->SetItemData(bPreventUser);

		//((CManagerRecordItemLong*)GetItem(5))->RefreshIconIndex();
	}

	virtual void GetItemMetrics(XTP_GRIDRECORDITEM_DRAWARGS* pDrawArgs, XTP_GRIDRECORDITEM_METRICS* pItemMetrics)
	{
		int nCol = pDrawArgs->pColumn->GetIndex();

		if(nCol < 4)
		{
			pItemMetrics->clrBackground = RGB(50, 50, 200);
			pItemMetrics->clrForeground= RGB(255, 255, 255);
		}
		else if(nCol < 12)
		{
			switch(((CRcpPowerRecordItemLong*)GetItem(nCol))->GetValue())
			{
			case 0:
				pItemMetrics->clrBackground = RGB(255, 255, 255);
				pItemMetrics->clrForeground= RGB(0, 0, 0);
				break;

			case 1:
				pItemMetrics->clrBackground = RGB(240, 240, 255);
				pItemMetrics->clrForeground= RGB(0, 0, 0);
				break;

			case 2:
				pItemMetrics->clrBackground = RGB(220, 220, 255);
				pItemMetrics->clrForeground= RGB(0, 0, 0);
				break;
			}
		}
		else if(nCol == 12)
		{
			switch(((CStatusRecordItemLong*)GetItem(nCol))->GetValue())
			{
			case 0:
				pItemMetrics->clrBackground = RGB(255, 255, 255);
				pItemMetrics->clrForeground = RGB(0, 0, 0);
				break;

			case 1:
				pItemMetrics->clrBackground = RGB(255, 200, 200);
				pItemMetrics->clrForeground = RGB(0, 0, 0);
				break;
			}
		}
	}



	BOOL GetDirtyFlag() { return m_bDirtyFlag; }
	void SetDirtyFlag() { m_bDirtyFlag = TRUE;}

	BOOL GetPreventLogin() { return ((CStatusRecordItemLong*)GetItem(12))->GetValue(); }
	long GetPower(long nType) { return ((CRcpPowerRecordItemLong*)GetItem(nType))->GetValue(); }

protected:
	BOOL m_bDirtyFlag;

public:
	long m_nCompany;
	long m_nWNo;
	long m_nRole;
	CString m_strPower;

	/*
	static BOOL GetValue(XTP_NM_REPORTRECORDITEM* pItemNotify)
	{
	return ((CPropertyItemBool*)pItemNotify->pItem)->GetValue();
	}
	*/
};


IMPLEMENT_DYNAMIC(CRcpPowerDlg, CXTResizeDialog)

CRcpPowerDlg::CRcpPowerDlg(CWnd* pParent /*=NULL*/, BOOL bSelectMode)
: CXTResizeDialog(CRcpPowerDlg::IDD, pParent)
{
	m_bSelectMode = bSelectMode;
	m_bDragMode = FALSE;
}

CRcpPowerDlg::~CRcpPowerDlg()
{
}

void CRcpPowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_wndReportCtrl);
	DDX_Control(pDX, IDC_COPY_POWER_BTN, m_CopyPowerBtn);
	DDX_Control(pDX, IDC_PART_SAVE_BTN, m_PartSaveBtn);
	DDX_Control(pDX, IDC_OK_BTN, m_OkBtn);

	DDX_Control(pDX, IDC_BRANCH_EDIT, m_edtBranch);
	DDX_Control(pDX, IDC_RNO_EDIT, m_edtRNo);
	DDX_Control(pDX, IDC_NAME_EDIT, m_edtName);
	DDX_Control(pDX, IDC_ID_EDIT, m_edtID);
}


BEGIN_MESSAGE_MAP(CRcpPowerDlg, CXTResizeDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CRcpPowerDlg::OnBnClickedOkBtn)
	//ON_BN_CLICKED(IDC_CANCEL_BTN, &CRcpPowerDlg::OnBnClickedCancelBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT_LIST, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_PART_SAVE_BTN, OnBnClickedPartSaveBtn)
	ON_BN_CLICKED(IDC_COPY_POWER_BTN, OnBnClickedCopyPowerBtn)
	ON_EN_CHANGE(IDC_BRANCH_EDIT, OnEnChangeBranchEdit)
	ON_EN_CHANGE(IDC_RNO_EDIT, OnEnChangeRnoEdit)
	ON_EN_CHANGE(IDC_NAME_EDIT, OnEnChangeNameEdit)
	ON_EN_CHANGE(IDC_ID_EDIT, OnEnChangeIdEdit)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_REPORT_LIST, OnReportBeginDrag)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CRcpPowerDlg::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

// CRcpPowerDlg 메시지 처리기입니다.
BOOL CRcpPowerDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	BOOL bEditable = !m_bSelectMode;

	CBitmap bmp;
	VERIFY(m_ilIcons.Create(16,16, ILC_COLOR24|ILC_MASK, 0, 1));
	VERIFY(bmp.LoadBitmap(IDB_MSN_STATUS));
	m_ilIcons.Add(&bmp, RGB(255, 0, 255));

	m_wndReportCtrl.SetImageList(&m_ilIcons);
	m_wndReportCtrl.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_wndReportCtrl.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReportCtrl.SetPaintManager(new CMyReportPaintManager());
	m_wndReportCtrl.SetTreeIndent(10);
	m_wndReportCtrl.SetGridColor(RGB(222, 222, 222));
	m_wndReportCtrl.AllowEdit(bEditable);

	CXTPGridColumn *p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(0, _T("소속사"), 90, FALSE));
	p1->SetEditable(FALSE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(1, _T("사번"), 50));
	p1->SetEditable(FALSE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(2, _T("이름"), 100));
	p1->SetEditable(FALSE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(3, _T("ID"), 80));
	p1->SetEditable(FALSE);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(4, _T("상황"), 40));
	p1->SetEditable(bEditable);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(5, _T("접수"), 40));
	p1->SetEditable(bEditable);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(6, _T("고객정산"), 50));
	p1->SetEditable(bEditable);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(7, _T("기사정산"), 50));
	p1->SetEditable(bEditable);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(8, _T("직원"), 40));
	p1->SetEditable(bEditable);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(9, _T("고객"), 40));
	p1->SetEditable(bEditable);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(10, _T("입금"), 40));
	p1->SetEditable(bEditable);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(11, _T("통계"), 40));
	p1->SetEditable(bEditable);
	p1 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(12, _T("로그인"), 50));
	p1->SetEditable(bEditable);

	m_edtBranch.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtBranch.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "소속사");
	m_edtRNo.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtRNo.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "사 번");
	m_edtName.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtName.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "이 름");
	m_edtID.SetMyFont("맑은 고딕", 15, FW_BOLD);
	m_edtID.SetUserOption(RGB(0, 0, 0), RGB(245, 245, 245), "아이디");

	if(m_bSelectMode)
	{
		m_CopyPowerBtn.ShowWindow(SW_HIDE);
		m_PartSaveBtn.ShowWindow(SW_HIDE);
		m_OkBtn.SetWindowText("선택");
		SetWindowText(m_strDstName + "님의 권한을 선택하시는 분의 권한으로 변경합니다.");
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	else
	{
		// Set control resizing.
		SetResize(IDC_REPORT_LIST, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);

		// Load window placement
		LoadPlacement(_T("CRcpPowerDlg"));
	}


	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRcpPowerDlg::RefreshList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rcp_power_admin", FALSE, TRUE);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), TRUE);

	m_wndReportCtrl.GetRecords()->RemoveAll();
	if(pRs.Execute(&pCmd)) {
		for(int i = 0 ; i < pRs.GetRecordCount(); i++)
		{		
			long nCompany, nMNo;
			CString strID, strName, strBranchName;
			BOOL bPreventLogin;
			CString strPower;
			long nRole;

			pRs.GetFieldValue("lCode", nCompany);
			pRs.GetFieldValue("nMNo", nMNo);
			pRs.GetFieldValue("sName", strName);
			pRs.GetFieldValue("sBranchName", strBranchName);
			pRs.GetFieldValue("sID", strID);
			pRs.GetFieldValue("bPreventLogin", bPreventLogin);
			pRs.GetFieldValue("sPower", strPower);
			pRs.GetFieldValue("nRole", nRole);

			CMakeRcpPower power;
			power.SetPowerChunk(strPower, nRole, strBranchName, strID, strName, nCompany, nMNo, bPreventLogin);

			m_wndReportCtrl.AddRecord(new CRcpPowerRecord(nCompany, nMNo, strBranchName, strName, strID, 
							power.GetMonitorPower(),
							power.GetRcpPower(),
							power.GetReportCustomerPower(),
							power.GetReportRiderPower(),
							power.GetStaffPower(), 
							power.GetCustomerPower(), 
							power.GetIncomePower(),
							power.GetStatPower(), 
							bPreventLogin ? 1 : 0,
							nRole, strPower));
			pRs.MoveNext();
		}

		m_wndReportCtrl.Populate();
	}

	pRs.Close();

}


void CRcpPowerDlg::OnBnClickedOkBtn()
{
	if(m_bSelectMode)
	{
		POSITION pos = m_wndReportCtrl.GetSelectedRows()->GetFirstSelectedRowPosition();
		if(pos == NULL)
		{
			MessageBox("권한을 복사해 줄 소유자를 선택하시기 바랍니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		long nItem = m_wndReportCtrl.GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
		CXTPGridRecord *pRecord = m_wndReportCtrl.GetRecords()->GetAt(nItem);

		if(((CRcpPowerRecord*)pRecord)->m_nRole == 0)
		{
			MessageBox("관리자의 권한을 복사해 줄 수는 없습니다.", "확인", MB_ICONINFORMATION);
			return;
		}

		m_nSrcCompany = ((CRcpPowerRecord*)pRecord)->m_nCompany;
		m_nSrcWNo = ((CRcpPowerRecord*)pRecord)->m_nWNo;
		m_strSrcName = ((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetValue();

	}

	OnOK();
}

//void CRcpPowerDlg::OnBnClickedCancelBtn()
//{
//	OnCancel();
//}

void CRcpPowerDlg::OnBnClickedCopyPowerBtn()
{
	POSITION pos = m_wndReportCtrl.GetSelectedRows()->GetFirstSelectedRowPosition();
	if(pos == NULL)
	{
		MessageBox("권한복사 대상자를 선택하시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	long nItem = m_wndReportCtrl.GetSelectedRows()->GetNextSelectedRow(pos)->GetIndex();
	CXTPGridRecord *pRecord = m_wndReportCtrl.GetRows()->GetAt(nItem)->GetRecord();

	if(((CRcpPowerRecord*)pRecord)->m_nRole == 0)
	{
		MessageBox("관리자의 권한은 복사로 변경할 수 없습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	CRcpPowerDlg dlg(this, TRUE);
	dlg.m_strDstName = ((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetValue();

	if(IDOK == dlg.DoModal())
	{
		CString strMsg;
		strMsg.Format("%s님의 권한 -> %s님의 권한으로 변경합니다.", dlg.m_strSrcName, dlg.m_strDstName);
		if(IDYES == MessageBox(strMsg, "권한변경 확인", MB_YESNO))
		{
			CMkCommand pCmd(m_pMkDb, "update_rcp_power_for_copy");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), dlg.m_nSrcCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), dlg.m_nSrcWNo);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), ((CRcpPowerRecord*)pRecord)->m_nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), ((CRcpPowerRecord*)pRecord)->m_nWNo);
			if(!pCmd.Execute())
			{
				MessageBox("저장중에 오류가 발생했습니다.\n다시시도하시기 바랍니다.", "에러", MB_ICONERROR);
				return;
			}
			RefreshList();
		}
	}
}


void CRcpPowerDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	if(m_bSelectMode) return;

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if(pItemNotify->pRow)
	{
		CRcpPowerRecord* pRecord = (CRcpPowerRecord*)pItemNotify->pRow->GetRecord();

		CRcpPowerSetDlg dlg;
		dlg.m_nCompany = pRecord->m_nCompany;
		dlg.m_nMNo = pRecord->m_nWNo;
		dlg.m_nRole = pRecord->m_nRole;
		dlg.m_strBranchName = ((CXTPGridRecordItemText*)pRecord->GetItem(0))->GetValue();
		dlg.m_strName = ((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetValue();
		dlg.m_bPrevent = pRecord->GetPreventLogin();
		if(dlg.DoModal() == IDOK)
			RefreshList();
	}
}

void CRcpPowerDlg::OnBnClickedPartSaveBtn()
{
	CMkCommand pCmd(m_pMkDb, "select_rcp_power_manager");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	CMkParameter *parManagerPower = pCmd.AddParameter(typeString, typeOutput, 2000, "");
	if(!pCmd.Execute()) {
		MessageBox("관리자 권한획득 실패\n권한저장 실패함", "실패", MB_ICONINFORMATION);
		return;
	}
	
	CString strManagerPower;
	parManagerPower->GetValue(strManagerPower);

	CMakeRcpPower powerManager;
	powerManager.SetPowerChunk(strManagerPower, 0);

    
	for(int i = 0; i < m_wndReportCtrl.GetRecords()->GetCount(); i++)
	{
		CRcpPowerRecord *pPower = (CRcpPowerRecord*)m_wndReportCtrl.GetRecords()->GetAt(i);

		if(pPower->GetDirtyFlag())
		{
			if(pPower->m_nRole == 0 && m_ci.m_nCompanyCode == pPower->m_nCompany)
			{
				MessageBox("본사 관리자 권한 수정은 로지소프트로 문의바랍니다.", "확인", MB_ICONINFORMATION);
				continue;
			}

			CMakeRcpPower power;
			power.SetPowerChunk(pPower->m_strPower,pPower->m_nRole);
			power.ChangePower(MONITOR_POWER_CODE, pPower->GetPower(4));
			power.ChangePower(RCP_POWER_CODE, pPower->GetPower(5));
			power.ChangePower(REPORT_CUSTOMER_POWER_CODE, pPower->GetPower(6));
			power.ChangePower(REPORT_RIDER_POWER_CODE, pPower->GetPower(7));
			power.ChangePower(STAFF_POWER_CODE, pPower->GetPower(8));
			power.ChangePower(CUSTOMER_POWER_CODE, pPower->GetPower(9));
			power.ChangePower(INCOME_POWER_CODE, pPower->GetPower(10));
			power.ChangePower(STAT_POWER_CODE, pPower->GetPower(11));
			CString strPower = power.AndPower(&powerManager);

			CMkCommand pCmd(m_pMkDb, "update_rcp_power_new");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pPower->m_nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), pPower->m_nWNo);
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), pPower->GetPreventLogin());
			pCmd.AddParameter(typeString, typeInput, strPower.GetLength(), strPower);
			if(!pCmd.Execute())
			{
				MessageBox("저장중에 오류가 발생했습니다.\n다시시도하시기 바랍니다.", "에러", MB_ICONERROR);
				RefreshList();
				return;
			}
		}
	}

	RefreshList();
	MessageBox("저장 되었습니다.", "확인", MB_OK);

}


void CRcpPowerDlg::OnEnChangeBranchEdit()
{
	FilterList();
}

void CRcpPowerDlg::OnEnChangeRnoEdit()
{
	FilterList();
}

void CRcpPowerDlg::OnEnChangeNameEdit()
{
	FilterList();
}

void CRcpPowerDlg::OnEnChangeIdEdit()
{
	FilterList();
}

void CRcpPowerDlg::FilterList()
{
	CString strSearchBranch; m_edtBranch.GetWindowText(strSearchBranch);
	CString strSearchRNo; m_edtRNo.GetWindowText(strSearchRNo);
	CString strSearchName; m_edtName.GetWindowText(strSearchName);
	CString strSearchID; m_edtID.GetWindowText(strSearchID);

	strSearchBranch.MakeUpper();
	strSearchRNo.MakeUpper();
	strSearchName.MakeUpper();
	strSearchID.MakeUpper();

	CXTPGridRecords *pRecords = m_wndReportCtrl.GetRecords();
	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strBranch = pRecord->GetItem(0)->GetCaption(NULL);
		CString strRNo = pRecord->GetItem(1)->GetCaption(NULL);
		CString strName = pRecord->GetItem(2)->GetCaption(NULL);
		CString strID = pRecord->GetItem(3)->GetCaption(NULL);

		strBranch.MakeUpper();
		strRNo.MakeUpper();
		strName.MakeUpper();
		strID.MakeUpper();

		BOOL bVisible = TRUE;

		if((strBranch.Find(strSearchBranch) < 0) && (strSearchBranch != "") )
			bVisible = FALSE;

		if((strRNo.Find(strSearchRNo) < 0) && (strSearchRNo != "") )
			bVisible = FALSE;

		if((strName.Find(strSearchName) < 0) && (strSearchName != ""))
			bVisible = FALSE;

		if((strID.Find(strSearchID) < 0) && (strSearchID != ""))
			bVisible = FALSE;

		pRecord->SetVisible(bVisible);
	}

	m_wndReportCtrl.Populate();
}

void CRcpPowerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	::ReleaseCapture();

	if(TRUE == m_bDragMode)
	{
		m_bDragMode = FALSE;  //순서에 주의 할것

		CRect rcList;
		m_wndReportCtrl.GetWindowRect(&rcList);
		ScreenToClient(rcList);

		if(rcList.PtInRect(point))
		{
			CXTPGridSelectedRows *pRows = m_wndReportCtrl.GetSelectedRows();

			if(pRows == NULL) return;
			if(pRows->GetCount() == 0) return;

			CPoint pt(point);
			ClientToScreen(&pt);

			m_wndReportCtrl.ScreenToClient(&pt);
			CXTPGridRow *pRow = m_wndReportCtrl.HitTest(pt);

			if(pRow == NULL) return;

			CRcpPowerRecord *pSrcRecord = (CRcpPowerRecord*)pRows->GetAt(0)->GetRecord();
			CRcpPowerRecord *pDscRecord = (CRcpPowerRecord*)pRow->GetRecord();

			if(pSrcRecord == pDscRecord)
				return;

			CString strSrcName = pSrcRecord->GetItem(2)->GetCaption(NULL);
			long nSrcCompany = pSrcRecord->m_nCompany;
			long nSrcWNo = pSrcRecord->m_nWNo;
			CString strDstrCName = pDscRecord->GetItem(2)->GetCaption(NULL);
			long nDscCompany = pDscRecord->m_nCompany;
			long nDscWNo = pDscRecord->m_nWNo;

			if(pSrcRecord->m_nRole == 0 || pDscRecord->m_nRole == 0)
			{
				MessageBox("관리자의 권한을 복사 혹은 복사로 변경 할 수는 없습니다.", "확인", MB_ICONINFORMATION);
				return;
			}

			CString strMsg;
			strMsg.Format("%s님의 권한 -> %s님의 권한으로 변경합니다.", strSrcName, strDstrCName);

			if(IDYES == MessageBox(strMsg, "권한변경 확인", MB_YESNO))
			{ 
				CMkCommand cmd(m_pMkDb, "update_rcp_power_for_copy");
				cmd.AddParameter(nDscCompany);
				cmd.AddParameter(nDscWNo);
				cmd.AddParameter(nSrcCompany);
				cmd.AddParameter(nSrcWNo);

				if(!cmd.Execute())
				{
					MessageBox("저장중에 오류가 발생했습니다.\n다시시도하시기 바랍니다.", "에러", MB_ICONERROR);
					return;
				}
				RefreshList();
			}
		}		
	}

	CXTResizeDialog::OnLButtonUp(nFlags, point);
}
