# SockNet

(for functions documentation, see **socknet.h**)

### C socket programming made easy (hopefully)

Socknet is networking library with the goal of wrapping socket programming around the concept of network modules. It allows the user to send data of a custom size between a **server** and multiple **clients**.

It is developped for use in my epitech projects so the source code abide to the epitech coding-style rules.

## Dependencies

- [GNU Compiler Collection](https://gcc.gnu.org/) (11.4.0+)
- [GNU Make](https://www.gnu.org/software/make/) (4.3+)
- [CLogger](https://github.com/alexishachemi/clogger) (any)
- [Linked](https://github.com/alexishachemi/linked) (any)
- [Doxygen](https://www.doxygen.nl/) (1.9.1+) (only for documentation)

## Building

to build the library you can use the included Makefile:

```sh
make
```

It will then build the `libsocknet.a` binary.

## Installing

Custom Makefile rules (`install`, `uninstall`, `reinstall`) can be used to manage installation of the library in your system:

```sh
make install
```

## Usage

Once installed or built, you can use the library by including the library header in your source files:

```c
#include <socknet.h>
```

and add the library to the linker when compiling:

```sh
gcc myfile.c -lsocknet
```

For more information about how to use the library, see the [example client](tests/client.c) and [example server](tests/server.c).

You can also generate Doxygen documentation using the apropriate makefile rule:

```sh
make docs
```

once generated, just open `docs/html/index.html` on your browser.
