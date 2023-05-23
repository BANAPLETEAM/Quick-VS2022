// WebChargeListDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "WebChargeListDlg.h"

#include "SearchGroupDlg.h"
#include "CustomerGroup.h"

// CWebChargeListDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CWebChargeListDlg, CMyDialog)
CWebChargeListDlg::CWebChargeListDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CWebChargeListDlg::IDD, pParent)
{
	m_nCompany = 0;
	m_nDongID = 0;
	m_nChargeID = 0;
	m_nGNo= 0;
	m_nRow = 40;
	m_nCol = 7;
}

CWebChargeListDlg::~CWebChargeListDlg()
{
}

void CWebChargeListDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DONG_EDIT, m_edtDong);
	DDX_Control(pDX, IDC_DETAIL_EDIT, m_edtDongDetail);
	DDX_Control(pDX, IDC_CHARGELIST_COMBO, m_cmbChargeDongList);	
	DDX_Control(pDX, IDC_EXPLORER, m_Explorer);
	DDX_Control(pDX, IDC_TYPE_CHECK, m_chkType);
	DDX_Control(pDX, IDC_CHARGE_CHECK, m_chkCharge);	
	DDX_Control(pDX, IDC_CHARGE_EDIT, m_edtChargeName);
	DDX_Control(pDX, IDC_GROUP_EDIT, m_edtGroupName);
	DDX_Control(pDX, IDC_TYPE_COMBO, m_cmbType);
	DDX_Control(pDX, IDC_CARTYPE_COMBO, m_cmbCarType);

	DDX_Control(pDX, IDC_ONETHOUSAND_CHECK, m_chkOneThousand);	
	DDX_Control(pDX, IDC_DATAMODIFY_CHECK, m_chkModifyData);	
	DDX_Control(pDX, IDC_STANDART_CHECK, m_chkStandardCharge);	
	
	DDX_Control(pDX, IDC_EMAIL_EDIT, m_edtEmail);
	DDX_Control(pDX, IDC_TITLE_EDIT, m_edtTitle);
	DDX_Control(pDX, IDC_SENDEMAIL_EDIT, m_edtSendMailAddress);
	DDX_Control(pDX, IDC_CUSTOMERNAME_EDIT, m_edtCustomerName);
	DDX_Control(pDX, IDC_EXCEL_CHECK, m_chkExcel);
	DDX_Control(pDX, IDC_ROW_EDIT, m_edtRow);
	DDX_Control(pDX, IDC_COL_EDIT, m_edtCol);
}


BEGIN_MESSAGE_MAP(CWebChargeListDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CHARGELIST_LOAD_BTN, OnBnClickedChargelistLoadBtn)
	ON_BN_CLICKED(IDC_GROUP_INQUERY_BTN, OnBnClickedGroupInqueryBtn)
	ON_BN_CLICKED(IDC_CHARGE_INQUERY_BTN2, OnBnClickedChargeInqueryBtn2)
	ON_BN_CLICKED(IDC_EMAIL_BTN, OnBnClickedEmailBtn)
	ON_BN_CLICKED(IDC_STANDART_CHECK, OnBnClickedStandartCheck)
	ON_BN_CLICKED(IDC_EXCEL_CHECK, OnBnClickedExcelCheck)
	ON_BN_CLICKED(IDC_CHARGE_CHECK, OnBnClickedChargeCheck)
END_MESSAGE_MAP()


// CWebChargeListDlg �޽��� ó�����Դϴ�.

void CWebChargeListDlg::OnBnClickedGroupInqueryBtn()
{

	CSearchGroupDlg dlg;
	dlg.m_nCompany = LF->GetCurBranchInfo()->nPayTable;
	dlg.m_nDataType = SG_GROUP;
	if(dlg.DoModal() == IDOK)
	{
		m_nGNo = dlg.m_nGNo;
		if(m_nGNo > 0)
		{
			
			// Ÿ�Ծ˾ƿ���, ����� �˾ƿ��� 
			// �³� Ȯ���ϱ� �Ѹ���
			CMkRecordset pRs(m_pMkDb);
			CMkCommand pCmd(m_pMkDb, "select_get_group_info2");
			pCmd.AddParameter(m_nGNo);
			
			if(!pRs.Execute(&pCmd)) return;
			long nChargeID = 0, nType = 0, nDefaultDongID = 0;
			CString strChargeName = "", strDefaultDong = "", strDefaultDongDetail = "";

			for(int i = 0; i < pRs.GetRecordCount(); i++)
			{
				pRs.GetFieldValue("nChargeID", nChargeID);
				pRs.GetFieldValue("nType", nType);					
				pRs.GetFieldValue("sChargeName", strChargeName);
				pRs.GetFieldValue("nDefaultDongID", nDefaultDongID);					
				pRs.GetFieldValue("sDefaultDong", strDefaultDong);					
				pRs.GetFieldValue("sDefaultDongDetail", strDefaultDongDetail);	
			}
			pRs.Close();
			
		
			CString  strMsg = "", strGroupName = m_cg.GetGroupData(m_nGNo)->strGroupName;
			switch(nType)
			{
			case 0:
				strMsg = strGroupName + " �׷����� AŸ�� ���";
				break;
			case 1:
				strMsg = strGroupName + " �׷����� BŸ�� ���";
				break;
			case 2:
				strMsg = strGroupName + " �׷����� CŸ�� ���";
			    break;
			case 3:
				strMsg = strGroupName + " �׷����� DŸ�� ���";
			    break;
			default:
				strMsg = strGroupName + " �׷����� AŸ�� ���";
			    break;
			}
			BOOL bChangeDong = FALSE;
			if(strChargeName.GetLength() > 0)
			{
				strMsg += " ��  " + strChargeName +  " ������� ���"; 
				if(nDefaultDongID > 0 && strDefaultDong.GetLength() > 0 )
				{
					strMsg += "�ϸ�  �����(��)��  " + strDefaultDong + " ���� �ٲٽðڽ��ϱ�? ";
					bChangeDong = TRUE;
				}
				else
				{
					strMsg += " �Ͻðڽ��ϱ�? ";
				}
			}
			else
				strMsg += " ���� å���Ǹ� ��������� ���°� �½��ϱ�?";
			
			if(LF->MsgBox(strMsg, "Ȯ��", MB_ICONINFORMATION | MB_YESNO) == IDYES)
			{
				m_cmbType.SetCurSel(nType);
				m_edtGroupName.SetWindowText(strGroupName);
				m_edtChargeName.SetWindowText(nChargeID > 0 ? strChargeName : "");
				if(m_nGNo > 0)
					m_edtCustomerName.SetWindowText(strGroupName);

				m_nChargeID = nChargeID > 0 ? nChargeID : 0;
				m_chkCharge.SetCheck(nChargeID > 0 ? TRUE : FALSE);
				if(bChangeDong && nDefaultDongID > 0 )
				{
					m_nDongID = nDefaultDongID;
					m_edtDong.SetWindowText(strDefaultDong);
					m_edtDongDetail.SetWindowText(strDefaultDongDetail);
				}
			}	
		}
	}
}


void CWebChargeListDlg::OnBnClickedChargeCheck()
{
	if(m_chkStandardCharge.GetCheck())
		m_chkStandardCharge.SetCheck(FALSE);	
	else
		m_chkStandardCharge.SetCheck(TRUE);
}

void CWebChargeListDlg::OnBnClickedChargeInqueryBtn2()
{	
	CSearchGroupDlg dlg;
	dlg.m_nCompany = LF->GetCurBranchInfo()->nPayTable;
	dlg.m_nDataType = SG_DISCOUNT_COMPANY;
	if(dlg.DoModal() == IDOK)
	{
		m_nChargeID = dlg.m_nChargeID;
		if(m_nChargeID > 0)
		{
			CString strChargeName = m_mapChargeType[m_nChargeID].strChargeName;
			m_edtChargeName.SetWindowText(strChargeName);
			m_chkCharge.SetCheck(TRUE);
		}

	}
}

void CWebChargeListDlg::OnBnClickedEmailBtn()
{
	CString strEmail = "";
	m_edtEmail.GetWindowText(strEmail);

	if(!(strEmail.GetLength() > 0 && strEmail.Find("@") > 1))
	{
		MessageBox("�̸����� ���ų� �̸��� ������ �ƴմϴ�.");
		return;
	}

	Refresh(strEmail);
}

void CWebChargeListDlg::Refresh(CString sEmail)
{
	try
	{
		UpdateData(TRUE);
		CString strDong, strDongDetail;		

		m_edtDong.GetWindowText(strDong);
		m_edtDongDetail.GetWindowText(strDongDetail);
		
		CString strRow, strCol, strDongList = "";
		m_cmbChargeDongList.GetLBText(m_cmbChargeDongList.GetCurSel(), strDongList);
		int nPartSido = (int)m_cmbChargeDongList.GetItemData(m_cmbChargeDongList.GetCurSel());

		m_edtRow.GetWindowText(strRow);m_edtCol.GetWindowText(strCol);
		m_nRow = atol(strRow); m_nCol = atol(strCol);
		if(m_nRow <= 30 || m_nRow > 90 )
			throw("������� 30�����̰ų� 90���� �ѱ�� �����ϴ�.");
		if(m_nCol <= 4 || m_nCol > 10 )
			throw("��� �÷����� 4�����̰ų� 10�÷��� �ѱ�� �����ϴ�.");
			
		if(strDong.GetLength() > 0 && strDongDetail.GetLength() > 0 && strDongList.GetLength() > 0 && m_nDongID > 0)
		{
			HRESULT hr;
			BSTR bstrURL = NULL, bstrHeaders = NULL;
			VARIANT vFlags = {0},vTargetFrameName = {0},vPostData = {0},vHeaders = {0};
			//CString strUrl = "http://appwebQuick.logisoft.co.kr:8000/default.asp";
			CString strUrl = "http://quick2.logisoft.co.kr/old_quick_site_default.asp";
			//_variant_t vtUrl(strUrl.AllocSysString());

			bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
			V_VT(&vHeaders) = VT_BSTR;
			V_BSTR(&vHeaders) = bstrHeaders;
			CString strForm, strPostInfo, strCustomerName, strDefaultDong,strSendEmail,strTitle;		
			if(sEmail.GetLength() > 0)
			{
				m_edtCustomerName.GetWindowText(strCustomerName);
				m_edtDong.GetWindowText(strDefaultDong);
				m_edtSendMailAddress.GetWindowText(strSendEmail);
				m_edtTitle.GetWindowText(strTitle);

				if(strCustomerName.GetLength() ==0) 	throw "������ �Է��ϼ���";
				if(strDefaultDong.GetLength() ==0) 		throw "��������� �Է��ϼ���";
				if(strSendEmail.GetLength() ==0) 			throw "�����ô� �̸����� �Է��ϼ���";
				if(strTitle.GetLength() ==0) 					throw "���������� �Է��ϼ���";

			}

			strForm.Format("id_name=%s&sPWD=%s&sWName=%s&nWCompany=%ld&bIntegrated=%s&nSessionKey=%ld\n"\
				"&sIP=%s&nGetPage=13&nStartID=%ld&sDestSido=%s&nPartSido=%d&nChargeType=%d&nChargeID=%d\n"\
				"&nCheckDefault=%d&nCheckOneThousand=%d&sEmail=%s&sCustomerName=%s&sDefaultDong=%s\n"\
				"&sSendMailAddress=%s&sEmailTitle=%s&nCarType=%d&nModifyData=%d&nExcelView=%d&nUserRow=%d&nUserCol=%d",
				m_ui.strID, m_ui.strPW,m_ui.strName, m_ci.m_nCompanyCode,m_ci.m_bRcpIntMode1 ? "1" : "0", 
				m_ui.nSiteSessionKey, m_ei.strExternalIP,m_nDongID, strDongList, nPartSido, m_cmbType.GetCurSel(),
				m_chkCharge.GetCheck() && m_nChargeID > 0 ? m_nChargeID: 0,m_chkType.GetCheck(), m_chkOneThousand.GetCheck(), sEmail,
				strCustomerName,strDefaultDong,strSendEmail,strTitle,m_cmbCarType.GetCurSel(),m_chkModifyData.GetCheck(),
				m_chkExcel.GetCheck(),m_nRow, m_nCol);			
			hr = GetPostData(strForm,&vPostData);	

			if(m_Explorer.GetSafeHwnd())
				m_Explorer.Navigate((LPCTSTR)strUrl,&vFlags,&vTargetFrameName,&vPostData,&vHeaders);
		}
	}
	catch(char *e)
	{
		MessageBox(e,"Ȯ��", MB_ICONINFORMATION );
	}
	catch(CString s)
	{
		MessageBox(s,"Ȯ��", MB_ICONINFORMATION );
	}
}

void CWebChargeListDlg::OnBnClickedChargelistLoadBtn()
{
	
	Refresh("");
}

HRESULT CWebChargeListDlg::GetPostData(CString strKey, LPVARIANT pvPostData)
{
	HRESULT hr;
	LPSAFEARRAY psa;

	//	LPCTSTR cszPostData = "id=mania&Flavor=Mocha+Chip";

	//m_CtrlID.GetWindowText(m_strUserID);
	//m_CtrlPassWord.GetWindowText(m_strPassWord);


	CString PostInfo= strKey;
	LPCTSTR cszPostData = (LPCTSTR)PostInfo;
	UINT cElems = lstrlen(cszPostData);
	LPSTR pPostData;

	if (!pvPostData)
	{
		return E_POINTER;
	}

	VariantInit(pvPostData);

	psa = SafeArrayCreateVector(VT_UI1, 0, cElems);
	if (!psa)
	{
		return E_OUTOFMEMORY;
	}

	hr = SafeArrayAccessData(psa, (LPVOID*)&pPostData);
	memcpy(pPostData, cszPostData, cElems);
	hr = SafeArrayUnaccessData(psa);

	V_VT(pvPostData) = VT_ARRAY | VT_UI1;
	V_ARRAY(pvPostData) = psa;
	return NOERROR;
}

BOOL CWebChargeListDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	HKEY hKey = HKEY_CLASSES_ROOT;
	HKEY hKey2;
	CString sSubKey = ".xls";
	long nRet;	
	nRet =  ::RegOpenKeyEx(hKey,sSubKey,NULL,KEY_WRITE | KEY_READ, &hKey2 );
	int length = 9;
	if(!nRet)
	{
		RegSetValueEx(hKey2 ,"PerceivedType", 0,REG_SZ ,(LPBYTE)(LPCTSTR)"document",length);
		RegCloseKey(hKey2);
	}
		
	char buffer[10];
	

	
	
	int nDongID = 0;
	//char buffer[10];
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_chargelist_info");
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nDongID);
	pCmd.AddParameter(typeLong, typeInput, sizeof(long), m_nCompany);
	CMkParameter *pParDong = pCmd.AddParameter(typeString, typeOutput, 20, "");
	CMkParameter *pParDongDetail = pCmd.AddParameter(typeString, typeOutput, 100, "");
	if(!pRs.Execute(&pCmd)) return TRUE;

	CString sDongDetail,sDong,sChargeList;

	pParDong->GetValue(sDong);
	pParDongDetail->GetValue(sDongDetail);
	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		pRs.GetFieldValue("sChargeList", sChargeList);
		pRs.GetFieldValue("nID", nDongID);
			
		m_cmbChargeDongList.InsertString(i,sChargeList);
		m_cmbChargeDongList.SetItemData(i, nDongID);
		
		pRs.MoveNext();

	}
	pRs.Close();

	m_cmbChargeDongList.SetCurSel(0);
	m_cmbCarType.SetCurSel(0);
	m_cmbType.SetCurSel(0);
	m_edtDong.SetWindowText(sDong);
	m_edtDongDetail.SetWindowText(sDongDetail);
	m_edtRow.SetWindowText(ltoa(m_nRow,buffer,10));
	m_edtCol.SetWindowText(ltoa(m_nCol,buffer,10));

	CString strTitle = "";
	strTitle.Format(" %s(%s) �� ���ؿ��ǥ�Դϴ�. ",  LF->GetCurBranchInfo()->strBranchName, LF->GetCurBranchInfo()->strPhone);
	m_edtTitle.SetWindowText(strTitle);


	if(sDong.GetLength() > 0)
		OnBnClickedChargelistLoadBtn();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CWebChargeListDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{	
		return FALSE;
		if(pMsg->hwnd == m_Explorer.GetSafeHwnd() ) {
			
		}
	}

	return CMyDialog::PreTranslateMessage(pMsg);
}

void CWebChargeListDlg::OnBnClickedStandartCheck()
{
	if(m_chkStandardCharge.GetCheck())
	{
		m_edtGroupName.SetWindowText("");
		m_nChargeID = 0;
		m_nGNo = 0;
		m_edtChargeName.SetWindowText("");
		m_chkCharge.SetCheck(FALSE);
	}
	else
	{
		m_chkStandardCharge.SetCheck(TRUE);
	}
	
}

void CWebChargeListDlg::OnBnClickedExcelCheck()
{
	char buffer[10];
	if(m_chkExcel.GetCheck())
	{
		m_nRow = 50;m_nCol = 6;
	}
	else
	{
		m_nRow = 40;m_nCol = 7;
	}
	
	
	m_edtRow.SetWindowText(ltoa(m_nRow,buffer,10));
	m_edtCol.SetWindowText(ltoa(m_nCol,buffer,10));
}
