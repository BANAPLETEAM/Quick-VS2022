#include "stdafx.h"
#include "Wql.h"

CWql::CWql(void)
{
	m_nErrorCode = 0;
	m_bCoInitialize = FALSE;
	m_pLoc = NULL;
	m_pSvc = NULL;
	m_pEnumerator = NULL;
	m_pclsObj = NULL;
	Init();
}


CWql::CWql(BOOL bNoCoInitialize)
{
	m_nErrorCode = 0;
	m_bCoInitialize = FALSE;
	m_pLoc = NULL;
	m_pSvc = NULL;
	m_pEnumerator = NULL;
	m_pclsObj = NULL;

	if (FALSE == bNoCoInitialize) Init();;

}


CWql::~CWql(void)
{
	UnInit();
}


int CWql::Init()
{
	HRESULT hres;

	// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------

	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		m_sError.Format("Failed to initialize COM library. Error code = 0x", hres);
		m_nErrorCode = 1;
		return m_nErrorCode;                  // Program has failed.
	}

	// Set general COM security levels --------------------------
	// Note: If you are using Windows 2000, you need to specify -
	// the default authentication credentials for a user by using
	// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
	// parameter of CoInitializeSecurity ------------------------

	hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);


	if (FAILED(hres))
	{
		m_sError.Format("Failed to initialize security. Error code = 0x", hres);
		CoUninitialize();
		m_nErrorCode = 1;
		return m_nErrorCode;                    // Program has failed.
	}

	m_sError = "";
	m_nErrorCode = 0;
	m_bCoInitialize = TRUE;
	return m_nErrorCode;
}

void CWql::UnInit()
{

	if (m_pSvc)
	{
		m_pSvc->Release();
		m_pSvc = NULL;
	}

	if (m_pLoc)
	{
		m_pLoc->Release();
		m_pLoc = NULL;
	}
	if (m_pEnumerator)
	{
		m_pEnumerator->Release();
		m_pEnumerator = NULL;
	}

	if (m_pclsObj)
	{
		m_pclsObj->Release();
		m_pclsObj = NULL;
	}

	if (m_bCoInitialize)
	{
		CoUninitialize();
		m_bCoInitialize = FALSE;
	}

}


BOOL CWql::Open(const char* sWql)
{

	// Step 3: ---------------------------------------------------
	// Obtain the initial locator to WMI -------------------------
	HRESULT hres;

	//    IWbemLocator *pLoc = NULL;

	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID*)&m_pLoc);

	if (FAILED(hres))
	{
		m_sError.Format("Failed to create IWbemLocator object. Error code = 0x", hres);
		m_nErrorCode = 1;
		UnInit();
		return FALSE;                 // Program has failed.
	}

	// Step 4: -----------------------------------------------------
	// Connect to WMI through the IWbemLocator::ConnectServer method

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = m_pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object 
		&m_pSvc                    // pointer to IWbemServices proxy
	);

	if (FAILED(hres))
	{
		m_sError.Format("Could not connect. Error code = 0x", hres);
		m_nErrorCode = 1;
		UnInit();
		return FALSE; // Program has failed.
	}




	// Step 5: --------------------------------------------------
	// Set security levels on the proxy -------------------------

	hres = CoSetProxyBlanket(
		m_pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);

	if (FAILED(hres))
	{
		m_sError.Format("Could not set proxy blanket. Error code = 0x", hres);
		m_nErrorCode = 1;
		UnInit();
		return FALSE; // Program has failed.
	}

	// Step 6: --------------------------------------------------
	// Use the IWbemServices pointer to make requests of WMI ----

	// For example, get the name of the operating system
//    IEnumWbemClassObject* pEnumerator = NULL;
	hres = m_pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(sWql),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&m_pEnumerator);

	if (FAILED(hres))
	{
		m_sError.Format("Query for [%s] failed. Error code = 0x", sWql, hres);
		m_nErrorCode = 1;
		UnInit();
		return FALSE; // Program has failed.
	}

	m_sError = "";
	m_nErrorCode = 0;
	return TRUE;
}


BOOL CWql::MoveNext()
{
	//    IWbemClassObject *pclsObj;
	ULONG uReturn = 0;

	if (m_pclsObj)
	{
		m_pclsObj->Release();
		m_pclsObj = NULL;
	}

	if (m_pEnumerator)
	{
		HRESULT hr = m_pEnumerator->Next(WBEM_INFINITE, 1, &m_pclsObj, &uReturn);

		if (0 == uReturn)
		{
			return FALSE;
		}

		m_sError = "";
		m_nErrorCode = 0;
		return TRUE;
	}

	return FALSE;
}

BOOL CWql::GetValue(const char* szColName, CString& sRet)
{
	VARIANT vtProp;

	CA2W pszW(szColName);

	// Get the value of the Name property
	HRESULT hr = m_pclsObj->Get(pszW, 0, &vtProp, 0, 0);

	if (FAILED(hr))
	{
		m_sError.Format("Column [%s] 값을 조회중 에러입니다.", szColName);
		m_nErrorCode = 1;
		return FALSE;
	}
	else
	{
		if (VT_NULL == vtProp.vt) sRet = "";
		else sRet = CString(vtProp.bstrVal);
	}
	VariantClear(&vtProp);

	m_sError = "";
	m_nErrorCode = 0;
	return TRUE;
}

BOOL CWql::GetValue(const char* szColName, int& nRet, int nDefaultVal)
{
	VARIANT vtProp;

	CA2W pszW(szColName);

	// Get the value of the Name property
	HRESULT hr = m_pclsObj->Get(pszW, 0, &vtProp, 0, 0);

	if (FAILED(hr))
	{
		m_sError.Format("Column [%s] 값을 조회중 에러입니다.", szColName);
		m_nErrorCode = 1;
		return FALSE;
	}
	else
	{

		if (VT_NULL == vtProp.vt) nRet = nDefaultVal;
		else
		{
			switch (vtProp.vt)
			{
			case VT_BOOL: nRet = vtProp.boolVal;
				if (0 != nRet)  nRet = TRUE;
				break;
			case VT_INT: nRet = vtProp.intVal;
				break;
			case VT_I1: nRet = vtProp.lVal;
				break;
			case VT_UI1: nRet = vtProp.intVal;
				break;
			case VT_UI2: nRet = vtProp.uintVal;
				break;
			case VT_UI4: nRet = vtProp.uintVal;
				break;
			case VT_I8: nRet = vtProp.llVal;
				break;
			case VT_UI8: nRet = vtProp.uintVal;
				break;
			case VT_UINT: nRet = vtProp.uintVal;
				break;
			default:	   nRet = nDefaultVal;
			}
		}
	}


	VariantClear(&vtProp);

	m_sError = "";
	m_nErrorCode = 0;
	return TRUE;
}
