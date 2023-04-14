// MentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MentDlg.h"
#include "CustomerSmsDlg.h"	
#include "MentAddDlg.h"


// CMentDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMentDlg, CMyDialog)
CMentDlg::CMentDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CMentDlg::IDD, pParent)
{
}

CMentDlg::~CMentDlg()
{
}

void CMentDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);

	DDX_Control(pDX, IDC_ADD_BTN, m_btnAdd);
	DDX_Control(pDX, IDC_DELETE_BTN, m_btnDelete);
	DDX_Control(pDX, IDC_COPY_BTN, m_btnCopy);
	DDX_Control(pDX, IDC_MSG_LENGTH_STATIC, m_stcMsgLength);
	DDX_Control(pDX, IDC_MSG_EDIT, m_edtMsg);
}


BEGIN_MESSAGE_MAP(CMentDlg, CMyDialog)
	ON_BN_CLICKED(IDC_COPY_BTN, OnBnClickedCopyBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CMentDlg 메시지 처리기입니다.

void CMentDlg::OnBnClickedCopyBtn()
{
	int index = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(index == -1)
	{
		MessageBox("복사할 메세지를 선택하세요", "확인", MB_ICONERROR);
		return;
	}

	CString msg;
	msg = m_List.GetItemText(index,1);

	m_strMent = msg;
	if(m_pCustomerSmsDlg != NULL)
	{
		m_pCustomerSmsDlg->m_edtMent.SetWindowText(msg);
		m_pCustomerSmsDlg->OnEnChangeMentEdit();
	}
	OnOK();
}

void CMentDlg::OnBnClickedAddBtn()
{
	CMentAddDlg pDlg;
	pDlg.m_pParent = this;
	pDlg.DoModal();
}

void CMentDlg::OnBnClickedDeleteBtn()
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);

	if(nItem == -1)
	{
		MessageBox("삭제할 메세지를 선택하세요", "확인", MB_ICONERROR);
		return;
	}

	CString sID = m_List.GetItemText(nItem, 2);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "delete_ment");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), _ttoi(sID));

	if(!pRs.Execute(&pCmd)) return;

	pRs.Close();

	RefreshList();
}

void CMentDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CMentDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nItem = m_List.GetNextItem(-1, LVNI_SELECTED);
	CString strID = m_List.GetItemText(nItem, 2);
	CString strTitle = m_List.GetItemText(nItem, 0);
	CString strMemo = m_List.GetItemText(nItem, 1);

	CMentAddDlg pDlg;
	pDlg.m_pParent = this;
	pDlg.m_strID = strID;
	pDlg.m_strTitle = strTitle;
	pDlg.m_strMemo = strMemo;
	pDlg.DoModal();


	*pResult = 0;
}

void CMentDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pNMLV->iItem < 0)
	{
		*pResult = 0;
		return;
	}
	else
	{
		CString strMsg,strMsgLength;

		strMsg = m_List.GetItemText(pNMLV->iItem, 1);
		m_edtMsg.SetWindowText(strMsg);
		strMsgLength.Format("%d/80자", strMsg.GetLength() );
		m_stcMsgLength.SetWindowText(strMsgLength);
	}
	*pResult = 0;
}

BOOL CMentDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
		//SetWindowPos(&CWnd::wndTopMost, 0,0,0, 0, SWP_NOSIZE | SWP_NOMOVE);

	CImageList ImageList;
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_List.InsertColumn(0, "타이틀", LVCFMT_LEFT, 200);
	m_List.InsertColumn(1, "내용", LVCFMT_LEFT, 500);
	m_List.InsertColumn(2, "nID", LVCFMT_LEFT, 0);

	/*
	m_List.InsertColumn(0,"코드",LVCFMT_LEFT, 200);
	m_List.InsertColumn(1,"메시지 내용",LVCFMT_LEFT, 500);
	*/

	m_edtMsg.SetFontSize(13);
	RefreshList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMentDlg::RefreshList()
{
	m_List.DeleteAllItems();

	int nItem = 0, nType, nCompany, nID;
	CString strMsg, strTitle;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_all_ments");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ui.nCompany);
	CMkParameter *parOutCompanyPhone = pCmd.AddParameter(typeString, typeOutput, 25, "");
	if(pRs.Execute(&pCmd)) 
	{
		while(!pRs.IsEOF())
		{
			pRs.GetFieldValue("nID", nID);
			pRs.GetFieldValue("nCompany", nCompany);
			pRs.GetFieldValue("nType", nType);
			pRs.GetFieldValue("sMsg", strMsg);
			pRs.GetFieldValue("sTitle", strTitle);

			m_List.InsertItem(nItem, strTitle);
			m_List.SetItemText(nItem, 1, strMsg);

			CString str;
			str.Format("%d", nID);
			m_List.SetItemText(nItem, 2, str);

			pRs.MoveNext();
		}
	}
	/*
	m_List.DeleteAllItems();

	int nItem = 0, nType, nCompany;
	CString strMsg;
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_all_ments");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	CMkParameter *parOutCompanyPhone = pCmd.AddParameter(typeString, typeOutput, 25, "");
	if(pRs.Execute(&pCmd)) 
	{
	while(!pRs.IsEOF())
	{
	pRs.GetFieldValue("nCompany", nCompany);
	pRs.GetFieldValue("nType", nType);
	pRs.GetFieldValue("sMsg", strMsg);

	if(nCompany != 0) {
	m_List.InsertItem(nItem, GetMentTitle(nType));
	m_List.SetItemText(nItem, 1, strMsg);
	m_List.SetItemData(nItem++, nType);
	pRs.MoveNext();
	if(pRs.IsEOF()) break;
	}
	else {
	m_List.InsertItem(nItem, GetMentTitle(nType));
	m_List.SetItemText(nItem, 1, strMsg);
	m_List.SetItemData(nItem++, nType);
	}

	pRs.MoveNext();
	}
	}
	*/

}
