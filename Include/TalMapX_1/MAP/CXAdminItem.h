// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXAdminItem 래퍼 클래스

class CXAdminItem : public COleDispatchDriver
{
public:
	CXAdminItem(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXAdminItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXAdminItem(const CXAdminItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXAdminItem 메서드
public:
	void Destroy()
	{
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString GetAdminName(LPCTSTR Sep, long Type)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Sep, Type);
		return result;
	}
	CString GetAdminCode()
	{
		CString result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetCenterPos(long Type)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type);
		return result;
	}
	BOOL InAdmin(long Lon, long Lat)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Lon, Lat);
		return result;
	}
	void GotoCenter(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}

	// IXAdminItem 속성
public:

};
