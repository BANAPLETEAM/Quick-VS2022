// RiderAdviceDlg2010.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderAdviceDlg2010.h"
#include ".\RiderAdviceDlg2010.h"
#include "MyReportPaintManager.h"
#include "LogiUtil.h"
#include "FakeDlg.h"


// CRiderAdviceDlg2010 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderAdviceDlg2010, CMyDialog)
CRiderAdviceDlg2010::CRiderAdviceDlg2010(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRiderAdviceDlg2010::IDD, pParent)
{
	m_nOrderCompany = -1;
	m_nModifyID = 0;
	m_bConfirmTNo = FALSE;
	m_strTNo = "";
}

CRiderAdviceDlg2010::~CRiderAdviceDlg2010()
{
}

void CRiderAdviceDlg2010::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_TNO_EDIT, m_edtTNo);
	DDX_Text(pDX, IDC_TNO_EDIT, m_strTNo);
	DDX_Control(pDX, IDC_SAVE_BTN3, m_btnSave3);
}


BEGIN_MESSAGE_MAP(CRiderAdviceDlg2010, CMyDialog)
	ON_BN_CLICKED(IDC_SAVE_BTN, OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_CHECK_BTN, OnBnClickedCheckBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN2, OnBnClickedSaveBtn2)
	ON_BN_CLICKED(IDC_SAVE_BTN3, &CRiderAdviceDlg2010::OnBnClickedSaveBtn3)
END_MESSAGE_MAP()


// CRiderAdviceDlg2010 메시지 처리기입니다.
BOOL CRiderAdviceDlg2010::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CFakeDlg dlg;
	dlg.DoModal();
	//m_List.SetPaintManager(new CMyReportPaintManager());
  
	CXTPGridColumn* pColumn = m_List.AddColumn(new CXTPGridColumn(0, _T("대분류"), 90, FALSE)); 
	pColumn->SetTreeColumn(1);      
	CXTPGridColumn* pColumn1 = m_List.AddColumn(new CXTPGridColumn(1, _T("타입"), 130));
	CXTPGridColumn* pColumn2 = m_List.AddColumn(new CXTPGridColumn(2, _T("체크"), 20));
	CXTPGridColumn* pColumn3 = m_List.AddColumn(new CXTPGridColumn(3, _T("패널티"), 50));
	CXTPGridColumn* pColumn4 = m_List.AddColumn(new CXTPGridColumn(4, _T("벌점"), 30));
	CXTPGridColumn* pColumn5 = m_List.AddColumn(new CXTPGridColumn(5, _T("배차제한 사유(자세히 기록해주세요)"), 190));

	pColumn->GetEditOptions()->m_bAllowEdit = FALSE; 
	pColumn1->GetEditOptions()->m_bAllowEdit = FALSE; 
	pColumn2->GetEditOptions()->m_bAllowEdit = FALSE; 
	pColumn2->SetAlignment(LVCFMT_CENTER);
	pColumn3->GetEditOptions()->m_bAllowEdit = TRUE; 
	pColumn4->GetEditOptions()->m_bAllowEdit = FALSE;  
	pColumn5->GetEditOptions()->m_bAllowEdit = TRUE; 
	m_List.SetPaintManager(new CMyReportPaintManager);
	m_List.GetReportHeader()->AllowColumnRemove(FALSE);
	m_List.GetReportHeader()->AllowColumnSort(FALSE);
	m_List.SetTreeIndent(30);
	m_List.SetGridColor(RGB(222, 222, 222));
	m_List.AllowEdit(TRUE);
	m_List.GetPaintManager()->m_strNoItems = "표시할 대상이 존재하지 않음";

	m_List.Populate();
	RefreshList();

	return TRUE;
}

void CRiderAdviceDlg2010::RefreshList()
{
	m_map.clear();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_black_mark_list");
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_nModifyID);

	long nCode, nPenaltyDay, nBlackMarks, nCheckCode = -1, nApplyPenaltyDay =0;
	CString strType, strTitle, strEtc, strTNo;
	BOOL bCorp, bModifyCheck = FALSE;

	CString sPreTitle;
	CXTPGridRecord *pRecord = NULL;
	CXTPGridRecord *pRecordChild = NULL; 

	if(!rs.Execute(&cmd)) return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nCode", nCode);
		rs.GetFieldValue("sTitle", strTitle);
		rs.GetFieldValue("sType", strType);
		rs.GetFieldValue("nPenaltyDay", nPenaltyDay);
		rs.GetFieldValue("nBlackMarks", nBlackMarks);
		rs.GetFieldValue("bCorp", bCorp);

		if(m_nModifyID > 0)
		{
			rs.GetFieldValue("nCheckCode", nCheckCode);
			rs.GetFieldValue("sEtc", strEtc);
			rs.GetFieldValue("nApplyPenaltyDay", nApplyPenaltyDay);			
		}

		if(nCode == nCheckCode)
		{
	  		bModifyCheck = TRUE;
			m_bConfirmTNo = TRUE;
			m_edtTNo.SetWindowText(strTNo);
			((CEdit*)GetDlgItem(IDC_TNO_EDIT))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_CHECK_BTN))->EnableWindow(FALSE);
		}

		if(strTitle != sPreTitle)
			pRecord = m_List.AddRecord(new CRiderAdviceRecord2010(nCode, strTitle, strType, nPenaltyDay, 
			nBlackMarks, bCorp, FALSE,bModifyCheck , strEtc, nApplyPenaltyDay));
		else
		{
			pRecordChild = pRecord->GetChilds()->Add(new CRiderAdviceRecord2010(nCode, strTitle, strType, nPenaltyDay, 
				nBlackMarks, bCorp, TRUE,bModifyCheck , strEtc, nApplyPenaltyDay));
			pRecord->SetExpanded(TRUE);
		} 

		bModifyCheck = FALSE;
		sPreTitle = strTitle;

		rs.MoveNext();
	}

	m_List.Populate();
}


void CRiderAdviceDlg2010::OnBnClickedSaveBtn()
{
    if(CheckCount() == FALSE)
		return;
	
	if(Save(FALSE) == TRUE)
	{
		MessageBox("배차제한 등록이 완료되었습니다.", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}

BOOL CRiderAdviceDlg2010::Save(BOOL bAll)
{
	long nCount = 0;
	CRiderAdviceRecord2010 *pRecord = NULL;
	long nItemCount = m_List.GetRows()->GetCount();
	
	for(int i=0; i<nItemCount; i++)
	{
		CXTPGridRow* pRow = m_List.GetRows()->GetAt(i);
		pRecord = (CRiderAdviceRecord2010*)pRow->GetRecord();

		if(pRecord->GetChecked())
		{
			if(SaveSub(bAll, pRecord) == FALSE)
				return FALSE;
		}		
	}

	return TRUE;
}

BOOL CRiderAdviceDlg2010::SaveSub(BOOL bAll, CRiderAdviceRecord2010 *pRecord)
{
	CString strTNo = "";
	BOOL bIntegrated = FALSE;
	long nApplyCompany = 0,nTNo = 0,  nReturnValue = 0;

	if(m_ba.GetCount() > 1)  //통합이면
		bIntegrated = TRUE; 
	
	m_edtTNo.GetWindowText(strTNo);
	nTNo = atol(strTNo);

	//if(m_nCompany m_nRiderCompany))
	// 팀장님 02-18 통합콜센타일 경우 1. 오더기준 2. 회사기준, 3. 접수자기준

	if(! bAll) // 오더에다 걸면 
	{
		if(m_nOrderCompany > 0)
			nApplyCompany = m_nOrderCompany;	
		else
			nApplyCompany = m_nCompany;
	}
	else  // 오더에 걸린 통합본사
	{		
		if(m_nOrderCompany > 0)
			nApplyCompany = m_ci.GetShareCode1(m_nOrderCompany);	
		else
			nApplyCompany = m_ci.GetShareCode1(m_nCompany);	
	}

	long nCode = pRecord->m_nCode;
	if(nApplyCompany <= 0)
		nApplyCompany = m_ui.nCompany;

	CString strMemo = ((CXTPGridRecordItemText*)pRecord->GetItem(5))->GetCaption(NULL); 

	CMkCommand cmd(m_pMkDb, "insert_share_order_rider_register_5");
	CMkRecordset rs(m_pMkDb);
	cmd.AddParameter(m_nModifyID);
	cmd.AddParameter(nApplyCompany);
	cmd.AddParameter(bAll );
	cmd.AddParameter(bIntegrated);
	cmd.AddParameter(m_nRiderCompany);
	cmd.AddParameter(m_nRNo);
	cmd.AddParameter(pRecord->m_strType);
	cmd.AddParameter(strMemo);
	cmd.AddParameter(pRecord->GetComboValue());	
	cmd.AddParameter(nCode);
	cmd.AddParameter(pRecord->m_nBlackMarks);
	cmd.AddParameter(nTNo);	
	cmd.AddParameter(m_ui.nCompany);	
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);
	CMkParameter *pPar = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
	rs.Execute(&cmd);

	pPar->GetValue(nReturnValue);
	if(nReturnValue == 6)
	{
		MessageBox("해당지사 혹은 1차코드에 이미 등록되어 있습니다", "확인", MB_ICONINFORMATION);
		return FALSE; 
	}

	return TRUE;
}

BOOL CRiderAdviceDlg2010::CheckCount()
{
	long nCount = 0; CString strTNo = "";
	CRiderAdviceRecord2010 *pRecord = NULL;
	long nItemCount = m_List.GetRows()->GetCount();
	
	for(int i=0; i<nItemCount; i++)
	{
		CXTPGridRow* pRow = m_List.GetRows()->GetAt(i);
		pRecord = (CRiderAdviceRecord2010*)pRow->GetRecord();

		if(pRecord->GetChecked())
		{
			CXTPGridColumn *pColumn = m_List.GetColumns()->GetAt(5);
			CString strEtc = pRecord->GetItem(5)->GetCaption(pColumn);
			
			if(strEtc.GetLength() <= 10 )
			{
				MessageBox("배차제한 사유에 대해 자세히 기록해주세요.(10자이상)\n내용이 없거나, 임의내용(ex.공유불가, 타사락참조, 재등록 등)으로만 등록한 경우 삭제될 수 있습니다.", "확인", MB_ICONINFORMATION);
				return FALSE;
			}
			if(pRecord->GetComboValue() <= 0 )
			{
				MessageBox("패널티 컬럼을 클릭하시어 패널티 기간을 설정하여 주세요 ", "확인", MB_ICONINFORMATION);
				return FALSE;

			}


			nCount++;

		}
	}
	
	if(nCount == 0)
	{
		MessageBox("최소 하나 이상 체크하세요", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if(nCount > 1)
	{
		MessageBox("1개이상 체크 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	if(m_nModifyID == 0)
		return CheckCountDb(nCount);
	else
		return TRUE;
}

BOOL CRiderAdviceDlg2010::CheckCountDb(long nCount)
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "check_give_rider_blackmarks_ability");
	cmd.AddParameter(m_ci.GetShareCode1());
	cmd.AddParameter(m_nRiderCompany);
	cmd.AddParameter(m_nRNo);

	if(!rs.Execute(&cmd)) return FALSE;

	if(rs.GetRecordCount() == 0)
		return FALSE;
	
	long nTodayCount = 0;
	rs.GetFieldValue("nCount", nTodayCount);

//	업데이트금지 최.. 20171120
	if(nTodayCount == 0) return TRUE;

	if(nTodayCount > 0)
	{
		MessageBox("금일 해당 기사님에게 이미 벌점을 주었습니다", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;
}

void CRiderAdviceDlg2010::OnBnClickedCancelBtn()
{
	OnCancel();
}

void CRiderAdviceDlg2010::OnBnClickedCheckBtn()
{
	CString strTNo = ""; 
	long nTNo = 0, nReturnValue = 0;
	m_edtTNo.GetWindowText(strTNo);

	if(strTNo.GetLength() <= 0)
	{
		MessageBox("오더번호를 기입하세요", "확인" , MB_ICONINFORMATION);
		return;
	}

	if(!LF->IsStringDigit(strTNo))
	{
		MessageBox("숫자가 아닙니다.", "확인" , MB_ICONINFORMATION);
		return;
	}
	nTNo = atol(strTNo);
	

	CMkCommand cmd(m_pMkDb, "select_allocate_limit_tno_confirm");
	CMkRecordset rs(m_pMkDb);
	cmd.AddParameter(nTNo);
	cmd.AddParameter(m_nRiderCompany);
	cmd.AddParameter(m_nRNo);
	CMkParameter *pPar = cmd.AddParameter(typeLong,typeOutput, sizeof(long), 0);
	CMkParameter *pParOrderCompany = cmd.AddParameter(typeLong,typeOutput, sizeof(long), 0);
	if(!cmd.Execute())
		return;

	pPar->GetValue(nReturnValue);
	if(nReturnValue == 0)
		MessageBox("해당오더에 기사님이 운행하지 않았습니다.", "확인", MB_ICONINFORMATION);
	else if(nReturnValue == 1)
		MessageBox(" 7일이 지난 오더는 배차제한을 하실수 없습니다.", "확인", MB_ICONINFORMATION);
	else if(nReturnValue == 2)
		MessageBox(" 해당오더가 없습니다.", "확인", MB_ICONINFORMATION);
	else if(nReturnValue == 4)
		MessageBox(" 기존에 해당기사에 배차제한을건 오더입니다", "확인", MB_ICONINFORMATION);
	else if(nReturnValue == 10)
	{
		MessageBox("해당오더를 확인하였습니다.", "확인", MB_ICONINFORMATION);
		m_bConfirmTNo = TRUE;
		pParOrderCompany->GetValue(m_nOrderCompany);
		((CButton*)GetDlgItem(IDC_CHECK_BTN))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_TNO_EDIT))->EnableWindow(FALSE);
	}   	 	
}

void CRiderAdviceDlg2010::OnBnClickedSaveBtn2()
{
	if(m_ci.m_bRcpIntMode1 != TRUE)
	{
		MessageBox("지사에서는 전지사 적용을 하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	if(CheckCount() == FALSE)
		return;

	if(Save(TRUE) == TRUE)
	{
		MessageBox("배차제한 등록이 완료되었습니다.", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}

void CRiderAdviceDlg2010::OnBnClickedSaveBtn3()
{
	//insert_balck_mark_share_all
	long nItemCount = m_List.GetRows()->GetCount();

	CString strTNo; m_edtTNo.GetWindowText(strTNo);
	long nTNo = atoi(strTNo); 

	BOOL bSuccess = FALSE;

	for(int i=0; i<nItemCount; i++)
	{
		CXTPGridRow* pRow = m_List.GetRows()->GetAt(i);
		CRiderAdviceRecord2010 *pRecord = (CRiderAdviceRecord2010*)pRow->GetRecord();

		if(pRecord->GetChecked())
		{
			CString strMemo = ((CXTPGridRecordItemText*)pRecord->GetItem(5))->GetCaption(NULL); 

			CMkCommand cmd(m_pMkDb, "insert_balck_mark_share_all");
			cmd.AddParameter(nTNo);
			cmd.AddParameter(m_nRiderCompany);
			cmd.AddParameter(m_nRNo);
			cmd.AddParameter(pRecord->m_strType);
			cmd.AddParameter(strMemo);
			cmd.AddParameter(pRecord->GetComboValue());
			cmd.AddParameter(pRecord->m_nBlackMarks);
			cmd.AddParameter(pRecord->m_nCode);
			cmd.AddParameter(m_ui.nCompany);
			cmd.AddParameter(m_ui.nWNo);
			cmd.AddParameter(m_ui.strName);

			if(!cmd.Execute())
				return;

			bSuccess = TRUE;
		}
	}

	if(bSuccess)
	{
		MessageBox("콜센터 전체에 적용되었습니다", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}
