// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXLayerBaseMan ���� Ŭ����

class CXLayerBaseMan : public COleDispatchDriver
{
public:
	CXLayerBaseMan(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXLayerBaseMan(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXLayerBaseMan(const CXLayerBaseMan& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXLayerBaseMan �޼���
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
	void ClearLayer()
	{
		InvokeHelper(0x3e9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH FindLayer(long ID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3ea, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ID);
		return result;
	}
	BOOL DeleteLayer(long ID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3eb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ID);
		return result;
	}
	LPDISPATCH NewLayer(long ID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3ec, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ID);
		return result;
	}
	LPDISPATCH FindObject(long LayerID, long LayerObjectID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3ed, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerID, LayerObjectID);
		return result;
	}
	LPDISPATCH NewObject(long LayerID, long ObjectID, long LayerObjectID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x3ee, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerID, ObjectID, LayerObjectID);
		return result;
	}
	BOOL DeleteObject(long LayerID, long LayerObjectID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3ef, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, LayerID, LayerObjectID);
		return result;
	}
	void ClearStyle()
	{
		InvokeHelper(0x3f0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH FindStyle(long ID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ID);
		return result;
	}
	LPDISPATCH NewStyle(long ID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ID);
		return result;
	}
	void DeleteStyle(long ID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID);
	}
	long GetStyleCount()
	{
		long result;
		InvokeHelper(0x3f4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH FindFont(long ID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ID);
		return result;
	}
	LPDISPATCH NewFont(long ID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ID);
		return result;
	}
	void DeleteFont(long ID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID);
	}
	void ClearFont()
	{
		InvokeHelper(0x3f8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long GetFontCount()
	{
		long result;
		InvokeHelper(0x3f9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	unsigned char GetStateMode()
	{
		unsigned char result;
		InvokeHelper(0x3fa, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetStateMode(unsigned char Mode)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x3fb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Mode);
	}
	LPDISPATCH HitTest(long X, long Y, BOOL VisibleOnly)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x3fc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, X, Y, VisibleOnly);
		return result;
	}
	LPDISPATCH NewShape(long LayerID, long LayerObjectID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3fd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerID, LayerObjectID);
		return result;
	}
	LPDISPATCH NewPolygon(long LayerID, long LayerObjectID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3fe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerID, LayerObjectID);
		return result;
	}
	LPDISPATCH NewTrackLog(long LayerID, long LayerObjectID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x3ff, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerID, LayerObjectID);
		return result;
	}
	LPDISPATCH NewCircle(long LayerID, long LayerObjectID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x400, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerID, LayerObjectID);
		return result;
	}
	LPDISPATCH NewDensity(long LayerID, long LayerObjectID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x401, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerID, LayerObjectID);
		return result;
	}
	LPDISPATCH NewTraffic(long LayerID, long LayerObjectID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x402, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, LayerID, LayerObjectID);
		return result;
	}
	long GetLayerCount()
	{
		long result;
		InvokeHelper(0x403, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GetLayer(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x404, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// IXLayerBaseMan �Ӽ�
public:

};
