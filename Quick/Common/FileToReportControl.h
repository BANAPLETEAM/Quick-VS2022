#pragma once

#include "msado27.tlh"

class CFileToReportControl
{
public:
	CFileToReportControl(void);
	~CFileToReportControl(void);

private:
	CXTPListCtrl2 *m_pReportControl;
	CComboBox *m_pCombo;
	CEdit *m_pEdit;

	CString m_strPath;
	CString m_strConnection;
	BOOL m_bConnected;
	ADODB::_Connection * m_pConnection; 
	ADODB::Fields *m_fields;
	ADODB::_RecordsetPtr   m_pRs;

	ATLMAP_PHONE m_atlmapPhone;

public:
	void LoadExcel();
	BOOL ReadExcel();
	void ReadSheet();
	void LoadText();
	void SetControl(CXTPListCtrl2 *pControl, CComboBox *pCombo, CEdit *pEdit);
	void AddText();

	
	//지역변수 리턴으로 주석처리 //by mksong (2013-01-02 오전 8:52)
	ATLMAP_PHONE* GetPhoneMap();
};

