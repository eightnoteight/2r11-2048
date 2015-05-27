# How to build it?

After clone ``2r11-2048`` you need to initialize the submodules:

``git submodule update --init``

If you want to build the version that uses ``accacia`` instead of ``ncurses`` using [Hefesto](https://github.com/rafael-santiago/hefesto.git):

After to follow the steps to get ``Hefesto`` installed on your system, being inside the root of ``2r11-2048`` subdirectory just type:

``hefesto``

The above comand will build the standard version of ``2r11-2048`` and the following command will generate a "vintage"
minimalist version of ``2r11-2048`` that uses ``libaccacia``.

``hefesto --cflags=-DUSE_ACCACIA``

On both cases the binary will be generated inside the ``bin`` subdirectory named as ``2048``.

# How to build it without Hefesto?

Without hefesto try to run the shell script ``build.sh``.

If you want to generate a version that uses ``libacaccia`` in replacement of ``ncurses`` you should add the following
line inside the ``2048.h`` file (just after the includes section) before run ``build.sh``:

``#define USE_ACCACIA 1``
