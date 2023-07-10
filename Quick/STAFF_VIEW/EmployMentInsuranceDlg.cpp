// EmployMentInsuranceDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "EmployMentInsuranceDlg.h"
#include "WebUploadDlg.h"
#include "SearchRegionHolidayDlg.h"


// CEmployMentInsuranceDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEmployMentInsuranceDlg, CDialog)

CEmployMentInsuranceDlg::CEmployMentInsuranceDlg(CWnd* pParent /*=NULL*/)
: CDialog(CEmployMentInsuranceDlg::IDD, pParent)
{
	m_strBizNoImage.Empty();
}

CEmployMentInsuranceDlg::~CEmployMentInsuranceDlg()
{
}

void CEmployMentInsuranceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COMPNY_BIZ_NO, m_edtCompanyBizNo);
	DDX_Control(pDX, IDC_BUTTON_IMAGE_UPLOAD, m_btnImageUpload);
	DDX_Control(pDX, IDC_EDIT_COMPNY_OWNER, m_edtCompanyOwner);
	DDX_Control(pDX, IDC_EDIT_COMPANY_LOCATION, m_edtCompanyLocation);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
	DDX_Control(pDX, IDCANCEL, m_btnCanel);
	DDX_Control(pDX, IDC_EDIT_COMPNY_TEL, m_edtCompanyTel);
	DDX_Control(pDX, IDC_BRANCH_LIST, m_lstBranch);
	DDX_Control(pDX, IDC_SEARCH_EDT, m_edtSearch);

	DDX_Control(pDX, IDC_EDIT_COMPNY_BIZ_NAME, m_edtCompanyBizName);
	DDX_Control(pDX, IDC_BUTTON_IMAGE_SHOW, m_btnImageShow);
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_STATIC3, m_stc3);
	DDX_Control(pDX, IDC_STATIC4, m_stc4);
	DDX_Control(pDX, IDC_STATIC5, m_stc5);
	DDX_Control(pDX, IDC_STATIC6, m_stc6);
	DDX_Control(pDX, IDC_STATIC7, m_stc7);
	DDX_Control(pDX, IDC_CHECK_NO_USE, m_chkNoUse);
	DDX_Control(pDX, IDC_EDIT_OWNER_SSN, m_edtOwnerSSN);
}


BEGIN_MESSAGE_MAP(CEmployMentInsuranceDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CEmployMentInsuranceDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_IMAGE_UPLOAD, &CEmployMentInsuranceDlg::OnBnClickedButtonImageUpload)
	ON_BN_CLICKED(IDC_BUTTON_IMAGE_SHOW, &CEmployMentInsuranceDlg::OnBnClickedButtonImageShow)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION_SEARCH_BTN, &CEmployMentInsuranceDlg::OnBnClickedButtonLocationSearchBtn)
	ON_BN_CLICKED(IDC_CHECK_NO_USE, &CEmployMentInsuranceDlg::OnBnClickedCheckNoUse)
	ON_BN_CLICKED(IDC_APPLY_ALL_BTN, &CEmployMentInsuranceDlg::OnBnClickedApplyAllBtn)
	ON_NOTIFY(NM_CLICK, IDC_BRANCH_LIST, OnReportItemClick)
	ON_EN_CHANGE(IDC_SEARCH_EDT, &CEmployMentInsuranceDlg::OnEnChangeSearchEdt)
END_MESSAGE_MAP()


void CEmployMentInsuranceDlg::OnReportItemClick(NMHDR* pNotifyStruct, LRESULT* /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*)pNotifyStruct;
	if (!pItemNotify->pRow || !pItemNotify->pColumn) {
		return;
	}

	int col = pItemNotify->pColumn->GetIndex();

	if ( col == 0 && pItemNotify->pt.x >= 14) {
		CXTPListCtrlLogiRecord* record = (CXTPListCtrlLogiRecord*)pItemNotify->pRow->GetRecord();		
		record->SetChecked(0, !record->GetChecked(0));
	}
}

// CEmployMentInsuranceDlg 메시지 처리기입니다.


void CEmployMentInsuranceDlg::OnBnClickedButtonSave()
{
	if (Save(company_code_)) {
		MessageBox("수정되었습니다", "확인", MB_ICONINFORMATION);
		OnOK();
	}
}

BOOL CEmployMentInsuranceDlg::CheckSave(bool msg_box)
{
	CString strBizNo, strOwner, strTel, strLocation, strImage, strBizName, strOwnerSSN;
	int not_use_emp_ins_biz_no = 0;
	return CheckSave(strBizNo, strOwner, strTel, strLocation, strImage, strBizName, strOwnerSSN, not_use_emp_ins_biz_no, msg_box);
}

BOOL CEmployMentInsuranceDlg::CheckSave(CString &strBizNo, CString &strOwner, CString &strTel, CString &strLocation, CString &strImage, CString &strBizName, CString &strOwnerSSN, int &not_use_emp_ins_biz_no, bool msg_box)
{

	if (m_chkNoUse.GetCheck()) {
		not_use_emp_ins_biz_no = 1;
	}
	else {
		strBizNo = LF->GetStringFromEdit(&m_edtCompanyBizNo);
		strOwner = LF->GetStringFromEdit(&m_edtCompanyOwner);
		strTel = LF->GetStringFromEdit(&m_edtCompanyTel);
		strLocation = m_strBizAddress;
		strBizName = LF->GetStringFromEdit(&m_edtCompanyBizName);
		strOwnerSSN = LF->GetStringFromEdit(&m_edtOwnerSSN);
		strImage = m_strBizNoImage;
	}

	strBizNo.Replace("-", "");
	strTel.Replace("-", "");
	strOwnerSSN.Replace("-", "");

	if (not_use_emp_ins_biz_no == 0) {
		if (strBizNo.IsEmpty() ||
			strOwner.IsEmpty() ||
			strTel.IsEmpty() ||
			strBizName.IsEmpty() ||
			strLocation.IsEmpty() ||
			strOwnerSSN.IsEmpty() ||
			m_strZipNo.IsEmpty()) {
				if(msg_box)
					MessageBox("항목을 빠집없이 입력하세요", "확인", MB_ICONINFORMATION);
				return FALSE;
		}

		if (strImage.IsEmpty()) {
			if(msg_box)
				MessageBox("사업자등록증 혹은 신분증을 업로드하세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if (strBizNo.GetLength() != 10 && strBizNo.GetLength() != 13) {
			if(msg_box)
				MessageBox("주민번호는 13자리 사업자번호는 10자리로 입력해 주세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}

		if (strOwnerSSN.GetLength() != 13) {
			if(msg_box)
				MessageBox("대표자 주민번호는 13자리 사업자번호는 10자리로 입력해 주세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}		

		if (!LF->IsHangul(strOwner) && !LF->IsEnglish(strOwner)){
			if(msg_box)
				MessageBox("대표자는 한글 혹은 영문으로만 입력해 주세요", "확인", MB_ICONINFORMATION);
			return FALSE;
		}		
	}	

	return TRUE;
}

BOOL CEmployMentInsuranceDlg::Save(int company_code)
{
	CString strBizNo, strOwner, strTel, strLocation, strImage, strBizName, strOwnerSSN;
	int not_use_emp_ins_biz_no = 0;

	if (!CheckSave(strBizNo, strOwner, strTel, strLocation, strImage, strBizName, strOwnerSSN, not_use_emp_ins_biz_no))
		return FALSE;

	CMkCommand cmd(m_pMkDb, "insert_company_info_empins_biz_no_2");
	cmd.AddParameter(company_code);
	cmd.AddParameter(not_use_emp_ins_biz_no);
	cmd.AddParameter(strBizNo);
	cmd.AddParameter(strBizName);
	cmd.AddParameter(strOwner);
	cmd.AddParameter(strLocation);
	cmd.AddParameter(strTel);
	cmd.AddParameter(strImage);
	cmd.AddParameter(m_strZipNo);
	cmd.AddParameter(strOwnerSSN);
	cmd.AddParameter(m_ui.nCompany);
	cmd.AddParameter(m_ui.nWNo);
	cmd.AddParameter(m_ui.strName);	

	return cmd.Execute();
}

BOOL CEmployMentInsuranceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_stc1.SetTextFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD)); m_stc1.SetAlign(DT_LEFT); m_stc1.SetTextColor(RGB(0, 0, 255));
	m_stc2.SetTextFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD)); m_stc2.SetAlign(DT_LEFT); m_stc1.SetTextColor(RGB(0, 0, 255));
	m_stc3.SetTextFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD)); m_stc3.SetAlign(DT_LEFT); m_stc1.SetTextColor(RGB(0, 0, 255));
	m_stc4.SetTextFont(m_FontManager.GetFont("맑은 고딕", 18, FW_BOLD)); m_stc4.SetAlign(DT_LEFT); m_stc4.SetTextColor(RGB(0, 0, 0));
	m_stc5.SetTextFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD)); m_stc5.SetAlign(DT_LEFT); m_stc5.SetTextColor(RGB(0, 0, 0));
	m_stc6.SetTextFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD)); m_stc6.SetAlign(DT_LEFT); m_stc5.SetTextColor(RGB(255, 0, 0));
	m_stc7.SetTextFont(m_FontManager.GetFont("맑은 고딕", 16, FW_BOLD)); m_stc7.SetAlign(DT_LEFT); m_stc5.SetTextColor(RGB(255, 0, 0));

	CRect rc;
	GetWindowRect(&rc);

	if (m_ci.GetRcpIntMode1()) {
		GetDlgItem(IDC_SEARCH_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SEARCH_EDT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BRANCH_LIST)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_APPLY_ALL_BTN)->ShowWindow(SW_SHOW);
		MoveWindow(rc.left, rc.top, 738, rc.Height());
		MakeBranchList();
	}
	else {
		GetDlgItem(IDC_SEARCH_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SEARCH_EDT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BRANCH_LIST)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_APPLY_ALL_BTN)->ShowWindow(SW_HIDE);
		MoveWindow(rc.left, rc.top, 481, rc.Height());
	}


	SetWindowText("선택지사 : " + m_ci.GetBranchName(company_code_));

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_company_info_empins_biz_no_3");
	cmd.AddParameter(company_code_);
	CMkParameter *parameter = cmd.AddParameter(typeLong, typeOutput, sizeof(long), 0);

	if (rs.Execute(&cmd)) {
		CString strBizNo, strBizName, strBizOwner, strTel;
		CString strOwnerSSN;
		int able_save; parameter->GetValue(able_save);;
		int not_use_emp_ins_biz_no;

		rs.GetFieldValue("sBizNo", strBizNo);
		rs.GetFieldValue("sBizName", strBizName);
		rs.GetFieldValue("sBizOwner", strBizOwner);
		rs.GetFieldValue("sBizAddress", m_strBizAddress);
		rs.GetFieldValue("sTel", strTel);
		rs.GetFieldValue("sImageUrl", m_strBizNoImage);
		rs.GetFieldValue("not_use_emp_ins_biz_no", not_use_emp_ins_biz_no);
		rs.GetFieldValue("zip_code", m_strZipNo);
		rs.GetFieldValue("sOwnerSSN", strOwnerSSN);						

		if (!strBizNo.IsEmpty() || not_use_emp_ins_biz_no == 1) {

			if (not_use_emp_ins_biz_no) {
				m_chkNoUse.SetCheck(TRUE);
			}
			else {
				m_edtCompanyBizNo.SetWindowText(strBizNo);
				m_edtCompanyBizName.SetWindowText(strBizName);
				m_edtCompanyOwner.SetWindowText(strBizOwner);
				m_edtCompanyTel.SetWindowText(strTel);
				m_edtOwnerSSN.SetWindowText(strOwnerSSN);
				//m_edtCompanyLocation.SetWindowText(strBizAddress);
				SetLocationText(m_strBizAddress, m_strZipNo);
			}		

			CheckControl();

			if(!CheckSave(false))
				able_save = true;

			if(!able_save && not_use_emp_ins_biz_no == 0) {
				m_btnSave.EnableWindow(FALSE);
			}
		}	
	}	



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CEmployMentInsuranceDlg::CheckControl()
{
	BOOL not_use = !m_chkNoUse.GetCheck();

	m_edtCompanyBizNo.EnableWindow(not_use);
	m_edtCompanyOwner.EnableWindow(not_use);
	m_edtCompanyTel.EnableWindow(not_use);
	m_edtCompanyBizName.EnableWindow(not_use);
	m_btnImageUpload.EnableWindow(not_use);
	m_btnImageShow.EnableWindow(not_use);
}

void CEmployMentInsuranceDlg::OnBnClickedButtonImageUpload()
{
	UploadImage(m_strBizNoImage);
}

void CEmployMentInsuranceDlg::UploadImage(CString &strResult)
{

	CWebUploadDlg dlg; 
	dlg.m_strURL = LF->GetWebUploadUrl("COMPANY_BIZ_DOCUMENT", 0);

	if(dlg.m_strURL.IsEmpty()) {
		::MessageBox(NULL, "업로드 정보를 확인 할 수 없습니다", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strTemp = "biz_" + LF->GetStringFromLong(GetTickCount()) + LF->GetStringFromLong(GetTickCount());

	dlg.m_strURL += "&system=companybizdoc/daeri";	
	dlg.m_strURL += "&fileName=" + strTemp;

	if(dlg.DoModal() == IDOK) 
	{
		strResult = "http://work.logisoft.co.kr:8000/from_open_storage?ws=daeri&file=" + dlg.m_strResult;
		MessageBox("업로드 되었습니다.\r\n\r\n저장 버튼을 눌려야 최종 저장됩니다", "확인", MB_ICONINFORMATION);
	}
}

void CEmployMentInsuranceDlg::OnBnClickedButtonImageShow()
{
	ShowImage(m_strBizNoImage);	
}

void CEmployMentInsuranceDlg::ShowImage(CString strImage)
{
	if(strImage.IsEmpty())
		MessageBox("이미지가 등록되지 않았습니다", "확인", MB_ICONINFORMATION);
	else
		ShellExecute(NULL, "open", "msedge.exe", strImage, "", SW_SHOW); 
}

void CEmployMentInsuranceDlg::OnBnClickedButtonLocationSearchBtn()
{
	SearchRegion();
}

void CEmployMentInsuranceDlg::SearchRegion()
{
	CSearchRegionHolidayDlg dlg; 
	dlg.m_bReturnLiID = TRUE;
	dlg.m_strSearch = "";

	if(dlg.DoModal() == IDOK) 
	{
		m_strBizAddress = dlg.m_strSearchResult;
		m_strZipNo = dlg.m_strZipNo;
		SetLocationText(m_strBizAddress, m_strZipNo);
	}
}

void CEmployMentInsuranceDlg::SetLocationText(CString address, CString zipno)
{
	CString temp = address + (zipno.IsEmpty() ? "" : " (우편번호:" + zipno + ")");
	m_edtCompanyLocation.SetWindowText(temp);
}

void CEmployMentInsuranceDlg::MakeBranchList()
{	
	m_lstBranch.InsertColumn(0, "선택", LVCFMT_CENTER, 40);
	m_lstBranch.InsertColumn(1, "지사", LVCFMT_LEFT, 180);
	m_lstBranch.Populate();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_company_info_empins_biz_info_update_able_branch");
	cmd.AddParameter(m_ci.m_nCompanyCode);

	int index = 0;

	if (rs.Execute(&cmd)) {
		while (!rs.IsEOF()) {
			int company_code; CString branch_name;
			rs.GetFieldValue("nID", company_code);
			rs.GetFieldValue("sBranchName", branch_name);

			CXTPGridRecord *record = m_lstBranch.InsertItemReturn(index, "", -1, -1, -1, TRUE);
			m_lstBranch.SetItemText(index, 1, branch_name);
			m_lstBranch.SetItemLong(index++, company_code);			
			//record->GetItem(0)->SetAlignment(DT_CENTER);
			rs.MoveNext();
		}

		m_lstBranch.Populate();
	}
}

void CEmployMentInsuranceDlg::OnBnClickedCheckNoUse()
{
	CheckControl();
}

void CEmployMentInsuranceDlg::OnBnClickedApplyAllBtn()
{

	if (!CheckSave())
		return;

	int count = 0;
	CXTPGridRecords* records = m_lstBranch.GetRecords();

	for (int i = 0; i < records->GetCount(); i++) {		
		if (((CXTPListCtrlLogiRecord*)records->GetAt(i))->GetChecked(0)) 
			count++;
	}

	if (count == 0) {
		MessageBox("저장 할 지사를 체크하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if (MessageBox("[" + LF->GetStringFromLong(count) + "]개의 지사에 적용 하시겠습니까?", "확인", MB_OKCANCEL) != IDOK) {
		return;
	}

	int success_count = 0;

	for (int i = 0; i < records->GetCount(); i++) {
		CXTPListCtrlLogiRecord *record = (CXTPListCtrlLogiRecord*)records->GetAt(i);

		if (record->GetChecked(0))
			success_count += Save(m_lstBranch.GetItemLong(record)) ? 1 : 0;
	}

	if (success_count > 0) {
		MessageBox("성공적으로 [" + LF->GetStringFromLong(count) + "]개의 지사에 적용되었습니다.", "확인", MB_ICONINFORMATION);
		OnOK();
	}	
}


void CEmployMentInsuranceDlg::OnEnChangeSearchEdt()
{
	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstBranch.GetRecords();

	if(pRecords == NULL) return;
	if(pRecords->GetCount() == 0) return;

	for(int i = 0; i < pRecords->GetCount(); i++)
	{		
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strItem1 = m_lstBranch.GetItemText(pRecord, 1);

		if(strItem1.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else
			pRecord->SetVisible(FALSE);
	}

	m_lstBranch.Populate();
}
