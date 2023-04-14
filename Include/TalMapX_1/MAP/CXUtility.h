// CXUtility.h  : Microsoft Visual C++로 만든 ActiveX 컨트롤 래퍼 클래스의 선언입니다.

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CXUtility

class CXUtility : public COleDispatchDriver
{
public:
	CXUtility() {}		// COleDispatchDriver 기본 생성자를 호출합니다.
	CXUtility(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXUtility(const CXUtility& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성입니다.
public:

	// 작업입니다.
public:

	CString GetRootDir()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long GetAvailableMemory(LPCTSTR Title)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Title);
		return result;
	}
	LPDISPATCH GetDPOnMapRect(long LLon, long RLon, long LLat, long ULat, long DPWidth, long DPHeight, long Lon, long Lat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LLon, RLon, LLat, ULat, DPWidth, DPHeight, Lon, Lat);
		return result;
	}
	LPDISPATCH GetLLOnMapRect(long LLon, long RLon, long LLat, long ULat, long DPWidth, long DPHeight, long X, long Y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LLon, RLon, LLat, ULat, DPWidth, DPHeight, X, Y);
		return result;
	}
	long RGBColor(long R, long G, long B)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, R, G, B);
		return result;
	}
	long RGBAColor(long R, long G, long B, long A)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, R, G, B, A);
		return result;
	}
	long GetRedValue(long Color)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Color);
		return result;
	}
	long GetGreenValue(long Color)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Color);
		return result;
	}
	long GetBlueValue(long Color)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Color);
		return result;
	}
	CString ExpandFileName(LPCTSTR FileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, FileName);
		return result;
	}
	CString ExtractFileExt(LPCTSTR FileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, FileName);
		return result;
	}
	CString ExtractFileName(LPCTSTR FileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, FileName);
		return result;
	}
	CString ExtractFilePath(LPCTSTR FileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, FileName);
		return result;
	}
	BOOL DirectoryExists(LPCTSTR Dir)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Dir);
		return result;
	}
	BOOL FileExists(LPCTSTR Path)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Path);
		return result;
	}
	BOOL TextToClipboard(LPCTSTR Text)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Text);
		return result;
	}
	long AttachEKR(LPCTSTR Path)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Path);
		return result;
	}
	void DetachEKR(long * Value)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetConstToValue(LPCTSTR Value)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	CString FileDialog(LPCTSTR Title, LPCTSTR Path, LPCTSTR FileName, LPCTSTR Filter)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Title, Path, FileName, Filter);
		return result;
	}
	CString SaveImageDialog(LPCTSTR Path, LPCTSTR FileName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Path, FileName);
		return result;
	}
	CString GetCurrentDir()
	{
		CString result;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	double GetAngleFromLine(LPDISPATCH Pos1, LPDISPATCH Pos2)
	{
		double result;
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Pos1, Pos2);
		return result;
	}
	LPDISPATCH GetMapRect()
	{
		LPDISPATCH result;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapPos()
	{
		LPDISPATCH result;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapPos3D()
	{
		LPDISPATCH result;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetCtrlRect()
	{
		LPDISPATCH result;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetPoint(long X, long Y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, X, Y);
		return result;
	}
	LPDISPATCH GetRect(long Left, long Top, long Right, long Bottom)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Left, Top, Right, Bottom);
		return result;
	}
	LPDISPATCH GetSize(long Width, long Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Width, Height);
		return result;
	}
	LPDISPATCH GetValue()
	{
		LPDISPATCH result;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetPointList()
	{
		LPDISPATCH result;
		InvokeHelper(0x79, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetMapPosList()
	{
		LPDISPATCH result;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetVectorList()
	{
		LPDISPATCH result;
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetIntIntegerMap()
	{
		LPDISPATCH result;
		InvokeHelper(0x83, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetIntStringMap()
	{
		LPDISPATCH result;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetStrIntegerMap()
	{
		LPDISPATCH result;
		InvokeHelper(0x85, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetStrStringMap()
	{
		LPDISPATCH result;
		InvokeHelper(0x86, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetVector()
	{
		LPDISPATCH result;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}


};
