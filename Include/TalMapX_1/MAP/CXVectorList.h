// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXVectorList 래퍼 클래스

class CXVectorList : public COleDispatchDriver
{
public:
	CXVectorList(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXVectorList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXVectorList(const CXVectorList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXVectorList 메서드
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
	long Add(LPDISPATCH Vec)
	{
		long result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Vec);
		return result;
	}
	long Insert(long Index, LPDISPATCH Vec)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index, Vec);
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

	// IXVectorList 속성
public:

};
