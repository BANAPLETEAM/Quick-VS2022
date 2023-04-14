// TankTypeQDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "TankTypeQDlg.h"
#include ".\tanktypeqdlg.h"
#include "DataBox.h"

#define  SETTING_VIEW	2
#define  NOT_ALL_APPLY	4
#define  ALL_APPLY		5
#define  CALL_COUNT		6

#define  RIDER_CALCURATE	7
#define  RIDER_COUNT		8
#define  BRANCH_COUNT		9

// CTankTypeQDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTankTypeQDlg, CMyDialog)
CTankTypeQDlg::CTankTypeQDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CTankTypeQDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_nServer = 0;
}

CTankTypeQDlg::~CTankTypeQDlg()
{
}

void CTankTypeQDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_List);
	DDX_Control(pDX, IDC_RATE_COMBO, m_cmbRate);
	DDX_Control(pDX, IDC_CHECK_COMBO, m_cmbCheck);
}


BEGIN_MESSAGE_MAP(CTankTypeQDlg, CMyDialog)
	ON_BN_CLICKED(IDC_APPLY_BTN, OnBnClickedApplyBtn)

	ON_NOTIFY(XTP_NM_GRID_CHECKED, IDC_CUSTOM1, OnReportCheckItem)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM1, OnReportClickItem)

	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_RATE_ALL_BTN, OnBnClickedRateAllBtn)
	ON_BN_CLICKED(IDC_CHECK_ALL_BTN, OnBnClickedCheckAllBtn)
	ON_BN_CLICKED(IDC_CHECK_NOTALL_BTN, OnBnClickedCheckNotallBtn)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CTankTypeQDlg 메시지 처리기입니다.


BOOL CTankTypeQDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_cmbCheck.SetCurSel(0);
	m_cmbRate.SetCurSel(0);
	RefreshList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CTankTypeQDlg::RefreshList()
{
	m_List.DeleteAllItem();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_tank_view_info");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);

	if(!pRs.Execute(&pCmd)) return ;

	CString sBranchName;
	long nCompany, nTankType, nShowPartApply;
	BOOL bShowTank; 
	char buffer[10];
	CStringArray sArray, sArray2; CUIntArray nArray,nArray2;
	sArray.Add("정상");			nArray.Add(0);
	sArray.Add("20%만보기");	nArray.Add(1);
	sArray.Add("25%만보기"); 	nArray.Add(2);
	sArray.Add("30%만보기"); 	nArray.Add(3);
	sArray.Add("40%만보기"); 	nArray.Add(4);
	sArray.Add("50%만보기"); 	nArray.Add(5);
	sArray.Add("66%만보기"); 	nArray.Add(6);
	sArray.Add("75%만보기"); 	nArray.Add(7);
	sArray.Add("80%만보기"); 	nArray.Add(8);
	sArray.Add("90%만보기"); 	nArray.Add(9);

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nTankType", nTankType);
		pRs.GetFieldValue("bShowTank", bShowTank);
		pRs.GetFieldValue("nShowPartApply", nShowPartApply);	
		pRs.GetFieldValue("sBranchName", sBranchName);	

		BOOL bCallCount = FALSE, bRiderCalculate = FALSE, bRiderCount = FALSE, bBranchCalculate = FALSE;
		SetInitColumn(nShowPartApply, bCallCount, bRiderCalculate, bRiderCount, bBranchCalculate);

		m_List.MyAddItem(0,itoa(i+1, buffer,10),"No",40, FALSE,DT_CENTER);
		m_List.MyAddItem(1,sBranchName,"지사명", 100, FALSE,DT_LEFT);
		m_List.MyCheckAddItem(2,bShowTank,"셋팅보이기", 70,LVCFMT_CENTER);
		m_List.MyComboAddItem(3,sArray, nArray, "셋팅비율", 90, DT_LEFT, nTankType);		
		m_List.MyCheckAddItem(4,nShowPartApply == 0 ? TRUE : FALSE, "전부미적용", 80, DT_LEFT);
		m_List.MyCheckAddItem(5,nShowPartApply == 100 ? TRUE : FALSE, "전부적용", 70, DT_LEFT);
		m_List.MyCheckAddItem(6,bCallCount,		"콜카운트", 70, DT_LEFT);
		m_List.MyCheckAddItem(7,bRiderCalculate,	"정산탭기사정산", 100, DT_LEFT);
		m_List.MyCheckAddItem(8,bRiderCount,		"정산탭기사별건수", 110, DT_LEFT);
		m_List.MyCheckAddItem(9,bBranchCalculate, "통계탭일별건수", 100, DT_LEFT);


		m_List.InsertItemDataLong(nCompany);
		m_List.EndItem();

		pRs.MoveNext();

	}
	pRs.Close();
	m_List.AllowEdit(TRUE);
	m_List.Populate();

}


void CTankTypeQDlg::OnBnClickedApplyBtn()
{

	if(m_List.GetItemCount() == 0 )
		return;

	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		CMyXTPGridRecord* pRecord = (CMyXTPGridRecord*)m_List.GetRecords()->GetAt(i);
		if(pRecord->m_bDirtyFlag)
		{

			long nCheck = 0;
			long nCompany = pRecord->GetItemDataLong();
			BOOL bSettingView = m_List.GetItemCheck(i,2);
			int	 nSettingRate = m_List.GetItemComboValue(i, 3);
			BOOL bNotAllApply = m_List.GetItemCheck(i,4);
			BOOL bAllApply = m_List.GetItemCheck(i,5);
			BOOL bCallCount = m_List.GetItemCheck(i, 6);
			BOOL bRiderCalculate = m_List.GetItemCheck(i,7);
			BOOL bRiderCount = m_List.GetItemCheck(i,8);
			BOOL bBranchCalculate = m_List.GetItemCheck(i,9);

			if(bNotAllApply)
				nCheck = 0;				
			else if(bAllApply)
				nCheck = 100;
			else
			{
				nCheck += bCallCount ?  1 : 0;
				nCheck += bRiderCalculate ?  2 : 0;
				nCheck += bRiderCount ? 4 : 0;
				nCheck += bBranchCalculate ? 8 : 0;
			}

			CMkCommand pCmd(m_pMkDb, "update_tank_type_apply_dis");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
			pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), bSettingView);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCheck);  
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nSettingRate);  
			if(!pCmd.Execute()) 
			{
				MessageBox("적용중 도중에 실패하였습니다. 다시시도 하세요", "확인", MB_ICONINFORMATION);
				return;
			}

		}


	}
	MessageBox("수정되었습니다.", "확인", MB_ICONINFORMATION);

	/*


	BRANCH_INFO *pBi = NULL;
	if(m_ba.GetCount() >= 2)
	{
	for(int i = 0; i < m_ba.GetCount(); i ++)
	{
	pBi = m_ba.GetAt(i);
	if(!pBi->bIntegrated && pBi->nCompanyCode == nCompany)
	{
	pBi->nTankType = pOptionDlgGeneral->m_cmbTankType.GetCurSel();
	break;
	}

	}
	}
	else
	{
	pBi = m_ba.GetAt(0);
	pBi->nTankType = pOptionDlgGeneral->m_cmbTankType.GetCurSel();
	}
	*/

}
void CTankTypeQDlg::SetInitColumn(int nShowPartApply, BOOL &bCallCount, BOOL &bRiderCalculate, 
								 BOOL &bRiderCount, BOOL &bBranchCalculate)
{
	if(nShowPartApply <= 0)
	{
		bCallCount = bRiderCalculate = bRiderCount = bBranchCalculate = 0;
		return;
	}
	if(nShowPartApply >= 100)
	{
		bCallCount = bRiderCalculate = bRiderCount = bBranchCalculate = 1;
		return;
	}

	if(nShowPartApply >= 8)
	{
		bBranchCalculate = 1;
		nShowPartApply -= 8;
	}
	if(nShowPartApply >= 4)
	{
		bRiderCount = 1;
		nShowPartApply -= 4;
	}
	if(nShowPartApply >= 2)
	{
		bRiderCalculate = 1;
		nShowPartApply -= 2;
	}
	if(nShowPartApply >= 1)
	{
		bCallCount = 1;
		nShowPartApply -= 1;
	}

}

void CTankTypeQDlg::OnReportClickItem(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{

}
void CTankTypeQDlg::OnReportCheckItem(NMHDR * pNotifyStruct, LRESULT *p) 
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();


	CMyXTPGridRecord *pRecord = (CMyXTPGridRecord *)pItemNotify->pRow->GetRecord();

	BOOL bCheck = m_List.GetItemCheck(nRow, nCol);

	if(nCol == 4 && bCheck)
	{		
		m_List.GetRecords()->GetAt(nRow)->GetItem(5)->SetChecked(!bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(6)->SetChecked(!bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(7)->SetChecked(!bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(8)->SetChecked(!bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(9)->SetChecked(!bCheck);				

	}
	else if(nCol == 5 && bCheck)
	{

		m_List.GetRecords()->GetAt(nRow)->GetItem(4)->SetChecked(!bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(5)->SetChecked(bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(6)->SetChecked(bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(7)->SetChecked(bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(8)->SetChecked(bCheck);
		m_List.GetRecords()->GetAt(nRow)->GetItem(9)->SetChecked(bCheck);
	}
	else if( (nCol == 6 || nCol == 7 || nCol == 8 || nCol == 9) && bCheck)
	{

		m_List.GetRecords()->GetAt(nRow)->GetItem(4)->SetChecked(!bCheck);

	}
	else if( (nCol == 6 || nCol == 7 || nCol == 8 || nCol == 9) && !bCheck)
	{		
		m_List.GetRecords()->GetAt(nRow)->GetItem(5)->SetChecked(bCheck);		
	}
	m_List.Populate();
}

void CTankTypeQDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CTankTypeQDlg::OnBnClickedRateAllBtn()
{
	int nCurSel = m_cmbRate.GetCurSel();	
	if(m_List.GetSelectedCount() > 1)
	{
		for(int i = 0; i < m_List.GetSelectedCount(); i++)
		{
			CMyComboRecordItem* pItem = (CMyComboRecordItem*)m_List.GetSelectedRecord(i)->GetItem(2);
			pItem->SetValue(nCurSel);
		}

	}
	else
	{
		for(int i = 0; i < m_List.GetRecords()->GetCount(); i++)
		{
			CMyComboRecordItem* pItem = (CMyComboRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(3);
			pItem->SetValue(nCurSel);
		}	
	}

	m_List.Populate();
}

void CTankTypeQDlg::OnBnClickedCheckAllBtn()
{
	SetCheckFunction(TRUE);
}
void CTankTypeQDlg::SetCheckFunction(BOOL bCheck)
{
	int nCurSel = m_cmbCheck.GetCurSel();
	switch(nCurSel)
	{
	case 0:
		nCurSel = SETTING_VIEW;
		break;
	case 1:
		nCurSel = NOT_ALL_APPLY;
		break;
	case 2:
		nCurSel = ALL_APPLY;
		break;
	case 3:
		nCurSel = CALL_COUNT;
		break;
	case 4:
		nCurSel = RIDER_CALCURATE;
		break;
	case 5:
		nCurSel = RIDER_COUNT;
		break;
	case 6:
		nCurSel = BRANCH_COUNT;
		break;
	}
	int nRecordCount  = 0;

	if(m_List.GetSelectedCount() > 1)	
		nRecordCount = m_List.GetSelectedCount();				
	else
		nRecordCount = m_List.GetRecords()->GetCount();	


	for(int i = 0; i < nRecordCount; i++)
	{
		CMyCheckRecordItem* pCheckItem;
		CMyCheckRecordItem* pItem = (m_List.GetSelectedCount() > 1) ?
			(CMyCheckRecordItem*)m_List.GetSelectedRecord(i)->GetItem(nCurSel) :
		(CMyCheckRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(nCurSel);

		pItem->SetChecked(bCheck);

		if(nCurSel == NOT_ALL_APPLY)
		{
			for(int j = ALL_APPLY; j < BRANCH_COUNT +1; j++)
			{
				pCheckItem = (m_List.GetSelectedCount() > 1) ?
					(CMyCheckRecordItem*)m_List.GetSelectedRecord(i)->GetItem(j) :
				(CMyCheckRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(j);

				if(bCheck)
					pCheckItem->SetChecked(!bCheck);
				else
				{

					pCheckItem = (m_List.GetSelectedCount() > 1) ?
						(CMyCheckRecordItem*)m_List.GetSelectedRecord(i)->GetItem(NOT_ALL_APPLY) :
					(CMyCheckRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(NOT_ALL_APPLY);
					pCheckItem->SetChecked(FALSE);
				}
			}
		}
		else if(nCurSel == ALL_APPLY)
		{

			for(int j = CALL_COUNT; j < BRANCH_COUNT +1; j++)
			{
				pCheckItem =  (m_List.GetSelectedCount() > 1) ?
					(CMyCheckRecordItem*)m_List.GetSelectedRecord(i)->GetItem(j):
				(CMyCheckRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(j);
				pCheckItem->SetChecked(bCheck);							
			}

			pCheckItem = (m_List.GetSelectedCount() > 1) ?
				(CMyCheckRecordItem*)m_List.GetSelectedRecord(i)->GetItem(NOT_ALL_APPLY) :
			(CMyCheckRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(NOT_ALL_APPLY);
			pCheckItem->SetChecked(!bCheck);
		}
		else if(nCurSel >= CALL_COUNT && nCurSel <= BRANCH_COUNT)
		{
			for(int j = NOT_ALL_APPLY; j < ALL_APPLY +1; j++)
			{
				pCheckItem = (m_List.GetSelectedCount() > 1) ?
					(CMyCheckRecordItem*)m_List.GetSelectedRecord(i)->GetItem(j):
				(CMyCheckRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(j);

				if(bCheck)
					pCheckItem->SetChecked(!bCheck);
				else
				{
					pCheckItem = (m_List.GetSelectedCount() > 1) ?
						(CMyCheckRecordItem*)m_List.GetSelectedRecord(i)->GetItem(nCurSel):
					(CMyCheckRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(nCurSel);
					pCheckItem->SetChecked(FALSE);

					pCheckItem = (m_List.GetSelectedCount() > 1) ?
						(CMyCheckRecordItem*)m_List.GetSelectedRecord(i)->GetItem(ALL_APPLY):
					(CMyCheckRecordItem*)m_List.GetRecordsGetAt(i)->GetItem(ALL_APPLY);
					if(pCheckItem->GetCheck())
						pCheckItem->SetChecked(FALSE);

				}
			}
		}			
	}


	m_List.Populate();
}

void CTankTypeQDlg::OnBnClickedCheckNotallBtn()
{
	SetCheckFunction(FALSE);

}

void CTankTypeQDlg::OnBnClickedButton1()
{
	m_cmbRate.SetCurSel(0);
	this->OnBnClickedRateAllBtn();
	m_List.Populate();
	m_cmbCheck.SetCurSel(1);
	this->OnBnClickedCheckAllBtn();
	m_List.Populate();
	this->OnBnClickedApplyBtn();
	m_List.Populate();
}
