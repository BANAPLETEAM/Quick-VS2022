// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXIntIntegerMap ���� Ŭ����

class CXIntIntegerMap : public COleDispatchDriver
{
public:
	CXIntIntegerMap(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXIntIntegerMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXIntIntegerMap(const CXIntIntegerMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXIntIntegerMap �޼���
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

	// IXIntIntegerMap �Ӽ�
public:

};
