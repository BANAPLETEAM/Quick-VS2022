// ��ǻ�Ϳ��� ���� ���̺귯�� �������� [Ŭ���� �߰�]�� ����Ͽ� ������ IDispatch ���� Ŭ�����Դϴ�.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXToolTip ���� Ŭ����

class CXToolTip : public COleDispatchDriver
{
public:
	CXToolTip(){} // COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	CXToolTip(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXToolTip(const CXToolTip& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Ư��
public:

	// �۾�
public:


	// IXToolTip �޼���
public:
	void SetFont(long Type, LPCTSTR Name, long Size, BOOL Bold, BOOL Italic, BOOL Underline, BOOL StrikeOut)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Name, Size, Bold, Italic, Underline, StrikeOut);
	}
	void SetFontColor(long Type, unsigned long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Value);
	}
	void SetBrush(long Type, unsigned long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type, Value);
	}

	// IXToolTip �Ӽ�
public:

};
