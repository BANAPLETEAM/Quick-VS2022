// ShareRcpSubPageDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "ShareRcpSubPageDlg.h"
#include "RcpView.h"

static LOGFONT m_ListFont = {15,0,0,0,FW_BOLD,0,0,0,HANGUL_CHARSET,0,0,0,0,"���� ���"};
// CShareRcpSubPageDlg

IMPLEMENT_DYNCREATE(CShareRcpSubPageDlg, CMyFormView)

CShareRcpSubPageDlg::CShareRcpSubPageDlg()
	: CMyFormView(CShareRcpSubPageDlg::IDD)
{
	m_bTake = FALSE;
}

CShareRcpSubPageDlg::~CShareRcpSubPageDlg()
{
}

void CShareRcpSubPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT_LIST, m_lstReport);
}

BEGIN_MESSAGE_MAP(CShareRcpSubPageDlg, CMyFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CShareRcpSubPageDlg �����Դϴ�.

#ifdef _DEBUG
void CShareRcpSubPageDlg::AssertValid() const
{
	CMyFormView::AssertValid();
}

void CShareRcpSubPageDlg::Dump(CDumpContext& dc) const
{
	CMyFormView::Dump(dc);
}
#endif //_DEBUG


// CShareRcpSubPageDlg �޽��� ó�����Դϴ�.

BOOL CShareRcpSubPageDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CMyFormView::PreTranslateMessage(pMsg);
}

void CShareRcpSubPageDlg::OnInitialUpdate()
{
	if(m_bInitialUpdateCalled) return;
	CMyFormView::OnInitialUpdate();

	m_lstReport.InsertColumn(0, "�Ҽ�", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(1, "��ȣ", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "����", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(3, "����", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(4, "����", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(5, "��ߵ�", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(6, "������", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(7, "�ݾ�", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(8, "Ź��", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(9, "����", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(10, "�Ϸ��", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(11, "����", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(12, "����", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(13, "���Ҽ�", LVCFMT_LEFT, 90);
	m_lstReport.InsertColumn(14, "���", LVCFMT_LEFT, 40);
	m_lstReport.InsertColumn(15, "����", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(16, "������", LVCFMT_LEFT, 60);

	m_lstReport.GetPaintManager()->SetTextFont(m_ListFont);
	m_lstReport.AddFooterRows();

	m_lstReport.Populate();

	SetResize(IDC_REPORT_LIST, sizingRightBottom);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CShareRcpSubPageDlg::Refresh()
{
	if(LU->GetRcpView() == NULL)
		return;

	m_lstReport.DeleteAllItems();

	OrderRecordList &order = LU->GetRcpView()->GetTodayOrder()->GetOrderRecordList();
	OrderRecordList::iterator it;

	for(it = order.begin(); it != order.end(); it++)
	{
		OrderRecord *record = &it->second;

		if((record->nShareCode1 != record->nRiderShareCode1) &&
			(record->nShareCode1 != 0) && (record->nRiderShareCode1 != 0))
		{
			if(((m_bTake == TRUE) && record->nShareCode1 == m_ci.m_nShareCode1) ||
				((m_bTake == FALSE) && record->nRiderShareCode1 == m_ci.m_nShareCode1))
				InsertData(record);
		}
	}

	m_lstReport.SetFooterMessage(GetFooterData());
	m_lstReport.Populate();
}

void CShareRcpSubPageDlg::InsertData(OrderRecord *record)
{
	char buffer[10];
	long nCount = m_lstReport.GetItemCount();

	m_lstReport.InsertItem(nCount, m_ci.GetName(record->nCompany));
	m_lstReport.SetItemText(nCount, 1, itoa(record->nTNo, buffer, 10));
	m_lstReport.SetItemText(nCount, 2, record->dtRcp.Format("%m-%d %H:%M"));
	m_lstReport.SetItemText(nCount, 3, LF->GetStateString(record->nState));
	m_lstReport.SetItemText(nCount, 4, m_bTake == TRUE ? record->strCName.c_str() : "N/A");
	m_lstReport.SetItemText(nCount, 5, record->strStart.c_str());
	m_lstReport.SetItemText(nCount, 6, record->strDest.c_str());
	m_lstReport.SetItemText(nCount, 7, LF->GetMyNumberFormat(record->nCharge));
	m_lstReport.SetItemText(nCount, 8, LF->GetMyNumberFormat(record->nChargeTrans));
	m_lstReport.SetItemText(nCount, 9, record->dt3.Format("%H:%M:%S")); 
	m_lstReport.SetItemText(nCount, 10, record->dtFinal.Format("%H:%M:%S"));
	m_lstReport.SetItemText(nCount, 11, LF->GetCarTypeFromLong(record->nCarType, TRUE));
	m_lstReport.SetItemText(nCount, 12, LF->GetPayTypeFromLong(record->nPayType, TRUE));
	m_lstReport.SetItemText(nCount, 13, m_ci.GetName(record->nRiderCompany));
	m_lstReport.SetItemText(nCount, 14, itoa(record->nRNo, buffer, 10));
	m_lstReport.SetItemText(nCount, 15, record->strRName.c_str());
	m_lstReport.SetItemText(nCount, 16, record->strWName.c_str());

	m_lstReport.SetItemLong(nCount, record->nState);
	m_lstReport.SetItemLong2(nCount, record->nPayType);
}


CString CShareRcpSubPageDlg::GetFooterData()
{ 
	//���� 4/10,000 �ſ� 10/20000 �۱� 20/2000 Ź�� 2/1022 �հ� 23/1221

	CXTPGridRecords *pRecords =  m_lstReport.GetRecords();
	long nAllCount = pRecords->GetCount();

	long nCashCount = 0, nCreditCount = 0, nOnlineCount = 0, nTransCount = 0, nAllCountReal = 0;
	long nCashCharge = 0, nCreditCharge = 0, nOnlineCharge = 0, nTransCharge = 0, nAllChargeReal = 0;

	for(int i=0; i<nAllCount; i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i); 
		long nState = m_lstReport.GetItemLong(pRecord);

		if(nState < STATE_OK_ONLY_MAN || nState > STATE_FINISH)
			continue;

		long nPayType = m_lstReport.GetItemLong2(pRecord);

		switch(nPayType)
		{
		case 0:
		case 1:
			nCashCount++;
			nCashCharge += LF->GetNoneCommaNumber(m_lstReport.GetItemText(pRecord, 7));
			break;
		case 2:
			nCreditCount++;
			nCreditCharge += LF->GetNoneCommaNumber(m_lstReport.GetItemText(pRecord, 7));
			break;
		case 3:
			nOnlineCount++;
			nOnlineCharge += LF->GetNoneCommaNumber(m_lstReport.GetItemText(pRecord, 7));
			break;
		}

		if(LF->GetNoneCommaNumber(m_lstReport.GetItemText(pRecord, 8)) > 0)
		{
			nTransCount++;
			nTransCharge += LF->GetNoneCommaNumber(m_lstReport.GetItemText(pRecord, 8));
		}

		nAllCountReal++;
		nAllChargeReal += LF->GetNoneCommaNumber(m_lstReport.GetItemText(pRecord, 7));

	}      

	//���� 4/10,000 �ſ� 10/20000 �۱� 20/2000 Ź�� 2/1022 �հ� 23/1221

	CString sTemp = ""; 
	sTemp.Format("���� %d/%d  |  �ſ� %d/%d  |  �۱� %d/%d  |  Ź�� %d/%d  |  �հ� %d/%d", 
		nCashCount, nCashCharge, nCreditCount, nCreditCharge, nOnlineCount, nOnlineCharge, nTransCount, nTransCharge,	nAllCountReal, nAllChargeReal);

	return sTemp;
}

void CShareRcpSubPageDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyFormView::OnSize(nType, cx, cy);
}

void CShareRcpSubPageDlg::FilterList(long nIndex, CString sSearch)
{
	//0 �Ҽ� 1/���Ҽ� 2/��ߵ� 3/������
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		BOOL bFind = FALSE;
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString sCompany = m_lstReport.GetItemText(pRecord, 0);
		CString sRiderCompany = m_lstReport.GetItemText(pRecord, 11);
		CString sStart = m_lstReport.GetItemText(pRecord, 5);
		CString sDest = m_lstReport.GetItemText(pRecord, 6);

		switch(nIndex)
		{
			case 0:
				if(sCompany.Find(sSearch) > -1)
					bFind = TRUE;
				break;
			case 1:
				if(sRiderCompany.Find(sSearch) > -1)
					bFind = TRUE;
				break;
			case 2:
				if(sStart.Find(sSearch) > -1)
					bFind = TRUE;
				break;
			case 3:
				if(sDest.Find(sSearch) > -1)
					bFind = TRUE;
				break;
		}

		pRecord->SetVisible(bFind);
	}

	m_lstReport.Populate();
}
