
#ifndef DEMO_WASM
#define DEMO_WASM

// This is used to flag a function as something that
// should be accessible in javascript.
#define EXPORT __attribute__((visibility("default")))

#endif
