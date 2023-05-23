// SetPoiDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Quick.h"
#include "SetPoiDlg.h"
#include "POIDataNew.h"


// CSetPoiDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSetPoiDlg, CMyDialog)

CSetPoiDlg::CSetPoiDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSetPoiDlg::IDD, pParent)
{

}

CSetPoiDlg::~CSetPoiDlg()
{
}

void CSetPoiDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPoiDlg, CMyDialog)
	ON_BN_CLICKED(IDC_CLEAR_POI_BTN, &CSetPoiDlg::OnBnClickedClearPoiBtn)
	ON_BN_CLICKED(IDC_CLEAR_NEW_ADDRESS_BTN, &CSetPoiDlg::OnBnClickedClearNewAddressBtn)
	ON_BN_CLICKED(IDCANCEL, &CSetPoiDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSetPoiDlg �޽��� ó�����Դϴ�.

void CSetPoiDlg::OnBnClickedClearPoiBtn()
{
	DeleteFile(LF->GetModuleFullPath() + "poi_d.dat");
	DeleteFile(LF->GetModuleFullPath() + "poi.ini");
	if(m_poiNew.IsDataLoadOK())
		MessageBox("���α׷� ����� �ٶ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else
		MessageBox("POI�� �ʱ�ȭ �Ͽ����ϴ�.\n����ȭ������ ���� �Ͻñ� �ٶ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
}

void CSetPoiDlg::OnBnClickedClearNewAddressBtn()
{
	CString strName = LF->GetModuleFullPath() + "RDATA.txt";
	DeleteFile(strName);

	if(m_poiNew.IsDataLoadOK())
		MessageBox("���α׷� ����� �ٶ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
	else
		MessageBox("POI�� �ʱ�ȭ �Ͽ����ϴ�.\n����ȭ������ ���� �Ͻñ� �ٶ��ϴ�.", "Ȯ��", MB_ICONINFORMATION);
}

void CSetPoiDlg::OnBnClickedCancel()
{
	OnCancel();
}
