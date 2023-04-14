// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXStrIntegerMap ���� Ŭ����

class CXStrIntegerMap : public COleDispatchDriver
{
public:
	CXStrIntegerMap(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXStrIntegerMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXStrIntegerMap(const CXStrIntegerMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXStrIntegerMap �޼���
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

	// IXStrIntegerMap �Ӽ�
public:

};
