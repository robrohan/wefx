#include "../src/wasm.h"
#include "../src/wefx.h"

/*
 * - the top-left is (0,0) and the pixel coordinates increase
 * in the right and down directions
 * - the pixel centers have integer coordinates.
 */
#define W 105
#define H 50

// This is a handle to the event queue from the browser
// TODO: not super happy with this, but passing a poitner
// back from wefx to the queue just crashes the browser
// so we'll use the queue defined in wefx.c
extern wefx_event_queue *wefx_q;

// Called once at startup
EXPORT int init()
{
    // Open a "window"
    int err = wefx_open(W, H, "Logo Window");
    if (err)
        return 1;

    // enable mouse and keyboard events
    wefx_event_queue *queue = wefx_open_events();
    if (queue == NULL)
        return 1;

    wefx_clear_color(0x00, 0x00, 0x00);
    wefx_color(0xff, 0xff, 0xff);
    wefx_clear();
    srand(9999991);

    return 0;
}

// Handle input each frame
void input(int time)
{
    // we need to at least drain the event queue
    // or we'll evenutally run out of memory
    wefx_event *e = wefx_dequeue(wefx_q);
    while (e != NULL)
    {
        switch (e->type)
        {
        case WEFX_MOUSEDOWN:
            wefx_clear_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
            break;
        case WEFX_KEYDOWN:
            if (e->key == 0)
                break;
            if (e->key == 'a')
            {
                wefx_clear_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
            }
            break;
        }
        // Dodgy, but javascript creates this when it makes
        // the event so we need to free the event here.
        free(e);

        // grab the next item in the queue
        e = wefx_dequeue(wefx_q);
    }
}

// Draw to our screen buffer
void draw(int time)
{
    wefx_clear();
    wefx_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
    
    // W
    wefx_line(15, 15, 20, 35);
    wefx_line(20, 35, 22, 25);
    wefx_line(23, 25, 25, 35);
    wefx_line(25, 35, 30, 15);
    // E
    wefx_line(50, 15, 35, 15);
    wefx_line(45, 25, 35, 25);
    wefx_line(50, 35, 35, 35);
    wefx_line(35, 15, 35, 35);
    // F
    wefx_line(70, 15, 55, 15);
    wefx_line(65, 25, 55, 25);
    wefx_line(55, 15, 55, 35);
    // X
    wefx_line(75, 15, 90, 35);
    wefx_line(90, 15, 75, 35);
}

// Called every frame
EXPORT void main_loop(float time)
{
    int itime = (int)time;
    input(itime);
    draw(itime);
}
