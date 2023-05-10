// AllocateGroupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AllocateGroupDlg.h"
#include "AllocateGroupNew.h"


#include "MyReportPaintManager.h"


// CAllocateGroupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAllocateGroupDlg, CMyDialog)
CAllocateGroupDlg::CAllocateGroupDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAllocateGroupDlg::IDD, pParent)
{
}

CAllocateGroupDlg::~CAllocateGroupDlg()
{
}

void CAllocateGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CAllocateGroupDlg, CMyDialog)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDelBtn)
	ON_BN_CLICKED(IDC_OK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_NOTIFY(NM_DBLCLK,  IDC_LIST, OnLbnDblclkListSearch)
	ON_BN_CLICKED(IDC_CLOSE, OnBnClickedClose)
END_MESSAGE_MAP()


// CAllocateGroupDlg 메시지 처리기입니다.

BOOL CAllocateGroupDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CBitmap bitmap;
	CImageList imageList;
	bitmap.LoadBitmap(IDB_LIST);
	imageList.Create(16,18,ILC_COLOR24 | ILC_MASK,1,1); 
	imageList.Add(&bitmap,RGB(0, 255, 255));
	m_List.SetImageList(&imageList,LVSIL_SMALL);
	m_List.GetPaintManager()->m_strNoItems = "";
	m_List.InsertColumn(0, "그룹번호",LVCFMT_LEFT, 70);
	m_List.InsertColumn(1, "그룹명",LVCFMT_LEFT, 213);
	m_List.InsertColumn(2, "순번",LVCFMT_LEFT, 0);

	
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAllocateGroupDlg::RefreshList()
{
	m_List.DeleteAllItems();
	char buffer[10];
	m_nItem = 0;

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_allocate_group");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
	if(!pRs.Execute(&pCmd)) return;

	while(!pRs.IsEOF())
	{
		int nCompany;
		int nGNo;
		CString sName;

		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("sName", sName);

		m_List.InsertItem(m_nItem, ltoa(nGNo,buffer,10));
		m_List.SetItemText(m_nItem, 1, sName);
		m_List.SetItemText(m_nItem++, 2, ltoa(m_nItem + 1, buffer, 10));

		pRs.MoveNext();
	}
	m_List.Populate();
}


void CAllocateGroupDlg::OnBnClickedDelBtn()
{
	int nItem = m_List.GetSelectedItem();
	if(nItem >= 0)
	{
		CString sGNo = m_List.GetItemText(nItem, 0);
		MessageBox("sGNo :::"+sGNo);

		CMkRecordset pRs(m_pMkDb);
		CMkCommand pCmd(m_pMkDb,"delete_allocate_group");

		pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_ci.m_nCompanyCode);
		pCmd.AddParameter(typeLong, typeInput, sizeof(long), atol(sGNo));

		if(pCmd.Execute())
		{
			MessageBox("배차그룹을 삭제하였습니다.", "확인", MB_ICONINFORMATION);
			RefreshList();
		}
		else {
			MessageBox("배차그룹 삭제 실패하였습니다.", "확인", MB_ICONINFORMATION);	
		}
	}
	else
	{
		MessageBox("삭제할 아이템을 선택해주세요 !!", "확인", MB_ICONINFORMATION);
	}
}

BOOL CAllocateGroupDlg::CheckIntegrity()
{
	CString strLineGroup, strTemp, strTemp2;
		
	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		strLineGroup = m_List.GetItemText(i, 4);
		while( strLineGroup.Replace(" ","") > 0 ) {}; //Remove Space
		strLineGroup.Trim();
		strLineGroup.Trim("'");
		
		int curPos = 0;
		strTemp = strLineGroup.Tokenize(",", curPos);
		strTemp = "," + strTemp + ",";
		while(strTemp != ",,")
		{
			for(int k = 0; k < m_List.GetItemCount(); k++)
			{
				if(i == k) continue;

				strTemp2 = ","+m_List.GetItemText(k, 4)+",";
				while( strTemp2.Replace(" ","") > 0 ) {}; //Remove Space

				if(strTemp2.Find(strTemp) >= 0) {
					CString strMsg;
					strMsg.Format("%d번 지사의 %s 국선이, %d번 지사에도 존재함", i + 1, strTemp, k + 1);
					MessageBox(strMsg, "확인", MB_ICONINFORMATION);
					return FALSE;
				}
			}
			strTemp = strLineGroup.Tokenize(",", curPos);
			strTemp = "," + strTemp + ",";
		}
	}	
	return TRUE;
}



void CAllocateGroupDlg::OnBnClickedOk()
{
	if(CheckIntegrity())
	{
		CWaitCursor wait;
		for(int i = 0; i < m_List.GetItemCount(); i++)
		{
			int nCompany = m_List.GetItemData(i);
			CString strLineGroup = m_List.GetItemText(i, 4);

			CMkCommand pCmd(m_pMkDb, "update_line_group");
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_ci.m_nCompanyCode);
			pCmd.AddParameter(typeLong, typeInput, sizeof(long), nCompany);
			pCmd.AddParameter(typeString, typeInput, strLineGroup.GetLength(), strLineGroup);
			if(!pCmd.Execute()) {
				MessageBox("업데이트 실패, 재시도 바랍니다.", "확인", MB_ICONINFORMATION);
				return;
			}
			
			for(int k = 0; k < m_ba.GetCount(); k++) {
				CBranchInfo *pBi = m_ba.GetAt(k);
				if(pBi->nCompanyCode == nCompany) {
					pBi->strLineGroup = strLineGroup;
					pBi->strLineGroup += ",";
				}
			}
		}
		MessageBox("저장되었습니다.", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}

void CAllocateGroupDlg::OnBnClickedAdd()
{
	CAllocateGroupNew dlg;
	dlg.bNewMode = TRUE;

	if(IDOK == dlg.DoModal())
	{
		RefreshList();
	}
}

void CAllocateGroupDlg::OnLbnDblclkListSearch(NMHDR * pNotifyStruct, LRESULT *result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	int nRow = pItemNotify->pRow->GetIndex();
	int nCol = pItemNotify->pColumn->GetItemIndex();

	CAllocateGroupNew dlg;
	dlg.bNewMode = FALSE;
	dlg.m_sGNo	= m_List.GetItemText(nRow, 0);
	dlg.m_sName	= m_List.GetItemText(nRow, 1);

	if(IDOK == dlg.DoModal())
	{
		RefreshList();
	}
}


void CAllocateGroupDlg::OnBnClickedClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}
