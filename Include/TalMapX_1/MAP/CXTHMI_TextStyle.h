// 컴퓨터에서 형식 라이브러리 마법사의 [클래스 추가]를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// #import "F:\\INSTALL\\eKsys\\Library\\DLL\\TalMap\\TalMapX.dll" no_namespace
// CXTHMI_TextStyle 래퍼 클래스

class CXTHMI_TextStyle : public COleDispatchDriver
{
public:
	CXTHMI_TextStyle(){} // COleDispatchDriver 기본 생성자를 호출합니다.
	CXTHMI_TextStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXTHMI_TextStyle(const CXTHMI_TextStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 특성
public:

	// 작업
public:


	// IXTHMI_TextStyle 메서드
public:
	unsigned char GetVisible()
	{
		unsigned char result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetVisible(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetAlpha()
	{
		unsigned char result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetAlpha(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetPen()
	{
		unsigned char result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetPen(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetBrush()
	{
		unsigned char result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetBrush(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetFont()
	{
		unsigned char result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetFont(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned long GetColor()
	{
		unsigned long result;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void SetColor(unsigned long Val)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetTextStyle()
	{
		unsigned char result;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetTextStyle(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetIconPos()
	{
		unsigned char result;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetIconPos(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetRopMode()
	{
		unsigned char result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetRopMode(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetIconType()
	{
		unsigned char result;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetIconType(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}
	unsigned char GetIcon()
	{
		unsigned char result;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_UI1, (void*)&result, NULL);
		return result;
	}
	void SetIcon(unsigned char Val)
	{
		static BYTE parms[] = VTS_UI1 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Val);
	}

	// IXTHMI_TextStyle 속성
public:

};
