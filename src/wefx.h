/*
A simple graphics library made in the spirit of gfx by Douglas Thain
http://www.nd.edu/~dthain/courses/cse20211/fall2013/gfx
*/
#ifndef WEFX__H
#define WEFX__H

#include "walloc.h"
#include "math.h"

#ifndef NULL
	#define NULL ((void *)0)
#endif

enum wefx_button_type {
	WEFX_NONE = 0,
	WEFX_LEFT,
	WEFX_RIGHT,
};

enum wefx_event_type {
	WEFX_KEYDOWN = 0,
	WEFX_KEYPRESS,
	WEFX_KEYUP,
	WEFX_MOUSEMOVE,
	WEFX_MOUSEDOWN,
	WEFX_MOUSEUP,
	WEFX_CLICK
};

typedef struct wefx_event {
	enum wefx_event_type type;
	enum wefx_button_type button;
	char key;                      // TODO: this wont work with utf8
	                               // keyCode is deprecated in javascript
	int timestamp;
	int x;
	int y;
} wefx_event;

typedef struct wefx_event_node {
	struct wefx_event *event;
	struct wefx_event_node *next;
} wefx_event_node;

typedef struct wefx_event_queue {
	wefx_event_node *head;
	wefx_event_node *tail;
} wefx_event_queue;

void wefx_init_queue(wefx_event_queue *q);

int wefx_enqueue(wefx_event_queue *q, wefx_event* event);

wefx_event* wefx_dequeue(wefx_event_queue *q);

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
// int wefx_xpos();
// int wefx_ypos();

/* Return the X and Y dimensions of the window. */
int wefx_xsize();
int wefx_ysize();

/* Check to see if an event is waiting. */
// int wefx_event_waiting();

#endif // WEFX__H