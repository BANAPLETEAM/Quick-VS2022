// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

//#import "C:\\Users\\TAEIN\\Documents\\eKsys\\Library\\DLL\\SmartSR\\SmartSRX_1.0.0.88.dll" no_namespace
// CXCoordSys 래퍼 클래스

class CXCoordSys : public COleDispatchDriver
{
public:
	CXCoordSys(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXCoordSys(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXCoordSys(const CXCoordSys& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXCoordSys 메서드
public:
	LPDISPATCH BesselToWGS84(long Lon, long Lat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat);
		return result;
	}
	LPDISPATCH WGS84ToBessel(long Lon, long Lat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat);
		return result;
	}
	LPDISPATCH WGS84ToTM(long Lon, long Lat, long Param)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat, Param);
		return result;
	}
	LPDISPATCH TMToWGS84(long TMX, long TMY, long Param)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, TMX, TMY, Param);
		return result;
	}
	LPDISPATCH BesselToTM(long Lon, long Lat, long Param)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat, Param);
		return result;
	}
	LPDISPATCH TMToBessel(long TMX, long TMY, long Param)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, TMX, TMY, Param);
		return result;
	}
	LPDISPATCH BesselToKatec(long Lon, long Lat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Lon, Lat);
		return result;
	}
	LPDISPATCH KatecToBessel(long TMX, long TMY)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, TMX, TMY);
		return result;
	}

	// IXCoordSys 속성
public:

};
