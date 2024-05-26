#include "events.h"
#include "wasm.h"
/*

Here we reserve a spot for an event queue where we will store user events from the browser.
E.g. Mouse down, mouse move, key down, etc.

*/
EXPORT wefx_event_queue *wefx_q = NULL;
/*

# Event Queue

In order to process browser events (keyboard and mouse input), we use
a simple Queue. The Javascript that hosts this code will capture events
in the browser and pass them into C using the queue. We can then use the
queue to look at and process those events.

## Open Events - wefx_open_events

Similar to how _wefx\_open_ created screen memory, the _wefx_open_events_
function allocates memory for the event queue.

*/
wefx_event_queue *wefx_open_events()
{
    wefx_q = malloc(sizeof(struct wefx_event_queue));
    // wefx_q = &(const struct wefx_event_queue){ 0 };
    if (wefx_q != NULL)
    {
        wefx_init_queue(wefx_q);
        return wefx_q;
    }

    return NULL;
}
/*

When we create a new queue, we want to set the head and tail to null to
mark it as empty. This is not strictly necessary, but it will make knowing
if the queue is empty a bit easier.

*/
void wefx_init_queue(wefx_event_queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}
/*

## Add Events from Javascript

Javascript will call this function directly to register that an event has
occurred.

Here we just take the parameters passed in from Javascript, put them into
the _wefx\_event_ struct, and add it to the end of the queue.

*/
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
/*

## Add an Event to a Queue

_wefx\_enqueue_ takes an event and adds it to the given queue. It does a number of
checks to make sure the queue is in a valid state, and adds the event if
everything is ok.

*/
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
/*

## Remove an Event from a Queue

Take the first event in the queue off the queue, and return it.

*/
wefx_event *wefx_dequeue(wefx_event_queue *q)
{
    if (q == NULL)
        return NULL;

    wefx_event *e = NULL;

    if (q->head == NULL)
        return NULL;

    wefx_event_node *n = q->head;

    if(n->event == NULL) {
        goto clean_up;
    }

    e = n->event;

    if(n->next == NULL) {
        goto clean_up;
    }
    q->head = n->next;

    // if our new head is null, make sure the
    // tail is set to null
    if (q->head == NULL)
        q->tail = NULL;

clean_up:
    if (n != NULL)
        free(n);

    return e;
}
