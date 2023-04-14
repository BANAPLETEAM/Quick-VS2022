// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXRouteFlag ���� Ŭ����

class CXRouteFlag : public COleDispatchDriver
{
public:
	CXRouteFlag(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXRouteFlag(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXRouteFlag(const CXRouteFlag& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXRouteFlag �޼���
public:
	void SetPOIStyle(LPDISPATCH POIStyle)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, POIStyle);
	}
	LPDISPATCH GetPOIStyle()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void SetImageOffset(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetImageOffset()
	{
		unsigned char result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetImageIndex(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetImageIndex()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetTextStyle(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetTextStyle()
	{
		unsigned char result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetAngle(unsigned short Value)
	{
		static BYTE parms[] = VTS_UI2 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned short GetAngle()
	{
		unsigned short result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_UI2, (void*)&result, NULL);
		return result;
	}
	void SetScale(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetScale()
	{
		unsigned char result;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetAlpha(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetAlpha()
	{
		unsigned char result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetSyncAngle(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetSyncAngle()
	{
		unsigned char result;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetPerspectiveImage(unsigned char Value)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	unsigned char GetPerspectiveImage()
	{
		unsigned char result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetCaption(LPCTSTR Caption)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1f41, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Caption);
	}
	CString GetCaption()
	{
		CString result;
		InvokeHelper(0x1f42, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetHint(LPCTSTR Hint)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1f43, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Hint);
	}
	CString GetHint()
	{
		CString result;
		InvokeHelper(0x1f44, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void SetDirectionToBoth()
	{
		InvokeHelper(0x1f45, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IXRouteFlag �Ӽ�
public:

};
