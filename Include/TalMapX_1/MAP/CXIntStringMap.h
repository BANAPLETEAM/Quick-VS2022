// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXIntStringMap ���� Ŭ����

class CXIntStringMap : public COleDispatchDriver
{
public:
	CXIntStringMap(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXIntStringMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXIntStringMap(const CXIntStringMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXIntStringMap �޼���
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

	// IXIntStringMap �Ӽ�
public:

};
