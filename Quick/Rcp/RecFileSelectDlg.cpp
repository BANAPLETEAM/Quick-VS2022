// RecFileSelectDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "RecFileSelectDlg.h"


// CRecFileSelectDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRecFileSelectDlg, CDialog)

CRecFileSelectDlg::CRecFileSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecFileSelectDlg::IDD, pParent)
{

}

CRecFileSelectDlg::~CRecFileSelectDlg()
{
	CXTPGridRecords *pRecords = m_lst.GetRecords();
	long nCount = pRecords->GetCount();

	for(int i=0; i<nCount; i++)
	{
		ST_REC_FILE *st = (ST_REC_FILE*)m_lst.GetItemData(i);
		delete st;
		st = NULL;
	}
}

void CRecFileSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORT, m_lst);
}


BEGIN_MESSAGE_MAP(CRecFileSelectDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORT, OnReportItemDblClick)
END_MESSAGE_MAP()


// CRecFileSelectDlg 메시지 처리기입니다.

BOOL CRecFileSelectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lst.InsertColumn(0, "날짜", LVCFMT_CENTER, 100);
	m_lst.InsertColumn(1, "키폰ID", LVCFMT_RIGHT, 50);
	m_lst.InsertColumn(2, "접수자", LVCFMT_LEFT, 80);
	m_lst.Populate();

	CMkRecordset rs(m_pMkDb);
	CMkCommand cmd(m_pMkDb, "select_record_file_from_phone");
	cmd.AddParameter(m_nCompany);
	cmd.AddParameter(m_dtDate);
	cmd.AddParameter(m_strPhone);

	if(!rs.Execute(&cmd))
		return FALSE;

	long nRecordCount = rs.GetRecordCount();

	for(int i=0; i<nRecordCount; i++)
	{
		ST_REC_FILE *st = new ST_REC_FILE;
		rs.GetFieldValue("dtRegister", st->dtDate);
		rs.GetFieldValue("sKeyPhoneID", st->strKeyPhoneID);
		rs.GetFieldValue("sFileName", st->strFileName);
		rs.GetFieldValue("nType", st->nBound);
		rs.GetFieldValue("sOperator", st->strOperator);

		m_lst.InsertItem(i, st->dtDate.Format("%m-%d %H:%M:%S"));
		m_lst.SetItemText(i, 1, st->strKeyPhoneID);
		m_lst.SetItemText(i, 2, st->strOperator);
		m_lst.SetItemData(i, (DWORD_PTR)st);

		rs.MoveNext();
	}

	m_lst.Populate();

	if(nRecordCount == 0)
		OnCancel();

	if(nRecordCount == 1)
	{
		if(!LF->POWER_CHECK(1951, "파일 재생"))
		{
			CXTPGridRecord *pRecord = m_lst.GetRecords()->GetAt(0);
			ST_REC_FILE *st = (ST_REC_FILE*)m_lst.GetItemData(pRecord);

			if(st->strOperator == m_ui.strName)
			{
				if(!LF->POWER_CHECK(1953, "본인 녹취 듣기", TRUE))
					return TRUE;
			}
			else
			{
				MessageBox("녹취 파일듣기 권한이 없습니다.", "확인", MB_ICONINFORMATION);
				return TRUE;
			}
		}

		SelectRecord(m_lst.GetRows()->GetAt(0)->GetRecord());
	}


	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRecFileSelectDlg::SelectRecord(CXTPGridRecord *pRecord)
{
	ST_REC_FILE *st = (ST_REC_FILE*)m_lst.GetItemData(pRecord);

	m_dtRetDate = st->dtDate;
	m_strRetKeyPhoneID = st->strKeyPhoneID;
	m_strRetFileName = st->strFileName;
	m_nRetBound = st->nBound;

	OnOK();
}


void CRecFileSelectDlg::OnReportItemDblClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	CXTPGridRecord *pRecord = m_lst.GetFirstSelectedRecord();

	if(pRecord != NULL)
	{
		ST_REC_FILE *st = (ST_REC_FILE*)m_lst.GetItemData(pRecord);

		if(!LF->POWER_CHECK(1951, "파일 재생"))
		{
			if(st->strOperator == m_ui.strName)
			{
				if(!LF->POWER_CHECK(1953, "본인 녹취 듣기", TRUE))
					return;
			}
			else
			{
				MessageBox("녹취 파일듣기 권한이 없습니다.", "확인", MB_ICONINFORMATION);
				return;
			}
		}

		SelectRecord(pRecord);
	}
}
