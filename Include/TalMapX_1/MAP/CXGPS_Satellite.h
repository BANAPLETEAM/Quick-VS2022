// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXGPS_Satellite 래퍼 클래스

class CXGPS_Satellite : public COleDispatchDriver
{
public:
	CXGPS_Satellite(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXGPS_Satellite(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXGPS_Satellite(const CXGPS_Satellite& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXGPS_Satellite 메서드
public:
	unsigned char GetUsedForFix()
	{
		unsigned char result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetSatelliteID()
	{
		unsigned char result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	unsigned char GetElevation()
	{
		unsigned char result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	long GetAzimuth()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetSnr()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXGPS_Satellite 속성
public:

};
