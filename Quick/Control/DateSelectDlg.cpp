// DateSelectDlg.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"
#include "resource.h"
#include "DateSelectDlg.h"

// CDateSelectDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDateSelectDlg, CMyDialog)

CDateSelectDlg::CDateSelectDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDateSelectDlg::IDD, pParent)
	, m_dtDate(COleDateTime::GetCurrentTime())
	, m_dtTime(COleDateTime::GetCurrentTime())
{
	m_strTitle = "";
	m_bAllocate = FALSE;
	m_dtLastAllocate.SetStatus(COleDateTime::invalid);
}

CDateSelectDlg::~CDateSelectDlg()
{
}

void CDateSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATE, m_ctpDt);
	DDX_Control(pDX, IDC_TIME, m_ctpTime);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_dtDate);
	DDX_DateTimeCtrl(pDX, IDC_TIME, m_dtTime);
}


BEGIN_MESSAGE_MAP(CDateSelectDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CDateSelectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDateSelectDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDateSelectDlg �޽��� ó�����Դϴ�.

void CDateSelectDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if(m_bAllocate)
	{
		if(m_dtLastAllocate.GetStatus() == COleDateTime::valid)
		{
			COleDateTimeSpan span = m_dtDate - m_dtLastAllocate;
			if(span.GetDays() > 180)
			{
				MessageBox("���������� 6���� �̻� ������ �� �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
				return;
			}
		}
		else
		{
			if(MessageBox("���������� �����Ǿ��ִ� ����Դϴ�.\n������ �����Ͻðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) != IDOK)
				return;
		}
	}


	m_dtDateTime.SetDateTime(m_dtDate.GetYear(), m_dtDate.GetMonth(), m_dtDate.GetDay(), m_dtTime.GetHour(), m_dtTime.GetMinute(), m_dtTime.GetSecond());
		
	OnOK();
}

BOOL CDateSelectDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	SetWindowText(m_strTitle);
	m_ctpTime.SetFormat("tth-mm");

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDateSelectDlg::OnBnClickedCancel()
{
	OnCancel();
}
