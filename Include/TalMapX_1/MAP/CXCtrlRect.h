// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXCtrlRect ���� Ŭ����

class CXCtrlRect : public COleDispatchDriver
{
public:
	CXCtrlRect(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXCtrlRect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXCtrlRect(const CXCtrlRect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXCtrlRect �޼���
public:
	void SetLeft(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetLeft()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__Left(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get__Left()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetTop(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetTop()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__Top(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get__Top()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetWidth(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetWidth()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__Width(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get__Width()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetHeight(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	long GetHeight()
	{
		long result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put__Height(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get__Height()
	{
		long result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IXCtrlRect �Ӽ�
public:

};
