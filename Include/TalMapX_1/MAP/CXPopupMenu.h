// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXPopupMenu 래퍼 클래스

class CXPopupMenu : public COleDispatchDriver
{
public:
	CXPopupMenu(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXPopupMenu(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXPopupMenu(const CXPopupMenu& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXPopupMenu 메서드
public:
	BOOL Create()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void DestroyPopupMenu()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH AppendString(long ID, LPCTSTR Caption, LPCTSTR Hint, LPCTSTR Contents, long Data)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ID, Caption, Hint, Contents, Data);
		return result;
	}
	LPDISPATCH AppendSeparator()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH AppendSubMenu(LPCTSTR Caption, LPCTSTR Hint)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Caption, Hint);
		return result;
	}
	LPDISPATCH TrackPopupMenu(long Flags, long X, long Y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Flags, X, Y);
		return result;
	}
	LPDISPATCH GetMenuItem(long ItemID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ItemID);
		return result;
	}

	// IXPopupMenu 속성
public:

};
