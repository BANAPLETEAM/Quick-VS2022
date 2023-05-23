// SelectChargeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SelectChargeDlg.h"



// CSelectChargeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSelectChargeDlg, CMyDialog)
CSelectChargeDlg::CSelectChargeDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSelectChargeDlg::IDD, pParent)
{
	m_pRs = NULL;
	m_nChargeBasic = 0;
	m_nChargeAdd = 0;
	m_nChargeDis = 0;
}

CSelectChargeDlg::~CSelectChargeDlg()
{
}

void CSelectChargeDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_DONG_CHARGE_EDIT, m_strDongCharge);
}


BEGIN_MESSAGE_MAP(CSelectChargeDlg, CMyDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
	ON_BN_CLICKED(IDC_DONG_CHARGE_BTN, OnBnClickedDongChargeBtn)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CSelectChargeDlg 메시지 처리기입니다.

BOOL CSelectChargeDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	
	CImageList m_ImageList; 
	m_ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&m_ImageList,LVSIL_SMALL); 
	
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	m_List.InsertColumn(0,"날짜",LVCFMT_LEFT,75);
	m_List.InsertColumn(1,"출발지",LVCFMT_LEFT,130);
	m_List.InsertColumn(2,"도착지",LVCFMT_LEFT,130);
	m_List.InsertColumn(3,"급",LVCFMT_LEFT,40);
	m_List.InsertColumn(4,"왕복",LVCFMT_LEFT,40);
	m_List.InsertColumn(5,"차량",LVCFMT_LEFT,40);
	m_List.InsertColumn(6,"기본",LVCFMT_RIGHT,60);
	m_List.InsertColumn(7,"추가",LVCFMT_RIGHT,60);
	m_List.InsertColumn(8,"할인",LVCFMT_RIGHT,60);

	if(m_pRs != NULL)
	{	
		COleDateTime dt1;
		CString strSName, strDName, strStart, strDest;
		long nRunType, nWayType;
		long nCarType, nBasic, nAdd, nDis;
		char buffer[10];

		for(int i = 0; i < m_pRs->GetRecordCount(); i++)
		{
			m_pRs->GetFieldValue("dt1", dt1);
			m_pRs->GetFieldValue("sSName", strSName);
			m_pRs->GetFieldValue("sSDong", strStart);
			m_pRs->GetFieldValue("sDName", strDName);
			m_pRs->GetFieldValue("sDDong", strDest);
			m_pRs->GetFieldValue("nRunType", nRunType);
			m_pRs->GetFieldValue("nWayType", nWayType);
			m_pRs->GetFieldValue("nCarType", nCarType);
			m_pRs->GetFieldValue("nChargeBasic", nBasic);
			m_pRs->GetFieldValue("nChargeAdd", nAdd);
			m_pRs->GetFieldValue("nChargeDis", nDis);

			if(strSName.GetLength() > 0)
				strStart += "(" + strSName + ")";

			if(strDName.GetLength() > 0)
				strDest += "(" + strDName + ")";

			m_List.InsertItem(i, dt1.Format("%Y-%m-%d"));
			m_List.SetItemText(i, 1, strStart);
			m_List.SetItemText(i, 2, strDest);
			m_List.SetItemText(i, 3, LF->GetRunTypeFromLong(nRunType, 1));
			m_List.SetItemText(i, 4, LF->GetWayTypeFromLong(nWayType, 1));
			m_List.SetItemText(i, 5, LF->GetCarTypeFromLong(nCarType, 1));
			m_List.SetItemText(i, 6, ltoa(nBasic, buffer, 10));
			m_List.SetItemText(i, 7, ltoa(nAdd, buffer, 10));
			m_List.SetItemText(i, 8, ltoa(nDis, buffer, 10));

			if(i == 0)
			{
				m_nWayType = nWayType;
				m_nRunType = nRunType;
				m_nCarType = nCarType;
				m_nChargeBasic = nBasic;
				m_nChargeAdd = nAdd;
				m_nChargeDis = nDis;
			}

			m_pRs->MoveNext();
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSelectChargeDlg::OnBnClickedOk()
{
	OnOK();
}

void CSelectChargeDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if(!(pNMLV->uNewState & LVIS_SELECTED)) return;
	int nItem = pNMLV->iItem;

	m_nRunType = LF->GetRunTypeFromString(m_List.GetItemText(nItem, 3));
	m_nWayType = LF->GetWayTypeFromString(m_List.GetItemText(nItem, 4));
	m_nCarType = LF->GetCarTypeFromString(m_List.GetItemText(nItem, 5));
	m_nChargeBasic = atol(m_List.GetItemText(nItem, 6));
	m_nChargeAdd = atol(m_List.GetItemText(nItem, 7));
	m_nChargeDis = atol(m_List.GetItemText(nItem, 8));

	*pResult = 0;
}

void CSelectChargeDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nItem;

	if((nItem = m_List.GetNextItem(-1, LVNI_SELECTED)) < 0) 
		return;

	m_nRunType = LF->GetRunTypeFromString(m_List.GetItemText(nItem, 3));
	m_nWayType = LF->GetWayTypeFromString(m_List.GetItemText(nItem, 4));
	m_nCarType = LF->GetCarTypeFromString(m_List.GetItemText(nItem, 5));
	m_nChargeBasic = atol(m_List.GetItemText(nItem, 6));
	m_nChargeAdd = atol(m_List.GetItemText(nItem, 7));
	m_nChargeDis = atol(m_List.GetItemText(nItem, 8));

	OnOK();

	*pResult = 0;
}

void CSelectChargeDlg::OnBnClickedDongChargeBtn()
{
	m_nChargeBasic = atol(m_strDongCharge);
	OnOK();
}

void CSelectChargeDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}
