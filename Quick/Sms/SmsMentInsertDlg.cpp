
#include "stdafx.h"
#include "resource.h"
#include "SmsMentInsertDlg.h"
#include "EmoticonDlg.h"
// CSmsMentInsertDlg 대화 상자입니다.


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CSmsMentInsertDlg, CMyDialog)

CSmsMentInsertDlg::CSmsMentInsertDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmsMentInsertDlg::IDD, pParent)
{
	m_pEmoticonDlg = NULL;
}

CSmsMentInsertDlg::~CSmsMentInsertDlg()
{
	DELETE_OBJECT(m_pEmoticonDlg);
}

void CSmsMentInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MENT_EDIT, m_edtMent);
	DDX_CBString(pDX, IDC_MENT_EDIT, m_strMent);
	DDX_Control(pDX, IDC_SMS_MMS_BTN, m_btnSmsMms);
	DDX_Control(pDX, IDC_BYTE_STATIC, m_stcByte);
}

BEGIN_MESSAGE_MAP(CSmsMentInsertDlg, CMyDialog)

	ON_BN_CLICKED(IDC_MENT_BTN1, OnBnClickedMent1Btn)
	ON_BN_CLICKED(IDC_MENT_BTN2, OnBnClickedMent2Btn)
	ON_BN_CLICKED(IDC_MENT_BTN3, OnBnClickedMent3Btn)
	ON_BN_CLICKED(IDC_MENT_BTN4, OnBnClickedMent4Btn)
	ON_BN_CLICKED(IDC_MENT_BTN5, OnBnClickedMent5Btn)
	ON_BN_CLICKED(IDC_MENT_BTN6, OnBnClickedMent6Btn)
	ON_BN_CLICKED(IDC_MENT_BTN7, OnBnClickedMent7Btn)
	ON_BN_CLICKED(IDC_MENT_BTN8, OnBnClickedMent8Btn)
	ON_BN_CLICKED(IDC_MENT_BTN9, OnBnClickedMent9Btn)
	ON_BN_CLICKED(IDC_MENT_BTN10, OnBnClickedMent10Btn)

	ON_BN_CLICKED(IDC_SPECIAL_CHAR_BTN, OnBnClickedSpecialCharBtn)
	ON_BN_CLICKED(IDC_EMOTICON_BTN, OnBnClickedEmoticonBtn)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)

	ON_EN_CHANGE(IDC_MENT_EDIT, OnEnChangeMentEdit)

	ON_MESSAGE(WM_SEND_EMOTICON, OnSendEmoticon)

END_MESSAGE_MAP()


void CSmsMentInsertDlg::OnEnChangeMentEdit()
{
	DisplayByte();
}

BOOL CSmsMentInsertDlg::OnInitDialog()
{ 
	CMyDialog::OnInitDialog();

	if(m_nType == SMS_TYPE_ALLOCATE)
	{
		GetDlgItem(IDC_MENT_BTN1)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN2)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN3)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN4)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN5)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN6)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN7)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN8)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN9)->EnableWindow(TRUE);
		GetDlgItem(IDC_MENT_BTN10)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_MENT_BTN1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN2)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN3)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN4)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN5)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN6)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN7)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN8)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN9)->EnableWindow(FALSE);
		GetDlgItem(IDC_MENT_BTN10)->EnableWindow(FALSE);
	}

	m_btnSmsMms.LoadBitmaps(IDB_SMS_SMS, IDB_SMS_SMS); 

	m_edtMent.SetFont(m_FontManager.GetFont("맑은 고딕", 20));
	m_edtMent.SetWindowText(m_strMent);

	DisplayByte();
	return TRUE;
}

void CSmsMentInsertDlg::OnBnClickedSpecialCharBtn()
{

}

void CSmsMentInsertDlg::OnBnClickedEmoticonBtn()
{
	if(m_pEmoticonDlg == NULL)
	{
		m_pEmoticonDlg = new CEmoticonDlg(this);
		m_pEmoticonDlg->Create(CEmoticonDlg::IDD, this);
	}

	CRect rcThis, rcEmoticon;

	GetWindowRect(rcThis);
	m_pEmoticonDlg->GetWindowRect(rcEmoticon);

	long nWidth = rcEmoticon.Width();
	long nHeight = rcEmoticon.Height();

	rcEmoticon.top = rcThis.top;
	rcEmoticon.bottom = rcEmoticon.top + nHeight; 
	rcEmoticon.left = rcThis.right + 1;
	rcEmoticon.right = rcEmoticon.left + nWidth;

	m_pEmoticonDlg->MoveWindow(rcEmoticon);
	m_pEmoticonDlg->ShowWindow(SW_SHOW);
}

void CSmsMentInsertDlg::OnBnClickedSaveBtn()
{
	m_edtMent.GetWindowText(m_strMent);
	OnOK();
}

void CSmsMentInsertDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CSmsMentInsertDlg::OnBnClickedMent1Btn()
{
	AddText(IDC_MENT_BTN1);
}

void CSmsMentInsertDlg::OnBnClickedMent2Btn()
{
	AddText(IDC_MENT_BTN2);
}

void CSmsMentInsertDlg::OnBnClickedMent3Btn()
{
	AddText(IDC_MENT_BTN3);
}

void CSmsMentInsertDlg::OnBnClickedMent4Btn()
{
	AddText(IDC_MENT_BTN4);
}

void CSmsMentInsertDlg::OnBnClickedMent5Btn()
{
	AddText(IDC_MENT_BTN5);
}

void CSmsMentInsertDlg::OnBnClickedMent6Btn()
{
	AddText(IDC_MENT_BTN6);
}

void CSmsMentInsertDlg::OnBnClickedMent7Btn()
{
	AddText(IDC_MENT_BTN7);
}

void CSmsMentInsertDlg::OnBnClickedMent8Btn()
{
	AddText(IDC_MENT_BTN8);
}

void CSmsMentInsertDlg::OnBnClickedMent9Btn()
{
	AddText(IDC_MENT_BTN9);
}

void CSmsMentInsertDlg::OnBnClickedMent10Btn()
{
	AddText(IDC_MENT_BTN10);
}

void CSmsMentInsertDlg::AddText(UINT nFlag, CString strAddText)
{
	CString strText; 

	if(strAddText.IsEmpty())
	{
		GetDlgItem(nFlag)->GetWindowText(strText);
		strText = "[" + strText + "]";
	}
	else
		strText = strAddText;

	CString strInput; m_edtMent.GetWindowText(strInput);

	CStringW strTextW(strText); 
	CStringW sInputW(strInput);

	int nStartSel, nDestSel; 

	m_edtMent.GetSel(nStartSel, nDestSel);

	if(nStartSel == -1) return; 

	CString sResult = CString(strInput.Left(nStartSel)) + CString(strTextW) + CString(strInput.Right(strInput.GetLength() - nDestSel));
	m_edtMent.SetWindowText(sResult);


	m_edtMent.SetFocus();
	m_edtMent.SetSel(nStartSel + strText.GetLength(), nStartSel + strText.GetLength());

	DisplayByte();
}

void CSmsMentInsertDlg::DisplayByte()
{
	CString strMent;
	m_edtMent.GetWindowText(strMent);

	long nLength = strMent.GetLength();

	CString strTemp; strTemp.Format("Byte : %d", nLength);
	m_stcByte.SetWindowText(strTemp);

	if(nLength >= 90) 
		m_btnSmsMms.LoadBitmaps(IDB_SMS_MMS, IDB_SMS_MMS); 
	else		
		m_btnSmsMms.LoadBitmaps(IDB_SMS_SMS, IDB_SMS_SMS); 

	m_btnSmsMms.Invalidate();
}

LONG CSmsMentInsertDlg::OnSendEmoticon(WPARAM wParam, LPARAM lParam)
{
	char const *strValue = reinterpret_cast<char const *>(wParam);

	AddText(0, strValue);

	delete strValue;

	return 0;
}