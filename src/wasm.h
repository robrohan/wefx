/*

# Export Function to Javascript

Here we simply define a macro that will let the compiler know
that a function should be made available in Javascript.

Prefix functions with the _EXPORT_ keyword if you would like
to be able to call a C function from within Javascript.

*/
#ifndef WEFX_WASM_H
#define WEFX_WASM_H

#include "math.h"
#include "walloc.h"

#define EXPORT __attribute__((visibility("default")))

#endif
