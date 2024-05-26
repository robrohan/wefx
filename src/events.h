#ifndef WEFX_EVENTS_H
#define WEFX_EVENTS_H

enum wefx_button_type
{
    WEFX_NONE = 0,
    WEFX_LEFT,
    WEFX_RIGHT,
};

enum wefx_event_type
{
    WEFX_KEYDOWN = 0,
    WEFX_KEYPRESS = 1,
    WEFX_KEYUP = 2,
    WEFX_MOUSEMOVE = 3,
    WEFX_MOUSEDOWN = 4,
    WEFX_MOUSEUP = 5,
    WEFX_CLICK = 6
};

typedef struct wefx_event
{
    enum wefx_event_type type;
    enum wefx_button_type button;
    char key; // TODO: this wont work with utf8
              // keyCode is deprecated in javascript
    int timestamp;
    int x;
    int y;
} wefx_event;

typedef struct wefx_event_node
{
    struct wefx_event *event;
    struct wefx_event_node *next;
} wefx_event_node;

typedef struct wefx_event_queue
{
    wefx_event_node *head;
    wefx_event_node *tail;
} wefx_event_queue;

//////////////////////////////////////////////

wefx_event_queue *wefx_open_events();

void wefx_init_queue(wefx_event_queue *q);

int wefx_enqueue(wefx_event_queue *q, wefx_event *event);

wefx_event *wefx_dequeue(wefx_event_queue *q);

#endif
