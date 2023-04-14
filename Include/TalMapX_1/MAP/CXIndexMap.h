// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXIndexMap 래퍼 클래스

class CXIndexMap : public COleDispatchDriver
{
public:
	CXIndexMap(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXIndexMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXIndexMap(const CXIndexMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXIndexMap 메서드
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
	BOOL IsMinimized()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetMinimize()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetNormal()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetAreaCount(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long SetAreaInfo(long ID, LPCTSTR Name, LPCTSTR Code, long ImageIndex, LPDISPATCH MapRect)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID, Name, Code, ImageIndex, MapRect);
		return result;
	}
	BOOL SetAreaImage(LPCTSTR FullPath)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FullPath);
		return result;
	}
	BOOL ShowIndexMap()
	{
		BOOL result;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL HideIndexMap()
	{
		BOOL result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetIndexMapSize(long Width, long Height)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Width, Height);
	}
	long SetIndexMapLeft(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetIndexMapLeft()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetIndexMapTop(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetIndexMapTop()
	{
		long result;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetIndexMapWidth(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetIndexMapWidth()
	{
		long result;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetIndexMapHeight(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetIndexMapHeight()
	{
		long result;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL IsIndexMapVisible()
	{
		BOOL result;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}

	// IXIndexMap 속성
public:

};
