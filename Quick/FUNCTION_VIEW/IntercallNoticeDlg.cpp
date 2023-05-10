// IntercallNoticeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "IntercallNoticeDlg.h"



// CIntercallNoticeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CIntercallNoticeDlg, CMyDialog)
CIntercallNoticeDlg::CIntercallNoticeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CIntercallNoticeDlg::IDD, pParent)
{
}

CIntercallNoticeDlg::~CIntercallNoticeDlg()
{
}

void CIntercallNoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_SEND_EDIT, m_SendEdit);
	DDX_Control(pDX, IDC_TITLE_EDIT, m_TitleEdit);
	DDX_Text(pDX, IDC_SEND_EDIT, m_strSend);
	DDX_Text(pDX, IDC_TITLE_EDIT, m_strTitle);
	DDV_MaxChars(pDX, m_strSend, 3000);
}


BEGIN_MESSAGE_MAP(CIntercallNoticeDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
END_MESSAGE_MAP()


// CIntercallNoticeDlg 메시지 처리기입니다.

BOOL CIntercallNoticeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 

	m_List.SetImageList(&ImageList, LVSIL_SMALL); 
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_List.InsertColumn(0, "발송시각", LVCFMT_LEFT, 125);
	m_List.InsertColumn(1, "제목", LVCFMT_LEFT, 310);
	m_List.InsertColumn(2, "내용", LVCFMT_LEFT, 0);

	RefreshHistory();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CIntercallNoticeDlg::RefreshHistory()
{
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_intercall_notice_history");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	if(!pRs.Execute(&pCmd)) return;

	int nItem = 0;
	COleDateTime dtWrite;
	CString strTitle, strMsg;

	while(!pRs.IsEOF())
	{	
		pRs.GetFieldValue("dtWrite", dtWrite);
		pRs.GetFieldValue("sTitle", strTitle);
		pRs.GetFieldValue("sMsg", strMsg);
		m_List.InsertItem(nItem, dtWrite.Format("%Y-%m-%d %H:%M:%S"));
		m_List.SetItemText(nItem, 1, strTitle);
		m_List.SetItemText(nItem, 2, strMsg);
		pRs.MoveNext();
		nItem++;
	}
	pRs.Close();
}

void CIntercallNoticeDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	
	if(m_strSend.GetLength() >= 3000) return;

	CMkCommand pCmd(m_pMkDb, "insert_intercall_notice");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	pCmd.AddParameter(typeString, typeInput, m_strTitle.GetLength(), m_strTitle);
	pCmd.AddParameter(typeString, typeInput, m_strSend.GetLength(), m_strSend);
	if(pCmd.Execute()) {
		MessageBox("발송 되었습니다", "확인", MB_ICONINFORMATION);
		CMyDialog::OnOK();
	}
	else {
		MessageBox("발송 실패하였습니다.", "확인", MB_ICONINFORMATION);
	}
}


void CIntercallNoticeDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nSelItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	if(nSelItem >= 0) {
		MessageBox(m_List.GetItemText(nSelItem, 2), m_List.GetItemText(nSelItem, 1),
					MB_ICONINFORMATION);
	}

	*pResult = 0;
}

void CIntercallNoticeDlg::OnOK()
{
    //CMyDialog::OnOK();
}

BOOL CIntercallNoticeDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN )		
		{
			switch(::GetDlgCtrlID(pMsg->hwnd))
			{
				case IDC_TITLE_EDIT:
					m_SendEdit.SetFocus();
					return TRUE;
			}
		}
	}


	return CMyDialog::PreTranslateMessage(pMsg);
}
