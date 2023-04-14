// DateSelectDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "resource.h"
#include "DateSelectDlg.h"

// CDateSelectDlg 대화 상자입니다.

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


// CDateSelectDlg 메시지 처리기입니다.

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
				MessageBox("배차제한을 6개월 이상 설정할 수 없습니다.", "확인", MB_ICONINFORMATION);
				return;
			}
		}
		else
		{
			if(MessageBox("무제한으로 설정되어있는 기사입니다.\n기한을 변경하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDateSelectDlg::OnBnClickedCancel()
{
	OnCancel();
}
