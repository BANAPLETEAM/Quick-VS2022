
#pragma once


#define CREATE_MODALESS(Type, Parent) \
	static Type *pDlg = NULL;\
	if(!pDlg) pDlg = new Type(Parent);

#define SHOW_MODALESS(Type, Parent) \
	pDlg->CreateModalessDlg(Parent, &pDlg);

#define CREATE_AND_SHOW_MODALESS(Type, Parent) \
	CREATE_MODALESS(Type, Parent) \
	SHOW_MODALESS(Type, Parent)



/*
#define CREATE_MODALESS_FUNC(Type, func) \
	static Type *pDlg = NULL;\
	if(!pDlg) pDlg = new Type(this);\
	pDlg->CreateModalessDlg(this, &pDlg, func);


#define CREATE_MODALESS_PARENT(Type, Parent) \
	static Type *pDlg = NULL;\
	if(!pDlg) pDlg = new Type(Parent);\
	pDlg->CreateModalessDlgNoFunc(Parent, &pDlg);


#define CREATE_MODALESS_PARENT_FUNC(Type, Parent, func) \
	static Type *pDlg = NULL;\
	if(!pDlg) pDlg = new Type(Parent);\
	pDlg->CreateModalessDlg(Parent, &pDlg, func);


#define CREATE_MODALESS_FUNC2(Type, SubType, func) \
	static Type *pDlg = NULL;\
	if(!pDlg) pDlg = new Type(this);\
	pDlg->CreateModalessDlg2(this, &pDlg, SubType, func);


#define CREATE_MODALESS_PARENT_FUNC2(Type, Parent, SubType, func) \
	static Type *pDlg = NULL;\
	if(!pDlg) pDlg = new Type(Parent);\
	pDlg->CreateModalessDlg2(Parent, &pDlg, SubType, func);

*/