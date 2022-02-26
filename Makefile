
CC=clang
STACK_SIZE=$$(( 8 * 1024 * 1024 ))

NO_BUILT_INS=-fno-builtin-sin -fno-builtin-cos -fno-builtin-pow -fno-builtin-round -fno-builtin-ceil -fno-builtin-floor -fno-builtin-abs -fno-builtin-malloc -fno-builtin-rand -fno-builtin-srand

about:
	@echo ""
	@echo " wefx "
	@echo ""
	@echo "make serve   -  build wasm, and lanuch basic web server"
	@echo "make clean   -  clean temp files"
	@echo "make build   -  just build the wasm file"
	@echo "make test    -  run some basic tests."
	@echo ""

clean:
	rm -f public/wefx.wasm
	rm -f test

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
		$(NO_BUILT_INS) \
		-o public/wefx.wasm \
		src/walloc.c src/math.c src/wefx.c src/main.c



serve: clean build
# XXX: maybe instead do a very simple server in C
	cd public; python3 -m http.server

test: 
# add -lm if you want to test against built in math.h
	clang -std=c99 -m32 -g \
		$(NO_BUILT_INS) \
		src/math.c src/test.c \
		-o test
	./test