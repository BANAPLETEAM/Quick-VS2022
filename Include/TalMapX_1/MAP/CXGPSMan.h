// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXGPSMan 래퍼 클래스

class CXGPSMan : public COleDispatchDriver
{
public:
	CXGPSMan(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXGPSMan(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXGPSMan(const CXGPSMan& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXGPSMan 메서드
public:
	void Close()
	{
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL OpenFile(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	BOOL OpenPort(long Port, long BaudRate, unsigned char ByteSize, unsigned char Parity, unsigned char StopBits)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI1 VTS_UI1 VTS_UI1 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Port, BaudRate, ByteSize, Parity, StopBits);
		return result;
	}
	BOOL ReadFile(LPCTSTR Path, long Type)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path, Type);
		return result;
	}
	BOOL IsActive()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetGPSInfo()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString GetPortList(long Type)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Type);
		return result;
	}
	long SetInterval(long Microsec)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Microsec);
		return result;
	}
	long GetInterval()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetLoop(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetLoop()
	{
		long result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL SetLogFile(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	void CloseLogFile()
	{
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL IsActiveLogFile()
	{
		BOOL result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void ClearGPSLogList()
	{
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long SetEnableLog(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetEnableLog()
	{
		long result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetViewGPSLog(LPDISPATCH Image, long Type, long UseAngle, long Scale, long Alpha)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Image, Type, UseAngle, Scale, Alpha);
	}
	void AddGPSLogList(VARIANT * Time, long Lon, long Lat, long Angle, long Speed)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Time, Lon, Lat, Angle, Speed);
	}
	LPDISPATCH GetSatelliteDPPos(LPDISPATCH Sat, float Radius, LPDISPATCH Offset)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_R4 VTS_DISPATCH ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Sat, Radius, Offset);
		return result;
	}

	// IXGPSMan 속성
public:

};
