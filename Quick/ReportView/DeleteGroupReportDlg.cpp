// DeleteGroupReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DeleteGroupReportDlg.h"

#include "UnBillDlg.h"


// CDeleteGroupReportDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDeleteGroupReportDlg, CMyDialog)
CDeleteGroupReportDlg::CDeleteGroupReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDeleteGroupReportDlg::IDD, pParent)
{
	m_nGNo = 0;
	m_bRefresh = FALSE;
	m_nApplyReportID = 0;
}

CDeleteGroupReportDlg::~CDeleteGroupReportDlg()
{
}

void CDeleteGroupReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_Report);
}


BEGIN_MESSAGE_MAP(CDeleteGroupReportDlg, CMyDialog)
	ON_BN_CLICKED(IDC_MAKE_BTN, OnBnClickedMakeBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDbClick)
END_MESSAGE_MAP()


// CDeleteGroupReportDlg 메시지 처리기입니다.

BOOL CDeleteGroupReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_Report.InsertColumn(0, "체크", LVCFMT_CENTER, 38);
	m_Report.InsertColumn(1, "No.", LVCFMT_RIGHT,  55);
    m_Report.InsertColumn(2, "날짜", LVCFMT_CENTER, 125);
	m_Report.InsertColumn(3, "상태", LVCFMT_CENTER, 65);
	m_Report.InsertColumn(4, "청구액", LVCFMT_RIGHT, 70);
	m_Report.InsertColumn(5, "수금액", LVCFMT_RIGHT, 60);
	m_Report.InsertColumn(6, "미수금", LVCFMT_RIGHT, 60);	

	m_Report.Populate();
	RefreshList();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDeleteGroupReportDlg::RefreshList()
{
	m_Report.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_report");

	pCmd.AddParameter(m_nGNo);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtReportStart, dtReportEnd;
	long nReportState, nBillCollection, nUnCollection, nID, nGNo, nReceivableAmount;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		BOOL bCheck = FALSE;
		pRs.GetFieldValue("dtReportStart", dtReportStart);
		pRs.GetFieldValue("dtReportEnd", dtReportEnd);
		pRs.GetFieldValue("nReportState", nReportState);
		pRs.GetFieldValue("nBillCollection", nBillCollection);
		pRs.GetFieldValue("nUnCollection", nUnCollection);
		pRs.GetFieldValue("nReceivableAmount", nReceivableAmount);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nGNo", nGNo);

		bCheck = (m_nApplyReportID == nID) ? TRUE : FALSE;

		m_Report.AddRecord(new CDeleteGroupRecord(dtReportStart, dtReportEnd, 
			GetReportState(nReportState), nUnCollection, nBillCollection,
			nReceivableAmount, nID, nReportState, nGNo,bCheck));

		pRs.MoveNext();
	}

	m_Report.Populate();
}

CString CDeleteGroupReportDlg::GetReportState(long nReportState)
{
	if(nReportState == 0)
		return "정산완료";
	else if(nReportState == 10)
		return "부분입금";
	else if(nReportState == 20)
		return "입금완료";

	return "알수없음";

}
void CDeleteGroupReportDlg::OnBnClickedMakeBtn()
{
	long nCount = 0; BOOL bHasBillCollection = FALSE; CString sID = "";
	CheckReportAbil(nCount, bHasBillCollection, sID);

	if(nCount == 0)
	{
		MessageBox("삭제 할 정산 내역을 최소 하나 이상 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(nCount > 30)
	{
		MessageBox("30개 이상 작업 할 수 없습니다\r\n나누어서 작업 해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString sMsg = "";

	if(bHasBillCollection == TRUE)
	{
		sMsg = "삭제 할 정산 내역중 수금받은 내역이 있습니다\r\n한번 삭제 하면 다시 복구 할 수 없습니다\r\n계속 진행 하시겠습니까?";

		if(MessageBox(sMsg, "확인", MB_OKCANCEL) != IDOK)
			return;
	}

	sMsg.Format("%d개의 정산을 삭제 합니다\r\n\r\n한번 삭제 하면 다시 복구 할 수 없습니다\r\n계속 진행 하시겠습니까?", nCount);

	if(MessageBox(sMsg, "확인", MB_OKCANCEL) != IDOK)
		return;

	CMkCommand pCmd(m_pMkDb, "delete_group_report");
	pCmd.AddParameter(sID);

	if(!pCmd.Execute()) return;

	m_bRefresh = TRUE;
	MessageBox("삭제되었습니다", "확인", MB_ICONINFORMATION);
	RefreshList();

	

}

void CDeleteGroupReportDlg::CheckReportAbil(long &nCount, BOOL &bHasBillCollection, CString &sID)
{
	char buffer[20];
	for(int i=0; i<m_Report.GetItemCount(); i++)
	{
		if(m_Report.GetChecked(i, 0) == TRUE)
		{
			nCount++;

			CXTPGridRow *pRow = m_Report.GetRows()->GetAt(i);
			CDeleteGroupRecord *pRecord = (CDeleteGroupRecord*)pRow->GetRecord();

			sID += (CString)itoa(pRecord->m_nID, buffer, 10) + ";";

			CString sBillConnection = m_Report.GetItemText(i, 4);
			sBillConnection.Replace(",", "");

			if(_ttoi(sBillConnection) > 0)
				bHasBillCollection = TRUE;
		}
	}
}
void CDeleteGroupReportDlg::OnBnClickedCancelBtn()
{
	OnOK();
}

void CDeleteGroupReportDlg::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	CXTPGridRow *pRow = m_Report.GetSelectedRows()->GetAt(0);

	if(pRow == NULL)
		return;

	CDeleteGroupRecord *pRecord = (CDeleteGroupRecord*)pRow->GetRecord();

	CUnBillDlg dlg;
	dlg.m_bAlone = TRUE;
	dlg.m_nID = pRecord->m_nID;
	dlg.m_nGNo = pRecord->m_nGNo;

	dlg.DoModal();
}
