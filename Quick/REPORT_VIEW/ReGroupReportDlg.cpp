// ReGroupReportDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ReGroupReportDlg.h"

#include "DeleteGroupReportDlg.h"
#include "UnBillDlg.h"


// CReGroupReportDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CReGroupReportDlg, CMyDialog)
CReGroupReportDlg::CReGroupReportDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CReGroupReportDlg::IDD, pParent)
{
	m_nGNo = 0;
	m_bRefresh = FALSE;
	m_nApplyReportID = 0;
}

CReGroupReportDlg::~CReGroupReportDlg()
{
}

void CReGroupReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_Report);
	DDX_Control(pDX, IDC_INCLUDE_TODAY_CHECK, m_chkIncludeToday);
}


BEGIN_MESSAGE_MAP(CReGroupReportDlg, CMyDialog)
	ON_BN_CLICKED(IDC_MAKE_BTN, OnBnClickedMakeBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, OnBnClickedCancelBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDbClick)
END_MESSAGE_MAP()


// CReGroupReportDlg 메시지 처리기입니다.

void CReGroupReportDlg::OnReportItemDbClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
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

BOOL CReGroupReportDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_Report.InsertColumn(0, "체크", LVCFMT_CENTER, 38);
	m_Report.InsertColumn(1, "날짜", LVCFMT_CENTER, 130);
	m_Report.InsertColumn(2, "상태", LVCFMT_CENTER, 70);
	m_Report.InsertColumn(3, "미수금", LVCFMT_RIGHT, 65);
	m_Report.InsertColumn(4, "수금액", LVCFMT_RIGHT, 65);

	m_Report.Populate();
	RefreshList();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CReGroupReportDlg::RefreshList()
{
	m_Report.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_group_report");

	pCmd.AddParameter(m_nGNo);

	if(!pRs.Execute(&pCmd)) return;

	COleDateTime dtReportStart, dtReportEnd;
	long nReportState, nBillCollection, nUnCollection,nReceivableAmount, nID, nGNo;

	for(int i=0; i<pRs.GetRecordCount(); i++)
	{
		BOOL bCheck = FALSE;
		pRs.GetFieldValue("dtReportStart", dtReportStart);
		pRs.GetFieldValue("dtReportEnd", dtReportEnd);
		pRs.GetFieldValue("nReportState", nReportState);
		pRs.GetFieldValue("nBillCollection", nBillCollection);
		pRs.GetFieldValue("nUnCollection", nUnCollection);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nGNo", nGNo);
		pRs.GetFieldValue("nReceivableAmount", nReceivableAmount);

		bCheck = (m_nApplyReportID == nID) ? TRUE : FALSE;
		m_Report.AddRecord(new CDeleteGroupRecord(dtReportStart, dtReportEnd, 
			CDeleteGroupReportDlg::GetReportState(nReportState), nUnCollection, nBillCollection,
			nReceivableAmount, nID, nReportState, nGNo ,bCheck));

		

		pRs.MoveNext();
	}

	m_Report.Populate();
}

void CReGroupReportDlg::OnBnClickedMakeBtn()
{
	long nCount = 0; BOOL bHasBillCollection = FALSE; CString sID = "";
	CheckReportAbil(nCount, bHasBillCollection, sID);

	if(nCount == 0)
	{
		MessageBox("재정산 할 정산 내역을 최소 하나 이상 선택하세요", "확인", MB_ICONINFORMATION);
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
		sMsg = "재정산 내역중 수금받은 내역이 있습니다\r\n재정산 불가능한 한목 제거후 계속 진행하시겠습니까?";

		if(MessageBox(sMsg, "확인", MB_OKCANCEL) != IDOK)
			return;

		else
		{
			for(int i=0; i<m_Report.GetItemCount(); i++)
			{
				if(m_Report.GetChecked(i, 0) == TRUE)
				{
					CXTPGridRows *pRows = m_Report.GetRows();
					CDeleteGroupRecord *pRecord = (CDeleteGroupRecord*)pRows->GetAt(i)->GetRecord();

					if(pRecord->m_nReportState == 10 || pRecord->m_nReportState == 20)
						m_Report.SetChecked(i, 0, FALSE);
				}
			}

			m_Report.Populate();

			OnBnClickedMakeBtn();
			return;
		}
	}

	sMsg.Format("%d개의 항목을 재정산합니다", nCount);

	if(MessageBox(sMsg, "확인", MB_OKCANCEL) != IDOK)
		return;

	CString sEtc = "재정산";


	CMkCommand pCmd(m_pMkDb, "rereport_group_real");
	pCmd.AddParameter(sID);
	pCmd.AddParameter(sEtc);
	pCmd.AddParameter(m_chkIncludeToday.GetCheck());

	if(!pCmd.Execute()) return;

	m_bRefresh = TRUE;
	MessageBox("재정산 되었습니다", "확인", MB_ICONINFORMATION);
	RefreshList();

}

void CReGroupReportDlg::CheckReportAbil(long &nCount, BOOL &bHasBillCollection, CString &sID)
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

void CReGroupReportDlg::OnBnClickedCancelBtn()
{
	OnCancel();
}
