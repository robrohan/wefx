#include "wefx.h"
#include "wasm.h"


EXPORT void init() {
	wefx_open(640, 480, "Test Window");
	wefx_clear_color(0xc0, 0xc0, 0xc0);
	wefx_clear();
}

EXPORT void main_loop(float time) {
	wefx_color(0xff, 0, 0);
	wefx_point((int)time % 640, 220);

	wefx_color(0, 0xff, 0);
	wefx_point((int)time % 640, 240);
		
	wefx_color(0, 0, 0xff);
	wefx_point((int)time % 640, 260);
}
