// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXValue 래퍼 클래스

class CXValue : public COleDispatchDriver
{
public:
	CXValue(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXValue(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXValue(const CXValue& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXValue 메서드
public:
	void SetI(long Index, long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	long GetI(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	void SetD(long Index, double Value)
	{
		static BYTE parms[] = VTS_I4 VTS_R8 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	double GetD(long Index)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Index);
		return result;
	}
	void SetV(long Index, long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	long GetV(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	CString GetVAsString(long Index, long Len)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index, Len);
		return result;
	}

	// IXValue 속성
public:

};
