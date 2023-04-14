
#ifndef _MKTYPE_H_
#define _MKTYPE_H_

#pragma warning(disable:4200)

enum cmkQuerytype {
	typeQuery = 1,
	typeParameter = 1,
	typeRecordset = 2,
	typeStoredProc = 4
};

enum cmkVT {
	typeInt = 2,
	typeLong = 3,
	typeBool = 11,
	typeDate = 7,
	typeString = 202,
	typeWStr = 203,
//	typeDouble = 300,
	typeFloat = 301
};

enum cmkDir {
	typeInput = 1,
	typeOutput = 2,
	typeInputOutput = 3,
	typeReturn = 4
};


typedef struct {	
	int nType;
	int nDirection;
	long lSize;
	char pValue[0];
} PARAMETER_STRUCT;

typedef struct {
	USHORT nType;
	char szStoredProc[55];
	USHORT nVarCount;
	char data[0];
} COMMAND_STRUCT;


typedef struct {
	int nType;
	long lSize;
	char szFieldName[30];
} FIELD_STRUCT;




#endif

