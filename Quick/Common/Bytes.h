
#if !defined(AFX_BYTE_H__03F99078_8436_4C08_B144_AB499AA29B8F__INCLUDED_)
#define AFX_BYTE_H__03F99078_8436_4C08_B144_AB499AA29B8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Byte.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CByte window
class  CByte 
{
// Construction
public:
	CByte();
	CByte(CString sEncStr);
	CByte(BYTE* pByte,int nLength);
	CByte(CByte* pByte);
	CByte(const CByte& Byte);
// Operations
public:
	void Encode();
	BOOL SetByte(BYTE* pByte,int nLength);
	BOOL SetByte(CByte Byte);
	BOOL SetByte(CByte* pByte);
	CByte  operator+(const CByte& Byte);
	CByte& operator=(const CByte& Byte);
	CByte& operator=(const CByte* Byte);
	BYTE* GetByte();
	CString GetEncString();
	int   GetLength();
public:
	virtual ~CByte();

	// Generated message map functions
private:
	BYTE* m_pbyte;
	int	  m_nLength;
};

/////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_BYTE_H__03F99078_8436_4C08_B144_AB499AA29B8F__INCLUDED_)
