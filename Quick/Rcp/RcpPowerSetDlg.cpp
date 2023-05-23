// RcpPowerSetDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RcpPowerSetDlg.h"
#include "MyReportPaintManager.h"




IMPLEMENT_DYNAMIC(CRcpPowerSetDlg, CXTResizeDialog)

CRcpPowerSetDlg::CRcpPowerSetDlg(CWnd* pParent /*=NULL*/)
: CXTResizeDialog(CRcpPowerSetDlg::IDD, pParent)
{
}

CRcpPowerSetDlg::~CRcpPowerSetDlg()
{
}

void CRcpPowerSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
	DDX_Control(pDX, IDC_NAME_STATIC, m_NameStatic);
	DDX_Control(pDX, IDC_PREVENT_CHECK, m_PreventCheck);
	DDX_Check(pDX, IDC_PREVENT_CHECK, m_bPrevent);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
}


BEGIN_MESSAGE_MAP(CRcpPowerSetDlg, CXTResizeDialog)
	ON_BN_CLICKED(IDC_OK_BTN, &CRcpPowerSetDlg::OnBnClickedOkBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CRcpPowerSetDlg::OnBnClickedCancelBtn)
	ON_NOTIFY(XTP_NM_GRID_CHECKED, IDC_REPORTCTRL, OnCustom1Click)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
END_MESSAGE_MAP()


// CRcpPowerSetDlg 메시지 처리기입니다.

void CRcpPowerSetDlg::OnCustom1Click(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{

	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

}
BOOL CRcpPowerSetDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

//	m_wndReportCtrl.SetImageList(&m_ilIcons);
	m_wndReportCtrl.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_wndReportCtrl.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReportCtrl.GetReportHeader()->AllowColumnSort(FALSE);
	m_wndReportCtrl.SetPaintManager(new CMyReportPaintManager());

	CXTPGridColumn* pColumn = m_wndReportCtrl.AddColumn(new CXTPGridColumn(0, _T("메인그룹"), 60, FALSE));
	pColumn->SetTreeColumn(1);
	CXTPGridColumn* pColumn2 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(1, _T("서브그룹"), 60));
	CXTPGridColumn* pColumn3 = m_wndReportCtrl.AddColumn(new CXTPGridColumn(2, _T("ⓟ"), 20));
	m_wndReportCtrl.AddColumn(new CXTPGridColumn(3, _T("제목"), 130));
	m_wndReportCtrl.AddColumn(new CXTPGridColumn(4, _T("상세내역(P = 해당권한)"), 250));

	m_wndReportCtrl.SetTreeIndent(30);
	m_wndReportCtrl.SetGridColor(RGB(222, 222, 222));
	m_wndReportCtrl.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";

	m_wndReportCtrl.Populate();

	m_NameStatic.SetWindowText(m_strBranchName + "소속의 " + m_strName + "님 권한");


	// Set control resizing.
	SetResize(IDC_REPORTCTRL, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);

	// Load window placement
	LoadPlacement(_T("CRcpPowerSetDlg"));

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRcpPowerSetDlg::RefreshList()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rcp_power_list");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_nMNo);
	CMkParameter *parManagerPower = pCmd.AddParameter(typeString, typeOutput, 2000, "");
	CMkParameter *parPower = pCmd.AddParameter(typeString, typeOutput, 2000, "");

	CXTPGridRecord *pMainRecord = NULL;
	CXTPGridRecord *pSubMainRecord = NULL;
	CXTPGridRecord *pRecord = NULL;
	m_wndReportCtrl.GetRecords()->RemoveAll();

	if(pRs.Execute(&pCmd)) {

		CString strPower, strManagerPower;
		parPower->GetValue(strPower);
		parManagerPower->GetValue(strManagerPower);

		CMakeRcpPower power;
		power.SetPowerChunk(strPower, m_nRole);
		m_ManagerPower.SetPowerChunk(strManagerPower, 0);

		for(int i = 0 ; i < pRs.GetRecordCount(); i++)
		{		
			long nCode;
			CString strMain, strSubMain, strTitle, strDetail;

			pRs.GetFieldValue("nCode", nCode);
			pRs.GetFieldValue("sMain", strMain);
			pRs.GetFieldValue("sSubMain", strSubMain);
			pRs.GetFieldValue("sTitle", strTitle);
			pRs.GetFieldValue("sDetail", strDetail);

			BOOL bHasPower = power.GetPower(nCode) ? TRUE : FALSE;

			if(strMain.GetLength() > 0)
			{
				pMainRecord = m_wndReportCtrl.AddRecord(new CDetailPowerRecord(nCode, strMain, strSubMain, strTitle, strDetail, bHasPower));
				pMainRecord->SetExpanded(TRUE);
			}
			else if(strSubMain.GetLength() > 0)
			{
				pSubMainRecord = pMainRecord->GetChilds()->Add(new CDetailPowerRecord(nCode, strMain, strSubMain, strTitle, strDetail, bHasPower));
				pSubMainRecord->SetExpanded(TRUE);
			}
			else
			{
				pSubMainRecord->GetChilds()->Add(new CDetailPowerRecord(nCode, strMain, strSubMain, strTitle, strDetail, bHasPower));
			}

			pRs.MoveNext();
		}

		m_wndReportCtrl.Populate();
	}

	pRs.Close();
}


void CRcpPowerSetDlg::OnBnClickedOkBtn()
{
	if(m_nRole == 0 && m_ci.m_nCompanyCode == m_nCompany)
	{

		if(m_ui.bDeveloper && m_ui.bBlankPassword)
		{
			m_wndReportCtrl.ExpandAll();
			SavePower(TRUE);
		}
		else
		{
			MessageBox("본사관리자의 권한은 수정이 불가능합니다.\n"\
					"로지소프트로 문의 바랍니다.", 
					"수정불가",
					MB_ICONINFORMATION);
		}
	}
	else
	{
		m_wndReportCtrl.ExpandAll();
		SavePower();
	}
}

void CRcpPowerSetDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CRcpPowerSetDlg::SavePower(BOOL bLogiSet)
{
	UpdateData(TRUE);

	CString strPower;
	m_strMsg = "아래의 권한을 부여할수 없습니다.\n관리자가 가지고 있지 않은 권한입니다.\n\n\n";
	BOOL bNotHasPower = FALSE;

	CXTPGridRecords *pRecords = m_wndReportCtrl.GetRecords();

	for(int j = 0; j < pRecords->GetCount(); j++)
		//for(int i = 0; i < m_wndReportCtrl.GetRows()->GetCount(); i++)
	{
		//CXTPGridRow *pRow = (CXTPGridRow*)m_wndReportCtrl.GetRows()->GetAt(i);
		CDetailPowerRecord *pPower3 = (CDetailPowerRecord*)pRecords->GetAt(j);
		CXTPGridRecords *pChilds3 = pPower3->GetChilds();

		if(!GetPowerSub(pPower3, bLogiSet, strPower, bNotHasPower))
			return;

		if(pChilds3)
		{
			for(int k = 0; k < pChilds3->GetCount(); k++)
			{
				CDetailPowerRecord *pPower2 = (CDetailPowerRecord*)pChilds3->GetAt(k);
				CXTPGridRecords *pChilds2 = pPower2->GetChilds();

				if(!GetPowerSub(pPower2, bLogiSet, strPower, bNotHasPower))
					return;

				if(pChilds2)
				{
					for(int i = 0; i < pChilds2->GetCount(); i++)
					{				
						CDetailPowerRecord *pPower = (CDetailPowerRecord*)pChilds2->GetAt(i);

						if(!GetPowerSub(pPower, bLogiSet, strPower, bNotHasPower))
							return;
					}
				}
			}
		}		
	}

	CMkCommand pCmd(m_pMkDb, "update_rcp_power_new");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nMNo);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bPrevent);
	pCmd.AddParameter(typeString, typeInput, strPower.GetLength(), strPower);
	if(!pCmd.Execute())
	{
		MessageBox("저장중에 오류가 발생했습니다.\n다시시도하시기 바랍니다.", "에러", MB_ICONERROR);
	}
	else
	{
		if(bNotHasPower)
		{
			MessageBox(m_strMsg, "권한없음", MB_ICONINFORMATION);
			MessageBox("일부권한을 제외하고 저장이 완료되었습니다.", "확인", MB_ICONINFORMATION);
			OnOK();
		}
		else
		{
			MessageBox("저장이 완료되었습니다.", "확인", MB_ICONINFORMATION);
			OnOK();
		}
	}
}


BOOL CRcpPowerSetDlg::GetPowerSub(CDetailPowerRecord *pPower, BOOL bLogiSet, CString &strPower, BOOL &bNotHasPower)
{
	if(pPower->GetPowerType())
	{ 
		//1511
		//if(m_ManagerPower.GetPower(pPower->m_nCode))
		if(m_ManagerPower.GetPower(pPower->m_nCode) || bLogiSet)
		{
			strPower +=  LF->GetStringFromLong(pPower->m_nCode);
			strPower += ",";
		} 
		else
		{					
			BOOL bReverse = FALSE;

			if(pPower->m_nCode == 1511) //전화(CID)당일보기
				bReverse = TRUE;

			m_strMsg += "[" + ((CXTPGridRecordItemText*)pPower->GetItem(3))->GetValue() + "]\n";
			bNotHasPower = TRUE;

			if(bReverse) //반대의 권한을 가지는 애들 
			{
				strPower +=  LF->GetStringFromLong(pPower->m_nCode);
				strPower += ",";
				bNotHasPower = FALSE;
			}
		}
	}
	else if(bLogiSet)
	{
		CMkCommand cmd(m_pMkDb, "update_rcp_power_remove_all");
		cmd.AddParameter(m_nCompany);
		cmd.AddParameter(pPower->m_nCode);
		if(!cmd.Execute())
		{
			MessageBox("저장중에 오류가 발생했습니다.\n다시시도하시기 바랍니다.", "에러", MB_ICONERROR);
			return FALSE;
		}
	}

	return TRUE;
}

void CRcpPowerSetDlg::OnEnChangeSearchEdit()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);
	strSearch.MakeUpper();

	CXTPGridRecords *pMainRecords = m_wndReportCtrl.GetRecords(); 
	BOOL bFind = FALSE;

	for(int i=0; i<pMainRecords->GetCount(); i++)
	{ 
		CXTPGridRecord *pMainRecord = pMainRecords->GetAt(i);
		CXTPGridRecords *pSubRecords = pMainRecord->GetChilds();

		if(pSubRecords) 
		{
			CXTPGridRecord *pSubRecord = pSubRecords->GetAt(i);
			CXTPGridRecords *pSubRecords2 = pMainRecord->GetChilds();

			for(int i=0; i<pSubRecords->GetCount(); i++)
			{
				CXTPGridRecord *pSubRecord2 = pSubRecords2->GetAt(i);
				CXTPGridRecords *pTitleRecords = pSubRecord2->GetChilds();

				bFind = FALSE;
				if(pTitleRecords)
				{
					for(int j = 0; j < pTitleRecords->GetCount(); j++)
					{
						CXTPGridRecord *pTitleRecord = pTitleRecords->GetAt(j);

						CString strItem1 = pTitleRecord->GetItem(1)->GetCaption(NULL);
						CString strItem2 = pTitleRecord->GetItem(3)->GetCaption(NULL);
						CString strItem3 = pTitleRecord->GetItem(4)->GetCaption(NULL);

						strItem1.MakeUpper();
						strItem2.MakeUpper();
						strItem3.MakeUpper();

						if(strItem1.Find(strSearch) >= 0 ||
							strItem2.Find(strSearch) >= 0 ||
							strItem3.Find(strSearch) >= 0)
						{
							bFind = TRUE;
							pTitleRecord->SetVisible(TRUE);
						}
						else
							pTitleRecord->SetVisible(FALSE);
					}
				}

				if(!bFind)
				{
					CString strItem1 = pSubRecord2->GetItem(1)->GetCaption(NULL);
					CString strItem2 = pSubRecord2->GetItem(3)->GetCaption(NULL);
					CString strItem3 = pSubRecord2->GetItem(4)->GetCaption(NULL);

					strItem1.MakeUpper();
					strItem2.MakeUpper();
					strItem3.MakeUpper();

					if(strItem1.Find(strSearch) >= 0 ||
						strItem2.Find(strSearch) >= 0 ||
						strItem3.Find(strSearch) >= 0)
						pSubRecord2->SetVisible(TRUE);
					else
						pSubRecord2->SetVisible(FALSE);
				}
				else
					pSubRecord2->SetVisible(TRUE);
			}
		}
	}

	m_wndReportCtrl.Populate();
}