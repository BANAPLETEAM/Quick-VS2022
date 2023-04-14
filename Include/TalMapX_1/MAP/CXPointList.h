// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXPointList 래퍼 클래스

class CXPointList : public COleDispatchDriver
{
public:
	CXPointList(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXPointList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXPointList(const CXPointList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXPointList 메서드
public:
	long Count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH First()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH Last()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Clear()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long Add(LPDISPATCH Point)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Point);
		return result;
	}
	long Insert(long Index, LPDISPATCH Point)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index, Point);
		return result;
	}
	long Delete(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	LPDISPATCH Value(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// IXPointList 속성
public:

};
