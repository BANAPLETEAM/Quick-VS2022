// WebPrintDlg1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Quick.h"
#include "WebPrintDlg1.h"


// CWebPrintDlg1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWebPrintDlg1, CDialog)

CWebPrintDlg1::CWebPrintDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CWebPrintDlg1::IDD, pParent)
{

}

CWebPrintDlg1::~CWebPrintDlg1()
{
}

void CWebPrintDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_ex);
}


BEGIN_MESSAGE_MAP(CWebPrintDlg1, CDialog)
	ON_BN_CLICKED(IDC_PRINT_BTN, &CWebPrintDlg1::OnBnClickedPrintBtn)
	ON_BN_CLICKED(IDC_PRINT_PRE_BTN, &CWebPrintDlg1::OnBnClickedPrintPreBtn)
END_MESSAGE_MAP()


// CWebPrintDlg1 메시지 처리기입니다.

BOOL CWebPrintDlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ex.put_Silent(TRUE);
	m_ex.Navigate(m_strUrl, NULL, NULL, NULL, NULL);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CWebPrintDlg1::PrintBtn(BOOL bPrint)
{ 
	//webHide.Document.Body.All.GetElementsByName("btnSetData")[0].InvokeMember("click")으로 한번 해 

	CString ret;
	HRESULT hr;

	CComBSTR bstrScript;
	LPDISPATCH lpDisp = m_ex.get_Document();
	IHTMLDocument2 * pHtmlDoc2 = NULL;

	hr = lpDisp->QueryInterface(IID_IHTMLDocument2 ,(void**)&pHtmlDoc2);

	
  
	BOOL bInsertID = FALSE;
	BOOL bInsertPW = FALSE;

	CString strItem = "";

	if (hr == S_OK)
	{
		IHTMLElementCollection *pelement = NULL;
		hr = pHtmlDoc2->get_all( &pelement );

		if (hr == S_OK && pelement != NULL)
		{
			LONG celem;
			hr = pelement->get_length( &celem );

			if ( hr == S_OK )
			{
				
				for ( int i=0; i< celem; i++ )
				{ 
					VARIANT varIndex;
					varIndex.vt = VT_UINT;
					varIndex.lVal = i;
					VARIANT var2;
					VariantInit( &var2 );
					IDispatch* pDisp; 
					hr = pelement->item( varIndex,var2, &pDisp );

					if ( hr == S_OK )
					{

						IHTMLElement* pElem;
						hr = pDisp->QueryInterface(IID_IHTMLElement,(void **)&pElem);

						if ( hr == S_OK )
						{
							BSTR bstr; 

							hr = pElem->get_tagName(&bstr);
							CString strTag; 
							strTag = bstr;

							if(CString(bstr) == "INPUT")
							{
								pElem->get_id(&bstr);

								if(CString(bstr) == "btnPrint" && bPrint == TRUE)
									pElem->click();
								else if(CString(bstr) == "btnPrePrint" && bPrint == FALSE) 
									pElem->click();
							}								

							IHTMLInputTextElement* pUser;
							hr = pDisp->QueryInterface(IID_IHTMLInputTextElement, (void **)&pUser );

							if ( hr == S_OK )
							{
								pUser->get_name(&bstr);

								pUser->Release();
							}

							IHTMLInputElement *pinElem;

							hr = pDisp->QueryInterface(IID_IHTMLInputElement, (void **)&pinElem );

							if ( hr == S_OK)
							{
								pinElem->get_src(&bstr);
							}
						}
						else
						{
							pElem->Release();
						}
					}
				}
			}
		}
		else
		{
		}

		pelement->Release();
	}
	else
	{
	}

	pHtmlDoc2->Release();
	lpDisp->Release();
}

void CWebPrintDlg1::OnBnClickedPrintBtn()
{
	PrintBtn(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CWebPrintDlg1::OnBnClickedPrintPreBtn()
{
	PrintBtn(FALSE);
}
