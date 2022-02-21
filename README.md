# wefx

Status: Alpha / In Progress

Wefx is a graphics library for drawing simple things using C, wasm, and an HTML canvas. It aims to be similar to [gfx](https://www3.nd.edu/~dthain/courses/cse20211/fall2013/gfx/). It is meant to be a teaching / learning tool for C and graphics. This is not using OpenGL or anything heavy like that. It is doing very basic pixel manipulation and will have very simple functions to draw pixels and lines.

## Running

## Mac and Linux

You'll need `make` and `clang` installed. MacOS and Linux should not have a problem installing these. See `brew`, `apt-get`, or your local package manager for examples. 

To compile you'll do:

```
make build
```

If you have python3 installed, you can run `make serve` and it'll build and run a web server for you to play with on http://localhost:8000.

Otherwise, you can use your favorite mini http server to serve the `public` directory (see `make start` for an example).

### Windows

On windows, you'll have to do something else, but you should be able to build with Visual Studio, install `clang` and then run the commands shown in the `Makefile`.
