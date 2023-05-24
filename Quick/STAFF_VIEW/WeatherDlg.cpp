// WeatherDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "WeatherDlg.h"



// CWeatherDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CWeatherDlg, CMyDialog)
CWeatherDlg::CWeatherDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWeatherDlg::IDD, pParent)
{
}

CWeatherDlg::~CWeatherDlg()
{
}

void CWeatherDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
	DDX_Control(pDX, IDC_DO_COMBO, m_DoCmb);
	DDX_Control(pDX, IDC_SI_COMBO, m_SiCmb);
	DDX_Control(pDX, IDC_YEAR_COMBO, m_YearCmb);
	DDX_Control(pDX, IDC_MONTH_COMBO, m_MonthCmb);
	DDX_Control(pDX, IDC_REFRESH_BTN, m_RefreshBtn);
}


BEGIN_MESSAGE_MAP(CWeatherDlg, CMyDialog)
	ON_BN_CLICKED(IDC_REFRESH_BTN, OnBnClickedRefreshBtn)
	ON_CBN_SELCHANGE(IDC_DO_COMBO, OnCbnSelchangeDoCombo)
	ON_CBN_SELCHANGE(IDC_SI_COMBO, OnCbnSelchangeSiCombo)
END_MESSAGE_MAP()


void CWeatherDlg::OnBnClickedRefreshBtn()
{
	RefreshSite();
}

void CWeatherDlg::RefreshSite()
{
	m_Http.Init();
	m_Http.SetConnectInfo("630.co.kr",80,"past/past.htm"); 

	CString strDo, strSi,strYear, strMonth;

	strSi = (CString)(LPTSTR)m_SiCmb.GetItemData(m_SiCmb.GetCurSel());

	m_DoCmb.GetLBText(m_DoCmb.GetCurSel(), strDo);
	m_YearCmb.GetLBText(m_YearCmb.GetCurSel(), strYear);
	m_MonthCmb.GetLBText(m_MonthCmb.GetCurSel(), strMonth);
	

	//?strDo_nm=������&member_nm=108&sYear=2008&sMonth=01

	m_Http.AddParamValue("strDo_nm",strDo);
	m_Http.AddParamValue("member_nm",strSi);
	m_Http.AddParamValue("sYear",strYear);
	m_Http.AddParamValue("sMonth",strMonth);

	if(0 != m_Http.Call()) {
		MessageBox("������ �̻�", "Ȯ��", MB_ICONINFORMATION);
		return;
	}

	CString sHtml = "";
	CString sInfo = (char*)m_Http.GetResponse();	

	long nStartIndex = sInfo.Find("<!-- ���Ȳ ��� ����â ���� -->", 0);
	long nStartIndex1 = sInfo.Find("<table", nStartIndex+1);
	long nStartRealIndex = sInfo.Find("<table", nStartIndex1+1); // �ι�° ���̺� ���ۺ���

	long nDestIndex = sInfo.Find("<!-- ���Ȳ ��� ����â �� -->");

	sHtml = sInfo.Mid(nStartRealIndex, nDestIndex - nStartRealIndex);
    
	sHtml = "<link href=\"http://www.630.co.kr/css/css.css\" rel=\"stylesheet\" type=\"text/css\">" + sHtml;
	sHtml = "<script LANGUAGE=JavaScript src=\"http://www.630.co.kr/menu2.js\"><!--//-->	</script>" + sHtml;

 	CString sCity = (CString)(LPTSTR)m_SiCmb.GetItemData(m_SiCmb.GetCurSel()); 
   
	//<td width=58, align = center >����</td> <td width=58, align = center >����</td> <td width=58, align = center>��</td>

   	CString sToday = "<table border = 0> <tr height = 20> <td> </td> <td width = 173 > <table width = 173, border = 0> <tr> <td width=58, align = right>����</td> <td width=58, align = center >����</td> <td width=58, align = left>��</td> </tr> </table> </td> <td> </td> </tr>";
	sToday += "<tr> <td width = 255></td> <td align = center, width = 173>";
	sToday += "<script language=\"javascript\">flashWrite(\"http://www.630.co.kr/include/flash/silhwang.swf?dataPath=http://www.630.co.kr/data/leftSwf";
	sToday += sCity + ".txt\",\"173\",\"60\",\"a\",\"\",\"transparent\")</script>";
	sToday += "<td width = 250></td> </tr></table> ";

	sHtml = sToday + sHtml;

	sHtml = "<script language=\"javascript\" src=\"http://www.630.co.kr/include/flash/flashWrite.js\"></script>" + sHtml;
	sHtml = "<script LANGUAGE=\"JavaScript\" src=\"http://www.630.co.kr/include/leftweather.js\"></script>" + sHtml;

	sHtml.Replace("img src=\"../", "img src=\"http://www.630.co.kr/");
	sHtml.Replace("img src=\"image", "img src=\"http://www.630.co.kr/past/image");
	sHtml.Replace("flashWrite(\"../", "flashWrite(\"http://www.630.co.kr/");


	MakeFile(sHtml);
}

void CWeatherDlg::MakeFile(CString sHtml)
{
	CFileFind findfile;
	CString sFolder = "c:\\SmartQ\\*.*";
					   
	BOOL bFind = findfile.FindFile(sFolder);
	BOOL bFindFile = FALSE;

	if(bFind)
	{
		while(bFind)
		{
			bFind = findfile.FindNextFile();

			if(findfile.IsDots())
				continue;

			CString str = findfile.GetFileName();

			if(str.Find("weather") >=0)
			{
				bFindFile = TRUE;
				break;
			}
		}
	}
	
	if(!bFindFile)
		CFile file(_T("c:\\SmartQ\\weather.html"), CFile::modeCreate | CFile::modeWrite);

	FILE* fp = NULL;
	fp = fopen("c:\\SmartQ\\weather.html", "wt");

	if(fp == NULL)
		return;

	fprintf(fp, sHtml);

	fclose(fp);

	m_Explorer.Navigate("c:\\SmartQ\\weather.html", NULL, NULL, NULL, NULL);

//	Sleep(1000);
//	DeleteFile("C:\\weather.html");
}

BOOL CWeatherDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	BOOL bSelect = FALSE;

	long nDo = AfxGetApp()->GetProfileInt("City", "nDo", 0);
	long nCity = AfxGetApp()->GetProfileInt("City", "nCity", 0);

	m_DoCmb.SetCurSel(nDo);

	OnCbnSelchangeDoCombo();

	m_SiCmb.SetCurSel(nCity);

	COleDateTime dtCurrent = COleDateTime::GetCurrentTime();
	long nYear = dtCurrent.GetYear();

	char buffer[10];

	for(int i=0; i<7; i++)
        m_YearCmb.InsertString(i, (CString)itoa(nYear--, buffer, 10));

	m_YearCmb.SetCurSel(0);

	for(int i=0; i<12; i++)
	{
		if(i<9)
			m_MonthCmb.InsertString(i, "0" + (CString)itoa(i+1, buffer, 10));
		else
			m_MonthCmb.InsertString(i, (CString)itoa(i+1, buffer, 10));


		if(dtCurrent.GetMonth() == i+1)
			m_MonthCmb.SetCurSel(i);
	}

	RefreshSite();		

	//������;��û����;��û�ϵ�;������;���󳲵�;����ϵ�;��󳲵�;���ϵ�;���ֵ�;

	return TRUE;
}

void CWeatherDlg::OnCbnSelchangeDoCombo()
{
	CString strDo;
	long index = m_DoCmb.GetCurSel();
	m_DoCmb.GetLBText(index, strDo);
	strDo.Replace(" ", "");

	AfxGetApp()->WriteProfileInt("City", "nDo", index);

	for(int i=0; i<m_SiCmb.GetCurSel(); i++)
		m_SiCmb.DeleteString(i);

	long nItem = 0;
	
	if(strDo == "������")
	{
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"108");
		m_SiCmb.InsertString(nItem, "��  õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"112");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"119");
		m_SiCmb.InsertString(nItem, "����õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"098");
		m_SiCmb.InsertString(nItem, "��  õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"203");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"202");
		m_SiCmb.InsertString(nItem, "��  ȭ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"201");

	}
	else if(strDo == "��û����")
	{
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"133");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"236");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"235");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"129");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"238");
		m_SiCmb.InsertString(nItem, "õ  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"232");
	}
	else if(strDo == "��û�ϵ�")
	{		
		m_SiCmb.InsertString(nItem, "û  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"131");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"127");
		m_SiCmb.InsertString(nItem, "��  õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"221");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"226");
		m_SiCmb.InsertString(nItem, "��ǳ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"135");
	}
	else if(strDo == "������")
	{
		m_SiCmb.InsertString(nItem, "��  õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"101");
		m_SiCmb.InsertString(nItem, "ö  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"095");
		m_SiCmb.InsertString(nItem, "ȫ  õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"212");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"114");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"121");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"105");
		m_SiCmb.InsertString(nItem, "�����"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"100");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"216");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"090");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"211");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"115");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"106");

	}
	else if(strDo == "���󳲵�" )
	{
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"156");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"164");
		m_SiCmb.InsertString(nItem, "��  õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"256");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"260");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"262");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"168");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"170");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"261");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"165");
		m_SiCmb.InsertString(nItem, "��굵"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"169");
	}
	else if(strDo == "����ϵ�" )
	{
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"146");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"140");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"243");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"245");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"244");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"248");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"247");
	}
	else if(strDo == "��󳲵�")
	{
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"159");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"155");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"288");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"152");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"192");
		m_SiCmb.InsertString(nItem, "��  â"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"284");
		m_SiCmb.InsertString(nItem, "��  õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"285");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"162");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"294");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"295");
		m_SiCmb.InsertString(nItem, "��  û"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"289");
	}
	else if(strDo == "���ϵ�")
	{
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"143");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"138");
		m_SiCmb.InsertString(nItem, "��  õ"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"281");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"279");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"278");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"273");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"136");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"277");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"272");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"271");
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"130");
	}
	else if(strDo == "���ֵ�")
	{
		m_SiCmb.InsertString(nItem, "��  ��"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"184");
		m_SiCmb.InsertString(nItem, "������"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"265");
		m_SiCmb.InsertString(nItem, "������"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"189");
		m_SiCmb.InsertString(nItem, "���ְ���"); m_SiCmb.SetItemData(nItem++, (DWORD_PTR)"185");
	}

	m_SiCmb.SetCurSel(0);
}

BOOL CWeatherDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_RBUTTONDOWN)
    {
		CRect rect;
		m_Explorer.GetClientRect(&rect);

		CPoint pt;
		GetCursorPos(&pt);

		m_Explorer.ScreenToClient(&pt);

		if(rect.PtInRect(pt))
			return TRUE;
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}
BEGIN_MESSAGE_MAP(CExplorer1, CExplorer)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void CExplorer1::OnRButtonDown(UINT nFlags, CPoint point)
{
	return;

	CExplorer::OnRButtonDown(nFlags, point);
}

void CWeatherDlg::OnCbnSelchangeSiCombo()
{
	AfxGetApp()->WriteProfileInt("City", "nCity", m_SiCmb.GetCurSel());
}
