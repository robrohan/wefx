#include "wasm.h"
#include "wefx.h"

/*
  - the top-left is (0,0) such that pixel coordinates increase in the right and 
  	down directions (e.g. that the pixel at (7,4) is directly above the pixel 
  	at (7,5))
  - the pixel centers have integer coordinates.
*/

EXPORT void init()
{
    wefx_open(640, 480, "Test Window");
    wefx_clear_color(0xc0, 0xc0, 0xc0);
    wefx_clear();
}

EXPORT void main_loop(float time)
{
    int itime = (int)time;

    wefx_color(0xff, 0, 0);
    wefx_point(itime % 640, 220);

    wefx_color(0, 0xff, 0);
    int x = itime % 640;
    wefx_point(x, 240 + (cos(x) * 3));

    wefx_color(0, 0, 0xff);
    wefx_point(itime % 640, 260);

    wefx_color(0xff, 0xff, 0xff);
    wefx_line(0, 0, 640, 480);
    wefx_line(0, 480, 640, 0);
    // wefx_line(120, 10, 220, 380);

    if (itime % 640 == 0)
    {
        wefx_clear();
    }
}
