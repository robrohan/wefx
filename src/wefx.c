#include "wasm.h"

typedef unsigned int color;

EXPORT unsigned int *screen;
unsigned int *buffer;

color fg_color = 0;
color bg_color = 0;
int w = 0;
int h = 0;

EXPORT void wefx_open(int width, int height, const char *title)
{
    w = width;
    h = height;
    buffer = malloc(w * h * sizeof(int));
}

int rgb_to_int(int red, int green, int blue)
{
    int color = (0xFF << 24) + (blue << 16) + (green << 8) + (red);
    return color;
}

// Change the current foreground drawing color.
EXPORT void wefx_color(int red, int green, int blue)
{
    fg_color = rgb_to_int(red, green, blue);
}

// draw a point at x y using the current colour
EXPORT void wefx_point(int x, int y)
{
    buffer[x + y * w] = fg_color;
}

// Change the current background color.
EXPORT void wefx_clear_color(int red, int green, int blue)
{
    bg_color = rgb_to_int(red, green, blue);
}

// Clear the screen with the background color
EXPORT void wefx_clear()
{
    for (int q = 0; q < w * h; q++)
        buffer[q] = bg_color;
}

// Draw a line from (x1,y1) to (x2,y2)
EXPORT void wefx_line(int x0, int y0, int x1, int y1)
{
    // Bresenham's line algorithm
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    for (;;)
    {
        wefx_point(x0, y0);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * error;
        if (e2 >= dy)
        {
            if (x0 == x1)
                break;
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx)
        {
            if (y0 == y1)
                break;
            error = error + dx;
            y0 = y0 + sy;
        }
    }
}

//////////////////////////////////////////////////////////
EXPORT void wefx_draw(unsigned int *screen)
{
    for (int q = 0; q < w * h; q++)
        screen[q] = buffer[q];
}

EXPORT int wefx_win_width()
{
    return w;
}
EXPORT int wefx_win_height()
{
    return h;
}
//////////////////////////////////////////////////////////

/* Flush all previous output to the window? */
// void wefx_flush();

/* Wait for the user to press a key or mouse button. */
// char wefx_wait();

/* Return the X and Y coordinates of the last event. */
// int wefx_xpos();
// int wefx_ypos();

/* Return the X and Y dimensions of the window. */
// int wefx_xsize();
// int wefx_ysize();

/* Check to see if an event is waiting. */
// int wefx_event_waiting();
