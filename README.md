# FrozenCore
A game engine with C++ scripting.
Loads all external game code dynamically as plugin-style modules.

It currently only supports Linux and GCC but will eventually also support Windows 10.

# Build

Dependencies:
glfw
glew
freetype2

Create makefiles for your modules and add their path to the root makefile.

Add your modules to the config file at `Data/Engine.conf`

Run `make all` or `make run` in the root directory to build the engine and all modules.
