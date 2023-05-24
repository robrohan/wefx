#include "../src/wasm.h"
#include "../src/wefx.h"

// #include "Textures/All_Textures.ppm"
// #include "Textures/lost.ppm"
// #include "Textures/sky.ppm"
// #include "Textures/sprites.ppm"
// #include "Textures/title.ppm"
// #include "Textures/won.ppm"

#define W 1024
#define H 512

struct player
{
    float x;
    float y;
};

void draw_pixel(float left, float top, int size) {
    top = top + size;
    for(int r = 0; r <= size; r++) {
        for(int c = 0; c <= size; c++) {
            wefx_point(left+r, top-c);
        }
    }
}

void draw_player(struct player p)
{
    wefx_color(0xff, 0xff, 0xff);
    draw_pixel(p.x, p.y, 8);
}

void input(int time, wefx_event_queue *wefx_q)
{
    wefx_event *e = wefx_dequeue(wefx_q);
    switch (e->type)
    {
    case WEFX_MOUSEDOWN:
        wefx_clear_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
        break;
    case WEFX_KEYPRESS:
        if (e->key == 'w' || e->key == 'a' || e->key == 's' || e->key == 'd')
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

    wefx_color(0xff, 0, 0x0);
    draw_pixel(0, 0, 8);
    draw_pixel(W-8, H, 8);
    draw_pixel(W-8, 0, 8);
    draw_pixel(0, H, 8);

    // struct player p = {.x = cos(time*0.08)*(W), .y = H / 2 };
    // struct player p = {.x = W/2, .y = cos(time*0.08)*(H) };
    struct player p = {.x = W/2, .y = abs(cos(time*0.08)*(H)) };
    draw_player(p);

    // int x = time % W;
    // wefx_point(x, (H / 2) + cos(time) * 2);

    // for (int i = 0; i < 130; i++)
    // {
    //     wefx_color(0xff, 0, 0);
    //     wefx_point(x - i, ((H / 2) + sin(time - i) * 3) - 20);

    //     wefx_color(0, 0xff, 0);
    //     wefx_point(x - i, (H / 2) + cos(time - i) * 2);

    //     wefx_color(0, 0, 0xff);
    //     wefx_point(x - i, ((H / 2) + sin(time - i) * 3) + 20);
    // }

    // wefx_color(0xff, 0xff, 0xff);
    // wefx_line(0, 0, W, H);
    // wefx_line(0, H, W, 0);

    // wefx_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
    // wefx_line(W / 2, H / 2, abs(rand() % W), abs(rand() % H));

    // wefx_circle(W >> 1, H >> 1, (H >> 1) - 5);
}

EXPORT void main_loop(float time, wefx_event_queue *wefx_q)
{
    int itime = (int)time;
    input(itime, wefx_q);
    draw(itime);
}

EXPORT int init()
{
    int err = wefx_open(W, H, "Caster Window");
    if (err)
        return 1;

    if (wefx_open_events() == NULL)
        return 1;

    wefx_clear_color(0x00, 0x00, 0x00);
    wefx_clear();
    srand(1234567);
    return 0;
}