// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

//#import "C:\\Users\\TAEIN\\Documents\\eKsys\\Library\\DLL\\SmartSR\\SmartSRX_1.0.0.88.dll" no_namespace
// CXRouteMan 래퍼 클래스

class CXRouteMan : public COleDispatchDriver
{
public:
	CXRouteMan(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXRouteMan(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXRouteMan(const CXRouteMan& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXRouteMan 메서드
public:
	BOOL Local_OpenRPCost(LPCTSTR Path, long Type)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path, Type);
		return result;
	}
	BOOL Local_OpenNetMap(LPCTSTR Path, long Type)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path, Type);
		return result;
	}
	BOOL Remote_SetRPCType(long RouteType, long RoadType, long TollType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, RouteType, RoadType, TollType);
		return result;
	}
	BOOL Open(LPCTSTR Path, long Value)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path, Value);
		return result;
	}
	void SetOrgLonLat(long Lon, long Lat)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Lon, Lat);
	}
	long GetOrgLon()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetOrgLat()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetDstLonLat(long Lon, long Lat)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Lon, Lat);
	}
	long GetDstLon()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetDstLat()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void AddNode(long Lon, long Lat)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Lon, Lat);
	}
	void RemoveNode(long Lon, long Lat)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Lon, Lat);
	}
	void ClearNode()
	{
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Clear()
	{
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH SearchRoute1()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH SearchRoute2()
	{
		LPDISPATCH result;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetOrgDirection(unsigned char Direction)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction);
	}
	void SetOrgDirectionToBoth()
	{
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	unsigned char GetOrgDirection()
	{
		unsigned char result;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetViaDirection(unsigned char Direction)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction);
	}
	void SetViaDirectionToBoth()
	{
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	unsigned char GetViaDirection()
	{
		unsigned char result;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetDstDirection(unsigned char Direction)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction);
	}
	void SetDstDirectionToBoth()
	{
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	unsigned char GetDstDirection()
	{
		unsigned char result;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH SearchRoute3()
	{
		LPDISPATCH result;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH SearchRoute4()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetTollFareType(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	BOOL Local_OpenTollFare(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	LPDISPATCH SearchMSRoute1()
	{
		LPDISPATCH result;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void ReleaseRouteMan()
	{
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IXRouteMan 속성
public:

};
