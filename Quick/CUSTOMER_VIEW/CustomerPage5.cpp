// CustomerPage5.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "CustomerPage5.h"

// CCustomerPage5 ��ȭ �����Դϴ�.

IMPLEMENT_DYNCREATE(CCustomerPage5, CMyFormView)
CCustomerPage5::CCustomerPage5()
	: CMyFormView(CCustomerPage5::IDD)
	, m_bIncType(FALSE)
{
	m_bIncType = TRUE;
	m_bIntegrated = FALSE;
}

CCustomerPage5::~CCustomerPage5()
{
}

void CCustomerPage5::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_lcData);
	DDX_Control(pDX, IDC_DATE_COMBO, m_DateCombo);
	DDX_Control(pDX, IDC_MINCOUNT_COMBO, m_MinCountCombo);
	DDX_Radio(pDX, IDC_INCREASE_RADIO, m_bIncType);
	DDX_Control(pDX, IDC_MINCOUNT_STATIC, m_MinCountStatic);
	DDX_Control(pDX, IDC_DATE_STATIC, m_DateStatic);
	DDX_Control(pDX, IDC_USETYPE_STATIC, m_UseTypeStatic);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_SearchBtn);
}


BEGIN_MESSAGE_MAP(CCustomerPage5, CMyFormView)
	ON_BN_CLICKED(IDC_SEARCH_BTN, OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_INCREASE_RADIO, OnBnClickedIncreaseRadio)
	ON_BN_CLICKED(IDC_DECREASE_RADIO, OnBnClickedDecreaseRadio)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_EXCEL, OnViewExcel)
END_MESSAGE_MAP()


// CCustomerPage5 �޽��� ó�����Դϴ�.

void CCustomerPage5::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_lcData.SetImageList(&m_ImageList,LVSIL_SMALL); 
	
	m_lcData.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_lcData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_lcData.InsertColumn(0,"����ȣ",LVCFMT_LEFT,80);
	m_lcData.InsertColumn(1,"��ȣ",LVCFMT_LEFT,180);
	m_lcData.InsertColumn(2,"��ȭ",LVCFMT_LEFT,100);
	m_lcData.InsertColumn(3,"�������",LVCFMT_LEFT,80);
	m_lcData.InsertColumn(4,"�����Ⱓ �Ǽ�",LVCFMT_RIGHT,100);
	m_lcData.InsertColumn(5,"���ıⰣ �Ǽ�",LVCFMT_RIGHT,100);
	m_lcData.InsertColumn(6,"����-���� �Ǽ�",LVCFMT_RIGHT,100);
	m_lcData.InsertColumn(7,"������", LVCFMT_RIGHT, 60);
	m_lcData.InsertColumn(8,"���", LVCFMT_LEFT, 100);
	m_lcData.InsertColumn(9,"��ġ", LVCFMT_LEFT, 200);
	m_DateCombo.SetCurSel(1);
	m_MinCountCombo.SetCurSel(2);

	SetResize(IDC_LIST1, sizingRightBottom);

	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCustomerPage5::RefreshList()
{
	CMyFormView::RefreshList();

	CWaitCursor wait;
	CString strMinCount, strCount;
	int index = 0;
	
	UpdateData(TRUE);
	m_lcData.DeleteAllItems();

	COleDateTime dtCur = COleDateTime::GetCurrentTime();
	COleDateTimeSpan span, twicespan;

	switch(m_DateCombo.GetCurSel())
	{
	case 0:
		span.SetDateTimeSpan(7,0,0,0);
		twicespan.SetDateTimeSpan(14,0,0,0);
		break;
	case 1:
		span.SetDateTimeSpan(14,0,0,0);
		twicespan.SetDateTimeSpan(28,0,0,0);
		break;
	case 2:
		span.SetDateTimeSpan(30,0,0,0);
		twicespan.SetDateTimeSpan(60,0,0,0);
		break;
	case 3:
		span.SetDateTimeSpan(60,0,0,0);
		twicespan.SetDateTimeSpan(120,0,0,0);
		break;
	default:
		AfxMessageBox("invalid row number");
	}

	m_MinCountCombo.GetWindowText(strMinCount);
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_customer_use_frequent5");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), 
			m_bIncType ? - atol(strMinCount) : atol(strMinCount) );
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur - twicespan);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur - span);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur - span);
	pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime), dtCur);
	if(!pRs.Execute(&pCmd)) return;


	if(pRs.IsEOF()) 
	{
		MessageBox("���ǿ� ��ġ�ϴ� �����Ͱ� ���������ʽ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	}
	else
	{
		strCount.Format("%d���� ���� �˻� �Ǿ����ϴ�.", pRs.GetRecordCount());
		LF->StatusText(0, strCount);
	}

	long nCNo, nBeforeCnt, nAfterCnt, nSubCnt, nRate, nID;
	CString strCompany, strTel;
	COleDateTime dtRegister;
	char buffer[20];
	CString strRate, strEtc, strLocation;

	while(!pRs.IsEOF())
	{
		pRs.GetFieldValue("lONo", nCNo);
		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("sCompany", strCompany);
		pRs.GetFieldValue("sTel1", strTel);
		pRs.GetFieldValue("dtRegister", dtRegister);
		pRs.GetFieldValue("BeforeCount", nBeforeCnt);
		pRs.GetFieldValue("AfterCount", nAfterCnt);
		pRs.GetFieldValue("SubCount", nSubCnt);
		pRs.GetFieldValue("Rate", nRate);
		pRs.GetFieldValue("sLocation", strLocation);
		
		if(strTel.GetLength() > 4)
		{
			m_lcData.InsertItem(index, ltoa(nID, buffer, 10));
			m_lcData.SetItemText(index, 1, strCompany);
			m_lcData.SetItemText(index, 2, LF->GetDashPhoneNumber(strTel));
			m_lcData.SetItemText(index, 3, dtRegister.Format("%Y-%m-%d"));
			m_lcData.SetItemText(index, 4, ltoa(nBeforeCnt, buffer, 10));
			m_lcData.SetItemText(index, 5, ltoa(nAfterCnt, buffer, 10));
			m_lcData.SetItemText(index, 6, ltoa(nSubCnt, buffer, 10));

			strRate.Format("%d%%", nRate);
			if(nRate >= 100) 
			{
				COLOR_STRUCT *pCS = new COLOR_STRUCT;

				pCS->crBk = RGB(230,230,255);
				pCS->crText = RGB(0,0,0);
				m_lcData.SetItemData(index, (DWORD_PTR)pCS);
				strEtc = "�ְ����";
			}
			else if(nRate <= -80) 
			{
				COLOR_STRUCT *pCS = new COLOR_STRUCT;
				pCS->crBk = RGB(255,200,200);
				pCS->crText = RGB(0,0,0);
				m_lcData.SetItemData(index, (DWORD_PTR)pCS);
				strEtc = "�ִ밨�Ұ�";
			}
			else 
			{
				strEtc = "";
			}

			m_lcData.SetItemText(index, 7, strRate);
			m_lcData.SetItemText(index, 8, strLocation);
			m_lcData.SetItemText(index++, 9, strEtc);
		}
		pRs.MoveNext();		
	}		
	m_lcData.Populate();
	pRs.Close();
}

void CCustomerPage5::OnBnClickedSearchBtn()
{
	RefreshList();
}

void CCustomerPage5::OnBnClickedIncreaseRadio()
{
	m_MinCountStatic.SetWindowText("�ּ� �Ǽ���");
}

void CCustomerPage5::OnBnClickedDecreaseRadio()
{
	m_MinCountStatic.SetWindowText("�ִ� �Ǽ���");
}

void CCustomerPage5::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lcData.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu *pRMenu=rMenu.GetSubMenu(2);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CCustomerPage5::OnViewExcel()
{
	if(!LF->POWER_CHECK(6900, "������ȯ", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nCompanyCode, 205, m_ui.nWNo, m_lcData.GetItemCount());  
	CMyExcel::ToExcel(&m_lcData);
}

