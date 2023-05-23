// DriverDetailDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "DriverDetailDlg.h"

#include "DriverDetailAddDlg.h"


// CDriverDetailDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDriverDetailDlg, CMyDialog)
CDriverDetailDlg::CDriverDetailDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CDriverDetailDlg::IDD, pParent)
	, m_strCompanyNum(_T(""))
	, m_strPart(_T(""))
	, m_strName(_T(""))
	, m_strID(_T(""))
	, m_strDailyMemo(_T(""))
	, m_nDailyPay(0)
	, m_strCustomer(_T(""))
	, m_strTitle(_T(""))
	, m_strContent(_T(""))
	, m_nInsentiveEdit(0)
	
	, m_dtTime(COleDateTime::GetCurrentTime())
	, m_dtDate(COleDateTime::GetCurrentTime())
{
	m_nCompany = 0;
	m_nRNo = 0;
}

CDriverDetailDlg::~CDriverDetailDlg()
{
}

void CDriverDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_COMPANYNUM, m_strCompanyNum);
	DDX_Text(pDX, IDC_EDIT_PART, m_strPart);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	//DDX_Text(pDX, IDC_DAILYCONTENT_COMBO, m_strDailyMemo);
	//DDX_Text(pDX, IDC_EDIT_DAILY_PAY, m_nDailyPay);
	DDX_Text(pDX, IDC_EDIT_CUSTOMER, m_strCustomer);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_strContent);
	//DDX_Text(pDX, IDC_INSENTIVE_EDIT, m_nInsentiveEdit);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dtTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Time);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_dtDate);
	DDX_Control(pDX, IDC_REWARD_COMBO, m_cmbReward);
	//DDX_Control(pDX, IDC_INSENTIVE_APPLY_CHECK, m_chkPersonApply);
	DDX_Control(pDX, IDC_LIST, m_List);	

	DDV_MaxChars(pDX, m_strDailyMemo, 40);
	DDV_MaxChars(pDX, m_strCustomer, 20);
	DDV_MaxChars(pDX, m_strTitle, 100);
	DDV_MaxChars(pDX, m_strContent, 500);

	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC4, m_Static4);
	DDX_Control(pDX, IDC_STATIC5, m_Static5);
	DDX_Control(pDX, IDC_STATIC6, m_Static6);
	DDX_Control(pDX, IDC_STATIC7, m_Static7);
	DDX_Control(pDX, IDC_STATIC8, m_Static8);
	DDX_Control(pDX, IDC_STATIC9, m_Static9);
	DDX_Control(pDX, IDC_STATIC10, m_Static10);

	DDX_Control(pDX, IDC_IDOK, m_btnOk);	
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnNew);
	DDX_Control(pDX, IDC_IDCANCEL, m_btnCanCel);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_btnModify);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDel);	

}


BEGIN_MESSAGE_MAP(CDriverDetailDlg, CMyDialog)
	ON_BN_CLICKED(IDC_IDOK, OnBnClickedIdok)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_IDCANCEL, OnBnClickedIdcancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_LIST, OnLvnDeleteallitemsList)
END_MESSAGE_MAP()


// CDriverDetailDlg 메시지 처리기입니다.

void CDriverDetailDlg::OnBnClickedIdok()
{
	OnOK();
}

void CDriverDetailDlg::RefreshList()
{
	CWaitCursor wait;
	char buffer[20];

	UpdateData(TRUE);
	m_List.DeleteAllItems();

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_driver_detail");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nCompany);
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), m_nRNo);
		
	if(!pRs.Execute(&pCmd)) return;		
	int nCount = 0;
	int nTotPoint = 0;
	int nPoint = 0;

	int nID, nCompany, nRNo, nCustomerNo;
	CString sTitle, sCustomer,sContent, sHistory, sRegister;
	COleDateTime dtRegister;
	int i = 0;

	for(i = 0; i < pRs.GetRecordCount(); i++)
	{		
		int nSubItem = 1;

		pRs.GetFieldValue("nID", nID);
		pRs.GetFieldValue("nCompany", nCompany);
		pRs.GetFieldValue("nRNo", nRNo);
		pRs.GetFieldValue("nPoint", nPoint);
		pRs.GetFieldValue("dtRegister", dtRegister);		
		pRs.GetFieldValue("sTitle", sTitle);
		pRs.GetFieldValue("sContent", sContent);
		pRs.GetFieldValue("nCustomerNo", nCustomerNo);
		pRs.GetFieldValue("sCustomer", sCustomer);		
		pRs.GetFieldValue("sRegister", sRegister);
		
		CString strReWardType;
		switch(nPoint)
		{
			case 0: strReWardType = "업무중지"; break;
			case 1: strReWardType = "주의"; break;
			case 2: strReWardType = "경고"; break;
			case 3: strReWardType = "추천"; break;
			case 4: strReWardType = ""; break;
		}

		m_List.InsertItem(i, ltoa(i, buffer, 10));
		m_List.SetItemText(i, nSubItem++, dtRegister.Format("%y-%m-%d %H:%M"));
		m_List.SetItemText(i, nSubItem++, sTitle);
		m_List.SetItemText(i, nSubItem++, strReWardType);
		m_List.SetItemText(i, nSubItem++, LF->GetDashPhoneNumber(sCustomer));
		m_List.SetItemText(i, nSubItem++, m_ci.GetName(nCompany));
		m_List.SetItemText(i, nSubItem++, sRegister);
		
		RIDER_DETAIL_INFO *ri = new RIDER_DETAIL_INFO;
		ri->nRNo = nRNo;
		ri->nCompany = nCompany;
		ri->dtRegister = dtRegister;
		ri->nID = nID;
		ri->sContent = sContent;
		ri->sReward = strReWardType;
		ri->nRewardType = nPoint;
		
		m_List.SetItemData(i,(DWORD_PTR)ri);
		nCount++;		
		pRs.MoveNext();
	}		

	if(i > 0)
	{
		m_List.InsertItem(i++,"합계");	
		m_List.SetItemText(i,2,itoa(nCount,buffer,10));
		CString strCount;
		strCount.Format("%d건" ,i);
		m_List.SetItemText(i,3,strCount);		
	}

	pRs.Close();


}
BOOL CDriverDetailDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();
	InitControl();
	RefreshList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDriverDetailDlg::InitControl(void)
{
	int nItem = 0;
	CImageList ImageList; 
	ImageList.Create(1,17,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 
	
	m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | 
				LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES);

	//컬럼 모두 지움
	int nColumnCount = m_List.GetHeaderCtrl()->GetItemCount();
	for(int i=0;i < nColumnCount;i++)
		m_List.DeleteColumn(0);
	
	m_List.InsertColumn(nItem++, "번호", LVCFMT_LEFT, 40);	
	m_List.InsertColumn(nItem++, "일시", LVCFMT_CENTER, 100);	
	m_List.InsertColumn(nItem++, "제목", LVCFMT_LEFT, 190);	
	m_List.InsertColumn(nItem++, "타입", LVCFMT_CENTER, 70);
	m_List.InsertColumn(nItem++, "고객", LVCFMT_LEFT, 90);	
    m_List.InsertColumn(nItem++, "등록회사", LVCFMT_LEFT, 70);
    m_List.InsertColumn(nItem++, "등록자", LVCFMT_LEFT, 70);

	m_Time.SetFormat("tth:mm:ss");		
	m_cmbReward.SetCurSel(0);
}

void CDriverDetailDlg::OnBnClickedButtonNew()
{
	CDriverDetailAddDlg dlg;
	
	dlg.m_nCompany = m_nCompany;
	dlg.m_nRNo = m_nRNo;
	if(dlg.DoModal() == IDOK)
	{
		RefreshList();
	}
}

void CDriverDetailDlg::OnBnClickedIdcancel()
{
	OnCancel();
}

void CDriverDetailDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		
	RIDER_DETAIL_INFO *ri = (RIDER_DETAIL_INFO*)m_List.GetItemData(pNMLV->iItem);
	if(!(pNMLV->uNewState &	LVIS_SELECTED) ) return;

	if(m_List.GetItemCount() -1 == pNMLV->iItem) return;
	UpdateData();
		
	m_dtDate.SetDate(ri->dtRegister.GetYear(),ri->dtRegister.GetMonth(),ri->dtRegister.GetDay());
	m_dtTime.SetDateTime(ri->dtRegister.GetYear(),ri->dtRegister.GetMonth(),ri->dtRegister.GetDay(),
		ri->dtRegister.GetHour(),ri->dtRegister.GetMinute(),ri->dtRegister.GetSecond() );


	m_strTitle = m_List.GetItemText(pNMLV->iItem, 2);
	m_strCustomer = m_List.GetItemText(pNMLV->iItem,4);
	m_strContent = ri->sContent;
	m_cmbReward.SetCurSel(ri->nRewardType);

	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CDriverDetailDlg::CheckData()
{
	if(m_strTitle.GetLength() <= 0 && m_strTitle.GetLength() > 40)
	{
		MessageBox("제목에 1자이상이거나 40자이하로 기입해주세요","확인",MB_ICONINFORMATION);
		return FALSE;
	}	
	return TRUE;
}
void CDriverDetailDlg::OnBnClickedButtonModify()
{
	int nItem = m_List.GetSelectionMark();
	if(nItem < 0 )
	{
		MessageBox("수정할 과거이력을 선택해주세요","확인",MB_ICONINFORMATION);
		return;
	}
	else
	{
		//if(m_ui.pi.bStaffPower == FALSE)
		//{
		//	MessageBox("수정하실 권한이없습니다.","확인",MB_ICONINFORMATION);
		//	return;
		//}

		
		if(!CheckData()) return;

		RIDER_DETAIL_INFO *ri = (RIDER_DETAIL_INFO*)m_List.GetItemData(nItem);
		if(ri == NULL) return;

		CString strReward;
		m_cmbReward.GetWindowText(strReward);

		CWaitCursor wait;
		
		UpdateData(TRUE);
		
		COleDateTime dtRegister;
		dtRegister.SetDateTime(m_dtDate.GetYear(),m_dtDate.GetMonth(), m_dtDate.GetDay(),
			m_dtTime.GetHour(), m_dtTime.GetMinute(), m_dtTime.GetSecond());

		CMkCommand pCmd(m_pMkDb, "update_driver_detail");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nCompany );
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nRNo);
		pCmd.AddParameter(typeDate, typeInput, sizeof(COleDateTime),ri->dtRegister);			
		pCmd.AddParameter(typeString, typeInput, m_strTitle.GetLength(),m_strTitle);
		pCmd.AddParameter(typeString, typeInput, m_strContent.GetLength(), m_strContent);	
		pCmd.AddParameter(typeString, typeInput, m_strCustomer.GetLength(), m_strCustomer);
		pCmd.AddParameter(typeString, typeInput, strReward.GetLength(),strReward );

		UpdateData(FALSE);

		if(!pCmd.Execute()) return;		
		
		MessageBox("수정되었습니다.","수정",MB_ICONINFORMATION);
		
		RefreshList();


	}
}

void CDriverDetailDlg::OnBnClickedButtonDelete()
{
	int nItem = m_List.GetSelectionMark();
	if(nItem < 0 )
	{
		MessageBox("삭제할 과거이력을 선택해주세요","확인",MB_ICONINFORMATION);
		return;
	}
	else
	{	
		
		if(m_ui.nRole != 0)
		{
			MessageBox("최고관리자만 삭제가 가능합니다.","권한없음",MB_ICONINFORMATION);
			return;
		}

		RIDER_DETAIL_INFO *ri = (RIDER_DETAIL_INFO*)m_List.GetItemData(nItem);
		if(ri == NULL) return;

		CWaitCursor wait;
		
		UpdateData(TRUE);
		
		CMkCommand pCmd(m_pMkDb, "delete_driver_detail");
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nID);
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nCompany );
		pCmd.AddParameter(typeLong, typeInput, sizeof(int), ri->nRNo);

		
		
		UpdateData(FALSE);

		if(!pCmd.Execute()) return;		
		
		MessageBox("삭제되었습니다.","삭제",MB_ICONINFORMATION);
		
		RefreshList();


	}
}

void CDriverDetailDlg::OnLvnDeleteallitemsList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	for(int i = 0; i < m_List.GetItemCount(); i++)
	{
		RIDER_DETAIL_INFO *ri = (RIDER_DETAIL_INFO*)m_List.GetItemData(i);
		if(ri) delete ri;
	}

	*pResult = 0;
}
