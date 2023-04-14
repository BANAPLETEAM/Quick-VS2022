// SmsNewBulkFilterDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsNewBulkFilterDlg.h"
#include "Excel.h"


// CSmsNewBulkFilterDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsNewBulkFilterDlg, CMyDialog)

CSmsNewBulkFilterDlg::CSmsNewBulkFilterDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmsNewBulkFilterDlg::IDD, pParent)
{
}

CSmsNewBulkFilterDlg::~CSmsNewBulkFilterDlg()
{
}

void CSmsNewBulkFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHONE_REPORT1, m_lstPhone1);
	DDX_Control(pDX, IDC_EXCEL_SHEET_COMBO1, m_cmbExcelSheet1);
	DDX_Control(pDX, IDC_PHONE_EDIT1, m_edtPhone1);
	DDX_Control(pDX, IDC_PHONE_REPORT2, m_lstPhone2);
	DDX_Control(pDX, IDC_EXCEL_SHEET_COMBO2, m_cmbExcelSheet2);
	DDX_Control(pDX, IDC_PHONE_EDIT2, m_edtPhone2);

	DDX_Control(pDX, IDC_RESULT_REPORT, m_lstResult);
}


BEGIN_MESSAGE_MAP(CSmsNewBulkFilterDlg, CMyDialog)
	ON_BN_CLICKED(IDC_LOAD_EXCEL_BTN1, &CSmsNewBulkFilterDlg::OnBnClickedLoadExcelBtn1)
	ON_BN_CLICKED(IDC_LOAD_EXCEL_BTN2, &CSmsNewBulkFilterDlg::OnBnClickedLoadExcelBtn2)
	ON_CBN_SELCHANGE(IDC_EXCEL_SHEET_COMBO1, &CSmsNewBulkFilterDlg::OnCbnSelchangeExcelSheetCombo1)
	ON_CBN_SELCHANGE(IDC_EXCEL_SHEET_COMBO2, &CSmsNewBulkFilterDlg::OnCbnSelchangeExcelSheetCombo2)
	ON_BN_CLICKED(IDC_LOAD_TEXT_BTN1, &CSmsNewBulkFilterDlg::OnBnClickedLoadTextBtn1)
	ON_BN_CLICKED(IDC_LOAD_TEXT_BTN2, &CSmsNewBulkFilterDlg::OnBnClickedLoadTextBtn2)
	ON_BN_CLICKED(IDC_ADD_PHONE_BUTTON1, &CSmsNewBulkFilterDlg::OnBnClickedAddPhoneButton1)
	ON_BN_CLICKED(IDC_ADD_PHONE_BUTTON2, &CSmsNewBulkFilterDlg::OnBnClickedAddPhoneButton2)
	ON_BN_CLICKED(IDC_ADD_REPORT_BTN, &CSmsNewBulkFilterDlg::OnBnClickedAddReportBtn)
	ON_BN_CLICKED(IDC_MINUS_REPORT_BTN, &CSmsNewBulkFilterDlg::OnBnClickedMinusReportBtn)
	ON_BN_CLICKED(IDC_EXCEL_BTN, &CSmsNewBulkFilterDlg::OnBnClickedExcelBtn)
END_MESSAGE_MAP()


// CSmsNewBulkFilterDlg 메시지 처리기입니다.

BOOL CSmsNewBulkFilterDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	m_cFileReport1.SetControl(&m_lstPhone1, &m_cmbExcelSheet1, &m_edtPhone1);
	m_cFileReport2.SetControl(&m_lstPhone2, &m_cmbExcelSheet2, &m_edtPhone2);


	static LOGFONT lfList = {14,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"맑은 고딕"};

	m_lstPhone1.InsertColumn(0, "전화번호", LVCFMT_LEFT, 120);
	m_lstPhone1.GetPaintManager()->m_strNoItems = "";
	m_lstPhone1.GetPaintManager()->SetTextFont(lfList);
	m_lstPhone1.ShowHeader(FALSE);
	m_lstPhone1.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_lstPhone1.Populate();

	m_lstPhone2.InsertColumn(0, "전화번호", LVCFMT_LEFT, 120);
	m_lstPhone2.GetPaintManager()->m_strNoItems = "";
	m_lstPhone2.GetPaintManager()->SetTextFont(lfList);
	m_lstPhone2.ShowHeader(FALSE);
	m_lstPhone2.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_lstPhone2.Populate();

	m_lstResult.InsertColumn(0, "전화번호", LVCFMT_LEFT, 120);
	m_lstResult.GetPaintManager()->m_strNoItems = "";
	m_lstResult.GetPaintManager()->SetTextFont(lfList);
	m_lstResult.ShowHeader(FALSE);
	m_lstResult.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_lstResult.Populate();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSmsNewBulkFilterDlg::OnBnClickedLoadExcelBtn1()
{
	m_cFileReport1.LoadExcel();
}

void CSmsNewBulkFilterDlg::OnBnClickedLoadExcelBtn2()
{
	m_cFileReport2.LoadExcel();
}

void CSmsNewBulkFilterDlg::OnCbnSelchangeExcelSheetCombo1()
{
	m_cFileReport1.ReadSheet();
}

void CSmsNewBulkFilterDlg::OnCbnSelchangeExcelSheetCombo2()
{
	m_cFileReport2.ReadSheet();
}

void CSmsNewBulkFilterDlg::OnBnClickedLoadTextBtn1()
{
	m_cFileReport1.LoadText();
}

void CSmsNewBulkFilterDlg::OnBnClickedLoadTextBtn2()
{
	m_cFileReport2.LoadText();
}

void CSmsNewBulkFilterDlg::OnBnClickedAddPhoneButton1()
{
	m_cFileReport1.AddText();
}

void CSmsNewBulkFilterDlg::OnBnClickedAddPhoneButton2()
{
	m_cFileReport2.AddText();
}

BOOL CSmsNewBulkFilterDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN) 
		{
			if(pMsg->hwnd == m_edtPhone1.GetSafeHwnd())
				OnBnClickedAddPhoneButton1();

			if(pMsg->hwnd == m_edtPhone2.GetSafeHwnd())
				OnBnClickedAddPhoneButton1();

			return TRUE;
		}

	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CSmsNewBulkFilterDlg::OnBnClickedAddReportBtn()
{
	MakeResult(TRUE);
}

void CSmsNewBulkFilterDlg::OnBnClickedMinusReportBtn()
{
	MakeResult(FALSE);
}

void CSmsNewBulkFilterDlg::MakeResult(BOOL bPlus)
{
	m_lstResult.DeleteAllItems();
	ATLMAP_PHONE *pOriginalMap = m_cFileReport1.GetPhoneMap();
	ATLMAP_PHONE *pOriginalTarget = m_cFileReport2.GetPhoneMap();

	if(bPlus)
	{
		ATLMAP_PHONE::CPair *pPair = NULL;
		POSITION pos = pOriginalTarget->GetStartPosition();

		while(pos)
		{
			pPair = pOriginalTarget->GetNext(pos);
			pOriginalMap->SetAt(pPair->m_key, pPair->m_value);
		}
	}
	else
	{
		ATLMAP_PHONE::CPair *pPair = NULL;
		POSITION pos = pOriginalTarget->GetStartPosition();

		while(pos)
		{
			pPair = pOriginalTarget->GetNext(pos);
			pOriginalMap->RemoveKey(pPair->m_key);
		}
	}
	ATLMAP_PHONE::CPair *pPair = NULL;
	POSITION pos = pOriginalMap->GetStartPosition();

	long nItem = 0;

	while(pos)
	{
		pPair = pOriginalMap->GetNext(pos);
		m_lstResult.InsertItem(nItem++, pPair->m_value);
	}

	m_lstResult.Populate();

}

void CSmsNewBulkFilterDlg::OnBnClickedExcelBtn()
{
	if(m_lstResult.GetItemCount() <= 0)
	{
		MessageBox("저장 할 리스트에 값이 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CMyExcel::ToExcel(&m_lstResult);
}
