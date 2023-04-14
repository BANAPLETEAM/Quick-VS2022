// AddRcpNoticeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "AddRcpNoticeDlg.h"
#include ".\addrcpnoticedlg.h"


// CAddRcpNoticeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddRcpNoticeDlg, CMyDialog)
CAddRcpNoticeDlg::CAddRcpNoticeDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CAddRcpNoticeDlg::IDD, pParent)
, m_dtRevDate(COleDateTime::GetCurrentTime())
, m_dtRevTime(COleDateTime::GetCurrentTime())
, m_bRevNotice(FALSE)
{
	m_bReadOnly = FALSE;
	m_dtRevDateTime = COleDateTime::GetCurrentTime();
}

CAddRcpNoticeDlg::~CAddRcpNoticeDlg()
{
}

void CAddRcpNoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NOTICE_EDIT, m_strNotice);
	DDX_Control(pDX, IDC_REV_NOTICE_CHECK, m_chkRevNotice);
	DDX_Check(pDX, IDC_REV_NOTICE_CHECK, m_bRevNotice);
	DDX_Control(pDX, IDC_REV_DATE, m_dtpRevDate);
	DDX_DateTimeCtrl(pDX, IDC_REV_DATE, m_dtRevDate);
	DDX_Control(pDX, IDC_REV_TIME, m_dtpRevTime);
	DDX_DateTimeCtrl(pDX, IDC_REV_TIME, m_dtRevTime);
	DDX_Control(pDX, IDC_NOTICE_EDIT, m_edtNotice);
}


BEGIN_MESSAGE_MAP(CAddRcpNoticeDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_REV_NOTICE_CHECK, &CAddRcpNoticeDlg::OnBnClickedRevNoticeCheck)
END_MESSAGE_MAP()


// CAddRcpNoticeDlg 메시지 처리기입니다.

BOOL CAddRcpNoticeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	//if(m_bReadOnly)
	//{ 
	//	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	//	((CEdit*)GetDlgItem(IDC_NOTICE_EDIT))->SetReadOnly(TRUE);
	//}

	//m_edtNotice.SetMyFont("맑은 고딕", 17, FW_NORMAL);
	//m_edtNotice.SetUserOption(RGB(0, 0, 0), RGB(220, 255, 180), "");
	m_edtNotice.SetFont(m_FontManager.GetFont("맑은 고딕", 17, FW_NORMAL));

	UpdateData(FALSE);
	OnBnClickedRevNoticeCheck();

	if(m_bReadOnly == TRUE)
	{
		m_chkRevNotice.EnableWindow(FALSE); 

		if(m_bRevNotice)
		{			
			m_dtpRevDate.EnableWindow(TRUE);
			m_dtpRevTime.EnableWindow(TRUE);
		}
		else
		{
			m_dtpRevDate.EnableWindow(FALSE);
			m_dtpRevTime.EnableWindow(FALSE);
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAddRcpNoticeDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if(m_strNotice.IsEmpty()) 
		MessageBox("내용을 입력하시기 바랍니다.", "확인", MB_ICONINFORMATION);
	else
	{
		if(m_chkRevNotice.GetCheck() == BST_CHECKED)
		{
			COleDateTime dtCur = COleDateTime::GetCurrentTime();
			COleDateTime dtRev = COleDateTime(m_dtRevDate.GetYear(), m_dtRevDate.GetMonth(), m_dtRevDate.GetDay(), m_dtRevTime.GetHour(), m_dtRevTime.GetMinute(), 0);

			if(dtCur > dtRev)
			{
				MessageBox("현재시간보다 이전 시간은 입력 하실 수 없습니다", "확인", MB_ICONINFORMATION);
				return;
			}

			m_dtRevDateTime = dtRev;			
		}

		CDialog::OnOK();
	}
}

void CAddRcpNoticeDlg::OnOK()
{
	//CDialog::OnOK();
}

void CAddRcpNoticeDlg::OnBnClickedRevNoticeCheck()
{
	m_dtpRevDate.EnableWindow(m_chkRevNotice.GetCheck()); 
	m_dtpRevTime.EnableWindow(m_chkRevNotice.GetCheck());
}
