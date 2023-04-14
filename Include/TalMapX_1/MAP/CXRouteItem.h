// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXRouteItem 래퍼 클래스

class CXRouteItem : public COleDispatchDriver
{
public:
	CXRouteItem(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXRouteItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXRouteItem(const CXRouteItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXRouteItem 메서드
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
	long GetID()
	{
		long result;
		InvokeHelper(0x1b59, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCurrentItem()
	{
		InvokeHelper(0x1b5a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Clear()
	{
		InvokeHelper(0x1b5b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearFlag()
	{
		InvokeHelper(0x1b5c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearPath()
	{
		InvokeHelper(0x1b5d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH AddOrigin(long Lon, long Lat, unsigned char DirType)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI1 ;
		InvokeHelper(0x1b5e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat, DirType);
		return result;
	}
	LPDISPATCH AddVia(long Lon, long Lat, unsigned char DirType)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI1 ;
		InvokeHelper(0x1b5f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat, DirType);
		return result;
	}
	LPDISPATCH AddDestination(long Lon, long Lat, unsigned char DirType)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI1 ;
		InvokeHelper(0x1b60, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat, DirType);
		return result;
	}
	void ClearOriginFlag()
	{
		InvokeHelper(0x1b61, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearViaFlag()
	{
		InvokeHelper(0x1b62, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearDestinationFlag()
	{
		InvokeHelper(0x1b63, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH LoadCost(LPCTSTR Path, long Type)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1b64, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Path, Type);
		return result;
	}
	void FreeCost(LPDISPATCH Cost)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1b65, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cost);
	}
	BOOL FindPath(LPDISPATCH Cost, long Type)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x1b66, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Cost, Type);
		return result;
	}
	BOOL SetSourceInfo(LPCTSTR Path, long Type)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1b67, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path, Type);
		return result;
	}
	void ReleaseSource()
	{
		InvokeHelper(0x1b68, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long GetLength()
	{
		long result;
		InvokeHelper(0x1b69, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTravelTime()
	{
		long result;
		InvokeHelper(0x1b6a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetLayerStyle(LPDISPATCH LayerStyle)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1b6b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LayerStyle);
	}
	LPDISPATCH GetLayerStyle()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b6c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapRect()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b6d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// IXRouteItem 속성
public:

};
