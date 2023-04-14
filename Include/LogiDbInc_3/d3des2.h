#pragma once

typedef unsigned int  UINT;
typedef char		  MBYTE;
typedef int           BOOL;

extern void des_init(MBYTE *key, int offset, BOOL triple);
extern void des_ecb(BOOL encrypt, MBYTE *in, int offin, MBYTE *out, int offout);


