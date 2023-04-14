// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXStrIntegerMap 래퍼 클래스

class CXStrIntegerMap : public COleDispatchDriver
{
public:
	CXStrIntegerMap(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXStrIntegerMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXStrIntegerMap(const CXStrIntegerMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXStrIntegerMap 메서드
public:
	long GetItemCount()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long FindItemValue(LPCTSTR Key)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Key);
		return result;
	}
	BOOL InsertItem(LPCTSTR Key, long Value)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Key, Value);
		return result;
	}
	void DeleteItem(LPCTSTR Key)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Key);
	}
	void Clear()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IXStrIntegerMap 속성
public:

};
