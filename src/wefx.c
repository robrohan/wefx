#include "wefx.h"
#include "wasm.h"

typedef unsigned int color;

EXPORT unsigned int *screen;
static unsigned int *buffer;

static color fg_color = 0;
static color bg_color = 0;
static int w = 0;
static int h = 0;

wefx_event_queue *wefx_q = NULL;

int wefx_open(int width, int height, const char *title)
{
    w = width;
    h = height;
    buffer = malloc(w * h * sizeof(int));
    if (buffer == NULL)
    {
        return 1;
    }
    return 0;
}

int rgb_to_int(int red, int green, int blue)
{
    int color = (0xFF << 24) + (blue << 16) + (green << 8) + (red);
    return color;
}

// Change the current foreground drawing color.
void wefx_color(int red, int green, int blue)
{
    fg_color = rgb_to_int(red, green, blue);
}

// draw a point at x y using the current colour
void wefx_point(int x, int y)
{
    buffer[x + y * w] = fg_color;
}

// Change the current background color.
void wefx_clear_color(int red, int green, int blue)
{
    bg_color = rgb_to_int(red, green, blue);
}

// Clear the screen with the background color
void wefx_clear()
{
    for (int q = 0; q < w * h; q++)
        buffer[q] = bg_color;
}

// Draw a line from (x1,y1) to (x2,y2)
void wefx_line(int x0, int y0, int x1, int y1)
{
    // Bresenham's line algorithm
    // read more here:
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
// Event Queue
wefx_event_queue *wefx_open_events()
{
    wefx_q = malloc(sizeof(struct wefx_event_queue));
    if (wefx_q != NULL)
    {
        wefx_init_queue(wefx_q);
        return wefx_q;
    }

    return NULL;
}

EXPORT void wefx_add_queue_event(int type, int button, int timestamp, int key, int x, int y)
{
    // if we don't care about events drop everything
    if (wefx_q == NULL)
        return;

    wefx_event *e = malloc(sizeof(struct wefx_event));
    if (e == NULL)
    {
        // we couldn't create memory for some reason
        // this seems to happen a bit when running in
        // wasm (or maybe walloc)
        return;
    }
    e->type = type;
    e->button = button;
    e->timestamp = timestamp;
    e->key = (char)key;
    e->x = x;
    e->y = y;

    wefx_enqueue(wefx_q, e);
}

void wefx_init_queue(wefx_event_queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

int wefx_enqueue(wefx_event_queue *q, wefx_event *event)
{
    // create a new node to store the event
    wefx_event_node *node = malloc(sizeof(struct wefx_event_node));
    if (node == NULL)
    {
        return -1;
    }

    node->event = event;
    node->next = NULL;

    // if the queue has a tail, add us as the next behind the tail
    if (q->tail != NULL)
    {
        q->tail->next = node;
    }
    // now really make us the last node
    q->tail = node;

    // if we are first in line, go to the head
    if (q->head == NULL)
    {
        q->head = node;
    }

    return 1;
}

wefx_event *wefx_dequeue(wefx_event_queue *q)
{
    if (q == NULL)
        return NULL;

    if (q->head == NULL)
    {
        return NULL;
    }

    wefx_event_node *n = q->head;
    wefx_event *e = n->event;
    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    free(n);
    return e;
}

//////////////////////////////////////////////////////////
EXPORT void wefx_draw(unsigned int *screen)
{
    for (int q = 0; q < w * h; q++)
        screen[q] = buffer[q];
}

/* Return the X and Y dimensions of the window. */
EXPORT int wefx_xsize()
{
    return w;
}
EXPORT int wefx_ysize()
{
    return h;
}
