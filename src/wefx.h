/*
A simple graphics library made in the spirit of gfx by Douglas Thain
http://www.nd.edu/~dthain/courses/cse20211/fall2013/gfx
*/
#ifndef WEFX__H
#define WEFX__H

#include "walloc.h"
#include "math.h"

/* Open a new graphics window. */
void wefx_open(int width, int height, const char *title);

/* Draw a point at (x,y) */
void wefx_point( int x, int y );

/* Draw a line from (x1,y1) to (x2,y2) */
void wefx_line(int x1, int y1, int x2, int y2);

/* Change the current drawing color. */
void wefx_color(int red, int green, int blue);

/* Clear the graphics window to the background color. */
void wefx_clear();

/* Change the current background color. */
void wefx_clear_color(int red, int green, int blue);

/* Wait for the user to press a key or mouse button. */
// char wefx_wait();

/* Return the X and Y coordinates of the last event. */
int wefx_xpos();
int wefx_ypos();

/* Return the X and Y dimensions of the window. */
int wefx_xsize();
int wefx_ysize();

/* Check to see if an event is waiting. */
// int wefx_event_waiting();

/* Flush all previous output to the window. */
void wefx_flush();

#endif // WEFX__H