
// DlgMsg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RiderMsgDlg.h"
#include "RiderSMSDlg.h"
#include "RiderMsgAllDlg2.h"


// CRiderMsgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRiderMsgDlg, CMyDialog)
CRiderMsgDlg::CRiderMsgDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CRiderMsgDlg::IDD, pParent)
, m_strMsg(_T(""))
, m_strOldMsg(_T("")) 
, m_nSend(FALSE)
{
	m_nRNo = -1;
	m_nCompanyCode = m_ci.m_nCompanyCode;
	m_bIntegrated = FALSE;
	m_bStart = FALSE;
}

CRiderMsgDlg::~CRiderMsgDlg()
{	
}

void CRiderMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY_STATIC, m_stcHistory);
	DDX_Control(pDX, IDC_SEARCH_STATIC, m_stcSearch);
	DDX_Control(pDX, IDC_MSG_STATIC, m_stcMsg);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_RIDER_LIST, m_lstRider);
	DDX_Control(pDX, IDC_HISTORY_LIST, m_lstHistory);
	DDX_Control(pDX, IDC_COUNT_STATIC, m_stcCount);
	DDX_Control(pDX, IDC_SELECT_COUNT_STATIC, m_stcSelectCount);

	DDX_Control(pDX, IDC_DELETE_SEL_BTN, m_btnDeleteSel);
	DDX_Control(pDX, IDC_DELETE_ALL_BTN, m_btnDeleteAll);
	DDX_Control(pDX, IDC_NEW_BTN, m_btnNew);
	DDX_Control(pDX, IDC_SEND_BTN, m_btnSend);
	DDX_Control(pDX, IDC_CANCEL_BTN2, m_btnCancel);
	DDX_Control(pDX, IDC_EDIT_BTN, m_btnEdit);
	DDX_Text(pDX, IDC_MSG_EDIT, m_strMsg);
	DDX_Control(pDX, IDC_DELETE_INFO_CHK, m_chkDelete);
	DDX_Control(pDX, IDC_DELETE_INFO_COMBO, m_cmbDelete);
	DDX_Control(pDX, IDC_INFO_STATIC, m_stcInfo);
	DDX_Control(pDX, IDC_DELETE_INFO_COMBO, m_cmbDelete);
	DDX_Control(pDX, IDC_SMS_TYPE_COMBO, m_cmbSMS);
	DDX_Control(pDX, IDC_CURRENT_USER_HISTORY_LIST, m_lstCurrentUserHistory);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranch);

	DDX_Control(pDX, IDC_MAIN_COMBO, m_cmbMain);
	DDX_Control(pDX, IDC_BRANCH_EDIT, m_edtBranch);
	DDX_Control(pDX, IDC_OPEN_BRNACH_BTN, m_btnOpenBranch);
	DDX_Control(pDX, IDC_WORKING_CHECK, m_chkWorkibg);
	DDX_Control(pDX, IDC_NOT_WORKING_CHECK, m_chkNotWorkibg);

	DDX_Control(pDX, IDC_HISTORY_STATIC2, m_stcHistory2);
	DDX_Control(pDX, IDC_SEARCH_STATIC2, m_stcSearch2);
	DDX_Control(pDX, IDC_AUTO_DELETE_STATIC, m_stcAutoDelete);
	DDX_Control(pDX, IDC_MULTI_SELECT_STATIC, m_stcMultiSelect);
	DDX_Control(pDX, IDC_SEND_TYPE_STATIC, m_stcSendType);
	DDX_Control(pDX, IDC_SEND_ALL_BTN, m_btnSendAll);
}


BEGIN_MESSAGE_MAP(CRiderMsgDlg, CMyDialog)

	ON_BN_CLICKED(IDC_DELETE_INFO_CHK, OnBnClickedDeleteChk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SEND_BTN, OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_ALL_COMPANY_BUTTON, OnBnClickedAllCompanyBtn)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_RIDER_LIST, OnLvnItemchangedRiderList)
	ON_BN_CLICKED(IDC_NEW_BTN, OnBnClickedNewBtn)
	ON_EN_CHANGE(IDC_MSG_EDIT, OnEnChangeMsgEdit)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_WM_TIMER()
	//ON_NOTIFY(LVN_DELETEALLITEMS, IDC_HISTORY_LIST, OnLvnDeleteallitemsHistoryList)
	//ON_NOTIFY(NM_CLICK, IDC_HISTORY_LIST, OnNMClickHistoryList)
	ON_BN_CLICKED(IDC_DELETE_SEL_BTN, OnBnClickedDeleteSelBtn)
	ON_BN_CLICKED(IDC_DELETE_ALL_BTN, OnBnClickedDeleteAllBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN2, OnBnClickedCancelBtn2)
	ON_BN_CLICKED(IDC_EDIT_BTN, &CRiderMsgDlg::OnBnClickedEditBtn)
	ON_CBN_SELCHANGE(IDC_DELETE_INFO_COMBO, OnCbnSelchangeDeleteCombo)
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, OnCbnSelchangeBranchCombo)
	ON_CBN_DROPDOWN(IDC_BRANCH_COMBO, OnCbnDropdownBranchCombo)
	ON_NOTIFY(XTP_NM_GRID_SELCHANGED, IDC_RIDER_LIST, OnReportItemChange)
	ON_NOTIFY(NM_CLICK, IDC_HISTORY_LIST, OnReportItemMsgClick)
	ON_NOTIFY(NM_CLICK, IDC_CURRENT_USER_HISTORY_LIST, OnCurrentUSerHistoryReportItemMsgClick)

	ON_BN_CLICKED(IDC_OPEN_BRNACH_BTN, &CRiderMsgDlg::OnBnClickedOpenBrnachBtn)
	ON_MESSAGE(WM_CHANGE_BRANCH_ALL_CODE, OnChangeBrachAllCode)
	ON_BN_CLICKED(IDC_WORKING_CHECK, &CRiderMsgDlg::OnBnClickedWorkingCheck)
	ON_BN_CLICKED(IDC_NOT_WORKING_CHECK, &CRiderMsgDlg::OnBnClickedNotWorkingCheck)
	ON_BN_CLICKED(IDC_SEND_ALL_BTN, &CRiderMsgDlg::OnBnClickedSendAllBtn)
	ON_BN_CLICKED(IDC_SEND_DOWN_URL_BTN, &CRiderMsgDlg::OnBnClickedSendDownUrlBtn)
END_MESSAGE_MAP()


// CRiderMsgDlg 메시지 처리기입니다.

BOOL CRiderMsgDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	//SetWindowPos(&CWnd::wndTopMost, 0,0,0, 0, SWP_NOSIZE | SWP_NOMOVE);

	MakeModaless();
	CenterWindow();

	if((m_ci.m_nCompanyCode == 2900 || m_ci.m_nCompanyCode == 2750) && (m_ui.nRole == 0))
		m_btnSendAll.ShowWindow(SW_SHOW);

	m_chkWorkibg.SetCheck(TRUE);
	m_chkNotWorkibg.SetCheck(TRUE);

	int nCol = 0;
	m_lstRider.InsertColumn(nCol,"번호",LVCFMT_CENTER, 40);
	//if(m_bIntegrated)
	m_lstRider.InsertColumn(++nCol, "소속", LVCFMT_CENTER, 60);
	m_lstRider.InsertColumn(++nCol,"기사명",LVCFMT_LEFT, m_bIntegrated ? 90 : 120);
	m_lstRider.InsertColumn(++nCol,"",LVCFMT_LEFT, 0);  // sHp
	m_lstRider.InsertColumn(++nCol,"",LVCFMT_LEFT, 0);  // sTel
	m_lstRider.InsertColumn(++nCol,"",LVCFMT_LEFT, 0);  // nWorkState
	m_lstRider.GetPaintManager()->m_strNoItems = "";

	m_lstHistory.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lstHistory.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_lstHistory.InsertColumn(COL_DATE, "날짜/시간",LVCFMT_CENTER, 80);
	m_lstHistory.InsertColumn(COL_RECIVE, "대상",LVCFMT_LEFT, 80);
	m_lstHistory.InsertColumn(COL_MESSAGE," 내용",LVCFMT_LEFT, 240);
	m_lstHistory.InsertColumn(COL_WNO, "접수자사번",LVCFMT_LEFT, 50);
	m_lstHistory.InsertColumn(COL_WNAME, "접수자",LVCFMT_LEFT, 50);
	m_lstHistory.InsertColumn(COL_DT_READ," 읽은시간",LVCFMT_LEFT, 65);
	m_lstHistory.InsertColumn(COL_DT_DELETE, "삭제날짜", LVCFMT_LEFT, 80);
	m_lstHistory.InsertColumn(COL_MESSAGE_ID , "", LVCFMT_LEFT, 0);
	m_lstHistory.InsertColumn(COL_NO , "", LVCFMT_LEFT, 0);
	m_lstHistory.GetPaintManager()->m_strNoItems = "";

	m_lstCurrentUserHistory.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lstCurrentUserHistory.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_lstCurrentUserHistory.InsertColumn(COL_USER_HISITORY_DATE,				"날짜/시간",LVCFMT_CENTER, 80);
	m_lstCurrentUserHistory.InsertColumn(COL_USER_HISITORY_MESSAGE,			" 내용",LVCFMT_LEFT, 240);
	m_lstCurrentUserHistory.InsertColumn(COL_USER_HISITORY_RIDER_COMANY_NAME,	" 기사회사",LVCFMT_LEFT, 70);
	m_lstCurrentUserHistory.InsertColumn(COL_USER_HISITORY_RNO,				"기사사번",LVCFMT_LEFT, 60);
	m_lstCurrentUserHistory.InsertColumn(COL_USER_HISITORY_RNAME,				"기사이름",LVCFMT_LEFT, 60);
	m_lstCurrentUserHistory.InsertColumn(COL_USER_HISITORY_DT_READ,			" 읽은시간",LVCFMT_LEFT, 65);
	m_lstCurrentUserHistory.InsertColumn(COL_USER_HISITORY_MESSAGE_ID ,		"", LVCFMT_LEFT, 0);
	m_lstCurrentUserHistory.InsertColumn(COL_USER_HISITORY_NO ,				 "", LVCFMT_LEFT, 0);
	m_lstCurrentUserHistory.GetPaintManager()->m_strNoItems = "";

	m_cmbSMS.AddString("PDA전송(무료)");
	m_cmbSMS.AddString("PDA/SMS 동시전송");
	m_cmbSMS.AddString("기사별 가상계좌 전송");
	m_cmbSMS.SetCurSel(0);

	m_cBranchCombo.InitBranchCombo(&m_cmbMain, &m_edtBranch, &m_btnOpenBranch);
	m_cBranchCombo.SetParent(this);
	RefreshRiderList();

	if(m_paSelected.GetCount())
	{
		for(int i = m_lstRider.GetItemCount() - 1; i >= 0; --i )
		{
			int nListCode = m_lstRider.GetItemData(i);
			int nListRNo = atoi(m_lstRider.GetItemText(i,0));

			BOOL bDelete = TRUE;
			for(int n = 0, nSize = m_paSelected.GetCount(); n < nSize; ++n)
			{
				MSG_RIDER_INFO* pRiderInfo = m_paSelected.GetAt(n);
				if( pRiderInfo->nCompany == nListCode && nListRNo == pRiderInfo->nRNo)
				{
					bDelete = FALSE;
					break;
				}			
			}
			if(bDelete)
			{
				CXTPGridRecord *pRecord = m_lstRider.GetRecords()->GetAt(i);
				m_lstRider.GetRecords()->RemoveRecord(pRecord);
			}
		}

		m_lstRider.Populate();
	}

	if(m_lstRider.GetItemCount() > 0)
	{
		long nCompany = (long)m_lstRider.GetItemData(0);
		long nRNo = atol(m_lstRider.GetItemText(0, 0));
		RefreshHistory(nCompany,nRNo);

		RefreshWorkerHistory();

		CXTPGridSelectedRows* pSelRows = m_lstRider.GetSelectedRows();

		for(int i = 0; i < m_paSelected.GetCount(); i++)
		{
			for(int k = 0; k < m_lstRider.GetItemCount(); k++)
			{
				int nRNo = atol(m_lstRider.GetItemText(k, 0));
				long nCompany = (long)m_lstRider.GetItemData(k);
				MSG_RIDER_INFO *pMRI = m_paSelected.GetAt(i);

				if(nCompany == pMRI->nCompany && nRNo == pMRI->nRNo)
				{
					CXTPGridRow *pRow = m_lstRider.GetRows()->GetAt(k);
					pSelRows->Add(pRow);
				}
			}
		}
	}

	if(m_nRNo >= 0) {
		char buffer[10];
		m_edtSearch.SetWindowText(ltoa(m_nRNo, buffer, 10));
		OnEnChangeSearchEdit();
	}

	m_bStart = TRUE;
	//OnCbnSelchangeRiderCombo();
	OnEnChangeMsgEdit();
	RefreshSelectCount();

	m_chkDelete.SetCheck(AfxGetApp()->GetProfileInt("RiderMsg", "bDelete", 1));
	m_cmbDelete.SetCurSel(0);
	OnBnClickedDeleteChk();

	m_edtMsg.SetMyFont("맑은 고딕", 15, FW_NORMAL);
	m_edtMsg.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRiderMsgDlg::RefreshRiderList()
{
	int nItem = 0;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_list_for_report3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(TRUE);
	//pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_ci.m_bRcpIntMode1);
	if(!pRs.Execute(&pCmd)) return;

	m_lstRider.DeleteAllItems();

	int nCol = 1, nWorkState = 0;
	m_lstRider.InsertItem(nItem, "0");
	//if(m_bIntegrated)
		m_lstRider.SetItemText(nItem, nCol++, "전체그룹");
	m_lstRider.SetItemText(nItem, nCol++, "전체메시지");
	m_lstRider.SetItemData(nItem++, m_nCompanyCode);

	while(!pRs.IsEOF())
	{
		long nRNo, nCompany;
		CString strRName, strPhone, sID;
		char buffer[10];

		pRs.GetFieldValue("nMNo", nRNo);
		pRs.GetFieldValue("sName", strRName);
		pRs.GetFieldValue("lCode", nCompany);
		pRs.GetFieldValue("sHp", strPhone);
		pRs.GetFieldValue("sID", sID);
		pRs.GetFieldValue("nWorkState", nWorkState);

		nCol = 1;
		m_lstRider.InsertItem(nItem, ltoa(nRNo, buffer, 10));
		//if(m_bIntegrated)
			m_lstRider.SetItemText(nItem, nCol++, m_ci.GetBranchName(nCompany));
		m_lstRider.SetItemText(nItem, nCol++, strRName);		
		m_lstRider.SetItemText(nItem, nCol++, nWorkState ? "1" : "0");
		m_lstRider.SetItemText(nItem, nCol++, strPhone);
		m_lstRider.SetItemText(nItem, nCol++, sID);		
		m_lstRider.SetItemData(nItem, nCompany);
		m_lstRider.SetItemLong(nItem++, nWorkState);

		pRs.MoveNext();
	}

	pRs.Close();

	m_lstRider.Populate();
}

void CRiderMsgDlg::RefreshHistory(long nCompany, long nRNo)
{
	//	MessageBox("a");

	int nItem = 0;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_rider_msg_history3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo == 0 ? 0xFFFF : nRNo);
	if(!pRs.Execute(&pCmd)) return;

	m_lstHistory.DeleteAllItems();

	while(!pRs.IsEOF())
	{
		long nWNo, nID, nSendCount;
		char buffer[10];
		COleDateTime dtWrite, dtRead, dtDelete;
		CString *pstrMsg = new CString;
		CString sWName;
		BOOL	bWholeMsg;

		pRs.GetFieldValue("sMessage", *pstrMsg);
		pRs.GetFieldValue("nWNo", nWNo);
		pRs.GetFieldValue("sWName", sWName);
		pRs.GetFieldValue("dtWrite", dtWrite);
		pRs.GetFieldValue("dtRead", dtRead);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("bWholeCompany", bWholeMsg);
		pRs.GetFieldValue("dtDelete", dtDelete);
		pRs.GetFieldValue("nSendCount", nSendCount);


		m_lstHistory.InsertItem(nItem, dtWrite.Format("%m/%d %H:%M"));
		CString str;
		if( bWholeMsg )
		{
			//CBranchInfo *pBi = (CBranchInfo*)m_BranchCombo.GetItemData(0);
			//if(NULL == pBi) 
			//{
			//	AfxMessageBox("내부오류 0001");
			//	return;
			//}

			long nCurCompany; BOOL bIntegrated;
			CString sCodeList = "";

			m_cBranchCombo.GetVirtualCode(nCurCompany, bIntegrated, sCodeList);

			str.Format( "%s %d건", m_ci.GetBranchName(nCurCompany) + "(전체)", nSendCount);
		}

		else if( 65535 == nRNo || 0 == nRNo )
		{
			str.Format( "%s %d건", m_ci.GetBranchName(nCompany) + "(전체)", nSendCount);
		}
		else
		{
			str = "단독";
		}

		m_lstHistory.SetItemText(nItem, COL_RECIVE, str);
		m_lstHistory.SetItemText(nItem, COL_MESSAGE, *pstrMsg);
		m_lstHistory.SetItemText(nItem, COL_WNO, ltoa(nWNo, buffer, 10));
		m_lstHistory.SetItemText(nItem, COL_WNAME, sWName);
		m_lstHistory.SetItemText(nItem, COL_DT_READ, dtRead.Format("%H:%M"));
		m_lstHistory.SetItemText(nItem, COL_MESSAGE_ID, ltoa(nID, buffer, 10));
		m_lstHistory.SetItemText(nItem, COL_DT_DELETE, dtDelete.Format("%m/%d %H:%M"));
		m_lstHistory.SetItemData(nItem++, (DWORD)pstrMsg);

		pRs.MoveNext();
	}

	pRs.Close();	

	m_lstHistory.Populate();
}



/*
void CRiderMsgDlg::OnCbnSelchangeRiderCombo()
{
CString strMsg, strTemp;
COleDateTime dtLast;
BOOL bRead;

CMkRecordset pRs(m_pMkDb);
CMkCommand pCmd(m_pMkDb, "select_rider_msg");
pCmd.AddParameter(typeLong, typeInput, sizeof(int), FIRSTBRANCH(m_bIntegrated, m_nCompanyCode)); 
pCmd.AddParameter(typeLong, typeInput, sizeof(int), LASTBRANCH(m_bIntegrated, m_nCompanyCode));
pCmd.AddParameter(typeLong, typeInput, sizeof(int), (int)m_cmbRider.GetItemData(m_cmbRider.GetCurSel()));
if(!pRs.Execute(&pCmd)) return;

if(pRs.GetRecordCount() > 0)
{
pRs.GetFieldValue("bReadRiderMsg", bRead); 
pRs.GetFieldValue("sMessage", strMsg);
pRs.GetFieldValue("dtLastMsg", dtLast);

if(!strMsg.IsEmpty())
{
strTemp  = "[";
strTemp +=  dtLast.Format("%Y-%m-%d %H:%M:%S");
strTemp += "에 발송한 마지막 메세지]";
if(m_cmbRider.GetCurSel() != 0)
strTemp += bRead ? "(읽음)" : "(읽지않음)";
strTemp += "\r\n\r\n";
strTemp += strMsg;
}
m_OldMsgEdit.SetWindowText(strTemp);
}
else
{
m_OldMsgEdit.SetWindowText("");
}
pRs.Close();
}
*/

void CRiderMsgDlg::OnOK()
{
	//	CMyDialog::OnOK();
}


void CRiderMsgDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

void CRiderMsgDlg::OnBnClickedSendBtn()
{ 
	if(m_cmbSMS.GetCurSel() != 2)
	{
		if(m_edtMsg.GetWindowTextLength() <= 0)
		{
			MessageBox("메세지를 입력 하세요", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	long nSelCount = m_lstRider.GetSelectedRows()->GetCount();
	if(IsAllRider())
	{
		if(IDNO == MessageBox("전체기사님에게 전송하시겠습니까?", "전송범위", MB_YESNO))
			return;
	}
	else if(nSelCount > 0)
	{
		CString strTemp;
		strTemp.Format("%d명의 기사님에게 전송하시겠습니까?", nSelCount);
		if(IDNO == MessageBox(strTemp, "전송범위", MB_YESNO))
			return;
	}

	if( m_cmbSMS.GetCurSel() == 1 ) 
	{ 
		OnBnClickedSendBothBtn();
		return;
	}
	else if( m_cmbSMS.GetCurSel() == 2 ) 
	{
		OnBnClickedSendVRAccountBtn();
		return;
	}
	else if( m_cmbSMS.GetCurSel() != 0 )
		return;

	if(!POWER_CHECK(1201, "기사공지 전송/수정", TRUE))
		return;

	m_edtMsg.GetWindowText(m_strMsg);

	if(m_strMsg.GetLength() > 1000) 
	{
		MessageBox("메시지 길이는 최대 1000자까지만 가능합니다.\n\n"\
			"대리2005 클라이언트(휴대폰/PDA)는 256자만 표시되며,\n\n"\
			"대리2006 클라이언트는 1000자 모두 표시됩니다.",
			"길이 초과",
			MB_ICONINFORMATION);
		return;
	}

	BOOL bWholeAlliance = FALSE;
	BOOL bAlreadyQuery = FALSE;
	int nItem = -1, nCount = 0;

	CXTPGridSelectedRows *pRows = m_lstRider.GetSelectedRows();

	for(int i = 0; i<nSelCount; i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);
		nItem = pRow->GetIndex();

		if(m_ci.m_nCompanyCode == 6500 || m_ci.m_nCompanyCode == 5396 || m_ci.m_nCompanyCode == 6464 || m_ci.m_nCompanyCode == 6050)
		{
			long nRNo = atol(m_lstRider.GetItemText(nItem, 0));
			if(nRNo == 0 && !bAlreadyQuery)
			{
				if(IDYES == MessageBox("연합전체기사님에게 전송하시겠습니까?", "전송범위", MB_YESNO))
				{
					bWholeAlliance = TRUE;
				}
				bAlreadyQuery = TRUE;
			}
		}

		if(SendPDAMsg(nItem, bWholeAlliance))
			nCount++;
	}


	if(nCount == 0)
	{
		MessageBox("기사를 선택하여 주시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}
	else {

		CString strMsg, strCount;

		if(nCount > 1)
		{
			strCount.Format("%d명의 기사님에게 전송되었습니다.", nCount);
		}
		else {
			strCount.Format("메시지를 성공적으로 전송하였습니다.");
		}

		if(m_chkDelete.GetCheck() == BST_CHECKED)
		{
			CString str, strCmb, strStc;
			long nIndex = m_cmbDelete.GetCurSel();
			m_cmbDelete.GetLBText(nIndex, strCmb);

			m_stcInfo.GetWindowText(strStc);

			strMsg.Format("%s\n\n%s", strCount,strStc);                        
		}
		else
			strMsg = strCount;

		MessageBox(strMsg, "확인", MB_ICONINFORMATION);

		long nCompany = (long)m_lstRider.GetItemData(nItem);
		long nRNo = atol(m_lstRider.GetItemText(nItem, 0));
		RefreshHistory(nCompany,nRNo);

		RefreshWorkerHistory();
		//CMyDialog::OnOK();
	}
}


void CRiderMsgDlg::OnBnClickedSendVRAccountBtn()
{	

	int nItem = -1, nCount = 0;
	for(int i = 0; i < m_lstRider.GetSelectedRows()->GetCount(); i++)
	{
		CXTPGridRow *pRow = m_lstRider.GetSelectedRows()->GetAt(i);
		nItem = pRow->GetIndex();
		if(SendVRAcoountMsg(nItem))		
			nCount++;
	}
	/*while((nItem = m_lstRider.GetNextItem(nItem, LVNI_SELECTED)) != -1)
	{
		if(SendVRAcoountMsg(nItem))		
			nCount++;
	}*/

	if(nCount == 0)
	{
		MessageBox("기사를 선택하여 주시기 바랍니다.", "확인", MB_ICONINFORMATION);
		return;
	}
	else {
		CString strMsg;
		strMsg.Format("%d명의 기사님에게 전송되었습니다.", nCount);
		MessageBox(strMsg, "확인", MB_ICONINFORMATION);
		//CMyDialog::OnOK();

		nItem = m_lstRider.GetNextItem(nItem, LVNI_SELECTED);
		if(nItem == -1 ) return;

		long nRNo = atol(m_lstRider.GetItemText(nItem, 0));
		long nCompany = (long)m_lstRider.GetItemData(nItem);

		RefreshHistory(nCompany,nRNo);

		RefreshWorkerHistory();
	}
}

BOOL CRiderMsgDlg::SendVRAcoountMsg(int nItem)
{
	long nRNo = atol(m_lstRider.GetItemText(nItem, 0));
	long nCompany = (long)m_lstRider.GetItemData(nItem);

	UpdateData(TRUE);
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_send_rider_vraccout_info2");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), m_bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo == 0 ? 0xFFFF : nRNo);	
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);
	if(!pCmd.Execute()) 
		return FALSE;

	int nOutPut = 0;
	pPar->GetValue(nOutPut);
	if(nOutPut == 1000)
	{
		CString strMsg;
		strMsg.Format("%d번 기사님은 계좌가 없습니다.", nRNo);
		MessageBox(strMsg, "확인",MB_ICONINFORMATION   );
		return FALSE;
	}
	else
		return TRUE;
}


BOOL CRiderMsgDlg::SendPDAMsg(int nItem, BOOL bWholeAlliance)
{
	long nIndex = m_cmbDelete.GetCurSel();
	long nRiderCompany = (long)m_lstRider.GetItemData(nItem);
	CString sDay;
	m_cmbDelete.GetLBText(nIndex, sDay);

	//CBranchInfo *pBi = (CBranchInfo*)m_BranchCombo.GetItemData(m_BranchCombo.GetCurSel());

	long nCurCompany = 0;
	BOOL bIntegrated = 0;
	CString sCodeList = "";

	m_cBranchCombo.GetVirtualCode(nCurCompany, bIntegrated, sCodeList);

	long nRNo = atol(m_lstRider.GetItemText(nItem, 0));

	if((nRNo == 0) && (bIntegrated == FALSE)) // 지사전체메세지
		nRiderCompany = nCurCompany;

	UpdateData(TRUE);
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "edit_rider_msg10"); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCurCompany);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), bIntegrated);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRiderCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo == 0 ? 0xFFFF : nRNo);
	pCmd.AddParameter(typeString, typeInput, m_strMsg.GetLength(), m_strMsg);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), bWholeAlliance);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), m_chkDelete.GetCheck() == BST_CHECKED ? 1 : 0);
	pCmd.AddParameter(typeBool, typeInput, sizeof(int), _ttoi(sDay));
	pCmd.AddParameter(typeString, typeInput, m_ui.strName.GetLength(), m_ui.strName);
	if(!pCmd.Execute()) 
		return FALSE;

	return TRUE;
}

//void CRiderMsgDlg::OnLvnItemchangedRiderList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	//KillTimer(0);
//	//SetTimer(0, 500, NULL);		
//
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//
//	if(!(pNMListView->uNewState & LVIS_SELECTED)) return;
//	
//	
//	long nCompany = (long)m_lstRider.GetItemData(pNMListView->iItem);
//	long nRNo = atol(m_lstRider.GetItemText(pNMListView->iItem, 0));
//
//	if(nRNo == 0) nRNo = 0xFFFF;
//	
//	RefreshSelectCount();
//	RefreshHistory(nCompany, nRNo);
//	OnEnChangeMsgEdit();
//	
//	
//	//
//
//	*pResult = 0;
//}

void CRiderMsgDlg::OnBnClickedNewBtn()
{
	m_edtMsg.SetWindowText("");
	OnEnChangeMsgEdit();
}

void CRiderMsgDlg::OnEnChangeMsgEdit()
{
	CString strMsg, strCount;
	m_edtMsg.GetWindowText(strMsg);
	strCount.Format("글자수: %d", strMsg.GetLength());
	m_stcCount.SetWindowText(strCount);
}

BOOL CRiderMsgDlg::IsAllRider()
{
	CXTPGridSelectedRows *pRows = m_lstRider.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++)
	{
		CXTPGridRow *pRow = pRows->GetAt(i);

		if(m_lstRider.GetItemText(pRow->GetIndex(), 2) == "전체메시지")
			return TRUE;
	}

	return FALSE;
}


void CRiderMsgDlg::OnBnClickedSendBothBtn()
{
	if(!POWER_CHECK(1201, "기사공지 전송/수정", TRUE))
		return;

	UpdateData();
	int nItem = -1, nCount = 0;
	BOOL bAllRider = IsAllRider();

	CString strMent, strCmb, strStc;
	long nIndex = m_cmbDelete.GetCurSel();

	if(m_chkDelete.GetCheck() == BST_CHECKED)
	{
		m_cmbDelete.GetLBText(nIndex, strCmb);
		m_stcInfo.GetWindowText(strStc);
		strMent.Format("%s%s", strCmb, strStc);
	}
	else
		strMent = "";

	long nSelectCount = 0;

	CXTPGridSelectedRows *pRows = m_lstRider.GetSelectedRows();

	nSelectCount = pRows->GetCount();	

	if(nSelectCount > 1 || bAllRider)
	{
		CRiderMsgAllDlg2 dlg;
		dlg.m_bAllRider = bAllRider;
		dlg.m_List2 = &m_lstRider;
		dlg.m_bIntegrated = m_bIntegrated;
		dlg.m_nCompany = m_nCompanyCode;
		dlg.m_strMessageMent = m_strMsg;

		if(dlg.DoModal() == IDOK)
		{
			for(int nRow = 0; nRow < nSelectCount; nRow++)
			{
				CXTPGridRow *pRow = pRows->GetAt(nCount);
				nItem = pRow->GetIndex();

				//if(nItem == 0)
				//	continue;
				if(SendPDAMsg(nItem))
					nCount++;
				//}
			}

			if(nCount > 0)
				RefreshWorkerHistory();

			/*while((nItem = m_lstRider.GetNextItem(nItem, LVNI_SELECTED)) != -1)
			{
				if(SendPDAMsg(nItem))
					nCount++;
			}*/
		}
	}
	else
	{
		for(int nRow = 0; nRow < nSelectCount; nRow++)
		{
			CXTPGridRow *pRow = pRows->GetAt(nRow);
			nItem = pRow->GetIndex();

			if(SendRiderSMS(nItem))
				if(SendPDAMsg(nItem))
					nCount++;
		}
	/*	while((nItem = m_lstRider.GetNextItem(nItem, LVNI_SELECTED)) != -1)
		{
			if(SendRiderSMS(nItem))
				if(SendPDAMsg(nItem))
					nCount++;
		}*/
		if(nCount == 0)
		{
			MessageBox("기사를 선택하여 주시기 바랍니다.", "확인", MB_ICONINFORMATION);
			return;
		}
		else {
			CString strMsg;
			strMsg.Format("%d명의 기사님에게 전송되었습니다. \r\n휴대폰 번호가 정확하지 않은 기사님은 SMS가 전송되지 않습니다.", nCount);

			if(strMent != "")
				strMsg += "\n\n" + strMent;
			else
			{
				strMsg.Format("%d명의 기사님에게 전송되었습니다.\r\n휴대폰 번호가 정확하지 않은 기사님은 SMS가 전송되지 않습니다.", nCount);
				strMsg += "\n\n" + strMent;
			}

			MessageBox(strMsg, "확인", MB_ICONINFORMATION);
			CMyDialog::OnOK();
		}
	}

	if(nCount > 0)
	{
		nItem = m_lstRider.GetNextItem(nItem, LVNI_SELECTED);
		if(nItem == -1 ) return;

		long nCompany = (long)m_lstRider.GetItemData(nItem);
		long nRNo = atol(m_lstRider.GetItemText(nItem, 0));
		RefreshHistory(nCompany,nRNo);

		RefreshWorkerHistory();
	}
}

void CRiderMsgDlg::OnEnChangeSearchEdit()
{
	FilterRider();
}

BOOL CRiderMsgDlg::SendRiderSMS(int nItem)
{
	UpdateData(TRUE);
	CString strEtc;

	//if(nItem == 0)
	//{
	//	MessageBox("SMS 전직원전송은 아직 지원하지 않습니다.", "확인", MB_ICONINFORMATION);
	//	return FALSE;
	//}

	long nCompany = (long)m_lstRider.GetItemData(nItem);
	long nRNo = atol(m_lstRider.GetItemText(nItem, 0));
	//CString strPhone = m_lstRider.GetItemText(nItem, m_bIntegrated ? 4 : 3);
	CString strPhone = m_lstRider.GetItemText(nItem, 4);
	if(strPhone.IsEmpty() || strPhone.Left(2) != "01") 
	{
		//MessageBox("기사 전화번호가 존재하지 않거나, 휴대폰 번호가 아닙니다.", "확인", MB_ICONINFORMATION);
		return FALSE;
	}

	CRiderSMSDlg dlg;
	dlg.m_nCompany = nCompany;
	dlg.m_strRiderPN = strPhone;
	//dlg.m_strRecvPN = m_ci.m_strOfficePhone;
	//encProfile.GetString("sms", "callback", "");

	dlg.m_strMsg = m_strMsg;
	if(IDOK == dlg.DoModal())
	{
		//encProfile.WriteString("sms", "callback", dlg.m_strRecvPN);

		dlg.m_strRecvPhone = GetNoneDashNumber(dlg.m_strRecvPhone);
		dlg.m_strRiderPN = GetNoneDashNumber(dlg.m_strRiderPN);

		if(!::SendSmsNew(m_ci.m_nCompanyCode, 555, dlg.m_strRiderPN, dlg.m_strRecvPhone, dlg.m_strMsg, "기사공지", "", ""))
		{
			MessageBox("SMS 전송 실패", "전송실패", MB_ICONINFORMATION);
			return FALSE;
		}

	/*

		CMkCommand pCmd(m_pMkDb, "insert_sms_data2");
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), 555);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strRiderPN.GetLength(), dlg.m_strRiderPN);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strRecvPN.GetLength(), dlg.m_strRecvPN);
		pCmd.AddParameter(typeString, typeInput, dlg.m_strMsg.GetLength(), dlg.m_strMsg);
		pCmd.AddParameter(typeString, typeInput, strEtc.GetLength(), strEtc);
		if(!pCmd.Execute()) 
		{
			MessageBox("SMS 전송 실패", "전송실패", MB_ICONINFORMATION);
			return FALSE;
		}

		*/

		return TRUE;
	}

	return FALSE;
}


void CRiderMsgDlg::OnTimer(UINT nIDEvent)
{
	/*int nItem = m_lstRider.GetNextItem(-1, LVNI_SELECTED);

	if(nItem >= 0) {
	long nCompany = (long)m_lstRider.GetItemData(nItem);
	long nRNo = atol(m_lstRider.GetItemText(nItem, 0));

	if(nRNo == 0) nRNo = 0xFFFF;

	RefreshHistory(nCompany, nRNo);
	OnEnChangeMsgEdit();
	}

	KillTimer(nIDEvent);*/

	CMyDialog::OnTimer(nIDEvent);
}


void CRiderMsgDlg::RefreshSelectCount()
{
	int nItem = -1, nCount = 0;
	CString strCount;
	BOOL bAll = FALSE;

	/*while((nItem = m_lstRider.GetNextItem(nItem, LVNI_SELECTED)) >= 0)
	{
		if((nItem == 0) && (m_lstRider.GetItemText(nItem, 1) == "전체그룹")) {
			bAll = TRUE;
			break;
		}
		nCount++;		
	}*/

	//nItem = m_lstRider.GetNextItem(nItem, LVNI_SELECTED);
	nItem = m_lstRider.GetSelectedItem();//GetNextItem(nItem, LVNI_SELECTED);
	//if(nItem == 0 && m_lstRider.GetSe)

	if(nItem == 0)
		bAll = TRUE;

	strCount.Format("전송대상 기사 %d분", bAll ? m_lstRider.GetRows()->GetCount() - 1 : m_lstRider.GetSelectedRows()->GetCount());
	m_stcSelectCount.SetWindowText(strCount);
}

//void CRiderMsgDlg::OnLvnDeleteallitemsHistoryList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//
//	for(int i = 0; i < m_lstHistory.GetItemCount(); i++)
//	{
//		CString *pstrMsg = (CString*)m_lstHistory.GetItemData(i);
//		delete pstrMsg;
//	}
//
//	*pResult = 0;
//}



//void CRiderMsgDlg::OnNMClickHistoryList(NMHDR *pNMHDR, LRESULT *pResult)
//{
//
//	int nItem = m_lstHistory.GetNextItem(-1, LVNI_SELECTED);
//	
//	if(nItem >= 0) {
//		CString *pstrMsg = (CString*)m_lstHistory.GetItemData(nItem);
//		m_edtMsg.SetWindowText(*pstrMsg);
//		OnEnChangeMsgEdit();
//	}
//
//	*pResult = 0;
//}

void CRiderMsgDlg::OnBnClickedDeleteSelBtn()
{
	if(!POWER_CHECK(1202, "기사공지 삭제", TRUE))
		return;

	//CWaitCursor wait;
	int nItem = m_lstHistory.GetNextItem(-1, LVNI_SELECTED);
	if(nItem >= 0) {
		CMkCommand pCmd(m_pMkDb, "delete_rider_sel_msg2");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), atol(m_lstHistory.GetItemText(nItem, COL_MESSAGE_ID)));
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		if(pCmd.Execute()) {
			int nItem2 = m_lstRider.GetNextItem(-1, LVNI_SELECTED);
			if(nItem2 >= 0) {
				long nRNo = atol(m_lstRider.GetItemText(nItem2, 0));
				long nCompany = (long)m_lstRider.GetItemData(nItem2);
				if(nRNo == 0) nRNo = 0xFFFF;
				RefreshHistory(nCompany, nRNo);
				RefreshWorkerHistory();
			}
		}
	}
}

void CRiderMsgDlg::OnBnClickedDeleteAllBtn()
{
	if(!POWER_CHECK(1202, "기사공지 삭제", TRUE))
		return;


	if(IDYES == MessageBox("해당기사의 전체메시지를 삭제하시겠습니까?",
		"삭제확인", MB_YESNO))
	{
		//CWaitCursor wait;
		int nItem = m_lstRider.GetNextItem(-1, LVNI_SELECTED);
		if(nItem >= 0) {
			long nRNo = atol(m_lstRider.GetItemText(nItem, 0));
			long nCompany = (long)m_lstRider.GetItemData(nItem);

			CMkCommand pCmd(m_pMkDb, "delete_all_rider_msg_list");
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nCompany);
			pCmd.AddParameter(typeLong, typeInput, sizeof(int), nRNo == 0 ? 0xFFFF : nRNo);
			if(pCmd.Execute())		
			{
				RefreshHistory(nCompany, nRNo);
			}
		}
	}
}

void CRiderMsgDlg::OnBnClickedCancelBtn2()
{
	OnCancel();
}

void CRiderMsgDlg::OnBnClickedEditBtn()
{
	if(!POWER_CHECK(1201, "기사공지 수정", TRUE))
		return;

	int index = m_lstHistory.GetNextItem(-1 , LVNI_SELECTED);

	if(index == -1) return;

	int nId = atoi(m_lstHistory.GetItemText(index,COL_MESSAGE_ID));

	CString sMessage;
	m_edtMsg.GetWindowText(sMessage);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_rider_msg_for_edit");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), nId);
	pCmd.AddParameter(typeString, typeInput, sMessage.GetLength(), sMessage);

	if(!pRs.Execute(&pCmd))
	{
		MessageBox("업데이트 실패", "확인", MB_ICONERROR);
	}
	else
	{
		MessageBox("업데이트 성공", "확인", MB_ICONINFORMATION);
		m_edtMsg.SetWindowTextA("");
		int nItem = m_lstRider.GetNextItem(-1 , LVNI_SELECTED);
		if(nItem == -1 ) return;

		RefreshHistory(m_nCompanyCode, atoi(m_lstRider.GetItemText(nItem, 0)) );
	}
	//MessageBox("내용수정", "확인", MB_ICONINFORMATION);
}

void CRiderMsgDlg::OnCbnSelchangeDeleteCombo()
{
	OnBnClickedDeleteChk();
}

void CRiderMsgDlg::OnCbnSelchangeBranchCombo()
{
	FilterRider();
}

void CRiderMsgDlg::FilterRider()
{
	char buffer [10];
	m_edtSearch.GetWindowText(m_strSearch);

	long nCount = m_lstRider.GetRecords()->GetCount();

	long nSelCompany = 0;
	BOOL bIntegrated = 0;
	CString sCodeList = "";
	m_cBranchCombo.GetVirtualCode(nSelCompany, bIntegrated, sCodeList);

	for(int i = 0; i < nCount; i++)
	{ 
		if(i==0) continue; //전체메세지

		CString strName, sRNo, sCompany;

		CXTPGridColumn *pColumn = NULL;
		CXTPGridRecord *pRecord = m_lstRider.GetRecords()->GetAt(i);

		sRNo = ((CXTPGridRecordItemText*)pRecord->GetItem(0))->GetCaption(pColumn);

		//if(m_bIntegrated)
			strName = ((CXTPGridRecordItemText*)pRecord->GetItem(2))->GetCaption(pColumn);
		//else
		//	strName = ((CXTPGridRecordItemText*)pRecord->GetItem(1))->GetCaption(pColumn);

		long nCompany = m_lstRider.GetItemData(pRecord);
		sCompany = (CString)itoa(nCompany, buffer, 10) + ",";

		BOOL bShow = TRUE;

		if(bIntegrated == TRUE) 
		{
			if(sCodeList != "")
			{
				if(sCodeList.Find(sCompany) == -1)
					bShow = FALSE;
			}
			//else
			//{
			//	if(nSelCompany != atoi(sCompany))
			//	{
			//		sCompany.Replace(",", "");
			//		bShow = FALSE;
			//	}
			//}
		}
		else
		{
			if(nSelCompany != atoi(sCompany))
			{
				sCompany.Replace(",", "");
				bShow = FALSE;
			}
		}

		if(bShow)
		{
			if(sRNo.Find(m_strSearch) < 0 && 
				strName.Find(m_strSearch) < 0)
				bShow = FALSE;

		}

		BOOL bWork = m_chkWorkibg.GetCheck();
		BOOL bNotWork = m_chkNotWorkibg.GetCheck();
		long nWorkState = m_lstRider.GetItemLong(pRecord);

		if((bWork == FALSE) && (nWorkState == 0))
			bShow = FALSE;
		if((bNotWork == FALSE) && (nWorkState == 1))
			bShow = FALSE;

		pRecord->SetVisible(bShow); 
	}

	m_lstRider.Populate(); 

	if(m_lstRider.GetVisibleItemCount() > 1) // 2개이상 1번이 모두선택
	{
		CXTPGridRows *pRows = m_lstRider.GetRows();
		CXTPGridRow *pRow = pRows->GetAt(1);
		m_lstRider.GetSelectedRows()->Select(pRow);
	}
}


void CRiderMsgDlg::OnBnClickedDeleteChk()
{
	if(m_chkDelete.GetCheck() == BST_CHECKED)
	{
		m_cmbDelete.EnableWindow(TRUE);

		CString str, strFormat;
		long index = m_cmbDelete.GetCurSel();
		m_cmbDelete.GetLBText(index, str);

		COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
		COleDateTimeSpan span(_ttoi(str), 0, 0, 0);

		COleDateTime dtTime = dtCurrent + span;

		strFormat.Format("%d월%d일 9시에 자동삭제.", dtTime.GetMonth(), dtTime.GetDay());

		m_stcInfo.SetWindowText(strFormat);
	}
	else
	{
		m_cmbDelete.EnableWindow(FALSE);
		m_stcInfo.SetWindowText("영구보존 됩니다.");
	}

	AfxGetApp()->WriteProfileInt("RiderMsg", "bDelete", m_chkDelete.GetCheck());
}

void CRiderMsgDlg::OnReportItemChange(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridSelectedRows *pRows = m_lstRider.GetSelectedRows();

	if(pRows == NULL) return;
	if(pRows->GetCount() == 0) return;

	CXTPGridRecord *pRecord = pRows->GetAt(0)->GetRecord();

	int nRNo = atol(m_lstRider.GetItemText(pRecord, 0));
	long nCurCompany = m_lstRider.GetItemData(pRecord);

	if(nRNo == 0) nRNo = 0xFFFF;

	RefreshSelectCount();
	RefreshHistory(nCurCompany, nRNo);
	OnEnChangeMsgEdit();
}

void CRiderMsgDlg::OnReportItemMsgClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nItem = m_lstHistory.GetNextItem(-1, LVNI_SELECTED);

	if(nItem >= 0) {
		CString *pstrMsg = (CString*)m_lstHistory.GetItemData(nItem);
		m_edtMsg.SetWindowText(*pstrMsg);
		OnEnChangeMsgEdit();
	}
}
void CRiderMsgDlg::OnBnClickedAllianceMsgBtn()
{

}

void CRiderMsgDlg::RefreshWorkerHistory()
{
	int nItem = 0;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_worker_msg_history3");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode); 
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ui.nWNo);
	COleDateTime dtFrom = COleDateTime::GetCurrentTime() - COleDateTimeSpan(7, 0, 0, 0);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtFrom);

	if(!pRs.Execute(&pCmd)) return;

	m_lstCurrentUserHistory.DeleteAllItems();
	long nCount = pRs.GetRecordCount();

	while(!pRs.IsEOF())
	{
		long nCompany,nRNo, nID;
		char buffer[10];
		COleDateTime dtWrite, dtRead;
		CString *pstrMsg = new CString;
		CString sName;
		BOOL	bWholeCompany;

		pRs.GetFieldValue("sMessage", *pstrMsg);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("sName", sName);
		pRs.GetFieldValue("dtWrite", dtWrite);
		pRs.GetFieldValue("dtRead", dtRead);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("bWholeCompany", bWholeCompany);

		m_lstCurrentUserHistory.InsertItem(nItem, dtWrite.Format("%m/%d %H:%M"));
		m_lstCurrentUserHistory.SetItemText(nItem, COL_USER_HISITORY_MESSAGE,			*pstrMsg);
		m_lstCurrentUserHistory.SetItemText(nItem, COL_USER_HISITORY_RIDER_COMANY_NAME,bWholeCompany ? "전체" : m_ci.GetBranchName(nCompany)); // 여기 수정해야 함....
		m_lstCurrentUserHistory.SetItemText(nItem, COL_USER_HISITORY_RNO,				nRNo == 65535 ? "전체" : ltoa(nRNo, buffer, 10));
		CString str;
		if(nRNo == 65535) str = "전체";
		else if(sName == "복수선택") { str = ltoa(nID, buffer, 10); str += "건"; }
		else str = ltoa(nID, buffer, 10);
		m_lstCurrentUserHistory.SetItemText(nItem, COL_USER_HISITORY_RNAME,			str);
		m_lstCurrentUserHistory.SetItemText(nItem, COL_USER_HISITORY_DT_READ,			nRNo == 65535 ? "-" : dtRead.Format("%H:%M"));
		m_lstCurrentUserHistory.SetItemText(nItem, COL_USER_HISITORY_MESSAGE_ID,		nRNo == 65535 ? "-" : ltoa(nID, buffer, 10));
		m_lstCurrentUserHistory.SetItemData(nItem++, (DWORD)pstrMsg);		

		pRs.MoveNext();
	}

	pRs.Close();	

	m_lstCurrentUserHistory.Populate();

}

void CRiderMsgDlg::OnCurrentUSerHistoryReportItemMsgClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nItem = m_lstCurrentUserHistory.GetNextItem(-1, LVNI_SELECTED);

	if(nItem >= 0) {
		CString *pstrMsg = (CString*)m_lstCurrentUserHistory.GetItemData(nItem);
		m_edtMsg.SetWindowText(*pstrMsg);
		OnEnChangeMsgEdit();
	}
}


void CRiderMsgDlg::OnBnClickedAllCompanyBtn()
{ 
	m_cBranchCombo.InitBranchCombo(&m_cmbMain, &m_edtBranch, &m_btnOpenBranch);
	RefreshRiderList();
	FilterRider();
	//m_BranchCombo.SetCurSel(0);
}

void CRiderMsgDlg::FilterListControl(int nCompany, int nRNo)
{
	// 	int nSel = m_BranchCombo.GetCurSel();
	// 	int nComboCode = m_BranchCombo.GetItemData(nSel);

	for(int i =m_lstRider.GetItemCount() - 1; i >= 0; --i)
	{
		int nListCode = m_lstRider.GetItemData(i);
		int nListRNo = atoi(m_lstRider.GetItemText(i,0));
		// 일단 회사 코드가 틀리면 삭제
		if( nCompany != nListCode )
		{
			CXTPGridRecord *pRecord = m_lstRider.GetRecords()->GetAt(i);
			m_lstRider.GetRecords()->RemoveRecord(pRecord);
		}
		// 회사코드가 같은 행이라도
		// 직원필터안함(nRNo == -1)이 아니고 직원번호가 틀리면 삭제
		if(nRNo != -1 && nRNo != nListRNo )
		{
			CXTPGridRecord *pRecord = m_lstRider.GetRecords()->GetAt(i);
			m_lstRider.GetRecords()->RemoveRecord(pRecord);
		}
	}

	m_lstRider.Populate();

}

void CRiderMsgDlg::OnCbnDropdownBranchCombo()
{
	//int nSel = m_BranchCombo.GetCurSel();
	//if(nSel != 0)
	//{
	//	RefreshRiderList();
	//}
}
void CRiderMsgDlg::OnBnClickedOpenBrnachBtn()
{
	m_cBranchCombo.OpenBranchDlg();
}

LONG CRiderMsgDlg::OnChangeBrachAllCode(WPARAM wParam, LPARAM lParam)
{	
	FilterRider();
	return 0;
}

void CRiderMsgDlg::OnBnClickedWorkingCheck()
{
	FilterRider();
}

void CRiderMsgDlg::OnBnClickedNotWorkingCheck()
{
	FilterRider();
}

void CRiderMsgDlg::OnBnClickedSendAllBtn()
{
	if((m_ci.m_nCompanyCode == 2900 || m_ci.m_nCompanyCode == 2750) && (m_ui.nRole == 0))
	{
		CString strMsg;
		m_edtMsg.GetWindowText(strMsg);

		if(strMsg.GetLength() <= 0)
		{
			MessageBox("메세지를 입력하세요", "확인", MB_ICONINFORMATION);
			return;
		}

		CString strTemp;
		strTemp.Format("해당 메세지를 즉시공유 전체기사님에게 전송하시겠습니까?\r\n\r\n[%s]", strMsg);

		if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
			return;

		CMkCommand pCmd(m_pMkDb, "insert_all_share_rider_msg");
		pCmd.AddParameter(m_ci.m_nCompanyCode);
		pCmd.AddParameter(strMsg);

		if(pCmd.Execute())
		{
			MessageBox("메세지를 성공적으로 전송되었습니다", "확인", MB_ICONINFORMATION);
			OnOK();
		}
	}
}

void CRiderMsgDlg::OnBnClickedSendDownUrlBtn()
{
	//m_edtMsg.SetWindowText("로지소프트\r\nhttp://market.android.com/details?id=com.logisoft.Quick1");
	m_edtMsg.SetWindowText("로지퀵 다운로드\r\n↓아래 클릭↓\r\nhttp://goo.gl/UEPsNr\r\n다운로드후 실행하여 설치요망!");
	//http://goo.gl/UEPsNr

}
