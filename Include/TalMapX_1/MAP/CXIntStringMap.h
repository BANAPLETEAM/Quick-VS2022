// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXIntStringMap 래퍼 클래스

class CXIntStringMap : public COleDispatchDriver
{
public:
	CXIntStringMap(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXIntStringMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXIntStringMap(const CXIntStringMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXIntStringMap 메서드
public:
	long GetItemCount()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString FindItemValue(long Key)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Key);
		return result;
	}
	BOOL InsertItem(long Key, LPCTSTR Value)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
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

	// IXIntStringMap 속성
public:

};
