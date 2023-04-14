// RegionSelectDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "RegionSelectDlg.h"
#include "SearchRegionNewDlg.h"
#include "POIDataNew.h"

// CRegionSelectDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRegionSelectDlg, CMyDialog)

CRegionSelectDlg::CRegionSelectDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CRegionSelectDlg::IDD, pParent)
{

}

CRegionSelectDlg::~CRegionSelectDlg()
{
}

void CRegionSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);
	DDX_Control(pDX, IDC_FIRST_REGION_EDIT, m_edtFirstRegion);
	DDX_Control(pDX, IDC_SECOND_REGION_EDIT, m_edtSecondRegion);
	DDX_Control(pDX, IDC_THIRD_REGION_EDIT, m_edtThirdRegion);
	DDX_Control(pDX, IDC_FORTH_REGION_EDIT, m_edtForthRegion);
	DDX_Control(pDX, IDC_FIFTH_REGION_EDIT, m_edtFifthRegion);
}


BEGIN_MESSAGE_MAP(CRegionSelectDlg, CMyDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_FIRST_DELETE_BTN, (IDC_FIRST_DELETE_BTN + MAX_REGION_SELECT_COUNT), OnEnClickedDeleteItem)

	ON_BN_CLICKED(IDC_DELETE_ALL_BTN, OnBnClickedDeleteAllBtn)
	ON_BN_CLICKED(IDC_OK_BTN, OnBnClickedOkBtn)
END_MESSAGE_MAP()


// CRegionSelectDlg 메시지 처리기입니다.

BOOL CRegionSelectDlg::OnInitDialog() 
{
	CMyDialog::OnInitDialog();
	CenterWindow(GetParent());

	m_edtSearch.SetMyFont("맑은 고딕", 16, FW_BOLD);
	m_edtSearch.SetUserOption(RGB(0, 0, 255), RGB(230, 220, 255), "지역을 선택하세요");
	m_edtFirstRegion.SetMyFont("맑은 고딕", 16, FW_BOLD);
	m_edtFirstRegion.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "");
	m_edtSecondRegion.SetMyFont("맑은 고딕", 16, FW_BOLD);
	m_edtSecondRegion.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "");
	m_edtThirdRegion.SetMyFont("맑은 고딕", 16, FW_BOLD);
	m_edtThirdRegion.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "");
	m_edtForthRegion.SetMyFont("맑은 고딕", 16, FW_BOLD);
	m_edtForthRegion.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "");
	m_edtFifthRegion.SetMyFont("맑은 고딕", 16, FW_BOLD);
	m_edtFifthRegion.SetUserOption(RGB(0, 0, 255), RGB(230, 255, 220), "");

	for(int i = 0 ;i<MAX_REGION_SELECT_COUNT; i++)
	{
		if(m_nSelectedRegionDongID[i] > 0)
		{
			CEdit *pEdit = (CEdit*)GetDlgItem(IDC_FIRST_REGION_EDIT + i);
			CPOIUnit *pData = m_poiNew.GetDongPOI(m_nSelectedRegionDongID[i]);
			pEdit->SetWindowText(pData->GetRegionName(m_nSelectedRegionDongID[i]));
		}		
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRegionSelectDlg::OnEnClickedDeleteItem(UINT nFlag)
{
	//#define IDC_FIRST_REGION_EDIT           3919
	//#define IDC_FIRST_DELETE_BTN            3930

	CEdit *pEdit = (CEdit*)GetDlgItem(nFlag - 11); 
	pEdit->SetWindowText("");
	m_nSelectedRegionDongID[nFlag - IDC_FIRST_DELETE_BTN] = -1;
}

BOOL CRegionSelectDlg::IsValidRegionArray(int nRegion[MAX_REGION_SELECT_COUNT])
{
	for(int i = 0; i < MAX_REGION_SELECT_COUNT; i++)
		if(nRegion[i] > 0)
			return TRUE;

	return FALSE;
}

BOOL CRegionSelectDlg::IsSelectedRegion(int nDongID, int nRegion[MAX_REGION_SELECT_COUNT])
{
	//int Parent = pParentData->GetDongParentID(nID);
	//int ParentInParent = m_poiNew.GetDongParentID(Parent);

	//void CPOIUnit::GetTreeID(int &nSido, int &nGugun, int &nDong, int &nLi)
	//int ParentInParent, Parent, nDong, nLi;
	//CPOIUnit *pData = m_poiNew.GetDongPOI(nDongID);
	//pData->GetTreeID(ParentInParent, Parent, nDong, nLi);

	int Parent = -1, ParentInParent = -1;
	CPOIUnit *pParentData = m_poiNew.GetDongPOI(nDongID)->GetParent();
	CPOIUnit *pMoreParentData = pParentData != NULL ? pParentData->GetParent() : NULL;

	if(pParentData!= NULL) Parent = pParentData->GetDongID();
	if(pMoreParentData!= NULL) ParentInParent = pMoreParentData->GetDongID();


	for(int i = 0; i < MAX_REGION_SELECT_COUNT; i++)
	{
		if(nRegion[i] > 0)
		{
			if(nRegion[i] == nDongID || 
				nRegion[i] == Parent || 
				nRegion[i] == ParentInParent) 
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CRegionSelectDlg::PreTranslateMessage(MSG* pMsg)
{  
	if(::GetDlgCtrlID(pMsg->hwnd) == IDC_SEARCH_EDIT)
	{  
		if(pMsg->message == WM_KEYDOWN)
		{
			switch(pMsg->wParam)
			{
			case VK_RETURN:
				{
					if(m_edtSearch.GetWindowTextLength() == 0)
						OnOK();
					else
						OpenSearchRegionDlg();
				}
				return TRUE;				
			}
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CRegionSelectDlg::OpenSearchRegionDlg()
{
	long nIndex = GetAbleIndex();

	if(nIndex < 0)
	{
		MessageBox("5개 이상 선택하실 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_SEARCH_EDIT);
	CString sData; pEdit->GetWindowText(sData);

	CSearchRegionNewDlg dlg;
	dlg.m_strSearch = sData;

	if(dlg.DoModal() == IDOK) 
	{ 
		if(IsDongInsertOK(dlg.m_nDongID))
		{
			m_nSelectedRegionDongID[nIndex] = dlg.m_nDongID;
			CEdit *pReginEdit = (CEdit*)GetDlgItem(IDC_FIRST_REGION_EDIT + nIndex);

			CPOIUnit *pData = m_poiNew.GetDongPOI(dlg.m_nDongID);
			CString sDong = pData->GetRegionName();
			pReginEdit->SetWindowText(sDong);
		}
		else
		{
			MessageBox("이미 등록되어 있습니다", "확인", MB_ICONINFORMATION);
			return;
		}

		m_edtSearch.SetWindowText("");
	}	
}

BOOL CRegionSelectDlg::IsDongInsertOK(long nID)
{
	for(int i=0; i<MAX_REGION_SELECT_COUNT; i++)
	{
		if(m_nSelectedRegionDongID[i] == nID)
			return FALSE;
	}

	return TRUE;
}

long CRegionSelectDlg::GetAbleIndex()
{
	for(int i=0; i<MAX_REGION_SELECT_COUNT; i++)
	{
		if(m_nSelectedRegionDongID[i] <= 0)
			return i;
	}

	return -1;
}

void CRegionSelectDlg::OnBnClickedDeleteAllBtn()
{ 
	for(int i=0; i<MAX_REGION_SELECT_COUNT; i++)
	{
		OnEnClickedDeleteItem(IDC_FIRST_DELETE_BTN + i);
	}
}

void CRegionSelectDlg::OnBnClickedOkBtn()
{
	OnOK();
}