// ColumnSelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ColumnSelDlg.h"


// CColumnSelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CColumnSelDlg, CMyDialog)

CColumnSelDlg::CColumnSelDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CColumnSelDlg::IDD, pParent)
{
	m_plstReport = NULL;
}

CColumnSelDlg::~CColumnSelDlg()
{
}

void CColumnSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REPORT, m_lstColumn);
}


BEGIN_MESSAGE_MAP(CColumnSelDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CColumnSelDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CColumnSelDlg 메시지 처리기입니다.

BOOL CColumnSelDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_lstColumn.InsertColumn(0, "ⓝ", LVCFMT_CENTER, 30);
	m_lstColumn.InsertColumn(1, "컬럼명", LVCFMT_CENTER, 140);
	m_lstColumn.GetReportHeader()->AllowColumnSort(FALSE);
	m_lstColumn.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CColumnSelDlg::RefreshList()
{
	if(m_plstReport == NULL)
		return;

	CXTPGridColumns *pColumns = m_plstReport->GetColumns();
	CString sNewOrderVisible = AfxGetApp()->GetProfileString(m_sClass, m_sList + "B", "");

	BOOL bNotSave = FALSE;
	long nColCount = pColumns->GetCount();

	long nFirstFindVisible = 0;
	long nSecondFindVisible = 0; 
	long nNewVisible = 0;

	if(LF->GetCommaCount(sNewOrderVisible) != nColCount)
		bNotSave = TRUE; 

	for(int i=0; i<nColCount; i++)
	{
		CXTPGridColumn *pColumn = pColumns->GetAt(i);

		nSecondFindVisible = sNewOrderVisible.Find(";", nFirstFindVisible);

		if(bNotSave)
		{
			nNewVisible = TRUE;
		}
		else
			nNewVisible = _ttoi(sNewOrderVisible.Mid(nFirstFindVisible, nSecondFindVisible - nFirstFindVisible));
			
		m_lstColumn.InsertCheckItem(i, "", -1, nNewVisible);
		m_lstColumn.SetItemText(i, 1, pColumn->GetCaption());
		nFirstFindVisible = nSecondFindVisible + 1;
	}

	m_lstColumn.Populate();
}

void CColumnSelDlg::OnBnClickedOk()
{
	char buffer[10];
	CString sCols = "";
	CXTPGridRecords * pRecords = m_lstColumn.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		BOOL bChk = m_lstColumn.GetChecked(pRecords->GetAt(i), 0);

		m_plstReport->GetColumns()->GetAt(i)->SetVisible(bChk);

		sCols += (CString)(itoa(bChk, buffer, 10)) + ";";
	}

	AfxGetApp()->WriteProfileString(m_sClass, m_sList + "B", sCols);

	OnOK();
}
