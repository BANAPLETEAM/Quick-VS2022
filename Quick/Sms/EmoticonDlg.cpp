// EmoticonDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "EmoticonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define EMOTICON_SPECIAL_CHAR 100
#define EMOTICON_LOVE 101
#define EMOTICON_ANGRY 102
#define EMOTICON_ETC 103

// CEmoticonDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEmoticonDlg, CMyDialog)

CEmoticonDlg::CEmoticonDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CEmoticonDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_nEmoticonType = EMOTICON_SPECIAL_CHAR;
}

CEmoticonDlg::~CEmoticonDlg()
{
}

void CEmoticonDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
}


BEGIN_MESSAGE_MAP(CEmoticonDlg, CMyDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_EMOTICON_BTN1, OnBnClickedEmoticon1Btn)
	ON_BN_CLICKED(IDC_EMOTICON_BTN2, OnBnClickedEmoticon2Btn)
	ON_BN_CLICKED(IDC_EMOTICON_BTN3, OnBnClickedEmoticon3Btn)
	ON_BN_CLICKED(IDC_EMOTICON_BTN4, OnBnClickedEmoticon4Btn)
	ON_NOTIFY(NM_CLICK, IDC_REPORT_LIST, OnReportItemClick)
END_MESSAGE_MAP()


BOOL CEmoticonDlg::OnInitDialog()
{ 
	CMyDialog::OnInitDialog();

	if((long)LF->GetEmoticonMap()->size() <= 0)
		LF->FillEmotioconMap();

	m_lstReport.GetPaintManager()->SetColumnStyle(xtpGridColumnResource);	
	m_lstReport.GetPaintManager()->m_strNoItems = "";
	m_lstReport.GetPaintManager()->SetGridStyle(TRUE,xtpGridSolid);
	m_lstReport.ShowHeader(FALSE);
	m_lstReport.Populate(); 

	RefreshList();

	return TRUE;
}

void CEmoticonDlg::OnBnClickedEmoticon1Btn()
{
	m_nEmoticonType = EMOTICON_SPECIAL_CHAR;
	RefreshList();
}

void CEmoticonDlg::OnBnClickedEmoticon2Btn()
{
	m_nEmoticonType = EMOTICON_LOVE;
	RefreshList();
}

void CEmoticonDlg::OnBnClickedEmoticon3Btn()
{
	m_nEmoticonType = EMOTICON_ANGRY;
	RefreshList();
}

void CEmoticonDlg::OnBnClickedEmoticon4Btn()
{
	m_nEmoticonType = EMOTICON_ETC;
	RefreshList();
}

long CEmoticonDlg::GetColSize()
{
	if(m_nEmoticonType == EMOTICON_SPECIAL_CHAR) return 40;
	else if(m_nEmoticonType == EMOTICON_LOVE) return 85;
	else if(m_nEmoticonType == EMOTICON_ANGRY) return 100;
	else if(m_nEmoticonType == EMOTICON_ETC) return 90; 

	return 100;
} 

void CEmoticonDlg::ClearList()
{
	m_lstReport.GetRecords()->RemoveAll();
	m_lstReport.GetColumns()->Clear();

}

void CEmoticonDlg::RefreshList()
{ 
	ClearList();

	CRect rc;
	m_lstReport.GetClientRect(rc);

	long nColCount = rc.Width() / GetColSize();

	if(nColCount <= 0)
		return; 

	for(int i=0; i<nColCount; i++)
	{
		CXTPGridColumn *pCol = m_lstReport.AddColumn(new CXTPGridColumn(i, _T(""), GetColSize()));
		pCol->SetAlignment(DT_CENTER);
	}

	MAP_EMOTICON *pMap = LF->GetEmoticonMap();

	long nItem = 0;

	CXTPEmoticonRecord *pRecord = NULL;

	for(MAP_EMOTICON::iterator it = pMap->begin(); it != pMap->end(); it++)
	{
		ST_EMOTICON st = it->second; 

		if(st.nType == GetEmoticonType())
		{
			long nMod = 0;

			if(nItem == 0)
				nMod = 0;
			else
				nMod = nItem % nColCount;

			if(nMod == 0)
				pRecord = (CXTPEmoticonRecord*)m_lstReport.AddRecord(new CXTPEmoticonRecord(nColCount));

			((CXTPGridRecordItemText*)pRecord->GetItem(nMod))->SetCaption(st.strEmoticon);

			nItem++; 
		}
	}

	m_lstReport.Populate();
}

void CEmoticonDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd())
	{
		CRect rcForm, rcList;
		GetClientRect(rcForm);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcForm.right - 5;
		rcList.bottom = rcForm.bottom - 5;
		m_lstReport.MoveWindow(rcList);

		RefreshList();
	}
}

void CEmoticonDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	char *szEmoticon = new char[255];

	CString strEmoticon = m_lstReport.GetRecords()->GetAt(nRow)->GetItem(nCol)->GetCaption(NULL);

	if(strEmoticon.IsEmpty())
		return;

	strcpy(szEmoticon, strEmoticon);

	if(m_pParent)
		m_pParent->SendMessage(WM_SEND_EMOTICON, WPARAM(szEmoticon), LPARAM(0));
}
