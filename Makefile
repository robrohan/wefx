.PHONY: docs

CC=clang
STACK_SIZE=$$(( 8 * 1024 * 1024 ))

PANDOC?=pandoc
NARRATIVE?=narrative
MAIN?=examples/example0.c

C_ERRS += -Wall -Wextra -Wpedantic \
		-Wformat=2 -Wno-unused-parameter -Wshadow \
		-Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
		-Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
		-Wno-unused

NO_BUILT_INS=-fno-builtin-sin -fno-builtin-cos -fno-builtin-tan \
	-fno-builtin-ceil -fno-builtin-floor \
	-fno-builtin-pow -fno-builtin-round  \
	-fno-builtin-abs -fno-builtin-sqrt \
	-fno-builtin-malloc \
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
	@echo "make init_linux - install needed libs on linux"
	@echo "make init_mac   - install needed libs on macos"

# Install libraries needed on linux
init_linux:
	sudo apt install clang-14
	sudo apt install lld-14
	sudo apt-get install gcc-multilib

# Install libraries needed on MacOS
init_mac:
#	You'll need homebrew installed: https://brew.sh/
#	also be careful if you already have xcode installed
#	as this will give you two versions of clang which can be
#	confusing
	brew install llvm
	brew install lld
	clang --version
	wasm-ld --version
	@echo "if the above command isn't found"
	@echo "try to run: 'brew reinstall llvm' and/or 'brew reinstall lld'"

clean:
	rm -rf build

build: clean
	mkdir -p build
	$(CC) $(C_ERRS) \
		--target=wasm32 \
		-std=c11 \
		-g \
		-nostdlib \
		-Os -flto \
		-Wl,--allow-undefined \
		-Wl,--export-dynamic \
		-Wl,--no-entry \
		-Wl,--lto-O3 \
		-Wl,-z,stack-size=$(STACK_SIZE) \
		$(NO_BUILT_INS) \
		-o build/wefx.wasm \
		src/walloc.c src/math.c src/events.c src/wefx.c $(MAIN)
	cp public/index.html build/index.html

serve: clean build
	cd build; python3 -m http.server

clean_test:
	rm -f test

docs:
# requires narrative and pandoc to be installed
# if you would like to try the docker container way
# see below
	rm -f docs/manual.md
	cd docs; \
	$(NARRATIVE) \
		-i ./NARRATIVE \
		-o manual.md; \
	$(PANDOC) --pdf-engine=xelatex -s -t pdf \
		--citeproc \
		-f markdown manual.md \
		-o manual.pdf;

install_linux:
	apt-get install groff pandoc texlive-xetex

test: clean_test
	@echo "if you get: 'fatal error: 'bits/libc-header-start.h' file not found'"
	@echo "you need 32 bit libs installed. Either remove -m32 from the flags below"
	@echo "or run 'sudo apt-get install gcc-multilib' or equivalent."

	mkdir -p build
# add -lm if you want to test against built in math.h
# and -m32 for non-mac systems (mac wont do 32 bits anymore)
	$(CC) $(C_ERRS) -std=c11 -g \
		$(NO_BUILT_INS) \
		src/math.c src/wefx.c src/events.c src/test.c \
		-o build/test
	./build/test

########################################
# Build the docs using docker containers
# WIP. You need docker installed as well.
docker_docs: docker_narrative docker_pdf

docker_narrative:
	rm -f ./docs/manual.md
	docker run --rm -it \
		-v $(shell pwd):/root/workspace \
		robrohan/narrative \
			-i ./docs/NARRATIVE \
			-o ./docs/manual.md

docker_pdf:
	docker run --rm -it \
		-v $(shell cd docs; pwd):/root/workspace \
		robrohan/pandoc --pdf-engine=xelatex -s -t pdf \
		--citeproc \
		-f markdown ./manual.md \
		-o ./manual.pdf

docker_epub:
	docker run --rm -it \
		-v $(shell cd docs; pwd):/root/workspace \
		robrohan/pandoc --pdf-engine=xelatex -s -t epub \
		--citeproc \
		-f markdown ./manual.md \
		-o ./manual.epub



