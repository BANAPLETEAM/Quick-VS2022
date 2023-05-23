// WebGroupReportDetailDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "WebGroupReportDetailDlg.h"
#include <afxinet.h>
#include "CustomerGroup.h"


// CWebGroupReportDetailDlg 대화 상자입니다.
//IMPLEMENT_DYNCREATE(COptionDlgGeneral, CMyFormView)
IMPLEMENT_DYNCREATE(CWebGroupReportDetailDlg, CMyFormView)
 
CWebGroupReportDetailDlg::CWebGroupReportDetailDlg(CWnd* pParent /*=NULL*/)
	: CMyFormView(CWebGroupReportDetailDlg::IDD)
{
	m_strTitle = "";
}

CWebGroupReportDetailDlg::~CWebGroupReportDetailDlg()
{
	TRACE("~CWebGroupReportDetailDlg:m_sTitle=%s\r\n", m_strTitle);
}

void CWebGroupReportDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
	DDX_Control(pDX, IDC_INCLUDE_ORDER_CHECK, m_chkIncludeOrder);
	DDX_Control(pDX, IDC_NOT_INCLUDE_ORDER_CHECK, m_chkNotIncludeOrder);

	int nCount = sizeof(m_bSelect)/sizeof(m_bSelect[0]);
	for(int i=0; i< nCount; i++)
		DDX_Check(pDX, IDC_COLUMN_CHECK0 + i, m_bSelect[i]);

}


BEGIN_MESSAGE_MAP(CWebGroupReportDetailDlg, CMyFormView)
	ON_BN_CLICKED(IDC_INCLUDE_ORDER_CHECK, OnBnClickedIncludeOrderCheck)
	ON_BN_CLICKED(IDC_NOT_INCLUDE_ORDER_CHECK, OnBnClickedNotIncludeOrderCheck)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_WM_MOUSEACTIVATE()
	ON_BN_CLICKED(IDC_REFRESH_BTN2, OnBnClickedRefreshBtn2)
	ON_BN_CLICKED(IDC_REFRESH_BTN3, OnBnClickedRefreshBtn3)
	ON_BN_CLICKED(IDC_REFRESH_BTN4, OnBnClickedRefreshBtn4)
	ON_BN_CLICKED(IDC_REFRESH_BTN5, OnBnClickedRefreshBtn5)
	ON_BN_CLICKED(IDC_EXCEL_BTN, OnBnClickedExcelBtn)
END_MESSAGE_MAP()



void CWebGroupReportDetailDlg::OnBnClickedIncludeOrderCheck()
{
	if(m_chkIncludeOrder.GetCheck())
		m_chkNotIncludeOrder.SetCheck(FALSE);
	else
		m_chkNotIncludeOrder.SetCheck(TRUE);

	InitCheckBox(TRUE);
}

void CWebGroupReportDetailDlg::InitCheckBox(BOOL bEnable)
{
	for(int i=0; i<21; i++)
	{
		CButton *pButton = (CButton*)GetDlgItem(IDC_COLUMN_CHECK0 + i);
		pButton->EnableWindow(bEnable);
	}

}

void CWebGroupReportDetailDlg::OnBnClickedNotIncludeOrderCheck()
{
	if(m_chkNotIncludeOrder.GetCheck())
		m_chkIncludeOrder.SetCheck(FALSE);
	else
		m_chkIncludeOrder.SetCheck(TRUE);

	InitCheckBox(FALSE);
}

void CWebGroupReportDetailDlg::OnBnClickedRefreshBtn()
{
	Refresh();
}

void CWebGroupReportDetailDlg::Refresh()
{
	UpdateData(TRUE);

	/*
	CString sData = "";
	char buffer[20];

	for(int i=0; i<21; i++)
		sData += (CString)itoa(m_bSelect[i], buffer, 10) + ";"; 
  
	CString sFor = "work.logisoft.co.kr:8000/GroupReport/GroupReport_Temp.asp?nID=" + (CString)itoa(m_nID, buffer, 10) + "&bShowOrder=" + (CString)itoa(m_chkIncludeOrder.GetCheck(), buffer, 10) + "&sColumn=" + sData;
 	CString sFor1 = "GroupReport/GroupReport_Temp.asp?nID=" + (CString)itoa(m_nID, buffer, 10) + "&bShowOrder=" + (CString)itoa(m_chkIncludeOrder.GetCheck(), buffer, 10) + "&sColumn=" + sData;
	//http://work.logisoft.co.kr:8000/GroupReport/GroupReport_Temp.asp?nID=205378&bShowOrder=1&sColumn=1;0;0;0;0;1;1;1;0;0;1;0;0;1;0;1;0;0;0;0;0;
	m_Http.Init();   
	m_Http.SetConnectInfo("http://work.logisoft.co.kr", 80000, sFor1, 1);

	if(0 != m_Http.Call()) {
		MessageBox("웹서버 이상", "확인", MB_ICONINFORMATION);
		return ;
	}

	CString sInfo = (char*)m_Http.GetResponse();

	CString sFullName = "c:\\SmartQ\\그룹정산\\" + m_sTitle + ".html";
	//GetValueFileName(sFullName);

	if(MakeFile(sInfo, m_sTitle))
		m_Explorer.Navigate(sFor, NULL, NULL, NULL, NULL);  
	*/

		CString sData = "";
	char buffer[20];

	for(int i=0; i<21; i++)
		sData += (CString)itoa(m_bSelect[i], buffer, 10) + ";"; 
  
	CString sFor = "http://work.logisoft.co.kr:8000/GroupReport/GroupReport_Temp.asp?nID=" + (CString)itoa(m_nID, buffer, 10) + "&bShowOrder=" + (CString)itoa(m_chkIncludeOrder.GetCheck(), buffer, 10) + "&sColumn=" + sData;
 	CString sFor1 = "GroupReport/GroupReport_Temp.asp?nID=" + (CString)itoa(m_nID, buffer, 10) + "&bShowOrder=" + (CString)itoa(m_chkIncludeOrder.GetCheck(), buffer, 10) + "&sColumn=" + sData;

	CInternetSession session;

	try {

		//CInternetFile *p_html = (CInternetFile *)session.OpenURL(sFor1);
		CInternetFile *p_html = (CInternetFile *)session.OpenURL(sFor);

		if(p_html != NULL)
		{
			CString str, strSum;
			CString sResult;

			p_html->SetReadBufferSize(512);
			while(1)
			{
				if(!p_html->ReadString(str)) break;
				strSum += str;
			}

			p_html->Close();
			delete p_html;
			session.Close();

			//int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(LPCTSTR)strSum, -1, 0, 0);
			//MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(LPCTSTR)strSum ,  -1 , (LPWSTR)sResult.GetBuffer(nSize), nSize);

			if(MakeFile(strSum, m_strTitle))
				m_Explorer.Navigate(sFor, NULL, NULL, NULL, NULL);  
		}
	} catch(CInternetException *){
		CString sTemp;
		COleDateTime dtCur = COleDateTime::GetCurrentTime();
		sTemp.Format("[%s] 웹접속실패\r\n", dtCur.Format("%Y-%m-%d %H:%M:%S"));
	}	
}


BOOL CWebGroupReportDetailDlg::MakeFile(CString sHtml,CString sFileName)
{
	CFileFind findfile;
	CString sFolder = "c:\\SmartQ\\그룹정산\\*.*";
	CString FileName;

	BOOL bFind = findfile.FindFile(sFolder);
	BOOL bFindFile = FALSE;

	LF->CreateDir("c:\\SmartQ\\그룹정산");

	if(bFind)
	{
		while(bFind)
		{
			bFind = findfile.FindNextFile();

			if(findfile.IsDots())
				continue;

			CString str = findfile.GetFileName();

			if(str.Find(sFileName) >=0)
			{
				bFindFile = TRUE;
				break;
			}
		}
	}

	CString sFullName = "c:\\SmartQ\\그룹정산\\" + sFileName + ".html";

	if(!bFindFile)
		CFile file(_T(sFullName), CFile::modeCreate | CFile::modeWrite);

	FILE* fp = NULL;
	fp = fopen(sFullName, "wt");

	if(fp == NULL)
		return FALSE;

	fprintf(fp, sHtml);

	fclose(fp);

	return TRUE;

	//	m_Explorer.Navigate(sFullName, NULL, NULL, NULL, NULL);

	//	Sleep(1000);
	//	DeleteFile("C:\\weather.html");
}



// CWebGroupReportDetailDlg 메시지 처리기입니다.



void CWebGroupReportDetailDlg::OnInitialUpdate()
{
	CMyFormView::OnInitialUpdate();

	InitControl();
}

void CWebGroupReportDetailDlg::InitControl()
{
	CStringArray strColumn;
	strColumn.Copy(m_cg.GetGroupData(m_nGNo)->strColumnChk);

	long nSize = strColumn.GetSize();	

	if(nSize != 21)
		return;

	for(int i=0; i<21; i++)
		m_bSelect[i] = _ttoi(strColumn.GetAt(i));

	m_chkIncludeOrder.SetCheck(m_cg.GetGroupData(m_nGNo)->bShowOrder);

	UpdateData(FALSE);
}

int CWebGroupReportDetailDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return 0;
	return CMyFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CWebGroupReportDetailDlg::OnBnClickedRefreshBtn2()
{
	SetCheckBox(TRUE);
}

void CWebGroupReportDetailDlg::OnBnClickedRefreshBtn3()
{
	SetCheckBox(FALSE);
}

void CWebGroupReportDetailDlg::OnBnClickedRefreshBtn4()
{
	InitControl();
}

void CWebGroupReportDetailDlg::SetCheckBox(BOOL bCheck)
{
	for(int i=0; i<21; i++)
		m_bSelect[i] = bCheck;

	UpdateData(FALSE); 
}

void CWebGroupReportDetailDlg::OnBnClickedRefreshBtn5()
{
	UpdateData(TRUE);

	char buffer[20];

	CStringArray sColumn;


	for(int i=0; i<21; i++)
		sColumn.Add(itoa(m_bSelect[i], buffer, 10));

	ST_CUSTOMER_GROUP_INFOMATION * st = m_cg.GetGroupData(m_nGNo);

	st->bShowOrder = m_chkIncludeOrder.GetCheck();
	st->strColumnChk.Copy(sColumn);

	if(m_cg.SetGroupReportData(m_nGNo, st))
		MessageBox("저장되었습니다", "확인", MB_ICONINFORMATION);
	else
		MessageBox("저장중 에러발생!!", "확인", MB_ICONINFORMATION);

}

void CWebGroupReportDetailDlg::OnBnClickedExcelBtn()
{
	UpdateData(TRUE);
	char buffer[20];
    
	CString sData;
	for(int i=0; i<21; i++)
		sData += (CString)itoa(m_bSelect[i], buffer, 10) + ";";

	if(sData.Find("1") < 0)
	{
		MessageBox("최소 하나 항목이상 체크해 주세요", "확인", MB_ICONINFORMATION);
		return;
	}

	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "web_select_group_report_order_by_excel"); 

	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nID);		
	pCmd.AddParameter(typeString, typeInput, sData.GetLength(), sData);

	if(!pRs.Execute(&pCmd))
	{
		MessageBox("잠시후에 다시 시도하세요", "확인", MB_ICONINFORMATION);
		return;
	}

	if(!LF->POWER_CHECK(3900, "엑셀변환", TRUE))
		return;

	LF->AddSecurityLog(LF->GetCurBranchInfo()->nDOrderTable, 315, pRs.GetRecordCount());  
	CMyExcel::ToExcel(&pRs);

	pRs.Close();
}
