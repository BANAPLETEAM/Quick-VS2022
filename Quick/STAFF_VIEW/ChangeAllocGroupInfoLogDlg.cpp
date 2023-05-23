// ChangeAllocGroupInfoLogDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "quick.h"
#include "ChangeAllocGroupInfoLogDlg.h"
#include ".\changeallocgroupinfologdlg.h"


// CChangeAllocGroupInfoLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChangeAllocGroupInfoLogDlg, CMyDialog)
CChangeAllocGroupInfoLogDlg::CChangeAllocGroupInfoLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CChangeAllocGroupInfoLogDlg::IDD, pParent)
{
	m_nGroupAllocID = 0;
}

CChangeAllocGroupInfoLogDlg::~CChangeAllocGroupInfoLogDlg()
{
}

void CChangeAllocGroupInfoLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_lst);
}


BEGIN_MESSAGE_MAP(CChangeAllocGroupInfoLogDlg, CMyDialog)

	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
END_MESSAGE_MAP()


// CChangeAllocGroupInfoLogDlg 메시지 처리기입니다.

void CChangeAllocGroupInfoLogDlg::OnBnClickedRefreshBtn()
{
	RefreshList();
}

void CChangeAllocGroupInfoLogDlg::RefreshList()
{
	m_lst.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_alloc_group_change_log");
	cmd.AddParameter(m_nGroupAllocID);
 
	COleDateTime dtGenerate;
	long nWCompany, nWNo;
	CString strWName, strGroupName;
	long nPanaltyDelayTime4Order, nPanaltyDelayTime4MyOrder, nPanaltyDelayTime4OCOrder;
	long nPanaltyTypeShowOrder, nPenaltyDelayTime4MyCorpOrder, nAutoDownGradeDay, nAutoDownGradeCount;
	BOOL bAutoAllocType, bAutoGradeAdjByLogic, bAutoDownGrade;
	CString strPreWName;

	if(!rs.Execute(&cmd)) return;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("dtGenerate", dtGenerate);
		rs.GetFieldValue("nWCompany", nWCompany);
		rs.GetFieldValue("nWNo", nWNo);
		rs.GetFieldValue("sWName", strWName);
		rs.GetFieldValue("nPanaltyDelayTime4Order", nPanaltyDelayTime4Order);
		rs.GetFieldValue("nPanaltyDelayTime4MyOrder", nPanaltyDelayTime4MyOrder);
		rs.GetFieldValue("nPanaltyDelayTime4OCOrder", nPanaltyDelayTime4OCOrder);
		rs.GetFieldValue("nPanaltyTypeShowOrder", nPanaltyTypeShowOrder);
		rs.GetFieldValue("nPenaltyDelayTime4MyCorpOrder", nPenaltyDelayTime4MyCorpOrder);
		rs.GetFieldValue("sGroupName", strGroupName);
		rs.GetFieldValue("bAutoAllocType", bAutoAllocType);
		rs.GetFieldValue("bAutoGradeAdjByLogic", bAutoGradeAdjByLogic);
		rs.GetFieldValue("bAutoDownGrade", bAutoDownGrade);
		rs.GetFieldValue("nAutoDownGradeDay", nAutoDownGradeDay);
		rs.GetFieldValue("nAutoDownGradeCount", nAutoDownGradeCount);

		if(i == 0)
			m_lst.InsertItem(i, "~ 현재");
		else
			m_lst.InsertItem(i, "~ " + dtGenerate.Format("%y-%m-%d %H:%M"));			
		
		m_lst.SetItemText(i, 1, strGroupName);
		m_lst.SetItemText(i, 2, LF->GetStringFromLong(nPanaltyDelayTime4Order));
		m_lst.SetItemText(i, 3, LF->GetStringFromLong(nPanaltyDelayTime4MyOrder));
		m_lst.SetItemText(i, 4, LF->GetStringFromLong(nPanaltyDelayTime4OCOrder));
		m_lst.SetItemText(i, 5, LF->GetStringFromLong(nPenaltyDelayTime4MyCorpOrder));

		if(nPanaltyTypeShowOrder == 0)
			m_lst.SetItemText(i, 6, "전체공유콜");
		else if(nPanaltyTypeShowOrder == 1)
			m_lst.SetItemText(i, 6, "1차공유콜");
		else if(nPanaltyTypeShowOrder == 2)
			m_lst.SetItemText(i, 6, "기사소속콜");

		if(bAutoAllocType == TRUE)
			m_lst.SetItemText(i, 7, "사용");
		else
			m_lst.SetItemText(i, 7, "미사용");

		if(bAutoGradeAdjByLogic == TRUE)
			m_lst.SetItemText(i, 8, "사용");
		else
			m_lst.SetItemText(i, 8, "미사용");

		if(bAutoDownGrade == TRUE)
			m_lst.SetItemText(i, 9, "사용");
		else
			m_lst.SetItemText(i, 9, "미사용");

		m_lst.SetItemText(i, 10, LF->GetStringFromLong(nAutoDownGradeDay));
		m_lst.SetItemText(i, 11, LF->GetStringFromLong(nAutoDownGradeCount));

		m_lst.SetItemText(i, 12, "");

		strPreWName = strWName;

		if(i != 0)
		{
			m_lst.SetItemText(i, 12, strPreWName);
		}

		rs.MoveNext();
	}
	m_lst.Populate();
}

BOOL CChangeAllocGroupInfoLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lst.InsertColumn(0, "기간", LVCFMT_CENTER, 130);
	m_lst.InsertColumn(1, "그룹명", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(2, "오더", LVCFMT_LEFT, 50);
	m_lst.InsertColumn(3, "자사", LVCFMT_LEFT, 50);
	m_lst.InsertColumn(4, "타사", LVCFMT_LEFT, 50);
	m_lst.InsertColumn(5, "자사법인", LVCFMT_LEFT, 60);
	m_lst.InsertColumn(6, "오더보기", LVCFMT_LEFT, 70);
	m_lst.InsertColumn(7, "자동배차", LVCFMT_LEFT, 65);
	m_lst.InsertColumn(8, "자동등급조정", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(9, "자동등급하향", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(10, "등급하향일수", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(11, "등급하향건수", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(12, "접수자", LVCFMT_LEFT, 70);

	m_lst.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
