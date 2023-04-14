// SmsNewBulkTestDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsNewBulkTestDlg.h"
#include "EmoticonDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmsNewBulkTestDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsNewBulkTestDlg, CMyDialog)

CSmsNewBulkTestDlg::CSmsNewBulkTestDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmsNewBulkTestDlg::IDD, pParent)
{
	m_pEmoticonDlg = NULL;
	m_nSelectedID = -1;
}

CSmsNewBulkTestDlg::~CSmsNewBulkTestDlg()
{
}

void CSmsNewBulkTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_dtpFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_dtpTo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dtFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dtTo);
	DDX_Control(pDX, IDC_DATE_BTN, m_btnData);	

	DDX_Control(pDX, IDC_MENT_EDIT1, m_edtMent1);
	DDX_Control(pDX, IDC_MENT_EDIT2, m_edtMent2);
	DDX_Control(pDX, IDC_MENT_EDIT3, m_edtMent3);
	DDX_Control(pDX, IDC_PHONE_EDIT1, m_edtPhone1);
	DDX_Control(pDX, IDC_PHONE_EDIT2, m_edtPhone2);
	DDX_Control(pDX, IDC_PHONE_EDIT3, m_edtPhone3);
	DDX_Control(pDX, IDC_BACK_PHONE_EDIT1, m_edtBackPhone1);
	DDX_Control(pDX, IDC_BACK_PHONE_EDIT2, m_edtBackPhone2);
	DDX_Control(pDX, IDC_BACK_PHONE_EDIT3, m_edtBackPhone3);

	DDX_Control(pDX, IDC_SMS_REPORT, m_lstReport);

	DDX_Control(pDX, IDC_SKT_CHECK, m_chkSK);
	DDX_Control(pDX, IDC_KT_CHECK, m_chkKT);
	DDX_Control(pDX, IDC_LGU_CHECK, m_chkLGU);
	DDX_Control(pDX, IDC_SEARCH_EDIT, m_edtSearch);

	DDX_Control(pDX, IDC_BYTE_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_BYTE_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_BYTE_STATIC3, m_stc3);
}


BEGIN_MESSAGE_MAP(CSmsNewBulkTestDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_LIST_BTN, &CSmsNewBulkTestDlg::OnBnClickedRefreshListBtn)
	ON_BN_CLICKED(IDC_SEND_BTN1, &CSmsNewBulkTestDlg::OnBnClickedSendBtn1)
	ON_BN_CLICKED(IDC_SEND_BTN2, &CSmsNewBulkTestDlg::OnBnClickedSendBtn2)
	ON_EN_CHANGE(IDC_PHONE_EDIT1, &CSmsNewBulkTestDlg::OnEnChangePhoneEdit1)
	ON_EN_CHANGE(IDC_PHONE_EDIT2, &CSmsNewBulkTestDlg::OnEnChangePhoneEdit2)
	ON_BN_CLICKED(IDC_SEND_BTN3, &CSmsNewBulkTestDlg::OnBnClickedSendBtn3)
	ON_EN_CHANGE(IDC_MENT_EDIT6, &CSmsNewBulkTestDlg::OnEnChangeMentEdit6)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_SMS_OK, OnSmsOk)
	ON_COMMAND(ID_SMS_NOT_OK, OnSmsNotOk)
	ON_COMMAND(ID_TEXT_TO_1, OnTextTo1)
	ON_COMMAND(ID_TEXT_TO_2, OnTextTo2)
	ON_COMMAND(ID_TEXT_TO_3, OnTextTo3)
	ON_BN_CLICKED(IDC_EMOTICON_BTN1, &CSmsNewBulkTestDlg::OnBnClickedEmoticonBtn1)
	ON_MESSAGE(WM_SEND_EMOTICON, OnSendEmoticon)
	ON_BN_CLICKED(IDC_EMOTICON_BTN2, &CSmsNewBulkTestDlg::OnBnClickedEmoticonBtn2)
	ON_BN_CLICKED(IDC_EMOTICON_BTN3, &CSmsNewBulkTestDlg::OnBnClickedEmoticonBtn3)
	ON_EN_CHANGE(IDC_SEARCH_EDIT, &CSmsNewBulkTestDlg::OnEnChangeSearchEdit)
	ON_BN_CLICKED(IDC_SKT_CHECK, &CSmsNewBulkTestDlg::OnBnClickedSktCheck)
	ON_BN_CLICKED(IDC_KT_CHECK, &CSmsNewBulkTestDlg::OnBnClickedKtCheck)
	ON_BN_CLICKED(IDC_LGU_CHECK, &CSmsNewBulkTestDlg::OnBnClickedLguCheck)
	ON_EN_CHANGE(IDC_MENT_EDIT1, &CSmsNewBulkTestDlg::OnEnChangeMentEdit1)
	ON_EN_CHANGE(IDC_MENT_EDIT2, &CSmsNewBulkTestDlg::OnEnChangeMentEdit2)
	ON_EN_CHANGE(IDC_MENT_EDIT3, &CSmsNewBulkTestDlg::OnEnChangeMentEdit3)
END_MESSAGE_MAP()

void CSmsNewBulkTestDlg::OnBnClickedRefreshListBtn()
{
	RefreshList();
}

BOOL CSmsNewBulkTestDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CString strPhone1, strPhone2, strPhone3;

	strPhone1 = AfxGetApp()->GetProfileString("CSmsNewBulkTestDlg", "strPhone1", "");
	strPhone2 = AfxGetApp()->GetProfileString("CSmsNewBulkTestDlg", "strPhone2", "");
	strPhone3 = AfxGetApp()->GetProfileString("CSmsNewBulkTestDlg", "strPhone3", "");

	m_edtPhone1.SetWindowText(strPhone1);
	m_edtPhone2.SetWindowText(strPhone2);
	m_edtPhone3.SetWindowText(strPhone3);

	m_edtBackPhone1.SetWindowText(m_ci.m_strPhone);
	m_edtBackPhone2.SetWindowText(m_ci.m_strPhone);
	m_edtBackPhone3.SetWindowText(m_ci.m_strPhone);

	m_edtMent1.SetFont(m_FontManager.GetFont("맑은 고딕", 20));
	m_edtMent2.SetFont(m_FontManager.GetFont("맑은 고딕", 20));
	m_edtMent3.SetFont(m_FontManager.GetFont("맑은 고딕", 20));

	m_btnData.InitDateButton(&m_dtpFrom, &m_dtpTo);
	m_btnData.OnMenuMonthIncludeToday();

	m_lstReport.InsertColumn(0, "날짜", LVCFMT_LEFT, 110);
	m_lstReport.InsertColumn(1, "전화번호", LVCFMT_LEFT, 110);
	m_lstReport.InsertColumn(2, "통신사", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(3, "메시지", LVCFMT_LEFT, 150);
	m_lstReport.InsertColumn(4, "통신사상태", LVCFMT_CENTER, 65);
	m_lstReport.InsertColumn(5, "실제전송", LVCFMT_CENTER, 60);
	m_lstReport.InsertColumn(6, "통신사실패", LVCFMT_LEFT, 110);
	m_lstReport.Populate();

	m_chkSK.SetCheck(TRUE);
	m_chkKT.SetCheck(TRUE);
	m_chkLGU.SetCheck(TRUE);

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSmsNewBulkTestDlg::RefreshList()
{
	UpdateData(TRUE);

	m_lstReport.DeleteAllItems();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_sms_bulk_test");

	cmd.AddParameter(m_ci.m_nCompanyCode);
	cmd.AddParameter(m_dtFrom);
	cmd.AddParameter(m_dtTo);

	if(!rs.Execute(&cmd))
		return;

	long nID;
	COleDateTime dtGenerate;
	CString strPhone, strMsg, strNet, strNetResult, strUserResult, strNetFail;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("dtGenerate", dtGenerate);
		rs.GetFieldValue("sPhone", strPhone);
		rs.GetFieldValue("sMsg", strMsg);
		rs.GetFieldValue("sNet", strNet);
		rs.GetFieldValue("sNetResult", strNetResult);
		rs.GetFieldValue("sUserResult", strUserResult);
		rs.GetFieldValue("sNetFail", strNetFail);

		m_lstReport.InsertItem(i, dtGenerate.Format("%Y-%m-%d %H:%M"));
		m_lstReport.SetItemText(i, 1, ::GetDashPhoneNumber(strPhone));
		m_lstReport.SetItemText(i, 2, strNet);
		m_lstReport.SetItemText(i, 3, strMsg);
		m_lstReport.SetItemText(i, 4, strNetResult);
		m_lstReport.SetItemText(i, 5, strUserResult);
		m_lstReport.SetItemText(i, 6, strNetFail);
		m_lstReport.SetItemLong(i, nID);

		rs.MoveNext();		
	} 

	m_lstReport.Populate();
}

void CSmsNewBulkTestDlg::OnBnClickedSendBtn1()
{
	CString strPhone, strMsg, strBackPhone;
	m_edtMent1.GetWindowText(strMsg);
	m_edtPhone1.GetWindowText(strPhone);
	m_edtBackPhone1.GetWindowText(strBackPhone);
	SendTestSms(strPhone, strMsg, strBackPhone);
}

void CSmsNewBulkTestDlg::OnBnClickedSendBtn2()
{
	CString strPhone, strMsg, strBackPhone;
	m_edtMent2.GetWindowText(strMsg);
	m_edtPhone2.GetWindowText(strPhone);
	m_edtBackPhone2.GetWindowText(strBackPhone);
	SendTestSms(strPhone, strMsg, strBackPhone);
}

void CSmsNewBulkTestDlg::SendTestSms(CString strPhone, CString strMent, CString strBackPhone)
{
	if(!::IsMobilePhoneNumber(strPhone))
	{
		MessageBox("휴대폰번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	} 

	if(strBackPhone.GetLength() < 7)
	{
		MessageBox("콜백번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(strMent.GetLength() < 2)
	{
		MessageBox("전송하실 메시지를 입력하세요.", "확인", MB_ICONINFORMATION);
		return;
	}

	if(::SendSmsBulkTest(m_ci.m_nCompanyCode, SMS_TYPE_TEST, strPhone, strBackPhone, strMent, "테스트"))
	{
		RefreshList();
		MessageBox("전송되었습니다.\r\n리스트에서 우클릭후 실제 전송내역의 상태값을 변경하세요.", "확인", MB_ICONINFORMATION);
	}

}

void CSmsNewBulkTestDlg::OnEnChangePhoneEdit1()
{
	CString strPhone;
	m_edtPhone1.GetWindowText(strPhone);
	AfxGetApp()->WriteProfileString("CSmsNewBulkTestDlg", "strPhone1", strPhone);
}

void CSmsNewBulkTestDlg::OnEnChangePhoneEdit2()
{
	CString strPhone;
	m_edtPhone2.GetWindowText(strPhone);
	AfxGetApp()->WriteProfileString("CSmsNewBulkTestDlg", "strPhone2", strPhone);
}

void CSmsNewBulkTestDlg::OnBnClickedSendBtn3()
{
	CString strPhone, strMsg, strBackPhone;
	m_edtMent3.GetWindowText(strMsg);
	m_edtPhone3.GetWindowText(strPhone);
	m_edtBackPhone3.GetWindowText(strBackPhone);
	SendTestSms(strPhone, strMsg, strBackPhone);
}

void CSmsNewBulkTestDlg::OnEnChangeMentEdit6()
{
	CString strPhone;
	m_edtPhone3.GetWindowText(strPhone);
	AfxGetApp()->WriteProfileString("CSmsNewBulkTestDlg", "strPhone3", strPhone);
}

void CSmsNewBulkTestDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;
	m_lstReport.GetWindowRect(&rect);
	if(!rect.PtInRect(point)) return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu=rMenu.GetSubMenu(35);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}

void CSmsNewBulkTestDlg::OnSmsOk()
{
	ChangeUserState(TRUE);
}

void CSmsNewBulkTestDlg::OnSmsNotOk()
{
	ChangeUserState(FALSE);
}

void CSmsNewBulkTestDlg::ChangeUserState(BOOL bOK)
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CString strTemp;

	if(bOK)
		strTemp = "폰으로 SMS를 받으셨습니까?";
	else
		strTemp = "폰으로 SMS를 받지 못하셨습니까?";

	if(MessageBox(strTemp, "확인", MB_OKCANCEL) != IDOK)
		return;

	long nID = m_lstReport.GetItemLong(pRecord);

	CMkCommand cmd(m_pMkDb, "update_sms_test_user_state");
	cmd.AddParameter(nID);
	cmd.AddParameter(bOK);

	if(cmd.Execute())
		((CXTPGridRecordItemText*)pRecord->GetItem(5))->SetCaption(bOK ? "성공" : "실패");

	m_lstReport.Populate();
}

void CSmsNewBulkTestDlg::OnBnClickedEmoticonBtn1()
{
	OpenEmoticonDlg(IDC_MENT_EDIT1);
}

void CSmsNewBulkTestDlg::OpenEmoticonDlg(long nUID)
{
	if(m_pEmoticonDlg == NULL)
	{
		m_pEmoticonDlg = new CEmoticonDlg(this);
		m_pEmoticonDlg->Create(CEmoticonDlg::IDD, this);
	}

	m_nSelectedID = nUID;

	CRect rcThis, rcEmoticon;

	CWnd *pWnd = GetDlgItem(m_nSelectedID);
	pWnd->GetWindowRect(rcThis);
	m_pEmoticonDlg->GetWindowRect(rcEmoticon);

	long nWidth = rcEmoticon.Width();
	long nHeight = rcEmoticon.Height();

	rcEmoticon.top = rcThis.top;
	rcEmoticon.bottom = rcThis.top + nHeight; 
	rcEmoticon.left = rcThis.right + 1;
	rcEmoticon.right = rcEmoticon.left + nWidth;

	m_pEmoticonDlg->MoveWindow(rcEmoticon);
	m_pEmoticonDlg->ShowWindow(SW_SHOW);
}

LONG CSmsNewBulkTestDlg::OnSendEmoticon(WPARAM wParam, LPARAM lParam)
{
	char const *strValue = reinterpret_cast<char const *>(wParam);

	CEdit *pEdit = (CEdit*)GetDlgItem(m_nSelectedID);

	::AddTextMiddle(strValue, pEdit);

	if(m_nSelectedID == IDC_MENT_EDIT1)
		OnEnChangeMentEdit1(); 
	else if(m_nSelectedID == IDC_MENT_EDIT2)
		OnEnChangeMentEdit2(); 
	else if(m_nSelectedID == IDC_MENT_EDIT3)
		OnEnChangeMentEdit3(); 

	delete strValue;

	return 0;
}

void CSmsNewBulkTestDlg::OnBnClickedEmoticonBtn2()
{
	OpenEmoticonDlg(IDC_MENT_EDIT2);
}

void CSmsNewBulkTestDlg::OnBnClickedEmoticonBtn3()
{
	OpenEmoticonDlg(IDC_MENT_EDIT3);
}

void CSmsNewBulkTestDlg::OnTextTo1()
{
	SendTextToEdit(IDC_MENT_EDIT1);
	DisplayByte(IDC_MENT_EDIT1, IDC_BYTE_STATIC1);
}

void CSmsNewBulkTestDlg::OnTextTo2()
{
	SendTextToEdit(IDC_MENT_EDIT2);
	DisplayByte(IDC_MENT_EDIT2, IDC_BYTE_STATIC2);
}

void CSmsNewBulkTestDlg::OnTextTo3()
{
	SendTextToEdit(IDC_MENT_EDIT3);
	DisplayByte(IDC_MENT_EDIT3, IDC_BYTE_STATIC3);
}

void CSmsNewBulkTestDlg::SendTextToEdit(long nUID)
{
	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CString strText = pRecord->GetItem(3)->GetCaption(NULL);

	CEdit *pEdit = (CEdit*)GetDlgItem(nUID);
	pEdit->SetWindowText(strText);
}

void CSmsNewBulkTestDlg::SearchList()
{
	BOOL bSK = m_chkSK.GetCheck();
	BOOL bKT = m_chkKT.GetCheck();
	BOOL bLGU = m_chkLGU.GetCheck();
	BOOL bAll = bSK && bKT && bLGU;

	CString strSearch; m_edtSearch.GetWindowText(strSearch);

	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strPhone = pRecord->GetItem(1)->GetCaption(NULL);
		CString strMsg = pRecord->GetItem(3)->GetCaption(NULL);
		CString strNet = pRecord->GetItem(2)->GetCaption(NULL);

		if(!bAll)
		{
			BOOL bVisible = FALSE;

			if(bSK == TRUE && strNet == "SK")
				bVisible = TRUE;
			if(bKT == TRUE && strNet == "KT")
				bVisible = TRUE;
			if(bLGU == TRUE && strNet == "LGU+")
				bVisible = TRUE;

			if(bVisible == FALSE)
			{
				pRecord->SetVisible(FALSE);
				continue;
			}			
		}

		if(strPhone.Find(strSearch) >= 0 ||
			strMsg.Find(strSearch) >= 0)
			pRecord->SetVisible(TRUE);
		else 
			pRecord->SetVisible(FALSE);
	}

	m_lstReport.Populate();
}

void CSmsNewBulkTestDlg::OnEnChangeSearchEdit()
{
	SearchList();
}

void CSmsNewBulkTestDlg::OnBnClickedSktCheck()
{
	SearchList();
}

void CSmsNewBulkTestDlg::OnBnClickedKtCheck()
{
	SearchList();
}

void CSmsNewBulkTestDlg::OnBnClickedLguCheck()
{
	SearchList();
}

void CSmsNewBulkTestDlg::OnEnChangeMentEdit1()
{
	DisplayByte(IDC_MENT_EDIT1, IDC_BYTE_STATIC1);
}

void CSmsNewBulkTestDlg::OnEnChangeMentEdit2()
{
	DisplayByte(IDC_MENT_EDIT2, IDC_BYTE_STATIC2);
}

void CSmsNewBulkTestDlg::OnEnChangeMentEdit3()
{
	DisplayByte(IDC_MENT_EDIT3, IDC_BYTE_STATIC3);
}

void CSmsNewBulkTestDlg::DisplayByte(UINT nEdit, UINT nStatic)
{
	CEdit *pEdit = (CEdit*)GetDlgItem(nEdit);
	CStatic *pStatic = (CStatic*)GetDlgItem(nStatic);

	CString strMent; pEdit->GetWindowText(strMent);
	strMent.Replace("\r\n", " ");  //줄바꿈을 2바이트로 인식, 계산하기위함
	long nLength = strMent.GetLength();

	CString strTemp = ""; strTemp.Format("Byte : %d", nLength);
	pStatic->SetWindowText(strTemp);
	pEdit->SetFocus();
}  