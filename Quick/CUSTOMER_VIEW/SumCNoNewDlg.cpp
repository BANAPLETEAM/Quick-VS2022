// SumCNoNewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SumCNoNewDlg.h"


// CSumCNoNewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSumCNoNewDlg, CMyDialog)

CSumCNoNewDlg::CSumCNoNewDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSumCNoNewDlg::IDD, pParent)
{
	m_nDelCNo = 0;
	m_nSumCNo = 0;
}

CSumCNoNewDlg::~CSumCNoNewDlg()
{
}

void CSumCNoNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEL_NAME_STATIC, m_stcDelName);
	DDX_Control(pDX, IDC_DEL_NO_STATIC, m_stcDelNo);
	DDX_Control(pDX, IDC_SUM_NAME_STATIC, m_stcSumName);
	DDX_Control(pDX, IDC_SUM_NO_STATIC, m_stcSumNo);
	DDX_Control(pDX, IDC_DEL_PHONE_LIST, m_lstDelPhone);
	DDX_Control(pDX, IDC_SUM_PHONE_LIST, m_lstSumPhone);
}


BEGIN_MESSAGE_MAP(CSumCNoNewDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, &CSumCNoNewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSumCNoNewDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSumCNoNewDlg 메시지 처리기입니다.

void CSumCNoNewDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void CSumCNoNewDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}

BOOL CSumCNoNewDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	RefreshInfo(m_nDelCNo, &m_lstDelPhone, &m_stcDelName, &m_stcDelNo);
	RefreshInfo(m_nSumCNo, &m_lstSumPhone, &m_stcSumName, &m_stcSumNo);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSumCNoNewDlg::RefreshInfo(long nCNo, CListBox *pListBox, CStatic *stcName, CStatic *strNo)
{
	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_customer_phone_list");
	cmd.AddParameter(nCNo);
	CMkParameter *pParCompany = cmd.AddParameter(typeString,typeOutput, 100, "");
	CMkParameter *pParID = cmd.AddParameter(typeLong,typeOutput, sizeof(long), 0);

	if(!rs.Execute(&cmd))
		return;
 
	CString strName; pParCompany->GetValue(strName);
	long nID; pParID->GetValue(nID);

	stcName->SetWindowText(strName);
	strNo->SetWindowText(LF->GetStringFromLong(nID));

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		CString strTel;
		rs.GetFieldValue("sTel", strTel);
		pListBox->InsertString(i, strTel);

		rs.MoveNext();
	}
	
}