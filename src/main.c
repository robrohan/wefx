#include "wasm.h"
#include "wefx.h"

/*
 * - the top-left is (0,0) and the pixel coordinates increase
 * in the right and down directions
 * - the pixel centers have integer coordinates.
 */

#define W 1024
#define H 768

// Called once at startup
EXPORT void init()
{
    wefx_open(W, H, "Test Window");
    wefx_clear_color(0xc0, 0xc0, 0xc0);
    wefx_clear();
    srand(9999991);
}

// Called every frame
EXPORT void main_loop(float time)
{
    int itime = (int)time;

    wefx_color(0xff, 0, 0);
    wefx_point(itime % W, (H/2)-20);

    wefx_color(0, 0xff, 0);
    int x = itime % W;
    wefx_point(x, (H/2) + cos(time) * 2);

    wefx_color(0, 0, 0xff);
    wefx_point(itime % W, (H/2)+20);

	wefx_color(0xff, 0xff, 0xff);
    wefx_line(0, 0, W, H);
    wefx_line(0, H, W, 0);  

    wefx_color(rand() % 0xff, rand() % 0xff, rand() & 0xff);
    wefx_line(W/2, H/2, abs(rand() % W), abs(rand() % H));

    if (itime % W == 0)
    {
        wefx_clear();
    }
}
