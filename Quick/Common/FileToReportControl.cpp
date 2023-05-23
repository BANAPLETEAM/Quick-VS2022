#include "StdAfx.h"
#include "FileToReportControl.h"

CFileToReportControl::CFileToReportControl(void)
{
	m_strPath = "";
	m_strConnection = "";
	m_bConnected = FALSE;

	CoInitialize(NULL);
	::CoCreateInstance(ADODB::CLSID_Connection, NULL, CLSCTX_ALL, ADODB::IID__Connection, (void**)&m_pConnection);	
}

CFileToReportControl::~CFileToReportControl(void)
{
	if(m_bConnected )
	{	
		if(m_pConnection)  // 정상적으로 끊어질때...
			m_pConnection->Close();	
	}
}

void CFileToReportControl::SetControl(CXTPListCtrl2 *pControl, CComboBox *pCombo, CEdit *pEdit)
{
	m_pReportControl = pControl;
	m_pCombo = pCombo;
	m_pEdit = pEdit;
}

void CFileToReportControl::LoadExcel()
{
	CWaitCursor wait;	// Set clock cursor;

	try
	{
		if(m_bConnected)	
		{
			if(AfxMessageBox("현재 열린 문서를 닫으시겠습니까?", MB_OKCANCEL) == IDOK)
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
			_T("Excel Files (*.xls)(*.xlsx)(*.mdb)|;*.xls;*.mdb;*.xlsx"), NULL );	
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
		AfxMessageBox(Msg, MB_ICONERROR);
	}
	catch(_com_error error)
	{
		AfxMessageBox( error.Description(), MB_OK|MB_ICONERROR);
		m_strPath = "";
	}

	ReadExcel();
}

BOOL CFileToReportControl::ReadExcel()
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

		m_pCombo->ResetContent();

		while (VARIANT_TRUE != Rs1->GetadoEOF())
		{
			strTemp = LF->ChangeStringFromExcel(Rs1->Fields->GetItem(_variant_t((long)2))->Value);

			m_pCombo->AddString(strTemp);
			Rs1->MoveNext();
		}
		Rs1->Close();

		if(m_pCombo->GetCount() > ZERO)
		{
			m_pCombo->SetCurSel(ZERO);
			ReadSheet();
		}

		return TRUE;
	}
	catch(_com_error error)
	{
		AfxMessageBox(error.Description(), MB_OK|MB_ICONERROR);
		return FALSE;
	}
}

void CFileToReportControl::ReadSheet()
{
	long nIndex = m_pCombo->GetCurSel();

	if(nIndex < 0)
	{
		AfxMessageBox("불러올 시트를 선택하세요", MB_ICONINFORMATION);
		return;
	}

	HRESULT hr = 0;
	ADODB::_Recordset *pPreviewSheetSet= NULL;
	CString strTable;//  = "KOREA1$";

	m_pCombo->GetLBText(nIndex, strTable);
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

		if(pListRecordset->Open(_bstr_t(strQuery), _variant_t((IDispatch *) m_pConnection, true), 
			ADODB::adOpenStatic,ADODB::adLockOptimistic, ADODB::adCmdText) == S_OK) 
		{
			long nRecordCount = pListRecordset->GetRecordCount();
			for(long nRow = 0; nRow < nRecordCount; nRow++)
			{
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

					if(LF->IsMobilePhoneNumber(strVal))
						m_pReportControl->InsertItem(nRow, strVal);
				} // col 돌리기

				pListRecordset->MoveNext();
			}

			pListRecordset->Close();
			pListRecordset->Release();
		}
	}

	m_pReportControl->Populate();
}

void CFileToReportControl::LoadText()
{
	CFileDialog dlg( TRUE, "", m_strPath,
		OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
		_T("Excel Files (*.txt)|;*.txt"), NULL );	
	dlg.m_ofn.lpstrInitialDir = m_strPath;	
	dlg.m_ofn.lpstrTitle = _T("파일형식 맞는 파일을 선택하세요.");
	if(dlg.DoModal() != IDOK)
		return;		
	POSITION pos = dlg.GetStartPosition();
	m_strPath = dlg.GetNextPathName(pos);

	if(m_strPath.GetLength() == 0)
	{
		AfxMessageBox("파일이름이 없거나 선택이 되지 않았습니다.", MB_ICONINFORMATION);
		return;
	}

	m_pReportControl->DeleteAllItems();
	long nItem = 0;

	TRY
	{
		CFile file; 
		CString strPhone;

		file.Open(m_strPath, CFile::modeRead);
		CArchive ar(&file, CArchive::load);

		while(ar.ReadString(strPhone))
		{
			if(LF->IsMobilePhoneNumber(strPhone))
				m_pReportControl->InsertItem(nItem++, strPhone);
		}

		file.Close();

		m_pReportControl->Populate();
	}
	CATCH_ALL(e)
	{
		AfxMessageBox("파일 오픈중 에러발생!!", MB_ICONERROR);
	}
	END_CATCH_ALL
}

void CFileToReportControl::AddText()
{
	CString strTemp;
	m_pEdit->GetWindowText(strTemp);

	if(!LF->IsMobilePhoneNumber(strTemp))
	{
		AfxMessageBox("휴대폰 번호를 입력하세요", MB_ICONERROR);
		return;
	}

	m_pReportControl->InsertItem(m_pReportControl->GetHeaderRecords()->GetCount(), strTemp);
	m_pReportControl->Populate();
}

ATLMAP_PHONE* CFileToReportControl::GetPhoneMap()
{
	m_atlmapPhone.RemoveAll();

	CXTPGridRecords *pRecords = m_pReportControl->GetRecords();

	for(int i=0; i<pRecords->GetCount(); i++)
	{
		CXTPGridRecord *pRecord = pRecords->GetAt(i);
		CString strTemp = pRecord->GetItem(0)->GetCaption(NULL);

		m_atlmapPhone.SetAt(atoi(strTemp), strTemp);
	}

	return &m_atlmapPhone;
}
