// OrderInsertDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "OrderInsertDlg.h"
//#include "SearchCorpDlg.h"
#include "VarietyDlg.h"

// COrderInsertDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(COrderInsertDlg, CMyDialog)

COrderInsertDlg::COrderInsertDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(COrderInsertDlg::IDD, pParent)
{
	m_strPath = "";
	m_strConnection = "";
	m_bConnected = FALSE;
	m_bChangeToCorp = FALSE;
}

COrderInsertDlg::~COrderInsertDlg()
{
	if(m_bConnected )
	{	
		if(m_pConnection)  // ���������� ��������...
			m_pConnection->Close();	
	}
}

void COrderInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRANCH_COMBO, m_cmbBranch);
	DDX_Control(pDX, IDC_SHEET_COMBO, m_cmbSheet); 
	DDX_Control(pDX, IDC_LIST, m_lstReport); 
}


BEGIN_MESSAGE_MAP(COrderInsertDlg, CMyDialog)
	ON_BN_CLICKED(IDC_READ_BTN, &COrderInsertDlg::OnBnClickedReadBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &COrderInsertDlg::OnBnClickedCloseBtn)
	ON_CBN_SELCHANGE(IDC_SHEET_COMBO, &COrderInsertDlg::OnCbnSelchangeSheetCombo)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_REFRESH_STATE, OnRefreshState)
	ON_COMMAND(ID_DELETE, OnDelete)	
//	ON_COMMAND(ID_CORP_INSERT, OnCorpInsert)
	ON_CBN_SELCHANGE(IDC_BRANCH_COMBO, &COrderInsertDlg::OnCbnSelchangeBranchCombo)
	ON_BN_CLICKED(IDC_ORDER_INSERT_BTN, &COrderInsertDlg::OnBnClickedOrderInsertBtn)
END_MESSAGE_MAP()                                                                                       


// COrderInsertDlg �޽��� ó�����Դϴ�.

void COrderInsertDlg::OnBnClickedReadBtn()
{
	CWaitCursor wait;	// Set clock cursor;

	try
	{
		if(m_bConnected)	
		{
			if(MessageBox("���� ���� ������ �����ðڽ��ϱ�?", "Ȯ��", MB_OKCANCEL) == IDOK)
			{
				m_pConnection->Close();	
				m_bConnected = FALSE;
			}
			else
				return;			
			//throw("�̹� ������ �����ֽ��ϴ�. ������ �ݾ��ּ���");
		}

		HRESULT hr = 0;
		ADODB::_Recordset * pRecordset = NULL;

		static DWORD dwTotalSize = 0;
		static long nFileCount = 0;
		CFileDialog dlg( TRUE, "", m_strPath,
			OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
			_T("Excel Files (*.xls)(*.xlsx)(*.mdb)|;*.xls;*.mdb;*.xlsx"), this );	
		dlg.m_ofn.lpstrInitialDir = m_strPath;	
		dlg.m_ofn.lpstrTitle = _T("�������� �´� ������ �����ϼ���.");
		if(dlg.DoModal() != IDOK)
			return;		
		POSITION pos = dlg.GetStartPosition();
		m_strPath = dlg.GetNextPathName(pos);
		if(m_strPath.GetLength() == 0)
			throw("�����̸��� ���ų� ������ ���� �ʾҽ��ϴ�.");

		if(m_strPath.Right(4).MakeUpper() == "XLSX"  )
		{
			//m_strConnection = _T("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" + m_strPath + ";Extended Properties=\"Excel 12.0;hdr=no\"");
			m_strConnection = _T("Provider=Microsoft.ACE.OLEDB.12.0; Data Source=" + m_strPath + ";Extended Properties=\"Excel 12.0;hdr=no\"");
		}
		else if(m_strPath.Right(3).MakeUpper() == "XLS"  )
			m_strConnection = _T("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=" + m_strPath + ";Extended Properties=\"Excel 8.0;hdr=no\"");
		else
		{
			throw("���� ���ϸ� �۾� �����մϴ�.");
		}


		m_bConnected = (m_pConnection->Open(_bstr_t(m_strConnection), _T(""), _T(""), ADODB::adConnectUnspecified) == S_OK);

		if(!m_bConnected)
			throw("������ ������ �����ϴ� ������ ������ �ݾ��ֽñ� �ٶ��ϴ�.");

		ReadExcel();
		return;
	}
	catch(char *Msg)
	{
		MessageBox(Msg, "Ȯ��" ,MB_ICONERROR);
	}
	catch(_com_error error)
	{
		MessageBox(error.Description(), _T("SQL Query Failed"), MB_OK|MB_ICONERROR);
		m_strPath = "";
	}

	ReadExcel();
}

BOOL COrderInsertDlg::ReadExcel()
{
	try
	{
		if(!m_bConnected || m_pConnection == NULL)
			throw("������ ���� ������ ������� �ʾҽ��ϴ�.");

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
			throw("������ ���̺���� �����ϴ�.");


		//		m_lstTable.DeleteAllItems();

		strTemp.Empty();
		long nItem = 0;

		m_cmbSheet.ResetContent();

		while (VARIANT_TRUE != Rs1->GetadoEOF())
		{
			strTemp = ::ChangeStringFromExcel(Rs1->Fields->GetItem(_variant_t((long)2))->Value);

			m_cmbSheet.AddString(strTemp);

			/*
			if(m_bExcel && (strTemp.Right(1) == "$" ||strTemp.Right(2) == "$'" ) )
			{
			m_lstTable.InsertItem(nItem,strTemp, 10);
			nItem++;  // $���̺��� �ƴѰ��
			}
			else if(!m_bExcel)
			{
			m_lstTable.InsertItem(nItem,strTemp, 10);
			nItem++;
			}
			*/

			Rs1->MoveNext();
		}
		Rs1->Close();

		if(m_cmbSheet.GetCount() > ZERO)
		{
			m_cmbSheet.SetCurSel(ZERO);
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

enum {COL_TIME, COL_TEL, COL_START, COL_DEST, COL_CHARGE, COL_MEMO, COL_CORP, COL_CORP_DEPART, COL_NAME, COL_ETC};

BOOL COrderInsertDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CoInitialize(NULL);

	//CString s = "kk";
	//SetResize(IDC_LIST1, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	if(!m_bConnected)
	{
		::CoCreateInstance(ADODB::CLSID_Connection, NULL, CLSCTX_ALL, ADODB::IID__Connection, (void**)&m_pConnection);	
	}

	m_lstReport.InsertColumn(0, "��¥", LVCFMT_LEFT, 120);
	m_lstReport.InsertColumn(1, "�Ƿ���ȸ���", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(2, "�Ƿ����μ�", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(3, "�Ƿ��������", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(4, "�Ƿ�����ȭ1", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(5, "�Ƿ�����ȭ2", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(6, "�Ƿ�����ġ", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(7, "�Ƿ����޸�", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(8, "�����ȸ���", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(9, "������μ�", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(10, "����������", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(11, "�������ȭ1", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(12, "�������ȭ2", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(13, "�������ġ", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(14, "������ȸ���", LVCFMT_LEFT, 100);
	m_lstReport.InsertColumn(15, "�������μ�", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(16, "�����������", LVCFMT_LEFT, 70);
	m_lstReport.InsertColumn(17, "��������ȭ1", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(18, "��������ȭ2", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(19, "��������ġ", LVCFMT_LEFT, 80);
	m_lstReport.InsertColumn(20, "����", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(21, "����", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(22, "��/�պ�", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(23, "���", LVCFMT_LEFT, 50);
	m_lstReport.InsertColumn(24, "�⺻���", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(25, "�߰����", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(26, "���ο��", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(27, "Ź�ۿ��", LVCFMT_LEFT, 60);
	m_lstReport.InsertColumn(28, "����", LVCFMT_LEFT, 100);

	m_lstReport.Populate();

	long nItem = 0;

	for(int i=1; i<m_ba.GetCount(); i++)
	{
		CBranchInfo *pBi = m_ba.GetAt(i);
		if(pBi->bIntegrated)
			continue;

		m_cmbBranch.InsertString(nItem , pBi->strBranchName);
		m_cmbBranch.SetItemData(nItem ++, (DWORD_PTR)pBi);
	}

	if(m_ba.GetCount() > 0)
		m_cmbBranch.SetCurSel(ZERO);


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void COrderInsertDlg::OnBnClickedCloseBtn()
{
	if(m_bConnected )
	{	
		if(m_pConnection)  // ���������� ��������...
			m_pConnection->Close();

		m_cmbSheet.ResetContent();

		m_bConnected = FALSE;
	}
}

void COrderInsertDlg::OnCbnSelchangeSheetCombo()
{
	ReadSheet();
}

void COrderInsertDlg::ReadSheet()
{
	long nIndex = m_cmbSheet.GetCurSel();

	if(nIndex < 0)
	{
		MessageBox("�ҷ��� ��Ʈ�� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	HRESULT hr = 0;
	ADODB::_Recordset *pPreviewSheetSet= NULL;
	CString strTable;//  = "KOREA1$";

	m_cmbSheet.GetLBText(nIndex, strTable);
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

		/*
		long  nCount = 0, nCol = 0;

		CString strSendTel = "", strReceiveTel = "", strMsg = "", strTitle = "", strSendTime = "";

		m_cmbRNo.ResetContent(); m_cmbAmount.ResetContent(); m_cmbEtc.ResetContent();

		for(int nField = 0; nField < m_nFieldCounts; nField++) 
		{					
		strColName = BstrToCString(pFields->GetItem(_variant_t((long)nField))->GetName());
		m_List.InsertColumn(nCol++ , strColName,DT_LEFT, 100,TRUE);	


		m_cmbRNo.InsertString(nField, strColName);
		m_cmbAmount.InsertString(nField, strColName);
		m_cmbEtc.InsertString(nField, strColName);

		nCount++;			
		}

		//m_List.SetImageList(&ImageList,LVSIL_SMALL); 
		m_List.ModifyStyle(0, LVS_SHOWSELALWAYS);
		m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_FLATSB | LVS_EX_GRIDLINES );	
		m_List.AllowEdit(TRUE);
		m_List.Populate();



		if(	pPreviewSheetSet) // bHader ������ �߿�
		{
		pPreviewSheetSet->Close();
		pPreviewSheetSet->Release();
		}
		*/

		strQuery = "select * from [" + strTable + "]";

		CString strVal = "",strTel = "";
		//SMSChunkSubDlg4Data data;
		ADODB::_Recordset *pListRecordset= NULL;
		ADODB::Field15 *pField = NULL;

		::CoCreateInstance(ADODB::CLSID_Recordset, NULL, CLSCTX_ALL, ADODB::IID__Recordset, (void**)&pListRecordset);

		m_lstReport.DeleteAllItems();

		if(pListRecordset->Open(_bstr_t(strQuery), _variant_t((IDispatch *) m_pConnection, true), 
			ADODB::adOpenStatic,ADODB::adLockOptimistic, ADODB::adCmdText) == S_OK) 
		{
			long nRecordCount = pListRecordset->GetRecordCount();
			for(long nRow = 0; nRow < nRecordCount; nRow++)
			{
				if(nRow == 0)
				{
					pListRecordset->MoveNext();
					continue;
				}

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
					strVal = ::ChangeStringFromExcel(val);

					if(col == 4 || col ==  5 || col == 12 || col ==  13 || col == 20 || col == 21) //��ȭ��ȣ
						strVal = ::GetNoneDashNumberRemoveDDD(strVal);
					else if(col == 29 || col == 30 || col == 31 || col == 32) //���
						strVal.Replace(",", "");

					if(strVal == "NULL")
						strVal = "";

					if(col == COL_TIME)
						m_lstReport.InsertItem(nRow-1, strVal);
					else
						m_lstReport.SetItemText(nRow-1, col, strVal);

				} // col ������

				pListRecordset->MoveNext();
			}

			m_lstReport.Populate();
			//RefreshStateAll();

			pListRecordset->Close();
			pListRecordset->Release();
		}
	}
}

void COrderInsertDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	if(!m_lstReport.GetSafeHwnd())
		return;

	CRect rcDlg, rcList;
	GetClientRect(rcDlg);
	m_lstReport.GetWindowRect(rcList);
	ScreenToClient(rcList);

	rcList.right = rcDlg.right - 3;
	rcList.bottom = rcDlg.bottom - 3; 

	m_lstReport.MoveWindow(rcList);
}

void COrderInsertDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CRect rect;

	m_lstReport.GetWindowRect(&rect);	

	if(!rect.PtInRect(point)) 
		return;

	BCMenu rMenu;
	rMenu.LoadMenu(IDR_CONTEXT_MENU);
	BCMenu *pRMenu = (BCMenu*)rMenu.GetSubMenu(31);


	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nGNo = m_lstReport.GetItemLong(pRecord);
	long nCNo = m_lstReport.GetItemLong2(pRecord);

	//if(nCNo > 0 && nGNo > 0)
	//	pRMenu->EnableMenuItem(ID_CORP_INSERT,  MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	/*
	if(nCNo > 0 && nGNo == 0)
	{
		m_bChangeToCorp = TRUE;
		pRMenu->SetMenuText(ID_CORP_INSERT, "���ΰ�����", MF_BYCOMMAND);
	}
	else if(nCNo == 0 && nGNo == 0)
	{
		m_bChangeToCorp = FALSE;
		pRMenu->SetMenuText(ID_CORP_INSERT, "���ΰ����", MF_BYCOMMAND);
	}
	*/

	pRMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);		
}

void COrderInsertDlg::RefreshOtherPhone(CString strPrePhone1, CXTPGridRecord *pPreRecord)
{
}

void COrderInsertDlg::OnCorpUpdate()
{
	/*
	long nIndex = m_cmbBranch.GetCurSel();

	if(nIndex < 0)
	{
		MessageBox("��� �Ͻ� ���縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectedRecord();

	if(pRecord == NULL)
		return;

	long nCNo = m_lstReport.GetItemLong2(pRecord);
	CString strPhone1 = m_lstReport.GetItemText(pRecord, 1);

	CBranchInfo *pBi = (CBranchInfo*)m_cmbBranch.GetItemData(nIndex);

	CSearchCorpDlg dlg;
	dlg.SetBranchInfo(pBi);

	if(dlg.DoModal() == IDOK)
	{
		CMkCommand cmd(m_pMkDb, "update_corp_customer_for_corder_order_insert");
		cmd.AddParameter(pBi->nCompany);
		cmd.AddParameter(nCNo);
		cmd.AddParameter(dlg.m_nGNo);

		if(cmd.Execute())
		{
			MessageBox("�������� ���ԵǾ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
			CheckRowValid(pRecord);
			RefreshOtherPhone(strPhone1, pRecord);
		}
	}

	m_lstReport.Populate();
	*/
}

void COrderInsertDlg::OnCorpInsert()
{
	/*
	if(m_bChangeToCorp)
	{
		OnCorpUpdate();
		return;
	}

	long nIndex = m_cmbBranch.GetCurSel();

	if(nIndex < 0)
	{
		MessageBox("��� �Ͻ� ���縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CXTPGridRecord *pRecord = m_lstReport.GetFirstSelectRecord();

	if(pRecord == NULL)
		return;

	long nGNo = m_lstReport.GetItemLong(pRecord);
	long nCNo = m_lstReport.GetItemLong2(pRecord);

	CBranchInfo *pBi = (CBranchInfo*)m_cmbBranch.GetItemData(nIndex);

	CSearchCorpDlg dlg;
	dlg.SetBranchInfo(pBi);

	if(dlg.DoModal() == IDOK)
	{
		CVarietyDlg dlg1;
		dlg1.m_strTitleDlg = "������ �Է��ϼ���";

		if(dlg1.DoModal() != IDOK)
			return;

		CString strLocation = m_lstReport.GetItemText(pRecord, COL_DEST);
		CString strPhone1 = m_lstReport.GetItemText(pRecord, COL_TEL);
		CString strMemo = m_lstReport.GetItemText(pRecord, COL_MEMO);

		CMkCommand cmd(m_pMkDb, "insert_corp_customer_for_corder_order_insert_1");
		cmd.AddParameter(pBi->nCompany);
		cmd.AddParameter(dlg1.m_strValue);
		cmd.AddParameter(strLocation);
		cmd.AddParameter(strMemo);
		cmd.AddParameter(strPhone1);
		cmd.AddParameter(dlg.m_nGNo);

		if(cmd.Execute())
		{
			MessageBox("���ΰ����� ��ϵǾ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
			CheckRowValid(pRecord);
			RefreshOtherPhone(strPhone1, pRecord);
		}
	}

	m_lstReport.Populate();
	*/
}

void COrderInsertDlg::OnDelete()
{
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();
	CXTPGridSelectedRows *pRows = m_lstReport.GetSelectedRows();

	long nCount = pRows->GetCount();

	for(int i=0; i<nCount; i++)
	{		
		CXTPGridRecord *pRecord = pRows->GetAt(i)->GetRecord();;
		pRecords->RemoveRecord(pRecord);
	}

	m_lstReport.Populate();
}

void COrderInsertDlg::OnRefreshState()
{
}


void COrderInsertDlg::OnCbnSelchangeBranchCombo()
{
}

void COrderInsertDlg::OnBnClickedOrderInsertBtn()
{
	CXTPGridRecord *pSelRecord = m_lstReport.GetFirstSelectedRecord();

	if(pSelRecord == NULL)
		return;

	CBranchInfo *pBi = NULL;

	if(m_cmbBranch.GetCount() > 0)
	{
		long nIndex = m_cmbBranch.GetCurSel();

		if(nIndex < 0)
		{
			MessageBox("��� �Ͻ� ���縦 �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
			return;
		}
		pBi = (CBranchInfo*)m_cmbBranch.GetItemData(nIndex);
	}
	else
	{
		pBi = GetCurBranchInfo();
	}

	if(pBi == NULL)
	{
		MessageBox("��� �Ͻ� ���簡 �����ϴ�.", "Ȯ��", MB_ICONINFORMATION);
		return;
	}
	
	CXTPGridRecords *pRecords = m_lstReport.GetRecords();

	long nCount = 0;

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strPhone = pRecord->GetItem(4)->GetCaption(NULL);
		CString strMobile = pRecord->GetItem(5)->GetCaption(NULL);

		if(strPhone.GetLength() <= 6 && strMobile.GetLength() <= 6)
		{
			MessageBox("������ ������ ��� �����ʽ��ϴ�.\r\n�Ƿ����� ��ȭ��ȣ�� �Է��ϼ���", "Ȯ��", MB_ICONINFORMATION);
			return;
		}

		nCount++;
	}

	if(nCount > 500)
	{
		MessageBox("500���̻��� �Է� �ϽǼ� �����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CString strTemp = ""; strTemp.Format("%d���� ��� �Ͻðڽ��ϱ�?", nCount);

	if(MessageBox(strTemp, "Ȯ��", MB_OKCANCEL) != IDOK)
		return;

	long  nInsertCount = 0;

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);

		CString strDate = m_lstReport.GetItemText(pRecord, 0);
		CString strOCompany = m_lstReport.GetItemText(pRecord, 1);
		CString strODepart = m_lstReport.GetItemText(pRecord, 2);
		CString strOName = m_lstReport.GetItemText(pRecord, 3);
		CString strOPhone = m_lstReport.GetItemText(pRecord, 4);
		CString strOMobile = m_lstReport.GetItemText(pRecord, 5);
		CString strOLocation = m_lstReport.GetItemText(pRecord, 6);
		CString strOMemo = m_lstReport.GetItemText(pRecord, 7);
		CString strSCompany = m_lstReport.GetItemText(pRecord, 8);
		CString strSDepart = m_lstReport.GetItemText(pRecord, 9);
		CString strSName = m_lstReport.GetItemText(pRecord, 10);
		CString strSPhone = m_lstReport.GetItemText(pRecord, 11);
		CString strSMobile = m_lstReport.GetItemText(pRecord, 12);
		CString strSLocation = m_lstReport.GetItemText(pRecord, 13);
		CString strDCompany = m_lstReport.GetItemText(pRecord, 14);
		CString strDDepart = m_lstReport.GetItemText(pRecord, 15);
		CString strDName = m_lstReport.GetItemText(pRecord, 16);
		CString strDPhone = m_lstReport.GetItemText(pRecord, 17);
		CString strDMobile = m_lstReport.GetItemText(pRecord, 18);
		CString strDLocation = m_lstReport.GetItemText(pRecord, 19);
		CString strPayType = m_lstReport.GetItemText(pRecord, 20);
		CString strCarType = m_lstReport.GetItemText(pRecord, 21);
		CString strWayType = m_lstReport.GetItemText(pRecord, 22);
		CString strRunType = m_lstReport.GetItemText(pRecord, 23);
		CString strChageBasic = m_lstReport.GetItemText(pRecord, 24);
		CString strChargeAdd = m_lstReport.GetItemText(pRecord, 25);
		CString strChargeDis = m_lstReport.GetItemText(pRecord, 26);
		CString strChargeTran = m_lstReport.GetItemText(pRecord, 27);
		CString strEtc = m_lstReport.GetItemText(pRecord, 28);

		
		if(strOPhone.GetLength() <= 6 && strDMobile.GetLength() <= 7)
			continue;

		CMkCommand cmd(m_pMkDb, "insert_order_user");
		CMkParameter *pParRet = cmd.AddParameter(typeLong, typeReturn, 0);
		cmd.AddParameter(pBi->nCompanyCode);
		cmd.AddParameter(strDate);
		cmd.AddParameter(strOCompany);
		cmd.AddParameter(strODepart);
		cmd.AddParameter(strOName);
		cmd.AddParameter(strOPhone);
		cmd.AddParameter(strOMobile);
		cmd.AddParameter(strOLocation);
		cmd.AddParameter(strOMemo);

		cmd.AddParameter(strSCompany);
		cmd.AddParameter(strSDepart);
		cmd.AddParameter(strSName);
		cmd.AddParameter(strSPhone);
		cmd.AddParameter(strSMobile);
		cmd.AddParameter(strSLocation);

		cmd.AddParameter(strDCompany);
		cmd.AddParameter(strDDepart);
		cmd.AddParameter(strDName);
		cmd.AddParameter(strDPhone);
		cmd.AddParameter(strDMobile);
		cmd.AddParameter(strDLocation);

		cmd.AddParameter(strPayType);
		cmd.AddParameter(strCarType);
		cmd.AddParameter(strWayType);
		cmd.AddParameter(strRunType);
		cmd.AddParameter(strChageBasic);
		cmd.AddParameter(strChargeAdd);
		cmd.AddParameter(strChargeDis);
		cmd.AddParameter(strChargeTran);
		cmd.AddParameter(strEtc);

		cmd.AddParameter(m_ui.nWNo);
		cmd.AddParameter(m_ui.nCompany);
		cmd.AddParameter(m_ui.strName);

		if(!cmd.Execute())
		{
			MessageBox("��������� �����Ͽ����ϴ�.\r\n�ٽ� �õ��� �ּ���", "Ȯ��", MB_ICONINFORMATION);
			return;
		}

		long nRet;
		pParRet->GetValue(nRet);

		if(nRet == 1)
		{
			MessageBox("�����ð��� ��¥���Ŀ� ���� �ʽ��ϴ�.\r\n������Ͽ� �����߽��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
			return;
		}

		nInsertCount++;
	}

	if(nInsertCount > 0)
	{
		MessageBox("��ϵǾ����ϴ�", "Ȯ��", MB_ICONINFORMATION);
		OnOK();
	}
}
