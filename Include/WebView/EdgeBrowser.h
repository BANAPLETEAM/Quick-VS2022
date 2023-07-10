#pragma once
#include <afxwin.h>
#include <dcomp.h>
#include <vector>
#include <memory>
#include "ComponentBase.h"

class CEdgeBrowser : public CWnd
{
public:
    CEdgeBrowser();

private:
    void InitializeWebView(CWnd* parent, LPCWSTR url = L"about:blank");

public:
    CWnd* parent_wnd_ = NULL;
    DWORD m_creationModeId = 0;
    CString url_;
    CString execute_response_;

    wil::com_ptr<ICoreWebView2> m_webView;
    wil::com_ptr<ICoreWebView2Environment> m_webViewEnvironment;
    wil::com_ptr<IDCompositionDevice> m_dcompDevice;
    wil::com_ptr<ICoreWebView2Controller> m_controller;
    std::vector<std::unique_ptr<ComponentBase>> m_components;

    void CloseWebView(bool cleanupUserDataFolder = false);
    HRESULT OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment);
    HRESULT OnCreateCoreWebView2ControllerCompleted(HRESULT result, ICoreWebView2Controller* controller);
    HRESULT ExecuteScriptResponse(HRESULT errorCode, LPCWSTR resultObjectAsJson);
    //HRESULT WebMessageReceived(ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args);
    HRESULT NavigationStarting(ICoreWebView2* sender, ICoreWebView2NavigationStartingEventArgs* args);
    HRESULT NavigationCompleted(ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args);
    void ResizeEverything();
    HRESULT DCompositionCreateDevice2(IUnknown* renderingDevice, REFIID riid, void** ppv);

    void Navigate(CWnd* parent, LPCWSTR url);
    void GoForward() { m_webView->GoForward(); }
    void GoBack() { m_webView->GoBack(); }
    void Execute(CString strFuncName, CString strText);
    void Execute(CString script);
    //
    //class CEdgeBrowserAppDlg* dlg_ = nullptr;
    //

    ICoreWebView2Controller* GetWebViewController()
    {
        return m_controller.get();
    }
    ICoreWebView2* GetWebView()
    {
        return m_webView.get();
    }
    ICoreWebView2Environment* GetWebViewEnvironment()
    {
        return m_webViewEnvironment.get();
    }

    template <class ComponentType, class... Args> void NewComponent(Args&&... args);
    template <class ComponentType> ComponentType* GetComponent();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnSize(UINT nType, int cx, int cy);
};



template <class ComponentType, class... Args> void CEdgeBrowser::NewComponent(Args&&... args)
{
    m_components.emplace_back(new ComponentType(std::forward<Args>(args)...));
}

template <class ComponentType> ComponentType* CEdgeBrowser::GetComponent()
{
    for (auto& component : m_components)
    {
        if (auto wanted = dynamic_cast<ComponentType*>(component.get()))
        {
            return wanted;
        }
    }
    return nullptr;
}
