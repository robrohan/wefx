
CC=clang
STACK_SIZE=$$(( 8 * 1024 * 1024 ))

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

serve: clean build
	cd public; python3 -m http.server

test: 
# add -lm if you want to test against built in math.h
	clang -std=c99 -m32 \
		src/math.c src/test.c \
		-o test
	./test