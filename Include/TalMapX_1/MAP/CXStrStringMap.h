// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXStrStringMap ���� Ŭ����

class CXStrStringMap : public COleDispatchDriver
{
public:
	CXStrStringMap(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXStrStringMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXStrStringMap(const CXStrStringMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXStrStringMap �޼���
public:
	long GetItemCount()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString FindItemValue(LPCTSTR Key)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Key);
		return result;
	}
	BOOL InsertItem(LPCTSTR Key, LPCTSTR Value)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
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

	// IXStrStringMap �Ӽ�
public:

};
