// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXMagicImage ���� Ŭ����

class CXMagicImage : public COleDispatchDriver
{
public:
	CXMagicImage(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXMagicImage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXMagicImage(const CXMagicImage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXMagicImage �޼���
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

	// IXMagicImage �Ӽ�
public:

};
