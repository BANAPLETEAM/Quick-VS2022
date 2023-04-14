// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

//#import "C:\\Users\\TAEIN\\Documents\\eKsys\\Library\\DLL\\SmartSR\\SmartSRX_1.0.0.88.dll" no_namespace
// CXRouteInfo3 래퍼 클래스

class CXRouteInfo3 : public COleDispatchDriver
{
public:
	CXRouteInfo3(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXRouteInfo3(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXRouteInfo3(const CXRouteInfo3& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXRouteInfo3 메서드
public:
	long GetResult()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTotalDistance()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTotalTime()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetTotalToll()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXRouteInfo3 속성
public:

};
