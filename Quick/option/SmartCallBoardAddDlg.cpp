// SmartCallBoardAddDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "SmartCallBoardAddDlg.h"
#include "FileUpload.h"
#include "ImageViewDlg.h"

// CSmartCallBoardAddDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSmartCallBoardAddDlg, CMyDialog)

CSmartCallBoardAddDlg::CSmartCallBoardAddDlg(CWnd* pParent /*=NULL*/)
: CMyDialog(CSmartCallBoardAddDlg::IDD, pParent)
, m_strTitle(_T(""))
, m_strBody(_T(""))
, m_bPlaying(FALSE)
{
	m_nMinUseCount = 0;
}

CSmartCallBoardAddDlg::~CSmartCallBoardAddDlg()
{
}

void CSmartCallBoardAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TITLE_EDIT, m_strTitle);
	DDX_Text(pDX, IDC_BODY_EDIT, m_strBody);
	//DDX_Text(pDX, IDC_URL_EDIT, m_strUrl);
	DDX_Text(pDX, IDC_MILEAGE_EDIT, m_strMileage);	
	DDX_Control(pDX, IDC_STATIC1, m_stc1);
	DDX_Control(pDX, IDC_URL_EDIT, m_edtUrl);
	DDX_Control(pDX, IDC_UPLOAD_BTN, m_btnUpload);
	DDX_Control(pDX, IDC_VIEW_BTN, m_btnView);
	DDX_Control(pDX, IDC_MILEAGE_EDIT, m_edtMileage);
	DDX_Control(pDX, IDC_PLAYING_CHECK, m_chkPlaying);
	DDX_Check(pDX, IDC_PLAYING_CHECK, m_bPlaying);
	DDX_Control(pDX, IDC_MIN_USE_COUNT_COMBO, m_cmbMinUseCount);
	DDX_CBIndex(pDX, IDC_ORDER_INSERT_TYPE_COMBO, m_nOrderInsertType);
}


BEGIN_MESSAGE_MAP(CSmartCallBoardAddDlg, CMyDialog)
	ON_BN_CLICKED(IDC_UPLOAD_BTN, &CSmartCallBoardAddDlg::OnBnClickedUploadBtn)
	ON_BN_CLICKED(IDC_VIEW_BTN, &CSmartCallBoardAddDlg::OnBnClickedViewBtn)
	ON_BN_CLICKED(IDOK, &CSmartCallBoardAddDlg::OnBnClickedOk)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CSmartCallBoardAddDlg �޽��� ó�����Դϴ�.

void CSmartCallBoardAddDlg::OnBnClickedUploadBtn()
{
	char szFilter[] = "Image Files(*.BMP, *.GIF, *.JPG, *.PNG, *.bmp, *.gif, *.jpg, *.png) | *.BMP;*.GIF;*.JPG;*.PNG;*.bmp;*.gif;*.jpg;*.png | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if(IDOK != dlg.DoModal()) 
		return;

	CString strFileName = dlg.GetPathName();

	CFileUpload fu;
	fu.SetConnectInfo(FTP_IP, "smartquick/event", "", "");

	if(!fu.UploadFile(strFileName))
	{
		MessageBox("���� ���ε��� �̻�߻�\r\n", "�ٽýõ��ϼ���", MB_ICONINFORMATION);
		return;
	}

	MessageBox("�̹��� ���ε尡 �Ϸ� �Ǿ����ϴ�\r\nȮ�ι�ư�� ���� �����ϼ���", "Ȯ��", MB_ICONINFORMATION);
	//  
	//m_strUrl = "http://work.logisoft.co.kr:8000/smartcall/funhan_event/" + strFileName;
	m_strUrl = "http://work.logisoft.co.kr:8000/smartquick/event/GetFileView.asp?strFileName=" + strFileName;
	//m_edtUrl.SetWindowText(m_strUrl);
	//m_edtUrl.SetWindowText( m_strUrl );
	m_edtUrl.SetWindowText(GetFileNameOnly(m_strUrl));
	return;
}

void CSmartCallBoardAddDlg::OnBnClickedViewBtn()
{
	//CImageDlg dlg;
	//CString strImage = fc.GetStringFromEdit(&m_edtUrl);
	CString strImage = m_strUrl;

	if(strImage.IsEmpty())
	{
		MessageBox("�̹����� ���ε� �� �ּ���", "Ȯ��", MB_ICONINFORMATION);
		return;	
	}

	CImageViewDlg dlg;
	dlg.m_strUrl = strImage;
	dlg.DoModal();

	//ShellExecute(NULL, "open", "iexplore.exe", fc.GetStringFromEdit(&m_edtUrl), "", SW_SHOW); 
}

BOOL CSmartCallBoardAddDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	if(!m_bEventBoard)
	{
		//m_edtUrl.EnableWindow(FALSE);
		m_btnUpload.EnableWindow(FALSE);
		m_btnView.EnableWindow(FALSE);
		m_chkPlaying.EnableWindow(FALSE);
		m_edtMileage.EnableWindow(FALSE);
		m_cmbMinUseCount.EnableWindow(FALSE);
	}

	m_cmbMinUseCount.SetWindowText(::GetStringFromLong(m_nMinUseCount));
	m_edtUrl.SetWindowText(GetFileNameOnly(m_strUrl));

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSmartCallBoardAddDlg::OnBnClickedOk()
{
	if(m_bEventBoard)
	{
		if(m_strUrl.IsEmpty()) 
		{
			MessageBox("�̺�Ʈ �Խ����� ȫ���̺�Ʈ �̹����� ���ε� �ϼ���", "Ȯ��", MB_ICONINFORMATION);
			return;
		}
	}

	CString strMinUseCount;
	m_cmbMinUseCount.GetWindowText(strMinUseCount);

	m_nMinUseCount = atoi(strMinUseCount);

	OnOK();
}

void CSmartCallBoardAddDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

CString CSmartCallBoardAddDlg::GetFileNameOnly(CString strFullPath)
{
	long nFind = strFullPath.Find("strFileName=");

	if(nFind < 0) 
		return strFullPath;

	CString strFileName = strFullPath.Mid(nFind + 12, strFullPath.GetLength() - nFind - 12);

	return strFileName;
	//http://work.logisoft.co.kr:8000/smartcall/funhan_event/GPS_1504171435145517.jpg

}