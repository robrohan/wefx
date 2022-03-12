
CC=clang
# STACK_SIZE=$$(( 8 * 1024 * 1024 ))
STACK_SIZE=$$(( 8 * 1024 ))

MAIN?=examples/main.c

NO_BUILT_INS=-fno-builtin-sin -fno-builtin-cos \
	-fno-builtin-ceil -fno-builtin-floor \
	-fno-builtin-pow -fno-builtin-round  \
	-fno-builtin-abs -fno-builtin-malloc \
	-fno-builtin-rand -fno-builtin-srand

about:
	@echo ""
	@echo " wefx "
	@echo ""
	@echo "make serve   -  build wasm, and lanuch basic web server"
	@echo "make clean   -  clean temp files"
	@echo "make build   -  just build the wasm file"
	@echo "                MAIN=examples/xxxx.c to override entry file"
	@echo "make test    -  run some basic tests."
	@echo ""

clean:
	rm -rf build

build: clean
	mkdir -p build
	$(CC) \
		--target=wasm32 \
		-std=c99 \
		-Wall \
		-g \
		-Os -flto \
		-nostdlib \
		-Wl,--export-dynamic \
		-Wl,--no-entry \
		-Wl,--lto-O3 \
		-Wl,-z,stack-size=$(STACK_SIZE) \
		$(NO_BUILT_INS) \
		-o build/wefx.wasm \
		src/walloc.c src/math.c src/wefx.c $(MAIN)
	cp public/index.html build/index.html

serve: clean build
	cd build; python3 -m http.server

clean_test:
	rm -f test

test: clean_test
	mkdir -p build
# add -lm if you want to test against built in math.h
	clang -std=c99 -m32 -g \
		$(NO_BUILT_INS) \
		src/math.c src/wefx.c src/test.c \
		-o build/test
	./build/test