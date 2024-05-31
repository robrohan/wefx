#ifndef WEFX__H
#define WEFX__H

#include "math.h"
#include "walloc.h"

// Open a new graphics window.
int wefx_open(unsigned int width, unsigned int height, const char *title);

// Draw a point at (x,y)
void wefx_point(int x, int y);

void wefx_circle(int x0, int y0, int r0);

// Draw a line from (x1,y1) to (x2,y2)
void wefx_line(int x1, int y1, int x2, int y2);

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

#endif // WEFX__H
