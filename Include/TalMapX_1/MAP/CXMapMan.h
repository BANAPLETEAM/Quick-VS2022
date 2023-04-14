// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXMapMan ���� Ŭ����

class CXMapMan : public COleDispatchDriver
{
public:
	CXMapMan(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXMapMan(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMapMan(const CXMapMan& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXMapMan �޼���
public:
	void SetVisible(unsigned char newVal)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2329, DISPATCH_METHOD, VT_EMPTY, NULL, parms, newVal);
	}
	unsigned char GetVisible()
	{
		unsigned char result;
		InvokeHelper(0x232a, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetVisibleLevel(unsigned char Level, unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 VTS_UI1 ;
		InvokeHelper(0x232b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Level, Value);
	}
	unsigned char GetVisibleLevel(unsigned char Level)
	{
		unsigned char result;
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232c, DISPATCH_METHOD, VT_UI1, (void*)&result, parms, Level);
		return result;
	}
	void SetShowCaption(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowCaption()
	{
		long result;
		InvokeHelper(0x232e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetShowImage(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x232f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowImage()
	{
		long result;
		InvokeHelper(0x2330, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetShowHint(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2331, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetShowHint()
	{
		long result;
		InvokeHelper(0x2332, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetSelected(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2333, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetSelected()
	{
		long result;
		InvokeHelper(0x2334, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanClick(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2335, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanClick()
	{
		long result;
		InvokeHelper(0x2336, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanSelect(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2337, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanSelect()
	{
		long result;
		InvokeHelper(0x2338, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetCanFocus(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2339, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetCanFocus()
	{
		long result;
		InvokeHelper(0x233a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetCursor(unsigned char Value)
	{
		long result;
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x233b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetCursor()
	{
		long result;
		InvokeHelper(0x233c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetObjectID()
	{
		long result;
		InvokeHelper(0x1f41, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IsObjectID(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f42, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	void Register_TimerEvent(long Interval, long Continue_Event, long ID)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1f43, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Interval, Continue_Event, ID);
	}
	void Unregister_TimerEvent(long ID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f44, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID);
	}
	long SetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1f45, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	long GetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1f46, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	long BaseManSetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1b59, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	long BaseManGetValue(long Type, long Code, LPDISPATCH Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_DISPATCH ;
		InvokeHelper(0x1b5a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Type, Code, Value);
		return result;
	}
	BOOL SetDefaultPath(LPCTSTR newVal)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b5b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, newVal);
		return result;
	}
	CString GetDefaultPath()
	{
		CString result;
		InvokeHelper(0x1b5c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ExpandDefaultPath(LPCTSTR Path)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b5d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Path);
		return result;
	}
	void SetManMode(long Mode)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b5e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Mode);
	}
	long GetManMode()
	{
		long result;
		InvokeHelper(0x1b5f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL IsManMode(long Mode)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b60, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Mode);
		return result;
	}
	void BaseManSetString(long Type, long Code, LPCTSTR Str)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x1b61, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Code, Str);
	}
	long SetMapData(LPCTSTR Value, long Type)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value, Type);
		return result;
	}
	void ClearCache()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long SetMeshCapacity(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetMeshCapacity()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long SetShowLandMarkSymbol(long Value)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Value);
		return result;
	}
	long GetShowLandMarkSymbol()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL SetCachePath(LPCTSTR FullPath)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FullPath);
		return result;
	}
	void ClearCachePath()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL GetTextInfoByNear(long Level, LPDISPATCH Value, long Lon, long Lat, BOOL Visible, double Distance)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_DISPATCH VTS_I4 VTS_I4 VTS_BOOL VTS_R8 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Level, Value, Lon, Lat, Visible, Distance);
		return result;
	}
	BOOL GetTextInfo(LPDISPATCH Value, long Lon, long Lat, BOOL Visible)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Value, Lon, Lat, Visible);
		return result;
	}

	// IXMapMan �Ӽ�
public:

};