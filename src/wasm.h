/*

# Export Function to Javascript

Here we simply define a macro that will let the compiler know
that a function should be made available in Javascript.

Prefix functions with the _EXPORT_ keyword.

*/
#ifndef WEFX_WASM_H
#define WEFX_WASM_H

#include "math.h"
#include "walloc.h"

// This is used to flag a function as something that
// should be accessible in javascript.
#define EXPORT __attribute__((visibility("default")))

#endif
