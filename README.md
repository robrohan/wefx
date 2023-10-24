# wefx

Wefx is a simple graphics library for drawing using C, WASM ([Web Assembly][webassembly]), and an [HTML canvas][htmlcanvas]. It aims to serve a similar purpose as [gfx][gfx], but provide an introduction to using C and WASM. Wefx is meant to be a teaching / learning tool for C and graphics. Wefx is not using OpenGL /
WebGL or anything like that. It is doing very basic pixel manipulation and
has very simple functions to draw pixels and lines.

If you would like to see an overview of Wefx, you can watch a [video of the project on YouTube][video]

You can also [download the documentation](https://raw.githubusercontent.com/robrohan/wefx/main/docs/manual.pdf)

![Example Screenshot](https://raw.githubusercontent.com/robrohan/wefx/main/docs/wefx_shot.png)

## Using The Project

The flow of the project has two steps: the build step, and the serve step:

```
 ⌈                    ⌉             ⌈                   ⌉
 | ./src + ./examples | ⭢  clang ⭢ | ./build/wefx.wasm |
 ⌊                    ⌋             ⌊                   ⌋
                                             ⭣
        _____________________________________/
       /
      ⭣
 ⌈          ⌉                  ⌈         ⌉    ⌈      ⌉
 | ./build/ | ⭢  web server ⭢ | browser | ⭢ | you! |
 ⌊          ⌋                  ⌊         ⌋    ⌊      ⌋
```

In other words, you compile the C code into a WASM, and then serve the
`build` directory using a web server. You can then open a web browser and
visit http://localhost:8000 to view the running C code.

You'll need the following programs installed:

- clang
- make (optional - MacOS and Linux)
- (optional) python3

On MacOS or Linux these tools should be available already, or easily
installed with homebrew (`brew install`), or Apt (`apt install`), or your local package manager.

### Compiling

To understand what is happening (or if you do not want to use _make_), open
the _Makefile_ file and look at the _build_ task. There you can see how
_clang_ is used.

If you have _make_ available, type:

```{sh}
make build
```

on the command line. This will, assuming there are no errors, create the
file `./build/wefx.wasm`. Once this builds you can serve your creation by
doing the following...

### Serving

The gist of this is you need to serve the contents of the `/build`
directory in a web server. You need to do this because the file that loads
the newly create `wasm` file ([index.html](./public/index.html) can only
load the wasm file over http. You can not simply open the `index.html` file
directly from your file system (this is just how wasm loading works).

If you try to open the `index.html` file directly you will get an error
like:

> Cross-Origin Request Blocked: The Same Origin Policy disallows reading the remote resource at file:///xxxxx/build/wefx.wasm. (Reason: CORS request not http).

A basic http server comes with python3, and the make file will run that
server if you run:

```{sh}
make serve
```

and the python3 web server will serve the files in the _build_ directory.
You can then use your favorite browser and browse to http://localhost:8000
to see the compiled code.

---

**Note** `make serve` will both recompile your code and run the web server.

---

If you already have a favorite server (for example I use
[busboy](https://github.com/robrohan/busboy)), you can use that serve to
serve the `build` directory instead, and then run the `make build` command
to replace the wasm file as you play around.

For example in one shell I run:

```{sh}
busyboy --root=./build
```

Then, after I make changes to the C code, I run

```{sh}
make build
```

And then simply refresh the browser to see changes.

### Writing Code

If just teaching / learning about graphics, you'll only need to edit the
[./examples/example0.c](./examples/example0.c) file. There are two entry
points into that file:

| Function | Usage |
| ---------| -----|
|init()| Called once at the start of the app|
|main_loop(time)| Called every frame with time being time since app start|

You can also add your own entry files in the examples directory, and then pass them to the build script using the _MAIN_ variable. For example:

```{sh}
make build MAIN=examples/example1.c
```

This will build the WASM file using `example1.c` as the entry point.

### Getting Started

#### API

The API calls try to emulate [gfx][gfx] as much as possible. Here are a few currently supported functions (see the documentation for a full reference):

| Function | Does |
| ---------| -----|
|wefx_open(width, height, title) | Create a canvas on which to draw |
|wefx_clear_color(red, green, blue) | Set the background color |
|wefx_color(red, green, blue) | Set the drawing color |
|wefx_point(x, y) | Draw a single point |
|wefx_line(x1, y1, x2, y2) | Draw a line from (x1,y1) to (x2,y2) |
|wefx_clear() | Clear the canvas using the background color |

#### Coordinate System

The coordinate system in newer versions has changed to reflect most other drawing styles. The system works thusly:

```
      +Y
       |
       |
       |
       |
 (0,0) +---------- +X

```

In version 1 (or earlier) of the library, the positive Y was flipped:

```
 (0,0) +---------- +X
       |
       |
       |
       |
      +Y
```

### Windows OS

I have not run this on Windows, but you should be able to build it with Visual
Studio. You will have to install `clang` as an add on, and then setup the
build flags to the ones shown in the `Makefile`.

[gfx]: https://www3.nd.edu/~dthain/courses/cse20211/fall2013/gfx/
[video]: https://www.youtube.com/watch?v=vrqixVOd-rc
[webassembly]: https://en.wikipedia.org/wiki/WebAssembly
[htmlcanvas]: https://en.wikipedia.org/wiki/Canvas_element
