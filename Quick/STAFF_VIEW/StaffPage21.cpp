// StaffForm17.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "StaffPage21.h"
 #include "ChangeAllocGroupInfoDlg.h"
#include "RiderMsgDlg.h"
#include "LogiUtil.h"
#include "VarietyDlg3.h"


// CStaffPage21

IMPLEMENT_DYNCREATE(CStaffPage21, CMyFormView)

CStaffPage21::CStaffPage21()
	: CMyFormView(CStaffPage21::IDD)
{
}

CStaffPage21::~CStaffPage21()
{
}

void CStaffPage21::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRADE_LIST, m_lstGrade);
	DDX_Control(pDX, IDC_RIDER_LIST, m_lstRider);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_HELP_STATIC, m_stcHelp);
}

BEGIN_MESSAGE_MAP(CStaffPage21, CMyFormView)
	ON_BN_CLICKED(IDC_REFRESH_GRADE_BTN, OnBnClickedRefreshGradeBtn)
	ON_BN_CLICKED(IDC_REFRESH_RIDER_BTN, OnBnClickedRefreshRiderBtn)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_RIDER_LIST, OnReportBeginDrag)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, OnEnChangeSearchEdit)
	ON_CBN_SELCHANGE(IDC_TYPE_COMBO, OnCbnSelchangeTypeCombo)
	ON_NOTIFY(NM_DBLCLK, IDC_GRADE_LIST, OnReportItemDblClick)
	ON_NOTIFY(NM_CLICK, IDC_GRADE_LIST, OnReportItemClick)
	ON_NOTIFY(NM_CLICK, IDC_RIDER_LIST, OnReportItemClickRider)
	ON_BN_CLICKED(IDC_SEND_MSG_BTN, &CStaffPage21::OnBnClickedSendMsgBtn)
END_MESSAGE_MAP()


// CStaffPage21 진단입니다.

#ifdef _DEBUG
void CStaffPage21::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CStaffPage21::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CStaffPage21 메시지 처리기입니다.

void CStaffPage21::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	m_lstRider.InsertColumn(0, "소속회사", LVCFMT_LEFT, 80);
	m_lstRider.InsertColumn(1, "사번", LVCFMT_LEFT, 50);
	m_lstRider.InsertColumn(2, "이름", LVCFMT_LEFT, 120);
	m_lstRider.InsertColumn(3, "업무상태", LVCFMT_LEFT, 60);
	m_lstRider.InsertColumn(4, "배차그룹", LVCFMT_CENTER, 120);
	m_lstRider.InsertColumn(5, "자동등급하향", LVCFMT_LEFT, 130);
	m_lstRider.InsertColumn(6, "다음변경날짜", LVCFMT_LEFT, 230); 

	m_lstRider.Populate();

	m_lstGrade.AddColumn(new CXTPGridColumn(0, "", 320, FALSE));
 	m_lstGrade.SetPaintManager(new CStaffFormPaintManager17);
	m_lstGrade.GetReportHeader()->SetAutoColumnSizing(FALSE);
	m_lstGrade.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstGrade.AllowEdit(FALSE);
	m_lstGrade.SetGridColor(RGB(212, 208, 200));
	m_lstGrade.GetPaintManager()->SetGridStyle(TRUE, xtpGridSolid);
	m_lstGrade.GetPaintManager()->m_strNoItems = "";
	m_lstGrade.ShowHeader(FALSE);
	m_lstGrade.EnableMarkup(FALSE);
	m_lstGrade.Populate();

	SetResize(IDC_GRADE_LIST, sizingBottom);
	SetResize(IDC_RIDER_LIST, sizingRightBottom);

	SetResizeHori(IDC_GRADE_LIST, IDC_RIDER_LIST);

	InsertCombo();
	m_cmbType.SetCurSel(0);
	
	static BOOL bFirst = TRUE;

	if(bFirst)
	{
		//RefreshList();
		RefreshRiderList();
		bFirst = FALSE;
	}
}

void CStaffPage21::InsertCombo()
{	
	if(LF->InsertAllocGroupCombo(&m_cmbType, LF->GetCurBranchInfo()->nCompanyCode))
	{
		//10이상 안넘음
		long nCount = m_cmbType.GetCount();

		CString strTemp[12];
		long nData[12];

		for(int i=0; i<nCount; i++)
		{
			m_cmbType.GetLBText(i, strTemp[i]);
			nData[i] = m_cmbType.GetItemData(i);
		}

		m_cmbType.ResetContent();

		m_cmbType.InsertString(0, "모두 검색");
		m_cmbType.SetItemData(0, 12);

		for(int i=0; i<nCount; i++)
		{
			m_cmbType.InsertString(i+1, strTemp[i]);
			m_cmbType.SetItemData(i+1, nData[i]);
		}
	}
}

void CStaffPage21::OnBnClickedRefreshGradeBtn()
{
	RefreshList();
}

void CStaffPage21::RefreshList()
{
	CMyFormView::RefreshList();

	m_lstGrade.GetRecords()->RemoveAll();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_alloc_group_join_company_1");

	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);
	CMkParameter *pPar = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);
    
	if(!rs.Execute(&cmd)) return;

	long nCompanywAutoAllocType = 0;
	pPar->GetValue(nCompanywAutoAllocType);

	colorText17[0] = RGB(0, 0, 0);
	colorBack17[0] = RGB(255, 255, 255);

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		ALLOC_GROUP st;

		rs.GetFieldValue("nID", st.nID);
		rs.GetFieldValue("nGrade", st.nGrade);
		rs.GetFieldValue("sGroupName", st.strGroupName);
		rs.GetFieldValue("nPanaltyDelayTime4Order", st.nPanaltyDelayTime4Order);
		rs.GetFieldValue("nPanaltyDelayTime4MyOrder", st.nPanaltyDelayTime4MyOrder);
		rs.GetFieldValue("nPanaltyDelayTime4OCOrder", st.nPanaltyDelayTime4OCOrder);
		rs.GetFieldValue("nPanaltyTypeShowOrder", st.nPanaltyTypeShowOrder);
		rs.GetFieldValue("nPenaltyDelayTime4MyCorpOrder", st.nPenaltyDelayTime4MyCorpOrder);
		rs.GetFieldValue("bAutoAllocType", st.bAutoAllocType);
		rs.GetFieldValue("bAutoGradeAdjByLogic", st.bAutoGradeAdjByLogic);
		rs.GetFieldValue("bAutoDownGrade", st.bAutoDownGrade);
		rs.GetFieldValue("nAutoDownGradeDay", st.nAutoDownGradeDay);
		rs.GetFieldValue("nAutoDownGradeCount", st.nAutoDownGradeCount);
		rs.GetFieldValue("nTextColor", st.nTextColor);
		rs.GetFieldValue("nBackColor", st.nBackColor); 

		st.nCompanyAutoAllocType = nCompanywAutoAllocType;

		if(st.nTextColor == st.nBackColor) 
		{
			st.nTextColor = RGB(0, 0, 0);
			st.nBackColor = RGB(255, 255, 255);
		}

		colorText17[st.nGrade] = st.nTextColor;
		colorBack17[st.nGrade] = st.nBackColor;

		m_lstGrade.AddRecord(new CStaffPage21Record(st));

		rs.MoveNext();
	}

	ALLOC_GROUP st; st.nGrade = 0; st.nID = 0;
	m_lstGrade.AddRecord(new CStaffPage21Record(st));

	m_lstGrade.Populate();
	m_lstGrade.GetSelectedRows()->Clear();
	m_stcHelp.SetWindowText("현재지사 : " + (CString)LF->GetCurBranchInfo()->strBranchName);

	m_lstRider.Populate();
}

void CStaffPage21::OnBnClickedRefreshRiderBtn()
{
	RefreshRiderList();
	SearchFilter();
}

void CStaffPage21::SearchFilter()
{
    CString strSearchData; m_edtSearch.GetWindowText(strSearchData);
	long nSearchGrade = m_cmbType.GetItemData(m_cmbType.GetCurSel());

	CXTPGridRecords *pRecords = m_lstRider.GetRecords();

	if(pRecords == NULL)
		return;

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		BOOL bGradeOK = TRUE;
		BOOL bCharOK = TRUE;

		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		long nGrade = (long)m_lstRider.GetItemData(pRecord);

		if(nSearchGrade <= 10)
		{
			if(nSearchGrade != nGrade)
				bGradeOK = FALSE;
			else
				bGradeOK = TRUE;
		}

		if(!bGradeOK)
		{
			pRecord->SetVisible(FALSE);
			continue;
		}
		
		CString strRNo = pRecord->GetItem(1)->GetCaption(NULL);
		CString strRName = pRecord->GetItem(2)->GetCaption(NULL);

		if((strRNo.Find(strSearchData) >= 0) ||
			(strRName.Find(strSearchData) >= 0))
			bCharOK = TRUE;
		else
			bCharOK = FALSE;
		
		pRecord->SetVisible(bCharOK);
	}

	m_lstRider.Populate();
}

void CStaffPage21::RefreshRiderList()
{ 
	m_lstRider.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_list_for_group_2");
	cmd.AddParameter(LF->GetCurBranchInfo()->nCompanyCode);

	if(!rs.Execute(&cmd)) return;

	CString strName, strGroupName, strAutoChangeGroup; 
	long nRiderCompany, nRNo, nWorkState, nRiderGroupCode, nGrade;
	COleDateTime dtAutoChangeGroupCode;
	long nAutoChangeGroupCode, nAutoDownGradeDay, nAutoDownGradeCount, nGroupCompany;
	BOOL bAutoDownGrade;

	for(int i=0;i <rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("sName", strName); 
		rs.GetFieldValue("sGroupName", strGroupName);
		rs.GetFieldValue("lCode", nRiderCompany);
		rs.GetFieldValue("nMNo", nRNo);
		rs.GetFieldValue("nWorkState", nWorkState);
		rs.GetFieldValue("nRiderGroupCode", nRiderGroupCode);
		rs.GetFieldValue("nGrade", nGrade);
		rs.GetFieldValue("dtAutoChangeGroupCode", dtAutoChangeGroupCode);
		rs.GetFieldValue("nAutoChangeGroupCode", nAutoChangeGroupCode);
		rs.GetFieldValue("bAutoDownGrade", bAutoDownGrade);
		rs.GetFieldValue("nAutoDownGradeDay", nAutoDownGradeDay);
		rs.GetFieldValue("nAutoDownGradeCount", nAutoDownGradeCount);
		rs.GetFieldValue("sAutoChangeGroup", strAutoChangeGroup);
		rs.GetFieldValue("nGroupCompany", nGroupCompany);
		
		m_lstRider.InsertItem(i, m_ci.GetShareCompanyBranchName(nRiderCompany));
		m_lstRider.SetItemText(i, 1, LF->GetStringFromLong(nRNo));
		m_lstRider.SetItemText(i, 2, strName);
		m_lstRider.SetItemText(i, 3, nWorkState == 1 ? "중지" : "");

		if(nGrade == 0)
			m_lstRider.SetItemText(i, 4, "");
		else
			m_lstRider.SetItemText(i, 4, strGroupName + " [" + LF->GetStringFromLong(nGrade) + "등급]");

		if((bAutoDownGrade == TRUE) && (nAutoChangeGroupCode <= 0))
		{
			CString strTemp = "";
			strTemp.Format("%d일이내 %d건이하", nAutoDownGradeDay, nAutoDownGradeCount);
			m_lstRider.SetItemText(i, 5, strTemp); 
		}
		else
			m_lstRider.SetItemText(i, 5, "");

		if(nAutoChangeGroupCode > 0)
		{
			CString strTemp = "";
			strTemp.Format("[%d-%d] %s로 자동그룹이동", dtAutoChangeGroupCode.GetMonth(), dtAutoChangeGroupCode.GetDay(), strAutoChangeGroup);
			m_lstRider.SetItemText(i, 6, strTemp);
		}
		else
			m_lstRider.SetItemText(i, 6, "");

		m_lstRider.SetItemLong(i, nRiderCompany); 
		m_lstRider.SetItemLong2(i, nRiderGroupCode);
		m_lstRider.SetItemLong3(i, nRiderCompany != nGroupCompany && nRiderGroupCode > 0 ? TRUE : FALSE);
		m_lstRider.SetItemData(i, nGrade);
		
		rs.MoveNext();
	}

	m_lstRider.Populate();

}

void CStaffPage21::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		CRect rect;
		m_lstGrade.GetWindowRect(&rect);
		ScreenToClient(rect);

		if(rect.PtInRect(point))
		{
			point -= rect.TopLeft();
            CXTPGridRow *pRow = m_lstGrade.HitTest(point);
			if(pRow != NULL)
			{
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
				::ReleaseCapture();
                CStaffPage21Record *pRecord = (CStaffPage21Record*)pRow->GetRecord();
				ChangeRiderGroup(pRecord->m_stAlloc);
			}
		}
	}

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	::ReleaseCapture();
	m_bDragMode  = FALSE;  //순서에 주의 할것

	CMyFormView::OnLButtonUp(nFlags, point);
}

void CStaffPage21::OnMouseMove(UINT nFlags, CPoint point)
{
	if(TRUE == m_bDragMode)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	}

	CMyFormView::OnMouseMove(nFlags, point);
}

void CStaffPage21::OnReportBeginDrag(NMHDR * /*pNotifyStruct*/, LRESULT * /*result*/)
{
	m_bDragMode = TRUE;
	::SetCursor(AfxGetApp()->LoadCursor(IDC_MOVEHOLD));
	SetCapture();
}

void CStaffPage21::ChangeRiderGroup(ALLOC_GROUP st)
{
	//if(!LF->POWER_CHECK(4920, "배차그룹수정", TRUE))
	//	return;

	CXTPGridSelectedRows *pSelectRows = m_lstRider.GetSelectedRows();
 
	if(pSelectRows == NULL)
	{
		MessageBox("그룹에 등록 하려는 기사님을 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CVarietyDlg3 dlg;
	dlg.m_strTitle = "사유를 입력하세요";
	
	if(dlg.DoModal() != IDOK)
		return;

	for(int i=0; i<pSelectRows->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pSelectRows->GetAt(i)->GetRecord();

		CString strRNo = m_lstRider.GetItemText(pRecord, 1);
		CString strRName = m_lstRider.GetItemText(pRecord, 2);
		long nRNo = atoi(strRNo);
		long nRiderCompany = m_lstRider.GetItemLong(pRecord);
		long nPreGroupCode = m_lstRider.GetItemLong2(pRecord);

		if(st.nID == nPreGroupCode)
			continue;

		CMkCommand cmd(m_pMkDb, "update_rider_group_get_groupname_2");
		cmd.AddParameter(nRiderCompany);
		cmd.AddParameter(nRNo);
		cmd.AddParameter(strRName);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);
		cmd.AddParameter(nPreGroupCode);
		cmd.AddParameter(st.nID);
		cmd.AddParameter(dlg.m_strMemo);
		cmd.AddParameter(dlg.m_bUse);
		cmd.AddParameter(dlg.m_dtAuto);
		cmd.AddParameter(dlg.m_nAutoGroupCode);
		CMkParameter *pPar = cmd.AddParameter(typeString, typeOutput, 100, "");

		if(cmd.Execute())
			RefreshRiderListOne(pRecord->GetIndex(), nRiderCompany, nRNo);
	} 

	m_lstRider.Populate();
}

void CStaffPage21::RefreshRiderListOne(long nItem, long nRiderCompany, long nRNo)
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_rider_list_for_group_one_2");
	cmd.AddParameter(nRiderCompany);
	cmd.AddParameter(nRNo);

	if(!rs.Execute(&cmd)) return;

	CString strName, strGroupName, strAutoChangeGroup; 
	long nWorkState, nRiderGroupCode, nGrade;
	
	COleDateTime dtAutoChangeGroupCode;
	long nAutoChangeGroupCode, nAutoDownGradeDay, nAutoDownGradeCount, nGroupCompany;
	BOOL bAutoDownGrade;

	rs.GetFieldValue("sName", strName); 
	rs.GetFieldValue("sGroupName", strGroupName);
	rs.GetFieldValue("nWorkState", nWorkState);
	rs.GetFieldValue("nRiderGroupCode", nRiderGroupCode);
	rs.GetFieldValue("nGrade", nGrade);
	rs.GetFieldValue("dtAutoChangeGroupCode", dtAutoChangeGroupCode);
	rs.GetFieldValue("nAutoChangeGroupCode", nAutoChangeGroupCode);
	rs.GetFieldValue("bAutoDownGrade", bAutoDownGrade);
	rs.GetFieldValue("nAutoDownGradeDay", nAutoDownGradeDay);
	rs.GetFieldValue("nAutoDownGradeCount", nAutoDownGradeCount);
	rs.GetFieldValue("sAutoChangeGroup", strAutoChangeGroup);
	rs.GetFieldValue("nGroupCompany", nGroupCompany);

	m_lstRider.SetItemText(nItem, 0, m_ci.GetShareCompanyBranchName(nRiderCompany));
	m_lstRider.SetItemText(nItem, 1, LF->GetStringFromLong(nRNo));
	m_lstRider.SetItemText(nItem, 2, strName);
	m_lstRider.SetItemText(nItem, 3, nWorkState == 1 ? "중지" : "");

	if(nGrade == 0)
		m_lstRider.SetItemText(nItem, 4, "");
	else
		m_lstRider.SetItemText(nItem, 4, strGroupName + " [" + LF->GetStringFromLong(nGrade) + "등급]");

	if((bAutoDownGrade == TRUE) && (nAutoChangeGroupCode <= 0))
	{
		CString strTemp = "";
		strTemp.Format("%d일이내 %d건이하", nAutoDownGradeDay, nAutoDownGradeCount);
		m_lstRider.SetItemText(nItem, 5, strTemp); 
	}
	else
		m_lstRider.SetItemText(nItem, 5, "");

	if(nAutoChangeGroupCode > 0)
	{
		CString strTemp = "";
		strTemp.Format("[%d-%d] %s로 자동그룹이동", dtAutoChangeGroupCode.GetMonth(), dtAutoChangeGroupCode.GetDay(), strAutoChangeGroup);
		m_lstRider.SetItemText(nItem, 6, strTemp);
	}
	else
		m_lstRider.SetItemText(nItem, 6, "");

	m_lstRider.SetItemLong(nItem, nRiderCompany);
	m_lstRider.SetItemLong2(nItem, nRiderGroupCode);
	m_lstRider.SetItemLong3(nItem, nRiderCompany != nGroupCompany && nRiderGroupCode > 0 ? TRUE : FALSE);
	m_lstRider.SetItemData(nItem, nGrade);
}

void CStaffPage21::OnEnChangeSearchEdit() 
{ 	  
	m_lstGrade.EnableMarkup(FALSE);    
	m_lstGrade.ModifyStyle(0, LVS_SHOWSELALWAYS); 
	m_lstGrade.Populate(); 

	SearchFilter();
}

void CStaffPage21::OnCbnSelchangeTypeCombo()
{
	SearchFilter();
}

void CStaffPage21::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CStaffPage21Record *pRecord = (CStaffPage21Record*)m_lstGrade.GetRecords()->GetAt(nRow);

	if(pRecord == NULL)
		return;

	if(pRecord->m_stAlloc.nID == 0)
		return;

	CChangeAllocGroupInfoDlg dlg;
	dlg.m_nGroupAllocID = pRecord->m_stAlloc.nID;
	dlg.m_nCompany = LF->GetCurBranchInfo()->nCompanyCode;
	if(dlg.DoModal() == IDOK)
	{
		CMkCommand cmd(m_pMkDb, "update_alloc_group_info_3");
		cmd.AddParameter(pRecord->m_stAlloc.nID);
		cmd.AddParameter(dlg.m_strGroupName);
		cmd.AddParameter(dlg.m_nPanaltyDelayTime4Order);
		cmd.AddParameter(dlg.m_nPanaltyDelayTime4MyOrder);
		cmd.AddParameter(dlg.m_nPanaltyDelayTime4OCOrder);
		cmd.AddParameter(dlg.m_nPanaltyTypeShowOrder); 
		cmd.AddParameter(dlg.m_nPenaltyDelayTime4MyCorpOrder);
		cmd.AddParameter(dlg.m_bAutoAllocType);
		cmd.AddParameter(dlg.m_bAutoGradeAdjByLogic);
		cmd.AddParameter(dlg.m_bUseAutoDownGrade);
		cmd.AddParameter(dlg.m_nDownGradeDay);
		cmd.AddParameter(dlg.m_nDownGradeCount);
		cmd.AddParameter(dlg.m_clrText);
		cmd.AddParameter(dlg.m_clrBack);
		cmd.AddParameter(dlg.m_bDownGradeOnlyMyCall);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);

		if(cmd.Execute()) 
		{
			colorText17[pRecord->m_stAlloc.nGrade] = dlg.m_clrText;
			colorBack17[pRecord->m_stAlloc.nGrade] = dlg.m_clrBack;

			OnBnClickedRefreshGradeBtn();
			m_lstRider.Populate();
			m_lstGrade.GetSelectedRows()->Clear();
		}
	}
}

void CStaffPage21::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{  
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
 
	//m_lstGrade.GetSelectedRows()->Select(NULL);
	m_lstGrade.GetSelectedRows()->Clear();
}


void CStaffPage21::OnReportItemClickRider(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	if(nCol>2) //굵은 글씨 이상
		return;

	long nCompany = m_lstRider.GetItemLong(nRow);;
	long nRNo = atoi(m_lstRider.GetItemText(nRow, 1));

	LU->ShowRiderInfoDlg(nCompany, nRNo);
}

void CStaffPage21::OnBnClickedSendMsgBtn()
{
	if(!LF->POWER_CHECK(1200, "기사공지창 보기", TRUE))
		return;

	CREATE_MODALESS(CRiderMsgDlg, this);
	pDlg->SetIntegrated(1);
	pDlg->SetCompanyCode(LF->GetCurBranchInfo()->nCompanyCode); 

	CXTPGridSelectedRows *pRows = m_lstRider.GetSelectedRows();

	for(int i=0; i<pRows->GetCount(); i++) 
	{
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();

		MSG_RIDER_INFO *pMRI = new MSG_RIDER_INFO;

		pMRI->nCompany = m_lstRider.GetItemLong(pRecord);
		pMRI->nRNo = atoi(m_lstRider.GetItemText(pRecord, 1));
		pDlg->m_paSelected.Add(pMRI);			
	}

	SHOW_MODALESS(CRiderMsgDlg, this);

	for(int i = 0; i < pDlg->m_paSelected.GetCount(); i++)
	{
		MSG_RIDER_INFO *pMRI = pDlg->m_paSelected.GetAt(i);
		delete pMRI;
	}
}
