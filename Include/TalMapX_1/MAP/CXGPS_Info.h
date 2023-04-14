// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXGPS_Info 래퍼 클래스

class CXGPS_Info : public COleDispatchDriver
{
public:
	CXGPS_Info(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXGPS_Info(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXGPS_Info(const CXGPS_Info& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXGPS_Info 메서드
public:
	LPDISPATCH GetGPS_Pos()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetGPS_Satellite(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long GetGPS_SatelliteCount()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXGPS_Info 속성
public:

};
