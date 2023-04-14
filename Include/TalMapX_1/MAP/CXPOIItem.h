// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXPOIItem 래퍼 클래스

class CXPOIItem : public COleDispatchDriver
{
public:
	CXPOIItem(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXPOIItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXPOIItem(const CXPOIItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXPOIItem 메서드
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
	long GetID()
	{
		long result;
		InvokeHelper(0x3e9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetStyle(LPDISPATCH Style)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x3ea, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
	}
	LPDISPATCH GetStyle()
	{
		LPDISPATCH result;
		InvokeHelper(0x3eb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void ClearStyle()
	{
		InvokeHelper(0x3ec, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH CreatePrivateStyle()
	{
		LPDISPATCH result;
		InvokeHelper(0x3ed, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetGroup()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL SetImage(LPDISPATCH Image)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Image);
		return result;
	}
	long SetImageIndex(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetImageIndex()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetImageOffset(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetImageOffset()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetTextStyle(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetTextStyle()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetCaption(LPCTSTR Value)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	CString GetCaption()
	{
		CString result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long SetContents(LPCTSTR Value)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	CString GetContents()
	{
		CString result;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetLonLat(long Lon, long Lat)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Lon, Lat);
	}
	LPDISPATCH GetLonLat()
	{
		LPDISPATCH result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long SetAnimation(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetAnimation()
	{
		long result;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetAngle(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetAngle()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetSyncAngle(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetSyncAngle()
	{
		long result;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetScale(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetScale()
	{
		long result;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetAlpha(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetAlpha()
	{
		long result;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetPerspectiveImage(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetPerspectiveImage()
	{
		long result;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH CreateInfoBox(long Type, LPCTSTR Caption, LPCTSTR Contents, BOOL ShowDetail, BOOL ShowMenu)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Caption, Contents, ShowDetail, ShowMenu);
		return result;
	}
	LPDISPATCH GetInfoBox()
	{
		LPDISPATCH result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void DestroyInfoBox()
	{
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH GetMapChart()
	{
		LPDISPATCH result;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void DestroyMapChart()
	{
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH CreateChart_Pie(long Type)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type);
		return result;
	}
	LPDISPATCH CreateChart_Bar(long Type)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type);
		return result;
	}

	// IXPOIItem 속성
public:

};
