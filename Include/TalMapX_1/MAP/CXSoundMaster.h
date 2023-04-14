// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXSoundMaster 래퍼 클래스

class CXSoundMaster : public COleDispatchDriver
{
public:
	CXSoundMaster(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXSoundMaster(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXSoundMaster(const CXSoundMaster& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXSoundMaster 메서드
public:
	BOOL Create(long MaxStockSound)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, MaxStockSound);
		return result;
	}
	void DestroySoundMaster()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL IsActive()
	{
		BOOL result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void StockSound_Clear()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long StockSound_LoadBuf(signed char * Buf, long Len)
	{
		long result;
		static BYTE parms[] = VTS_PI1 VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Buf, Len);
		return result;
	}
	long StockSound_Load(LPCTSTR Path)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Path);
		return result;
	}
	long StockSound_LoadFromEKR(long * Value, LPCTSTR Name, long EKRIndex)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_BSTR VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value, Name, EKRIndex);
		return result;
	}
	void StockSound_Delete(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	BOOL StockSound_IsValid(long Index)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Index);
		return result;
	}
	BOOL StockSound_Play(long Index, long Type)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Index, Type);
		return result;
	}

	// IXSoundMaster 속성
public:

};
