// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXIntIntegerMap 래퍼 클래스

class CXIntIntegerMap : public COleDispatchDriver
{
public:
	CXIntIntegerMap(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXIntIntegerMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXIntIntegerMap(const CXIntIntegerMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXIntIntegerMap 메서드
public:
	long GetItemCount()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long FindItemValue(long Key)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Key);
		return result;
	}
	BOOL InsertItem(long Key, long Value)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Key, Value);
		return result;
	}
	void DeleteItem(long Key)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Key);
	}
	void Clear()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IXIntIntegerMap 속성
public:

};
