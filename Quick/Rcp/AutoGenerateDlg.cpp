// AutoGenerateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "AutoGenerateDlg.h"



// CAutoGenerateDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAutoGenerateDlg, CMyDialog)
CAutoGenerateDlg::CAutoGenerateDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CAutoGenerateDlg::IDD, pParent)
{
}

CAutoGenerateDlg::~CAutoGenerateDlg()
{
}

void CAutoGenerateDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FROM_EDIT, m_strFrom);
	DDX_Text(pDX, IDC_TO_EDIT, m_strTo);
	DDX_Text(pDX, IDC_UNIT_EDIT, m_strUnit);
	DDX_Text(pDX, IDC_DEPOSIT_EDIT, m_strDeposit);
}


BEGIN_MESSAGE_MAP(CAutoGenerateDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()



// CAutoGenerateDlg 메시지 처리기입니다.

void CAutoGenerateDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	try {
		if(m_strFrom.IsEmpty()) throw "구간생성 시작값을 입력하시기 바랍니다.";
		if(m_strTo.IsEmpty()) throw "구간생성 끝값을 입력하시기 바랍니다.";
		if(atol(m_strTo) > 600000) throw "구간생성 끝값은 60만원 이하여야 합니다.";
		if(atol(m_strFrom) >= atol(m_strTo)) throw "구간생성 시작값이 끝값보다 작아야 합니다.";
		if(atol(m_strUnit) < 500) throw "구간값은 500원 이상이여야 합니다.";
		if(m_strDeposit.IsEmpty()) throw "입금액을 입력하시기 바랍니다.";

	}
	catch(char *szMsg) 
	{
		MessageBox(szMsg,"유효성 검사", MB_ICONINFORMATION);
		return;
	}

	OnOK();
}
