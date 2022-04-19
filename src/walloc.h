/*

# Malloc Implementation - walloc

_walloc_, written by S.L. Igalia, is a bare-bones implementation of malloc
for use by C programs when targetting WebAssembly. It is a single-file
implementation of _malloc_ and _free_ with no dependencies [@Walloc_2022_Wingo].

Here we are just defining the interface to the walloc code.

*/
#ifndef WEFX_WALLOC__H
#define WEFX_WALLOC__H

void *malloc(unsigned long);
void free(void *);

#endif /* MALLOC__H */
