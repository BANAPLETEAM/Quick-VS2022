// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXMagicImagePanel ���� Ŭ����

class CXMagicImagePanel : public COleDispatchDriver
{
public:
	CXMagicImagePanel(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXMagicImagePanel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMagicImagePanel(const CXMagicImagePanel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXMagicImagePanel �޼���
public:
	void SetAutoDestroy(long Value)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2329, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	BOOL IsValid()
	{
		BOOL result;
		InvokeHelper(0x1f41, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void ClearImage_NoName()
	{
		InvokeHelper(0x1f42, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH GetImage(long Type)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b59, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type);
		return result;
	}

	// IXMagicImagePanel �Ӽ�
public:

};
