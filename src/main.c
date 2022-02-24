#include "wasm.h"
#include "wefx.h"

/*
 * - the top-left is (0,0) and the pixel coordinates increase
 * in the right and down directions
 * - the pixel centers have integer coordinates.
 */

// Called once at startup
EXPORT void init()
{
    wefx_open(640, 480, "Test Window");
    wefx_clear_color(0xc0, 0xc0, 0xc0);
    wefx_clear();
    srand(9999991);
}

// Called every frame
EXPORT void main_loop(float time)
{
    int itime = (int)time;

    wefx_color(0xff, 0, 0);
    wefx_point(itime % 640, 220);

    wefx_color(0, 0xff, 0);
    int x = itime % 640;
    wefx_point(x, 240 + cos(time) * 2);

    wefx_color(0, 0, 0xff);
    wefx_point(itime % 640, 260);

	wefx_color(0xff, 0xff, 0xff);
    wefx_line(0, 0, 640, 480);
    wefx_line(0, 480, 640, 0);  

    wefx_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
    wefx_line(320, 240, abs(rand() % 640), abs(rand() % 480));

    if (itime % 640 == 0)
    {
        wefx_clear();
    }
}
