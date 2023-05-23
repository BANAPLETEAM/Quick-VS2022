// SmsNewBulkDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SmsNewBulkDlg.h"
#include "SmsMentInsertDlg.h"
#include "SmsNewBulkFilterDlg.h"
#include "SmsNewBulkMentDlg.h"
#include "SmsNewBulkTestDlg.h"
#include "SmsNewBulkConfirmDlg.h"
#include "FileUpload.h"

// CSmsNewBulkDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSmsNewBulkDlg, CSmsBaseDlg)

CSmsNewBulkDlg::CSmsNewBulkDlg(CWnd* pParent /*=NULL*/)
	: CSmsBaseDlg(CSmsNewBulkDlg::IDD, pParent)
{
	m_strPath = "";
	m_strConnection = "";
	m_bConnected = FALSE;
 
	m_bFirstRefresh = TRUE;

	m_nSendCount = 0;
	m_pEmoticonDlg = NULL;
	m_strTitle = "";
	m_pMsgWnd = NULL;
	m_pConfirmDlg = NULL;
	m_pTestDlg = NULL;
	m_pMentDlg = NULL;
	m_pFilterDlg = NULL;
} 

CSmsNewBulkDlg::~CSmsNewBulkDlg()
{
	if(m_bConnected )
	{	
		if(m_pConnection)  // 정상적으로 끊어질때...
			m_pConnection->Close();	
	}
	if(m_pConfirmDlg)
	{
		delete m_pConfirmDlg;
		m_pConfirmDlg = NULL;
	}
	if(m_pTestDlg)
	{
		delete m_pTestDlg;
		m_pTestDlg = NULL;
	}
	if(m_pMentDlg)
	{
		delete m_pMentDlg;
		m_pMentDlg = NULL;
	}
	if(m_pFilterDlg)
	{
		delete m_pFilterDlg;
		m_pFilterDlg = NULL;
	}
}

void CSmsNewBulkDlg::DoDataExchange(CDataExchange* pDX)
{
	CSmsBaseDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PHONE_REPORT, m_lstPhone);

	DDX_Control(pDX, IDC_REMOVE_OVERLAP_CHECK, m_chkRemoveOverlap);
	DDX_Control(pDX, IDC_REMOVE_RIDER_CHECK, m_chkRemoveRider);
	DDX_Control(pDX, IDC_REMOVE_NOSMS_CHECK, m_chkRemoveNosms);

	DDX_Control(pDX, IDC_EXCEL_SHEET_COMBO, m_cmbExcelSheet);	

	DDX_Control(pDX, IDC_RESERVE_BTN, m_chkReserve);
	DDX_Control(pDX, IDC_REDATE_DT, m_dtpRedate);
	DDX_Control(pDX, IDC_RETIME_DT, m_dtpRetime);


	DDX_Control(pDX, IDC_INSERT_PHONE_EDIT, m_edtInsertPhone);
}

BEGIN_MESSAGE_MAP(CSmsNewBulkDlg, CSmsBaseDlg)
	ON_BN_CLICKED(IDC_REMOVE_OVERLAP_CHECK, OnBnClickedRemoveOverlapCheck)
	ON_BN_CLICKED(IDC_REMOVE_RIDER_CHECK, OnBnClickedRemoveRiderCheck)
	ON_BN_CLICKED(IDC_REMOVE_NOSMS_CHECK, OnBnClickedRemoveNosmsCheck)
	
	ON_BN_CLICKED(IDC_TEST_BTN, OnBnClickedTest)
	
	ON_BN_CLICKED(IDC_MENT_BTN, OnBnClickedMent)
	ON_BN_CLICKED(IDC_FILTER_BTN, OnBnClickedFilter)
	
	ON_CBN_SELCHANGE(IDC_EXCEL_SHEET_COMBO, &CSmsNewBulkDlg::OnCbnSelchangeExcelSheetCombo)
	ON_BN_CLICKED(IDC_LOAD_EXCEL_BTN, &CSmsNewBulkDlg::OnBnClickedLoadExcelBtn)
	ON_BN_CLICKED(IDC_LOAD_TEXT_BTN, &CSmsNewBulkDlg::OnBnClickedLoadTextBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CSmsNewBulkDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CONFIRM_BTN, &CSmsNewBulkDlg::OnBnClickedConfirmBtn)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_DELETE_PHONE, OnDeletePhone)
	ON_COMMAND(ID_EXCEL, OnExcel)
		
	ON_MESSAGE(WM_CHANGE_BRANCH_CODE, OnChangeBrachCode)
	ON_MESSAGE(WM_CHANGE_MENT, OnRecvMent)
	ON_BN_CLICKED(IDC_INSERT_PHONE_BTN, &CSmsNewBulkDlg::OnBnClickedInsertPhoneBtn)
	ON_MESSAGE(WM_CLICKED_BUTTON, OnClickedButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()

LONG CSmsNewBulkDlg::OnClickedButton(WPARAM wParam, LPARAM lParam)
{
	RefreshList();

	return 0;
}

void CSmsNewBulkDlg::OnPaint() 
{  
    CPaintDC dc(this); // device context for painting  
 
	LF->FillBackground(&dc, this);  
	LF->DrawRoundRect(&dc, this, &m_stc1, &m_edtSearchBranch, -14, -9, 6, 6, RGB(255, 255, 255));
	LF->DrawRoundRect(&dc, this, &m_stc10, &m_dtpRetime, -20, -10, 57, 7, RGB(255, 255, 255)); 
	LF->DrawRoundRect(&dc, this, &m_stc7, &m_edtSendCharge, -11, -11, 6, 5, RGB(255, 255, 255));
	LF->DrawRoundRect(&dc, this, &m_stc3, &m_lstPhone, -19, -9, 8, 10, RGB(255, 255, 255)); 

	LF->MakeLineVertical(&dc, this, &m_edtSaveMent[0], &m_edtSaveMent[3], 15, 20, 1);
	LF->MakeLineVertical(&dc, this, &m_edtSaveMent[1], &m_lstPhone, 15, -2, 1);
}

void CSmsNewBulkDlg::OnBnClickedTest()
{
	if(m_pTestDlg)
	{
		m_pTestDlg->RefreshList();
		m_pTestDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pTestDlg = new CSmsNewBulkTestDlg;
		m_pTestDlg->Create(IDD_SMS_NEW_BULK_TEST_DLG);
		m_pTestDlg->CenterWindow();
		m_pTestDlg->ShowWindow(SW_SHOW);
	}
}


BOOL CSmsNewBulkDlg::OnInitDialog()
{
	CSmsBaseDlg::OnInitDialog(); 

	m_picShort.SetImage(IDB_SMS_BULK_PHONE_SHORT, RGB(0, 0, 255));
	m_picLong.SetImage(IDB_SMS_BULK_PHONE_LONG, RGB(0, 0, 255));

	m_chkRemoveOverlap.SetImage(IDB_SMS_OPTION_CHECK1, IDB_SMS_OPTION1, this);
	m_chkRemoveRider.SetImage(IDB_SMS_OPTION_CHECK2, IDB_SMS_OPTION2, this);
	m_chkRemoveNosms.SetImage(IDB_SMS_OPTION_CHECK3, IDB_SMS_OPTION3, this);
	m_chkReserve.SetImage(IDB_SMS_OPTION_CHECK4, IDB_SMS_OPTION4, this);

	m_edtInsertPhone.SetWindowText(AfxGetApp()->GetProfileString("CSmsNewBulkDlg", "strPhone", ""));

	m_dtpRedate.SetTime(COleDateTime::GetCurrentTime()); 
	m_dtpRetime.SetTime(COleDateTime::GetCurrentTime());

	m_edtInsertPhone.SetFont(m_FontManager.GetFont("맑은 고딕", 16));

	m_dtpRetime.SetFormat("tth-mm");
	GetDlgItem(IDC_REDATE_DT)->EnableWindow(TRUE);
	GetDlgItem(IDC_RETIME_DT)->EnableWindow(TRUE);
	 
	CoInitialize(NULL);

	if(!m_bConnected)
	{
		::CoCreateInstance(ADODB::CLSID_Connection, NULL, CLSCTX_ALL, ADODB::IID__Connection, (void**)&m_pConnection);	
	}

	m_chkRemoveOverlap.SetCheck(TRUE);
	m_chkRemoveRider.SetCheck(FALSE);
	m_chkRemoveNosms.SetCheck(FALSE);

	static LOGFONT lfList = {14,0,0,0,FW_NORMAL,0,0,0,HANGUL_CHARSET,0,0,0,0,"맑은 고딕"};
 
	m_lstPhone.InsertColumn(0, "전화번호", LVCFMT_LEFT, 120);
	m_lstPhone.GetPaintManager()->m_strNoItems = "";
	m_lstPhone.GetPaintManager()->SetTextFont(lfList);
	m_lstPhone.ShowHeader(FALSE);
	m_lstPhone.GetReportHeader()->SetAutoColumnSizing(TRUE);
	m_lstPhone.Populate();
												 	
	LF->LoadNoSmsPhone(m_cBranch.GetCompany());
	LF->LoadRiderPhone();

	Invalidate();
	m_edtMent.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSmsNewBulkDlg::OnBnClickedRemoveOverlapCheck()
{
	RefreshList();
}

void CSmsNewBulkDlg::OnBnClickedRemoveRiderCheck()
{
	RefreshList();
}

void CSmsNewBulkDlg::OnBnClickedRemoveNosmsCheck()
{
	RefreshList(); 
}

void CSmsNewBulkDlg::OnCbnSelchangeExcelSheetCombo()
{
	ReadSheet();
}

void CSmsNewBulkDlg::OnBnClickedLoadExcelBtn()
{
	CWaitCursor wait;	// Set clock cursor;

	try
	{
		if(m_bConnected)	
		{
			if(MessageBox("현재 열린 문서를 닫으시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
			{
				m_pConnection->Close();	
				m_bConnected = FALSE;
			}
			else
				return;			
		}

		HRESULT hr = 0;
		ADODB::_Recordset * pRecordset = NULL;

		static DWORD dwTotalSize = 0;
		static long nFileCount = 0;
		CFileDialog dlg( TRUE, "", m_strPath,
			OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
			_T("Excel Files (*.xls)(*.xlsx)(*.mdb)|;*.xls;*.mdb;*.xlsx"), this );	
		dlg.m_ofn.lpstrInitialDir = m_strPath;	
		dlg.m_ofn.lpstrTitle = _T("파일형식 맞는 파일을 선택하세요.");
		if(dlg.DoModal() != IDOK)
			return;		
		POSITION pos = dlg.GetStartPosition();
		m_strPath = dlg.GetNextPathName(pos);
		if(m_strPath.GetLength() == 0)
			throw("파일이름이 없거나 선택이 되지 않았습니다.");

		if(m_strPath.Right(4).MakeUpper() == "XLSX"  )
			m_strConnection = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" + m_strPath + ";Extended Properties=\"Excel 12.0;hdr=no\"");
		else if(m_strPath.Right(3).MakeUpper() == "XLS"  )
			m_strConnection = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + m_strPath + ";Extended Properties=\"Excel 8.0;hdr=no\"");
		else
		{
			throw("엑셀 파일만 작업 가능합니다.");
		}


		m_bConnected = (m_pConnection->Open(_bstr_t(m_strConnection), _T(""), _T(""), ADODB::adConnectUnspecified) == S_OK);

		if(!m_bConnected)
			throw("파일을 열수가 없습니다 열려진 파일을 닫아주시기 바랍니다.");

		ReadExcel();
		return;
	}
	catch(char *Msg)
	{
		MessageBox(Msg, "확인" ,MB_ICONERROR);
	}
	catch(_com_error error)
	{
		MessageBox(error.Description(), _T("SQL Query Failed"), MB_OK|MB_ICONERROR);
		m_strPath = "";
	}

	ReadExcel();
}


BOOL CSmsNewBulkDlg::ReadExcel()
{
	try
	{
		if(!m_bConnected || m_pConnection == NULL)
			throw("파일을 여는 과정에 연결되지 않았습니다.");

		CString strTemp;
		_variant_t varCriteria[4];
		LONG lIndex = 0;
		HRESULT hr = 0;

		_bstr_t bstrTableType("Table");
		varCriteria[0].vt = VT_EMPTY;
		varCriteria[1].vt = VT_EMPTY;
		varCriteria[2].vt = VT_EMPTY;
		varCriteria[3] = bstrTableType;

		VARIANT varData;
		SAFEARRAY FAR* psa;
		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = 4;
		psa = SafeArrayCreate(VT_VARIANT, 1, rgsabound);

		SysFreeString(bstrTableType);

		for( lIndex = 0 ; lIndex < 4 ;lIndex++)
		{
			hr  = SafeArrayPutElement(psa, &lIndex,&varCriteria[lIndex]);
		}

		varData.vt = VT_VARIANT | VT_ARRAY;
		V_ARRAY(&varData) = psa;		
		ADODB::_RecordsetPtr   Rs1= NULL;
		Rs1 =  m_pConnection->OpenSchema(ADODB::adSchemaTables,varData);
		if(Rs1 == NULL)
			throw("파일의 테이블들이 없습니다.");


		//		m_lstTable.DeleteAllItems();

		strTemp.Empty();
		long nItem = 0;

		m_cmbExcelSheet.ResetContent();

		while (VARIANT_TRUE != Rs1->GetadoEOF())
		{
			strTemp = LF->ChangeStringFromExcel(Rs1->Fields->GetItem(_variant_t((long)2))->Value);

			m_cmbExcelSheet.AddString(strTemp);
			Rs1->MoveNext();
		}
		Rs1->Close();

		if(m_cmbExcelSheet.GetCount() > ZERO)
		{
			m_cmbExcelSheet.SetCurSel(ZERO);
			ReadSheet();
		}

		return TRUE;
	}
	catch(_com_error error)
	{
		MessageBox(error.Description(), _T("Failed To Connect"), MB_OK|MB_ICONERROR);
		return FALSE;
	}
}

void CSmsNewBulkDlg::OnBnClickedSendBtn()
{
	if(m_lstPhone.GetRows()->GetCount() <= 0)
	{
		MessageBox("엑셀 혹은 텍스트 파일로 전화번로를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CString strMent; m_edtMent.GetWindowText(strMent);
	CString strTitle; m_edtMMSTitle.GetWindowText(strTitle);
	//CString strCallBackPhone; m_cmbCallBack.GetWindowText(strCallBackPhone);
	//strCallBackPhone.Replace("-", "");

	CString strCallBackPhone = m_cmbCallBack.GetSmsPhoneNumber();

	if(strMent.IsEmpty())
	{
		MessageBox("전송하실 멘트를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(strCallBackPhone.IsEmpty())
	{
		MessageBox("발신번호를 입력하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	BOOL bReserve = m_chkReserve.GetCheck();
	COleDateTime dtReserve(COleDateTime::GetCurrentTime());

	if(bReserve)
	{ 
		COleDateTime dtCur = COleDateTime::GetCurrentTime();

		COleDateTime dtDate; m_dtpRedate.GetTime(dtDate);
	 	COleDateTime dtTime; m_dtpRetime.GetTime(dtTime);

		dtReserve = COleDateTime(dtDate.GetYear(), dtDate.GetMonth(), dtDate.GetDay(), dtTime.GetHour(), dtTime.GetMinute(), dtTime.GetSecond());

		COleDateTimeSpan span = dtReserve - dtCur;

		if(dtCur > dtReserve)
		{
			MessageBox("현재시간보다 이전시간으로 예약 하실 수 없습니다", "확인", MB_ICONINFORMATION);
			return;
		}
	}

	if(MessageBox("전송하시겠습니까?", "확인", MB_OKCANCEL) != IDOK)
		return;

	CXTPGridRecords *pRecords = m_lstPhone.GetRecords();
	long nCount = pRecords->GetCount();
	
/*
	const int nMBSize = 1024 * 1024 * 10;
	char *szTemp = new char[nMBSize + 1];
	memset(szTemp, 0, nMBSize + 1);
	int nCur = 0; 

	for(int i=0; i<nCount; i++)
	{
		char szPhone[20];
		CString strItem = (CString)pRecords->GetAt(i)->GetItem(0)->GetCaption(NULL);
		strItem = LF->GetNoneDashNumber(strItem);
		strcpy(szPhone, strItem);
		int nLen = strlen(szPhone);
		strcpy(&szTemp[nCur], szPhone);
		strcpy(&szTemp[nCur + nLen], "\r\n");
		nCur += nLen + 2; 
	}    

  
	CString strMsg;   

	srand(time(NULL));  
	long nRand = rand()%10000;  

	CString strFileName;
	strFileName.Format("a_%d.txt", nRand);
 */
	//m_pMkDb->UploadFile(strFileName, szTemp, nCur);
	//(nCur * 8) + 1  

	/*
 
	if(!m_pMkDb->UploadFile(strFileName, szTemp, nCur))
	{ 
		delete szTemp;
		MessageBox(strMsg, "에러", MB_ICONINFORMATION);
		return;
	}
	*/

	/*
	if(!m_pMkDb->UploadFile("211.172.242.164", 9999, "112233", szTemp, nCur, strFileName, strMsg))
	{ 
		delete szTemp;
		MessageBox(strMsg, "에러", MB_ICONINFORMATION);
		return;
	}
	*/
	
//	delete szTemp;

	if(nCount >= 13000)
	{
		MessageBox("13000건 이상 동시 전송 하실수 없습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	#define	ARRY_STRING_COUNT 20

	CString strPhoneList[ARRY_STRING_COUNT] = {"", }; //660 개씩

	long nItem = 0;

	for(int i=0; i<nCount; i++)
	{
		CString strItem = (CString)pRecords->GetAt(i)->GetItem(0)->GetCaption(NULL);
		strItem = LF->GetNoneDashNumber(strItem);

		if((i > 0) && ((i % 660) == 0))
		{
			nItem++;
		}

		strPhoneList[nItem] += strItem + ";";
	}

	 
	if(m_nSendType == TYPE_SMS)  
	{ 
		CMkCommand cmd(m_pMkDb, "insert_bulk_sms_2013_client_1");
		CMkParameter *parRet = cmd.AddParameter(typeLong , typeReturn, sizeof(long), 0);
		cmd.AddParameter(m_cBranch.GetCompany());   
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);
		cmd.AddParameter(strCallBackPhone); 
		cmd.AddParameter(strMent);
		cmd.AddParameter(bReserve);
		cmd.AddParameter(dtReserve); 

		for(int i=0; i<ARRY_STRING_COUNT; i++)
			cmd.AddParameter(strPhoneList[i]); 

		if(!cmd.Execute())
			return;

		long nRet; parRet->GetValue(nRet);


		//멘트수정
		if(nRet == -1)
		{
			MessageBox("잔액이 부족 및 기타 사유로 전송 실패하였습니다.", "확인", MB_ICONERROR);
			return;
		}
		
		MessageBox("전송되었습니다", "확인", MB_ICONINFORMATION);
		return;
	}
	else
	{
		if(m_nMMSImageCount > 0) {
			CFileUpload fu;
			fu.SetConnectInfo(FTP_IP, FTP_URL_ID_PICTURE, "", "");
	 
			for(int i=0; i<m_nMMSImageCount; i++)
			{ 
				if(!fu.UploadFile(m_strImage[i]))
				{
					MessageBox("파일 업로드중 문제가 발생했습니다.\r\n다시 시도하세요.", "확인", MB_ICONINFORMATION);
				}
			}
		}		

		CMkCommand cmd(m_pMkDb, "insert_bulk_mms_2013_client_1");
		CMkParameter *parRet = cmd.AddParameter(typeLong , typeReturn, sizeof(long), 0);
		cmd.AddParameter(m_cBranch.GetCompany()); 
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.strName);
		cmd.AddParameter(strCallBackPhone);
		cmd.AddParameter(strMent);
		cmd.AddParameter(bReserve);
		cmd.AddParameter(dtReserve); 
		cmd.AddParameter(m_nMMSImageCount);
		cmd.AddParameter(strTitle);
		cmd.AddParameter(m_strImage[0]);
		cmd.AddParameter(m_strImage[1]);
		cmd.AddParameter(m_strImage[2]);

		for(int i=0; i<ARRY_STRING_COUNT; i++)
			cmd.AddParameter(strPhoneList[i]); 

		if(!cmd.Execute())
			return;

		long nRet; parRet->GetValue(nRet);

		if(nRet == -1)
		{
			MessageBox("잔액이 부족 및 기타 사유로 전송 실패하였습니다.", "확인", MB_ICONERROR);
			return;
		}
		
		MessageBox("전송되었습니다", "확인", MB_ICONINFORMATION);
		return;
	}
}

void CSmsNewBulkDlg::OnBnClickedLoadTextBtn()
{
	CFileDialog dlg( TRUE, "", m_strPath,
		OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
		_T("Excel Files (*.txt)|;*.txt"), this );	
	dlg.m_ofn.lpstrInitialDir = m_strPath;	
	dlg.m_ofn.lpstrTitle = _T("파일형식 맞는 파일을 선택하세요.");
	if(dlg.DoModal() != IDOK)
		return;		
	POSITION pos = dlg.GetStartPosition();
	m_strPath = dlg.GetNextPathName(pos);

	if(m_strPath.GetLength() == 0)
	{
		MessageBox("파일이름이 없거나 선택이 되지 않았습니다.", "확인", MB_ICONINFORMATION);
		return;
	}

	TRY
	{
		if(m_lstPhone.GetItemCount() > 0)
		{
			if(MessageBox("기존 읽어들인 내용을 삭제 하시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
			{
				m_mapOverlap.clear();
				m_mapRealPhone.clear();
			}
		}
		 
		CFile file; 
		CString strPhone;

		file.Open(m_strPath, CFile::modeRead);
		CArchive ar(&file, CArchive::load);

		while(ar.ReadString(strPhone))
		{
			strPhone.Replace("-", "");
			if(LF->IsMobilePhoneNumber(strPhone))
				AddRealPhoneMap(strPhone);
		}

		file.Close();
 
		RefreshList();
	}
	CATCH_ALL(e)
	{
		MessageBox("파일 오픈중 에러발생!!");
	}
	END_CATCH_ALL
}

void CSmsNewBulkDlg::ReadSheet()
{
	long nIndex = m_cmbExcelSheet.GetCurSel();

	if(nIndex < 0)
	{
		MessageBox("불러올 시트를 선택하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	HRESULT hr = 0;
	ADODB::_Recordset *pPreviewSheetSet= NULL;
	CString strTable;//  = "KOREA1$";

	m_cmbExcelSheet.GetLBText(nIndex, strTable);
	//BOOL bHeaer = HeaderCheck2( strTable);
	::CoCreateInstance(ADODB::CLSID_Recordset, NULL, CLSCTX_ALL, ADODB::IID__Recordset, (void**)&pPreviewSheetSet);

	CString strQuery = "select * from [" + strTable + "]";
	int nSendTel = 0, nReceiveTel = 0, nMsg = 0, nTitle = 0, nSendTime = 0;

	if(pPreviewSheetSet->Open(_bstr_t(strQuery), _variant_t((IDispatch *) m_pConnection, true), 
		ADODB::adOpenStatic, ADODB::adLockOptimistic, ADODB::adCmdText) == S_OK) 
	{
		long nRecordCount = pPreviewSheetSet->GetRecordCount();

		ADODB::Fields *pFields;

		CString strColName;

		pFields = pPreviewSheetSet->GetFields();
		long nFieldCount = pFields->GetCount();

		
		strQuery = "select * from [" + strTable + "]";

		CString strVal = "",strTel = "";
		//SMSChunkSubDlg4Data data;
		ADODB::_Recordset *pListRecordset= NULL;
		ADODB::Field15 *pField = NULL;

		::CoCreateInstance(ADODB::CLSID_Recordset, NULL, CLSCTX_ALL, ADODB::IID__Recordset, (void**)&pListRecordset);

		if(m_lstPhone.GetItemCount() > 0) 
		{
			if(MessageBox("기존 읽어들인 내용을 삭제 하시겠습니까?", "확인", MB_OKCANCEL) == IDOK)
			{
				m_mapOverlap.clear();
				m_mapRealPhone.clear();
			}
		}

		if(pListRecordset->Open(_bstr_t(strQuery), _variant_t((IDispatch *) m_pConnection, true), 
			ADODB::adOpenStatic,ADODB::adLockOptimistic, ADODB::adCmdText) == S_OK) 
		{
			long nRecordCount = pListRecordset->GetRecordCount();
			for(long nRow = 0; nRow < nRecordCount; nRow++)
			{
				//if(nRow == 0)
				//{
				//	pListRecordset->MoveNext();
				//	continue;
				//}

				BOOL bAllCheck = FALSE;			

				for(long col = 0; col < nFieldCount; col++)
				{	
					pListRecordset->Fields->GetItem(_variant_t((long)col))->Type;
					_variant_t val, valvt, valString("");

					switch(pListRecordset->Fields->GetItem(_variant_t((long)col))->Type)
					{
					case 5: // adDouble = 5
						val.vt = VT_I4;							
						break;
					case 7: // adDate = 7
						val.vt = VT_DATE;
						break;
					case 202: // adVarWChar = 202
					case 200: // adVarChar = 200
					case 201: // adLongVarChar = 200
					case 130: // adWChar = 200
						val.vt = VT_BSTR;
						break;	
					}				

					ADODB::Field20Ptr pField2 = pListRecordset->GetFields()->GetItem(_variant_t((long)col) );										
					pField2->get_Value(&val);										
					strVal = LF->ChangeStringFromExcel(val);
					strVal.Replace("-", "");

					if(strVal.Left(2) == "01" && LF->IsNumber(strVal) && (strVal.GetLength() == 10 || strVal.GetLength() == 11))
						AddRealPhoneMap(strVal);
				} // col 돌리기

				pListRecordset->MoveNext();
			}

			pListRecordset->Close();
			pListRecordset->Release();
		}
	}

	RefreshList();
}

BOOL CSmsNewBulkDlg::IsNosmsPhone(CString strPhone)
{
	MAP_PHONE* mapNosmsPhone = LF->GetNosmsPhoneMap(m_cBranch.GetCompany());

	MAP_PHONE::iterator itNosmsPhone = mapNosmsPhone->find(atoi(strPhone));

	if(itNosmsPhone != mapNosmsPhone->end())
		return TRUE;

	return FALSE;
}

BOOL CSmsNewBulkDlg::IsOverPhone(CString strPhone)
{
	MAP_PHONE::iterator itOvelap = m_mapOverlap.find(atoi(strPhone));

	if(itOvelap != m_mapOverlap.end())
		return TRUE;

	m_mapOverlap.insert(MAP_PHONE::value_type(atoi(strPhone), strPhone));
	return FALSE;	
}

BOOL CSmsNewBulkDlg::IsRiderPhone(CString strPhone)
{
	MAP_PHONE* vecRiderPhone = LF->GetRiderPhoneMap();

	MAP_PHONE::iterator itRider = vecRiderPhone->find(atoi(strPhone));

	if(itRider != vecRiderPhone->end())
		return TRUE;

	return FALSE;
}

void CSmsNewBulkDlg::InitData(MAP_PHONE *pMap)
{
	if(pMap == NULL)
		return;

	m_mapRealPhone.clear();

	for(MAP_PHONE::iterator it = pMap->begin(); it != pMap->end(); it++)
		AddRealPhoneMap(it->second);

	RefreshList();
}

void CSmsNewBulkDlg::AddRealPhoneMap(CString strPhone)
{
	ST_SMS_FILTER st;

	st.strPhone = strPhone;
	st.bNosms = IsNosmsPhone(strPhone);
	st.bOverlap = IsOverPhone(strPhone);
	st.bRiderPhone = IsRiderPhone(strPhone);

	m_mapRealPhone.insert(MAP_SMS_PHONE::value_type(m_mapRealPhone.size(), st));
}

void CSmsNewBulkDlg::DeleteRealPhoneMap(CString strPhone)
{
	strPhone.Replace("-", "");

	for(MAP_SMS_PHONE::iterator it = m_mapRealPhone.begin(); it != m_mapRealPhone.end(); it++)
	{
		if(it->second.strPhone == strPhone)
		{
			m_mapRealPhone.erase(it);
			break;
		}
	}

	RefreshList();
}

void CSmsNewBulkDlg::RefreshList()
{
	m_lstPhone.DeleteAllItems();

	BOOL bRiderPhone = m_chkRemoveRider.GetCheck();
	BOOL bNoSmsPhone = m_chkRemoveNosms.GetCheck();
	BOOL bOverlap = m_chkRemoveOverlap.GetCheck();

	long nItem = 0;

	for(MAP_SMS_PHONE::iterator it = m_mapRealPhone.begin(); it != m_mapRealPhone.end(); it++)
	{
		ST_SMS_FILTER st = it->second;

		if(bRiderPhone && st.bRiderPhone)
			continue;

		if(bNoSmsPhone && st.bNosms)
			continue;

		if(bOverlap && st.bOverlap)
			continue;

		m_lstPhone.InsertItem(nItem++, LF->GetDashPhoneNumber(st.strPhone));
	}

	m_lstPhone.Populate();
	SetSendCount(m_lstPhone.GetItemCount());
}

 
void CSmsNewBulkDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rcPhone, rcMent;

	m_lstPhone.GetWindowRect(&rcPhone);

	if(!rcPhone.PtInRect(point)) 
		return;

	CMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU_1);
	CMenu *pRMenu = rMenu.GetSubMenu(10);

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	
}


void CSmsNewBulkDlg::OnDelete()
{
	CSmsBaseDlg::OnDelete();
}

void CSmsNewBulkDlg::OnUpdate()
{
	CSmsBaseDlg::OnUpdate();
}

LONG CSmsNewBulkDlg::OnChangeBrachCode(WPARAM wParam, LPARAM lParam)
{	
	if(m_bFirstRefresh)
	{
		m_bFirstRefresh = FALSE;
		return 0;
	}

	CBranchInfo *pBi = (CBranchInfo*)wParam;
	m_nCompany = pBi->nCompanyCode;
	ResetData(TRUE);

	LF->LoadNoSmsPhone(m_cBranch.GetCompany());

	/*
	CBranchInfo *pBi = (CBranchInfo*)wParam;
	m_nCompany = pBi->nCompany;
	ResetData(TRUE);
	*/

	return 0;
}

void CSmsNewBulkDlg::OnBnClickedMent()
{
	/*CREATE_MODALESS(CSmsNewBulkMentDlg, this);
	pDlg->m_pParent = this; 
	pDlg->m_nCompany = m_cBranch.GetCompany();
	SHOW_MODALESS(CSmsNewBulkMentDlg, this);*/

	if(m_pMentDlg)
	{
		m_pMentDlg->m_nCompany = m_cBranch.GetCompany();
		m_pMentDlg->InitSmsBulkMent();
		m_pMentDlg->LoadSmsBulkMent();
		m_pMentDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pMentDlg = new CSmsNewBulkMentDlg;
		m_pMentDlg->m_pParent = this;
		m_pMentDlg->m_nCompany = m_cBranch.GetCompany();
		m_pMentDlg->Create(IDD_SMS_NEW_BULK_MENT_DLG);
		m_pMentDlg->CenterWindow();
		m_pMentDlg->ShowWindow(SW_SHOW);
	}
}

void CSmsNewBulkDlg::OnBnClickedFilter()
{
	if(m_pFilterDlg)
		m_pFilterDlg->ShowWindow(SW_SHOW);
	else
	{
		m_pFilterDlg = new CSmsNewBulkFilterDlg;
		m_pFilterDlg->Create(IDD_SMS_NEW_BULK_FILTER_DLG);
		m_pFilterDlg->CenterWindow();
		m_pFilterDlg->ShowWindow(SW_SHOW);
	}
}

LONG CSmsNewBulkDlg::OnRecvMent(WPARAM wParam, LPARAM lParam)
{
	char const *strValue = reinterpret_cast<char const *>(wParam);
	SetMentWindowText(strValue);
	DisplayByte();
 
	return 0;
}

void CSmsNewBulkDlg::OnBnClickedConfirmBtn()
{
	if(m_pConfirmDlg)
	{
		m_pConfirmDlg->RefreshList();
		m_pConfirmDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pConfirmDlg = new CSmsNewBulkConfirmDlg;
		m_pConfirmDlg->Create(IDD_SMS_NEW_BULK_CONFIRM_DLG);
		m_pConfirmDlg->CenterWindow();
		m_pConfirmDlg->ShowWindow(SW_SHOW);
	}
}

void CSmsNewBulkDlg::OnBnClickedInsertPhoneBtn()
{
	CString strPhone; 
	m_edtInsertPhone.GetWindowText(strPhone);

	AfxGetApp()->WriteProfileString("CSmsNewBulkDlg", "strPhone", strPhone);

	strPhone.Replace("-", "");

	AddRealPhoneMap(strPhone);
	RefreshList();
}

void CSmsNewBulkDlg::OnDeletePhone()
{
	CXTPGridRecord *pRecord = m_lstPhone.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	CString strPhone = pRecord->GetItem(0)->GetCaption(NULL);

	DeleteRealPhoneMap(strPhone);
}

void CSmsNewBulkDlg::OnExcel()
{
	CMyExcel::ToExcel(&m_lstPhone);
}