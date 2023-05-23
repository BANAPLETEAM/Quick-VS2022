// CardPayLogDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "quick.h"
#include "CardPayLogDlg.h"


// CCardPayLogDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCardPayLogDlg, CMyDialog)

CCardPayLogDlg::CCardPayLogDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CCardPayLogDlg::IDD, pParent)
{
	m_nTNo = 0;
}

CCardPayLogDlg::~CCardPayLogDlg()
{
}

void CCardPayLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG_LIST, m_lstReport);
}


BEGIN_MESSAGE_MAP(CCardPayLogDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CCardPayLogDlg::OnBnClickedOk)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCardPayLogDlg �޽��� ó�����Դϴ�.

void CCardPayLogDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnOK();
}

BOOL CCardPayLogDlg::OnInitDialog()
{ 
	CMyDialog::OnInitDialog();

	m_lstReport.InsertColumn(0, "�ð�", LVCFMT_CENTER, 120);
	m_lstReport.InsertColumn(1, "���;��̵�", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(2, "���ι�ȣ", LVCFMT_LEFT, 75);
	m_lstReport.InsertColumn(3, "ī���ȣ", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(4, "�ݾ�", LVCFMT_RIGHT, 60);
	m_lstReport.InsertColumn(5, "����", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(6, "�α��ξ��̵�", LVCFMT_LEFT, 80);
	m_lstReport.GetPaintManager()->m_strNoItems = "ī�����/��� ������ �����ϴ�.";
	m_lstReport.Populate();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCardPayLogDlg::RefreshList()
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_card_pay_log");
	cmd.AddParameter(m_nTNo);

	if(!rs.Execute(&cmd))
		return;

	COleDateTime dtLog;
	CString strMID, strOKNumber, strCard4Digits, strRetCodeMsg, strID;
	long nOrgAmt;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("dtLog", dtLog);
		rs.GetFieldValue("MID", strMID);
		rs.GetFieldValue("OKNumber", strOKNumber);
		rs.GetFieldValue("sCard4Digits", strCard4Digits);
		rs.GetFieldValue("sRetCodeMsg", strRetCodeMsg);
		rs.GetFieldValue("sID", strID);
		rs.GetFieldValue("nOrgAmt", nOrgAmt);

		CString strTemp;
		strTemp.Format("%s(%s)", dtLog.Format("%m-%d %H:%M:%S"), LF->GetDay(dtLog));

		m_lstReport.InsertItem(i, strTemp);
		m_lstReport.SetItemText(i, 1, strMID);
		m_lstReport.SetItemText(i, 2, strOKNumber);
		m_lstReport.SetItemText(i, 3, strCard4Digits);
		m_lstReport.SetItemText(i, 4, LF->GetMyNumberFormat(nOrgAmt));
		m_lstReport.SetItemText(i, 5, strRetCodeMsg);
		m_lstReport.SetItemText(i, 6, strID);

		rs.MoveNext();
	}

	m_lstReport.Populate();
}

void CCardPayLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(m_lstReport.GetSafeHwnd())
	{
		CRect rcForm, rcList;
		GetClientRect(rcForm);
		m_lstReport.GetWindowRect(rcList);
		ScreenToClient(rcList);

		rcList.right = rcForm.right - 10;
		rcList.bottom = rcForm.bottom - 10;
		m_lstReport.MoveWindow(rcList);
	}
}
