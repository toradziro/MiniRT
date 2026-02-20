#!/bin/bash
clang -Werror -Wall -Wextra -std=c11 -march=native -O3 `sdl2-config --cflags` -DTHREADS_MAX=12 srcs/main.c -lm `sdl2-config --libs` -o MiniRT
