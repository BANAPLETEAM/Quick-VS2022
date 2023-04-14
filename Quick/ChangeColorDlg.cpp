// ChangeColorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "ChangeColorDlg.h"



// CChangeColorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChangeColorDlg, CDialog)
CChangeColorDlg::CChangeColorDlg(CWnd* pParent /*=NULL*/)
: CXTResizeDialog(CChangeColorDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_bMoreColors = TRUE;
	m_clrText = RGB(0xff,0xff,0xff);
	m_clrBack = RGB(0x00,0x00,0xff);
}

CChangeColorDlg::~CChangeColorDlg()
{
}

void CChangeColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITEL_EDIT, m_TitleEdt);
	DDX_Control(pDX, IDC_CLR_TEXT, m_cpTextColor);
	DDX_Control(pDX, IDC_CLR_BACK, m_cpBackColor);
	DDX_XTColorPicker(pDX, IDC_CLR_TEXT, m_clrText);
	DDX_XTColorPicker(pDX, IDC_CLR_BACK, m_clrBack);
	DDX_Control(pDX, IDC_COMBO_DEMO, m_comboBox);
	DDX_Check(pDX, IDC_CHK_MORECOLORS, m_bMoreColors);
}


BEGIN_MESSAGE_MAP(CChangeColorDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYDRAGICON()
	ON_CPN_XT_SELENDOK(IDC_CLR_TEXT, OnSelEndOkTextClr)
	ON_CPN_XT_SELENDOK(IDC_CLR_BACK, OnSelEndOkBackClr)
	ON_BN_CLICKED(IDC_CHK_MORECOLORS, OnChkMorecolors)

	ON_BN_CLICKED(IDC_DEFAULT_COLOR_BTN, OnBnClickedDefaultColorBtn)
END_MESSAGE_MAP()


// CChangeColorDlg 메시지 처리기입니다.



void CChangeColorDlg::OnBnClickedOk()
{

	UpdateData(true);

	int nRTextColor = GetRValue(m_clrText);
	int nGTextColor = GetGValue(m_clrText);
	int nBTextColor =GetBValue(m_clrText);

	int nRBackColor = GetRValue(m_clrBack);
	int nGBackColor = GetGValue(m_clrBack);
	int nBBackColor =GetBValue(m_clrBack);

	long nTotalTextColor = nRTextColor + (nGTextColor << 8) + (nBTextColor << 16);
	long nTotalBackColor = nRBackColor + (nGBackColor << 8) + (nBBackColor << 16);

	if(nTotalBackColor == nTotalTextColor)
	{
		MessageBox("글자색과 바탕색이 같습니다", "확인", MB_ICONERROR);
		return;
	}

	m_TitleEdt.GetWindowText(m_sTitle);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "update_CompanyInfo");

	pCmd.AddParameter(typeLong, typeInput,sizeof(long), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput,sizeof(long), nTotalBackColor);
	pCmd.AddParameter(typeLong, typeInput,sizeof(long), nTotalTextColor);
	pCmd.AddParameter(typeString, typeInput, m_sTitle.GetLength(), m_sTitle);

	if(!pRs.Execute(&pCmd)) return;	

	MessageBox("변경되었습니다", "확인", MB_ICONINFORMATION);

	m_pBi->nRcpColor = nTotalBackColor;
	m_pBi->nRcpTextColor = nTotalTextColor;
	m_pBi->strMemo = m_sTitle;


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();

}

BOOL CChangeColorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CPoint point;
	GetCursorPos(&point);
	SetWindowPos(NULL, point.x, point.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	//MoveWindow(point.x, point.y, m_rect.Width(), m_rect.Height(), NULL);

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_CompanyInfo");

	pCmd.AddParameter(typeLong, typeInput,sizeof(long), m_nCompany);

	long nRcpColor, nRcpTextColor;
	CString sRcpColor,  sPenaltyMemo;

	if(!pRs.Execute(&pCmd)) return true;

	pRs.GetFieldValue("nRcpColor", nRcpColor);
	pRs.GetFieldValue("nRcpTextColor", nRcpTextColor);
	pRs.GetFieldValue("sMemo", m_sTitle);
	pRs.GetFieldValue("sPenaltyMemo", sPenaltyMemo);

	m_TitleEdt.SetWindowText(m_sTitle);
	int nRTextColor = GetRValue(nRcpTextColor);
	int nGTextColor = GetGValue(m_clrText);
	int nBTextColor =GetBValue(m_clrText);

	m_clrBack = RGB(GetRValue(nRcpColor), GetGValue(nRcpColor), GetBValue(nRcpColor));
	m_clrText = RGB(GetRValue(nRcpTextColor), GetGValue(nRcpTextColor), GetBValue(nRcpTextColor));

	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	SetResize(IDC_COMBO_DEMO,  SZ_TOP_LEFT,  SZ_TOP_RIGHT);
	SetResize(IDCANCEL,        SZ_TOP_RIGHT, SZ_TOP_RIGHT);

	// prevent vertical resizing.
	SetFlag(xtResizeNoVertical);


	//------------------------------------
	// TODO: Add extra initialization here
	//------------------------------------

	m_comboBox.AddString("접수창에 나타나는 화면입니다");
	m_comboBox.SetCurSel(0);

	m_cpBackColor.SetColor(m_clrBack);
	m_cpBackColor.SetDefaultColor(GetSysColor(COLOR_WINDOW));

	m_cpTextColor.SetColor(m_clrText);
	m_cpTextColor.SetDefaultColor(GetSysColor(COLOR_WINDOWTEXT));

	// Add some user defined color values.
	CUIntArray arUserColors;
	arUserColors.Add(RGB(150,0,0));
	arUserColors.Add(RGB(0,150,0));
	arUserColors.Add(RGB(0,0,150));
	CXTColorSelectorCtrl::SetUserColors(arUserColors);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CChangeColorDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CChangeColorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

	CXTResizeDialog::OnSysCommand(nID, lParam);
}

void CChangeColorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CXTResizeDialog::OnPaint();
	}
}

HBRUSH CChangeColorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CXTResizeDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	int nItem = pWnd->GetDlgCtrlID();
	switch (nItem)
	{
	case IDC_COMBO_DEMO:
		if( pWnd->IsWindowEnabled( ))
		{
			pDC->SetTextColor(m_clrText);
			pDC->SetBkColor(m_clrBack);
		}
		break;
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

HCURSOR CChangeColorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialog::OnQueryDragIcon();
}

void CChangeColorDlg::OnSelEndOkTextClr()
{
	UpdateData();
	m_comboBox.Invalidate();
}

void CChangeColorDlg::OnSelEndOkBackClr()
{
	UpdateData();
	m_comboBox.Invalidate();
}

void CChangeColorDlg::OnChkMorecolors()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	DWORD dwRem = m_bMoreColors ? 0 : CPS_XT_MORECOLORS;
	DWORD dwAdd = m_bMoreColors ? CPS_XT_MORECOLORS : 0;

	m_cpBackColor.ModifyCPStyle(dwRem, dwAdd);
	m_cpTextColor.ModifyCPStyle(dwRem, dwAdd);
}


void CChangeColorDlg::OnBnClickedDefaultColorBtn()
{
	UpdateData();
	m_clrBack = RGB(255, 255, 255);
	m_clrText = RGB(0, 0, 0);

	m_cpBackColor.SetColor(m_clrBack);
	m_cpTextColor.SetColor(m_clrText);

	m_comboBox.Invalidate();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
