// AuthManageLog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AuthManageLogDlg.h"



// CAuthManageLog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAuthManageLogDlg, CMyDialog)
CAuthManageLogDlg::CAuthManageLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAuthManageLogDlg::IDD, pParent)
{
}

CAuthManageLogDlg::~CAuthManageLogDlg()
{
}

void CAuthManageLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CAuthManageLogDlg, CMyDialog)
END_MESSAGE_MAP()


void CAuthManageLogDlg::Refresh()
{
	m_List.DeleteAllItems();

	int nRcpType = 10;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_auth_group_by_pc_log");

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nWNo);

	CMkParameter *pPar = pCmd.AddParameter(typeInt, typeOutput, sizeof(int), 0);

	if(!pRs.Execute(&pCmd)) return;

	pPar->GetValue(nRcpType);

	if(nRcpType == 100)
	{
		MessageBox("통합권한이 없습니다", "확인", MB_ICONERROR);
		OnCancel();
	}
	else if(nRcpType == 1000)
	{
		MessageBox("관리자 아닙니다", "확인", MB_ICONERROR);
		OnCancel();
	}

	int nClientNo;
	COleDateTime dtFirst, dtLast, newdtLast, dtFinal;

	int count = 0;
	int frontClientNo, afterClientNo = 0;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("nClientNo", nClientNo);
		pRs.GetFieldValue("dtFirstAuth", dtFirst);
		pRs.GetFieldValue("dtLastAuth", dtLast);
		pRs.GetFieldValue("newdtLastAuth", newdtLast);
		//pRs.GetFieldValue("dtWorkdate" , dtdate);
		pRs.GetFieldValue("dtFinalAuth", dtFinal);

		frontClientNo = nClientNo;

		CString sClientNo;
		sClientNo.Format("%d", nClientNo);

		if(newdtLast.GetYear() == -1)   // 재 인증을 한 적이 없는경우
		{
			if(count != 0)
				m_List.InsertItem(count++, "");

			m_List.InsertItem(count, sClientNo);
			m_List.SetItemText(count, 1, dtFirst.Format("%y-%m-%d %H:%M"));
			m_List.SetItemText(count, 2, dtLast.Format("%y-%m-%d %H:%M"));
			m_List.SetItemText(count, 3, dtFinal.Format("%y-%m-%d"));

		}
		else  //재 인증을 한적이 있는경우
		{
			if(frontClientNo == afterClientNo)  //위와 같은 피시 번호인지 확인
			{
				m_List.InsertItem(count, "");
				m_List.SetItemText(count, 1, "");
				m_List.SetItemText(count, 2, newdtLast.Format("%y-%m-%d %H:%M"));
				m_List.SetItemText(count, 3, dtFinal.Format("%y-%m-%d"));
			}
			else
			{
				if(count != 0)
					m_List.InsertItem(count++, "");

				m_List.InsertItem(count, sClientNo);
				m_List.SetItemText(count, 1, dtFirst.Format("%y-%m-%d %H:%M"));
				m_List.SetItemText(count, 2, newdtLast.Format("%y-%m-%d %H:%M"));
				m_List.SetItemText(count, 3, dtFinal.Format("%y-%m-%d"));
			}
		}

		count++;

		afterClientNo = frontClientNo;

		pRs.MoveNext();   
		m_List.Populate();
	}


}

// CAuthManageLog 메시지 처리기입니다.

BOOL CAuthManageLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES);

	m_List.InsertColumn(0, "PC번호", LVCFMT_LEFT, 50);
	m_List.InsertColumn(1, "최초인증", LVCFMT_LEFT, 95);
	m_List.InsertColumn(2, "마지막인증", LVCFMT_LEFT, 95);
	m_List.InsertColumn(3, "인증만료일", LVCFMT_LEFT, 95);

	m_List.Populate();
	Refresh();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
