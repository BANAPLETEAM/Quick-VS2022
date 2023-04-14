// CallBackPhoneRoleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "CallBackPhoneRoleDlg.h"


// CCallBackPhoneRoleDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCallBackPhoneRoleDlg, CMyDialog)

CCallBackPhoneRoleDlg::CCallBackPhoneRoleDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCallBackPhoneRoleDlg::IDD, pParent)
{

}

CCallBackPhoneRoleDlg::~CCallBackPhoneRoleDlg()
{
}

void CCallBackPhoneRoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCallBackPhoneRoleDlg, CMyDialog)
END_MESSAGE_MAP()


// CCallBackPhoneRoleDlg 메시지 처리기입니다.
