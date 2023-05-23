// ChangeAllocGroupInfoLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "quick.h"
#include "ChangeAllocGroupInfoLogDlg.h"
#include ".\changeallocgroupinfologdlg.h"


// CChangeAllocGroupInfoLogDlg ��ȭ �����Դϴ�.

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


// CChangeAllocGroupInfoLogDlg �޽��� ó�����Դϴ�.

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
			m_lst.InsertItem(i, "~ ����");
		else
			m_lst.InsertItem(i, "~ " + dtGenerate.Format("%y-%m-%d %H:%M"));			
		
		m_lst.SetItemText(i, 1, strGroupName);
		m_lst.SetItemText(i, 2, LF->GetStringFromLong(nPanaltyDelayTime4Order));
		m_lst.SetItemText(i, 3, LF->GetStringFromLong(nPanaltyDelayTime4MyOrder));
		m_lst.SetItemText(i, 4, LF->GetStringFromLong(nPanaltyDelayTime4OCOrder));
		m_lst.SetItemText(i, 5, LF->GetStringFromLong(nPenaltyDelayTime4MyCorpOrder));

		if(nPanaltyTypeShowOrder == 0)
			m_lst.SetItemText(i, 6, "��ü������");
		else if(nPanaltyTypeShowOrder == 1)
			m_lst.SetItemText(i, 6, "1��������");
		else if(nPanaltyTypeShowOrder == 2)
			m_lst.SetItemText(i, 6, "���Ҽ���");

		if(bAutoAllocType == TRUE)
			m_lst.SetItemText(i, 7, "���");
		else
			m_lst.SetItemText(i, 7, "�̻��");

		if(bAutoGradeAdjByLogic == TRUE)
			m_lst.SetItemText(i, 8, "���");
		else
			m_lst.SetItemText(i, 8, "�̻��");

		if(bAutoDownGrade == TRUE)
			m_lst.SetItemText(i, 9, "���");
		else
			m_lst.SetItemText(i, 9, "�̻��");

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

	m_lst.InsertColumn(0, "�Ⱓ", LVCFMT_CENTER, 130);
	m_lst.InsertColumn(1, "�׷��", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(2, "����", LVCFMT_LEFT, 50);
	m_lst.InsertColumn(3, "�ڻ�", LVCFMT_LEFT, 50);
	m_lst.InsertColumn(4, "Ÿ��", LVCFMT_LEFT, 50);
	m_lst.InsertColumn(5, "�ڻ����", LVCFMT_LEFT, 60);
	m_lst.InsertColumn(6, "��������", LVCFMT_LEFT, 70);
	m_lst.InsertColumn(7, "�ڵ�����", LVCFMT_LEFT, 65);
	m_lst.InsertColumn(8, "�ڵ��������", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(9, "�ڵ��������", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(10, "��������ϼ�", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(11, "�������Ǽ�", LVCFMT_LEFT, 80);
	m_lst.InsertColumn(12, "������", LVCFMT_LEFT, 70);

	m_lst.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
