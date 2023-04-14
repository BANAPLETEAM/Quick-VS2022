// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXLayerDensity 래퍼 클래스

class CXLayerDensity : public COleDispatchDriver
{
public:
	CXLayerDensity(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXLayerDensity(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXLayerDensity(const CXLayerDensity& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXLayerDensity 메서드
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
		InvokeHelper(0x1b59, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetStyle(LPDISPATCH Style)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1b5a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style);
	}
	LPDISPATCH GetStyle()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b5b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void NeedUpdate()
	{
		InvokeHelper(0x1b5c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetHint(LPCTSTR Hint)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b5d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Hint);
	}
	CString GetHint()
	{
		CString result;
		InvokeHelper(0x1b5e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetHintContents(LPCTSTR HintContents)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b5f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HintContents);
	}
	CString GetHintContents()
	{
		CString result;
		InvokeHelper(0x1b60, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void DestroyLayerObject()
	{
		InvokeHelper(0x1771, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long HitTest(long X, long Y)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1772, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	void ShiftTo(LPDISPATCH Offset)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1773, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Offset);
	}
	long PtInObject(long Lon, long Lat)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1774, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Lon, Lat);
		return result;
	}
	void FreeObject()
	{
		InvokeHelper(0x1775, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetStateModeNew()
	{
		InvokeHelper(0x1776, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetIndex(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1777, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	long GetIndex()
	{
		long result;
		InvokeHelper(0x1778, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetLayer()
	{
		LPDISPATCH result;
		InvokeHelper(0x1779, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long GetLayerID()
	{
		long result;
		InvokeHelper(0x177a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long AddValue(long Lon, long Lat, double Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 ;
		InvokeHelper(0x1389, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Lon, Lat, Value);
		return result;
	}
	void ClearValue()
	{
		InvokeHelper(0x138a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void GenerateDensity(long Distance, long Size)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x138b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Distance, Size);
	}
	void SetColor(long C1, long C2, long C3)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x138c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, C1, C2, C3);
	}

	// IXLayerDensity 속성
public:

};
