// SmsNewBulkMentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsNewBulkMentDlg.h"
#include "EmoticonDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSmsNewBulkMentDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsNewBulkMentDlg, CMyDialog)

CSmsNewBulkMentDlg::CSmsNewBulkMentDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmsNewBulkMentDlg::IDD, pParent)
{
	m_pParent = NULL;
	m_pEmoticonDlg = NULL;
	m_nLastSelectIndex = -1;

	for(int i=0; i<MENT_COUNT; i++)
		m_nID[i] = 0;
}

CSmsNewBulkMentDlg::~CSmsNewBulkMentDlg()
{
	DELETE_OBJECT(m_pEmoticonDlg);
}

void CSmsNewBulkMentDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	for(int i=0; i<MENT_COUNT; i++)
		DDX_Control(pDX, IDC_MENT_EDIT1 + i, m_edtMent[i]);
}


BEGIN_MESSAGE_MAP(CSmsNewBulkMentDlg, CMyDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_SELECT_BTN1, IDC_SELECT_BTN9, OnClickedItemSelect)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_UPDATE_BTN1, IDC_UPDATE_BTN9, OnClickedItemUpdate)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_EMOTICON_BTN1, IDC_EMOTICON_BTN9, OnClickedItemEmoticon)
	ON_MESSAGE(WM_SEND_EMOTICON, OnSendEmoticon)
END_MESSAGE_MAP()


void CSmsNewBulkMentDlg::OnClickedItemSelect(UINT nItem)
{	
	char *ch = new char[1024];
	CString strText;

	m_edtMent[nItem - IDC_SELECT_BTN1].GetWindowText(strText);

	strcpy(ch, strText);

	if(m_pParent)
		m_pParent->SendMessage(WM_CHANGE_MENT, (WPARAM)ch, (LPARAM)0);

	delete ch; 

	OnCancel();
}

void CSmsNewBulkMentDlg::OnClickedItemUpdate(UINT nItem)
{	
	long nIndex = nItem - IDC_UPDATE_BTN1;
	long nID = m_nID[nIndex];

	CString strText; m_edtMent[nIndex].GetWindowText(strText);

	BOOL bResult = FALSE;

	if(nID <= 0)
		bResult = ::InsertSaveMent(m_nCompany, SMS_TYPE_BULK, strText);
	else
		bResult = ::UpdateSaveMent(nID, strText);

	if(bResult)
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
}

void CSmsNewBulkMentDlg::OnClickedItemEmoticon(UINT nItem)
{	
	if(m_pEmoticonDlg == NULL)
	{
		m_pEmoticonDlg = new CEmoticonDlg(this);
		m_pEmoticonDlg->Create(CEmoticonDlg::IDD, this);
	}

	m_nLastSelectIndex = nItem - IDC_EMOTICON_BTN1;

	CRect rcThis, rcEmoticon;

	CWnd *pWnd = GetDlgItem(nItem);
	pWnd->GetWindowRect(rcThis);
	m_pEmoticonDlg->GetWindowRect(rcEmoticon);

	long nWidth = rcEmoticon.Width();
	long nHeight = rcEmoticon.Height();

	rcEmoticon.bottom = rcThis.bottom; 
	rcEmoticon.top = rcThis.bottom - nHeight;
	rcEmoticon.left = rcThis.right + 1;
	rcEmoticon.right = rcEmoticon.left + nWidth;

	m_pEmoticonDlg->MoveWindow(rcEmoticon);
	m_pEmoticonDlg->ShowWindow(SW_SHOW);
}

BOOL CSmsNewBulkMentDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	for(int i=0; i<MENT_COUNT; i++)
		m_edtMent[i].SetFont(m_FontManager.GetFont("맑은 고딕", 20));

	LoadSmsBulkMent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSmsNewBulkMentDlg::LoadSmsBulkMent()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_sms_save_ment4");
	cmd.AddParameter(m_nCompany); 
	cmd.AddParameter(SMS_TYPE_BULK);

	if(!rs.Execute(&cmd))
		return;

	CString strMent; long nID; BOOL bDefault;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		if(i>=MENT_COUNT)
			break; 

		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sMent", strMent);
		rs.GetFieldValue("bDefault", bDefault);

		m_nID[i] = nID;
		m_edtMent[i].SetWindowText(strMent);

		rs.MoveNext();
	}
}

LONG CSmsNewBulkMentDlg::OnSendEmoticon(WPARAM wParam, LPARAM lParam)
{
	char const *strValue = reinterpret_cast<char const *>(wParam);

	::AddTextMiddle(strValue, &m_edtMent[m_nLastSelectIndex]);

	delete strValue;

	return 0;
}

void CSmsNewBulkMentDlg::InitSmsBulkMent()
{
	for(int i = 0; i < MENT_COUNT; i++)
		m_edtMent[i].SetWindowText("");
}