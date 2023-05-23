// SetPoiDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "SetPoiDlg.h"
#include "POIDataNew.h"


// CSetPoiDlg 대화 상자입니다.

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


// CSetPoiDlg 메시지 처리기입니다.

void CSetPoiDlg::OnBnClickedClearPoiBtn()
{
	DeleteFile(LF->GetModuleFullPath() + "poi_d.dat");
	DeleteFile(LF->GetModuleFullPath() + "poi.ini");
	if(m_poiNew.IsDataLoadOK())
		MessageBox("프로그램 재시작 바랍니다.", "확인", MB_ICONINFORMATION);
	else
		MessageBox("POI를 초기화 하였습니다.\n접수화면으로 진행 하시기 바랍니다.", "확인", MB_ICONINFORMATION);
}

void CSetPoiDlg::OnBnClickedClearNewAddressBtn()
{
	CString strName = LF->GetModuleFullPath() + "RDATA.txt";
	DeleteFile(strName);

	if(m_poiNew.IsDataLoadOK())
		MessageBox("프로그램 재시작 바랍니다.", "확인", MB_ICONINFORMATION);
	else
		MessageBox("POI를 초기화 하였습니다.\n접수화면으로 진행 하시기 바랍니다.", "확인", MB_ICONINFORMATION);
}

void CSetPoiDlg::OnBnClickedCancel()
{
	OnCancel();
}
