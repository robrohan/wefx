#include "../src/wasm.h"
#include "../src/wefx.h"

/*
 * - the top-left is (0,0) and the pixel coordinates increase
 * in the right and down directions
 * - the pixel centers have integer coordinates.
 */

#define W 1024
#define H 768

// This is a handle to the event queue from the browser
// TODO: not super happy with this, but passing a poitner
// back from wefx to the queue just crashes the browser
// need some better debug tools.
extern wefx_event_queue *wefx_q;

// Called once at startup
EXPORT int init()
{
    // Open a "window"
    int err = wefx_open(W, H, "Test Window");
    if (err)
        return 1;

    // enable mouse and keyboard events
    wefx_event_queue *queue = wefx_open_events();
    if (queue == NULL)
        return 1;

    wefx_clear_color(0x00, 0x00, 0x00);
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

    int x = time % W;
    wefx_point(x, (H / 2) + cos(time) * 2);

    for (int i = 0; i < 130; i++)
    {
        wefx_color(0xff, 0, 0);
        wefx_point(x - i, ((H / 2) + sin(time - i) * 3) - 20);

        wefx_color(0, 0xff, 0);
        wefx_point(x - i, (H / 2) + cos(time - i) * 2);

        wefx_color(0, 0, 0xff);
        wefx_point(x - i, ((H / 2) + sin(time - i) * 3) + 20);
    }

    wefx_color(0xff, 0xff, 0xff);
    wefx_line(0, 0, W, H);
    wefx_line(0, H, W, 0);

    wefx_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
    wefx_line(W / 2, H / 2, abs(rand() % W), abs(rand() % H));
}

// Called every frame
EXPORT void main_loop(float time)
{
    int itime = (int)time;

    input(itime);
    draw(itime);
}
