// SmsDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsBaseDlg.h"
#include "SmsMentInsertDlg.h"
#include "AddMmsImageDlg.h"
#include "ReportMultilinePaintManager.h"
#include "EmoticonDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmsBaseDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsBaseDlg, CMyDialog)

CSmsBaseDlg::CSmsBaseDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmsBaseDlg::IDD, pParent)
{
	m_nMMSImageCount = 0;
	m_nSendCount = 0;

	m_nMentID[0] = 0;
	m_nMentID[1] = 0;
	m_nMentID[2] = 0;
	m_nMentID[3] = 0;

	m_pEmoticonDlg = NULL; 
	m_strTitle = "";

	m_nSmsType = 0;

	m_pMsgWnd = NULL;

	m_bPreSmsMode = -1;
	m_bSmsMode = TRUE;
	m_nMentEditTop = 0;
}

CSmsBaseDlg::CSmsBaseDlg(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
: CMyDialog(nIDTemplate, pParent)
{	
	m_nMMSImageCount = 0;
}

CSmsBaseDlg::~CSmsBaseDlg()
{
	DELETE_OBJECT(m_pEmoticonDlg);
	DeleteTempFile();
}

void CSmsBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MAIN_EDIT, m_edtMain);
	DDX_Control(pDX, IDC_SUB_EDIT, m_edtSub);
	DDX_Control(pDX, IDC_MAIN_BUTTON, m_btnMain);
	DDX_Control(pDX, IDC_SUB_BUTTON, m_btnSub);
	DDX_Control(pDX, IDC_SEARCH_BRANCH_EDT, m_edtSearchBranch);

	DDX_Control(pDX, IDC_MENT_EDIT, m_edtMent);

	DDX_Control(pDX, IDC_BYTE_STATIC, m_stcByte);

	DDX_Control(pDX, IDC_SMS_MMS_BTN, m_btnSmsMms);

	DDX_Control(pDX, IDC_ADD_FILE_BTN, m_btnAddFile);

	DDX_Control(pDX, IDC_CALL_BACK_COMBO, m_cmbCallBack);
	DDX_Control(pDX, IDC_RECEIVE_NUMBER_EDIT, m_edtReceiveNumber);


	DDX_Control(pDX, IDC_CUR_CHARGE_EDIT, m_edtCurCharge);
	DDX_Control(pDX, IDC_CUR_ABIL_COUNT_EDIT, m_edtCurAbilCount);
	DDX_Control(pDX, IDC_CHARGE_PER_ONE_EDIT, m_edtChargePerOne);
	DDX_Control(pDX, IDC_SEND_COUNT_EDIT, m_edtSendCount);
	DDX_Control(pDX, IDC_SEND_CHARGE_EDIT, m_edtSendCharge);

	DDX_Control(pDX, IDC_MENT_EDIT1, m_edtSaveMent[0]);
	DDX_Control(pDX, IDC_MENT_EDIT2, m_edtSaveMent[1]);
	DDX_Control(pDX, IDC_MENT_EDIT3, m_edtSaveMent[2]);
	DDX_Control(pDX, IDC_MENT_EDIT4, m_edtSaveMent[3]);

	DDX_Control(pDX, IDC_EMOTICON_BTN1, m_btnEmoticon[0]);
	DDX_Control(pDX, IDC_EMOTICON_BTN2, m_btnEmoticon[1]);
	DDX_Control(pDX, IDC_EMOTICON_BTN3, m_btnEmoticon[2]);
	DDX_Control(pDX, IDC_EMOTICON_BTN4, m_btnEmoticon[3]);

	DDX_Control(pDX, IDC_SEND_BTN, m_btnSend);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_btnClose);
	DDX_Control(pDX, IDC_TITLE_STATIC, m_stcTitle);

	DDX_Control(pDX, IDC_LONG_PIC, m_picLong);
	DDX_Control(pDX, IDC_SHORT_PIC, m_picShort);

	DDX_Control(pDX, IDC_MMS_TITLE_EDIT, m_edtMMSTitle);

	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_STATIC2, m_stc2);
	DDX_Control(pDX, IDC_STATIC3, m_stc3);
	DDX_Control(pDX, IDC_STATIC4, m_stc4);
	DDX_Control(pDX, IDC_STATIC5, m_stc5);
	DDX_Control(pDX, IDC_STATIC6, m_stc6);
	DDX_Control(pDX, IDC_STATIC7, m_stc7);
	DDX_Control(pDX, IDC_STATIC8, m_stc8);
	DDX_Control(pDX, IDC_STATIC9, m_stc9);
	DDX_Control(pDX, IDC_STATIC10, m_stc10);
	DDX_Control(pDX, IDC_STATIC11, m_stc11);
	DDX_Control(pDX, IDC_STATIC12, m_stc12);
	DDX_Control(pDX, IDC_STATIC13, m_stc13);
	DDX_Control(pDX, IDC_STATIC14, m_stc14);
	DDX_Control(pDX, IDC_STATIC15, m_stc15);

	DDX_Control(pDX, IDC_MENT_LIST, m_lstMent);
}

void CSmsBaseDlg::DeleteTempFile()
{
	for(int i=0; i<(long)m_strDeleteFileArry.GetSize(); i++)
	{
		CString strTemp = m_strDeleteFileArry.GetAt(i);
		DeleteFile(strTemp);
	}

	m_strDeleteFileArry.RemoveAll();
}

BEGIN_MESSAGE_MAP(CSmsBaseDlg, CMyDialog)
	ON_EN_CHANGE(IDC_MENT_EDIT, OnEnChangeMentEdit)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, OnBnClickedSaveButton)
	ON_NOTIFY(NM_CLICK, IDC_MENT_LIST, OnReportItemClick)
	ON_NOTIFY(NM_RCLICK, IDC_MENT_LIST, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, IDC_MENT_LIST, OnReportItemDblClick)
	ON_BN_CLICKED(IDC_ADD_FILE_BTN, OnBnClickedAddFileBtn)

	ON_BN_CLICKED(IDC_ADD_SMS_BALANCE_BTN, OnBnClickedAddSmsBalance)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnBnClickedCloseBtn)
	ON_MESSAGE(WM_SEND_EMOTICON, OnSendEmoticon)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_SELECT_BTN1, IDC_SELECT_BTN4, OnClickedItemSelect)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_UPDATE_BTN1, IDC_UPDATE_BTN4, OnClickedItemUpdate)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_EMOTICON_BTN1, IDC_EMOTICON_BTN4, OnClickedItemEmoticon)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()

	
	//ON_COMMAND(ID_INSERT, OnInsert)
	//ON_COMMAND(ID_UPDATE, OnUpdate)
	ON_COMMAND(ID_DELETE, OnDelete)

END_MESSAGE_MAP()

void CSmsBaseDlg::OnClickedItemSelect(UINT nID) 
{ 
	long nIndex = nID - IDC_SELECT_BTN1;
	CString strMent; m_edtSaveMent[nIndex].GetWindowText(strMent);
	SetMentWindowText(strMent); 
	DisplayByte();
}

void CSmsBaseDlg::OnClickedItemUpdate(UINT nID)
{
	long nIndex = nID - IDC_UPDATE_BTN1;
	CString strMent; m_edtSaveMent[nIndex].GetWindowText(strMent); 

	if(m_nMentID[nIndex] == 0)
	{
		if(::InsertSaveMent(m_ci.m_nCompanyCode, SMS_TYPE_BULK, strMent))
			MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
	}
	else
	{
		if(::UpdateSaveMent(m_nMentID[nIndex], strMent))
			MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
	}
}

void CSmsBaseDlg::OpenEmotionDlg(long nID, CWnd *pWndMain)
{
	if(m_pEmoticonDlg == NULL)
	{
		m_pEmoticonDlg = new CEmoticonDlg(this);
		m_pEmoticonDlg->Create(CEmoticonDlg::IDD, this);
	}

	m_nLastSelectIndex = nID;

	CRect rcThis, rcEmoticon;

	pWndMain->GetWindowRect(rcThis);
	m_pEmoticonDlg->GetWindowRect(rcEmoticon);

	long nWidth = rcEmoticon.Width();
	long nHeight = rcEmoticon.Height();

	rcEmoticon.bottom = rcThis.bottom; 
	rcEmoticon.top = rcThis.bottom - nHeight;
	rcEmoticon.left = rcThis.right + 1;
	rcEmoticon.right = rcEmoticon.left + nWidth;

	m_pEmoticonDlg->MoveWindow(rcEmoticon);
	m_pEmoticonDlg->ShowWindow(SW_SHOW);
}

void CSmsBaseDlg::OnClickedItemEmoticon(UINT nID)
{
	if(nID == IDC_EMOTICON_BTN1) 	OpenEmotionDlg(IDC_MENT_EDIT1, &m_btnEmoticon[0]);
	else if(nID == IDC_EMOTICON_BTN2) 	OpenEmotionDlg(IDC_MENT_EDIT2, &m_btnEmoticon[1]);
	else if(nID == IDC_EMOTICON_BTN3)	OpenEmotionDlg(IDC_MENT_EDIT3, &m_btnEmoticon[2]);
	else if(nID == IDC_EMOTICON_BTN4)	OpenEmotionDlg(IDC_MENT_EDIT4, &m_btnEmoticon[3]);
}

void CSmsBaseDlg::DisplayByte()
{
	CString strMent;
	m_edtMent.GetWindowText(strMent);

	strMent.Replace("\r\n", " ");  //줄바꿈을 2바이트로 인식, 계산하기위함
	long nLength = strMent.GetLength();

	CString strTemp; strTemp.Format("Byte : %d", nLength);
	m_stcByte.SetWindowText(strTemp);

	if(m_nMMSImageCount > 0)
	{
		m_nSendType = TYPE_MMS;
		m_btnSmsMms.LoadBitmaps(IDB_SMS_MMS, IDB_SMS_MMS); 
		m_edtChargePerOne.ChangeImage(IDB_SMS_MMS1);
		m_bSmsMode = FALSE;
	}
	else if(nLength >= 90) 
	{
		m_nSendType = TYPE_LMS;
		m_btnSmsMms.LoadBitmaps(IDB_SMS_LMS, IDB_SMS_LMS);	
		m_edtChargePerOne.ChangeImage(IDB_SMS_LMS1);
		m_bSmsMode = FALSE;
	}
	else		
	{
		m_nSendType = TYPE_SMS;
		m_btnSmsMms.LoadBitmaps(IDB_SMS_SMS, IDB_SMS_SMS);
		m_edtChargePerOne.ChangeImage(IDB_SMS_SMS1);
		m_bSmsMode = TRUE;
	}

	if(m_bPreSmsMode != m_bSmsMode)
		ChangeControl();

	m_bPreSmsMode = m_bSmsMode;

	m_btnAddFile.SetWindowText("파일첨부(" + ::GetStringFromLong(m_nMMSImageCount) + ")");
	m_btnSmsMms.Invalidate();

	DisplaySmsCount();
} 

void CSmsBaseDlg::MoveControlTop(CWnd *pWnd, long nTop, BOOL bMoveBottom)
{
	CRect rc;
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);

	long nHeight = rc.Height();

	rc.top = nTop;

	if(bMoveBottom)
		rc.bottom = rc.top + nHeight;

	pWnd->MoveWindow(rc);
}

void CSmsBaseDlg::ChangeControl()
{
	CRuntimeClass *p = GetRuntimeClass();

	CString strTemp(p->m_lpszClassName);

	BOOL bBUlkSms = strTemp == "CSmsNewDlg" ? FALSE : TRUE;

	if(m_bSmsMode == TRUE)
	{		 
		m_picLong.ShowWindow(SW_HIDE);
		m_picShort.ShowWindow(SW_SHOW); 
		m_edtMMSTitle.ShowWindow(SW_HIDE); 
 
		if(bBUlkSms)  
		{
			MoveControlTop(&m_edtMent, m_nMentEditTop, FALSE);
			MoveControlTop(&m_cmbCallBack, m_nMentEditTop - 33);
		}
		else
		{
			MoveControlTop(&m_edtMent, m_nMentEditTop, FALSE);
			MoveControlTop(&m_cmbCallBack, m_nMentEditTop - 58);
			MoveControlTop(&m_edtReceiveNumber, m_nMentEditTop - 32); 
		}		
	} 
	else 
	{
		m_picLong.ShowWindow(SW_SHOW); 
		m_picShort.ShowWindow(SW_HIDE);
		m_edtMMSTitle.ShowWindow(SW_SHOW);

		CRect rcTitle;
		m_edtMMSTitle.GetWindowRect(rcTitle); ScreenToClient(rcTitle);
		
		if(bBUlkSms)
		{
			MoveControlTop(&m_cmbCallBack, rcTitle.bottom + 5);
			MoveControlTop(&m_edtMent, rcTitle.bottom + 40, FALSE);
		}
		else
		{
			MoveControlTop(&m_cmbCallBack, rcTitle.bottom + 5);
			MoveControlTop(&m_edtReceiveNumber, rcTitle.bottom + 31);
			MoveControlTop(&m_edtMent, rcTitle.bottom + 63, FALSE);
		}
	}

	Invalidate(TRUE);
}

void CSmsBaseDlg::LoadSmsBalance()
{
	ST_SMS_INFO smsi = ::GetSMSBalance(m_cBranch.GetCompany());
	m_nCurBalance = smsi.nSMSBarance;
	m_nSmsType = smsi.nSMSType;
}

CString CSmsBaseDlg::GetSmsType(long nType)
{
	if(nType == TYPE_MMS)
		return "MMS";
	else if(nType == TYPE_LMS)
		return "LMS";
	else if(nType == TYPE_SMS)
		return "SMS";

	return "";	
}

void CSmsBaseDlg::DisplaySmsCount()
{  
	if(m_nSmsType == 0) //후입금
	{
		m_edtCurCharge.SetWindowText(::GetMyNumberFormat("-"));
		m_edtCurAbilCount.SetWindowText(::GetMyNumberFormat("-"));
	}
	else
	{
		m_edtCurCharge.SetWindowText(::GetMyNumberFormat(m_nCurBalance) + "원");
		m_edtCurAbilCount.SetWindowText(::GetMyNumberFormat(m_nCurBalance / m_sms.GetSmsCharge(m_nSendType)) + "건");
	}
	
	m_edtChargePerOne.SetWindowText(::GetMyNumberFormat(m_sms.GetSmsCharge(m_nSendType)) + "원");
	m_edtSendCount.SetWindowText(::GetMyNumberFormat(m_nSendCount) + "건");
	m_edtSendCharge.SetWindowText(::GetMyNumberFormat(m_nSendCount * m_sms.GetSmsCharge(m_nSendType)) + "원");

	if(m_nSendCount * m_sms.GetSmsCharge(m_nSendType) > m_nCurBalance)
		m_edtSendCharge.ShowButton(TRUE);
	else
		m_edtSendCharge.ShowButton(FALSE);
}

void CSmsBaseDlg::OnBnClickedSaveButton()
{
	CString strMent;
	m_edtMent.GetWindowText(strMent);

	if(strMent.IsEmpty())
	{
		MessageBox("저장 하실 멘트를 입력하세요", "확인", MB_ICONINFORMATION);
		return; 
	}

	if(::InsertSaveMent(m_cBranch.GetCompany(), m_nType, strMent))
	{
		LoadSaveMent();

		if(m_nType == SMS_TYPE_ALLOCATE)
			MessageBox("저장되었습니다. 항목에 맞게 멘트를 수정해 주세요.", "확인", MB_ICONINFORMATION);
	}
}

void CSmsBaseDlg::OnBnClickedCloseBtn()
{
	OnCancel();
}

void CSmsBaseDlg::OnEnChangeMentEdit()
{
	DisplayByte();
}

void CSmsBaseDlg::LoadSaveMent()
{
	m_lstMent.DeleteAllItems();

	long nCompany = m_cBranch.GetCompany();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_sms_save_ment4");
	cmd.AddParameter(nCompany);
	cmd.AddParameter(m_nType);

	if(!rs.Execute(&cmd))
		return;

	CString strMent; long nID; BOOL bDefault;

	for(int i=0; i<rs.GetRecordCount(); i++)
	{
		rs.GetFieldValue("nID", nID);
		rs.GetFieldValue("sMent", strMent);
		rs.GetFieldValue("bDefault", bDefault);

		m_lstMent.InsertItem(i, strMent);
		m_lstMent.SetItemLong(i, nID);

		if(i<=3)
		{
			m_nMentID[i] = nID;
			m_edtSaveMent[i].SetWindowText(strMent);
		}
		
		if(i == 0)
		{
			m_edtMent.SetWindowText(strMent);
			m_edtMent.SetFocus();
		}

		rs.MoveNext();	
	}

	m_lstMent.Populate();
	DisplayByte();
}

void CSmsBaseDlg::SetMentWindowText(CString strText)
{
	if(m_nType == SMS_TYPE_ALLOCATE)
	{
		strText.Replace("[접수시간]", m_stAllocate.strDt1);
		strText.Replace("[고객명]", m_stAllocate.strName);
		strText.Replace("[출발지]", m_stAllocate.strStart);
		strText.Replace("[도착지]", m_stAllocate.strDest);
		strText.Replace("[운행요금]", m_stAllocate.strCharge);
		strText.Replace("[적요]", m_stAllocate.strEtc);
		strText.Replace("[후불]", m_stAllocate.strPayType);
		strText.Replace("[기사충전금]", m_stAllocate.strRiderAutoCharge);
		strText.Replace("[기사이름]", m_stAllocate.strRiderName);
		strText.Replace("[회사명]", m_stAllocate.strCompanyName);
	}

	m_edtMent.SetWindowText(strText);
}

// CSmsNewDlg 메시지 처리기입니다.

void CSmsBaseDlg::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	//if (!pItemNotify->pRow || !pItemNotify->pColumn)
	//	return;

	//CXTPGridRecord *pRecord = m_lstMent.GetFirstSelectRecord();

	//if(pRecord == NULL)
	//	return;

	CPoint point;
	::GetCursorPos(&point);

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU); 
	CMenu *pRMenu;
	pRMenu = rMenu.GetSubMenu(43);
	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}


void CSmsBaseDlg::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
		return;

	CXTPGridRecord *pRecord = m_lstMent.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CString strText = m_lstMent.GetItemText(pRecord, 0);

	SetMentWindowText(strText);
	DisplayByte(); 
}

void CSmsBaseDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	OnUpdate();
}

void CSmsBaseDlg::OnBnClickedAddFileBtn()
{
	MessageBox("MMS전송은 준비중입니다", "확인", MB_ICONINFORMATION);
	return;

	CAddMmsImageDlg dlg;

	dlg.m_nAddImageCount = m_nMMSImageCount;

	for(int i=0; i<m_nMMSImageCount; i++)
	{
		dlg.m_strImage[i] = m_strImage[i];
		dlg.m_nImageSize[i] = m_nImageSize[i];
	}

	if(dlg.DoModal() == IDOK)
	{
		m_nMMSImageCount = dlg.m_nAddImageCount;

		for(int i=0; i<m_nMMSImageCount; i++) 
		{
			m_strImage[i] = dlg.m_strImage[i]; 
			m_nImageSize[i] = dlg.m_nImageSize[i];
		}

		DisplayByte();

		for(int i=0;i<dlg.m_strDeleteFileArry.GetSize(); i++)
			m_strDeleteFileArry.Add(dlg.m_strDeleteFileArry.GetAt(i));

	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CSmsBaseDlg::OnDelete()
{
	CXTPGridRecord *pRecord = m_lstMent.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nID = m_lstMent.GetItemLong(pRecord);

	if(::DeleteSaveMent(nID))
	{
		LoadSaveMent();
		OnClickedItemSelect(IDC_SELECT_BTN1);
	}
}

void CSmsBaseDlg::OnInsert()
{
	CSmsMentInsertDlg dlg;
	dlg.m_nType = m_nType;

	if(dlg.DoModal() == IDOK)
	{
		if(::InsertSaveMent(m_nCompany, m_nType, dlg.m_strMent))
		{
			LoadSaveMent();
			OnClickedItemSelect(IDC_SELECT_BTN1);
		}
	} 
}

void CSmsBaseDlg::OnUpdate()
{
	CXTPGridRecord *pRecord = m_lstMent.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return; 

	CSmsMentInsertDlg dlg;
	dlg.m_nType = m_nType;
	dlg.m_strMent = m_lstMent.GetItemText(pRecord, 0);

	long nID = m_lstMent.GetItemLong(pRecord);

	if(dlg.DoModal() == IDOK)
	{
		if(::UpdateSaveMent(nID, dlg.m_strMent))
		{
			LoadSaveMent();
			OnClickedItemSelect(IDC_SELECT_BTN1);
		}
	} 
}

void CSmsBaseDlg::OnOK()
{
	if(m_pMsgWnd)
		m_pMsgWnd->SendMessage(WM_CLOSE_SMS_DLG, (WPARAM)0, (LPARAM)0);

	CMyDialog::OnOK();
}

void CSmsBaseDlg::OnCancel()
{ 
	if(m_pMsgWnd) 
		m_pMsgWnd->SendMessage(WM_CLOSE_SMS_DLG, (WPARAM)0, (LPARAM)0);

	CMyDialog::OnCancel();
}

void CSmsBaseDlg::UpLoadFile()
{

}

BOOL CSmsBaseDlg::OnInitDialog()
{ 
	CMyDialog::OnInitDialog();

	CenterWindow();

	m_cBranch.SetParent(this, TRUE);
	m_cBranch.InitData(&m_edtMain, &m_edtSub, &m_btnMain, &m_btnSub, &m_edtSearchBranch);
	
	m_lstMent.SetPaintManager(new CReportMultilinePaintManager);
	m_lstMent.GetPaintManager()->m_strNoItems = "";
	m_lstMent.ShowHeader(FALSE);
	m_lstMent.Populate();

	m_lstMent.InsertColumn(0, "저장멘트", LVCFMT_LEFT, 370);
	m_lstMent.Populate();
	
	m_stc1.SetAlign(DT_RIGHT); m_stc1.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc2.SetAlign(DT_LEFT); m_stc2.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_BOLD));
	m_stc3.SetAlign(DT_LEFT); m_stc3.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc4.SetAlign(DT_LEFT); m_stc4.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc5.SetAlign(DT_LEFT); m_stc5.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc6.SetAlign(DT_LEFT); m_stc6.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc7.SetAlign(DT_RIGHT); m_stc7.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc8.SetAlign(DT_RIGHT); m_stc8.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc9.SetAlign(DT_RIGHT); m_stc9.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc10.SetAlign(DT_RIGHT); m_stc10.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc11.SetAlign(DT_RIGHT); m_stc11.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc12.SetAlign(DT_RIGHT); m_stc12.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc13.SetAlign(DT_RIGHT); m_stc13.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc14.SetAlign(DT_RIGHT); m_stc14.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	m_stc15.SetAlign(DT_RIGHT); m_stc15.SetTextFont(m_FontManager.GetFont("굴림", 12, FW_NORMAL));
	
	m_edtCurCharge.SetFont(m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	m_edtSendCharge.SetFont(m_FontManager.GetFont("맑은 고딕", 17, FW_BOLD));
	
	m_edtSaveMent[0].SetFont(m_FontManager.GetFont("맑은 고딕", 20));
	m_edtSaveMent[1].SetFont(m_FontManager.GetFont("맑은 고딕", 20));
	m_edtSaveMent[2].SetFont(m_FontManager.GetFont("맑은 고딕", 20));
	m_edtSaveMent[3].SetFont(m_FontManager.GetFont("맑은 고딕", 20));

	m_btnSmsMms.LoadBitmaps(IDB_SMS_SMS1, IDB_SMS_SMS1); 
	m_btnSend.LoadBitmaps(IDB_SMS_SEND, IDB_SMS_SEND_UP);
	m_btnClose.LoadBitmaps(IDB_CLOSE_UP, IDB_CLOSE_DOWN);

	m_edtMMSTitle.SetUserOption(RGB(0, 0, 0), RGB(255, 255, 255), "제 목");

	m_btnSmsMms.SizeToContent();
	m_btnSend.SizeToContent();
	m_btnClose.SizeToContent();

	m_edtMent.SetFont(m_FontManager.GetFont("맑은 고딕", 20));	

	m_edtChargePerOne.MakeButton(this, IDB_SMS_SMS);
	m_edtSendCharge.MakeButton(this, IDB_SMS_ABIL, 1);
	m_edtSendCharge.ShowButton(FALSE); 
	
	/*
	m_stcTitle.SetTextColor(RGB(255, 255, 255));
	m_stcTitle.SetTextFont(m_FontManager.GetFont("굴림", 16, FW_BOLD));
	m_stcTitle.SetWindowText(m_strTitle);
	m_stcTitle.SetAlign(DT_LEFT);
	*/ 
	SetWindowText(m_strTitle);

	SaveMentEditTop();
	m_edtMent.SetFocus();
	DisplayByte(); 
	m_cmbCallBack.SetReadOnly(TRUE);

	//m_btnSmsMms1.SetParent(&m_edtSaveMent[2]);
	//m_btnSendAbil.SetParent(&m_edtSaveMent[4]);

	//DisplayByte();
	//LoadSaveMent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSmsBaseDlg::SaveMentEditTop()
{
	CRect rc;
	m_edtMent.GetWindowRect(rc);
	ScreenToClient(rc);

	m_nMentEditTop = rc.top;
}

void CSmsBaseDlg::ResetData(BOOL bChangeBranch, BOOL bCompanyPhone)
{
	if(!bChangeBranch)
		m_cBranch.SetCompany(m_nCompany);

	long nCompany = m_cBranch.GetCompany(); 

	m_cmbCallBack.InitSmsPhoneNumber(nCompany, -1, 160);

	if(m_strCallBackPhone.GetLength() > 0)
		m_cmbCallBack.SetWindowText(m_strCallBackPhone);	

	if(m_strCallBackPhone.GetLength() > 0)
	{
		if(m_ci.GetShareCompanyOfficePhone(m_nCompany) != m_strCallBackPhone &&
			m_ci.GetPhone(m_nCompany) != m_strCallBackPhone)
		{			
			m_cmbCallBack.AddString(m_strCallBackPhone);
		}

		if(bChangeBranch == FALSE)
			m_cmbCallBack.SetWindowText(m_strCallBackPhone); 
	}

	m_edtReceiveNumber.SetWindowText(m_strRecvPhone);

	LoadSmsBalance();  
	LoadSaveMent();
	DisplaySmsCount();
	OnClickedItemSelect(IDC_SELECT_BTN1);
}

void CSmsBaseDlg::OnBnClickedAddSmsBalance()
{
	//if(!::HasPower(1840, "SMS<->공유정산금 이체 보기", TRUE))
	//	return;

	//LU()->ShowTrasferSmsToShareBalance();

	CMainFrame *pFrm = (CMainFrame*)AfxGetMainWnd();
	pFrm->SendMessage(WM_COMMAND, ID_TRANSFER_SMS_BETWEEN_SHARE_BALANCE, 0);
}

LONG CSmsBaseDlg::OnSendEmoticon(WPARAM wParam, LPARAM lParam)
{
	char const *strValue = reinterpret_cast<char const *>(wParam);

	CEdit *pEdit = (CEdit*)GetDlgItem(m_nLastSelectIndex);

	::AddTextMiddle(strValue, pEdit);

	delete strValue;

	return 0;
}

HBRUSH CSmsBaseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);


	if(pWnd->GetDlgCtrlID() == IDC_SEND_CHARGE_EDIT)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		//return HM()->GetBrushObject(RGB(255, 255, 255)); 
	}

	return hbr;
}


void CSmsBaseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonDown(nFlags, point);
}
// CAddRiderDlg 메시지 처리기입니다.

