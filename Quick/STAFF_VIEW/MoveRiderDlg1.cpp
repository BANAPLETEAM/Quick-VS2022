// MoveRiderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MoveRiderDlg1.h"
#include "MainFrm.h"

// CMoveRiderDlg1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMoveRiderDlg1, CMyDialog)
CMoveRiderDlg1::CMoveRiderDlg1(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMoveRiderDlg1::IDD, pParent)
	, m_nCompany(0)
	, m_nOptionStart(1)
	, m_nOptionEnd(100)
	, m_nPersonRiderNum(0)
	, m_nCountNum(0)
	, m_cmbSequence(0)
	, m_bIntegrated(FALSE)
{

}

CMoveRiderDlg1::~CMoveRiderDlg1()
{
}

void CMoveRiderDlg1::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_RiderList);
	DDX_Control(pDX, IDC_ALL_COMPANY_COMBO, m_cmbBranch);
	DDX_Control(pDX, IDC_DEPOSIT_LIST, m_DepositList);
	DDX_Control(pDX, IDC_SELECT_COMBO, m_cmbSelectCombo);
	DDX_Text(pDX, IDC_OPTION_START_EDIT, m_nOptionStart);
	DDV_MinMaxInt(pDX, m_nOptionStart, 0, 65554);
	DDX_Text(pDX, IDC_OPTION_END_EDIT, m_nOptionEnd);
	DDV_MinMaxInt(pDX, m_nOptionEnd, 0, 65554);
	DDX_Text(pDX, IDC_PERSON_RIDERNO_EDIT, m_nPersonRiderNum);
	DDV_MinMaxInt(pDX, m_nPersonRiderNum, 0, 65554);
	DDX_Text(pDX, IDC_COUNT_STATIC, m_nCountNum);
	DDX_Control(pDX, IDC_PROCESS_NUM_STATIC, m_stcProcessNum);
	DDX_Control(pDX, IDC_GROUP_LIST, m_GroupList);
	DDX_Control(pDX, IDC_OLD_RIDER_CHECK, m_chkOldRider);
	DDX_Control(pDX, IDC_NEW_RIDER_CHECK, m_chkNewRider);
	DDX_Control(pDX, IDC_CHECKBOX_ALL_SELECT_BUTTON, m_AllSelectBtn);
	DDX_Control(pDX, IDC_CHECKBOX_CANCEL_BUTTON, m_CancelBtn);
	DDX_Control(pDX, IDC_ALL_APPLY_BUTTON, m_AllApplyBtn);
	DDX_Control(pDX, IDC_PERSON_APPLY_BUTTON, m_PersonApplyBtn);
	//DDX_Control(pDX, IDC_DEPOSIT_BUTTON, m_DepositBtn);
	DDX_Control(pDX, IDC_GROUP_BUTTON, m_GroupBtn);
}


BEGIN_MESSAGE_MAP(CMoveRiderDlg1, CMyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_ALL_APPLY_BUTTON, OnBnClickedAllApplyButton)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST, OnLvnDeleteitemList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)	
	ON_BN_CLICKED(IDC_CHECKBOX_CANCEL_BUTTON, OnBnClickedCheckboxCancelButton)
	ON_BN_CLICKED(IDC_CHECKBOX_ALL_SELECT_BUTTON, OnBnClickedCheckboxAllSelectButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseButton)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnNMClickList)
	
	ON_BN_CLICKED(IDC_PERSON_APPLY_BUTTON, OnBnClickedPersonApplyButton)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)
	ON_BN_CLICKED(IDC_GROUP_BUTTON, OnBnClickedGroupButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OLD_RIDER_CHECK, OnBnClickedOldRiderCheck)
	ON_BN_CLICKED(IDC_NEW_RIDER_CHECK, OnBnClickedNewRiderCheck)
END_MESSAGE_MAP()


// CMoveRiderDlg1 메시지 처리기입니다.

BOOL CMoveRiderDlg1::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	InitControl();
	RefreshList();

	SetTimer(0, 500, 0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMoveRiderDlg1::InitControl()
{
	int nItem = 0;
	int nItem2 = 0;
	CImageList ImageList,ImageList2; 
	
	m_RiderList.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_RiderList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB 
		| LVS_EX_GRIDLINES |  LVS_EX_CHECKBOXES);
	m_RiderList.InsertColumn(nItem++, "소 속", LVCFMT_LEFT, 100);	
	m_RiderList.InsertColumn(nItem++, "사 번", LVCFMT_CENTER, 50);
	m_RiderList.InsertColumn(nItem++, "성 명", LVCFMT_LEFT, 80);


	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_DepositList.SetImageList(&ImageList,LVSIL_SMALL); 	
	m_DepositList.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_DepositList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);
	m_DepositList.InsertColumn(0,"기사번호",LVCFMT_CENTER,50);
	m_DepositList.InsertColumn(1,"기사명",LVCFMT_LEFT, 80);
	m_DepositList.InsertColumn(2,"총건수",LVCFMT_RIGHT,50);
	m_DepositList.InsertColumn(3,"운행요금",LVCFMT_RIGHT,65);
	m_DepositList.InsertColumn(4,"입금액",LVCFMT_RIGHT,50);
	m_DepositList.InsertColumn(5,"선입금",LVCFMT_RIGHT,70);
	m_DepositList.InsertColumn(6,"미수금합계",LVCFMT_RIGHT,75);
	m_DepositList.InsertColumn(7,"잔액",LVCFMT_RIGHT, 70);
	m_DepositList.InsertColumn(8,"입금상태",LVCFMT_CENTER, 65);
	m_DepositList.InsertColumn(9,"입금완료",LVCFMT_RIGHT, 65);
	m_DepositList.InsertColumn(10,"입금방식",LVCFMT_CENTER, 65);
	m_DepositList.InsertColumn(11,"금일충전",LVCFMT_RIGHT, 65);
	m_DepositList.InsertColumn(12,"입금시간",LVCFMT_LEFT, 65);
	m_DepositList.InsertColumn(13,"업무",LVCFMT_CENTER, 45);
	m_DepositList.InsertColumn(14,"주납금",LVCFMT_CENTER, 0);
	m_DepositList.InsertColumn(15,"주납일",LVCFMT_CENTER, 0);


	ImageList2.Create(1,17,ILC_COLOR,1,1); 
	m_GroupList.SetImageList(&ImageList2,LVSIL_SMALL); 	
	m_GroupList.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_GroupList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);
	m_GroupList.InsertColumn(0,"기사번호",LVCFMT_CENTER,70);
	m_GroupList.InsertColumn(1,"회사명",LVCFMT_LEFT, 90);
	m_GroupList.InsertColumn(2,"그룹이름",LVCFMT_RIGHT,90);
	
	
	UpdateData(TRUE);

	m_cmbBranch.ResetContent();
	m_cmbSelectCombo.ResetContent();
	m_chkNewRider.SetCheck(TRUE);	

	BOOL bIntegrated = FALSE;
	CBranchInfo *pBi2 = NULL;  // 통합시 브랜치정보일값.
	int nCount = 0;
	int nComboDefaultNum = 0;

	CBranchInfo *pBi = GetCurBranchInfo();

	if(pBi->bIntegrated)
	{
		for(int i = 0; i < m_ba.GetCount(); i++) {
			pBi2 = m_ba.GetAt(i);
			if(pBi2->bIntegrated)
				continue;
			else
			{
				m_cmbBranch.InsertString(nCount,pBi2->strBranchName);
				m_cmbBranch.SetItemData(nCount, pBi2->nCompanyCode);

				m_cmbSelectCombo.InsertString(nCount,pBi2->strBranchName);
				m_cmbSelectCombo.SetItemData(nCount, pBi2->nCompanyCode);						
				
			}	
			nCount++;
		}
		
		m_cmbBranch.SetCurSel(nComboDefaultNum);	
		m_cmbSelectCombo.SetCurSel(nComboDefaultNum);
	}
	else
	{
		m_cmbBranch.InsertString(nCount,pBi->strBranchName);
		m_cmbBranch.SetItemData(nCount, pBi->nCompanyCode);

		m_cmbSelectCombo.InsertString(nCount,pBi->strBranchName);
		m_cmbSelectCombo.SetItemData(nCount, pBi->nCompanyCode);		
	}


	if(m_cmbBranch.GetCount() >= 0)
		m_cmbBranch.SetCurSel(nComboDefaultNum);
	if(m_cmbSelectCombo.GetCount() >= 0)
		m_cmbSelectCombo.SetCurSel(nComboDefaultNum);
}


void CMoveRiderDlg1::RefreshList()
{	
	m_RiderList.DeleteAllItems();	

	char buffer[20];
	UpdateData(TRUE);
	CBranchInfo *pBi = GetCurBranchInfo();
	
	//CWaitCursor wait;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_inte_or_noninte_driver_branchname");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), pBi->nCompanyCode );
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), pBi->bIntegrated);

	if(!pRs.Execute(&pCmd)) return;

	CString strBranchName,strName;		
		int nMNo,lCode;
	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		lCode = nMNo = 0;		
		int nSubItem = 1;

		pRs.GetFieldValue("lCode", lCode);
		pRs.GetFieldValue("sBranchName", strBranchName);
		pRs.GetFieldValue("sName", strName);
		pRs.GetFieldValue("nMNo", nMNo);
				
		m_RiderList.InsertItem(i, strBranchName);
		m_RiderList.SetItemText(i, nSubItem++, ltoa(nMNo, buffer, 10));		
		m_RiderList.SetItemText(i, nSubItem++, strName);
		
		RIDER_INFO6 *ri =  new RIDER_INFO6;
		ri->nCompany = lCode;
		ri->nMNo = nMNo;
		ri->strBranchName = strBranchName;

		m_RiderList.SetItemData(i, (DWORD_PTR)ri);
		pRs.MoveNext();
	}

	pRs.Close();

}

void CMoveRiderDlg1::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BOOL CMoveRiderDlg1::ImPossIbleMoveOriginalAllCheck()
{

	UpdateData();
	int nBranch, nBranchCompany = 0;
	nBranch = m_cmbBranch.GetCurSel();
	nBranchCompany = (int)m_cmbBranch.GetItemData(nBranch);
	if(nBranchCompany == 0) return TRUE;
	int nVal = 0;
	
	char buffer[10];
	CString strDuplicate = "";
	CString strDuplicateSum = "";

	//CWaitCursor wait;	
	for(int i =0; i < this->m_RiderList.GetItemCount(); i++)
	{
		if(m_RiderList.GetCheck(i))
		{
			int nRNo = atoi(m_RiderList.GetItemText(i,1));
			CMkCommand pCmd(m_pMkDb, "select_Impossible_original_move_all_check");			
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nBranchCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo);			
			CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

			if(!pCmd.Execute()) return TRUE;

			parRet->GetValue(nVal);
			if(nVal)
			{
				strDuplicate.Format("%s번 ",itoa(nRNo,buffer,10));	
				strDuplicateSum +=  strDuplicate;		
			}
		}//IF
	}

	if(strDuplicateSum.GetLength() > 0)
	{
		strDuplicateSum += "기사님(들)이 이동하실 곳에 중복되어 있습니다";
		MessageBox(strDuplicateSum ,"중복기사 확인",MB_ICONINFORMATION);
			return TRUE;
	}
	else
		return FALSE;	

}
BOOL CMoveRiderDlg1::ImPossibleMoveAllCheck()
{
	UpdateData();
	int nBranch, nBranchCompany = 0;
	nBranch = m_cmbBranch.GetCurSel();
	nBranchCompany = (int)m_cmbBranch.GetItemData(nBranch);
	if(nBranchCompany == 0) return TRUE;
	int nVal = 0;
	//CWaitCursor wait;
	
	CMkCommand pCmd(m_pMkDb, "select_Impossible_move_all_check");
	
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nBranchCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nOptionStart);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nOptionEnd);	
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

	if(!pCmd.Execute()) return TRUE;
	parRet->GetValue(nVal);
	if(nVal > 0 ) 
		return TRUE;
	else
		return FALSE;
}

BOOL CMoveRiderDlg1::ImPossibleMoveCheck()
{
	UpdateData();
	int nBranch, nBranchCompany = 0;
	nBranch = m_cmbSelectCombo.GetCurSel();
	nBranchCompany = (int)m_cmbSelectCombo.GetItemData(nBranch);
	if(nBranchCompany == 0) return TRUE;
	int nVal = 0;
	//CWaitCursor wait;	
	CMkCommand pCmd(m_pMkDb, "select_Impossible_move_check");	
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nBranchCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nPersonRiderNum );		
	CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
	if(!pCmd.Execute()) return TRUE;
	parRet->GetValue(nVal);
	if(nVal > 0 ) 
		return TRUE;
	else
		return FALSE;

}
void CMoveRiderDlg1::OnBnClickedAllApplyButton()
{
	
	if(!CheckData()) return;
	
	char buffer[6];
	int nCount = 0;
	int nBranch, nBranchCompany = 0;
	nBranch = m_cmbBranch.GetCurSel();
	nBranchCompany = (int)m_cmbBranch.GetItemData(nBranch);
	
	if(nBranchCompany <= 0 ) return;

	if(m_chkNewRider.GetCheck())
	{
		if(ImPossibleMoveAllCheck())
			return;		
	}
	else
	{
		if(ImPossIbleMoveOriginalAllCheck()) 
			return;
	}

	for(int i =0; i< m_RiderList.GetItemCount(); i++)
	{
		int nCheckCount = 0;
		if(m_RiderList.GetCheck(i) == BST_CHECKED)
		{
			RIDER_INFO6 *ri = NULL;
			ri = (RIDER_INFO6*)m_RiderList.GetItemData(i);
			if(ri == NULL) return;

			int nRetValue = 0;	

			//CWaitCursor wait;			
			CMkRecordset pRs(m_pMkDb);			
			CMkCommand pCmd(m_pMkDb, "driver_move_process2");
			CMkParameter *parQueryRet = pCmd.AddParameter(typeLong, typeReturn, sizeof(int), 0);
			CMkParameter *parQueryMsg = pCmd.AddParameter(typeString, typeOutput, 0, "");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nCompany );
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo );
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nBranchCompany);

			if(m_chkNewRider.GetCheck())
                pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nOptionStart + nCount);
			else
				pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo );

			pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID );
			CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);
			
			if(!pRs.Execute(&pCmd)) return;
			
			if(parQueryRet->GetLong() == -999) //OVERLOAD_PROTECT
			{
				CString strQueryMsg;
				parQueryMsg->GetValue(strQueryMsg);
				MessageBox(strQueryMsg, "부하방지 정책", MB_ICONINFORMATION);	
				return;
			}
			parRet->GetValue(nRetValue);
			if(nRetValue == 100)
			{	CString strMsg;
				strMsg.Format("기사번호 %d이 이동하실 지사에 동일한 기사번호가 있습니다."
					,m_nOptionStart + nCount);
				strMsg += " 이전까지의 작업까지는 성공적으로 이동되었습니다.\n\n ";
				strMsg.Format(" 기사번호 %d 를 제외하고 계속 작업을 하시겠습니까?",m_nOptionStart+nCount);
				if(MessageBox(strMsg,"지사의 기사확인", MB_YESNO|MB_ICONINFORMATION) == IDNO)
					return;
			}
			nCount++;			
			UpdateData();
			m_stcProcessNum.SetWindowText(itoa(nCount,buffer,10));
			UpdateData(FALSE);
			
		}
	}
	RefreshList();
}


void CMoveRiderDlg1::OnBnClickedPersonApplyButton()
{	
	try
	{
		int nCount = 0;
		int nItem = 0;
		int nBranch, nBranchCompany = 0;
		nBranch = m_cmbSelectCombo.GetCurSel();
		nBranchCompany = (int)m_cmbSelectCombo.GetItemData(nBranch);
		UpdateData();
		if(m_nPersonRiderNum <= 0 || m_nPersonRiderNum > 65555)
			throw("이동하실 기사번호가 0보다 작거나 65555이상이면 수행되지않습니다.");
		
		if(ImPossibleMoveCheck())
			throw("이동하실 지사에 같은 기사번호가 있습니다.");
			
		if(nBranchCompany <= 0 ) return;
		int nItemCount = 0;
		for(int i=0; i< m_RiderList.GetItemCount(); i++)
		{
			if(m_RiderList.GetCheck(i))
			{			
				nItemCount++;
				nItem = i;				
			}			
		}
		if( nItemCount != 1 )
			throw("개별적용은 1개만 체크선택해주세요");
			
		
		RIDER_INFO6 *ri = NULL;
		ri = (RIDER_INFO6*)m_RiderList.GetItemData(nItem);
		if(ri == NULL) return;

		UpdateData();
		int nRetValue = 0;
		if(m_nPersonRiderNum <= 0 ) return;

		//CWaitCursor wait;
		
		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb, "driver_move_process");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nCompany );
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo );
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), nBranchCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nPersonRiderNum);
		pCmd.AddParameter(typeString, typeInput, m_ui.strID.GetLength(), m_ui.strID );	
		CMkParameter *parRet = pCmd.AddParameter(typeLong, typeOutput, sizeof(int), 0);

		if(!pCmd.Execute()) return;
		
		parRet->GetValue(nRetValue);
		if(nRetValue == 100)
			throw("이동하실 지사에 해당기사가 있습니다");
		
		RefreshList();
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg,"기사확인", MB_ICONINFORMATION);
		return;
	}
	
}


void CMoveRiderDlg1::OnLvnDeleteitemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	RIDER_INFO6 *ri = NULL;
	ri = (RIDER_INFO6*)m_RiderList.GetItemData(pNMLV->iItem);
	if(ri != NULL)
	{
		delete ri;
		ri = NULL;
	}
	*pResult = 0;
}

void CMoveRiderDlg1::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	int nItem = m_RiderList.GetSelectionMark();

	if(nItem <= -1) return;

	RIDER_INFO6 *ri = NULL;	
	ri = (RIDER_INFO6*)m_RiderList.GetItemData(nItem);
	if(ri == NULL) return;
	

	*pResult = 0;
}


BOOL CMoveRiderDlg1::CheckData()
{

	try
	{
		UpdateData();
		if(m_cmbBranch.GetCurSel() < 0)
			throw("이동하실 회사를 선택해주세요");
		if(m_cmbSelectCombo.GetCurSel() < 0)
			throw("이동하실 회사를 선택해주세요");

		int nCheck = 0;
		for(int i = 0; i< m_RiderList.GetItemCount(); i++)
		{
			if(m_RiderList.GetCheck(i) == BST_CHECKED )
				nCheck++;						
		}		
		if(m_chkNewRider.GetCheck())
		{
			if(m_nOptionStart > m_nOptionEnd)
				throw("시작하는 기사번호가 끝나는 기사번호보다 큽니다.");
			if(m_nOptionStart == 0)
				throw("기사번호는 0번보다는 커야 합니다.");
			if(m_nOptionEnd >= 65555)
				throw("기사번호는 65555보다는 작아야 합니다.");			
			if(m_nOptionEnd < m_nOptionStart)
				throw("끝번호는 크거나 같아야 합니다.");

			if(m_nOptionEnd - m_nOptionStart == 0)
			{				
				CString strDifference = NULL;
				if(nCheck > 1 && nCheck < 1)
				{
					strDifference.Format("기사체크한 값이 입력하신값과 %d",nCheck - 1);
					strDifference += " 개이상 차이가 납니다.\0";
					char *szbuffer;
					szbuffer = (char*)malloc(100);
					strcpy(szbuffer,strDifference.GetBuffer());						
					throw(szbuffer);				
				}
			}
			else
			{
				int nInputCount = m_nOptionEnd - m_nOptionStart + 1;
				if(nInputCount != nCheck)
				{
					CString strMessage;
					strMessage.Format("이동하실 기사체크수는 %d명이고 입력하신 기사 %d명입니다.\0",
						nInputCount, nCheck);				
					char *szbuffer;		
					szbuffer = (char*)malloc(100);
					strcpy(szbuffer,strMessage.GetBuffer());				
					throw(szbuffer);
					
				}
			}		
		}
		else
		{
			char buffer[10];
			CString strDuplicateNum;
			CUIntArray uArr;
			int i = 0;
			for(i = 0; i < m_RiderList.GetItemCount(); i++)
			{
				if(m_RiderList.GetCheck(i))
				{
					UINT uResult = (UINT)atol(m_RiderList.GetItemText(i,1));
					uArr.Add(uResult);
				}
			}

			for(i = 0; i < uArr.GetCount(); i++)
				for(int j=0; j < uArr.GetCount(); j++)
				{
					if(i == j ) continue;
					if(uArr.GetAt(i) == uArr.GetAt(j))
					{
						long nRNo = (long)uArr.GetAt(i);
						strDuplicateNum.Format("%s번 기사가 중복번호입니다.", ltoa(nRNo, buffer,10));
						MessageBox(strDuplicateNum,"확인", MB_ICONINFORMATION);
						return FALSE;
					}
				}

		}
		return TRUE;
	}
	catch(char *szMsg)
	{
		MessageBox(szMsg, "확인",MB_ICONINFORMATION);
		return FALSE;
	}
	
}
void CMoveRiderDlg1::OnBnClickedCheckboxCancelButton()
{
	for(int i = 0; i < m_RiderList.GetItemCount(); i++)
	{		
		m_RiderList.SetCheck(i,0);
	}
	UpdateData();
	m_nCountNum = 0;
	UpdateData(FALSE);
}

void CMoveRiderDlg1::OnBnClickedCheckboxAllSelectButton()
{
	for(int i = 0; i < m_RiderList.GetItemCount(); i++)
	{		
		m_RiderList.SetCheck(i,1);
	}
	UpdateData();
	m_nCountNum = m_RiderList.GetItemCount();
	UpdateData(FALSE);
}

void CMoveRiderDlg1::OnBnClickedCloseButton()
{
	OnCancel();
}
void CMoveRiderDlg1::DepositListIn(int nItemData)
{
	COleDateTime dtFrom = COleDateTime::GetCurrentTime();
	COleDateTime dtTo = COleDateTime::GetCurrentTime();
	//CString strDate;	

	if(dtFrom.GetHour() < BASE_HOUR) {
		dtTo.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtFrom = dtTo - COleDateTimeSpan(1, 0, 0, 0);
	}
	else {
		dtFrom.SetDateTime(dtFrom.GetYear(), dtFrom.GetMonth(), dtFrom.GetDay(), BASE_HOUR, 0, 0);
		dtTo = dtFrom + COleDateTimeSpan(1, 0, 0, 0);
	}

	

	CString strText;
	int nSearchRNo = -1;
	CString strSearchName;	
	RIDER_INFO6 *ri = NULL;
	ri = (RIDER_INFO6*)m_RiderList.GetItemData(nItemData);
	if(ri == NULL)
		return;

	//CWaitCursor wait;
	char buffer[20];
	UpdateData(TRUE);

	m_DepositList.DeleteAllItems();	

	CMkRecordset pRs2(m_pMkDb);	
	CMkCommand pCmd2(m_pMkDb, "select_rider_income_report_alone");		//쉐어코드 변수 사용하지 않음
	pCmd2.AddParameter(typeLong, typeInput, sizeof(int), ri->nCompany);
	pCmd2.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtFrom);
	pCmd2.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtTo);
	pCmd2.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	if(!pRs2.Execute(&pCmd2)) return;

	int nItem = 0, nRNo, nWeekDepositDay;
	long nCharge, nDeposit, nDebt, nSaveDeposit, nBalance;
	long nDepositType, nWeekDeposit;
	COleDateTime dtSave;
	
	long nCount, nWorkState;
	CString strRName;
	long nTodaySave;

	long nRiderCount = 0, nTCount = 0; 
	long nTCharge = 0, nTDeposit = 0;
	long nTBalance = 0, nTDebt = 0;
	long nTTodaySave = 0;
	long nCompany;

	while(!pRs2.IsEOF())	
	{
		pRs2.GetFieldValue("lCode", nCompany);
		pRs2.GetFieldValue("nMNo", nRNo);
		pRs2.GetFieldValue("sName", strRName);
		pRs2.GetFieldValue("nCount", nCount);
		pRs2.GetFieldValue("nCharge", nCharge);
		pRs2.GetFieldValue("nDeposit", nDeposit);
		pRs2.GetFieldValue("nDebt", nDebt);
		pRs2.GetFieldValue("nSaveDeposit", nSaveDeposit);
		//pRs2.GetFieldValue("nSaveType", nSaveType);
		pRs2.GetFieldValue("dtSave", dtSave);
		pRs2.GetFieldValue("nBalance", nBalance);
		pRs2.GetFieldValue("nWorkState", nWorkState);
		pRs2.GetFieldValue("nDepositType", nDepositType);
		pRs2.GetFieldValue("nWeekDeposit", nWeekDeposit);
		pRs2.GetFieldValue("nWeekDepositDay", nWeekDepositDay);
		pRs2.GetFieldValue("nTodaySave", nTodaySave);

		
		//if(POWER_CHECK(7012, "입금정산 수정"))
		//{
		//	if(!(nSearchRNo == nRNo ||
		//		(strSearchName.GetLength() > 0 && 
		//		strRName.Find(strSearchName) >= 0)))
		//	{
		//		pRs2.MoveNext();
		//		continue;
		//	}
		//}
		 

		if(nDepositType == 20) //DT_WEEK_PAY
			nDeposit = 0;

		m_DepositList.InsertItem(nItem, ltoa(nRNo, buffer, 10));
		m_DepositList.SetItemText(nItem, 1, strRName);
		m_DepositList.SetItemText(nItem, 2, CString(ltoa(nCount, buffer, 10)));
		m_DepositList.SetItemText(nItem, 3, GetMyNumberFormat(nCharge));
		m_DepositList.SetItemText(nItem, 4, GetMyNumberFormat(nDeposit));
		m_DepositList.SetItemText(nItem, 5, GetMyNumberFormat(nBalance));
		m_DepositList.SetItemText(nItem, 6, GetMyNumberFormat(nDebt));
		m_DepositList.SetItemText(nItem, 7, GetMyNumberFormat(nBalance + nSaveDeposit - nDeposit - nDebt));
		m_DepositList.SetItemText(nItem, 9, GetMyNumberFormat(nSaveDeposit));
		m_DepositList.SetItemText(nItem, 10, GetDepositTypeStringFromType(nDepositType));
		m_DepositList.SetItemText(nItem, 11, GetMyNumberFormat(nTodaySave));
		m_DepositList.SetItemText(nItem, 12, dtSave.Format("%m-%d %H:%M"));
		m_DepositList.SetItemText(nItem, 13, nWorkState == 1 ? "중지" : "");
		m_DepositList.SetItemText(nItem, 14, ltoa(nWeekDeposit, buffer, 10));
		m_DepositList.SetItemText(nItem, 15, ltoa(nWeekDepositDay, buffer, 10));
		

		nRiderCount++;
		nTCount += nCount;
		nTCharge += nCharge;
		nTDeposit += nDeposit;
		nTBalance += nBalance;
		nTDebt += nDebt;
		nTTodaySave += nTodaySave;

		if((nSaveDeposit >= nDeposit && nDebt == 0) || (nDeposit == 0 && nDebt == 0)) {
			m_DepositList.SetItemText(nItem, 8, "완료");
			m_DepositList.SetItemData(nItem++, 1);
		}
		else if(nDebt > 0 && nDepositType != 10) {
			m_DepositList.SetItemText(nItem, 8, "미수");
			m_DepositList.SetItemData(nItem++, 20);
		}
		else if(nSaveDeposit > 0)
		{
			m_DepositList.SetItemText(nItem, 8, "일부입금");
			m_DepositList.SetItemData(nItem++, 30);
		}
		else {
			m_DepositList.SetItemData(nItem++, 0);
		}
		pRs2.MoveNext();
	}

}
void CMoveRiderDlg1::GroupListIn(int nItemData)
{
	//CWaitCursor wait;
	
	UpdateData(TRUE);

	RIDER_INFO6 *ri = NULL;
	ri = (RIDER_INFO6*)m_RiderList.GetItemData(nItemData);
	if(ri == NULL)
		return;
	
	m_GroupList.DeleteAllItems();	

	char buffer[10];
	CMkRecordset pRs2(m_pMkDb);	
	CMkCommand pCmd2(m_pMkDb, "select_group_rider");
	pCmd2.AddParameter(typeLong, typeInput, sizeof(int), ri->nCompany);	
	pCmd2.AddParameter(typeLong, typeInput, sizeof(int), ri->nMNo);
	if(!pRs2.Execute(&pCmd2)) return;

	long nCompanyCode, nRNo;
	nCompanyCode = nRNo =0;
	CString strBranchName, strGroupName;
	int nItem = 0;
	while(!pRs2.IsEOF())	
	{
		pRs2.GetFieldValue("sBranchName", strBranchName);
		pRs2.GetFieldValue("sGroupName", strGroupName);
		pRs2.GetFieldValue("nCompanyCode", nCompanyCode);
		pRs2.GetFieldValue("nRNo", nRNo);

		m_GroupList.InsertItem(nItem, itoa(ri->nMNo,buffer,10) );
        m_GroupList.SetItemText(nItem, 1, strBranchName);		
		m_GroupList.SetItemText(nItem, 2, strGroupName);		

		nItem++;
		pRs2.MoveNext();
		
	}
		

}
void CMoveRiderDlg1::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
/*
	#if (_WIN32_IE >= 0x0300)
#define ListView_GetCheckState(hwndLV, i) \
   ((((UINT)(SNDMSG((hwndLV), LVM_GETITEMSTATE, (WPARAM)(i), LVIS_STATEIMAGEMASK))) >> 12) -1)
#endif
*/
	TRACE("OnNMClickList\n");
	/*	
	if(pNMListView->uOldState  & LVIS_SELECTED)
	{
		int nCheck = 0;
		for(int i = 0; i <= m_RiderList.GetItemCount(); i++)
		{		
			if(m_RiderList.GetCheck(i) == BST_CHECKED)
				nCheck++;

		}
		UpdateData();
		m_nCountNum = nCheck;
		UpdateData(FALSE);				
	}
*/
	
	*pResult = 0;
}

void CMoveRiderDlg1::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if(!(pNMListView->uNewState & LVIS_SELECTED)) return;

	UpdateData(FALSE);			
	DepositListIn(pNMLV->iItem);		
	GroupListIn(pNMLV->iItem);	

	*pResult = 0;
}

void CMoveRiderDlg1::OnBnClickedGroupButton()
{
	/*
	CGroupSettingDlg dlg;
	dlg.m_nCompanyCode = m_nCompany;
	dlg.m_nIntegrationCode = m_nCompany;
	dlg.m_bIntegrated = m_bIntegrated; // 통합이냐 지사냐
	dlg.m_nMode = MODIFY_MOD;
	if(dlg.DoModal() == IDOK)
	{
		int nItem = m_RiderList.GetSelectionMark();
		if(nItem <0) return;
		GroupListIn(nItem);	
	}
	*/
}

void CMoveRiderDlg1::OnTimer(UINT nIDEvent)
{
	int nCheck = 0;
	for(int i = 0; i <= m_RiderList.GetItemCount(); i++)
	{		
		if(m_RiderList.GetCheck(i) == BST_CHECKED)
			nCheck++;

	}

	char buffer[10];
	m_nCountNum = nCheck;
	((CStatic*)GetDlgItem(IDC_COUNT_STATIC))->SetWindowText(ltoa(nCheck, buffer, 10));

	CMyDialog::OnTimer(nIDEvent);
}

void CMoveRiderDlg1::OnBnClickedOldRiderCheck()
{	
	((CButton*)GetDlgItem(IDC_NEW_RIDER_CHECK))->SetCheck(0);
	((CEdit*)GetDlgItem(IDC_OPTION_START_EDIT))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_OPTION_END_EDIT))->EnableWindow(FALSE);
}

void CMoveRiderDlg1::OnBnClickedNewRiderCheck()
{
	((CButton*)GetDlgItem(IDC_OLD_RIDER_CHECK))->SetCheck(0);
	((CEdit*)GetDlgItem(IDC_OPTION_START_EDIT))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_OPTION_END_EDIT))->EnableWindow(TRUE);
	
}
