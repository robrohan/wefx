
CC=clang
STACK_SIZE=$$(( 8 * 1024 * 1024 ))

clean:
	rm -f public/wefx.wasm

build:
	$(CC) \
		--target=wasm32 \
		-std=c99 \
		-Wall \
		-g \
		-O3 -flto \
		-nostdlib \
		-Wl,--export-dynamic \
		-Wl,--no-entry \
		-Wl,--lto-O3 \
		-Wl,-z,stack-size=$(STACK_SIZE) \
		-o public/wefx.wasm \
		src/walloc.c src/math.c src/wefx.c src/example.c

start: clean build
# You probably wont have this: https://github.com/robrohan/busboy
# But anything like it will do. e.g. python3 -m http.server
	busboy --root=public

serve: clean build
	cd public; python3 -m http.server
