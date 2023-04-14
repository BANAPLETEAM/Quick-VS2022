// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXGPS_Pos 래퍼 클래스

class CXGPS_Pos : public COleDispatchDriver
{
public:
	CXGPS_Pos(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXGPS_Pos(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXGPS_Pos(const CXGPS_Pos& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXGPS_Pos 메서드
public:
	VARIANT GetTime()
	{
		VARIANT result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	CString GetTimeToStr()
	{
		CString result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetTimeAsSystemTime()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapPos()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	double GetSpeed()
	{
		double result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetAltitude()
	{
		double result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetAngle()
	{
		double result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	unsigned char GetFixMode()
	{
		unsigned char result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	double GetPDop()
	{
		double result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetHDop()
	{
		double result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double GetVDop()
	{
		double result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}

	// IXGPS_Pos 속성
public:

};
