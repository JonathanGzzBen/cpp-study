# SimpleApp Cross Compiled

This program can be compiled from Linux to Windows to create a GUI application contained in single binary.

The requirement is to have wxWidgets compiled in a prefix that can be set in the variable `WX_PREFIX` in the `Makefile` file.

wxWidgets should be compiled statically in order to produce a single `.exe` binary.

The command for static compiling wxWidgets is:

```shell

$ ./configure --host=x86_64-w64-mingw32 --target=x86_64-w64-mingw32 --prefix=/usr/local/wxwidgets-mingw64 --disable-shared
$ make
# make install

```

Where the host and target can be changed depending on the compiler being used and the prefix can be any custom path.
