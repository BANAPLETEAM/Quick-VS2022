// QueryChargeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "QueryChargeDlg.h"
#include "MkMessenger.h"

// CQueryChargeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CQueryChargeDlg, CMyDialog)
CQueryChargeDlg::CQueryChargeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CQueryChargeDlg::IDD, pParent)
{
	m_bChargeSave = TRUE;
	m_nMNo = 0;
}

CQueryChargeDlg::~CQueryChargeDlg()
{
}

void CQueryChargeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtCharge);
	DDX_Control(pDX, IDC_ETC_EDIT, m_edtEtc);

	DDX_Text(pDX, IDC_CHARGE_EDIT, m_strCharge);
	DDX_Text(pDX, IDC_ETC_EDIT, m_strEtc);
	DDX_Text(pDX, IDC_CUSTOMER_EDIT, m_strCustomer);
	DDX_Text(pDX, IDC_START_EDIT, m_strStart);
	DDX_Text(pDX, IDC_START_DONG_EDIT, m_strStartDong);
	DDX_Text(pDX, IDC_DEST_EDIT, m_strDest);
	DDX_Text(pDX, IDC_DEST_DONG_EDIT, m_strDestDong);
	DDX_Check(pDX, IDC_CHARGE_SAVE_CHECK, m_bChargeSave);
	DDX_Text(pDX, IDC_OP_STATIC, m_strOP);
}


BEGIN_MESSAGE_MAP(CQueryChargeDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CQueryChargeDlg 메시지 처리기입니다.

BOOL CQueryChargeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	long nTop = AfxGetApp()->GetProfileInt("QueryDlg", "nTop", 0);
	long nLeft = AfxGetApp()->GetProfileInt("QueryDlg", "nLeft", 0);

	if(nTop != 0)
	{
		CRect rect, rcDlg;

		this->GetWindowRect(&rcDlg);

		rect.top = nTop;
		rect.bottom = nTop + rcDlg.Height();
		rect.left = nLeft;
		rect.right = nLeft + rcDlg.Width();

		this->MoveWindow(rect);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CQueryChargeDlg::OnBnClickedOk()
{
	OnOK();
}

void CQueryChargeDlg::OnOK()
{
	UpdateData(TRUE);

	m_strCharge.Remove(',');
	if(atol(m_strCharge) < 500)
		m_strCharge.Format("%d", atol(m_strCharge)*1000);

	char buffer[10];
	char szQueryCharge[512];
	szQueryCharge[0] = 0;
 
	STRCAT2("^&", szQueryCharge, "$$%RESPONSECHARGE2", m_strUniqueID,
		m_strCharge, m_strEtc, ltoa(m_bChargeSave, buffer, 10), m_strStart + " -> " + m_strDest, VL_END);

	m_pNewMsgDlg->SendMsg(szQueryCharge);


	SaveLocation();

	CMyDialog::OnOK();

	delete this;
}

void CQueryChargeDlg::OnCancel()
{
	m_pNewMsgDlg->SendMsg(m_strStart + "-> " + 
		m_strDest + "의 요금문의를 취소하였습니다.");

	CMyDialog::OnCancel();
	delete this;
}


BOOL CQueryChargeDlg::PreTranslateMessage(MSG* pMsg)
{
	return CMyDialog::PreTranslateMessage(pMsg);
}

void CQueryChargeDlg::OnBnClickedCancel()
{
	SaveLocation();

	OnCancel();
}

void CQueryChargeDlg::SaveLocation()
{
	CRect rect;
	this->GetWindowRect(&rect);

	AfxGetApp()->WriteProfileInt("QueryDlg", "nTop", rect.top);
	AfxGetApp()->WriteProfileInt("QueryDlg", "nLeft", rect.left);
}
