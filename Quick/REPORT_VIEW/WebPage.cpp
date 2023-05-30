/////////////////////////////////////////////////////////////////
//             By Eugene Khodakovsky                           //
//                  April,2002                                 //
//             Eugene@cpplab.com                               //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WebPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CHECK_POINTER(p)\
	ATLASSERT(p != NULL);\
	if(p == NULL)\
	{\
		ShowError("NULL pointer");\
		return false;\
	}

const CString GetSystemErrorMessage(DWORD dwError)
{
	CString strError;
	LPTSTR lpBuffer;

	if(!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,  dwError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
			(LPTSTR) &lpBuffer, 0, NULL))

	{
		strError = "FormatMessage Netive Error" ;
	}
	else
	{
		strError = lpBuffer;
		LocalFree(lpBuffer);
	}
	return strError;
}

CString GetNextToken(CString& strSrc, const CString strDelim,bool bTrim, bool bFindOneOf)
{
	CString strToken;
	int idx = bFindOneOf? strSrc.FindOneOf(strDelim) : strSrc.Find(strDelim);
	if(idx != -1)
	{
		strToken  = strSrc.Left(idx);
		strSrc = strSrc.Right(strSrc.GetLength() - (idx + 1) );
	}
	else
	{
		strToken = strSrc;
		strSrc.Empty();
	}
	if(bTrim)
	{
		strToken.TrimLeft();
		strToken.TrimRight();
	}
	return strToken;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWebPage::CWebPage()
{
}

CWebPage::~CWebPage()
{

}

bool CWebPage::SetDocument(IDispatch* pDisp)
{
	CHECK_POINTER(pDisp);

	m_spDoc = NULL;

	CComPtr<IDispatch> spDisp = pDisp;

	HRESULT hr = spDisp->QueryInterface(IID_IHTMLDocument2,(void**)&m_spDoc);
	if(FAILED(hr))
	{
		ShowError("Failed to get HTML document COM object");
		return false;
	}
	return true;
}

bool CWebPage::GetJScript(CComPtr<IDispatch>& spDisp)
{
	CHECK_POINTER(m_spDoc);
	HRESULT hr = m_spDoc->get_Script(&spDisp);
	ATLASSERT(SUCCEEDED(hr));
	return SUCCEEDED(hr);
}

bool CWebPage::GetJScripts(CComPtr<IHTMLElementCollection>& spColl)
{
	CHECK_POINTER(m_spDoc);
	HRESULT hr = m_spDoc->get_scripts(&spColl);
	ATLASSERT(SUCCEEDED(hr));
	return SUCCEEDED(hr);
}

bool CWebPage::CallJScript(const CString strFunc,CComVariant* pVarResult)
{
	CStringArray paramArray;
	return CallJScript(strFunc,paramArray,pVarResult);
}

bool CWebPage::CallJScript(const CString strFunc,const CString strArg1,CComVariant* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	return CallJScript(strFunc,paramArray,pVarResult);
}

bool CWebPage::CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,CComVariant* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	paramArray.Add(strArg2);
	return CallJScript(strFunc,paramArray,pVarResult);
}

bool CWebPage::CallJScript(const CString strFunc,const CString strArg1,const CString strArg2,const CString strArg3,CComVariant* pVarResult)
{
	CStringArray paramArray;
	paramArray.Add(strArg1);
	paramArray.Add(strArg2);
	paramArray.Add(strArg3);
	return CallJScript(strFunc,paramArray,pVarResult);
}

bool CWebPage::CallJScript(const CString strFunc, const CStringArray& paramArray,CComVariant* pVarResult)
{
	CComPtr<IDispatch> spScript;
	if(!GetJScript(spScript))
	{
		ShowError("Cannot GetScript");
		return false;
	}
	CComBSTR bstrMember(strFunc);
	DISPID dispid = NULL;
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL,&bstrMember,1,
											LOCALE_SYSTEM_DEFAULT,&dispid);
	if(FAILED(hr))
	{
		ShowError(GetSystemErrorMessage(hr));
		return false;
	}

	const int arraySize = paramArray.GetSize();

	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = arraySize;
	dispparams.rgvarg = new VARIANT[dispparams.cArgs];
	
	for( int i = 0; i < arraySize; i++)
	{
		CComBSTR bstr = paramArray.GetAt(arraySize - 1 - i); // back reading
		bstr.CopyTo(&dispparams.rgvarg[i].bstrVal);
		dispparams.rgvarg[i].vt = VT_BSTR;
	}
	dispparams.cNamedArgs = 0;

	EXCEPINFO excepInfo;
	memset(&excepInfo, 0, sizeof excepInfo);
   	CComVariant vaResult;
	UINT nArgErr = (UINT)-1;  // initialize to invalid arg
         
	hr = spScript->Invoke(dispid,IID_NULL,0,
							DISPATCH_METHOD,&dispparams,&vaResult,&excepInfo,&nArgErr);

	delete [] dispparams.rgvarg;
	if(FAILED(hr))
	{
		ShowError(GetSystemErrorMessage(hr));
		return false;
	}
	
	if(pVarResult)
	{
		*pVarResult = vaResult;
	}
	return true;
}

//
//bool CWebPage::CallJScript(const CString strFunc, IHTMLDocument2 *pDoc )
//{
//
//
//	CComPtr<IDispatch> spScript;
//	if(!GetJScript(spScript))
//	{
//		ShowError("Cannot GetScript");
//		return false;
//	}
//
//	CComBSTR bstrMember(strFunc);
//	DISPID dispid = NULL;
//	HRESULT hr = spScript->GetIDsOfNames(IID_NULL,&bstrMember,1,
//		LOCALE_SYSTEM_DEFAULT,&dispid);
//	if(FAILED(hr))
//	{
//		ShowError(GetSystemErrorMessage(hr));
//		return false;
//	}
//	IHTMLWindow2 *pWindow;
//	IDispatch* pDocDisp = NULL;	
//	pDoc->get_parentWindow(&pWindow);
//	pWindow->
//	IDispatch *pWindowDisp = NULL;
//	//pBrowserApp->get_Document(&pDocDisp);
//	//pBrowserApp->get_Application((&pWindowDisp);
////pDoc->
//
//	CComVariant docDisp(pDocDisp);
//	CComVariant winDisp(pWindowDisp);
//	DISPPARAMS dispparams;
//	memset(&dispparams, 0, sizeof dispparams);
//	dispparams.cArgs = 1;	
//	dispparams.rgvarg = &pDocDisp;
//	//dispparams.rgvarg     = new VARIANT[ dispparams.cArgs];
//
//	//dispparams.rgvarg[0].pdispVal = docDisp.pdispVal; //.pdispVal;
//	//dispparams.rgvarg[1].pdispVal = winDisp.pdispVal;
//
//	//dispparams.rgvarg[1] = &winDisp; //pWindowDisp;
//	dispparams.cNamedArgs = 0;
//
//
//	EXCEPINFO excepInfo;
//	memset(&excepInfo, 0, sizeof excepInfo);
//	CComVariant vaResult;
//	UINT nArgErr = (UINT)-1;  // initialize to invalid arg
//
//	VARIANT varResult;
//	varResult.vt = VT_EMPTY;
//
//
//	//hr = spScript->Invoke(dispid,IID_NULL,0,
//	//DISPATCH_METHOD,&dispparams,&vaResult,&excepInfo,&nArgErr);
//	hr = spScript->Invoke(dispid,IID_NULL, 0, DISPATCH_METHOD,&dispparams , &varResult, &excepInfo , &nArgErr);
//
//	return TRUE;
//}

bool CWebPage::CallJScript(const CString strFunc, IHTMLDocument2 *pDoc, IWebBrowser2 *pBrowserApp)
{

	CComPtr<IDispatch> spScript;
	if(!GetJScript(spScript))
	{
		ShowError("Cannot GetScript");
		return false;
	}

	CComBSTR bstrMember(strFunc);
	DISPID dispid = NULL;
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL,&bstrMember,1,
		LOCALE_SYSTEM_DEFAULT,&dispid);
	if(FAILED(hr))
	{
		ShowError(GetSystemErrorMessage(hr));
		return false;
	}
	
	IDispatch* pDocDisp = NULL;	
	IDispatch *pWindowDisp = NULL;
	pBrowserApp->get_Document(&pDocDisp);
	pBrowserApp->get_Application(&pWindowDisp);
	
	

	CComVariant docDisp(pDocDisp);
	CComVariant winDisp(pWindowDisp);
	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = 1;	
	dispparams.rgvarg = &winDisp;
	//dispparams.rgvarg     = new VARIANT[ dispparams.cArgs];

	//dispparams.rgvarg[0].pdispVal = docDisp.pdispVal; //.pdispVal;
	//dispparams.rgvarg[1].pdispVal = winDisp.pdispVal;

	//dispparams.rgvarg[1] = &winDisp; //pWindowDisp;
	dispparams.cNamedArgs = 0;

	
	EXCEPINFO excepInfo;
	memset(&excepInfo, 0, sizeof excepInfo);
	CComVariant vaResult;
	UINT nArgErr = (UINT)-1;  // initialize to invalid arg

	VARIANT varResult;
	varResult.vt = VT_EMPTY;

	
	//hr = spScript->Invoke(dispid,IID_NULL,0,
		//DISPATCH_METHOD,&dispparams,&vaResult,&excepInfo,&nArgErr);
	hr = spScript->Invoke(dispid,IID_NULL, 0, DISPATCH_METHOD,&dispparams , &varResult, &excepInfo , &nArgErr);

	return TRUE;
}
bool CWebPage::CallJScript(const CString strFunc, LPDISPATCH pDocDisp)
{

	CComPtr<IDispatch> spScript;
	if(!GetJScript(spScript))
	{
		ShowError("Cannot GetScript");
		return false;
	}

	CComBSTR bstrMember(strFunc);
	DISPID dispid = NULL;
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL,&bstrMember,1,
		LOCALE_SYSTEM_DEFAULT,&dispid);
	if(FAILED(hr))
	{
		ShowError(GetSystemErrorMessage(hr));
		return false;
	}

	//IDispatch* pDocDisp = NULL;	
	IDispatch *pWindowDisp = NULL;
	//IDispatch *pDialogDisp = NULL;


	VARIANT varChild;
	varChild.lVal = 1;
	

	/*pBrowserApp->get_Document(&pDocDisp);
	pBrowserApp->get_Application(&pWindowDisp);	*/
	//hr = pDlg->GetAccessibleChild(varChild, &pDialogDisp);
	//pDialogDisp = pDlg;//->GetIDispatch(TRUE);
	//pD
	
	//pBrowserApp->get_Parent(&pDialogDisp);

	CComVariant docDisp(pDocDisp);
	CComVariant winDisp(pWindowDisp);
	//CComVariant DialogDisp(pDialogDisp);
	DISPPARAMS dispparams;

	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = 1;	
	dispparams.rgvarg = &docDisp;
	//dispparams.rgvarg = &DialogDisp;	
	//dispparams.rgvarg     = new VARIANT[ dispparams.cArgs];
	//dispparams.rgvarg[0].pdispVal = docDisp.pdispVal; //.pdispVal;
	//dispparams.rgvarg[1].pdispVal = winDisp.pdispVal;
	//dispparams.rgvarg[1] = &winDisp; //pWindowDisp;
	dispparams.cNamedArgs = 0;


	EXCEPINFO excepInfo;
	memset(&excepInfo, 0, sizeof excepInfo);
	CComVariant vaResult;
	UINT nArgErr = (UINT)-1;  // initialize to invalid arg

	VARIANT varResult;
	varResult.vt = VT_EMPTY;


	//hr = spScript->Invoke(dispid,IID_NULL,0,
	//DISPATCH_METHOD,&dispparams,&vaResult,&excepInfo,&nArgErr);
	hr = spScript->Invoke(dispid,IID_NULL, 0, DISPATCH_METHOD,&dispparams , &varResult, &excepInfo , &nArgErr);
	if(SUCCEEDED(hr))
		return TRUE;
	return FALSE;
}



bool CWebPage::CallJScript(const CString strFunc, IHTMLDocument2 *pDoc, IWebBrowser2 *pBrowserApp, CWnd *pDlg)
{

	CComPtr<IDispatch> spScript;
	if(!GetJScript(spScript))
	{
		ShowError("Cannot GetScript");
		return false;
	}

	CComBSTR bstrMember(strFunc);
	DISPID dispid = NULL;
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL,&bstrMember,1,
		LOCALE_SYSTEM_DEFAULT,&dispid);
	if(FAILED(hr))
	{
		ShowError(GetSystemErrorMessage(hr));
		return false;
	}

	IDispatch* pDocDisp = NULL;	
	IDispatch *pWindowDisp = NULL;
	//IDispatch *pDialogDisp = NULL;
	

	VARIANT varChild;
	varChild.lVal = 1;

	pBrowserApp->get_Document(&pDocDisp);
	pBrowserApp->get_Application(&pWindowDisp);	
	//hr = pDlg->GetAccessibleChild(varChild, &pDialogDisp);
	//pDialogDisp = pDlg;//->GetIDispatch(TRUE);
	//pD
	LPDISPATCH pDialogDisp = pDlg->GetIDispatch(TRUE);
	//pBrowserApp->get_Parent(&pDialogDisp);
	
	CComVariant docDisp(pDocDisp);
	CComVariant winDisp(pWindowDisp);
	CComVariant DialogDisp(pDialogDisp);
	DISPPARAMS dispparams;
	
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = 1;	
	dispparams.rgvarg = &winDisp;
	//dispparams.rgvarg = &DialogDisp;	
	//dispparams.rgvarg     = new VARIANT[ dispparams.cArgs];
	//dispparams.rgvarg[0].pdispVal = docDisp.pdispVal; //.pdispVal;
	//dispparams.rgvarg[1].pdispVal = winDisp.pdispVal;
	//dispparams.rgvarg[1] = &winDisp; //pWindowDisp;
	dispparams.cNamedArgs = 0;


	EXCEPINFO excepInfo;
	memset(&excepInfo, 0, sizeof excepInfo);
	CComVariant vaResult;
	UINT nArgErr = (UINT)-1;  // initialize to invalid arg

	VARIANT varResult;
	varResult.vt = VT_EMPTY;


	//hr = spScript->Invoke(dispid,IID_NULL,0,
	//DISPATCH_METHOD,&dispparams,&vaResult,&excepInfo,&nArgErr);
	hr = spScript->Invoke(dispid,IID_NULL, 0, DISPATCH_METHOD,&dispparams , &varResult, &excepInfo , &nArgErr);

	return TRUE;
}


// returned java script function name, input string is truncating
CString CWebPage::ScanJScript(CString& strAText, CStringArray& args)
{
	args.RemoveAll();
	CString strDelim(" \n\r\t"),strSrc(strAText);
	bool bFound = false;
	while(!strSrc.IsEmpty())
	{
		CString strStart = GetNextToken(strSrc,strDelim);
		if(strStart == "function")
		{
			bFound = true;
			break;
		}
		if(strStart == "/*")
		{
			// Skip comments
			while(!strSrc.IsEmpty())
			{
				CString strStop = GetNextToken(strSrc,strDelim);
				if(strStop == "*/")
				{
					break;
				}
			}
		}
	}

	if(!bFound)
		return "";
	
	CString strFunc = GetNextToken(strSrc,"(",true);
	CString strArgs = GetNextToken(strSrc,")",true);

	// Parse arguments
	CString strArg;
	while(!(strArg = GetNextToken(strArgs,",")).IsEmpty())
		args.Add(strArg);

	strAText= strSrc;
	return strFunc;
}

//MSHTML::IHTMLDocument2Ptr pDoc(GetHtmlDocument());		
//MSHTML::IHTMLDocument3Ptr pDoc3 = pDoc;		
//MSHTML::IHTMLElementCollectionPtr pCollection;		
//MSHTML::IHTMLInputTextElementPtr pInputText;		
//MSHTML::IHTMLInputElementPtr pInput;		
//MSHTML::IHTMLFormElementPtr pForm;		

////pDoc3->
//pCollection = pDoc3->getElementsByName(_bstr_t("login"));	//<input name="login"...		
//pInputText = pCollection->item(CComVariant(0),CComVariant(0));		
//pInputText->put_value(CComBSTR("YOURLOGINNAME"));//change it!			
//pCollection = pDoc3->getElementsByName(_bstr_t("passwd")); //<input name="passwd"...		
//pInputText = pCollection->item(CComVariant(0),CComVariant(0)); 		
//pInputText->put_value(CComBSTR("YOURPASSWORD"));//change it!		
//pCollection = pDoc3->getElementsByName(_bstr_t(".save"));
////<input name=".save" type="submit"...		
//pInput = pCollection->item(CComVariant(0),CComVariant(0)); 		
//pInput->get_form(&pForm);		
//HRESULT hr = pForm->submit();		
//if (hr != S_OK)			
//	MessageBox("Error submitting form");

