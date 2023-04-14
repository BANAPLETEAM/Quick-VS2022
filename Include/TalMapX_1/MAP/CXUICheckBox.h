// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXUICheckBox 래퍼 클래스

class CXUICheckBox : public COleDispatchDriver
{
public:
	CXUICheckBox(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXUICheckBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXUICheckBox(const CXUICheckBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXUICheckBox 메서드
public:
	void SetVisible(unsigned char newVal)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2329, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newVal);
	}
	unsigned char GetVisible()
	{
		unsigned char result;
		InvokeHelper(0x232a, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetVisibleLevel(unsigned char Level, unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 VTS_UI1 ;
		InvokeHelper(0x232b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Level, Value);
	}
	unsigned char GetVisibleLevel(unsigned char Level)
	{
		unsigned char result;
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232c, DISPATCH_METHOD, VT_UI1, (void*)&result, parms, Level);
		return result;
	}
	void SetShowCaption(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowCaption()
	{
		long result;
		InvokeHelper(0x232e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetShowImage(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowImage()
	{
		long result;
		InvokeHelper(0x2330, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetShowHint(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2331, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowHint()
	{
		long result;
		InvokeHelper(0x2332, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetSelected(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2333, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetSelected()
	{
		long result;
		InvokeHelper(0x2334, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanClick(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2335, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanClick()
	{
		long result;
		InvokeHelper(0x2336, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanSelect(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2337, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanSelect()
	{
		long result;
		InvokeHelper(0x2338, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanFocus(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2339, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanFocus()
	{
		long result;
		InvokeHelper(0x233a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetCursor(unsigned char Value)
	{
		long result;
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x233b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetCursor()
	{
		long result;
		InvokeHelper(0x233c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetObjectID()
	{
		long result;
		InvokeHelper(0x1f41, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IsObjectID(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f42, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	void Register_TimerEvent(long Interval, long Continue_Event, long ID)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1f43, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Interval, Continue_Event, ID);
	}
	void Unregister_TimerEvent(long ID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f44, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID);
	}
	long SetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1f45, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	long GetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1f46, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	BOOL IsModified()
	{
		BOOL result;
		InvokeHelper(0x2135, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL IsUpdating()
	{
		BOOL result;
		InvokeHelper(0x2136, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void BeginUpdate()
	{
		InvokeHelper(0x2137, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EndUpdate()
	{
		InvokeHelper(0x2138, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetModified(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2139, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newValue);
	}
	long GetModified()
	{
		long result;
		InvokeHelper(0x213a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetEventMode(long Type)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x213b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type);
		return result;
	}
	void SetEventMode(long Mode)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x213c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Mode);
	}
	void AddEventMode(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x213d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	void DeleteEventMode(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x213e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	void SetData(long * Value)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x213f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetData()
	{
		long result;
		InvokeHelper(0x2140, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetTag(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2141, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetTag()
	{
		long result;
		InvokeHelper(0x2142, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetString(LPCTSTR Str)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2143, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Str);
	}
	CString GetString()
	{
		CString result;
		InvokeHelper(0x2144, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void DestroyUIObj()
	{
		InvokeHelper(0x1b59, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetNativeEventNotify(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b60, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetNativeEventNotify()
	{
		long result;
		InvokeHelper(0x1b61, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetFont(long Height, unsigned char Style, LPCTSTR Name, unsigned char Quality)
	{
		static BYTE parms[] = VTS_I4 VTS_UI1 VTS_BSTR VTS_UI1 ;
		InvokeHelper(0x1b62, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Height, Style, Name, Quality);
	}
	void SetBrush(long Style, unsigned long Color, long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 VTS_I4 ;
		InvokeHelper(0x1b63, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Color, Value);
	}
	void SetPen(long Style, long Width, unsigned long Color)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4 ;
		InvokeHelper(0x1b64, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Width, Color);
	}
	void SetEnabled(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b65, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetEnabled()
	{
		long result;
		InvokeHelper(0x1b66, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetLeft(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b67, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetLeft()
	{
		long result;
		InvokeHelper(0x1b68, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetTop(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b69, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetTop()
	{
		long result;
		InvokeHelper(0x1b6a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetWidth(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b6b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetWidth()
	{
		long result;
		InvokeHelper(0x1b6c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetHeight(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b6d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetHeight()
	{
		long result;
		InvokeHelper(0x1b6e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetUIID(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b6f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetUIID()
	{
		long result;
		InvokeHelper(0x1b70, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetTransparent(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b71, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetTransparent()
	{
		long result;
		InvokeHelper(0x1b72, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetAnchor(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b73, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetAnchor()
	{
		long result;
		InvokeHelper(0x1b74, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetUIObjFontColor(unsigned long Value)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1b75, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned long GetUIObjFontColor()
	{
		unsigned long result;
		InvokeHelper(0x1b76, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void SetCaption(LPCTSTR Value)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b77, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	CString GetCaption()
	{
		CString result;
		InvokeHelper(0x1b78, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetAutoSize(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b79, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetAutoSize()
	{
		long result;
		InvokeHelper(0x1b7a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCaptionStyle(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b7b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCaptionStyle()
	{
		long result;
		InvokeHelper(0x1b7c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetCaptionSize()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b7d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetName(LPCTSTR Value)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b7e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	CString GetName()
	{
		CString result;
		InvokeHelper(0x1b7f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetBound(long Left, long Top, long Width, long Height)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b80, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Left, Top, Width, Height);
	}
	LPDISPATCH GetClientRect()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b81, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH ScreenToClient(long X, long Y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b82, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, X, Y);
		return result;
	}
	LPDISPATCH ClientToScreen(long X, long Y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b83, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, X, Y);
		return result;
	}
	BOOL IsFocused()
	{
		BOOL result;
		InvokeHelper(0x1b84, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL IsOnMouse()
	{
		BOOL result;
		InvokeHelper(0x1b85, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL IsParent(LPDISPATCH Obj)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1b86, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Obj);
		return result;
	}
	void SetDisplayClipping(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b87, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetDisplayClipping()
	{
		long result;
		InvokeHelper(0x1b88, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetParent()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b89, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetParent(LPDISPATCH Parent)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1b8a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Parent);
	}
	void SetAngle(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b8b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetAngle()
	{
		long result;
		InvokeHelper(0x1b8c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetScale(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x1b8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetScale()
	{
		unsigned char result;
		InvokeHelper(0x1b8e, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetAlpha(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x1b8f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetAlpha()
	{
		unsigned char result;
		InvokeHelper(0x1b90, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetParentAlpha(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x1b91, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetParentAlpha()
	{
		unsigned char result;
		InvokeHelper(0x1b92, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetChildByUIID(long Value)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b93, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Value);
		return result;
	}
	long GetChildCount()
	{
		long result;
		InvokeHelper(0x1b94, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetControlCount()
	{
		long result;
		InvokeHelper(0x1b95, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long CreateChildFromEKResource(LPCTSTR Path)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b96, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Path);
		return result;
	}
	void DeleteChildAll()
	{
		InvokeHelper(0x1b97, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DeleteControlAll()
	{
		InvokeHelper(0x1b98, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MoveTo(long X, long Y, long Async, long Step, long Wait)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b99, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X, Y, Async, Step, Wait);
	}
	void ResizeTo(long Width, long Height, long Slide)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b9a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Width, Height, Slide);
	}
	LPDISPATCH GetDPOffset()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b9b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetDPOffset(long osX, long osY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b9c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, osX, osY);
	}
	void Update()
	{
		InvokeHelper(0x1b9d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long SetBackColor(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b9e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetBackColor()
	{
		long result;
		InvokeHelper(0x1b9f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetLineColor(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1ba0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetLineColor()
	{
		long result;
		InvokeHelper(0x1ba1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetLineWidth(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1ba2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetLineWidth()
	{
		long result;
		InvokeHelper(0x1ba3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetTextStyle(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1ba4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetTextStyle()
	{
		long result;
		InvokeHelper(0x1ba5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetTextAlign(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1ba6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetTextAlign()
	{
		long result;
		InvokeHelper(0x1ba7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetTextVAlign(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1ba8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetTextVAlign()
	{
		long result;
		InvokeHelper(0x1ba9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetTextMultiline(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1baa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetTextMultiline()
	{
		long result;
		InvokeHelper(0x1bab, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetUseAlphaClick(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1bac, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetUseAlphaClick()
	{
		long result;
		InvokeHelper(0x1bad, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetCanDrag(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1bae, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetCanDrag()
	{
		long result;
		InvokeHelper(0x1baf, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetDragTracker(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1bb0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetDragTracker()
	{
		long result;
		InvokeHelper(0x1bb1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetCustomDraw_Before(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1bb2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetCustomDraw_Before()
	{
		long result;
		InvokeHelper(0x1bb3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetCustomDraw_After(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1bb4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetCustomDraw_After()
	{
		long result;
		InvokeHelper(0x1bb5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetHint(LPCTSTR Value)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1bb6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	CString GetHint()
	{
		CString result;
		InvokeHelper(0x1bb7, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL SetImage(LPCTSTR ImagePath)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1771, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ImagePath);
		return result;
	}
	BOOL SetImageList(LPCTSTR ImagePath, long ItemWidth, long ItemHeight)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x1772, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ImagePath, ItemWidth, ItemHeight);
		return result;
	}
	LPDISPATCH GetImageList()
	{
		LPDISPATCH result;
		InvokeHelper(0x1773, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetImageList2(LPDISPATCH ImageList)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1774, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ImageList);
	}
	long SetItemWidth(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1775, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetItemWidth()
	{
		long result;
		InvokeHelper(0x1776, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetItemHeight(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1777, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetItemHeight()
	{
		long result;
		InvokeHelper(0x1778, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetItemIndex(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1779, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetItemIndex()
	{
		long result;
		InvokeHelper(0x177a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetChecked(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1389, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetChecked()
	{
		long result;
		InvokeHelper(0x138a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXUICheckBox 속성
public:

};
