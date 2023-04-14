// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXVector 래퍼 클래스

class CXVector : public COleDispatchDriver
{
public:
	CXVector(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXVector(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXVector(const CXVector& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXVector 메서드
public:
	void SetX(double Value)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	double GetX()
	{
		double result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double get__X()
	{
		double result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put__X(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SetY(double Value)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	double GetY()
	{
		double result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double get__Y()
	{
		double result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put__Y(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SetZ(double Value)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	double GetZ()
	{
		double result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double get__Z()
	{
		double result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put__Z(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SetW(double Value)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	double GetW()
	{
		double result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double get__W()
	{
		double result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	void put__W(double newValue)
	{
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// IXVector 속성
public:

};
