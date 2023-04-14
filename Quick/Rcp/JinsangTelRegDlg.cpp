// JinsangTelRegDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "JinsangTelRegDlg.h"


// CJinsangTelRegDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CJinsangTelRegDlg, CMyDialog)
CJinsangTelRegDlg::CJinsangTelRegDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CJinsangTelRegDlg::IDD, pParent)
	, m_sTelNumber(_T(""))
	, m_sName(_T(""))
	, m_nDuration(0)
	, m_sDesc(_T(""))
{
}

CJinsangTelRegDlg::~CJinsangTelRegDlg()
{
}

void CJinsangTelRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TELNUMBER, m_sTelNumber);
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDX_Text(pDX, IDC_EDIT1_DURATION, m_nDuration);
	DDX_Text(pDX, IDC_EDIT_DESC, m_sDesc);
	DDX_Control(pDX, IDC_COMBO_DURATION, m_cComboDuration);
}


BEGIN_MESSAGE_MAP(CJinsangTelRegDlg, CMyDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DURATION, OnCbnSelchangeComboDuration)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CJinsangTelRegDlg 메시지 처리기입니다.

void CJinsangTelRegDlg::OnCbnSelchangeComboDuration()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCurSel = m_cComboDuration.GetCurSel();
	if(nCurSel == -1) return;

	CString sDuration;
	m_cComboDuration.GetLBText(nCurSel,sDuration);
	m_nDuration = atoi(sDuration);
	UpdateData(FALSE);
}

BOOL CJinsangTelRegDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	m_cComboDuration.ResetContent();
	m_cComboDuration.AddString("7   -1주일");
	m_cComboDuration.AddString("30  -1개월");
	m_cComboDuration.AddString("90  -3개월");
	m_cComboDuration.AddString("180 -6개월");
	m_cComboDuration.AddString("365 -1년");
	m_cComboDuration.AddString("3650-10년");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CJinsangTelRegDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	this->m_sTelNumber.Trim();
	if(m_sTelNumber.IsEmpty())
	{
		MessageBox("진상고객 전화가 등록되지 않았습니다.", 
				"확인", 
				MB_ICONINFORMATION);
		
		return;
	}

	if(this->m_nDuration <= 0)
	{
		MessageBox("진상고객 전화가 등록되지 않았습니다.", 
				"확인", 
				MB_ICONINFORMATION);
		return;
	}

	OnOK();
}

void CJinsangTelRegDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
