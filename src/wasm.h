#ifndef WEFX_WASM_H
#define WEFX_WASM_H

#include "walloc.h"
#include "math.h"

// This is used to flag a function as something that
// should be accessible in javascript.
#define EXPORT __attribute__((visibility("default")))

#endif
