#include "stdafx.h"
#include "resource.h"
#include "EdgeBrowser.h"
#include "ViewComponent.h"


CEdgeBrowser::CEdgeBrowser()
{
}

void CEdgeBrowser::Navigate(CWnd* parent, LPCWSTR url)
{
    HRESULT hresult;
    if (m_webView) {
        hresult = m_webView->Navigate(url);
    }
    else {
        if (!parent_wnd_)
			parent_wnd_ = parent;

        InitializeWebView(parent_wnd_, url);
        hresult = S_OK;
    }

    if (hresult == S_OK) {
        ResizeEverything();
    }
}


void CEdgeBrowser::InitializeWebView(CWnd* parent, LPCWSTR url)
{
    parent_wnd_ = parent;
    url_ = (CW2CT)url;
    CloseWebView();
    m_dcompDevice = nullptr;

    HRESULT hr2 = DCompositionCreateDevice2(nullptr, IID_PPV_ARGS(&m_dcompDevice));
    if (!SUCCEEDED(hr2))
    {
        AfxMessageBox("Attempting to create WebView using DComp Visual is not supported.\r\n"
            "DComp device creation failed.\r\n"
            "Current OS may not support DComp.\r\n"
            "Create with Windowless DComp Visual Failed", MB_OK);
        return;
    }


#ifdef USE_WEBVIEW2_WIN10
    m_wincompCompositor = nullptr;
#endif
    LPCWSTR subFolder = nullptr;
    auto options = Microsoft::WRL::Make<CoreWebView2EnvironmentOptions>();
    options->put_AllowSingleSignOnUsingOSPrimaryAccount(FALSE);

    HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(subFolder, nullptr, options.Get(), Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(this, &CEdgeBrowser::OnCreateEnvironmentCompleted).Get());

    if (!SUCCEEDED(hr))
    {
        if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
        {
            TRACE("Couldn't find Edge installation. Do you have a version installed that is compatible with this ");
        }
        else
        {
            AfxMessageBox("Failed to create webview environment");
        }
    }
}

void CEdgeBrowser::CloseWebView(bool cleanupUserDataFolder)
{

    if (m_controller)
    {
        m_controller->Close();
        m_controller = nullptr;
        m_webView = nullptr;
    }
    m_webViewEnvironment = nullptr;
    if (cleanupUserDataFolder)
    {
        //Clean user data        
    }
}


HRESULT CEdgeBrowser::OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment)
{
    m_webViewEnvironment = environment;
    m_webViewEnvironment->CreateCoreWebView2Controller(this->GetSafeHwnd(), Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this, &CEdgeBrowser::OnCreateCoreWebView2ControllerCompleted).Get());

    return S_OK;
}

HRESULT CEdgeBrowser::OnCreateCoreWebView2ControllerCompleted(HRESULT result, ICoreWebView2Controller* controller)
{
    if (result == S_OK)
    {
        m_controller = controller;
        wil::com_ptr<ICoreWebView2> coreWebView2;
        m_controller->get_CoreWebView2(&coreWebView2);
        coreWebView2.query_to(&m_webView);

        NewComponent<ViewComponent>(
            this, m_dcompDevice.get(),
#ifdef USE_WEBVIEW2_WIN10
            m_wincompCompositor,
#endif
            m_creationModeId == IDM_CREATION_MODE_TARGET_DCOMP);
        
        HRESULT hresult = m_webView->Navigate(CT2CW(url_));

        if (hresult == S_OK)
        {
            TRACE("Web Page Opened Successfully");
            ResizeEverything();
        }

        EventRegistrationToken token;
        m_webView->add_NavigationStarting(Microsoft::WRL::Callback< ICoreWebView2NavigationStartingEventHandler>(this, &CEdgeBrowser::NavigationStarting).Get(), &token);
        //m_webView->add_WebMessageReceived(Microsoft::WRL::Callback<ICoreWebView2WebMessageReceivedEventHandler>
        //    (this, &CEdgeBrowser::WebMessageReceived).Get(), &token);

        m_webView->add_NavigationCompleted(Microsoft::WRL::Callback<ICoreWebView2NavigationCompletedEventHandler>(this, &CEdgeBrowser::NavigationCompleted).Get(), &token);
    }
    else
    {
        TRACE("Failed to create webview");
    }
    return S_OK;
}

void CEdgeBrowser::ResizeEverything()
{
    if (GetSafeHwnd()) {
        RECT rc; GetClientRect(&rc);
        if (auto view = GetComponent<ViewComponent>()) {
            view->SetBounds(rc);
        }
    }
}

HRESULT CEdgeBrowser::DCompositionCreateDevice2(IUnknown* renderingDevice, REFIID riid, void** ppv)
{
    HRESULT hr = E_FAIL;
    static decltype(::DCompositionCreateDevice2)* fnCreateDCompDevice2 = nullptr;
    if (fnCreateDCompDevice2 == nullptr)
    {
        HMODULE hmod = ::LoadLibraryEx("dcomp.dll", nullptr, 0);
        if (hmod != nullptr)
        {
            fnCreateDCompDevice2 = reinterpret_cast<decltype(::DCompositionCreateDevice2)*>(
                ::GetProcAddress(hmod, "DCompositionCreateDevice2"));
        }
    }
    if (fnCreateDCompDevice2 != nullptr)
    {
        hr = fnCreateDCompDevice2(renderingDevice, riid, ppv);
    }
    return hr;
}

void CEdgeBrowser::Execute(CString script)
{
   	m_webView->ExecuteScript(CT2CW(script), Microsoft::WRL::Callback<ICoreWebView2ExecuteScriptCompletedHandler>(this, &CEdgeBrowser::ExecuteScriptResponse).Get());
}

void CEdgeBrowser::Execute(CString strFuncName, CString strText)
{
    CString script = strFuncName + "('" + strText + "')";    
    m_webView->ExecuteScript(CT2CW(script), Microsoft::WRL::Callback<ICoreWebView2ExecuteScriptCompletedHandler>(this, &CEdgeBrowser::ExecuteScriptResponse).Get());
}

HRESULT CEdgeBrowser::ExecuteScriptResponse(HRESULT errorCode, LPCWSTR resultObjectAsJson)
{
    if (errorCode != S_OK) {
        CString msg = "error code = ";
        CString json = CW2CT(resultObjectAsJson);
        MessageBox(msg + json, errorCode == S_OK ? "전송 성공" : "전송 실패", MB_ICONINFORMATION);
    }

    //parent_wnd_->SendMessage(WM_USER + 90, (WPARAM)resultObjectAsJson);

    return S_OK;
}


HRESULT CEdgeBrowser::NavigationStarting(ICoreWebView2* sender, ICoreWebView2NavigationStartingEventArgs* args)
{
    LPWSTR pwStr;
    args->get_Uri(&pwStr);
    CString url = CW2CT(pwStr);

    if (url.Find("event:") >= 0) {
        MessageBox(url, "메시지 확인", MB_ICONINFORMATION);
    }
    else {
        //if (dlg_) {
        //    dlg_->m_edtUrl.SetWindowText(url);
        //}
    }
    
    return S_OK;
}

HRESULT CEdgeBrowser::NavigationCompleted(ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args)
{
    m_webView = sender;
    LPWSTR pwStr = CT2CW(url_);
    parent_wnd_->SendMessage(WM_USER + 91, (WPARAM)pwStr);

    return S_OK;
}

//HRESULT CEdgeBrowser::WebMessageReceived(ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args)
//{
//    LPWSTR pwStr;
//    args->TryGetWebMessageAsString(&pwStr);
//    CString receivedMessage = pwStr;
//    if (!receivedMessage.IsEmpty()) {
//        AfxMessageBox("This message came from Javascript : " + receivedMessage);
//    }
//    return S_OK;
//}


BEGIN_MESSAGE_MAP(CEdgeBrowser, CWnd)
    ON_WM_SIZE()
END_MESSAGE_MAP()


void CEdgeBrowser::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);

    ResizeEverything();
}