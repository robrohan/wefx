#include "../src/wasm.h"
#include "../src/wefx.h"

#define W 1024
#define H 768

EXPORT int init()
{
    int err = wefx_open(W, H, "Test Window");
    if (err)
        return 1;

    if (wefx_open_events() == NULL)
        return 1;

    wefx_clear_color(0x00, 0x00, 0x00);
    wefx_clear();
    srand(9999991);
    return 0;
}

void input(int time, wefx_event_queue *wefx_q)
{
    wefx_event *e = wefx_dequeue(wefx_q);
    switch (e->type)
    {
    case WEFX_MOUSEDOWN:
        wefx_clear_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
        break;
    case WEFX_KEYDOWN:
        if (e->key == 'w' || e->key == 'a'|| e->key == 's' || e->key == 'd')
        {
            wefx_clear_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
        }
        break;
    }
    free(e);
}

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

    wefx_circle(W >> 1, H >> 1, (H >> 1) - 5);
}

EXPORT void main_loop(float time, wefx_event_queue *wefx_q)
{
    int itime = (int)time;
    input(itime, wefx_q);
    draw(itime);
}
