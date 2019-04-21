cmake_minimum_required(VERSION 3.14)
project(CSG)

set(CMAKE_CXX_STANDARD 14)

include_directories(code.3d/include)
include_directories(libg3x/include)

set(files
        code.3d/include/cone.h
        code.3d/include/cube.h
        code.3d/include/cylinder.h
        code.3d/include/file.h
        code.3d/include/matrix.h
        code.3d/include/object.h
        code.3d/include/sphere.h
        code.3d/include/stack.h
        code.3d/include/torus.h
        code.3d/include/tree.h
        code.3d/src/cone.c
        code.3d/src/cube.c
        code.3d/src/cylinder.c
        code.3d/src/file.c
        code.3d/src/main.c
        code.3d/src/matrix.c
        code.3d/src/object.c
        code.3d/src/sphere.c
        code.3d/src/stack.c
        code.3d/src/torus.c
        code.3d/src/tree.c
        code.3d/Makefile
        libg3x/include/g3x.h
        libg3x/include/g3x_basix.h
        libg3x/include/g3x_capture.h
        libg3x/include/g3x_colors.h
        libg3x/include/g3x_GLtransfo.h
        libg3x/include/g3x_macros.h
        libg3x/include/g3x_pnm.h
        libg3x/include/g3x_quaternions.h
        libg3x/include/g3x_tools.h
        libg3x/include/g3x_transfo.h
        libg3x/include/g3x_types.h
        libg3x/include/g3x_window.h
        libg3x/include/mtracer.h
        libg3x/libg3x.32b++.so
        libg3x/libg3x.32b.so
        libg3x/libg3x.64b++.so
        libg3x/libg3x.64b.so)
