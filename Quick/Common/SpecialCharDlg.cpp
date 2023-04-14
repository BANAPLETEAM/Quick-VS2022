// SpecialCharDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SpecialCharDlg.h"

#include "MentAddDlg.h"


// CSpecialCharDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSpecialCharDlg, CMyDialog)
CSpecialCharDlg::CSpecialCharDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSpecialCharDlg::IDD, pParent)
{
	for(int i = 0; i < MAX_COUNT; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			m_strCharGroup[i][j] = "";
		}
		m_nCharCount[i] = 0;
	}

	m_pParent = NULL;
}

CSpecialCharDlg::~CSpecialCharDlg()
{
	m_pParent = NULL;
}

void CSpecialCharDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	for(int i = 0; i< MAX_COUNT; i++)
		DDX_Control(pDX, IDC_CHAR_BTN1 + i, m_CharBtn[i]);

	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_Scroll);
	DDX_Control(pDX, IDC_CHAR_COUNT_STC, m_stcCharCount);
	DDX_Control(pDX, IDC_MEMO_RDO, m_rdoMemo);
	DDX_Control(pDX, IDC_TITLE_RDO, m_rdoTitle);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_CloseBtn);
}


BEGIN_MESSAGE_MAP(CSpecialCharDlg, CMyDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHAR_BTN1, IDC_CHAR_BTN14, onClickBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_MEMO_RDO, OnBnClickedMemoRdo)
	ON_BN_CLICKED(IDC_TITLE_RDO, OnBnClickedTitleRdo)
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


// CSpecialCharDlg 메시지 처리기입니다.

void CSpecialCharDlg::OnBnClickedCloseBtn()
{
	m_pParent->m_pSpecialCharDlg = NULL;
	OnCancel();
}

void CSpecialCharDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CMyDialog::OnLButtonDown(nFlags, point);
}

void CSpecialCharDlg::OnBnClickedMemoRdo()
{
	m_pParent->m_edtMemo.SetFocus();
}

void CSpecialCharDlg::OnBnClickedTitleRdo()
{
	m_pParent->m_edtTitle.SetFocus();
}

BOOL CSpecialCharDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->wParam == VK_ESCAPE)
	{
		m_pParent->m_pSpecialCharDlg = NULL;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CSpecialCharDlg::MoveFocus()
{
	if(m_pParent->m_bTitle)
		m_pParent->m_edtTitle.SetFocus();
	else
		m_pParent->m_edtMemo.SetFocus();
}


void CSpecialCharDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if(nHitTest == HTCLOSE)
	{
		m_pParent->m_pSpecialCharDlg = NULL;
	}

	CMyDialog::OnNcLButtonDown(nHitTest, point);
}

BOOL CSpecialCharDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_rdoMemo.SetCheck(BST_CHECKED);

	CImageList ImageList;
	ImageList.Create(1,20,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS | LVS_NOSORTHEADER);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT     | LVS_EX_GRIDLINES);
	m_List.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	m_List.InsertColumn(0,"", LVCFMT_CENTER, 0);
	m_List.InsertColumn(1,"", LVCFMT_CENTER, 30);
	m_List.InsertColumn(2,"", LVCFMT_CENTER, 30);
	m_List.InsertColumn(3,"", LVCFMT_CENTER, 30);
	m_List.InsertColumn(4,"", LVCFMT_CENTER, 30);
	m_List.InsertColumn(5,"", LVCFMT_CENTER, 30);


	InitChar();

	onClickBtn(IDC_CHAR_BTN1);

	GetWindowRect(m_Rect);

	MoveDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSpecialCharDlg::onClickBtn(UINT nFlag)
{
	PrintList(nFlag - IDC_CHAR_BTN1, 0);
}


void CSpecialCharDlg::PrintList(UINT Flags, int nPage)
{
	/*
	m_List.DeleteAllItems();
	m_Flag = Flags;

	CString sCount;
	sCount.Format("%d/%d", nPage + 1, m_nCharCount[Flags]/30 + 1);
	m_nCharCountStc.SetWindowText(sCount);

	m_Scroll.SetScrollRange(0, m_nCharCount[Flags]/30);
	m_Scroll.SetScrollPos(nPage);

	int PrintCount = nPage * 30; //30개씩 프린트

	int nItem = 0;
	for(int i = 0; i < m_nCharCount[Flags]; i++)
	{
	if(i >= 31)  //30개만 프린트
	break;

	if(i == 0)
	{
	m_List.InsertItem(nItem, m_strCharGroup[Flags][i + PrintCount]);
	continue;
	}
	else if(i % 5 ==0)
	{
	nItem ++;
	m_List.InsertItem(nItem, m_strCharGroup[Flags][i + PrintCount]);
	continue;
	}
	m_List.SetItemText(nItem, i%5, m_strCharGroup[Flags][i + PrintCount]);
	}
	*/
	m_List.DeleteAllItems();
	m_Flag = Flags;

	CString sCount;
	sCount.Format("%d/%d", nPage + 1, m_nCharCount[Flags]/30 + 1);
	m_stcCharCount.SetWindowText(sCount);

	m_Scroll.SetScrollRange(0, m_nCharCount[Flags]/30);
	m_Scroll.SetScrollPos(nPage);

	int PrintCount = nPage * 30; //30개씩 프린트

	int nItem = -1;
	for(int i = 0; i < m_nCharCount[Flags]; i++)
	{
		if(i >= 37)  //36개만 프린트 맨 앞은 공백
			break;

		if(i == 0 || i%6 == 0)
		{
			nItem++;
			m_List.InsertItem(nItem, "");
			//m_List.SetItemText(nItem, i%6 ,m_strCharGroup[Flags][i + PrintCount]);
		}
		else
		{
			m_List.SetItemText(nItem, i%6 ,m_strCharGroup[Flags][i + PrintCount - (nItem + 1)]);
			CString str;
			str.Format("i: %d, PrintCount: %d, nItem : %d", i, PrintCount, nItem);

		}
	}

	MoveFocus();
}


int CSpecialCharDlg::ReturnType(CString sType)
{
	if(sType == "가")
		return 0;

	if(sType == "나")
		return 1;

	if(sType ==  "다")
		return 2;

	if(sType == "라")
		return 3;

	if(sType == "마")
		return 4;

	if(sType == "바")
		return 5;

	if(sType == "사")
		return 6;

	if(sType == "아")
		return 7;

	if(sType == "자")
		return 8;

	if(sType == "차")
		return 9;

	if(sType == "카")
		return 10;

	if(sType == "타")
		return 11;

	if(sType == "파")
		return 12;

	if(sType == "하")
		return 13;

	return 0;
}
// CSpecialCharDlg 메시지 처리기입니다.


void CSpecialCharDlg::InitChar()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_special_char");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), 0);

	if(!pRs.Execute(&pCmd)) return;

	while(!pRs.IsEOF())
	{
		CString sType;
		CString	sSpecialChar;

		pRs.GetFieldValue("sType", sType);
		pRs.GetFieldValue("sSpecialChar", sSpecialChar);

		int index = ReturnType(sType);
		m_strCharGroup[index][m_nCharCount[index]] = sSpecialChar;

		m_nCharCount[index] += 1;
		pRs.MoveNext();
	}
}

void CSpecialCharDlg::Close()
{
	OnCancel();
}

void CSpecialCharDlg::MoveDialog()
{
	CRect ParentRect;

	m_pParent->GetClientRect(&ParentRect);
	m_pParent->ClientToScreen(&ParentRect);

	MoveWindow(ParentRect.right + 4, ParentRect.top, m_Rect.Width(), m_Rect.Height());
}
