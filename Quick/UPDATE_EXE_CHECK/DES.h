#pragma once


#define BOXLEN	64
#define LONGS   32


class CDES
{
public:
	void Init(CHAR*,int ,BOOL);
	void Ecb(BOOL , CHAR*, int , CHAR*, int );

protected:
	void spbox( CHAR *box, int *mask, int *compiled);
	void initDesSPboxes();
	void inits3DesSPboxes();
	void KDspbox(CHAR *box, int *mask, int *compiled, CHAR *key, int offset, int index);
	void initKDdesSPboxes(CHAR *key, int offset);
	void DES_SPboxes();
	void key_single(CHAR *hexkey, int off1, int mode,	int *keybuf, int offset );
	void key_dbl(CHAR *hexkey, int off1, int mode, int *keyout, int offset );
	void key_triple(CHAR *hexkey, int off1, int mode, int *keyout, int offset );
	void engine_single(CHAR *inblock, int offin, CHAR *outblock, int offout, int *keys);
	void engine_triple(CHAR *inblock, int offin, CHAR *outblock, int offout, int *keys);

protected:
	int SP1[BOXLEN];
	int SP2[BOXLEN];
	int SP3[BOXLEN];
	int SP4[BOXLEN];
	int SP5[BOXLEN];
	int SP6[BOXLEN];
	int SP7[BOXLEN];
	int SP8[BOXLEN];
	int ekeysched[LONGS];
	int dkeysched[LONGS];

};