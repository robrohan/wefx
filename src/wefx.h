#ifndef WEFX__H
#define WEFX__H

#ifndef WEFX_NO_MATH
#include "math.h"
#endif

#ifndef WEFX_NO_WALLOC
#include "walloc.h"
#else
#include <stdlib.h>
#endif

#ifndef WEFX_NO_EXPORT
#include "wasm.h"
#else
#define EXPORT
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

// Open a new graphics window.
int wefx_open(unsigned int width, unsigned int height, const char *title);

// Draw a point at (x,y)
void wefx_point(int x, int y);

// Draw a pixel at (x0,y0) with size psize
void wefx_pixel(int x0, int y0);

void wefx_circle(int x0, int y0, int r);

// Draw a line from (x0,y0) to (x1,y1)
void wefx_line(int x0, int y0, int x1, int y1);

// Draw a rectangle from top left (x1, y1), to bottom right (x2,y2)
void wefx_rect(int x0, int y0, int x1, int y1);

void wefx_set_psize(int size);

// Change the current drawing color.
void wefx_color(unsigned int red, unsigned int green, unsigned int blue);

// Clear the graphics window to the background color.
void wefx_clear(void);

// Change the current background color.
void wefx_clear_color(unsigned int red, unsigned int green, unsigned int blue);

// Wait for the user to press a key or mouse button.
// char wefx_wait();

// Return the X and Y coordinates of the last event.
// int wefx_xpos();
// int wefx_ypos();

// Return the X and Y dimensions of the window.
int wefx_xsize(void);
int wefx_ysize(void);

extern void print(const char *);

void wefx_draw(unsigned int *screen);

unsigned int * wefx_get_buffer(void);

#endif // WEFX__H
